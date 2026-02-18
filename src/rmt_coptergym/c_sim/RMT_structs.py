import ctypes

############################################################
# Standard-Typdefinitionen (wie von Ihnen bereitgestellt)
############################################################

# Logical type definitions
false = 0
true = 1

# Fixed width word size data types
int8_T = ctypes.c_int8
uint8_T = ctypes.c_uint8
int16_T = ctypes.c_int16
uint16_T = ctypes.c_uint16
int32_T = ctypes.c_int32
uint32_T = ctypes.c_uint32
int64_T = ctypes.c_int64
uint64_T = ctypes.c_uint64
real32_T = ctypes.c_float
real64_T = ctypes.c_double

# Type for ZCSigState (aus zero_crossing_types.h, typischerweise ein int/enum)
ZCSigState = ctypes.c_int

# Generic type definitions
real_T = real64_T
time_T = real64_T
boolean_T = ctypes.c_bool  # Using ctypes.c_bool for direct mapping
int_T = ctypes.c_int
uint_T = ctypes.c_uint
ulong_T = ctypes.c_ulong
ulonglong_T = ctypes.c_ulonglong
char_T = ctypes.c_char
uchar_T = ctypes.c_ubyte
byte_T = ctypes.c_char

# Complex number type definitions
class creal32_T(ctypes.Structure):
    _fields_ = [("re", real32_T), ("im", real32_T)]

class creal64_T(ctypes.Structure):
    _fields_ = [("re", real64_T), ("im", real64_T)]

class creal_T(ctypes.Structure):
    _fields_ = [("re", real_T), ("im", real_T)]

class cint8_T(ctypes.Structure):
    _fields_ = [("re", int8_T), ("im", int8_T)]

class cuint8_T(ctypes.Structure):
    _fields_ = [("re", uint8_T), ("im", uint8_T)]

class cint16_T(ctypes.Structure):
    _fields_ = [("re", int16_T), ("im", int16_T)]

class cuint16_T(ctypes.Structure):
    _fields_ = [("re", uint16_T), ("im", uint16_T)]

class cint32_T(ctypes.Structure):
    _fields_ = [("re", int32_T), ("im", int32_T)]

class cuint32_T(ctypes.Structure):
    _fields_ = [("re", uint32_T), ("im", uint32_T)]

class cint64_T(ctypes.Structure):
    _fields_ = [("re", int64_T), ("im", int64_T)]

class cuint64_T(ctypes.Structure):
    _fields_ = [("re", uint64_T), ("im", uint64_T)]

# Pointer type
pointer_T = ctypes.c_void_p

############################################################
# Strukturen aus RMT_FDM_RT_types.h und verwandten Dateien
############################################################

# Basistypen und kleine Bus-Strukturen

class pos_R_local_meas_Bus(ctypes.Structure):
    _fields_ = [
        ("x_R_O_meas_m", real_T),
        ("y_R_O_meas_m", real_T),
        ("z_R_O_meas_m", real_T)
    ]

class Simulation_Control_Bus(ctypes.Structure):
    _fields_ = [
        ("flg_Reset", boolean_T),
        ("flg_Run", boolean_T),
        ("flg_Run_p", boolean_T),
        ("flg_Run_q", boolean_T),
        ("flg_Run_r", boolean_T),
        ("flg_Run_Phi", boolean_T),
        ("flg_Run_Theta", boolean_T),
        ("flg_Run_Psi", boolean_T),
        ("flg_Run_vel_x", boolean_T),
        ("flg_Run_vel_y", boolean_T),
        ("flg_Run_vel_z", boolean_T),
        ("flg_Run_pos_x", boolean_T),
        ("flg_Run_pos_y", boolean_T),
        ("flg_Run_pos_z", boolean_T),
        ("flg_Propulsion_On", boolean_T),
        ("flg_Aerodynamics_On", boolean_T),
        ("flg_Weight_Balance_On", boolean_T),
        ("flg_Ground_Contacts_On", boolean_T),
        ("flg_Enable_Sensor_Errors", boolean_T),
        ("flg_Enable_Controller", boolean_T)
    ]

class rot_W_OW_B_radDs_Bus(ctypes.Structure):
    _fields_ = [
        ("w_x_W_OW_B_radDs", real_T),
        ("w_y_W_OW_B_radDs", real_T),
        ("w_z_W_OW_B_radDs", real_T)
    ]

class vel_W_R_E_O_mDs_Bus(ctypes.Structure):
    _fields_ = [
        ("u_W_R_E_O_mDs", real_T),
        ("v_W_R_E_O_mDs", real_T),
        ("w_W_R_E_O_mDs", real_T)
    ]

class Atmosphere_Bus(ctypes.Structure):
    _fields_ = [
        ("Static_Temperature_ATM_K", real_T),
        ("Speed_of_Sound_mDs", real_T),
        ("Static_Pressure_ATM_NDm2", real_T),
        ("rho_kgDm3", real_T)
    ]

class rot_K_IB_B_radDs_Bus(ctypes.Structure):
    _fields_ = [
        ("w_x_K_IB_B_radDs", real_T),
        ("w_y_K_IB_B_radDs", real_T),
        ("w_z_K_IB_B_radDs", real_T)
    ]

