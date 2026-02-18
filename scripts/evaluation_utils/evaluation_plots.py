import pandas as pd
import numpy as np
import sys
import matplotlib

import matplotlib.pyplot as plt
from matplotlib.ticker import FormatStrFormatter
import matplotlib.lines as mlines
import matplotlib.patches as mpatches
from matplotlib.legend_handler import HandlerPatch

def make_legend_arrow(legend, orig_handle,
                      xdescent, ydescent,
                      width, height,
                      fontsize):
    
    arrow_length = width * 1.35        # 50% länger
    head_size_factor = 0.35           # Kopf kleiner
    
    return mpatches.FancyArrowPatch(
        (xdescent-2.85, height/2),
        (xdescent-2 + arrow_length, height/2),
        arrowstyle=f'simple,head_length={head_size_factor*10},head_width={head_size_factor*5}',
        linewidth=orig_handle.get_linewidth(),
        color=orig_handle.get_edgecolor()
    )

import seaborn as sns
import os
import ast
from metrics import calculate_composite_score

# ==============================================================================
# 1. CONFIGURATION
# ==============================================================================

FIG_WIDTH = 3.5
FIG_HEIGHT = 3.65

# Saved in data/trajectories
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
        "legend.fontsize": 9,
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

LINE_STYLES = {
    "Target": {"linestyle": "-", "linewidth": 1.5, "alpha": 1.0},
    "INDI":   {"linestyle": "--", "linewidth": 1.0, "alpha": 0.8},
}
DEFAULT_STYLE = {"linestyle": "-", "linewidth": 1.0, "alpha": 0.8}

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

    
    # Calculate Score if not present (or recalculate to be safe)
    df = calculate_composite_score(df)
    
    return df

# ==============================================================================
# 3. LATEX TABLE (With Instability Check)
# ==============================================================================
def generate_latex_table(df, output_dir):
    print("   Generate LaTeX Table")
    metrics = ["Stability", "WCR", "RMSE_TE_VEL", "RMSE_TE_XYZ", "RMSE_TE_RPY", "Score" ] #, "Energy"]
    available = [m for m in metrics if m in df.columns]
    
    grouped = df.groupby("Agent")[available]

    means = grouped.mean()
    stds = grouped.std()

    df_tex = pd.DataFrame(index=means.index)
    for m in available:
        if m in ["RMSE_TE_VEL", "RMSE_TE_XYZ", "RMSE_TE_RPY", "Score"]:
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
    # print(f"  > Saved as Latex table: {tex_path}")

# ==============================================================================
# 4. BAR PLOTS
# ==============================================================================
def plot_rmse_bars_per_scenario_type(df, output_dir):
    """
    Original logic: One plot per scenario (Static, Drop...), X=Mission.
    """
    print("   Plot RMSE Bars (Per Scenario)")
    save_dir = os.path.join(output_dir, "Bar_Plots")
    os.makedirs(save_dir, exist_ok=True)
    
    scenarios = df["Scenario"].unique()
    
    for scen in scenarios:
        subset = df[df["Scenario"] == scen]
        if subset.empty: continue

        plt.figure(figsize=(FIG_WIDTH, 0.5*FIG_HEIGHT))
        ax = sns.barplot(
            data=subset, x="Mission_Clean", y="Score", hue="Agent",
            hue_order=[h for h in HUE_ORDER if h in subset["Agent"].unique()],
            palette=PALETTE, edgecolor="black", linewidth=0.6, alpha=0.9, errorbar=None 
        )
        
        ax.set_xlabel("")
        ax.set_ylabel("Composite Score")
        ax.set_title(f"Anomaly Comparison for Scenario: {SCENARIO_PRETTY_NAMES.get(scen, scen)}", y=1.35)
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
    print("   Plot RMSE Bars (Cross-Anomaly)")
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
        
        plt.figure(figsize=(1.45*FIG_WIDTH, 0.75*FIG_HEIGHT))
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
        ax.set_ylabel("Perform. Score")
        ax.set_title(f"Anomaly Comparison for Benchmark: {miss_clean}", y=1.45)
        
        ax.grid(True, axis='y', zorder=0)
        ax.set_axisbelow(True)
        
        # Trim negative values from view
        ax.set_ylim(bottom=0)
        
        # Rotate labels if necessary (0 usually works well with multiline)
        plt.xticks(rotation=0)
        plt.yticks()
        
        sns.move_legend(ax, "lower center", bbox_to_anchor=(0.5, 0.975), ncol=3, title=None, frameon=False)
        
        plt.tight_layout()
        plt.savefig(os.path.join(save_dir, f"Bar_Mission_{miss_clean}_CrossAnomaly.pdf"))
        plt.close()

