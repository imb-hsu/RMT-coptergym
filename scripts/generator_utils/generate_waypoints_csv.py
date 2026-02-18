import numpy as np
import os
import pandas as pd

# --- 1. KONFIGURATION ---
FIELD_NAMES = ['time', 'pos_x', 'pos_y', 'pos_z', 'vel_x', 'vel_y', 'vel_z', 
               'vel_limit_x', 'vel_limit_y', 'vel_limit_z', 
               'rpy_x', 'rpy_y', 'rpy_z', 'thrust']
OUTPUT_BASE_DIR = 'data'
ROUND_DIGITS = 4

# --- NEU: Globale Kompatibilitäts-Flagge ---
# Wenn True, werden alle Geschwindigkeitslimits auf 2 m/s begrenzt und
# die Startgeschwindigkeiten werden entsprechend gekappt, um dem INDI-Controller zu entsprechen.
FORCE_INDI_COMPATIBILITY = True

DEFAULT_INITIAL_STATE = {
    'time': 0.0,
    'pos_x': 0.0, 'pos_y': 0.0, 'pos_z': -10.0,
    'vel_x': 0.0, 'vel_y': 0.0, 'vel_z': 0.0,
    'vel_limit_x': 2.0, 'vel_limit_y': 2.0, 'vel_limit_z': 2.0,
    'rpy_x': 0.0, 'rpy_y': 0.0, 'rpy_z': 0.0,
    'thrust': 930.0
}
GLOBAL_BOUNDS = {
    'time': (0.0, 10.0), 'pos': ((-40, 40), (-40, 40), (-50, 0)), 'vel': ((-12, 12), (-12, 12), (-12, 12)),
    'vel_limit': ((2, 2), (2, 2), (2, 2)), 'rpy': ((-90, 90), (-90, 90), (-180, 180)), 'thrust': (0, 2100)
}

