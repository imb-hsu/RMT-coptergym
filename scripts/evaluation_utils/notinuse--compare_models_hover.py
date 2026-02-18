import os
import pandas as pd
import numpy as np
import platform
import ast
import gymnasium as gym
from stable_baselines3 import PPO
from stable_baselines3.common.vec_env import DummyVecEnv
import matplotlib.pyplot as plt
import seaborn as sns

# Import Environment - Adjust if you use a different variant
from rmt_coptergym.application_envs.RL_VEL_I_Env_relative import VEL_Env as VEL_Env_Integral
from rmt_coptergym.application_envs.RL_VEL_Env_relative import VEL_Env as VEL_Env_NoIntegral


# ==============================================================================
# CONFIGURATION
# ==============================================================================
# TODO: Bitte Pfade zu den beiden Modellen hier anpassen!
MODEL_1_PATH = "PPO_rel_I_additive.zip" 
MODEL_2_PATH = "PPO_rel_noI_additive.zip"

CTRL_FREQ = 125
MAX_DURATION = 10.0

# ==============================================================================
# HELPER FUNCTIONS (Replicated from evaluation.py for standalone usage)
# ==============================================================================
def parse_vector_col(series):
    """Wandelt Strings in Numpy Arrays um."""
    parsed_list = []
    detected_len = None
    for x in series:
        val = None
        if isinstance(x, (list, np.ndarray)): val = list(x)
        elif isinstance(x, str):
            x = x.strip()
            try: val = ast.literal_eval(x)
            except:
                try:
                    clean = x.replace('[','').replace(']','').replace('\n',' ')
                    parts = clean.split()
                    if parts: val = [float(v) for v in parts]
                except: val = None
        if val and detected_len is None: detected_len = len(val)
        parsed_list.append(val)
    
    if detected_len is None: detected_len = 3
    final = []
    zeros = [0.0]*detected_len
    for item in parsed_list:
        if item is None or len(item) != detected_len: final.append(zeros)
        else: final.append(item)
    return np.array(final)

def calculate_metrics_physics(df, motor_min, motor_range, ctrl_freq=125.0, filename="Unknown", max_duration=10.0, total_waypoints=None):
    metrics = {
        'rmse_xyz': 999.0, 'rmse_te_xyz': 999.0,
        'rmse_rpy': 999.0, 'rmse_te_rpy': 999.0,
        'rmse_vel': 999.0, 'rmse_te_vel': 999.0,
        'energy': 0.0, 'jitter': 0.0, 
        'flight_time': 0.0, 'stability': 0.0, 'success': 0.0, 'wcr': 0.0
    }
    if df.empty: return metrics

    # Flight Time & Stability
    if 'sim_time' in df.columns: metrics['flight_time'] = df['sim_time'].max()
    else: metrics['flight_time'] = len(df) / ctrl_freq
    metrics['stability'] = min(metrics['flight_time'] / max_duration, 1.0)

    # Success
    if 'eval_metrics' in df.columns:
        valid = df['eval_metrics'].dropna()
        if not valid.empty:
            try:
                last = valid.iloc[-1]
                parsed = ast.literal_eval(last) if isinstance(last, str) else last
                metrics['success'] = float(parsed.get('success', 0.0))
            except: pass
    if metrics['success'] < 0.5 and 'status' in df.columns:
        if df['status'].eq('final target reached').any(): metrics['success'] = 1.0

    # RMSE Helper
    def calc_rmse(diff_vec):
        mse = np.mean(np.sum(diff_vec**2, axis=1))
        rmse = np.sqrt(mse)
        # Time Extended
        rmse_te = rmse
        if metrics['success'] < 0.5 and metrics['flight_time'] < (max_duration - 0.1):
            missing = int((max_duration - metrics['flight_time']) * ctrl_freq)
            if missing > 0:
                last_sq = np.sum(diff_vec[-1]**2)
                total_sse = np.sum(np.sum(diff_vec**2, axis=1)) + (missing * last_sq)
                rmse_te = np.sqrt(total_sse / (len(diff_vec) + missing))
        return rmse, rmse_te

    # XYZ
    diff_xyz = None
    if 'agent_pos' in df.columns and 'mission_goal_pos' in df.columns:
        diff_xyz = parse_vector_col(df['agent_pos']) - parse_vector_col(df['mission_goal_pos'])
    elif 'error_pos' in df.columns:
        diff_xyz = parse_vector_col(df['error_pos'])
    
    if diff_xyz is not None:
        metrics['rmse_xyz'], metrics['rmse_te_xyz'] = calc_rmse(diff_xyz)

    # VEL
    diff_vel = None
    if 'agent_vel_c' in df.columns and 'mission_goal_vel' in df.columns:
        diff_vel = parse_vector_col(df['agent_vel_c']) - parse_vector_col(df['mission_goal_vel'])
    elif 'error_vel_c' in df.columns:
        diff_vel = parse_vector_col(df['error_vel_c'])
    
    if diff_vel is not None:
        metrics['rmse_vel'], metrics['rmse_te_vel'] = calc_rmse(diff_vel)

    # RPY
    if 'error_rpy_deg' in df.columns:
        diff_rpy = parse_vector_col(df['error_rpy_deg'])
        metrics['rmse_rpy'], metrics['rmse_te_rpy'] = calc_rmse(diff_rpy)

    # Energy/Jitter
    motors_norm = None
    if 'motor_signal_measured_rps' in df.columns:
        motors = parse_vector_col(df['motor_signal_measured_rps'])
        motors_norm = (motors - motor_min) / motor_range
    elif 'action_cmd' in df.columns:
        motors = parse_vector_col(df['action_cmd'])
        motors_norm = (motors - motor_min) / motor_range
    
    if motors_norm is not None and len(motors_norm) > 0:
        metrics['energy'] = np.mean(np.square(motors_norm))
        if len(motors_norm) > 1:
            metrics['jitter'] = np.mean(np.square(np.diff(motors_norm, axis=0)))

    return metrics

