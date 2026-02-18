import numpy as np
import os
import pandas as pd

"""
Actuator Faults – Loss of Effectiveness (LoE) Generator

This script generates CSV datasets representing various actuator failure scenarios.
The simulation uses these files to apply a multiplicative loss factor to motor commands.

Scenarios covered:
1. NOM (Nominal): No faults.
2. PLOE (Permanent LoE): Constant loss of effectiveness starting at t=0.
3. ALOE (Abrupt LoE): Sudden loss of effectiveness at a specific timestamp.
4. IAD (Intermittent Actuator Dropout): Short, temporary 100% failures (dropouts).
5. GLOE (Gradual/Progressive LoE): Effectiveness degrades linearly over time.
"""

# Configuration and Dataset Definitions
FIELD_NAMES = ['time'] + [f'motorloss_{i+1}' for i in range(8)]
OUTPUT_BASE_DIR = 'data'
ROUND_DIGITS = 4
SIM_DURATION = 10.0
NUM_STEPS = int(SIM_DURATION * 100)

# The dataset configurations define both the random parameters for training generation
# and specific sequences for deterministic evaluation scenarios.
DATASET_CONFIGS = [
    {
        'name': 'permanent_LoE',
        'num_trajectories': 250,
        'type': 'constant',
        'params': {
            'num_failed_motors': (1, 2),
            'loss_range': (0.25, 0.5)
        },
        # Evaluation: Motor 1 has 25% loss from the start
        'eval_sequence': [
            {'time': 0.0, 'motorloss': [0.25, 0, 0, 0, 0, 0, 0, 0]}
        ]
    },
    {
        'name': 'permanent_LoE_multi',
        'num_trajectories': 250,
        'type': 'constant',
        'params': {
            'num_failed_motors': (3, 5),
            'loss_range': (0.2, 0.5)
        },
        # Evaluation: Mixed losses on multiple motors from the start
        'eval_sequence': [
            {'time': 0.0, 'motorloss': [0.25, 0, 0, 0.2, 0, 0.45, 0, 0]}
        ]
    },
    {
        'name': 'abrupt_LoE',
        'num_trajectories': 250,
        'type': 'sudden',
        'params': {
            'num_failed_motors': 1,
            'failure_time_range': (2.0, 8.0),
            'loss_range': (0.5, 1.0)
        },
        # Evaluation: Normal operation until t=5.0, then Motor 4 fails completely
        'eval_sequence': [
            {'time': 0.0, 'motorloss': [0, 0, 0, 0, 0, 0, 0, 0]},
            {'time': 5.0, 'motorloss': [0, 0, 0, 1.0, 0, 0, 0, 0]}
        ]
    },
    {
        'name': 'abrupt_LoE_multi',
        'num_trajectories': 250,
        'type': 'sudden',
        'params': {
            'num_failed_motors': (2, 3),
            'failure_time_range': (2.0, 7.0),
            'loss_range': (0.5, 1.0)
        },
        # Evaluation: Normal operation until t=5.0, then Motor 4 and 7 fail
        'eval_sequence': [
            {'time': 0.0, 'motorloss': [0, 0, 0, 0, 0, 0, 0, 0]},
            {'time': 5.0, 'motorloss': [0, 0, 0, 0.60, 0, 0, 0.0, 0.80]}
        ]
    },
    {
        'name': 'gradual_LoE',
        'num_trajectories': 250,
        'type': 'degradation',
        'params': {
            'num_failed_motors': 1,
            'start_time_range': (1.0, 3.0),
            'duration_range': (3.0, 6.0),
            'max_loss_range': (0.5, 1.0)
        },
        # Evaluation: Uses parameters to generate a smooth linear degradation profile
        'eval_anomaly': {
            'motor_idx': 7,
            'start_time_range': 2.0,
            'duration_range': 6.0,
            'max_loss_range': 0.75
        }
    },
    {
        'name': 'gradual_LoE_multi',
        'num_trajectories': 250,
        'type': 'degradation',
        'params': {
            'num_failed_motors': 2,
            'start_time_range': (1.0, 3.0),
            'duration_range': (3.0, 6.0),
            'max_loss_range': (0.35, 0.70)
        },
        # Evaluation: Uses parameters to generate a smooth linear degradation profile for motors 1 and 2
        'eval_anomaly': {
            'motor_idx': (1,2),
            'start_time_range': 2.0,
            'duration_range': 6.0,
            'max_loss_range': 0.5
        }
    },
    {
        'name': 'Intermittent_Actuator_Dropout',
        'num_trajectories': 250,
        'type': 'intermittent',
        'params': {
            'num_failed_motors': 1,
            'num_dropouts': (1, 4),
            'dropout_duration_range': (0.3, 2.5),
            'loss_range': 1.0 # Fixed 100% loss for dropouts
        },
        # Evaluation: Sequence of short dropouts on Motor 3
        'eval_sequence': [
            {'time': 0.0,  'motorloss': [0, 0, 0.0, 0, 0, 0, 0, 0]},
            {'time': 2.0,  'motorloss': [0, 0, 0.8, 0, 0, 0, 0, 0]},
            {'time': 2.3,  'motorloss': [0, 0, 0.0, 0, 0, 0, 0, 0]},
            {'time': 4.0,  'motorloss': [0, 0, 0.9, 0, 0, 0, 0, 0]},
            {'time': 4.75, 'motorloss': [0, 0, 0.0, 0, 0, 0, 0, 0]},
            {'time': 6.0,  'motorloss': [0, 0, 1.0, 0, 0, 0, 0, 0]},
            {'time': 7.5,  'motorloss': [0, 0, 0.0, 0, 0, 0, 0, 0]}
        ]
    },
    {
        'name': 'Intermittent_Actuator_Dropout_multi',
        'num_trajectories': 250,
        'type': 'intermittent',
        'params': {
            'num_failed_motors': (2, 4),
            'num_dropouts': (3, 8),
            'dropout_duration_range': (0.3, 2.5),
            'loss_range': 1.0 # Fixed 100% loss for dropouts
        },
        # Evaluation: Alternating dropouts on Motor 1 and Motor 2
        'eval_sequence': [
            {'time': 0.0,  'motorloss': [0.0, 0.0, 0, 0, 0, 0, 0, 0]},
            {'time': 2.0,  'motorloss': [0.8, 0.0, 0, 0, 0, 0, 0, 0]},
            {'time': 2.2,  'motorloss': [0.0, 0.0, 0, 0, 0, 0, 0, 0]},
            {'time': 4.0,  'motorloss': [0.0, 0.9, 0, 0, 0, 0, 0, 0]},
            {'time': 4.3,  'motorloss': [0.0, 0.0, 0, 0, 0, 0, 0, 0]},
            {'time': 6.0,  'motorloss': [0.8, 0.0, 0, 0, 0, 0, 0, 0]},
            {'time': 6.2,  'motorloss': [0.0, 0.0, 0, 0, 0, 0, 0, 0]},
            {'time': 8.0,  'motorloss': [0.0, 0.9, 0, 0, 0, 0, 0, 0]},
            {'time': 8.3,  'motorloss': [0.0, 0.0, 0, 0, 0, 0, 0, 0]}
        ]
    }
]

