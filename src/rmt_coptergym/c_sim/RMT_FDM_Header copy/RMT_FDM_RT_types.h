/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: RMT_FDM_RT_types.h
 *
 * Code generated for Simulink model 'RMT_FDM_RT'.
 *
 * Model version                  : 11.18
 * Simulink Coder version         : 24.2 (R2024b) 21-Jun-2024
 * C/C++ source code generated on : Mon Mar 30 13:53:24 2026
 *
 * Target selection: ert_shrlib.tlc
 * Embedded hardware selection: Intel->x86-64 (Windows64)
 * Emulation hardware selection:
 *    Differs from embedded hardware (MATLAB Host)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef RMT_FDM_RT_types_h_
#define RMT_FDM_RT_types_h_
#include "rtwtypes.h"
#include "pos_R_local_meas_Bus.h"
#ifndef DEFINED_TYPEDEF_FOR_Simulation_Control_Bus_
#define DEFINED_TYPEDEF_FOR_Simulation_Control_Bus_

typedef struct {
  boolean_T flg_Reset;
  boolean_T flg_Run;
  boolean_T flg_Run_p;
  boolean_T flg_Run_q;
  boolean_T flg_Run_r;
  boolean_T flg_Run_Phi;
  boolean_T flg_Run_Theta;
  boolean_T flg_Run_Psi;
  boolean_T flg_Run_vel_x;
  boolean_T flg_Run_vel_y;
  boolean_T flg_Run_vel_z;
  boolean_T flg_Run_pos_x;
  boolean_T flg_Run_pos_y;
  boolean_T flg_Run_pos_z;
  boolean_T flg_Propulsion_On;
  boolean_T flg_Aerodynamics_On;
  boolean_T flg_Weight_Balance_On;
  boolean_T flg_Ground_Contacts_On;
  boolean_T flg_Enable_Sensor_Errors;
  boolean_T flg_Enable_Controller;
} Simulation_Control_Bus;

#endif

#ifndef DEFINED_TYPEDEF_FOR_rot_W_OW_B_radDs_Bus_
#define DEFINED_TYPEDEF_FOR_rot_W_OW_B_radDs_Bus_

typedef struct {
  real_T w_x_W_OW_B_radDs;
  real_T w_y_W_OW_B_radDs;
  real_T w_z_W_OW_B_radDs;
} rot_W_OW_B_radDs_Bus;

#endif

#ifndef DEFINED_TYPEDEF_FOR_vel_W_R_E_O_mDs_Bus_
#define DEFINED_TYPEDEF_FOR_vel_W_R_E_O_mDs_Bus_

typedef struct {
  real_T u_W_R_E_O_mDs;
  real_T v_W_R_E_O_mDs;
  real_T w_W_R_E_O_mDs;
} vel_W_R_E_O_mDs_Bus;

#endif

#ifndef DEFINED_TYPEDEF_FOR_Atmosphere_Bus_
#define DEFINED_TYPEDEF_FOR_Atmosphere_Bus_

typedef struct {
  real_T Static_Temperature_ATM_K;
  real_T Speed_of_Sound_mDs;
  real_T Static_Pressure_ATM_NDm2;
  real_T rho_kgDm3;
} Atmosphere_Bus;

#endif

#ifndef DEFINED_TYPEDEF_FOR_rot_K_IB_B_radDs_Bus_
#define DEFINED_TYPEDEF_FOR_rot_K_IB_B_radDs_Bus_

typedef struct {
  real_T w_x_K_IB_B_radDs;
  real_T w_y_K_IB_B_radDs;
  real_T w_z_K_IB_B_radDs;
} rot_K_IB_B_radDs_Bus;

#endif

#ifndef DEFINED_TYPEDEF_FOR_att_euler_rad_Bus_
#define DEFINED_TYPEDEF_FOR_att_euler_rad_Bus_

typedef struct {
  real_T Phi_rad;
  real_T Theta_rad;
  real_T Psi_rad;
} att_euler_rad_Bus;

#endif

#ifndef DEFINED_TYPEDEF_FOR_vel_K_R_E_B_mDs_Bus_
#define DEFINED_TYPEDEF_FOR_vel_K_R_E_B_mDs_Bus_

typedef struct {
  real_T u_K_R_E_B_mDs;
  real_T v_K_R_E_B_mDs;
  real_T w_K_R_E_B_mDs;
} vel_K_R_E_B_mDs_Bus;

