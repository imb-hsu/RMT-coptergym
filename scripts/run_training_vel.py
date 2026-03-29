"""
SUMMARY: Adaptive Reinforcement Learning for Multicopter Velocity Control
This script implements a Curriculum Learning (CL) pipeline using Proximal Policy Optimization (PPO) 
 to train a robust velocity controller for a multicopter (X8 configuration). 
The training is structured in stages to progressively handle complex flight dynamics and 
actuator anomalies (Loss of Effectiveness, Dropouts). 

Key features:
1. Multi-stage Curriculum: From hover stabilization to high-speed dynamic missions.
2. Robustness Training: Controlled injection of actuator faults during training.
3. Automated Evaluation: Post-training deterministic benchmarking against baseline 
   scenarios and representative anomaly cases.
"""

import os
import torch

# this limits currently the overall used cores to 5 instead the ususal 40's
# Idea was to keep them at 5*cores(10) to force usage of 50/60 availanle cores

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

# Importiere Hilfsfunktionen und die korrekte Umgebung
#from rmt_coptergym.utils.utils import plot_trajectory_results

from rmt_coptergym.application_envs.RL_VEL_Env_absolute import VEL_Env
env_string = "absBasic"

#from rmt_coptergym.application_envs.RL_VEL_Env_relative import VEL_Env
#env_string = "relBasicInt"

#from rmt_coptergym.application_envs.RL_VEL_rel_IntDW import VEL_Env
#env_string = "rel_IntDW"

#from rmt_coptergym.application_envs.RL_VEL_rel_PID import PID_VEL_Env as VEL_Env
#env_string = "rel_PID"

from rmt_coptergym.utils.plots import EvaluationPlots
from rmt_coptergym.utils.trajectory_dataloader import TrajectoryDataLoader
from rmt_coptergym.utils.utils import plot_trajectory_results

# --- Custom Callback für Checkpoint-Evaluierung und Plotting ---
def run_checkpoint_overview(model_path: str, eval_pool: list[pd.DataFrame], env_kwargs: dict):
    """
    Eine schlanke Evaluationsfunktion, die für einen Checkpoint
    nur Übersichts-Plots für jede Evaluationsmission erstellt.
    """
    print(f"  > Erstelle Übersichts-Plots für Checkpoint: {os.path.basename(model_path)}")
    model = PPO.load(model_path, device='cpu') # Lade auf CPU, um GPU-Speicher zu schonen
    
    # Erstelle einen Unterordner für die Plots dieses Checkpoints
    plot_save_dir = os.path.join(os.path.dirname(model_path), f"{os.path.basename(model_path).replace('.zip', '')}_plots")
    os.makedirs(plot_save_dir, exist_ok=True)

    for mission_df in eval_pool:
        # Erstelle eine temporäre Umgebung für genau diese eine Mission
        single_mission_pool = [mission_df]
        eval_env_kwargs = {**env_kwargs, 'mission_pool': single_mission_pool, 'is_eval': True}
        env = DummyVecEnv([lambda: VEL_Env(**eval_env_kwargs)])

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
        
        # Rufe deine alte Übersichts-Plot-Funktion auf
        plot_path = os.path.join(plot_save_dir, f"overview_{mission_name}.png")
        # WICHTIG: Deine plot_trajectory_results muss die Vektoren parsen, falls sie als Strings im df sind
        # Passe die Funktion ggf. an, damit sie mit dem rohen DataFrame umgehen kann.
        # Du müsstest die .apply(lambda x: x[0]) etc. durch die _parse_vector_col Logik ersetzen
        # oder sicherstellen, dass die Daten bereits als Vektoren vorliegen.
        
        # ANNAHME: plot_trajectory_results ist angepasst, um mit dem DF umzugehen.
        plot_trajectory_results(df, plot_path) # HIER DEINE ALTE PLOT FUNKTION AUFRUFEN

    print(f"  > Alle Übersichts-Plots gespeichert in: {plot_save_dir}")


