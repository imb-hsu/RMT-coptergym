# Speichern als: gym_env/utils/dataloader.py

import os
import pandas as pd
import random
from typing import List, Tuple
from typing import List, Tuple, Dict


class TrajectoryDataLoader:
    """
    Findet, verwaltet und lädt Trajektorien- und Anomalie-Datensätze für das Training.
    Diese Klasse wird außerhalb der Gym-Environment im Trainingsskript initialisiert.
    """
    def __init__(self, base_data_dir: str = None, anomaly_base_data_dir: str = None):
        """
        Initialisiert den DataLoader und scannt die verfügbaren Datensätze.

        Args:
            base_data_dir (str, optional): Der Pfad zum Haupt-Datenordner (z.B. 'data/trajectories').
                                           Wenn None, wird versucht, ihn automatisch zu finden.
            anomaly_base_data_dir (str, optional): Der Pfad zum Anomalie-Datenordner (z.B. 'data/anomalies').
                                                   Wenn None, wird versucht, ihn automatisch zu finden.
        """
        if base_data_dir is None:
            self.base_data_dir = self._find_data_directory('trajectories')
        else:
            self.base_data_dir = base_data_dir

        if not os.path.isdir(self.base_data_dir):
            raise FileNotFoundError(f"Das angegebene Datenverzeichnis wurde nicht gefunden: {self.base_data_dir}")

        self.datasets = self._scan_data_directory(self.base_data_dir)
        if not self.datasets:
            print(f"Warnung: Keine Datensatz-Ordner im Verzeichnis {self.base_data_dir} gefunden.")
            # raise FileNotFoundError(f"Keine Datensatz-Ordner im Verzeichnis {self.base_data_dir} gefunden.")

        # Anomaly data handling
        if anomaly_base_data_dir is None:
            self.anomaly_base_data_dir = self._find_data_directory('anomalies')
        else:
            self.anomaly_base_data_dir = anomaly_base_data_dir
        
        if not os.path.isdir(self.anomaly_base_data_dir):
            print(f"Warnung: Das angegebene Anomalie-Datenverzeichnis wurde nicht gefunden: {self.anomaly_base_data_dir}")
            self.anomaly_datasets = {} # Initialize as empty if not found
        else:
            self.anomaly_datasets = self._scan_data_directory(self.anomaly_base_data_dir, is_anomaly=True)
            if not self.anomaly_datasets:
                print(f"Warnung: Keine Anomalie-Datensatz-Ordner im Verzeichnis {self.anomaly_base_data_dir} gefunden.")

    def _find_data_directory(self, subfolder: str) -> str:
        """Versucht, das Datenverzeichnis automatisch zu finden, indem es vom Skriptordner aufsteigt."""
        try:
            # Annahme: Dieses Skript ist in einem Unterverzeichnis (z.B. gym_env/utils)
            script_dir = os.path.dirname(__file__)
            # Gehe vom Skriptordner hoch, bis wir im Projekt-Root sind
            project_root = os.path.dirname(os.path.dirname(os.path.dirname(script_dir))) # RL-CopterBase
            return os.path.join(project_root, 'data', subfolder)
        except NameError:
            # Fallback für interaktive Umgebungen
            return os.path.join('.', 'data', subfolder)
            
    def _scan_data_directory(self, directory: str, is_anomaly: bool = False) -> Dict[str, List[str]]:
        """Scannt das Basisverzeichnis und listet alle verfügbaren Trajektorien pro Datensatz auf."""
        if is_anomaly:
            print(f"Scanning for anomaly datasets in {directory}...")
        else:
            print(f"Scanning for trajectory datasets in {directory}...")
        
        datasets = {}
        for dataset_name in os.listdir(directory):
            dataset_path = os.path.join(directory, dataset_name)
            if os.path.isdir(dataset_path):
                files = [os.path.join(dataset_path, f) for f in os.listdir(dataset_path) if f.endswith('.csv')]
                if files:
                    datasets[dataset_name] = files
                    print(f"  - Found {'anomaly' if is_anomaly else 'dataset'} '{dataset_name}' with {len(files)} files.")
        return datasets

    @property
    def available_datasets(self) -> list:
        """Gibt eine Liste der Namen aller gefundenen Datensätze zurück."""
        return list(self.datasets.keys())

    @property
    def available_anomaly_datasets(self) -> list:
        """Gibt eine Liste der Namen aller gefundenen Anomalie-Datensätze zurück."""
        return list(self.anomaly_datasets.keys())

    def load_curriculum(self, curriculum_config: dict) -> list:
        """
        Lädt Trajektorien basierend auf einer Curriculum-Konfiguration.

        Args:
            curriculum_config (dict): Definiert, welche Datensätze mit welchem Anteil geladen werden sollen.
                                      Beispiel: {'Stabilize_To_Origin': 1.0, 'Hover_And_Switch': 0.4}

        Returns:
            list: Eine Liste von geladenen pandas.DataFrames.
        """
        all_loaded_trajectories = []
        print("\n--- Loading data according to curriculum ---")
        for dataset_name, percentage in curriculum_config.items():
            if dataset_name not in self.datasets:
                print(f"  Warning: Dataset '{dataset_name}' im Curriculum, aber nicht gefunden. Wird übersprungen.")
                continue

            all_files = self.datasets[dataset_name]
            num_to_load = int(len(all_files) * percentage)
            files_to_load = random.sample(all_files, num_to_load)
            
            print(f"  Loading {num_to_load}/{len(all_files)} trajectories from '{dataset_name}'...")
            
            for f in files_to_load:
                all_loaded_trajectories.append(pd.read_csv(f))
                
        if not all_loaded_trajectories:
            print("Warning: No trajectories were loaded. Check your curriculum config and data folder.")
            
        print(f"--- Total trajectories loaded: {len(all_loaded_trajectories)} ---")
        return all_loaded_trajectories
    
    def load_anomaly_pool(self, anomaly_config: dict) -> List[pd.DataFrame]:
        """
        Lädt Anomalie-Datensätze basierend auf einer Konfiguration.

        Args:
            anomaly_config (dict): Definiert, welche Anomalie-Datensätze mit welchem Anteil geladen werden sollen.
                                   Beispiel: {'static_failure': 1.0, 'sudden_failure_single': 0.5}

        Returns:
            List[pd.DataFrame]: Eine Liste von geladenen pandas.DataFrames, die Anomalie-Zeitreihen enthalten.
        """
        all_loaded_anomalies = []
        print("\n--- Loading anomaly data according to configuration ---")
        for dataset_name, percentage in anomaly_config.items():
            if dataset_name not in self.anomaly_datasets:
                print(f"  Warning: Anomaly dataset '{dataset_name}' in config, but not found. Skipping.")
                continue

            all_files = self.anomaly_datasets[dataset_name]
            num_to_load = int(len(all_files) * percentage)
            files_to_load = random.sample(all_files, num_to_load)
            
            print(f"  Loading {num_to_load}/{len(all_files)} anomaly files from '{dataset_name}'...")
            
            for f in files_to_load:
                df = pd.read_csv(f)
                df['anomaly_name'] = dataset_name # Add anomaly_name for identification
                all_loaded_anomalies.append(df)
                
        if not all_loaded_anomalies:
            print("Warning: No anomaly data was loaded. Check your anomaly config and data folder.")
            
        print(f"--- Total anomaly files loaded: {len(all_loaded_anomalies)} ---")
        return all_loaded_anomalies

    def create_pools(self, curriculum_config: dict, load_eval_only: bool = False) -> Tuple[List[pd.DataFrame], List[pd.DataFrame]]:
        """
        Erstellt getrennte Trainings- und Evaluations-Pools basierend auf einer Curriculum-Konfiguration.

        Args:
            curriculum_config (dict): Definiert, welche Datensätze mit welchem Anteil geladen werden sollen.
                                      Beispiel: {'Stabilize_To_Origin': 1.0, 'Hover_And_Switch': 0.4}

        Returns:
            Tuple[List[pd.DataFrame], List[pd.DataFrame]]: Ein Tupel mit (train_pool, eval_pool).
        """
        train_pool = []
        eval_pool = []
        print("\n--- Creating Train and Eval Pools according to curriculum ---")
        
        for dataset_name, percentage in curriculum_config.items():
            if dataset_name not in self.datasets:
                print(f"  Warning: Dataset '{dataset_name}' not found. Skipping."); continue

            all_files = self.datasets[dataset_name]
            eval_file = all_files[0]
            train_files = all_files[1:]

            # 1. Eval-Pool füllen
            # print(f"  - Adding eval trajectory from '{dataset_name}' to Eval Pool.")
            if os.path.exists(eval_file):
                df_eval = pd.read_csv(eval_file)
                df_eval['mission_name'] = dataset_name
                eval_pool.append(df_eval)
            else:
                print(f"  Warning: Eval file for '{dataset_name}' not found at '{eval_file}'.")

            # 2. Train-Pool füllen
            if not load_eval_only:
                if not train_files: continue
                # Load a percentage of the available training files
                num_to_load = max(1, int(len(train_files) * percentage))
                files_to_load = random.sample(train_files, num_to_load)
                
                # print(f"  - Loading {num_to_load}/{len(train_files)} trajectories from '{dataset_name}' into Train Pool.")
                for f in files_to_load:
                    df_train = pd.read_csv(f)
                    df_train['mission_name'] = dataset_name
                    train_pool.append(df_train)
                
        if not train_pool:
            print("Warning: Train Pool is empty.")
        if not eval_pool: print("Warning: Eval Pool is empty.")
            
        print(f"--- Pools created: {len(train_pool)} training missions, {len(eval_pool)} evaluation missions ---")
        return train_pool, eval_pool