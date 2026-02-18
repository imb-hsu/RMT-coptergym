/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: RMT_FDM_DLL_FrameWork_FCS_RT_types.h
 *
 * Code generated for Simulink model 'RMT_FDM_DLL_FrameWork_FCS_RT'.
 *
 * Model version                  : 11.34
 * Simulink Coder version         : 24.2 (R2024b) 21-Jun-2024
 * C/C++ source code generated on : Thu Dec  4 22:28:01 2025
 *
 * Target selection: ert_shrlib.tlc
 * Embedded hardware selection: Intel->x86-64 (Windows64)
 * Emulation hardware selection:
 *    Differs from embedded hardware (MATLAB Host)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef RMT_FDM_DLL_FrameWork_FCS_RT_types_h_
#define RMT_FDM_DLL_FrameWork_FCS_RT_types_h_
#include "rtwtypes.h"
#include "fc_vel_K_R_E_C_cmd_mDs_Bus.h"
#include "fc_att_euler_cmd_Bus.h"
#include "fc_pilot_cmd_Bus.h"
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

#ifndef DEFINED_TYPEDEF_FOR_fc_baro_meas_Bus_
#define DEFINED_TYPEDEF_FOR_fc_baro_meas_Bus_

typedef struct {
  real_T Static_Pressure_meas_NDm2;
  real_T Static_Temperature_meas_K;
  real_T h_Alt_Baro_meas_m;
} fc_baro_meas_Bus;

#endif

#ifndef DEFINED_TYPEDEF_FOR_fc_gyro_meas_Bus_
#define DEFINED_TYPEDEF_FOR_fc_gyro_meas_Bus_

typedef struct {
  real_T w_x_K_IB_B_IMU_meas_radDs;
  real_T w_y_K_IB_B_IMU_meas_radDs;
  real_T w_z_K_IB_B_IMU_meas_radDs;
} fc_gyro_meas_Bus;

#endif

#ifndef DEFINED_TYPEDEF_FOR_fc_acc_meas_Bus_
#define DEFINED_TYPEDEF_FOR_fc_acc_meas_Bus_

typedef struct {
  real_T f_x_P_B_IMU_meas_mDs2;
  real_T f_y_P_B_IMU_meas_mDs2;
  real_T f_z_P_B_IMU_meas_mDs2;
} fc_acc_meas_Bus;

#endif

#ifndef DEFINED_TYPEDEF_FOR_fc_imu_meas_Bus_
#define DEFINED_TYPEDEF_FOR_fc_imu_meas_Bus_

typedef struct {
  fc_gyro_meas_Bus gyro_meas;
  fc_acc_meas_Bus acc_meas;
} fc_imu_meas_Bus;

#endif

#ifndef DEFINED_TYPEDEF_FOR_fc_pos_R_WGS84_meas_Bus_
#define DEFINED_TYPEDEF_FOR_fc_pos_R_WGS84_meas_Bus_

typedef struct {
  real_T lambda_R_WGS84_meas_rad;
  real_T mue_R_WGS84_meas_rad;
  real_T h_R_WGS84_meas_m;
} fc_pos_R_WGS84_meas_Bus;

#endif

#ifndef DEFINED_TYPEDEF_FOR_fc_pos_R_local_meas_Bus_
#define DEFINED_TYPEDEF_FOR_fc_pos_R_local_meas_Bus_

typedef struct {
  real_T x_R_O_meas_m;
  real_T y_R_O_meas_m;
  real_T z_R_O_meas_m;
} fc_pos_R_local_meas_Bus;

#endif

#ifndef DEFINED_TYPEDEF_FOR_fc_vel_K_R_E_O_meas_Bus_
#define DEFINED_TYPEDEF_FOR_fc_vel_K_R_E_O_meas_Bus_

typedef struct {
  real_T u_K_R_E_O_meas_mDs;
  real_T v_K_R_E_O_meas_mDs;
  real_T w_K_R_E_O_meas_mDs;
} fc_vel_K_R_E_O_meas_Bus;

#endif

#ifndef DEFINED_TYPEDEF_FOR_fc_path_K_R_meas_Bus_
#define DEFINED_TYPEDEF_FOR_fc_path_K_R_meas_Bus_

