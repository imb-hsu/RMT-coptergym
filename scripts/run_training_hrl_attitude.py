import os
import torch

# In theory setting the threads might be useful - in practice it doesn't produce noticeable impact
#num_threads = 50
#os.environ['OMP_NUM_THREADS'] = str(num_threads)
#os.environ['MKL_NUM_THREADS'] = str(num_threads)
#os.environ['OPENBLAS_NUM_THREADS'] = str(num_threads)
# Set Threads for each 'core'
#torch.set_num_threads(num_threads)

import matplotlib
matplotlib.use('Agg')

import numpy as np
import platform
import time
import json
from stable_baselines3 import PPO
from stable_baselines3.common.env_util import make_vec_env
from stable_baselines3.common.vec_env import SubprocVecEnv, DummyVecEnv
from stable_baselines3.common.callbacks import EvalCallback, CheckpointCallback
from stable_baselines3.common.monitor import Monitor
import pandas as pd

import matplotlib.pyplot as plt
import copy

# Import Help function to assign the correct HRL Att Env
from rmt_coptergym.application_envs.HRL_Att_Env import HRL_Att_Env
env_string = "HRL_Att_Env"

from rmt_coptergym.utils.plots import EvaluationPlots
from rmt_coptergym.utils.trajectory_dataloader import TrajectoryDataLoader
from rmt_coptergym.utils.utils import plot_trajectory_results

# --- Custom Callback for Checkpoint Evaluation and Plotting ---
def run_checkpoint_overview(model_path: str, eval_pool: list[pd.DataFrame], env_kwargs: dict):
    """
    A short evaluation function which will be called on each checkpoint, to track and plot progress.
    """
    print(f"  > Creating overview plots for checkpoint: {os.path.basename(model_path)}")
    model = PPO.load(model_path, device='cpu') # Load on CPU to save GPU memory
    
    # Create a subfolder for the plots of this checkpoint
    plot_save_dir = os.path.join(os.path.dirname(model_path), f"{os.path.basename(model_path).replace('.zip', '')}_plots")
    os.makedirs(plot_save_dir, exist_ok=True)

    for mission_df in eval_pool:
        # Create Temp Env for training-progress tracking
        single_mission_pool = [mission_df]
        eval_env_kwargs = {**env_kwargs, 'mission_pool': single_mission_pool, 'is_eval': True}
        env = DummyVecEnv([lambda: HRL_Att_Env(**eval_env_kwargs)])

        obs = env.reset()
        done = False
        log_data = []
        while not done:
            action, _ = model.predict(obs, deterministic=True)
            obs, _, dones, info = env.step(action)
            log_data.append(info[0])
            done = dones[0]
        env.close()
        
        if not log_data:
            continue

        df = pd.DataFrame(log_data)
        mission_name = df['mission_name'].iloc[0]
        
        plot_path = os.path.join(plot_save_dir, f"overview_{mission_name}.png")
        plot_trajectory_results(df, plot_path) 

    print(f"  > All Summary-Plots saved in: {plot_save_dir}")


class CheckpointWithPlotsCallback(CheckpointCallback):
    """
    Callback function for handling the checkpoint evaluation for each checkpoint.
    """
    def __init__(self, eval_pool: list, env_kwargs: dict, **kwargs):
        super().__init__(**kwargs)
        self.eval_pool = eval_pool
        self.env_kwargs = env_kwargs

    def _on_step(self) -> bool:
        # save model, if save_freq reached.
        continue_training = super()._on_step()
        # `self.last_saved_checkpoint_path` contains the path to the last saved model
        # just make sure we have a model saved to load here.
        if self.n_calls % self.save_freq == 0 and self.save_path is not None:
            # get saved model path and load checkpoint for evaluation
            model_path = os.path.join(self.save_path, f"{self.name_prefix}_{self.num_timesteps}_steps.zip")
            if os.path.exists(model_path):
                 run_checkpoint_overview(model_path, self.eval_pool, self.env_kwargs)

        return continue_training

