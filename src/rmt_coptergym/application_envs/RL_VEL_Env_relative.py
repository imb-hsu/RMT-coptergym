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

        # --- 4. NEU: Paired Efficiency Reward (Dein physikalischer Ansatz) ---
        pair_error = np.abs(self.action.cmd[[1,0,2,3]] - self.action.cmd[[4,5,7,6]]) / 200 #self.limits.motor.range
        paired_efficiency_reward = float(np.mean(self._calculate_reward_from_error(pair_error)))

        # --- 5. NEU: Overall Balance Reward (Die globale Sicherheit) ---
        #std_dev_cmds = np.std(self.action.cmd)
        #balance_error = np.clip(std_dev_cmds / (0.5 * self.limits.motor.range), 0, 1)
        #balance_reward = self._calculate_reward_from_error(np.array([balance_error]))[0]
        balance_error = np.mean(np.square(self.action.cmd/self.limits.motor.range))
        balance_reward = np.exp(-balance_error * 1.5) 

        # Definiere die Grenzen der Komfortzone
        lower_bound = self.limits.motor.min + 0.25 * self.limits.motor.range # bei 35%
        upper_bound = self.limits.motor.min + 0.75 * self.limits.motor.range # bei 65%

        # Definiere den minimalen Reward an den Rändern (wichtig: nicht 0!)
        MIN_REWARD_AT_EDGE = 0.3 

        # Erstelle die Punkte für die Interpolation (die Ecken des Trapezoids)
        # x-Werte: die Motor-Kommandos
        xp = [self.limits.motor.min, lower_bound, upper_bound, self.limits.motor.max]
        # y-Werte: die entsprechenden Reward-Werte
        fp = [MIN_REWARD_AT_EDGE, 1.0, 1.0, MIN_REWARD_AT_EDGE]
        # Berechne den Reward durch lineare Interpolation
        comfort_zone_reward = np.interp(np.mean(self.action.cmd), xp, fp)

        # --- 6. NEU: Control Smoothness Reward (Der "D-Anteil") ---
        action_delta =  self.action.box 
        smoothness_error = np.mean(np.square(action_delta)) #np.linalg.norm(action_delta) / (50+15)
        smoothness_error = np.clip(smoothness_error, 0, 1) # Sicherstellen, dass es [0,1] ist
        
        # Fehler in einen Reward umwandeln
        smoothness_reward = self._calculate_reward_from_error(np.array([smoothness_error]))[0]

        weights = self.reward_weights # Das Dictionary aus der __init__
        
        # reward_components = np.array([
        #     vel_reward          ** weights.get('vel', 1.0),
        #     rp_reward           ** weights.get('rollpitch', 1.0),
        #     yaw_reward          ** weights.get('yaw', 1.0),
        #     omega_reward        ** weights.get('omega', 1.0),
        #     accel_reward        ** weights.get('accel', 1.0),
        #     paired_efficiency_reward ** weights.get('paired_efficiency', 1.0),
        #     balance_reward      ** weights.get('balance', 1.0),
        #     smoothness_reward   ** weights.get('smoothness', 1.0)
        # ])

        # epsilon = 1e-6
        # log_rewards = np.log(reward_components + epsilon)
        # base_reward = float(np.exp(np.mean(log_rewards)))*(comfort_zone_reward ** weights.get('comfort_zone', 1.0))
        
        terms = [
                (weights.get('vel', 1.0),                vel_reward),
                (weights.get('rollpitch', 1.0),          rp_reward),
                (weights.get('yaw', 1.0),                yaw_reward),
                (weights.get('omega', 1.0),              omega_reward),
                (weights.get('accel', 1.0),              accel_reward),
                (weights.get('paired_efficiency', 1.0),  paired_efficiency_reward),
                (weights.get('balance', 1.0),            balance_reward),
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
        base_reward = float(additive_base) * (comfort_zone_reward ** weights.get('comfort_zone', 1.0))
        
        # Log the components for analysis
        self.reward.terms['vel_tracking']       = {'w': weights.get('vel', 1.0),                'r': vel_reward, 'error': self.normalized_dict['error_vel']}
        self.reward.terms['roll_pitch']         = {'w': weights.get('rollpitch', 1.0),          'r': rp_reward, 'error': self.normalized_dict['error_rpy'][:2]}
        self.reward.terms['yaw']                = {'w': weights.get('yaw', 1.0),                'r': yaw_reward, 'error': self.normalized_dict['error_rpy'][2]}
        self.reward.terms['omega']              = {'w': weights.get('omega', 1.0),              'r': omega_reward, 'error': self.normalized_dict['omega']}
        self.reward.terms['accel']              = {'w': weights.get('accel', 1.0),              'r': accel_reward, 'error': self.normalized_dict['accel']}
        self.reward.terms['comfort_zone']       = {'w': weights.get('comfort_zone', 1.0),       'r': comfort_zone_reward, 'error': (np.abs(self.limits.motor.range/2)-self.action.cmd)}
        self.reward.terms['paired_efficiency']  = {'w': weights.get('paired_efficiency', 1.0),  'r': paired_efficiency_reward, 'error': pair_error}
        self.reward.terms['balance']            = {'w': weights.get('balance', 1.0),            'r': balance_reward, 'error': balance_error}
        self.reward.terms['smoothness']         = {'w': weights.get('smoothness', 1.0),         'r': smoothness_reward, 'error': smoothness_error}
        self.reward.base = base_reward
        
        return base_reward
    