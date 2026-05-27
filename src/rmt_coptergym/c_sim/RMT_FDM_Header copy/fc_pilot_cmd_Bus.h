/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: fc_pilot_cmd_Bus.h
 *
 * Code generated for Simulink model 'RMT_FDM_DLL_FrameWork_FCS_RT'.
 *
 * Model version                  : 11.39
 * Simulink Coder version         : 24.2 (R2024b) 21-Jun-2024
 * C/C++ source code generated on : Mon Mar 30 13:54:53 2026
 */

#ifndef fc_pilot_cmd_Bus_h_
#define fc_pilot_cmd_Bus_h_
#include "rtwtypes.h"
#include "fc_vel_K_R_E_C_cmd_mDs_Bus.h"
#include "fc_att_euler_cmd_Bus.h"

typedef struct {
  real_T w_y_D_cmd_radDs;
  fc_vel_K_R_E_C_cmd_mDs_Bus vel_K_R_E_C_cmd_mDs;
  fc_att_euler_cmd_Bus att_euler_cmd;
  boolean_T vel_att_mode_swi;
  boolean_T arm_swi;
  boolean_T override_swi;
  boolean_T power_swi;
  boolean_T rotor_start_swi;
} fc_pilot_cmd_Bus;

#endif                                 /* fc_pilot_cmd_Bus_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
