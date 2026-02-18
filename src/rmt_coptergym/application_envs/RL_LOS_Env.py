import numpy as np
from gymnasium import spaces

from rmt_coptergym.base_envs.RMT_RL_Env import RMT_RL_Env

class LOS_Env(RMT_RL_Env):
    """
    Line-of-Sight (LOS) Navigation Environment.
    The agent learns to navigate towards a "lookahead" point on the direct
    line to the final target, rather than the final target itself. This
    encourages smoother trajectories.
    This class is independent but structurally similar to E2E_Env.
    """

    def __init__(self, 
                 lookahead_distance: float = 1.0,
                 reward_type: str = 'additive',
                 reward_shaping_func: str = 'exponential',
                 **kwargs):
        """
        Args:
            lookahead_distance (float): The distance of the virtual target point
                                        from the agent along the line to the final goal.
            reward_type (str): How reward components are combined.
            reward_shaping_func (str): The function mapping error to reward.
            **kwargs: Arguments passed to the parent RMT_RL_Env class.
        """
        if reward_type not in ['additive', 'multiplicative', 'combined', 'simple']:
            raise ValueError(f"Invalid reward_type: {reward_type}.")
        if reward_shaping_func not in ['exponential', 'squared_exponential']:
            raise ValueError(f"Invalid reward_shaping_func: {reward_shaping_func}.")

        self.lookahead_distance = lookahead_distance
        self.reward_type = reward_type
        self.reward_shaping_func = reward_shaping_func
        
        self.reward_scaling = {
            'pos': 1.5, 'vel': 0.5, 'att': 0.8, 'omega': 0.01, 'action': 0.001
        }
        
        # The actual dataset is now passed directly from the training script via kwargs.
        super().__init__(**kwargs)

    def _update_navigation_targets(self):
        """
        Overrides the parent method to implement the LOS logic.
        It calculates a new, intermediate target based on the lookahead distance.
        """

        ## WORK RO DO HERE!

        # First, let the base class calculate its standard navigation targets
         # Error to the final waypoint is already in self.error.pos
        self.nav_targets.error_to_final_goal = self.error.pos

        # Calculate Line-of-Sight (LOS) lookahead point
        direction_to_goal = self.error.pos / (np.linalg.norm(self.error.pos) + 1e-6)
        self.nav_targets.lookahead_point = self.agent.pos + direction_to_goal * self.lookahead_distance

        # Calculate error to the moving lookahead point
        self.nav_targets.error_to_lookahead_point = self.nav_targets.lookahead_point - self.agent.pos

        # Now, calculate the LOS target
        agent_pos = self.agent.pos
        final_target_pos = self.target.pos
        vector_to_target = final_target_pos - agent_pos
        distance_to_target = self.target.distance

        if distance_to_target > 1e-6:
            direction_to_target = vector_to_target / distance_to_target
            los_target_pos = agent_pos + direction_to_target * self.lookahead_distance
            # Overwrite the position target. This will be used by this class's
            # reward and observation logic in the current step.
            self.target.pos = los_target_pos

    # --- The following methods are copied from E2E_Env for independence ---

    def build_state_obs_space(self) -> spaces.Dict:
        return spaces.Dict({
            "pos_error":    spaces.Box(low=-1.0, high=1.0, shape=(3,), dtype=np.float32),
            "vel_error":    spaces.Box(low=-1.0, high=1.0, shape=(3,), dtype=np.float32),
            "rpy_error":    spaces.Box(low=-1.0, high=1.0, shape=(3,), dtype=np.float32),
        })

    def get_state_observation(self) -> dict:
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
        scaled_error = self.reward_scaling[scaling_key] * error_norm
        if self.reward_shaping_func == 'exponential':
            return np.exp(-scaled_error)
        elif self.reward_shaping_func == 'squared_exponential':
            return np.exp(-(scaled_error**2))
        return 0.0

    def _compute_reward_terms(self) -> float:
        # This implementation is identical to E2E_Env's reward logic.
        # It calculates rewards based on the (potentially modified by LOS) target.
        pos_reward = self._shape_reward(self.target.distance, 'pos')

        vel_reward = 1.0
        if hasattr(self.target, 'vel_c') and not np.any(np.isnan(self.target.vel_c)):
            vel_reward = self._shape_reward(np.linalg.norm(self.error.vel_c), 'vel')

        att_reward = 1.0
        if hasattr(self.target, 'rpy_rad') and not np.any(np.isnan(self.target.rpy_rad)):
            att_reward = self._shape_reward(np.linalg.norm(self.error.rpy_rad), 'att')
        else:
            att_reward = self._shape_reward(np.linalg.norm(self.agent.rpy_rad[:2]), 'att')
 
        omega_reward = self._shape_reward(np.linalg.norm(self.agent.omega), 'omega')
        smoothness_reward = self._shape_reward(np.linalg.norm(self.action.cmd - self.action.cmd_old), 'action')

        if self.reward_type == 'additive':
            weights = {'pos': 0.4, 'vel': 0.2, 'att': 0.15, 'omega': 0.1, 'smooth': 0.15}
            return (weights['pos'] * pos_reward + weights['vel'] * vel_reward + 
                    weights['att'] * att_reward + weights['omega'] * omega_reward +
                    weights['smooth'] * smoothness_reward)
        
        elif self.reward_type == 'multiplicative':
            vel_term = vel_reward if not np.any(np.isnan(self.target.vel_c)) else 1.0
            return pos_reward * att_reward * omega_reward * smoothness_reward * vel_term
        
        # Other reward types from E2E_Env could be copied here if needed.
        return pos_reward # Default to simple position reward