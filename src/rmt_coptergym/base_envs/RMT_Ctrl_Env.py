import numpy as np
from gymnasium import spaces

from rmt_coptergym.base_envs.RMT_Base_Env import RMT_Base

class RMT_Ctrl_Env(RMT_Base):
    """
    Environment for benchmarking the Flight Control Systems (FCS),
    internally the INDI is used

 
    This environment does not take external RL actions for motor control.
    Instead, it contains an internal P-controller that generates velocity
    commands to follow a trajectory from the MissionManager. The purpose is to
    create a performance baseline to compare RL agents against.

    It inherits from RMT_Base to reuse the simulation handling, data loading,
    and state tracking infrastructure.
    """

    def __init__(self,
                 **kwargs):
        """
        Args:
            **kwargs: Arguments passed to the parent RMT_Base class.
        """

        # --- IMPORTANT ---
        # Force the use of the internal Flight Control System (FCS).
        # This is the key difference from the RL environments.
        kwargs['use_fcs'] = True

        # Call the parent constructor. This will set up the simulation,
        # mission manager, etc. It will also call the overridden methods
        # like build_action_space() and build_observation_space().
        super().__init__(**kwargs)


    def build_action_space(self) -> None:
        """
        (Implements RMT_Base.build_action_space)
        This environment does not take external actions in the traditional sense.
        The "action" is determined internally by the velocity controller.
        We define a dummy action space for compatibility with the Gym API.
        """
        # A dummy action space. The step function will ignore the input action.
        self.action_space = spaces.Box(low=-1.0, high=1.0, shape=(1,), dtype=np.float32)
        self.action_space_type = "Box" #

    def build_observation_space(self) -> None:
        """
        (Implements RMT_Base.build_observation_space)
        Defines a simple observation space containing basic state information.
        This is not intended for an RL agent but can be useful for logging
        and analysis.
        """
        # A simple, flat observation space for logging.
        obs_shape = 12 # pos, rpy, vel_c, omega
        self.observation_space = spaces.Box(low=-np.inf, high=np.inf, shape=(obs_shape,), dtype=np.float32)

    def _get_obs(self) -> np.ndarray:
        """
        (Implements RMT_Base._get_obs)
        Returns a simple, flat array of the agent's current state.
        """
        obs = np.concatenate([
            self.agent.pos,
            self.agent.rpy_rad,
            self.agent.vel_c,
            self.agent.omega
        ]).astype(np.float32)
        return obs

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
        cmd.u_K_R_E_C_cmd_mDs = self.command_vel[0]
        cmd.v_K_R_E_C_cmd_mDs = self.command_vel[1]
        cmd.w_K_R_E_C_cmd_mDs = self.command_vel[2]

        p_gain = 1.0
        command_rpy = p_gain * self.error.rpy_rad

        cmd_rpy = self.sim.pilot_cmd.att_euler_cmd
        cmd_rpy.Phi_cmd_rad = command_rpy[0]
        cmd_rpy.Theta_cmd_rad = command_rpy[1]
        cmd_rpy.Psi_dot_cmd_radDs = command_rpy[2]


    def compute_reward(self) -> float:
        """
        (Implements RMT_Base.compute_reward)
        This environment is for benchmarking, not training, so it returns a
        constant reward of 0.
        """
        return 0.0
