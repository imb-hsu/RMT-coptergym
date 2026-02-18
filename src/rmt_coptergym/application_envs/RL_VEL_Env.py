import numpy as np
from gymnasium import spaces

from rmt_coptergym.base_envs.RMT_RL_Env import RMT_RL_Env

class VEL_Env(RMT_RL_Env):
    """
    Velocity Control Environment.
    The agent's primary goal is to match a target velocity vector `target.vel_c`.
    The observation space is focused on velocity and attitude errors, ignoring
    positional error, to train a low-level velocity controller.
    """

    def __init__(self, **kwargs):
        """
        Args:
            **kwargs: Arguments passed to the parent RMT_RL_Env class.
        """
        # Call the parent constructor, passing all kwargs up the chain.
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

    def _compute_reward_terms(self) -> float:
        """Calculates the reward, heavily focused on velocity tracking."""

        # --- 1. Velocity Reward (Hauptziel) ---
        vel_reward_vec = self._calculate_reward_from_error(self.normalized_dict['error_vel'])
        vel_reward = float(0.5*np.mean(vel_reward_vec)+0.5*np.min(vel_reward_vec))

        # --- 2. Attitude Stability Reward (Wichtige Nebenbedingung) ---
        # Bestrafe Abweichungen von der aufrechten Lage
        # Hier nehmen wir den normalisierten Zustand, nicht den Fehler!
        att_reward_vec = self._calculate_reward_from_error(self.normalized_dict['rpy']) # Nur Roll/Pitch
        att_reward = float(0.5*np.mean(att_reward_vec)+0.5*np.min(att_reward_vec))

        # --- 3. Control Smoothness Reward (Effizienz) ---
        # Das ist bereits ein "D-Anteil" für die Aktionen, wichtig für Stabilität
        action_delta = self.action.cmd - self.action.cmd_old
        norm_action_delta = np.abs(action_delta) / 2.0 # Geht von [-2, 2] -> [0, 1]
        smoothness_reward = float(np.mean(self._calculate_reward_from_error(norm_action_delta)))

        # --- Kombination ---
        weights = {'vel': 0.5, 'att': 0.2, 'smooth': 0.3}
        base_reward = (weights['vel'] * vel_reward + 
                    weights['att'] * att_reward +
                    weights['smooth'] * smoothness_reward)
        
        base_reward = float(0.5*base_reward+0.5*np.min([vel_reward, att_reward, smoothness_reward]))
        
        # Log the components for analysis
        self.reward.terms['vel_tracking'] = {'w': weights['vel'], 'r': vel_reward, 'error': self.normalized_dict['error_vel']}
        self.reward.terms['stability'] = {'w': weights['att'], 'r': att_reward, 'error': self.normalized_dict['rpy']}
        self.reward.terms['smoothness'] = {'w': weights['smooth'], 'r': smoothness_reward, 'error': norm_action_delta}
        self.reward.base = base_reward
        
        return base_reward
    