#endif

#ifndef DEFINED_TYPEDEF_FOR_pos_R_O_m_Bus_
#define DEFINED_TYPEDEF_FOR_pos_R_O_m_Bus_

typedef struct {
  real_T x_R_O_m;
  real_T y_R_O_m;
  real_T z_R_O_m;
} pos_R_O_m_Bus;

#endif

#ifndef DEFINED_TYPEDEF_FOR_pos_R_WGS84_Bus_
#define DEFINED_TYPEDEF_FOR_pos_R_WGS84_Bus_

typedef struct {
  real_T lambda_R_WGS84_rad;
  real_T mue_R_WGS84_rad;
  real_T h_R_WGS84_m;
} pos_R_WGS84_Bus;

#endif

#ifndef DEFINED_TYPEDEF_FOR_Actuator_States_Init_Bus_
#define DEFINED_TYPEDEF_FOR_Actuator_States_Init_Bus_

typedef struct {
  real_T u_0_radDs[8];
} Actuator_States_Init_Bus;

#endif

#ifndef DEFINED_TYPEDEF_FOR_States_Init_Bus_
#define DEFINED_TYPEDEF_FOR_States_Init_Bus_

typedef struct {
  rot_K_IB_B_radDs_Bus rot_K_IB_B_radDs;
  att_euler_rad_Bus att_euler_rad;
  vel_K_R_E_B_mDs_Bus vel_K_R_E_B_mDs;
  pos_R_O_m_Bus pos_R_O_m;
  pos_R_WGS84_Bus pos_R_WGS84;
  Actuator_States_Init_Bus actuator;
} States_Init_Bus;

#endif

#ifndef DEFINED_TYPEDEF_FOR_Failure_Bus_
#define DEFINED_TYPEDEF_FOR_Failure_Bus_

typedef struct {
  real_T motor_loss[8];
} Failure_Bus;

#endif

#ifndef DEFINED_TYPEDEF_FOR_Controller_Commands_Bus_
#define DEFINED_TYPEDEF_FOR_Controller_Commands_Bus_

typedef struct {
  real_T w1_cmd_radDs;
  real_T w2_cmd_radDs;
  real_T w3_cmd_radDs;
  real_T w4_cmd_radDs;
  real_T w5_cmd_radDs;
  real_T w6_cmd_radDs;
  real_T w7_cmd_radDs;
  real_T w8_cmd_radDs;
} Controller_Commands_Bus;

#endif

#ifndef DEFINED_TYPEDEF_FOR_vel_dot_K_R_EB_B_mDs2_Bus_
#define DEFINED_TYPEDEF_FOR_vel_dot_K_R_EB_B_mDs2_Bus_

typedef struct {
  real_T u_dot_K_R_EB_B_mDs2;
  real_T v_dot_K_R_EB_B_mDs2;
  real_T w_dot_K_R_EB_B_mDs2;
} vel_dot_K_R_EB_B_mDs2_Bus;

#endif

#ifndef DEFINED_TYPEDEF_FOR_rot_dot_K_IB_B_B_radDs2_Bus_
#define DEFINED_TYPEDEF_FOR_rot_dot_K_IB_B_B_radDs2_Bus_

typedef struct {
  real_T w_x_dot_K_IB_B_B_radDs2;
  real_T w_y_dot_K_IB_B_B_radDs2;
  real_T w_z_dot_K_IB_B_B_radDs2;
} rot_dot_K_IB_B_B_radDs2_Bus;

#endif

#ifndef DEFINED_TYPEDEF_FOR_att_dot_euler_radDs_Bus_
#define DEFINED_TYPEDEF_FOR_att_dot_euler_radDs_Bus_

typedef struct {
  real_T Phi_dot_radDs;
  real_T Theta_dot_radDs;
  real_T Psi_dot_radDs;
} att_dot_euler_radDs_Bus;

#endif

#ifndef DEFINED_TYPEDEF_FOR_pos_dot_R_E_O_mDs_Bus_
#define DEFINED_TYPEDEF_FOR_pos_dot_R_E_O_mDs_Bus_

typedef struct {
  real_T x_dot_R_E_O_mDs;
  real_T y_dot_R_E_O_mDs;
  real_T z_dot_R_E_O_mDs;
} pos_dot_R_E_O_mDs_Bus;

#endif

#ifndef DEFINED_TYPEDEF_FOR_States_Dot_Bus_
#define DEFINED_TYPEDEF_FOR_States_Dot_Bus_