class CheckpointWithPlotsCallback(CheckpointCallback):
    def __init__(self, eval_pool: list, env_kwargs: dict, **kwargs):
        super().__init__(**kwargs)
        self.eval_pool = eval_pool
        self.env_kwargs = env_kwargs

    def _on_step(self) -> bool:
        # Rufe die Logik des originalen Callbacks auf.
        # Dieser speichert das Modell, wenn save_freq erreicht ist.
        continue_training = super()._on_step()

        # `self.last_saved_checkpoint_path` ist eine neue Variable in SB3 (ab v2.0)
        # die den Pfad zum letzten gespeicherten Modell enthält.
        # Wir prüfen, ob im letzten Aufruf ein Modell gespeichert wurde.
        if self.n_calls % self.save_freq == 0 and self.save_path is not None:
            # Hol den exakten Pfad des gerade gespeicherten Modells
            model_path = os.path.join(self.save_path, f"{self.name_prefix}_{self.num_timesteps}_steps.zip")
            if os.path.exists(model_path):
                 run_checkpoint_overview(model_path, self.eval_pool, self.env_kwargs)

        return continue_training

def run_rl_evaluation(model_path: str, eval_pool: list[pd.DataFrame], anomaly_pool: list[pd.DataFrame], env_kwargs: dict, save_dir: str):
    """
    Führt das trainierte RL-Modell auf jeder Trajektorie des Evaluationsdatensatzes aus.
    Erstellt eine Hierarchie für vergleichbare Benchmarks:
      1. Baseline (Keine Anomalie)
      2. Pro Anomalie-Typ genau EINE repräsentative Störung (Index 0 aus der Gruppe)
    """
    print(f"\n=== Starte deterministische Evaluation: {model_path} ===")
    os.makedirs(save_dir, exist_ok=True)
    
    # Modell laden (nur einmal nötig)
    try:
        model = PPO.load(model_path)
    except Exception as e:
        print(f"[ERROR] Konnte Modell nicht laden: {e}")
        return

    # ---------------------------------------------------------
    # 1. Anomalien gruppieren & Repräsentanten wählen
    # ---------------------------------------------------------
    # Wir wollen nicht 200 Ordner für 200 Dateien, sondern nur 1 Ordner pro Fehlertyp.
    # Wir nehmen an, dass der Loader die Dateien so sortiert hat, dass der
    # 'eval_sequence' (dein harter Testfall) immer als erstes kommt.
    
    representative_anomalies = {}
    
    for df in anomaly_pool:
        # Namen holen (wurde im Loader gesetzt via 'anomaly_name')
        # Fallback auf 'mission_name' oder 'anomaly_name', falls Key variiert
        if 'anomaly_name' in df.columns:
            name = df.iloc[0]['anomaly_name']
        elif 'anomaly_name' in df.columns:
            name = df.iloc[0]['anomaly_name']
        else:
            name = "Unknown_Anomaly"
        
        # Wenn wir diesen Typ noch nicht haben -> Speichern (das ist der Erste/Repräsentant)
        if name not in representative_anomalies:
            representative_anomalies[name] = df

    print(f"Gefundene Anomalie-Szenarien: {list(representative_anomalies.keys())}")

    # ---------------------------------------------------------
    # 2. Szenarien-Liste erstellen
    # ---------------------------------------------------------
    scenarios = []

    # A) Baseline: Keine Anomalie (Referenz)
    scenarios.append({
        "folder_name": "00_Baseline_No_Anomaly",
        "anom_pool": [],     # Leerer Pool
        "active": False      # Chance 0.0
    })

    # B) Anomalie-Szenarien (Deterministisch)
    # Wir sortieren nach Namen, damit '01', '02' immer gleich zugeordnet sind
    for idx, (anom_name, anom_df) in enumerate(sorted(representative_anomalies.items())):
        
        # Ordnername bereinigen (z.B. "01_Intermittent_Actuator_Dropout")
        safe_name = "".join([c for c in anom_name if c.isalnum() or c in (' ', '_', '-')]).strip()
        folder_name = f"{idx+1:02d}_{safe_name}"
        
        scenarios.append({
            "folder_name": folder_name,
            "anom_pool": [anom_df], # Liste mit Länge 1 -> Zwingt Env immer diesen DF zu nutzen
            "active": True          # Chance 1.0
        })

    # ---------------------------------------------------------
    # 3. Execution Loop (Szenarien -> Missionen)
    # ---------------------------------------------------------
    for scenario in scenarios:
        print(f"\n--- Starte Szenario: {scenario['folder_name']} ---")
        
        # Basis-Ordner für dieses Szenario erstellen
        scenario_dir = os.path.join(save_dir, scenario["folder_name"])
        os.makedirs(scenario_dir, exist_ok=True)

        # Loop über alle Evaluations-Missionen (Trajektorien)
        for i, mission_df in enumerate(eval_pool):
            
            # --- Environment Setup für diesen Run ---
            current_kwargs = env_kwargs.copy()
            current_kwargs.update({
                'mission_pool': [mission_df], # Genau diese Mission (Index 0 in Env)
                'is_eval': True,
                'seed': 42, # Fixer Seed für absolute Reproduzierbarkeit
                
                # Anomalie-Logik:
                # Da anom_pool nur 1 Eintrag hat (unseren Repräsentanten), 
                # nimmt die Env bei reset() immer index 0.
                'anomaly_pool': scenario["anom_pool"], 
                'anomaly_chance': 1.0 if scenario["active"] else 0.0
            })

            # Env erstellen (DummyVecEnv kapselt es für SB3)
            env = DummyVecEnv([lambda: VEL_Env(**current_kwargs)])
            
            # --- Simulation ---
            obs = env.reset()
            log_data = []
            done = False
            
            while not done:
                # Deterministische Action für sauberen Vergleich
                action, _ = model.predict(obs, deterministic=True)
                obs, _, dones, info_list = env.step(action)
                
                # Info sammeln (VecEnv gibt Liste zurück)
                log_data.append(info_list[0])
                done = dones[0]
            
            env.close()

            # --- Ergebnisse verarbeiten ---
            if not log_data:
                print(f"  [WARN] Keine Daten für Mission {i}. Überspringe.")
                continue

            # Missionsnamen sicher ermitteln
            mission_name = log_data[0].get('mission_name', f"Mission_{i}")
            
            # Unterordner pro Mission anlegen: .../eval/01_Anomaly/Figure_8/
            mission_save_dir = os.path.join(scenario_dir, mission_name)
            os.makedirs(mission_save_dir, exist_ok=True)
            
            # 1. CSV speichern
            df_res = pd.DataFrame(log_data)
            csv_path = os.path.join(mission_save_dir, "rl_results.csv")
            df_res.to_csv(csv_path, index=False)
            
            # 2. Plots erstellen (Deine Klasse)
            try:
                plotter = EvaluationPlots(save_dir=mission_save_dir)
                plotter.create_all_plots(df_res)
            except Exception as e:
                print(f"  [ERROR] Plotting fehlgeschlagen bei {mission_name}: {e}")

    print(f"\n=== Evaluation abgeschlossen. Alle Ergebnisse in: {save_dir} ===")