class att_euler_rad_Bus(ctypes.Structure):
    _fields_ = [
        ("Phi_rad", real_T),
        ("Theta_rad", real_T),
        ("Psi_rad", real_T)
    ]

class vel_K_R_E_B_mDs_Bus(ctypes.Structure):
    _fields_ = [
        ("u_K_R_E_B_mDs", real_T),
        ("v_K_R_E_B_mDs", real_T),
        ("w_K_R_E_B_mDs", real_T)
    ]

class pos_R_O_m_Bus(ctypes.Structure):
    _fields_ = [
        ("x_R_O_m", real_T),
        ("y_R_O_m", real_T),
        ("z_R_O_m", real_T)
    ]

class pos_R_WGS84_Bus(ctypes.Structure):
    _fields_ = [
        ("lambda_R_WGS84_rad", real_T),
        ("mue_R_WGS84_rad", real_T),
        ("h_R_WGS84_m", real_T)
    ]

class Actuator_States_Init_Bus(ctypes.Structure):
    _fields_ = [
        ("u_0_radDs", real_T * 8)
    ]

class States_Init_Bus(ctypes.Structure):
    _fields_ = [
        ("rot_K_IB_B_radDs", rot_K_IB_B_radDs_Bus),
        ("att_euler_rad", att_euler_rad_Bus),
        ("vel_K_R_E_B_mDs", vel_K_R_E_B_mDs_Bus),
        ("pos_R_O_m", pos_R_O_m_Bus),
        ("pos_R_WGS84", pos_R_WGS84_Bus),
        ("actuator", Actuator_States_Init_Bus)
    ]

class Controller_Commands_Bus(ctypes.Structure):
    _fields_ = [
        ("w1_cmd_radDs", real_T),
        ("w2_cmd_radDs", real_T),
        ("w3_cmd_radDs", real_T),
        ("w4_cmd_radDs", real_T),
        ("w5_cmd_radDs", real_T),
        ("w6_cmd_radDs", real_T),
        ("w7_cmd_radDs", real_T),
        ("w8_cmd_radDs", real_T)
    ]

# Fahrzeug- und Umgebungsbusse

class vel_dot_K_R_EB_B_mDs2_Bus(ctypes.Structure):
    _fields_ = [
        ("u_dot_K_R_EB_B_mDs2", real_T),
        ("v_dot_K_R_EB_B_mDs2", real_T),
        ("w_dot_K_R_EB_B_mDs2", real_T)
    ]

class rot_dot_K_IB_B_B_radDs2_Bus(ctypes.Structure):
    _fields_ = [
        ("w_x_dot_K_IB_B_B_radDs2", real_T),
        ("w_y_dot_K_IB_B_B_radDs2", real_T),
        ("w_z_dot_K_IB_B_B_radDs2", real_T)
    ]

class att_dot_euler_radDs_Bus(ctypes.Structure):
    _fields_ = [
        ("Phi_dot_radDs", real_T),
        ("Theta_dot_radDs", real_T),
        ("Psi_dot_radDs", real_T)
    ]

class pos_dot_R_E_O_mDs_Bus(ctypes.Structure):
    _fields_ = [
        ("x_dot_R_E_O_mDs", real_T),
        ("y_dot_R_E_O_mDs", real_T),
        ("z_dot_R_E_O_mDs", real_T)
    ]

class States_Dot_Bus(ctypes.Structure):
    _fields_ = [
        ("vel_dot_K_R_EB_B_mDs2", vel_dot_K_R_EB_B_mDs2_Bus),
        ("rot_dot_K_IB_B_B_radDs2", rot_dot_K_IB_B_B_radDs2_Bus),
        ("att_dot_euler_radDs", att_dot_euler_radDs_Bus),
        ("pos_dot_R_E_O_mDs", pos_dot_R_E_O_mDs_Bus)
    ]

class for_T_R_B_N_Bus(ctypes.Structure):
    _fields_ = [
        ("X_T_R_B_N", real_T),
        ("Y_T_R_B_N", real_T),
        ("Z_P_R_B_N", real_T)
    ]

class mom_T_R_B_Nm_Bus(ctypes.Structure):
    _fields_ = [
        ("L_T_R_B_Nm", real_T),
        ("M_T_R_B_Nm", real_T),
        ("N_T_R_B_Nm", real_T)
    ]

class for_mom_T_R_B_Bus(ctypes.Structure):
    _fields_ = [
        ("for_T_R_B_N", for_T_R_B_N_Bus),
        ("mom_T_R_B_Nm", mom_T_R_B_Nm_Bus)
    ]

class for_P_R_B_N_Bus(ctypes.Structure):
    _fields_ = [
        ("X_P_R_B_N", real_T),
        ("Y_P_R_B_N", real_T),
        ("Z_P_R_B_N", real_T)
    ]

class mom_P_R_B_Nm_Bus(ctypes.Structure):
    _fields_ = [
        ("L_P_R_B_Nm", real_T),
        ("M_P_R_B_Nm", real_T),
        ("N_P_R_B_Nm", real_T)
    ]

class for_mom_P_R_B_Bus(ctypes.Structure):
    _fields_ = [
        ("for_P_R_B_N", for_P_R_B_N_Bus),
        ("mom_P_R_B_Nm", mom_P_R_B_Nm_Bus)
    ]

