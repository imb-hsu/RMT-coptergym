"""
Test Script to evaluate teh effects of FTC envs actions on actual INDI and RL performance!
delta_motors: with an added delta of 50 we have very high impact and affect dynamics effectively, lower scale will be anti-controlled
delta_targets: manipualted targets with vel of 2m/s have effects after around 1-2 sec but get anti-controlled by INDI later
"""
import os, sys
import numpy as np
import pandas as pd
import platform
import matplotlib.pyplot as plt

from rmt_coptergym.application_envs.RL_FTC_Hybrid_deltaTargets_Env import VEL_Env as RL_FTC_Hybrid_deltaTargets_Env
from rmt_coptergym.application_envs.RL_FTC_Hybrid_deltaMotors_Env import VEL_Env as RL_FTC_Hybrid_deltaMotors_Env
from rmt_coptergym.application_envs.RL_VEL_Env_absolute import VEL_Env as RL_VEL_Env_absolute
from rmt_coptergym.utils.trajectory_dataloader import TrajectoryDataLoader

# --- Config ---
SEED = 42
MAX_STEPS = 1250

ENV_CLASSES = {
    "delta_targets": RL_FTC_Hybrid_deltaTargets_Env,
    "delta_motors": RL_FTC_Hybrid_deltaMotors_Env,
    "vel_absolute": RL_VEL_Env_absolute,   # optional
}

LOG_KEYS = [
    "sim_time",
    "agent_pos",
    "agent_vel_c",
    "error_pos",
    "motor_signal_measured_rps",
    "indi_cmd_vel",
    "indi_cmd_rpy",
    "anomaly_motorloss",
]

# --- Anomalien manuell definieren ---
motor_columns = [f"motorloss_{i}" for i in range(1, 9)]
ANOMALY_LEVELS = {
    "no_fault": 0.0,
    "mid_fault": 0.5,
    "full_fault": 1.0
}

custom_anomaly_pool = {
    name: pd.DataFrame([[0.0] +[0.0] + [val]*7 ], columns=["time"] + motor_columns)
    for name, val in ANOMALY_LEVELS.items()
}

# --- Dummy Actions ---
def get_dummy_action(env_class, env, mode="zero"):
    if mode == "zero":
        return -1*np.ones(env.action_space.shape) if env_class==RL_VEL_Env_absolute else np.zeros(env.action_space.shape)
    elif mode == "constant":
        return np.ones(env.action_space.shape) * 1.0 # 0.85
    else:
        raise ValueError(f"Unknown action mode {mode}")

# --- Runner ---
def run_env(env_class, mission_df, anomaly_pool, anomaly_chance, action_mode, max_steps=MAX_STEPS):
    env = env_class(
        mission_pool=[mission_df],
        anomaly_pool=anomaly_pool,
        anomaly_chance=anomaly_chance,
        is_eval=True,
        seed=SEED,
        use_unix=platform.system() != "Windows",
        ctrl_freq=125,
        max_duration=10.0,
    )

    LOG_STEPS = set([0,1,2,3,4, 125, 250])

    obs, info = env.reset(seed=SEED)
    log = [info]

    for step in range(max_steps):
        action = get_dummy_action(env, action_mode)
        obs, _, terminated, truncated, info = env.step(action)
        log.append(info)

        if step in LOG_STEPS or terminated or truncated:
            print(f"Step {step}:")
            print(f"  pos        = {info['agent_pos']}")
            print(f"  vel_c      = {info['agent_vel_c']}")
            print(f"  indi_vel   = {info['indi_cmd_vel']}")
            print(f"  motor_rps  = {info['motor_signal_measured_rps']}")
            print(f"  anomaly    = {info['anomaly_motorloss']}")

        if terminated or truncated:
            break

    env.close()
    return pd.DataFrame(log)

def fmt(arr, precision=4):
    arr = np.array(arr).flatten()
    return "[" + ", ".join(f"{x:.{precision}f}" for x in arr) + "]"

def build_row(step, info, action):
    return {
        "sim_time": fmt(info["sim_time"]),
        "step": step,
        "pos": fmt(info["agent_pos"]),
        "vel_c": fmt(info["agent_vel_c"]),
        "indi_vel": fmt(info["indi_cmd_vel"]),
        "action": fmt(action),
        "motor_rps": fmt(info["motor_signal_measured_rps"]),
        "sim_in": fmt(info["motor_signal_simin"]),
        "anomaly": fmt(info["anomaly_motorloss"]),
    }

