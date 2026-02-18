import numpy as np
from gymnasium import spaces
from typing import Dict, Any
from rmt_coptergym.base_envs.RMT_RL_Env import RMT_RL_Env

class PID_VEL_Env(RMT_RL_Env):
    """
    Velocity Control Environment für X8 Koaxial-Copter.
    
    Architektur:
    - Coupled PID: P, I und D Terme koppeln intern (z.B. Vel * Yaw) via geometrisches Mittel.
    - Root Rewards: 1 - sqrt(err/scale) für steile Gradienten nahe 0.
    - Execution Quality: Constraints (Eff, Act, Smooth) bilden einen multiplikativen Faktor.
    """

    def __init__(self, 
                reward_weights: Dict[str, Any] = None,
                **kwargs):
        
        # --- 1. Gewichte (Prioritäten) ---
        # Die PID-Gewichte (w_p, w_i, w_d) sollten in Summe ca. 1.0 ergeben.
        default_weights = {
            "w_p": 4,#0.75,  # P-Term (Velocity & Yaw)
            "w_i": 1,#0.2,  # I-Term (Integral & Yaw) - Hoch gegen Drift
            "w_d": 0.5,#0.05,  # D-Term (Accel & Omega) - Gegen Schwingungen
            
            # Multiplikator-Skalierung (optional, meist 1.0)
            "scale_smooth": 1.0,
            "w_pid": 2,
            "comfort_zone": 1.0,
            "paired_efficiency": 1.0,
            "balance": 0.25, #0.5,
            "smoothness": 0.1 # Standardmäßig ist smoothness unwichtig
        }
        if reward_weights is not None:
            default_weights.update(reward_weights)
        self.reward_weights = default_weights

        # --- 2. Motor-Paare (X8 Schema) ---
        # Mapping: U1/L6, U2/L5, U3/L8, U4/L7
        self.motor_pairs = np.array([[0, 5], [1, 4], [2, 7], [3, 6]], dtype=np.int32)

        super().__init__(**kwargs)
        
        # --- 3. Critical Fixes ---
        # Zeitliche Auflösung für Integral berechnen
        self.dt = self.timestep * self.frame_skip

        # Integral State
        self.vel_integral_error = np.zeros(3)
        self.vel_integral_limit = 2.5 # m/s (Passend zur Scale 'int')

        # --- 4. Physikalische Skalen (Bounds) ---
        # Defines where the reward hits 0 (or minimum floor).
        # Diese Werte sind physikalisch greifbar (Meter, Rad/s, etc.)
        self.scales = {
            'vel': 2.0,             # 0 Punkte ab 2.0 m/s Fehler
            'acc': 10.0,            # 0 Punkte ab 10 m/s^2 (~1G)
            'int': 0.5,             # 0 Punkte ab 2.0 m/s Integral-Fehler
            'yaw': np.deg2rad(45),  # 0 Punkte ab 45 Grad Yaw-Fehler
            'omega': 6.0,           # 0 Punkte ab 6 rad/s Drehrate
            'eff_tol': 200.0        # 0 Punkte ab 150 rad/s Motor-Differenz
        }

    def reset(self, **kwargs):
        self.vel_integral_error = np.zeros(3)
        return super().reset(**kwargs)

    # --- Observations ---

    def build_state_obs_space(self) -> spaces.Dict:
        """
        Definiert nur die dynamischen State-Infos.
        Statische Infos (current_vel, etc.) kommen aus Base-Obs.
        """
        return spaces.Dict({
            "vel_error":    spaces.Box(low=-1.0, high=1.0, shape=(3,), dtype=np.float32),
            "vel_integral": spaces.Box(low=-1.0, high=1.0, shape=(3,), dtype=np.float32),
            "rpy_error":    spaces.Box(low=-1.0, high=1.0, shape=(3,), dtype=np.float32),
            # 'current_accel' ist optional hier, da oft in Base enthalten, 
            # aber für Konsistenz lassen wir es oft weg oder fügen es hinzu, 
            # wenn der Agent explizit Accel minimieren soll.
        })

    def get_state_observation(self) -> dict:
        # Integral normalisieren (-1..1)
        norm_integral = np.clip(self.vel_integral_error / self.vel_integral_limit, -1.0, 1.0)
        
        return {
            "vel_error":    self.normalized_dict['error_vel'],
            "vel_integral": norm_integral.astype(np.float32),
            "rpy_error":    self.normalized_dict['error_rpy'],
        }

    # --- Action Transform (Deine Version) ---

    def _transform_action(self, delta_action):
        """
        Custom relative overwrite from Base_Env preserving MDisc support.
        """
        if self.action_space_type == "Box": 
            self.action.box = delta_action
            # Defined between -1 and 1, shifting to 0..1 and scale to motorlimits
            motor_commands_rads = self.action.cmd_old + 50 * delta_action
            self.action.cmd = np.clip(motor_commands_rads, self.limits.motor.min, self.limits.motor.max).astype(np.float64)
            self.action.disc = None 
        elif self.action_space_type  == "MDisc":
            self.action.disc = delta_action
            # read values from 0 to 100 and encode in rads
            motor_commands_rads = self.action.cmd_old + delta_action - 50
            self.action.cmd = np.clip(motor_commands_rads, self.limits.motor.min, self.limits.motor.max).astype(np.float64)
            self.action.box = None 
        else:
            raise ValueError(f"Error: Unsupported action_space_type: {self.action_space_type}")

    # --- Reward Helpers ---

    def _calc_root_reward(self, error_val, scale, power=0.5, min_reward=0.0):
        """
        Berechnet 1 - (abs(error)/scale)^power.
        Skaliert das Ergebnis auf [min_reward, 1.0], um Null-Multiplikation zu verhindern.
        """
        norm_err = np.abs(error_val) / scale
        norm_err = np.clip(norm_err, 0.0, 1.0)
        
        base_reward = 1.0 - np.power(norm_err, power)
        
        # Mapping auf [min_reward, 1.0]
        #return min_reward + (1.0 - min_reward) * base_reward
        return np.exp(-3.0 * norm_err)

    # --- Reward Calculation ---

    def _compute_reward_terms(self) -> float:
        dt = self.dt
        w = self.reward_weights
        
        # Global Floor für Constraints (damit Quality Score nicht 0 wird)
        CONSTRAINT_FLOOR = 0.1

        # 1. Integral Update (With Leaking for RL stability)
        self.vel_integral_error = 0.999 * self.vel_integral_error + self.error.vel_c * dt
        self.vel_integral_error = np.clip(self.vel_integral_error, -self.vel_integral_limit, self.vel_integral_limit)

        # --- A. PERFORMANCE (PID mit geometrischer Kopplung) ---
        
        # P-Term: Kopplung von Velocity (Mean) und Yaw
        # Wir nutzen power=0.5 (Wurzel) für steile Gradienten bei kleinen Fehlern.
        #r_vel_vec = self._calc_root_reward(self.error.vel_c, self.scales['vel'], power=0.5)
        r_vel_vec = self._calc_root_reward(self.normalized_dict['error_vel'],1.0, power=0.5)
        r_vel = np.mean(r_vel_vec)
        
        #r_yaw = self._calc_root_reward(self.error.rpy_rad[2], self.scales['yaw'], power=0.5)
        r_yaw = self._calc_root_reward(self.normalized_dict['error_rpy'][2],1.0, power=0.5)
        
        # Kopplung: sqrt(Vel * Yaw). Wenn Orientierung falsch ist, ist P schlecht.
        term_p = np.sqrt(r_vel * r_yaw + 1e-6)

        # I-Term: Kopplung von Integral und Yaw
        # Verhindert Windup-Belohnung bei falscher Ausrichtung.
        r_int_vec = self._calc_root_reward(self.vel_integral_error, self.scales['int'], power=0.5)
        r_int = np.mean(r_int_vec)
        
        term_i = np.sqrt(r_int * r_yaw + 1e-6)

        # D-Term: Kopplung von Accel (Ruhe) und Omega (Drehrate)
        # Accel: Wir nutzen normalized dict (0..1) und nehmen an 1.0 ist Max-Accel (schlecht).
        r_acc_vec = self._calc_root_reward(self.normalized_dict['accel'], 1.0, power=0.5)
        r_acc = np.mean(r_acc_vec)
        
        #r_omega_vec = self._calc_root_reward(self.agent.omega, self.scales['omega'], power=0.5)
        r_omega_vec = self._calc_root_reward(self.normalized_dict['omega'],1.0, power=0.5)

        r_omega = np.mean(r_omega_vec)
        
        term_d = np.sqrt(r_acc * r_omega + 1e-6)

        # Basis Performance Score (Additiv)
        #pid_score = (w['w_p'] * term_p) + (w['w_i'] * term_i) + (w['w_d'] * term_d)
        pid_score = np.cbrt(term_p**w['w_p']) * (term_i**w['w_i']) * (term_d**w['w_d'])


        # --- B. EXECUTION QUALITY (Constraints) ---

        # 1. Efficiency (X8 Paare)
        cmds = self.action.cmd
        vals_a = cmds[self.motor_pairs[:, 0]]
        vals_b = cmds[self.motor_pairs[:, 1]]
        diff_rads = np.abs(vals_a - vals_b)
        
        # Toleranz 150 rad/s. Floor 0.25.
        r_eff_vec = self._calc_root_reward(diff_rads, self.scales['eff_tol'], power=0.5, min_reward=CONSTRAINT_FLOOR)
        r_eff = np.mean(r_eff_vec)

        # 2. Activity (Trapezoid)
        mean_cmd_norm = np.mean((cmds - self.limits.motor.min) / self.limits.motor.range)
        
        # Komfortzone 30% bis 80%. Ränder fallen auf CONSTRAINT_FLOOR (nicht 0!).
        xp = [0.0, 0.1, 0.25, 0.75, 1.0]
        fp = [0.0, CONSTRAINT_FLOOR/2, 1.0, 1.0, CONSTRAINT_FLOOR]
        r_act = np.interp(mean_cmd_norm, xp, fp)

        # 3. Smoothness (Exponential Penalty)
        action_mag = np.mean(np.abs(self.action.box))
        r_smooth_raw = np.exp(-2.0 * action_mag * w.get('scale_smooth', 1.0))
        # Floor anwenden
        r_smooth = np.maximum(r_smooth_raw, CONSTRAINT_FLOOR)

        balance_error = np.mean(np.square(self.action.cmd/self.limits.motor.range))
        r_balance = np.exp(-balance_error * 1.5) 


        # --- C. FINAL COMBINATION ---

        # Qualitäts-Score als Geometrisches Mittel der 3 Constraints
        # Dies erhält die Magnitude (0.8 * 0.8 * 0.8 -> 0.8) und verhindert zu starke Reduktion.
        quality_score = np.cbrt(r_eff**w['paired_efficiency']  * r_smooth**w['smoothness'] * r_balance**w['balance'])
        
        # Final: PID-Leistung * Ausführungs-Qualität
        final_reward = pid_score**(w['w_pid']) * quality_score * r_act**w['comfort_zone']

        # --- Logging ---
        # Wichtig: w=0.0 für multiplikative/Info Terme setzen, um Plotter-Crash zu vermeiden
        self.reward.terms['Term_P'] = {'r': term_p,  'w': w['w_p'], 'val': term_p * w['w_p']}
        self.reward.terms['Term_I'] = {'r': term_i,  'w': w['w_i'], 'val': term_i * w['w_i']}
        self.reward.terms['Term_D'] = {'r': term_d,  'w': w['w_d'], 'val': term_d * w['w_d']}
        
        self.reward.terms['Eff']    = {'r': r_eff,    'w': 1.0,      'val': r_eff}
        self.reward.terms['Act']    = {'r': r_act,    'w': 1.0,      'val': r_act}
        self.reward.terms['Smooth'] = {'r': r_smooth, 'w': 1.0,      'val': r_smooth}
        self.reward.terms['QUAL']   = {'r': quality_score, 'w': 1/w['w_pid'], 'val': quality_score}
        self.reward.terms['PID']   = {'r': pid_score, 'w': w['w_pid'], 'val': pid_score}

        self.reward.base = final_reward
        return final_reward