def run_rl_evaluation(model_path: str, eval_pool: list[pd.DataFrame], anomaly_pool: list[pd.DataFrame], env_kwargs: dict, save_dir: str):
    """
    Runs the trained RL model on each trajectory of the evaluation dataset.
    Creates a hierarchy for comparable benchmarks:
      1. Baseline (No Anomaly)
      2. Exactly ONE representative disturbance per anomaly type (Index 0 from the group)
    """
    print(f"\n=== Starting deterministic evaluation: {model_path} ===")
    os.makedirs(save_dir, exist_ok=True)
    
    # Load model (only needed once)
    try:
        model = PPO.load(model_path)
    except Exception as e:
        print(f"[ERROR] Could not load model: {e}")
        return

    # ---------------------------------------------------------
    # 1. Group anomalies & select representatives
    # ---------------------------------------------------------
    # We don't want 200 folders for 200 files, but only 1 folder per failure type.
    # We assume the loader sorted files such that the 'eval_sequence' 
    # (your hard test case) always comes first.
    
    representative_anomalies = {}
    
    for df in anomaly_pool:
        # Get name (was set in loader via 'anomaly_name')
        # Fallback to 'mission_name' or 'anomaly_name' if keys vary
        if 'anomaly_name' in df.columns:
            name = df.iloc[0]['anomaly_name']
        elif 'anomaly_name' in df.columns:
            name = df.iloc[0]['anomaly_name']
        else:
            name = "Unknown_Anomaly"
        
        # If we don't have this type yet -> save it (this is the first/representative)
        if name not in representative_anomalies:
            representative_anomalies[name] = df

    print(f"Anomaly scenarios found: {list(representative_anomalies.keys())}")

    # ---------------------------------------------------------
    # 2. Create scenario list
    # ---------------------------------------------------------
    scenarios = []

    # A) Baseline: No Anomaly (Reference)
    scenarios.append({
        "folder_name": "00_Baseline_No_Anomaly",
        "anom_pool": [],     # Empty pool
        "active": False      # 0.0 chance
    })

    # B) Anomaly Scenarios (Deterministic)
    # We sort by name so '01', '02' etc. are always assigned the same way
    for idx, (anom_name, anom_df) in enumerate(sorted(representative_anomalies.items())):
        
        # Clean folder name (e.g., "01_dropout_failure_single")
        safe_name = "".join([c for c in anom_name if c.isalnum() or c in (' ', '_', '-')]).strip()
        folder_name = f"{idx+1:02d}_{safe_name}"
        
        scenarios.append({
            "folder_name": folder_name,
            "anom_pool": [anom_df], # List length 1 -> Forces Env to always use this DF
            "active": True          # 1.0 chance
        })

    # ---------------------------------------------------------
    # 3. Execution Loop (Scenarios -> Missions)
    # ---------------------------------------------------------
    for scenario in scenarios:
        print(f"\n--- Starting scenario: {scenario['folder_name']} ---")
        
        # Create base folder for this scenario
        scenario_dir = os.path.join(save_dir, scenario["folder_name"])
        os.makedirs(scenario_dir, exist_ok=True)

        # Loop over all evaluation missions (trajectories)
        for i, mission_df in enumerate(eval_pool):
            
            # --- Environment Setup for this run ---
            current_kwargs = env_kwargs.copy()
            current_kwargs.update({
                'mission_pool': [mission_df], # Exactly this mission (Index 0 in Env)
                'is_eval': True,
                'seed': 42, # Fixed seed for absolute reproducibility
                
                # Anomaly logic:
                # Since anom_pool has only 1 entry (our representative),
                # the Env will always pick index 0 on reset().
                'anomaly_pool': scenario["anom_pool"], 
                'anomaly_chance': 1.0 if scenario["active"] else 0.0
            })

            # Create Env (DummyVecEnv wraps it for SB3)
            env = DummyVecEnv([lambda: HRL_Att_Env(**current_kwargs)])
            
            # --- Simulation ---
            obs = env.reset()
            log_data = []
            done = False
            
            while not done:
                # Deterministic action for clean comparison
                action, _ = model.predict(obs, deterministic=True)
                obs, _, dones, info_list = env.step(action)
                
                # Collect Info (VecEnv returns a list)
                log_data.append(info_list[0])
                done = dones[0]
            
            env.close()

            # --- Process results ---
            if not log_data:
                print(f"  [WARN] No data for mission {i}. Skipping.")
                continue

            # Safely determine mission name
            mission_name = log_data[0].get('mission_name', f"Mission_{i}")
            
            # Create subfolder per mission: .../eval/01_Anomaly/Figure_8/
            mission_save_dir = os.path.join(scenario_dir, mission_name)
            os.makedirs(mission_save_dir, exist_ok=True)
            
            # 1. Save CSV
            df_res = pd.DataFrame(log_data)
            csv_path = os.path.join(mission_save_dir, "rl_results.csv")
            df_res.to_csv(csv_path, index=False)
            
            # 2. Create plots (Using your class)
            try:
                plotter = EvaluationPlots(save_dir=mission_save_dir)
                plotter.create_all_plots(df_res)
            except Exception as e:
                print(f"  [ERROR] Plotting failed for {mission_name}: {e}")

    print(f"\n=== Evaluation finished. All results in: {save_dir} ===")

