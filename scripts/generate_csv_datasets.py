import sys
import os
import time

"""
Unified Data Generation Script

This script serves as a single entry point to generate all necessary datasets
for the simulation, including waypoint trajectories and anomaly profiles.

It calls the respective generator scripts in a defined order, providing a
simple and repeatable way to prepare all data.
"""

# To ensure the script can be run from any location and still find the
# necessary modules, we adjust the Python path. We assume the following
# directory structure:
#
# RL-CopterBase/
# |-- scripts/
# |   |-- generate_csv_datasets.py  (this script)
# |   |-- generator_utils/
# |       |-- __init__.py
# |       |-- generate_waypoints_csv.py
# |       |-- generate_anomalies_csv.py
#
from generator_utils import generate_waypoints_csv
from generator_utils import generate_anomalies_csv

def main():
    """Main function to run all data generation scripts sequentially."""
    print("="*80)
    print("--- STARTING UNIFIED DATASET GENERATION ---")
    print("="*80)
    start_time = time.perf_counter()

    print("\n>>> STEP 1: Generating Waypoint Trajectories...")
    generate_waypoints_csv.main()

    print("\n>>> STEP 2: Generating Anomaly CSVs...")
    generate_anomalies_csv.main()

    end_time = time.perf_counter()
    print(f"\n--- UNIFIED DATASET GENERATION COMPLETED in {end_time - start_time:.2f} seconds ---")

if __name__ == "__main__":
    main()