import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
import os
import ast
import sys
import seaborn as sns

# ==============================================================================
# 1. CONFIGURATION
# ==============================================================================
# Adjust these paths to point to your downloaded CSV files!
# You can use absolute paths or paths relative to the project root.

DATA_DIR = os.path.join(os.path.dirname(os.path.dirname(os.path.abspath(__file__))), "saves", "DesignChoices_CSV")
OUTPUT_DIR = os.path.join(os.path.dirname(os.path.dirname(os.path.abspath(__file__))), "data", "Plots_DesignChoices")

# Define the scenarios and the corresponding files for both models
SCENARIOS = {
    "Hover": {
        "Integral":   os.path.join(DATA_DIR, "Hover_rl_results_rel_I_additive.csv"),     # <--- CHANGE THIS
        "NoIntegral": os.path.join(DATA_DIR, "Hover_rl_results_rel_noI_additive.csv"),
        "Absolute": os.path.join(DATA_DIR, "Hover_rl_results_abs_noI_additive.csv")      # <--- CHANGE THIS
    },
    "Jump": {
        "Integral":   os.path.join(DATA_DIR, "Jump_rl_results_rel_I_additive.csv"),      # <--- CHANGE THIS
        "NoIntegral": os.path.join(DATA_DIR, "Jump_rl_results_rel_noI_additive.csv")    # <--- CHANGE THIS
    }
}

# Settings for metrics
STEADY_STATE_WINDOW = 2.0  # Seconds at the end of the flight to calculate static offset

# ==============================================================================
# 2. HELPER FUNCTIONS
# ==============================================================================
def parse_vector_col(series):
    """Parses string representations of vectors (e.g., '[0.1 0.2 0.3]') into numpy arrays."""
    parsed_list = []
    detected_len = 3
    for x in series:
        val = None
        if isinstance(x, (list, np.ndarray)): 
            val = list(x)
        elif isinstance(x, str):
            x = x.strip()
            try: 
                val = ast.literal_eval(x)
            except:
                try:
                    # Handle space-separated values inside brackets
                    clean = x.replace('[','').replace(']','').replace('\n',' ')
                    parts = clean.split()
                    if parts: val = [float(v) for v in parts]
                except: val = None
        
        if val and hasattr(val, '__len__'): 
            detected_len = len(val)
        parsed_list.append(val)
    
    final = []
    zeros = [0.0] * detected_len
    for item in parsed_list:
        if item is None or len(item) != detected_len: 
            final.append(zeros)
        else: 
            final.append(item)
    return np.array(final)

def calculate_metrics(df, name):
    """Calculates RMSE and Static Offset metrics."""
    metrics = {}
    
    # 1. Parse Vectors
    if 'agent_vel_c' not in df.columns or 'mission_goal_vel' not in df.columns:
        print(f"[WARN] Missing velocity columns in {name}. Cannot calculate metrics.")
        return None

    vel_actual = parse_vector_col(df['agent_vel_c'])
    vel_target = parse_vector_col(df['mission_goal_vel'])
    time = df['sim_time'].values
    
    # 2. Calculate Error Vector
    error = vel_target - vel_actual
    
    # 3. RMSE (Root Mean Square Error) - Overall tracking performance
    itae = np.mean(np.sum(error**2, axis=1))
    mse = np.mean(np.sum(error**2, axis=1))
    metrics['ITAE'] = itae
    metrics['RMSE_Vel'] = np.sqrt(mse)
    
    # 4. Static Offset (Steady State Error)
    # We look at the last N seconds of the trajectory
    t_end = time[-1]
    mask = time >= (t_end - STEADY_STATE_WINDOW)
    
    if np.any(mask):
        # Mean error in the steady state window
        static_offset_vec = np.mean(error[mask], axis=0)
        metrics['Static_Offset_X'] = static_offset_vec[0]
        metrics['Static_Offset_Y'] = static_offset_vec[1]
        metrics['Static_Offset_Z'] = static_offset_vec[2]
        metrics['Static_Offset_Norm'] = np.linalg.norm(static_offset_vec)
    else:
        metrics['Static_Offset_X'] = np.nan
        metrics['Static_Offset_Y'] = np.nan
        metrics['Static_Offset_Z'] = np.nan
        metrics['Static_Offset_Norm'] = np.nan
        
    # 5. Extract Motor Commands (if available)
    motors = None
    actions = None
    if 'motor_signal_measured_rps' in df.columns:
        motors = parse_vector_col(df['motor_signal_measured_rps'])
    if 'action_cmd' in df.columns:
        actions = parse_vector_col(df['action_cmd'])

    return metrics, vel_actual, vel_target, time, motors, actions

def plot_comparison(scenario_name, data_dict):
    """Generates a 3-subplot figure comparing velocities."""
    fig, axes = plt.subplots(3, 1, figsize=(10, 12), sharex=True)
    fig.suptitle(f"{scenario_name} Comparison: Velocity Tracking", fontsize=16)
    
    axes_labels = ['Vx (Forward)', 'Vy (Right)', 'Vz (Down)']
    
    # Plot Target (using the first available dataset, assuming targets are similar)
    target_plotted = False
    
    for model_name, data in data_dict.items():
        time = data['time']
        vel = data['vel']
        target = data['target']
        
        # Plot Target only once to avoid clutter
        if not target_plotted:
            axes[0].plot(time, target[:, 0], 'k--', label='Target', linewidth=1.5, alpha=0.7)
            axes[1].plot(time, target[:, 1], 'k--', linewidth=1.5, alpha=0.7)
            axes[2].plot(time, target[:, 2], 'k--', linewidth=1.5, alpha=0.7)
            target_plotted = True
            
        # Plot Agent
        axes[0].plot(time, vel[:, 0], label=model_name)
        axes[1].plot(time, vel[:, 1], label=model_name)
        axes[2].plot(time, vel[:, 2], label=model_name)

    # Formatting
    for i, ax in enumerate(axes):
        ax.set_ylabel(f"{axes_labels[i]} [m/s]", fontsize=12)
        ax.grid(True, which='both', linestyle='--', alpha=0.7)
        ax.legend(loc='upper right')
        
    axes[2].set_xlabel("Time [s]", fontsize=12)
    
    plt.tight_layout()
    save_path = os.path.join(OUTPUT_DIR, f"Comparison_{scenario_name}.png")
    plt.savefig(save_path)
    plt.close(fig)
    print(f"  > Plot saved to: {save_path}")

