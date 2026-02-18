import numpy as np
from gymnasium import spaces
from typing import Dict, Any

from rmt_coptergym.base_envs.RMT_RL_Env import RMT_RL_Env

class VEL_Env(RMT_RL_Env):
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
            "vel": 1.0,
            "rollpitch": 1.0,
            "yaw": 1.0,
            "omega": 1.0,
            "accel": 1.0,
            "comfort_zone": 1.0,
            "paired_efficiency": 1.0,
            "balance": 1.0,
            "smoothness": 0.1
        }
        if reward_weights is not None:
            default_weights.update(reward_weights)
        self.reward_weights = default_weights

        super().__init__(**kwargs)

        # Integral State
        self.dt = self.timestep * self.frame_skip
        self.integral_error = np.zeros(6)
        self.integral_error_pos_world = np.zeros(3)
        self.integral_error_norm = np.zeros(6)
        self.integral_limit_vel = 20*self.goal.tolerance.vel # m/s (Passend zur Scale 'int')
        self.integral_limit_rpy_deg = 10*self.goal.tolerance.rpy_deg

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
        self.integral_error = np.zeros(6)
        self.integral_error_norm = np.zeros(6)
        return super().reset(**kwargs)

    def build_state_obs_space(self) -> spaces.Dict:
        """Defines the 'state' part of the observation space for velocity tracking."""
        # The agent primarily needs to know its velocity error and attitude error for stability.

        return spaces.Dict({
            "vel_error":    spaces.Box(low=-1.0, high=1.0, shape=(3,), dtype=np.float32),
            "rpy_error":    spaces.Box(low=-1.0, high=1.0, shape=(3,), dtype=np.float32),
            "error_integral":   spaces.Box(low=-1.0, high=1.0, shape=(6,), dtype=np.float32),
            "current_accel":    spaces.Box(low=-1.0, high=1.0, shape=(3,), dtype=np.float32),
        })

    def get_state_observation(self) -> dict:
        """Constructs the 'state' part of the observation dictionary."""
        return {
            "vel_error": self.normalized_dict['error_vel'],
            "rpy_error": self.normalized_dict['error_rpy'],
            "error_integral": self.integral_error_norm,
            "current_accel": self.normalized_dict['accel'],
        }
    
    def _transform_action(self, delta_action):
        """
        custom relative overwrite from Base_Env
        """

        if self.action_space_type == "Box": 
            self.action.box = delta_action
            # Defined between -1 and 1, shifting to 0..1 and scale to motorlimits
            motor_commands_rads = self.action.cmd_old + 50*delta_action# ((action + 1)/2) * self.limits.motor.range + self.limits.motor.min
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

    def _compute_reward_terms(self) -> float:
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
        comfort_zone_reward = np.interp(min(self.action.cmd), xp, fp )

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
            base_reward *= (comfort_zone_reward ** weights.get('comfort_zone', 1.0))
        
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
            
            base_reward *= (comfort_zone_reward ** weights.get('comfort_zone', 1.0))
        
        # Log the components for analysis
        self.reward.terms['integral']           = {'w': w_int,           'r': integral_reward, 'error': self.integral_error_norm}
        self.reward.terms['vel_tracking']       = {'w': w_vel,                'r': vel_reward, 'error': self.normalized_dict['error_vel']}
        self.reward.terms['roll_pitch']         = {'w': w_rp,          'r': rp_reward, 'error': self.normalized_dict['error_rpy'][:2]}
        self.reward.terms['yaw']                = {'w': w_yaw,                'r': yaw_reward, 'error': self.normalized_dict['error_rpy'][2]}
        self.reward.terms['omega']              = {'w': w_omega,              'r': omega_reward, 'error': self.normalized_dict['omega']}
        self.reward.terms['accel']              = {'w': w_accel,              'r': accel_reward, 'error': self.normalized_dict['accel']}
        self.reward.terms['comfort_zone']       = {'w': weights.get('comfort_zone', 1.0),       'r': comfort_zone_reward, 'error': (np.abs(self.limits.motor.range/2)-self.action.cmd)}
        self.reward.terms['paired_efficiency']  = {'w': w_paired,  'r': paired_efficiency_reward, 'error': pair_error}
        self.reward.terms['balance']            = {'w': w_balance,            'r': balance_reward, 'error': balance_error}
        self.reward.terms['smoothness']         = {'w': w_smooth,         'r': smoothness_reward, 'error': smoothness_error}
        self.reward.base = base_reward
        
        return base_reward
    