class Propulsion_Data_Out_Bus(ctypes.Structure):
    _fields_ = [
        ("for_mom_P_R_B", for_mom_P_R_B_Bus),
        ("Propulsion_Out", real_T)
    ]

class for_A_R_B_N_Bus(ctypes.Structure):
    _fields_ = [
        ("X_A_R_B_N", real_T),
        ("Y_A_R_B_N", real_T),
        ("Z_A_R_B_N", real_T)
    ]

class mom_A_R_B_Nm_Bus(ctypes.Structure):
    _fields_ = [
        ("L_A_R_B_Nm", real_T),
        ("M_A_R_B_Nm", real_T),
        ("N_A_R_B_Nm", real_T)
    ]

class for_mom_A_R_B_Bus(ctypes.Structure):
    _fields_ = [
        ("for_A_R_B_N", for_A_R_B_N_Bus),
        ("mom_A_R_B_Nm", mom_A_R_B_Nm_Bus)
    ]

class for_LDG_R_B_N_Bus(ctypes.Structure):
    _fields_ = [
        ("X_LDG_R_B_N", real_T),
        ("Y_LDG_R_B_N", real_T),
        ("Z_LDG_R_B_N", real_T)
    ]

class mom_LDG_R_B_Nm_Bus(ctypes.Structure):
    _fields_ = [
        ("L_LDG_R_B_Nm", real_T),
        ("M_LDG_R_B_Nm", real_T),
        ("N_LDG_R_B_Nm", real_T)
    ]

class for_mom_LDG_R_B_Bus(ctypes.Structure):
    _fields_ = [
        ("for_LDG_R_B_N", for_LDG_R_B_N_Bus),
        ("mom_LDG_R_B_Nm", mom_LDG_R_B_Nm_Bus)
    ]

class for_G_R_B_N_Bus(ctypes.Structure):
    _fields_ = [
        ("X_G_R_B_N", real_T),
        ("Y_G_R_B_N", real_T),
        ("Z_G_R_B_N", real_T)
    ]

class mom_G_R_B_Nm_Bus(ctypes.Structure):
    _fields_ = [
        ("L_G_R_B_Nm", real_T),
        ("M_G_R_B_Nm", real_T),
        ("N_G_R_B_Nm", real_T)
    ]

class for_mom_G_R_B_Bus(ctypes.Structure):
    _fields_ = [
        ("for_G_R_B_N", for_G_R_B_N_Bus),
        ("mom_G_R_B_Nm", mom_G_R_B_Nm_Bus)
    ]

class Weight_Balance_Bus(ctypes.Structure):
    _fields_ = [
        ("pos_RG_B_m", real_T * 3),
        ("m_kg", real_T),
        ("I_R_BB_kgm2", real_T * 9)
    ]

class Airframe_Outputs_Bus(ctypes.Structure):
    _fields_ = [
        ("for_mom_T_R_B", for_mom_T_R_B_Bus),
        ("Propulsion_Data_Out", Propulsion_Data_Out_Bus),
        ("for_mom_A_R_B", for_mom_A_R_B_Bus),
        ("for_mom_LDG_R_B", for_mom_LDG_R_B_Bus),
        ("for_mom_G_R_B", for_mom_G_R_B_Bus),
        ("Weight_Balance", Weight_Balance_Bus)
    ]

class Gravitation_Bus(ctypes.Structure):
    _fields_ = [
        ("acc_G_R_OO_O_mDs2", real_T * 3)
    ]

class Environment_Bus(ctypes.Structure):
    _fields_ = [
        ("Atmosphere", Atmosphere_Bus),
        ("Gravitation", Gravitation_Bus)
    ]

# Kinematik-Busse

class rot_K_EB_B_radDs_Bus(ctypes.Structure):
    _fields_ = [
        ("w_x_K_EB_B_radDs", real_T),
        ("w_y_K_EB_B_radDs", real_T),
        ("w_z_K_EB_B_radDs", real_T)
    ]

class rot_K_OB_B_radDs_Bus(ctypes.Structure):
    _fields_ = [
        ("w_x_K_OB_B_radDs", real_T),
        ("w_y_K_OB_B_radDs", real_T),
        ("w_z_K_OB_B_radDs", real_T)
    ]

class Kin_Trafo_Matrices_Bus(ctypes.Structure):
    _fields_ = [
        ("M_BO", real_T * 9),
        ("M_OB", real_T * 9),
        ("M_NO", real_T * 9),
        ("M_ON", real_T * 9)
    ]

class Kinematic_Data_Bus(ctypes.Structure):
    _fields_ = [
        ("rot_K_IB_B_radDs", rot_K_IB_B_radDs_Bus),
        ("vel_K_R_E_B_mDs", vel_K_R_E_B_mDs_Bus),
        ("rot_K_EB_B_radDs", rot_K_EB_B_radDs_Bus),
        ("rot_K_OB_B_radDs", rot_K_OB_B_radDs_Bus),
        ("Kin_Trafo_Matrices", Kin_Trafo_Matrices_Bus)
    ]

class vel_A_R_E_O_mDs_Bus(ctypes.Structure):
    _fields_ = [
        ("u_A_R_E_0_mDs", real_T),
        ("v_A_R_E_0_mDs", real_T),
        ("w_A_R_E_0_mDs", real_T)
    ]

