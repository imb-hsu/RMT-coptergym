import numpy as np
from gymnasium import spaces

# Import the RL base class from its new location
from rmt_coptergym.base_envs.RMT_RL_Env import RMT_RL_Env

class CopterHoverEnv(RMT_RL_Env):
    """
    A concrete RL environment for a hover task.
    The agent's goal is to maintain a stable hover at a specified target position.
    """

    def __init__(self, **kwargs):
        # Set the default dataset for this specific hover task.
        # The MissionManager will load this from the .npz file.
        kwargs.setdefault('dataset_name', 'Stabilize_In_Place')
        super().__init__(**kwargs)

    def build_action_space(self):
        """Defines the action space for the agent."""
        if self.action_space_type == "Box":
            # 8 motors, normalized between -1 and 1
            self.action_space = spaces.Box(low=-1.0, high=1.0, shape=(8,), dtype=np.float32)
        elif self.action_space_type == "MDisc":
            # 8 motors, discrete values of 0-100
            self.action_space = spaces.MultiDiscrete([101] * 8)
        else:
            raise ValueError(f"Unsupported action_space_type: {self.action_space_type}")

    def build_state_space(self) -> spaces.Dict:
        """Defines the 'state' part of the observation space for the hover task."""
        # Define the bounds for each observation component
        return spaces.Dict({
            "vel_c": spaces.Box(low=-1.0, high=1.0, shape=(3,), dtype=np.float32),
            "rpy": spaces.Box(low=-1.0, high=1.0, shape=(3,), dtype=np.float32),
            "omega": spaces.Box(low=-1.0, high=1.0, shape=(3,), dtype=np.float32),
            "pos": spaces.Box(low=-1.0, high=1.0, shape=(3,), dtype=np.float32),
            "motor_signal": spaces.Box(low=0.0, high=1.0, shape=(8,), dtype=np.float32),
        })

    def get_state_observation(self) -> dict:
        """Constructs the 'state' part of the observation dictionary."""
        return {
            "vel_c": self.norm_state['vel_c'],
            "rpy": self.norm_state['rpy'],
            "omega": self.norm_state['omega'],
            "pos": self.norm_state['pos'],
            "motor_signal": self._normalize_vector(self.agent.motor_signal, self.limits.motor.min, self.limits.motor.max, target_min=0.0, target_max=1.0),
        }

    def _compute_reward_terms(self) -> float:
        """Calculates the reward for the hover task."""
        # Position reward: exponential decay based on distance
        pos_reward = np.exp(-2.0 * self.target.distance)
        self.reward.terms['pos'] = pos_reward

        # Velocity reward: exponential decay based on velocity error
        vel_error_norm = np.linalg.norm(self.error.vel_c)
        vel_reward = np.exp(-0.5 * vel_error_norm)
        self.reward.terms['vel'] = vel_reward

        # Attitude reward: penalize roll and pitch
        rpy_error_norm = np.linalg.norm(self.agent.rpy_rad[:2]) # Only roll and pitch
        att_reward = np.exp(-1.0 * rpy_error_norm)
        self.reward.terms['att'] = att_reward

        # Control effort penalty: penalize large changes in action
        action_delta = np.linalg.norm(self.action.cmd - self.action.cmd_old)
        smoothness_penalty = np.exp(-0.001 * action_delta)
        self.reward.terms['smoothness'] = smoothness_penalty

        # Combine rewards
        if self.reward_type == "multiplicative":
            total_reward = pos_reward * vel_reward * att_reward * smoothness_penalty
        else: # Additive
            total_reward = 0.4 * pos_reward + 0.2 * vel_reward + 0.2 * att_reward + 0.2 * smoothness_penalty

        return total_reward
