import numpy as np
from gymnasium import spaces

from rmt_coptergym.base_envs.RMT_Base_Env import RMT_Base

class RMT_Hybrid_Env(RMT_Base):
    """
    A base class for Reinforcement Learning Copter Environments.
    It inherits from RMT_Base to manage the simulation and provides a rich set of
    default implementations for common RL tasks like observation normalization,
    termination checks, and reward shaping.

    This class introduces the RL-specific logic, such as observation/action
    spaces, reward calculation, and episode termination, which are implemented
    by concrete agent environments inheriting from this class. Which also merges
    teh ahndling of teh INDI CTRL_Env
    """

    metadata = {
        "reward_types": ["multiplicative", "additive", "progress", "distance", "goalregion"],
        "action_space_types": ["Box", "MDisc"],
        "mask_types": ["none", "smooth_cmd", "logical"]
    }

    def __init__(self,
                 action_space_type: str = "Box",
                 mask_type: str = None,
                 tolerance_position: float = 0.1,
                 tolerance_velocity: float = 0.1,
                 lookahead_distance: float = 2.0,
                 tolerance_attitude_deg: float = 0.5,
                 reward_type: str = "additive",
                 reward_function: str = 'exponential',
                 reward_time_penalty: float = 0.01,
                 reward_success_bonus: float = 10.0,
                 reward_failure_penalty: float = -10.0, #
                 anomaly_knowledge: bool = False,
                 **kwargs):
