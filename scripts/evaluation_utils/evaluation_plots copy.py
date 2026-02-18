import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
from matplotlib.ticker import FormatStrFormatter

import seaborn as sns
import os
import ast
from metrics import calculate_composite_score

# ==============================================================================
# 1. CONFIGURATION
# ==============================================================================
EVAL_MISSIONS = [
    "Benchmark_Ministep", 
    "Benchmark_Spiral", 
    "Benchmark_Response", 
    "Benchmark_Stabilize"
]

EVAL_ANOMALIES = [
    "abrupt_LoE" , 
    "abrupt_LoE_multi", 
    "gradual_LoE", 
    "gradual_LoE_multi", 
    "Intermittent_Actuator_Dropout", 
    "Intermittent_Actuator_Dropout_multi", 
    "permanent_LoE", 
    "permanent_LoE_multi"
    ]

ALL_SCENARIOS = ["baseline"] + EVAL_ANOMALIES

# Mapping for readable names in plot
SCENARIO_PRETTY_NAMES = {
    "baseline": "NORM",
    "abrupt_LoE": "ALOE", 
    "abrupt_LoE_multi": "ALOE (Multi)",
    "gradual_LoE": "GLOE", 
    "gradual_LoE_multi": "GLOE (Multi)", 
    "Intermittent_Actuator_Dropout": "IAD", 
    "Intermittent_Actuator_Dropout_multi": "IAD (Multi)", 
    "permanent_LoE": "PLOE", 
    "permanent_LoE_multi": "PLOE (Multi)"

}

def set_paper_style():
    plt.rcParams.update({
        "font.family": "serif",
        "font.serif": ["Times New Roman", "DejaVu Serif"],
        "font.size": 10,
        "axes.titlesize": 10,
        "axes.labelsize": 10,
        "legend.fontsize": 10,
        "xtick.labelsize": 8,
        "ytick.labelsize": 8,
        "lines.linewidth": 1.5,
        "figure.dpi": 300,
        "savefig.bbox": "tight",
        "axes.facecolor": "white",
        "grid.color": "#E0E0E0",
        "grid.linestyle": ":",
    })

PALETTE = {
    "Target": "black",             
    "INDI": "#4E4E4E",            
    "RL Add. (Blind)": "#E69F00", 
    "RL Geo. (Blind)": "#56B4E9", 
    "RL Add. (Aware)": "#D55E00", 
    "RL Geo. (Aware)": "#0072B2", 
}

STYLE = {
    
}

if name == "Target": ls, lw, alpha = ':', 1.25, 1.0
                    elif name == "INDI": ls, lw, alpha = '--', 1.0, 0.8
                    else: ls, lw, alpha = '-', 1.0, 0.8

NAME_MAPPING = {
    "INDI_Controller": "INDI",
    "RL_Add_Blind": "RL Add. (Blind)",
    "RL_Geo_Blind": "RL Geo. (Blind)",
    "RL_Add_Aware": "RL Add. (Aware)",
    "RL_Geo_Aware": "RL Geo. (Aware)",
}

HUE_ORDER = ["INDI", "RL Add. (Blind)", "RL Geo. (Blind)", "RL Add. (Aware)", "RL Geo. (Aware)"]


Z_ORDER = {
    "Target": 1,
    "RL Add. (Blind)": 3,
    "RL Geo. (Blind)": 4,
    "RL Add. (Aware)": 5,
    "RL Geo. (Aware)": 6,
    "INDI": 10 
}

# ==============================================================================
# 2. HELPER
# ==============================================================================
def parse_vector_col(series):
    parsed_list = []
    detected_len = 3
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
        if val and hasattr(val, '__len__'): detected_len = len(val)
        parsed_list.append(val)
    
    final = []
    zeros = [0.0]*detected_len
    for item in parsed_list:
        if item is None or len(item) != detected_len: final.append(zeros)
        else: final.append(item)
    return np.array(final)