# --- 2. DATASET DEFINITIONS ---
DATASET_CONFIGS = [
    {
        'name': 'Benchmark_Stabilize',
        'max_waypoints': 2, 'num_trajectories': 1,
        'params': [],
        'eval_trajectory': [
            # Start: Versetzt, Schnell, Schief
            {'time': 0.0, 'pos': (2, 2, -8),  'vel': (2, 2, 2), 'rpy': (-20, 20, 0), 'vel_limit': (2,2,2)},
            # Ziel: Hovern bei (0,0,-10). Zeit None = Open End (bis Timeout/Success)
            {'time': None, 'pos': (0, 0, -10), 'vel': (0,0,0), 'rpy': (0,0,0)}
        ]
    },
    {
        'name': 'Benchmark_Spiral',
        'max_waypoints': 5, 'num_trajectories': 1,
        'params': [], # Nur eval_trajectory
        'eval_trajectory': [
            #{'time': i * 0.85,
            # 'pos': (3 * np.sin(i * np.pi / 3), 1.5 * np.sin(i * np.pi / 1.5), -10 + np.sin(i*np.pi/5)),             
            # 'vel': (0,0,0), 'rpy': (0,0,0), 'vel_limit': (5,5,5)
            #} for i in range(11)
            {'pos': (0, 0, -15), 'vel': (0, 0, 0), 'rpy': (0,0,0), 'vel_limit': (2,2,2)},
            {'pos': (0.5, 0.5, -15.5), 'vel': (0, 0, 0), 'rpy': (0,0,0)},
            {'pos': (1, 0, -16), 'vel': (0, 0, 0), 'rpy': (0,0,0)},
            {'pos': (0.5, -0.5, -16.5), 'vel': (0, 0, 0), 'rpy': (0,0,0)},
            {'pos': (0, 0, -17), 'vel': (0, 0, 0), 'rpy': (0,0,0)},
        ]
    },
    {
        'name': 'Benchmark_Response',
        'max_waypoints': 8, 'num_trajectories': 1,
        'params': [], # Nur eval_trajectory
        'eval_trajectory': [
            {'time': 0.0, 'pos': (0, 0, -15), 'vel': (0, 1, 0), 'rpy': (0,0,0), 'vel_limit': (2,2,2)},
            {'time': 0.1, 'pos': (0.5, 0.0, -15), 'vel': (0,0,0), 'rpy': (0,0,0)},
            {'time': 1.5, 'pos': (0.75, 0.5,-15), 'vel': (0,0,0), 'rpy': (0,0,0)},
            {'time': 3,   'pos': (1.0, 0.0,-15), 'vel': (0,0,0), 'rpy': (0,0,0)},
            {'time': 4.5, 'pos': (1.25, 0.5,-15), 'vel': (0,0,0), 'rpy': (0,0,0)},
            {'time': 6.0, 'pos': (1.5, 0.0,-15), 'vel': (0,0,0), 'rpy': (0,0,0)},
            {'time': 7.5, 'pos': (1.75, 0.5,-15), 'vel': (0,0,0), 'rpy': (0,0,0)},
            {'time': 9,   'pos': (2.0, 0.0,-15), 'vel': (0,0,0), 'rpy': (0,0,0)},

        ]
    },
    {
        'name': 'Benchmark_Ministep',
        'max_waypoints': 7, 'num_trajectories': 1,
        'params': [],
        'eval_trajectory': [
            # Start
            {'pos': (0, 0, -20), 'vel': (0,0,0), 'rpy': (0,0,0), 'vel_limit': (2,2,2)},
            # Treppe runter und zur Seite
            {'pos': (0.0, -0.25, -20.25), 'vel': (0,0,0), 'rpy': (0,0,0)},
            {'pos': (0.25, -0.25, -20), 'vel': (0,0,0), 'rpy': (0,0,0)},
            {'pos': (-0.25, -0.5, -20.25), 'vel': (0,0,0), 'rpy': (0,0,0)},
            {'pos': (-0.25, -0.75, -20), 'vel': (0,0,0), 'rpy': (0,0,0)},
            {'pos': (-0.0, -0.75, -19.75), 'vel': (0,0,0), 'rpy': (0,0,0)},
            {'pos': (0.0, -1, -20), 'vel': (0,0,0), 'rpy': (0,0,0)},

        ]
    },
    {
        'name': 'Position_Hover',
        'max_waypoints': 2, 'num_trajectories': 100,
        'params': [
            {'pos': {'initial': ((-5, 5), (-5, 5), (-15, -5))}, 'vel': {'initial': ((-0, 0), (-0, 0), (-0, 0))}, 'rpy': {'initial': ((-2, 2), (-2, 2), (-2, 2))}, 'vel_limit': {'initial': ((1,4),(1,4),(1,4))}},
            {'time': None, 'pos': 'hold', 'vel': {'target': np.zeros(3)}, 'rpy': {'target': np.zeros(3)}}
        ],
        'eval_trajectory': [
            {'time': 0.0, 'pos': (0, -0, -10), 'vel': (0, 0, 0), 'rpy': (0, 0, 0), 'vel_limit': (2,2,2)},
            {'pos': (0, 0, -10), 'vel': (0,0,0), 'rpy': (0,0,0), 'vel_limit': (2,2,2)}
        ]
    },
    {
        'name': 'Position_To_Origin',
        'max_waypoints': 2, 'num_trajectories': 500,
        'params': [
            {'pos': {'initial': ((-5, 5), (-5, 5), (-15, -5))}, 'vel': {'initial': ((-5, 5), (-5, 5), (-5, 5))}, 'rpy': {'initial': ((-15, 15), (-15, 15), (-15, 15))}, 'vel_limit': {'initial': ((1,4),(1,4),(1,4))}},
            {'time': None, 'pos': {'target': (0, 0, -10)}, 'vel': {'target': np.zeros(3)}, 'rpy': {'target': np.zeros(3)}}
        ],
        'eval_trajectory': [
            {'time': 0.0, 'pos': (5, -5, -5), 'vel': (4, 2, 2), 'rpy': (15, -15, 90), 'vel_limit': (2,2,2)},
            {'pos': (0, 0, -10), 'vel': (0,0,0), 'rpy': (0,0,0), 'vel_limit': (2,2,2)}
        ]
    },
    {
        'name': 'Position_Switch', 
        'max_waypoints': 3, 'num_trajectories': 500,
        'params': [
            {'pos': {'initial': ((-5,5),(-5,5),(-20,-5))}, 'vel': {'initial': ((-0.5,0.5),(-0.5,0.5),(-0.5,0.5))}},
            {'time': {'step': (2.0, 4.0)}, 'pos': 'hold', 'vel': {'target': np.zeros(3)}, 'rpy': {'target': np.zeros(3)}},
            {'time': {'step': (3.0, 5.0)}, 'pos': {'step': (2.0, 8.0)},'vel': {'target': np.zeros(3)}, 'rpy': {'target': np.zeros(3)}}
        ],
        'eval_trajectory': [
            {'pos': (0,0,-10), 'vel': (1, -1, 0), 'vel_limit': (3,3,3)},
            {'time': 3.0, 'pos': (0,0,-10), 'vel': (0,0,0), 'rpy': (0,0,0)},
            {'time': 7.0, 'pos': (2,2,-12), 'vel': (0,0,0), 'rpy': (0,0,0)}
        ]
    },
    {
        'name': 'Position_Square', 
        'max_waypoints': 4, 'num_trajectories': 500,
        'params': [
            {'pos': {'initial': ((0,0),(0,0),(-12,-10))}, 'vel': {'initial': ((-0.0,0.0),(-0.0,0.0),(-0.0,0.0))}, 'rpy': {'initial': ((-0, 0), (-0, 0), (-0, 0))}},
            {'time': None, 'pos': {'target': ((2,6), (0,0), (-12,-10))}, 'vel': {'target': np.zeros(3)}, 'rpy': {'target': np.zeros(3), 'vel_limit': (2,2,2)}},
            {'time': None, 'pos': {'target': ((2,6), (2,6), (-12,-10))}, 'vel': {'target': np.zeros(3)},'rpy': {'target': np.zeros(3)} },
            {'time': None, 'pos': {'target': ((0,0), (2,6), (-12,-10))}, 'vel': {'target': np.zeros(3)}, 'rpy': {'target': np.zeros(3)}}
        ],
        'eval_trajectory': [
            {'pos': (0,0,-10), 'vel': (0, 0, 0), 'vel_limit': (3,3,3)},
            {'time': 3.0, 'pos': (4,0,-11), 'vel': (0,0,0), 'rpy': (0,0,0)},
            {'time': 3.0, 'pos': (4,4,-12), 'vel': (0,0,0), 'rpy': (0,0,0)},
            {'time': 7.0, 'pos': (0,4,-11), 'vel': (0,0,0), 'rpy': (0,0,0)}
        ]
    },
    {
        'name': 'Position_Long_Range',
        'max_waypoints': 5, 'num_trajectories': 500,
        'params': [
            {'pos': {'initial': ((-10,10),(-10,10),(-30,-20))}, 'vel_limit': {'initial': ((6,10),(6,10),(6,10))}, 'rpy': {'initial': ((-20, 20), (-20, 20), (-45, 45))}},
            {'time': None, 'pos': {'step': (8.0, 15.0)}, 'vel': {'target': (0,0,0)}, 'rpy':{'target': (0,0,0)}},
            {'time': None, 'pos': {'step': (8.0, 15.0)}},
            {'time': None, 'pos': {'step': (8.0, 15.0)}},
            {'time': None, 'pos': {'step': (8.0, 15.0)}}
        ],
        'eval_trajectory': [
            {'time': 0.0, 'pos': (0,0,-20), 'vel': (0,0,0), 'rpy': (-5,-5,0), 'vel_limit': (8,8,8)},
            {'pos': (7,0,-15), 'vel': (0,0,0), 'rpy': (0,0,0), 'vel_limit': (8,8,8)},
            {'pos': (10,5,-20), 'rpy': (0,0,0), 'vel': (0,0,0)},
            {'pos': (0,-5,-25), 'rpy': (0,0,0), 'vel': (0,0,0)},
            {'pos': (0,0,-10), 'rpy': (0,0,0), 'vel': (0,0,0)}
        ]
    },
    {
        'name':  'Position_Mission',
        'max_waypoints':    6, 'num_trajectories': 500,
        'params': [
            # WP1: Initial random position
            {'pos': {'initial': ((-2,2),(-2,2),(-12,-8))}, 'vel_limit': {'initial': (6,10)}, 'rpy': {'initial': ((0, 0), (0, 0), (-90, 90))}},
            # WP2: Step to a new position
            {'time': None, 'pos': {'step': (5.0, 8.0)}, 'vel': {'target': np.zeros(3)}, 'rpy': {'target': np.zeros(3)}},
            # WP3: Step to another position with a lower velocity limit
            {'time': None, 'pos': {'step': (1.0, 3.0)}, 'vel_limit': {'target': (1,3)}, 'vel': {'target': (0,0,0)}},
            {'time': None, 'pos': {'step': (1.0, 3.0)}, 'vel_limit': {'target': (1,3)}, 'vel': {'target': (0,0,0)}},
            {'time': None, 'pos': {'step': (1.0, 3.0)}, 'vel_limit': {'target': (1,3)}, 'vel': {'target': (0,0,0)}},
            # WP5: Return to the starting position
            {'time': None, 'pos': {'return': True}, 'vel': {'target': np.zeros(3)}, 'rpy': {'target': np.zeros(3)}, 'vel_limit': {'initial': (6,10)}}
        ],
        'eval_trajectory': [
            {'time': 0.0, 'pos': (0,0,-10), 'vel': (0,0,0), 'rpy': (0,0,90), 'vel_limit': (8,8,8)},
            {'pos': (12,0,-15), 'vel': (0,0,0), 'rpy': (0,0,0), 'vel_limit': (8,8,8)},
            {'pos': (13,1,-16), 'vel': (0,0,0), 'rpy': (0,0,0), 'vel_limit': (1,1,1)},
            {'pos': (12,-1,-15), 'vel': (0,0,0), 'rpy': (0,0,0), 'vel_limit': (2,2,2)},
            {'pos': (12,-2,-17), 'vel': (0,0,0), 'rpy': (0,0,0), 'vel_limit': (1,1,1)},
            {'pos': (0,0,-10), 'vel': (0,0,0), 'rpy': (0,0,0), 'vel_limit': (8,8,8)}
        ]
    },
    {
        'name': 'Velocity_Stabilize',
        'max_waypoints': 2, 'num_trajectories': 500,
        'params': [
            {'pos': {'initial': ((-5,5),(-5,5),(-15,-5))}, 'vel': {'initial': ((-5,5),(-5,5),(-2,2))}, 'rpy': {'initial': ((-15,15),(-15,15),(0,0))}},
            {'time': None, 'vel': {'target': np.zeros(3)}, 'rpy': {'target': np.zeros(3)}}
        ],
        'eval_trajectory': [
            {'time': 0.0, 'pos': (0,0,-10), 'vel': (3, -2, 1), 'rpy': (15,15,0), 'vel_limit': (5,5,5)},
            {'time': None, 'vel': (0, 0, 0), 'rpy': (0,0,0), 'vel_limit': (5,5,5)},
        ]
    },
    {
        'name': 'Velocity_StepSequence',
        'max_waypoints': 4, 'num_trajectories': 500,
        'params': [
            {'pos': {'initial': ((-5,5),(-5,5),(-25,-10))},'vel_limit': {'initial': (5,10)}, 'vel': {'initial': ((-2,2),(-2,2),(-1,1))}, 'rpy': {'initial': ((-15,15),(-15,15),(0,0)) }},
            {'time': {'target': 0.0}, 'vel': {'step': (2, 5)}, 'rpy': {'target': np.zeros(3)}},
            {'time': {'step': (2.0, 4.0)}, 'vel': {'step': (2, 5)}},
            {'time': {'step': (2.0, 4.0)}, 'vel': {'step': (2, 5)}}
        ],
        'eval_trajectory': [
            {'time': 0.0, 'pos': (0,0,-10), 'vel': (2, -1, 1), 'rpy': (20,-20,0), 'vel_limit': (6,6,6)},
            {'time': 0.0, 'vel': (2, 0, 0), 'rpy': (0,0,0), 'vel_limit': (6,6,6)},
            {'time': 4.0, 'vel': (1, 1, 0), 'rpy': (0,0,0), 'vel_limit': (6,6,6)},
            {'time': 6.0, 'vel': (-1, -1, 0), 'rpy': (0,0,0), 'vel_limit': (6,6,6)},
        ]
    },
    {
        'name': 'Velocity_Jump1',
        'max_waypoints': 3, 'num_trajectories': 250,
        'params': [
            {'pos': {'initial': ((-5,5),(-5,5),(-25,-10))},'vel': {'initial': ((-5,0),(-5,0),(-5,0))}, 'vel_limit': {'initial': (5,10)}, 'rpy': {'initial': ((-15,15),(-15,15),(0,0))}},
            {'time': {'step': (2.0, 4.0)}, 'vel': {'target': ((1,5),(1,5),(1,5))}, 'rpy': {'target': np.zeros(3)}},
            {'time': {'step': (3.0, 5.0)}, 'vel': {'target': ((-5,-1),(-5,-1),(-5,-1))}}
        ],
        'eval_trajectory': [
            {'time': 0.0, 'pos': (0,0,-10), 'vel': (-5, 0, 0), 'rpy': (20,-20,0), 'vel_limit': (8,8,8)},
            {'time': 4.0, 'vel': (5, 0, 0), 'rpy': (0,0,0), 'vel_limit': (8,8,8)},
            {'time': 8.0, 'vel': (-2, -2, -2), 'rpy': (0,0,0), 'vel_limit': (8,8,8)},
        ]
    },
    {
        'name': 'Velocity_Jump2',
        'max_waypoints': 3, 'num_trajectories': 250,
        'params': [
            {'pos': {'initial': ((-5,5),(-5,5),(-35,-15))},'vel': {'initial': ((-5,5),(-5,5),(0,0))}, 'vel_limit': {'initial': (5,10)}, 'rpy': {'initial': ((-15,15),(-15,15),(0,0))}},
            {'time': {'step': (2.0, 4.0)}, 'vel': {'target': ((-5,5),(0,0),(-2,2))}, 'rpy': {'target': np.zeros(3)}},
            {'time': {'step': (3.0, 5.0)}, 'vel': {'target': ((0,0),(-5,5),(-5,5))}}
        ],
        'eval_trajectory': [
            {'time': 0.0, 'pos': (0,0,-20), 'vel': (1, 1, 0), 'rpy': (20,-20,0), 'vel_limit': (8,8,8)},
            {'time': 4.0, 'vel': (2, 0, 2), 'rpy': (0,0,0), 'vel_limit': (8,8,8)},
            {'time': 8.0, 'vel': (0, -2, -5), 'rpy': (0,0,0), 'vel_limit': (8,8,8)},
        ]
    },
    {
        'name': 'Velocity_Dynamic',
        'max_waypoints': 25, 'num_trajectories': 250,
        'params': [
            {'pos':  {'initial': ((-5,5),(-5,5),(-35,-15))},'vel': {'initial': ((-5,5),(-5,5),(0,0))}, 'rpy': {'initial': ((-15,15),(-15,15),(0,0))}, 'vel_limit': {'initial': (2,5)}}
        ] + [
            {'time': {'step': (0.3, 0.4)}, 'vel': {'step': (0, 1)}, 'rpy': {'target': np.zeros(3)}}
            for i in range(24)
        ],
        'eval_trajectory': [
            {'time': 0.0, 'pos': (0,0,-10), 'vel': (0, 3.0, 0), 'rpy': (0,0,0), 'vel_limit': (4,4,4)}
        ] + [
            {'time': (i + 1) * 0.4,
             'vel': (3 * np.sin((i + 1) * 0.4), 3 * np.cos((i + 1) * 0.4), 5 * np.sin((i + 5) * 0.4)),
             'vel_limit': (4,4,4), 'rpy': (0,0,0)}
            for i in range(24)
        ]
    }
]

