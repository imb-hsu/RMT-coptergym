import pandas as pd
import numpy as np
import ast
import os

def parse_vector_col(series: pd.Series) -> np.ndarray:
    """
    Parses a pandas Series containing string representations of vectors into a numpy array.
    Handles formats like '[1. 2. 3.]' (numpy) and '[1, 2, 3]' (python list).

    Args:
        series (pd.Series): The series to parse.

    Returns:
        np.ndarray: A numpy array of shape (n_rows, n_dims).
    """
    parsed_list = []
    detected_len = None

    for x in series:
        val = None
        if isinstance(x, (list, np.ndarray)):
            val = list(x)
        elif isinstance(x, str):
            x = x.strip()
            try: # Python list style
                val = ast.literal_eval(x)
            except (ValueError, SyntaxError):
                try: # Numpy string style
                    clean_str = x.replace('[', '').replace(']', '').replace('\n', ' ')
                    parts = clean_str.split()
                    if parts:
                        val = [float(p) for p in parts]
                except Exception:
                    val = None
        
        if val is not None and detected_len is None:
            if hasattr(val, '__len__') and len(val) > 0:
                detected_len = len(val)
        
        parsed_list.append(val)

    if detected_len is None:
        detected_len = 3 # Fallback to 3 dimensions
    
    final_data = []
    zero_vec = [0.0] * detected_len
    
    for item in parsed_list:
        if item is None or (hasattr(item, '__len__') and len(item) != detected_len):
            final_data.append(zero_vec)
        else:
            final_data.append(item)
            
    return np.array(final_data)


