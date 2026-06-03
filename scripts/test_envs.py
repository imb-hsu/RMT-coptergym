import os
import sys
import platform
import numpy as np
import pandas as pd
import time

# SB3 imports for parallelization testing
try:
    from stable_baselines3.common.env_util import make_vec_env
    from stable_baselines3.common.vec_env import SubprocVecEnv
except ImportError:
    print("[ERROR] stable-baselines3 is required for the parallelization test.")
    sys.exit(1)

from rmt_coptergym.application_envs.RL_FTC_Hybrid_deltaTargets_Env import VEL_Env as RL_FTC_Hybrid_deltaTargets_Env
from rmt_coptergym.application_envs.RL_FTC_Hybrid_deltaMotors_Env import VEL_Env as RL_FTC_Hybrid_deltaMotors_Env
from rmt_coptergym.utils.trajectory_dataloader import TrajectoryDataLoader

# --- Configuration ---
SEED = 42
CTRL_FREQ = 125
MAX_STEPS = 250  
TEST_STEPS = [0, 5, 50, 150, 249] 

ENV_CLASSES = {
    "FTC_dTargets": RL_FTC_Hybrid_deltaTargets_Env,
    "FTC_dMotors": RL_FTC_Hybrid_deltaMotors_Env,
}

# --- Visual Formatting Engine ---
def format_vec(vec, prec=2, add_padding=True):
    """
    Formats any vector (length 1, 3, or 8) into a string with 
    fixed-width slots to ensure perfect vertical alignment in tables.
    """
    if not isinstance(vec, (list, np.ndarray)):
        vec = [vec]
    
    vec = np.array(vec).flatten()
    slots = 8 # Force 8 slots for visual consistency
    
    parts = []
    for i in range(slots):
        if i < len(vec):
            parts.append(f"{vec[i]: >7.{prec}f}")
        else:
            # Padding for short vectors (3-element ones)
            if add_padding:
                parts.append(" " * 7)
            
    return "[" + " ".join(parts) + "]"

def print_header(text, char="="):
    print(f"\n{char*160}\n{text.center(160)}\n{char*160}")

def print_separator(column_names, col_width=65):
    """Prints a clean table separator line."""
    total_width = 17 + (len(column_names) * (col_width + 3))
    print("-" * total_width)

# --- Comparison Runner ---
def run_comparison():

    print_header('RL FTC HYBRID ENVIRONMENT ANALYSIS')

    print("We use here a comparison between INDI and teh FTC agents.")
    print("This helps to see how we interact with the RL actions in the FTC hybrid space.")
    print("FTC_dTargets changes the velocity target for teh controller, which leads to x,y,z movement.")
    print("FTC_dMotors addes additional load to the INDI motor commands.")
    print()


    # Setup Anomaly: 50% loss on all motors
    motor_columns = [f"motorloss_{i}" for i in range(1, 9)]
    anomaly_df = pd.DataFrame([[0.0] + [0.5]*8], columns=["time"] + motor_columns)
    
    results_store = {step: {} for step in TEST_STEPS}
    column_names = []

    # Setup Trajectory Data
    project_root = os.getcwd()
    loader = TrajectoryDataLoader(
        base_data_dir=os.path.join(project_root, 'data', 'trajectories'),
        anomaly_base_data_dir=os.path.join(project_root, 'data', 'anomalies')
    )
    _, eval_pool = loader.create_pools({"Position_Hover": 1.0}, load_eval_only=True)
    mission = eval_pool[0]

    # Run variations
    for env_name, env_class in ENV_CLASSES.items():
        for run_type in ["REF", "ACT"]:
            if run_type == "REF":
                col_name = f"INDI"
            elif run_type== "ACT":
                col_name= env_name

            column_names.append(col_name)
            
            env = env_class(
                mission_pool=[mission],
                anomaly_pool=[anomaly_df],
                anomaly_chance=1.0,
                is_eval=True,
                seed=SEED,
                use_unix=platform.system() != "Windows",
                ctrl_freq=CTRL_FREQ
            )
            
            obs, info = env.reset(seed=SEED)
            action_val = 1.0 if run_type == "ACT" else 0.0
            action = np.ones(env.action_space.shape) * action_val

            for s in range(MAX_STEPS):
                obs, _, term, trunc, info = env.step(action)
                if s in TEST_STEPS:
                    results_store[s][col_name] = {
                        "00_Pos": info['agent_pos'],
                        "01_Vel_C": info['agent_vel_c'],
                        "02_INDI_Vel": info['indi_cmd_vel'],
                        "03_Anomaly": info['anomaly_motorloss'],
                        "04_Action": action,
                        "05_INDI_RPY": info['indi_cmd_rpy'],
                        "06_Motor_RPS": info['motor_signal_measured_rps'],
                        "07_Sim_Input": info['motor_signal_sim_input'],
                        "08_INDI_cmd": info['INDI_cmd']
                    }
                if term or trunc: break
            env.close()

    # --- Print Structured Table ---
    metrics = ["00_Pos", "01_Vel_C", "02_INDI_Vel", "03_Anomaly", "04_Action", "05_INDI_RPY", "06_Motor_RPS", "07_Sim_Input", "08_INDI_cmd"]
    
    for step in TEST_STEPS:
        print(f"\n\n[ TIME STEP: {step:03d} ]")
        print_separator(column_names)
        
        # Header Row
        header_row = f"{'METRIC':<16} | "
        for name in column_names:
            header_row += f"{name:^65} | "
        print(header_row)
        print_separator(column_names)
        
        # Data Rows
        for m in metrics:
            row_str = f"{m:<16} | "
            for col in column_names:
                raw_val = results_store[step][col][m]
                formatted_val = format_vec(raw_val)
                row_str += f"{formatted_val} | "
            print(row_str)
        
        print_separator(column_names)