def calculate_composite_score(df):
    if df.empty: return df
    df = df.copy()
    # Simple normalization for score (min-max per column in this set)
    for col in ['rmse_te_xyz', 'rmse_te_rpy', 'rmse_te_vel']:
        if col in df.columns:
            min_v, max_v = df[col].min(), df[col].max()
            norm_col = f"norm_{col}"
            if max_v > min_v: df[norm_col] = (df[col] - min_v) / (max_v - min_v)
            else: df[norm_col] = 0.0
    
    # Score Formula
    df['Score'] = 2*df['stability'] + df.get('wcr', 0) - df.get('norm_rmse_te_vel', 0) - df.get('norm_rmse_te_xyz', 0) - df.get('norm_rmse_te_rpy', 0)
    return df

class PaperMetricsWrapper(gym.Wrapper):
    def __init__(self, env):
        super().__init__(env)
    def step(self, action):
        obs, reward, done, truncated, info = self.env.step(action)
        if done or truncated:
            is_success = False
            if info.get('status') == 'final target reached': is_success = True
            info['eval_metrics'] = {'success': 1.0 if is_success else 0.0}
        return obs, reward, done, truncated, info

# ==============================================================================
# MAIN
# ==============================================================================
if __name__ == "__main__":
    try:
        project_root = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
    except NameError:
        project_root = "."


    out_dir = os.path.join(project_root, "data", "I_Comparison")
    os.makedirs(out_dir, exist_ok=True)

    # 1. Create Hover Mission (Start 0,0,-10 -> Stay 0,0,-10)
    mission_data = {
        'time': [0.0, 0.0, 3.0],
        'pos_x': [0.0, np.nan, np.nan], 'pos_y': [0.0, np.nan, np.nan], 'pos_z': [-10.0, np.nan, np.nan],
        'vel_x': [0.0, 0.0,  1.0], 'vel_y': [1.0, 0.0,  -1.0], 'vel_z': [0.0, 0.0,  0.0],
        'vel_limit_x': [2.0, 2.0, 2.0], 'vel_limit_y': [2.0, 2.0, 2.0], 'vel_limit_z': [2.0, 2.0, 2.0],
        'rpy_x': [0.0, 0.0, 0.0], 'rpy_y': [0.0, 0.0, 0.0], 'rpy_z': [0.0, 0.0, 0.0],
        'thrust': [930.0, np.nan, np.nan]
    }
    mission_df = pd.DataFrame(mission_data)
    mission_df['mission_name'] = "Simple_Hover"

    # 2. Get Env Constants
    #env_kwargs = {'reward_function': 'exponential', 'reward_type': 'additive', 'anomaly_knowledge': False, 'ctrl_freq': CTRL_FREQ, 'use_unix': platform.system() != "Windows"}
        
    config = {
            "env_kwargs": {
            "reward_function": "exponential",
            'reward_type': 'additive',
            'anomaly_knowledge': False,
            "action_space_type": "Box",
            "ctrl_freq": 125,
            "use_unix": platform.system() != "Windows",
            "reward_weights": {
                "vel": 4.0,
                "rollpitch": 0.25,
                "yaw": 1.0,
                "accel": 0.25,
                "omega": 0.25,
                "comfort_zone": 1.0,
                "paired_efficiency": 1.0,
                "balance": 0.5,
                "smoothness": 0.5
            }
        },
        "model_kwargs": {
            "policy": "MultiInputPolicy",
            "policy_kwargs": {
                "net_arch": {
                    "pi": [
                        256,
                        256
                    ],
                    "vf": [
                        256,
                        256
                    ]
                },
                "activation_fn": "<not serializable>"
            },
            "n_steps": 2048,
            "batch_size": 64,
            "gamma": 0.99,
            "learning_rate": 0.0001,
            "ent_coef": 0.001,
            "clip_range": 0.2,
            "n_epochs": 7,
            "verbose": 0
        }
    }
    
    env_kwargs=config['env_kwargs']
    
    temp_env = VEL_Env_Integral(**env_kwargs)
    MOTOR_MIN, MOTOR_RANGE = temp_env.limits.motor.min, temp_env.limits.motor.range
    temp_env.close()

    # 3. Run Models
    # Define configuration for each model including its specific environment
    models_config = [
        {
            "name": "Design with Error-Integral",
            "path": os.path.join(project_root, "saves", "Comparison_integral_part", MODEL_1_PATH),
            "env_class": VEL_Env_Integral
        },
        {
            "name": "Standard Design",
            "path": os.path.join(project_root, "saves", "Comparison_integral_part", MODEL_2_PATH),
            "env_class": VEL_Env_NoIntegral
        }
    ]
    
    results = []
    all_data = {}

    for config in models_config:
        name = config["name"]
        path = config["path"]
        EnvClass = config["env_class"]

        if not os.path.exists(path):
            print(f"[WARN] Pfad nicht gefunden: {path}. Überspringe.")
            continue
        print(f"--- Running {name} ---")
        try:
            model = PPO.load(path, device='cpu')
            run_kwargs = env_kwargs.copy()
            run_kwargs.update({'mission_pool': [mission_df], 'anomaly_pool': [], 'is_eval': True})
            
            # Instantiate the specific environment for this model
            env = PaperMetricsWrapper(EnvClass(**run_kwargs))
            
            obs, _ = env.reset(seed=42); done = False; truncated = False; log_data = []
            while not (done or truncated):
                action, _ = model.predict(obs, deterministic=True)
                obs, _, done, truncated, info = env.step(action)
                log_data.append(info)
            env.close()
            
            df_log = pd.DataFrame(log_data)
            all_data[name] = df_log
            df_log.to_csv(os.path.join(out_dir, f"{name}_log.csv"), index=False)
            mets = calculate_metrics_physics(df_log, MOTOR_MIN, MOTOR_RANGE, CTRL_FREQ, name, MAX_DURATION, total_waypoints=2)
            mets['Agent'] = name
            results.append(mets)
        except Exception as e: print(f"[ERROR] Fehler bei {name}: {e}")

    # 4. Summary
    if results:
        df_res = pd.DataFrame(results)
        df_res = calculate_composite_score(df_res)
        print("\n=== COMPARISON RESULTS ===")
        print(df_res[["Agent", "stability", "rmse_te_xyz", "rmse_te_vel", "energy", "Score"]])
        df_res.to_csv(os.path.join(out_dir, "comparison_summary.csv"), index=False)

        # 5. Plotting
        print("\n=== GENERATING PLOTS ===")
        
        # Velocity Plot
        fig, axes = plt.subplots(3, 1, figsize=(7, 5), sharex=True)
        fig.suptitle(f"Steady State Error Behaviour", fontsize=16)
        
        for name, df in all_data.items():
            t = df['sim_time']
            vel = parse_vector_col(df['error_vel_c'])
            #vel = parse_vector_col(df['agent_vel_c'])
            
            axes[0].plot(t, vel[:, 0], label=name)
            axes[1].plot(t, vel[:, 1], label=name)
            axes[2].plot(t, vel[:, 2], label=name)
            
        axes[0].set_ylabel("$e_{Vx}$ [m/s]", fontsize=15)
        axes[0].legend()
        sns.move_legend(axes[0], "lower center", bbox_to_anchor=(0.5, 0.95), ncol=3, title=None, frameon=False, fontsize=12)
        
        axes[1].set_ylabel("$e_{Vy}$ [m/s]", fontsize=15)
        axes[2].set_ylabel("$e_{Vz}$ [m/s]", fontsize=15)
        axes[2].tick_params(axis='y', labelsize=12) 
        axes[2].tick_params(axis='x', labelsize=12)
        axes[2].set_xlabel("Time [s]", fontsize=15)
        axes[0].set_ylim(-1.1, 1.1)
        axes[1].set_ylim(-1.1, 1.1)
        axes[2].set_ylim(-0.6, 0.6)
        #axes[2].set_ylim(-0.18, 0.6)
        for ax in axes: ax.grid(True); ax.tick_params(axis='y', labelsize=12); ax.tick_params(axis='x', labelsize=12) ;#ax.legend(); 
    
        fig.align_ylabels(axes)
        plt.tight_layout()
        plt.savefig(os.path.join(out_dir, "comparison_velocity.png"))
        print(f"Saved velocity plot to {os.path.join(out_dir, 'comparison_velocity.png')}")

        # Close figure to free memory
        plt.close(fig)

    else: print("Keine Ergebnisse generiert.")