# --- 3. HELFERFUNKTIONEN ---
def _get_random_value(config):
    if config is None: return np.nan
    if isinstance(config, (tuple, list)):
        if config and isinstance(config[0], (tuple, list)): return np.array([np.random.uniform(b[0], b[1]) for b in config])
        elif len(config) == 2 and all(isinstance(i, (int, float)) for i in config): return np.random.uniform(config[0], config[1])
        else: return np.array(config)
    return config

def generate_random_unit_vector(dims=3):
    vec = np.random.randn(dims)
    return vec / (np.linalg.norm(vec) + 1e-9)

# --- 4. DER KERN-GENERATOR (VEREINFACHT UND ROBUST) ---
def generate_trajectory_data(waypoint_definitions, max_waypoints):
    if not waypoint_definitions: return []

    # --- Initialzustand (Roh-Werte) ---
    raw_waypoints = []
    initial_rules = waypoint_definitions[0]
    initial_wp = {}
    for field, command in initial_rules.items():
        if 'initial' in command:
            initial_wp[field] = _get_random_value(command['initial'])
    raw_waypoints.append(initial_wp)

    last_wp_for_calc = initial_wp.copy()
    
    # --- Ziel-Wegpunkte (Roh-Werte) ---
    for i in range(1, max_waypoints):
        rules_index = min(i, len(waypoint_definitions) - 1)
        rules = waypoint_definitions[rules_index]
        new_values = {}
        for field, command in rules.items():
            value_to_set = np.nan
            if command == 'hold': value_to_set = last_wp_for_calc.get(field)
            elif isinstance(command, dict):
                if 'return' in command and command['return']: value_to_set = initial_wp.get(field)
                elif 'target' in command: value_to_set = _get_random_value(command['target'])
                elif 'step' in command:
                    last_val = last_wp_for_calc.get(field, 0.0)
                    step = _get_random_value(command['step'])
                    if isinstance(last_val, np.ndarray):
                        value_to_set = last_val + generate_random_unit_vector(len(last_val)) * step
                    else:
                        value_to_set = last_val + step if field == 'time' else last_val + np.random.choice([-1, 1]) * step
            else: value_to_set = _get_random_value(command)

            if value_to_set is None: value_to_set = np.nan
            if not np.all(np.isnan(value_to_set)):
                new_values[field] = value_to_set
        
        raw_waypoints.append(new_values)
        last_wp_for_calc.update(new_values)
        
    return raw_waypoints

