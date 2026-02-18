import pandas as pd
import numpy as np
import os
import platform
import ast
import gymnasium as gym
from stable_baselines3 import PPO
from stable_baselines3.common.vec_env import DummyVecEnv
from rmt_coptergym.application_envs.RL_VEL_I_Env_relative_WAR import VEL_Env
from rmt_coptergym.utils.trajectory_dataloader import TrajectoryDataLoader
from rmt_coptergym.utils.utils import plot_trajectory_results
from metrics import parse_vector_col, calculate_metrics_physics, calculate_composite_score


# ==============================================================================
# RL SIMULATION
# ==============================================================================
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

def run_rl_simulation(agents_config, eval_missions, anomaly_groups, global_env_kwargs, output_dir, m_min, m_range, max_duration=10.0):
    print(f"   run RL simulation")
    results = []
    
    for agent_name, agent_cfg in agents_config.items():
        print(f"      - Agent: {agent_name}")
        
        # Pfad prüfen
        if not os.path.exists(agent_cfg['path']):
            print(f"[WARNING] model not found: {agent_cfg['path']}")
            continue

        model = PPO.load(agent_cfg['path'], device='cpu')
        
        # 1. Environment EINMAL erstellen (Initialisierung)
        base_kwargs = global_env_kwargs.copy()
        if 'env_kwargs' in agent_cfg: base_kwargs.update(agent_cfg['env_kwargs'])
        
        # Dummy Start-Werte
        base_kwargs['mission_pool'] = [eval_missions[0]]
        base_kwargs['anomaly_pool'] = []
        base_kwargs['is_eval'] = True
        
        vec_env = DummyVecEnv([lambda: PaperMetricsWrapper(VEL_Env(**base_kwargs))])
        
        # Zugriff auf die "echte" Env Instanz für unsere Update-Funktion
        # vec_env -> PaperMetricsWrapper -> VEL_Env
        internal_env = vec_env.envs[0].unwrapped 
        
        # 2. Loop über Szenarien
        scenarios = [("baseline", [])] + list(anomaly_groups.items())
        
        for scen_name, anomaly_list in scenarios:
            safe_scen_name = "".join([c for c in scen_name if c.isalnum() or c in (' ', '_', '-')]).strip()
            # print(f"  >> Szenario: {scen_name}")
            
            run_items = anomaly_list if len(anomaly_list) > 0 else [None]
            
            for mission_df in eval_missions:
                mission_name = mission_df['mission_name'][0]
                total_waypoints = len(mission_df) # Number of rows in trajectory definition
                save_path = os.path.join(output_dir, agent_name, safe_scen_name, mission_name)
                os.makedirs(save_path, exist_ok=True)
                
                for run_idx, anomaly_df in enumerate(run_items):
                    csv_filename = f"run_{run_idx}.csv"
                    full_csv_path = os.path.join(save_path, csv_filename)
                    
                    if not os.path.exists(full_csv_path):
                        
                        # Update Env settinsg so we do not need to reinitialize the env and lib-files
                        internal_env.update_eval_config([mission_df] if mission_df is not None else None, [anomaly_df] if anomaly_df is not None else None)
                        
                        # Seed setzen für Reproduzierbarkeit
                        vec_env.seed(42 + run_idx)
                        
                        # Reset lädt nun die Konfiguration, die wir gerade gesetzt haben
                        obs = vec_env.reset()
                        
                        done = False
                        log_data = []
                        
                        # Simulation Loop
                        while not done:
                            action, _ = model.predict(obs, deterministic=True)
                            obs, _, dones, infos = vec_env.step(action)
                            log_data.append(infos[0]) # Info vom Wrapper
                            done = dones[0]
                        
                        df_run = pd.DataFrame(log_data)
                        df_run.to_csv(full_csv_path, index=False)
                        
                        # Plotting
                        try:
                            plot_path = os.path.join(save_path, f"overview_plot_{run_idx}.png")
                            plot_trajectory_results(df_run, plot_path)
                        except Exception as e:
                            print(f"[WARNING] Plotting failed: {e}")
                    else:
                        df_run = pd.read_csv(full_csv_path)

                    # Metriken berechnen
                    mets = calculate_metrics_physics(df_run, m_min, m_range, global_env_kwargs['ctrl_freq'], full_csv_path, max_duration, total_waypoints)
                    
                    results.append({
                        "Agent": agent_name,
                        "Scenario": scen_name,
                        "Mission": mission_name,
                        "Run_ID": run_idx,
                        "RMSE_XYZ": mets['rmse_xyz'],
                        "RMSE_TE_XYZ": mets['rmse_te_xyz'],
                        "RMSE_RPY": mets['rmse_rpy'],
                        "RMSE_TE_RPY": mets['rmse_te_rpy'],
                        "RMSE_VEL": mets['rmse_vel'],
                        "RMSE_TE_VEL": mets['rmse_te_vel'],
                        "Energy": mets['energy'],
                        "Jitter": mets['jitter'],
                        "Flight_Time": mets['flight_time'],
                        "Stability": mets['stability'],
                        "Max_WP": mets['max_wp'],
                        "WCR": mets['wcr'],
                        "Path": full_csv_path
                    })
                    # print(f"  > RL: {agent_name}/{scen_name}/{mission_name} | RMSE_TE_XYZ={mets['rmse_te_xyz']:.2f} | RMSE_TE_RPY={mets['rmse_te_rpy']:.2f}")
        
        # Sauber schließen pro Agent
        vec_env.close()
            
    return results