def plot_aggregated_robustness_minmax(df, output_dir):
    """
    Aggregates over ALL anomalies.
    Error bars = [Min, Max] Range (instead of StdDev).
    Prevents negative bars and honestly shows instability.
    """
    print("   Plot Aggregated Robustness")
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
    # print(f"  > Saved: {outfile}")

# ==============================================================================
# 5. TRAJECTORIES
# ==============================================================================

def create_singular_trajectory_plot(ax, draw_list, plot_data, plot_type='xy'):
    legend_handles = []
    legend_labels = []

    for name in draw_list:
        d = plot_data[name]
        col = PALETTE.get(name, "gray")

        if plot_type=='xy':
            x_data = d['y']
            y_data = d['x']
            start_x = plot_data['RL Add. (Blind)']['y'][0] # use any dataset to get spawn location
            start_y = plot_data['RL Add. (Blind)']['x'][0]

        elif plot_type == 'tz':
            x_data = d['t']
            y_data = d['z']
            start_x = plot_data['RL Add. (Blind)']['t'][0] # use any dataset to get spawn location
            start_y = plot_data['RL Add. (Blind)']['z'][0]

        if name == "Target" and plot_type== "xy":
            full_x_traj = np.insert(x_data, 0, start_x)
            full_y_traj = np.insert(y_data, 0, start_y)

            # Calculate vectors and plot the quiver arrows
            X = full_x_traj[:-1]
            Y = full_y_traj[:-1]
            U = np.diff(full_x_traj)
            V = np.diff(full_y_traj)
            
            ax.quiver(X,Y,U,V, #Y[::skip], X[::skip], V[::skip], U[::skip],
                    color=col,
                    angles='xy',
                    scale_units='xy',
                    scale=1.1,
                    width=0.005, # You may need to tune this width
                    #label=name,
                    alpha=0.95)

            arrow_handle = mpatches.FancyArrowPatch(
                (0, 0), (1.0, 0),          # Start → Ende
                arrowstyle='fancy',          # schöner Pfeil
                mutation_scale=4,         # Größe Kopf
                linewidth=0.75,             # Linienstärke
                color=col
            )
            
            legend_handles.append(arrow_handle)
            legend_labels.append(name)


            for _, (wp_x, wp_y, wp_id) in enumerate(zip(x_data, y_data, d['widx'])):
                # The text to display is the waypoint number (1, 2, 3...)
                label_text = wp_id 
                ax.text(wp_x, wp_y, label_text, 
                        fontsize=7, 
                        fontweight='bold',
                        color='black',
                        ha='center', # Horizontal alignment
                        va='center', # Vertical alignment
                        # Add a circular background for readability
                        bbox=dict(boxstyle='circle,pad=0.2', fc='white', ec='black', alpha=0.9))

        else: # not target us enormal lineplots instead or markers and quivers

            style = LINE_STYLES.get(name, DEFAULT_STYLE)
            ax.plot(x_data, y_data, label=name, color=col, **style)
            line_handle = mlines.Line2D([], [], color=col, **style)
            legend_handles.append(line_handle)
            legend_labels.append(name)

    return legend_handles, legend_labels    