typedef struct {
  real_T gamma_K_R_meas_rad;
  real_T chi_K_R_meas_rad;
} fc_path_K_R_meas_Bus;

#endif

#ifndef DEFINED_TYPEDEF_FOR_fc_translation_K_R_meas_Bus_
#define DEFINED_TYPEDEF_FOR_fc_translation_K_R_meas_Bus_

typedef struct {
  real_T vel_K_R_abs_meas_mDs;
  fc_path_K_R_meas_Bus path_K_R_meas_rad;
} fc_translation_K_R_meas_Bus;

#endif

#ifndef DEFINED_TYPEDEF_FOR_fc_gps_meas_Bus_
#define DEFINED_TYPEDEF_FOR_fc_gps_meas_Bus_

typedef struct {
  fc_pos_R_WGS84_meas_Bus pos_R_WGS84_meas;
  fc_pos_R_local_meas_Bus pos_R_local_meas;
  fc_vel_K_R_E_O_meas_Bus vel_K_R_E_O_meas;
  fc_translation_K_R_meas_Bus Translation_K_R_meas;
} fc_gps_meas_Bus;

#endif

#ifndef DEFINED_TYPEDEF_FOR_fc_ahrs_meas_Bus_
#define DEFINED_TYPEDEF_FOR_fc_ahrs_meas_Bus_

typedef struct {
  real_T Phi_meas_rad;
  real_T Theta_meas_rad;
  real_T Psi_meas_rad;
  real_T M_BO_meas[9];
  real_T M_OB_meas[9];
} fc_ahrs_meas_Bus;

#endif

#ifndef DEFINED_TYPEDEF_FOR_fc_measurements_Bus_
#define DEFINED_TYPEDEF_FOR_fc_measurements_Bus_

typedef struct {
  fc_baro_meas_Bus baro_meas;
  fc_imu_meas_Bus imu_meas;
  fc_gps_meas_Bus gps_meas;
  fc_ahrs_meas_Bus ahrs_meas;
} fc_measurements_Bus;

#endif

#ifndef DEFINED_TYPEDEF_FOR_fc_ctrl_cmd_Bus_
#define DEFINED_TYPEDEF_FOR_fc_ctrl_cmd_Bus_

typedef struct {
  real_T w1_cmd_radDs;
  real_T w2_cmd_radDs;
  real_T w3_cmd_radDs;
  real_T w4_cmd_radDs;
  real_T w5_cmd_radDs;
  real_T w6_cmd_radDs;
  real_T w7_cmd_radDs;
  real_T w8_cmd_radDs;
} fc_ctrl_cmd_Bus;

#endif

#ifndef DEFINED_TYPEDEF_FOR_RM_Phi_Bus_
#define DEFINED_TYPEDEF_FOR_RM_Phi_Bus_

typedef struct {
  real_T Phi_Dot_radDs;
  real_T Phi_ref_rad;
} RM_Phi_Bus;

#endif

#ifndef DEFINED_TYPEDEF_FOR_RM_Theta_Bus_
#define DEFINED_TYPEDEF_FOR_RM_Theta_Bus_

typedef struct {
  real_T Theta_Dot_radDs;
  real_T Theta_ref_rad;
} RM_Theta_Bus;

#endif

#ifndef DEFINED_TYPEDEF_FOR_RM_attitude_Bus_
#define DEFINED_TYPEDEF_FOR_RM_attitude_Bus_

typedef struct {
  RM_Phi_Bus RM_Phi;
  RM_Theta_Bus RM_Theta;
  real_T PsiDot_cmd_radDs;
} RM_attitude_Bus;

#endif

#ifndef DEFINED_TYPEDEF_FOR_RM_p_Bus_
#define DEFINED_TYPEDEF_FOR_RM_p_Bus_

typedef struct {
  real_T nu_p_radDs2;
  real_T p_ref_radDs;
} RM_p_Bus;

#endif

#ifndef DEFINED_TYPEDEF_FOR_RM_q_Bus_
#define DEFINED_TYPEDEF_FOR_RM_q_Bus_