def old_run_rl_evaluation(model_path: str, eval_pool: list[pd.DataFrame], anomaly_pool: list[pd.DataFrame], env_kwargs: dict, save_dir: str):
    """
    Führt das trainierte RL-Modell auf jeder Trajektorie des Evaluationsdatensatzes aus
    und speichert individuelle Ergebnisse und Plots.
    """
    print(f"\n--- Evaluiere RL-Modell: {model_path} ---")
    # Stelle sicher, dass das Parent-Verzeichnis für die Plots existiert
    os.makedirs(save_dir, exist_ok=True)
    
    model = PPO.load(model_path)

    # Iteriere durch jede Trajektorie im Evaluationsset
    num_eval_episodes = len(eval_pool)
    for i in range(num_eval_episodes):
        # Wähle die Trajektorie für diese Episode manuell aus
        # Um sicherzustellen, dass jede Mission deterministisch evaluiert wird, erstellen wir
        # eine neue Umgebung für jede einzelne Mission.
        single_mission_df = eval_pool[i]
        single_mission_pool = [single_mission_df]
        eval_env_kwargs = {
            **env_kwargs, 
            'mission_pool': single_mission_pool, 
            'is_eval': True,
            'seed': 1,
            'anomaly_pool': anomaly_pool,
            'anomaly_chance': 1.0 # Anomalie in der Eval immer aktiv
        }
        env = DummyVecEnv([lambda: VEL_Env(**eval_env_kwargs)])

        obs = env.reset()

        log_data = []
        done = False
        while not done:
            action, _ = model.predict(obs, deterministic=True)
            obs, _, dones, info = env.step(action)
            log_data.append(info[0])
            done = dones[0]

        # Speichere und plotte die Ergebnisse für diese spezifische Trajektorie
        # Stelle sicher, dass log_data nicht leer ist
        if not log_data:
            print(f"  > Warnung: Keine Log-Daten für eine Mission im Pool-Index {i} erfasst. Überspringe.")
            env.close()
            continue

        mission_name = log_data[0]['mission_name']
        print(f"  > Evaluation für Mission abgeschlossen: {mission_name}")
        df = pd.DataFrame(log_data)
        
        mission_save_dir = os.path.join(save_dir, mission_name)
        os.makedirs(mission_save_dir, exist_ok=True)
        
        csv_path = os.path.join(mission_save_dir, "rl_results.csv")
        df.to_csv(csv_path, index=False)
        
        # Erstelle die detaillierten Plots mit der neuen Klasse
        plotter = EvaluationPlots(save_dir=mission_save_dir)
        plotter.create_all_plots(df)
        env.close()