def calculate_metrics_physics(df, motor_min, motor_range, ctrl_freq=125.0, filename="Unknown", max_duration=10.0, total_waypoints=None):
    """
    Berechnet KPIs. Enthält Debug-Prints, wenn Daten fehlen.
    """
    metrics = {
        'rmse_xyz': 999.0, 
        'rmse_te_xyz': 999.0,
        'rmse_rpy': 999.0,
        'rmse_te_rpy': 999.0,
        'rmse_vel': 999.0,
        'rmse_te_vel': 999.0,
        'energy': 0.0, 
        'motor_jitter': 0.0,
        'omega_jitter': 0.0,
        'flight_time': 0.0,
        'stability': 0.0,
        'max_wp': 0,
        'wcr': 0.0,
        'success': 0.0
    }
    
    if df.empty:
        print(f"[DEBUG] DataFrame leer: {filename}")
        return metrics

    # --- 1. Flugzeit ---
    if 'sim_time' in df.columns:
        metrics['flight_time'] = df['sim_time'].max()
    elif 'time' in df.columns:
        metrics['flight_time'] = df['time'].max()
    else:
        metrics['flight_time'] = len(df) / ctrl_freq

    # --- Stability ---
    # Ratio of flight time to max duration (1.0 = stable/survived)
    metrics['stability'] = min(metrics['flight_time'] / max_duration, 1.0)

    # --- 2. Fortschritt ---
    if 'mission_waypoint_index' in df.columns:
        metrics['max_wp'] = df['mission_waypoint_index'].max()

    # --- Success Check (Pre-Calculation for time-extended RMSE) ---
    if 'eval_metrics' in df.columns:
        valid = df['eval_metrics'].dropna()
        if not valid.empty:
            try:
                last = valid.iloc[-1]
                parsed = ast.literal_eval(last) if isinstance(last, str) else last
                metrics['success'] = float(parsed.get('success', 0.0))
            except: pass
    
    # Fallback: Check 'status' column if success not yet detected (e.g. for INDI or if eval_metrics missing)
    if metrics['success'] < 0.5 and 'status' in df.columns:
        if df['status'].eq('final target reached').any():
            metrics['success'] = 1.0

    # --- 3. RMSE Calculation (XYZ - Position) ---
    diff_xyz = None
    
    # Prio A: Physikalische Position vs. Ziel (Beste Methode)
    if 'agent_pos' in df.columns and 'mission_goal_pos' in df.columns:
        pos_vecs = parse_vector_col(df['agent_pos'])
        ref_vecs = parse_vector_col(df['mission_goal_pos'])
        
        if pos_vecs.shape == ref_vecs.shape:
            diff_xyz = pos_vecs - ref_vecs # N x 3
            
    # Prio B: Error Vektor Spalte
    if diff_xyz is None and 'error_pos' in df.columns:
        diff_xyz = parse_vector_col(df['error_pos'])
        
    # Prio C: Einzelspalten (oft bei RMT)
    if diff_xyz is None and all(c in df.columns for c in ['e_px', 'e_py', 'e_pz']):
        # Construct diff manually
        diff_xyz = df[['e_px', 'e_py', 'e_pz']].values

    if diff_xyz is not None:
        # 3a. Raw RMSE
        mse_xyz = np.mean(np.sum(diff_xyz**2, axis=1))
        metrics['rmse_xyz'] = np.sqrt(mse_xyz)

        # 3b. time-extended RMSE (Penalize Crashes) for XYZ
        metrics['rmse_te_xyz'] = metrics['rmse_xyz'] # Default
        
        if metrics['success'] < 0.5 and metrics['flight_time'] < (max_duration - 0.1):
            missing_steps = int((max_duration - metrics['flight_time']) * ctrl_freq)
            if missing_steps > 0:
                last_error_sq = np.sum(diff_xyz[-1]**2)
                total_sse = np.sum(np.sum(diff_xyz**2, axis=1)) + (missing_steps * last_error_sq)
                total_steps = len(diff_xyz) + missing_steps
                metrics['rmse_te_xyz'] = np.sqrt(total_sse / total_steps)
    else:
        print(f"[DEBUG] Kein XYZ RMSE berechenbar in {os.path.basename(filename)}. Verfügbare Spalten: {[c for c in df.columns if 'pos' in c or 'e_' in c]}")

    # --- 4. RMSE Calculation (RPY - Attitude) ---
    diff_rpy = None
    if 'error_rpy_deg' in df.columns:
        diff_rpy = parse_vector_col(df['error_rpy_deg'])
    
    if diff_rpy is not None:
        mse_rpy = np.mean(np.sum(diff_rpy**2, axis=1))
        metrics['rmse_rpy'] = np.sqrt(mse_rpy)
        metrics['rmse_te_rpy'] = metrics['rmse_rpy'] # Default
        if metrics['success'] < 0.5 and metrics['flight_time'] < (max_duration - 0.1):
            missing_steps = int((max_duration - metrics['flight_time']) * ctrl_freq)
            if missing_steps > 0:
                last_error_sq = np.sum(diff_rpy[-1]**2)
                total_sse = np.sum(np.sum(diff_rpy**2, axis=1)) + (missing_steps * last_error_sq)
                total_steps = len(diff_rpy) + missing_steps
                metrics['rmse_te_rpy'] = np.sqrt(total_sse / total_steps)

    # --- 5. RMSE Calculation (VEL - Velocity) ---
    diff_vel = None
    if 'agent_vel_c' in df.columns and 'mission_goal_vel' in df.columns:
        vel_vecs = parse_vector_col(df['agent_vel_c'])
        ref_vecs = parse_vector_col(df['mission_goal_vel'])
        if vel_vecs.shape == ref_vecs.shape:
            diff_vel = vel_vecs - ref_vecs
    elif 'error_vel_c' in df.columns:
        diff_vel = parse_vector_col(df['error_vel_c'])

    if diff_vel is not None:
        mse_vel = np.mean(np.sum(diff_vel**2, axis=1))
        metrics['rmse_vel'] = np.sqrt(mse_vel)
        metrics['rmse_te_vel'] = metrics['rmse_vel'] # Default
        if metrics['success'] < 0.5 and metrics['flight_time'] < (max_duration - 0.1):
            missing_steps = int((max_duration - metrics['flight_time']) * ctrl_freq)
            if missing_steps > 0:
                last_error_sq = np.sum(diff_vel[-1]**2)
                total_sse = np.sum(np.sum(diff_vel**2, axis=1)) + (missing_steps * last_error_sq)
                total_steps = len(diff_vel) + missing_steps
                metrics['rmse_te_vel'] = np.sqrt(total_sse / total_steps)

    # --- WCR (Waypoint Completion Ratio) ---
    if total_waypoints is not None and total_waypoints > 0:
        metrics['wcr'] = min(metrics['max_wp'] / total_waypoints, 1.0) if metrics['success'] < 0.5 else 1.0

    # --- 6. Jitter (Unruhe/Rauschen) ---
    # Omega Jitter: Wie stark zittern die Winkelgeschwindigkeiten?
    if 'agent_omega' in df.columns:
        omega = parse_vector_col(df['agent_omega'])
        if len(omega) > 1:
            # Wir nutzen die mittlere absolute Differenz als Maß für Hochfrequenz-Zittern
            metrics['omega_jitter'] = np.mean(np.square(np.diff(omega, axis=0))) #abs to square

    # Motor Jitter & Energy
    motors_norm = None
    if 'motor_signal_measured_rps' in df.columns:
        motors = parse_vector_col(df['motor_signal_measured_rps'])
        motors_norm = (motors - motor_min) / motor_range
    elif 'action_cmd' in df.columns:
        motors = parse_vector_col(df['action_cmd'])
        motors_norm = (motors - motor_min) / motor_range
    elif any(c.startswith('cmd_') for c in df.columns):
        cmd_cols = sorted([c for c in df.columns if c.startswith('cmd_')])
        motors = df[cmd_cols].values
        motors_norm = (motors - motor_min) / motor_range

    if motors_norm is not None and len(motors_norm) > 0:
        metrics['energy'] = np.mean(np.square(motors_norm))
        if len(motors_norm) > 1:
            # Motor Jitter: Maß für die Belastung der ESCs/Motoren
            metrics['motor_jitter'] = np.mean(np.square(np.diff(motors_norm, axis=0))) # abs to square
            
    return metrics

