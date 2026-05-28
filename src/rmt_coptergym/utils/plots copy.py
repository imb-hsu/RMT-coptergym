import os
import numpy as np
import pandas as pd
import ast # Safe evaluation of string literals
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D

class EvaluationPlots:
    """
    Generiert eine Reihe von detaillierten Plots zur qualitativen Analyse
    einer einzelnen Evaluations-Episode.
    """
    def __init__(self, save_dir: str, tolerance_position: float = 0.1, tolerance_velocity: float = 0.1):
        """
        Initialisiert die Plotting-Klasse.

        Args:
            save_dir (str): Verzeichnis, in dem die Plots gespeichert werden.
            tolerance_position (float): Toleranz für Positionsfehler-Visualisierungen.
            tolerance_velocity (float): Toleranz für Geschwindigkeitsfehler-Visualisierungen.
        """
        self.save_dir = save_dir
        os.makedirs(self.save_dir, exist_ok=True)
        self.tolerance_position = tolerance_position
        self.tolerance_velocity = tolerance_velocity
        self.plotted_targets = set()

    def _parse_vector_col(self, series: pd.Series) -> np.ndarray:
        """Hilfsfunktion, um eine Spalte mit Vektor-Strings in ein NumPy-Array umzuwandeln."""
        try:
            # Sicherstellen, dass die Daten bereits als Listen/Arrays vorliegen
            if not series.empty and isinstance(series.iloc[0], (np.ndarray, list)):
                return np.array(series.tolist())

            # Bestimme die erwartete Vektorlänge aus dem ersten gültigen Eintrag
            first_valid = series.dropna().iloc[0] if not series.dropna().empty else None
            if first_valid:
                # Parse den ersten gültigen Eintrag, um die Dimension zu erhalten
                first_vec = ast.literal_eval(first_valid) if isinstance(first_valid, str) else first_valid
                vec_len = len(first_vec)
            else:
                vec_len = 3 # Standard-Fallback, wenn die Spalte komplett leer ist

            # Sicherer Parser, der bei Fehlern einen NaN-Vektor der korrekten Länge zurückgibt
            def safe_eval(x):
                if isinstance(x, str) and x.strip() and x != 'nan':
                    return ast.literal_eval(x)
                return np.full(vec_len, np.nan)

            return np.array(series.apply(safe_eval).tolist())
        except Exception:
            # Finaler Fallback, falls alles andere fehlschlägt
            return np.full((len(series), 3), np.nan)

    def create_all_plots(self, logdata_df: pd.DataFrame):
        """
        Erstellt alle verfügbaren Evaluations-Plots für den gegebenen DataFrame.

        Args:
            logdata_df (pd.DataFrame): DataFrame mit den geloggten Daten einer Episode.
        """
        print(f"  > Erstelle detaillierte Plots in: {self.save_dir}")
        
        # --- Datenextraktion und -aufbereitung ---
        # Extrahiere Spalten sicher und fülle sie mit NaNs, falls sie nicht existieren.
        times = logdata_df['sim_time']
        position = self._parse_vector_col(logdata_df.get('agent_pos', pd.Series([np.nan] * len(times))))
        x_pos, y_pos, z_pos = position[:, 0], position[:, 1], position[:, 2]
        
        rewards = logdata_df.get('reward', pd.Series([np.nan] * len(times)))
        velocity = self._parse_vector_col(logdata_df.get('agent_vel_c', pd.Series([np.nan] * len(times))))
        rpy = self._parse_vector_col(logdata_df.get('agent_rpy_deg', pd.Series([np.nan] * len(times))))
        omegas = self._parse_vector_col(logdata_df.get('agent_omega', pd.Series([np.nan] * len(times))))
        accel = self._parse_vector_col(logdata_df.get('agent_accel', pd.Series([np.nan] * len(times))))
        
        target_position_array = self._parse_vector_col(logdata_df.get('mission_goal_pos', pd.Series([np.nan] * len(times))))
        target_x, target_y, target_z = target_position_array[:, 0], target_position_array[:, 1], target_position_array[:, 2]
        
        target_velocity = self._parse_vector_col(logdata_df.get('mission_goal_vel', pd.Series([np.nan] * len(times))))
        motor_cmds = self._parse_vector_col(logdata_df.get('action_cmd', pd.Series([np.nan] * len(times))))
        motor_signals = self._parse_vector_col(logdata_df.get('motor_signal_measured_rps', pd.Series([np.nan] * len(times))))
        
        distance = logdata_df.get('distance_current', pd.Series([np.nan] * len(times)))
        error_pos = self._parse_vector_col(logdata_df.get('error_pos', pd.Series([np.nan] * len(times))))
        error_vel = self._parse_vector_col(logdata_df.get('error_vel_c', pd.Series([np.nan] * len(times))))

        # --- Reward-Komponenten extrahieren und parsen ---
        reward_components = {}
        if 'reward_terms' in logdata_df.columns and not logdata_df['reward_terms'].isnull().all():
            
            def safe_parse_reward_dict(entry):
                # Fall 1: Es ist bereits ein Dictionary -> perfekt!
                if isinstance(entry, dict):
                    return entry
                # Fall 2: Es ist ein String -> versuche, es zu parsen
                if isinstance(entry, str):
                    try:
                        return ast.literal_eval(entry)
                    except (ValueError, SyntaxError):
                        return None # Parsing fehlgeschlagen
                # Fall 3: Es ist etwas anderes (z.B. NaN) -> ignorieren
                return None

            # Wende die sichere Parsing-Funktion an und entferne leere Einträge
            parsed_terms = logdata_df['reward_terms'].apply(safe_parse_reward_dict).dropna()

            if not parsed_terms.empty:
                # Umstrukturieren für einfaches Plotten
                for term_dict in parsed_terms:
                    for name, values in term_dict.items():
                        # Stelle sicher, dass die Struktur korrekt ist ('w' und 'r' sind vorhanden)
                        if isinstance(values, dict) and 'w' in values and 'r' in values:
                             reward_components.setdefault(name, []).append(values)

        # --- 3D Position Plot ---
        self.plot_3d_trajectory(x_pos, y_pos, z_pos, target_x, target_y, target_z)

        # --- Reward Plots (nur wenn Reward-Daten vorhanden sind) ---
        if not rewards.isnull().all() and reward_components:
            reward_func_name = logdata_df['reward_function'].iloc[0] if 'reward_function' in logdata_df.columns else 'N/A'
            self.plot_rewards(times, rewards, reward_components, reward_func_name)

        # --- Positions Over Time Plot ---
        self.plot_position_2d(times, x_pos, y_pos, z_pos, target_x, target_y, target_z)

        # --- Velocities Over Time Plot ---
        self.plot_velocities(times, velocity, target_velocity)

        # --- RPY Over Time Plot ---
        self.plot_rpy(times, rpy)

        # --- Omega Over Time Plot ---
        self.plot_omegas(times, omegas)

        # --- Accel Over Time Plot ---
        self.plot_accel(times, accel)

        # --- Motorsignals Over Time Plot ---
        if not np.isnan(motor_signals).all() or not np.isnan(motor_cmds).all():
            self.plot_motor_signals(times, motor_signals, motor_cmds)

        # --- Error/Progress Over Time Plot ---
        self.plot_progress(times, distance, error_pos, velocity, error_vel)


    def plot_3d_trajectory(self, x, y, z, tx, ty, tz):
        fig = plt.figure(figsize=(10, 8))
        ax = fig.add_subplot(111, projection='3d')
        
        # Plot Agent Trajectory if available
        if not np.all(np.isnan([x, y, z])):
            ax.plot(x, y, z, color="blue", label="Drohnen-Trajektorie", alpha=0.8)
            ax.scatter(x[0], y[0], z[0], s=50, color="green", label="Start", depthshade=True)
            ax.scatter(x[-1], y[-1], z[-1], s=50, color="red", label="Ende", depthshade=True)

        # Plot Target Trajectory if available
        if not np.all(np.isnan([tx, ty, tz])):
            ax.plot(tx, ty, tz, color="darkorange", linestyle="--", label="Ziel-Trajektorie")
            unique_targets = np.unique(np.c_[tx, ty, tz], axis=0)
            ax.scatter(unique_targets[:,0], unique_targets[:,1], unique_targets[:,2], color="orange", s=50, marker='x', label="Wegpunkte")

        ax.set_xlabel("X [m]"); ax.set_ylabel("Y [m]"); ax.set_zlabel("Z [m]")
        ax.set_title("3D Trajektorie")
        ax.legend()
        ax.grid(True)
        # ax.invert_zaxis() # Je nach Koordinatensystem anpassen
        plt.savefig(os.path.join(self.save_dir, "1_Trajectory_3D.png"))
        plt.close()

    def plot_rewards(self, times, total_rewards, components: dict, reward_func_name: str):
        """
        Erstellt einen detaillierten Plot der Reward-Komponenten.
        """
        fig, axs = plt.subplots(3, 1, figsize=(12, 15), sharex=True)
        fig.suptitle(f"Reward-Analyse (Funktion: {reward_func_name})", fontsize=16)

        # --- Plot 1: Total Reward ---
        axs[0].plot(times, total_rewards, label="Gesamt-Reward (final)", color="black")
        axs[0].fill_between(times, 0, 1, color="green", alpha=0.1, label="Positiver Bereich")
        axs[0].fill_between(times, -1, 0, color="red", alpha=0.1, label="Negativer Bereich")
        axs[0].set_ylabel("Reward")
        axs[0].set_title("Finaler Reward pro Schritt (inkl. Boni/Strafen)")
        axs[0].legend(); axs[0].grid(True)

        # --- Plot 2: Gestapelte, gewichtete Reward-Terme ---
        labels = list(components.keys())
        # Extrahiere gewichtete Werte: w * r
        weighted_values = [
            [d['w'] * d['r'] for d in components[label]] for label in labels
        ]
        
        axs[1].stackplot(times, weighted_values, labels=[f"{label} (w*r)" for label in labels])
        axs[1].set_ylabel("Gewichteter Reward-Anteil")
        axs[1].set_title("Anteil der Komponenten am Basis-Reward")
        axs[1].legend(loc='upper left'); axs[1].grid(True)
        axs[1].axhline(0, color='black', linewidth=0.8, linestyle='--')

        # --- Plot 3: Ungewichtete (rohe) Reward-Terme ---
        # Extrahiere rohe Werte: r
        raw_values = [
            [d['r'] for d in components[label]] for label in labels
        ]
        
        for i, label in enumerate(labels):
            axs[2].plot(times, raw_values[i], label=f"{label} (roh)")

        axs[2].set_ylim(0, 1.05)
        axs[2].set_ylabel("Ungewichteter Reward")
        axs[2].set_title("Rohe Performance pro Komponente (0-1)")
        axs[2].legend(loc='lower left'); axs[2].grid(True)
        
        axs[2].set_xlabel("Zeit [s]")
        plt.tight_layout(rect=[0, 0.03, 1, 0.96])
        plt.savefig(os.path.join(self.save_dir, "2_Rewards_In_Detail.png"))
        plt.close()

    def plot_position_2d(self, times, x, y, z, tx, ty, tz):
        fig, axs = plt.subplots(1, 2, figsize=(16, 8))
        
        # XY-Plot
        if not np.all(np.isnan([x, y])):
            axs[0].plot(x, y, color="blue", alpha=0.8, label="Drohne")
            axs[0].scatter(x[0], y[0], color="green", s=50, label="Start")
            axs[0].scatter(x[-1], y[-1], facecolors="none", edgecolors="blue", s=50, label="Ende")
        
        if not np.all(np.isnan([tx, ty])):
            axs[0].plot(tx, ty, linestyle="--", color="darkorange", label="Ziel")
            
            for t_x, t_y in np.unique(np.c_[tx, ty], axis=0):
                circle = plt.Circle((t_x, t_y), radius=self.tolerance_position, color="orange", alpha=0.2)
                axs[0].add_patch(circle)

        axs[0].set_xlabel("X-Position [m]"); axs[0].set_ylabel("Y-Position [m]")
        axs[0].set_title("Position in der XY-Ebene")
        axs[0].set_aspect('equal', adjustable='box')
        axs[0].legend(); axs[0].grid(True)

        # Z-Plot
        if not np.all(np.isnan(z)):
            axs[1].plot(times, z, label="Agent", color="blue")
        
        if not np.all(np.isnan(tz)):
            axs[1].plot(times, tz, label="Target", linestyle="--", color="darkorange")
            axs[1].fill_between(times, tz - self.tolerance_position, tz + self.tolerance_position, color="orange", alpha=0.2)
        axs[1].set_xlabel("Zeit [s]"); axs[1].set_ylabel("Z-Position [m]")
        axs[1].set_title("Höhenprofil")
        axs[1].legend(); axs[1].grid(True)

        plt.tight_layout()
        plt.savefig(os.path.join(self.save_dir, "3_Position_Over_Time.png"))
        plt.close()

    def plot_velocities(self, times, velocity, target_velocity):
        fig, axs = plt.subplots(3, 1, figsize=(12, 10), sharex=True)
        fig.suptitle("Geschwindigkeiten im Kontroll-Frame (u, v, w)")
        for idx, axis in enumerate(["u", "v", "w"]):
            if not np.all(np.isnan(velocity[:, idx])):
                axs[idx].plot(times, velocity[:, idx], label=f"Agent {axis}-Vel", color="blue")
            
            if not np.all(np.isnan(target_velocity[:, idx])):
                axs[idx].plot(times, target_velocity[:, idx], color="darkorange", linestyle="--", label=f"Target {axis}-Vel")
                axs[idx].fill_between(times, target_velocity[:, idx] - self.tolerance_velocity, target_velocity[:, idx] + self.tolerance_velocity, color="orange", alpha=0.2)
            axs[idx].set_ylabel(f"{axis}-Geschwindigkeit [m/s]"); axs[idx].legend(); axs[idx].grid(True)
        axs[2].set_xlabel("Zeit [s]")
        plt.tight_layout(rect=[0, 0, 1, 0.97])
        plt.savefig(os.path.join(self.save_dir, "4_Velocities_Over_Time.png"))
        plt.close()

    def plot_rpy(self, times, rpy):
        fig, axs = plt.subplots(3, 1, figsize=(12, 10), sharex=True)
        fig.suptitle("Lage (Roll, Pitch, Yaw)")
        for idx, axis in enumerate(["Roll", "Pitch", "Yaw"]):
            axs[idx].plot(times, rpy[:, idx], label=f"{axis}", color="blue")
            axs[idx].set_ylabel(f"{axis} [deg]"); axs[idx].legend(); axs[idx].grid(True)
        axs[2].set_xlabel("Zeit [s]")
        plt.tight_layout(rect=[0, 0, 1, 0.97])
        plt.savefig(os.path.join(self.save_dir, "5_RPY_Over_Time.png"))
        plt.close()

    def plot_omegas(self, times, omegas):
        fig, axs = plt.subplots(3, 1, figsize=(12, 10), sharex=True)
        fig.suptitle("Winkelgeschwindigkeiten (p, q, r)")
        for idx, axis in enumerate(["p (Roll)", "q (Pitch)", "r (Yaw)"]):
            axs[idx].plot(times, omegas[:, idx], label=f"Omega {axis}", color="blue")
            axs[idx].set_ylabel(f"Omega [rad/s]"); axs[idx].legend(); axs[idx].grid(True)
        axs[2].set_xlabel("Zeit [s]")
        plt.tight_layout(rect=[0, 0, 1, 0.97])
        plt.savefig(os.path.join(self.save_dir, "6_Omega_Over_Time.png"))
        plt.close()

    def plot_accel(self, times, accel):
        fig, axs = plt.subplots(3, 1, figsize=(12, 10), sharex=True)
        fig.suptitle("Beschleunigung (ax, ay, az)")
        for idx, axis in enumerate(["x", "y", "z"]):
            axs[idx].plot(times, accel[:, idx], label=f"Accel. {axis}", color="blue")
            axs[idx].set_ylabel(f"Accel. [m/s^2]"); axs[idx].legend(); axs[idx].grid(True)
        axs[2].set_xlabel("Zeit [s]")
        plt.tight_layout(rect=[0, 0, 1, 0.97])
        plt.savefig(os.path.join(self.save_dir, "6_Accel_Over_Time.png"))
        plt.close()

    def plot_motor_signals(self, times, motor_signals, motor_cmds):
        fig, axs = plt.subplots(4, 1, figsize=(12, 12), sharex=True)
        fig.suptitle("Motorsignale (Soll vs. Ist)")
    
        groups = {
            "Gruppe 1 (vorne re)": (0, 5),
            "Gruppe 2 (vorne li)": (1, 4),
            "Gruppe 3 (hinten li)": (2, 7),
            "Gruppe 4 (hinten re)": (3, 6)
        }
        
        for i, (name, (idx1, idx2)) in enumerate(groups.items()):
            # Soll-Werte (aus Action)
            if not np.all(np.isnan(motor_cmds)):
                axs[i].plot(times, motor_cmds[:, idx1], label=f"Soll Ober", color="red", alpha=0.7, ls='--')
                axs[i].plot(times, motor_cmds[:, idx2], label=f"Soll Unter", color="orange", alpha=0.7, ls='--')
            # Ist-Werte (gemessen)
            if not np.all(np.isnan(motor_signals)):
                axs[i].plot(times, motor_signals[:, idx1], label=f"Ist Ober", color="blue")
                axs[i].plot(times, motor_signals[:, idx2], label=f"Ist Unter", color="cyan")
            
            axs[i].set_ylabel("Drehzahl [rad/s]")
            axs[i].legend(ncol=2)
            axs[i].grid(True)
            axs[i].set_title(name)
            # axs[i].set_ylim(bottom=0)

        axs[3].set_xlabel("Zeit [s]")
        plt.tight_layout(rect=[0, 0, 1, 0.97])
        plt.savefig(os.path.join(self.save_dir, "7_Motorcmds_Over_Time.png"))
        plt.close()

    def plot_progress(self, times, distance, error_pos, velocity, error_vel):
        fig, axs = plt.subplots(2, 2, figsize=(16, 10))
        fig.suptitle("Fehler und Fortschritt über Zeit")

        # Distanz zum Ziel
        axs[0, 0].plot(times, distance, color="red", label="Distanz zum Ziel")
        axs[0, 0].set_xlabel("Zeit [s]"); axs[0, 0].set_ylabel("Distanz [m]")
        axs[0, 0].legend(); axs[0, 0].grid(True)
        axs[0, 0].set_title("Gesamtdistanz zum Ziel")

        # Positionsfehler
        colormap = {"X": "darkred", "Y": "darkblue", "Z": "darkgreen"}
        for idx, axis in enumerate(["X", "Y", "Z"]):
            axs[1, 0].plot(times, error_pos[:, idx], label=f"{axis}-Fehler", color=colormap[axis])
        axs[1, 0].fill_between(times, -self.tolerance_position, self.tolerance_position, color="orange", alpha=0.2, label="Toleranz")
        axs[1, 0].set_xlabel("Zeit [s]"); axs[1, 0].set_ylabel("Positionsfehler [m]")
        axs[1, 0].set_ylim(-self.tolerance_position * 2.5, self.tolerance_position * 2.5)
        axs[1, 0].legend(); axs[1, 0].grid(True)
        axs[1, 0].set_title("Positionsfehler (im Kontroll-Frame)")

        # Gesamtgeschwindigkeit
        axs[0, 1].plot(times, np.linalg.norm(velocity, axis=1), label="Agent-Geschwindigkeit", color="red")
        axs[0, 1].set_xlabel("Zeit [s]"); axs[0, 1].set_ylabel("Geschwindigkeit [m/s]")
        axs[0, 1].legend(); axs[0, 1].grid(True)
        axs[0, 1].set_title("Gesamtgeschwindigkeit des Agenten")

        # Geschwindigkeitsfehler
        for idx, axis in enumerate(["u", "v", "w"]):
            axs[1, 1].plot(times, error_vel[:, idx], label=f"{axis}-Fehler", color=colormap[list(colormap.keys())[idx]])
        axs[1, 1].fill_between(times, -self.tolerance_velocity, self.tolerance_velocity, color="orange", alpha=0.2, label="Toleranz")
        axs[1, 1].set_xlabel("Zeit [s]"); axs[1, 1].set_ylabel("Geschwindigkeitsfehler [m/s]")
        axs[1, 1].set_ylim(-self.tolerance_velocity * 2.5, self.tolerance_velocity * 2.5)
        axs[1, 1].legend(); axs[1, 1].grid(True)
        axs[1, 1].set_title("Geschwindigkeitsfehler (im Kontroll-Frame)")

        plt.tight_layout(rect=[0, 0, 1, 0.96])
        plt.savefig(os.path.join(self.save_dir, "8_Progress_Over_Time.png"))
        plt.close()