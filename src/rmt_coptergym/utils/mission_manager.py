# Speichern als: gym_env/utils/mission_manager.py

import numpy as np
import pandas as pd
import os
import matplotlib.pyplot as plt
import ast

# Wichtig: Der DataLoader wird jetzt hier importiert, damit der Test funktioniert.
from .trajectory_dataloader import TrajectoryDataLoader

class MissionManager:
    """
    Verwaltet den Zustand einer EINZELNEN, bereits geladenen Mission für eine Episode.
    """
    def __init__(self, trajectory_df: pd.DataFrame):
        self.waypoints = trajectory_df.to_dict('records')
        if not self.waypoints:
            raise ValueError("Provided trajectory DataFrame is empty.")

        self.name = trajectory_df['mission_name'].iloc[0] if 'mission_name' in trajectory_df.columns else 'Unnamed Mission'
        self.is_mission_complete = False
        self.initial_state = self._group_vectors(self.waypoints[0])
        self.target_waypoint_index = 1 if len(self.waypoints) > 1 else 0
        
        self.current_goal_state = {}
        self._update_persistent_goal()
        self.goal = self.current_goal_state.copy()

    def _group_vectors(self, flat_waypoint: dict) -> dict:
        grouped_wp = {}
        # Check for both direct vector keys (e.g., 'pos') and component keys (e.g., 'pos_x')
        for vec_name in ['pos', 'vel', 'vel_limit', 'rpy']:
            # Priority 1: Check for a direct vector key (e.g., 'pos': [0,0,-10])
            if vec_name in flat_waypoint and isinstance(flat_waypoint[vec_name], (np.ndarray, list, tuple)):
                value = flat_waypoint[vec_name]
                if not any(pd.isna(c) for c in value):
                    grouped_wp[vec_name] = np.array(value)
            # Priority 2: Fallback to component keys (e.g., 'pos_x', 'pos_y', 'pos_z')
            else:
                axes = ['x', 'y', 'z']
                components = [flat_waypoint.get(f'{vec_name}_{axis}') for axis in axes]
                if not any(pd.isna(c) for c in components):
                    grouped_wp[vec_name] = np.array(components)

        for scalar_name in ['time', 'thrust']:
            if pd.notna(flat_waypoint.get(scalar_name)):
                grouped_wp[scalar_name] = flat_waypoint[scalar_name]
        return grouped_wp
    
    def _update_persistent_goal(self):
        targets = self._group_vectors(self.waypoints[self.target_waypoint_index])
        self.current_goal_state.update(targets)

    def update_goal(self, env_time: float, is_current_goal_achieved: bool = False):
        if self.is_mission_complete: return
        is_at_last = self.target_waypoint_index == len(self.waypoints) - 1
        if is_at_last and is_current_goal_achieved:
            self.is_mission_complete = True; return
        next_target_idx = self.target_waypoint_index + 1
        if next_target_idx < len(self.waypoints):
            next_wp = self.waypoints[next_target_idx]
            next_time = next_wp.get('time', np.nan)
            time_triggered = pd.notna(next_time) and env_time >= next_time
            success_triggered = pd.isna(next_time) and is_current_goal_achieved
            if time_triggered or success_triggered:
                self.target_waypoint_index = next_target_idx
                self._update_persistent_goal()
        self.goal = self.current_goal_state.copy()
        if self.target_waypoint_index == len(self.waypoints) - 1 and 'pos' in self.goal:
            self.goal.setdefault('vel', np.zeros(3))
            self.goal.setdefault('rpy', np.zeros(3))

# --- Eigenständige Test- und Visualisierungsfunktionen ---

