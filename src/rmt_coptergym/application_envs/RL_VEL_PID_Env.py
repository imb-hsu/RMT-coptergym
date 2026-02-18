import numpy as np
from gymnasium import spaces
from typing import Dict, Any
from rmt_coptergym.base_envs.RMT_RL_Env import RMT_RL_Env

class PID_VEL_Env(RMT_RL_Env):
    """
    Velocity Control Environment speziell für X8 Koaxial-Copter.
    
    Features:
    - Hardcodiertes Motor-Pairing basierend auf dem Schema (U1/L6, U2/L5, etc.).
    - Additiver 'Efficiency Reward', um die Paare zu synchronisieren.
    - PID-Struktur für Velocity-Tracking.
    - Multiplikative Smoothness für 'gemütliche' Delta-Actions.
    """

    def __init__(self, 
                reward_weights: Dict[str, Any] = None,
                **kwargs):
        
        # --- 1. Gewichte (Tuning der Prioritäten) ---
        default_weights = {
            # Performance (Additiv)
            "w_vel_p": 0.4,    # Velocity Error (Hauptziel)
            "w_vel_d": 0.1,    # Acceleration (Dämpfung)
            "w_vel_i": 0.2,    # Integral (Drift Prevention)
            "w_yaw":   0.05,    # Yaw Holding (Orientierung)
            "w_reg":   0.05,   # Regularization ("Feder" -> Horizontale)
            "w_eff":   0.2,   # Efficiency (Motor-Paar-Synchronität)

            
            # Constraints (Multiplikativ)
            "w_act":    1.0,
            "scale_smooth": 1.0 # Skalierung der Smoothness-Kurve
        }
        if reward_weights is not None:
            default_weights.update(reward_weights)
        self.reward_weights = default_weights

        # --- 2. Motor-Paare (Hardcoded X8 Schema) ---
        # Mapping: Motor ID (1-8) -> Array Index (0-7)
        # Paar 1: U:1 (Idx 0) & L:6 (Idx 5)
        # Paar 2: U:2 (Idx 1) & L:5 (Idx 4)
        # Paar 3: U:3 (Idx 2) & L:8 (Idx 7)
        # Paar 4: U:4 (Idx 3) & L:7 (Idx 6)
        self.motor_pairs = np.array([[0, 5], [1, 4], [2, 7], [3, 6]], dtype=np.int32)

        super().__init__(**kwargs)

        # --- 3. Interne States & Parameter ---
        self.vel_integral_error = np.zeros(3)
        self.vel_integral_limit = 5.0 
        
        # Sensitivität der Reward-Kurven (Alpha in exp(-alpha * x^2))
        #self.alpha = {
        #    'p': 2.0,   # Aggressives Tracking
        #    'd': 1.0,   # Weiche Dämpfung
        #    'i': 2.0,   # Mittlerer I-Einfluss
        #    'yaw': 3.0, # Präzises Yaw
        #    'reg': 0.5, # Weiche "Feder"
        #    'eff': 3.0, # Strenge Paarung
        #    'smooth': 2.0 # Filter gegen Zappeln
        #}

                # --- ALPHAS (MASSIV ERHÖHT) ---
        # Berechnungsgrundlage: 
        # Normierter Fehler = (Physikalischer Fehler / Range)
        # Range ist groß (z.B. 12m/s), daher ist Normierter Fehler winzig.
        # Wir müssen Alpha mit dem Quadrat der Range skalieren.
        
        self.alpha = {
            # Range ca 12m/s. Alpha 100 bedeutet:
            # Bei 1.0m/s Fehler (Norm 0.08) -> exp(-100 * 0.007) = 0.5 (Halbe Punkte)
            # Bei 0.1m/s Fehler (Norm 0.008) -> exp(-100 * 0.00006) = 0.99 (Super)
            'p': 80.0,    
            
            # Accel ist meist kleiner, hier reicht weniger Schärfe
            'd': 5.0,     
            
            # Integral ist auf 5.0 limitiert. Normiert 0..1.
            # Hier wollen wir, dass er bei vollem Integral (Limit) 0 Punkte kriegt.
            'i': 5.0,     
            
            # Yaw Fehler ist in Radiant normalisiert (oft auf PI). 
            # Fehler 10 Grad (0.17 rad) -> Norm ca 0.05 -> Sq 0.0025
            # Wir wollen Strafe bei 10 Grad.
            'yaw': 20.0,  
            
            'reg': 0.0, 
            
            # Efficiency: Motoren auf 2200 Range.
            # Differenz 100 (Norm 0.045) -> Sq 0.002
            # Alpha 200 -> exp(-200 * 0.002) = 0.67 (Spürbar)
            # Differenz 200 (Norm 0.09) -> exp(-200 * 0.008) = 0.2 (Aua)
            'eff': 200.0, 
            
            # Smoothness ist okay, da 0..1 direkt aus Action kommt
            'smooth': 2.0 
        }

    def reset(self, **kwargs):
        self.vel_integral_error = np.zeros(3)
        return super().reset(**kwargs)

    # --- Observation ---

    def build_state_obs_space(self) -> spaces.Dict:
        return spaces.Dict({
            "vel_error":        spaces.Box(low=-1.0, high=1.0, shape=(3,), dtype=np.float32),
            "error_integral":     spaces.Box(low=-1.0, high=1.0, shape=(6,), dtype=np.float32),
            "rpy_error":        spaces.Box(low=-1.0, high=1.0, shape=(3,), dtype=np.float32), # Wichtig für Yaw
            "current_accel":    spaces.Box(low=-1.0, high=1.0, shape=(3,), dtype=np.float32), # Für D-Anteil
            "motor_spread":     spaces.Box(low=0.0, high=1.0, shape=(4,), dtype=np.float32)   # Info für Agent: Wie asynchron sind die Paare?
        })

    def get_state_observation(self) -> dict:
        # Integral normalisieren (-1..1)
        norm_integral = np.clip(self.vel_integral_error / self.vel_integral_limit, -1.0, 1.0)
        
        # Motor Spread berechnen (für Observation)
        # Wir nutzen command_old (die letzten gesendeten Befehle)
        current_cmds = self.normalized_dict['command_old'] 
        
        # Vektorisierte Berechnung der Differenzen für alle 4 Paare
        # pair_cmds shape: (4, 2) -> Diff entlang Achse 1
        vals_a = current_cmds[self.motor_pairs[:, 0]]
        vals_b = current_cmds[self.motor_pairs[:, 1]]
        # Differenz absolut, normalisiert (da command_old schon normiert ist, passt das grob)
        spreads = np.abs(vals_a - vals_b) # Angenommen command_old ist [-1, 1] -> spread [0, 2]
        spreads = np.clip(spreads / 2.0, 0, 1) # Auf 0..1 bringen

        return {
            "vel_error":        self.normalized_dict['error_vel'],
            "vel_integral":     norm_integral.astype(np.float32),
            "rpy_error":        self.normalized_dict['error_rpy'],
            "current_accel":    self.normalized_dict['accel'],
            "motor_spread":     spreads.astype(np.float32)
        }

    # --- Action Transform (Relative) ---

    def _transform_action(self, delta_action):
        if self.action_space_type == "Box": 
            self.action.box = delta_action
            # Relative Control: Neuer Befehl = Alter Befehl + Delta
            # Scale 50.0 sorgt für Reaktionsfreudigkeit
            motor_commands_rads = self.action.cmd_old + 50.0 * delta_action
            self.action.cmd = np.clip(motor_commands_rads, self.limits.motor.min, self.limits.motor.max).astype(np.float64)
        else:
            super()._transform_action(delta_action)

    # --- Reward Calculation ---

    def _compute_reward_terms(self) -> float:
        dt = self.timestep * self.frame_skip
        w = self.reward_weights

        # 1. Integral Update
        self.vel_integral_error = 0.999 * self.vel_integral_error + self.error.vel_c * dt
        self.vel_integral_error = np.clip(self.vel_integral_error, -self.vel_integral_limit, self.vel_integral_limit)

        # --- A. Performance (Additive) ---

        # P-Term (Velocity)
        norm_v_err = self.normalized_dict['error_vel']
        r_p = np.exp(-self.alpha['p'] * np.sum(np.square(norm_v_err)))

        # D-Term (Acceleration)
        norm_acc = self.normalized_dict['accel']
        r_d = np.exp(-self.alpha['d'] * np.sum(np.square(norm_acc)))

        # I-Term (Integral)
        norm_i_err = self.vel_integral_error / self.vel_integral_limit
        r_i = np.exp(-self.alpha['i'] * np.sum(np.square(norm_i_err)))

        # Yaw-Term
        yaw_err = self.normalized_dict['error_rpy'][2]
        r_yaw = np.exp(-self.alpha['yaw'] * (yaw_err**2))

        # Regularization
        rp_state = self.normalized_dict['rpy'][:2]
        r_reg = np.exp(-self.alpha['reg'] * np.sum(np.square(rp_state)))

        # Efficiency (Paired Coupling) - FIX FÜR X8 YAW
        cmds = self.action.cmd
        vals_a = cmds[self.motor_pairs[:, 0]]
        vals_b = cmds[self.motor_pairs[:, 1]]
        
        # Differenz absolut pro Paar
        pair_diff_norm = np.abs(vals_a - vals_b) / self.limits.motor.range
        
        # WICHTIG: Erst exp pro Paar, dann Mean. Das erlaubt, dass Paare unterschiedlich sein dürfen (für Yaw),
        # solange sie in sich schlüssig sind.
        r_eff = np.mean(np.exp(-self.alpha['eff'] * (pair_diff_norm**2)))

        # Summe Performance (OHNE r_act!)
        performance_score = (w['w_vel_p'] * r_p) + \
                            (w['w_vel_d'] * r_d) + \
                            (w['w_vel_i'] * r_i) + \
                            (w['w_yaw']   * r_yaw) + \
                            (w['w_reg']   * r_reg) + \
                            (w['w_eff']   * r_eff)

        # --- B. Multiplikative Constraints ---
        
        # 1. Smoothness
        action_mag = np.mean(np.abs(self.action.box))
        r_smooth = np.exp(-self.alpha['smooth'] * action_mag * w.get('scale_smooth', 1.0))

        # 2. Activity (Motoren anlassen!)
        mean_cmd_norm = np.mean((cmds - self.limits.motor.min) / self.limits.motor.range)
        
        # Kurve: Absturz(<10%) -> Ideal(30-80%) -> Sättigung(>95%)
        xp = [0.0, 0.1, 0.30, 0.80, 1.0]
        fp = [0.01, 0.1, 1.0,  1.0,  0.1]
        r_act = np.interp(mean_cmd_norm, xp, fp)

        # --- C. Final ---

        # Logische Verknüpfung: Performance UND Smooth UND Active
        final_reward = performance_score * r_smooth * r_act

        # --- Logging FIX ---
        # Wir setzen 'w': 0.0 für multiplikative Terme, damit der Stackplot nicht crasht.
        # Im "Raw Plot" (Plot 3) sieht man sie trotzdem.
        
        self.reward.terms['Vel_P']  = {'r': r_p,      'w': w['w_vel_p'], 'val': r_p * w['w_vel_p']}
        self.reward.terms['Vel_D']  = {'r': r_d,      'w': w['w_vel_d'], 'val': r_d * w['w_vel_d']}
        self.reward.terms['Vel_I']  = {'r': r_i,      'w': w['w_vel_i'], 'val': r_i * w['w_vel_i']}
        self.reward.terms['Yaw']    = {'r': r_yaw,    'w': w['w_yaw'],   'val': r_yaw * w['w_yaw']}
        self.reward.terms['Reg']    = {'r': r_reg,    'w': w['w_reg'],   'val': r_reg * w['w_reg']}
        self.reward.terms['Eff']    = {'r': r_eff,    'w': w['w_eff'],   'val': r_eff * w['w_eff']}
        
        # Hier w=0.0 setzen, um TypeError zu vermeiden!
        self.reward.terms['Smooth'] = {'r': r_smooth, 'w': 1.0,       'val': r_smooth} 
        self.reward.terms['Act']    = {'r': r_act,    'w': w['w_act'],          'val': r_act}
        
        self.reward.base = final_reward
        return final_reward