typedef struct {
  vel_dot_K_R_EB_B_mDs2_Bus vel_dot_K_R_EB_B_mDs2;
  rot_dot_K_IB_B_B_radDs2_Bus rot_dot_K_IB_B_B_radDs2;
  att_dot_euler_radDs_Bus att_dot_euler_radDs;
  pos_dot_R_E_O_mDs_Bus pos_dot_R_E_O_mDs;
} States_Dot_Bus;

#endif

#ifndef DEFINED_TYPEDEF_FOR_for_T_R_B_N_Bus_
#define DEFINED_TYPEDEF_FOR_for_T_R_B_N_Bus_

typedef struct {
  real_T X_T_R_B_N;
  real_T Y_T_R_B_N;
  real_T Z_P_R_B_N;
} for_T_R_B_N_Bus;

#endif

#ifndef DEFINED_TYPEDEF_FOR_mom_T_R_B_Nm_Bus_
#define DEFINED_TYPEDEF_FOR_mom_T_R_B_Nm_Bus_

typedef struct {
  real_T L_T_R_B_Nm;
  real_T M_T_R_B_Nm;
  real_T N_T_R_B_Nm;
} mom_T_R_B_Nm_Bus;

#endif

#ifndef DEFINED_TYPEDEF_FOR_for_mom_T_R_B_Bus_
#define DEFINED_TYPEDEF_FOR_for_mom_T_R_B_Bus_

typedef struct {
  for_T_R_B_N_Bus for_T_R_B_N;
  mom_T_R_B_Nm_Bus mom_T_R_B_Nm;
} for_mom_T_R_B_Bus;

#endif

#ifndef DEFINED_TYPEDEF_FOR_for_P_R_B_N_Bus_
#define DEFINED_TYPEDEF_FOR_for_P_R_B_N_Bus_

typedef struct {
  real_T X_P_R_B_N;
  real_T Y_P_R_B_N;
  real_T Z_P_R_B_N;
} for_P_R_B_N_Bus;

#endif

#ifndef DEFINED_TYPEDEF_FOR_mom_P_R_B_Nm_Bus_
#define DEFINED_TYPEDEF_FOR_mom_P_R_B_Nm_Bus_

typedef struct {
  real_T L_P_R_B_Nm;
  real_T M_P_R_B_Nm;
  real_T N_P_R_B_Nm;
} mom_P_R_B_Nm_Bus;

#endif

#ifndef DEFINED_TYPEDEF_FOR_for_mom_P_R_B_Bus_
#define DEFINED_TYPEDEF_FOR_for_mom_P_R_B_Bus_

typedef struct {
  for_P_R_B_N_Bus for_P_R_B_N;
  mom_P_R_B_Nm_Bus mom_P_R_B_Nm;
} for_mom_P_R_B_Bus;

#endif

#ifndef DEFINED_TYPEDEF_FOR_Propulsion_Data_Out_Bus_
#define DEFINED_TYPEDEF_FOR_Propulsion_Data_Out_Bus_

typedef struct {
  for_mom_P_R_B_Bus for_mom_P_R_B;
  real_T Propulsion_Out;
} Propulsion_Data_Out_Bus;

#endif

#ifndef DEFINED_TYPEDEF_FOR_for_A_R_B_N_Bus_
#define DEFINED_TYPEDEF_FOR_for_A_R_B_N_Bus_

typedef struct {
  real_T X_A_R_B_N;
  real_T Y_A_R_B_N;
  real_T Z_A_R_B_N;
} for_A_R_B_N_Bus;

#endif

#ifndef DEFINED_TYPEDEF_FOR_mom_A_R_B_Nm_Bus_
#define DEFINED_TYPEDEF_FOR_mom_A_R_B_Nm_Bus_

typedef struct {
  real_T L_A_R_B_Nm;
  real_T M_A_R_B_Nm;
  real_T N_A_R_B_Nm;
} mom_A_R_B_Nm_Bus;

#endif

#ifndef DEFINED_TYPEDEF_FOR_for_mom_A_R_B_Bus_
#define DEFINED_TYPEDEF_FOR_for_mom_A_R_B_Bus_

typedef struct {
  for_A_R_B_N_Bus for_A_R_B_N;
  mom_A_R_B_Nm_Bus mom_A_R_B_Nm;
} for_mom_A_R_B_Bus;

#endif