# --- 5. FINALE VERARBEITUNGSFUNKTION (mit korrekter Konfliktlösung) ---
def process_and_flatten_trajectory(raw_waypoints):
    if not raw_waypoints: return []
    processed_wps = []
    
    # --- Hilfsfunktion für robuste NaN-Prüfung ---
    def is_valid(value):
        if value is None: return False
        if isinstance(value, (np.ndarray, list, tuple)):
            return not np.all(np.isnan(value))
        return not np.isnan(value)

    # 1. Initialzustand verarbeiten
    first_wp_flat = DEFAULT_INITIAL_STATE.copy()
    raw_first_wp = {k: v for k, v in raw_waypoints[0].items() if is_valid(v)}
    
    # --- NEU: Logik für INDI-Kompatibilität ---
    # Diese Logik wird jetzt VOR der Konfliktlösung angewendet, um sicherzustellen,
    # dass die Limits korrekt sind, bevor die Geschwindigkeiten angepasst werden.
    if FORCE_INDI_COMPATIBILITY:
        if 'vel' in raw_first_wp:
            raw_first_wp['vel'] = np.array(raw_first_wp['vel'])
            vel_mag = np.linalg.norm(raw_first_wp['vel'])
            if vel_mag > 2.0:
                raw_first_wp['vel'] = raw_first_wp['vel'] * (2.0 / vel_mag)
        # Setze das Geschwindigkeitslimit IMMER hart auf 2.0, unabhängig von den Parametern.
        raw_first_wp['vel_limit'] = np.full(3, 2.0)

    initial_vel = raw_first_wp.get('vel')
    # Korrektur: Hole den generierten vel_limit-Wert. Wenn es ein Skalar ist, erstelle ein 3D-Array.
    # Fallback auf den Default-Wert, falls nichts generiert wurde.
    vl_val_raw = raw_first_wp.get('vel_limit', DEFAULT_INITIAL_STATE['vel_limit_x'])
    vl_val = np.full(3, vl_val_raw) if np.isscalar(vl_val_raw) else np.array(vl_val_raw)
    
    if initial_vel is not None:
        vel_mag = np.linalg.norm(initial_vel)
        # Nimm den ersten Wert des Limits für den Vergleich (Annahme: isotrop)
        limit_mag = vl_val[0]
        if vel_mag > limit_mag:
            new_limit = np.ceil(vel_mag)
            #print(f"  -> Konflikt im Start: vel_mag ({vel_mag:.2f}) > vel_lim ({limit_mag:.2f}). Neues vel_limit: {new_limit}")
            vl_val = np.full(3, new_limit, dtype=float)
    raw_first_wp['vel_limit'] = vl_val

    for key, val in raw_first_wp.items():
        if isinstance(val, (np.ndarray, list, tuple)):
            axes = ['x', 'y', 'z'] # Always use x, y, z for consistency
            for i, axis in enumerate(axes): first_wp_flat[f'{key}_{axis}'] = float(val[i])
        else: first_wp_flat[key] = float(val)
    processed_wps.append(first_wp_flat)

    # 2. Ziel-Wegpunkte verarbeiten
    for i in range(1, len(raw_waypoints)):
        next_wp_flat = {field: np.nan for field in FIELD_NAMES}
        last_processed_wp = processed_wps[-1]
        raw_current_wp = {k: v for k, v in raw_waypoints[i].items() if is_valid(v)}
        
        for axis in ['x', 'y', 'z']:
            next_wp_flat[f'vel_limit_{axis}'] = last_processed_wp[f'vel_limit_{axis}']

        # Runden des vel_limit, falls es neu gesetzt wird
        if 'vel_limit' in raw_current_wp:
            vl = raw_current_wp['vel_limit']
            raw_current_wp['vel_limit'] = np.ceil(vl) if isinstance(vl, (np.ndarray, list, tuple)) else np.ceil(vl)

        if FORCE_INDI_COMPATIBILITY:
            raw_current_wp['vel_limit'] = np.full(3, 2.0)

        for key, val in raw_current_wp.items():
            if isinstance(val, (np.ndarray, list, tuple)):
                axes = ['x', 'y', 'z'] # Always use x, y, z for consistency
                for j, axis in enumerate(axes): next_wp_flat[f'{key}_{axis}'] = float(val[j])
            else: next_wp_flat[key] = float(val)

        vel = np.array([next_wp_flat.get('vel_x', np.nan), next_wp_flat.get('vel_y', np.nan), next_wp_flat.get('vel_z', np.nan)])
        limit = next_wp_flat['vel_limit_x']
        if not np.any(np.isnan(vel)):
            vel_mag = np.linalg.norm(vel)
            if vel_mag > limit:
                clipped_vel = vel * (limit / vel_mag)
                next_wp_flat['vel_x'], next_wp_flat['vel_y'], next_wp_flat['vel_z'] = clipped_vel
        processed_wps.append(next_wp_flat)
                
    return processed_wps