def plot_motor_comparison(scenario_name, data_dict, motor_idx=0):
    """Generates a plot comparing a specific motor command across models."""
    fig, ax = plt.subplots(figsize=(8, 5))
    fig.suptitle(f"Comparison of absolute and relative actionspaces", fontsize=17)
    
    # Define styles and filter for specific models
    model_styles = {
        "Absolute":   {"label": "abs. action", "color": "#D55E00", "alpha": 0.80, "zorder": 1},
        "NoIntegral": {"label": "rel. action", "color": "#0072B2",   "alpha": 1.00, "zorder": 2}
    }

    # Iterate in specific order to ensure layering (Absolute in background)
    for model_name in ["Absolute", "NoIntegral"]:
        if model_name in data_dict:
            data = data_dict[model_name]
            time = data['time']
            motors = data.get('motors')
            actions = data.get('actions')
            style = model_styles[model_name]
            
            if motors is not None and len(motors) > 0 and motors.shape[1] > motor_idx:
                ax.plot(
                    time, 
                    motors[:, motor_idx], 
                    label= style["label"]+" (motorcmds)", 
                    color=style["color"],
                    linewidth=1.5, 
                    alpha=style["alpha"],
                    zorder=style["zorder"]
                )

            if actions is not None and len(actions) > 0 and actions.shape[1] > motor_idx:
                ax.plot(
                    time, 
                    actions[:, motor_idx], 
                    label=style["label"]+" (actiontargets)", 
                    color=style["color"],
                    linewidth=1.5, 
                    alpha=style["alpha"]-0.3,
                    zorder=style["zorder"]
                )

    ax.set_ylabel("Motor Signal [RPS]", fontsize=15)
    ax.set_xlabel("Time [s]", fontsize=15)
    ax.tick_params(axis='y', labelsize=14) 
    ax.tick_params(axis='x', labelsize=14)    
    ax.grid(True, which='both', linestyle='--', alpha=0.7)
    
    # Custom Legend outside plot
    ax.legend()
    sns.move_legend(
        ax, "lower center", 
        bbox_to_anchor=(0.5, 1.0), 
        ncol=2, 
        title=None, frameon=False, fontsize=15
    )
    
    plt.tight_layout()
    save_path = os.path.join(OUTPUT_DIR, f"Comparison_Motor{motor_idx+1}_{scenario_name}.png")
    plt.savefig(save_path, bbox_inches='tight')
    plt.close(fig)
    print(f"  > Motor Plot saved to: {save_path}")

# ==============================================================================
# 3. MAIN EXECUTION
# ==============================================================================
if __name__ == "__main__":
    os.makedirs(OUTPUT_DIR, exist_ok=True)
    
    print("=== STARTING VELOCITY COMPARISON FROM CSV ===")
    
    for scenario_name, files in SCENARIOS.items():
        print(f"\n--- Processing Scenario: {scenario_name} ---")
        
        plot_data = {}
        metrics_summary = []
        
        for model_name, file_path in files.items():
            if not os.path.exists(file_path):
                print(f"[WARN] File not found: {file_path}. Skipping {model_name}.")
                continue
            
            try:
                df = pd.read_csv(file_path)
                res = calculate_metrics(df, model_name)
                
                if res:
                    metrics, vel, target, time, motors, actions = res
                    
                    # Store for plotting
                    plot_data[model_name] = {
                        'time': time,
                        'vel': vel,
                        'target': target,
                        'motors': motors,
                        'actions': actions
                    }
                    
                    # Store metrics
                    metrics['Model'] = model_name
                    metrics_summary.append(metrics)
                    
            except Exception as e:
                print(f"[ERROR] Failed to process {file_path}: {e}")

        # Print Metrics Table
        if metrics_summary:
            df_metrics = pd.DataFrame(metrics_summary)
            # Reorder columns for readability
            cols = ['Model', 'RMSE_Vel', 'Static_Offset_Norm', 'Static_Offset_X', 'Static_Offset_Y', 'Static_Offset_Z']
            print("\nPerformance Metrics:")
            print(df_metrics[cols].to_string(index=False, float_format=lambda x: "{:.4f}".format(x)))
            
            # Save metrics to CSV
            df_metrics.to_csv(os.path.join(OUTPUT_DIR, f"Metrics_{scenario_name}.csv"), index=False)

        # Generate Plot
        if len(plot_data) > 0:
            plot_comparison(scenario_name, plot_data)
            plot_motor_comparison(scenario_name, plot_data, motor_idx=2) # Plot Motor 1
        else:
            print(f"[WARN] Not enough data to plot {scenario_name}.")

    print("\n=== DONE ===")
    print(f"Results are in: {OUTPUT_DIR}")