#ifndef DEFINED_TYPEDEF_FOR_for_LDG_R_B_N_Bus_
#define DEFINED_TYPEDEF_FOR_for_LDG_R_B_N_Bus_

typedef struct {
  real_T X_LDG_R_B_N;
  real_T Y_LDG_R_B_N;
  real_T Z_LDG_R_B_N;
} for_LDG_R_B_N_Bus;

#endif

#ifndef DEFINED_TYPEDEF_FOR_mom_LDG_R_B_Nm_Bus_
#define DEFINED_TYPEDEF_FOR_mom_LDG_R_B_Nm_Bus_

typedef struct {
  real_T L_LDG_R_B_Nm;
  real_T M_LDG_R_B_Nm;
  real_T N_LDG_R_B_Nm;
} mom_LDG_R_B_Nm_Bus;

#endif

#ifndef DEFINED_TYPEDEF_FOR_for_mom_LDG_R_B_Bus_
#define DEFINED_TYPEDEF_FOR_for_mom_LDG_R_B_Bus_

typedef struct {
  for_LDG_R_B_N_Bus for_LDG_R_B_N;
  mom_LDG_R_B_Nm_Bus mom_LDG_R_B_Nm;
} for_mom_LDG_R_B_Bus;

#endif

#ifndef DEFINED_TYPEDEF_FOR_for_G_R_B_N_Bus_
#define DEFINED_TYPEDEF_FOR_for_G_R_B_N_Bus_

typedef struct {
  real_T X_G_R_B_N;
  real_T Y_G_R_B_N;
  real_T Z_G_R_B_N;
} for_G_R_B_N_Bus;

#endif

#ifndef DEFINED_TYPEDEF_FOR_mom_G_R_B_Nm_Bus_
#define DEFINED_TYPEDEF_FOR_mom_G_R_B_Nm_Bus_

typedef struct {
  real_T L_G_R_B_Nm;
  real_T M_G_R_B_Nm;
  real_T N_G_R_B_Nm;
} mom_G_R_B_Nm_Bus;

#endif

#ifndef DEFINED_TYPEDEF_FOR_for_mom_G_R_B_Bus_
#define DEFINED_TYPEDEF_FOR_for_mom_G_R_B_Bus_

typedef struct {
  for_G_R_B_N_Bus for_G_R_B_N;
  mom_G_R_B_Nm_Bus mom_G_R_B_Nm;
} for_mom_G_R_B_Bus;

#endif

#ifndef DEFINED_TYPEDEF_FOR_Weight_Balance_Bus_
#define DEFINED_TYPEDEF_FOR_Weight_Balance_Bus_

typedef struct {
  real_T pos_RG_B_m[3];
  real_T m_kg;
  real_T I_R_BB_kgm2[9];
} Weight_Balance_Bus;

#endif

#ifndef DEFINED_TYPEDEF_FOR_Airframe_Outputs_Bus_
#define DEFINED_TYPEDEF_FOR_Airframe_Outputs_Bus_

typedef struct {
  for_mom_T_R_B_Bus for_mom_T_R_B;
  Propulsion_Data_Out_Bus Propulsion_Data_Out;
  for_mom_A_R_B_Bus for_mom_A_R_B;
  for_mom_LDG_R_B_Bus for_mom_LDG_R_B;
  for_mom_G_R_B_Bus for_mom_G_R_B;
  Weight_Balance_Bus Weight_Balance;
} Airframe_Outputs_Bus;

#endif

#ifndef DEFINED_TYPEDEF_FOR_Gravitation_Bus_
#define DEFINED_TYPEDEF_FOR_Gravitation_Bus_

typedef struct {
  real_T acc_G_R_OO_O_mDs2[3];
} Gravitation_Bus;

#endif

#ifndef DEFINED_TYPEDEF_FOR_Environment_Bus_
#define DEFINED_TYPEDEF_FOR_Environment_Bus_

typedef struct {
  Atmosphere_Bus Atmosphere;
  Gravitation_Bus Gravitation;
} Environment_Bus;

#endif

#ifndef DEFINED_TYPEDEF_FOR_rot_K_EB_B_radDs_Bus_
#define DEFINED_TYPEDEF_FOR_rot_K_EB_B_radDs_Bus_

typedef struct {
  real_T w_x_K_EB_B_radDs;
  real_T w_y_K_EB_B_radDs;
  real_T w_z_K_EB_B_radDs;
} rot_K_EB_B_radDs_Bus;