typedef struct {
  real_T nu_q_radDs2;
  real_T q_ref_radDs;
} RM_q_Bus;

#endif

#ifndef DEFINED_TYPEDEF_FOR_RM_r_Bus_
#define DEFINED_TYPEDEF_FOR_RM_r_Bus_

typedef struct {
  real_T nu_r_radDs2;
  real_T r_ref_radDs;
} RM_r_Bus;

#endif

#ifndef DEFINED_TYPEDEF_FOR_RM_rate_Bus_
#define DEFINED_TYPEDEF_FOR_RM_rate_Bus_

typedef struct {
  RM_p_Bus RM_p;
  RM_q_Bus RM_q;
  RM_r_Bus RM_r;
} RM_rate_Bus;

#endif

#ifndef DEFINED_TYPEDEF_FOR_RM_u_C_Bus_
#define DEFINED_TYPEDEF_FOR_RM_u_C_Bus_

typedef struct {
  real_T nu_u_mDs2;
  real_T u_C_ref_mDs;
} RM_u_C_Bus;

#endif

#ifndef DEFINED_TYPEDEF_FOR_RM_v_C_Bus_
#define DEFINED_TYPEDEF_FOR_RM_v_C_Bus_

typedef struct {
  real_T nu_v_mDs2;
  real_T v_C_ref_mDs;
} RM_v_C_Bus;

#endif

#ifndef DEFINED_TYPEDEF_FOR_RM_w_C_Bus_
#define DEFINED_TYPEDEF_FOR_RM_w_C_Bus_

typedef struct {
  real_T nu_w_mDs2;
  real_T w_C_ref_mDs;
} RM_w_C_Bus;

#endif

#ifndef DEFINED_TYPEDEF_FOR_RM_vel_Bus_
#define DEFINED_TYPEDEF_FOR_RM_vel_Bus_

typedef struct {
  RM_u_C_Bus RM_u_C;
  RM_v_C_Bus RM_v_C;
  RM_w_C_Bus RM_w_C;
} RM_vel_Bus;

#endif

#ifndef DEFINED_TYPEDEF_FOR_fc_RM_Bus_
#define DEFINED_TYPEDEF_FOR_fc_RM_Bus_

typedef struct {
  RM_attitude_Bus RM_attitude;
  RM_rate_Bus RM_rate;
  RM_vel_Bus RM_vel;
} fc_RM_Bus;

#endif

#ifndef DEFINED_TYPEDEF_FOR_vel_est_Bus_
#define DEFINED_TYPEDEF_FOR_vel_est_Bus_

typedef struct {
  real_T u_K_R_E_C_est_mDs;
  real_T v_K_R_E_C_est_mDs;
  real_T w_K_R_E_C_est_mDs;
} vel_est_Bus;

#endif

#ifndef DEFINED_TYPEDEF_FOR_vel_dot_est_Bus_
#define DEFINED_TYPEDEF_FOR_vel_dot_est_Bus_

typedef struct {
  real_T u_dot_K_R_EC_C_est_mDs2;
  real_T v_dot_K_R_EC_C_est_mDs2;
  real_T w_dot_K_R_EC_C_est_mDs2;
} vel_dot_est_Bus;

#endif

#ifndef DEFINED_TYPEDEF_FOR_rate_est_Bus_
#define DEFINED_TYPEDEF_FOR_rate_est_Bus_

typedef struct {
  real_T p_est_radDs;
  real_T q_est_radDs;
  real_T r_est_radDs;
} rate_est_Bus;

#endif

#ifndef DEFINED_TYPEDEF_FOR_rate_dot_est_Bus_
#define DEFINED_TYPEDEF_FOR_rate_dot_est_Bus_

typedef struct {
  real_T p_Dot_est_radDs2;
  real_T q_Dot_est_radDs2;
  real_T r_Dot_est_radDs2;
} rate_dot_est_Bus;

#endif

#ifndef DEFINED_TYPEDEF_FOR_att_est_Bus_
#define DEFINED_TYPEDEF_FOR_att_est_Bus_

typedef struct {
  real_T Phi_est_rad;
  real_T Theta_est_rad;
  real_T Psi_Dot_est_radDs;
} att_est_Bus;