def plot_trajectories_all(df, output_dir):
    print("   Plot Trajectories")
    
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
            print(f"      - Scenario: {scen_key}")
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
                            widx = traj_df['mission_waypoint_index'].values
                            #print('widx ', widx)
                            # Auch hier z invertieren für Höhe
                            plot_data["Target"] = {'t': t, 'x': ref[:,0], 'y': ref[:,1], 'z': -ref[:,2], 'widx': widx}
                            target_captured = True
                    except: pass

                if not plot_data: continue
                miss_clean = miss_key.replace("Benchmark_", "")
                
                draw_list = sorted(plot_data.keys(), key=lambda k: Z_ORDER.get(k, 5))

                # ==========================================
                # 1. COMBINED MULTIPLOT (Left: XY, Right: Z)
                # ==========================================
                fig_width = 7.0
                fig_height = 3.5
                fig = plt.figure(figsize=(FIG_WIDTH*2, FIG_HEIGHT))
                # Reserve space at top for title/legend
                fig.subplots_adjust(top=0.81, bottom=0.15, left=0.08, right=0.98, wspace=0.25)

                line_y_position = 0.942
                line = mlines.Line2D([0.08, 0.98], [line_y_position, line_y_position], transform=fig.transFigure, color='gray', linewidth=0.75)
                fig.add_artist(line)

                # --- Left: XY Plot ---
                ax = fig.add_subplot(1, 2, 1)

                legend_handles, legend_labels = create_singular_trajectory_plot(ax, draw_list, plot_data)
                
                ax.set_xlabel(r"$y$ [m] (East)")
                ax.set_ylabel(r"$x$ [m] (North)")
                ax.set_title("Position XY")
                ax.yaxis.set_major_formatter(FormatStrFormatter('%.1f'))
                ax.set_aspect('equal', adjustable='datalim')
                ax.set_anchor('N') 
                ax.grid(True)

                if False:
                    ax_xy = fig.add_subplot(1, 2, 1)
                    for name in draw_list:
                        d = plot_data[name]
                        col = PALETTE.get(name, "gray")
                        style = LINE_STYLES.get(name, DEFAULT_STYLE)
                        
                        # --- XY Plot (Left) ---
                        # East (y) on X-Axis, North (x) on Y-Axis for "Map"
                        ax_xy.plot(d['y'], d['x'], label=name, color=col, **style)
                    
                    ax_xy.set_xlabel(r"$y$ [m] (East)")
                    ax_xy.set_ylabel(r"$x$ [m] (North)")
                    ax_xy.set_title("Position XY", fontsize=10)
                    ax_xy.yaxis.set_major_formatter(FormatStrFormatter('%.1f'))
                    ax_xy.set_aspect('equal', adjustable='datalim')
                    ax_xy.grid(True)


                # --- Right: Z Plot ---
                ax_z = fig.add_subplot(1, 2, 2)

                _, _ = create_singular_trajectory_plot(ax_z, draw_list, plot_data, plot_type='tz')

                ax_z.yaxis.set_major_formatter(FormatStrFormatter('%.1f'))
                #ax.set_aspect('equal', adjustable='datalim')
                ax_z.set_anchor('N') 
                ax_z.grid(True)
                    
                ax_z.set_xlabel(r"Time $t$ [s]")
                ax_z.set_ylabel(r"Height $z$ [m]")
                ax_z.set_title("Altitude Z")

                if False:
                    for name in draw_list:
                        d = plot_data[name]
                        col = PALETTE.get(name, "gray")
                        style = LINE_STYLES.get(name, DEFAULT_STYLE)
                        ax_z.plot(d['t'], d['z'], label=name, color=col, **style)

                    ax_z.set_xlabel("Time [s]")
                    ax_z.set_ylabel(r"Height $z$ [m]")
                    ax_z.set_title("Altitude Z", fontsize=10)
                    ax_z.grid(True)
                
                # --- Header & Legend ---

                fig.suptitle(f"Scenario: {SCENARIO_PRETTY_NAMES.get(scen_key, scen_key)} | Benchmark: {miss_clean}", 
                            fontsize=10, x=0.5,y=0.99, ha='center', va='top') # y=0.96 ist fast ganz oben im reservierten Bereich

                fig.legend(
                    legend_handles,
                    legend_labels,
                    loc='upper center',
                    bbox_to_anchor=(0.5, 0.96),
                    ncol=3,
                    frameon=False,
                    fontsize=8,
                        handler_map={mpatches.FancyArrowPatch: HandlerPatch(patch_func=make_legend_arrow)},
                    labelspacing = 0.2,
                )

                if False:

                    fig.suptitle(f"Scenario: {SCENARIO_PRETTY_NAMES.get(scen_key, scen_key)} | Benchmark: {miss_clean}", 
                                fontsize=10, y=0.99, va='top')

                    handles, labels = ax_z.get_legend_handles_labels()
                    fig.legend(handles, labels, loc='upper center', bbox_to_anchor=(0.5, 0.95), 
                            ncol=2, frameon=False, fontsize=8)
                    
                    line_y_position = 0.96
                    line = mlines.Line2D([0.0, 0.9], [line_y_position, line_y_position], transform=fig.transFigure, color='gray', linewidth=0.75)
                    fig.add_artist(line)
                    
                out_folder_comb = os.path.join(output_dir, "Trajectories_Combined", scen_key)
                os.makedirs(out_folder_comb, exist_ok=True)
                plt.savefig(os.path.join(out_folder_comb, f"Comb_{miss_clean}.pdf"), format="pdf", bbox_inches='tight', pad_inches=0.02)
                plt.savefig(os.path.join(out_folder_comb, f"Comb_{miss_clean}.png"), dpi=300)
                plt.close()


                # ==========================================
                # 2. SEPARATE PLOTS (in subfolders)
                # ==========================================
                
                # --- Z PLOT (Single) ---
                fig_width = 3.5
                fig_height = 3.5
                fig = plt.figure(figsize=(fig_width, fig_height))
                fig.subplots_adjust(top=0.8, bottom=0.15, left=0.18, right=0.96)
                ax = fig.add_subplot(1, 1, 1)

                legend_handles, legend_labels = create_singular_trajectory_plot(ax, draw_list, plot_data, plot_type='tz')

                ax.yaxis.set_major_formatter(FormatStrFormatter('%.1f'))
                #ax.set_aspect('equal', adjustable='datalim')
                ax.set_anchor('N') 
                ax.grid(True)
                    
                ax.set_xlabel(r"Time $t$ [s]")
                ax.set_ylabel(r"Height $z$ [m]")
                fig.suptitle(f"Z-Plot: {SCENARIO_PRETTY_NAMES.get(scen_key, scen_key)} | Benchmark: {miss_clean}", 
                            fontsize=10, x=0.1,y=0.99, ha='left', va='top') # y=0.96 ist fast ganz oben im reservierten Bereich

                fig.legend(
                    legend_handles,
                    legend_labels,
                    loc='upper center',
                    bbox_to_anchor=(0.5, 0.96),
                    ncol=2,
                    frameon=False,
                    fontsize=8,
                        handler_map={mpatches.FancyArrowPatch: HandlerPatch(patch_func=make_legend_arrow)},
                    labelspacing = 0.2,
                )
                
                line_y_position = 0.942
                line = mlines.Line2D([0.0, 0.9], [line_y_position, line_y_position], transform=fig.transFigure, color='gray', linewidth=0.75)
                fig.add_artist(line)                

                if False:
                    for name in draw_list:
                        d = plot_data[name]
                        col = PALETTE.get(name, "gray")
                        style = LINE_STYLES.get(name, DEFAULT_STYLE)
                        ax.plot(d['t'], d['z'], label=name, color=col, **style)

                    ax.set_xlabel("Time [s]")
                    ax.set_ylabel(r"Height $z$ [m]")
                    ax.grid(True)
                    
                    fig.suptitle(f"Z-Plot: {miss_clean}", fontsize=10, y=0.99, va='top')
                    handles, labels = ax.get_legend_handles_labels()
                    fig.legend(handles, labels, loc='upper center', bbox_to_anchor=(0.5, 0.92), ncol=2, frameon=False, fontsize=8)
                
                # Save path changed to separate_plots
                out_folder_z = os.path.join(output_dir, "Trajectories_Z", scen_key)
                os.makedirs(out_folder_z, exist_ok=True)
                plt.savefig(os.path.join(out_folder_z, f"Z_{miss_clean}.pdf"), format="pdf", bbox_inches='tight', pad_inches=0.02)
                plt.savefig(os.path.join(out_folder_z, f"Z_{miss_clean}.png"), dpi=300)
                plt.close()
                
                # --- XY PLOT (Single) ---

                fig = plt.figure(figsize=(FIG_WIDTH, FIG_HEIGHT))
                fig.subplots_adjust(top=0.81, bottom=0.12, left=0.12, right=0.875)
                ax = fig.add_subplot(1, 1, 1)

                legend_handles, legend_labels = create_singular_trajectory_plot(ax, draw_list, plot_data)

                ax.set_xlabel(r"$y$ [m] (East)")
                ax.set_ylabel(r"$x$ [m] (North)")
                ax.yaxis.set_major_formatter(FormatStrFormatter('%.1f'))
                ax.set_aspect('equal', adjustable='datalim')
                ax.set_anchor('N') 
                ax.grid(True)
                    

                fig.suptitle(f"XY-Plot: {SCENARIO_PRETTY_NAMES.get(scen_key, scen_key)} | Benchmark: {miss_clean}", 
                            fontsize=10, x=0.1,y=0.99, ha='left', va='top') # y=0.96 ist fast ganz oben im reservierten Bereich

                fig.legend(
                    legend_handles,
                    legend_labels,
                    loc='upper center',
                    bbox_to_anchor=(0.5, 0.96),
                    ncol=2,
                    frameon=False,
                    fontsize=8,
                        handler_map={mpatches.FancyArrowPatch: HandlerPatch(patch_func=make_legend_arrow)},
                    labelspacing = 0.2,
                )
                
                line_y_position = 0.942
                line = mlines.Line2D([0.0, 0.9], [line_y_position, line_y_position], transform=fig.transFigure, color='gray', linewidth=0.75)
                fig.add_artist(line)

                # Save path changed to separate_plots
                out_folder_xy = os.path.join(output_dir, "Trajectories_XY", scen_key)
                os.makedirs(out_folder_xy, exist_ok=True)
                plt.savefig(os.path.join(out_folder_xy, f"XY_{miss_clean}.pdf"), format="pdf") #, bbox_inches='tight', pad_inches=0.02)
                plt.savefig(os.path.join(out_folder_xy, f"XY_{miss_clean}.png"), dpi=300)
                plt.close()


                #
                fig = plt.figure(figsize=(FIG_WIDTH, FIG_HEIGHT))
                fig.subplots_adjust(top=0.81, bottom=0.12, left=0.12, right=0.875)
                ax = fig.add_subplot(1, 1, 1)

                legend_handles, legend_labels = create_singular_trajectory_plot(ax, draw_list, plot_data)
                    
                ax.set_xlabel(r"$y$ [m] (East)")
                ax.set_ylabel(r"$x$ [m] (North)")
                fig.suptitle(f"XY-Plot: {SCENARIO_PRETTY_NAMES.get(scen_key, scen_key)} | Benchmark: {miss_clean}", 
                            fontsize=10, x=0.1,y=0.99, ha='left', va='top') # y=0.96 ist fast ganz oben im reservierten Bereich

                fig.legend(
                    legend_handles,
                    legend_labels,
                    loc='upper center',
                    bbox_to_anchor=(0.475, 0.96),
                    ncol=2,
                    frameon=False,
                    fontsize=8,
                        handler_map={mpatches.FancyArrowPatch: HandlerPatch(patch_func=make_legend_arrow)},
                    labelspacing = 0.2,
                )
                
                line_y_position = 0.942
                line = mlines.Line2D([0.0, 0.9], [line_y_position, line_y_position], transform=fig.transFigure, color='gray', linewidth=0.75)
                fig.add_artist(line)

                # Achsen-Settings
                ax.yaxis.set_major_formatter(FormatStrFormatter('%.1f'))
                ax.set_aspect('equal', adjustable='datalim')
                ax.set_anchor('N') 
                ax.grid(True)

                # Save path changed to separate_plots
                out_folder_xy = os.path.join(output_dir, "Trajectories_XY", scen_key)
                os.makedirs(out_folder_xy, exist_ok=True)
                plt.savefig(os.path.join(out_folder_xy, f"XY_{miss_clean}.pdf"), format="pdf") #, bbox_inches='tight', pad_inches=0.02)
                plt.savefig(os.path.join(out_folder_xy, f"XY_{miss_clean}.png"), dpi=300)
                plt.close()


