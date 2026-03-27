import numpy as np
from gymnasium import spaces
from typing import Dict, Any

from rmt_coptergym.base_envs.RMT_RL_Env import RMT_RL_Env

class HRL_Att_Env(RMT_RL_Env):
    """
    Velocity Control Environment.
    The agent's primary goal is to match a target velocity vector `target.vel_c`.
    The observation space is focused on velocity and attitude errors, ignoring
    positional error, to train a low-level velocity controller.
    """

    def __init__(self, 
                reward_weights: Dict[str, Any] = None,
                **kwargs):
        """
        Args:
            **kwargs: Arguments passed to the parent RMT_RL_Env class.
        """
        # handle default parameter with this variable.
        default_weights = {
            "rollpitch": 1.0,
            "y_rate": 1.0,
            'thrust':1.0,
            'integral':1.0,
            "rp_rate": 1.0,
            "efficiency": 1.0,
            "smoothness": 0.1,
            "safety_zone": 1.0,
        }
        if reward_weights is not None:
            default_weights.update(reward_weights)
        self.reward_weights = default_weights

        super().__init__(**kwargs)

        self.delta_actionrange = 50

        # Integral State
        self.dt = self.timestep * self.frame_skip
        self.integral_error = np.zeros(4)
        self.leak_rate = 0.995 
        self.integral_limits = np.array([
            20.0,  # Roll Limit
            20.0,  # Pitch Limit
            50.0,  # Yaw Rate Limit
            0.5    # Thrust Limit
        ])

    def update_weights_online(self, new_weights: Dict[str, Any] ):
        """
        Updates the environment weights dynamically (e.g. reward weights)
        without requiring a full reset/recreation.
        """
        if new_weights:
            # Update des Dictionaries (existierende Keys behalten, neue überschreiben)
            self.reward_weights.update(new_weights)
            print(f"DEBUG: Reward weights updated with {new_weights} to: {self.reward_weights}")
        else:
            print('DEBUG: No WeightUpdate')

    def reset(self, **kwargs):
        self.integral_error = np.zeros(4)
        self.integral_error_norm = np.zeros(4)
        return super().reset(**kwargs)

    def build_observation_space(self) -> spaces.Dict:
        """
        Überschreibt die Space-Definition der Base-Class komplett.
        Vereint alle für den Attitude/Mixer-Agenten nötigen Inputs in einem flachen Dictionary.
        """
        obs_dict = {
            # --- Task / Error Metrics ---
            "rp_error":       spaces.Box(low=-1.0, high=1.0, shape=(2,), dtype=np.float32),
            "omega_z_error":  spaces.Box(low=-1.0, high=1.0, shape=(1,), dtype=np.float32),
            "thrust_error":   spaces.Box(low=-1.0, high=1.0, shape=(1,), dtype=np.float32),
            "error_integral": spaces.Box(low=-1.0, high=1.0, shape=(4,), dtype=np.float32),
            
            # --- Ego State / Kinematics ---
            "current_rpy":    spaces.Box(low=-1.0, high=1.0, shape=(3,), dtype=np.float32),
            "current_omega":  spaces.Box(low=-1.0, high=1.0, shape=(3,), dtype=np.float32),
            
            # --- Actuator State ---
            "current_motors": spaces.Box(low=-1.0, high=1.0, shape=self.action_space.shape, dtype=np.float32),
        }
        
        # Optional: Anomalie-Wissen (Motor-Ausfälle etc.)
        if self.has_anomaly_knowledge:
            obs_dict["motor_loss"] = spaces.Box(low=0.0, high=1.0, shape=self.action_space.shape, dtype=np.float32)

        return spaces.Dict(obs_dict)

    def _get_obs(self) -> dict:
        """
        Überschreibt die Observation-Generierung der Base-Class komplett.
        Gibt direkt das fertige, flache Dictionary für den LL-Agenten zurück.
        """
        # 1. Lokale Berechnungen (z.B. Thrust Error)
        target_thrust = self.target.cmd[0] if isinstance(self.target.cmd, np.ndarray) else self.target.cmd
        current_thrust_norm = (np.mean(self.action.cmd) - self.limits.motor.min) / self.limits.motor.range
        thrust_err = target_thrust - current_thrust_norm

        # 2. Dictionary zusammenbauen
        obs = {
            # --- Task / Error Metrics ---
            "rp_error":       self.normalized_dict['error_rpy'][0:2],
            "omega_z_error":  self.normalized_dict['error_omega_z'],
            "thrust_error":   self.error_thrust_norm,
            "error_integral": self.integral_error_norm,
            
            # --- Ego State / Kinematics ---
            "current_rpy":    self.normalized_dict['rpy'],
            "current_omega":  self.normalized_dict['omega'],
            
            # --- Actuator State ---
            "current_motors": self.normalized_dict['command'],
        }
        
        # Optional: Anomalie-Wissen
        if self.has_anomaly_knowledge:
            obs["motor_loss"] = self.anomaly.motor_loss_array
            
        return obs
    
    def _transform_action(self, delta_action):
        """
        custom relative overwrite from Base_Env
        """

        if self.action_space_type == "Box": 
            self.action.box = delta_action
            # Defined between -1 and 1, shifting to 0..1 and scale to motorlimits
            motor_commands_rads = self.action.cmd_old + self.delta_actionrange *delta_action# ((action + 1)/2) * self.limits.motor.range + self.limits.motor.min
            self.action.cmd = np.clip(motor_commands_rads, self.limits.motor.min, self.limits.motor.max).astype(np.float64)
            # discrete values for potential MDisc action space (for info/masking)
            motor_commands_disc = None #np.round(100 * (action +1)/2)
            self.action.disc = None #np.clip(motor_commands_disc, 0, 100).astype(np.int32)
        elif self.action_space_type  == "MDisc":
            self.action.disc = delta_action
            # read values from 0 to 100 and encode in rads
            motor_commands_rads = self.action.cmd_old + delta_action-50 #(action / 100.0) * self.limits.motor.range + self.limits.motor.min
            self.action.cmd = np.clip(motor_commands_rads, self.limits.motor.min, self.limits.motor.max).astype(np.float64)
            # box values for potential Box action space (for info/masking)
            motor_commands_box = None #(action / 100.0) * 2 - 1 # Scale 0 to 100 to -1 to 1
            self.action.box = None #np.clip(motor_commands_box, -1, 1).astype(np.float32)
        else:
            raise ValueError(f"Error: Unsupported action_space_type: {self.action_space_type}")

    def _compute_integrals(self):
        """Called every step before building the observation."""
        
        # 1. Gather current errors (Make sure they are purely proportional, not normalized yet)
        current_error = np.array([
            self.normalized_dict['error_rpy'][0],
            self.normalized_dict['error_rpy'][1],
            self.normalized_dict['error_omega_z'],
            self.error_thrust_norm
        ])
        
        # 2. Update with Leak + Euler Integration
        self.integral_error = (self.integral_error * self.leak_rate) + (current_error * self.dt)
        
        # 3. Apply Anti-Windup (Clipping)
        self.integral_error = np.clip(
            self.integral_error, 
            -self.integral_limits, 
            self.integral_limits
        )
        
        # 4. Normalize for the Observation Space (-1.0 to 1.0)
        self.integral_error_norm = self.integral_error / self.integral_limits

    def _compute_reward_terms(self) -> float:
        """
        Modularer Attitude-Reward: Vereint HRL-Ziele, Mysore-Logik und 
        dein bestehendes Weighting/Logging-System.
        """
        # --- 0. PRE-CALCULATIONS ---
        self.error_thrust_norm = np.clip( (self.target.cmd - np.mean(self.action.cmd))/(0.5*self.limits.motor.range), -1,1)
        self._compute_integrals() # Berechnet self.integral_error_norm [Roll, Pitch, YawRate, Thrust]
        weights = self.reward_weights
        eps = 1e-6
        
        # Hilfsvariablen für die Berechnung
        target_thrust = self.target.cmd[0] if isinstance(self.target.cmd, np.ndarray) else self.target.cmd
        current_thrust = (np.mean(self.action.cmd) - self.limits.motor.min) / self.limits.motor.range
        
        # --- 1. REWARD KOMPONENTEN (Mapping mittels deiner Activation-Funktion) ---
        
        # A. ATTITUDE TRACKING (Zwei Modi möglich)
        # Modus 1: Winkel-Fehler (Dein HRL-Ansatz)
        r_rp_angle_vec = self._calculate_reward_from_error(self.normalized_dict['error_rpy'][:2])
        r_rp_angle = float(0.5 * np.mean(r_rp_angle_vec) + 0.5 * np.min(r_rp_angle_vec))
        
        # Modus 2: Rate-Fehler (Mysore Ansatz - Omega X/Y)
        # Hier nehmen wir an, dass der HL-Agent eigentlich Winkel will, 
        # aber wir bestrafen hohe Raten zur Dämpfung (ähnlich Mysore Eq. 9)
        r_omega_xy_vec = self._calculate_reward_from_error(self.normalized_dict['omega'][:2])
        r_omega_xy = float(np.mean(r_omega_xy_vec))

        # B. YAW RATE TRACKING
        r_yaw_rate = float(self._calculate_reward_from_error(np.array([self.normalized_dict['error_omega_z']])))

        # C. THRUST TRACKING (Das HRL-Äquivalent zu Mysores Hover-Penalty)
        r_thrust_vec = float(self._calculate_reward_from_error(self.error_thrust_norm))
        r_thrust = float(0.5*np.mean(r_thrust_vec) + 0.5*np.min(r_thrust_vec))

        # D. INTEGRAL (Steady-State Accuracy)
        r_int_vec = self._calculate_reward_from_error(self.integral_error_norm)
        r_int = float(np.min(r_int_vec)) # Strict: Worst-Axis Penalty

        # E. EFFICIENCY (X8 Pairing & Energy Balance)
        # Coaxial Pairing: Motors [0..3] vs [4..7]
        pair_error = np.abs(self.action.cmd[[1,0,2,3]] - self.action.cmd[[4,5,7,6]]) / (0.5*self.limits.motor.range)
        r_pairing = float(np.prod(self._calculate_reward_from_error(pair_error))**(1/4))
        # Balance: Energieverteilung
        balance_error = np.mean(np.square((self.action.cmd -self.limits.motor.min)/ self.limits.motor.range))
        r_balance = float(self._calculate_reward_from_error(balance_error))
        r_eff = 0.5 * r_pairing + 0.5 * r_balance

        # F. SMOOTHNESS (Delta-Aktionen aus dem NN)
        action_delta = self.action.box 
        smoothness_error = np.mean(np.square(action_delta)) 
        smoothness_error = np.clip(smoothness_error, 0, 1)
        r_smooth = self._calculate_reward_from_error(np.array([smoothness_error]))[0]

        # G. SAFETY / COMFORT ZONE (Veto-Faktor zwischen 0.25 und 0.75)
        motor_load = self.action.cmd / self.limits.motor.max
        # Wir nutzen deine interp-Logik
        individual_safety = np.interp(motor_load, [0.0, 0.15, 0.85, 1.0], [0.15, 1.0, 1.0, 0.3])
        r_safety_veto = float(np.min(individual_safety))

        # --- 2. DYNAMIC WEIGHTING & COMPOSITION ---
        
        # Wir übernehmen dein System der dynamischen Gewichtung:
        # Bei großen Winkelfehlern ("Emergency") können wir Effizienz/Smoothness ausblenden
        att_err_norm = max(np.abs(self.normalized_dict['rpy'][:2]))
        # Fader: Bei < 5° (ca. 0.05 norm) ist alles 1.0, bei > 20° (ca. 0.2 norm) ist Panik.
        emergency_factor = np.clip(1.0 - (max(att_err_norm - np.deg2rad(5),0) /np.deg2rad(20)), 0.0, 1.0)

        # Kompaktliste für die Berechnung (Value, Weight, Key)
        # Falls Mysore-Vergleich gewünscht: 'rp_rate' höher gewichten, 'rp_angle' niedriger
        comp_data = [
            (r_rp_angle,  weights.get('rollpitch', 1.5), 'rp_angle', self.normalized_dict['error_rpy'] ),
            (r_yaw_rate,  weights.get('y_rate', 1.0),    'y_rate', self.normalized_dict['error_omega_z']),
            (r_thrust,    weights.get('thrust', 1.2),    'thrust', target_thrust - current_thrust),
            (r_int,       weights.get('integral', 0.5),  'integral', self.integral_error_norm),
            (r_omega_xy,  weights.get('rp_rate', 0.2) * emergency_factor,   'damping', self.normalized_dict['omega'][:2]),
            (r_eff,       weights.get('efficiency', 0.8) * emergency_factor, 'efficiency', [pair_error, balance_error]),
            (r_smooth,    weights.get('smoothness', 0.1) * emergency_factor, 'smoothness', smoothness_error)
        ]

        base_reward = 0.0
        if self.reward_type == "multiplicative":
            # Mysore/RE+AL Logik: Geometrisches Mittel
            weighted_log_sum = 0.0
            total_weight = 0.0
            for val, w, key, error in comp_data:
                weighted_log_sum += w * np.log(max(val, eps))
                total_weight += w
            base_reward = float(np.exp(weighted_log_sum / total_weight))
        
        elif self.reward_type == "additive":
            # Klassisch Arithmetisch
            weighted_sum = sum(val * w for val, w, key, error in comp_data)
            total_weight = sum(w for val, w, key in comp_data)
            base_reward = float(weighted_sum / total_weight)

        # Der Safety-Veto Term wirkt immer multiplikativ als "harter Constraint"
        final_reward = base_reward * (r_safety_veto ** weights.get('safety_zone', 1.0))

        # --- 3. LOGGING (Dein Stil) ---
        for val, w, key, error in comp_data:
            self.reward.terms[key] = {'w': w, 'r': val, 'error': error}
        
        self.reward.terms['safety_veto'] = {'w': weights.get('safety_zone', 1.0), 'r': r_safety_veto}
        self.reward.base = final_reward
        
        return final_reward

    def _compute_reward_terms_old(self) -> float:
        """Calculates the reward, heavily focused on velocity tracking."""

        # --- 0. PRE-CALCULATIONS ---

        self.integral_error_pos_world = 0.999* self.integral_error_pos_world + (self.R_world_to_body().T @ self.error.vel_c) * self.dt
        self.integral_error [0:3] = self.R_world_to_body() @ self.integral_error_pos_world
        self.integral_error [3:6] = 0.999* self.integral_error [3:6] + self.error.rpy_deg * self.dt
        
        self.integral_error[0:3] = np.clip(self.integral_error[0:3], -self.integral_limit_vel, self.integral_limit_vel)
        self.integral_error[3:6] = np.clip(self.integral_error[3:6], -self.integral_limit_rpy_deg, self.integral_limit_rpy_deg)

        self.integral_error_norm = np.concatenate([
            self.integral_error[0:3]/self.integral_limit_vel, 
            self.integral_error[3:6]/self.integral_limit_rpy_deg
        ])

        # SAFETY FLOOR für Integral: Verhindert 0.0 im geometrischen Mittel
        #integral_reward_vec = self._calculate_reward_from_error(self.integral_error_norm)
        #integral_reward = max(float(0.5*np.mean(integral_reward_vec)+0.5*np.min(integral_reward_vec)), 0.01)
        
        # Strict Integral: Use min() to punish worst axis, and steep reward curve (factor -6.0)
        norm_abs_error = np.abs(np.clip(self.integral_error_norm, -1, 1))
        integral_reward_vec = np.exp(-6.0 * norm_abs_error) 
        integral_reward = max(float(np.min(integral_reward_vec)), 0.001)

        # --- 1. BASIC REWARD TERMS ---
        
        # Velocity
        vel_reward_vec = self._calculate_reward_from_error(self.normalized_dict['error_vel'])
        vel_reward = float(0.5*np.mean(vel_reward_vec)+0.5*np.min(vel_reward_vec))

        # Attitude (Roll/Pitch)
        rp_reward_vec = self._calculate_reward_from_error(self.normalized_dict['error_rpy'][:2])
        rp_reward = float(0.5*np.mean(rp_reward_vec)+0.5*np.min(rp_reward_vec))

        # Yaw
        yaw_reward_vec = self._calculate_reward_from_error(self.normalized_dict['error_rpy'][2])
        yaw_reward = float(yaw_reward_vec)

        # Rates & Accel
        omega_reward_vec = self._calculate_reward_from_error(self.normalized_dict['omega'])
        omega_reward = float(0.5*np.mean(omega_reward_vec)+0.5*np.min(omega_reward_vec))

        accel_reward_vec = self._calculate_reward_from_error(self.normalized_dict['accel'])
        accel_reward = float(0.5*np.mean(accel_reward_vec)+0.5*np.min(accel_reward_vec))

        # Paired Efficiency
        pair_error = np.abs(self.action.cmd[[1,0,2,3]] - self.action.cmd[[4,5,7,6]]) / 200 
        paired_efficiency_reward = float(np.prod(self._calculate_reward_from_error(pair_error))**(1/4))

        # Balance (Energy)
        balance_error = np.mean(np.square(self.action.cmd/self.limits.motor.range))
        balance_reward = np.exp(-balance_error * 1.5) 

        # Comfort Zone
        lower_bound = self.limits.motor.min + 0.25 * self.limits.motor.range
        upper_bound = self.limits.motor.min + 0.75 * self.limits.motor.range
        MIN_REWARD_AT_EDGE = 0.3 
        xp = [self.limits.motor.min, lower_bound, upper_bound, self.limits.motor.max]
        fp = [MIN_REWARD_AT_EDGE, 1.0, 1.0, MIN_REWARD_AT_EDGE]
        safety_zone_reward = np.interp(min(self.action.cmd), xp, fp )

        # Smoothness
        action_delta = self.action.box 
        smoothness_error = np.mean(np.square(action_delta)) 
        smoothness_error = np.clip(smoothness_error, 0, 1)
        smoothness_reward = self._calculate_reward_from_error(np.array([smoothness_error]))[0]

        # --- 2. DYNAMIC WEIGHTING (DW) ---
        
        #vel_err_norm = np.clip(np.linalg.norm(self.normalized_dict['error_vel']), 0, 1)
        #emergency_factor = np.exp(-10.0 * vel_err_norm)
        emergency_weights = 0 if max(self.normalized_dict['error_vel'])>0.3 else 1.0
        # Constraint-Faktor

        weights = self.reward_weights
        
        # Gewichte definieren (Dynamisch!)
        w_vel      = weights.get('vel', 3.0)       # Bleibt stark
        w_int      = weights.get('integral', 1.5)  # Bleibt stark
        w_yaw      = weights.get('yaw', 1.5)       # Bleibt stark
        
        # Diese hier werden ausgeblendet bei Panik:
        w_rp       = weights.get('rollpitch', 0.1)         * emergency_weights 
        w_paired   = weights.get('paired_efficiency', 1.0) * emergency_weights
        w_balance  = weights.get('balance', 0.5)           * emergency_weights
        w_smooth   = weights.get('smoothness', 0.1)        * emergency_weights
        w_accel    = weights.get('accel', 0.1)             * emergency_weights
        w_omega    = weights.get('omega', 0.1)             * emergency_weights

        base_reward = 0.0 

        # --- 3. CALCULATION ---

        if self.reward_type == "multiplicative":
            # Liste von Tupeln: (Reward_Wert, Gewicht)
            # WICHTIG: Wir übergeben hier r und w getrennt, um korrekt zu summieren!
            components = [
                (vel_reward, w_vel),
                (integral_reward, w_int),
                (rp_reward, w_rp),
                (yaw_reward, w_yaw),
                (omega_reward, w_omega),
                (accel_reward, w_accel),
                (paired_efficiency_reward, w_paired),
                (balance_reward, w_balance),
                (smoothness_reward, w_smooth)
            ]

            weighted_log_sum = 0.0
            total_weight_sum = 0.0

            for r_val, w_val in components:
                # Log-Trick für numerische Stabilität (verhindert log(0))
                # Wir clippen den Reward leicht
                r_safe = np.clip(r_val, 1e-6, 1.0)
                
                weighted_log_sum += w_val * np.log(r_safe)
                total_weight_sum += w_val
            
            # Das echte gewichtete Geometrische Mittel:
            # exp( sum(w * log(r)) / sum(w) )
            if total_weight_sum > 0:
                base_reward = float(np.exp(weighted_log_sum / total_weight_sum))
            else:
                base_reward = 0.0
            
            # Comfort Zone bleibt ein harter Multiplikator (Veto-Recht)
            base_reward *= (safety_zone_reward ** weights.get('safety_zone', 1.0))
        
        elif self.reward_type == "additive":
            # Additiv ist einfacher, aber hier auch mit dynamischen Gewichten aktualisieren
            terms = [
                (w_int,     integral_reward),
                (w_vel,     vel_reward),
                (w_rp,      rp_reward),
                (w_yaw,     yaw_reward),
                (w_omega,   omega_reward),
                (w_accel,   accel_reward),
                (w_paired,  paired_efficiency_reward),
                (w_balance, balance_reward),
                (w_smooth,  smoothness_reward)
            ]
            weighted_sum = sum(w * r for w, r in terms)
            total_weight = sum(w for w, r in terms)
            
            if total_weight > 0:
                base_reward = float(weighted_sum / total_weight)
            else:
                base_reward = 0.0
            
            base_reward *= (safety_zone_reward ** weights.get('safety_zone', 1.0))
        
        # Log the components for analysis
        self.reward.terms['integral']           = {'w': w_int,           'r': integral_reward, 'error': self.integral_error_norm}
        self.reward.terms['vel_tracking']       = {'w': w_vel,                'r': vel_reward, 'error': self.normalized_dict['error_vel']}
        self.reward.terms['roll_pitch']         = {'w': w_rp,          'r': rp_reward, 'error': self.normalized_dict['error_rpy'][:2]}
        self.reward.terms['yaw']                = {'w': w_yaw,                'r': yaw_reward, 'error': self.normalized_dict['error_rpy'][2]}
        self.reward.terms['omega']              = {'w': w_omega,              'r': omega_reward, 'error': self.normalized_dict['omega']}
        self.reward.terms['accel']              = {'w': w_accel,              'r': accel_reward, 'error': self.normalized_dict['accel']}
        self.reward.terms['safety_zone']        = {'w': weights.get('safety_zone', 1.0),       'r': safety_zone_reward, 'error': (np.abs(self.limits.motor.range/2)-self.action.cmd)}
        self.reward.terms['paired_efficiency']  = {'w': w_paired,  'r': paired_efficiency_reward, 'error': pair_error}
        self.reward.terms['balance']            = {'w': w_balance,            'r': balance_reward, 'error': balance_error}
        self.reward.terms['smoothness']         = {'w': w_smooth,         'r': smoothness_reward, 'error': smoothness_error}
        self.reward.base = base_reward
        
        return base_reward
    