class vel_A_R_E_B_mDs_Bus(ctypes.Structure):
    _fields_ = [
        ("u_A_R_E_B_mDs", real_T),
        ("v_A_R_E_B_mDs", real_T),
        ("w_A_R_E_B_mDs", real_T)
    ]

class Aero_Velocities_Bus(ctypes.Structure):
    _fields_ = [
        ("vel_A_R_E_0_mDs", vel_A_R_E_O_mDs_Bus),
        ("vel_A_R_E_B_mDs", vel_A_R_E_B_mDs_Bus)
    ]

class Translation_A_R_Bus(ctypes.Structure):
    _fields_ = [
        ("VEL_A_R_abs_mDs", real_T),
        ("alpha_A_R_rad", real_T),
        ("beta_A_R_rad", real_T)
    ]

class Aero_Trafo_Matrices_Bus(ctypes.Structure):
    _fields_ = [
        ("M_BS", real_T * 9),
        ("M_SB", real_T * 9),
        ("M_BA", real_T * 9),
        ("M_AB", real_T * 9),
        ("M_AO", real_T * 9),
        ("M_OA", real_T * 9)
    ]

class rot_A_AB_B_radDs_Bus(ctypes.Structure):
    _fields_ = [
        ("w_x_A_AB_B_radDs", real_T),
        ("w_y_A_AB_B_radDs", real_T),
        ("w_z_A_AB_B_radDs", real_T)
    ]

class rot_A_AB_A_radDs_Bus(ctypes.Structure):
    _fields_ = [
        ("w_x_A_AB_A_radDs", real_T),
        ("w_y_A_AB_A_radDs", real_T),
        ("w_z_A_AB_A_radDs", real_T)
    ]

class rot_A_AB_S_radDs_Bus(ctypes.Structure):
    _fields_ = [
        ("w_x_A_AB_S_radDs", real_T),
        ("w_y_A_AB_S_radDs", real_T),
        ("w_z_A_AB_S_radDs", real_T)
    ]

class Aero_Angular_Rates_Bus(ctypes.Structure):
    _fields_ = [
        ("rot_A_AB_B_radDs", rot_A_AB_B_radDs_Bus),
        ("rot_A_AB_A_radDs", rot_A_AB_A_radDs_Bus),
        ("rot_A_AB_S_radDs", rot_A_AB_S_radDs_Bus)
    ]

class Airdata_Bus(ctypes.Structure):
    _fields_ = [
        ("Aero_Velocities", Aero_Velocities_Bus),
        ("Translation_A_R", Translation_A_R_Bus),
        ("Aero_Trafo_Matrices", Aero_Trafo_Matrices_Bus),
        ("Aero_Angular_Rates", Aero_Angular_Rates_Bus)
    ]

class vel_W_R_E_B_mDs_Bus(ctypes.Structure):
    _fields_ = [
        ("u_W_R_E_B_mDs", real_T),
        ("v_W_R_E_B_mDs", real_T),
        ("w_W_R_E_B_mDs", real_T)
    ]

class Wind_Velocities_Bus(ctypes.Structure):
    _fields_ = [
        ("vel_W_R_E_B_mDs", vel_W_R_E_B_mDs_Bus),
        ("vel_W_R_E_O_mDs", vel_W_R_E_O_mDs_Bus)
    ]

class rot_W_0W_0_radDs_Bus(ctypes.Structure):
    _fields_ = [
        ("w_x_W_0W_0_radDs", real_T),
        ("w_y_W_0W_0_radDs", real_T),
        ("w_z_W_0W_0_radDs", real_T)
    ]

class Wind_Angular_Rates_Bus(ctypes.Structure):
    _fields_ = [
        ("rot_W_0W_0_radDs", rot_W_0W_0_radDs_Bus),
        ("rot_W_OW_B_radDs", rot_W_OW_B_radDs_Bus)
    ]

class Wind_Data_Bus(ctypes.Structure):
    _fields_ = [
        ("Wind_Velocities", Wind_Velocities_Bus),
        ("Wind_Angular_Rates", Wind_Angular_Rates_Bus)
    ]

class Motion_Kinematics_Bus(ctypes.Structure):
    _fields_ = [
        ("Kinematic_Data", Kinematic_Data_Bus),
        ("Airdata", Airdata_Bus),
        ("Wind_Data", Wind_Data_Bus)
    ]

# Hauptausgabebusse

class Outputs_Bus(ctypes.Structure):
    _fields_ = [
        ("States_Dot", States_Dot_Bus),
        ("Airframe_Outputs", Airframe_Outputs_Bus),
        ("Environment", Environment_Bus),
        ("Motion_Kinematics", Motion_Kinematics_Bus)
    ]

class States_Bus(ctypes.Structure):
    _fields_ = [
        ("rot_K_IB_B_radDs", rot_K_IB_B_radDs_Bus),
        ("att_euler_rad", att_euler_rad_Bus),
        ("vel_K_R_E_B_mDs", vel_K_R_E_B_mDs_Bus),
        ("pos_R_O_m", pos_R_O_m_Bus)
    ]

class Commands_Bus(ctypes.Structure):
    _fields_ = [
        ("w1_act_radDs", real_T),
        ("w2_act_radDs", real_T),
        ("w3_act_radDs", real_T),
        ("w4_act_radDs", real_T),
        ("w5_act_radDs", real_T),
        ("w6_act_radDs", real_T),
        ("w7_act_radDs", real_T),
        ("w8_act_radDs", real_T)
    ]

