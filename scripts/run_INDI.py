import os, sys
import numpy as np
import pandas as pd
import platform
from stable_baselines3.common.vec_env import DummyVecEnv

project_root = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
local_src = os.path.join(project_root, "src")
sys.path.insert(0, local_src)
print(sys.path)

# Import custom environments and utilities
from rmt_coptergym.base_envs.RMT_Ctrl_Env import RMT_Ctrl_Env # Keep this import
from rmt_coptergym.utils.utils import plot_trajectory_results # Import from the correct path
from rmt_coptergym.utils.plots import EvaluationPlots # Import for detailed plots
from rmt_coptergym.utils.trajectory_dataloader import TrajectoryDataLoader


def run_indi_benchmark(output_base_dir: str, eval_mission_pool: list[pd.DataFrame], eval_anomaly_pool: list[pd.DataFrame], env_kwargs_base: dict):
    """
    Runs the internal INDI controller on a specified list of evaluation missions,
    considering different anomaly scenarios.
    For each mission and scenario, it saves the resulting trajectory data and a plot.
    """
    print("\n" + "="*80)
    print("--- Running INDI Controller Benchmark on all Eval Trajectories ---")
    print("="*80)

    if not eval_mission_pool:
        print("Keine Evaluations-Missionen gefunden. Breche ab."); return

    # --- 1. Anomalien gruppieren & Repräsentanten wählen ---
    representative_anomalies = {}
    for df in eval_anomaly_pool:
        name = df.iloc[0]['anomaly_name'] if 'anomaly_name' in df.columns else "Unknown_Anomaly"
        if name not in representative_anomalies:
            representative_anomalies[name] = df 

    print(f"Gefundene Anomalie-Szenarien für INDI-Benchmark: {list(representative_anomalies.keys())}")

    # --- 2. Szenarien-Liste erstellen ---
    scenarios = []

    # A) Baseline: Keine Anomalie (Referenz)
    scenarios.append({
        "folder_name": "baseline",
        "anom_pool": [],     
        "anomaly_chance": 0.0 
    })

    # B) Anomalie-Szenarien
    for idx, (anom_name, anom_df) in enumerate(sorted(representative_anomalies.items())):
        safe_name = "".join([c for c in anom_name if c.isalnum() or c in (' ', '_', '-')]).strip()
        folder_name = f"{safe_name}"
        
        scenarios.append({
            "folder_name": folder_name,
            "anom_pool": [anom_df], 
            "anomaly_chance": 1.0   
        })

    # --- 3. Execution Loop (Szenarien -> Missionen) ---
    for scenario in scenarios:
        # Hier definieren wir den Ordner für das SZENARIO (z.B. data/INDI/01_degradation_failure)
        scenario_dir = os.path.join(output_base_dir, scenario["folder_name"])
        os.makedirs(scenario_dir, exist_ok=True)
        
        print(f"\n--- Starte Szenario: {scenario['folder_name']} ---")

        # Iteriere durch JEDE Evaluations-Mission
        for mission_df in eval_mission_pool:
            mission_name = mission_df['mission_name'][0]
        
            print(f"  > Benchmarking Mission: {mission_name} ...")
            
            # --- Initialisiere die Env für diese eine Mission ---
            single_mission_pool = [mission_df]
            current_env_kwargs = env_kwargs_base.copy()
            current_env_kwargs.update({
                'mission_pool': [mission_df],
                'is_eval': True,
                'seed': 42,
                'anomaly_pool': scenario["anom_pool"], 
                'anomaly_chance': scenario["anomaly_chance"]
            })
            env = RMT_Ctrl_Env(**current_env_kwargs)

            obs, info = env.reset(seed=42) 
            
            # --- Simulations-Schleife ---
            log_data = [info]
            while True:
                action = np.zeros(env.action_space.shape)
                obs, _, terminated, truncated, info = env.step(action)
                log_data.append(info)
                if terminated or truncated:
                    break
            env.close()

            # --- ERGEBNISSE SPEICHERN (JETZT INNERHALB DER SCHLEIFE!) ---
            results_df = pd.DataFrame(log_data)
            
            # KORREKTUR: Pfad beinhaltet jetzt den scenario_dir UND den Missionsnamen
            # Struktur: data/INDI/00_Baseline/MissionX/
            mission_output_dir = os.path.join(scenario_dir, mission_name)
            os.makedirs(mission_output_dir, exist_ok=True)
            
            csv_path = os.path.join(mission_output_dir, "benchmark_results.csv")
            results_df.to_csv(csv_path, index=False)
            
            # Erstelle die Plots
            # try-except Block, falls Plotting mal schiefgeht, damit nicht alles abbricht
            try:
                plotter = EvaluationPlots(save_dir=mission_output_dir)
                plotter.create_all_plots(results_df)
                
                plot_path = os.path.join(mission_output_dir, "overview_plot.png")
                plot_trajectory_results(results_df, plot_path)
            except Exception as e:
                print(f"    [!] Fehler beim Plotten für {mission_name}: {e}")

            print(f"    -> Gespeichert in: {mission_output_dir}")