def compare_with_benchmark(rl_eval_dir: str, indi_benchmark_dir: str, eval_mission_names: list):
    """
    Lädt RL- und INDI-Ergebnisse und erstellt Vergleichsplots.
    """
    print("\n" + "="*80 + "\n--- Erstelle Vergleichsplots vs. INDI Benchmark ---\n" + "="*80)
    for mission_name in eval_mission_names:
        rl_csv_path = os.path.join(rl_eval_dir, mission_name, "rl_results.csv")
        indi_csv_path = os.path.join(indi_benchmark_dir, mission_name, "benchmark_results.csv")

        if not os.path.exists(rl_csv_path) or not os.path.exists(indi_csv_path):
            print(f"  > Überspringe Vergleich für '{mission_name}': Ergebnisdateien fehlen.")
            continue

        df_rl = pd.read_csv(rl_csv_path)
        df_indi = pd.read_csv(indi_csv_path)

        def parse_vec(s):
            try:
                # Sichereres Parsen von String-Repräsentationen von Arrays
                return np.array(json.loads(s.replace(" ", ", ").replace("[,", "[").replace("],", "]")))
            except:
                return np.array([np.nan, np.nan, np.nan])

        fig, axes = plt.subplots(2, 1, figsize=(15, 12), sharex=True)
        fig.suptitle(f"RL vs. INDI Benchmark: {mission_name}", fontsize=16)

        axes[0].set_title("Positionsfehler-Norm")
        axes[0].plot(df_rl['sim_time'], df_rl['distance_current'], label='RL Agent', color='blue')
        axes[0].plot(df_indi['sim_time'], df_indi['distance_current'], label='INDI Controller', color='red', linestyle='--')
        axes[0].set_ylabel("Positionsfehler [m]")
        axes[0].grid(True); axes[0].legend()

        axes[1].set_title("Geschwindigkeitsfehler-Norm")
        axes[1].plot(df_rl['sim_time'], df_rl['error_vel_c'].apply(parse_vec).apply(np.linalg.norm), label='RL Agent', color='blue')
        axes[1].plot(df_indi['sim_time'], df_indi['error_vel_c'].apply(parse_vec).apply(np.linalg.norm), label='INDI Controller', color='red', linestyle='--')
        axes[1].set_ylabel("Geschwindigkeitsfehler [m/s]"); axes[1].set_xlabel("Zeit [s]")
        axes[1].grid(True); axes[1].legend()

        plt.tight_layout(rect=[0, 0.03, 1, 0.96])
        comparison_plot_path = os.path.join(rl_eval_dir, mission_name, "comparison_plot.png")
        plt.savefig(comparison_plot_path)
        plt.close(fig)
        print(f"  > Vergleichsplot für '{mission_name}' gespeichert.")

