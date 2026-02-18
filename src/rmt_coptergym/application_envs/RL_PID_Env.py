import numpy as np
from gymnasium import spaces

from rmt_coptergym.base_envs.RMT_RL_Env import RMT_RL_Env

class PID_Env(RMT_RL_Env):
    """
    Environment to train a PID-like controller.
    The observation space is augmented with the integral of the position error,
    and the reward function is specifically designed to minimize Proportional,
    Integral, and Derivative error terms.
    """

    def __init__(self, **kwargs):
        """
        Args:
            reward_shaping_func (str): The function mapping error to reward.
            **kwargs: Arguments passed to the parent RMT_RL_Env class.
        """
        self.error_integral = np.zeros(3)
        self.max_integral_val = 10.0  # Anti-windup limit

        # PID reward weights (can be tuned)
        self.pid_weights = {'P': 0.6, 'I': 0.1, 'D': 0.3}
        
        # For this environment, the reward structure is fixed via _compute_reward_terms.
        # The actual dataset is now passed directly from the training script via kwargs.
        super().__init__(**kwargs)

    def reset(self, **kwargs):
        # Reset the integral term at the start of each episode
        self.error_integral = np.zeros(3)
        return super().reset(**kwargs)

    def build_state_obs_space(self) -> spaces.Dict:
        """ Extends the base observation space with the error integral. """
        return spaces.Dict({
            "pos_error":      spaces.Box(low=-1.0, high=1.0, shape=(3,), dtype=np.float32),
            "vel_error":      spaces.Box(low=-1.0, high=1.0, shape=(3,), dtype=np.float32),
            "rpy_error":      spaces.Box(low=-1.0, high=1.0, shape=(3,), dtype=np.float32),
            "error_integral": spaces.Box(low=-1.0, high=1.0, shape=(3,), dtype=np.float32),
        })

    def get_state_observation(self) -> dict:
        """ Constructs the observation, including the normalized error integral. """
        # Update and clamp the error integral (anti-windup)
        # self.error.pos is the current position error, self.dt is the timestep duration
        self.error_integral += self.error.pos * self.dt
        np.clip(self.error_integral, -self.max_integral_val, self.max_integral_val, out=self.error_integral)

        # Get standard error observations (similar to E2E_Env)
        norm_pos_err = np.zeros(3)
        if not np.any(np.isnan(self.error.pos)):
            norm_pos_err = self._normalize_vector(self.error.pos, -self.norm_pos_range, self.norm_pos_range)

        norm_vel_err = np.zeros(3)
        if not np.any(np.isnan(self.error.vel_c)):
            norm_vel_err = self._normalize_vector(self.error.vel_c, self.norm_vel_min, self.norm_vel_max)

        norm_rpy_err = np.zeros(3)
        if not np.any(np.isnan(self.error.rpy_rad)):
            norm_rpy_err = self._normalize_vector(self.error.rpy_rad, self.norm_rad_min, self.norm_rad_max)

        # Add the normalized integral term
        norm_err_int = self._normalize_vector(self.error_integral, -self.max_integral_val, self.max_integral_val)

        return {
            "pos_error": norm_pos_err.astype(np.float32),
            "vel_error": norm_vel_err.astype(np.float32),
            "rpy_error": norm_rpy_err.astype(np.float32),
            "error_integral": norm_err_int.astype(np.float32),
        }

    def _shape_reward(self, error_norm: float, scaling_key: str) -> float:
        """Central function to shape an error norm into a reward in [0, 1]."""
        scaled_error = self.reward_scaling[scaling_key] * error_norm
        if self.reward_shaping_func == 'exponential':
            return np.exp(-scaled_error)
        return 0.0
        
    def _compute_reward_terms(self) -> float:
        """
        Computes a reward based on PID principles.
        - Proportional: Negative of the current error norm.
        - Integral: Negative of the integral error norm.
        - Derivative: Negative of the velocity error norm (change in position error).
        """
        # P-Term: Current position error
        p_term_reward = self._shape_reward(np.linalg.norm(self.error.pos), 'pos')

        # I-Term: Accumulated position error
        i_term_reward = self._shape_reward(np.linalg.norm(self.error_integral), 'vel') # Use 'vel' scaling as a proxy

        # D-Term: Current velocity error (approximates derivative of position error)
        d_term_reward = self._shape_reward(np.linalg.norm(self.error.vel_c), 'att') # Use 'att' scaling as a proxy

        # Weighted sum of the PID components
        reward = (self.pid_weights['P'] * p_term_reward +
                  self.pid_weights['I'] * i_term_reward +
                  self.pid_weights['D'] * d_term_reward)
        
        return reward