def plot_velocities(df, output_dir):
    print("   Plot Velocities!")
    
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
            for miss_key in EVAL_MISSIONS:

                if miss_key not in db[scen_key]: 
                    continue 
                else: pass 
                
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
                        if 'agent_vel_c' in traj_df.columns:
                            pos = parse_vector_col(traj_df['agent_vel_c'])
                            x, y, z = pos[:,0], pos[:,1], -pos[:,2]
                        else: continue

                        if 'error_vel_c' in traj_df.columns:
                            error = parse_vector_col(traj_df['error_vel_c'])
                            ex, ey, ez = error[:,0], error[:,1], -error[:,2]
                        else: continue
                        
                        plot_data[agent] = {'t': t, 'x': x, 'y': y, 'z': z, 'ex': ex, 'ey': ey, 'ez': ez}
                        
                        # Target
                        if not target_captured and 'mission_goal_vel' in traj_df.columns:
                            ref = parse_vector_col(traj_df['mission_goal_vel'])
                            widx = traj_df['mission_waypoint_index'].values
                            #print('widx ', widx)
                            plot_data["Target"] = {'t': t, 'x': ref[:,0], 'y': ref[:,1], 'z': -ref[:,2], 'widx': widx}
                            target_captured = True
                    except: print("ERROR try failed to assign current agent_data")

                if not plot_data: continue
                miss_clean = miss_key.replace("Benchmark_", "")
                
                draw_list = sorted(plot_data.keys(), key=lambda k: Z_ORDER.get(k, 5))


                # ==========================================
                # 1. All Axes
                # ==========================================
                fig_width = FIG_WIDTH
                fig_height = 1.9*FIG_HEIGHT
                fig = plt.figure(figsize=(fig_width, fig_height))
                # Reserve space at top for title/legend
                fig.subplots_adjust(top=0.895, bottom=0.15, left=0.08, right=0.875, wspace=0.25, hspace=0.05)

                axes = []
                for i in range(3):
                    if i == 0:
                        ax = fig.add_subplot(3, 1, i+1)
                    else:
                        ax = fig.add_subplot(3, 1, i+1, sharex=axes[0])
                    axes.append(ax)
                
                components = ['x', 'y', 'z']
                for ax, comp in zip(axes, components):
                    for name in draw_list:
                        d = plot_data[name]
                        col = PALETTE.get(name, "gray")
                        style = LINE_STYLES.get(name, DEFAULT_STYLE)
                        ax.plot(d['t'], d[comp], label=name, color=col, **style)

                    ax.set_ylabel("Velocity $V_" + comp +"$ [m/s]")
                    ax.grid(True)

                # nur unten Zeitlabel
                axes[-1].set_xlabel("Time [s]")

                # obere x-Ticklabels aus
                for ax in axes[:-1]:
                    ax.tick_params(labelbottom=False)

                line_y_position = 0.9735
                line = mlines.Line2D([0.0, 0.9], [line_y_position, line_y_position], transform=fig.transFigure, color='gray', linewidth=0.75)
                fig.add_artist(line)
                
                # --- Header & Legend ---
                fig.suptitle(f"Scenario: {SCENARIO_PRETTY_NAMES.get(scen_key, scen_key)} | Benchmark: {miss_clean}", 
                            fontsize=10, y=0.9935, va='top')

                handles, labels = axes[0].get_legend_handles_labels()
                fig.legend(handles, labels, loc='upper center', bbox_to_anchor=(0.475, 0.985), 
                           ncol=2, frameon=False)
                
                out_folder_comb = os.path.join(output_dir, "Velocities", scen_key)
                os.makedirs(out_folder_comb, exist_ok=True)
                plt.savefig(os.path.join(out_folder_comb, f"Velocities_{miss_clean}.pdf"), format="pdf", bbox_inches='tight', pad_inches=0.02)
                plt.close()

                # ==========================================
                # 1. Errors
                # ==========================================
                fig_width = FIG_WIDTH
                fig_height = 1.9*FIG_HEIGHT
                fig = plt.figure(figsize=(fig_width, fig_height))
                # Reserve space at top for title/legend
                fig.subplots_adjust(top=0.895, bottom=0.15, left=0.08, right=0.875, wspace=0.25, hspace=0.05)

                axes = []
                for i in range(3):
                    if i == 0:
                        ax = fig.add_subplot(3, 1, i+1)
                    else:
                        ax = fig.add_subplot(3, 1, i+1, sharex=axes[0])
                    axes.append(ax)
                
                components = ['ex', 'ey', 'ez']
                labels = ['x', 'y', 'z']
                for ax, comp, lab in zip(axes, components, labels):
                    for name in draw_list:
                        if name == "Target": continue
                        d = plot_data[name]
                        col = PALETTE.get(name, "gray")
                        style = LINE_STYLES.get(name, DEFAULT_STYLE)
                        ax.plot(d['t'], d[comp], label=name, color=col, **style)

                    ax.set_ylabel("Velocity Error $e_{V" + lab +"}$ [m/s]")
                    ax.grid(True)

                # nur unten Zeitlabel
                axes[-1].set_xlabel("Time [s]")

                # obere x-Ticklabels aus
                for ax in axes[:-1]:
                    ax.tick_params(labelbottom=False)

                line_y_position = 0.9735
                line = mlines.Line2D([0.0, 0.9], [line_y_position, line_y_position], transform=fig.transFigure, color='gray', linewidth=0.75)
                fig.add_artist(line)
                
                # --- Header & Legend ---
                fig.suptitle(f"Scenario: {SCENARIO_PRETTY_NAMES.get(scen_key, scen_key)} | Benchmark: {miss_clean}", 
                            fontsize=10, y=0.9935, va='top')

                handles, labels = axes[0].get_legend_handles_labels()
                fig.legend(handles, labels, loc='upper center', bbox_to_anchor=(0.475, 0.985), 
                           ncol=2, frameon=False)
                
                out_folder_comb = os.path.join(output_dir, "Velocities", scen_key)
                os.makedirs(out_folder_comb, exist_ok=True)
                plt.savefig(os.path.join(out_folder_comb, f"ErrorVel_{miss_clean}.pdf"), format="pdf", bbox_inches='tight', pad_inches=0.02)
                plt.close()