def load_and_filter_data(csv_path):
    if not os.path.exists(csv_path): raise FileNotFoundError(f"CSV fehlt: {csv_path}")
    df = pd.read_csv(csv_path)
    
    # Mapping Agent Names
    df["Agent"] = df["Agent"].map(NAME_MAPPING).fillna(df["Agent"])
    df["Mission_Clean"] = df["Mission"].str.replace("Benchmark_", "", regex=False).str.replace("_", " ", regex=False)
    
    # Mapping Scenarios (for Plot-Labels)
    # We create a new column 'Scenario_Label', keeping 'Scenario' for filtering
    df["Scenario_Label"] = df["Scenario"].map(SCENARIO_PRETTY_NAMES).fillna(df["Scenario"])

    # Filter Missions
    df = df[df["Mission"].isin(EVAL_MISSIONS)]
    
    # Filter Anomalies
    def is_valid_scenario(s):
        if "baseline" in s.lower(): return True
        for anom in EVAL_ANOMALIES:
            if anom in s: return True
        return False
    
    df = df[df["Scenario"].apply(is_valid_scenario)]

    print(df.head(3))
    
    # Calculate Score if not present (or recalculate to be safe)
    df = calculate_composite_score(df)
    
    return df

# ==============================================================================
# 3. LATEX TABLE (With Instability Check)
# ==============================================================================
def generate_latex_table(df, output_dir):
    print("\n--- Generating LaTeX Table ---")
    metrics = ["Stability", "WCR", "RMSE_TE_VEL", "RMSE_TE_XYZ", "RMSE_TE_RPY", "Score" ] #, "Energy"]
    available = [m for m in metrics if m in df.columns]
    
    grouped = df.groupby("Agent")[available]

    means = grouped.mean()
    stds = grouped.std()

    
    
    df_tex = pd.DataFrame(index=means.index)
    for m in available:
        if m == "Jitter":
            mean_str = means[m].apply(lambda x: f"{x:.2e}")
            std_str = stds[m].apply(lambda x: f"{x:.2e}")
        elif m in ["RMSE_TE_VEL", "RMSE_TE_XYZ", "RMSE_TE_RPY", "Score"]:
            mean_str = means[m].apply(lambda x: f"{x:.2f}")
            std_str = stds[m].apply(lambda x: f"{x:.2f}")
        else:
            mean_str = means[m].apply(lambda x: f"{x:.2f}")
            std_str = stds[m].apply(lambda x: f"{x:.2f}")
        df_tex[m] = "$" + mean_str + " \\pm " + std_str + "$"
        
    df_tex = df_tex.reindex([h for h in HUE_ORDER if h in df_tex.index])
    
    tex_path = os.path.join(output_dir, "Table_Overall_Performance.tex")
    with open(tex_path, "w") as f:
        f.write(df_tex.to_latex(escape=False, column_format="l" + "c"*len(available)))
    print(f"  > Saved as Latex table: {tex_path}")

# ==============================================================================
# 3a. BASELINE STATS TABLE (Jitter/Energy)
# ==============================================================================
def generate_baseline_stats_table(df, output_dir):
    print("\n--- Generating Energy/Jitter Stats Table (All Scenarios) ---")
    
    metrics = ["Energy", "Jitter"]
    available = [m for m in metrics if m in df.columns]
    
    if not available:
        print("  > No Energy/Jitter data found.")
        return

    # Group by Agent (aggregating over all missions and scenarios)
    grouped = df.groupby("Agent")[available]
    means = grouped.mean()
    stds = grouped.std()
    
    # 1. CSV Output (Readable)
    df_csv = pd.DataFrame(index=means.index)
    for m in available:
        if m == "Jitter":
            mean_str = means[m].apply(lambda x: f"{x:.3e}")
            std_str = stds[m].apply(lambda x: f"{x:.3e}")
        else:
            mean_str = means[m].apply(lambda x: f"{x:.3f}")
            std_str = stds[m].apply(lambda x: f"{x:.3f}")
        df_csv[m] = mean_str + " ± " + std_str
        
    df_csv = df_csv.reindex([h for h in HUE_ORDER if h in df_csv.index])
    
    csv_path = os.path.join(output_dir, "Table_Energy_Jitter_Stats.csv")
    df_csv.to_csv(csv_path)
    print(f"  > Saved as CSV: {csv_path}")

    # 2. LaTeX Output
    df_tex = pd.DataFrame(index=means.index)
    for m in available:
        if m == "Jitter":
            mean_str = means[m].apply(lambda x: f"{x:.3e}")
            std_str = stds[m].apply(lambda x: f"{x:.3e}")
        else:
            mean_str = means[m].apply(lambda x: f"{x:.3f}")
            std_str = stds[m].apply(lambda x: f"{x:.3f}")
        
        df_tex[m] = "$" + mean_str + " \\pm " + std_str + "$"
        
    df_tex = df_tex.reindex([h for h in HUE_ORDER if h in df_tex.index])
    
    tex_path = os.path.join(output_dir, "Table_Energy_Jitter_Stats.tex")
    with open(tex_path, "w") as f:
        f.write(df_tex.to_latex(escape=False, column_format="l" + "c"*len(available)))
    print(f"  > Saved as LaTeX: {tex_path}")