def main():
    start_time_total = time.perf_counter()

    # =================================================================================
    # --- 1. ZENTRALE KONFIGURATION ---
    # =================================================================================
    training_steps = 3_000_000 #1_000_000

    # 82 min for 1mil 24 cores, 
    # 150 min for 2mil 36 cores
    # 288 min for 4mil 36 cores, 
    # 203 min for 1mil 8 cores

    CONFIG = {
        "save_name": "",
        "run_info": "AbsEnv_IncreasedDynWeights_BasicNets",
        "num_cpu": 8,

        # --- Curriculum Learning Stages --- 4x500k @8 core = 3020 sek = 50.3min
        "curriculum_stages": [
            # --- STAGE 1: Robust Hover Foundation ---
            {
                "name": "Robust_Hover_Base",
                "missions": {
                    'Position_Hover': 0.25,
                    'Velocity_Stabilize': 0.75,
                    'Position_To_Origin': 1.0,
                    'Velocity_Jump1': 0.25,
                    'Velocity_Jump2': 0.25,
                    'Velocity_StepSequence': 0.25,
                    'Position_Switch': 0.25,
                },
                "anomaly_chance": 0.4, 
                "anomaly_config": {
                    'permanent_LoE': 1.0, 
                    'Intermittent_Actuator_Dropout': 0.2, 
                    'abrupt_LoE': 0.2
                },
                "timesteps": training_steps, # Volle Länge (Fundament!)
                "env_kwargs": {
                    # Wir erlauben hier noch etwas mehr "Sicherheits-Abstand"
                    "reward_weights": { 
                        "integral": 2.0 
                    } 
                }
            },
            
            # --- STAGE 2: Dynamic Agility ---
            # Ziel: Den Ausgleich auch während der Bewegung halten
            {
                "name": "Robust_Dynamics",
                "missions": {
                    'Position_Hover': 0.2,
                    'Velocity_Stabilize': 0.5,
                    'Position_To_Origin': 0.5,
                    'Velocity_Jump1': 1.0,
                    'Velocity_Jump2': 1.0,
                    'Velocity_StepSequence': 1.0,
                    'Position_Switch': 1.0,
                    'Position_Square': 0.5,
                    'Velocity_Dynamic': 0.2,
                },
                "anomaly_chance": 0.6, 
                "anomaly_config": {
                    'permanent_LoE': 1.0,
                    'abrupt_LoE': 0.8, 
                    'gradual_LoE': 0.5,  
                    'Intermittent_Actuator_Dropout': 1.0
                },
                "timesteps": training_steps,
                "env_kwargs": {
                    # Gewichte bleiben stabil, damit er sich nicht umgewöhnen muss
                }
            },

            # --- STAGE 3: Master Class (Extended) ---
            # Ziel: Perfektionierung und Härte
            {
                "name": "Full_Profile_Extended",
                "missions": {
                    'Velocity_Stabilize': 0.25,
                    'Position_To_Origin': 0.25,
                    'Velocity_Dynamic': 1.0,
                    'Position_Long_Range': 1.0,
                    'Position_Mission': 1.0,
                    'Velocity_Jump1': 0.25,
                    'Velocity_Jump1': 0.25,
                    'Velocity_StepSequence': 1.0,
                    'Position_Square': 1.0
                },
                "anomaly_chance": 0.8, 
                "anomaly_config": {
                    'permanent_LoE': 0.5,
                    'abrupt_LoE': 0.75,
                    'abrupt_LoE_multi': 0.75,
                    'Intermittent_Actuator_Dropout': 0.5,  
                    'Intermittent_Actuator_Dropout_multi': 0.75,
                    'gradual_LoE': 1.0
                },
                # HIER DEIN WUNSCH: Doppelte Zeit für das Feintuning
                "timesteps": int(training_steps * 2.0), 
                "env_kwargs": {
                    "reward_weights": {
                        # Optional: Integral noch wichtiger machen für finalen 0-Offset
                        "integral": 3.0,
                        "vel": 3.5
                    },
                }
            }
        ],
        # --- Missions for final evaluation and benchmark comparison ---
        "eval_mission_names": ['Velocity_Stabilize', 'Velocity_Step_Sequence', 'Velocity_Jump', 'Velocity_Dynamic'],

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
                "vel": 2,#3.0,
                "integral": 2.5, 
                "yaw": 2.0,

                # Physics
                # important during hovering - but for flying contra productive, still kept as small correction
                "rollpitch": 0.1,
                "accel": 0.25,#0.05,
                "omega": 0.25,#0.05,

                # Efficiancy
                # Paired Efficiency ist fundamental for normal operation X8, same with balance - smoothness cinflicts wich dynamic control
                "paired_efficiency": 0.5,
                "balance": 0.5,
                "smoothness": 0.5,#0.05, 

                # --- HARD CONSTRAINTS ---
                "comfort_zone": 1.0
            
            }
        },

        "model_kwargs": {
            'policy': 'MultiInputPolicy',
            'policy_kwargs': dict(
                net_arch=dict(pi=[64, 64], vf=[64, 64]), # dict(pi=[256, 256], vf=[256, 256]), # my approach vs default [64, 64]
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

    save_path_name = "PPO_VEL_" + f"{time.strftime('%Y-%m-%d_%H-%M')}"+"_ENV_" + env_string \
                    + reward_type_string + anomaly_known +"_" + CONFIG['run_info']
    CONFIG['save_name']=save_path_name

    if training_steps < 1000: # Debug Modus erkannt
        print("!!! DEBUG MODE: Reduziere n_steps für schnelles Feedback !!!")
        # Setze n_steps auf min 64, damit der Puffer klein ist (64*8 = 512 Steps)
        CONFIG['model_kwargs']['n_steps'] = 8 
        CONFIG['model_kwargs']['batch_size'] = 8 # Batch size muss <= buffer sein

    project_root = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
    save_path = os.path.join(project_root, "saves", save_path_name)
    os.makedirs(save_path, exist_ok=True)

    with open(os.path.join(save_path, "config.json"), "w") as f:
        json.dump(CONFIG, f, indent=4, default=lambda o: '<not serializable>')

    loader = TrajectoryDataLoader()
    
    # Lade alle verfügbaren Missionen für die Evaluation
    all_available_eval_missions = loader.available_datasets
    eval_missions_config = {'Benchmark_Ministep': 1.0, 'Benchmark_Response': 1.0, 'Benchmark_Spiral': 1.0, 'Benchmark_Stabilize': 1.0} #{name: 1.0 for name in all_available_eval_missions}
    
    _, eval_mission_pool = loader.create_pools(eval_missions_config, load_eval_only=True)
    
    if not eval_mission_pool:
        raise ValueError("Der Evaluations-Pool ist leer! Prüfe 'dataset_definitions'.")
    
    eval_anomaly_pool = []
    
    # Hole alle Fehlertypen, die im Training vorkommen könnten
    all_possible_anomalies = set()
    for stage in CONFIG['curriculum_stages']:
        all_possible_anomalies.update(stage['anomaly_config'].keys())
    
    print(f"Erstelle kompakten Anomalie-Pool aus: {sorted(all_possible_anomalies)}")

    for anomaly_name in sorted(all_possible_anomalies):
        if anomaly_name in loader.anomaly_datasets:
            all_files = loader.anomaly_datasets[anomaly_name]
            
            # WICHTIG: Nimm immer Index 0 (Eval-Sequence) + maximal 2 Variationen
            files_to_load = all_files[:3] 
            
            for f in files_to_load:
                df = pd.read_csv(f)
                df['anomaly_name'] = anomaly_name # Namen sichern für Auswertung
                eval_anomaly_pool.append(df)
        else:
            print(f"Warnung: Anomalie '{anomaly_name}' nicht im Loader gefunden.")

    # Set Eval_env
    eval_env_kwargs = {
        **CONFIG['env_kwargs'], 
        'mission_pool': eval_mission_pool, 
        'is_eval': True, 
        'seed': 42, # Fixer Seed für Vergleichbarkeit
        
        # Hier nutzen wir unseren handverlesenen Pool
        'anomaly_pool': eval_anomaly_pool,
        'anomaly_chance': 1.0 # In der Eval immer Fehler prüfen!
    }
    
    # DummyVecEnv kapselt die Env für SB3
    eval_env = DummyVecEnv([lambda: Monitor(VEL_Env(**eval_env_kwargs))])
    
    # WICHTIG: Anzahl der Eval-Episoden bestimmen
    # Wir wollen idealerweise jede Anomalie im Pool mindestens einmal sehen.
    # Da die Env iteriert (idx % len), setzen wir n_eval_episodes gleich der Pool-Größe.
    # Falls der Pool sehr klein ist (< 5), nimm mindestens 10.
    
    n_eval_eps = len(eval_mission_pool) * len(eval_anomaly_pool) # max(len(eval_anomaly_pool), 10)

    print(f"EvalCallback konfiguriert für {n_eval_eps} Episoden pro Check.")

    eval_callback = EvalCallback(
        eval_env,
        eval_freq = max(100_000 // CONFIG['num_cpu'], 1), # dummy value will be overwritten in eahc stage
        n_eval_episodes=n_eval_eps, 
        deterministic=True
    )
    

    # =================================================================================
    # --- MODELLTRAINING (Curriculum-Schleife) ---
    # =================================================================================
    model = None
    last_model_path = None

    for i, stage in enumerate(CONFIG['curriculum_stages']):
        stage_num = i + 1

        #if stage_num == 2:
        #    print("\nTraining wird wie geplant nach Abschluss von Stage 1 beendet.")
        #    break

        print("\n" + "="*80 + f"\nSTART CURRICULUM STAGE {stage_num}/{len(CONFIG['curriculum_stages'])}: {stage['name']}\n" + "="*80)
        start_time_stage = time.perf_counter()

        # Erstelle für jede Stufe einen eigenen Speicherort für die besten Modelle und Logs
        stage_save_path = os.path.join(save_path, f"stage_{stage_num}_{stage['name']}")
        os.makedirs(stage_save_path, exist_ok=True)

         ## Test here custom env-kwargs
        # 1. Beginne mit der tiefen Kopie der Basis-Konfiguration
        current_env_kwargs = copy.deepcopy(CONFIG['env_kwargs'])
        
        # 2. Überschreibe sie mit stufenspezifischen Werten, falls vorhanden
        if 'env_kwargs' in stage:
            # Wichtig: Bei verschachtelten Dictionaries wie 'reward_weights'
            # müssen wir intelligent zusammenführen, nicht einfach überschreiben.
            for key, value in stage['env_kwargs'].items():
                if isinstance(value, dict) and key in current_env_kwargs:
                    current_env_kwargs[key].update(value)
                else:
                    current_env_kwargs[key] = value
        
        # --- Umgebungen und Callbacks für DIESE Stufe erstellen ---

        # Dieser Schritt ist entscheidend: Durch das Neuerstellen der Callbacks wird ihr interner Zähler zurückgesetzt.

        #print("init eval CB: ", CONFIG['num_cpu'])
        #eval_callback = EvalCallback(
        #    eval_env, best_model_save_path=stage_save_path, log_path=stage_save_path,
        #    eval_freq=max(100_000 // CONFIG['num_cpu'], 1), n_eval_episodes=len(eval_pool), 
        #    deterministic=True,
        #)
        
        min_batch_size = CONFIG['model_kwargs']['n_steps'] * CONFIG['num_cpu']
        effective_timesteps = max(stage['timesteps'], min_batch_size)

        # EvalCallback is persistent outside of loop, here we update savepathe

        if eval_env is not None:
            eval_env.env_method("update_weights_online", current_env_kwargs['reward_weights'])

        eval_callback.best_model_save_path = stage_save_path
        eval_callback.log_path = stage_save_path
        eval_callback.eval_freq = np.ceil(0.17*(effective_timesteps / CONFIG['num_cpu'])) #max(1, int((effective_timesteps / 5) / CONFIG['num_cpu']))
        eval_callback.best_mean_reward = -np.inf 


        checkpoint_plot_callback = CheckpointWithPlotsCallback(
            eval_pool=eval_mission_pool,
            env_kwargs=current_env_kwargs,
            save_freq= np.ceil(0.34*(effective_timesteps / CONFIG['num_cpu'])), #max(1, int((effective_timesteps / 3) / CONFIG['num_cpu'])),
            save_path=os.path.join(stage_save_path, 'checkpoints'),
            name_prefix="rl_model"
        )

        
        # --- Trainingsumgebung für DIESE Stufe erstellen ---
        stage_train_pool = loader.create_pools(stage['missions'])[0]
        stage_anomaly_pool = loader.load_anomaly_pool(stage['anomaly_config'])
        train_env_kwargs = {
            **current_env_kwargs, 
            'mission_pool': stage_train_pool, 
            'is_eval': False,
            'anomaly_pool': stage_anomaly_pool,
            'anomaly_chance': stage['anomaly_chance'] # Verwende die stufenspezifische Wahrscheinlichkeit
        }
        train_env = make_vec_env(VEL_Env, n_envs=CONFIG['num_cpu'], seed=42, vec_env_cls=SubprocVecEnv, env_kwargs=train_env_kwargs)

        # --- Modell erstellen oder laden ---
        if last_model_path is None:
            # Erstelle ein neues Modell für die erste Stufe
            model = PPO(env=train_env, tensorboard_log=os.path.join(stage_save_path, 'logs'), **CONFIG['model_kwargs'])
        else:
            # Lade das Modell der vorherigen Stufe und weise die neue Umgebung zu.
            # SB3 kümmert sich um die Details.
            print(f"Lade Modell aus vorheriger Stufe: {last_model_path}")
            model = PPO.load(last_model_path, env=train_env, **CONFIG['model_kwargs'])

        # --- Training starten ---
        model.learn(
            total_timesteps=stage['timesteps'], 
            callback=[eval_callback, checkpoint_plot_callback], 
            progress_bar=True, 
            reset_num_timesteps=False # Wichtig für kumulative Logs im Tensorboard
        )
        
        # Speichere das finale Modell dieser Stufe explizit
        final_model_path = os.path.join(stage_save_path, "final_model.zip")
        model.save(final_model_path)
        last_model_path = os.path.join(stage_save_path, "best_model.zip")
        # Sicherheitscheck: Wenn kein bestes Modell gespeichert wurde, nimm das finale.
        if not os.path.exists(last_model_path):
            last_model_path = final_model_path

        train_env.close()
        end_time_stage = time.perf_counter()
        print(f"--- STAGE {stage_num} BEENDET in {end_time_stage - start_time_stage:.2f} Sekunden ---")

        # --- Qualitative Evaluation für das BESTE Modell dieser Stufe ---
        print(f"\n--- Starte qualitative Evaluation für das BESTE Modell aus Stage {stage_num} ---")
        best_model_path_stage = os.path.join(stage_save_path, "best_model.zip")
        if os.path.exists(best_model_path_stage):
            stage_eval_dir = os.path.join(stage_save_path, "qualitative_evaluation_best_model")
            run_rl_evaluation(best_model_path_stage, eval_mission_pool, eval_anomaly_pool, current_env_kwargs, stage_eval_dir)
        else:
            print(f"Warnung: Konnte kein 'best_model.zip' in {stage_save_path} finden. Evaluation übersprungen.")
        

    print(f"\n--- TRAINING ABGESCHLOSSEN ---")
    eval_env.close()

    # =================================================================================
    # --- FINALE AUSWERTUNG & VERGLEICH ---
    # =================================================================================
    print("\n" + "="*80 + "\n--- STARTE FINALE AUSWERTUNG UND BENCHMARKING ---\n" + "="*80)
    start_time_eval = time.perf_counter()
    
    # 1. Führe die Evaluation mit dem finalen Modell des gesamten Trainings durch
    final_eval_dir = os.path.join(save_path, 'final_evaluation')
    print("Führe finale Evaluation mit dem letzten trainierten Modell durch...")
    run_rl_evaluation(last_model_path, eval_mission_pool, eval_anomaly_pool, current_env_kwargs, final_eval_dir)

    # 2. Vergleiche die finalen RL-Ergebnisse mit dem INDI-Benchmark
    # indi_benchmark_dir = os.path.join(project_root, 'data', 'INDI')
    # compare_with_benchmark(final_eval_dir, indi_benchmark_dir, eval_mission_names)
    end_time_eval = time.perf_counter()

    print(f"\n--- Evaluation und Benchmark abgeschlossen in {end_time_eval - start_time_eval:.2f} Sekunden ---")
    
    end_time_total = time.perf_counter()
    print("\n" + "="*100)
    print(f"--- GESAMTE SKRIPTAUSFÜHRUNGSZEIT: {end_time_total - start_time_total:.2f} Sekunden | {(end_time_total - start_time_total)/60:.2f} Minuten | {(end_time_total - start_time_total)/3600:.2f} Stunden ---")
    print("="*100)

if __name__ == '__main__':
    # Dieser Block ist für Multiprocessing unter Windows erforderlich
    # und stellt sicher, dass der Code nur ausgeführt wird, wenn das Skript direkt gestartet wird.
    main()