class Vehicle_Bus(ctypes.Structure):
    _fields_ = [
        ("States", States_Bus),
        ("Outputs", Outputs_Bus),
        ("Commands", Commands_Bus)
    ]

# Messungsbusse

class baro_meas_Bus(ctypes.Structure):
    _fields_ = [
        ("Static_Pressure_meas_NDm2", real_T),
        ("Static_Temperature_meas_K", real_T),
        ("h_Baro_meas_m", real_T)
    ]

class gyro_meas_Bus(ctypes.Structure):
    _fields_ = [
        ("w_x_K_IB_B_IMU_meas_radDs", real_T),
        ("w_y_K_IB_B_IMU_meas_radDs", real_T),
        ("w_z_K_IB_B_IMU_meas_radDs", real_T)
    ]

class acc_meas_Bus(ctypes.Structure):
    _fields_ = [
        ("f_x_P_B_IMU_meas_mDs2", real_T),
        ("f_y_P_B_IMU_meas_mDs2", real_T),
        ("f_z_P_B_IMU_meas_mDs2", real_T)
    ]

class imu_meas_Bus(ctypes.Structure):
    _fields_ = [
        ("gyro_meas", gyro_meas_Bus),
        ("acc_meas", acc_meas_Bus)
    ]

class pos_R_WGS84_meas_Bus(ctypes.Structure):
    _fields_ = [
        ("lambda_R_WGS84_meas_rad", real_T),
        ("mue_R_WGS84_meas_rad", real_T),
        ("h_R_WGS84_meas_m", real_T)
    ]

class vel_K_R_E_O_meas_Bus(ctypes.Structure):
    _fields_ = [
        ("u_K_R_E_O_meas_mDs", real_T),
        ("v_K_R_E_O_meas_mDs", real_T),
        ("w_K_R_E_O_meas_mDs", real_T)
    ]

class path_K_R_meas_rad_Bus(ctypes.Structure):
    _fields_ = [
        ("gamma_K_R_meas_rad", real_T),
        ("chi_K_R_meas_rad", real_T)
    ]

class Translation_K_R_meas_Bus(ctypes.Structure):
    _fields_ = [
        ("vel_K_R_abs_meas_mDs", real_T),
        ("path_K_R_meas_rad", path_K_R_meas_rad_Bus)
    ]

class gps_meas_Bus(ctypes.Structure):
    _fields_ = [
        ("pos_R_WGS84_meas", pos_R_WGS84_meas_Bus),
        ("pos_R_local_meas", pos_R_local_meas_Bus),
        ("vel_K_R_E_O_meas", vel_K_R_E_O_meas_Bus),
        ("Translation_K_R_meas", Translation_K_R_meas_Bus)
    ]

class ahrs_meas_Bus(ctypes.Structure):
    _fields_ = [
        ("Phi_meas_rad", real_T),
        ("Theta_meas_rad", real_T),
        ("Psi_meas_rad", real_T),
        ("M_BO_meas", real_T * 9),
        ("M_OB_meas", real_T * 9)
    ]

class motor_meas_Bus(ctypes.Structure):
    _fields_ = [
        ("w1_meas_radDs", real_T),
        ("w2_meas_radDs", real_T),
        ("w3_meas_radDs", real_T),
        ("w4_meas_radDs", real_T),
        ("w5_meas_radDs", real_T),
        ("w6_meas_radDs", real_T),
        ("w7_meas_radDs", real_T),
        ("w8_meas_radDs", real_T)

    ]


class switches_meas_Bus(ctypes.Structure):
    _fields_ = [
        ("wow_switch_1_meas", real_T)
    ]

class Measurements_Bus(ctypes.Structure):
    _fields_ = [
        ("baro_meas", baro_meas_Bus),
        ("imu_meas", imu_meas_Bus),
        ("gps_meas", gps_meas_Bus),
        ("ahrs_meas", ahrs_meas_Bus),
        ("motor_meas", motor_meas_Bus),
        ("switches_meas", switches_meas_Bus)
    ]


############################################################
# Strukturen aus RMT_FDM_DLL_FrameWork_FCS_RT_types.h
# (Nur neue, nicht duplizierte Strukturen)
############################################################

# Flight-Controller-spezifische Messungsbusse ("fc_"-Präfix)

class fc_baro_meas_Bus(ctypes.Structure):
    _fields_ = [
        ("Static_Pressure_meas_NDm2", real_T),
        ("Static_Temperature_meas_K", real_T),
        ("h_Alt_Baro_meas_m", real_T)
    ]

class fc_gyro_meas_Bus(ctypes.Structure):
    _fields_ = [
        ("w_x_K_IB_B_IMU_meas_radDs", real_T),
        ("w_y_K_IB_B_IMU_meas_radDs", real_T),
        ("w_z_K_IB_B_IMU_meas_radDs", real_T)
    ]

class fc_acc_meas_Bus(ctypes.Structure):
    _fields_ = [
        ("f_x_P_B_IMU_meas_mDs2", real_T),
        ("f_y_P_B_IMU_meas_mDs2", real_T),
        ("f_z_P_B_IMU_meas_mDs2", real_T)
    ]