#endif

#ifndef DEFINED_TYPEDEF_FOR_fc_est_Bus_
#define DEFINED_TYPEDEF_FOR_fc_est_Bus_

typedef struct {
  vel_est_Bus vel_est;
  vel_dot_est_Bus vel_dot_es;
  rate_est_Bus rate_est;
  rate_dot_est_Bus rate_dot_est;
  att_est_Bus att_est;
} fc_est_Bus;

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

/* Custom Type definition for MATLAB Function: '<S17>/Redistribution' */
#ifndef struct_tag_sGaAmWJmK5HvPUvd2k3PkCG
#define struct_tag_sGaAmWJmK5HvPUvd2k3PkCG

struct tag_sGaAmWJmK5HvPUvd2k3PkCG
{
  uint32_T nanflag;
  uint32_T ComparisonMethod;
};

#endif                                 /* struct_tag_sGaAmWJmK5HvPUvd2k3PkCG */

#ifndef typedef_sGaAmWJmK5HvPUvd2k3PkCG_RMT_FDM_DLL_FrameWork_FCS_RT_T
#define typedef_sGaAmWJmK5HvPUvd2k3PkCG_RMT_FDM_DLL_FrameWork_FCS_RT_T

typedef struct tag_sGaAmWJmK5HvPUvd2k3PkCG
  sGaAmWJmK5HvPUvd2k3PkCG_RMT_FDM_DLL_FrameWork_FCS_RT_T;

#endif      /* typedef_sGaAmWJmK5HvPUvd2k3PkCG_RMT_FDM_DLL_FrameWork_FCS_RT_T */

/* Custom Type definition for MATLAB Function: '<S17>/Scale_NST_Solution' */
#ifndef struct_tag_sc6f4Behc0Ffg9eeZ0XliHC
#define struct_tag_sc6f4Behc0Ffg9eeZ0XliHC

struct tag_sc6f4Behc0Ffg9eeZ0XliHC
{
  uint32_T dim;
  uint32_T nanflag;
  uint32_T linear;
  uint32_T ComparisonMethod;
};

#endif                                 /* struct_tag_sc6f4Behc0Ffg9eeZ0XliHC */

#ifndef typedef_sc6f4Behc0Ffg9eeZ0XliHC_RMT_FDM_DLL_FrameWork_FCS_RT_T
#define typedef_sc6f4Behc0Ffg9eeZ0XliHC_RMT_FDM_DLL_FrameWork_FCS_RT_T

typedef struct tag_sc6f4Behc0Ffg9eeZ0XliHC
  sc6f4Behc0Ffg9eeZ0XliHC_RMT_FDM_DLL_FrameWork_FCS_RT_T;

#endif      /* typedef_sc6f4Behc0Ffg9eeZ0XliHC_RMT_FDM_DLL_FrameWork_FCS_RT_T */

#ifndef struct_tag_smzGQHcQ1fZcSCW5rtLpn4F
#define struct_tag_smzGQHcQ1fZcSCW5rtLpn4F

struct tag_smzGQHcQ1fZcSCW5rtLpn4F
{
  boolean_T CaseSensitivity;
  char_T PartialMatching[6];
  boolean_T StructExpand;
  boolean_T IgnoreNulls;
  boolean_T SupportOverrides;
};

#endif                                 /* struct_tag_smzGQHcQ1fZcSCW5rtLpn4F */

#ifndef typedef_smzGQHcQ1fZcSCW5rtLpn4F_RMT_FDM_DLL_FrameWork_FCS_RT_T
#define typedef_smzGQHcQ1fZcSCW5rtLpn4F_RMT_FDM_DLL_FrameWork_FCS_RT_T

typedef struct tag_smzGQHcQ1fZcSCW5rtLpn4F
  smzGQHcQ1fZcSCW5rtLpn4F_RMT_FDM_DLL_FrameWork_FCS_RT_T;

#endif      /* typedef_smzGQHcQ1fZcSCW5rtLpn4F_RMT_FDM_DLL_FrameWork_FCS_RT_T */

/* Custom Type definition for MATLAB Function: '<S17>/Redistribution' */
#ifndef struct_tag_L5JvjW1A13FyCQi5N783sB
#define struct_tag_L5JvjW1A13FyCQi5N783sB