def generate_raw_waypoints(waypoint_definitions, max_waypoints):
    if not waypoint_definitions: return []
    initial_rules = waypoint_definitions[0]
    initial_wp = {}
    for field, command in initial_rules.items():
        if 'initial' in command:
            initial_wp[field] = _get_random_value(command['initial'])
    waypoints = [initial_wp]
    last_wp_for_calc = initial_wp.copy()
    for i in range(1, max_waypoints):
        rules_index = min(i, len(waypoint_definitions) - 1)
        rules = waypoint_definitions[rules_index]
        new_values = {}
        for field, command in rules.items():
            value_to_set = np.nan
            if command == 'hold': value_to_set = last_wp_for_calc.get(field)
            elif isinstance(command, dict):
                if 'target' in command: value_to_set = _get_random_value(command['target'])
                elif 'step' in command:
                    last_val = last_wp_for_calc.get(field, 0.0)
                    step = _get_random_value(command['step'])
                    if isinstance(last_val, np.ndarray):
                        value_to_set = last_val + generate_random_unit_vector(len(last_val)) * step
                    else:
                        value_to_set = last_val + step if field == 'time' else last_val + np.random.choice([-1, 1]) * step
            else: value_to_set = _get_random_value(command)
            
            # Hier None explizit zu np.nan konvertieren, falls es durch die Regeln kommt
            if value_to_set is None:
                value_to_set = np.nan

            if not np.all(np.isnan(value_to_set)):
                new_values[field] = value_to_set
        waypoints.append(new_values)
        last_wp_for_calc.update(new_values)
    return waypoints