#endif

#ifndef DEFINED_TYPEDEF_FOR_rot_K_OB_B_radDs_Bus_
#define DEFINED_TYPEDEF_FOR_rot_K_OB_B_radDs_Bus_

typedef struct {
  real_T w_x_K_OB_B_radDs;
  real_T w_y_K_OB_B_radDs;
  real_T w_z_K_OB_B_radDs;
} rot_K_OB_B_radDs_Bus;

#endif

#ifndef DEFINED_TYPEDEF_FOR_Kin_Trafo_Matrices_Bus_
#define DEFINED_TYPEDEF_FOR_Kin_Trafo_Matrices_Bus_

typedef struct {
  real_T M_BO[9];
  real_T M_OB[9];
  real_T M_NO[9];
  real_T M_ON[9];
} Kin_Trafo_Matrices_Bus;

#endif

#ifndef DEFINED_TYPEDEF_FOR_Kinematic_Data_Bus_
#define DEFINED_TYPEDEF_FOR_Kinematic_Data_Bus_

typedef struct {
  rot_K_IB_B_radDs_Bus rot_K_IB_B_radDs;
  vel_K_R_E_B_mDs_Bus vel_K_R_E_B_mDs;
  rot_K_EB_B_radDs_Bus rot_K_EB_B_radDs;
  rot_K_OB_B_radDs_Bus rot_K_OB_B_radDs;
  Kin_Trafo_Matrices_Bus Kin_Trafo_Matrices;
} Kinematic_Data_Bus;

#endif

#ifndef DEFINED_TYPEDEF_FOR_vel_A_R_E_O_mDs_Bus_
#define DEFINED_TYPEDEF_FOR_vel_A_R_E_O_mDs_Bus_

typedef struct {
  real_T u_A_R_E_0_mDs;
  real_T v_A_R_E_0_mDs;
  real_T w_A_R_E_0_mDs;
} vel_A_R_E_O_mDs_Bus;

#endif

#ifndef DEFINED_TYPEDEF_FOR_vel_A_R_E_B_mDs_Bus_
#define DEFINED_TYPEDEF_FOR_vel_A_R_E_B_mDs_Bus_

typedef struct {
  real_T u_A_R_E_B_mDs;
  real_T v_A_R_E_B_mDs;
  real_T w_A_R_E_B_mDs;
} vel_A_R_E_B_mDs_Bus;

#endif

#ifndef DEFINED_TYPEDEF_FOR_Aero_Velocities_Bus_
#define DEFINED_TYPEDEF_FOR_Aero_Velocities_Bus_

typedef struct {
  vel_A_R_E_O_mDs_Bus vel_A_R_E_0_mDs;
  vel_A_R_E_B_mDs_Bus vel_A_R_E_B_mDs;
} Aero_Velocities_Bus;

#endif

#ifndef DEFINED_TYPEDEF_FOR_Translation_A_R_Bus_
#define DEFINED_TYPEDEF_FOR_Translation_A_R_Bus_

typedef struct {
  real_T VEL_A_R_abs_mDs;
  real_T alpha_A_R_rad;
  real_T beta_A_R_rad;
} Translation_A_R_Bus;

#endif

#ifndef DEFINED_TYPEDEF_FOR_Aero_Trafo_Matrices_Bus_
#define DEFINED_TYPEDEF_FOR_Aero_Trafo_Matrices_Bus_

typedef struct {
  real_T M_BS[9];
  real_T M_SB[9];
  real_T M_BA[9];
  real_T M_AB[9];
  real_T M_AO[9];
  real_T M_OA[9];
} Aero_Trafo_Matrices_Bus;

#endif

#ifndef DEFINED_TYPEDEF_FOR_rot_A_AB_B_radDs_Bus_
#define DEFINED_TYPEDEF_FOR_rot_A_AB_B_radDs_Bus_

typedef struct {
  real_T w_x_A_AB_B_radDs;
  real_T w_y_A_AB_B_radDs;
  real_T w_z_A_AB_B_radDs;
} rot_A_AB_B_radDs_Bus;

#endif

#ifndef DEFINED_TYPEDEF_FOR_rot_A_AB_A_radDs_Bus_
#define DEFINED_TYPEDEF_FOR_rot_A_AB_A_radDs_Bus_

typedef struct {
  real_T w_x_A_AB_A_radDs;
  real_T w_y_A_AB_A_radDs;
  real_T w_z_A_AB_A_radDs;
} rot_A_AB_A_radDs_Bus;

