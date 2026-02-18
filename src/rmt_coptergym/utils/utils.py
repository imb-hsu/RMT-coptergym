import os
import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
from stable_baselines3 import PPO
from stable_baselines3.common.env_util import make_vec_env
from stable_baselines3.common.vec_env import DummyVecEnv

# Import your custom environment
from rmt_coptergym.application_envs.RL_E2E_Env import E2E_Env

def merge_datasets(datasets: dict, names_to_merge: list) -> dict:
    """
    Merges multiple full mission datasets into a single training dataset.
    It intelligently excludes the first trajectory (index 0) of each mission
    to prevent data leakage into the training set.
    """
    if not names_to_merge: return {}
    # Find a valid template name that exists in the datasets
    template_name = next((name for name in names_to_merge if name in datasets), None)
    if template_name is None: return {}

    merged_dataset = {field: [] for field in datasets[template_name].keys()}
    for name in names_to_merge:
        if name in datasets:
            for field, data in datasets[name].items():
                # IMPORTANT: Exclude the first trajectory (eval) to avoid data leakage
                if data.shape[0] > 1:
                    merged_dataset[field].append(data[1:, ...]) # Use ellipsis for >2D arrays
    for field in merged_dataset:
        if merged_dataset[field]:
            merged_dataset[field] = np.concatenate(merged_dataset[field], axis=0)
        else: # Handle case where only single-trajectory missions were provided
            # Create an empty array with the correct shape
            template_shape = list(datasets[template_name][field].shape)
            template_shape[0] = 0
            merged_dataset[field] = np.empty(template_shape, dtype=datasets[template_name][field].dtype)
    return merged_dataset

def extract_eval_trajectories(datasets: dict, names_for_eval: list) -> dict:
    """
    Extracts ONLY the first trajectory (index 0) from specified datasets
    and merges them into a single evaluation set.
    """
    if not names_for_eval: return {}
    template_name = next((name for name in names_for_eval if name in datasets), None)
    if template_name is None: return {}

    eval_dataset = {field: [] for field in datasets[template_name].keys()}
    for name in names_for_eval:
        if name in datasets:
            for field, data in datasets[name].items():
                # Extract only the first trajectory (index 0)
                eval_dataset[field].append(data[0:1, ...]) # Use ellipsis for >2D arrays
    for field in eval_dataset:
        eval_dataset[field] = np.concatenate(eval_dataset[field], axis=0)
    return eval_dataset

def run_qualitative_evaluation(model_path: str, eval_pool: list, config: dict, save_dir: str):
    """
    Loads the best model and runs it on each evaluation trajectory individually,
    saving the results for plotting.
    """
    print("\n" + "="*80)
    print("STARTING QUALITATIVE EVALUATION FOR PLOTTING")
    print("="*80)

    model = PPO.load(model_path)

    for mission_dict in eval_pool:
        mission_name = mission_dict['name']
        
        # --- DER TRICK ---
        # Erstelle eine Environment, deren Pool NUR aus dieser einen Mission besteht.
        single_mission_pool = [mission_dict]
        eval_env_kwargs = {**config['env_kwargs'], 'mission_pool': single_mission_pool, 'is_eval': True}
        env = make_vec_env(E2E_Env, n_envs=1, vec_env_cls=DummyVecEnv, env_kwargs=eval_env_kwargs)

        obs, _ = env.reset()
        done = False
        log_data = []
        while not done:
            action, _ = model.predict(obs, deterministic=True)
            obs, _, done, info = env.step(action)
            log_data.append(info[0])
        env.close()

        df = pd.DataFrame(log_data)
        output_file = os.path.join(save_dir, f"qualitative_eval_{mission_name}.csv")
        df.to_csv(output_file, index=False)
        print(f"Saved trajectory data to {output_file}")

        # Here you could directly call the plotting functions that use the DataFrame
        plot_trajectory_results(df=df, save_path=output_file)

