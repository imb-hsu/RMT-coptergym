import numpy as np
from gymnasium import spaces

from rmt_coptergym.base_envs.RMT_Base_Env import RMT_Base

class Benchmark_Env(RMT_Base):
    """
    Benchmark Environment for generating ideal trajectories using the internal
    Flight Control System (FCS) of the simulation.

    This environment does NOT expose a standard RL action space for motor control.
    Instead, it contains an internal PID-like controller that generates velocity
    commands to follow a trajectory from the MissionManager. The purpose is to
    create a performance baseline to compare RL agents against.

    It inherits from RMT_Base to reuse the simulation handling, data loading,
    and state tracking infrastructure.
    """

    def __init__(self,
                 p_gain: float = 2.0,
                 **kwargs):
        """
        Args:
            p_gain (float): The proportional gain for the internal position-to-velocity
                            controller. This determines how aggressively the benchmark
                            agent tries to correct its position error.
            **kwargs: Arguments passed to the parent RMT_Base class.
        """
        self.p_gain = p_gain

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
        self.action_space_type = "Benchmark" # Custom type for clarity

    def build_observation_space(self) -> None:
        """
        (Implements RMT_Base.build_observation_space)
        Defines a simple observation space containing basic state information.
        This is not intended for an RL agent but can be useful for logging
        and analysis.
        """
        # A simple, flat observation space for logging.
        obs_shape = 12 # pos, rpy, vel_c, omega
        return spaces.Box(low=-np.inf, high=np.inf, shape=(obs_shape,), dtype=np.float32)

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
        velocity based on the position error to the current target.
        """
        # The base class already calculates self.error.pos in the control frame.
        # We can use this directly for our P-controller.

        # Simple P-controller: desired velocity is proportional to position error.
        desired_vel = self.p_gain * self.error.pos

        # Get the velocity limit from the current mission goal.
        # Fallback to the environment's default limit if not specified.
        vel_limit_raw = self.mission.goal.get('vel_limit', self.limits.agent.vel_magnitude)

        # Handle both scalar and vector limits from the dataset
        if isinstance(vel_limit_raw, np.ndarray):
            vel_limit_val = np.linalg.norm(vel_limit_raw)
        else:
            vel_limit_val = vel_limit_raw if not np.isnan(vel_limit_raw) else self.limits.agent.vel_magnitude

        # Clip the desired velocity to the mission's velocity limit.
        desired_speed = np.linalg.norm(desired_vel)
        if desired_speed > vel_limit_val:
            desired_vel = desired_vel * (vel_limit_val / desired_speed)

        # Set the calculated velocity commands for the simulation's internal controller.
        cmd = self.sim.inputs.fc_pilot_cmd.vel_K_R_E_C_cmd_mDs
        cmd.u_K_R_E_C_cmd_mDs = desired_vel[0]
        cmd.v_K_R_E_C_cmd_mDs = desired_vel[1]
        cmd.w_K_R_E_C_cmd_mDs = desired_vel[2]

    def _transform_action(self, action):
        """
        (Overrides RMT_Base._transform_action)
        This environment's "action" is calculated internally, so we don't
        need to transform an external action. This method is a no-op.
        """
        pass # Do nothing with the external action.

    def _set_dll_inputs(self):
        """
        (Overrides RMT_Base._set_dll_inputs)
        The velocity commands are already set in _update_task_specifics.
        This method is a no-op to prevent overwriting motor commands.
        """
        pass # Velocity commands are set elsewhere.

    def compute_reward(self) -> float:
        """
        (Implements RMT_Base.compute_reward)
        This environment is for benchmarking, not training, so it returns a
        constant reward of 0.
        """
        return 0.0