# ==============================================================================
# 3b. SCORE PLOT
# ==============================================================================
def plot_score_comparison(df, output_dir):
    print("\n--- Creating Score Comparison Plot (Mean with Min/Max) ---")
    save_dir = os.path.join(output_dir, "Score_Plots")
    os.makedirs(save_dir, exist_ok=True)
    
    # Calculate statistics
    stats = df.groupby("Agent")["Score"].agg(["mean", "min", "max"]).reset_index()
    stats = stats.sort_values("mean", ascending=False)
    
    plt.figure(figsize=(8, 4))
    ax = plt.gca()
    
    agents = stats["Agent"].tolist()
    means = stats["mean"].values
    mins = stats["min"].values
    maxs = stats["max"].values
    
    # Error bars: distance from mean
    yerr = [means - mins, maxs - means]
    
    colors = [PALETTE.get(a, "gray") for a in agents]
    
    ax.bar(
        agents, means, 
        yerr=yerr, 
        color=colors,
        edgecolor="black", linewidth=0.8, alpha=0.9,
        capsize=5,
        error_kw=dict(lw=1.5, capthick=1.5, ecolor='#333333')
    )
    
    ax.set_ylabel("Composite Score\n(Stability + WCR - NormRMSE)")
    ax.set_xlabel("")
    ax.set_title("Overall Agent Performance Score (Mean & Min-Max Range)", fontsize=12)
    ax.grid(True, axis='y', linestyle=':', zorder=0)
    ax.set_axisbelow(True)
    
    plt.tight_layout()
    plt.savefig(os.path.join(save_dir, "Score_Overall.pdf"))
    plt.close()
    print(f"  > Saved: Score_Overall.pdf")

# ==============================================================================
# 4. BAR PLOTS
# ==============================================================================
def plot_rmse_bars_per_scenario_type(df, output_dir):
    """
    Original logic: One plot per scenario (Static, Drop...), X=Mission.
    """
    print("\n--- Creating Barplots (Per Scenario) ---")
    save_dir = os.path.join(output_dir, "Bar_Plots")
    os.makedirs(save_dir, exist_ok=True)
    
    scenarios = df["Scenario"].unique()
    
    for scen in scenarios:
        subset = df[df["Scenario"] == scen]
        if subset.empty: continue

        plt.figure(figsize=(7.0, 3.2))
        ax = sns.barplot(
            data=subset, x="Mission_Clean", y="Score", hue="Agent",
            hue_order=[h for h in HUE_ORDER if h in subset["Agent"].unique()],
            palette=PALETTE, edgecolor="black", linewidth=0.6, alpha=0.9, errorbar=None 
        )
        
        ax.set_xlabel("")
        ax.set_ylabel("Composite Score")
        ax.set_title(f"Scenario: {SCENARIO_PRETTY_NAMES.get(scen, scen)}", fontsize=10)
        ax.grid(True, axis='y', zorder=0)
        ax.set_axisbelow(True)
        sns.move_legend(ax, "lower center", bbox_to_anchor=(0.5, 1.05), ncol=5, title=None, frameon=False)
        
        scen_file = scen.replace("_", " ")
        plt.savefig(os.path.join(save_dir, f"Bar_Scen_{scen_file}.pdf"))
        plt.close()