def old_run_rl_evaluation(model_path: str, eval_pool: list[pd.DataFrame], anomaly_pool: list[pd.DataFrame], env_kwargs: dict, save_dir: str):
    """
    Runs the trained RL model on each trajectory of the evaluation dataset
    and saves individual results and plots.
    """
    print(f"\n--- Evaluating RL Model: {model_path} ---")
    # Ensure parent directory for plots exists
    os.makedirs(save_dir, exist_ok=True)
    
    model = PPO.load(model_path)

    # Iterate through each trajectory in the evaluation set
    num_eval_episodes = len(eval_pool)
    for i in range(num_eval_episodes):
        # Select trajectory for this episode manually.
        # To ensure every mission is evaluated deterministically, we create
        # a new environment for each individual mission.
        single_mission_df = eval_pool[i]
        single_mission_pool = [single_mission_df]
        eval_env_kwargs = {
            **env_kwargs, 
            'mission_pool': single_mission_pool, 
            'is_eval': True,
            'seed': 1,
            'anomaly_pool': anomaly_pool,
            'anomaly_chance': 1.0 # Anomaly always active during eval
        }
        env = DummyVecEnv([lambda: HRL_Att_Env(**eval_env_kwargs)])

        obs = env.reset()

        log_data = []
        done = False
        while not done:
            action, _ = model.predict(obs, deterministic=True)
            obs, _, dones, info = env.step(action)
            log_data.append(info[0])
            done = dones[0]

        # Save and plot results for this specific trajectory
        # Ensure log_data is not empty
        if not log_data:
            print(f"  > Warning: No log data recorded for mission at pool index {i}. Skipping.")
            env.close()
            continue

        mission_name = log_data[0]['mission_name']
        print(f"  > Evaluation completed for mission: {mission_name}")
        df = pd.DataFrame(log_data)
        
        mission_save_dir = os.path.join(save_dir, mission_name)
        os.makedirs(mission_save_dir, exist_ok=True)
        
        csv_path = os.path.join(mission_save_dir, "rl_results.csv")
        df.to_csv(csv_path, index=False)
        
        # Create detailed plots with the new class
        plotter = EvaluationPlots(save_dir=mission_save_dir)
        plotter.create_all_plots(df)
        env.close()