# Helper Functions
def _get_rand(value_range):
    """Returns a random float within a range or the value itself if scalar."""
    if isinstance(value_range, (tuple, list)):
        return np.random.uniform(value_range[0], value_range[1])
    return value_range

def _get_int_rand(value_range):
    """Returns a random integer within a range or the value itself if scalar."""
    if isinstance(value_range, (tuple, list)):
        return np.random.randint(value_range[0], value_range[1] + 1)
    return int(value_range)

# Core Generator
def generate_anomaly_data(config, time_vector, eval_params=None):
    """
    Generates a single anomaly trajectory based on the provided configuration.
    
    Args:
        config (dict): Configuration dictionary for the anomaly type.
        time_vector (np.array): Array of time steps.
        eval_params (dict, optional): Specific parameters for evaluation (deterministic).
        
    Returns:
        np.array: Matrix of motor loss factors (shape: len(time_vector) x 8).
    """
    motor_loss = np.zeros((len(time_vector), 8))

    # Deterministic generation for evaluation datasets via sequence
    if eval_params and 'eval_sequence' in eval_params:
        sequence = sorted(eval_params['eval_sequence'], key=lambda x: x['time'])
        
        for i, waypoint in enumerate(sequence):
            start_time = waypoint['time']
            # Determine end time: either start of next waypoint or end of simulation
            end_time = sequence[i+1]['time'] if (i + 1) < len(sequence) else SIM_DURATION
            
            mask = (time_vector >= start_time) & (time_vector < end_time)
            motor_loss[mask] = waypoint['motorloss']
            
        # Ensure the final state is set at the end of the simulation
        if sequence:
            motor_loss[-1] = sequence[-1]['motorloss']
            
        return motor_loss

    # --- Random generation logic for training data ---
    params = config['params']
    anomaly_type = config['type']
    num_motors = _get_int_rand(params.get('num_failed_motors', 1))
    failed_motor_indices = np.random.choice(8, num_motors, replace=False)
    
    if anomaly_type == 'constant':
        loss = _get_rand(params['loss_range'])
        motor_loss[:, failed_motor_indices] = loss
        
    elif anomaly_type == 'sudden':
        failure_time = _get_rand(params['failure_time_range'])
        loss = _get_rand(params['loss_range'])
        mask = time_vector >= failure_time
        for idx in failed_motor_indices:
            motor_loss[mask, idx] = np.clip(loss, 0.0, 1.0)
        
    elif anomaly_type == 'degradation':
        # Calculate a linear ramp for degradation
        start_time = _get_rand(params['start_time_range'] if not eval_params else eval_params['start_time_range'])
        duration = _get_rand(params['duration_range'] if not eval_params else eval_params['duration_range'])
        max_loss = _get_rand(params['max_loss_range'] if not eval_params else eval_params['max_loss_range'])
        end_time = start_time + duration
        
        if eval_params and 'motor_idx' in eval_params:
            # Handle both scalar (int) and iterable (list/tuple) motor indices
            m_idx = eval_params['motor_idx']
            target_indices = m_idx if isinstance(m_idx, (list, tuple, np.ndarray)) else [m_idx]
        else:
            target_indices = failed_motor_indices

        # Pre-calculate profile (vectorized)
        loss_profile = np.zeros_like(time_vector)
        ramp_mask = (time_vector >= start_time) & (time_vector < end_time)
        full_mask = (time_vector >= end_time)
        loss_profile[ramp_mask] = (time_vector[ramp_mask] - start_time) / duration * max_loss
        loss_profile[full_mask] = max_loss
        
        for idx in target_indices:
            motor_loss[:, idx] = np.clip(loss_profile, 0.0, 1.0)
                
    elif anomaly_type == 'intermittent':
        num_dropouts = _get_int_rand(params['num_dropouts'])
        for _ in range(num_dropouts):
            duration = _get_rand(params['dropout_duration_range'])
            start_time = np.random.uniform(0, SIM_DURATION - duration)
            loss = _get_rand(params['loss_range'])
            motor_idx = np.random.choice(failed_motor_indices)
            
            start_idx = np.searchsorted(time_vector, start_time)
            end_idx = np.searchsorted(time_vector, start_time + duration)
            motor_loss[start_idx:end_idx, motor_idx] = np.clip(loss, 0.0, 1.0)
            
    return motor_loss