def plot_rmse_bars_per_mission_across_anomalies(df, output_dir):
    """
    NEW: One plot per benchmark mission.
    X-Axis = Anomaly Type (Static, Drop, Sudden...).
    Hue = Agent.
    Shows which agent fails at which error.
    """
    print("\n--- Creating Barplots (Per Benchmark / Cross-Anomaly) ---")
    save_dir = os.path.join(output_dir, "Bar_Plots")
    os.makedirs(save_dir, exist_ok=True)
    
    # Remove Baseline for this plot as it is not an anomaly
    df_anom = df[~df["Scenario"].str.contains("Baseline", case=False)].copy()
    if df_anom.empty: return

    missions = df_anom["Mission"].unique()
    
    for miss in missions:
        subset = df_anom[df_anom["Mission"] == miss].copy()
        if subset.empty: continue
        
        # Format Labels: Split "(Multi)" to new line
        subset["Scenario_Label"] = subset["Scenario_Label"].str.replace(" (Multi)", "\n(Multi)", regex=False)
        
        # Filter: Discard crashed agents (Stability < 1) or negative scores
        # We set them to NaN so the bar is not drawn but the space is kept
        mask_invalid = (subset["Stability"] < 0.99) | (subset["Score"] < 0)
        subset.loc[mask_invalid, "Score"] = np.nan
        
        miss_clean = miss.replace("Benchmark_", "")
        
        plt.figure(figsize=(11.5, 5.25))
        ax = sns.barplot(
            data=subset, 
            x="Scenario_Label",
            y="Score", 
            hue="Agent",
            hue_order=[h for h in HUE_ORDER if h in subset["Agent"].unique()],
            palette=PALETTE, 
            edgecolor="black", linewidth=0.6, alpha=0.9, errorbar=None
        )
        
        ax.set_xlabel("")
        ax.set_ylabel("Perform. Score", fontsize=28)
        ax.set_title(f"Anomaly Comparison for Benchmark: {miss_clean}", fontsize=24, y=1.35)
        ax.grid(True, axis='y', zorder=0)
        ax.set_axisbelow(True)
        
        # Trim negative values from view
        ax.set_ylim(bottom=0)
        
        # Rotate labels if necessary (0 usually works well with multiline)
        plt.xticks(rotation=0, fontsize=26)
        plt.yticks(fontsize=26)
        
        sns.move_legend(ax, "lower center", bbox_to_anchor=(0.5, 0.95), ncol=3, title=None, frameon=False, fontsize=26)
        
        plt.tight_layout()
        plt.savefig(os.path.join(save_dir, f"Bar_Mission_{miss_clean}_CrossAnomaly.pdf"))
        plt.close()
        print(f"  > Saved: Bar_Mission_{miss_clean}_CrossAnomaly.pdf")