#endif

#ifndef DEFINED_TYPEDEF_FOR_rot_A_AB_S_radDs_Bus_
#define DEFINED_TYPEDEF_FOR_rot_A_AB_S_radDs_Bus_

typedef struct {
  real_T w_x_A_AB_S_radDs;
  real_T w_y_A_AB_S_radDs;
  real_T w_z_A_AB_S_radDs;
} rot_A_AB_S_radDs_Bus;

#endif

#ifndef DEFINED_TYPEDEF_FOR_Aero_Angular_Rates_Bus_
#define DEFINED_TYPEDEF_FOR_Aero_Angular_Rates_Bus_

typedef struct {
  rot_A_AB_B_radDs_Bus rot_A_AB_B_radDs;
  rot_A_AB_A_radDs_Bus rot_A_AB_A_radDs;
  rot_A_AB_S_radDs_Bus rot_A_AB_S_radDs;
} Aero_Angular_Rates_Bus;

#endif

#ifndef DEFINED_TYPEDEF_FOR_Airdata_Bus_
#define DEFINED_TYPEDEF_FOR_Airdata_Bus_

typedef struct {
  Aero_Velocities_Bus Aero_Velocities;
  Translation_A_R_Bus Translation_A_R;
  Aero_Trafo_Matrices_Bus Aero_Trafo_Matrices;
  Aero_Angular_Rates_Bus Aero_Angular_Rates;
} Airdata_Bus;

#endif

#ifndef DEFINED_TYPEDEF_FOR_vel_W_R_E_B_mDs_Bus_
#define DEFINED_TYPEDEF_FOR_vel_W_R_E_B_mDs_Bus_

typedef struct {
  real_T u_W_R_E_B_mDs;
  real_T v_W_R_E_B_mDs;
  real_T w_W_R_E_B_mDs;
} vel_W_R_E_B_mDs_Bus;

#endif

#ifndef DEFINED_TYPEDEF_FOR_Wind_Velocities_Bus_
#define DEFINED_TYPEDEF_FOR_Wind_Velocities_Bus_

typedef struct {
  vel_W_R_E_B_mDs_Bus vel_W_R_E_B_mDs;
  vel_W_R_E_O_mDs_Bus vel_W_R_E_O_mDs;
} Wind_Velocities_Bus;

#endif

#ifndef DEFINED_TYPEDEF_FOR_rot_W_0W_0_radDs_Bus_
#define DEFINED_TYPEDEF_FOR_rot_W_0W_0_radDs_Bus_

typedef struct {
  real_T w_x_W_0W_0_radDs;
  real_T w_y_W_0W_0_radDs;
  real_T w_z_W_0W_0_radDs;
} rot_W_0W_0_radDs_Bus;

#endif

#ifndef DEFINED_TYPEDEF_FOR_Wind_Angular_Rates_Bus_
#define DEFINED_TYPEDEF_FOR_Wind_Angular_Rates_Bus_

typedef struct {
  rot_W_0W_0_radDs_Bus rot_W_0W_0_radDs;
  rot_W_OW_B_radDs_Bus rot_W_OW_B_radDs;
} Wind_Angular_Rates_Bus;

#endif

#ifndef DEFINED_TYPEDEF_FOR_Wind_Data_Bus_
#define DEFINED_TYPEDEF_FOR_Wind_Data_Bus_

typedef struct {
  Wind_Velocities_Bus Wind_Velocities;
  Wind_Angular_Rates_Bus Wind_Angular_Rates;
} Wind_Data_Bus;

#endif

#ifndef DEFINED_TYPEDEF_FOR_Motion_Kinematics_Bus_
#define DEFINED_TYPEDEF_FOR_Motion_Kinematics_Bus_

typedef struct {
  Kinematic_Data_Bus Kinematic_Data;
  Airdata_Bus Airdata;
  Wind_Data_Bus Wind_Data;
} Motion_Kinematics_Bus;

#endif

#ifndef DEFINED_TYPEDEF_FOR_Outputs_Bus_
#define DEFINED_TYPEDEF_FOR_Outputs_Bus_

typedef struct {
  States_Dot_Bus States_Dot;
  Airframe_Outputs_Bus Airframe_Outputs;
  Environment_Bus Environment;
  Motion_Kinematics_Bus Motion_Kinematics;
} Outputs_Bus;

#endif