struct tag_L5JvjW1A13FyCQi5N783sB
{
  char_T f1[7];
};

#endif                                 /* struct_tag_L5JvjW1A13FyCQi5N783sB */

#ifndef typedef_cell_wrap_1_RMT_FDM_DLL_FrameWork_FCS_RT_T
#define typedef_cell_wrap_1_RMT_FDM_DLL_FrameWork_FCS_RT_T

typedef struct tag_L5JvjW1A13FyCQi5N783sB
  cell_wrap_1_RMT_FDM_DLL_FrameWork_FCS_RT_T;

#endif                  /* typedef_cell_wrap_1_RMT_FDM_DLL_FrameWork_FCS_RT_T */

/* Custom Type definition for MATLAB Function: '<S17>/Scale_NST_Solution' */
#ifndef struct_tag_6jR4RtbHdjyG00WYqgD5nF
#define struct_tag_6jR4RtbHdjyG00WYqgD5nF

struct tag_6jR4RtbHdjyG00WYqgD5nF
{
  char_T f1[16];
};

#endif                                 /* struct_tag_6jR4RtbHdjyG00WYqgD5nF */

#ifndef typedef_cell_wrap_0_RMT_FDM_DLL_FrameWork_FCS_RT_T
#define typedef_cell_wrap_0_RMT_FDM_DLL_FrameWork_FCS_RT_T

typedef struct tag_6jR4RtbHdjyG00WYqgD5nF
  cell_wrap_0_RMT_FDM_DLL_FrameWork_FCS_RT_T;

#endif                  /* typedef_cell_wrap_0_RMT_FDM_DLL_FrameWork_FCS_RT_T */

#ifndef struct_tag_njgfiHhWBCqqqpWsKZxr7F
#define struct_tag_njgfiHhWBCqqqpWsKZxr7F

struct tag_njgfiHhWBCqqqpWsKZxr7F
{
  char_T f1[15];
  char_T f2[15];
  char_T f3[12];
  char_T f4[11];
  char_T f5[16];
};

#endif                                 /* struct_tag_njgfiHhWBCqqqpWsKZxr7F */

#ifndef typedef_cell_2_RMT_FDM_DLL_FrameWork_FCS_RT_T
#define typedef_cell_2_RMT_FDM_DLL_FrameWork_FCS_RT_T

typedef struct tag_njgfiHhWBCqqqpWsKZxr7F cell_2_RMT_FDM_DLL_FrameWork_FCS_RT_T;

#endif                       /* typedef_cell_2_RMT_FDM_DLL_FrameWork_FCS_RT_T */

#ifndef struct_tag_xOZlLoGvSrTJr14RWwCqHG
#define struct_tag_xOZlLoGvSrTJr14RWwCqHG

struct tag_xOZlLoGvSrTJr14RWwCqHG
{
  char_T f1[3];
  char_T f2[7];
  char_T f3[6];
};

#endif                                 /* struct_tag_xOZlLoGvSrTJr14RWwCqHG */

#ifndef typedef_cell_1_RMT_FDM_DLL_FrameWork_FCS_RT_T
#define typedef_cell_1_RMT_FDM_DLL_FrameWork_FCS_RT_T

typedef struct tag_xOZlLoGvSrTJr14RWwCqHG cell_1_RMT_FDM_DLL_FrameWork_FCS_RT_T;

#endif                       /* typedef_cell_1_RMT_FDM_DLL_FrameWork_FCS_RT_T */

/* Custom Type definition for MATLAB Function: '<S17>/Redistribution' */
#ifndef struct_tag_HOps0FrfA6RiWumqewPwZD
#define struct_tag_HOps0FrfA6RiWumqewPwZD

struct tag_HOps0FrfA6RiWumqewPwZD
{
  cell_wrap_1_RMT_FDM_DLL_FrameWork_FCS_RT_T _data;
};

#endif                                 /* struct_tag_HOps0FrfA6RiWumqewPwZD */