def plot_aggregated_robustness_minmax(df, output_dir):
    """
    Aggregates over ALL anomalies.
    Error bars = [Min, Max] Range (instead of StdDev).
    Prevents negative bars and honestly shows instability.
    """
    print("\n--- Creating Aggregated Robustness Plot (Min/Max Range) ---")
    save_dir = os.path.join(output_dir, "Bar_Plots")
    os.makedirs(save_dir, exist_ok=True)
    
    df_anom = df[~df["Scenario"].str.contains("Baseline")].copy()
    if df_anom.empty: return

    # Calculate Mean, Min, Max
    stats = df_anom.groupby(["Mission_Clean", "Agent"])["Score"].agg(["mean", "min", "max"]).reset_index()
    
    missions = sorted(stats["Mission_Clean"].unique())
    agents = [h for h in HUE_ORDER if h in stats["Agent"].unique()]
    
    x = np.arange(len(missions))
    width = 0.8 / len(agents)
    
    plt.figure(figsize=(7.0, 3.5))
    ax = plt.gca()
    
    for i, agent in enumerate(agents):
        agent_data = stats[stats["Agent"] == agent]
        agent_data = agent_data.set_index("Mission_Clean").reindex(missions).reset_index()
        
        means = agent_data["mean"].values
        mins = agent_data["min"].values
        maxs = agent_data["max"].values
        
        # Error Bars for Matplotlib are relative to Mean
        # lower = mean - min, upper = max - mean
        yerr_lower = means - mins
        yerr_upper = maxs - means
        
        # Nan Handling
        means = np.nan_to_num(means)
        yerr_lower = np.nan_to_num(yerr_lower)
        yerr_upper = np.nan_to_num(yerr_upper)
        
        yerr = np.array([yerr_lower, yerr_upper])
        
        pos = x + (i * width) - (0.8 / 2) + (width / 2)
        
        ax.bar(
            pos, means, width,
            yerr=yerr,
            label=agent,
            color=PALETTE[agent],
            edgecolor="black", linewidth=0.6, alpha=0.9,
            capsize=3,
            error_kw=dict(lw=1, capthick=1, ecolor='#333333')
        )

    ax.set_xticks(x)
    ax.set_xticklabels(missions)
    ax.set_ylabel("Avg. Score (Min-Max Range)")
    # ax.set_title("Overall Robustness (Avg across all Failures)", fontsize=10)
    ax.grid(True, axis='y', linestyle=':', zorder=0)
    ax.set_axisbelow(True)
    
    ax.legend(loc='lower center', bbox_to_anchor=(0.5, 1.05), ncol=3, frameon=False, fontsize=9)
    plt.tight_layout()
    
    outfile = os.path.join(save_dir, "Bar_Aggregated_Robustness_MinMax.pdf")
    plt.savefig(outfile, format="pdf")
    plt.close()
    print(f"  > Saved: {outfile}")