#ifndef DEFINED_TYPEDEF_FOR_States_Bus_
#define DEFINED_TYPEDEF_FOR_States_Bus_

typedef struct {
  rot_K_IB_B_radDs_Bus rot_K_IB_B_radDs;
  att_euler_rad_Bus att_euler_rad;
  vel_K_R_E_B_mDs_Bus vel_K_R_E_B_mDs;
  pos_R_O_m_Bus pos_R_O_m;
} States_Bus;

#endif

#ifndef DEFINED_TYPEDEF_FOR_Commands_Bus_
#define DEFINED_TYPEDEF_FOR_Commands_Bus_

typedef struct {
  real_T w1_act_radDs;
  real_T w2_act_radDs;
  real_T w3_act_radDs;
  real_T w4_act_radDs;
  real_T w5_act_radDs;
  real_T w6_act_radDs;
  real_T w7_act_radDs;
  real_T w8_act_radDs;
} Commands_Bus;

#endif

#ifndef DEFINED_TYPEDEF_FOR_Vehicle_Bus_
#define DEFINED_TYPEDEF_FOR_Vehicle_Bus_

typedef struct {
  States_Bus States;
  Outputs_Bus Outputs;
  Commands_Bus Commands;
} Vehicle_Bus;

#endif

#ifndef DEFINED_TYPEDEF_FOR_baro_meas_Bus_
#define DEFINED_TYPEDEF_FOR_baro_meas_Bus_

typedef struct {
  real_T Static_Pressure_meas_NDm2;
  real_T Static_Temperature_meas_K;
  real_T h_Baro_meas_m;
} baro_meas_Bus;

#endif

#ifndef DEFINED_TYPEDEF_FOR_gyro_meas_Bus_
#define DEFINED_TYPEDEF_FOR_gyro_meas_Bus_

typedef struct {
  real_T w_x_K_IB_B_IMU_meas_radDs;
  real_T w_y_K_IB_B_IMU_meas_radDs;
  real_T w_z_K_IB_B_IMU_meas_radDs;
} gyro_meas_Bus;

#endif

#ifndef DEFINED_TYPEDEF_FOR_acc_meas_Bus_
#define DEFINED_TYPEDEF_FOR_acc_meas_Bus_

typedef struct {
  real_T f_x_P_B_IMU_meas_mDs2;
  real_T f_y_P_B_IMU_meas_mDs2;
  real_T f_z_P_B_IMU_meas_mDs2;
} acc_meas_Bus;

#endif

#ifndef DEFINED_TYPEDEF_FOR_imu_meas_Bus_
#define DEFINED_TYPEDEF_FOR_imu_meas_Bus_

typedef struct {
  gyro_meas_Bus gyro_meas;
  acc_meas_Bus acc_meas;
} imu_meas_Bus;

#endif

#ifndef DEFINED_TYPEDEF_FOR_pos_R_WGS84_meas_Bus_
#define DEFINED_TYPEDEF_FOR_pos_R_WGS84_meas_Bus_

typedef struct {
  real_T lambda_R_WGS84_meas_rad;
  real_T mue_R_WGS84_meas_rad;
  real_T h_R_WGS84_meas_m;
} pos_R_WGS84_meas_Bus;

#endif

#ifndef DEFINED_TYPEDEF_FOR_vel_K_R_E_O_meas_Bus_
#define DEFINED_TYPEDEF_FOR_vel_K_R_E_O_meas_Bus_

typedef struct {
  real_T u_K_R_E_O_meas_mDs;
  real_T v_K_R_E_O_meas_mDs;
  real_T w_K_R_E_O_meas_mDs;
} vel_K_R_E_O_meas_Bus;

#endif

#ifndef DEFINED_TYPEDEF_FOR_path_K_R_meas_rad_Bus_
#define DEFINED_TYPEDEF_FOR_path_K_R_meas_rad_Bus_

typedef struct {
  real_T gamma_K_R_meas_rad;
  real_T chi_K_R_meas_rad;
} path_K_R_meas_rad_Bus;

#endif

#ifndef DEFINED_TYPEDEF_FOR_Translation_K_R_meas_Bus_
#define DEFINED_TYPEDEF_FOR_Translation_K_R_meas_Bus_

typedef struct {
  real_T vel_K_R_abs_meas_mDs;
  path_K_R_meas_rad_Bus path_K_R_meas_rad;
} Translation_K_R_meas_Bus;

