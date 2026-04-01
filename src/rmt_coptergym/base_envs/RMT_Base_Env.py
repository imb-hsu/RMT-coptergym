import numpy as np
import pandas as pd
import ctypes
import os
import platform

import gymnasium as gym
from gymnasium import spaces # spaces might not be strictly needed here, but good to keep for consistency
from gymnasium.utils import seeding
from abc import ABC, abstractmethod
from types import SimpleNamespace

# Assuming RMT_structs_definition.py is moved to RMT/RMT_structs.py
from rmt_coptergym.c_sim.RMT_structs import (
    Simulation_Control_Bus, States_Init_Bus, fc_pilot_cmd_Bus,
    Vehicle_Bus, Measurements_Bus, fc_est_Bus, Failure_Bus,
    real_T
) 

# Import the mission manager
from rmt_coptergym.utils.mission_manager import MissionManager


class RMT_Base(gym.Env, ABC):
    """
    Base class for Copter simulation environment, handling the low-level
    interaction with the external DLL/SO for simulation mechanics.
    This class manages the simulation state, DLL calls, and basic data transformations.
    It does NOT contain any RL-specific logic like reward calculation,
    observation space definition for agents, or episode termination conditions.
    Runs on 250 Hz.

    Frame Layout PX4 Octorotor Coaxial https://docs.px4.io/main/en/airframes/airframe_reference.html#octorotor-coaxial

     U:[2 >]      U:[1 <] 
     L:[5 <]      L:[6 >]
          \\      //
           \\    //
            [ /\ ]
           //    \\
          //      \\
     U:[3 <]      U:[4 >]
     L:[8 >]      L:[7 <]   

    """

    # This is the standard way to tell Gymnasium which render modes are supported.
    # We list 'human' and 'rgb_array' for future-proofing, even if not implemented yet.
    # The default render_mode in __init__ is None, so no rendering will be attempted.
    metadata = {"render_modes": ["human", "rgb_array"], "render_fps": 30}
    
    ################################################################################

    def __init__(self,
                 # sim_params
                 seed = None, 
                 render_mode = None,
                 ctrl_freq: int = 125,
                 max_duration: float = 10.0,
                 use_unix: bool = False,
                 use_fcs: bool = False, # Use the internal Flight Control System
                 # NOTE: The 'initial_*' parameters below serve as fallbacks.
                 mission_pool: list = [pd.DataFrame()], # Expects a pre-loaded dataset dictionary
                 is_eval: bool = False,
                 # initialization
                 initial: dict = {
                    'pos':      np.array([0.0,0.0,-10.0]),
                    'rpy_deg':  np.array([0.0,0.0,0.0]),
                    'vxyz':     np.array([0.0,0.0,0.0]),
                },
                 # init for trajectories and flight data
                 # data_set is now handled by MissionManager from a structured .npz file
                 check_pos: dict = {'tolerance': 0.1, 'limits':np.array([[-20,-20,-40], [20,20,0]])}, #
                 # Align default velocity limit with the dataset generator's typical values
                 check_vel: dict = {'tolerance': 0.1, 'limits':np.array([[-2,-2,-2],[2,2,2]])}, #
                 check_rpy: dict = {'tolerance': 2.0, 'limits':np.array([[-90,-90,-180], [90,90,180]])}, #
                 check_wxyz: dict = {'tolerance': 0.05,'limits':np.array([[-100,-100,-100], [100,100,100]])}, #
                 check_accel: dict = {'tolerance': 0.1,'limits':np.array([[-10,-10,-10], [10,10,10]])}, #
                 check_thrust: dict={'tolerance': 10, 'limits':np.array([0,2191])},
                 anomaly_chance: float = 0.0,
                 anomaly_pool: list = [],
                 anomaly: dict = {'time': np.array([0,0]), 'performance_loss':np.array([0,0,0,0,0,0,0,0])}
                 ):
        super().__init__()

        # --- Create container objects for state and configuration ---
        self.agent = SimpleNamespace()
        self.agent.meas = SimpleNamespace() 
        self.target = SimpleNamespace()
        self.error = SimpleNamespace()
        self.trajectory = SimpleNamespace()
        self.action = SimpleNamespace()
        self.defect = SimpleNamespace()
        self.defect.time = SimpleNamespace()
        self.limits = SimpleNamespace()
        self.limits.motor = SimpleNamespace()
        self.limits.agent = SimpleNamespace()
        self.initial_state = SimpleNamespace()
        self.initial_state.agent = SimpleNamespace()
        self.anomaly = SimpleNamespace()
        self.goal = SimpleNamespace()
        self.goal.tolerance = SimpleNamespace()
        self.sim = SimpleNamespace()
        self.reward = SimpleNamespace() #Namespace structure to contain different reward components for calculating total reward

        # --- Simulation Parameters ---
        self.initial_seed=seed
        self.np_random, seed = seeding.np_random(seed)
        #print(f"DEBUG: Environment INIT with seed: {self.initial_seed} --> {seed}")

        # Robustly handle render_mode according to Gymnasium conventions.
        assert render_mode is None or render_mode in self.metadata["render_modes"], \
            f"Invalid render_mode: {render_mode}. Must be one of {self.metadata['render_modes']}"
        self.render_mode = render_mode
        # --- Task and Goal Handling ---
        if not isinstance(mission_pool, list) or not mission_pool or not all(isinstance(df, pd.DataFrame) for df in mission_pool):
            raise TypeError("'mission_pool' muss eine nicht-leere Liste von pandas.DataFrames sein.")
        self.mission_pool = mission_pool
        self.is_eval = is_eval
        self.eval_episode_counter = 0
        self.mission = None # MissionManager will be initialized in reset()

        self.build_action_space()
        self.observation_space = self.build_observation_space() # This now works because action_space is defined

        self.sim_freq = 250
        self.ctrl_freq = ctrl_freq
        if self.sim_freq % self.ctrl_freq != 0:
            raise ValueError("Control frequency {self.ctrl_freq}Hz must divide sim frequency {self.sim_freq}Hz.")
        self.sim.controlled = use_fcs # Set whether to use the internal controller
    
        self.timestep       = 1.0 / self.sim_freq
        self.frame_skip     = self.sim_freq // self.ctrl_freq
        self.max_duration   = max_duration

        # --- Motor Defects and Health ---
        self.defect.time.start = anomaly['time'][0]
        self.defect.time.end   = anomaly['time'][1]
        self.defect.motors     = anomaly['performance_loss'] > 0        # transfrom the actual motorloss in bools to depict a motor has any kind of issue 
        self.defect.motor_performanceloss = anomaly['performance_loss']
        # Check shape and values for motor performance loss
        if self.defect.motor_performanceloss.shape != (8,) or not np.all((self.defect.motor_performanceloss >= 0) & (self.defect.motor_performanceloss <= 1)):
            raise ValueError("anomaly['performance_loss'] must be an array of shape (8,) with values between 0 and 1.")

        # --- Motor Defects and Health ---
        # Changed check for anomaly_pool to allow empty list if no anomalies are used
        if not isinstance(anomaly_pool, list) or not all(isinstance(df, pd.DataFrame) for df in anomaly_pool):
            raise TypeError("'anomaly_pool' muss eine Liste von pandas.DataFrames sein.")
        self.anomaly.pool = anomaly_pool
        self.anomaly.probability = anomaly_chance
        
        # --- Simulation Constraints --- 

        self.limits.motor.min   = check_thrust['limits'][0]
        self.limits.motor.max   = check_thrust['limits'][1]
        self.limits.motor.range = self.limits.motor.max - self.limits.motor.min

        self.initial_state.agent.pos        = initial['pos']
        self.initial_state.agent.rpy_deg    = initial['rpy_deg']
        self.initial_state.agent.rpy_rad    = np.deg2rad(self.initial_state.agent.rpy_deg )
        self.initial_state.agent.vel_b      = initial['vxyz']
        self.initial_state.agent.omega      = np.array([0.0,0.0,0.0])
        self.initial_state.cmd              = 823 * np.ones(8) # Default hover thrust

        self.limits.agent.pos               = check_pos['limits']
        self.limits.agent.velocity          = check_vel['limits'] 
        self.limits.agent.rpy_deg           = check_rpy['limits']
        self.limits.agent.rpy_rad           = np.deg2rad(check_rpy['limits'])
        self.limits.agent.omega             = check_wxyz['limits']
        self.limits.agent.accel             = check_accel['limits']
        self.limits.agent.thrust            = check_thrust['limits']

        self.goal.tolerance.pos             = check_pos['tolerance']
        self.goal.tolerance.vel             = check_vel['tolerance']
        self.goal.tolerance.rpy_deg             = check_rpy['tolerance']
        self.goal.tolerance.rpy_rad             = np.deg2rad(self.goal.tolerance.rpy_deg)
        self.goal.tolerance.omega           = check_wxyz['tolerance']
        self.goal.tolerance.accel           = check_accel['tolerance']
        self.goal.tolerance.thrust          = check_thrust['tolerance']

        # --- Normalization Constants ---
        self._setup_normalization_constants()

        # --- DLL Handling ---    
        lib_file_name = "RMT_FDM_DLL_FrameWork_FCS_RT.so" if use_unix else "RMT_FDM_DLL_FrameWork_FCS_RT.dll"

        try:
            # Navigate from the current file's directory (.../src/rmt_coptergym/base_envs)
            # up to the project root directory (RL-CopterBase) where the DLL is located.
            script_dir  = os.path.dirname(os.path.abspath(__file__))
            # Navigate up to the project root
            project_root = os.path.dirname(os.path.dirname(os.path.dirname(script_dir)))
            # Construct the correct path to the DLL inside the package structure
            lib_path    = os.path.join(project_root, 'src', 'rmt_coptergym','c_sim', lib_file_name)

            # On Windows (from Python 3.8+), it's best practice to add the DLL's directory
            # to the search path to help find dependencies, even if not strictly needed now.
            if platform.system() == "Windows":
                with os.add_dll_directory(project_root):
                    self.sim.lib = ctypes.CDLL(lib_path)
            else:
                self.sim.lib = ctypes.CDLL(lib_path)
            # 3. Globale Ein- und Ausgabestrukturen holen (entspricht dlsym für Variablen)
            # Pointers for DLL interaction
                # Der Name der globalen Variable in der DLL
            #print(f"Bibliothek '{lib_path}' erfolgreich geladen.")
            try:

                # --- 1. Instanz-spezifische I/O-Strukturen erstellen ---
                # Dies sind die Speicherbereiche, die Python für diese Instanz verwaltet.
                self.sim.sim_control = Simulation_Control_Bus()
                self.sim.states_init = States_Init_Bus()
                self.sim.w_cmd = (real_T * 8)()
                self.sim.pilot_cmd = fc_pilot_cmd_Bus()
                self.sim.failures = Failure_Bus()
                self.sim.vehicle_out = Vehicle_Bus()
                self.sim.measurements_out = Measurements_Bus()
                self.sim.fc_est_out = fc_est_Bus()

                # --- 2. Funktionssignaturen für die neue API definieren ---
                # Die "create"-Funktion, die Pointer auf alle I/O-Strukturen erwartet
                self.sim.lib.RMT_FDM_DLL_FrameWork_FCS_RT.restype = ctypes.c_void_p
                self.sim.lib.RMT_FDM_DLL_FrameWork_FCS_RT.argtypes = [
                    ctypes.POINTER(Simulation_Control_Bus),
                    ctypes.POINTER(States_Init_Bus),
                    ctypes.POINTER(real_T * 8),
                    ctypes.POINTER(fc_pilot_cmd_Bus),
                    ctypes.POINTER(Failure_Bus),
                    ctypes.POINTER(Vehicle_Bus),
                    ctypes.POINTER(Measurements_Bus),
                    ctypes.POINTER(fc_est_Bus),
                ]

                # Die `step`-Funktion
                self.sim.lib.RMT_FDM_DLL_FrameWork_FCS_RT_step.argtypes = [
                    ctypes.c_void_p,
                    ctypes.POINTER(Simulation_Control_Bus),
                    ctypes.POINTER(States_Init_Bus),
                    ctypes.POINTER(real_T * 8),
                    ctypes.POINTER(fc_pilot_cmd_Bus),
                    ctypes.POINTER(Failure_Bus),
                    ctypes.POINTER(Vehicle_Bus),
                    ctypes.POINTER(Measurements_Bus),
                    ctypes.POINTER(fc_est_Bus),
                ]

                # `initialize` und `terminate`
                self.sim.lib.RMT_FDM_DLL_FrameWork_FCS_RT_initialize.argtypes = [ctypes.c_void_p]
                self.sim.lib.RMT_FDM_DLL_FrameWork_FCS_RT_terminate.argtypes = [ctypes.c_void_p]

                # --- 3. Die C-Simulationsinstanz erstellen ("Handle" holen) ---
                # Wir übergeben die Pointer auf unsere Python-verwalteten Strukturen.
                self.sim.handle = self.sim.lib.RMT_FDM_DLL_FrameWork_FCS_RT(
                    ctypes.byref(self.sim.sim_control),
                    ctypes.byref(self.sim.states_init),
                    self.sim.w_cmd,
                    ctypes.byref(self.sim.pilot_cmd),
                    ctypes.byref(self.sim.failures),
                    ctypes.byref(self.sim.vehicle_out),
                    ctypes.byref(self.sim.measurements_out),
                    ctypes.byref(self.sim.fc_est_out),
                )
                if not self.sim.handle:
                    raise RuntimeError("Failed to create simulation instance in C.")
                #print(f"C-seitige Simulationsinstanz mit Handle {self.sim.handle} erstellt.")

                # --- 4. Die C-Instanz initialisieren ---
                self.sim.lib.RMT_FDM_DLL_FrameWork_FCS_RT_initialize(self.sim.handle)


                #        self.sim.lib.create_simulation.restype = ctypes.c_void_p
                #        self.sim.lib.destroy_simulation.argtypes = [ctypes.c_void_p]
                #        self.sim.lib.initialize_simulation.argtypes = [ctypes.c_void_p]
                #
                #       self.sim.lib.step_simulation.argtypes = [ctypes.c_void_p, ctypes.POINTER(ExtU_RMT_FDM_DLL_FrameWork_FCS_RT_T)]
                #       self.sim.lib.get_outputs.argtypes = [ctypes.c_void_p, ctypes.POINTER(ExtY_RMT_FDM_DLL_FrameWork_FCS_RT_T)]
                #
                #       # Erstelle die private C++ Simulationsinstanz für DIESE Env-Instanz
                #       self.sim.handle = self.sim.lib.create_simulation()
                #       if not self.sim.handle:
                #          raise RuntimeError("Failed to create C++ simulation instance via wrapper.")