def plot_trajectory_results(df: pd.DataFrame, save_path: str):
    """
    Generates and saves a comprehensive plot of a trajectory run.

    Args:
        df (pd.DataFrame): DataFrame containing the logged data from an episode.
        save_path (str): The full path (including filename) to save the plot image.
    """
    fig, axes = plt.subplots(3, 3, figsize=(20, 18), sharex=False)
    fig.suptitle(f"Trajectory Analysis: {os.path.basename(os.path.dirname(save_path))}", fontsize=16)

    time = df['sim_time']
        
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

    axes[0, 0].set_title("Reward Components & Total")

    # 2. Plot Components (Die Analyse)
    if 'reward_terms' in df.columns and not df['reward_terms'].isnull().all():
        parsed_terms = df['reward_terms'].apply(safe_parse_reward_dict).dropna()
        
        if not parsed_terms.empty:
            term_names = sorted(parsed_terms.iloc[0].keys())
            
            # Nutze eine Colormap, um Farben automatisch zuzuweisen (besser als Standard-Zyklus bei vielen Termen)
            cmap = plt.get_cmap('tab10') 
            
            for i, name in enumerate(term_names):
                # Extrahiere Zeitreihe für diesen Term
                # Wir nehmen 'r' (roh) oder 'val' (gewichtet) - hier wohl 'r' für 0..1 Analyse besser?
                # Falls du gewichtete Werte willst, nimm d.get('val', 0). 
                # Für Analyse der Multiplikatoren ist 'r' meist aufschlussreicher (da 0..1).
                values = [term_dict.get(name, {}).get('r', 0) for term_dict in parsed_terms]
                
                # Plot als Linie
                axes[0, 0].plot(time, values, label=name, color=cmap(i % 10), alpha=0.7, linewidth=1.5)

    # 1. Plot Total Reward (Die Wahrheit)
    # Wir plotten dies zuerst oder zuletzt (Z-Order), damit es gut sichtbar ist.
    if 'reward' in df.columns:
        axes[0, 0].plot(time, df['reward'], label='TOTAL REWARD', color='black', linewidth=2.0, zorder=10)

    axes[0, 0].set_ylabel("Reward Value")
    # Legende nach außen schieben oder klein machen, damit sie nicht den Plot verdeckt
    axes[0, 0].legend(loc='upper left', bbox_to_anchor=(1.0, 1.05), fontsize='small', framealpha=0.8)
    axes[0, 0].grid(True, which='both', linestyle='--', alpha=0.7)
    axes[0, 0].set_ylim(-1.0, 2.0)

    axes[0, 1].set_title("Top-Down View (XY-Plane)")

    # Helferfunktion, um die Spalte sicher in ein (N, 3) Array umzuwandeln
    def _col_to_array(series):
        # Wenn die Spalte leer ist, gib ein leeres Array mit der richtigen Form zurück
        if series.empty: return np.empty((0, 3))
        # Wenn es schon Arrays sind, staple sie einfach
        if isinstance(series.iloc[0], np.ndarray): return np.stack(series.values)
        # Ansonsten parse die Strings
        def safe_parse(s):
            try: return np.array(ast.literal_eval(s))
            except: return np.array([np.nan, np.nan, np.nan])
        return np.stack(series.fillna('[NaN,NaN,NaN]').apply(safe_parse).values)

    agent_pos = _col_to_array(df['agent_pos'])
    target_pos = _col_to_array(df['mission_goal_pos'])

    # Plot die Pfade
    axes[0, 1].plot(agent_pos[:, 0], agent_pos[:, 1], color="blue", alpha=0.8, label="Agent Path")
    axes[0, 1].plot(target_pos[:, 0], target_pos[:, 1], linestyle="--", color="darkorange", label="Target Path")
    axes[0, 1].scatter(agent_pos[0, 0], agent_pos[0, 1], color="green", s=80, label="Start", zorder=3)
    axes[0, 1].scatter(agent_pos[-1, 0], agent_pos[-1, 1], facecolors="none", edgecolors="blue", s=80, label="End", zorder=3)
    axes[0, 1].scatter(target_pos[:, 0], target_pos[:, 1], label='Waypoints', c='orange', marker='x', zorder=3)

    # --- NEU: Dynamische, quadratische Achsen-Limits ---
    # Finde die extremsten Koordinaten in allen Daten
    all_x = np.concatenate([agent_pos[:, 0], target_pos[:, 0]])
    all_y = np.concatenate([agent_pos[:, 1], target_pos[:, 1]])

    # Entferne NaNs für die Berechnung
    all_x = all_x[~np.isnan(all_x)]
    all_y = all_y[~np.isnan(all_y)]

    if all_x.size > 0 and all_y.size > 0:
        x_min, x_max = np.min(all_x), np.max(all_x)
        y_min, y_max = np.min(all_y), np.max(all_y)

        # Finde das Zentrum des benötigten Bereichs
        center_x = (x_max + x_min) / 2
        center_y = (y_max + y_min) / 2

        # Finde die größte benötigte Spanne (entweder in X oder Y Richtung)
        span = max(x_max - x_min, y_max - y_min)

        # Füge einen kleinen Puffer hinzu (z.B. 10% der Spanne)
        buffer = span * 0.1

        # Setze die quadratischen Limits um das Zentrum
        axes[0, 1].set_xlim(center_x - span/2 - buffer, center_x + span/2 + buffer)
        axes[0, 1].set_ylim(center_y - span/2 - buffer, center_y + span/2 + buffer)
    axes[0, 1].set_ylabel("Y Position [m]"); axes[0, 1].set_xlabel("X Position [m]")
    axes[0, 1].legend(loc='upper right')
    axes[0, 1].grid(True)
    axes[0, 1].set_aspect('equal', adjustable='box') # Wichtig für korrekte Darstellun

    axes[0, 2].set_title("Error Norms")
    # Wandle die Spalten zuerst in (N, 3) Arrays um
    error_pos_array = _col_to_array(df['error_pos'])
    error_vel_array = _col_to_array(df['error_vel_c'])
    # Berechne die Norm für JEDEN ZEITSCHRITT (axis=1)
    pos_error_norm = np.linalg.norm(error_pos_array, axis=1)
    vel_error_norm = np.linalg.norm(error_vel_array, axis=1)
    axes[0, 2].plot(time, pos_error_norm, label='Position Error [m]', color='blue')
    axes[0, 2].plot(time, vel_error_norm, label='Velocity Error [m/s]', color='red', alpha=0.7)
    axes[0, 2].set_ylabel("Error Magnitude")
    axes[0, 2].legend(loc='upper right')
    axes[0, 2].grid(True)

    # --- 1. Position Plot ---
    axes[1,0].set_title("Position (X, Y, Z)")
    axes[1,0].plot(time, df['agent_pos'].apply(lambda x: x[0]), label='Agent Pos X', c='blue')
    axes[1,0].plot(time, df['mission_goal_pos'].apply(lambda x: x[0]), label='Target Pos X', c='cyan', ls='--')
    axes[1,0].plot(time, df['agent_pos'].apply(lambda x: x[1]), label='Agent Pos Y', c='red')
    axes[1,0].plot(time, df['mission_goal_pos'].apply(lambda x: x[1]), label='Target Pos Y', c='magenta', ls='--')
    axes[1,0].plot(time, df['agent_pos'].apply(lambda x: x[2]), label='Agent Pos Z', c='green')
    axes[1,0].plot(time, df['mission_goal_pos'].apply(lambda x: x[2]), label='Target Pos Z', c='lime', ls='--')
    axes[1,0].set_ylabel("Position [m]")
    axes[1,0].legend(loc='upper right')
    axes[1,0].grid(True)

    # --- 3. Velocity Plot ---
    axes[1,1].set_title("Velocity in Control Frame (u, v, w)")
    
    axes[1,1].plot(time, df['max_vel'].apply(lambda x: x[0]), label='Limits Vel', c='black')
    axes[1,1].plot(time, df['max_vel'].apply(lambda x: x[1]), c='black')
    axes[1,1].plot(time, df['max_vel'].apply(lambda x: x[2]), c='black')
    axes[1,1].plot(time, df['min_vel'].apply(lambda x: x[0]), c='black')
    axes[1,1].plot(time, df['min_vel'].apply(lambda x: x[1]), c='black')
    axes[1,1].plot(time, df['min_vel'].apply(lambda x: x[2]), c='black')

    axes[1,1].plot(time, df['agent_vel_c'].apply(lambda x: x[0]), label='Agent Vel u', c='blue')
    axes[1,1].plot(time, df['mission_goal_vel'].apply(lambda x: x[0]), label='Target Vel u', c='cyan', ls='--')
    axes[1,1].plot(time, df['agent_vel_c'].apply(lambda x: x[1]), label='Agent Vel v', c='red')
    axes[1,1].plot(time, df['mission_goal_vel'].apply(lambda x: x[1]), label='Target Vel v', c='magenta', ls='--')
    axes[1,1].plot(time, df['agent_vel_c'].apply(lambda x: x[2]), label='Agent Vel w', c='green')
    axes[1,1].plot(time, df['mission_goal_vel'].apply(lambda x: x[2]), label='Target Vel w', c='lime', ls='--')

    axes[1,1].set_ylabel("Velocity [m/s]")
    axes[1,1].legend(loc='upper right')
    axes[1,1].grid(True)

    # --- 2. Attitude Plot ---
    axes[2,0].set_title("Attitude (Roll, Pitch, Yaw)")
    axes[2,0].plot(time, df['agent_rpy_deg'].apply(lambda x: x[0]), label='Roll', c='blue')
    axes[2,0].plot(time, df['agent_rpy_deg'].apply(lambda x: x[1]), label='Pitch', c='red')
    axes[2,0].plot(time, df['agent_rpy_deg'].apply(lambda x: x[2]), label='Yaw', c='green')
    axes[2,0].set_ylabel("Angle [deg]")
    axes[2,0].legend(loc='upper right')
    axes[2,0].grid(True)

    # --- 4. Motor Commands Plot ---
    axes[2,2].set_title("Motor Commands (Setpoint)")
    motor_cmds = np.stack(df['motor_signal_measured_rps'].values)
    #for i in range(8):
    #    axes[2,2].plot(time, motor_cmds[:, i], label=f'Motor {i+1}', alpha=0.8)
    mean_cmds = np.mean(motor_cmds, axis=1)
    std_cmds = np.std(motor_cmds, axis=1)
    axes[2,2].plot(time, mean_cmds, label='Mean Command', color='blue')
    axes[2,2].fill_between(time, mean_cmds - std_cmds, mean_cmds + std_cmds, color='orange', alpha=0.2, label='Std Dev')
    axes[2,2].set_ylabel("Rotor Speed [rad/s]")
    axes[2,2].set_xlabel("Time [s]")
    axes[2,2].legend(loc='upper right', ncol=4)
    axes[2,2].grid(True)

    # --- 5. acc Plot ---
    axes[1,2].set_title("Acceleration in Control Frame (u, v, w)")
    axes[1,2].plot(time, df['agent_accel'].apply(lambda x: x[0]), label='Agent Dot x', c='blue')
    axes[1,2].plot(time, df['agent_accel'].apply(lambda x: x[1]), label='Agent Dot y', c='red')
    axes[1,2].plot(time, df['agent_accel'].apply(lambda x: x[2]), label='Agent Dot z', c='green')
    axes[1,2].plot(time, df['agent_imu_accel'].apply(lambda x: x[0]), label='IMU x', c='cyan', ls ='--')
    axes[1,2].plot(time, df['agent_imu_accel'].apply(lambda x: x[1]), label='IMU y', c='magenta', ls ='--')
    axes[1,2].plot(time, df['agent_imu_accel'].apply(lambda x: x[2]), label='IMU z', c='lime', ls ='--')
    axes[1,2].set_ylabel("Acceleration [m/s^2]")
    axes[1,2].legend(loc='upper right')
    axes[1,2].grid(True)

    # --- 5. Omega Plot ---
    axes[2,1].set_title("Omegas in Control Frame (u, v, w)")
    axes[2,1].plot(time, df['agent_omega'].apply(lambda x: x[0]), label='Agent wx', c='blue')
    axes[2,1].plot(time, df['agent_imu_omega'].apply(lambda x: x[0]), label='IMU vx', c='cyan', ls='--')
    axes[2,1].plot(time, df['agent_omega'].apply(lambda x: x[1]), label='Agent wy', c='red')
    axes[2,1].plot(time, df['agent_imu_omega'].apply(lambda x: x[1]), label='IMU wy', c='magenta', ls='--')
    axes[2,1].plot(time, df['agent_omega'].apply(lambda x: x[2]), label='Agent wz', c='green')
    axes[2,1].plot(time, df['agent_imu_omega'].apply(lambda x: x[2]), label='IMU wz', c='lime', ls='--')
    axes[2,1].set_ylabel("Omegas [rad/s]")
    axes[2,1].legend(loc='upper right')
    axes[2,1].grid(True)

    # =============================================================================
    # --- Selektives Achsen-Sharing ---
    # =============================================================================
    master_ax = axes[0, 0]
    for row in range(3):
        for col in range(3):
            ax = axes[row, col]
            if ax is axes[0, 1]:
                continue
            if ax is not master_ax:
                ax.sharex(master_ax)
            if row < 2:
                plt.setp(ax.get_xticklabels(), visible=False)

    # Setze X-Achsen-Label nur für die untere Reihe der Zeit-Plots
    axes[2, 0].set_xlabel("Time [s]")
    axes[2, 1].set_xlabel("Time [s]")

    plt.tight_layout(rect=[0, 0.03, 1, 0.96])
    plt.savefig(save_path)
    plt.close(fig)
    #print(f"  > Plot saved to {save_path}")