# ==============================================================================
# INDI COLLECTOR
# ==============================================================================
def collect_indi_results(indi_base_dir, motor_min, motor_range, ctrl_freq, mission_lens=None, max_duration=10.0):
    print(f"   get INDI data")

    results = []
    
    if not os.path.exists(indi_base_dir): 
        print(f"[ERROR] INDI data not found: {indi_base_dir}")
        return results

    # Ordner durchsuchen
    scenarios = [d for d in os.listdir(indi_base_dir) if os.path.isdir(os.path.join(indi_base_dir, d))]

    for scen in scenarios:
        scen_path = os.path.join(indi_base_dir, scen)
        missions = [d for d in os.listdir(scen_path) if os.path.isdir(os.path.join(scen_path, d))]
        
        for miss in missions:
            miss_path = os.path.join(scen_path, miss)
            csv_file = os.path.join(miss_path, "benchmark_results.csv")
            
            if os.path.exists(csv_file):
                try:
                    total_waypoints = mission_lens.get(miss, None) if mission_lens else None
                    df = pd.read_csv(csv_file)
                    mets = calculate_metrics_physics(df, motor_min, motor_range, ctrl_freq, csv_file, max_duration, total_waypoints)
                    
                    results.append({
                        "Agent": "INDI_Controller", 
                        "Scenario": scen,      
                        "Mission": miss,       
                        "Run_ID": 0,           
                        "RMSE_XYZ": mets['rmse_xyz'],
                        "RMSE_TE_XYZ": mets['rmse_te_xyz'],
                        "RMSE_RPY": mets['rmse_rpy'],
                        "RMSE_TE_RPY": mets['rmse_te_rpy'],
                        "RMSE_VEL": mets['rmse_vel'],
                        "RMSE_TE_VEL": mets['rmse_te_vel'],
                        "Energy": mets['energy'],
                        "Jitter": mets['jitter'],
                        "Flight_Time": mets['flight_time'],
                        "Stability": mets['stability'],
                        "Max_WP": mets['max_wp'],
                        "WCR": mets['wcr'],
                        "Path": csv_file
                    })
                    # print(f"  > INDI: {scen}/{miss} | RMSE_TE_XYZ={mets['rmse_te_xyz']:.2f} | RMSE_TE_RPY={mets['rmse_te_rpy']:.2f}")
                except Exception as e:
                    print(f"  [ERROR] {csv_file}: {e}")
            else:
                pass
                # print(f"  [WARN] Keine CSV in {miss_path}")
    return results

# ==============================================================================
# MAIN
# ==============================================================================