def calculate_composite_score_old(df):
    if df.empty: return df
    df = df.copy()
    # Metriken, bei denen kleiner besser ist (Fehler & Jitter)
    cols_to_norm = ['RMSE_TE_XYZ', 'RMSE_TE_RPY', 'RMSE_TE_VEL', 'Omega_Jitter', 'Motor_Jitter']
    for col in cols_to_norm:
        if col in df.columns:
            norm_col = f"NORM_{col}"
            df[norm_col] = 0.0
            for mission in df['Mission'].unique():
                mask = df['Mission'] == mission
                vals = df.loc[mask, col]
                min_v, max_v = vals.min(), vals.max()
                if max_v > min_v:
                    df.loc[mask, norm_col] = (vals - min_v) / (max_v - min_v)

    #cols_to_norm = {'RMSE_TE_XYZ':2, 'RMSE_TE_RPY': 25, 'RMSE_TE_VEL': 2.0, 'Omega_Jitter':0.1, 'Motor_Jitter':0.1}
    #for col in cols_to_norm:
    #    if col in df.columns:
    #        norm_col = f"NORM_{col}"
    #        df[norm_col] = 0.0
    #        for mission in df['Mission'].unique():
    #            mask = df['Mission'] == mission
    #            vals = df.loc[mask, col]
    #            df.loc[mask, norm_col] = np.clip(np.abs(vals) / cols_to_norm[col], 0, 1)
    
    # Finaler Score: 
    # + Bonus für Überleben (Stability) und Missionsfortschritt (WCR)
    # - Abzug für normierte Tracking-Fehler
    # - Abzug für normierte Unruhe (Jitter)
    df['Score'] = (1 * df['Stability'] + 
                   1 * df.get('WCR', 0) - 
                   0.2 * df.get('NORM_RMSE_TE_XYZ', 0) - 
                   1.0 * df.get('NORM_RMSE_TE_VEL', 0) - # vel counts doubled as main control target
                   0.4 * df.get('NORM_RMSE_TE_RPY', 0) -
                   0.2 * df.get('NORM_Omega_Jitter', 0) - 
                   0.2 * df.get('NORM_Motor_Jitter', 0))
    return df


def calculate_composite_score(df):
    if df.empty: return df
    df = df.copy()

    # Bestehende NORM- oder Score-Spalten entfernen, falls die Funktion 
    # erneut auf ein bereits aggregiertes DF angewendet wird
    cols_to_drop = [c for c in df.columns if c.startswith('NORM_') or c == 'Score']
    df = df.drop(columns=cols_to_drop, errors='ignore')

    # 1. Absolute Limits definieren
    limits = {
        'RMSE_TE_VEL': 2.5,   
        'RMSE_TE_XYZ': 2.5,   
        'RMSE_TE_RPY': 35.0,  
        'Omega_Jitter': 0.1,  
        'Motor_Jitter': 0.05
    }

    for col, limit in limits.items():
        if col in df.columns:
            norm_col = f"NORM_{col}"  
            # Deine Formel: (Ist/Limit)^2 clipped auf [0, 2] und um -1 verschoben
            # Range: -1.0 (perfekt) bis +1.0 (sehr schlecht)
            df[norm_col] = np.clip((df[col] / limit)**2, 0, 1)
    
    # 2. Finaler Score
    # Da NORM bei guten Werten negativ ist (-1), führt das Minus vor dem Gewicht zu einem Bonus.
    df['Score'] = (
        0.5 * df['Stability'] + 
        0.5 * df.get('WCR', 0) - 
        0.4 * df.get('NORM_RMSE_TE_VEL', 0) - # Hauptziel
        0.1 * df.get('NORM_RMSE_TE_XYZ', 0) - 
        0.2 * df.get('NORM_RMSE_TE_RPY', 0) -
        0.15 * df.get('NORM_Omega_Jitter', 0) -  
        0.15 * df.get('NORM_Motor_Jitter', 0)
    )
    return df