class fc_imu_meas_Bus(ctypes.Structure):
    _fields_ = [
        ("gyro_meas", fc_gyro_meas_Bus),
        ("acc_meas", fc_acc_meas_Bus)
    ]

class fc_pos_R_WGS84_meas_Bus(ctypes.Structure):
    _fields_ = [
        ("lambda_R_WGS84_meas_rad", real_T),
        ("mue_R_WGS84_meas_rad", real_T),
        ("h_R_WGS84_meas_m", real_T)
    ]

class fc_pos_R_local_meas_Bus(ctypes.Structure):
    _fields_ = [
        ("x_R_O_meas_m", real_T),
        ("y_R_O_meas_m", real_T),
        ("z_R_O_meas_m", real_T)
    ]

class fc_vel_K_R_E_O_meas_Bus(ctypes.Structure):
    _fields_ = [
        ("u_K_R_E_O_meas_mDs", real_T),
        ("v_K_R_E_O_meas_mDs", real_T),
        ("w_K_R_E_O_meas_mDs", real_T)
    ]

class fc_path_K_R_meas_Bus(ctypes.Structure):
    _fields_ = [
        ("gamma_K_R_meas_rad", real_T),
        ("chi_K_R_meas_rad", real_T)
    ]

class fc_translation_K_R_meas_Bus(ctypes.Structure):
    _fields_ = [
        ("vel_K_R_abs_meas_mDs", real_T),
        ("path_K_R_meas_rad", fc_path_K_R_meas_Bus)
    ]

class fc_gps_meas_Bus(ctypes.Structure):
    _fields_ = [
        ("pos_R_WGS84_meas", fc_pos_R_WGS84_meas_Bus),
        ("pos_R_local_meas", fc_pos_R_local_meas_Bus),
        ("vel_K_R_E_O_meas", fc_vel_K_R_E_O_meas_Bus),
        ("Translation_K_R_meas", fc_translation_K_R_meas_Bus)
    ]

class fc_ahrs_meas_Bus(ctypes.Structure):
    _fields_ = [
        ("Phi_meas_rad", real_T),
        ("Theta_meas_rad", real_T),
        ("Psi_meas_rad", real_T),
        ("M_BO_meas", real_T * 9),
        ("M_OB_meas", real_T * 9)
    ]

class fc_measurements_Bus(ctypes.Structure):
    _fields_ = [
        ("baro_meas", fc_baro_meas_Bus),
        ("imu_meas", fc_imu_meas_Bus),
        ("gps_meas", fc_gps_meas_Bus),
        ("ahrs_meas", fc_ahrs_meas_Bus)
    ]
    
# Flight-Controller-Steuerungsbusse

class fc_ctrl_cmd_Bus(ctypes.Structure):
    _fields_ = [
        ("w1_cmd_radDs", real_T),
        ("w2_cmd_radDs", real_T),
        ("w3_cmd_radDs", real_T),
        ("w4_cmd_radDs", real_T),
        ("w5_cmd_radDs", real_T),
        ("w6_cmd_radDs", real_T),
        ("w7_cmd_radDs", real_T),
        ("w8_cmd_radDs", real_T)
    ]
    
# Referenzmodell- (RM) und Schätzungs- (est) Busse

class RM_Phi_Bus(ctypes.Structure):
    _fields_ = [
        ("Phi_Dot_radDs", real_T),
        ("Phi_ref_rad", real_T)
    ]

class RM_Theta_Bus(ctypes.Structure):
    _fields_ = [
        ("Theta_Dot_radDs", real_T),
        ("Theta_ref_rad", real_T)
    ]

class RM_attitude_Bus(ctypes.Structure):
    _fields_ = [
        ("RM_Phi", RM_Phi_Bus),
        ("RM_Theta", RM_Theta_Bus),
        ("PsiDot_cmd_radDs", real_T)
    ]

class RM_p_Bus(ctypes.Structure):
    _fields_ = [
        ("nu_p_radDs2", real_T),
        ("p_ref_radDs", real_T)
    ]

class RM_q_Bus(ctypes.Structure):
    _fields_ = [
        ("nu_q_radDs2", real_T),
        ("q_ref_radDs", real_T)
    ]

class RM_r_Bus(ctypes.Structure):
    _fields_ = [
        ("nu_r_radDs2", real_T),
        ("r_ref_radDs", real_T)
    ]

class RM_rate_Bus(ctypes.Structure):
    _fields_ = [
        ("RM_p", RM_p_Bus),
        ("RM_q", RM_q_Bus),
        ("RM_r", RM_r_Bus)
    ]

class RM_u_C_Bus(ctypes.Structure):
    _fields_ = [
        ("nu_u_mDs2", real_T),
        ("u_C_ref_mDs", real_T)
    ]

class RM_v_C_Bus(ctypes.Structure):
    _fields_ = [
        ("nu_v_mDs2", real_T),
        ("v_C_ref_mDs", real_T)
    ]

class RM_w_C_Bus(ctypes.Structure):
    _fields_ = [
        ("nu_w_mDs2", real_T),
        ("w_C_ref_mDs", real_T)
    ]

class RM_vel_Bus(ctypes.Structure):
    _fields_ = [
        ("RM_u_C", RM_u_C_Bus),
        ("RM_v_C", RM_v_C_Bus),
        ("RM_w_C", RM_w_C_Bus)
    ]