#
#                       # Erstelle Python-seitige Speicher für Ein- und Ausgaben
#                       self.sim.inputs = ExtU_RMT_FDM_DLL_FrameWork_FCS_RT_T()
#                       self.sim.outputs = ExtY_RMT_FDM_DLL_FrameWork_FCS_RT_T()

                        #u_symbol = "RMT_FDM_DLL_FrameWork_FCS_RT_U"
                        #y_symbol = "RMT_FDM_DLL_FrameWork_FCS_RT_Y"
                        #self.sim.inputs = ExtU_RMT_FDM_DLL_FrameWork_FCS_RT_T.in_dll(self.sim.lib, u_symbol)
                        #self.sim.outputs = ExtY_RMT_FDM_DLL_FrameWork_FCS_RT_T.in_dll(self.sim.lib, y_symbol)
            except ValueError:
                print(f"Error: loading global sim structs ") #'{u_symbol}' or '{y_symbol}'.")
                raise
            self.sim.initialized = False # Flag to track if DLL has been initialized via reset
        except OSError as e:
            raise RuntimeError(f"Error: Could not load DLL in path: '{lib_path}': {e}")
        
        # --- Internal Simulation State Variables ---
        self._set_internal_state('init')

    def _set_action_state(self, initial_motor_setup):
        initial_cmds = initial_motor_setup * np.ones(self.action_space.shape, dtype=np.float64)
        self.action.cmd = initial_cmds
        self.action.cmd_old = initial_cmds.copy()
        self.action.box       = np.zeros(self.action_space.shape, dtype=np.float64)
        self.action.disc      = np.zeros(self.action_space.shape, dtype=np.float64)
        self.action.thrust_z  = 0.0

    def _set_internal_state(self, status='reset'):
        """Initializes or resets internal simulation state variables to their defaults."""
        self.clock  = 0.0
        self.status = status

        # NOTE: _reset_sim_state is now called from reset() after the mission is loaded.
        # Agent's current state from simulation
        self.agent.pos      = self.initial_state.agent.pos.copy()
        self.agent.rpy_deg  = self.initial_state.agent.rpy_deg.copy()
        self.agent.rpy_rad  = self.initial_state.agent.rpy_rad.copy()
        self.agent.vel_b    = self.initial_state.agent.vel_b.copy()
        #self.agent.vel_c    = self.initial_state.agent.vel_c
        self.agent.omega    = self.initial_state.agent.omega.copy()
        self.agent.motor_signal = self.initial_state.cmd.copy()

        # Target state (will be set by _set_targets)
        self.target.pos      = np.zeros(3, dtype=np.float64)
        self.target.rpy_rad  = np.zeros(3, dtype=np.float64)
        self.target.vel_c    = np.zeros(3, dtype=np.float64)
        self.target.omega    = np.zeros(3, dtype=np.float64)
        self.target.distance = 1e-12

        # Error state (will be calculated in _update_simvalues)
        self.error.pos       = np.zeros(3, dtype=np.float64)
        self.error.vel_c     = np.zeros(3, dtype=np.float64)
        self.error.rpy_rad   = np.zeros(3, dtype=np.float64)
        self.error.rpy_deg   = np.zeros(3, dtype=np.float64)
        self.error.omega     = np.zeros(3, dtype=np.float64)

        # Commanded state
        self.command_vel = np.zeros(3, dtype=np.float64)

        self.trajectory.waypoints = None 
        if self.action_space_type: # Will be set in child class
            self._set_action_state(self.agent.motor_signal)

            
    def _reset_sim_state(self, init):
        # Die C-Instanz initialisieren, um sie in einen sauberen Startzustand zu bringen.
        self.sim.lib.RMT_FDM_DLL_FrameWork_FCS_RT_initialize(self.sim.handle)

        #   old  self.sim.lib.initialize_simulation(self.sim.handle)
        #if not(self.sim.initialized):
        #    self.sim.lib.RMT_FDM_DLL_FrameWork_FCS_RT_initialize()
        #    self.sim.initialized = True

        # --- Set Initial Constraints for Sim ---    
        self.sim.states_init.vel_K_R_E_B_mDs.u_K_R_E_B_mDs = init.agent.vel_b[0]
        self.sim.states_init.vel_K_R_E_B_mDs.v_K_R_E_B_mDs = init.agent.vel_b[1]
        self.sim.states_init.vel_K_R_E_B_mDs.w_K_R_E_B_mDs = init.agent.vel_b[2]

        self.sim.states_init.rot_K_IB_B_radDs.w_x_K_IB_B_radDs = init.agent.omega[0]
        self.sim.states_init.rot_K_IB_B_radDs.w_y_K_IB_B_radDs = init.agent.omega[1]
        self.sim.states_init.rot_K_IB_B_radDs.w_z_K_IB_B_radDs = init.agent.omega[2]

        self.sim.states_init.att_euler_rad.Phi_rad      = init.agent.rpy_rad[0]
        self.sim.states_init.att_euler_rad.Theta_rad    = init.agent.rpy_rad[1]
        self.sim.states_init.att_euler_rad.Psi_rad      = init.agent.rpy_rad[2]

        self.sim.states_init.pos_R_O_m.x_R_O_m = init.agent.pos[0]
        self.sim.states_init.pos_R_O_m.y_R_O_m = init.agent.pos[1]
        self.sim.states_init.pos_R_O_m.z_R_O_m = init.agent.pos[2]

        self.sim.states_init.pos_R_WGS84.lambda_R_WGS84_rad = 0.2033
        self.sim.states_init.pos_R_WGS84.mue_R_WGS84_rad = 0.8439
        self.sim.states_init.pos_R_WGS84.h_R_WGS84_m = 548.0

        # Setzen der initialen Aktuator-Zustände
        for i in range(8):
            self.sim.states_init.actuator.u_0_radDs[i] = init.cmd[i]
        # --- Special initialization sequence with two step() calls ---
        
        # Set Simulation parameters to prepare for reset
        self.sim.sim_control.flg_Reset = False
        self.sim.sim_control.flg_Run = False
        self.sim.sim_control.flg_Enable_Controller = False
        self.sim.pilot_cmd.arm_swi = False
        self.sim.pilot_cmd.override_swi = True
        self.sim.pilot_cmd.vel_att_mode_swi = True
        self.sim.pilot_cmd.vel_K_R_E_C_cmd_mDs.w_K_R_E_C_cmd_mDs = -2.0
        #self.sim.lib.RMT_FDM_DLL_FrameWork_FCS_RT_step() # -> performing one step to get values into sim
        self._internal_step()
        # Second step() to reset and apply initial values
        self.sim.sim_control.flg_Reset = True
        self.sim.sim_control.flg_Run = False
        self.sim.sim_control.flg_Enable_Controller = False
        self.sim.pilot_cmd.arm_swi = True
        self.sim.pilot_cmd.override_swi = True # Keep override enabled
        self.sim.pilot_cmd.vel_att_mode_swi = True
        self.sim.pilot_cmd.vel_K_R_E_C_cmd_mDs.w_K_R_E_C_cmd_mDs = -2.0
        self._internal_step()

        # --- Third, "settling" step ---
        # This step runs the simulation for one tick with the correct initial values.
        # This allows derivative blocks (like acceleration) inside the DLL to converge
        # before the agent's first real step, preventing initial spikes.
        self.sim.sim_control.flg_Reset = False
        self.sim.sim_control.flg_Run = True
    
        # --- Set Flags for the actual simulation run ---
        # The flg_Run flag is already true from the settling step.
        # We just need to ensure all other flags are correctly set.
        self.sim.sim_control.flg_Run_p = True
        self.sim.sim_control.flg_Run_q = True
        self.sim.sim_control.flg_Run_r = True
        self.sim.sim_control.flg_Run_Phi = True
        self.sim.sim_control.flg_Run_Theta = True
        self.sim.sim_control.flg_Run_Psi = True
        self.sim.sim_control.flg_Run_vel_x = True
        self.sim.sim_control.flg_Run_vel_y = True
        self.sim.sim_control.flg_Run_vel_z = True
        self.sim.sim_control.flg_Run_pos_x = True
        self.sim.sim_control.flg_Run_pos_y = True
        self.sim.sim_control.flg_Run_pos_z = True
        self.sim.sim_control.flg_Propulsion_On = True
        self.sim.sim_control.flg_Aerodynamics_On = True
        self.sim.sim_control.flg_Weight_Balance_On = True
        self.sim.sim_control.flg_Ground_Contacts_On = False      # not tested to set on true
        self.sim.sim_control.flg_Enable_Sensor_Errors = False    # not tested to set on true
        self.sim.sim_control.flg_Enable_Controller = self.sim.controlled

        self._internal_step()
        self._internal_step()
        self._internal_step()
        self._internal_step()
        self._internal_step()
        self._internal_step()


    def _transform_action(self, action):
        """
        Translates agent action based on action_space_type to different internal
        representations (box, discrete, and direct motor commands in rad/s).
        """
        if self.action_space_type == "Box": 
            self.action.box = action
            # Defined between -1 and 1, shifting to 0..1 and scale to motorlimits
            motor_commands_rads = ((action + 1)/2) * self.limits.motor.range + self.limits.motor.min
            self.action.cmd = np.clip(motor_commands_rads, self.limits.motor.min, self.limits.motor.max).astype(np.float64)
            # discrete values for potential MDisc action space (for info/masking)
            motor_commands_disc = np.round(100 * (action +1)/2)
            self.action.disc = np.clip(motor_commands_disc, 0, 100).astype(np.int32)
        elif self.action_space_type  == "MDisc":
            self.action.disc = action
            # read values from 0 to 100 and encode in rads
            motor_commands_rads = (action / 100.0) * self.limits.motor.range + self.limits.motor.min
            self.action.cmd = np.clip(motor_commands_rads, self.limits.motor.min, self.limits.motor.max).astype(np.float64)
            # box values for potential Box action space (for info/masking)
            motor_commands_box = (action / 100.0) * 2 - 1 # Scale 0 to 100 to -1 to 1
            self.action.box = np.clip(motor_commands_box, -1, 1).astype(np.float32)
        else:
            raise ValueError(f"Error: Unsupported action_space_type: {self.action_space_type}")

    def _get_current_motor_loss_vector(self):
        if not self.anomaly.is_active or self.anomaly.current_anomaly_df is None:
            return np.zeros(8, dtype=np.float64)
        anomaly_df = self.anomaly.current_anomaly_df
        # Find the row where 'time' is less than or equal to the current clock time
        # and take the last such row (most recent anomaly state).
        # Using searchsorted for efficiency on sorted time data.
        idx = np.searchsorted(anomaly_df['time'].values, self.clock, side='right') - 1
        # Ensure index is within bounds (should always be >= 0 if time starts at 0)
        idx = max(0, idx)
        motor_loss_cols = [f'motorloss_{i+1}' for i in range(8)]
        current_loss_row = anomaly_df.iloc[idx][motor_loss_cols]
        return current_loss_row.values.astype(np.float64)           
    
    def _set_dll_inputs(self):
        """Apply action.cmd to the appropriate motors based on defects."""
        #Check for Changes/Updates on the anomaly and if action.cmd is available

        if self.action.cmd is not None:
            self.anomaly.motorloss_vector = self._get_current_motor_loss_vector() 
            for i in range(8):
                self.sim.failures.motor_loss[i] = self.anomaly.motorloss_vector[i] # directly affects the sim bus!
            # Assign inputs based on defect state - using a scaling dependency
            effective_motor_cmds = self.action.cmd * (1.0 - self.anomaly.motorloss_vector)
            for i in range(8):
                self.sim.w_cmd [i] = effective_motor_cmds[i]
        else:
            for i in range(8):
                self.sim.w_cmd [i] = 0 # no delta action no change here!
            
        #print('DEBUG: command: ', self.sim.w_cmd )

        """"
        # old approach: 
        # Healthstate//Anomalies: 0 nothing broken, 1 top rotor broken, 2 bottom rotor broken and 3/other both broken
        # Assuming action.cmd has 4 elements, corresponding to 4 rotor groups
        # Rotor group 0: motors 0 and 5
        cmd[0] = self.action.cmd[0] if self.ROTORGROUP_DEFECTS[0] in [0, 2] else 0.0
        cmd[5] = self.action.cmd[0] if self.ROTORGROUP_DEFECTS[0] in [0, 1] else 0.0
        # Rotor group 1: motors 1 and 4
        cmd[1] = self.action.cmd[1] if self.ROTORGROUP_DEFECTS[1] in [0, 2] else 0.0
        cmd[4] = self.action.cmd[1] if self.ROTORGROUP_DEFECTS[1] in [0, 1] else 0.0
        # Rotor group 2: motors 2 and 7
        cmd[2] = self.action.cmd[2] if self.ROTORGROUP_DEFECTS[2] in [0, 2] else 0.0
        cmd[7] = self.action.cmd[2] if self.ROTORGROUP_DEFECTS[2] in [0, 1] else 0.0
        # Rotor group 3: motors 3 and 6
        cmd[3] = self.action.cmd[3] if self.ROTORGROUP_DEFECTS[3] in [0, 2] else 0.0
        cmd[6] = self.action.cmd[3] if self.ROTORGROUP_DEFECTS[3] in [0, 1] else 0.0
        """

    def R_world_to_body(self) -> np.ndarray:
        """Return Rotation matrix based on current yaw rotation of the agent """
        yaw_rad = self.agent.rpy_rad[2]
        cy = np.cos(yaw_rad)
        sy = np.sin(yaw_rad)
        return np.array([
            [ cy,  sy, 0],
            [-sy,  cy, 0],
            [  0,   0, 1]
        ], dtype=np.float64)

    def _update_simvalues(self):
        """Reads the current state from the DLL output struct and calculates its errors and deltas."""
        # Shortcuts for easier access
        #        yout_vehicle = self.sim.outputs.Vehicle
        #        yout_est     = self.sim.outputs.fc_estimation 
        #        yout_meas    = self.sim.outputs.Measurements

        yout_vehicle = self.sim.vehicle_out
        yout_est     = self.sim.fc_est_out
        yout_meas    = self.sim.measurements_out


        self.agent.pos = np.array([
            yout_vehicle.States.pos_R_O_m.x_R_O_m,
            yout_vehicle.States.pos_R_O_m.y_R_O_m,
            yout_vehicle.States.pos_R_O_m.z_R_O_m ], dtype=np.float64)

        self.agent.rpy_rad = np.array([
            yout_vehicle.States.att_euler_rad.Phi_rad,
            yout_vehicle.States.att_euler_rad.Theta_rad,
            yout_vehicle.States.att_euler_rad.Psi_rad ], dtype=np.float64)

        self.agent.rpy_deg = np.rad2deg(self.agent.rpy_rad)

        self.agent.omega = np.array([
            yout_vehicle.States.rot_K_IB_B_radDs.w_x_K_IB_B_radDs,
            yout_vehicle.States.rot_K_IB_B_radDs.w_y_K_IB_B_radDs,
            yout_vehicle.States.rot_K_IB_B_radDs.w_z_K_IB_B_radDs ], dtype=np.float64)
        
        self.agent.accel = np.array([
            yout_est.vel_dot_est.u_dot_K_R_EC_C_est_mDs2,
            yout_est.vel_dot_est.v_dot_K_R_EC_C_est_mDs2,
            yout_est.vel_dot_est.w_dot_K_R_EC_C_est_mDs2], dtype=np.float64)
        
        # Velocity in Control Frame (Confirm frame definition from DLL documentation!)
        self.agent.vel_c = np.array([
            yout_est.vel_est.u_K_R_E_C_est_mDs,
            yout_est.vel_est.v_K_R_E_C_est_mDs,
            yout_est.vel_est.w_K_R_E_C_est_mDs], dtype=np.float64)
        
        # IMU Sensor Readings
        self.agent.meas.imu_gyro = np.array([
            yout_meas.imu_meas.gyro_meas.w_x_K_IB_B_IMU_meas_radDs,
            yout_meas.imu_meas.gyro_meas.w_y_K_IB_B_IMU_meas_radDs,
            yout_meas.imu_meas.gyro_meas.w_z_K_IB_B_IMU_meas_radDs], dtype=np.float64)
        
        self.agent.meas.imu_accel = np.array([
            yout_meas.imu_meas.acc_meas.f_x_P_B_IMU_meas_mDs2,
            yout_meas.imu_meas.acc_meas.f_y_P_B_IMU_meas_mDs2,
            yout_meas.imu_meas.acc_meas.f_z_P_B_IMU_meas_mDs2 + 9.81], dtype=np.float64)


        # Raw motor signals (rad/s)
        self.agent.motor_signal = np.array([ yout_vehicle.Commands.w1_act_radDs,
                                        yout_vehicle.Commands.w2_act_radDs,
                                        yout_vehicle.Commands.w3_act_radDs,
                                        yout_vehicle.Commands.w4_act_radDs,
                                        yout_vehicle.Commands.w5_act_radDs,
                                        yout_vehicle.Commands.w6_act_radDs,
                                        yout_vehicle.Commands.w7_act_radDs,
                                        yout_vehicle.Commands.w8_act_radDs ])

        # == ERRORS ===
        # Calculated in c-Frame, transformation from world to c-frame is needed
        # World-Frame Position Error
        error_world = self.target.pos - self.agent.pos
        error_world = error_world.reshape(-1, 1)

        # Rotationsmatrix based on yaw

        # Transform world error into drone body, but keep parallel to ground
        error_c = np.dot(self.R_world_to_body(), error_world)
        self.error.pos = error_c.reshape(-1)
        self.target.distance = np.linalg.norm(self.error.pos) # Update distance based on position error

        # Orientation Error
        self.error.rpy_rad = self.target.rpy_rad - self.agent.rpy_rad
        self.error.rpy_deg = np.rad2deg(self.error.rpy_rad)

        # self.error.vel_c is calculated in the command_vel function!

        # Update distance over error
        self.target.distance = np.linalg.norm(self.error.pos)

    def _internal_step(self):
        """
        Führt einen einzelnen, instanziierten Simulationsschritt aus
        und holt die Ergebnisse.
        """
        #    self.sim.lib.step_simulation(self.sim.handle, ctypes.byref(self.sim.inputs))
        #    self.sim.lib.get_outputs(self.sim.handle, ctypes.byref(self.sim.outputs))
        self.sim.lib.RMT_FDM_DLL_FrameWork_FCS_RT_step(
            self.sim.handle,
            ctypes.byref(self.sim.sim_control),
            ctypes.byref(self.sim.states_init),
            self.sim.w_cmd,
            ctypes.byref(self.sim.pilot_cmd),
            ctypes.byref(self.sim.failures),
            ctypes.byref(self.sim.vehicle_out),
            ctypes.byref(self.sim.measurements_out),
            ctypes.byref(self.sim.fc_est_out),
        )

    def _do_sim_step(self, new_action):
        """
        Performs the actual simulation steps with the DLL based on the agent's action.
        Updates internal simulation state variables.
        """
        # Store old action command for smoothness calculation in RL layer
        self.action.cmd_old = self.action.cmd.copy() 

        # Transform agent's action to DLL commands
        self._transform_action(new_action)
        self._set_dll_inputs()

        # Perform multiple DLL steps per environment step
        for _ in range(self.frame_skip):
            # Check time limit *within* inner loop if precise timing needed for truncation
            if self.clock >= self.max_duration:
                 break # Avoid extra DLL steps if time is already up
            #self.sim.lib.RMT_FDM_DLL_FrameWork_FCS_RT_step() - old code new step for parallel
            self._internal_step()

            self.clock += self.timestep # Increment internal clock accurately

        # Update internal state variables from DLL outputs
        self._update_simvalues()

    def _is_goal_achieved(self) -> bool:
        """
        Checks if the agent has achieved the current goal defined by the MissionManager.
        This function iterates through all keys in `self.mission.goal` and checks
        if the agent's state is within the defined tolerance for each goal component.
        """

        # If the goal dictionary is empty (e.g., only a time was specified),
        # it cannot be "achieved" in a state-based sense.
        if not self.mission.goal:
            return False

        all_checks_passed = True

        # Check position error
        tolerance_position = np.ones(3)*self.goal.tolerance.pos
        if 'pos' in self.mission.goal and not np.any(np.isnan(self.mission.goal['pos'])):
            #pos_error = np.linalg.norm(self.agent.pos - self.mission.goal['pos'])
            if np.any(np.abs(self.error.pos) > tolerance_position):
                all_checks_passed = False

 
        # Check velocity error
        tolerance_velocity = np.ones(3)*self.goal.tolerance.vel
        if 'vel' in self.mission.goal and not np.any(np.isnan(self.mission.goal['vel'])):
            #vel_error = np.linalg.norm(self.agent.vel_c - self.mission.goal['vel'])
            if np.any(np.abs(self.error.vel_c) > tolerance_velocity):
                all_checks_passed = False
 
        # Check attitude error (roll, pitch, yaw) in degrees
        tolerance_rpy = np.ones(3)*self.goal.tolerance.rpy_deg
        if 'rpy' in self.mission.goal and not np.any(np.isnan(self.mission.goal['rpy'])):
            #rpy_error_deg = self.agent.rpy_deg - self.mission.goal['rpy']
            #rpy_error_deg[2] = (rpy_error_deg[2] + 180) % 360 - 180 # Wrap yaw error to [-180, 180]
            if np.any(np.abs(self.error.rpy_deg) > tolerance_rpy):
                all_checks_passed = False
 
        # If all present checks passed, the goal is considered achieved.
        if all_checks_passed:
            self.status = 'Goal Achieved'
            return True
        
        return False
    
    def _setup_normalization_constants(self):
        """Sets up constants for observation normalization based on environment limits."""
        self.norm_buffer = 1.0
        self.norm_pos_min = self.limits.agent.pos[0] * self.norm_buffer
        self.norm_pos_max = self.limits.agent.pos[1] * self.norm_buffer
        self.norm_pos_range = self.norm_pos_max - self.norm_pos_min

        # Use the min/max vectors directly
        self.norm_vel_min = self.limits.agent.velocity[0] * self.norm_buffer
        self.norm_vel_max = self.limits.agent.velocity[1] * self.norm_buffer

        self.norm_rad_min = self.limits.agent.rpy_rad[0] * self.norm_buffer
        self.norm_rad_max = self.limits.agent.rpy_rad[1] * self.norm_buffer

        # Initialize omega normalization constants here
        self.norm_omega_min = self.limits.agent.omega[0] * self.norm_buffer
        self.norm_omega_max = self.limits.agent.omega[1] * self.norm_buffer

        # Demo for ACC - limited by currnet vel max of 2 m/s
        self.norm_accel_min = self.limits.agent.accel[0] * self.norm_buffer
        self.norm_accel_max = self.limits.agent.accel[1] * self.norm_buffer


    def _update_normalization_limit(self):
        """
        Updates normalization constants based on the current mission's velocity limit.
        This allows the normalization to adapt to different mission requirements.
        """
        # Get the velocity limit from the current mission goal.
        # Fallback to the environment's default limit if not specified.
        vel_limit_loaded = self.mission.goal.get('vel_limit', self.limits.agent.velocity[1])

        # Handle both scalar and vector limits from the dataset
        if isinstance(vel_limit_loaded, np.ndarray):
            # It's already a vector, use it directly
            vel_limit_vec = vel_limit_loaded
        else:
            # It's a scalar, broadcast it to a 3D vector
            vel_limit_vec = np.full(3, vel_limit_loaded)

        self.norm_vel_max = np.abs(vel_limit_vec) * self.norm_buffer
        self.norm_vel_min = -self.norm_vel_max

    def _update_normalized_dictionary(self):
        """
        Centralized hub for normalization.
        Computes a dictionary of normalized physical state values.
        """
        self.normalized_dict = {
            'pos': self._normalize_vector(self.agent.pos, self.norm_pos_min, self.norm_pos_max),
            'vel_c': self._normalize_vector(self.agent.vel_c, self.norm_vel_min, self.norm_vel_max),
            'accel': self._normalize_vector(self.agent.accel, self.norm_accel_min, self.norm_accel_max),
            'rpy': self._normalize_vector(self.agent.rpy_rad, self.norm_rad_min, self.norm_rad_max),
            'omega': self._normalize_vector(self.agent.omega, self.norm_omega_min, self.norm_omega_max),
            'command': self._normalize_vector(self.action.cmd, self.limits.motor.min, self.limits.motor.max),
            'command_old': self._normalize_vector(self.action.cmd_old, self.limits.motor.min, self.limits.motor.max),
            'error_pos': self._normalize_vector(self.error.pos, self.norm_pos_min, self.norm_pos_max), # IDEE für SPÄTER np.array([-10,-10,-10]), np.array([10,10,10])),
            'error_vel': self._normalize_vector(self.error.vel_c, self.norm_vel_min, self.norm_vel_max),
            'error_rpy': self._normalize_vector(self.error.rpy_rad, np.deg2rad(np.array([-20,-20,-20])), np.deg2rad(np.array([20,20,20]))), #self.norm_rad_min/2, self.norm_rad_max/2),
        }

    def _normalize_vector(self, value, min_val, max_val, target_min=-1.0, target_max=1.0):
        """ Normalizes NumPy array from [min_val, max_val] to [target_min, target_max]."""
        value = np.asarray(value)
        # --- Robust NaN Handling ---
        # If the input value is NaN (e.g., an undefined target), return a neutral
        # zero vector. This prevents NaN values from propagating into the agent's policy.
        if np.any(np.isnan(value)):
            return np.zeros(value.shape, dtype=np.float32)

        min_val = np.asarray(min_val)
        max_val = np.asarray(max_val)
        range_val = max_val - min_val
        # Use smaller epsilon, check if range_val is per-element
        is_scalar_range = (range_val.ndim == 0)
        if is_scalar_range:
            if abs(range_val) < 1e-9: range_val = 1.0
        else:
            range_val[np.abs(range_val) < 1e-9] = 1.0

        norm_01 = (value - min_val) / range_val
        target_range = target_max - target_min
        norm_target = (norm_01 * target_range) + target_min
        return np.clip(norm_target, target_min, target_max)
    
    def close(self):
        """Terminates the DLL when the environment is closed."""
        #if self.sim.initialized:
        #    self.sim.lib.RMT_FDM_DLL_FrameWork_FCS_RT_terminate()
        #    self.sim.initialized = False
       #         """Gibt die C++ Simulationsinstanz frei, um Speicherlecks zu vermeiden."""
       #        if hasattr(self, 'sim') and hasattr(self.sim, 'handle') and self.sim.handle:
       #            print("Destroying C++ simulation instance...")
       #            self.sim.lib.destroy_simulation(self.sim.handle)
       #            self.sim.handle = None

        if hasattr(self, 'sim') and hasattr(self.sim, 'handle') and self.sim.handle:
            #print(f"Zerstöre C-seitige Instanz mit Handle {self.sim.handle}...")
            self.sim.lib.RMT_FDM_DLL_FrameWork_FCS_RT_terminate(self.sim.handle)
            self.sim.handle = None

    def update_eval_config(self, mission_pool = None, anomaly_pool = None):
        """
        Setzt die Environment explizit für einen Evaluations-Run auf.
        Wird vom Eval-Skript vor reset() aufgerufen.
        """

        if mission_pool is not(None): 
            if not isinstance(mission_pool, list) or not mission_pool or not all(isinstance(df, pd.DataFrame) for df in mission_pool):
                raise TypeError("'mission_pool' muss eine nicht-leere Liste von pandas.DataFrames sein.")
            self.mission_pool = mission_pool
            self.is_eval = True
        
        
        if anomaly_pool is not(None):
            if not isinstance(anomaly_pool, list) or not all(isinstance(df, pd.DataFrame) for df in anomaly_pool):
                raise TypeError("'anomaly_pool' muss eine Liste von pandas.DataFrames sein.")
            self.anomaly.pool = anomaly_pool
            self.anomaly.probability = 1.0
            self.is_eval = True

    def reset(self, seed=None, options=None):
        """
        Resets the underlying simulation environment.
        This method should be called by the inheriting RL environment's reset.
        """
        # Seed the random number generator for reproducibility - organized by make_vec_env for first reset before training
        super().reset(seed=seed)
        #print(f"DEBUG: Environment RESET with seed: {seed}")
        self._set_internal_state()

        has_anomalies = (self.anomaly.pool is not None) and (len(self.anomaly.pool) > 0)
        n_anoms = len(self.anomaly.pool) if has_anomalies else 1
        n_miss = len(self.mission_pool)

        if self.is_eval:
            # --- EVALUATION LOGIK (Deterministisch & Zirkulierend) ---
            
            # A) Anomalie auswählen (Inner Loop)
            # Zykliert schnell: 0, 1, 2, 0, 1, 2 ...
            if has_anomalies:
                self.anomaly.is_active = True
                anomaly_idx = self.eval_episode_counter % n_anoms
                self.anomaly.current_anomaly_df = self.anomaly.pool[anomaly_idx]
            else:
                self.anomaly.is_active = False
                self.anomaly.current_anomaly_df = None

            # B) Mission auswählen (Outer Loop)
            # Wechselt erst, wenn alle Anomalien für die aktuelle Mission durch sind
            # (0//3)%2 = 0, (1//3)%2 = 0, (2//3)%2 = 0, (3//3)%2 = 1 ...
            trajectory_idx = (self.eval_episode_counter // n_anoms) % n_miss
            
            # Counter erhöhen für das nächste Mal
            self.eval_episode_counter += 1

        else:
            # --- TRAINING LOGIK (Zufall) ---
            
            # A) Mission zufällig
            trajectory_idx = self.np_random.integers(0, n_miss)
            
            # B) Anomalie zufällig (basierend auf Wahrscheinlichkeit)
            if has_anomalies and (self.np_random.random() < self.anomaly.probability):
                self.anomaly.is_active = True
                anomaly_idx = self.np_random.integers(0, n_anoms)
                self.anomaly.current_anomaly_df = self.anomaly.pool[anomaly_idx]
            else:
                self.anomaly.is_active = False
                self.anomaly.current_anomaly_df = None

            # Mission laden
        selected_mission_df = self.mission_pool[trajectory_idx]
        self.mission = MissionManager(trajectory_df=selected_mission_df)

        # Assign anomaly/motorloss to simulation bus
        self.anomaly.motorloss_vector = self._get_current_motor_loss_vector()
        for i in range(8):
                    self.sim.failures.motor_loss [i] = self.anomaly.motorloss_vector[i]

        # Initial State überschreiben (Mission Waypoint 0)
        mission_initial_state = self.mission.initial_state
        self.initial_state.agent.pos = mission_initial_state.get('pos', self.initial_state.agent.pos)
        self.initial_state.agent.rpy_deg = mission_initial_state.get('rpy', self.initial_state.agent.rpy_deg)
        self.initial_state.agent.rpy_rad = np.deg2rad(self.initial_state.agent.rpy_deg)
        self.initial_state.agent.vel_b = mission_initial_state.get('vel', self.initial_state.agent.vel_b)

        if 'thrust' in mission_initial_state and not np.isnan(mission_initial_state['thrust']):
            self.initial_state.cmd = np.full(8, mission_initial_state['thrust'])
        
        # Anomalie auf initialen Schub anwenden
        self.initial_state.cmd = self.initial_state.cmd * (1.0 - self.anomaly.motorloss_vector) 
       
        # Targets & Sim State setzen
        self.set_targets()
        self._reset_sim_state(self.initial_state)
        self._update_simvalues()
        self._update_normalized_dictionary()

        return self._get_obs(), self._get_info()

    def update_logic(self):
        # Calculate the ideal velocity command based on the mission.
        self._calculate_command_velocity()

        # --- Update Target and Error based on final command ---
        # Set the official target velocity to the one calculated by the controller.
        # This ensures consistency for logging and reward calculation.
        self.target.vel_c = self.command_vel
        # Now calculate the final velocity error for this step.
        self.error.vel_c = self.target.vel_c - self.agent.vel_c
        self.error.rpy_rad = self.target.rpy_rad - self.agent.rpy_rad

        # Update task-specific errors
        self._update_task_specifics()


    def step(self, action):
        """
        Performs a simulation step. This method is abstract in this base class
        and must be implemented by the inheriting RL environment.
        """

        # --- Update Mission Goal ---
        # This should be the first thing in the step, to define the goal for this timestep.
        self.status = '...'
        is_achieved = self._is_goal_achieved()
        self.mission.update_goal(env_time=self.clock, is_current_goal_achieved=is_achieved)
        self.set_targets() # set targets after mission update, so targets are valid for plotting and next iteration

        self.update_logic() # update logic to definie vel_commands for upcoming sim_steps!
        
        # Update normalization constants based on the current mission goal (e.g., vel_limit)
        self._update_normalization_limit()

        self._do_sim_step(action)

        self.update_logic() # update logic after steps for eval

        # Centralize normalization of the agent's state after the physical state is updated
        self._update_normalized_dictionary()


        # Check for episode end (termination/truncation)
        terminated, truncated = self.check_episode_end()

        # Calculate reward based on the new state
        reward = self.compute_reward()

        # Get observation and info for the agent
        obs = self._get_obs()
        info = self._get_info()

        return obs, reward, terminated, truncated, info

    def _get_info(self) -> dict:
        """
        Gathers a comprehensive, universal set of information for logging and analysis.
        Safely accesses RL-specific attributes to ensure identical structure across all envs.
        """
        # --- Get Next Waypoint Info ---
        next_wp_info = {'time': np.nan, 'pos': np.full(3, np.nan), 'vel': np.full(3, np.nan)}
        if self.mission and self.mission.target_waypoint_index < len(self.mission.waypoints) - 1:
            next_wp_raw = self.mission.waypoints[self.mission.target_waypoint_index + 1]
            next_wp_grouped = self.mission._group_vectors(next_wp_raw)
            next_wp_info['time'] = next_wp_grouped.get('time', np.nan)
            next_wp_info['pos'] = next_wp_grouped.get('pos', np.full(3, np.nan))
            next_wp_info['vel'] = next_wp_grouped.get('vel', np.full(3, np.nan))

        info = {
            # Core Sim
            "sim_time":         self.clock,
            "status":           self.status,

            # Reward (safely accessed)
            "reward":           getattr(self.reward, 'total', 0.0),
            "reward_terms":     getattr(self.reward, 'terms', {}),
            "reward_function":  getattr(self, 'reward_type', 'N/A'),

            # Distance
            "distance_current": self.target.distance,
            "distance_initial": getattr(self.target, 'distance_initial', 0.0),
            "distance_is_near":   self.target.distance < self.goal.tolerance.pos,

            # Action (safely accessed)
            "action_type":      getattr(self, 'action_space_type', 'N/A'),
            "action_box":       getattr(self.action, 'box', None),
            "action_disc":          getattr(self.action, 'discrete', None),
            "action_cmd":  getattr(self.action, 'cmd', None),
            "motor_signal_measured_rps": self.agent.motor_signal,

            # Agent State (Raw)
            "agent_pos":        self.agent.pos,
            "agent_rpy_deg":    self.agent.rpy_deg,
            "agent_vel_c":      self.agent.vel_c,
            "agent_omega":      self.agent.omega,
            "agent_accel":      self.agent.accel,

            "agent_imu_omega":  self.agent.meas.imu_gyro,
            "agent_imu_accel":  self.agent.meas.imu_accel,

            # Mission Info
            "mission_name":     getattr(self.mission, 'name', 'N/A'),
            "mission_waypoint_index": getattr(self.mission, 'target_waypoint_index', -1),
            # Mission Goal State (What the agent is trying to achieve)
            "mission_goal_pos": self.target.pos,
            "mission_goal_vel": self.target.vel_c,

            "mission_next_wp_time": next_wp_info['time'],
            "mission_next_wp_pos": next_wp_info['pos'],

            # Command State (What the controller is telling the sim to do)
            "min_vel":       self.norm_vel_min,
            "max_vel":       self.norm_vel_max,

            # Error State (Raw)
            "error_pos":        self.error.pos,
            "error_vel_c":      self.error.vel_c,
            "error_rpy_deg":    self.error.rpy_deg,
            # Defects
            "anomaly_motorloss":    self.anomaly.motorloss_vector,

            "indi_cmd_vel": np.array([
                self.sim.pilot_cmd.vel_K_R_E_C_cmd_mDs.u_K_R_E_C_cmd_mDs,
                self.sim.pilot_cmd.vel_K_R_E_C_cmd_mDs.v_K_R_E_C_cmd_mDs,
                self.sim.pilot_cmd.vel_K_R_E_C_cmd_mDs.w_K_R_E_C_cmd_mDs,
            ]),

            "indi_cmd_rpy": np.array([
                self.sim.pilot_cmd.att_euler_cmd.Phi_cmd_rad,
                self.sim.pilot_cmd.att_euler_cmd.Theta_cmd_rad,
                self.sim.pilot_cmd.att_euler_cmd.Psi_dot_cmd_radDs,
            ]),

            "normalized_dict": self.normalized_dict,
            
            
        }
        return info

    def render(self):
        """Placeholder for gym env default design."""
        print("No rendering implemented.")
        pass

    # --- abstract methods --- 
    @abstractmethod
    def _get_obs(self) -> np.ndarray:
        """Must be implemented by the inheriting RL environment."""
        raise NotImplementedError
   
    @abstractmethod
    def build_action_space(self) -> None:
        """Muss implementiert werden, um den Aktionsraum des Agenten zu definieren."""
        raise NotImplementedError

    @abstractmethod
    def build_observation_space(self) -> None:
        """Muss implementiert werden, um den Beobachtungsraum des Agenten zu definieren."""
        raise NotImplementedError

    def set_targets(self) -> None:
        """
        (Implements RMT_Base.set_targets)
        The MissionManager is already initialized in the base class's reset method.
        This method now sets the environment's main target variables from the
        mission manager's current goal.
        If a goal component is not in the mission, it is set to NaN.
        """
        # The mission manager's goal is the single source of truth. Fallback to NaN.
        nan_3d = np.full(3, np.nan)
        self.target.pos     = self.mission.goal.get('pos', nan_3d)
        self.target.rpy_deg = self.mission.goal.get('rpy', nan_3d)
        # Only convert to radians if it's a valid number
        self.target.rpy_rad = np.deg2rad(self.target.rpy_deg) if not np.any(np.isnan(self.target.rpy_deg)) else nan_3d
        self.target.vel_c   = self.mission.goal.get('vel', nan_3d)
        # Add thrust/cmd target. If not present, it's NaN.
        self.target.cmd     = np.full(8, self.mission.goal.get('thrust', np.nan))

    def _calculate_command_velocity(self) -> None:
        """
        This is the new central navigation logic. It determines the desired velocity
        command based on the current mission goal and stores it in `self.command_vel`.
        This method provides a baseline controller that child classes can use or override.
        """
        # --- 1. Determine the control strategy based on the current mission goal ---
        # Priority 1: If an explicit, non-zero velocity target is given, use it directly (velocity-following).
        if 'vel' in self.mission.goal and not np.any(np.isnan(self.mission.goal['vel'])) and np.any(self.mission.goal['vel'] != 0):
            desired_vel = self.target.vel_c.copy()
        # Priority 2: If a position target exists, calculate a desired velocity using a P-controller (position-following).
        elif 'pos' in self.mission.goal and not np.any(np.isnan(self.mission.goal['pos'])):
            # The base class already calculates self.error.pos in the control frame.
            # The gain of 2.0 is a sensible default for a benchmark controller.
            p_gain = 2.0
            desired_vel = p_gain * self.error.pos
        # Fallback: If no other target is defined, command zero velocity to stabilize.
        else:
            desired_vel = np.zeros(3)

        # --- 2. Dynamic Damping to prevent overshoot near the target ---
        if 'pos' in self.mission.goal and not np.any(np.isnan(self.mission.goal['pos'])):
            desired_speed = np.linalg.norm(desired_vel)
            if desired_speed > self.target.distance:
                desired_vel = desired_vel * (self.target.distance / (desired_speed + 1e-6))

        # --- 4. Clip each velocity component against its specific axis limit ---
        # The correct limits (mission or default) are already in self.norm_vel_min/max from _update_normalization_limit
        final_vel = np.clip(desired_vel, self.norm_vel_min, self.norm_vel_max)

        # --- 5. Store the final calculated command in the dedicated namespace ---
        # This is the authoritative command for this timestep.
        self.command_vel = final_vel

    @abstractmethod
    def _update_task_specifics(self) -> None:
        """
        Abstract method to be implemented by child classes.
        Used to calculate task-specific values (e.g., navigation targets for RL) each step.
        This is called *after* _calculate_command_velocity.
        """
        raise NotImplementedError

    @abstractmethod
    def compute_reward(self) -> float:
        """
        Must be implemented by the inheriting RL environment.
        Calculates the reward for the current step.
        """
        raise NotImplementedError

    def check_episode_end(self) -> tuple[bool, bool]:
        """
        Checks for universal termination (failure/success) or truncation (time limit).
        This is a comprehensive check that covers all standard end-of-episode conditions.
        """
        # --- 1. Check for Truncation (Time Limit) ---
        # This is the primary condition for stopping an episode that hasn't failed.
        truncated = self.clock >= self.max_duration
        if truncated:
            self.status = 'time limit reached'
            return False, True # Not terminated, but truncated

        # --- 2. Check for Termination (Success or Failure) ---
        terminated = False
        
         # Success: Mission is fully completed
        if self.mission and self.mission.is_mission_complete:
            self.status = 'final target reached'
            # terminated = True # Here we do  not want to terminate the simulation, but track reaching our goal. After this success teh agent shoudl hold its goal till out of time.
       
        # Failure: Agent flew outside the defined workspace
        if np.any(self.agent.pos < self.limits.agent.pos[0]) or \
           np.any(self.agent.pos > self.limits.agent.pos[1]):
            #print('min: ', self.limits.agent.pos[0], 'current_val: ', self.agent.pos, 'max: ', self.limits.agent.pos[1])
            self.status = 'out of bounds'
            terminated = True
        # Failure: Agent moved too far away from the current target
        # The `distance_initial` is expected to be set by the RL layer when a waypoint is switched.
        if hasattr(self.target, 'distance_initial') and self.target.distance >= max(1.25 * self.target.distance_initial, 2.0):
            self.status = 'moved away'
            terminated = True
        # Failure: Agent tilted over beyond safe limits
        if np.any(self.agent.rpy_deg < self.limits.agent.rpy_deg[0]) or \
           np.any(self.agent.rpy_deg > self.limits.agent.rpy_deg[1]):
            self.status = 'tilted over'
            terminated = True

        return terminated, False # If terminated, it's not truncated