#endif

#ifndef DEFINED_TYPEDEF_FOR_gps_meas_Bus_
#define DEFINED_TYPEDEF_FOR_gps_meas_Bus_

typedef struct {
  pos_R_WGS84_meas_Bus pos_R_WGS84_meas;
  pos_R_local_meas_Bus pos_R_local_meas;
  vel_K_R_E_O_meas_Bus vel_K_R_E_O_meas;
  Translation_K_R_meas_Bus Translation_K_R_meas;
} gps_meas_Bus;

#endif

#ifndef DEFINED_TYPEDEF_FOR_ahrs_meas_Bus_
#define DEFINED_TYPEDEF_FOR_ahrs_meas_Bus_

typedef struct {
  real_T Phi_meas_rad;
  real_T Theta_meas_rad;
  real_T Psi_meas_rad;
  real_T M_BO_meas[9];
  real_T M_OB_meas[9];
} ahrs_meas_Bus;

#endif

#ifndef DEFINED_TYPEDEF_FOR_motor_meas_Bus_
#define DEFINED_TYPEDEF_FOR_motor_meas_Bus_

typedef struct {
  real_T w1_meas_radDs;
  real_T w2_meas_radDs;
  real_T w3_meas_radDs;
  real_T w4_meas_radDs;
  real_T w5_meas_radDs;
  real_T w6_meas_radDs;
  real_T w7_meas_radDs;
  real_T w8_meas_radDs;
} motor_meas_Bus;

#endif

#ifndef DEFINED_TYPEDEF_FOR_switches_meas_Bus_
#define DEFINED_TYPEDEF_FOR_switches_meas_Bus_

typedef struct {
  real_T wow_switch_1_meas;
} switches_meas_Bus;

#endif

#ifndef DEFINED_TYPEDEF_FOR_Measurements_Bus_
#define DEFINED_TYPEDEF_FOR_Measurements_Bus_

typedef struct {
  baro_meas_Bus baro_meas;
  imu_meas_Bus imu_meas;
  gps_meas_Bus gps_meas;
  ahrs_meas_Bus ahrs_meas;
  motor_meas_Bus motor_meas;
  switches_meas_Bus switches_meas;
} Measurements_Bus;

#endif

#ifndef DEFINED_TYPEDEF_FOR_struct_ll1jZ5uVLOVPuPbqbOoQ7F_
#define DEFINED_TYPEDEF_FOR_struct_ll1jZ5uVLOVPuPbqbOoQ7F_

typedef struct {
  real_T rot_dir;
  real_T T;
  real_T u_min;
  real_T u_max;
  real_T u_0;
} struct_ll1jZ5uVLOVPuPbqbOoQ7F;

#endif

#ifndef DEFINED_TYPEDEF_FOR_struct_8NJXmdPO4l0ktN8poN1fPB_
#define DEFINED_TYPEDEF_FOR_struct_8NJXmdPO4l0ktN8poN1fPB_

typedef struct {
  real_T pos_PfP_Pf_m[3];
  real_T pos_RPf_B_m[3];
  real_T D;
  struct_ll1jZ5uVLOVPuPbqbOoQ7F Electric_Drive;
} struct_8NJXmdPO4l0ktN8poN1fPB;

#endif

#ifndef DEFINED_TYPEDEF_FOR_struct_wwfm95Z8BQf7NEemEoGwBC_
#define DEFINED_TYPEDEF_FOR_struct_wwfm95Z8BQf7NEemEoGwBC_

typedef struct {
  real_T Vel_brPts_mDs[11];
  real_T omega_brPts_radDs[26];
  real_T Cz[286];
  real_T Cn[286];
} struct_wwfm95Z8BQf7NEemEoGwBC;

#endif

#ifndef DEFINED_TYPEDEF_FOR_struct_qXZFuXHL3JOSsWXmuRsKx_
#define DEFINED_TYPEDEF_FOR_struct_qXZFuXHL3JOSsWXmuRsKx_

typedef struct {
  struct_8NJXmdPO4l0ktN8poN1fPB Propeller[8];
  struct_wwfm95Z8BQf7NEemEoGwBC Lookup;
} struct_qXZFuXHL3JOSsWXmuRsKx;

#endif

/* Forward declaration for rtModel */
typedef struct tag_RTM_RMT_FDM_RT_T RT_MODEL_RMT_FDM_RT_T;

#endif                                 /* RMT_FDM_RT_types_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