class fc_RM_Bus(ctypes.Structure):
    _fields_ = [
        ("RM_attitude", RM_attitude_Bus),
        ("RM_rate", RM_rate_Bus),
        ("RM_vel", RM_vel_Bus)
    ]

class vel_est_Bus(ctypes.Structure):
    _fields_ = [
        ("u_K_R_E_C_est_mDs", real_T),
        ("v_K_R_E_C_est_mDs", real_T),
        ("w_K_R_E_C_est_mDs", real_T)
    ]

class vel_dot_est_Bus(ctypes.Structure):
    _fields_ = [
        ("u_dot_K_R_EC_C_est_mDs2", real_T),
        ("v_dot_K_R_EC_C_est_mDs2", real_T),
        ("w_dot_K_R_EC_C_est_mDs2", real_T)
    ]

class rate_est_Bus(ctypes.Structure):
    _fields_ = [
        ("p_est_radDs", real_T),
        ("q_est_radDs", real_T),
        ("r_est_radDs", real_T)
    ]

class rate_dot_est_Bus(ctypes.Structure):
    _fields_ = [
        ("p_Dot_est_radDs2", real_T),
        ("q_Dot_est_radDs2", real_T),
        ("r_Dot_est_radDs2", real_T)
    ]

class att_est_Bus(ctypes.Structure):
    _fields_ = [
        ("Phi_est_rad", real_T),
        ("Theta_est_rad", real_T),
        ("Psi_Dot_est_radDs", real_T)
    ]

class fc_est_Bus(ctypes.Structure):
    _fields_ = [
        ("vel_est", vel_est_Bus),
        ("vel_dot_est", vel_dot_est_Bus),
        ("rate_est", rate_est_Bus),
        ("rate_dot_est", rate_dot_est_Bus),
        ("att_est", att_est_Bus)
    ]
    
# Pilotenkommando-Bus (aus fc_pilot_cmd_Bus.h)

class fc_vel_K_R_E_C_cmd_mDs_Bus(ctypes.Structure):
    _fields_ = [
        ("u_K_R_E_C_cmd_mDs", real_T),
        ("v_K_R_E_C_cmd_mDs", real_T),
        ("w_K_R_E_C_cmd_mDs", real_T)
    ]

class fc_att_euler_cmd_Bus(ctypes.Structure):
    _fields_ = [
        ("Phi_cmd_rad", real_T),
        ("Theta_cmd_rad", real_T),
        ("Psi_dot_cmd_radDs", real_T)
    ]

class fc_pilot_cmd_Bus(ctypes.Structure):
    _fields_ = [
        ("w_y_D_cmd_radDs", real_T),
        ("vel_K_R_E_C_cmd_mDs", fc_vel_K_R_E_C_cmd_mDs_Bus),
        ("att_euler_cmd", fc_att_euler_cmd_Bus),
        ("vel_att_mode_swi", boolean_T),
        ("arm_swi", boolean_T),
        ("override_swi", boolean_T),
        ("power_swi", boolean_T),
        ("rotor_start_swi", boolean_T)
    ]

class Failure_Bus(ctypes.Structure):
    _fields_ = [
        ("motor_loss", real_T*8)
    ]

# Haupt-Ein- und Ausgabestrukturen des DLL-Frameworks

class ExtU_RMT_FDM_DLL_FrameWork_FCS_RT_T(ctypes.Structure):
    _fields_ = [
        ("Simulation_Control", Simulation_Control_Bus),
        ("States_Init", States_Init_Bus),
        ("w_cmd_radDs", real_T * 8),
        ("fc_pilot_cmd", fc_pilot_cmd_Bus),
        ("Failures", Failure_Bus)
    ]

class ExtY_RMT_FDM_DLL_FrameWork_FCS_RT_T(ctypes.Structure):
    _fields_ = [
        ("Vehicle", Vehicle_Bus),
        ("Measurements", Measurements_Bus),
        ("fc_estimation", fc_est_Bus)
    ]

# Interne Zustands- und Signalstrukturen des Modells

class B_RMT_FDM_DLL_FrameWork_FCS_RT_T(ctypes.Structure):
    _fields_ = [
        ("Vehicle", Vehicle_Bus),
        ("Measurements", Measurements_Bus),
        ("RT2", fc_measurements_Bus),
        ("RT3", States_Init_Bus),
        ("RT1", fc_pilot_cmd_Bus),
        ("RT_itkc", fc_ctrl_cmd_Bus),
        ("RT4", Controller_Commands_Bus),
        ("Contoller_cmd_faults", Controller_Commands_Bus),
        ("Switch", Controller_Commands_Bus),
        ("Product", real_T * 3),
        ("Product2", real_T * 3)
    ]