#ifndef typedef_s_HOps0FrfA6RiWumqewPwZD_RMT_FDM_DLL_FrameWork_FCS_RT_T
#define typedef_s_HOps0FrfA6RiWumqewPwZD_RMT_FDM_DLL_FrameWork_FCS_RT_T

typedef struct tag_HOps0FrfA6RiWumqewPwZD
  s_HOps0FrfA6RiWumqewPwZD_RMT_FDM_DLL_FrameWork_FCS_RT_T;

#endif     /* typedef_s_HOps0FrfA6RiWumqewPwZD_RMT_FDM_DLL_FrameWork_FCS_RT_T */

/* Custom Type definition for MATLAB Function: '<S17>/Scale_NST_Solution' */
#ifndef struct_tag_1nlLkVeIuST25DF6il3ApD
#define struct_tag_1nlLkVeIuST25DF6il3ApD

struct tag_1nlLkVeIuST25DF6il3ApD
{
  cell_wrap_0_RMT_FDM_DLL_FrameWork_FCS_RT_T _data;
};

#endif                                 /* struct_tag_1nlLkVeIuST25DF6il3ApD */

#ifndef typedef_s_1nlLkVeIuST25DF6il3ApD_RMT_FDM_DLL_FrameWork_FCS_RT_T
#define typedef_s_1nlLkVeIuST25DF6il3ApD_RMT_FDM_DLL_FrameWork_FCS_RT_T

typedef struct tag_1nlLkVeIuST25DF6il3ApD
  s_1nlLkVeIuST25DF6il3ApD_RMT_FDM_DLL_FrameWork_FCS_RT_T;

#endif     /* typedef_s_1nlLkVeIuST25DF6il3ApD_RMT_FDM_DLL_FrameWork_FCS_RT_T */

#ifndef struct_tag_uzuPWHtc1cM7ZRTfbsKeiF
#define struct_tag_uzuPWHtc1cM7ZRTfbsKeiF

struct tag_uzuPWHtc1cM7ZRTfbsKeiF
{
  cell_2_RMT_FDM_DLL_FrameWork_FCS_RT_T _data;
};

#endif                                 /* struct_tag_uzuPWHtc1cM7ZRTfbsKeiF */

#ifndef typedef_s_uzuPWHtc1cM7ZRTfbsKeiF_RMT_FDM_DLL_FrameWork_FCS_RT_T
#define typedef_s_uzuPWHtc1cM7ZRTfbsKeiF_RMT_FDM_DLL_FrameWork_FCS_RT_T

typedef struct tag_uzuPWHtc1cM7ZRTfbsKeiF
  s_uzuPWHtc1cM7ZRTfbsKeiF_RMT_FDM_DLL_FrameWork_FCS_RT_T;

#endif     /* typedef_s_uzuPWHtc1cM7ZRTfbsKeiF_RMT_FDM_DLL_FrameWork_FCS_RT_T */

#ifndef struct_tag_JkNjgv3CFjBZhduPupEzEE
#define struct_tag_JkNjgv3CFjBZhduPupEzEE

struct tag_JkNjgv3CFjBZhduPupEzEE
{
  cell_1_RMT_FDM_DLL_FrameWork_FCS_RT_T _data;
};

#endif                                 /* struct_tag_JkNjgv3CFjBZhduPupEzEE */

#ifndef typedef_s_JkNjgv3CFjBZhduPupEzEE_RMT_FDM_DLL_FrameWork_FCS_RT_T
#define typedef_s_JkNjgv3CFjBZhduPupEzEE_RMT_FDM_DLL_FrameWork_FCS_RT_T

typedef struct tag_JkNjgv3CFjBZhduPupEzEE
  s_JkNjgv3CFjBZhduPupEzEE_RMT_FDM_DLL_FrameWork_FCS_RT_T;

#endif     /* typedef_s_JkNjgv3CFjBZhduPupEzEE_RMT_FDM_DLL_FrameWork_FCS_RT_T */

/* Forward declaration for rtModel */
typedef struct tag_RTM_RMT_FDM_DLL_FrameWork_FCS_RT_T
  RT_MODEL_RMT_FDM_DLL_FrameWork_FCS_RT_T;

#endif                               /* RMT_FDM_DLL_FrameWork_FCS_RT_types_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