# ==============================================================================
# MAIN
# ==============================================================================
def main():
    try:
        project_root = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
    except NameError:
        project_root = "."

    print(f"Matplotlib Version: {matplotlib.__version__}")
    print(f"Using Matplotlib from: {matplotlib.__file__}")
    print("-" * 20)
    print(f"Python Executable: {sys.executable}")


    input_csv = os.path.join(project_root, "data", "Evaluation", "Raw_Files", "summary_metrics_full.csv")
    output_dir = os.path.join(project_root, "data", "Evaluation", "Plots")
    os.makedirs(output_dir, exist_ok=True)
    
    set_paper_style()
    
    if os.path.exists(input_csv):
        print("Plotting Script: Run")
        print("   Initialize")
        print("   Load Data")
        df = load_and_filter_data(input_csv)
        
        # 1. Table
        generate_latex_table(df, output_dir)
        
        # 2. Barplots (Different Views)
        plot_rmse_bars_per_scenario_type(df, output_dir)
        plot_rmse_bars_per_mission_across_anomalies(df, output_dir)
        
        # 3. Trajectories
        plot_velocities(df, output_dir)
        plot_trajectories_all(df, output_dir)
        
        print("\nDone. Results in:", output_dir)
    else:
        print(f"CSV nicht gefunden: {input_csv}")


if __name__ == "__main__":
    main()

# ==================================================