class DW_RMT_FDM_DLL_FrameWork_FCS_RT_T(ctypes.Structure):
    _fields_ = [
        ("Delay16_DSTATE", real_T),
        ("Delay_DSTATE", real_T),
        ("Delay1_DSTATE", real_T),
        ("Delay2_DSTATE", real_T),
        ("Delay3_DSTATE", real_T),
        ("Delay17_DSTATE", real_T),
        ("Delay18_DSTATE", real_T),
        ("Delay4_DSTATE", real_T),
        ("Delay5_DSTATE", real_T),
        ("Delay6_DSTATE", real_T),
        ("Delay7_DSTATE", real_T),
        ("Delay8_DSTATE", real_T),
        ("Delay9_DSTATE", real_T),
        ("Delay10_DSTATE", real_T),
        ("Delay11_DSTATE", real_T),
        ("Delay12_DSTATE", real_T),
        ("Delay13_DSTATE", real_T),
        ("Delay14_DSTATE", real_T),
        ("Delay15_DSTATE", real_T),
        ("UD_DSTATE", real_T * 3),
        ("Delay_DSTATE_oj24", real_T * 10),
        ("Phi_Ref_DSTATE", real_T),
        ("Theta_Ref_DSTATE", real_T),
        ("p_Ref_DSTATE", real_T),
        ("q_Ref_DSTATE", real_T),
        ("r_Ref_DSTATE", real_T),
        ("DiscreteTimeIntegrator_DSTATE", real_T),
        ("DiscreteTimeIntegrator_DSTATE_hs0d", real_T),
        ("DiscreteTimeIntegrator_DSTATE_japy", real_T),
        ("DiscreteTimeIntegrator_DSTATE_avov", real_T * 8),
        ("DiscreteTimeIntegrator1_DSTATE", real_T * 3),
        ("DiscreteTimeIntegrator_DSTATE_pv2o", real_T * 3),
        ("DiscreteTimeIntegrator1_DSTATE_lwvn", real_T * 2),
        ("DiscreteTimeIntegrator_DSTATE_ajjv", real_T * 2),
        ("SFunction_DIMS5", int32_T),
        ("SFunction_DIMS6", int32_T),
        ("Phi_Ref_PrevResetState", int8_T),
        ("Theta_Ref_PrevResetState", int8_T),
        ("p_Ref_PrevResetState", int8_T),
        ("q_Ref_PrevResetState", int8_T),
        ("r_Ref_PrevResetState", int8_T),
        ("DiscreteTimeIntegrator_PrevResetState", int8_T),
        ("DiscreteTimeIntegrator_PrevResetState_nmap", int8_T),
        ("DiscreteTimeIntegrator_PrevResetState_fwtq", int8_T),
        ("DiscreteTimeIntegrator_PrevResetState_dbpn", int8_T),
        ("DiscreteTimeIntegrator_IC_LOADING", uint8_T),
        ("icLoad", boolean_T),
        ("icLoad_ooxy", boolean_T),
        ("icLoad_hvp0", boolean_T),
        ("icLoad_agwh", boolean_T),
        ("icLoad_k4aw", boolean_T),
        ("icLoad_eux1", boolean_T),
        ("icLoad_mxgu", boolean_T),
        ("icLoad_pbo0", boolean_T),
        ("icLoad_dtzm", boolean_T),
        ("icLoad_mfcp", boolean_T),
        ("icLoad_js0i", boolean_T),
        ("icLoad_doan", boolean_T),
        ("icLoad_mzf4", boolean_T),
        ("icLoad_chzd", boolean_T),
        ("icLoad_giyv", boolean_T),
        ("icLoad_lwdp", boolean_T),
        ("icLoad_bu4u", boolean_T),
        ("icLoad_atsy", boolean_T),
        ("icLoad_nbvc", boolean_T)
    ]

class X_RMT_FDM_DLL_FrameWork_FCS_RT_T(ctypes.Structure):
    _fields_ = [
        ("RMT_Plant_CSTATE", real_T * 54)
    ]

class XDot_RMT_FDM_DLL_FrameWork_FCS_RT_T(ctypes.Structure):
    _fields_ = [
        ("RMT_Plant_CSTATE", real_T * 54)
    ]

class XDis_RMT_FDM_DLL_FrameWork_FCS_RT_T(ctypes.Structure):
    _fields_ = [
        ("RMT_Plant_CSTATE", boolean_T * 54)
    ]

class PrevZCX_RMT_FDM_DLL_FrameWork_FCS_RT_T(ctypes.Structure):
    _fields_ = [
        ("Delay16_Reset_ZCE", ZCSigState),
        ("Delay_Reset_ZCE", ZCSigState),
        ("Delay1_Reset_ZCE", ZCSigState),
        ("Delay2_Reset_ZCE", ZCSigState),
        ("Delay3_Reset_ZCE", ZCSigState),
        ("Delay17_Reset_ZCE", ZCSigState),
        ("Delay18_Reset_ZCE", ZCSigState),
        ("Delay4_Reset_ZCE", ZCSigState),
        ("Delay5_Reset_ZCE", ZCSigState),
        ("Delay6_Reset_ZCE", ZCSigState),
        ("Delay7_Reset_ZCE", ZCSigState),
        ("Delay8_Reset_ZCE", ZCSigState),
        ("Delay9_Reset_ZCE", ZCSigState),
        ("Delay10_Reset_ZCE", ZCSigState),
        ("Delay11_Reset_ZCE", ZCSigState),
        ("Delay12_Reset_ZCE", ZCSigState),
        ("Delay13_Reset_ZCE", ZCSigState),
        ("Delay14_Reset_ZCE", ZCSigState),
        ("Delay15_Reset_ZCE", ZCSigState),
        ("Delay_Reset_ZCE_pegz", ZCSigState)
    ]    