if __name__ == '__main__':
    # Das Skript geht davon aus, dass es im `scripts`-Ordner liegt.
    try:
        project_root = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
    except NameError:
        project_root = '.' # Fallback für interaktive Ausführung
        
    # Define the output directory
    output_dir = os.path.join(project_root, 'data', 'INDI_test')

    # --- 1. Lade den Trajektorien-Evaluations-Pool ---
    loader = TrajectoryDataLoader(base_data_dir=os.path.join(project_root, 'data', 'trajectories'), anomaly_base_data_dir = os.path.join(project_root, 'data', 'anomalies'))
    
    all_available_eval_missions = ["Position_Hover", "Benchmark_Ministep", "Benchmark_Response", "Benchmark_Spiral", "Benchmark_Stabilize"] #loader.available_datasets
    eval_missions_config = {name: 1.0 for name in all_available_eval_missions}
    
    _, eval_mission_pool = loader.create_pools(eval_missions_config, load_eval_only=True)
    
    if not eval_mission_pool:
        raise ValueError("Der Evaluations-Pool ist leer! Prüfe 'dataset_definitions'.")
    
    # --- 2. Lade den Anomalie-Evaluations-Pool (nur repräsentative Anomalien) ---
    eval_anomaly_pool_representative = []
    all_available_anomaly_types = loader.available_anomaly_datasets
    
    print(f"Erstelle repräsentativen Anomalie-Pool aus: {sorted(all_available_anomaly_types)}")

    for anomaly_name in sorted(all_available_anomaly_types):
        if anomaly_name in loader.anomaly_datasets:
            all_files_for_type = loader.anomaly_datasets[anomaly_name]
            
            # WICHTIG: Nimm immer nur die erste Datei (Index 0) als Repräsentanten
            if all_files_for_type:
                first_anomaly_file = all_files_for_type[0]
                df = pd.read_csv(first_anomaly_file)
                df['anomaly_name'] = anomaly_name # Stellen Sie sicher, dass der Name gesetzt ist
                eval_anomaly_pool_representative.append(df)
            else:
                print(f"  Warnung: Keine Anomalie-Dateien für Typ '{anomaly_name}' gefunden.")
        else:
            print(f"  Warnung: Anomalie-Typ '{anomaly_name}' nicht im Loader gefunden.")

    # --- 3. Definiere Basis-Umgebungs-Kwargs für INDI ---
    env_kwargs_base = {
        'max_duration': 10.0, # Standarddauer, kann von der Mission überschrieben werden
        'use_unix': platform.system() != "Windows",
        'ctrl_freq': 125, # Standard-Kontrollfrequenz
    }

    run_indi_benchmark(
        output_base_dir=output_dir,
        eval_mission_pool=eval_mission_pool,
        eval_anomaly_pool=eval_anomaly_pool_representative,
        env_kwargs_base=env_kwargs_base
    )