def main():
    print("Evaluation Script: Run")
    print("   Initialize")
    try:
        project_root = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
    except NameError:
        project_root = "."
        
    rl_output_dir = os.path.join(project_root, "data", "Evaluation", "Raw_Files")
    indi_input_dir = os.path.join(project_root, "data", "INDI_test") 
    
    AGENTS = {
        "RL_Add_Blind": {
            "path": os.path.join(project_root, "saves", "PPO_VEL_Curriculum_2025-12-04_01-14_rel_I_Env_256Net_additive_newWAR_C2_noKnowledge", "stage_3_Full_Profile_Extended", "best_model.zip"), 
            "env_kwargs": {'reward_type': 'additive', 'anomaly_knowledge': False}
        },
        "RL_Geo_Blind": {
            "path": os.path.join(project_root, "saves", "PPO_VEL_Curriculum_2025-12-04_09-28_rel_I_Env_256Net_multiplicative_WAR_C2_NoKnowledge", "stage_3_Full_Profile_Extended", "best_model.zip"), 
            "env_kwargs": {'reward_type': 'multiplicative', 'anomaly_knowledge': False}
        },
        "RL_Add_Aware": {
            "path": os.path.join(project_root, "saves", "PPO_VEL_Curriculum_2025-12-04_01-50_rel_I_Env_256Net_additive_newWAR_C2_Knowledge", "stage_3_Full_Profile_Extended", "best_model.zip"), 
            "env_kwargs": {'reward_type': 'additive', 'anomaly_knowledge': True}
        },
        "RL_Geo_Aware": {
            "path": os.path.join(project_root, "saves", "PPO_VEL_Curriculum_2025-12-04_09-18_rel_I_Env_256Net_multiplicative_newWAR_C2_Knowledge", "stage_3_Full_Profile_Extended", "best_model.zip"), 
            "env_kwargs": {'reward_type': 'multiplicative', 'anomaly_knowledge': True}
        }
    }
    
    # Initialize dummy Env and load const env 
    ENV_KWARGS_GLOBAL = {
        'reward_function': 'exponential', 'reward_type': 'multiplicative', 
        'anomaly_knowledge': False, 'ctrl_freq': 125, 
        'use_unix': platform.system() != "Windows"
    }
    temp_env = VEL_Env(**ENV_KWARGS_GLOBAL) 
    MOTOR_MIN = temp_env.limits.motor.min 
    MOTOR_RANGE = temp_env.limits.motor.range 
    CTRL_FREQ = ENV_KWARGS_GLOBAL['ctrl_freq']
    temp_env.close()

    # Loader Setup
    print("   Load Missions")
    loader = TrajectoryDataLoader(verbose=False)
    
    EVAL_MISSIONS = ["Benchmark_Ministep", "Benchmark_Spiral", "Benchmark_Response", "Benchmark_Stabilize"]
    eval_missions_config = {name: 1.0 for name in EVAL_MISSIONS}    
    _, eval_mission_pool = loader.create_pools(eval_missions_config, load_eval_only=True)
    
    # Create lookup for mission lengths (Total Waypoints)
    MISSION_LENS = {}
    for df in eval_mission_pool:
        MISSION_LENS[df['mission_name'].iloc[0]] = len(df)
    
    
    print("   Load Anomalies")
    EVAL_ANOMALIES = ["abrupt_LoE" , "abrupt_LoE_multi", "gradual_LoE", "gradual_LoE_multi", "Intermittent_Actuator_Dropout", "Intermittent_Actuator_Dropout_multi", "permanent_LoE", "permanent_LoE_multi"]
    
    #print(f"Loader hat folgende Keys: {list(loader.anomaly_datasets.keys())}")
    
    anomaly_groups = {}
    for anom_type in EVAL_ANOMALIES:
        if anom_type in loader.anomaly_datasets:
            file_list = loader.anomaly_datasets[anom_type][:1]
            
            print(f"      - Anomaly: {anom_type}")
            
            loaded_dfs = []
            for fpath in file_list:
                df = pd.read_csv(fpath)
                df['anomaly_name'] = anom_type
                loaded_dfs.append(df)
            anomaly_groups[anom_type] = loaded_dfs
        else:
            print(f"  [WARN] ANOMALY '{anom_type}' NOT FOUND")

    #print(anomaly_groups)

    # Simulation
    print("   get Simulation and INDI results")
    rl_res = run_rl_simulation(AGENTS, eval_mission_pool, anomaly_groups, ENV_KWARGS_GLOBAL, rl_output_dir, MOTOR_MIN, MOTOR_RANGE, max_duration=10.0)
    indi_res = collect_indi_results(indi_input_dir, MOTOR_MIN, MOTOR_RANGE, CTRL_FREQ, mission_lens=MISSION_LENS, max_duration=10.0)
    
    all_res = rl_res + indi_res
    
    print("   evaluate results")
    if all_res:
        df_final = pd.DataFrame(all_res)
        
        # Calculate Score
        df_final = calculate_composite_score(df_final)

        print(df_final.head(3))
        
        # Save full summary
        out_csv = os.path.join(rl_output_dir, "summary_metrics_full.csv")
        df_final.to_csv(out_csv, index=False)

        # Save small summary
        out_csv = os.path.join(rl_output_dir, "summary_metrics_small.csv")
        # Aggregate mean values for the small summary
        summary_cols = ["Stability", "WCR", "RMSE_TE_XYZ", "RMSE_TE_RPY", "RMSE_TE_VEL", "Score"]
        df_summary = df_final.groupby("Agent")[[c for c in summary_cols if c in df_final.columns]].mean().reset_index()
        df_summary.to_csv(out_csv, index=False)
        print("\n" + "="*34)
        print(f"EVALUATION COMPLETE. Got all data. \nSaved to: {out_csv} \n")

        
        # Print Score Overview
        print(df_final.groupby("Agent")[["Stability", "WCR", "RMSE_TE_XYZ", "RMSE_TE_RPY", "RMSE_TE_VEL", "Score"]].mean())
        print("\n" + "="*34)
    else:
        print("[ERROR] Got no results to evaluate.")

if __name__ == "__main__":
    main()