def compare_with_benchmark(rl_eval_dir: str, indi_benchmark_dir: str, eval_mission_names: list):
    """
    Loads RL and INDI results and creates comparison plots.
    """
    print("\n" + "="*80 + "\n--- Creating comparison plots vs. INDI Benchmark ---\n" + "="*80)
    for mission_name in eval_mission_names:
        rl_csv_path = os.path.join(rl_eval_dir, mission_name, "rl_results.csv")
        indi_csv_path = os.path.join(indi_benchmark_dir, mission_name, "benchmark_results.csv")

        if not os.path.exists(rl_csv_path) or not os.path.exists(indi_csv_path):
            print(f"  > Skipping comparison for '{mission_name}': Result files missing.")
            continue

        df_rl = pd.read_csv(rl_csv_path)
        df_indi = pd.read_csv(indi_csv_path)

        def parse_vec(s):
            try:
                # Safer parsing of string representations of arrays
                return np.array(json.loads(s.replace(" ", ", ").replace("[,", "[").replace("],", "]")))
            except:
                return np.array([np.nan, np.nan, np.nan])

        fig, axes = plt.subplots(2, 1, figsize=(15, 12), sharex=True)
        fig.suptitle(f"RL vs. INDI Benchmark: {mission_name}", fontsize=16)

        axes[0].set_title("Position Error Norm")
        axes[0].plot(df_rl['sim_time'], df_rl['distance_current'], label='RL Agent', color='blue')
        axes[0].plot(df_indi['sim_time'], df_indi['distance_current'], label='INDI Controller', color='red', linestyle='--')
        axes[0].set_ylabel("Position Error [m]")
        axes[0].grid(True); axes[0].legend()

        axes[1].set_title("Velocity Error Norm")
        axes[1].plot(df_rl['sim_time'], df_rl['error_vel_c'].apply(parse_vec).apply(np.linalg.norm), label='RL Agent', color='blue')
        axes[1].plot(df_indi['sim_time'], df_indi['error_vel_c'].apply(parse_vec).apply(np.linalg.norm), label='INDI Controller', color='red', linestyle='--')
        axes[1].set_ylabel("Velocity Error [m/s]"); axes[1].set_xlabel("Time [s]")
        axes[1].grid(True); axes[1].legend()

        plt.tight_layout(rect=[0, 0.03, 1, 0.96])
        comparison_plot_path = os.path.join(rl_eval_dir, mission_name, "comparison_plot.png")
        plt.savefig(comparison_plot_path)
        plt.close(fig)
        print(f"  > Comparison plot for '{mission_name}' saved.")

