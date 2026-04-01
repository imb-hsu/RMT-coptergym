import numpy as np
from gymnasium import spaces
from typing import Dict, Any

from rmt_coptergym.base_envs.RMT_Hybrid_Env import RMT_Hybrid_Env

class VEL_Env(RMT_Hybrid_Env):
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

        self.scaling_delta_action = 50 # scaling how many rads we want to change for each step

    def build_state_obs_space(self) -> spaces.Dict:
        """Defines the 'state' part of the observation space for velocity tracking."""
        # The agent primarily needs to know its velocity error and attitude error for stability.
        return spaces.Dict({
            "vel_error":    spaces.Box(low=-1.0, high=1.0, shape=(3,), dtype=np.float32),
            "rpy_error":    spaces.Box(low=-1.0, high=1.0, shape=(3,), dtype=np.float32),
            "current_accel":    spaces.Box(low=-1.0, high=1.0, shape=(3,), dtype=np.float32),
        })

    def get_state_observation(self) -> dict:
        """Constructs the 'state' part of the observation dictionary."""
        return {
            "vel_error": self.normalized_dict['error_vel'],
            "rpy_error": self.normalized_dict['error_rpy'],
            "current_accel": self.normalized_dict['accel'],
        }

    def build_action_space(self):
        """
        Defines the action space for the agent (e.g., direct motor commands).
        This method is called by RMT_Base's __init__ to set self.action_space.
        This implementation is common for most low-level control tasks.
        Environments requiring a different action space (e.g., high-level commands)
        can override this method.
        """
        if self.action_space_type == "Box":
            # 8 motors, normalized continuous actions between -1 and 1
            # 3 times pos tagrets and 3 time rpy targets
            self.action_space = spaces.Box(low=-1.0, high=1.0, shape=(8,), dtype=np.float32)
        else:
            raise ValueError(f"Unsupported action_space_type:")
    
    def _transform_action(self, delta_action):
        """
        custom relative overwrite from Base_Env
        """
        if self.action_space_type == "Box": 
            self.action.cmd = delta_action *  self.scaling_delta_action

            self.action.box = delta_action
            self.action.disc = None #np.clip(motor_commands_disc, 0, 100).astype(np.int32)
        else:
            raise ValueError(f"Error: Unsupported action_space_type:")

    def _compute_reward_terms(self) -> float:
        """Calculates the reward, heavily focused on velocity tracking."""

        # --- 1. Velocity Reward (Hauptziel) ---
        vel_reward_vec = self._calculate_reward_from_error(self.normalized_dict['error_vel'])
        vel_reward = float(0.5*np.mean(vel_reward_vec)+0.5*np.min(vel_reward_vec))

        # --- 2. Attitude Stability Reward (Wichtige Nebenbedingung) ---
        # Bestrafe Abweichungen von der aufrechten Lage
        # Hier nehmen wir den normalisierten Zustand, nicht den Fehler!
        rp_reward_vec = self._calculate_reward_from_error(self.normalized_dict['error_rpy'][:2]) # Nur Roll/Pitch
        rp_reward = float(0.5*np.mean(rp_reward_vec)+0.5*np.min(rp_reward_vec))

        yaw_reward_vec = self._calculate_reward_from_error(self.normalized_dict['error_rpy'][2]) # Nur Yaw
        yaw_reward = float(yaw_reward_vec)

        omega_reward_vec = self._calculate_reward_from_error(self.normalized_dict['omega'])
        omega_reward = float(0.5*np.mean(omega_reward_vec)+0.5*np.min(omega_reward_vec))

        accel_reward_vec = self._calculate_reward_from_error(self.normalized_dict['accel'])
        accel_reward = float(0.5*np.mean(accel_reward_vec)+0.5*np.min(accel_reward_vec))

        
        # --- 6. NEU: Control Smoothness Reward (Der "D-Anteil") ---
        action_delta =  self.action.box 
        smoothness_error = np.mean(np.square(action_delta)) #np.linalg.norm(action_delta) / (50+15)
        smoothness_error = np.clip(smoothness_error, 0, 1) # Sicherstellen, dass es [0,1] ist
        
        # Fehler in einen Reward umwandeln
        smoothness_reward = self._calculate_reward_from_error(np.array([smoothness_error]))[0]

        weights = self.reward_weights # Das Dictionary aus der __init__
         
        terms = [
                (weights.get('vel', 1.0),                vel_reward),
                (weights.get('rollpitch', 1.0),          rp_reward),
                (weights.get('yaw', 1.0),                yaw_reward),
                (weights.get('omega', 1.0),              omega_reward),
                (weights.get('accel', 1.0),              accel_reward),
                #(weights.get('paired_efficiency', 1.0),  paired_efficiency_reward),
                #(weights.get('balance', 1.0),            balance_reward),
                (weights.get('smoothness', 1.0),         smoothness_reward)
            ]

        # 1. Berechne die gewichtete Summe
        weighted_sum = sum(w * r for w, r in terms)

        # 2. Berechne die Summe der Gewichte (für die Normalisierung)
        total_weight = sum(w for w, r in terms)

        # 3. Normalisierter Basis-Reward (0 bis 1)
        if total_weight > 0:
            additive_base = weighted_sum / total_weight
        else:
            additive_base = 0.0

        # 4. Multipliziere mit der Comfort Zone (Hard Constraint bleibt multiplikativ)
        # Das ist gut so! Wenn er die Comfort Zone verlässt, soll der Reward einbrechen,
        # egal wie gut die Summe ist.
        base_reward = float(additive_base) #* (comfort_zone_reward ** weights.get('comfort_zone', 1.0))
        
        # Log the components for analysis
        self.reward.terms['vel_tracking']       = {'w': weights.get('vel', 1.0),                'r': vel_reward, 'error': self.normalized_dict['error_vel']}
        self.reward.terms['roll_pitch']         = {'w': weights.get('rollpitch', 1.0),          'r': rp_reward, 'error': self.normalized_dict['error_rpy'][:2]}
        self.reward.terms['yaw']                = {'w': weights.get('yaw', 1.0),                'r': yaw_reward, 'error': self.normalized_dict['error_rpy'][2]}
        self.reward.terms['omega']              = {'w': weights.get('omega', 1.0),              'r': omega_reward, 'error': self.normalized_dict['omega']}
        self.reward.terms['accel']              = {'w': weights.get('accel', 1.0),              'r': accel_reward, 'error': self.normalized_dict['accel']}
        #self.reward.terms['comfort_zone']       = {'w': weights.get('comfort_zone', 1.0),       'r': comfort_zone_reward, 'error': (np.abs(self.limits.motor.range/2)-self.action.cmd)}
        #self.reward.terms['paired_efficiency']  = {'w': weights.get('paired_efficiency', 1.0),  'r': paired_efficiency_reward, 'error': pair_error}
        #self.reward.terms['balance']            = {'w': weights.get('balance', 1.0),            'r': balance_reward, 'error': balance_error}
        self.reward.terms['smoothness']         = {'w': weights.get('smoothness', 1.0),         'r': smoothness_reward, 'error': smoothness_error}
        self.reward.base = base_reward
        
        return base_reward
    