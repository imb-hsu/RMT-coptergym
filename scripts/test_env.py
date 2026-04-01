import numpy as np

def run_single_step(env, action, label=""):
    obs, info = env.reset(), {}
    
    print(f"\n--- {label} ---")
    
    obs, reward, terminated, truncated, info = env.step(action)

    print("Action:", action)
    print("Delta vel:", getattr(env, "delta_cmd_vel", None))
    print("Delta rpy:", getattr(env, "delta_cmd_rpy", None))

    print("Command vel (target):", info.get("mission_goal_vel"))
    print("Agent vel:", info.get("agent_vel_c"))
    print("Error vel:", info.get("error_vel_c"))

    print("Motor cmd:", info.get("action_cmd"))
    print("Measured motors:", info.get("motor_signal_measured_rps"))

    print("Reward:", reward)
    
    return info


def compare_env_behavior(env_class, env_kwargs=None):
    if env_kwargs is None:
        env_kwargs = {}

    # --- ENV 1: Baseline (no RL influence) ---
    env1 = env_class(**env_kwargs)
    zero_action = np.zeros(env1.action_space.shape)

    info_baseline = run_single_step(env1, zero_action, label="BASELINE (no delta)")

    # --- ENV 2: With RL delta ---
    env2 = env_class(**env_kwargs)
    
    # simple deterministic delta
    test_action = np.array([0.5, 0.0, 0.0,   # vel delta
                            0.1, 0.0, 0.0]) # rpy delta

    info_delta = run_single_step(env2, test_action, label="DELTA ACTION")

    # --- Compare ---
    print("\n=== COMPARISON ===")
    print("Vel diff:", np.array(info_delta["agent_vel_c"]) - np.array(info_baseline["agent_vel_c"]))
    print("Error diff:", np.array(info_delta["error_vel_c"]) - np.array(info_baseline["error_vel_c"]))