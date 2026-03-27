# Save as: gym_env/utils/dataloader.py

import os
import pandas as pd
import random
from typing import List, Tuple
from typing import List, Tuple, Dict


import logging

logging.basicConfig(format='%(message)s')
logger = logging.getLogger()

class TrajectoryDataLoader:
    """
    Finds, manages, and loads trajectory and anomaly datasets for training.
    This class is initialized outside the Gym environment in the training script.
    """
    def __init__(self, base_data_dir: str = None, anomaly_base_data_dir: str = None, verbose: bool = False):
        """
        Initializes the DataLoader and scans for available datasets.

        Args:
            base_data_dir (str, optional): The path to the main data directory (e.g., 'data/trajectories').
                                           If None, it will try to find it automatically.
            anomaly_base_data_dir (str, optional): The path to the anomaly data directory (e.g., 'data/anomalies').
                                                   If None, it will try to find it automatically.
            verbose (bool): If True, sets logging level to INFO to show all progress messages.
        """

        if verbose:
            logger.setLevel(logging.INFO)
        else:
            logger.setLevel(logging.WARNING)

        if base_data_dir is None:
            self.base_data_dir = self._find_data_directory('trajectories')
        else:
            self.base_data_dir = base_data_dir

        if not os.path.isdir(self.base_data_dir):
            raise FileNotFoundError(f"The specified data directory was not found: {self.base_data_dir}")

        self.datasets = self._scan_data_directory(self.base_data_dir)
        if not self.datasets:
            logging.warning(f"No dataset folders found in directory {self.base_data_dir}.")

        # Anomaly data handling
        if anomaly_base_data_dir is None:
            self.anomaly_base_data_dir = self._find_data_directory('anomalies')
        else:
            self.anomaly_base_data_dir = anomaly_base_data_dir
        
        if not os.path.isdir(self.anomaly_base_data_dir):
            logging.warning(f"The specified anomaly data directory was not found: {self.anomaly_base_data_dir}")
            self.anomaly_datasets = {} # Initialize as empty if not found
        else:
            self.anomaly_datasets = self._scan_data_directory(self.anomaly_base_data_dir, is_anomaly=True)
            if not self.anomaly_datasets:
                logging.warning(f"No anomaly dataset folders found in directory {self.anomaly_base_data_dir}.")

    def _find_data_directory(self, subfolder: str) -> str:
        """Tries to find the data directory automatically by traversing up from the script folder."""
        try:
            # Assumption: This script is in a subdirectory (e.g., gym_env/utils)
            script_dir = os.path.dirname(__file__)
            # Go up from the script folder until we are in the project root
            project_root = os.path.dirname(os.path.dirname(os.path.dirname(script_dir))) # RL-CopterBase
            print('Trajectory loaded from:', project_root)
            return os.path.join(project_root, 'data', subfolder)
        except NameError:
            # Fallback for interactive environments
            return os.path.join('.', 'data', subfolder)
            
    def _scan_data_directory(self, directory: str, is_anomaly: bool = False) -> Dict[str, List[str]]:
        """Scans the base directory and lists all available trajectories per dataset."""
        if is_anomaly:
            logging.info(f"Scanning for anomaly datasets in {directory}...")
        else:
            logging.info(f"Scanning for trajectory datasets in {directory}...")
        
        datasets = {}
        for dataset_name in os.listdir(directory):
            dataset_path = os.path.join(directory, dataset_name)
            if os.path.isdir(dataset_path):
                files = [os.path.join(dataset_path, f) for f in os.listdir(dataset_path) if f.endswith('.csv')]
                if files:
                    datasets[dataset_name] = files
                    logging.info(f"  - Found {'anomaly' if is_anomaly else 'dataset'} '{dataset_name}' with {len(files)} files.")
        return datasets

    @property
    def available_datasets(self) -> list:
        """Returns a list of the names of all found datasets."""
        return list(self.datasets.keys())

    @property
    def available_anomaly_datasets(self) -> list:
        """Returns a list of the names of all found anomaly datasets."""
        return list(self.anomaly_datasets.keys())

    def load_curriculum(self, curriculum_config: dict) -> list:
        """
        Loads trajectories based on a curriculum configuration.

        Args:
            curriculum_config (dict): Defines which datasets to load and what percentage of them.
                                      Example: {'Stabilize_To_Origin': 1.0, 'Hover_And_Switch': 0.4}

        Returns:
            list: A list of loaded pandas.DataFrames.
        """
        all_loaded_trajectories = []
        logging.info("\n--- Loading data according to curriculum ---")
        for dataset_name, percentage in curriculum_config.items():
            if dataset_name not in self.datasets:
                logging.warning(f"  - Dataset '{dataset_name}' in curriculum but not found. Skipping.")
                continue

            all_files = self.datasets[dataset_name]
            num_to_load = int(len(all_files) * percentage)
            files_to_load = random.sample(all_files, num_to_load)
            
            logging.info(f"  - Loading {num_to_load}/{len(all_files)} trajectories from '{dataset_name}'...")
            
            for f in files_to_load:
                all_loaded_trajectories.append(pd.read_csv(f))
                
        if not all_loaded_trajectories:
            logging.warning("No trajectories were loaded. Check your curriculum config and data folder.")
            
        logging.info(f"--- Total trajectories loaded: {len(all_loaded_trajectories)} ---")
        return all_loaded_trajectories
    
    def load_anomaly_pool(self, anomaly_config: dict) -> List[pd.DataFrame]:
        """
        Loads anomaly datasets based on a configuration.

        Args:
            anomaly_config (dict): Defines which anomaly datasets to load and what percentage of them.
                                   Example: {'static_failure': 1.0, 'sudden_failure_single': 0.5}

        Returns:
            List[pd.DataFrame]: A list of loaded pandas.DataFrames containing anomaly time series.
        """
        all_loaded_anomalies = []
        logging.info("\n--- Loading anomaly data according to configuration ---")
        for dataset_name, percentage in anomaly_config.items():
            if dataset_name not in self.anomaly_datasets:
                logging.warning(f"  - Anomaly dataset '{dataset_name}' in config but not found. Skipping.")
                continue

            all_files = self.anomaly_datasets[dataset_name]
            num_to_load = int(len(all_files) * percentage)
            files_to_load = random.sample(all_files, num_to_load)
            
            logging.info(f"  - Loading {num_to_load}/{len(all_files)} anomaly files from '{dataset_name}'...")
            
            for f in files_to_load:
                df = pd.read_csv(f)
                df['anomaly_name'] = dataset_name # Add anomaly_name for identification
                all_loaded_anomalies.append(df)
                
        if not all_loaded_anomalies:
            logging.warning("No anomaly data was loaded. Check your anomaly config and data folder.")
            
        logging.info(f"--- Total anomaly files loaded: {len(all_loaded_anomalies)} ---")
        return all_loaded_anomalies

    def create_pools(self, curriculum_config: dict, load_eval_only: bool = False) -> Tuple[List[pd.DataFrame], List[pd.DataFrame]]:
        """
        Creates separate training and evaluation pools based on a curriculum configuration.

        Args:
            curriculum_config (dict): Defines which datasets to load and what percentage of them.
                                      Example: {'Stabilize_To_Origin': 1.0, 'Hover_And_Switch': 0.4}
            load_eval_only (bool): If True, only the evaluation pool will be populated.

        Returns:
            Tuple[List[pd.DataFrame], List[pd.DataFrame]]: A tuple containing (train_pool, eval_pool).
        """
        train_pool = []
        eval_pool = []
        logging.info("\n--- Creating Train and Eval Pools according to curriculum ---")
        
        for dataset_name, percentage in curriculum_config.items():
            if dataset_name not in self.datasets:
                logging.warning(f"  - Dataset '{dataset_name}' not found. Skipping."); continue

            all_files = self.datasets[dataset_name]
            eval_file = all_files[0]
            train_files = all_files[1:]

            # 1. Fill Eval-Pool
            # logging.info(f"  - Adding eval trajectory from '{dataset_name}' to Eval Pool.")
            if os.path.exists(eval_file):
                df_eval = pd.read_csv(eval_file)
                df_eval['mission_name'] = dataset_name
                eval_pool.append(df_eval)
            else:
                logging.warning(f"  - Eval file for '{dataset_name}' not found at '{eval_file}'.")

            # 2. Fill Train-Pool
            if not load_eval_only:
                if not train_files: continue
                # Load a percentage of the available training files
                num_to_load = max(1, int(len(train_files) * percentage))
                files_to_load = random.sample(train_files, num_to_load)
                
                # logging.info(f"  - Loading {num_to_load}/{len(train_files)} trajectories from '{dataset_name}' into Train Pool.")
                for f in files_to_load:
                    df_train = pd.read_csv(f)
                    df_train['mission_name'] = dataset_name
                    train_pool.append(df_train)
                
        if not train_pool and not load_eval_only:
            logging.warning("Train Pool is empty.")
        if not eval_pool: 
            logging.warning("Eval Pool is empty.")
            
        logging.info(f"--- Pools created: {len(train_pool)} training missions, {len(eval_pool)} evaluation missions ---")
        return train_pool, eval_pool