# --- MAIN SCRIPT ---
def main():
    np.random.seed(42)
    time_vector = np.linspace(0, SIM_DURATION, NUM_STEPS)
    
    # Resolve the project root directory relative to this script (assumed to be in 'scripts/')
    project_root = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
    output_root_dir = os.path.join(project_root, OUTPUT_BASE_DIR, 'anomalies')

    for config in DATASET_CONFIGS:
        name, num_traj = config['name'], config['num_trajectories']
        
        print(f"\n--- Generating anomaly set: {name} ({num_traj} trajectories) ---")
        dataset_dir = os.path.join(output_root_dir, name)
        os.makedirs(dataset_dir, exist_ok=True)
        
        for i in range(num_traj):
            current_eval_params = None
            if i == 0:
                if 'eval_sequence' in config:
                    current_eval_params = {'eval_sequence': config['eval_sequence']}
                elif 'eval_anomaly' in config:
                    current_eval_params = config['eval_anomaly']
                
            motor_loss_data = generate_anomaly_data(config, time_vector, eval_params=current_eval_params)
            
            compact_data_rows = []
            rounded_motor_loss_data = np.round(motor_loss_data, ROUND_DIGITS)
            last_state = rounded_motor_loss_data[0]
            compact_data_rows.append({'time': time_vector[0], **{f'motorloss_{j+1}': last_state[j] for j in range(8)}})
            
            for step_idx in range(1, NUM_STEPS):
                current_state = rounded_motor_loss_data[step_idx]
                if not np.array_equal(current_state, last_state):
                    compact_data_rows.append({'time': time_vector[step_idx], **{f'motorloss_{j+1}': current_state[j] for j in range(8)}})
                    last_state = current_state
            
            final_state = rounded_motor_loss_data[-1]
            if not np.array_equal(final_state, last_state):
                 compact_data_rows.append({'time': time_vector[-1], **{f'motorloss_{j+1}': final_state[j] for j in range(8)}})

            df = pd.DataFrame(compact_data_rows, columns=FIELD_NAMES).round(ROUND_DIGITS)
            
            output_path = os.path.join(dataset_dir, f'anomaly_{i:04d}.csv')
            df.to_csv(output_path, index=False)
            
        print(f"Successfully saved to '{dataset_dir}'")
    print(f"\n--- All anomaly sets successfully generated in '{output_root_dir}' ---")

if __name__ == "__main__":
    main()