# --- Parallelization Test with Asymmetric Faults ---
def test_parallelization_robust():
    print_header("PARALLELIZATION & ISOLATION TEST: ASYMMETRIC FAULTS")

    print("Here we inspect if the envs behave truly parallel without influence in the subprocvec envs.")
    
    project_root = os.getcwd()
    loader = TrajectoryDataLoader(
        base_data_dir=os.path.join(project_root, 'data', 'trajectories'),
        anomaly_base_data_dir=os.path.join(project_root, 'data', 'anomalies')
    )
    _, eval_pool = loader.create_pools({"Position_Hover": 1.0}, load_eval_only=True)
    mission = eval_pool[0]

    n_envs = 2
    
    def make_env_fn(rank):
        def _init():
            motor_cols = [f"motorloss_{i}" for i in range(1, 9)]
            
            # Env 0: ASYMMETRIC FAULT
            # This should cause significant tumbling/rotation.
            if rank == 0:
                fault_pattern = [0.8, 0.2, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0]
            else:
                fault_pattern = [0.0] * 8 # Clean
                
            anom_df = pd.DataFrame([[0.0] + fault_pattern], columns=["time"] + motor_cols)
            
            return RL_FTC_Hybrid_deltaMotors_Env(
                max_duration=10,
                mission_pool=[mission],
                anomaly_pool=[anom_df],
                anomaly_chance=1.0,
                is_eval=True,
                seed=SEED + rank,
                use_unix=platform.system() != "Windows"
            )
        return _init

    print(f"Initializing {n_envs} environments via SubprocVecEnv...")
    envs = SubprocVecEnv([make_env_fn(i) for i in range(n_envs)])
    envs.reset()
    
    # Both ENVs get FULL ACTION (1.0)
    actions = np.ones((n_envs, envs.action_space.shape[0]))

    infos = envs.reset_infos
    pp0, pp1 = infos[0]['agent_pos'], infos[1]['agent_pos']
    
    # Step for 125 cycles (1 second)
    count_dones=0
    for _ in range(125):
        obs, rewards, dones, infos = envs.step(actions)
        if any(dones):
            break

    #print(infos)
    # Capture results
    f0, f1 = infos[0]['anomaly_motorloss'], infos[1]['anomaly_motorloss']
    p0, p1 = infos[0]['agent_pos'], infos[1]['agent_pos']
    m0, m1 = infos[0]['motor_signal_sim_input'], infos[1]['motor_signal_sim_input']
    mm0, mm1 = infos[0]['motor_signal_measured_rps'], infos[1]['motor_signal_measured_rps']

    print("\n" + "="*85)
    print("ENV 0 [ASYMMETRIC FAULT + FULL ACTION]:") 
    if (dones[0]):
        print("  --> this simulation stopped: ", infos[0]['status'])
    print(f"  Anomaly Pattern: {format_vec(f0)}")
    print(f"  Sim Input:       {format_vec(m0)}")
    print(f"  Motor Measured:  {format_vec(mm0)}")
    print(f"  Position:        {format_vec(pp0, add_padding=False)} --> {format_vec(p0, add_padding=False)}")
    
    print("\nENV 1 [CLEAN + FULL ACTION]:")
    if (dones[1]):
        print("  --> this simulation stopped: ", infos[1]['status'])
    print(f"  Anomaly Pattern: {format_vec(f1)}")
    print(f"  Sim Input:       {format_vec(m1)}")
    print(f"  Motor Measured:  {format_vec(mm1)}")
    print(f"  Position:        {format_vec(pp1, add_padding=False)} --> {format_vec(p1, add_padding=False)}")
    print("="*85)

    # Validation Logic
    isolation_ok = (np.max(f1) == 0 and np.max(f0) > 0)
    # Dynamics check: Env 0 should have drifted/tumbled far away from Env 1
    drift_distance = np.linalg.norm(p0 - p1)
    dynamics_ok = drift_distance > 0.5 
    
    print(f"\nIsolation (Fault Leakage):    {'PASSED' if isolation_ok else 'FAILED'}")
    print(f"Dynamics (Drift Difference):  {'PASSED' if dynamics_ok else 'FAILED'} (Dist: {drift_distance:.2f}m)")
    print("_"*100)
    
    envs.close()
    return isolation_ok and dynamics_ok

# --- Main Execution ---
if __name__ == "__main__":
    # 1. Detailed Analysis
    run_comparison()
    # 2. Parallelism Test
    parallel_success = test_parallelization_robust()