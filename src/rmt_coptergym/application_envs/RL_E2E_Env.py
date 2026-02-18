import numpy as np
from gymnasium import spaces

from rmt_coptergym.base_envs.RMT_RL_Env import RMT_RL_Env

class E2E_Env(RMT_RL_Env):
    """
    End-to-End Navigation Environment for trajectory tracking.
    This environment implements the core research task of comparing different
    observation representations (Absolute vs. Line-of-Sight) for controlling a drone.
    Corresponds to Task 2.2 in the project plan.
    """

    def __init__(self, 
                reward_type: str = 'additive',
                **kwargs):
        """
        Args:
            reward_type (str):  How the reward components are combined.
                                Options: 'additive', 'multiplicative', 'combined', 'simple'.

            **kwargs: Arguments passed to the parent classes.
        """
        if reward_type not in ['additive', 'multiplicative', 'combined', 'simple']:
            raise ValueError(f"Invalid reward_type: {reward_type}. Must be 'additive', 'multiplicative', 'combined', or 'simple'.")
            
        self.reward_type = reward_type
        
        
        
        # Call the parent constructor FIRST, passing all kwargs up the chain.
        # RMT_RL_Env and RMT_Base will pick out the arguments they need.
        super().__init__(**kwargs)

    def build_state_obs_space(self) -> spaces.Dict:
        """Defines the 'state' part of the observation space."""
        # This is the 'dynamic_obs' part, containing the error terms.
        return spaces.Dict({
            "pos_error":    spaces.Box(low=-1.0, high=1.0, shape=(3,), dtype=np.float32),
            "vel_error":    spaces.Box(low=-1.0, high=1.0, shape=(3,), dtype=np.float32),
            "rpy_error":    spaces.Box(low=-1.0, high=1.0, shape=(3,), dtype=np.float32),
        })

    def get_state_observation(self) -> dict:
        """Constructs the 'state' part of the observation dictionary."""
        # This populates the 'dynamic_obs' (error) part of the observation.
        
        # If a target is not defined (NaN), the normalized error should be zero.
        norm_pos_err = np.zeros(3)
        if not np.any(np.isnan(self.error.pos)):
            norm_pos_err = self._normalize_vector(self.error.pos, -self.norm_pos_range, self.norm_pos_range)

        norm_vel_err = np.zeros(3)
        if not np.any(np.isnan(self.error.vel_c)):
            norm_vel_err = self._normalize_vector(self.error.vel_c, self.norm_vel_min, self.norm_vel_max)

        norm_rpy_err = np.zeros(3)
        if not np.any(np.isnan(self.error.rpy_rad)):
            norm_rpy_err = self._normalize_vector(self.error.rpy_rad, self.norm_rad_min, self.norm_rad_max)

        return {
            "pos_error": norm_pos_err.astype(np.float32),
            "vel_error": norm_vel_err.astype(np.float32),
            "rpy_error": norm_rpy_err.astype(np.float32),
        }
    
    def _shape_reward(self, error_norm: float, scaling_key: str) -> float:
        """Central function to shape an error norm into a reward in [0, 1]."""
        scaled_error = self.reward_scaling[scaling_key] * error_norm
        if self.reward_shaping_func == 'exponential':
            return np.exp(-scaled_error)
        elif self.reward_shaping_func == 'squared_exponential':
            # This penalizes small errors less, but large errors more severely.
            return np.exp(-(scaled_error**2))
        return 0.0

    def _compute_reward_terms(self) -> float:
        """Calculates the reward for the trajectory tracking task."""
        # --- 1. Calculate Individual Reward Components using the shaping function ---
        self.reward.terms = {} # Reset terms dict

        # Position reward
        pos_reward = self._shape_reward(self.target.distance, 'pos')

        # Velocity reward (only if a velocity target is defined)
        vel_reward = 1.0 # Default to perfect reward if no target is set
        if hasattr(self.target, 'vel_c') and not np.any(np.isnan(self.target.vel_c)):
            vel_error_norm = np.linalg.norm(self.error.vel_c)
            vel_reward = self._shape_reward(vel_error_norm, 'vel')

        # Generalized Attitude reward
        att_reward = 1.0 # Default to perfect reward
        if hasattr(self.target, 'rpy_rad') and not np.any(np.isnan(self.target.rpy_rad)):
            # Case 1: Track a specific attitude target
            att_error_norm = np.linalg.norm(self.error.rpy_rad)
            att_reward = self._shape_reward(att_error_norm, 'att')
        else:
            # Case 2: No attitude target, just maintain stability (penalize roll/pitch)
            att_instability = np.linalg.norm(self.agent.rpy_rad[:2])
            att_reward = self._shape_reward(att_instability, 'att')
 
        # Angular velocity reward: penalize high rotation rates
        omega_reward = self._shape_reward(np.linalg.norm(self.agent.omega), 'omega')
 
        # Control smoothness reward: penalize large changes in motor commands
        action_delta = np.linalg.norm(self.action.cmd - self.action.cmd_old)
        smoothness_reward = self._shape_reward(action_delta, 'action')

        # --- 2. Combine Components Based on Selected Reward Type ---
        base_reward = 0.0
        if self.reward_type == 'additive':
            # Weighted sum of all components
            weights = {'pos': 0.4, 'vel': 0.2, 'att': 0.15, 'omega': 0.1, 'smooth': 0.15}
            base_reward = (weights['pos'] * pos_reward + 
                           weights['vel'] * vel_reward + 
                           weights['att'] * att_reward + 
                           weights['omega'] * omega_reward +
                           weights['smooth'] * smoothness_reward)
            self.reward.terms = {
                'weighted_additive': {
                    'pos': {'w': weights['pos'], 'r': pos_reward},
                    'vel': {'w': weights['vel'], 'r': vel_reward},
                    'att': {'w': weights['att'], 'r': att_reward},
                    'omega': {'w': weights['omega'], 'r': omega_reward},
                    'smooth': {'w': weights['smooth'], 'r': smoothness_reward},
                }
            }
        
        elif self.reward_type == 'multiplicative':
            # Product of components. Penalizes any single failure heavily.
            # Give velocity a lower impact if not explicitly targeted
            vel_term = vel_reward if not np.any(np.isnan(self.target.vel_c)) else 1.0
            base_reward = pos_reward * att_reward * omega_reward * smoothness_reward * vel_term
            self.reward.terms = {
                'multiplicative': {
                    'pos': pos_reward, 'vel': vel_term, 'att': att_reward, 
                    'omega': omega_reward, 'smooth': smoothness_reward
                }
            }

        elif self.reward_type == 'combined':
            # Combine static (positional) and dynamic (control) aspects separately
            static_weights = {'pos': 0.7, 'att': 0.3}
            dynamic_weights = {'vel': 0.4, 'omega': 0.3, 'smooth': 0.3}
            
            static_reward = static_weights['pos'] * pos_reward + static_weights['att'] * att_reward
            dynamic_reward = (dynamic_weights['vel'] * vel_reward + 
                              dynamic_weights['omega'] * omega_reward + 
                              dynamic_weights['smooth'] * smoothness_reward)
            
            base_reward = 0.7 * static_reward + 0.3 * dynamic_reward
            self.reward.terms = {
                'combined': {
                    'static_group': {'w': 0.7, 'r': static_reward, 'terms': {'pos': pos_reward, 'att': att_reward}},
                    'dynamic_group': {'w': 0.3, 'r': dynamic_reward, 'terms': {'vel': vel_reward, 'omega': omega_reward, 'smooth': smoothness_reward}}
                }
            }
        
        elif self.reward_type == 'simple':
            # Focus on the primary task: get to the position and be stable
            weights = {'pos': 0.5, 'vel': 0.3, 'att': 0.2}
            base_reward = (weights['pos'] * pos_reward + 
                           weights['vel'] * vel_reward + 
                           weights['att'] * att_reward)
            self.reward.terms = {
                'simple_additive': {
                    'pos': {'w': weights['pos'], 'r': pos_reward},
                    'vel': {'w': weights['vel'], 'r': vel_reward},
                    'att': {'w': weights['att'], 'r': att_reward},
                }
            }
        
        return base_reward