def main():
    start_time_total = time.perf_counter()

    # =================================================================================
    # --- 1. CENTRAL CONFIGURATION ---
    # =================================================================================
    training_steps = 1# 4_000_000 #1_000_000

    # 82 min for 1mil 24 cores, 
    # 150 min for 2mil 36 cores
    # 288 min for 4mil 36 cores, 
    # 203 min for 1mil 8 cores

    CONFIG = {
        "save_name": "",
        "run_info": "test_hrl_angular",
        "num_cpu": 8,

        # --- Curriculum Learning Stages for Angular/Attitude Control ---
        "curriculum_stages": [
            
            # --- STAGE 1: Broad Foundation & Initial Robustness ---
            # Focus: Broad coverage of ~60% of mission scope. 
            # The agent learns basic stability and response to simple failures (40%).
            {
                "name": "Angular_Broad_Foundation",
                "missions": {
                    'Angular_Origin': 1.0,               # Main focus: Stabilization
                    'Angular_ConstantThrustChange': 1.0, # Main focus: Vertical load handling
                    'Angular_TempStep': 0.8,             # Main focus: Step responses
                    'Angular_StepSequence': 0.6,         # Intermediate: Sequential angles
                    'Angular_Dynamic_Steady': 0.2,       # Low frequency dynamic preview
                    'Angular_Dynamic_StopGo': 0.1,       # Rehearsal/Anchor
                    'Angular_Dynamic_Chatter': 0.1,      # Rehearsal/Anchor
                },
                "anomaly_chance": 0.4, 
                "anomaly_config": {
                    'static_failure': 1.0,               # Permanent motor loss
                    'dropout_failure_single': 0.3,       # Intermittent signal loss
                    'sudden_failure_single': 0.2         # Mid-flight failure
                },
                "timesteps": training_steps,
                "env_kwargs": {
                    "reward_weights": { 
                    } 
                }
            },
            
            # --- STAGE 2: Dynamic Agility & Performance ---
            # Focus: Continuous dynamics become the primary task. 
            # Simple missions remain as anchors (0.1-0.2) to prevent forgetting.
            {
                "name": "Angular_Dynamic_Robustness",
                "missions": {
                    'Angular_Origin': 0.1,               # Anchor
                    'Angular_ConstantThrustChange': 0.2, # Anchor
                    'Angular_TempStep': 0.4,             # Transitioning
                    'Angular_StepSequence': 0.6,         # Rhythmic response
                    'Angular_Dynamic_Steady': 1.0,       # MAIN FOCUS: Continuous tracking
                    'Angular_Dynamic_StopGo': 0.8,       # MAIN FOCUS: Agility/Start-Stop
                    'Angular_Dynamic_Chatter': 0.2,      # High-frequency preview
                },
                "anomaly_chance": 0.6, 
                "anomaly_config": {
                    'static_failure': 0.8,
                    'sudden_failure_single': 1.0, 
                    'degradation_failure': 0.6,          # Gradual power loss
                    'dropout_failure_single': 0.8
                },
                "timesteps": training_steps,
                "env_kwargs": {
                    "reward_weights":{
                        "rollpitch": 2.0,
                        "y_rate": 2.0,
                        "integral": 2.0,                  # Focus on zero steady-state error
                        "safety_zone": 0.8,

                    }
                }
            },

            # --- STAGE 3: Mastery & Extreme Resiliency ---
            # Focus: Maximum complexity (Chatter/StopGo) under extreme failure stress (80%).
            # All previous missions are kept as 0.1 anchors for long-term stability.
            {
                "name": "Angular_Mastery_Extreme",
                "missions": {
                    'Angular_Origin': 0.1,               # Anchor
                    'Angular_ConstantThrustChange': 0.1, # Anchor
                    'Angular_TempStep': 0.1,             # Anchor
                    'Angular_StepSequence': 0.2,         # Anchor
                    'Angular_Dynamic_Steady': 0.6,       # Sustained dynamic stability
                    'Angular_Dynamic_StopGo': 1.0,       # MAIN FOCUS: High-agility recovery
                    'Angular_Dynamic_Chatter': 1.0,      # MAIN FOCUS: Extreme noise rejection
                },
                "anomaly_chance": 0.8, 
                "anomaly_config": {
                    'static_failure': 0.5,
                    'sudden_failure_single': 0.8,
                    'sudden_failure_multi': 0.6,        # Hardest case: Multiple motor failures
                    'dropout_failure_multi': 0.6,       # Multiple signal drops
                    'degradation_failure': 1.0          # Total performance loss tracking
                },
                "timesteps": int(training_steps * 2.0), # Extended fine-tuning for edge cases
                "env_kwargs": {
                    "reward_weights": {
                        "rollpitch": 2.0,
                        "y_rate": 2.0,
                        "integral": 3.0,                  # Focus on zero steady-state error
                        "safety_zone": 0.5,

                    },
                }
            }
        ],
        
        # --- Evaluation and benchmark settings ---
        "eval_mission_names": [
            'Angular_Origin', 
            'Angular_StepSequence', 
            'Angular_Dynamic_Steady', 
            'Angular_Dynamic_Chatter'
        ],
        
        "env_kwargs": {
            'reward_function': 'exponential',
            'reward_type': 'additive',
            'anomaly_knowledge': True,
            'action_space_type': 'Box',
            'ctrl_freq': 125,
            'use_unix': platform.system() != "Windows",
            "reward_weights": {
                # Performance Goals:
                # Main Error Tracking, Integral Important to avoid drifts and static offsets
                "rollpitch": 1.0,
                "y_rate": 1.0,
                'thrust':1.0,
                'integral':1.0,
                # Physics
                # important during hovering - but for flying contra productive, still kept as small correction
                "rp_rate": 1.0,
                # Efficiency and Smoothness
                # efficiancy combines paired motor commands and overal motor usage - smoothness conflicts with dynamic control but keeps delta actions rather small
                "efficiency": 1.0,
                "smoothness": 0.1,
                # hard check to track if motors ar neither fullthrottle or off
                "safety_zone": 1.0,
            }
        },

        "model_kwargs": {
            'policy': 'MultiInputPolicy',
            'policy_kwargs': dict(
                net_arch=dict(pi=[256, 256], vf=[256, 256]), #[128, 128]  # default [64, 64]
                activation_fn=torch.nn.Tanh
            ),
            'n_steps': 2048,
            'batch_size': 64,
            'gamma': 0.99,
            'learning_rate': 1e-4,
            'ent_coef': 0.001,
            'clip_range': 0.2,
            'n_epochs': 5,
            'verbose': 0,
        }
    }

    if CONFIG['env_kwargs']['anomaly_knowledge']:
        anomaly_known = "AnoTrue_"
    else:
        anomaly_known = "AnoFalse_"

    if CONFIG['env_kwargs']['reward_type'] == "additive":
        reward_type_string = "_add_"
    elif CONFIG['env_kwargs']['reward_type'] == "multiplicative":
        reward_type_string = "_geo_"
    else:
        reward_type_string = "_UnknownReward_"

    save_path_name = "PPO_HRL-A_" + f"{time.strftime('%Y-%m-%d_%H-%M')}"+"_ENV_" + env_string \
                    + reward_type_string + anomaly_known +"_" + CONFIG['run_info']
    CONFIG['save_name']=save_path_name

    if training_steps < 1000: # Debug mode detected
        print("!!! DEBUG MODE: Reducing n_steps for fast feedback !!!")
        # Set n_steps to min 8, so buffer is small (8*8 = 64 steps)
        CONFIG['model_kwargs']['n_steps'] = 8 
        CONFIG['model_kwargs']['batch_size'] = 8 # Batch size must be <= buffer

    project_root = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
    save_path = os.path.join(project_root, "saves", save_path_name)
    os.makedirs(save_path, exist_ok=True)

    with open(os.path.join(save_path, "config.json"), "w") as f:
        json.dump(CONFIG, f, indent=4, default=lambda o: '<not serializable>')

    loader = TrajectoryDataLoader()
    
    # Load all available missions for evaluation
    all_available_eval_missions = loader.available_datasets
    eval_missions_config = {name: 1.0 for name in all_available_eval_missions}
    
    _, eval_mission_pool = loader.create_pools(eval_missions_config, load_eval_only=True)
    
    if not eval_mission_pool:
        raise ValueError("The evaluation pool is empty! Check 'dataset_definitions'.")
    
    eval_anomaly_pool = []
    
    # Get all failure types that could occur in training
    all_possible_anomalies = set()
    for stage in CONFIG['curriculum_stages']:
        all_possible_anomalies.update(stage['anomaly_config'].keys())
    
    print(f"Creating compact anomaly pool from: {sorted(all_possible_anomalies)}")

    for anomaly_name in sorted(all_possible_anomalies):
        if anomaly_name in loader.anomaly_datasets:
            all_files = loader.anomaly_datasets[anomaly_name]
            
            # IMPORTANT: Always take Index 0 (Eval-Sequence) + max 2 variations
            files_to_load = all_files[:3] 
            
            for f in files_to_load:
                df = pd.read_csv(f)
                df['anomaly_name'] = anomaly_name # Save name for analysis
                eval_anomaly_pool.append(df)
        else:
            print(f"Warning: Anomaly '{anomaly_name}' not found in loader.")

    # Set Eval_env
    eval_env_kwargs = {
        **CONFIG['env_kwargs'], 
        'mission_pool': eval_mission_pool, 
        'is_eval': True, 
        'seed': 42, # Fixed seed for comparability
        
        # Here we use our hand-picked pool
        'anomaly_pool': eval_anomaly_pool,
        'anomaly_chance': 1.0 # Always check for faults during eval!
    }
    
    # DummyVecEnv wraps the Env for SB3
    eval_env = DummyVecEnv([lambda: Monitor(HRL_Att_Env(**eval_env_kwargs))])
    
    # IMPORTANT: Determine number of Eval episodes
    # We ideally want to see every anomaly in the pool at least once.
    # Since the Env iterates (idx % len), we set n_eval_episodes equal to pool size.
    
    n_eval_eps = len(eval_mission_pool) * len(eval_anomaly_pool) 

    print(f"EvalCallback configured for {n_eval_eps} episodes per check.")

    eval_callback = EvalCallback(
        eval_env,
        eval_freq = max(100_000 // CONFIG['num_cpu'], 1), # dummy value will be overwritten in each stage
        n_eval_episodes=n_eval_eps, 
        deterministic=True
    )
    

    # =================================================================================
    # --- MODEL TRAINING (Curriculum Loop) ---
    # =================================================================================
    model = None
    last_model_path = None

    for i, stage in enumerate(CONFIG['curriculum_stages']):
        stage_num = i + 1

        #if stage_num == 2:
        #    print("\nTraining will be terminated as planned after Stage 1 completion.")
        #    break

        print("\n" + "="*80 + f"\nSTART CURRICULUM STAGE {stage_num}/{len(CONFIG['curriculum_stages'])}: {stage['name']}\n" + "="*80)
        start_time_stage = time.perf_counter()

        # Create a separate save location for best models and logs for each stage
        stage_save_path = os.path.join(save_path, f"stage_{stage_num}_{stage['name']}")
        os.makedirs(stage_save_path, exist_ok=True)

         ## Test here custom env-kwargs
        # 1. Start with a deep copy of the base configuration
        current_env_kwargs = copy.deepcopy(CONFIG['env_kwargs'])
        
        # 2. Overwrite with stage-specific values if present
        # Important: For nested dicts like 'reward_weights', we must merge intelligently.
        if 'env_kwargs' in stage:
            for key, value in stage['env_kwargs'].items():
                if isinstance(value, dict) and key in current_env_kwargs:
                    current_env_kwargs[key].update(value)
                else:
                    current_env_kwargs[key] = value
        
        # --- Create environments and callbacks for THIS stage ---
        # Crucial step: Recreating callbacks resets their internal counters.

        min_batch_size = CONFIG['model_kwargs']['n_steps'] * CONFIG['num_cpu']
        effective_timesteps = max(stage['timesteps'], min_batch_size)

        # EvalCallback is persistent outside of loop, here we update savepaths
        if eval_env is not None:
            eval_env.env_method("update_weights_online", current_env_kwargs['reward_weights'])

        eval_callback.best_model_save_path = stage_save_path
        eval_callback.log_path = stage_save_path
        eval_callback.eval_freq = np.ceil(0.17*(effective_timesteps / CONFIG['num_cpu'])) 
        eval_callback.best_mean_reward = -np.inf 


        checkpoint_plot_callback = CheckpointWithPlotsCallback(
            eval_pool=eval_mission_pool,
            env_kwargs=current_env_kwargs,
            save_freq= np.ceil(0.34*(effective_timesteps / CONFIG['num_cpu'])), 
            save_path=os.path.join(stage_save_path, 'checkpoints'),
            name_prefix="rl_model"
        )

        
        # --- Create training environment for THIS stage ---
        stage_train_pool = loader.create_pools(stage['missions'])[0]
        stage_anomaly_pool = loader.load_anomaly_pool(stage['anomaly_config'])
        train_env_kwargs = {
            **current_env_kwargs, 
            'mission_pool': stage_train_pool, 
            'is_eval': False,
            'anomaly_pool': stage_anomaly_pool,
            'anomaly_chance': stage['anomaly_chance'] # Use stage-specific probability
        }
        train_env = make_vec_env(HRL_Att_Env, n_envs=CONFIG['num_cpu'], seed=42, vec_env_cls=SubprocVecEnv, env_kwargs=train_env_kwargs)

        # --- Create or load model ---
        if last_model_path is None:
            # Create a new model for the first stage
            model = PPO(env=train_env, tensorboard_log=os.path.join(stage_save_path, 'logs'), **CONFIG['model_kwargs'])
        else:
            # Load the model from previous stage and assign the new environment.
            # SB3 handles the details.
            print(f"Loading model from previous stage: {last_model_path}")
            model = PPO.load(last_model_path, env=train_env, **CONFIG['model_kwargs'])

        # --- Start training ---
        model.learn(
            total_timesteps=stage['timesteps'], 
            callback=[eval_callback, checkpoint_plot_callback], 
            progress_bar=True, 
            reset_num_timesteps=False # Important for cumulative logs in Tensorboard
        )
        
        # Save final model of this stage explicitly
        final_model_path = os.path.join(stage_save_path, "final_model.zip")
        model.save(final_model_path)
        last_model_path = os.path.join(stage_save_path, "best_model.zip")
        
        # Safety check: If no best model was saved, use the final model.
        if not os.path.exists(last_model_path):
            last_model_path = final_model_path

        train_env.close()
        end_time_stage = time.perf_counter()
        print(f"--- STAGE {stage_num} FINISHED in {end_time_stage - start_time_stage:.2f} seconds ---")

        # --- Qualitative evaluation for the BEST model of this stage ---
        print(f"\n--- Starting qualitative evaluation for the BEST model from Stage {stage_num} ---")
        best_model_path_stage = os.path.join(stage_save_path, "best_model.zip")
        if os.path.exists(best_model_path_stage):
            stage_eval_dir = os.path.join(stage_save_path, "qualitative_evaluation_best_model")
            run_rl_evaluation(best_model_path_stage, eval_mission_pool, eval_anomaly_pool, current_env_kwargs, stage_eval_dir)
        else:
            print(f"Warning: Could not find 'best_model.zip' in {stage_save_path}. Evaluation skipped.")
        

    print(f"\n--- TRAINING COMPLETED ---")
    eval_env.close()

    # =================================================================================
    # --- FINAL EVALUATION & COMPARISON ---
    # =================================================================================
    print("\n" + "="*80 + "\n--- STARTING FINAL EVALUATION AND BENCHMARKING ---\n" + "="*80)
    start_time_eval = time.perf_counter()
    
    # 1. Run evaluation with the final model of the entire training process
    final_eval_dir = os.path.join(save_path, 'final_evaluation')
    print("Running final evaluation with the last trained model...")
    run_rl_evaluation(last_model_path, eval_mission_pool, eval_anomaly_pool, current_env_kwargs, final_eval_dir)

    # 2. Compare final RL results with INDI benchmark (uncomment if needed)
    # indi_benchmark_dir = os.path.join(project_root, 'data', 'INDI')
    # compare_with_benchmark(final_eval_dir, indi_benchmark_dir, eval_mission_names)
    end_time_eval = time.perf_counter()

    print(f"\n--- Evaluation and benchmark completed in {end_time_eval - start_time_eval:.2f} seconds ---")
    
    end_time_total = time.perf_counter()
    print("\n" + "="*100)
    print(f"--- TOTAL SCRIPT EXECUTION TIME: {end_time_total - start_time_total:.2f} seconds | {(end_time_total - start_time_total)/60:.2f} minutes | {(end_time_total - start_time_total)/3600:.2f} hours ---")
    print("="*100)

if __name__ == '__main__':
    # This block is required for Multiprocessing on Windows
    # and ensures code only runs when script is started directly.
    main()