"""
        Initializes the RL Base Environment.
        It passes all configuration arguments to the underlying RMT_Base simulation.
        """

        # --- IMPORTANT ---
        # Force the use of the internal Flight Control System (FCS).
        # This is the key difference from the RL environments.
        kwargs['use_fcs'] = True
        self.delta_cmd_vel = np.array([0,0,0])
        self.delta_cmd_rpy = np.array([0,0,0])

        # Initialize the simulation base class with all provided arguments.
        # This calls the child's build_action_space and build_observation_space.

        self.lookahead_distance = lookahead_distance
        self.has_anomaly_knowledge = anomaly_knowledge
        # --- RL-specific setup ---
        self.action_space_type = action_space_type
        self.mask_type = mask_type
        if self.action_space_type not in self.metadata["action_space_types"]:
            raise ValueError(f"Unsupported action_space_type: {self.action_space_type}.")
        if self.mask_type not in self.metadata["mask_types"] and self.mask_type is not None:
            raise ValueError(f"Unsupported mask_type: {self.mask_type}.")
        if self.action_space_type == "Box" and self.mask_type not in [None, "none"]:
            print("ActionSpace Box is not supported with MaskedPPO, disabling Mask.")
            self.mask_type = None

        # --- Tolerances ---
        self.tolerance_position = tolerance_position
        self.tolerance_velocity = tolerance_velocity
        self.tolerance_attitude_deg = tolerance_attitude_deg
        self.tolerance_attitude_rad = np.deg2rad(tolerance_attitude_deg)

        # --- Reward Configuration ---
        self.reward_type = reward_type
        if self.reward_type not in self.metadata["reward_types"]:
            raise ValueError(f"Unsupported reward_type: {self.reward_type}.")
        self.reward_time_penalty = reward_time_penalty
        self.reward_success_bonus = reward_success_bonus
        self.reward_failure_penalty = reward_failure_penalty

        if reward_function not in ['exponential', 'squared_exponential']:
            raise ValueError(f"Invalid reward_function: {reward_function}.")
            
        self.reward_function = reward_function

        super().__init__(**kwargs)

        # Initialize a namespace for reward components
        self.reward = SimpleNamespace()
        self._reset_reward_terms()

    #MOST IMPORTANT PART INDI HANDLING HERE:

    def _update_task_specifics(self) -> None:
        """
        (Implements RMT_Base._update_task_specifics)
        This is where the benchmark logic happens. We calculate the desired
        velocity based on the position error to the current target, with
        dynamic damping to prevent overshoot.
        """
        # The base class's `_calculate_command_velocity` method has already
        # determined the ideal velocity command and stored it in `self.command.vel_c`.
        # The INDI environment's only task-specific action is to pass this
        # command directly to the simulation's internal flight controller.
        
        cmd = self.sim.pilot_cmd.vel_K_R_E_C_cmd_mDs
        cmd.u_K_R_E_C_cmd_mDs = self.command_vel[0] + self.delta_cmd_vel[0]
        cmd.v_K_R_E_C_cmd_mDs = self.command_vel[1] + self.delta_cmd_vel[1]
        cmd.w_K_R_E_C_cmd_mDs = self.command_vel[2] + self.delta_cmd_vel[2]

        p_gain = 1.0
        command_rpy = p_gain * self.error.rpy_rad

        cmd_rpy = self.sim.pilot_cmd.att_euler_cmd
        cmd_rpy.Phi_cmd_rad         = command_rpy[0] + self.delta_cmd_rpy[0]
        cmd_rpy.Theta_cmd_rad       = command_rpy[1] + self.delta_cmd_rpy[1]
        cmd_rpy.Psi_dot_cmd_radDs   = command_rpy[2] + self.delta_cmd_rpy[2]

    # Now follow up with basic RL Base Class handling...

    def _reset_reward_terms(self):
        """Helper to reset reward components for logging."""
        self.reward.total = 0.0
        self.reward.base = 0.0
        self.reward.terms = {} # Dictionary to hold named reward components

    def _get_info(self) -> dict:
        """
        Erweitert die Basis-Info-Methode um RL-spezifische Reward-Details.
        """
        info = super()._get_info()
        info['anomaly knowledge'] = self.has_anomaly_knowledge
        # Füge die detaillierten Reward-Komponenten hinzu, die in der RL-Schicht berechnet werden.
        info['reward_base'] = getattr(self.reward, 'base', 0.0)
        # Überschreibe die Standard-Reward-Werte mit den präzisen Werten aus dieser Schicht.
        info['reward'] = getattr(self.reward, 'total', 0.0)
        info['reward_terms'] = getattr(self.reward, 'terms', {})
        return info

    def _get_obs(self) -> dict: #
        """
        (Implements RMT_Base._get_obs)
        Constructs the observation dictionary for the agent.
        This is now abstract and must be implemented by the child class (e.g., CopterHoverEnv).
        """
        # Holen Sie sich die beiden Teil-Dictionaries
        state_obs = self.get_state_observation() # Gibt {'pos_error': ..., ...} zurück
        base_obs = self.get_base_observation()   # Gibt {'current_vel': ..., ...} zurück

        # Kombinieren Sie sie mit dem Dictionary-Unpacking-Operator
        flat_obs = {**state_obs, **base_obs}
        
        return flat_obs

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
            self.action_space = spaces.Box(low=-1.0, high=1.0, shape=(6,), dtype=np.float32)
        else:
            raise ValueError(f"Unsupported action_space_type:")

    def build_observation_space(self):
        # --- Observation Space Structure ---
        # This environment uses a dictionary observation space with two keys:
        # 'state': Contains the physical, kinematic state of the agent (e.g., velocity, orientation).
        # 'base':  Contains task-specific information that defines the current objective
        # This structure separates "what I am" (base_obs) from "what I need to do" (state_obs).
        # NOTE: This is NOT a `gymnasium.GoalEnv` for HER.
        # Holen Sie sich die Definitionen aus den Unter-Methoden
        # (Diese Methoden definieren nur die Box-Spaces, nicht die Dictionaries)
        state_obs_spaces = self.build_state_obs_space() # Gibt z.B. {'pos_error': Box, ...} zurück
        base_obs_spaces = self.build_base_obs_space()   # Gibt z.B. {'current_vel': Box, ...} zurück

        # Kombinieren Sie die beiden Dictionaries zu einem einzigen, flachen Dictionary
        flat_obs_space_dict = {**state_obs_spaces, **base_obs_spaces}
        
        return spaces.Dict(flat_obs_space_dict)


    @abstractmethod
    def build_state_obs_space(self) -> spaces.Dict:
        """
        Must be implemented by the concrete environment.
        Defines the dictionary space for the 'state' part of the observation.
        """
        raise NotImplementedError

    def build_base_obs_space(self) -> spaces.Dict:
        """
        Builds the static/contextual part of the observation space.
        This part is consistent across different RL environments.
        """
        if self.has_anomaly_knowledge:
            obs = spaces.Dict(
                {
                    "current_vel": spaces.Box(low=-1.0, high=1.0, shape=(3,), dtype=np.float32),
                    "current_rpy": spaces.Box(low=-1.0, high=1.0, shape=(3,), dtype=np.float32),
                    "current_omega": spaces.Box(low=-1.0, high=1.0, shape=(3,), dtype=np.float32),
                    "vel_limit": spaces.Box(low=-1.0, high=1.0, shape=(3,), dtype=np.float32),
                    "last_action": spaces.Box(low=-1.0, high=1.0, shape=self.action_space.shape, dtype=np.float32),
                    "motor_loss": spaces.Box(low=0.0, high=1.0, shape=(8,), dtype=np.float32),
                    
                }
            )
        else: 
            obs = spaces.Dict(
                {
                    "current_vel": spaces.Box(low=-1.0, high=1.0, shape=(3,), dtype=np.float32),
                    "current_rpy": spaces.Box(low=-1.0, high=1.0, shape=(3,), dtype=np.float32),
                    "current_omega": spaces.Box(low=-1.0, high=1.0, shape=(3,), dtype=np.float32),
                    "vel_limit": spaces.Box(low=-1.0, high=1.0, shape=(3,), dtype=np.float32),
                    "last_action": spaces.Box(low=-1.0, high=1.0, shape=self.action_space.shape, dtype=np.float32),                    
                }
            )

        return obs

    @abstractmethod
    def get_state_observation(self) -> dict:
        """
        Must be implemented by the concrete environment (e.g., E2E_Env).
        Computes the 'state_obs' (dynamic error) part of the observation dictionary.
        """
        raise NotImplementedError

    def get_base_observation(self) -> dict:
        """
        Computes the 'base_obs' (static context) part of the observation dictionary.
        This implementation is consistent across all environments.
        """
        if self.has_anomaly_knowledge:
            obs= {
                "current_vel": self.normalized_dict['vel_c'].astype(np.float32),
                "current_rpy": self.normalized_dict['rpy'].astype(np.float32),
                "current_omega": self.normalized_dict['omega'].astype(np.float32),
                "vel_limit": self._normalize_vector(self.norm_vel_max, -12, 12),
                "last_action": self.normalized_dict['command_old'].astype(np.float32),
                "motor_loss": self.anomaly.motorloss_vector.astype(np.float32)
            }
        else:
            obs= {
                "current_vel": self.normalized_dict['vel_c'].astype(np.float32),
                "current_rpy": self.normalized_dict['rpy'].astype(np.float32),
                "current_omega": self.normalized_dict['omega'].astype(np.float32),
                "vel_limit": self._normalize_vector(self.norm_vel_max, -12, 12),
                "last_action": self.normalized_dict['command_old'].astype(np.float32),
            }
        return obs

    @abstractmethod
    def _compute_reward_terms(self) -> float:
        """
        Must be implemented by the concrete environment (e.g., CopterHoverEnv).
        Calculates the task-specific base reward for the current state and should
        populate `self.reward.terms` with any individual components for logging.
        """
        raise NotImplementedError
    
    def _calculate_reward_from_error(self, abs_error: np.ndarray) -> np.ndarray:
        """
        Converts a NORMALIZED absolute error vector [-1, 1] into a reward vector [0, 1].
        This is the reward 'activation' function.
        """
        #norm_abs_error = 0.5*(abs_error + 1.0)
        norm_abs_error = np.abs(np.clip(abs_error,-1,+1))

        if self.reward_function == 'linear':
            return 1.0 - norm_abs_error
        elif self.reward_function == 'squared':
            return 1.0 - norm_abs_error**2
        elif self.reward_function == 'sqrt':
            return 1.0 - np.sqrt(norm_abs_error)
        elif self.reward_function == 'exponential':
            # Skalierung hier, um sicherzustellen, dass exp(-1) nicht zu hoch ist
            return np.exp(-3.0 * norm_abs_error) 
        elif self.reward_function == 'squared_exponential':
            return np.exp(-(norm_abs_error**2))
    
        raise ValueError(f"Unknown reward shaping function: {self.reward_function}")

    def compute_reward(self) -> float:
        """
        (Implements RMT_Base.compute_reward)
        Calculates the final reward for the step.
        This implementation adds standard time penalties and terminal bonuses.
        """

        # --- Standard, non-HER reward calculation for the current environment step ---
        self._reset_reward_terms()  # Clear previous terms
        base_reward = self._compute_reward_terms()  # Implemented by child class

        # Apply standard penalties/bonuses
        final_reward = base_reward - self.reward_time_penalty

        if self.status == 'final target reached':
            final_reward += 0#1# self.reward_success_bonus * 2  # Double bonus for final
        elif self.status == 'reached waypoint':
            final_reward += self.reward_success_bonus
        elif self.status in ['moved away', 'out of bounds', 'tilted over']:
            final_reward += self.reward_failure_penalty

        self.reward.total = final_reward
        return self.reward.total