# --- 6. MAIN SCRIPT & IO ---
def main():
    np.random.seed(42)
    os.makedirs(OUTPUT_BASE_DIR, exist_ok=True)
    
    for config in DATASET_CONFIGS:
        name, num_traj, max_wp = config['name'], config['num_trajectories'], config['max_waypoints']
        
        print(f"\n--- Generating dataset: {name} ({num_traj} trajectories) ---")
        # Assumes this script is in a 'scripts' folder at the project root.
        project_root = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
        dataset_dir = os.path.join(project_root, 'data', 'trajectories', name)
        os.makedirs(dataset_dir, exist_ok=True)
        
        for i in range(num_traj):
            if i == 0 and 'eval_trajectory' in config:
                raw_waypoints = config['eval_trajectory']
            else:
                #raw_waypoints = generate_raw_waypoints(config.get('params', {}), max_wp)
                raw_waypoints = generate_trajectory_data(config.get('params', {}), max_wp)
            
            processed_waypoints = process_and_flatten_trajectory(raw_waypoints)
            if not processed_waypoints: continue
            
            df = pd.DataFrame(processed_waypoints).round(ROUND_DIGITS)
            # Hier korrigieren wir auch die Feldnamen für die Spaltenreihenfolge
            df = df.reindex(columns=FIELD_NAMES)
            
            output_path = os.path.join(dataset_dir, f'trajectory_{i:04d}.csv')
            df.to_csv(output_path, index=False)
            
        print(f"Successfully saved to '{dataset_dir}'")
    print(f"\n--- All datasets successfully generated in '{OUTPUT_BASE_DIR}' ---")

if __name__ == "__main__":
    main()