def plot_mission_results(results_df: pd.DataFrame):
    """
    Visualisiert die Ergebnisse eines Simulationslaufs aus einer benchmark_results.csv.
    Erstellt ein Fenster mit zwei Subplots: 3D-Trajektorie und Geschwindigkeits-Time-Series.
    """
    # Helper to convert string representations of lists to numpy arrays
    def parse_vector(s):
        try:
            # ast.literal_eval is safer than eval
            return np.array(ast.literal_eval(s.replace(' ', ',')))
        except (ValueError, SyntaxError):
            return np.array([np.nan, np.nan, np.nan])

    # --- Data Preparation ---
    # Apply the parser to all vector-like columns
    for col in ['agent_pos', 'mission_goal_pos', 'agent_vel_c', 'command_vel_c', 'mission_goal_vel']:
        if col in results_df.columns:
            results_df[col] = results_df[col].apply(parse_vector)

    mission_name = results_df['mission_name'].iloc[0] if 'mission_name' in results_df.columns else 'Benchmark'

    # --- Plotting ---
    fig, (ax1, ax2) = plt.subplots(1, 2, figsize=(18, 8))
    fig.suptitle(f"Benchmark Results: {mission_name}", fontsize=16)

    # --- Plot 1: 3D Position Trajectory ---
    ax1 = fig.add_subplot(1, 2, 1, projection='3d')
    agent_pos_data = np.stack(results_df['agent_pos'].to_numpy())
    mission_goal_pos_data = np.stack(results_df['mission_goal_pos'].to_numpy())

    # Plot Agent's actual path
    ax1.plot(agent_pos_data[:, 0], agent_pos_data[:, 1], agent_pos_data[:, 2], color='blue', linestyle='-', label='Agent Path')
    ax1.scatter(agent_pos_data[0, 0], agent_pos_data[0, 1], agent_pos_data[0, 2], c='green', s=100, label='Start', depthshade=True)
    ax1.scatter(agent_pos_data[-1, 0], agent_pos_data[-1, 1], agent_pos_data[-1, 2], c='red', s=100, label='End', depthshade=True)

    # Plot Mission Goal Waypoints
    # Find unique waypoints to avoid overplotting
    unique_goals, indices = np.unique(mission_goal_pos_data, axis=0, return_index=True)
    unique_goals = unique_goals[np.isfinite(unique_goals).all(axis=1)] # Filter out NaN goals
    if unique_goals.size > 0:
        ax1.scatter(unique_goals[:, 0], unique_goals[:, 1], unique_goals[:, 2], c='magenta', marker='x', s=150, label='Waypoints', depthshade=True)

    ax1.set_xlabel('X'); ax1.set_ylabel('Y'); ax1.set_zlabel('Z')
    ax1.set_title("Position Trajectory (3D)")
    ax1.legend()
    ax1.grid(True)

    # --- Plot 2: Velocity Profile ---
    time_axis = results_df['sim_time']
    agent_vel_data = np.stack(results_df['agent_vel_c'].to_numpy())
    command_vel_data = np.stack(results_df['command_vel_c'].to_numpy())

    # Agent Velocity
    ax2.plot(time_axis, agent_vel_data[:, 0], color='r', linestyle='-', label='Agent Vel X')
    ax2.plot(time_axis, agent_vel_data[:, 1], color='g', linestyle='-', label='Agent Vel Y')
    ax2.plot(time_axis, agent_vel_data[:, 2], color='b', linestyle='-', label='Agent Vel Z')

    # Commanded Velocity
    ax2.plot(time_axis, command_vel_data[:, 0], color='r', linestyle='--', alpha=0.7, label='Command Vel X')
    ax2.plot(time_axis, command_vel_data[:, 1], color='g', linestyle='--', alpha=0.7, label='Command Vel Y')
    ax2.plot(time_axis, command_vel_data[:, 2], color='b', linestyle='--', alpha=0.7, label='Command Vel Z')

    ax2.set_xlabel("Time (s)")
    ax2.set_ylabel('Velocity (m/s)')
    ax2.set_title("Velocity Profile")
    ax2.legend()
    ax2.grid(True)
    ax2.axhline(0, color='black', linewidth=0.5) # Nulllinie

    plt.tight_layout(rect=[0, 0.03, 1, 0.95]) # Passt Layout an den Haupttitel an
    plt.show(block=False)
    plt.pause(0.1)

# Dieser Block wird nur ausgeführt, wenn mission_manager.py direkt gestartet wird
if __name__ == '__main__':
    print("--- Starte MissionManager im Visualisierungs-Modus ---")
    
    # --- 1. Lade eine Benchmark-Ergebnisdatei ---
    try:
        # Pfad zur Beispieldatei (passen Sie dies bei Bedarf an)
        script_dir = os.path.dirname(__file__)
        project_root = os.path.dirname(os.path.dirname(os.path.dirname(script_dir)))
        # Beispiel: Lade die Ergebnisse für die 'Position_Square' Mission aus dem INDI-Benchmark
        results_path = os.path.join(project_root, 'data', 'INDI', 'Position_Square', 'benchmark_results.csv')
        
        if not os.path.exists(results_path):
            raise FileNotFoundError(f"Ergebnisdatei nicht gefunden: {results_path}\nFühren Sie zuerst einen Benchmark-Lauf durch.")

        print(f"Lade Ergebnisdatei: {results_path}")
        results_df = pd.read_csv(results_path)

    except FileNotFoundError as e:
        print(f"\nFehler: {e}")
        exit()

    # --- 2. Visualisiere die Ergebnisse ---
    plot_mission_results(results_df)

    print("\nTest-Skript beendet. Schließen Sie das Plot-Fenster, um das Programm zu beenden.")
    plt.show() # Hält das Skript an, damit der Plot sichtbar bleibt