# ==============================================================================
# 5. TRAJECTORIES
# ==============================================================================
def plot_trajectories_all(df, output_dir):
    print("\n--- Creating Trajectory Overlays (Multiplot & Separate) ---")
    
    # Helper data structure
    db = {}
    
    for idx, row in df.iterrows():
        s = row['Scenario']
        m = row['Mission']
        a = row['Agent']
        p = row['Path']
        
        if s not in db: db[s] = {}
        if m not in db[s]: db[s][m] = {}
        if a not in db[s][m]: db[s][m][a] = []
        # Use Score for sorting/median selection (fallback to 0 if missing)
        db[s][m][a].append((row.get('Score', 0), p))

    # Plotting Loop
    for scen_raw in ALL_SCENARIOS:
        found_scenarios = [k for k in db.keys() if scen_raw in k]
        
        for scen_key in found_scenarios:
            print("Debug: Scenario: ", scen_key)
            for miss_key in EVAL_MISSIONS:
                
                if miss_key not in db[scen_key]: 
                    continue 
                
                # --- PLOT DATA GATHERING ---
                plot_data = {}
                target_captured = False
                
                agents_in_mission = db[scen_key][miss_key].keys()
                
                for agent in agents_in_mission:
                    runs = db[scen_key][miss_key][agent]
                    runs.sort(key=lambda x: x[0]) # Sort by Score
                    median_path = runs[len(runs)//2][1]
                    
                    if not os.path.exists(median_path): continue
                    
                    try:
                        traj_df = pd.read_csv(median_path)
                        
                        # Time
                        if 'sim_time' in traj_df.columns: t = traj_df['sim_time'].values
                        elif 'time' in traj_df.columns: t = traj_df['time'].values
                        else: t = np.arange(len(traj_df)) * 0.008
                        
                        # Pos (Assuming NED -> Z is Down, so Height is -Z)
                        if 'agent_pos' in traj_df.columns:
                            pos = parse_vector_col(traj_df['agent_pos'])
                            x, y, z = pos[:,0], pos[:,1], -pos[:,2]
                        elif 'pos_z' in traj_df.columns:
                            z = -traj_df['pos_z'].values
                            x, y = np.zeros_like(z), np.zeros_like(z)
                        else: continue
                        
                        plot_data[agent] = {'t': t, 'x': x, 'y': y, 'z': z}
                        
                        # Target
                        if not target_captured and 'mission_goal_pos' in traj_df.columns:
                            ref = parse_vector_col(traj_df['mission_goal_pos'])
                            # Auch hier z invertieren für Höhe
                            plot_data["Target"] = {'t': t, 'x': ref[:,0], 'y': ref[:,1], 'z': -ref[:,2]}
                            target_captured = True
                    except: pass

                if not plot_data: continue
                miss_clean = miss_key.replace("Benchmark_", "")
                # print("Debug: Clean: ", miss_clean)
                
                draw_list = sorted(plot_data.keys(), key=lambda k: Z_ORDER.get(k, 5))

                # ==========================================
                # 1. COMBINED MULTIPLOT (Left: XY, Right: Z)
                # ==========================================
                fig, (ax_xy, ax_z) = plt.subplots(1, 2, figsize=(12.5, 4.5))
                
                # Title over all
                fig.suptitle(f"Scenario: {SCENARIO_PRETTY_NAMES.get(scen_key, scen_key)} | Benchmark:  {miss_clean}", fontsize=18, y=0.98)
                
                # Iteration for both subplots
                for name in draw_list:
                    d = plot_data[name]
                    col = PALETTE.get(name, "gray")
                    
                    if name == "Target": ls, lw, alpha = ':', 1.5, 1.0
                    elif name == "INDI": ls, lw, alpha = '--', 1.8, 1.0
                    else: ls, lw, alpha = '-', 1.2, 0.8
                    
                    # --- XY Plot (Left) ---
                    # East (y) on X-Axis, North (x) on Y-Axis for "Map"
                    ax_xy.plot(d['y'], d['x'], label=name, color=col, linestyle=ls, linewidth=lw, alpha=alpha)
                    
                    # --- Z Plot (Right) ---
                    ax_xy_z_line = ax_z.plot(d['t'], d['z'], label=name, color=col, linestyle=ls, linewidth=lw, alpha=alpha)

                # Style XY
                ax_xy.set_xlabel(r"$y$ [m] (East)", fontsize=18)
                ax_xy.set_ylabel(r"$x$ [m] (North)", fontsize=18)
                ax_xy.axis('equal')
                ax_xy.grid(True)
                ax_xy.set_title("Position XY", fontsize=18)

                # Style Z
                ax_z.set_xlabel("Time [s]", fontsize=18)
                ax_z.set_ylabel(r"Height $z$ [m]", fontsize=18) # Inverted NED z
                ax_z.grid(True)
                ax_z.set_title("Altitude Z", fontsize=18)
                
                # Common legend on top
                # We get handles from the second plot as they are the same
                handles, labels = ax_z.get_legend_handles_labels()
                fig.legend(handles, labels, loc='lower center', bbox_to_anchor=(0.5, 0.75), 
                           ncol=len(labels), frameon=False, fontsize=18)
                
                # Tighten layout (leave space for legend)
                plt.tight_layout(rect=[0, 0, 1, 0.90]) 
                
                # Speichern Combined
                out_folder_comb = os.path.join(output_dir, "Trajectories_Combined", scen_key)
                os.makedirs(out_folder_comb, exist_ok=True)
                plt.savefig(os.path.join(out_folder_comb, f"Comb_{miss_clean}.pdf"))
                plt.savefig(os.path.join(out_folder_comb, f"Comb_{miss_clean}.png"), dpi=200)
                plt.close()


                # ==========================================
                # 2. SEPARATE PLOTS (in subfolders)
                # ==========================================
                
                # --- Z PLOT (Single) ---
                plt.figure(figsize=(4.5, 4.5))
                for name in draw_list:
                    d = plot_data[name]
                    col = PALETTE.get(name, "gray")
                    if name == "Target": ls, lw, alpha = ':', 1.5, 1.0
                    elif name == "INDI": ls, lw, alpha = '--', 1.8, 1.0
                    else: ls, lw, alpha = '-', 1.2, 0.8
                    plt.plot(d['t'], d['z'], label=name, color=col, linestyle=ls, linewidth=lw, alpha=alpha)

                plt.xlabel("Time [s]")
                plt.ylabel(r"Height $z$ [m]")
                plt.grid(True)
                plt.title(f"{miss_clean}", fontsize=8)
                
                # Save path changed to separate_plots
                out_folder_z = os.path.join(output_dir, "Trajectories_Z", "separate_plots", scen_key)
                os.makedirs(out_folder_z, exist_ok=True)
                plt.savefig(os.path.join(out_folder_z, f"Z_{miss_clean}.pdf"), bbox_inches='tight')
                plt.savefig(os.path.join(out_folder_z, f"Z_{miss_clean}.png"), dpi=200, bbox_inches='tight')
                plt.close()
                
                # --- XY PLOT (Single) ---
                plt.figure(figsize=(5.5, 6.25))

                ax = plt.gca()
                for name in draw_list:
                    d = plot_data[name]
                    col = PALETTE.get(name, "gray")
                    if name == "Target": ls, lw, alpha = ':', 1.5, 1.0
                    elif name == "INDI": ls, lw, alpha = '--', 1.8, 1.0
                    else: ls, lw, alpha = '-', 1.2, 0.8
                    ax.plot(d['y'], d['x'], label=name, color=col, linestyle=ls, linewidth=lw, alpha=alpha)
                    
                ax.set_xlabel(r"$y$ [m] (East)", fontsize=18)
                ax.set_ylabel(r"$x$ [m] (North)", fontsize=18)

                ax.axis('equal')
                ax.grid(True)

                ax.set_title(f"XY-Plot for Scenario: {SCENARIO_PRETTY_NAMES.get(scen_key, scen_key)} | Benchmark:  {miss_clean}", fontsize=18, y=1.15)
                
                ax.legend()
                sns.move_legend(ax, "lower center", bbox_to_anchor=(0.5, 0.965), ncol=3, title=None, frameon=False, fontsize=18)

                # Save path changed to separate_plots
                out_folder_xy = os.path.join(output_dir, "Trajectories_XY", "separate_plots", scen_key)
                os.makedirs(out_folder_xy, exist_ok=True)
                plt.savefig(os.path.join(out_folder_xy, f"XY_{miss_clean}.pdf"), bbox_inches='tight')
                plt.savefig(os.path.join(out_folder_xy, f"XY_{miss_clean}.png"), dpi=200, bbox_inches='tight')
                plt.close()

                
                set_paper_style()
                fig_width = 3.5  # inches (ca 8.9 cm)
                fig_height = 3.75 # inches (etwas Platz für Legende oben/unten)
                fig = plt.figure(figsize=(fig_width, fig_height))#, layout="constrained")

                ax = plt.gca()
                for name in draw_list:
                    d = plot_data[name]
                    col = PALETTE.get(name, "gray")
                    if name == "Target": ls, lw, alpha = ':', 1.5, 1.0
                    elif name == "INDI": ls, lw, alpha = '--', 1.8, 1.0
                    else: ls, lw, alpha = '-', 1.2, 0.8
                    ax.plot(d['y'], d['x'], label=name, color=col, linestyle=ls, linewidth=lw, alpha=alpha)
                    
                ax.set_xlabel(r"$y$ [m] (East)")
                ax.set_ylabel(r"$x$ [m] (North)")
                ax.set_title(f"XY-Plot for Scenario: {SCENARIO_PRETTY_NAMES.get(scen_key, scen_key)} | Benchmark:  {miss_clean}", y=1.25)

                ax.legend(loc='lower center', bbox_to_anchor=(0.5, 1.02), ncol=2, frameon=False, borderaxespad=0)

                #ax.axis('equal')
                ax.set_aspect('equal', adjustable='box')
                #ax.set_aspect('equal', adjustable='datalim')

                ax.grid(True)

                print("Speichere Test-Plot...")
                plt.savefig(os.path.join(out_folder_xy, f"TEST_XY_{miss_clean}.pdf"), format="pdf", bbox_inches='tight', pad_inches=0.02)
                print("Fertig. Bitte 'test_plots' prüfen.")
                plt.close()

                fig_width = 3.5
                fig_height = 3.65 
                fig = plt.figure(figsize=(fig_width, fig_height)) # KEIN layout=constrained!

                # 2. Platzreservierung ("Header" Bereich definieren)
                # top=0.75 bedeutet: Der Plot darf erst bei 75% der Höhe beginnen. 
                # Die oberen 25% gehören EXKLUSIV Titel und Legende.
                fig.subplots_adjust(top=0.78, bottom=0.12, left=0.15, right=0.9)

                ax = fig.add_subplot(1, 1, 1)

                # ... Plotting Loop wie gehabt ...
                for name in draw_list:
                    d = plot_data[name]
                    col = PALETTE.get(name, "gray")
                    if name == "Target": ls, lw, alpha = ':', 1.25, 1.0
                    elif name == "INDI": ls, lw, alpha = '--', 1.0, 0.8
                    else: ls, lw, alpha = '-', 1.0, 0.8
                    ax.plot(d['y'], d['x'], label=name, color=col, linestyle=ls, linewidth=lw, alpha=alpha)

                ax.set_xlabel(r"$y$ [m] (East)")
                ax.set_ylabel(r"$x$ [m] (North)")

                # --- DIE MAGIE: TITEL & LEGENDE FIXIEREN ---

                # Statt ax.set_title nutzen wir fig.suptitle.
                # Das verankert den Titel am FIGURE-Rand, nicht an der wackeligen Achse.
                fig.suptitle(f"XY-Plot: {SCENARIO_PRETTY_NAMES.get(scen_key, scen_key)} | Benchmark: {miss_clean}", 
                            y=0.99, va='top') # y=0.96 ist fast ganz oben im reservierten Bereich

                # Legende ebenfalls an der Figure verankern
                # Wir holen uns die Handles vom Plot, aber platzieren die Legende auf der Figure
                handles, labels = ax.get_legend_handles_labels()
                fig.legend(handles, labels, loc='upper center', bbox_to_anchor=(0.5, 0.96), 
                        ncol=2, frameon=False) 
                        # bbox_to_anchor=(0.5, 0.86) platziert sie sicher unter dem Titel, 
                        # aber immer noch im "Sicherheitsbereich" (oberhalb von top=0.72)

                # Achsen-Settings
                ax.yaxis.set_major_formatter(FormatStrFormatter('%.1f'))
                ax.set_aspect('equal', adjustable='datalim')
                ax.set_anchor('N') 
                ax.grid(True)

                plt.show()

                # Export
                print(f"Speichere Plot mit festem Header: {miss_clean}")
                plt.savefig(os.path.join(out_folder_xy, f"TEST_XY_{miss_clean}_HEADER.pdf"), format="pdf", bbox_inches='tight', pad_inches=0.02)
                plt.close()

    print("  > Trajectories finished (Combined & Separate).")
    
# ==============================================================================
# MAIN
# ==============================================================================
if __name__ == "__main__":
    try:
        project_root = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
    except NameError:
        project_root = "."
        
    input_csv = os.path.join(project_root, "data", "Paper_Eval_Raw_test", "summary_metrics_full.csv")
    output_dir = os.path.join(project_root, "data", "Paper_Eval_Plots_test")
    os.makedirs(output_dir, exist_ok=True)
    
    set_paper_style()
    
    if os.path.exists(input_csv):
        df = load_and_filter_data(input_csv)
        
        # 1. Tables
        generate_latex_table(df, output_dir)
        generate_baseline_stats_table(df, output_dir)
        plot_score_comparison(df, output_dir)
        
        # 2. Barplots (Different Views)
        plot_rmse_bars_per_scenario_type(df, output_dir)
        plot_rmse_bars_per_mission_across_anomalies(df, output_dir)
        #plot_aggregated_robustness_minmax(df, output_dir)
        
        # 3. Trajectories
        plot_trajectories_all(df, output_dir)
        
        print("\nDone. Results in:", output_dir)
    else:
        print(f"CSV nicht gefunden: {input_csv}")