def run_env_pretty(env_class, mission_df, anomaly_pool, anomaly_chance, action_mode, max_steps=250):

    LOG_STEPS = set([0,1,2,3,4,125,250, 500, 1000])

    env = env_class(
        mission_pool=[mission_df],
        anomaly_pool=anomaly_pool,
        anomaly_chance=anomaly_chance,
        is_eval=True,
        seed=SEED,
        use_unix=platform.system() != "Windows",
        ctrl_freq=125,
        max_duration=10.0,
    )

    obs, info = env.reset(seed=SEED)

    rows = []

    print("Motor Min:", env.limits.motor.min)
    print("Motor Max:", env.limits.motor.max)
    print("Motor Range:", env.limits.motor.range)
    print("Action Type:", env.action_space_type)

    for step in range(max_steps):
        action = get_dummy_action(env_class, env, action_mode)
        obs, _, terminated, truncated, info = env.step(action)

        if step in LOG_STEPS:
            rows.append(build_row(step, info, action))

        if terminated or truncated:
            break

    env.close()

    df = pd.DataFrame(rows)

    # 🔥 schöner Terminal-Print
    print("\n" + "="*80)
    print(f"ENV: {env_class}")
    print("="*80)
    print(df.to_string(index=False))

    return df

# --- Compare Runs robust ---
def compare_runs(df_a, df_b, keys):
    diffs = {}
    for k in keys:
        if k in df_a.columns and k in df_b.columns:
            try:
                a_vals = np.array([np.array(v, dtype=float) for v in df_a[k].values])
                b_vals = np.array([np.array(v, dtype=float) for v in df_b[k].values])

                len_max = max(len(a_vals), len(b_vals))
                if len(a_vals) < len_max:
                    pad_shape = (len_max - len(a_vals), a_vals.shape[1])
                    a_vals = np.vstack([a_vals, np.full(pad_shape, np.nan)])
                if len(b_vals) < len_max:
                    pad_shape = (len_max - len(b_vals), b_vals.shape[1])
                    b_vals = np.vstack([b_vals, np.full(pad_shape, np.nan)])

                diffs[k] = np.nanmean(np.abs(a_vals - b_vals))
            except Exception as e:
                print(f"Skipping key {k} due to error: {e}")
                continue
    return diffs

# --- Print Summary ---
def print_diff_summary(results):
    for (anom_name, run_type), diff in results.items():
        print(f"\n--- {anom_name} | {run_type} ---")
        for k, v in diff.items():
            print(f"{k:25s}: {v:.4f}")

# --- Plot Diff optional ---
def plot_diff(results, key):
    labels = []
    values = []
    for (anom_name, run_type), diff in results.items():
        if key in diff:
            labels.append(f"{anom_name}_{run_type}")
            values.append(diff[key])
    plt.figure(figsize=(8,4))
    plt.bar(labels, values)
    plt.ylabel(key)
    plt.xticks(rotation=30)
    plt.show()

def compare_stepwise(runs, keys):
    env_names = list(runs.keys())
    base = env_names[0]

    for other in env_names[1:]:
        print(f"\n--- Comparing {base} vs {other} ---")

        df_a = runs[base]
        df_b = runs[other]

        steps = min(len(df_a), len(df_b))

        for step in range(steps):
            print(f"\nStep {step}:")

            for k in keys:
                if k not in df_a.columns or k not in df_b.columns:
                    continue

                try:
                    a = np.array(df_a[k].iloc[step], dtype=float)
                    b = np.array(df_b[k].iloc[step], dtype=float)

                    diff = np.abs(a - b)

                    print(f"{k:25s} | A: {a} | B: {b} | |Δ|={np.round(diff,4)}")

                except Exception as e:
                    print(f"{k:25s} | skipped ({e})")


# --- Main ---
if __name__ == "__main__":
    try:
        project_root = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
    except NameError:
        project_root = '.'

    output_dir = os.path.join(project_root, 'data', 'INDI_test')
    os.makedirs(output_dir, exist_ok=True)

    loader = TrajectoryDataLoader(
        base_data_dir=os.path.join(project_root, 'data', 'trajectories'),
        anomaly_base_data_dir=os.path.join(project_root, 'data', 'anomalies')
    )

    _, eval_mission_pool = loader.create_pools({"Position_Hover": 1.0}, load_eval_only=True)
    mission = eval_mission_pool[0]
    print(mission)

    results = {}

    # --- Loop over anomalies and run types ---
for anom_name, anom_val in ANOMALY_LEVELS.items():
    for run_type in ["reference", "actioned"]:
        action_mode = "zero" if run_type == "reference" else "constant"

        anomaly_df_list = [custom_anomaly_pool[anom_name]] if anom_val > 0 else []

        print(f"\n==============================")
        print(f"TEST: {anom_name} | {run_type}")
        print(f"==============================")

        runs = {}
        for env_name, env_class in ENV_CLASSES.items():
            print(f"\nRunning env: {env_name}")
            df = run_env_pretty(env_class, mission, anomaly_df_list, anom_val, action_mode, max_steps=MAX_STEPS)
            runs[env_name] = df

        # Direktvergleich
        #compare_stepwise(runs, LOG_KEYS)

    # --- Summary ---
    #print_diff_summary(results)

    # Optional: Beispielplot für "motor_signal_measured_rps"
    #plot_diff(results, "motor_signal_measured_rps")