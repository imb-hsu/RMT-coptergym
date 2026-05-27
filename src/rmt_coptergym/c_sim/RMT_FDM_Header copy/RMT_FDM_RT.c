/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: RMT_FDM_RT.c
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

#include "RMT_FDM_RT.h"
#include "RMT_FDM_RT_types.h"
#include "rtwtypes.h"
#include "rt_nrand_Upu32_Yd_f_pw_snf.h"
#include <math.h>
#include "rt_atan2d_snf.h"
#include <string.h>
#include "rt_powd_snf.h"
#include "RMT_FDM_RT_private.h"
#include "look2_binlx.h"
#include "zero_crossing_types.h"

/* System initialize for referenced model: 'RMT_FDM_RT' */
void RMT_FDM_RT_Init(RT_MODEL_RMT_FDM_RT_T * const RMT_FDM_RT_M,
                     B_RMT_FDM_RT_caua_T *localB, DW_RMT_FDM_RT_fwu4_T *localDW,
                     X_RMT_FDM_RT_nymf_T *localX, ZCE_RMT_FDM_RT_T *localZCE)
{
  /* local scratch DWork variables */
  int32_T ForEach_itr;
  int32_T ForEach_itr_gq2o;
  int32_T i;
  int32_T iU;
  int32_T iU_0;
  int32_T iU_1;
  int32_T iU_2;
  int32_T iU_3;
  int32_T iU_4;
  int32_T iU_5;
  int32_T iU_6;
  int32_T iU_7;
  int32_T iU_8;
  int32_T iU_9;
  int32_T iU_a;
  int32_T iU_b;
  int32_T iU_c;
  int32_T iU_d;
  int32_T iU_e;
  int32_T iU_f;
  int32_T iU_g;
  int32_T i_0;
  int32_T i_1;
  int32_T i_2;
  int32_T i_3;
  uint32_T n6V;
  uint32_T n6V_0;
  uint32_T n6V_1;
  uint32_T n6V_2;
  uint32_T n6V_3;
  uint32_T n6V_4;
  uint32_T n6V_5;
  uint32_T n6V_6;
  uint32_T n6V_7;
  uint32_T n6V_8;
  uint32_T n6V_9;
  uint32_T n6V_a;
  uint32_T n6V_b;
  uint32_T n6V_c;
  uint32_T n6V_d;
  uint32_T n6V_e;
  uint32_T n6V_f;
  uint32_T n6V_g;
  uint32_T r;
  uint32_T r_0;
  uint32_T r_1;
  uint32_T r_2;
  uint32_T r_3;
  uint32_T r_4;
  uint32_T r_5;
  uint32_T r_6;
  uint32_T r_7;
  uint32_T r_8;
  uint32_T r_9;
  uint32_T r_a;
  uint32_T r_b;
  uint32_T r_c;
  uint32_T r_d;
  uint32_T r_e;
  uint32_T r_f;
  uint32_T r_g;
  uint32_T t;
  uint32_T t_0;
  uint32_T t_1;
  uint32_T t_2;
  uint32_T t_3;
  uint32_T t_4;
  uint32_T t_5;
  uint32_T t_6;
  uint32_T t_7;
  uint32_T t_8;
  uint32_T t_9;
  uint32_T t_a;
  uint32_T t_b;
  uint32_T t_c;
  uint32_T t_d;
  uint32_T t_e;
  uint32_T t_f;
  uint32_T t_g;
  uint32_T tseed;
  uint32_T tseed_0;
  uint32_T tseed_1;
  uint32_T tseed_2;
  uint32_T tseed_3;
  uint32_T tseed_4;
  uint32_T tseed_5;
  uint32_T tseed_6;
  uint32_T tseed_7;
  uint32_T tseed_8;
  uint32_T tseed_9;
  uint32_T tseed_a;
  uint32_T tseed_b;
  uint32_T tseed_c;
  uint32_T tseed_d;
  uint32_T tseed_e;
  uint32_T tseed_f;
  uint32_T tseed_g;

  /* InitializeConditions for Integrator: '<S12>/att_phi_rad' incorporates:
   *  Integrator: '<S13>/att_psi_rad'
   *  Integrator: '<S14>/att_theta_rad'
   *  Integrator: '<S21>/vel_x_K'
   *  Integrator: '<S22>/vel_y_K'
   *  Integrator: '<S238>/w_z_int_PRot_P_err_radDs'
   *  Integrator: '<S23>/vel_w_K'
   */
  if (rtmIsFirstInitCond(RMT_FDM_RT_M)) {
    localX->Phi_rad = 0.0;
    localX->Theta_rad = 0.0;
    localX->Psi_rad = 0.0;
    localX->u_K_R_E_B_mDs = 0.0;
    localX->v_K_R_E_B_mDs = 0.0;
    localX->w_K_R_E_B_mDs = 0.0;
    localX->w_z_int_PRot_P_err_radDs[0] = 0.0;
    localX->w_z_int_PRot_P_err_radDs[1] = 0.0;
    localX->w_z_int_PRot_P_err_radDs[2] = 0.0;
  }

  localDW->att_phi_rad_DWORK1 = true;

  /* End of InitializeConditions for Integrator: '<S12>/att_phi_rad' */

  /* InitializeConditions for Integrator: '<S14>/att_theta_rad' */
  localDW->att_theta_rad_DWORK1 = true;

  /* InitializeConditions for Integrator: '<S13>/att_psi_rad' */
  localDW->att_psi_rad_DWORK1 = true;

  /* InitializeConditions for Integrator: '<S21>/vel_x_K' */
  localDW->vel_x_K_DWORK1 = true;

  /* InitializeConditions for Integrator: '<S22>/vel_y_K' */
  localDW->vel_y_K_DWORK1 = true;

  /* InitializeConditions for Integrator: '<S23>/vel_w_K' */
  localDW->vel_w_K_DWORK1 = true;

  /* InitializeConditions for Integrator: '<S238>/w_z_int_PRot_P_err_radDs' */
  localDW->w_z_int_PRot_P_err_radDs_DWORK1 = true;

  /* InitializeConditions for RandomNumber: '<S228>/Random Number2' */
  for (iU = 0; iU < 3; iU = iU + 1) {
    tseed = (uint32_T)rtCP_RandomNumber2_Seed[iU];
    r = tseed >> 16U;
    t = tseed & 32768U;
    n6V = (((tseed - ((r << 16U) - t)) << 16U) + t) + r;
    if (n6V < 1U) {
      n6V = 1144108930U;
    } else if (n6V > 2147483646U) {
      n6V = 2147483646U;
    }

    localDW->RandSeed[iU] = n6V;
    localDW->NextOutput[iU] = rt_nrand_Upu32_Yd_f_pw_snf(&localDW->RandSeed[iU]);
  }

  /* End of InitializeConditions for RandomNumber: '<S228>/Random Number2' */

  /* InitializeConditions for Integrator: '<S18>/rot_x_K_IB_B_radDs' incorporates:
   *  Integrator: '<S17>/pos_z'
   *  Integrator: '<S19>/rot_y_K_IB_B_radDs'
   *  Integrator: '<S20>/rot_z_K_IB_B_radDs'
   *  Integrator: '<S237>/w_z_int_PRot_P_err_radDs'
   *  Integrator: '<S372>/w_z_int_PRot_P_err_radDs'
   *  Integrator: '<S373>/w_z_int_PRot_P_err_radDs'
   */
  if (rtmIsFirstInitCond(RMT_FDM_RT_M)) {
    localX->w_x_K_IB_B_radDs = 0.0;
    localX->w_y_K_IB_B_radDs = 0.0;
    localX->w_z_K_IB_B_radDs = 0.0;
    localX->z_R_O_m = 0.0;
    localX->w_z_int_PRot_P_err_radDs_iwjk[0] = 0.0;
    localX->w_z_int_PRot_P_err_radDs_iwjk[1] = 0.0;
    localX->w_z_int_PRot_P_err_radDs_iwjk[2] = 0.0;
    localX->w_z_int_PRot_P_err_radDs_auhp[0] = 0.0;
    localX->w_z_int_PRot_P_err_radDs_auhp[1] = 0.0;
    localX->w_z_int_PRot_P_err_radDs_auhp[2] = 0.0;
    localX->w_z_int_PRot_P_err_radDs_nmyl[0] = 0.0;
    localX->w_z_int_PRot_P_err_radDs_nmyl[1] = 0.0;
    localX->w_z_int_PRot_P_err_radDs_nmyl[2] = 0.0;
  }

  localDW->rot_x_K_IB_B_radDs_DWORK1 = true;

  /* End of InitializeConditions for Integrator: '<S18>/rot_x_K_IB_B_radDs' */

  /* InitializeConditions for Integrator: '<S19>/rot_y_K_IB_B_radDs' */
  localDW->rot_y_K_IB_B_radDs_DWORK1 = true;

  /* InitializeConditions for Integrator: '<S20>/rot_z_K_IB_B_radDs' */
  localDW->rot_z_K_IB_B_radDs_DWORK1 = true;

  /* InitializeConditions for Integrator: '<S17>/pos_z' */
  localDW->pos_z_DWORK1 = true;

  /* InitializeConditions for Integrator: '<S237>/w_z_int_PRot_P_err_radDs' */
  localDW->w_z_int_PRot_P_err_radDs_DWORK1_ndwy = true;

  /* InitializeConditions for Integrator: '<S372>/w_z_int_PRot_P_err_radDs' */
  localDW->w_z_int_PRot_P_err_radDs_DWORK1_ev2m = true;

  /* InitializeConditions for Integrator: '<S373>/w_z_int_PRot_P_err_radDs' */
  localDW->w_z_int_PRot_P_err_radDs_DWORK1_kugd = true;

  /* InitializeConditions for RandomNumber: '<S364>/Random Number2' */
  for (iU_0 = 0; iU_0 < 3; iU_0 = iU_0 + 1) {
    tseed_0 = (uint32_T)rtCP_RandomNumber2_Seed_kuez[iU_0];
    r_0 = tseed_0 >> 16U;
    t_0 = tseed_0 & 32768U;
    n6V_0 = (((tseed_0 - ((r_0 << 16U) - t_0)) << 16U) + t_0) + r_0;
    if (n6V_0 < 1U) {
      n6V_0 = 1144108930U;
    } else if (n6V_0 > 2147483646U) {
      n6V_0 = 2147483646U;
    }

    localDW->RandSeed_icpv[iU_0] = n6V_0;
    localDW->NextOutput_k1ay[iU_0] = rt_nrand_Upu32_Yd_f_pw_snf
      (&localDW->RandSeed_icpv[iU_0]);
  }

  /* End of InitializeConditions for RandomNumber: '<S364>/Random Number2' */

  /* InitializeConditions for Integrator: '<S387>/w_z_int_PRot_P_err_radDs' incorporates:
   *  Integrator: '<S388>/w_z_int_PRot_P_err_radDs'
   */
  if (rtmIsFirstInitCond(RMT_FDM_RT_M)) {
    localX->w_z_int_PRot_P_err_radDs_fg2g[0] = 0.0;
    localX->w_z_int_PRot_P_err_radDs_fg2g[1] = 0.0;
    localX->w_z_int_PRot_P_err_radDs_fg2g[2] = 0.0;
    localX->w_z_int_PRot_P_err_radDs_babv[0] = 0.0;
    localX->w_z_int_PRot_P_err_radDs_babv[1] = 0.0;
    localX->w_z_int_PRot_P_err_radDs_babv[2] = 0.0;
  }

  localDW->w_z_int_PRot_P_err_radDs_DWORK1_h3i2 = true;

  /* End of InitializeConditions for Integrator: '<S387>/w_z_int_PRot_P_err_radDs' */

  /* InitializeConditions for Integrator: '<S388>/w_z_int_PRot_P_err_radDs' */
  localDW->w_z_int_PRot_P_err_radDs_DWORK1_l3ag = true;

  /* InitializeConditions for RandomNumber: '<S380>/Random Number2' */
  for (iU_1 = 0; iU_1 < 3; iU_1 = iU_1 + 1) {
    tseed_1 = (uint32_T)rtCP_RandomNumber2_Seed_g2mi[iU_1];
    r_1 = tseed_1 >> 16U;
    t_1 = tseed_1 & 32768U;
    n6V_1 = (((tseed_1 - ((r_1 << 16U) - t_1)) << 16U) + t_1) + r_1;
    if (n6V_1 < 1U) {
      n6V_1 = 1144108930U;
    } else if (n6V_1 > 2147483646U) {
      n6V_1 = 2147483646U;
    }

    localDW->RandSeed_ju0n[iU_1] = n6V_1;
    localDW->NextOutput_pvtx[iU_1] = rt_nrand_Upu32_Yd_f_pw_snf
      (&localDW->RandSeed_ju0n[iU_1]);
  }

  /* End of InitializeConditions for RandomNumber: '<S380>/Random Number2' */

  /* InitializeConditions for RandomNumber: '<S316>/Random Number2' */
  for (iU_2 = 0; iU_2 < 3; iU_2 = iU_2 + 1) {
    tseed_2 = (uint32_T)rtCP_RandomNumber2_Seed_ndei[iU_2];
    r_2 = tseed_2 >> 16U;
    t_2 = tseed_2 & 32768U;
    n6V_2 = (((tseed_2 - ((r_2 << 16U) - t_2)) << 16U) + t_2) + r_2;
    if (n6V_2 < 1U) {
      n6V_2 = 1144108930U;
    } else if (n6V_2 > 2147483646U) {
      n6V_2 = 2147483646U;
    }

    localDW->RandSeed_h21n[iU_2] = n6V_2;
    localDW->NextOutput_ba35[iU_2] = rt_nrand_Upu32_Yd_f_pw_snf
      (&localDW->RandSeed_h21n[iU_2]);
  }

  /* End of InitializeConditions for RandomNumber: '<S316>/Random Number2' */

  /* InitializeConditions for RandomNumber: '<S354>/Random Number' */
  for (iU_3 = 0; iU_3 < 3; iU_3 = iU_3 + 1) {
    tseed_3 = (uint32_T)rtCP_RandomNumber_Seed[iU_3];
    r_3 = tseed_3 >> 16U;
    t_3 = tseed_3 & 32768U;
    n6V_3 = (((tseed_3 - ((r_3 << 16U) - t_3)) << 16U) + t_3) + r_3;
    if (n6V_3 < 1U) {
      n6V_3 = 1144108930U;
    } else if (n6V_3 > 2147483646U) {
      n6V_3 = 2147483646U;
    }

    localDW->RandSeed_hc1z[iU_3] = n6V_3;
    localDW->NextOutput_kxhu[iU_3] = rt_nrand_Upu32_Yd_f_pw_snf
      (&localDW->RandSeed_hc1z[iU_3]);
  }

  /* End of InitializeConditions for RandomNumber: '<S354>/Random Number' */

  /* InitializeConditions for DiscreteFir: '<S352>/Discrete FIR Filter' */
  for (i = 0; i < 3; i = i + 1) {
    localDW->DiscreteFIRFilter_states[i] = 0.0;
  }

  /* End of InitializeConditions for DiscreteFir: '<S352>/Discrete FIR Filter' */

  /* InitializeConditions for RandomNumber: '<S352>/Random Number' */
  for (iU_4 = 0; iU_4 < 3; iU_4 = iU_4 + 1) {
    tseed_4 = (uint32_T)rtCP_RandomNumber_Seed_f55z[iU_4];
    r_4 = tseed_4 >> 16U;
    t_4 = tseed_4 & 32768U;
    n6V_4 = (((tseed_4 - ((r_4 << 16U) - t_4)) << 16U) + t_4) + r_4;
    if (n6V_4 < 1U) {
      n6V_4 = 1144108930U;
    } else if (n6V_4 > 2147483646U) {
      n6V_4 = 2147483646U;
    }

    localDW->RandSeed_c3st[iU_4] = n6V_4;
    localDW->NextOutput_h3vk[iU_4] = rt_nrand_Upu32_Yd_f_pw_snf
      (&localDW->RandSeed_c3st[iU_4]) * rtCP_RandomNumber_StdDev_azwi[iU_4];
  }

  /* End of InitializeConditions for RandomNumber: '<S352>/Random Number' */

  /* InitializeConditions for RandomNumber: '<S342>/Random Number1' */
  for (iU_5 = 0; iU_5 < 3; iU_5 = iU_5 + 1) {
    tseed_5 = (uint32_T)rtCP_RandomNumber1_Seed[iU_5];
    r_5 = tseed_5 >> 16U;
    t_5 = tseed_5 & 32768U;
    n6V_5 = (((tseed_5 - ((r_5 << 16U) - t_5)) << 16U) + t_5) + r_5;
    if (n6V_5 < 1U) {
      n6V_5 = 1144108930U;
    } else if (n6V_5 > 2147483646U) {
      n6V_5 = 2147483646U;
    }

    localDW->RandSeed_adgi[iU_5] = n6V_5;
    localDW->NextOutput_kg2s[iU_5] = rt_nrand_Upu32_Yd_f_pw_snf
      (&localDW->RandSeed_adgi[iU_5]) * rtCP_RandomNumber1_StdDev[iU_5];
  }

  /* End of InitializeConditions for RandomNumber: '<S342>/Random Number1' */

  /* InitializeConditions for Integrator: '<S15>/pos_x' incorporates:
   *  Integrator: '<S16>/pos_y'
   */
  if (rtmIsFirstInitCond(RMT_FDM_RT_M)) {
    localX->x_R_O_m = 0.0;
    localX->y_R_O_m = 0.0;
  }

  localDW->pos_x_DWORK1 = true;

  /* End of InitializeConditions for Integrator: '<S15>/pos_x' */

  /* InitializeConditions for Integrator: '<S16>/pos_y' */
  localDW->pos_y_DWORK1 = true;

  /* InitializeConditions for DiscreteFir: '<S350>/Discrete FIR Filter' */
  for (i_0 = 0; i_0 < 3; i_0 = i_0 + 1) {
    localDW->DiscreteFIRFilter_states_jj3r[i_0] = 0.0;
  }

  /* End of InitializeConditions for DiscreteFir: '<S350>/Discrete FIR Filter' */

  /* InitializeConditions for DiscreteFir: '<S349>/Discrete FIR Filter' */
  for (i_1 = 0; i_1 < 3; i_1 = i_1 + 1) {
    localDW->DiscreteFIRFilter_states_m0pu[i_1] = 0.0;
  }

  /* End of InitializeConditions for DiscreteFir: '<S349>/Discrete FIR Filter' */

  /* InitializeConditions for RandomNumber: '<S317>/Random Number2' */
  for (iU_6 = 0; iU_6 < 3; iU_6 = iU_6 + 1) {
    tseed_6 = (uint32_T)rtCP_RandomNumber2_Seed_l1ri[iU_6];
    r_6 = tseed_6 >> 16U;
    t_6 = tseed_6 & 32768U;
    n6V_6 = (((tseed_6 - ((r_6 << 16U) - t_6)) << 16U) + t_6) + r_6;
    if (n6V_6 < 1U) {
      n6V_6 = 1144108930U;
    } else if (n6V_6 > 2147483646U) {
      n6V_6 = 2147483646U;
    }

    localDW->RandSeed_bfrf[iU_6] = n6V_6;
    localDW->NextOutput_d0v2[iU_6] = rt_nrand_Upu32_Yd_f_pw_snf
      (&localDW->RandSeed_bfrf[iU_6]);
  }

  /* End of InitializeConditions for RandomNumber: '<S317>/Random Number2' */

  /* InitializeConditions for RandomNumber: '<S315>/Random Number2' */
  for (iU_7 = 0; iU_7 < 3; iU_7 = iU_7 + 1) {
    tseed_7 = (uint32_T)rtCP_RandomNumber2_Seed_kn3y[iU_7];
    r_7 = tseed_7 >> 16U;
    t_7 = tseed_7 & 32768U;
    n6V_7 = (((tseed_7 - ((r_7 << 16U) - t_7)) << 16U) + t_7) + r_7;
    if (n6V_7 < 1U) {
      n6V_7 = 1144108930U;
    } else if (n6V_7 > 2147483646U) {
      n6V_7 = 2147483646U;
    }

    localDW->RandSeed_hwhk[iU_7] = n6V_7;
    localDW->NextOutput_oxco[iU_7] = rt_nrand_Upu32_Yd_f_pw_snf
      (&localDW->RandSeed_hwhk[iU_7]);
  }

  /* End of InitializeConditions for RandomNumber: '<S315>/Random Number2' */

  /* InitializeConditions for RandomNumber: '<S243>/Random Number2' */
  for (iU_8 = 0; iU_8 < 3; iU_8 = iU_8 + 1) {
    tseed_8 = (uint32_T)rtCP_RandomNumber2_Seed_f0v3[iU_8];
    r_8 = tseed_8 >> 16U;
    t_8 = tseed_8 & 32768U;
    n6V_8 = (((tseed_8 - ((r_8 << 16U) - t_8)) << 16U) + t_8) + r_8;
    if (n6V_8 < 1U) {
      n6V_8 = 1144108930U;
    } else if (n6V_8 > 2147483646U) {
      n6V_8 = 2147483646U;
    }

    localDW->RandSeed_cfee[iU_8] = n6V_8;
    localDW->NextOutput_myry[iU_8] = rt_nrand_Upu32_Yd_f_pw_snf
      (&localDW->RandSeed_cfee[iU_8]);
  }

  /* End of InitializeConditions for RandomNumber: '<S243>/Random Number2' */

  /* InitializeConditions for RandomNumber: '<S244>/Random Number2' */
  for (iU_9 = 0; iU_9 < 3; iU_9 = iU_9 + 1) {
    tseed_9 = (uint32_T)rtCP_RandomNumber2_Seed_d0me[iU_9];
    r_9 = tseed_9 >> 16U;
    t_9 = tseed_9 & 32768U;
    n6V_9 = (((tseed_9 - ((r_9 << 16U) - t_9)) << 16U) + t_9) + r_9;
    if (n6V_9 < 1U) {
      n6V_9 = 1144108930U;
    } else if (n6V_9 > 2147483646U) {
      n6V_9 = 2147483646U;
    }

    localDW->RandSeed_dfqp[iU_9] = n6V_9;
    localDW->NextOutput_psbc[iU_9] = rt_nrand_Upu32_Yd_f_pw_snf
      (&localDW->RandSeed_dfqp[iU_9]);
  }

  /* End of InitializeConditions for RandomNumber: '<S244>/Random Number2' */

  /* InitializeConditions for RandomNumber: '<S245>/Random Number2' */
  for (iU_a = 0; iU_a < 3; iU_a = iU_a + 1) {
    tseed_a = (uint32_T)rtCP_RandomNumber2_Seed_bhlk[iU_a];
    r_a = tseed_a >> 16U;
    t_a = tseed_a & 32768U;
    n6V_a = (((tseed_a - ((r_a << 16U) - t_a)) << 16U) + t_a) + r_a;
    if (n6V_a < 1U) {
      n6V_a = 1144108930U;
    } else if (n6V_a > 2147483646U) {
      n6V_a = 2147483646U;
    }

    localDW->RandSeed_hhkq[iU_a] = n6V_a;
    localDW->NextOutput_ps3h[iU_a] = rt_nrand_Upu32_Yd_f_pw_snf
      (&localDW->RandSeed_hhkq[iU_a]);
  }

  /* End of InitializeConditions for RandomNumber: '<S245>/Random Number2' */

  /* InitializeConditions for RandomNumber: '<S246>/Random Number2' */
  for (iU_b = 0; iU_b < 3; iU_b = iU_b + 1) {
    tseed_b = (uint32_T)rtCP_RandomNumber2_Seed_mev2[iU_b];
    r_b = tseed_b >> 16U;
    t_b = tseed_b & 32768U;
    n6V_b = (((tseed_b - ((r_b << 16U) - t_b)) << 16U) + t_b) + r_b;
    if (n6V_b < 1U) {
      n6V_b = 1144108930U;
    } else if (n6V_b > 2147483646U) {
      n6V_b = 2147483646U;
    }

    localDW->RandSeed_i5sw[iU_b] = n6V_b;
    localDW->NextOutput_ivlt[iU_b] = rt_nrand_Upu32_Yd_f_pw_snf
      (&localDW->RandSeed_i5sw[iU_b]);
  }

  /* End of InitializeConditions for RandomNumber: '<S246>/Random Number2' */

  /* InitializeConditions for RandomNumber: '<S247>/Random Number2' */
  for (iU_c = 0; iU_c < 3; iU_c = iU_c + 1) {
    tseed_c = (uint32_T)rtCP_RandomNumber2_Seed_mns2[iU_c];
    r_c = tseed_c >> 16U;
    t_c = tseed_c & 32768U;
    n6V_c = (((tseed_c - ((r_c << 16U) - t_c)) << 16U) + t_c) + r_c;
    if (n6V_c < 1U) {
      n6V_c = 1144108930U;
    } else if (n6V_c > 2147483646U) {
      n6V_c = 2147483646U;
    }

    localDW->RandSeed_bmmn[iU_c] = n6V_c;
    localDW->NextOutput_hejj[iU_c] = rt_nrand_Upu32_Yd_f_pw_snf
      (&localDW->RandSeed_bmmn[iU_c]);
  }

  /* End of InitializeConditions for RandomNumber: '<S247>/Random Number2' */

  /* InitializeConditions for RandomNumber: '<S248>/Random Number2' */
  for (iU_d = 0; iU_d < 3; iU_d = iU_d + 1) {
    tseed_d = (uint32_T)rtCP_RandomNumber2_Seed_oc5t[iU_d];
    r_d = tseed_d >> 16U;
    t_d = tseed_d & 32768U;
    n6V_d = (((tseed_d - ((r_d << 16U) - t_d)) << 16U) + t_d) + r_d;
    if (n6V_d < 1U) {
      n6V_d = 1144108930U;
    } else if (n6V_d > 2147483646U) {
      n6V_d = 2147483646U;
    }

    localDW->RandSeed_gbxp[iU_d] = n6V_d;
    localDW->NextOutput_nqkk[iU_d] = rt_nrand_Upu32_Yd_f_pw_snf
      (&localDW->RandSeed_gbxp[iU_d]);
  }

  /* End of InitializeConditions for RandomNumber: '<S248>/Random Number2' */

  /* InitializeConditions for RandomNumber: '<S249>/Random Number2' */
  for (iU_e = 0; iU_e < 3; iU_e = iU_e + 1) {
    tseed_e = (uint32_T)rtCP_RandomNumber2_Seed_kkhk[iU_e];
    r_e = tseed_e >> 16U;
    t_e = tseed_e & 32768U;
    n6V_e = (((tseed_e - ((r_e << 16U) - t_e)) << 16U) + t_e) + r_e;
    if (n6V_e < 1U) {
      n6V_e = 1144108930U;
    } else if (n6V_e > 2147483646U) {
      n6V_e = 2147483646U;
    }

    localDW->RandSeed_h5zc[iU_e] = n6V_e;
    localDW->NextOutput_op4z[iU_e] = rt_nrand_Upu32_Yd_f_pw_snf
      (&localDW->RandSeed_h5zc[iU_e]);
  }

  /* End of InitializeConditions for RandomNumber: '<S249>/Random Number2' */

  /* InitializeConditions for RandomNumber: '<S250>/Random Number2' */
  for (iU_f = 0; iU_f < 3; iU_f = iU_f + 1) {
    tseed_f = (uint32_T)rtCP_RandomNumber2_Seed_li24[iU_f];
    r_f = tseed_f >> 16U;
    t_f = tseed_f & 32768U;
    n6V_f = (((tseed_f - ((r_f << 16U) - t_f)) << 16U) + t_f) + r_f;
    if (n6V_f < 1U) {
      n6V_f = 1144108930U;
    } else if (n6V_f > 2147483646U) {
      n6V_f = 2147483646U;
    }

    localDW->RandSeed_lduk[iU_f] = n6V_f;
    localDW->NextOutput_ejvr[iU_f] = rt_nrand_Upu32_Yd_f_pw_snf
      (&localDW->RandSeed_lduk[iU_f]);
  }

  /* End of InitializeConditions for RandomNumber: '<S250>/Random Number2' */

  /* InitializeConditions for RandomNumber: '<S390>/Random Number2' */
  for (iU_g = 0; iU_g < 3; iU_g = iU_g + 1) {
    tseed_g = (uint32_T)rtCP_RandomNumber2_Seed_oqyr[iU_g];
    r_g = tseed_g >> 16U;
    t_g = tseed_g & 32768U;
    n6V_g = (((tseed_g - ((r_g << 16U) - t_g)) << 16U) + t_g) + r_g;
    if (n6V_g < 1U) {
      n6V_g = 1144108930U;
    } else if (n6V_g > 2147483646U) {
      n6V_g = 2147483646U;
    }

    localDW->RandSeed_pu2v[iU_g] = n6V_g;
    localDW->NextOutput_klkk[iU_g] = rt_nrand_Upu32_Yd_f_pw_snf
      (&localDW->RandSeed_pu2v[iU_g]);
  }

  /* End of InitializeConditions for RandomNumber: '<S390>/Random Number2' */

  /* InitializeConditions for Integrator: '<S333>/w_z_int_PRot_P_err_radDs' incorporates:
   *  Integrator: '<S257>/w_z_int_PRot_P_err_radDs'
   *  Integrator: '<S258>/w_z_int_PRot_P_err_radDs'
   *  Integrator: '<S265>/w_z_int_PRot_P_err_radDs'
   *  Integrator: '<S266>/w_z_int_PRot_P_err_radDs'
   *  Integrator: '<S273>/w_z_int_PRot_P_err_radDs'
   *  Integrator: '<S274>/w_z_int_PRot_P_err_radDs'
   *  Integrator: '<S281>/w_z_int_PRot_P_err_radDs'
   *  Integrator: '<S282>/w_z_int_PRot_P_err_radDs'
   *  Integrator: '<S289>/w_z_int_PRot_P_err_radDs'
   *  Integrator: '<S290>/w_z_int_PRot_P_err_radDs'
   *  Integrator: '<S297>/w_z_int_PRot_P_err_radDs'
   *  Integrator: '<S298>/w_z_int_PRot_P_err_radDs'
   *  Integrator: '<S305>/w_z_int_PRot_P_err_radDs'
   *  Integrator: '<S306>/w_z_int_PRot_P_err_radDs'
   *  Integrator: '<S313>/w_z_int_PRot_P_err_radDs'
   *  Integrator: '<S314>/w_z_int_PRot_P_err_radDs'
   *  Integrator: '<S324>/w_z_int_PRot_P_err_radDs'
   *  Integrator: '<S325>/w_z_int_PRot_P_err_radDs'
   *  Integrator: '<S332>/w_z_int_PRot_P_err_radDs'
   *  Integrator: '<S340>/w_z_int_PRot_P_err_radDs'
   *  Integrator: '<S341>/w_z_int_PRot_P_err_radDs'
   *  Integrator: '<S397>/w_z_int_PRot_P_err_radDs'
   *  Integrator: '<S398>/w_z_int_PRot_P_err_radDs'
   */
  if (rtmIsFirstInitCond(RMT_FDM_RT_M)) {
    localX->w_z_int_PRot_P_err_radDs_cg5d = 0.0;
    localX->w_z_int_PRot_P_err_radDs_dftl = 0.0;
    localX->w_z_int_PRot_P_err_radDs_jowp = 0.0;
    localX->w_z_int_PRot_P_err_radDs_baxu = 0.0;
    localX->w_z_int_PRot_P_err_radDs_cjc1 = 0.0;
    localX->w_z_int_PRot_P_err_radDs_aexu = 0.0;
    localX->w_z_int_PRot_P_err_radDs_njv5 = 0.0;
    localX->w_z_int_PRot_P_err_radDs_adwj = 0.0;
    localX->w_z_int_PRot_P_err_radDs_l00j = 0.0;
    localX->w_z_int_PRot_P_err_radDs_ir34 = 0.0;
    localX->w_z_int_PRot_P_err_radDs_kbfn = 0.0;
    localX->w_z_int_PRot_P_err_radDs_oqys = 0.0;
    localX->w_z_int_PRot_P_err_radDs_fldy = 0.0;
    localX->w_z_int_PRot_P_err_radDs_czdk = 0.0;
    localX->w_z_int_PRot_P_err_radDs_pct4 = 0.0;
    localX->w_z_int_PRot_P_err_radDs_oaeq = 0.0;
    localX->w_z_int_PRot_P_err_radDs_nhxo = 0.0;
    localX->w_z_int_PRot_P_err_radDs_l5ua = 0.0;
    localX->w_z_int_PRot_P_err_radDs_c3cm = 0.0;
    localX->w_z_int_PRot_P_err_radDs_j2wc = 0.0;
    localX->w_z_int_PRot_P_err_radDs_puds = 0.0;
    localX->w_z_int_PRot_P_err_radDs_ons5 = 0.0;
    localX->w_z_int_PRot_P_err_radDs_a2pk = 0.0;
    localX->w_z_int_PRot_P_err_radDs_mh2t = 0.0;
  }

  localDW->w_z_int_PRot_P_err_radDs_DWORK1_mvtc = true;

  /* End of InitializeConditions for Integrator: '<S333>/w_z_int_PRot_P_err_radDs' */

  /* InitializeConditions for Integrator: '<S341>/w_z_int_PRot_P_err_radDs' */
  localDW->w_z_int_PRot_P_err_radDs_DWORK1_ik1k = true;

  /* InitializeConditions for Integrator: '<S325>/w_z_int_PRot_P_err_radDs' */
  localDW->w_z_int_PRot_P_err_radDs_DWORK1_bsyt = true;

  /* InitializeConditions for Integrator: '<S258>/w_z_int_PRot_P_err_radDs' */
  localDW->w_z_int_PRot_P_err_radDs_DWORK1_f02p = true;

  /* InitializeConditions for Integrator: '<S266>/w_z_int_PRot_P_err_radDs' */
  localDW->w_z_int_PRot_P_err_radDs_DWORK1_nx4h = true;

  /* InitializeConditions for Integrator: '<S274>/w_z_int_PRot_P_err_radDs' */
  localDW->w_z_int_PRot_P_err_radDs_DWORK1_jzmo = true;

  /* InitializeConditions for Integrator: '<S282>/w_z_int_PRot_P_err_radDs' */
  localDW->w_z_int_PRot_P_err_radDs_DWORK1_avwp = true;

  /* InitializeConditions for Integrator: '<S290>/w_z_int_PRot_P_err_radDs' */
  localDW->w_z_int_PRot_P_err_radDs_DWORK1_disd = true;

  /* InitializeConditions for Integrator: '<S298>/w_z_int_PRot_P_err_radDs' */
  localDW->w_z_int_PRot_P_err_radDs_DWORK1_dcuw = true;

  /* InitializeConditions for Integrator: '<S306>/w_z_int_PRot_P_err_radDs' */
  localDW->w_z_int_PRot_P_err_radDs_DWORK1_fmga = true;

  /* InitializeConditions for Integrator: '<S314>/w_z_int_PRot_P_err_radDs' */
  localDW->w_z_int_PRot_P_err_radDs_DWORK1_ncdx = true;

  /* InitializeConditions for Integrator: '<S398>/w_z_int_PRot_P_err_radDs' */
  localDW->w_z_int_PRot_P_err_radDs_DWORK1_itla = true;

  /* InitializeConditions for Integrator: '<S397>/w_z_int_PRot_P_err_radDs' */
  localDW->w_z_int_PRot_P_err_radDs_DWORK1_psoo = true;

  /* InitializeConditions for Integrator: '<S313>/w_z_int_PRot_P_err_radDs' */
  localDW->w_z_int_PRot_P_err_radDs_DWORK1_f3vl = true;

  /* InitializeConditions for Integrator: '<S305>/w_z_int_PRot_P_err_radDs' */
  localDW->w_z_int_PRot_P_err_radDs_DWORK1_iirx = true;

  /* InitializeConditions for Integrator: '<S297>/w_z_int_PRot_P_err_radDs' */
  localDW->w_z_int_PRot_P_err_radDs_DWORK1_caav = true;

  /* InitializeConditions for Integrator: '<S289>/w_z_int_PRot_P_err_radDs' */
  localDW->w_z_int_PRot_P_err_radDs_DWORK1_cogt = true;

  /* InitializeConditions for Integrator: '<S281>/w_z_int_PRot_P_err_radDs' */
  localDW->w_z_int_PRot_P_err_radDs_DWORK1_jhud = true;

  /* InitializeConditions for Integrator: '<S273>/w_z_int_PRot_P_err_radDs' */
  localDW->w_z_int_PRot_P_err_radDs_DWORK1_no0f = true;

  /* InitializeConditions for Integrator: '<S265>/w_z_int_PRot_P_err_radDs' */
  localDW->w_z_int_PRot_P_err_radDs_DWORK1_da4c = true;

  /* InitializeConditions for Integrator: '<S257>/w_z_int_PRot_P_err_radDs' */
  localDW->w_z_int_PRot_P_err_radDs_DWORK1_does = true;

  /* InitializeConditions for Integrator: '<S324>/w_z_int_PRot_P_err_radDs' */
  localDW->w_z_int_PRot_P_err_radDs_DWORK1_mmow = true;

  /* InitializeConditions for Integrator: '<S340>/w_z_int_PRot_P_err_radDs' */
  localDW->w_z_int_PRot_P_err_radDs_DWORK1_hg1y = true;

  /* InitializeConditions for Integrator: '<S332>/w_z_int_PRot_P_err_radDs' */
  localDW->w_z_int_PRot_P_err_radDs_DWORK1_plxf = true;

  /* SystemInitialize for Iterator SubSystem: '<S1>/Actuator_Ext_Reset' */
  for (ForEach_itr_gq2o = 0; ForEach_itr_gq2o < 8; ForEach_itr_gq2o =
       ForEach_itr_gq2o + 1) {
    /* SystemInitialize for Gain: '<S5>/Gain' */
    localB->CoreSubsys[ForEach_itr_gq2o].w_act_dot_radDs2 = 0.0;

    /* InitializeConditions for Integrator: '<S5>/Integrator' */
    if (rtmIsFirstInitCond(RMT_FDM_RT_M)) {
      localX->CoreSubsys[ForEach_itr_gq2o].w_act_radDs = 0.0;
    }

    localDW->CoreSubsys[ForEach_itr_gq2o].Integrator_DWORK1 = true;

    /* End of InitializeConditions for Integrator: '<S5>/Integrator' */
    localZCE->CoreSubsys[ForEach_itr_gq2o].Integrator_Reset_ZCE =
      UNINITIALIZED_ZCSIG;
  }

  /* End of SystemInitialize for SubSystem: '<S1>/Actuator_Ext_Reset' */

  /* SystemInitialize for Iterator SubSystem: '<S33>/Propeller_RMT' */
  for (ForEach_itr = 0; ForEach_itr < 8; ForEach_itr = ForEach_itr + 1) {
    /* SystemInitialize for Product: '<S129>/Product1' */
    for (i_2 = 0; i_2 < 3; i_2 = i_2 + 1) {
      localB->CoreSubsys_pnae[ForEach_itr].Product1[i_2] = 0.0;
    }

    /* End of SystemInitialize for Product: '<S129>/Product1' */

    /* SystemInitialize for Math: '<S140>/Math Function' */
    localB->CoreSubsys_pnae[ForEach_itr].MathFunction = 0.0;

    /* SystemInitialize for SignalConversion: '<S113>/Signal Conversion3' */
    for (i_3 = 0; i_3 < 3; i_3 = i_3 + 1) {
      localB->CoreSubsys_pnae[ForEach_itr].SignalConversion3[i_3] = 0.0;
    }

    /* End of SystemInitialize for SignalConversion: '<S113>/Signal Conversion3' */

    /* SystemInitialize for Math: '<S160>/Math Function' */
    localB->CoreSubsys_pnae[ForEach_itr].MathFunction_dslh = 0.0;
  }

  /* End of SystemInitialize for SubSystem: '<S33>/Propeller_RMT' */
}

/* Disable for referenced model: 'RMT_FDM_RT' */
void RMT_FDM_RT_Disable(B_RMT_FDM_RT_caua_T *localB, DW_RMT_FDM_RT_fwu4_T
  *localDW)
{
  int32_T i;
  int32_T i_0;

  /* Disable for DiscreteIntegrator: '<S354>/Discrete-Time Integrator2' */
  for (i = 0; i < 3; i = i + 1) {
    localDW->DiscreteTimeIntegrator2_DSTATE[i] = localB->
      DiscreteTimeIntegrator2[i];
  }

  /* End of Disable for DiscreteIntegrator: '<S354>/Discrete-Time Integrator2' */

  /* Disable for DiscreteIntegrator: '<S345>/Discrete-Time Integrator' */
  for (i_0 = 0; i_0 < 3; i_0 = i_0 + 1) {
    localDW->DiscreteTimeIntegrator_DSTATE[i_0] = localB->
      DiscreteTimeIntegrator[i_0];
  }

  /* End of Disable for DiscreteIntegrator: '<S345>/Discrete-Time Integrator' */
}

/* Outputs for referenced model: 'RMT_FDM_RT' */
void RMT_FDM_RT(RT_MODEL_RMT_FDM_RT_T * const RMT_FDM_RT_M, const
                Simulation_Control_Bus *rtu_Simulation_Control, const real_T
                *rtu_External_Inputs_Navigation_Frame_psi_0_rad, const real_T
                *rtu_External_Inputs_Wind_Data_rot_W_OW_B_radDs_w_x_W_OW_B_radDs,
                const real_T
                *rtu_External_Inputs_Wind_Data_rot_W_OW_B_radDs_w_y_W_OW_B_radDs,
                const real_T
                *rtu_External_Inputs_Wind_Data_rot_W_OW_B_radDs_w_z_W_OW_B_radDs,
                const real_T
                *rtu_External_Inputs_Wind_Data_vel_W_R_E_O_mDs_u_W_R_E_O_mDs,
                const real_T
                *rtu_External_Inputs_Wind_Data_vel_W_R_E_O_mDs_v_W_R_E_O_mDs,
                const real_T
                *rtu_External_Inputs_Wind_Data_vel_W_R_E_O_mDs_w_W_R_E_O_mDs,
                const States_Init_Bus *rtu_States_Init, const Failure_Bus
                *rtu_Failures, const Controller_Commands_Bus
                *rtu_Controller_Commands, Vehicle_Bus *rty_Vehicle,
                Measurements_Bus *rty_Measurements, B_RMT_FDM_RT_caua_T *localB,
                DW_RMT_FDM_RT_fwu4_T *localDW, X_RMT_FDM_RT_nymf_T *localX,
                ZCE_RMT_FDM_RT_T *localZCE)
{
  /* local scratch DWork variables */
  int32_T ForEach_itr;
  int32_T ForEach_itr_gq2o;
  Atmosphere_Bus b_Atmosphere;
  Outputs_Bus b_Outputs;
  real_T b_ImpAsg_InsertedFor_for_P_R_B_N_at_inport_0[24];
  real_T b_ImpAsg_InsertedFor_mom_P_R_B_Nm_at_inport_0[24];
  real_T b_M_AB[9];
  real_T b_M_AO[9];
  real_T b_M_BO[9];
  real_T b_M_OB_h14v_tmp[9];
  real_T b_M_OB_k2bs[9];
  real_T b_M_SB[9];
  real_T b_MathFunction_avjt[9];
  real_T b_MathFunction_cbg2[9];
  real_T b_MathFunction_dsxx[9];
  real_T b_MathFunction_g133[9];
  real_T b_MatrixConcaenate[9];
  real_T b_MatrixConcaenate_a1h4[9];
  real_T b_MatrixConcatenate[9];
  real_T b_Product10_pps0[9];
  real_T b_Product1_ehnp[9];
  real_T b_Product1_j1ks[9];
  real_T b_Product1_n5kc[9];
  real_T b_Product1_ovxb[9];
  real_T b_Product_epes[9];
  real_T b_Reshape3_evca[9];
  real_T b_VectorConcatenate_dkiq[9];
  real_T b_VectorConcatenate_dkiq_0[9];
  real_T b_VectorConcatenate_g5kk[9];
  real_T b_VectorConcatenate_gmvx[9];
  real_T b_VectorConcatenate_hkqf[9];
  real_T b_VectorConcatenate_iewf[9];
  real_T b_VectorConcatenate_iewf_0[9];
  real_T b_VectorConcatenate_jnc0[9];
  real_T b_VectorConcatenate_jnc0_0[9];
  real_T b_VectorConcatenate_kj0i[9];
  real_T b_VectorConcatenate_kksp[9];
  real_T b_VectorConcatenate_ko43[9];
  real_T b_VectorConcatenate_kzox[9];
  real_T b_VectorConcatenate_nziv[9];
  real_T b_VectorConcatenate_ptbz[9];
  real_T b_vel_K_R_E_O_mDs_1[9];
  real_T b_vel_K_R_E_O_mDs_2[9];
  real_T tmp_4[9];
  real_T tmp_5[9];
  real_T tmp_6[9];
  real_T tmp_d[9];
  real_T tmp_e[9];
  real_T b_ImpAsg_InsertedFor_w_act_radDs_at_inport_0[8];
  real_T b_Elementproduct[6];
  real_T b_Elementproduct_fjwd[6];
  real_T b_Elementproduct_otn3[6];
  real_T b_Assignment[3];
  real_T b_Assignment_boes[3];
  real_T b_Assignment_ia0s[3];
  real_T b_Assignment_kod3[3];
  real_T b_Divide_bizu[3];
  real_T b_M_BO_0[3];
  real_T b_M_OB_h14v_tmp_0[3];
  real_T b_M_OB_h14v_tmp_1[3];
  real_T b_M_OB_h14v_tmp_2[3];
  real_T b_M_OB_h14v_tmp_3[3];
  real_T b_M_OB_h14v_tmp_4[3];
  real_T b_MathFunction_do5x[3];
  real_T b_Product1_av01[3];
  real_T b_Product1_lodv[3];
  real_T b_Product2_fd4p[3];
  real_T b_Product_aer5[3];
  real_T b_Product_dmg0[3];
  real_T b_Product_fmjd[3];
  real_T b_Product_jx5y[3];
  real_T b_Product_kgt5[3];
  real_T b_Product_n2sg[3];
  real_T b_RandomNumber2[3];
  real_T b_RandomNumber2_b4yr[3];
  real_T b_RandomNumber2_dn0u[3];
  real_T b_RandomNumber2_e2nc[3];
  real_T b_RandomNumber2_gjti[3];
  real_T b_RandomNumber2_k5jx[3];
  real_T b_RandomNumber2_lwaa[3];
  real_T b_RandomNumber2_mjrt[3];
  real_T b_RandomNumber2_muso[3];
  real_T b_RandomNumber2_nzfy[3];
  real_T b_RandomNumber2_ouvm[3];
  real_T b_RandomNumber2_p3bk[3];
  real_T b_Reshape[3];
  real_T b_Reshape1_ejex[3];
  real_T b_Reshape1_hoha[3];
  real_T b_Reshape1_lt4a[3];
  real_T b_Reshape2_jvfy[3];
  real_T b_Reshape2_ksra[3];
  real_T b_Reshape2_o51o[3];
  real_T b_Reshape3_czqe[3];
  real_T b_Reshape8[3];
  real_T b_Reshape8_0[3];
  real_T b_Reshape_aw0z[3];
  real_T b_Reshape_axns[3];
  real_T b_Reshape_j045[3];
  real_T b_Reshape_j1uf[3];
  real_T b_Reshape_jgsm[3];
  real_T b_Reshape_kl1z[3];
  real_T b_SignalConversion1_prrf[3];
  real_T b_SignalConversion_hgu0[3];
  real_T b_Subtract_kaxz[3];
  real_T b_Sum1_pk2u[3];
  real_T b_Sum2[3];
  real_T b_Sum2_jdsh[3];
  real_T b_Sum3[3];
  real_T b_Sum5_hbb1[3];
  real_T b_Sum_avzm[3];
  real_T b_Sum_hhfg[3];
  real_T b_Sum_jgmu[3];
  real_T b_Switch[3];
  real_T b_Switch_dxts[3];
  real_T b_Switch_jgoc[3];
  real_T b_Switch_jlc4[3];
  real_T b_Switch_jzso[3];
  real_T b_Switch_kohd[3];
  real_T b_Vector[3];
  real_T b_VectorConcatenate[3];
  real_T b_VectorConcatenate1[3];
  real_T b_VectorConcatenate1_ahwu[3];
  real_T b_VectorConcatenate1_dfc3[3];
  real_T b_VectorConcatenate1_eeyd[3];
  real_T b_VectorConcatenate1_fkvx[3];
  real_T b_VectorConcatenate1_hfce[3];
  real_T b_VectorConcatenate1_idvm[3];
  real_T b_VectorConcatenate1_llo0[3];
  real_T b_VectorConcatenate1_nxhe[3];
  real_T b_VectorConcatenate1_nze2[3];
  real_T b_VectorConcatenate2[3];
  real_T b_VectorConcatenate2_a0rr[3];
  real_T b_VectorConcatenate2_akq5[3];
  real_T b_VectorConcatenate2_b5g4[3];
  real_T b_VectorConcatenate2_bxrn[3];
  real_T b_VectorConcatenate2_eoub[3];
  real_T b_VectorConcatenate2_pfo0[3];
  real_T b_VectorConcatenate_6[3];
  real_T b_VectorConcatenate_amwl[3];
  real_T b_VectorConcatenate_arer[3];
  real_T b_VectorConcatenate_bt3y[3];
  real_T b_VectorConcatenate_cl4h[3];
  real_T b_VectorConcatenate_eeyb[3];
  real_T b_VectorConcatenate_emun[3];
  real_T b_VectorConcatenate_gaq1[3];
  real_T b_VectorConcatenate_h5xj[3];
  real_T b_VectorConcatenate_id0h[3];
  real_T b_VectorConcatenate_iiv2[3];
  real_T b_VectorConcatenate_keeq[3];
  real_T b_VectorConcatenate_kksp_0[3];
  real_T b_VectorConcatenate_ko43_0[3];
  real_T b_VectorConcatenate_kudp[3];
  real_T b_VectorConcatenate_l4yq[3];
  real_T b_VectorConcatenate_lpik[3];
  real_T b_VectorConcatenate_nhrs[3];
  real_T b_VectorConcatenate_noxd[3];
  real_T b_VectorConcatenate_nsr3[3];
  real_T b_VectorConcatenate_oawp[3];
  real_T b_VectorConcatenate_oque[3];
  real_T b_Vector_7[3];
  real_T b_Vector_buas[3];
  real_T b_Vector_bxq5[3];
  real_T b_Vector_e4oo[3];
  real_T b_Vector_ebga[3];
  real_T b_Vector_eeei[3];
  real_T b_Vector_fnf0[3];
  real_T b_Vector_hnym[3];
  real_T b_Vector_iguf[3];
  real_T b_Vector_lrwf[3];
  real_T b_Vector_m0fx[3];
  real_T b_Vector_pbcv[3];
  real_T b_Vector_pgif[3];
  real_T b_for_G_R_B_N_aifj[3];
  real_T b_for_G_R_B_N_ksmv_tmp[3];
  real_T b_mom_T_R_B_Nm_fyeb[3];
  real_T b_u2_oitx[3];
  real_T b_vel_K_R_E_O_mDs[3];
  real_T b_vel_K_R_E_O_mDs_m1dj[3];
  real_T tmp_9[3];
  real_T tmp_a[3];
  real_T tmp_b[3];
  real_T tmp_c[3];
  real_T tmp_f[3];
  real_T tmp_g[3];
  real_T tmp_h[3];
  real_T b_MathFunction[2];
  real_T b_VectorConcatenate2_ofdc[2];
  real_T Product_hwmn_tmp;
  real_T Product_mmjp_tmp;
  real_T Product_p0uf_tmp;
  real_T acc1;
  real_T acc1_0;
  real_T acc1_1;
  real_T b_Add_cf0u;
  real_T b_Add_ch30_tmp;
  real_T b_DataTypeConversion;
  real_T b_Divide1_igly;
  real_T b_N;
  real_T b_Product;
  real_T b_Product2_b3um;
  real_T b_Product2_mkuz_tmp;
  real_T b_Product3;
  real_T b_Sum1_hc1q;
  real_T b_Switch_gxqx;
  real_T b_Switch_iuqm;
  real_T b_Theta_rad;
  real_T b_TrigonometricFunction1_g1qe;
  real_T b_TrigonometricFunction1_g4q5;
  real_T b_TrigonometricFunction1_ihsx;
  real_T b_TrigonometricFunction1_kiq3;
  real_T b_TrigonometricFunction1_pesf_tmp;
  real_T b_TrigonometricFunction7_n3ob;
  real_T b_TrigonometricFunction_fw5d;
  real_T b_TrigonometricFunction_lzfd;
  real_T b_TrigonometricFunction_n3xf;
  real_T b_Vector_ipfw_tmp;
  real_T b_Vector_mdpm_tmp;
  real_T b_Vector_nadq_tmp;
  real_T b_Vector_nadq_tmp_0;
  real_T b_rho_kgDm3;
  real_T b_squarey_tmp;
  real_T b_squarey_tmp_0;
  real_T b_squarez;
  real_T b_squarez_tmp;
  real_T b_u_K_R_E_B_mDs_tmp;
  real_T b_u_K_R_E_B_mDs_tmp_0;
  real_T b_v_K_R_E_B_mDs;
  real_T b_v_K_R_E_B_mDs_tmp;
  real_T b_w_x_K_IB_B_radDs;
  real_T b_w_x_K_IB_B_radDs_tmp;
  real_T b_w_x_K_IB_B_radDs_tmp_0;
  real_T b_w_x_K_OB_B_radDs;
  real_T b_w_x_K_OB_B_radDs_tmp;
  real_T b_w_y_K_IB_B_radDs;
  real_T b_w_y_K_IB_B_radDs_tmp;
  real_T b_w_z_int_PRot_P_err_radDs_alwh;
  real_T tmp;
  real_T tmp_0;
  real_T tmp_1;
  real_T tmp_10;
  real_T tmp_11;
  real_T tmp_12;
  real_T tmp_13;
  real_T tmp_14;
  real_T tmp_15;
  real_T tmp_2;
  real_T tmp_3;
  real_T tmp_7;
  real_T tmp_8;
  real_T tmp_k;
  real_T tmp_l;
  real_T tmp_m;
  real_T tmp_n;
  real_T tmp_o;
  real_T tmp_p;
  real_T tmp_q;
  real_T tmp_r;
  real_T tmp_s;
  real_T tmp_t;
  real_T tmp_u;
  real_T tmp_v;
  real_T tmp_w;
  real_T tmp_x;
  real_T tmp_y;
  real_T tmp_z;
  real_T u0;
  real_T u0_0;
  real_T u0_1;
  real_T u0_2;
  real_T u0_3;
  real_T u0_4;
  real_T y;
  real_T y_0;
  real_T y_1;
  real_T y_2;
  real_T y_3;
  real_T y_4;
  real_T y_5;
  real_T y_6;
  real_T y_7;
  real_T y_8;
  real_T y_9;
  real_T y_a;
  real_T y_b;
  real_T y_c;
  real_T y_d;
  real_T y_e;
  real_T y_f;
  real_T y_g;
  int32_T b_M_AO_tmp;
  int32_T b_M_BO_tmp;
  int32_T b_M_OB_ckuz_tmp;
  int32_T b_Product10_dtl1_tmp;
  int32_T b_Product1_anfa_tmp;
  int32_T b_Product1_eroc_tmp;
  int32_T b_Product1_l1hk_tmp;
  int32_T b_Product1_nejo_tmp;
  int32_T b_Product_ciz4_tmp;
  int32_T b_VectorConcatenate_dkiq_tmp;
  int32_T b_VectorConcatenate_iewf_tmp;
  int32_T b_VectorConcatenate_jnc0_tmp;
  int32_T b_vel_K_R_E_O_mDs_tmp;
  int32_T i;
  int32_T iU;
  int32_T iU_0;
  int32_T iU_1;
  int32_T iU_2;
  int32_T iU_3;
  int32_T iU_4;
  int32_T iU_5;
  int32_T iU_6;
  int32_T iU_7;
  int32_T iU_8;
  int32_T iU_9;
  int32_T iU_a;
  int32_T iU_b;
  int32_T iU_c;
  int32_T iU_d;
  int32_T iU_e;
  int32_T iU_f;
  int32_T iU_g;
  int32_T i_0;
  int32_T i_1;
  int32_T i_10;
  int32_T i_11;
  int32_T i_12;
  int32_T i_13;
  int32_T i_14;
  int32_T i_15;
  int32_T i_16;
  int32_T i_17;
  int32_T i_18;
  int32_T i_19;
  int32_T i_1a;
  int32_T i_1b;
  int32_T i_1c;
  int32_T i_1d;
  int32_T i_1e;
  int32_T i_1f;
  int32_T i_1g;
  int32_T i_1h;
  int32_T i_1i;
  int32_T i_1j;
  int32_T i_1k;
  int32_T i_1l;
  int32_T i_1m;
  int32_T i_1n;
  int32_T i_1o;
  int32_T i_1p;
  int32_T i_1q;
  int32_T i_1r;
  int32_T i_1s;
  int32_T i_1t;
  int32_T i_1u;
  int32_T i_1v;
  int32_T i_1w;
  int32_T i_1x;
  int32_T i_1y;
  int32_T i_1z;
  int32_T i_2;
  int32_T i_20;
  int32_T i_21;
  int32_T i_22;
  int32_T i_23;
  int32_T i_24;
  int32_T i_25;
  int32_T i_26;
  int32_T i_27;
  int32_T i_28;
  int32_T i_29;
  int32_T i_2a;
  int32_T i_2b;
  int32_T i_2c;
  int32_T i_2d;
  int32_T i_2e;
  int32_T i_2f;
  int32_T i_2g;
  int32_T i_2h;
  int32_T i_2i;
  int32_T i_2j;
  int32_T i_2k;
  int32_T i_2l;
  int32_T i_2m;
  int32_T i_2n;
  int32_T i_2o;
  int32_T i_2p;
  int32_T i_2q;
  int32_T i_2r;
  int32_T i_2s;
  int32_T i_2t;
  int32_T i_2u;
  int32_T i_2v;
  int32_T i_2w;
  int32_T i_2x;
  int32_T i_2y;
  int32_T i_2z;
  int32_T i_3;
  int32_T i_30;
  int32_T i_31;
  int32_T i_32;
  int32_T i_33;
  int32_T i_34;
  int32_T i_35;
  int32_T i_36;
  int32_T i_37;
  int32_T i_38;
  int32_T i_39;
  int32_T i_3a;
  int32_T i_3b;
  int32_T i_3c;
  int32_T i_3d;
  int32_T i_3e;
  int32_T i_3f;
  int32_T i_3g;
  int32_T i_3h;
  int32_T i_3i;
  int32_T i_3j;
  int32_T i_3k;
  int32_T i_3l;
  int32_T i_3m;
  int32_T i_3n;
  int32_T i_3o;
  int32_T i_3p;
  int32_T i_3q;
  int32_T i_3r;
  int32_T i_3s;
  int32_T i_3t;
  int32_T i_3u;
  int32_T i_3v;
  int32_T i_3w;
  int32_T i_3x;
  int32_T i_3y;
  int32_T i_3z;
  int32_T i_4;
  int32_T i_40;
  int32_T i_41;
  int32_T i_42;
  int32_T i_43;
  int32_T i_44;
  int32_T i_45;
  int32_T i_46;
  int32_T i_47;
  int32_T i_48;
  int32_T i_49;
  int32_T i_4a;
  int32_T i_4b;
  int32_T i_4c;
  int32_T i_4d;
  int32_T i_4e;
  int32_T i_4f;
  int32_T i_4g;
  int32_T i_4h;
  int32_T i_4i;
  int32_T i_4j;
  int32_T i_4k;
  int32_T i_4l;
  int32_T i_4m;
  int32_T i_4n;
  int32_T i_4o;
  int32_T i_4p;
  int32_T i_4q;
  int32_T i_4r;
  int32_T i_4s;
  int32_T i_4t;
  int32_T i_4u;
  int32_T i_4v;
  int32_T i_4w;
  int32_T i_4x;
  int32_T i_4y;
  int32_T i_4z;
  int32_T i_5;
  int32_T i_50;
  int32_T i_51;
  int32_T i_52;
  int32_T i_53;
  int32_T i_54;
  int32_T i_55;
  int32_T i_56;
  int32_T i_57;
  int32_T i_58;
  int32_T i_59;
  int32_T i_5a;
  int32_T i_5b;
  int32_T i_5c;
  int32_T i_5d;
  int32_T i_5e;
  int32_T i_5f;
  int32_T i_5g;
  int32_T i_5h;
  int32_T i_5i;
  int32_T i_5j;
  int32_T i_5k;
  int32_T i_5l;
  int32_T i_5m;
  int32_T i_5n;
  int32_T i_5o;
  int32_T i_5p;
  int32_T i_5q;
  int32_T i_5r;
  int32_T i_5s;
  int32_T i_5t;
  int32_T i_5u;
  int32_T i_5v;
  int32_T i_5w;
  int32_T i_5x;
  int32_T i_5y;
  int32_T i_5z;
  int32_T i_6;
  int32_T i_60;
  int32_T i_61;
  int32_T i_62;
  int32_T i_63;
  int32_T i_64;
  int32_T i_65;
  int32_T i_66;
  int32_T i_67;
  int32_T i_68;
  int32_T i_69;
  int32_T i_6a;
  int32_T i_6b;
  int32_T i_6c;
  int32_T i_6d;
  int32_T i_6e;
  int32_T i_6f;
  int32_T i_6g;
  int32_T i_6h;
  int32_T i_6i;
  int32_T i_6j;
  int32_T i_6k;
  int32_T i_6l;
  int32_T i_6m;
  int32_T i_6n;
  int32_T i_6o;
  int32_T i_6p;
  int32_T i_6q;
  int32_T i_6r;
  int32_T i_6s;
  int32_T i_6t;
  int32_T i_6u;
  int32_T i_6v;
  int32_T i_6w;
  int32_T i_6x;
  int32_T i_6y;
  int32_T i_6z;
  int32_T i_7;
  int32_T i_70;
  int32_T i_71;
  int32_T i_72;
  int32_T i_73;
  int32_T i_74;
  int32_T i_75;
  int32_T i_76;
  int32_T i_77;
  int32_T i_78;
  int32_T i_79;
  int32_T i_7a;
  int32_T i_7b;
  int32_T i_7c;
  int32_T i_7d;
  int32_T i_7e;
  int32_T i_7f;
  int32_T i_7g;
  int32_T i_7h;
  int32_T i_7i;
  int32_T i_7j;
  int32_T i_7k;
  int32_T i_7l;
  int32_T i_7m;
  int32_T i_7n;
  int32_T i_7o;
  int32_T i_7p;
  int32_T i_7q;
  int32_T i_7r;
  int32_T i_7s;
  int32_T i_7t;
  int32_T i_7u;
  int32_T i_7v;
  int32_T i_7w;
  int32_T i_7x;
  int32_T i_7y;
  int32_T i_7z;
  int32_T i_8;
  int32_T i_80;
  int32_T i_81;
  int32_T i_82;
  int32_T i_83;
  int32_T i_84;
  int32_T i_85;
  int32_T i_86;
  int32_T i_87;
  int32_T i_88;
  int32_T i_89;
  int32_T i_8a;
  int32_T i_8b;
  int32_T i_8c;
  int32_T i_8d;
  int32_T i_8e;
  int32_T i_8f;
  int32_T i_8g;
  int32_T i_8h;
  int32_T i_8i;
  int32_T i_8j;
  int32_T i_8k;
  int32_T i_8l;
  int32_T i_8m;
  int32_T i_8n;
  int32_T i_8o;
  int32_T i_8p;
  int32_T i_8q;
  int32_T i_8r;
  int32_T i_8s;
  int32_T i_8t;
  int32_T i_9;
  int32_T i_a;
  int32_T i_b;
  int32_T i_c;
  int32_T i_d;
  int32_T i_e;
  int32_T i_f;
  int32_T i_g;
  int32_T i_h;
  int32_T i_i;
  int32_T i_j;
  int32_T i_k;
  int32_T i_l;
  int32_T i_m;
  int32_T i_n;
  int32_T i_o;
  int32_T i_p;
  int32_T i_q;
  int32_T i_r;
  int32_T i_s;
  int32_T i_t;
  int32_T i_u;
  int32_T i_v;
  int32_T i_w;
  int32_T i_x;
  int32_T i_y;
  int32_T i_z;
  int32_T k;
  int32_T k_0;
  int32_T k_1;
  int32_T tmp_16;
  int32_T tmp_i;
  int32_T tmp_j;
  int32_T uIdx;
  int32_T uIdx_0;
  int32_T uIdx_1;
  boolean_T b_LogicalOperator;
  boolean_T didZcEventOccur;
  boolean_T didZcEventOccur_0;
  boolean_T didZcEventOccur_1;
  boolean_T didZcEventOccur_2;
  boolean_T didZcEventOccur_3;
  boolean_T didZcEventOccur_4;
  boolean_T didZcEventOccur_5;
  boolean_T didZcEventOccur_6;
  boolean_T didZcEventOccur_7;
  boolean_T didZcEventOccur_8;
  boolean_T didZcEventOccur_9;
  boolean_T didZcEventOccur_a;
  boolean_T didZcEventOccur_b;
  ZCEventType zcEvent;
  ZCEventType zcEvent_0;
  ZCEventType zcEvent_1;
  ZCEventType zcEvent_2;
  ZCEventType zcEvent_3;
  ZCEventType zcEvent_4;
  ZCEventType zcEvent_5;
  ZCEventType zcEvent_6;
  ZCEventType zcEvent_7;
  ZCEventType zcEvent_8;
  ZCEventType zcEvent_9;
  ZCEventType zcEvent_a;
  ZCEventType zcEvent_b;
  ZCEventType zcEvent_c;
  ZCEventType zcEvent_d;
  ZCEventType zcEvent_e;
  ZCEventType zcEvent_f;
  ZCEventType zcEvent_g;
  ZCEventType zcEvent_h;
  ZCEventType zcEvent_i;
  ZCEventType zcEvent_j;
  ZCEventType zcEvent_k;
  ZCEventType zcEvent_l;
  ZCEventType zcEvent_m;
  ZCEventType zcEvent_n;
  ZCEventType zcEvent_o;
  ZCEventType zcEvent_p;
  ZCEventType zcEvent_q;
  ZCEventType zcEvent_r;
  ZCEventType zcEvent_s;

  /* SignalConversion generated from: '<S216>/Vector Concatenate1' incorporates:
   *  Constant: '<S216>/Constant'
   */
  b_VectorConcatenate1[0] = 0.0;

  /* Integrator: '<S12>/att_phi_rad' incorporates:
   *  Integrator: '<S13>/att_psi_rad'
   *  Integrator: '<S14>/att_theta_rad'
   */
  if (rtsiIsModeUpdateTimeStep(RMT_FDM_RT_M->solverInfo)) {
    didZcEventOccur = (rtu_Simulation_Control->flg_Reset &&
                       (localZCE->att_phi_rad_Reset_ZCE != POS_ZCSIG));
    localZCE->att_phi_rad_Reset_ZCE = (uint8_T)rtu_Simulation_Control->flg_Reset;

    /* evaluate zero-crossings */
    if (didZcEventOccur || localDW->att_phi_rad_DWORK1) {
      localX->Phi_rad = rtu_States_Init->att_euler_rad.Phi_rad;
    }

    didZcEventOccur_0 = (rtu_Simulation_Control->flg_Reset &&
                         (localZCE->att_theta_rad_Reset_ZCE != POS_ZCSIG));
    localZCE->att_theta_rad_Reset_ZCE = (uint8_T)
      rtu_Simulation_Control->flg_Reset;

    /* evaluate zero-crossings */
    if (didZcEventOccur_0 || localDW->att_theta_rad_DWORK1) {
      localX->Theta_rad = rtu_States_Init->att_euler_rad.Theta_rad;
    }

    didZcEventOccur_1 = (rtu_Simulation_Control->flg_Reset &&
                         (localZCE->att_psi_rad_Reset_ZCE != POS_ZCSIG));
    localZCE->att_psi_rad_Reset_ZCE = (uint8_T)rtu_Simulation_Control->flg_Reset;

    /* evaluate zero-crossings */
    if (didZcEventOccur_1 || localDW->att_psi_rad_DWORK1) {
      localX->Psi_rad = rtu_States_Init->att_euler_rad.Psi_rad;
    }
  }

  /* Trigonometry: '<S216>/Trigonometric Function' incorporates:
   *  Integrator: '<S12>/att_phi_rad'
   */
  b_v_K_R_E_B_mDs = cos(localX->Phi_rad);

  /* SignalConversion generated from: '<S216>/Vector Concatenate1' */
  b_VectorConcatenate1[1] = b_v_K_R_E_B_mDs;

  /* Trigonometry: '<S216>/Trigonometric Function1' incorporates:
   *  Integrator: '<S12>/att_phi_rad'
   */
  b_Theta_rad = sin(localX->Phi_rad);

  /* SignalConversion generated from: '<S216>/Vector Concatenate1' */
  b_VectorConcatenate1[2] = b_Theta_rad;

  /* SignalConversion generated from: '<S216>/Vector Concatenate2' incorporates:
   *  Constant: '<S216>/Constant'
   */
  b_VectorConcatenate2[0] = 0.0;

  /* Gain: '<S216>/Gain' */
  b_VectorConcatenate2[1] = -b_Theta_rad;

  /* SignalConversion generated from: '<S216>/Vector Concatenate2' */
  b_VectorConcatenate2[2] = b_v_K_R_E_B_mDs;

  /* Trigonometry: '<S217>/Trigonometric Function' incorporates:
   *  Integrator: '<S14>/att_theta_rad'
   */
  b_v_K_R_E_B_mDs = cos(localX->Theta_rad);

  /* SignalConversion generated from: '<S217>/Vector Concatenate' */
  b_VectorConcatenate_oque[0] = b_v_K_R_E_B_mDs;

  /* SignalConversion generated from: '<S217>/Vector Concatenate' incorporates:
   *  Constant: '<S217>/Constant'
   */
  b_VectorConcatenate_oque[1] = 0.0;

  /* Trigonometry: '<S217>/Trigonometric Function1' incorporates:
   *  Integrator: '<S14>/att_theta_rad'
   *  Trigonometry: '<S359>/Trigonometric Function1'
   *  Trigonometry: '<S376>/Trigonometric Function1'
   */
  b_u_K_R_E_B_mDs_tmp = sin(localX->Theta_rad);

  /* Gain: '<S217>/Gain' incorporates:
   *  Trigonometry: '<S217>/Trigonometric Function1'
   */
  b_VectorConcatenate_oque[2] = -b_u_K_R_E_B_mDs_tmp;

  /* SignalConversion generated from: '<S217>/Vector Concatenate2' incorporates:
   *  Trigonometry: '<S217>/Trigonometric Function1'
   */
  b_VectorConcatenate2_bxrn[0] = b_u_K_R_E_B_mDs_tmp;

  /* SignalConversion generated from: '<S217>/Vector Concatenate2' incorporates:
   *  Constant: '<S217>/Constant'
   */
  b_VectorConcatenate2_bxrn[1] = 0.0;

  /* SignalConversion generated from: '<S217>/Vector Concatenate2' */
  b_VectorConcatenate2_bxrn[2] = b_v_K_R_E_B_mDs;

  /* Outputs for Atomic SubSystem: '<S44>/M_z' */
  /* Trigonometry: '<S218>/Trigonometric Function' incorporates:
   *  Integrator: '<S13>/att_psi_rad'
   *  Trigonometry: '<S50>/Trigonometric Function'
   */
  b_u_K_R_E_B_mDs_tmp_0 = cos(localX->Psi_rad);

  /* End of Outputs for SubSystem: '<S44>/M_z' */

  /* SignalConversion generated from: '<S218>/Vector Concatenate' incorporates:
   *  Trigonometry: '<S218>/Trigonometric Function'
   */
  b_VectorConcatenate_nhrs[0] = b_u_K_R_E_B_mDs_tmp_0;

  /* Outputs for Atomic SubSystem: '<S44>/M_z' */
  /* Trigonometry: '<S218>/Trigonometric Function1' incorporates:
   *  Integrator: '<S13>/att_psi_rad'
   *  Trigonometry: '<S50>/Trigonometric Function1'
   */
  b_v_K_R_E_B_mDs_tmp = sin(localX->Psi_rad);

  /* End of Outputs for SubSystem: '<S44>/M_z' */

  /* SignalConversion generated from: '<S218>/Vector Concatenate' incorporates:
   *  Trigonometry: '<S218>/Trigonometric Function1'
   */
  b_VectorConcatenate_nhrs[1] = b_v_K_R_E_B_mDs_tmp;

  /* SignalConversion generated from: '<S218>/Vector Concatenate' incorporates:
   *  Constant: '<S218>/Constant'
   */
  b_VectorConcatenate_nhrs[2] = 0.0;

  /* Gain: '<S218>/Gain' incorporates:
   *  Trigonometry: '<S218>/Trigonometric Function1'
   */
  b_Reshape_kl1z[0] = -b_v_K_R_E_B_mDs_tmp;

  /* SignalConversion generated from: '<S218>/Vector Concatenate1' incorporates:
   *  Trigonometry: '<S218>/Trigonometric Function'
   */
  b_Reshape_kl1z[1] = b_u_K_R_E_B_mDs_tmp_0;

  /* SignalConversion generated from: '<S218>/Vector Concatenate1' incorporates:
   *  Constant: '<S218>/Constant'
   */
  b_Reshape_kl1z[2] = 0.0;

  /* Concatenate: '<S217>/Vector Concatenate3' incorporates:
   *  Concatenate: '<S217>/Vector Concatenate'
   *  Concatenate: '<S217>/Vector Concatenate1'
   *  Concatenate: '<S217>/Vector Concatenate2'
   */
  for (i_27 = 0; i_27 < 3; i_27 = i_27 + 1) {
    b_VectorConcatenate_dkiq[3 * i_27] = b_VectorConcatenate_oque[i_27];
  }

  for (i_28 = 0; i_28 < 3; i_28 = i_28 + 1) {
    b_VectorConcatenate_dkiq[1 + 3 * i_28] =
      RMT_FDM_RT_ConstB.VectorConcatenate1_nkgw[i_28];
  }

  for (i_29 = 0; i_29 < 3; i_29 = i_29 + 1) {
    b_VectorConcatenate_dkiq[2 + 3 * i_29] = b_VectorConcatenate2_bxrn[i_29];
  }

  /* End of Concatenate: '<S217>/Vector Concatenate3' */

  /* Concatenate: '<S218>/Vector Concatenate3' incorporates:
   *  Concatenate: '<S218>/Vector Concatenate'
   *  Concatenate: '<S218>/Vector Concatenate2'
   *  Reshape: '<S199>/Reshape'
   */
  for (i_2a = 0; i_2a < 3; i_2a = i_2a + 1) {
    b_VectorConcatenate_gmvx[3 * i_2a] = b_VectorConcatenate_nhrs[i_2a];
  }

  for (i_2b = 0; i_2b < 3; i_2b = i_2b + 1) {
    b_VectorConcatenate_gmvx[1 + 3 * i_2b] = b_Reshape_kl1z[i_2b];
  }

  for (i_2c = 0; i_2c < 3; i_2c = i_2c + 1) {
    b_VectorConcatenate_gmvx[2 + 3 * i_2c] =
      RMT_FDM_RT_ConstB.VectorConcatenate2_och4[i_2c];
  }

  /* End of Concatenate: '<S218>/Vector Concatenate3' */

  /* Concatenate: '<S216>/Vector Concatenate3' incorporates:
   *  Concatenate: '<S216>/Vector Concatenate'
   *  Concatenate: '<S216>/Vector Concatenate1'
   *  Concatenate: '<S216>/Vector Concatenate2'
   */
  for (i_2d = 0; i_2d < 3; i_2d = i_2d + 1) {
    tmp_4[3 * i_2d] = RMT_FDM_RT_ConstB.VectorConcatenate[i_2d];
  }

  for (i_2e = 0; i_2e < 3; i_2e = i_2e + 1) {
    tmp_4[1 + 3 * i_2e] = b_VectorConcatenate1[i_2e];
  }

  for (i_2f = 0; i_2f < 3; i_2f = i_2f + 1) {
    tmp_4[2 + 3 * i_2f] = b_VectorConcatenate2[i_2f];
  }

  /* End of Concatenate: '<S216>/Vector Concatenate3' */

  /* Product: '<S214>/Product10' */
  for (i_2g = 0; i_2g < 3; i_2g = i_2g + 1) {
    for (i_2h = 0; i_2h < 3; i_2h = i_2h + 1) {
      b_VectorConcatenate_dkiq_tmp = i_2g + 3 * i_2h;
      b_VectorConcatenate_dkiq_0[b_VectorConcatenate_dkiq_tmp] = 0.0;
      for (i_2i = 0; i_2i < 3; i_2i = i_2i + 1) {
        b_VectorConcatenate_dkiq_0[b_VectorConcatenate_dkiq_tmp] =
          b_VectorConcatenate_dkiq_0[b_VectorConcatenate_dkiq_tmp] +
          b_VectorConcatenate_dkiq[i_2g + 3 * i_2i] *
          b_VectorConcatenate_gmvx[i_2i + 3 * i_2h];
      }
    }
  }

  for (i_2j = 0; i_2j < 3; i_2j = i_2j + 1) {
    for (i_2k = 0; i_2k < 3; i_2k = i_2k + 1) {
      b_M_BO_tmp = i_2j + 3 * i_2k;
      b_M_BO[b_M_BO_tmp] = 0.0;
      for (i_2l = 0; i_2l < 3; i_2l = i_2l + 1) {
        b_M_BO[b_M_BO_tmp] = b_M_BO[b_M_BO_tmp] + tmp_4[i_2j + 3 * i_2l] *
          b_VectorConcatenate_dkiq_0[i_2l + 3 * i_2k];
      }
    }
  }

  /* End of Product: '<S214>/Product10' */

  /* Integrator: '<S21>/vel_x_K' incorporates:
   *  Integrator: '<S22>/vel_y_K'
   *  Integrator: '<S23>/vel_w_K'
   */
  if (rtsiIsModeUpdateTimeStep(RMT_FDM_RT_M->solverInfo)) {
    didZcEventOccur_2 = (rtu_Simulation_Control->flg_Reset &&
                         (localZCE->vel_x_K_Reset_ZCE != POS_ZCSIG));
    localZCE->vel_x_K_Reset_ZCE = (uint8_T)rtu_Simulation_Control->flg_Reset;

    /* evaluate zero-crossings */
    if (didZcEventOccur_2 || localDW->vel_x_K_DWORK1) {
      localX->u_K_R_E_B_mDs = rtu_States_Init->vel_K_R_E_B_mDs.u_K_R_E_B_mDs;
    }

    didZcEventOccur_3 = (rtu_Simulation_Control->flg_Reset &&
                         (localZCE->vel_y_K_Reset_ZCE != POS_ZCSIG));
    localZCE->vel_y_K_Reset_ZCE = (uint8_T)rtu_Simulation_Control->flg_Reset;

    /* evaluate zero-crossings */
    if (didZcEventOccur_3 || localDW->vel_y_K_DWORK1) {
      localX->v_K_R_E_B_mDs = rtu_States_Init->vel_K_R_E_B_mDs.v_K_R_E_B_mDs;
    }

    didZcEventOccur_4 = (rtu_Simulation_Control->flg_Reset &&
                         (localZCE->vel_w_K_Reset_ZCE != POS_ZCSIG));
    localZCE->vel_w_K_Reset_ZCE = (uint8_T)rtu_Simulation_Control->flg_Reset;

    /* evaluate zero-crossings */
    if (didZcEventOccur_4 || localDW->vel_w_K_DWORK1) {
      localX->w_K_R_E_B_mDs = rtu_States_Init->vel_K_R_E_B_mDs.w_K_R_E_B_mDs;
    }
  }

  /* SignalConversion generated from: '<S199>/Vector Concatenate' incorporates:
   *  Integrator: '<S21>/vel_x_K'
   */
  b_Reshape1_lt4a[0] = localX->u_K_R_E_B_mDs;

  /* SignalConversion generated from: '<S199>/Vector Concatenate' incorporates:
   *  Integrator: '<S22>/vel_y_K'
   */
  b_Reshape1_lt4a[1] = localX->v_K_R_E_B_mDs;

  /* SignalConversion generated from: '<S199>/Vector Concatenate' incorporates:
   *  Integrator: '<S23>/vel_w_K'
   */
  b_Reshape1_lt4a[2] = localX->w_K_R_E_B_mDs;

  /* SignalConversion generated from: '<S221>/Vector Concatenate' */
  b_Reshape2_o51o[0] =
    *rtu_External_Inputs_Wind_Data_vel_W_R_E_O_mDs_u_W_R_E_O_mDs;

  /* SignalConversion generated from: '<S221>/Vector Concatenate' */
  b_Reshape2_o51o[1] =
    *rtu_External_Inputs_Wind_Data_vel_W_R_E_O_mDs_v_W_R_E_O_mDs;

  /* SignalConversion generated from: '<S221>/Vector Concatenate' */
  b_Reshape2_o51o[2] =
    *rtu_External_Inputs_Wind_Data_vel_W_R_E_O_mDs_w_W_R_E_O_mDs;

  /* Product: '<S221>/Product' incorporates:
   *  Product: '<S214>/Product10'
   *  Reshape: '<S199>/Reshape2'
   *  Reshape: '<S221>/Reshape'
   */
  for (i_2m = 0; i_2m < 3; i_2m = i_2m + 1) {
    b_M_BO_0[i_2m] = 0.0;
    for (i_2n = 0; i_2n < 3; i_2n = i_2n + 1) {
      b_M_BO_0[i_2m] = b_M_BO_0[i_2m] + b_M_BO[i_2m + 3 * i_2n] *
        b_Reshape2_o51o[i_2n];
    }
  }

  for (i_2o = 0; i_2o < 3; i_2o = i_2o + 1) {
    b_Reshape2_o51o[i_2o] = b_M_BO_0[i_2o];
  }

  /* End of Product: '<S221>/Product' */

  /* SignalConversion generated from: '<S199>/Vector Concatenate1' incorporates:
   *  Reshape: '<S199>/Reshape2'
   *  Reshape: '<S221>/Reshape1'
   */
  b_Subtract_kaxz[0] = b_Reshape2_o51o[0];

  /* SignalConversion generated from: '<S199>/Vector Concatenate1' incorporates:
   *  Reshape: '<S199>/Reshape2'
   *  Reshape: '<S221>/Reshape1'
   */
  b_Subtract_kaxz[1] = b_Reshape2_o51o[1];

  /* SignalConversion generated from: '<S199>/Vector Concatenate1' incorporates:
   *  Reshape: '<S199>/Reshape2'
   *  Reshape: '<S221>/Reshape1'
   */
  b_Subtract_kaxz[2] = b_Reshape2_o51o[2];

  /* Sum: '<S199>/Subtract' incorporates:
   *  Reshape: '<S199>/Reshape'
   *  Reshape: '<S199>/Reshape1'
   */
  for (i_2p = 0; i_2p < 3; i_2p = i_2p + 1) {
    b_Subtract_kaxz[i_2p] = b_Reshape1_lt4a[i_2p] - b_Subtract_kaxz[i_2p];
  }

  /* End of Sum: '<S199>/Subtract' */

  /* Trigonometry: '<S209>/Trigonometric Function7' incorporates:
   *  Reshape: '<S199>/Reshape2'
   *  Sum: '<S199>/Subtract'
   */
  b_TrigonometricFunction7_n3ob = rt_atan2d_snf(b_Subtract_kaxz[2],
    b_Subtract_kaxz[0]);

  /* Trigonometry: '<S203>/Trigonometric Function1' incorporates:
   *  Trigonometry: '<S205>/Trigonometric Function1'
   */
  b_w_y_K_IB_B_radDs_tmp = cos(b_TrigonometricFunction7_n3ob);

  /* SignalConversion generated from: '<S203>/Vector Concatenate' incorporates:
   *  Trigonometry: '<S203>/Trigonometric Function1'
   */
  b_M_AO[0] = b_w_y_K_IB_B_radDs_tmp;

  /* SignalConversion generated from: '<S203>/Vector Concatenate' incorporates:
   *  Constant: '<S203>/Constant1'
   */
  b_M_AO[1] = 0.0;

  /* Trigonometry: '<S203>/Trigonometric Function' incorporates:
   *  Trigonometry: '<S205>/Trigonometric Function'
   */
  b_TrigonometricFunction1_pesf_tmp = sin(b_TrigonometricFunction7_n3ob);

  /* SignalConversion generated from: '<S203>/Vector Concatenate' incorporates:
   *  Trigonometry: '<S203>/Trigonometric Function'
   */
  b_M_AO[2] = b_TrigonometricFunction1_pesf_tmp;

  /* SignalConversion generated from: '<S203>/Matrix Concaenate' incorporates:
   *  Concatenate: '<S203>/Vector Concatenate1'
   */
  for (i_6 = 0; i_6 < 3; i_6 = i_6 + 1) {
    b_M_AO[i_6 + 3] = RMT_FDM_RT_ConstB.VectorConcatenate1[i_6];
  }

  /* End of SignalConversion generated from: '<S203>/Matrix Concaenate' */

  /* Gain: '<S203>/Gain' incorporates:
   *  Trigonometry: '<S203>/Trigonometric Function'
   */
  b_M_AO[6] = -b_TrigonometricFunction1_pesf_tmp;

  /* SignalConversion generated from: '<S203>/Vector Concatenate2' incorporates:
   *  Constant: '<S203>/Constant1'
   */
  b_M_AO[7] = 0.0;

  /* SignalConversion generated from: '<S203>/Vector Concatenate2' incorporates:
   *  Trigonometry: '<S203>/Trigonometric Function1'
   */
  b_M_AO[8] = b_w_y_K_IB_B_radDs_tmp;

  /* SignalConversion generated from: '<S210>/Vector Concatenate2' incorporates:
   *  Reshape: '<S199>/Reshape2'
   *  Sum: '<S199>/Subtract'
   */
  b_VectorConcatenate2_ofdc[0] = b_Subtract_kaxz[2];

  /* SignalConversion generated from: '<S210>/Vector Concatenate2' incorporates:
   *  Reshape: '<S199>/Reshape2'
   *  Sum: '<S199>/Subtract'
   */
  b_VectorConcatenate2_ofdc[1] = b_Subtract_kaxz[0];

  /* Math: '<S212>/Math Function' */
  for (i_7 = 0; i_7 < 2; i_7 = i_7 + 1) {
    b_MathFunction[i_7] = b_VectorConcatenate2_ofdc[i_7] *
      b_VectorConcatenate2_ofdc[i_7];
  }

  /* End of Math: '<S212>/Math Function' */

  /* Sum: '<S212>/Sum of Elements' */
  tmp = b_MathFunction[0] + b_MathFunction[1];

  /* Sqrt: '<S212>/Math Function1' incorporates:
   *  Sum: '<S212>/Sum of Elements'
   *
   * About '<S212>/Math Function1':
   *  Operator: signedSqrt
   */
  if (tmp < 0.0) {
    b_w_y_K_IB_B_radDs = -sqrt(fabs(tmp));
  } else {
    b_w_y_K_IB_B_radDs = sqrt(tmp);
  }

  /* End of Sqrt: '<S212>/Math Function1' */

  /* Trigonometry: '<S210>/Trigonometric Function1' incorporates:
   *  Reshape: '<S199>/Reshape2'
   *  Sum: '<S199>/Subtract'
   */
  b_TrigonometricFunction1_kiq3 = rt_atan2d_snf(b_Subtract_kaxz[1],
    b_w_y_K_IB_B_radDs);

  /* Trigonometry: '<S204>/Trigonometric Function1' incorporates:
   *  Gain: '<S200>/Gain'
   */
  b_w_x_K_OB_B_radDs = cos(-b_TrigonometricFunction1_kiq3);

  /* SignalConversion generated from: '<S204>/Vector Concatenate' */
  b_M_AB[0] = b_w_x_K_OB_B_radDs;

  /* Trigonometry: '<S204>/Trigonometric Function' incorporates:
   *  Gain: '<S200>/Gain'
   */
  b_w_x_K_IB_B_radDs = sin(-b_TrigonometricFunction1_kiq3);

  /* Gain: '<S204>/Gain' */
  b_M_AB[1] = -b_w_x_K_IB_B_radDs;

  /* SignalConversion generated from: '<S204>/Vector Concatenate' incorporates:
   *  Constant: '<S204>/Constant1'
   */
  b_M_AB[2] = 0.0;

  /* SignalConversion generated from: '<S204>/Vector Concatenate1' */
  b_M_AB[3] = b_w_x_K_IB_B_radDs;

  /* SignalConversion generated from: '<S204>/Vector Concatenate1' */
  b_M_AB[4] = b_w_x_K_OB_B_radDs;

  /* SignalConversion generated from: '<S204>/Vector Concatenate1' incorporates:
   *  Constant: '<S204>/Constant1'
   */
  b_M_AB[5] = 0.0;

  /* SignalConversion generated from: '<S204>/Matrix Concaenate' incorporates:
   *  Concatenate: '<S204>/Vector Concatenate2'
   */
  for (i_8 = 0; i_8 < 3; i_8 = i_8 + 1) {
    b_M_AB[i_8 + 6] = RMT_FDM_RT_ConstB.VectorConcatenate2[i_8];
  }

  /* End of SignalConversion generated from: '<S204>/Matrix Concaenate' */

  /* Product: '<S202>/Product' incorporates:
   *  Math: '<S196>/Math Function3'
   *  Product: '<S196>/Product'
   */
  for (i_2q = 0; i_2q < 3; i_2q = i_2q + 1) {
    for (i_2r = 0; i_2r < 3; i_2r = i_2r + 1) {
      b_Product_ciz4_tmp = i_2q + 3 * i_2r;
      b_Product_epes[b_Product_ciz4_tmp] = 0.0;
      for (i_2s = 0; i_2s < 3; i_2s = i_2s + 1) {
        b_Product_epes[b_Product_ciz4_tmp] = b_Product_epes[b_Product_ciz4_tmp]
          + b_M_AO[i_2q + 3 * i_2s] * b_M_AB[i_2s + 3 * i_2r];
      }
    }
  }

  /* End of Product: '<S202>/Product' */

  /* Math: '<S196>/Math Function3' incorporates:
   *  Product: '<S202>/Product'
   */
  for (i_2u = 0; i_2u < 3; i_2u = i_2u + 1) {
    for (i_2t = 0; i_2t < 3; i_2t = i_2t + 1) {
      b_M_AB[i_2t + 3 * i_2u] = b_Product_epes[i_2u + 3 * i_2t];
    }
  }

  /* End of Math: '<S196>/Math Function3' */

  /* Product: '<S196>/Product' incorporates:
   *  Math: '<S196>/Math Function3'
   *  Product: '<S214>/Product10'
   */
  for (i_2v = 0; i_2v < 3; i_2v = i_2v + 1) {
    for (i_2w = 0; i_2w < 3; i_2w = i_2w + 1) {
      b_M_AO_tmp = i_2v + 3 * i_2w;
      b_M_AO[b_M_AO_tmp] = 0.0;
      for (i_2x = 0; i_2x < 3; i_2x = i_2x + 1) {
        b_M_AO[b_M_AO_tmp] = b_M_AO[b_M_AO_tmp] + b_M_AB[i_2v + 3 * i_2x] *
          b_M_BO[i_2x + 3 * i_2w];
      }
    }
  }

  /* End of Product: '<S196>/Product' */
  for (i_2z = 0; i_2z < 3; i_2z = i_2z + 1) {
    for (i_2y = 0; i_2y < 3; i_2y = i_2y + 1) {
      /* Math: '<S213>/Math Function' incorporates:
       *  Math: '<S188>/Transpose'
       *  Product: '<S214>/Product10'
       */
      b_M_OB_h14v_tmp[i_2y + 3 * i_2z] = b_M_BO[i_2z + 3 * i_2y];
    }
  }

  /* Outputs for Atomic SubSystem: '<S44>/M_z' */
  /* SignalConversion generated from: '<S50>/Vector Concatenate' */
  b_VectorConcatenate_emun[0] = b_u_K_R_E_B_mDs_tmp_0;

  /* SignalConversion generated from: '<S50>/Vector Concatenate' */
  b_VectorConcatenate_emun[1] = b_v_K_R_E_B_mDs_tmp;

  /* SignalConversion generated from: '<S50>/Vector Concatenate' incorporates:
   *  Constant: '<S50>/Constant'
   */
  b_VectorConcatenate_emun[2] = 0.0;

  /* SignalConversion generated from: '<S50>/Vector Concatenate1' */
  b_VectorConcatenate1_dfc3[1] = b_u_K_R_E_B_mDs_tmp_0;

  /* SignalConversion generated from: '<S50>/Vector Concatenate1' incorporates:
   *  Constant: '<S50>/Constant'
   */
  b_VectorConcatenate1_dfc3[2] = 0.0;

  /* Gain: '<S50>/Gain' */
  b_VectorConcatenate1_dfc3[0] = -b_v_K_R_E_B_mDs_tmp;
  if (rtmIsMajorTimeStep(RMT_FDM_RT_M)) {
    /* SignalConversion generated from: '<S50>/Vector Concatenate2' incorporates:
     *  Concatenate: '<S50>/Vector Concatenate2'
     *  Constant: '<S50>/Constant'
     */
    localB->VectorConcatenate2_h100[0] = 0.0;

    /* SignalConversion generated from: '<S50>/Vector Concatenate2' incorporates:
     *  Concatenate: '<S50>/Vector Concatenate2'
     *  Constant: '<S50>/Constant'
     */
    localB->VectorConcatenate2_h100[1] = 0.0;

    /* Constant: '<S50>/Constant1' incorporates:
     *  Concatenate: '<S50>/Vector Concatenate2'
     */
    localB->VectorConcatenate2_h100[2] = 1.0;
  }

  /* Concatenate: '<S50>/Vector Concatenate3' incorporates:
   *  Concatenate: '<S50>/Vector Concatenate'
   *  Concatenate: '<S50>/Vector Concatenate1'
   *  Concatenate: '<S50>/Vector Concatenate2'
   */
  for (i_30 = 0; i_30 < 3; i_30 = i_30 + 1) {
    b_VectorConcatenate_kzox[3 * i_30] = b_VectorConcatenate_emun[i_30];
  }

  for (i_31 = 0; i_31 < 3; i_31 = i_31 + 1) {
    b_VectorConcatenate_kzox[1 + 3 * i_31] = b_VectorConcatenate1_dfc3[i_31];
  }

  for (i_32 = 0; i_32 < 3; i_32 = i_32 + 1) {
    b_VectorConcatenate_kzox[2 + 3 * i_32] = localB->
      VectorConcatenate2_h100[i_32];
  }

  /* End of Concatenate: '<S50>/Vector Concatenate3' */
  /* End of Outputs for SubSystem: '<S44>/M_z' */

  /* Product: '<S44>/Product1' incorporates:
   *  Math: '<S213>/Math Function'
   */
  for (i_33 = 0; i_33 < 3; i_33 = i_33 + 1) {
    for (i_34 = 0; i_34 < 3; i_34 = i_34 + 1) {
      b_Product1_nejo_tmp = i_33 + 3 * i_34;
      b_Product1_ovxb[b_Product1_nejo_tmp] = 0.0;
      for (i_35 = 0; i_35 < 3; i_35 = i_35 + 1) {
        b_Product1_ovxb[b_Product1_nejo_tmp] =
          b_Product1_ovxb[b_Product1_nejo_tmp] + b_VectorConcatenate_kzox[i_33 +
          3 * i_35] * b_M_OB_h14v_tmp[i_35 + 3 * i_34];
      }
    }
  }

  /* End of Product: '<S44>/Product1' */

  /* Math: '<S39>/Math Function' incorporates:
   *  Product: '<S44>/Product1'
   */
  for (i_37 = 0; i_37 < 3; i_37 = i_37 + 1) {
    for (i_36 = 0; i_36 < 3; i_36 = i_36 + 1) {
      b_MathFunction_dsxx[i_36 + 3 * i_37] = b_Product1_ovxb[i_37 + 3 * i_36];
    }
  }

  /* End of Math: '<S39>/Math Function' */

  /* Outputs for Atomic SubSystem: '<S61>/M_z' */
  /* Outputs for Atomic SubSystem: '<S44>/M_z' */
  /* SignalConversion generated from: '<S67>/Vector Concatenate' */
  b_VectorConcatenate_noxd[0] = b_u_K_R_E_B_mDs_tmp_0;

  /* SignalConversion generated from: '<S67>/Vector Concatenate' */
  b_VectorConcatenate_noxd[1] = b_v_K_R_E_B_mDs_tmp;

  /* End of Outputs for SubSystem: '<S44>/M_z' */

  /* SignalConversion generated from: '<S67>/Vector Concatenate' incorporates:
   *  Constant: '<S67>/Constant'
   */
  b_VectorConcatenate_noxd[2] = 0.0;

  /* Outputs for Atomic SubSystem: '<S44>/M_z' */
  /* SignalConversion generated from: '<S67>/Vector Concatenate1' */
  b_VectorConcatenate1_idvm[1] = b_u_K_R_E_B_mDs_tmp_0;

  /* End of Outputs for SubSystem: '<S44>/M_z' */

  /* SignalConversion generated from: '<S67>/Vector Concatenate1' incorporates:
   *  Constant: '<S67>/Constant'
   */
  b_VectorConcatenate1_idvm[2] = 0.0;

  /* Outputs for Atomic SubSystem: '<S44>/M_z' */
  /* Gain: '<S67>/Gain' */
  b_VectorConcatenate1_idvm[0] = -b_v_K_R_E_B_mDs_tmp;

  /* End of Outputs for SubSystem: '<S44>/M_z' */
  if (rtmIsMajorTimeStep(RMT_FDM_RT_M)) {
    /* SignalConversion generated from: '<S67>/Vector Concatenate2' incorporates:
     *  Concatenate: '<S67>/Vector Concatenate2'
     *  Constant: '<S67>/Constant'
     */
    localB->VectorConcatenate2_oktj[0] = 0.0;

    /* SignalConversion generated from: '<S67>/Vector Concatenate2' incorporates:
     *  Concatenate: '<S67>/Vector Concatenate2'
     *  Constant: '<S67>/Constant'
     */
    localB->VectorConcatenate2_oktj[1] = 0.0;

    /* Constant: '<S67>/Constant1' incorporates:
     *  Concatenate: '<S67>/Vector Concatenate2'
     */
    localB->VectorConcatenate2_oktj[2] = 1.0;
  }

  /* Concatenate: '<S67>/Vector Concatenate3' incorporates:
   *  Concatenate: '<S67>/Vector Concatenate'
   *  Concatenate: '<S67>/Vector Concatenate1'
   *  Concatenate: '<S67>/Vector Concatenate2'
   */
  for (i_38 = 0; i_38 < 3; i_38 = i_38 + 1) {
    b_VectorConcatenate_kj0i[3 * i_38] = b_VectorConcatenate_noxd[i_38];
  }

  for (i_39 = 0; i_39 < 3; i_39 = i_39 + 1) {
    b_VectorConcatenate_kj0i[1 + 3 * i_39] = b_VectorConcatenate1_idvm[i_39];
  }

  for (i_3a = 0; i_3a < 3; i_3a = i_3a + 1) {
    b_VectorConcatenate_kj0i[2 + 3 * i_3a] = localB->
      VectorConcatenate2_oktj[i_3a];
  }

  /* End of Concatenate: '<S67>/Vector Concatenate3' */
  /* End of Outputs for SubSystem: '<S61>/M_z' */

  /* Product: '<S61>/Product1' incorporates:
   *  Math: '<S213>/Math Function'
   */
  for (i_3b = 0; i_3b < 3; i_3b = i_3b + 1) {
    for (i_3c = 0; i_3c < 3; i_3c = i_3c + 1) {
      b_Product1_eroc_tmp = i_3b + 3 * i_3c;
      b_Product1_ehnp[b_Product1_eroc_tmp] = 0.0;
      for (i_3d = 0; i_3d < 3; i_3d = i_3d + 1) {
        b_Product1_ehnp[b_Product1_eroc_tmp] =
          b_Product1_ehnp[b_Product1_eroc_tmp] + b_VectorConcatenate_kj0i[i_3b +
          3 * i_3d] * b_M_OB_h14v_tmp[i_3d + 3 * i_3c];
      }
    }
  }

  /* End of Product: '<S61>/Product1' */

  /* Math: '<S40>/Math Function' incorporates:
   *  Product: '<S61>/Product1'
   */
  for (i_3f = 0; i_3f < 3; i_3f = i_3f + 1) {
    for (i_3e = 0; i_3e < 3; i_3e = i_3e + 1) {
      b_MathFunction_cbg2[i_3e + 3 * i_3f] = b_Product1_ehnp[i_3f + 3 * i_3e];
    }
  }

  /* End of Math: '<S40>/Math Function' */

  /* Outputs for Atomic SubSystem: '<S78>/M_z' */
  /* Outputs for Atomic SubSystem: '<S44>/M_z' */
  /* SignalConversion generated from: '<S84>/Vector Concatenate' */
  b_VectorConcatenate_h5xj[0] = b_u_K_R_E_B_mDs_tmp_0;

  /* SignalConversion generated from: '<S84>/Vector Concatenate' */
  b_VectorConcatenate_h5xj[1] = b_v_K_R_E_B_mDs_tmp;

  /* End of Outputs for SubSystem: '<S44>/M_z' */

  /* SignalConversion generated from: '<S84>/Vector Concatenate' incorporates:
   *  Constant: '<S84>/Constant'
   */
  b_VectorConcatenate_h5xj[2] = 0.0;

  /* Outputs for Atomic SubSystem: '<S44>/M_z' */
  /* SignalConversion generated from: '<S84>/Vector Concatenate1' */
  b_VectorConcatenate1_hfce[1] = b_u_K_R_E_B_mDs_tmp_0;

  /* End of Outputs for SubSystem: '<S44>/M_z' */

  /* SignalConversion generated from: '<S84>/Vector Concatenate1' incorporates:
   *  Constant: '<S84>/Constant'
   */
  b_VectorConcatenate1_hfce[2] = 0.0;

  /* Outputs for Atomic SubSystem: '<S44>/M_z' */
  /* Gain: '<S84>/Gain' */
  b_VectorConcatenate1_hfce[0] = -b_v_K_R_E_B_mDs_tmp;

  /* End of Outputs for SubSystem: '<S44>/M_z' */
  if (rtmIsMajorTimeStep(RMT_FDM_RT_M)) {
    /* SignalConversion generated from: '<S84>/Vector Concatenate2' incorporates:
     *  Concatenate: '<S84>/Vector Concatenate2'
     *  Constant: '<S84>/Constant'
     */
    localB->VectorConcatenate2_kq4e[0] = 0.0;

    /* SignalConversion generated from: '<S84>/Vector Concatenate2' incorporates:
     *  Concatenate: '<S84>/Vector Concatenate2'
     *  Constant: '<S84>/Constant'
     */
    localB->VectorConcatenate2_kq4e[1] = 0.0;

    /* Constant: '<S84>/Constant1' incorporates:
     *  Concatenate: '<S84>/Vector Concatenate2'
     */
    localB->VectorConcatenate2_kq4e[2] = 1.0;
  }

  /* Concatenate: '<S84>/Vector Concatenate3' incorporates:
   *  Concatenate: '<S84>/Vector Concatenate'
   *  Concatenate: '<S84>/Vector Concatenate1'
   *  Concatenate: '<S84>/Vector Concatenate2'
   */
  for (i_3g = 0; i_3g < 3; i_3g = i_3g + 1) {
    b_VectorConcatenate_ptbz[3 * i_3g] = b_VectorConcatenate_h5xj[i_3g];
  }

  for (i_3h = 0; i_3h < 3; i_3h = i_3h + 1) {
    b_VectorConcatenate_ptbz[1 + 3 * i_3h] = b_VectorConcatenate1_hfce[i_3h];
  }

  for (i_3i = 0; i_3i < 3; i_3i = i_3i + 1) {
    b_VectorConcatenate_ptbz[2 + 3 * i_3i] = localB->
      VectorConcatenate2_kq4e[i_3i];
  }

  /* End of Concatenate: '<S84>/Vector Concatenate3' */
  /* End of Outputs for SubSystem: '<S78>/M_z' */

  /* Product: '<S78>/Product1' incorporates:
   *  Math: '<S213>/Math Function'
   */
  for (i_3j = 0; i_3j < 3; i_3j = i_3j + 1) {
    for (i_3k = 0; i_3k < 3; i_3k = i_3k + 1) {
      b_Product1_anfa_tmp = i_3j + 3 * i_3k;
      b_Product1_n5kc[b_Product1_anfa_tmp] = 0.0;
      for (i_3l = 0; i_3l < 3; i_3l = i_3l + 1) {
        b_Product1_n5kc[b_Product1_anfa_tmp] =
          b_Product1_n5kc[b_Product1_anfa_tmp] + b_VectorConcatenate_ptbz[i_3j +
          3 * i_3l] * b_M_OB_h14v_tmp[i_3l + 3 * i_3k];
      }
    }
  }

  /* End of Product: '<S78>/Product1' */

  /* Math: '<S41>/Math Function' incorporates:
   *  Product: '<S78>/Product1'
   */
  for (i_3n = 0; i_3n < 3; i_3n = i_3n + 1) {
    for (i_3m = 0; i_3m < 3; i_3m = i_3m + 1) {
      b_MathFunction_avjt[i_3m + 3 * i_3n] = b_Product1_n5kc[i_3n + 3 * i_3m];
    }
  }

  /* End of Math: '<S41>/Math Function' */

  /* Outputs for Atomic SubSystem: '<S95>/M_z' */
  /* Outputs for Atomic SubSystem: '<S44>/M_z' */
  /* SignalConversion generated from: '<S101>/Vector Concatenate' */
  b_VectorConcatenate_bt3y[0] = b_u_K_R_E_B_mDs_tmp_0;

  /* SignalConversion generated from: '<S101>/Vector Concatenate' */
  b_VectorConcatenate_bt3y[1] = b_v_K_R_E_B_mDs_tmp;

  /* End of Outputs for SubSystem: '<S44>/M_z' */

  /* SignalConversion generated from: '<S101>/Vector Concatenate' incorporates:
   *  Constant: '<S101>/Constant'
   */
  b_VectorConcatenate_bt3y[2] = 0.0;

  /* Outputs for Atomic SubSystem: '<S44>/M_z' */
  /* SignalConversion generated from: '<S101>/Vector Concatenate1' */
  b_VectorConcatenate1_fkvx[1] = b_u_K_R_E_B_mDs_tmp_0;

  /* End of Outputs for SubSystem: '<S44>/M_z' */

  /* SignalConversion generated from: '<S101>/Vector Concatenate1' incorporates:
   *  Constant: '<S101>/Constant'
   */
  b_VectorConcatenate1_fkvx[2] = 0.0;

  /* Outputs for Atomic SubSystem: '<S44>/M_z' */
  /* Gain: '<S101>/Gain' */
  b_VectorConcatenate1_fkvx[0] = -b_v_K_R_E_B_mDs_tmp;

  /* End of Outputs for SubSystem: '<S44>/M_z' */
  if (rtmIsMajorTimeStep(RMT_FDM_RT_M)) {
    /* SignalConversion generated from: '<S101>/Vector Concatenate2' incorporates:
     *  Concatenate: '<S101>/Vector Concatenate2'
     *  Constant: '<S101>/Constant'
     */
    localB->VectorConcatenate2_dkch[0] = 0.0;

    /* SignalConversion generated from: '<S101>/Vector Concatenate2' incorporates:
     *  Concatenate: '<S101>/Vector Concatenate2'
     *  Constant: '<S101>/Constant'
     */
    localB->VectorConcatenate2_dkch[1] = 0.0;

    /* Constant: '<S101>/Constant1' incorporates:
     *  Concatenate: '<S101>/Vector Concatenate2'
     */
    localB->VectorConcatenate2_dkch[2] = 1.0;
  }

  /* Concatenate: '<S101>/Vector Concatenate3' incorporates:
   *  Concatenate: '<S101>/Vector Concatenate'
   *  Concatenate: '<S101>/Vector Concatenate1'
   *  Concatenate: '<S101>/Vector Concatenate2'
   */
  for (i_3o = 0; i_3o < 3; i_3o = i_3o + 1) {
    b_VectorConcatenate_nziv[3 * i_3o] = b_VectorConcatenate_bt3y[i_3o];
  }

  for (i_3p = 0; i_3p < 3; i_3p = i_3p + 1) {
    b_VectorConcatenate_nziv[1 + 3 * i_3p] = b_VectorConcatenate1_fkvx[i_3p];
  }

  for (i_3q = 0; i_3q < 3; i_3q = i_3q + 1) {
    b_VectorConcatenate_nziv[2 + 3 * i_3q] = localB->
      VectorConcatenate2_dkch[i_3q];
  }

  /* End of Concatenate: '<S101>/Vector Concatenate3' */
  /* End of Outputs for SubSystem: '<S95>/M_z' */

  /* Product: '<S95>/Product1' incorporates:
   *  Math: '<S213>/Math Function'
   */
  for (i_3r = 0; i_3r < 3; i_3r = i_3r + 1) {
    for (i_3s = 0; i_3s < 3; i_3s = i_3s + 1) {
      b_Product1_l1hk_tmp = i_3r + 3 * i_3s;
      b_Product1_j1ks[b_Product1_l1hk_tmp] = 0.0;
      for (i_3t = 0; i_3t < 3; i_3t = i_3t + 1) {
        b_Product1_j1ks[b_Product1_l1hk_tmp] =
          b_Product1_j1ks[b_Product1_l1hk_tmp] + b_VectorConcatenate_nziv[i_3r +
          3 * i_3t] * b_M_OB_h14v_tmp[i_3t + 3 * i_3s];
      }
    }
  }

  /* End of Product: '<S95>/Product1' */

  /* Math: '<S42>/Math Function' incorporates:
   *  Product: '<S95>/Product1'
   */
  for (i_3v = 0; i_3v < 3; i_3v = i_3v + 1) {
    for (i_3u = 0; i_3u < 3; i_3u = i_3u + 1) {
      b_MathFunction_g133[i_3u + 3 * i_3v] = b_Product1_j1ks[i_3v + 3 * i_3u];
    }
  }

  /* End of Math: '<S42>/Math Function' */

  /* SignalConversion generated from: '<S375>/Vector Concatenate1' incorporates:
   *  Constant: '<S375>/Constant'
   */
  b_VectorConcatenate1_llo0[0] = 0.0;

  /* Trigonometry: '<S375>/Trigonometric Function' incorporates:
   *  Integrator: '<S12>/att_phi_rad'
   *  Trigonometry: '<S186>/Trigonometric Function1'
   *  Trigonometry: '<S186>/Trigonometric Function4'
   *  Trigonometry: '<S186>/Trigonometric Function8'
   *  Trigonometry: '<S358>/Trigonometric Function'
   */
  b_w_x_K_IB_B_radDs_tmp = cos(localX->Phi_rad);

  /* SignalConversion generated from: '<S375>/Vector Concatenate1' incorporates:
   *  Trigonometry: '<S375>/Trigonometric Function'
   */
  b_VectorConcatenate1_llo0[1] = b_w_x_K_IB_B_radDs_tmp;

  /* Trigonometry: '<S375>/Trigonometric Function1' incorporates:
   *  Integrator: '<S12>/att_phi_rad'
   *  Trigonometry: '<S186>/Trigonometric Function'
   *  Trigonometry: '<S186>/Trigonometric Function5'
   *  Trigonometry: '<S186>/Trigonometric Function6'
   *  Trigonometry: '<S358>/Trigonometric Function1'
   */
  b_w_x_K_OB_B_radDs_tmp = sin(localX->Phi_rad);

  /* SignalConversion generated from: '<S375>/Vector Concatenate1' incorporates:
   *  Trigonometry: '<S375>/Trigonometric Function1'
   */
  b_VectorConcatenate1_llo0[2] = b_w_x_K_OB_B_radDs_tmp;

  /* SignalConversion generated from: '<S375>/Vector Concatenate2' incorporates:
   *  Constant: '<S375>/Constant'
   */
  b_VectorConcatenate2_akq5[0] = 0.0;

  /* Gain: '<S375>/Gain' incorporates:
   *  Trigonometry: '<S375>/Trigonometric Function1'
   */
  b_VectorConcatenate2_akq5[1] = -b_w_x_K_OB_B_radDs_tmp;

  /* SignalConversion generated from: '<S375>/Vector Concatenate2' incorporates:
   *  Trigonometry: '<S375>/Trigonometric Function'
   */
  b_VectorConcatenate2_akq5[2] = b_w_x_K_IB_B_radDs_tmp;

  /* Trigonometry: '<S376>/Trigonometric Function' incorporates:
   *  Integrator: '<S14>/att_theta_rad'
   *  Trigonometry: '<S186>/Trigonometric Function7'
   *  Trigonometry: '<S186>/Trigonometric Function9'
   *  Trigonometry: '<S359>/Trigonometric Function'
   */
  b_w_x_K_IB_B_radDs_tmp_0 = cos(localX->Theta_rad);

  /* SignalConversion generated from: '<S376>/Vector Concatenate' incorporates:
   *  Trigonometry: '<S376>/Trigonometric Function'
   */
  b_VectorConcatenate_id0h[0] = b_w_x_K_IB_B_radDs_tmp_0;

  /* SignalConversion generated from: '<S376>/Vector Concatenate' incorporates:
   *  Constant: '<S376>/Constant'
   */
  b_VectorConcatenate_id0h[1] = 0.0;

  /* Gain: '<S376>/Gain' */
  b_VectorConcatenate_id0h[2] = -b_u_K_R_E_B_mDs_tmp;

  /* SignalConversion generated from: '<S376>/Vector Concatenate2' */
  b_VectorConcatenate2_b5g4[0] = b_u_K_R_E_B_mDs_tmp;

  /* SignalConversion generated from: '<S376>/Vector Concatenate2' incorporates:
   *  Constant: '<S376>/Constant'
   */
  b_VectorConcatenate2_b5g4[1] = 0.0;

  /* SignalConversion generated from: '<S376>/Vector Concatenate2' incorporates:
   *  Trigonometry: '<S376>/Trigonometric Function'
   */
  b_VectorConcatenate2_b5g4[2] = b_w_x_K_IB_B_radDs_tmp_0;

  /* Outputs for Atomic SubSystem: '<S44>/M_z' */
  /* SignalConversion generated from: '<S377>/Vector Concatenate' */
  b_VectorConcatenate_arer[0] = b_u_K_R_E_B_mDs_tmp_0;

  /* SignalConversion generated from: '<S377>/Vector Concatenate' */
  b_VectorConcatenate_arer[1] = b_v_K_R_E_B_mDs_tmp;

  /* End of Outputs for SubSystem: '<S44>/M_z' */

  /* SignalConversion generated from: '<S377>/Vector Concatenate' incorporates:
   *  Constant: '<S377>/Constant'
   */
  b_VectorConcatenate_arer[2] = 0.0;

  /* Outputs for Atomic SubSystem: '<S44>/M_z' */
  /* Gain: '<S377>/Gain' */
  b_VectorConcatenate1_eeyd[0] = -b_v_K_R_E_B_mDs_tmp;

  /* SignalConversion generated from: '<S377>/Vector Concatenate1' */
  b_VectorConcatenate1_eeyd[1] = b_u_K_R_E_B_mDs_tmp_0;

  /* End of Outputs for SubSystem: '<S44>/M_z' */

  /* SignalConversion generated from: '<S377>/Vector Concatenate1' incorporates:
   *  Constant: '<S377>/Constant'
   */
  b_VectorConcatenate1_eeyd[2] = 0.0;

  /* SignalConversion generated from: '<S358>/Vector Concatenate1' incorporates:
   *  Constant: '<S358>/Constant'
   */
  b_VectorConcatenate1_nxhe[0] = 0.0;

  /* SignalConversion generated from: '<S358>/Vector Concatenate1' */
  b_VectorConcatenate1_nxhe[1] = b_w_x_K_IB_B_radDs_tmp;

  /* SignalConversion generated from: '<S358>/Vector Concatenate1' */
  b_VectorConcatenate1_nxhe[2] = b_w_x_K_OB_B_radDs_tmp;

  /* SignalConversion generated from: '<S358>/Vector Concatenate2' incorporates:
   *  Constant: '<S358>/Constant'
   */
  b_VectorConcatenate2_eoub[0] = 0.0;

  /* Gain: '<S358>/Gain' */
  b_VectorConcatenate2_eoub[1] = -b_w_x_K_OB_B_radDs_tmp;

  /* SignalConversion generated from: '<S358>/Vector Concatenate2' */
  b_VectorConcatenate2_eoub[2] = b_w_x_K_IB_B_radDs_tmp;

  /* SignalConversion generated from: '<S359>/Vector Concatenate' */
  b_vel_K_R_E_O_mDs[0] = b_w_x_K_IB_B_radDs_tmp_0;

  /* SignalConversion generated from: '<S359>/Vector Concatenate' incorporates:
   *  Constant: '<S359>/Constant'
   */
  b_vel_K_R_E_O_mDs[1] = 0.0;

  /* Gain: '<S359>/Gain' */
  b_vel_K_R_E_O_mDs[2] = -b_u_K_R_E_B_mDs_tmp;

  /* SignalConversion generated from: '<S359>/Vector Concatenate2' */
  b_vel_K_R_E_O_mDs_m1dj[0] = b_u_K_R_E_B_mDs_tmp;

  /* SignalConversion generated from: '<S359>/Vector Concatenate2' incorporates:
   *  Constant: '<S359>/Constant'
   */
  b_vel_K_R_E_O_mDs_m1dj[1] = 0.0;

  /* SignalConversion generated from: '<S359>/Vector Concatenate2' */
  b_vel_K_R_E_O_mDs_m1dj[2] = b_w_x_K_IB_B_radDs_tmp_0;

  /* Outputs for Atomic SubSystem: '<S44>/M_z' */
  /* SignalConversion generated from: '<S360>/Vector Concatenate' */
  b_Reshape3_czqe[0] = b_u_K_R_E_B_mDs_tmp_0;

  /* SignalConversion generated from: '<S360>/Vector Concatenate' */
  b_Reshape3_czqe[1] = b_v_K_R_E_B_mDs_tmp;

  /* End of Outputs for SubSystem: '<S44>/M_z' */

  /* SignalConversion generated from: '<S360>/Vector Concatenate' incorporates:
   *  Constant: '<S360>/Constant'
   */
  b_Reshape3_czqe[2] = 0.0;

  /* Outputs for Atomic SubSystem: '<S44>/M_z' */
  /* Gain: '<S360>/Gain' */
  b_Product1_lodv[0] = -b_v_K_R_E_B_mDs_tmp;

  /* SignalConversion generated from: '<S360>/Vector Concatenate1' */
  b_Product1_lodv[1] = b_u_K_R_E_B_mDs_tmp_0;

  /* End of Outputs for SubSystem: '<S44>/M_z' */

  /* SignalConversion generated from: '<S360>/Vector Concatenate1' incorporates:
   *  Constant: '<S360>/Constant'
   */
  b_Product1_lodv[2] = 0.0;

  /* Concatenate: '<S359>/Vector Concatenate3' incorporates:
   *  Concatenate: '<S359>/Vector Concatenate1'
   *  Product: '<S188>/Product'
   *  Reshape: '<S188>/Reshape'
   */
  for (i_3w = 0; i_3w < 3; i_3w = i_3w + 1) {
    b_vel_K_R_E_O_mDs_1[3 * i_3w] = b_vel_K_R_E_O_mDs[i_3w];
  }

  for (i_3x = 0; i_3x < 3; i_3x = i_3x + 1) {
    b_vel_K_R_E_O_mDs_1[1 + 3 * i_3x] =
      RMT_FDM_RT_ConstB.VectorConcatenate1_hef1[i_3x];
  }

  for (i_3y = 0; i_3y < 3; i_3y = i_3y + 1) {
    b_vel_K_R_E_O_mDs_1[2 + 3 * i_3y] = b_vel_K_R_E_O_mDs_m1dj[i_3y];
  }

  /* End of Concatenate: '<S359>/Vector Concatenate3' */

  /* Concatenate: '<S360>/Vector Concatenate3' incorporates:
   *  Concatenate: '<S360>/Vector Concatenate2'
   *  Product: '<S198>/Product1'
   *  Reshape: '<S186>/Reshape3'
   */
  for (i_3z = 0; i_3z < 3; i_3z = i_3z + 1) {
    b_Reshape3_evca[3 * i_3z] = b_Reshape3_czqe[i_3z];
  }

  for (i_40 = 0; i_40 < 3; i_40 = i_40 + 1) {
    b_Reshape3_evca[1 + 3 * i_40] = b_Product1_lodv[i_40];
  }

  for (i_41 = 0; i_41 < 3; i_41 = i_41 + 1) {
    b_Reshape3_evca[2 + 3 * i_41] =
      RMT_FDM_RT_ConstB.VectorConcatenate2_akmg[i_41];
  }

  /* End of Concatenate: '<S360>/Vector Concatenate3' */

  /* Concatenate: '<S358>/Vector Concatenate3' incorporates:
   *  Concatenate: '<S358>/Vector Concatenate'
   *  Concatenate: '<S358>/Vector Concatenate1'
   *  Concatenate: '<S358>/Vector Concatenate2'
   */
  for (i_42 = 0; i_42 < 3; i_42 = i_42 + 1) {
    tmp_5[3 * i_42] = RMT_FDM_RT_ConstB.VectorConcatenate_buxv[i_42];
  }

  for (i_43 = 0; i_43 < 3; i_43 = i_43 + 1) {
    tmp_5[1 + 3 * i_43] = b_VectorConcatenate1_nxhe[i_43];
  }

  for (i_44 = 0; i_44 < 3; i_44 = i_44 + 1) {
    tmp_5[2 + 3 * i_44] = b_VectorConcatenate2_eoub[i_44];
  }

  /* End of Concatenate: '<S358>/Vector Concatenate3' */

  /* Product: '<S357>/Product10' */
  for (i_45 = 0; i_45 < 3; i_45 = i_45 + 1) {
    for (i_46 = 0; i_46 < 3; i_46 = i_46 + 1) {
      b_vel_K_R_E_O_mDs_tmp = i_45 + 3 * i_46;
      b_vel_K_R_E_O_mDs_2[b_vel_K_R_E_O_mDs_tmp] = 0.0;
      for (i_47 = 0; i_47 < 3; i_47 = i_47 + 1) {
        b_vel_K_R_E_O_mDs_2[b_vel_K_R_E_O_mDs_tmp] =
          b_vel_K_R_E_O_mDs_2[b_vel_K_R_E_O_mDs_tmp] + b_vel_K_R_E_O_mDs_1[i_45
          + 3 * i_47] * b_Reshape3_evca[i_47 + 3 * i_46];
      }
    }
  }

  /* Math: '<S344>/Math Function' incorporates:
   *  Product: '<S357>/Product10'
   */
  for (i_48 = 0; i_48 < 3; i_48 = i_48 + 1) {
    for (i_49 = 0; i_49 < 3; i_49 = i_49 + 1) {
      b_M_OB_ckuz_tmp = i_48 + 3 * i_49;
      b_M_OB_k2bs[b_M_OB_ckuz_tmp] = 0.0;
      for (i_4a = 0; i_4a < 3; i_4a = i_4a + 1) {
        b_M_OB_k2bs[b_M_OB_ckuz_tmp] = b_M_OB_k2bs[b_M_OB_ckuz_tmp] + tmp_5[i_49
          + 3 * i_4a] * b_vel_K_R_E_O_mDs_2[i_4a + 3 * i_48];
      }
    }
  }

  /* End of Math: '<S344>/Math Function' */

  /* SignalConversion generated from: '<S186>/Vector Concatenate' incorporates:
   *  Constant: '<S186>/Constant1'
   */
  b_Product2_fd4p[0] = 1.0;

  /* Trigonometry: '<S186>/Trigonometric Function2' incorporates:
   *  Integrator: '<S14>/att_theta_rad'
   *  Trigonometry: '<S186>/Trigonometric Function3'
   */
  b_Product2_mkuz_tmp = tan(localX->Theta_rad);

  /* Product: '<S186>/Product' incorporates:
   *  Trigonometry: '<S186>/Trigonometric Function2'
   */
  b_Product2_fd4p[1] = b_w_x_K_OB_B_radDs_tmp * b_Product2_mkuz_tmp;

  /* Product: '<S186>/Product1' */
  b_Product2_fd4p[2] = b_w_x_K_IB_B_radDs_tmp * b_Product2_mkuz_tmp;

  /* SignalConversion generated from: '<S186>/Vector Concatenate1' incorporates:
   *  Constant: '<S186>/Constant2'
   */
  b_Reshape_jgsm[0] = 0.0;

  /* Trigonometry: '<S186>/Trigonometric Function4' */
  b_Reshape_jgsm[1] = b_w_x_K_IB_B_radDs_tmp;

  /* Gain: '<S186>/Gain' */
  b_Reshape_jgsm[2] = -b_w_x_K_OB_B_radDs_tmp;

  /* SignalConversion generated from: '<S186>/Vector Concatenate2' incorporates:
   *  Constant: '<S186>/Constant3'
   */
  b_Reshape_j1uf[0] = 0.0;

  /* Product: '<S186>/Divide' */
  b_Reshape_j1uf[1] = b_w_x_K_OB_B_radDs_tmp / b_w_x_K_IB_B_radDs_tmp_0;

  /* Product: '<S186>/Divide1' */
  b_Reshape_j1uf[2] = b_w_x_K_IB_B_radDs_tmp / b_w_x_K_IB_B_radDs_tmp_0;

  /* Concatenate: '<S186>/Matrix Concatenate' incorporates:
   *  Product: '<S198>/Product2'
   *  Reshape: '<S186>/Reshape'
   *  Reshape: '<S186>/Reshape1'
   *  Reshape: '<S186>/Reshape2'
   *  Reshape: '<S187>/Reshape'
   *  Reshape: '<S33>/Reshape'
   */
  for (i_4b = 0; i_4b < 3; i_4b = i_4b + 1) {
    b_MatrixConcatenate[3 * i_4b] = b_Product2_fd4p[i_4b];
  }

  for (i_4c = 0; i_4c < 3; i_4c = i_4c + 1) {
    b_MatrixConcatenate[1 + 3 * i_4c] = b_Reshape_jgsm[i_4c];
  }

  for (i_4d = 0; i_4d < 3; i_4d = i_4d + 1) {
    b_MatrixConcatenate[2 + 3 * i_4d] = b_Reshape_j1uf[i_4d];
  }

  /* End of Concatenate: '<S186>/Matrix Concatenate' */

  /* Trigonometry: '<S219>/Trigonometric Function1' */
  b_w_x_K_IB_B_radDs = cos(*rtu_External_Inputs_Navigation_Frame_psi_0_rad);

  /* SignalConversion generated from: '<S219>/Vector Concatenate' */
  b_MatrixConcaenate[0] = b_w_x_K_IB_B_radDs;

  /* Trigonometry: '<S219>/Trigonometric Function' */
  b_w_x_K_OB_B_radDs = sin(*rtu_External_Inputs_Navigation_Frame_psi_0_rad);

  /* Gain: '<S219>/Gain' */
  b_MatrixConcaenate[1] = -b_w_x_K_OB_B_radDs;

  /* SignalConversion generated from: '<S219>/Vector Concatenate' incorporates:
   *  Constant: '<S219>/Constant1'
   */
  b_MatrixConcaenate[2] = 0.0;

  /* SignalConversion generated from: '<S219>/Vector Concatenate1' */
  b_MatrixConcaenate[3] = b_w_x_K_OB_B_radDs;

  /* SignalConversion generated from: '<S219>/Vector Concatenate1' */
  b_MatrixConcaenate[4] = b_w_x_K_IB_B_radDs;

  /* SignalConversion generated from: '<S219>/Vector Concatenate1' incorporates:
   *  Constant: '<S219>/Constant1'
   */
  b_MatrixConcaenate[5] = 0.0;

  /* SignalConversion generated from: '<S219>/Matrix Concaenate' incorporates:
   *  Concatenate: '<S219>/Vector Concatenate2'
   */
  for (i_9 = 0; i_9 < 3; i_9 = i_9 + 1) {
    b_MatrixConcaenate[i_9 + 6] = RMT_FDM_RT_ConstB.VectorConcatenate2_pkka[i_9];
  }

  /* End of SignalConversion generated from: '<S219>/Matrix Concaenate' */

  /* Integrator: '<S238>/w_z_int_PRot_P_err_radDs' incorporates:
   *  Constant: '<S236>/Constant2'
   */
  if (rtsiIsModeUpdateTimeStep(RMT_FDM_RT_M->solverInfo)) {
    zcEvent = rt_ZCFcn(RISING_ZERO_CROSSING,
                       &localZCE->w_z_int_PRot_P_err_radDs_Reset_ZCE,
                       (1.0));

    /* evaluate zero-crossings */
    if ((zcEvent != NO_ZCEVENT) || localDW->w_z_int_PRot_P_err_radDs_DWORK1) {
      for (i_a = 0; i_a < 3; i_a = i_a + 1) {
        localX->w_z_int_PRot_P_err_radDs[i_a] = RMT_FDM_RT_ConstB.Constant3_kfn3;
      }
    }
  }

  if (rtmIsMajorTimeStep(RMT_FDM_RT_M)) {
    /* RandomNumber: '<S228>/Random Number2' incorporates:
     *  RandomNumber: '<S316>/Random Number2'
     */
    for (iU = 0; iU < 3; iU = iU + 1) {
      b_RandomNumber2_ouvm[iU] = localDW->NextOutput[iU];
    }

    /* End of RandomNumber: '<S228>/Random Number2' */
    for (i_4e = 0; i_4e < 3; i_4e = i_4e + 1) {
      /* Gain: '<S228>/Gain' incorporates:
       *  RandomNumber: '<S316>/Random Number2'
       */
      localB->Gain[i_4e] = 0.0;
      for (i_4f = 0; i_4f < 3; i_4f = i_4f + 1) {
        localB->Gain[i_4e] = localB->Gain[i_4e] + rtCP_Gain_Gain_h24a[i_4e + 3 *
          i_4f] * b_RandomNumber2_ouvm[i_4f];
      }
    }
  }

  /* SignalConversion generated from: '<S230>/Vector Concatenate' incorporates:
   *  Integrator: '<S12>/att_phi_rad'
   */
  b_Sum_hhfg[0] = localX->Phi_rad;

  /* SignalConversion generated from: '<S230>/Vector Concatenate' incorporates:
   *  Integrator: '<S14>/att_theta_rad'
   */
  b_Sum_hhfg[1] = localX->Theta_rad;

  /* SignalConversion generated from: '<S230>/Vector Concatenate' incorporates:
   *  Integrator: '<S13>/att_psi_rad'
   */
  b_Sum_hhfg[2] = localX->Psi_rad;

  /* Reshape: '<S230>/Reshape' */
  for (i_b = 0; i_b < 3; i_b = i_b + 1) {
    b_Reshape[i_b] = b_Sum_hhfg[i_b];
  }

  /* Switch: '<S232>/Switch' incorporates:
   *  Gain: '<S228>/Gain'
   *  Reshape: '<S230>/Reshape'
   *  Sum: '<S228>/Add'
   */
  if (rtu_Simulation_Control->flg_Enable_Sensor_Errors) {
    for (i_c = 0; i_c < 3; i_c = i_c + 1) {
      /* Integrator: '<S238>/w_z_int_PRot_P_err_radDs' */
      u0 = localX->w_z_int_PRot_P_err_radDs[i_c];

      /* Saturate: '<S228>/Saturation' */
      if (u0 > 5.2359877559829888) {
        y = 5.2359877559829888;
      } else if (u0 < -5.2359877559829888) {
        y = -5.2359877559829888;
      } else {
        y = u0;
      }

      /* End of Saturate: '<S228>/Saturation' */
      b_Switch[i_c] = y + localB->Gain[i_c];
    }
  } else {
    for (i_26 = 0; i_26 < 3; i_26 = i_26 + 1) {
      b_Switch[i_26] = b_Sum_hhfg[i_26];
    }
  }

  /* End of Switch: '<S232>/Switch' */

  /* Outputs for Atomic SubSystem: '<S239>/M_x' */
  if (rtmIsMajorTimeStep(RMT_FDM_RT_M)) {
    /* SignalConversion generated from: '<S240>/Vector Concatenate' incorporates:
     *  Concatenate: '<S240>/Vector Concatenate'
     *  Constant: '<S240>/Constant'
     */
    localB->VectorConcatenate_mpoo[1] = 0.0;

    /* SignalConversion generated from: '<S240>/Vector Concatenate' incorporates:
     *  Concatenate: '<S240>/Vector Concatenate'
     *  Constant: '<S240>/Constant'
     */
    localB->VectorConcatenate_mpoo[2] = 0.0;

    /* Constant: '<S240>/Constant1' incorporates:
     *  Concatenate: '<S240>/Vector Concatenate'
     */
    localB->VectorConcatenate_mpoo[0] = 1.0;
  }

  /* SignalConversion generated from: '<S240>/Vector Concatenate1' incorporates:
   *  Constant: '<S240>/Constant'
   */
  b_VectorConcatenate1_nze2[0] = 0.0;

  /* Trigonometry: '<S240>/Trigonometric Function' */
  b_TrigonometricFunction_lzfd = cos(b_Switch[0]);

  /* SignalConversion generated from: '<S240>/Vector Concatenate1' */
  b_VectorConcatenate1_nze2[1] = b_TrigonometricFunction_lzfd;

  /* Trigonometry: '<S240>/Trigonometric Function1' */
  b_TrigonometricFunction1_g1qe = sin(b_Switch[0]);

  /* SignalConversion generated from: '<S240>/Vector Concatenate1' */
  b_VectorConcatenate1_nze2[2] = b_TrigonometricFunction1_g1qe;

  /* SignalConversion generated from: '<S240>/Vector Concatenate2' incorporates:
   *  Constant: '<S240>/Constant'
   */
  b_VectorConcatenate2_a0rr[0] = 0.0;

  /* SignalConversion generated from: '<S240>/Vector Concatenate2' */
  b_VectorConcatenate2_a0rr[2] = b_TrigonometricFunction_lzfd;

  /* Gain: '<S240>/Gain' */
  b_VectorConcatenate2_a0rr[1] = -b_TrigonometricFunction1_g1qe;

  /* End of Outputs for SubSystem: '<S239>/M_x' */

  /* Outputs for Atomic SubSystem: '<S239>/M_y' */
  /* Trigonometry: '<S241>/Trigonometric Function' */
  b_TrigonometricFunction_n3xf = cos(b_Switch[1]);

  /* SignalConversion generated from: '<S241>/Vector Concatenate' */
  b_VectorConcatenate_l4yq[0] = b_TrigonometricFunction_n3xf;

  /* SignalConversion generated from: '<S241>/Vector Concatenate' incorporates:
   *  Constant: '<S241>/Constant'
   */
  b_VectorConcatenate_l4yq[1] = 0.0;

  /* Trigonometry: '<S241>/Trigonometric Function1' */
  b_TrigonometricFunction1_g4q5 = sin(b_Switch[1]);

  /* Gain: '<S241>/Gain' */
  b_VectorConcatenate_l4yq[2] = -b_TrigonometricFunction1_g4q5;
  if (rtmIsMajorTimeStep(RMT_FDM_RT_M)) {
    /* SignalConversion generated from: '<S241>/Vector Concatenate1' incorporates:
     *  Concatenate: '<S241>/Vector Concatenate1'
     *  Constant: '<S241>/Constant'
     */
    localB->VectorConcatenate1_hi5s[0] = 0.0;

    /* SignalConversion generated from: '<S241>/Vector Concatenate1' incorporates:
     *  Concatenate: '<S241>/Vector Concatenate1'
     *  Constant: '<S241>/Constant'
     */
    localB->VectorConcatenate1_hi5s[2] = 0.0;

    /* Constant: '<S241>/Constant1' incorporates:
     *  Concatenate: '<S241>/Vector Concatenate1'
     */
    localB->VectorConcatenate1_hi5s[1] = 1.0;
  }

  /* SignalConversion generated from: '<S241>/Vector Concatenate2' */
  b_VectorConcatenate2_pfo0[0] = b_TrigonometricFunction1_g4q5;

  /* SignalConversion generated from: '<S241>/Vector Concatenate2' incorporates:
   *  Constant: '<S241>/Constant'
   */
  b_VectorConcatenate2_pfo0[1] = 0.0;

  /* SignalConversion generated from: '<S241>/Vector Concatenate2' */
  b_VectorConcatenate2_pfo0[2] = b_TrigonometricFunction_n3xf;

  /* End of Outputs for SubSystem: '<S239>/M_y' */

  /* Outputs for Atomic SubSystem: '<S239>/M_z' */
  /* Trigonometry: '<S242>/Trigonometric Function' */
  b_TrigonometricFunction_fw5d = cos(b_Switch[2]);

  /* SignalConversion generated from: '<S242>/Vector Concatenate' */
  b_VectorConcatenate_nsr3[0] = b_TrigonometricFunction_fw5d;

  /* Trigonometry: '<S242>/Trigonometric Function1' */
  b_TrigonometricFunction1_ihsx = sin(b_Switch[2]);

  /* SignalConversion generated from: '<S242>/Vector Concatenate' */
  b_VectorConcatenate_nsr3[1] = b_TrigonometricFunction1_ihsx;

  /* SignalConversion generated from: '<S242>/Vector Concatenate' incorporates:
   *  Constant: '<S242>/Constant'
   */
  b_VectorConcatenate_nsr3[2] = 0.0;

  /* SignalConversion generated from: '<S242>/Vector Concatenate1' */
  b_VectorConcatenate1_ahwu[1] = b_TrigonometricFunction_fw5d;

  /* SignalConversion generated from: '<S242>/Vector Concatenate1' incorporates:
   *  Constant: '<S242>/Constant'
   */
  b_VectorConcatenate1_ahwu[2] = 0.0;

  /* Gain: '<S242>/Gain' */
  b_VectorConcatenate1_ahwu[0] = -b_TrigonometricFunction1_ihsx;
  if (rtmIsMajorTimeStep(RMT_FDM_RT_M)) {
    /* SignalConversion generated from: '<S242>/Vector Concatenate2' incorporates:
     *  Concatenate: '<S242>/Vector Concatenate2'
     *  Constant: '<S242>/Constant'
     */
    localB->VectorConcatenate2[0] = 0.0;

    /* SignalConversion generated from: '<S242>/Vector Concatenate2' incorporates:
     *  Concatenate: '<S242>/Vector Concatenate2'
     *  Constant: '<S242>/Constant'
     */
    localB->VectorConcatenate2[1] = 0.0;

    /* Constant: '<S242>/Constant1' incorporates:
     *  Concatenate: '<S242>/Vector Concatenate2'
     */
    localB->VectorConcatenate2[2] = 1.0;
  }

  /* End of Outputs for SubSystem: '<S239>/M_z' */

  /* Outputs for Atomic SubSystem: '<S239>/M_y' */
  /* Concatenate: '<S241>/Vector Concatenate3' incorporates:
   *  Concatenate: '<S241>/Vector Concatenate'
   *  Concatenate: '<S241>/Vector Concatenate1'
   *  Concatenate: '<S241>/Vector Concatenate2'
   */
  for (i_4g = 0; i_4g < 3; i_4g = i_4g + 1) {
    b_VectorConcatenate_jnc0[3 * i_4g] = b_VectorConcatenate_l4yq[i_4g];
  }

  for (i_4h = 0; i_4h < 3; i_4h = i_4h + 1) {
    b_VectorConcatenate_jnc0[1 + 3 * i_4h] = localB->
      VectorConcatenate1_hi5s[i_4h];
  }

  for (i_4i = 0; i_4i < 3; i_4i = i_4i + 1) {
    b_VectorConcatenate_jnc0[2 + 3 * i_4i] = b_VectorConcatenate2_pfo0[i_4i];
  }

  /* End of Concatenate: '<S241>/Vector Concatenate3' */
  /* End of Outputs for SubSystem: '<S239>/M_y' */

  /* Outputs for Atomic SubSystem: '<S239>/M_z' */
  /* Concatenate: '<S242>/Vector Concatenate3' incorporates:
   *  Concatenate: '<S242>/Vector Concatenate'
   *  Concatenate: '<S242>/Vector Concatenate1'
   *  Concatenate: '<S242>/Vector Concatenate2'
   */
  for (i_4j = 0; i_4j < 3; i_4j = i_4j + 1) {
    b_VectorConcatenate_hkqf[3 * i_4j] = b_VectorConcatenate_nsr3[i_4j];
  }

  for (i_4k = 0; i_4k < 3; i_4k = i_4k + 1) {
    b_VectorConcatenate_hkqf[1 + 3 * i_4k] = b_VectorConcatenate1_ahwu[i_4k];
  }

  for (i_4l = 0; i_4l < 3; i_4l = i_4l + 1) {
    b_VectorConcatenate_hkqf[2 + 3 * i_4l] = localB->VectorConcatenate2[i_4l];
  }

  /* End of Concatenate: '<S242>/Vector Concatenate3' */
  /* End of Outputs for SubSystem: '<S239>/M_z' */

  /* Outputs for Atomic SubSystem: '<S239>/M_x' */
  /* Concatenate: '<S240>/Vector Concatenate3' incorporates:
   *  Concatenate: '<S240>/Vector Concatenate'
   *  Concatenate: '<S240>/Vector Concatenate1'
   *  Concatenate: '<S240>/Vector Concatenate2'
   */
  for (i_4m = 0; i_4m < 3; i_4m = i_4m + 1) {
    tmp_6[3 * i_4m] = localB->VectorConcatenate_mpoo[i_4m];
  }

  for (i_4n = 0; i_4n < 3; i_4n = i_4n + 1) {
    tmp_6[1 + 3 * i_4n] = b_VectorConcatenate1_nze2[i_4n];
  }

  for (i_4o = 0; i_4o < 3; i_4o = i_4o + 1) {
    tmp_6[2 + 3 * i_4o] = b_VectorConcatenate2_a0rr[i_4o];
  }

  /* End of Concatenate: '<S240>/Vector Concatenate3' */
  /* End of Outputs for SubSystem: '<S239>/M_x' */

  /* Product: '<S239>/Product10' */
  for (i_4p = 0; i_4p < 3; i_4p = i_4p + 1) {
    for (i_4q = 0; i_4q < 3; i_4q = i_4q + 1) {
      b_VectorConcatenate_jnc0_tmp = i_4p + 3 * i_4q;
      b_VectorConcatenate_jnc0_0[b_VectorConcatenate_jnc0_tmp] = 0.0;
      for (i_4r = 0; i_4r < 3; i_4r = i_4r + 1) {
        b_VectorConcatenate_jnc0_0[b_VectorConcatenate_jnc0_tmp] =
          b_VectorConcatenate_jnc0_0[b_VectorConcatenate_jnc0_tmp] +
          b_VectorConcatenate_jnc0[i_4p + 3 * i_4r] *
          b_VectorConcatenate_hkqf[i_4r + 3 * i_4q];
      }
    }
  }

  for (i_4s = 0; i_4s < 3; i_4s = i_4s + 1) {
    for (i_4t = 0; i_4t < 3; i_4t = i_4t + 1) {
      b_Product10_dtl1_tmp = i_4s + 3 * i_4t;
      b_Product10_pps0[b_Product10_dtl1_tmp] = 0.0;
      for (i_4u = 0; i_4u < 3; i_4u = i_4u + 1) {
        b_Product10_pps0[b_Product10_dtl1_tmp] =
          b_Product10_pps0[b_Product10_dtl1_tmp] + tmp_6[i_4s + 3 * i_4u] *
          b_VectorConcatenate_jnc0_0[i_4u + 3 * i_4t];
      }
    }
  }

  /* End of Product: '<S239>/Product10' */

  /* Math: '<S229>/Math Function' incorporates:
   *  Product: '<S239>/Product10'
   */
  for (i_4w = 0; i_4w < 3; i_4w = i_4w + 1) {
    for (i_4v = 0; i_4v < 3; i_4v = i_4v + 1) {
      rty_Measurements->ahrs_meas.M_OB_meas[i_4v + 3 * i_4w] =
        b_Product10_pps0[i_4w + 3 * i_4v];
    }
  }

  /* End of Math: '<S229>/Math Function' */

  /* SignalConversion generated from: '<S205>/Vector Concatenate' */
  b_MatrixConcaenate_a1h4[0] = b_w_y_K_IB_B_radDs_tmp;

  /* SignalConversion generated from: '<S205>/Vector Concatenate' incorporates:
   *  Constant: '<S205>/Constant1'
   */
  b_MatrixConcaenate_a1h4[1] = 0.0;

  /* SignalConversion generated from: '<S205>/Vector Concatenate' */
  b_MatrixConcaenate_a1h4[2] = b_TrigonometricFunction1_pesf_tmp;

  /* SignalConversion generated from: '<S205>/Matrix Concaenate' incorporates:
   *  Concatenate: '<S205>/Vector Concatenate1'
   */
  for (i_d = 0; i_d < 3; i_d = i_d + 1) {
    b_MatrixConcaenate_a1h4[i_d + 3] =
      RMT_FDM_RT_ConstB.VectorConcatenate1_cp35[i_d];
  }

  /* End of SignalConversion generated from: '<S205>/Matrix Concaenate' */

  /* Gain: '<S205>/Gain' */
  b_MatrixConcaenate_a1h4[6] = -b_TrigonometricFunction1_pesf_tmp;

  /* SignalConversion generated from: '<S205>/Vector Concatenate2' incorporates:
   *  Constant: '<S205>/Constant1'
   */
  b_MatrixConcaenate_a1h4[7] = 0.0;

  /* SignalConversion generated from: '<S205>/Vector Concatenate2' */
  b_MatrixConcaenate_a1h4[8] = b_w_y_K_IB_B_radDs_tmp;

  /* Math: '<S196>/Math Function4' incorporates:
   *  Concatenate: '<S205>/Matrix Concaenate'
   */
  for (i_4y = 0; i_4y < 3; i_4y = i_4y + 1) {
    for (i_4x = 0; i_4x < 3; i_4x = i_4x + 1) {
      b_M_SB[i_4x + 3 * i_4y] = b_MatrixConcaenate_a1h4[i_4y + 3 * i_4x];
    }
  }

  /* End of Math: '<S196>/Math Function4' */

  /* SignalConversion generated from: '<S1>/Vector Concatenate' incorporates:
   *  Concatenate: '<S1>/Vector Concatenate'
   */
  localB->VectorConcatenate[0] = rtu_Controller_Commands->w1_cmd_radDs;

  /* SignalConversion generated from: '<S1>/Vector Concatenate' incorporates:
   *  Concatenate: '<S1>/Vector Concatenate'
   */
  localB->VectorConcatenate[1] = rtu_Controller_Commands->w2_cmd_radDs;

  /* SignalConversion generated from: '<S1>/Vector Concatenate' incorporates:
   *  Concatenate: '<S1>/Vector Concatenate'
   */
  localB->VectorConcatenate[2] = rtu_Controller_Commands->w3_cmd_radDs;

  /* SignalConversion generated from: '<S1>/Vector Concatenate' incorporates:
   *  Concatenate: '<S1>/Vector Concatenate'
   */
  localB->VectorConcatenate[3] = rtu_Controller_Commands->w4_cmd_radDs;

  /* SignalConversion generated from: '<S1>/Vector Concatenate' incorporates:
   *  Concatenate: '<S1>/Vector Concatenate'
   */
  localB->VectorConcatenate[4] = rtu_Controller_Commands->w5_cmd_radDs;

  /* SignalConversion generated from: '<S1>/Vector Concatenate' incorporates:
   *  Concatenate: '<S1>/Vector Concatenate'
   */
  localB->VectorConcatenate[5] = rtu_Controller_Commands->w6_cmd_radDs;

  /* SignalConversion generated from: '<S1>/Vector Concatenate' incorporates:
   *  Concatenate: '<S1>/Vector Concatenate'
   */
  localB->VectorConcatenate[6] = rtu_Controller_Commands->w7_cmd_radDs;

  /* SignalConversion generated from: '<S1>/Vector Concatenate' incorporates:
   *  Concatenate: '<S1>/Vector Concatenate'
   */
  localB->VectorConcatenate[7] = rtu_Controller_Commands->w8_cmd_radDs;

  /* Outputs for Iterator SubSystem: '<S1>/Actuator_Ext_Reset' incorporates:
   *  ForEach: '<S5>/For Each'
   */
  for (ForEach_itr_gq2o = 0; ForEach_itr_gq2o < 8; ForEach_itr_gq2o =
       ForEach_itr_gq2o + 1) {
    /* Integrator: '<S5>/Integrator' incorporates:
     *  ForEachSliceSelector generated from: '<S5>/u0_radDs'
     */
    /* Limited  Integrator  */
    if (rtsiIsModeUpdateTimeStep(RMT_FDM_RT_M->solverInfo)) {
      didZcEventOccur_b = (rtu_Simulation_Control->flg_Reset &&
                           (localZCE->CoreSubsys[ForEach_itr_gq2o].
                            Integrator_Reset_ZCE != POS_ZCSIG));
      localZCE->CoreSubsys[ForEach_itr_gq2o].Integrator_Reset_ZCE = (uint8_T)
        rtu_Simulation_Control->flg_Reset;

      /* evaluate zero-crossings */
      if (didZcEventOccur_b || localDW->CoreSubsys[ForEach_itr_gq2o].
          Integrator_DWORK1) {
        localX->CoreSubsys[ForEach_itr_gq2o].w_act_radDs =
          rtu_States_Init->actuator.u_0_radDs[ForEach_itr_gq2o];
      }
    }

    if (localX->CoreSubsys[ForEach_itr_gq2o].w_act_radDs >= 2712.0) {
      localX->CoreSubsys[ForEach_itr_gq2o].w_act_radDs = 2712.0;
    } else if (localX->CoreSubsys[ForEach_itr_gq2o].w_act_radDs <= 0.0) {
      localX->CoreSubsys[ForEach_itr_gq2o].w_act_radDs = 0.0;
    }

    /* Gain: '<S5>/Gain' incorporates:
     *  Concatenate: '<S1>/Vector Concatenate'
     *  DataTypeConversion: '<S5>/Data Type Conversion'
     *  ForEachSliceSelector generated from: '<S5>/w_cmd_radDs'
     *  Integrator: '<S5>/Integrator'
     *  Product: '<S5>/Product'
     *  Sum: '<S5>/Subtract'
     */
    localB->CoreSubsys[ForEach_itr_gq2o].w_act_dot_radDs2 = 100.0 * ((real_T)
      rtu_Simulation_Control->flg_Run * (localB->
      VectorConcatenate[ForEach_itr_gq2o] - localX->CoreSubsys[ForEach_itr_gq2o]
      .w_act_radDs));

    /* Sum: '<S5>/Sum' incorporates:
     *  Constant: '<S5>/Constant'
     *  ForEachSliceSelector generated from: '<S5>/motor_loss'
     */
    u0_0 = 1.0 - rtu_Failures->motor_loss[ForEach_itr_gq2o];

    /* Saturate: '<S5>/Saturation' */
    if (u0_0 > 1.0) {
      y_0 = 1.0;
    } else if (u0_0 < 0.0) {
      y_0 = 0.0;
    } else {
      y_0 = u0_0;
    }

    /* End of Saturate: '<S5>/Saturation' */

    /* ForEachSliceAssignment generated from: '<S5>/w_act_radDs' incorporates:
     *  Integrator: '<S5>/Integrator'
     *  Product: '<S5>/Product1'
     */
    b_ImpAsg_InsertedFor_w_act_radDs_at_inport_0[ForEach_itr_gq2o] = y_0 *
      localX->CoreSubsys[ForEach_itr_gq2o].w_act_radDs;
  }

  /* End of Outputs for SubSystem: '<S1>/Actuator_Ext_Reset' */

  /* SignalConversion generated from: '<S33>/Vector Concatenate' incorporates:
   *  Reshape: '<S33>/Reshape4'
   */
  memcpy(&localB->Reshape4[0], &b_ImpAsg_InsertedFor_w_act_radDs_at_inport_0[0],
         8U * sizeof(real_T));

  /* SignalConversion generated from: '<S33>/Vector Concatenate1' incorporates:
   *  Reshape: '<S199>/Reshape2'
   *  Sum: '<S199>/Subtract'
   */
  b_Reshape2_ksra[0] = b_Subtract_kaxz[0];

  /* SignalConversion generated from: '<S33>/Vector Concatenate1' incorporates:
   *  Reshape: '<S199>/Reshape2'
   *  Sum: '<S199>/Subtract'
   */
  b_Reshape2_ksra[1] = b_Subtract_kaxz[1];

  /* SignalConversion generated from: '<S33>/Vector Concatenate1' incorporates:
   *  Reshape: '<S199>/Reshape2'
   *  Sum: '<S199>/Subtract'
   */
  b_Reshape2_ksra[2] = b_Subtract_kaxz[2];

  /* Integrator: '<S18>/rot_x_K_IB_B_radDs' incorporates:
   *  Integrator: '<S19>/rot_y_K_IB_B_radDs'
   *  Integrator: '<S20>/rot_z_K_IB_B_radDs'
   */
  if (rtsiIsModeUpdateTimeStep(RMT_FDM_RT_M->solverInfo)) {
    didZcEventOccur_5 = (rtu_Simulation_Control->flg_Reset &&
                         (localZCE->rot_x_K_IB_B_radDs_Reset_ZCE != POS_ZCSIG));
    localZCE->rot_x_K_IB_B_radDs_Reset_ZCE = (uint8_T)
      rtu_Simulation_Control->flg_Reset;

    /* evaluate zero-crossings */
    if (didZcEventOccur_5 || localDW->rot_x_K_IB_B_radDs_DWORK1) {
      localX->w_x_K_IB_B_radDs =
        rtu_States_Init->rot_K_IB_B_radDs.w_x_K_IB_B_radDs;
    }

    didZcEventOccur_6 = (rtu_Simulation_Control->flg_Reset &&
                         (localZCE->rot_y_K_IB_B_radDs_Reset_ZCE != POS_ZCSIG));
    localZCE->rot_y_K_IB_B_radDs_Reset_ZCE = (uint8_T)
      rtu_Simulation_Control->flg_Reset;

    /* evaluate zero-crossings */
    if (didZcEventOccur_6 || localDW->rot_y_K_IB_B_radDs_DWORK1) {
      localX->w_y_K_IB_B_radDs =
        rtu_States_Init->rot_K_IB_B_radDs.w_y_K_IB_B_radDs;
    }

    didZcEventOccur_7 = (rtu_Simulation_Control->flg_Reset &&
                         (localZCE->rot_z_K_IB_B_radDs_Reset_ZCE != POS_ZCSIG));
    localZCE->rot_z_K_IB_B_radDs_Reset_ZCE = (uint8_T)
      rtu_Simulation_Control->flg_Reset;

    /* evaluate zero-crossings */
    if (didZcEventOccur_7 || localDW->rot_z_K_IB_B_radDs_DWORK1) {
      localX->w_z_K_IB_B_radDs =
        rtu_States_Init->rot_K_IB_B_radDs.w_z_K_IB_B_radDs;
    }
  }

  /* SignalConversion generated from: '<S198>/Vector Concatenate' incorporates:
   *  Integrator: '<S18>/rot_x_K_IB_B_radDs'
   */
  b_Reshape2_jvfy[0] = localX->w_x_K_IB_B_radDs;

  /* SignalConversion generated from: '<S198>/Vector Concatenate' incorporates:
   *  Integrator: '<S19>/rot_y_K_IB_B_radDs'
   */
  b_Reshape2_jvfy[1] = localX->w_y_K_IB_B_radDs;

  /* SignalConversion generated from: '<S198>/Vector Concatenate' incorporates:
   *  Integrator: '<S20>/rot_z_K_IB_B_radDs'
   */
  b_Reshape2_jvfy[2] = localX->w_z_K_IB_B_radDs;

  /* SignalConversion generated from: '<S198>/Vector Concatenate1' */
  b_Reshape1_ejex[0] =
    *rtu_External_Inputs_Wind_Data_rot_W_OW_B_radDs_w_x_W_OW_B_radDs;

  /* SignalConversion generated from: '<S198>/Vector Concatenate1' */
  b_Reshape1_ejex[1] =
    *rtu_External_Inputs_Wind_Data_rot_W_OW_B_radDs_w_y_W_OW_B_radDs;

  /* SignalConversion generated from: '<S198>/Vector Concatenate1' */
  b_Reshape1_ejex[2] =
    *rtu_External_Inputs_Wind_Data_rot_W_OW_B_radDs_w_z_W_OW_B_radDs;

  /* Sum: '<S198>/Subtract' incorporates:
   *  Reshape: '<S187>/Reshape1'
   *  Reshape: '<S198>/Reshape'
   *  Reshape: '<S198>/Reshape1'
   */
  for (i_4z = 0; i_4z < 3; i_4z = i_4z + 1) {
    b_Reshape1_ejex[i_4z] = b_Reshape2_jvfy[i_4z] - b_Reshape1_ejex[i_4z];
  }

  /* End of Sum: '<S198>/Subtract' */

  /* Reshape: '<S198>/Reshape2' incorporates:
   *  Reshape: '<S187>/Reshape1'
   */
  for (i_e = 0; i_e < 3; i_e = i_e + 1) {
    b_Reshape2_jvfy[i_e] = b_Reshape1_ejex[i_e];
  }

  /* SignalConversion generated from: '<S33>/Vector Concatenate2' incorporates:
   *  Reshape: '<S187>/Reshape1'
   *  Reshape: '<S198>/Reshape2'
   */
  b_for_G_R_B_N_aifj[0] = b_Reshape1_ejex[0];

  /* SignalConversion generated from: '<S33>/Vector Concatenate2' incorporates:
   *  Reshape: '<S187>/Reshape1'
   *  Reshape: '<S198>/Reshape2'
   */
  b_for_G_R_B_N_aifj[1] = b_Reshape1_ejex[1];

  /* SignalConversion generated from: '<S33>/Vector Concatenate2' incorporates:
   *  Reshape: '<S187>/Reshape1'
   *  Reshape: '<S198>/Reshape2'
   */
  b_for_G_R_B_N_aifj[2] = b_Reshape1_ejex[2];

  /* Integrator: '<S17>/pos_z' */
  if (rtsiIsModeUpdateTimeStep(RMT_FDM_RT_M->solverInfo)) {
    didZcEventOccur_8 = (rtu_Simulation_Control->flg_Reset &&
                         (localZCE->pos_z_Reset_ZCE != POS_ZCSIG));
    localZCE->pos_z_Reset_ZCE = (uint8_T)rtu_Simulation_Control->flg_Reset;

    /* evaluate zero-crossings */
    if (didZcEventOccur_8 || localDW->pos_z_DWORK1) {
      localX->z_R_O_m = rtu_States_Init->pos_R_O_m.z_R_O_m;
    }
  }

  /* Saturate: '<S185>/Limit  altitude  to troposhere' incorporates:
   *  Gain: '<S182>/Gain'
   *  Integrator: '<S17>/pos_z'
   */
  if (-localX->z_R_O_m > 11000.0) {
    b_Sum1_hc1q = 11000.0;
  } else if (-localX->z_R_O_m < 0.0) {
    b_Sum1_hc1q = 0.0;
  } else {
    b_Sum1_hc1q = -localX->z_R_O_m;
  }

  /* End of Saturate: '<S185>/Limit  altitude  to troposhere' */

  /* Sum: '<S185>/Sum1' incorporates:
   *  Constant: '<S185>/Sea Level  Temperature'
   *  Gain: '<S185>/Lapse Rate'
   */
  b_Sum1_hc1q = 288.15 - 0.0065 * b_Sum1_hc1q;

  /* Gain: '<S185>/1//T0' */
  b_Switch_gxqx = 0.00347041471455839 * b_Sum1_hc1q;

  /* Math: '<S185>/(T//T0)^(g//LR) ' incorporates:
   *  Constant: '<S185>/Constant'
   */
  if (b_Switch_gxqx < 0.0) {
    b_Switch_iuqm = -rt_powd_snf(-b_Switch_gxqx, 5.2558756014667134);
  } else {
    b_Switch_iuqm = rt_powd_snf(b_Switch_gxqx, 5.2558756014667134);
  }

  /* End of Math: '<S185>/(T//T0)^(g//LR) ' */

  /* Product: '<S185>/Product' */
  b_Product = b_Switch_iuqm / b_Switch_gxqx;

  /* Saturate: '<S185>/Limit  altitude  to Stratosphere' incorporates:
   *  Constant: '<S185>/Altitude of Troposphere'
   *  Gain: '<S182>/Gain'
   *  Integrator: '<S17>/pos_z'
   *  Sum: '<S185>/Sum'
   */
  if (11000.0 - (-localX->z_R_O_m) > 0.0) {
    y_1 = 0.0;
  } else if (11000.0 - (-localX->z_R_O_m) < -9000.0) {
    y_1 = -9000.0;
  } else {
    y_1 = 11000.0 - (-localX->z_R_O_m);
  }

  /* End of Saturate: '<S185>/Limit  altitude  to Stratosphere' */

  /* Math: '<S185>/Stratosphere Model' incorporates:
   *  Gain: '<S185>/g//R'
   *  Product: '<S185>/Product1'
   *
   * About '<S185>/Stratosphere Model':
   *  Operator: exp
   */
  b_Switch_gxqx = exp(1.0 / b_Sum1_hc1q * (0.034163191409533639 * y_1));

  /* Gain: '<S182>/Gain3' incorporates:
   *  Gain: '<S185>/rho0'
   *  Product: '<S185>/Product3'
   */
  b_rho_kgDm3 = 1.225 * b_Product * b_Switch_gxqx;

  /* Outputs for Iterator SubSystem: '<S33>/Propeller_RMT' incorporates:
   *  ForEach: '<S111>/For Each'
   */
  for (ForEach_itr = 0; ForEach_itr < 8; ForEach_itr = ForEach_itr + 1) {
    /* Product: '<S129>/Product' incorporates:
     *  Reshape: '<S33>/Reshape3'
     *  SignalConversion: '<S112>/Signal Conversion1'
     *  SignalConversion: '<S113>/Signal Conversion'
     */
    for (i_50 = 0; i_50 < 3; i_50 = i_50 + 1) {
      b_SignalConversion_hgu0[i_50] = 0.0;
      for (i_51 = 0; i_51 < 3; i_51 = i_51 + 1) {
        b_SignalConversion_hgu0[i_50] = b_SignalConversion_hgu0[i_50] +
          RMT_FDM_RT_ConstB.CoreSubsys_pnae.SignalConversion1_legq[i_50 + 3 *
          i_51] * b_for_G_R_B_N_aifj[i_51];
      }
    }

    /* End of Product: '<S129>/Product' */
    if (rtmIsMajorTimeStep(RMT_FDM_RT_M)) {
      /* Sum: '<S123>/Sum' incorporates:
       *  Constant: '<S111>/Constant2'
       *  Constant: '<S111>/Constant3'
       *  Product: '<S122>/Product'
       *  SignalConversion: '<S116>/Signal Conversion3'
       */
      for (i_52 = 0; i_52 < 3; i_52 = i_52 + 1) {
        tmp_w = 0.0;
        for (i_53 = 0; i_53 < 3; i_53 = i_53 + 1) {
          tmp_w = tmp_w +
            RMT_FDM_RT_ConstB.CoreSubsys_pnae.SignalConversion3[i_52 + 3 * i_53]
            * RMT_FDM_RT_ConstP.pooled1.Propeller[ForEach_itr].pos_PfP_Pf_m[i_53];
        }

        b_Sum_jgmu[i_52] = tmp_w +
          RMT_FDM_RT_ConstP.pooled1.Propeller[ForEach_itr].pos_RPf_B_m[i_52];
      }

      /* End of Sum: '<S123>/Sum' */
      for (i_54 = 0; i_54 < 3; i_54 = i_54 + 1) {
        /* Product: '<S129>/Product1' incorporates:
         *  SignalConversion: '<S112>/Signal Conversion1'
         *  Sum: '<S123>/Sum'
         */
        localB->CoreSubsys_pnae[ForEach_itr].Product1[i_54] = 0.0;
        for (i_55 = 0; i_55 < 3; i_55 = i_55 + 1) {
          localB->CoreSubsys_pnae[ForEach_itr].Product1[i_54] =
            localB->CoreSubsys_pnae[ForEach_itr].Product1[i_54] +
            RMT_FDM_RT_ConstB.CoreSubsys_pnae.SignalConversion1_legq[i_54 + 3 *
            i_55] * b_Sum_jgmu[i_55];
        }

        /* End of Product: '<S129>/Product1' */
      }
    }

    /* Sum: '<S176>/Subtract' incorporates:
     *  Product: '<S176>/y1z2'
     *  Product: '<S176>/z1y2'
     */
    b_Sum_avzm[0] = b_SignalConversion_hgu0[1] * localB->
      CoreSubsys_pnae[ForEach_itr].Product1[2] - b_SignalConversion_hgu0[2] *
      localB->CoreSubsys_pnae[ForEach_itr].Product1[1];

    /* Sum: '<S176>/Subtract1' incorporates:
     *  Product: '<S176>/x1z2'
     *  Product: '<S176>/z1x2'
     */
    b_Sum_avzm[1] = b_SignalConversion_hgu0[2] * localB->
      CoreSubsys_pnae[ForEach_itr].Product1[0] - b_SignalConversion_hgu0[0] *
      localB->CoreSubsys_pnae[ForEach_itr].Product1[2];

    /* Sum: '<S176>/Subtract2' incorporates:
     *  Product: '<S176>/x1y2'
     *  Product: '<S176>/y1x2'
     */
    b_Sum_avzm[2] = b_SignalConversion_hgu0[0] * localB->
      CoreSubsys_pnae[ForEach_itr].Product1[1] - b_SignalConversion_hgu0[1] *
      localB->CoreSubsys_pnae[ForEach_itr].Product1[0];

    /* Sum: '<S175>/Sum' incorporates:
     *  Product: '<S112>/Product'
     *  Product: '<S127>/Product'
     *  Reshape: '<S176>/Reshape'
     *  Reshape: '<S33>/Reshape2'
     */
    for (i_56 = 0; i_56 < 3; i_56 = i_56 + 1) {
      tmp_x = 0.0;
      for (i_57 = 0; i_57 < 3; i_57 = i_57 + 1) {
        tmp_x = tmp_x + RMT_FDM_RT_ConstB.CoreSubsys_pnae.Product[i_56 + 3 *
          i_57] * b_Reshape2_ksra[i_57];
      }

      b_Sum_avzm[i_56] = tmp_x + b_Sum_avzm[i_56];
    }

    /* End of Sum: '<S175>/Sum' */

    /* Trigonometry: '<S136>/Trigonometric Function' incorporates:
     *  SignalConversion: '<S113>/Signal Conversion'
     *  Sum: '<S175>/Sum'
     *  Trigonometry: '<S156>/Trigonometric Function'
     */
    b_Add_ch30_tmp = rt_atan2d_snf(b_Sum_avzm[1], b_Sum_avzm[0]);

    /* Trigonometry: '<S135>/Trigonometric Function' incorporates:
     *  Gain: '<S131>/Gain'
     *  Trigonometry: '<S136>/Trigonometric Function'
     *  Trigonometry: '<S155>/Trigonometric Function'
     */
    b_squarez_tmp = cos(-b_Add_ch30_tmp);

    /* SignalConversion generated from: '<S135>/Vector Concatenate' incorporates:
     *  Trigonometry: '<S135>/Trigonometric Function'
     */
    b_VectorConcatenate_keeq[0] = b_squarez_tmp;

    /* Trigonometry: '<S135>/Trigonometric Function1' incorporates:
     *  Gain: '<S131>/Gain'
     *  Trigonometry: '<S136>/Trigonometric Function'
     *  Trigonometry: '<S155>/Trigonometric Function1'
     */
    b_squarey_tmp_0 = sin(-b_Add_ch30_tmp);

    /* SignalConversion generated from: '<S135>/Vector Concatenate' incorporates:
     *  Trigonometry: '<S135>/Trigonometric Function1'
     */
    b_VectorConcatenate_keeq[1] = b_squarey_tmp_0;

    /* SignalConversion generated from: '<S135>/Vector Concatenate' incorporates:
     *  Constant: '<S135>/Constant'
     */
    b_VectorConcatenate_keeq[2] = 0.0;

    /* Gain: '<S135>/Gain' incorporates:
     *  Trigonometry: '<S135>/Trigonometric Function1'
     */
    b_Product_jx5y[0] = -b_squarey_tmp_0;

    /* SignalConversion generated from: '<S135>/Vector Concatenate1' incorporates:
     *  Trigonometry: '<S135>/Trigonometric Function'
     */
    b_Product_jx5y[1] = b_squarez_tmp;

    /* SignalConversion generated from: '<S135>/Vector Concatenate1' incorporates:
     *  Constant: '<S135>/Constant'
     */
    b_Product_jx5y[2] = 0.0;
    if (rtmIsMajorTimeStep(RMT_FDM_RT_M)) {
      /* Math: '<S140>/Math Function' incorporates:
       *  Constant: '<S111>/Constant1'
       *  Constant: '<S140>/Constant'
       *  Gain: '<S140>/Gain1'
       */
      localB->CoreSubsys_pnae[ForEach_itr].MathFunction = rt_powd_snf(0.5 *
        RMT_FDM_RT_ConstP.pooled1.Propeller[ForEach_itr].D, 4.0);
    }

    /* Gain: '<S111>/Gain' incorporates:
     *  Abs: '<S111>/Abs'
     *  ForEachSliceSelector generated from: '<S111>/w_z_PRot_P_cmd_radDs'
     *  Reshape: '<S33>/Reshape4'
     */
    b_squarez = RMT_FDM_RT_ConstP.pooled1.Propeller[ForEach_itr].
      Electric_Drive.rot_dir * fabs(localB->Reshape4[ForEach_itr]);

    /* Abs: '<S144>/Abs' incorporates:
     *  Abs: '<S160>/Abs'
     *  Abs: '<S164>/Abs'
     */
    b_squarey_tmp = fabs(b_squarez);

    /* SignalConversion generated from: '<S132>/Vector Concatenate' incorporates:
     *  Constant: '<S139>/Constant'
     */
    b_Reshape_axns[0] = 0.0;

    /* SignalConversion generated from: '<S132>/Vector Concatenate' incorporates:
     *  Constant: '<S138>/Constant'
     */
    b_Reshape_axns[1] = 0.0;

    /* Lookup_n-D: '<S137>/2-D Lookup Table' incorporates:
     *  Abs: '<S144>/Abs'
     *  Constant: '<S137>/Constant'
     */
    b_Reshape_axns[2] = look2_binlx(0.0, b_squarey_tmp,
      rtCP_uDLookupTable_bp01Data, rtCP_uDLookupTable_bp02Data,
      rtCP_uDLookupTable_tableData, rtCP_uDLookupTable_maxIndex, 11U);

    /* Product: '<S140>/Product' incorporates:
     *  Abs: '<S144>/Abs'
     *  Gain: '<S140>/Gain'
     *  Math: '<S140>/Square'
     */
    tmp_7 = localB->CoreSubsys_pnae[ForEach_itr].MathFunction *
      (1.5707963267948966 * (b_squarey_tmp * b_squarey_tmp)) * b_rho_kgDm3;

    /* Concatenate: '<S135>/Vector Concatenate3' incorporates:
     *  Concatenate: '<S135>/Vector Concatenate'
     *  Concatenate: '<S135>/Vector Concatenate2'
     *  Product: '<S130>/Product'
     */
    for (i_5c = 0; i_5c < 3; i_5c = i_5c + 1) {
      b_VectorConcatenate_ko43[3 * i_5c] = b_VectorConcatenate_keeq[i_5c];
    }

    for (i_5d = 0; i_5d < 3; i_5d = i_5d + 1) {
      b_VectorConcatenate_ko43[1 + 3 * i_5d] = b_Product_jx5y[i_5d];
    }

    for (i_5e = 0; i_5e < 3; i_5e = i_5e + 1) {
      b_VectorConcatenate_ko43[2 + 3 * i_5e] =
        RMT_FDM_RT_ConstB.CoreSubsys_pnae.VectorConcatenate2_km42[i_5e];
    }

    /* End of Concatenate: '<S135>/Vector Concatenate3' */

    /* Product: '<S131>/Product' incorporates:
     *  Product: '<S140>/Product'
     *  Reshape: '<S178>/Reshape'
     */
    for (i_5f = 0; i_5f < 3; i_5f = i_5f + 1) {
      b_VectorConcatenate_ko43_0[i_5f] = 0.0;
      for (i_5g = 0; i_5g < 3; i_5g = i_5g + 1) {
        b_VectorConcatenate_ko43_0[i_5f] = b_VectorConcatenate_ko43_0[i_5f] +
          b_VectorConcatenate_ko43[i_5f + 3 * i_5g] * (tmp_7 *
          b_Reshape_axns[i_5g]);
      }
    }

    /* End of Product: '<S131>/Product' */

    /* Product: '<S130>/Product' incorporates:
     *  SignalConversion: '<S113>/Signal Conversion2'
     */
    for (i_5h = 0; i_5h < 3; i_5h = i_5h + 1) {
      b_Product_jx5y[i_5h] = 0.0;
      for (i_5i = 0; i_5i < 3; i_5i = i_5i + 1) {
        b_Product_jx5y[i_5h] = b_Product_jx5y[i_5h] +
          RMT_FDM_RT_ConstB.CoreSubsys_pnae.SignalConversion2_mlwa[i_5h + 3 *
          i_5i] * b_VectorConcatenate_ko43_0[i_5i];
      }
    }

    /* End of Product: '<S130>/Product' */
    if (rtmIsMajorTimeStep(RMT_FDM_RT_M)) {
      for (i_f = 0; i_f < 3; i_f = i_f + 1) {
        /* SignalConversion: '<S113>/Signal Conversion3' incorporates:
         *  Sum: '<S123>/Sum'
         */
        localB->CoreSubsys_pnae[ForEach_itr].SignalConversion3[i_f] =
          b_Sum_jgmu[i_f];
      }

      /* Math: '<S160>/Math Function' incorporates:
       *  Constant: '<S111>/Constant1'
       *  Constant: '<S160>/Constant'
       *  Gain: '<S160>/Gain1'
       */
      localB->CoreSubsys_pnae[ForEach_itr].MathFunction_dslh = rt_powd_snf(0.5 *
        RMT_FDM_RT_ConstP.pooled1.Propeller[ForEach_itr].D, 5.0);
    }

    /* Sum: '<S178>/Subtract' incorporates:
     *  Product: '<S178>/y1z2'
     *  Product: '<S178>/z1y2'
     */
    b_Vector[0] = localB->CoreSubsys_pnae[ForEach_itr].SignalConversion3[1] *
      b_Product_jx5y[2] - localB->CoreSubsys_pnae[ForEach_itr]
      .SignalConversion3[2] * b_Product_jx5y[1];

    /* Sum: '<S178>/Subtract1' incorporates:
     *  Product: '<S178>/x1z2'
     *  Product: '<S178>/z1x2'
     */
    b_Vector[1] = localB->CoreSubsys_pnae[ForEach_itr].SignalConversion3[2] *
      b_Product_jx5y[0] - localB->CoreSubsys_pnae[ForEach_itr]
      .SignalConversion3[0] * b_Product_jx5y[2];

    /* Sum: '<S178>/Subtract2' incorporates:
     *  Product: '<S178>/x1y2'
     *  Product: '<S178>/y1x2'
     */
    b_Vector[2] = localB->CoreSubsys_pnae[ForEach_itr].SignalConversion3[0] *
      b_Product_jx5y[1] - localB->CoreSubsys_pnae[ForEach_itr]
      .SignalConversion3[1] * b_Product_jx5y[0];

    /* SignalConversion generated from: '<S155>/Vector Concatenate' */
    b_VectorConcatenate_eeyb[0] = b_squarez_tmp;

    /* SignalConversion generated from: '<S155>/Vector Concatenate' */
    b_VectorConcatenate_eeyb[1] = b_squarey_tmp_0;

    /* SignalConversion generated from: '<S155>/Vector Concatenate' incorporates:
     *  Constant: '<S155>/Constant'
     */
    b_VectorConcatenate_eeyb[2] = 0.0;

    /* Gain: '<S155>/Gain' */
    b_Product1_av01[0] = -b_squarey_tmp_0;

    /* SignalConversion generated from: '<S155>/Vector Concatenate1' */
    b_Product1_av01[1] = b_squarez_tmp;

    /* SignalConversion generated from: '<S155>/Vector Concatenate1' incorporates:
     *  Constant: '<S155>/Constant'
     */
    b_Product1_av01[2] = 0.0;

    /* SignalConversion generated from: '<S134>/Vector Concatenate' */
    b_SignalConversion1_prrf[0] =
      RMT_FDM_RT_ConstB.CoreSubsys_pnae.SignalConversion2_ijzr;

    /* SignalConversion generated from: '<S134>/Vector Concatenate' */
    b_SignalConversion1_prrf[1] =
      RMT_FDM_RT_ConstB.CoreSubsys_pnae.SignalConversion3_flbh;

    /* SignalConversion: '<S134>/Signal Conversion4' incorporates:
     *  Constant: '<S159>/Constant'
     *  Gain: '<S159>/Gain'
     *  Lookup_n-D: '<S159>/2-D Lookup Table'
     */
    b_SignalConversion1_prrf[2] = -look2_binlx(0.0, b_squarey_tmp,
      rtCP_uDLookupTable_bp01Data_h1m0, rtCP_uDLookupTable_bp02Data_knp5,
      rtCP_uDLookupTable_tableData_cgkc, rtCP_uDLookupTable_maxIndex_g45d, 11U);

    /* Product: '<S160>/Product1' incorporates:
     *  Gain: '<S160>/Gain'
     *  Product: '<S160>/Product'
     */
    tmp_8 = localB->CoreSubsys_pnae[ForEach_itr].MathFunction_dslh *
      (1.5707963267948966 * (b_squarey_tmp * b_squarez)) * b_rho_kgDm3;

    /* Concatenate: '<S155>/Vector Concatenate3' incorporates:
     *  Concatenate: '<S155>/Vector Concatenate'
     *  Concatenate: '<S155>/Vector Concatenate2'
     *  Product: '<S130>/Product1'
     */
    for (i_5p = 0; i_5p < 3; i_5p = i_5p + 1) {
      b_VectorConcatenate_kksp[3 * i_5p] = b_VectorConcatenate_eeyb[i_5p];
    }

    for (i_5q = 0; i_5q < 3; i_5q = i_5q + 1) {
      b_VectorConcatenate_kksp[1 + 3 * i_5q] = b_Product1_av01[i_5q];
    }

    for (i_5r = 0; i_5r < 3; i_5r = i_5r + 1) {
      b_VectorConcatenate_kksp[2 + 3 * i_5r] =
        RMT_FDM_RT_ConstB.CoreSubsys_pnae.VectorConcatenate2_mgso[i_5r];
    }

    /* End of Concatenate: '<S155>/Vector Concatenate3' */

    /* Product: '<S133>/Product' incorporates:
     *  Product: '<S160>/Product1'
     *  SignalConversion: '<S132>/Signal Conversion1'
     */
    for (i_5s = 0; i_5s < 3; i_5s = i_5s + 1) {
      b_VectorConcatenate_kksp_0[i_5s] = 0.0;
      for (i_5t = 0; i_5t < 3; i_5t = i_5t + 1) {
        b_VectorConcatenate_kksp_0[i_5s] = b_VectorConcatenate_kksp_0[i_5s] +
          b_VectorConcatenate_kksp[i_5s + 3 * i_5t] * (tmp_8 *
          b_SignalConversion1_prrf[i_5t]);
      }
    }

    /* End of Product: '<S133>/Product' */

    /* Sum: '<S130>/Sum' incorporates:
     *  Product: '<S130>/Product1'
     *  Reshape: '<S178>/Reshape'
     *  SignalConversion: '<S113>/Signal Conversion2'
     */
    for (i_5u = 0; i_5u < 3; i_5u = i_5u + 1) {
      tmp_y = 0.0;
      for (i_5v = 0; i_5v < 3; i_5v = i_5v + 1) {
        tmp_y = tmp_y +
          RMT_FDM_RT_ConstB.CoreSubsys_pnae.SignalConversion2_mlwa[i_5u + 3 *
          i_5v] * b_VectorConcatenate_kksp_0[i_5v];
      }

      b_Vector_7[i_5u] = b_Vector[i_5u] + tmp_y;
    }

    /* ForEachSliceAssignment generated from: '<S111>/mom_P_R_B_Nm' incorporates:
     *  Sum: '<S130>/Sum'
     */
    for (i_5w = 0; i_5w < 3; i_5w = i_5w + 1) {
      b_ImpAsg_InsertedFor_mom_P_R_B_Nm_at_inport_0[i_5w + 3 * ForEach_itr] =
        b_Vector_7[i_5w];
    }

    /* End of ForEachSliceAssignment generated from: '<S111>/mom_P_R_B_Nm' */

    /* ForEachSliceAssignment generated from: '<S111>/for_P_R_B_N' incorporates:
     *  Product: '<S130>/Product'
     *  SignalConversion: '<S113>/Signal Conversion6'
     */
    for (i_5x = 0; i_5x < 3; i_5x = i_5x + 1) {
      b_ImpAsg_InsertedFor_for_P_R_B_N_at_inport_0[i_5x + 3 * ForEach_itr] =
        b_Product_jx5y[i_5x];
    }

    /* End of ForEachSliceAssignment generated from: '<S111>/for_P_R_B_N' */
  }

  /* End of Outputs for SubSystem: '<S33>/Propeller_RMT' */

  /* Reshape: '<S26>/Reshape2' incorporates:
   *  Integrator: '<S18>/rot_x_K_IB_B_radDs'
   *  Integrator: '<S19>/rot_y_K_IB_B_radDs'
   *  Integrator: '<S20>/rot_z_K_IB_B_radDs'
   *  Reshape: '<S26>/Reshape'
   */
  b_for_G_R_B_N_ksmv_tmp[0] = localX->w_x_K_IB_B_radDs;
  b_for_G_R_B_N_ksmv_tmp[1] = localX->w_y_K_IB_B_radDs;
  b_for_G_R_B_N_ksmv_tmp[2] = localX->w_z_K_IB_B_radDs;

  /* Product: '<S189>/Element product' incorporates:
   *  Integrator: '<S18>/rot_x_K_IB_B_radDs'
   *  Integrator: '<S19>/rot_y_K_IB_B_radDs'
   *  Integrator: '<S20>/rot_z_K_IB_B_radDs'
   *  Integrator: '<S21>/vel_x_K'
   *  Integrator: '<S22>/vel_y_K'
   *  Integrator: '<S23>/vel_w_K'
   */
  b_Elementproduct[0] = localX->w_y_K_IB_B_radDs * localX->w_K_R_E_B_mDs;
  b_Elementproduct[1] = localX->w_z_K_IB_B_radDs * localX->u_K_R_E_B_mDs;
  b_Elementproduct[2] = localX->w_x_K_IB_B_radDs * localX->v_K_R_E_B_mDs;
  b_Elementproduct[3] = localX->w_z_K_IB_B_radDs * localX->v_K_R_E_B_mDs;
  b_Elementproduct[4] = localX->w_x_K_IB_B_radDs * localX->w_K_R_E_B_mDs;
  b_Elementproduct[5] = localX->w_y_K_IB_B_radDs * localX->u_K_R_E_B_mDs;

  /* Product: '<S187>/Product' incorporates:
   *  Constant: '<S35>/Constant2'
   *  Reshape: '<S187>/Reshape1'
   *  Reshape: '<S26>/Reshape'
   */
  for (i_58 = 0; i_58 < 3; i_58 = i_58 + 1) {
    b_Reshape1_ejex[i_58] = 0.0;
    for (i_59 = 0; i_59 < 3; i_59 = i_59 + 1) {
      b_Reshape1_ejex[i_58] = b_Reshape1_ejex[i_58] +
        rtCP_Constant2_Value_gfas[i_58 + 3 * i_59] * b_for_G_R_B_N_ksmv_tmp[i_59];
    }
  }

  /* End of Product: '<S187>/Product' */

  /* Product: '<S190>/Element product' incorporates:
   *  Integrator: '<S18>/rot_x_K_IB_B_radDs'
   *  Integrator: '<S19>/rot_y_K_IB_B_radDs'
   *  Integrator: '<S20>/rot_z_K_IB_B_radDs'
   */
  b_Elementproduct_otn3[0] = localX->w_y_K_IB_B_radDs * b_Reshape1_ejex[2];
  b_Elementproduct_otn3[1] = localX->w_z_K_IB_B_radDs * b_Reshape1_ejex[0];
  b_Elementproduct_otn3[2] = localX->w_x_K_IB_B_radDs * b_Reshape1_ejex[1];
  b_Elementproduct_otn3[3] = localX->w_z_K_IB_B_radDs * b_Reshape1_ejex[1];
  b_Elementproduct_otn3[4] = localX->w_x_K_IB_B_radDs * b_Reshape1_ejex[2];
  b_Elementproduct_otn3[5] = localX->w_y_K_IB_B_radDs * b_Reshape1_ejex[0];

  /* Product: '<S31>/Product1' incorporates:
   *  Product: '<S214>/Product10'
   *  Reshape: '<S31>/Reshape'
   */
  for (i_5a = 0; i_5a < 3; i_5a = i_5a + 1) {
    b_for_G_R_B_N_aifj[i_5a] = 0.0;
    for (i_5b = 0; i_5b < 3; i_5b = i_5b + 1) {
      b_for_G_R_B_N_aifj[i_5a] = b_for_G_R_B_N_aifj[i_5a] + b_M_BO[i_5a + 3 *
        i_5b] * RMT_FDM_RT_ConstB.Reshape[i_5b];
    }
  }

  /* End of Product: '<S31>/Product1' */

  /* Product: '<S37>/Element product' */
  b_Elementproduct_fjwd[0] = RMT_FDM_RT_ConstB.Reshape1[1] * b_for_G_R_B_N_aifj
    [2];
  b_Elementproduct_fjwd[1] = RMT_FDM_RT_ConstB.Reshape1[2] * b_for_G_R_B_N_aifj
    [0];
  b_Elementproduct_fjwd[2] = RMT_FDM_RT_ConstB.Reshape1[0] * b_for_G_R_B_N_aifj
    [1];
  b_Elementproduct_fjwd[3] = RMT_FDM_RT_ConstB.Reshape1[2] * b_for_G_R_B_N_aifj
    [1];
  b_Elementproduct_fjwd[4] = RMT_FDM_RT_ConstB.Reshape1[0] * b_for_G_R_B_N_aifj
    [2];
  b_Elementproduct_fjwd[5] = RMT_FDM_RT_ConstB.Reshape1[1] * b_for_G_R_B_N_aifj
    [0];

  /* Sum: '<S37>/Add3' incorporates:
   *  Reshape: '<S187>/Reshape1'
   */
  for (i_g = 0; i_g < 3; i_g = i_g + 1) {
    b_Reshape1_ejex[i_g] = b_Elementproduct_fjwd[i_g] -
      b_Elementproduct_fjwd[i_g + 3];
  }

  /* End of Sum: '<S37>/Add3' */

  /* Reshape: '<S31>/Reshape2' incorporates:
   *  Reshape: '<S187>/Reshape1'
   */
  for (i_h = 0; i_h < 3; i_h = i_h + 1) {
    b_Reshape2_ksra[i_h] = b_Reshape1_ejex[i_h];
  }

  /* End of Reshape: '<S31>/Reshape2' */

  /* Reshape: '<S181>/Reshape7' incorporates:
   *  Product: '<S181>/Product3'
   *  Reshape: '<S187>/Reshape1'
   */
  for (i_5j = 0; i_5j < 3; i_5j = i_5j + 1) {
    b_Reshape1_ejex[i_5j] = (real_T)
      rtu_Simulation_Control->flg_Weight_Balance_On * b_Reshape1_ejex[i_5j];
  }

  /* End of Reshape: '<S181>/Reshape7' */

  /* Product: '<S51>/Product' incorporates:
   *  Constant: '<S44>/Constant'
   *  Math: '<S213>/Math Function'
   */
  for (i_5k = 0; i_5k < 3; i_5k = i_5k + 1) {
    b_M_OB_h14v_tmp_0[i_5k] = 0.0;
    for (i_5l = 0; i_5l < 3; i_5l = i_5l + 1) {
      b_M_OB_h14v_tmp_0[i_5k] = b_M_OB_h14v_tmp_0[i_5k] + b_M_OB_h14v_tmp[i_5k +
        3 * i_5l] * rtCP_Constant_Value_lulu[i_5l];
    }
  }

  /* Sum: '<S51>/Sum' incorporates:
   *  Integrator: '<S17>/pos_z'
   *  Product: '<S51>/Product'
   */
  b_Add_cf0u = localX->z_R_O_m + b_M_OB_h14v_tmp_0[2];

  /* SignalConversion generated from: '<S53>/Vector Concatenate' incorporates:
   *  Integrator: '<S21>/vel_x_K'
   */
  b_VectorConcatenate[0] = localX->u_K_R_E_B_mDs;

  /* SignalConversion generated from: '<S53>/Vector Concatenate' incorporates:
   *  Integrator: '<S22>/vel_y_K'
   */
  b_VectorConcatenate[1] = localX->v_K_R_E_B_mDs;

  /* SignalConversion generated from: '<S53>/Vector Concatenate' incorporates:
   *  Integrator: '<S23>/vel_w_K'
   */
  b_VectorConcatenate[2] = localX->w_K_R_E_B_mDs;

  /* Outputs for Atomic SubSystem: '<S78>/vel_P_A_B_2_vel_Q_A_B' */
  /* Outputs for Atomic SubSystem: '<S44>/vel_P_A_B_2_vel_Q_A_B' */
  /* Sum: '<S55>/Subtract' incorporates:
   *  Constant: '<S44>/Constant'
   *  Integrator: '<S19>/rot_y_K_IB_B_radDs'
   *  Integrator: '<S20>/rot_z_K_IB_B_radDs'
   *  Product: '<S55>/y1z2'
   *  Product: '<S55>/z1y2'
   *  Sum: '<S89>/Subtract'
   */
  b_Vector_nadq_tmp_0 = localX->w_y_K_IB_B_radDs * 0.1 -
    localX->w_z_K_IB_B_radDs * -0.25;

  /* End of Outputs for SubSystem: '<S78>/vel_P_A_B_2_vel_Q_A_B' */
  b_Vector_e4oo[0] = b_Vector_nadq_tmp_0;

  /* Outputs for Atomic SubSystem: '<S61>/vel_P_A_B_2_vel_Q_A_B' */
  /* Sum: '<S55>/Subtract1' incorporates:
   *  Constant: '<S44>/Constant'
   *  Integrator: '<S18>/rot_x_K_IB_B_radDs'
   *  Integrator: '<S20>/rot_z_K_IB_B_radDs'
   *  Product: '<S55>/x1z2'
   *  Product: '<S55>/z1x2'
   *  Sum: '<S72>/Subtract1'
   */
  b_Vector_nadq_tmp = localX->w_z_K_IB_B_radDs * 0.25 - localX->w_x_K_IB_B_radDs
    * 0.1;

  /* End of Outputs for SubSystem: '<S61>/vel_P_A_B_2_vel_Q_A_B' */
  b_Vector_e4oo[1] = b_Vector_nadq_tmp;

  /* Sum: '<S55>/Subtract2' incorporates:
   *  Constant: '<S44>/Constant'
   *  Integrator: '<S18>/rot_x_K_IB_B_radDs'
   *  Integrator: '<S19>/rot_y_K_IB_B_radDs'
   *  Product: '<S55>/x1y2'
   *  Product: '<S55>/y1x2'
   */
  b_Vector_e4oo[2] = localX->w_x_K_IB_B_radDs * -0.25 - localX->w_y_K_IB_B_radDs
    * 0.25;

  /* Sum: '<S54>/Sum' incorporates:
   *  Concatenate: '<S53>/Vector Concatenate'
   *  Reshape: '<S55>/Reshape'
   */
  for (i_5m = 0; i_5m < 3; i_5m = i_5m + 1) {
    b_VectorConcatenate_6[i_5m] = b_VectorConcatenate[i_5m] + b_Vector_e4oo[i_5m];
  }

  /* End of Sum: '<S54>/Sum' */
  /* End of Outputs for SubSystem: '<S44>/vel_P_A_B_2_vel_Q_A_B' */

  /* Product: '<S44>/Product' incorporates:
   *  Product: '<S44>/Product1'
   *  Sum: '<S38>/Sum'
   */
  for (i_5n = 0; i_5n < 3; i_5n = i_5n + 1) {
    b_Sum_hhfg[i_5n] = 0.0;
    for (i_5o = 0; i_5o < 3; i_5o = i_5o + 1) {
      b_Sum_hhfg[i_5n] = b_Sum_hhfg[i_5n] + b_Product1_ovxb[i_5n + 3 * i_5o] *
        b_VectorConcatenate_6[i_5o];
    }
  }

  /* End of Product: '<S44>/Product' */

  /* Gain: '<S45>/Gain1' */
  b_w_z_int_PRot_P_err_radDs_alwh = -5.0 * b_Sum_hhfg[2];

  /* Saturate: '<S45>/Saturation' */
  if (b_w_z_int_PRot_P_err_radDs_alwh >= 0.0) {
    b_Divide1_igly = 0.0;
  } else {
    b_Divide1_igly = b_w_z_int_PRot_P_err_radDs_alwh;
  }

  /* End of Saturate: '<S45>/Saturation' */

  /* Product: '<S45>/Product' incorporates:
   *  Constant: '<S57>/Constant'
   *  DataTypeConversion: '<S45>/Data Type Conversion'
   *  Gain: '<S45>/Gain'
   *  RelationalOperator: '<S57>/Compare'
   *  Sum: '<S45>/Add'
   */
  b_w_z_int_PRot_P_err_radDs_alwh = (-30.0 * b_Add_cf0u + b_Divide1_igly) *
    (real_T)(b_Add_cf0u >= 0.0);

  /* Abs: '<S43>/Abs' incorporates:
   *  Gain: '<S43>/Gain2'
   */
  b_Add_cf0u = fabs(b_w_z_int_PRot_P_err_radDs_alwh);
  for (i_i = 0; i_i < 2; i_i = i_i + 1) {
    /* Gain: '<S43>/Gain' */
    localB->Gain_ckcu[i_i] = -b_Sum_hhfg[i_i];
  }

  /* Switch: '<S49>/Switch' incorporates:
   *  Gain: '<S43>/Gain'
   *  Gain: '<S43>/Gain1'
   *  RelationalOperator: '<S49>/UpperRelop'
   */
  for (i_5 = 0; i_5 < 2; i_5 = i_5 + 1) {
    if (localB->Gain_ckcu[i_5] < -b_Add_cf0u) {
      /* Switch: '<S49>/Switch' */
      localB->Switch[i_5] = -b_Add_cf0u;
    } else {
      /* Switch: '<S49>/Switch' */
      localB->Switch[i_5] = localB->Gain_ckcu[i_5];
    }
  }

  /* End of Switch: '<S49>/Switch' */

  /* Switch: '<S49>/Switch2' incorporates:
   *  Gain: '<S43>/Gain'
   *  RelationalOperator: '<S49>/LowerRelop1'
   */
  for (i_5 = 0; i_5 < 2; i_5 = i_5 + 1) {
    if (localB->Gain_ckcu[i_5] > b_Add_cf0u) {
      /* Switch: '<S49>/Switch2' */
      localB->Switch2[i_5] = b_Add_cf0u;
    } else {
      /* Switch: '<S49>/Switch2' incorporates:
       *  Switch: '<S49>/Switch'
       */
      localB->Switch2[i_5] = localB->Switch[i_5];
    }
  }

  /* End of Switch: '<S49>/Switch2' */

  /* SignalConversion generated from: '<S46>/Vector Concatenate' incorporates:
   *  Switch: '<S49>/Switch2'
   */
  for (i_j = 0; i_j < 2; i_j = i_j + 1) {
    b_Reshape8[i_j] = localB->Switch2[i_j];
  }

  /* End of SignalConversion generated from: '<S46>/Vector Concatenate' */

  /* SignalConversion generated from: '<S46>/Vector Concatenate' */
  b_Reshape8[2] = b_w_z_int_PRot_P_err_radDs_alwh;

  /* Assignment: '<S48>/Assignment' incorporates:
   *  Constant: '<S38>/Constant'
   *  Product: '<S48>/Product'
   *  Reshape: '<S180>/Reshape8'
   */
  for (i_k = 0; i_k < 3; i_k = i_k + 1) {
    b_Assignment[i_k] = b_Reshape8[i_k];
  }

  b_Assignment[0] = b_Reshape8[0] * 0.0;

  /* End of Assignment: '<S48>/Assignment' */

  /* Outputs for Atomic SubSystem: '<S39>/for_mom_X_2_for_mom_Y' */
  /* Product: '<S47>/Product' incorporates:
   *  Assignment: '<S48>/Assignment'
   *  Math: '<S39>/Math Function'
   */
  for (i_5y = 0; i_5y < 3; i_5y = i_5y + 1) {
    b_Product_aer5[i_5y] = 0.0;
    for (i_5z = 0; i_5z < 3; i_5z = i_5z + 1) {
      b_Product_aer5[i_5y] = b_Product_aer5[i_5y] + b_MathFunction_dsxx[i_5y + 3
        * i_5z] * b_Assignment[i_5z];
    }
  }

  /* End of Product: '<S47>/Product' */

  /* Sum: '<S58>/SubX' incorporates:
   *  Constant: '<S39>/Constant1'
   *  Product: '<S58>/y1z2'
   *  Product: '<S58>/z1y2'
   */
  b_Vector_ebga[0] = -0.25 * b_Product_aer5[2] - 0.1 * b_Product_aer5[1];

  /* Sum: '<S58>/SubY' incorporates:
   *  Constant: '<S39>/Constant1'
   *  Product: '<S58>/x1z2'
   *  Product: '<S58>/z1x2'
   */
  b_Vector_ebga[1] = 0.1 * b_Product_aer5[0] - 0.25 * b_Product_aer5[2];

  /* Sum: '<S58>/SubZ' incorporates:
   *  Constant: '<S39>/Constant1'
   *  Product: '<S58>/x1y2'
   *  Product: '<S58>/y1x2'
   */
  b_Vector_ebga[2] = 0.25 * b_Product_aer5[1] - -0.25 * b_Product_aer5[0];

  /* End of Outputs for SubSystem: '<S39>/for_mom_X_2_for_mom_Y' */

  /* Product: '<S68>/Product' incorporates:
   *  Constant: '<S61>/Constant'
   *  Math: '<S213>/Math Function'
   */
  for (i_60 = 0; i_60 < 3; i_60 = i_60 + 1) {
    b_M_OB_h14v_tmp_1[i_60] = 0.0;
    for (i_61 = 0; i_61 < 3; i_61 = i_61 + 1) {
      b_M_OB_h14v_tmp_1[i_60] = b_M_OB_h14v_tmp_1[i_60] + b_M_OB_h14v_tmp[i_60 +
        3 * i_61] * rtCP_Constant_Value_n4di[i_61];
    }
  }

  /* Sum: '<S68>/Sum' incorporates:
   *  Integrator: '<S17>/pos_z'
   *  Product: '<S68>/Product'
   */
  b_Divide1_igly = localX->z_R_O_m + b_M_OB_h14v_tmp_1[2];

  /* SignalConversion generated from: '<S70>/Vector Concatenate' incorporates:
   *  Integrator: '<S21>/vel_x_K'
   */
  b_VectorConcatenate_iiv2[0] = localX->u_K_R_E_B_mDs;

  /* SignalConversion generated from: '<S70>/Vector Concatenate' incorporates:
   *  Integrator: '<S22>/vel_y_K'
   */
  b_VectorConcatenate_iiv2[1] = localX->v_K_R_E_B_mDs;

  /* SignalConversion generated from: '<S70>/Vector Concatenate' incorporates:
   *  Integrator: '<S23>/vel_w_K'
   */
  b_VectorConcatenate_iiv2[2] = localX->w_K_R_E_B_mDs;

  /* Outputs for Atomic SubSystem: '<S95>/vel_P_A_B_2_vel_Q_A_B' */
  /* Outputs for Atomic SubSystem: '<S61>/vel_P_A_B_2_vel_Q_A_B' */
  /* Sum: '<S72>/Subtract' incorporates:
   *  Constant: '<S61>/Constant'
   *  Integrator: '<S19>/rot_y_K_IB_B_radDs'
   *  Integrator: '<S20>/rot_z_K_IB_B_radDs'
   *  Product: '<S72>/y1z2'
   *  Product: '<S72>/z1y2'
   *  Sum: '<S106>/Subtract'
   */
  b_Vector_mdpm_tmp = localX->w_y_K_IB_B_radDs * 0.1 - localX->w_z_K_IB_B_radDs *
    0.25;

  /* End of Outputs for SubSystem: '<S95>/vel_P_A_B_2_vel_Q_A_B' */
  b_Vector_eeei[0] = b_Vector_mdpm_tmp;

  /* Sum: '<S72>/Subtract1' */
  b_Vector_eeei[1] = b_Vector_nadq_tmp;

  /* Sum: '<S72>/Subtract2' incorporates:
   *  Constant: '<S61>/Constant'
   *  Integrator: '<S18>/rot_x_K_IB_B_radDs'
   *  Integrator: '<S19>/rot_y_K_IB_B_radDs'
   *  Product: '<S72>/x1y2'
   *  Product: '<S72>/y1x2'
   */
  b_Vector_eeei[2] = localX->w_x_K_IB_B_radDs * 0.25 - localX->w_y_K_IB_B_radDs *
    0.25;

  /* Sum: '<S71>/Sum' incorporates:
   *  Concatenate: '<S70>/Vector Concatenate'
   *  Reshape: '<S72>/Reshape'
   */
  for (i_62 = 0; i_62 < 3; i_62 = i_62 + 1) {
    b_VectorConcatenate_amwl[i_62] = b_VectorConcatenate_iiv2[i_62] +
      b_Vector_eeei[i_62];
  }

  /* End of Sum: '<S71>/Sum' */
  /* End of Outputs for SubSystem: '<S61>/vel_P_A_B_2_vel_Q_A_B' */

  /* Product: '<S61>/Product' incorporates:
   *  Product: '<S61>/Product1'
   *  Sum: '<S38>/Sum'
   */
  for (i_63 = 0; i_63 < 3; i_63 = i_63 + 1) {
    b_Sum_hhfg[i_63] = 0.0;
    for (i_64 = 0; i_64 < 3; i_64 = i_64 + 1) {
      b_Sum_hhfg[i_63] = b_Sum_hhfg[i_63] + b_Product1_ehnp[i_63 + 3 * i_64] *
        b_VectorConcatenate_amwl[i_64];
    }
  }

  /* End of Product: '<S61>/Product' */

  /* Gain: '<S62>/Gain1' */
  b_w_z_int_PRot_P_err_radDs_alwh = -5.0 * b_Sum_hhfg[2];

  /* Saturate: '<S62>/Saturation' */
  if (b_w_z_int_PRot_P_err_radDs_alwh >= 0.0) {
    b_Add_cf0u = 0.0;
  } else {
    b_Add_cf0u = b_w_z_int_PRot_P_err_radDs_alwh;
  }

  /* End of Saturate: '<S62>/Saturation' */

  /* Product: '<S62>/Product' incorporates:
   *  Constant: '<S74>/Constant'
   *  DataTypeConversion: '<S62>/Data Type Conversion'
   *  Gain: '<S62>/Gain'
   *  RelationalOperator: '<S74>/Compare'
   *  Sum: '<S62>/Add'
   */
  b_w_z_int_PRot_P_err_radDs_alwh = (-30.0 * b_Divide1_igly + b_Add_cf0u) *
    (real_T)(b_Divide1_igly >= 0.0);

  /* Abs: '<S60>/Abs' incorporates:
   *  Gain: '<S60>/Gain2'
   */
  b_Add_cf0u = fabs(b_w_z_int_PRot_P_err_radDs_alwh);
  for (i_l = 0; i_l < 2; i_l = i_l + 1) {
    /* Gain: '<S60>/Gain' */
    localB->Gain_aiks[i_l] = -b_Sum_hhfg[i_l];
  }

  /* Switch: '<S66>/Switch' incorporates:
   *  Gain: '<S60>/Gain'
   *  Gain: '<S60>/Gain1'
   *  RelationalOperator: '<S66>/UpperRelop'
   */
  for (i_5 = 0; i_5 < 2; i_5 = i_5 + 1) {
    if (localB->Gain_aiks[i_5] < -b_Add_cf0u) {
      /* Switch: '<S66>/Switch' */
      localB->Switch_e5kt[i_5] = -b_Add_cf0u;
    } else {
      /* Switch: '<S66>/Switch' */
      localB->Switch_e5kt[i_5] = localB->Gain_aiks[i_5];
    }
  }

  /* End of Switch: '<S66>/Switch' */

  /* Switch: '<S66>/Switch2' incorporates:
   *  Gain: '<S60>/Gain'
   *  RelationalOperator: '<S66>/LowerRelop1'
   */
  for (i_5 = 0; i_5 < 2; i_5 = i_5 + 1) {
    if (localB->Gain_aiks[i_5] > b_Add_cf0u) {
      /* Switch: '<S66>/Switch2' */
      localB->Switch2_p2qf[i_5] = b_Add_cf0u;
    } else {
      /* Switch: '<S66>/Switch2' incorporates:
       *  Switch: '<S66>/Switch'
       */
      localB->Switch2_p2qf[i_5] = localB->Switch_e5kt[i_5];
    }
  }

  /* End of Switch: '<S66>/Switch2' */

  /* SignalConversion generated from: '<S63>/Vector Concatenate' incorporates:
   *  Switch: '<S66>/Switch2'
   */
  for (i_m = 0; i_m < 2; i_m = i_m + 1) {
    b_Reshape1_hoha[i_m] = localB->Switch2_p2qf[i_m];
  }

  /* End of SignalConversion generated from: '<S63>/Vector Concatenate' */

  /* SignalConversion generated from: '<S63>/Vector Concatenate' */
  b_Reshape1_hoha[2] = b_w_z_int_PRot_P_err_radDs_alwh;

  /* Assignment: '<S65>/Assignment' incorporates:
   *  Constant: '<S38>/Constant'
   *  Product: '<S65>/Product'
   *  Reshape: '<S33>/Reshape1'
   */
  for (i_n = 0; i_n < 3; i_n = i_n + 1) {
    b_Assignment_kod3[i_n] = b_Reshape1_hoha[i_n];
  }

  b_Assignment_kod3[0] = b_Reshape1_hoha[0] * 0.0;

  /* End of Assignment: '<S65>/Assignment' */

  /* Outputs for Atomic SubSystem: '<S40>/for_mom_X_2_for_mom_Y' */
  /* Product: '<S64>/Product' incorporates:
   *  Assignment: '<S65>/Assignment'
   *  Math: '<S40>/Math Function'
   */
  for (i_65 = 0; i_65 < 3; i_65 = i_65 + 1) {
    b_Product_fmjd[i_65] = 0.0;
    for (i_66 = 0; i_66 < 3; i_66 = i_66 + 1) {
      b_Product_fmjd[i_65] = b_Product_fmjd[i_65] + b_MathFunction_cbg2[i_65 + 3
        * i_66] * b_Assignment_kod3[i_66];
    }
  }

  /* End of Product: '<S64>/Product' */

  /* Sum: '<S75>/SubX' incorporates:
   *  Constant: '<S40>/Constant1'
   *  Product: '<S75>/y1z2'
   *  Product: '<S75>/z1y2'
   */
  b_Vector_pgif[0] = 0.25 * b_Product_fmjd[2] - 0.1 * b_Product_fmjd[1];

  /* Sum: '<S75>/SubY' incorporates:
   *  Constant: '<S40>/Constant1'
   *  Product: '<S75>/x1z2'
   *  Product: '<S75>/z1x2'
   */
  b_Vector_pgif[1] = 0.1 * b_Product_fmjd[0] - 0.25 * b_Product_fmjd[2];

  /* Sum: '<S75>/SubZ' incorporates:
   *  Constant: '<S40>/Constant1'
   *  Product: '<S75>/x1y2'
   *  Product: '<S75>/y1x2'
   */
  b_Vector_pgif[2] = 0.25 * b_Product_fmjd[1] - 0.25 * b_Product_fmjd[0];

  /* End of Outputs for SubSystem: '<S40>/for_mom_X_2_for_mom_Y' */

  /* Product: '<S85>/Product' incorporates:
   *  Constant: '<S78>/Constant'
   *  Math: '<S213>/Math Function'
   */
  for (i_67 = 0; i_67 < 3; i_67 = i_67 + 1) {
    b_M_OB_h14v_tmp_2[i_67] = 0.0;
    for (i_68 = 0; i_68 < 3; i_68 = i_68 + 1) {
      b_M_OB_h14v_tmp_2[i_67] = b_M_OB_h14v_tmp_2[i_67] + b_M_OB_h14v_tmp[i_67 +
        3 * i_68] * rtCP_Constant_Value_fsfs[i_68];
    }
  }

  /* Sum: '<S85>/Sum' incorporates:
   *  Integrator: '<S17>/pos_z'
   *  Product: '<S85>/Product'
   */
  b_Divide1_igly = localX->z_R_O_m + b_M_OB_h14v_tmp_2[2];

  /* SignalConversion generated from: '<S87>/Vector Concatenate' incorporates:
   *  Integrator: '<S21>/vel_x_K'
   */
  b_VectorConcatenate_lpik[0] = localX->u_K_R_E_B_mDs;

  /* SignalConversion generated from: '<S87>/Vector Concatenate' incorporates:
   *  Integrator: '<S22>/vel_y_K'
   */
  b_VectorConcatenate_lpik[1] = localX->v_K_R_E_B_mDs;

  /* SignalConversion generated from: '<S87>/Vector Concatenate' incorporates:
   *  Integrator: '<S23>/vel_w_K'
   */
  b_VectorConcatenate_lpik[2] = localX->w_K_R_E_B_mDs;

  /* Outputs for Atomic SubSystem: '<S78>/vel_P_A_B_2_vel_Q_A_B' */
  /* Sum: '<S89>/Subtract' */
  b_Vector_m0fx[0] = b_Vector_nadq_tmp_0;

  /* Outputs for Atomic SubSystem: '<S95>/vel_P_A_B_2_vel_Q_A_B' */
  /* Sum: '<S89>/Subtract1' incorporates:
   *  Constant: '<S78>/Constant'
   *  Integrator: '<S18>/rot_x_K_IB_B_radDs'
   *  Integrator: '<S20>/rot_z_K_IB_B_radDs'
   *  Product: '<S89>/x1z2'
   *  Product: '<S89>/z1x2'
   *  Sum: '<S106>/Subtract1'
   */
  b_Vector_ipfw_tmp = localX->w_z_K_IB_B_radDs * -0.25 -
    localX->w_x_K_IB_B_radDs * 0.1;

  /* End of Outputs for SubSystem: '<S95>/vel_P_A_B_2_vel_Q_A_B' */
  b_Vector_m0fx[1] = b_Vector_ipfw_tmp;

  /* Sum: '<S89>/Subtract2' incorporates:
   *  Constant: '<S78>/Constant'
   *  Integrator: '<S18>/rot_x_K_IB_B_radDs'
   *  Integrator: '<S19>/rot_y_K_IB_B_radDs'
   *  Product: '<S89>/x1y2'
   *  Product: '<S89>/y1x2'
   */
  b_Vector_m0fx[2] = localX->w_x_K_IB_B_radDs * -0.25 - localX->w_y_K_IB_B_radDs
    * -0.25;

  /* Sum: '<S88>/Sum' incorporates:
   *  Concatenate: '<S87>/Vector Concatenate'
   *  Reshape: '<S89>/Reshape'
   */
  for (i_69 = 0; i_69 < 3; i_69 = i_69 + 1) {
    b_VectorConcatenate_kudp[i_69] = b_VectorConcatenate_lpik[i_69] +
      b_Vector_m0fx[i_69];
  }

  /* End of Sum: '<S88>/Sum' */
  /* End of Outputs for SubSystem: '<S78>/vel_P_A_B_2_vel_Q_A_B' */

  /* Product: '<S78>/Product' incorporates:
   *  Product: '<S78>/Product1'
   *  Sum: '<S38>/Sum'
   */
  for (i_6a = 0; i_6a < 3; i_6a = i_6a + 1) {
    b_Sum_hhfg[i_6a] = 0.0;
    for (i_6b = 0; i_6b < 3; i_6b = i_6b + 1) {
      b_Sum_hhfg[i_6a] = b_Sum_hhfg[i_6a] + b_Product1_n5kc[i_6a + 3 * i_6b] *
        b_VectorConcatenate_kudp[i_6b];
    }
  }

  /* End of Product: '<S78>/Product' */

  /* Gain: '<S79>/Gain1' */
  b_w_z_int_PRot_P_err_radDs_alwh = -5.0 * b_Sum_hhfg[2];

  /* Saturate: '<S79>/Saturation' */
  if (b_w_z_int_PRot_P_err_radDs_alwh >= 0.0) {
    b_Add_cf0u = 0.0;
  } else {
    b_Add_cf0u = b_w_z_int_PRot_P_err_radDs_alwh;
  }

  /* End of Saturate: '<S79>/Saturation' */

  /* Product: '<S79>/Product' incorporates:
   *  Constant: '<S91>/Constant'
   *  DataTypeConversion: '<S79>/Data Type Conversion'
   *  Gain: '<S79>/Gain'
   *  RelationalOperator: '<S91>/Compare'
   *  Sum: '<S79>/Add'
   */
  b_w_z_int_PRot_P_err_radDs_alwh = (-30.0 * b_Divide1_igly + b_Add_cf0u) *
    (real_T)(b_Divide1_igly >= 0.0);

  /* Abs: '<S77>/Abs' incorporates:
   *  Gain: '<S77>/Gain2'
   */
  b_Add_cf0u = fabs(b_w_z_int_PRot_P_err_radDs_alwh);
  for (i_o = 0; i_o < 2; i_o = i_o + 1) {
    /* Gain: '<S77>/Gain' */
    localB->Gain_p454[i_o] = -b_Sum_hhfg[i_o];
  }

  /* Switch: '<S83>/Switch' incorporates:
   *  Gain: '<S77>/Gain'
   *  Gain: '<S77>/Gain1'
   *  RelationalOperator: '<S83>/UpperRelop'
   */
  for (i_5 = 0; i_5 < 2; i_5 = i_5 + 1) {
    if (localB->Gain_p454[i_5] < -b_Add_cf0u) {
      /* Switch: '<S83>/Switch' */
      localB->Switch_cjwg[i_5] = -b_Add_cf0u;
    } else {
      /* Switch: '<S83>/Switch' */
      localB->Switch_cjwg[i_5] = localB->Gain_p454[i_5];
    }
  }

  /* End of Switch: '<S83>/Switch' */

  /* Switch: '<S83>/Switch2' incorporates:
   *  Gain: '<S77>/Gain'
   *  RelationalOperator: '<S83>/LowerRelop1'
   */
  for (i_5 = 0; i_5 < 2; i_5 = i_5 + 1) {
    if (localB->Gain_p454[i_5] > b_Add_cf0u) {
      /* Switch: '<S83>/Switch2' */
      localB->Switch2_oflh[i_5] = b_Add_cf0u;
    } else {
      /* Switch: '<S83>/Switch2' incorporates:
       *  Switch: '<S83>/Switch'
       */
      localB->Switch2_oflh[i_5] = localB->Switch_cjwg[i_5];
    }
  }

  /* End of Switch: '<S83>/Switch2' */

  /* SignalConversion generated from: '<S80>/Vector Concatenate' incorporates:
   *  Switch: '<S83>/Switch2'
   */
  for (i_p = 0; i_p < 2; i_p = i_p + 1) {
    b_mom_T_R_B_Nm_fyeb[i_p] = localB->Switch2_oflh[i_p];
  }

  /* End of SignalConversion generated from: '<S80>/Vector Concatenate' */

  /* SignalConversion generated from: '<S80>/Vector Concatenate' */
  b_mom_T_R_B_Nm_fyeb[2] = b_w_z_int_PRot_P_err_radDs_alwh;

  /* Assignment: '<S82>/Assignment' incorporates:
   *  Constant: '<S38>/Constant'
   *  Product: '<S82>/Product'
   *  Reshape: '<S181>/Reshape8'
   */
  for (i_q = 0; i_q < 3; i_q = i_q + 1) {
    b_Assignment_boes[i_q] = b_mom_T_R_B_Nm_fyeb[i_q];
  }

  b_Assignment_boes[0] = b_mom_T_R_B_Nm_fyeb[0] * 0.0;

  /* End of Assignment: '<S82>/Assignment' */

  /* Outputs for Atomic SubSystem: '<S41>/for_mom_X_2_for_mom_Y' */
  /* Product: '<S81>/Product' incorporates:
   *  Assignment: '<S82>/Assignment'
   *  Math: '<S41>/Math Function'
   */
  for (i_6c = 0; i_6c < 3; i_6c = i_6c + 1) {
    b_Product_n2sg[i_6c] = 0.0;
    for (i_6d = 0; i_6d < 3; i_6d = i_6d + 1) {
      b_Product_n2sg[i_6c] = b_Product_n2sg[i_6c] + b_MathFunction_avjt[i_6c + 3
        * i_6d] * b_Assignment_boes[i_6d];
    }
  }

  /* End of Product: '<S81>/Product' */

  /* Sum: '<S92>/SubX' incorporates:
   *  Constant: '<S41>/Constant1'
   *  Product: '<S92>/y1z2'
   *  Product: '<S92>/z1y2'
   */
  b_Vector_buas[0] = -0.25 * b_Product_n2sg[2] - 0.1 * b_Product_n2sg[1];

  /* Sum: '<S92>/SubY' incorporates:
   *  Constant: '<S41>/Constant1'
   *  Product: '<S92>/x1z2'
   *  Product: '<S92>/z1x2'
   */
  b_Vector_buas[1] = 0.1 * b_Product_n2sg[0] - -0.25 * b_Product_n2sg[2];

  /* Sum: '<S92>/SubZ' incorporates:
   *  Constant: '<S41>/Constant1'
   *  Product: '<S92>/x1y2'
   *  Product: '<S92>/y1x2'
   */
  b_Vector_buas[2] = -0.25 * b_Product_n2sg[1] - -0.25 * b_Product_n2sg[0];

  /* End of Outputs for SubSystem: '<S41>/for_mom_X_2_for_mom_Y' */

  /* Product: '<S102>/Product' incorporates:
   *  Constant: '<S95>/Constant'
   *  Math: '<S213>/Math Function'
   */
  for (i_6e = 0; i_6e < 3; i_6e = i_6e + 1) {
    b_M_OB_h14v_tmp_3[i_6e] = 0.0;
    for (i_6f = 0; i_6f < 3; i_6f = i_6f + 1) {
      b_M_OB_h14v_tmp_3[i_6e] = b_M_OB_h14v_tmp_3[i_6e] + b_M_OB_h14v_tmp[i_6e +
        3 * i_6f] * rtCP_Constant_Value_kqqp[i_6f];
    }
  }

  /* Sum: '<S102>/Sum' incorporates:
   *  Integrator: '<S17>/pos_z'
   *  Product: '<S102>/Product'
   */
  b_Divide1_igly = localX->z_R_O_m + b_M_OB_h14v_tmp_3[2];

  /* SignalConversion generated from: '<S104>/Vector Concatenate' incorporates:
   *  Integrator: '<S21>/vel_x_K'
   */
  b_VectorConcatenate_cl4h[0] = localX->u_K_R_E_B_mDs;

  /* SignalConversion generated from: '<S104>/Vector Concatenate' incorporates:
   *  Integrator: '<S22>/vel_y_K'
   */
  b_VectorConcatenate_cl4h[1] = localX->v_K_R_E_B_mDs;

  /* SignalConversion generated from: '<S104>/Vector Concatenate' incorporates:
   *  Integrator: '<S23>/vel_w_K'
   */
  b_VectorConcatenate_cl4h[2] = localX->w_K_R_E_B_mDs;

  /* Outputs for Atomic SubSystem: '<S95>/vel_P_A_B_2_vel_Q_A_B' */
  /* Sum: '<S106>/Subtract' */
  b_Vector_iguf[0] = b_Vector_mdpm_tmp;

  /* Sum: '<S106>/Subtract1' */
  b_Vector_iguf[1] = b_Vector_ipfw_tmp;

  /* Sum: '<S106>/Subtract2' incorporates:
   *  Constant: '<S95>/Constant'
   *  Integrator: '<S18>/rot_x_K_IB_B_radDs'
   *  Integrator: '<S19>/rot_y_K_IB_B_radDs'
   *  Product: '<S106>/x1y2'
   *  Product: '<S106>/y1x2'
   */
  b_Vector_iguf[2] = localX->w_x_K_IB_B_radDs * 0.25 - localX->w_y_K_IB_B_radDs *
    -0.25;

  /* Sum: '<S105>/Sum' incorporates:
   *  Concatenate: '<S104>/Vector Concatenate'
   *  Reshape: '<S106>/Reshape'
   */
  for (i_6g = 0; i_6g < 3; i_6g = i_6g + 1) {
    b_VectorConcatenate_oawp[i_6g] = b_VectorConcatenate_cl4h[i_6g] +
      b_Vector_iguf[i_6g];
  }

  /* End of Sum: '<S105>/Sum' */
  /* End of Outputs for SubSystem: '<S95>/vel_P_A_B_2_vel_Q_A_B' */

  /* Product: '<S95>/Product' incorporates:
   *  Product: '<S95>/Product1'
   *  Sum: '<S38>/Sum'
   */
  for (i_6h = 0; i_6h < 3; i_6h = i_6h + 1) {
    b_Sum_hhfg[i_6h] = 0.0;
    for (i_6i = 0; i_6i < 3; i_6i = i_6i + 1) {
      b_Sum_hhfg[i_6h] = b_Sum_hhfg[i_6h] + b_Product1_j1ks[i_6h + 3 * i_6i] *
        b_VectorConcatenate_oawp[i_6i];
    }
  }

  /* End of Product: '<S95>/Product' */

  /* Gain: '<S96>/Gain1' */
  b_w_z_int_PRot_P_err_radDs_alwh = -5.0 * b_Sum_hhfg[2];

  /* Saturate: '<S96>/Saturation' */
  if (b_w_z_int_PRot_P_err_radDs_alwh >= 0.0) {
    b_Add_cf0u = 0.0;
  } else {
    b_Add_cf0u = b_w_z_int_PRot_P_err_radDs_alwh;
  }

  /* End of Saturate: '<S96>/Saturation' */

  /* Product: '<S96>/Product' incorporates:
   *  Constant: '<S108>/Constant'
   *  DataTypeConversion: '<S96>/Data Type Conversion'
   *  Gain: '<S96>/Gain'
   *  RelationalOperator: '<S108>/Compare'
   *  Sum: '<S96>/Add'
   */
  b_w_z_int_PRot_P_err_radDs_alwh = (-30.0 * b_Divide1_igly + b_Add_cf0u) *
    (real_T)(b_Divide1_igly >= 0.0);

  /* Abs: '<S94>/Abs' incorporates:
   *  Gain: '<S94>/Gain2'
   */
  b_Add_cf0u = fabs(b_w_z_int_PRot_P_err_radDs_alwh);
  for (i_r = 0; i_r < 2; i_r = i_r + 1) {
    /* Gain: '<S94>/Gain' */
    localB->Gain_auvv[i_r] = -b_Sum_hhfg[i_r];
  }

  /* Switch: '<S100>/Switch' incorporates:
   *  Gain: '<S94>/Gain'
   *  Gain: '<S94>/Gain1'
   *  RelationalOperator: '<S100>/UpperRelop'
   */
  for (i_5 = 0; i_5 < 2; i_5 = i_5 + 1) {
    if (localB->Gain_auvv[i_5] < -b_Add_cf0u) {
      /* Switch: '<S100>/Switch' */
      localB->Switch_gr2v[i_5] = -b_Add_cf0u;
    } else {
      /* Switch: '<S100>/Switch' */
      localB->Switch_gr2v[i_5] = localB->Gain_auvv[i_5];
    }
  }

  /* End of Switch: '<S100>/Switch' */

  /* Switch: '<S100>/Switch2' incorporates:
   *  Gain: '<S94>/Gain'
   *  RelationalOperator: '<S100>/LowerRelop1'
   */
  for (i_5 = 0; i_5 < 2; i_5 = i_5 + 1) {
    if (localB->Gain_auvv[i_5] > b_Add_cf0u) {
      /* Switch: '<S100>/Switch2' */
      localB->Switch2_jiir[i_5] = b_Add_cf0u;
    } else {
      /* Switch: '<S100>/Switch2' incorporates:
       *  Switch: '<S100>/Switch'
       */
      localB->Switch2_jiir[i_5] = localB->Switch_gr2v[i_5];
    }
  }

  /* End of Switch: '<S100>/Switch2' */

  /* SignalConversion generated from: '<S97>/Vector Concatenate' incorporates:
   *  Switch: '<S100>/Switch2'
   */
  for (i_s = 0; i_s < 2; i_s = i_s + 1) {
    b_Sum3[i_s] = localB->Switch2_jiir[i_s];
  }

  /* End of SignalConversion generated from: '<S97>/Vector Concatenate' */

  /* SignalConversion generated from: '<S97>/Vector Concatenate' */
  b_Sum3[2] = b_w_z_int_PRot_P_err_radDs_alwh;

  /* Assignment: '<S99>/Assignment' incorporates:
   *  Constant: '<S38>/Constant'
   *  Product: '<S99>/Product'
   *  Sum: '<S38>/Sum3'
   */
  for (i_t = 0; i_t < 3; i_t = i_t + 1) {
    b_Assignment_ia0s[i_t] = b_Sum3[i_t];
  }

  b_Assignment_ia0s[0] = b_Sum3[0] * 0.0;

  /* End of Assignment: '<S99>/Assignment' */

  /* Outputs for Atomic SubSystem: '<S42>/for_mom_X_2_for_mom_Y' */
  /* Product: '<S98>/Product' incorporates:
   *  Assignment: '<S99>/Assignment'
   *  Math: '<S42>/Math Function'
   */
  for (i_6j = 0; i_6j < 3; i_6j = i_6j + 1) {
    b_Product_dmg0[i_6j] = 0.0;
    for (i_6k = 0; i_6k < 3; i_6k = i_6k + 1) {
      b_Product_dmg0[i_6j] = b_Product_dmg0[i_6j] + b_MathFunction_g133[i_6j + 3
        * i_6k] * b_Assignment_ia0s[i_6k];
    }
  }

  /* End of Product: '<S98>/Product' */

  /* Sum: '<S109>/SubX' incorporates:
   *  Constant: '<S42>/Constant1'
   *  Product: '<S109>/y1z2'
   *  Product: '<S109>/z1y2'
   */
  b_Vector_pbcv[0] = 0.25 * b_Product_dmg0[2] - 0.1 * b_Product_dmg0[1];

  /* Sum: '<S109>/SubY' incorporates:
   *  Constant: '<S42>/Constant1'
   *  Product: '<S109>/x1z2'
   *  Product: '<S109>/z1x2'
   */
  b_Vector_pbcv[1] = 0.1 * b_Product_dmg0[0] - -0.25 * b_Product_dmg0[2];

  /* Sum: '<S109>/SubZ' incorporates:
   *  Constant: '<S42>/Constant1'
   *  Product: '<S109>/x1y2'
   *  Product: '<S109>/y1x2'
   */
  b_Vector_pbcv[2] = -0.25 * b_Product_dmg0[1] - 0.25 * b_Product_dmg0[0];

  /* End of Outputs for SubSystem: '<S42>/for_mom_X_2_for_mom_Y' */

  /* Outputs for Atomic SubSystem: '<S41>/for_mom_X_2_for_mom_Y' */
  /* Sum: '<S81>/Sum' incorporates:
   *  Math: '<S41>/Math Function'
   *  Product: '<S81>/Product1'
   *  Reshape: '<S92>/Reshape'
   */
  for (i_6l = 0; i_6l < 3; i_6l = i_6l + 1) {
    tmp_z = 0.0;
    for (i_6m = 0; i_6m < 3; i_6m = i_6m + 1) {
      tmp_z = tmp_z + b_MathFunction_avjt[i_6l + 3 * i_6m] * 0.0;
    }

    b_Vector_hnym[i_6l] = b_Vector_buas[i_6l] + tmp_z;
  }

  /* End of Sum: '<S81>/Sum' */
  /* End of Outputs for SubSystem: '<S41>/for_mom_X_2_for_mom_Y' */

  /* Outputs for Atomic SubSystem: '<S42>/for_mom_X_2_for_mom_Y' */
  /* Sum: '<S98>/Sum' incorporates:
   *  Math: '<S42>/Math Function'
   *  Product: '<S98>/Product1'
   *  Reshape: '<S109>/Reshape'
   */
  for (i_6n = 0; i_6n < 3; i_6n = i_6n + 1) {
    tmp_10 = 0.0;
    for (i_6o = 0; i_6o < 3; i_6o = i_6o + 1) {
      tmp_10 = tmp_10 + b_MathFunction_g133[i_6n + 3 * i_6o] * 0.0;
    }

    b_Vector_lrwf[i_6n] = b_Vector_pbcv[i_6n] + tmp_10;
  }

  /* End of Sum: '<S98>/Sum' */
  /* End of Outputs for SubSystem: '<S42>/for_mom_X_2_for_mom_Y' */

  /* Outputs for Atomic SubSystem: '<S39>/for_mom_X_2_for_mom_Y' */
  /* Sum: '<S47>/Sum' incorporates:
   *  Math: '<S39>/Math Function'
   *  Product: '<S47>/Product1'
   *  Reshape: '<S58>/Reshape'
   */
  for (i_6p = 0; i_6p < 3; i_6p = i_6p + 1) {
    tmp_11 = 0.0;
    for (i_6q = 0; i_6q < 3; i_6q = i_6q + 1) {
      tmp_11 = tmp_11 + b_MathFunction_dsxx[i_6p + 3 * i_6q] * 0.0;
    }

    b_Vector_fnf0[i_6p] = b_Vector_ebga[i_6p] + tmp_11;
  }

  /* End of Sum: '<S47>/Sum' */
  /* End of Outputs for SubSystem: '<S39>/for_mom_X_2_for_mom_Y' */

  /* Sum: '<S38>/Sum4' incorporates:
   *  Math: '<S40>/Math Function'
   *  Product: '<S64>/Product1'
   *  Reshape: '<S75>/Reshape'
   *  Sum: '<S38>/Sum5'
   *  Sum: '<S64>/Sum'
   */
  for (i_6r = 0; i_6r < 3; i_6r = i_6r + 1) {
    tmp_12 = 0.0;
    for (i_6s = 0; i_6s < 3; i_6s = i_6s + 1) {
      /* Outputs for Atomic SubSystem: '<S40>/for_mom_X_2_for_mom_Y' */
      tmp_12 = tmp_12 + b_MathFunction_cbg2[i_6r + 3 * i_6s] * 0.0;

      /* End of Outputs for SubSystem: '<S40>/for_mom_X_2_for_mom_Y' */
    }

    /* Outputs for Atomic SubSystem: '<S40>/for_mom_X_2_for_mom_Y' */
    b_Vector_bxq5[i_6r] = (b_Vector_pgif[i_6r] + tmp_12) + (b_Vector_hnym[i_6r]
      + b_Vector_lrwf[i_6r]);

    /* End of Outputs for SubSystem: '<S40>/for_mom_X_2_for_mom_Y' */
  }

  /* End of Sum: '<S38>/Sum4' */

  /* Sum: '<S38>/Sum3' */
  for (i_6t = 0; i_6t < 3; i_6t = i_6t + 1) {
    b_Sum3[i_6t] = b_Vector_fnf0[i_6t] + b_Vector_bxq5[i_6t];
  }

  /* End of Sum: '<S38>/Sum3' */

  /* Product: '<S181>/Product1' incorporates:
   *  Reshape: '<S181>/Reshape1'
   *  Reshape: '<S181>/Reshape8'
   */
  for (i_u = 0; i_u < 3; i_u = i_u + 1) {
    b_mom_T_R_B_Nm_fyeb[i_u] = (real_T)
      rtu_Simulation_Control->flg_Aerodynamics_On *
      RMT_FDM_RT_ConstB.Reshape1_e4ip[i_u];
  }

  /* End of Product: '<S181>/Product1' */

  /* Sum: '<S181>/Sum2' incorporates:
   *  Product: '<S181>/Product2'
   *  Reshape: '<S181>/Reshape2'
   *  Reshape: '<S181>/Reshape5'
   *  Reshape: '<S181>/Reshape8'
   *  Reshape: '<S187>/Reshape1'
   *  Sum: '<S181>/Sum4'
   */
  for (i_v = 0; i_v < 3; i_v = i_v + 1) {
    b_Sum2[i_v] = b_mom_T_R_B_Nm_fyeb[i_v] + ((real_T)
      rtu_Simulation_Control->flg_Ground_Contacts_On * b_Sum3[i_v] +
      b_Reshape1_ejex[i_v]);
  }

  /* End of Sum: '<S181>/Sum2' */

  /* Sum: '<S33>/Sum of Elements1' incorporates:
   *  ForEachSliceAssignment generated from: '<S111>/mom_P_R_B_Nm'
   *  Reshape: '<S181>/Reshape8'
   */
  for (i = 0; i < 3; i = i + 1) {
    tmp_0 = b_ImpAsg_InsertedFor_mom_P_R_B_Nm_at_inport_0[i];
    for (i_0 = 1; i_0 < 8; i_0 = i_0 + 1) {
      tmp_0 = tmp_0 + b_ImpAsg_InsertedFor_mom_P_R_B_Nm_at_inport_0[i + i_0 * 3];
    }

    b_mom_T_R_B_Nm_fyeb[i] = tmp_0;
  }

  /* End of Sum: '<S33>/Sum of Elements1' */

  /* Reshape: '<S33>/Reshape1' incorporates:
   *  Reshape: '<S181>/Reshape8'
   */
  for (i_w = 0; i_w < 3; i_w = i_w + 1) {
    b_Reshape1_hoha[i_w] = b_mom_T_R_B_Nm_fyeb[i_w];
  }

  /* End of Reshape: '<S33>/Reshape1' */

  /* Sum: '<S181>/Sum' incorporates:
   *  Product: '<S181>/Product'
   *  Reshape: '<S180>/Reshape8'
   *  Reshape: '<S181>/Reshape8'
   *  Sum: '<S181>/Sum2'
   */
  for (i_x = 0; i_x < 3; i_x = i_x + 1) {
    b_Reshape8[i_x] = (real_T)rtu_Simulation_Control->flg_Propulsion_On *
      b_mom_T_R_B_Nm_fyeb[i_x] + b_Sum2[i_x];
  }

  /* End of Sum: '<S181>/Sum' */

  /* Reshape: '<S181>/Reshape8' incorporates:
   *  Reshape: '<S180>/Reshape8'
   */
  for (i_y = 0; i_y < 3; i_y = i_y + 1) {
    b_mom_T_R_B_Nm_fyeb[i_y] = b_Reshape8[i_y];
  }

  /* End of Reshape: '<S181>/Reshape8' */

  /* Sum: '<S187>/Add1' incorporates:
   *  Reshape: '<S180>/Reshape8'
   *  Sum: '<S190>/Add3'
   */
  for (i_6u = 0; i_6u < 3; i_6u = i_6u + 1) {
    b_Reshape8_0[i_6u] = b_Reshape8[i_6u] - (b_Elementproduct_otn3[i_6u] -
      b_Elementproduct_otn3[3 + i_6u]);
  }

  /* End of Sum: '<S187>/Add1' */

  /* Reshape: '<S187>/Reshape1' incorporates:
   *  Product: '<S187>/Product1'
   *  Product: '<S191>/Product'
   */
  for (i_6v = 0; i_6v < 3; i_6v = i_6v + 1) {
    b_Reshape1_ejex[i_6v] = 0.0;
    for (i_6w = 0; i_6w < 3; i_6w = i_6w + 1) {
      b_Reshape1_ejex[i_6v] = b_Reshape1_ejex[i_6v] +
        RMT_FDM_RT_ConstB.Product_niqp[i_6v + 3 * i_6w] * b_Reshape8_0[i_6w];
    }
  }

  /* End of Reshape: '<S187>/Reshape1' */

  /* Sum: '<S38>/Sum' incorporates:
   *  Product: '<S47>/Product'
   *  Product: '<S64>/Product'
   *  Product: '<S81>/Product'
   *  Product: '<S98>/Product'
   *  SignalConversion: '<S39>/Signal Conversion'
   *  SignalConversion: '<S40>/Signal Conversion'
   *  SignalConversion: '<S41>/Signal Conversion'
   *  SignalConversion: '<S42>/Signal Conversion'
   *  Sum: '<S38>/Sum1'
   *  Sum: '<S38>/Sum2'
   */
  for (i_z = 0; i_z < 3; i_z = i_z + 1) {
    b_Sum_hhfg[i_z] = b_Product_aer5[i_z] + (b_Product_fmjd[i_z] +
      (b_Product_n2sg[i_z] + b_Product_dmg0[i_z]));
  }

  /* End of Sum: '<S38>/Sum' */

  /* Sqrt: '<S36>/Sqrt' incorporates:
   *  Math: '<S36>/Math Function'
   *  Math: '<S36>/Math Function1'
   *  Math: '<S36>/Math Function2'
   *  Reshape: '<S199>/Reshape2'
   *  Sum: '<S199>/Subtract'
   *  Sum: '<S36>/Sum'
   */
  b_Divide1_igly = sqrt((b_Subtract_kaxz[0] * b_Subtract_kaxz[0] +
    b_Subtract_kaxz[1] * b_Subtract_kaxz[1]) + b_Subtract_kaxz[2] *
                        b_Subtract_kaxz[2]);

  /* SignalConversion generated from: '<S29>/Vector Concatenate' incorporates:
   *  Reshape: '<S199>/Reshape2'
   *  Sum: '<S199>/Subtract'
   */
  b_Product_kgt5[0] = b_Subtract_kaxz[0];

  /* SignalConversion generated from: '<S29>/Vector Concatenate' incorporates:
   *  Reshape: '<S199>/Reshape2'
   *  Sum: '<S199>/Subtract'
   */
  b_Product_kgt5[1] = b_Subtract_kaxz[1];

  /* SignalConversion generated from: '<S29>/Vector Concatenate' incorporates:
   *  Reshape: '<S199>/Reshape2'
   *  Sum: '<S199>/Subtract'
   */
  b_Product_kgt5[2] = b_Subtract_kaxz[2];

  /* Product: '<S29>/Product1' incorporates:
   *  Constant: '<S29>/Aerodynamic_Body Drag'
   *  Product: '<S199>/Product'
   *  Reshape: '<S29>/Reshape1'
   */
  for (i_6x = 0; i_6x < 3; i_6x = i_6x + 1) {
    tmp_9[i_6x] = 0.0;
    for (i_6y = 0; i_6y < 3; i_6y = i_6y + 1) {
      tmp_9[i_6x] = tmp_9[i_6x] + rtCP_Aerodynamic_BodyDrag_Value[i_6x + 3 *
        i_6y] * b_Product_kgt5[i_6y];
    }
  }

  for (i_6z = 0; i_6z < 3; i_6z = i_6z + 1) {
    b_Product_kgt5[i_6z] = tmp_9[i_6z];
  }

  /* End of Product: '<S29>/Product1' */

  /* Gain: '<S29>/Gain' incorporates:
   *  Product: '<S199>/Product'
   *  Product: '<S29>/Product'
   */
  for (i_70 = 0; i_70 < 3; i_70 = i_70 + 1) {
    b_Product_kgt5[i_70] = -0.5 * (b_Product_kgt5[i_70] * b_Divide1_igly *
      b_rho_kgDm3);
  }

  /* End of Gain: '<S29>/Gain' */

  /* Product: '<S180>/Product1' incorporates:
   *  Reshape: '<S180>/Reshape1'
   *  Reshape: '<S33>/Reshape'
   */
  for (i_10 = 0; i_10 < 3; i_10 = i_10 + 1) {
    b_Reshape_j1uf[i_10] = (real_T)rtu_Simulation_Control->flg_Aerodynamics_On *
      b_Product_kgt5[i_10];
  }

  /* End of Product: '<S180>/Product1' */

  /* Sum: '<S180>/Sum2' incorporates:
   *  Product: '<S180>/Product2'
   *  Product: '<S180>/Product3'
   *  Reshape: '<S180>/Reshape2'
   *  Reshape: '<S180>/Reshape3'
   *  Reshape: '<S180>/Reshape5'
   *  Reshape: '<S33>/Reshape'
   *  Sum: '<S180>/Sum4'
   */
  for (i_11 = 0; i_11 < 3; i_11 = i_11 + 1) {
    b_Sum2_jdsh[i_11] = b_Reshape_j1uf[i_11] + ((real_T)
      rtu_Simulation_Control->flg_Ground_Contacts_On * b_Sum_hhfg[i_11] +
      (real_T)rtu_Simulation_Control->flg_Weight_Balance_On *
      b_for_G_R_B_N_aifj[i_11]);
  }

  /* End of Sum: '<S180>/Sum2' */

  /* Sum: '<S33>/Sum of Elements' incorporates:
   *  ForEachSliceAssignment generated from: '<S111>/for_P_R_B_N'
   *  Reshape: '<S180>/Reshape8'
   */
  for (i_1 = 0; i_1 < 3; i_1 = i_1 + 1) {
    tmp_1 = b_ImpAsg_InsertedFor_for_P_R_B_N_at_inport_0[i_1];
    for (i_2 = 1; i_2 < 8; i_2 = i_2 + 1) {
      tmp_1 = tmp_1 + b_ImpAsg_InsertedFor_for_P_R_B_N_at_inport_0[i_1 + i_2 * 3];
    }

    b_Reshape8[i_1] = tmp_1;
  }

  /* End of Sum: '<S33>/Sum of Elements' */

  /* Reshape: '<S33>/Reshape' incorporates:
   *  Reshape: '<S180>/Reshape8'
   */
  for (i_12 = 0; i_12 < 3; i_12 = i_12 + 1) {
    b_Reshape_j1uf[i_12] = b_Reshape8[i_12];
  }

  /* End of Reshape: '<S33>/Reshape' */

  /* Sum: '<S180>/Sum' incorporates:
   *  Product: '<S180>/Product'
   *  Reshape: '<S180>/Reshape8'
   *  Reshape: '<S187>/Reshape'
   *  Sum: '<S180>/Sum2'
   */
  for (i_13 = 0; i_13 < 3; i_13 = i_13 + 1) {
    b_Reshape_jgsm[i_13] = (real_T)rtu_Simulation_Control->flg_Propulsion_On *
      b_Reshape8[i_13] + b_Sum2_jdsh[i_13];
  }

  /* End of Sum: '<S180>/Sum' */

  /* Reshape: '<S180>/Reshape8' incorporates:
   *  Reshape: '<S187>/Reshape'
   */
  for (i_14 = 0; i_14 < 3; i_14 = i_14 + 1) {
    b_Reshape8[i_14] = b_Reshape_jgsm[i_14];
  }

  /* End of Reshape: '<S180>/Reshape8' */

  /* Reshape: '<S187>/Reshape' incorporates:
   *  Constant: '<S35>/Constant1'
   *  Product: '<S187>/Divide'
   *  Sum: '<S187>/Add'
   *  Sum: '<S189>/Add3'
   */
  for (i_71 = 0; i_71 < 3; i_71 = i_71 + 1) {
    b_Reshape_jgsm[i_71] = b_Reshape_jgsm[i_71] / 0.966 - (b_Elementproduct[i_71]
      - b_Elementproduct[3 + i_71]);
  }

  /* End of Reshape: '<S187>/Reshape' */

  /* Product: '<S198>/Product2' incorporates:
   *  Math: '<S196>/Math Function4'
   *  Reshape: '<S198>/Reshape2'
   */
  for (i_72 = 0; i_72 < 3; i_72 = i_72 + 1) {
    b_Product2_fd4p[i_72] = 0.0;
    for (i_73 = 0; i_73 < 3; i_73 = i_73 + 1) {
      b_Product2_fd4p[i_72] = b_Product2_fd4p[i_72] + b_M_SB[i_72 + 3 * i_73] *
        b_Reshape2_jvfy[i_73];
    }
  }

  /* End of Product: '<S198>/Product2' */

  /* Product: '<S198>/Product1' incorporates:
   *  Math: '<S196>/Math Function3'
   *  Reshape: '<S198>/Reshape2'
   */
  for (i_74 = 0; i_74 < 3; i_74 = i_74 + 1) {
    b_Product1_lodv[i_74] = 0.0;
    for (i_75 = 0; i_75 < 3; i_75 = i_75 + 1) {
      b_Product1_lodv[i_74] = b_Product1_lodv[i_74] + b_M_AB[i_74 + 3 * i_75] *
        b_Reshape2_jvfy[i_75];
    }
  }

  /* End of Product: '<S198>/Product1' */

  /* Reshape: '<S26>/Reshape3' incorporates:
   *  Integrator: '<S18>/rot_x_K_IB_B_radDs'
   *  Integrator: '<S19>/rot_y_K_IB_B_radDs'
   *  Integrator: '<S20>/rot_z_K_IB_B_radDs'
   */
  tmp_a[0] = localX->w_x_K_IB_B_radDs;
  tmp_a[1] = localX->w_y_K_IB_B_radDs;
  tmp_a[2] = localX->w_z_K_IB_B_radDs;

  /* Reshape: '<S186>/Reshape3' incorporates:
   *  Concatenate: '<S186>/Matrix Concatenate'
   *  Product: '<S186>/Product2'
   */
  for (i_76 = 0; i_76 < 3; i_76 = i_76 + 1) {
    b_Reshape3_czqe[i_76] = 0.0;
    for (i_77 = 0; i_77 < 3; i_77 = i_77 + 1) {
      b_Reshape3_czqe[i_76] = b_Reshape3_czqe[i_76] + b_MatrixConcatenate[i_76 +
        3 * i_77] * tmp_a[i_77];
    }
  }

  /* End of Reshape: '<S186>/Reshape3' */

  /* BusCreator generated from: '<S28>/Bus Assignment' incorporates:
   *  BusAssignment: '<S28>/Bus Assignment'
   */
  b_Outputs.States_Dot.vel_dot_K_R_EB_B_mDs2.u_dot_K_R_EB_B_mDs2 =
    b_Reshape_jgsm[0];
  b_Outputs.States_Dot.vel_dot_K_R_EB_B_mDs2.v_dot_K_R_EB_B_mDs2 =
    b_Reshape_jgsm[1];
  b_Outputs.States_Dot.vel_dot_K_R_EB_B_mDs2.w_dot_K_R_EB_B_mDs2 =
    b_Reshape_jgsm[2];

  /* BusCreator generated from: '<S28>/Bus Assignment' incorporates:
   *  BusAssignment: '<S28>/Bus Assignment'
   */
  b_Outputs.States_Dot.rot_dot_K_IB_B_B_radDs2.w_x_dot_K_IB_B_B_radDs2 =
    b_Reshape1_ejex[0];
  b_Outputs.States_Dot.rot_dot_K_IB_B_B_radDs2.w_y_dot_K_IB_B_B_radDs2 =
    b_Reshape1_ejex[1];
  b_Outputs.States_Dot.rot_dot_K_IB_B_B_radDs2.w_z_dot_K_IB_B_B_radDs2 =
    b_Reshape1_ejex[2];

  /* BusCreator generated from: '<S28>/Bus Assignment' incorporates:
   *  BusAssignment: '<S28>/Bus Assignment'
   */
  b_Outputs.States_Dot.att_dot_euler_radDs.Phi_dot_radDs = b_Reshape3_czqe[0];
  b_Outputs.States_Dot.att_dot_euler_radDs.Theta_dot_radDs = b_Reshape3_czqe[1];
  b_Outputs.States_Dot.att_dot_euler_radDs.Psi_dot_radDs = b_Reshape3_czqe[2];

  /* Reshape: '<S26>/Reshape4' incorporates:
   *  Integrator: '<S21>/vel_x_K'
   *  Integrator: '<S22>/vel_y_K'
   *  Integrator: '<S23>/vel_w_K'
   */
  tmp_b[0] = localX->u_K_R_E_B_mDs;
  tmp_b[1] = localX->v_K_R_E_B_mDs;
  tmp_b[2] = localX->w_K_R_E_B_mDs;

  /* Product: '<S188>/Product' incorporates:
   *  Math: '<S188>/Transpose'
   */
  for (i_78 = 0; i_78 < 3; i_78 = i_78 + 1) {
    b_vel_K_R_E_O_mDs[i_78] = 0.0;
    for (i_79 = 0; i_79 < 3; i_79 = i_79 + 1) {
      b_vel_K_R_E_O_mDs[i_78] = b_vel_K_R_E_O_mDs[i_78] + b_M_OB_h14v_tmp[i_78 +
        3 * i_79] * tmp_b[i_79];
    }
  }

  /* End of Product: '<S188>/Product' */

  /* BusCreator generated from: '<S28>/Bus Assignment' incorporates:
   *  BusAssignment: '<S28>/Bus Assignment'
   *  Product: '<S188>/Product'
   *  Reshape: '<S188>/Reshape'
   */
  b_Outputs.States_Dot.pos_dot_R_E_O_mDs.x_dot_R_E_O_mDs = b_vel_K_R_E_O_mDs[0];
  b_Outputs.States_Dot.pos_dot_R_E_O_mDs.y_dot_R_E_O_mDs = b_vel_K_R_E_O_mDs[1];
  b_Outputs.States_Dot.pos_dot_R_E_O_mDs.z_dot_R_E_O_mDs = b_vel_K_R_E_O_mDs[2];

  /* BusCreator generated from: '<S28>/Bus Assignment' incorporates:
   *  BusAssignment: '<S28>/Bus Assignment'
   */
  b_Outputs.Airframe_Outputs.for_mom_T_R_B.for_T_R_B_N.X_T_R_B_N = b_Reshape8[0];
  b_Outputs.Airframe_Outputs.for_mom_T_R_B.for_T_R_B_N.Y_T_R_B_N = b_Reshape8[1];
  b_Outputs.Airframe_Outputs.for_mom_T_R_B.for_T_R_B_N.Z_P_R_B_N = b_Reshape8[2];

  /* BusCreator generated from: '<S28>/Bus Assignment' incorporates:
   *  BusAssignment: '<S28>/Bus Assignment'
   */
  b_Outputs.Airframe_Outputs.for_mom_T_R_B.mom_T_R_B_Nm.L_T_R_B_Nm =
    b_mom_T_R_B_Nm_fyeb[0];
  b_Outputs.Airframe_Outputs.for_mom_T_R_B.mom_T_R_B_Nm.M_T_R_B_Nm =
    b_mom_T_R_B_Nm_fyeb[1];
  b_Outputs.Airframe_Outputs.for_mom_T_R_B.mom_T_R_B_Nm.N_T_R_B_Nm =
    b_mom_T_R_B_Nm_fyeb[2];

  /* BusCreator generated from: '<S28>/Bus Assignment' incorporates:
   *  BusAssignment: '<S28>/Bus Assignment'
   */
  b_Outputs.Airframe_Outputs.Propulsion_Data_Out.for_mom_P_R_B.for_P_R_B_N.X_P_R_B_N
    = b_Reshape_j1uf[0];
  b_Outputs.Airframe_Outputs.Propulsion_Data_Out.for_mom_P_R_B.for_P_R_B_N.Y_P_R_B_N
    = b_Reshape_j1uf[1];
  b_Outputs.Airframe_Outputs.Propulsion_Data_Out.for_mom_P_R_B.for_P_R_B_N.Z_P_R_B_N
    = b_Reshape_j1uf[2];

  /* BusCreator generated from: '<S28>/Bus Assignment' incorporates:
   *  BusAssignment: '<S28>/Bus Assignment'
   */
  b_Outputs.Airframe_Outputs.Propulsion_Data_Out.for_mom_P_R_B.mom_P_R_B_Nm.L_P_R_B_Nm
    = b_Reshape1_hoha[0];
  b_Outputs.Airframe_Outputs.Propulsion_Data_Out.for_mom_P_R_B.mom_P_R_B_Nm.M_P_R_B_Nm
    = b_Reshape1_hoha[1];
  b_Outputs.Airframe_Outputs.Propulsion_Data_Out.for_mom_P_R_B.mom_P_R_B_Nm.N_P_R_B_Nm
    = b_Reshape1_hoha[2];

  /* BusCreator generated from: '<S28>/Bus Assignment' incorporates:
   *  BusAssignment: '<S28>/Bus Assignment'
   *  Constant: '<S33>/Constant'
   */
  b_Outputs.Airframe_Outputs.Propulsion_Data_Out.Propulsion_Out = 0.0;

  /* BusCreator generated from: '<S28>/Bus Assignment' incorporates:
   *  BusAssignment: '<S28>/Bus Assignment'
   */
  b_Outputs.Airframe_Outputs.for_mom_A_R_B.for_A_R_B_N.X_A_R_B_N =
    b_Product_kgt5[0];
  b_Outputs.Airframe_Outputs.for_mom_A_R_B.for_A_R_B_N.Y_A_R_B_N =
    b_Product_kgt5[1];
  b_Outputs.Airframe_Outputs.for_mom_A_R_B.for_A_R_B_N.Z_A_R_B_N =
    b_Product_kgt5[2];
  if (rtmIsMajorTimeStep(RMT_FDM_RT_M)) {
    /* BusCreator generated from: '<S28>/Bus Assignment' */
    localB->mom_A_R_B_Nm.L_A_R_B_Nm = RMT_FDM_RT_ConstB.Reshape2[0];
    localB->mom_A_R_B_Nm.M_A_R_B_Nm = RMT_FDM_RT_ConstB.Reshape2[1];
    localB->mom_A_R_B_Nm.N_A_R_B_Nm = RMT_FDM_RT_ConstB.Reshape2[2];

    /* BusCreator generated from: '<S28>/Bus Assignment' incorporates:
     *  Constant: '<S35>/Constant1'
     *  Constant: '<S35>/Constant2'
     *  Reshape: '<S35>/Reshape3'
     */
    for (i_15 = 0; i_15 < 3; i_15 = i_15 + 1) {
      localB->Weight_Balance.pos_RG_B_m[i_15] =
        RMT_FDM_RT_ConstB.pos_RG_B_m[i_15];
    }

    localB->Weight_Balance.m_kg = 0.966;
    memcpy(&localB->Weight_Balance.I_R_BB_kgm2[0], &rtCP_Constant2_Value_gfas[0],
           9U * sizeof(real_T));

    /* BusCreator generated from: '<S28>/Bus Assignment' incorporates:
     *  Constant: '<S183>/Constant'
     */
    for (i_16 = 0; i_16 < 3; i_16 = i_16 + 1) {
      localB->Gravitation.acc_G_R_OO_O_mDs2[i_16] =
        rtCP_Constant_Value_pbz0[i_16];
    }
  }

  /* BusCreator generated from: '<S28>/Bus Assignment' incorporates:
   *  BusAssignment: '<S28>/Bus Assignment'
   */
  b_Outputs.Airframe_Outputs.for_mom_A_R_B.mom_A_R_B_Nm = localB->mom_A_R_B_Nm;

  /* BusCreator generated from: '<S28>/Bus Assignment' incorporates:
   *  BusAssignment: '<S28>/Bus Assignment'
   */
  b_Outputs.Airframe_Outputs.for_mom_LDG_R_B.for_LDG_R_B_N.X_LDG_R_B_N =
    b_Sum_hhfg[0];
  b_Outputs.Airframe_Outputs.for_mom_LDG_R_B.for_LDG_R_B_N.Y_LDG_R_B_N =
    b_Sum_hhfg[1];
  b_Outputs.Airframe_Outputs.for_mom_LDG_R_B.for_LDG_R_B_N.Z_LDG_R_B_N =
    b_Sum_hhfg[2];

  /* BusCreator generated from: '<S28>/Bus Assignment' incorporates:
   *  BusAssignment: '<S28>/Bus Assignment'
   */
  b_Outputs.Airframe_Outputs.for_mom_LDG_R_B.mom_LDG_R_B_Nm.L_LDG_R_B_Nm =
    b_Sum3[0];
  b_Outputs.Airframe_Outputs.for_mom_LDG_R_B.mom_LDG_R_B_Nm.M_LDG_R_B_Nm =
    b_Sum3[1];
  b_Outputs.Airframe_Outputs.for_mom_LDG_R_B.mom_LDG_R_B_Nm.N_LDG_R_B_Nm =
    b_Sum3[2];

  /* BusCreator generated from: '<S28>/Bus Assignment' incorporates:
   *  BusAssignment: '<S28>/Bus Assignment'
   */
  b_Outputs.Airframe_Outputs.for_mom_G_R_B.for_G_R_B_N.X_G_R_B_N =
    b_for_G_R_B_N_aifj[0];
  b_Outputs.Airframe_Outputs.for_mom_G_R_B.for_G_R_B_N.Y_G_R_B_N =
    b_for_G_R_B_N_aifj[1];
  b_Outputs.Airframe_Outputs.for_mom_G_R_B.for_G_R_B_N.Z_G_R_B_N =
    b_for_G_R_B_N_aifj[2];

  /* BusCreator generated from: '<S28>/Bus Assignment' incorporates:
   *  BusAssignment: '<S28>/Bus Assignment'
   */
  b_Outputs.Airframe_Outputs.for_mom_G_R_B.mom_G_R_B_Nm.L_G_R_B_Nm =
    b_Reshape2_ksra[0];
  b_Outputs.Airframe_Outputs.for_mom_G_R_B.mom_G_R_B_Nm.M_G_R_B_Nm =
    b_Reshape2_ksra[1];
  b_Outputs.Airframe_Outputs.for_mom_G_R_B.mom_G_R_B_Nm.N_G_R_B_Nm =
    b_Reshape2_ksra[2];

  /* BusCreator generated from: '<S28>/Bus Assignment' incorporates:
   *  BusAssignment: '<S28>/Bus Assignment'
   */
  b_Outputs.Airframe_Outputs.Weight_Balance = localB->Weight_Balance;

  /* BusCreator generated from: '<S28>/Bus Assignment' incorporates:
   *  DataTypeConversion: '<S184>/Data Type Conversion'
   *  Gain: '<S185>/P0'
   *  Gain: '<S185>/gamma*R'
   *  Product: '<S185>/Product2'
   *  Sqrt: '<S185>/a'
   */
  b_Atmosphere.Static_Temperature_ATM_K = b_Sum1_hc1q;
  b_Atmosphere.Speed_of_Sound_mDs = sqrt(401.87433999999996 * b_Sum1_hc1q);
  b_Atmosphere.Static_Pressure_ATM_NDm2 = 101325.0 * b_Switch_iuqm *
    b_Switch_gxqx;
  b_Atmosphere.rho_kgDm3 = b_rho_kgDm3;

  /* BusCreator generated from: '<S28>/Bus Assignment' incorporates:
   *  BusAssignment: '<S28>/Bus Assignment'
   */
  b_Outputs.Environment.Atmosphere = b_Atmosphere;
  b_Outputs.Environment.Gravitation = localB->Gravitation;

  /* BusCreator generated from: '<S28>/Bus Assignment' incorporates:
   *  BusAssignment: '<S28>/Bus Assignment'
   *  Integrator: '<S18>/rot_x_K_IB_B_radDs'
   *  Integrator: '<S19>/rot_y_K_IB_B_radDs'
   *  Integrator: '<S20>/rot_z_K_IB_B_radDs'
   */
  b_Outputs.Motion_Kinematics.Kinematic_Data.rot_K_IB_B_radDs.w_x_K_IB_B_radDs =
    localX->w_x_K_IB_B_radDs;
  b_Outputs.Motion_Kinematics.Kinematic_Data.rot_K_IB_B_radDs.w_y_K_IB_B_radDs =
    localX->w_y_K_IB_B_radDs;
  b_Outputs.Motion_Kinematics.Kinematic_Data.rot_K_IB_B_radDs.w_z_K_IB_B_radDs =
    localX->w_z_K_IB_B_radDs;

  /* BusCreator generated from: '<S28>/Bus Assignment' incorporates:
   *  BusAssignment: '<S28>/Bus Assignment'
   *  Integrator: '<S21>/vel_x_K'
   *  Integrator: '<S22>/vel_y_K'
   *  Integrator: '<S23>/vel_w_K'
   */
  b_Outputs.Motion_Kinematics.Kinematic_Data.vel_K_R_E_B_mDs.u_K_R_E_B_mDs =
    localX->u_K_R_E_B_mDs;
  b_Outputs.Motion_Kinematics.Kinematic_Data.vel_K_R_E_B_mDs.v_K_R_E_B_mDs =
    localX->v_K_R_E_B_mDs;
  b_Outputs.Motion_Kinematics.Kinematic_Data.vel_K_R_E_B_mDs.w_K_R_E_B_mDs =
    localX->w_K_R_E_B_mDs;

  /* BusCreator generated from: '<S28>/Bus Assignment' incorporates:
   *  BusAssignment: '<S28>/Bus Assignment'
   *  Integrator: '<S18>/rot_x_K_IB_B_radDs'
   *  Integrator: '<S19>/rot_y_K_IB_B_radDs'
   *  Integrator: '<S20>/rot_z_K_IB_B_radDs'
   */
  b_Outputs.Motion_Kinematics.Kinematic_Data.rot_K_EB_B_radDs.w_x_K_EB_B_radDs =
    localX->w_x_K_IB_B_radDs;
  b_Outputs.Motion_Kinematics.Kinematic_Data.rot_K_EB_B_radDs.w_y_K_EB_B_radDs =
    localX->w_y_K_IB_B_radDs;
  b_Outputs.Motion_Kinematics.Kinematic_Data.rot_K_EB_B_radDs.w_z_K_EB_B_radDs =
    localX->w_z_K_IB_B_radDs;

  /* BusCreator generated from: '<S28>/Bus Assignment' incorporates:
   *  BusAssignment: '<S28>/Bus Assignment'
   *  Integrator: '<S18>/rot_x_K_IB_B_radDs'
   *  Integrator: '<S19>/rot_y_K_IB_B_radDs'
   *  Integrator: '<S20>/rot_z_K_IB_B_radDs'
   */
  b_Outputs.Motion_Kinematics.Kinematic_Data.rot_K_OB_B_radDs.w_x_K_OB_B_radDs =
    localX->w_x_K_IB_B_radDs;
  b_Outputs.Motion_Kinematics.Kinematic_Data.rot_K_OB_B_radDs.w_y_K_OB_B_radDs =
    localX->w_y_K_IB_B_radDs;
  b_Outputs.Motion_Kinematics.Kinematic_Data.rot_K_OB_B_radDs.w_z_K_OB_B_radDs =
    localX->w_z_K_IB_B_radDs;

  /* BusCreator generated from: '<S28>/Bus Assignment' incorporates:
   *  BusAssignment: '<S28>/Bus Assignment'
   *  Concatenate: '<S219>/Matrix Concaenate'
   *  Math: '<S213>/Math Function'
   *  Math: '<S213>/Math Function6'
   *  Product: '<S214>/Product10'
   */
  memcpy(&b_Outputs.Motion_Kinematics.Kinematic_Data.Kin_Trafo_Matrices.M_BO[0],
         &b_M_BO[0], 9U * sizeof(real_T));
  memcpy(&b_Outputs.Motion_Kinematics.Kinematic_Data.Kin_Trafo_Matrices.M_OB[0],
         &b_M_OB_h14v_tmp[0], 9U * sizeof(real_T));
  memcpy(&b_Outputs.Motion_Kinematics.Kinematic_Data.Kin_Trafo_Matrices.M_NO[0],
         &b_MatrixConcaenate[0], 9U * sizeof(real_T));
  for (i_7b = 0; i_7b < 3; i_7b = i_7b + 1) {
    for (i_7a = 0; i_7a < 3; i_7a = i_7a + 1) {
      b_Outputs.Motion_Kinematics.Kinematic_Data.Kin_Trafo_Matrices.M_ON[i_7a +
        3 * i_7b] = b_MatrixConcaenate[i_7b + 3 * i_7a];
    }
  }

  /* Product: '<S199>/Product' incorporates:
   *  Math: '<S213>/Math Function'
   *  Reshape: '<S199>/Reshape2'
   *  Sum: '<S199>/Subtract'
   */
  for (i_7c = 0; i_7c < 3; i_7c = i_7c + 1) {
    b_Product_kgt5[i_7c] = 0.0;
    for (i_7d = 0; i_7d < 3; i_7d = i_7d + 1) {
      b_Product_kgt5[i_7c] = b_Product_kgt5[i_7c] + b_M_OB_h14v_tmp[i_7c + 3 *
        i_7d] * b_Subtract_kaxz[i_7d];
    }
  }

  /* End of Product: '<S199>/Product' */

  /* BusCreator generated from: '<S28>/Bus Assignment' incorporates:
   *  BusAssignment: '<S28>/Bus Assignment'
   */
  b_Outputs.Motion_Kinematics.Airdata.Aero_Velocities.vel_A_R_E_0_mDs.u_A_R_E_0_mDs
    = b_Product_kgt5[0];
  b_Outputs.Motion_Kinematics.Airdata.Aero_Velocities.vel_A_R_E_0_mDs.v_A_R_E_0_mDs
    = b_Product_kgt5[1];
  b_Outputs.Motion_Kinematics.Airdata.Aero_Velocities.vel_A_R_E_0_mDs.w_A_R_E_0_mDs
    = b_Product_kgt5[2];

  /* BusCreator generated from: '<S28>/Bus Assignment' incorporates:
   *  BusAssignment: '<S28>/Bus Assignment'
   *  Reshape: '<S199>/Reshape2'
   *  Sum: '<S199>/Subtract'
   */
  b_Outputs.Motion_Kinematics.Airdata.Aero_Velocities.vel_A_R_E_B_mDs.u_A_R_E_B_mDs
    = b_Subtract_kaxz[0];
  b_Outputs.Motion_Kinematics.Airdata.Aero_Velocities.vel_A_R_E_B_mDs.v_A_R_E_B_mDs
    = b_Subtract_kaxz[1];
  b_Outputs.Motion_Kinematics.Airdata.Aero_Velocities.vel_A_R_E_B_mDs.w_A_R_E_B_mDs
    = b_Subtract_kaxz[2];

  /* SignalConversion generated from: '<S208>/Vector Concatenate2' incorporates:
   *  Reshape: '<S199>/Reshape2'
   *  Sum: '<S199>/Subtract'
   */
  b_Switch_dxts[0] = b_Subtract_kaxz[0];

  /* SignalConversion generated from: '<S208>/Vector Concatenate2' incorporates:
   *  Reshape: '<S199>/Reshape2'
   *  Sum: '<S199>/Subtract'
   */
  b_Switch_dxts[1] = b_Subtract_kaxz[1];

  /* SignalConversion generated from: '<S208>/Vector Concatenate2' incorporates:
   *  Reshape: '<S199>/Reshape2'
   *  Sum: '<S199>/Subtract'
   */
  b_Switch_dxts[2] = b_Subtract_kaxz[2];

  /* Math: '<S211>/Math Function' */
  for (i_17 = 0; i_17 < 3; i_17 = i_17 + 1) {
    b_MathFunction_do5x[i_17] = b_Switch_dxts[i_17] * b_Switch_dxts[i_17];
  }

  /* End of Math: '<S211>/Math Function' */

  /* Sum: '<S211>/Sum of Elements' */
  tmp_2 = b_MathFunction_do5x[0];
  for (i_3 = 1; i_3 < 3; i_3 = i_3 + 1) {
    tmp_2 = tmp_2 + b_MathFunction_do5x[i_3];
  }

  /* Sqrt: '<S211>/Math Function1' incorporates:
   *  Sum: '<S211>/Sum of Elements'
   *
   * About '<S211>/Math Function1':
   *  Operator: signedSqrt
   */
  if (tmp_2 < 0.0) {
    /* BusCreator generated from: '<S28>/Bus Assignment' incorporates:
     *  BusAssignment: '<S28>/Bus Assignment'
     */
    b_Outputs.Motion_Kinematics.Airdata.Translation_A_R.VEL_A_R_abs_mDs = -sqrt
      (fabs(tmp_2));
  } else {
    /* BusCreator generated from: '<S28>/Bus Assignment' incorporates:
     *  BusAssignment: '<S28>/Bus Assignment'
     */
    b_Outputs.Motion_Kinematics.Airdata.Translation_A_R.VEL_A_R_abs_mDs = sqrt
      (tmp_2);
  }

  /* End of Sqrt: '<S211>/Math Function1' */

  /* BusCreator generated from: '<S28>/Bus Assignment' incorporates:
   *  BusAssignment: '<S28>/Bus Assignment'
   */
  b_Outputs.Motion_Kinematics.Airdata.Translation_A_R.alpha_A_R_rad =
    b_TrigonometricFunction7_n3ob;
  b_Outputs.Motion_Kinematics.Airdata.Translation_A_R.beta_A_R_rad =
    b_TrigonometricFunction1_kiq3;

  /* BusCreator generated from: '<S28>/Bus Assignment' incorporates:
   *  BusAssignment: '<S28>/Bus Assignment'
   *  Concatenate: '<S205>/Matrix Concaenate'
   *  Math: '<S196>/Math Function3'
   *  Math: '<S196>/Math Function4'
   *  Math: '<S196>/Math Function5'
   *  Product: '<S196>/Product'
   *  Product: '<S202>/Product'
   */
  memcpy(&b_Outputs.Motion_Kinematics.Airdata.Aero_Trafo_Matrices.M_BS[0],
         &b_MatrixConcaenate_a1h4[0], 9U * sizeof(real_T));
  memcpy(&b_Outputs.Motion_Kinematics.Airdata.Aero_Trafo_Matrices.M_SB[0],
         &b_M_SB[0], 9U * sizeof(real_T));
  memcpy(&b_Outputs.Motion_Kinematics.Airdata.Aero_Trafo_Matrices.M_BA[0],
         &b_Product_epes[0], 9U * sizeof(real_T));
  memcpy(&b_Outputs.Motion_Kinematics.Airdata.Aero_Trafo_Matrices.M_AB[0],
         &b_M_AB[0], 9U * sizeof(real_T));
  memcpy(&b_Outputs.Motion_Kinematics.Airdata.Aero_Trafo_Matrices.M_AO[0],
         &b_M_AO[0], 9U * sizeof(real_T));
  for (i_7f = 0; i_7f < 3; i_7f = i_7f + 1) {
    for (i_7e = 0; i_7e < 3; i_7e = i_7e + 1) {
      b_Outputs.Motion_Kinematics.Airdata.Aero_Trafo_Matrices.M_OA[i_7e + 3 *
        i_7f] = b_M_AO[i_7f + 3 * i_7e];
    }
  }

  /* BusCreator generated from: '<S28>/Bus Assignment' incorporates:
   *  BusAssignment: '<S28>/Bus Assignment'
   */
  b_Outputs.Motion_Kinematics.Airdata.Aero_Angular_Rates.rot_A_AB_B_radDs.w_x_A_AB_B_radDs
    = b_Reshape2_jvfy[0];
  b_Outputs.Motion_Kinematics.Airdata.Aero_Angular_Rates.rot_A_AB_B_radDs.w_y_A_AB_B_radDs
    = b_Reshape2_jvfy[1];
  b_Outputs.Motion_Kinematics.Airdata.Aero_Angular_Rates.rot_A_AB_B_radDs.w_z_A_AB_B_radDs
    = b_Reshape2_jvfy[2];

  /* BusCreator generated from: '<S28>/Bus Assignment' incorporates:
   *  BusAssignment: '<S28>/Bus Assignment'
   */
  b_Outputs.Motion_Kinematics.Airdata.Aero_Angular_Rates.rot_A_AB_A_radDs.w_x_A_AB_A_radDs
    = b_Product1_lodv[0];
  b_Outputs.Motion_Kinematics.Airdata.Aero_Angular_Rates.rot_A_AB_A_radDs.w_y_A_AB_A_radDs
    = b_Product1_lodv[1];
  b_Outputs.Motion_Kinematics.Airdata.Aero_Angular_Rates.rot_A_AB_A_radDs.w_z_A_AB_A_radDs
    = b_Product1_lodv[2];

  /* BusCreator generated from: '<S28>/Bus Assignment' incorporates:
   *  BusAssignment: '<S28>/Bus Assignment'
   */
  b_Outputs.Motion_Kinematics.Airdata.Aero_Angular_Rates.rot_A_AB_S_radDs.w_x_A_AB_S_radDs
    = b_Product2_fd4p[0];
  b_Outputs.Motion_Kinematics.Airdata.Aero_Angular_Rates.rot_A_AB_S_radDs.w_y_A_AB_S_radDs
    = b_Product2_fd4p[1];
  b_Outputs.Motion_Kinematics.Airdata.Aero_Angular_Rates.rot_A_AB_S_radDs.w_z_A_AB_S_radDs
    = b_Product2_fd4p[2];

  /* BusCreator generated from: '<S28>/Bus Assignment' incorporates:
   *  BusAssignment: '<S28>/Bus Assignment'
   *  Reshape: '<S199>/Reshape2'
   *  Reshape: '<S221>/Reshape1'
   */
  b_Outputs.Motion_Kinematics.Wind_Data.Wind_Velocities.vel_W_R_E_B_mDs.u_W_R_E_B_mDs
    = b_Reshape2_o51o[0];
  b_Outputs.Motion_Kinematics.Wind_Data.Wind_Velocities.vel_W_R_E_B_mDs.v_W_R_E_B_mDs
    = b_Reshape2_o51o[1];
  b_Outputs.Motion_Kinematics.Wind_Data.Wind_Velocities.vel_W_R_E_B_mDs.w_W_R_E_B_mDs
    = b_Reshape2_o51o[2];

  /* BusCreator generated from: '<S28>/Bus Assignment' incorporates:
   *  BusAssignment: '<S28>/Bus Assignment'
   */
  b_Outputs.Motion_Kinematics.Wind_Data.Wind_Velocities.vel_W_R_E_O_mDs.u_W_R_E_O_mDs
    = *rtu_External_Inputs_Wind_Data_vel_W_R_E_O_mDs_u_W_R_E_O_mDs;
  b_Outputs.Motion_Kinematics.Wind_Data.Wind_Velocities.vel_W_R_E_O_mDs.v_W_R_E_O_mDs
    = *rtu_External_Inputs_Wind_Data_vel_W_R_E_O_mDs_v_W_R_E_O_mDs;
  b_Outputs.Motion_Kinematics.Wind_Data.Wind_Velocities.vel_W_R_E_O_mDs.w_W_R_E_O_mDs
    = *rtu_External_Inputs_Wind_Data_vel_W_R_E_O_mDs_w_W_R_E_O_mDs;

  /* SignalConversion generated from: '<S220>/Vector Concatenate' */
  b_Switch_jzso[0] =
    *rtu_External_Inputs_Wind_Data_rot_W_OW_B_radDs_w_x_W_OW_B_radDs;

  /* SignalConversion generated from: '<S220>/Vector Concatenate' */
  b_Switch_jzso[1] =
    *rtu_External_Inputs_Wind_Data_rot_W_OW_B_radDs_w_y_W_OW_B_radDs;

  /* SignalConversion generated from: '<S220>/Vector Concatenate' */
  b_Switch_jzso[2] =
    *rtu_External_Inputs_Wind_Data_rot_W_OW_B_radDs_w_z_W_OW_B_radDs;

  /* Product: '<S220>/Product' incorporates:
   *  Math: '<S213>/Math Function'
   *  Reshape: '<S220>/Reshape1'
   *  Switch: '<S348>/Switch'
   */
  for (i_7g = 0; i_7g < 3; i_7g = i_7g + 1) {
    b_M_OB_h14v_tmp_4[i_7g] = 0.0;
    for (i_7h = 0; i_7h < 3; i_7h = i_7h + 1) {
      b_M_OB_h14v_tmp_4[i_7g] = b_M_OB_h14v_tmp_4[i_7g] + b_M_OB_h14v_tmp[i_7g +
        3 * i_7h] * b_Switch_jzso[i_7h];
    }
  }

  for (i_7i = 0; i_7i < 3; i_7i = i_7i + 1) {
    b_Switch_jzso[i_7i] = b_M_OB_h14v_tmp_4[i_7i];
  }

  /* End of Product: '<S220>/Product' */

  /* BusCreator generated from: '<S28>/Bus Assignment' incorporates:
   *  BusAssignment: '<S28>/Bus Assignment'
   *  Reshape: '<S220>/Reshape2'
   *  Switch: '<S348>/Switch'
   */
  b_Outputs.Motion_Kinematics.Wind_Data.Wind_Angular_Rates.rot_W_0W_0_radDs.w_x_W_0W_0_radDs
    = b_Switch_jzso[0];
  b_Outputs.Motion_Kinematics.Wind_Data.Wind_Angular_Rates.rot_W_0W_0_radDs.w_y_W_0W_0_radDs
    = b_Switch_jzso[1];
  b_Outputs.Motion_Kinematics.Wind_Data.Wind_Angular_Rates.rot_W_0W_0_radDs.w_z_W_0W_0_radDs
    = b_Switch_jzso[2];

  /* BusCreator generated from: '<S28>/Bus Assignment' incorporates:
   *  BusAssignment: '<S28>/Bus Assignment'
   */
  b_Outputs.Motion_Kinematics.Wind_Data.Wind_Angular_Rates.rot_W_OW_B_radDs.w_x_W_OW_B_radDs
    = *rtu_External_Inputs_Wind_Data_rot_W_OW_B_radDs_w_x_W_OW_B_radDs;
  b_Outputs.Motion_Kinematics.Wind_Data.Wind_Angular_Rates.rot_W_OW_B_radDs.w_y_W_OW_B_radDs
    = *rtu_External_Inputs_Wind_Data_rot_W_OW_B_radDs_w_y_W_OW_B_radDs;
  b_Outputs.Motion_Kinematics.Wind_Data.Wind_Angular_Rates.rot_W_OW_B_radDs.w_z_W_OW_B_radDs
    = *rtu_External_Inputs_Wind_Data_rot_W_OW_B_radDs_w_z_W_OW_B_radDs;

  /* Integrator: '<S237>/w_z_int_PRot_P_err_radDs' incorporates:
   *  Constant: '<S235>/Constant2'
   */
  if (rtsiIsModeUpdateTimeStep(RMT_FDM_RT_M->solverInfo)) {
    zcEvent_0 = rt_ZCFcn(RISING_ZERO_CROSSING,
                         &localZCE->w_z_int_PRot_P_err_radDs_Reset_ZCE_e11l,
                         (1.0));

    /* evaluate zero-crossings */
    if ((zcEvent_0 != NO_ZCEVENT) ||
        localDW->w_z_int_PRot_P_err_radDs_DWORK1_ndwy) {
      for (i_18 = 0; i_18 < 3; i_18 = i_18 + 1) {
        localX->w_z_int_PRot_P_err_radDs_iwjk[i_18] =
          RMT_FDM_RT_ConstB.Constant3;
      }
    }
  }

  /* Sum: '<S233>/Sum' incorporates:
   *  Abs: '<S231>/Abs'
   *  Constant: '<S234>/Constant1'
   *  Constant: '<S234>/Constant3'
   *  DataTypeConversion: '<S184>/Data Type Conversion'
   *  Integrator: '<S237>/w_z_int_PRot_P_err_radDs'
   *  Product: '<S231>/Product'
   *  Product: '<S231>/Product1'
   *  Product: '<S231>/Product2'
   *  Product: '<S234>/Product1'
   *  Reshape: '<S230>/Reshape'
   *  Sum: '<S231>/Add'
   *  Sum: '<S231>/Add1'
   *  Sum: '<S231>/Add2'
   *  Sum: '<S231>/Sum'
   *  Sum: '<S234>/Add'
   *  Sum: '<S234>/Sum'
   */
  for (i_7j = 0; i_7j < 3; i_7j = i_7j + 1) {
    tmp_13 = 0.0;
    for (i_7k = 0; i_7k < 3; i_7k = i_7k + 1) {
      tmp_13 = tmp_13 + RMT_FDM_RT_ConstB.Add[i_7j + 3 * i_7k] * b_Reshape[i_7k];
    }

    tmp_c[i_7j] = ((tmp_13 + (fabs(b_Reshape[i_7j]) * b_Reshape[i_7j] * 0.0 +
      0.0003 * b_Reshape[i_7j] * b_Reshape[i_7j])) + ((b_Sum1_hc1q - 298.0) *
      0.0005 + rtCP_Constant3_Value_dg45[i_7j])) -
      localX->w_z_int_PRot_P_err_radDs_iwjk[i_7j];
  }

  /* End of Sum: '<S233>/Sum' */
  for (i_7l = 0; i_7l < 3; i_7l = i_7l + 1) {
    /* Product: '<S237>/Product' incorporates:
     *  Constant: '<S233>/Constant'
     *  Product: '<S233>/Product'
     */
    localB->Product[i_7l] = 157.07963267948966 * tmp_c[i_7l];
  }

  for (i_19 = 0; i_19 < 3; i_19 = i_19 + 1) {
    /* Product: '<S238>/Product' incorporates:
     *  Constant: '<S233>/Constant'
     *  Integrator: '<S237>/w_z_int_PRot_P_err_radDs'
     *  Integrator: '<S238>/w_z_int_PRot_P_err_radDs'
     *  Product: '<S233>/Product1'
     *  Sum: '<S233>/Sum1'
     */
    localB->Product_jgrl[i_19] = 157.07963267948966 *
      (localX->w_z_int_PRot_P_err_radDs_iwjk[i_19] -
       localX->w_z_int_PRot_P_err_radDs[i_19]);
  }

  /* SignalConversion generated from: '<S365>/Vector Concatenate' incorporates:
   *  BusCreator generated from: '<S28>/Bus Assignment'
   */
  b_Switch_jlc4[0] = b_Reshape8[0];

  /* SignalConversion generated from: '<S365>/Vector Concatenate' incorporates:
   *  BusCreator generated from: '<S28>/Bus Assignment'
   */
  b_Switch_jlc4[1] = b_Reshape8[1];

  /* SignalConversion generated from: '<S365>/Vector Concatenate' incorporates:
   *  BusCreator generated from: '<S28>/Bus Assignment'
   */
  b_Switch_jlc4[2] = b_Reshape8[2];

  /* Product: '<S365>/Product1' incorporates:
   *  BusCreator generated from: '<S28>/Bus Assignment'
   *  Reshape: '<S365>/Reshape'
   *  Switch: '<S367>/Switch'
   */
  for (i_7m = 0; i_7m < 3; i_7m = i_7m + 1) {
    b_Switch_jlc4[i_7m] = b_Switch_jlc4[i_7m] / localB->Weight_Balance.m_kg;
  }

  /* End of Product: '<S365>/Product1' */

  /* Concatenate: '<S376>/Vector Concatenate3' incorporates:
   *  Concatenate: '<S376>/Vector Concatenate'
   *  Concatenate: '<S376>/Vector Concatenate1'
   *  Concatenate: '<S376>/Vector Concatenate2'
   */
  for (i_7n = 0; i_7n < 3; i_7n = i_7n + 1) {
    b_VectorConcatenate_iewf[3 * i_7n] = b_VectorConcatenate_id0h[i_7n];
  }

  for (i_7o = 0; i_7o < 3; i_7o = i_7o + 1) {
    b_VectorConcatenate_iewf[1 + 3 * i_7o] =
      RMT_FDM_RT_ConstB.VectorConcatenate1_j0xr[i_7o];
  }

  for (i_7p = 0; i_7p < 3; i_7p = i_7p + 1) {
    b_VectorConcatenate_iewf[2 + 3 * i_7p] = b_VectorConcatenate2_b5g4[i_7p];
  }

  /* End of Concatenate: '<S376>/Vector Concatenate3' */

  /* Concatenate: '<S377>/Vector Concatenate3' incorporates:
   *  Concatenate: '<S377>/Vector Concatenate'
   *  Concatenate: '<S377>/Vector Concatenate1'
   *  Concatenate: '<S377>/Vector Concatenate2'
   */
  for (i_7q = 0; i_7q < 3; i_7q = i_7q + 1) {
    b_VectorConcatenate_g5kk[3 * i_7q] = b_VectorConcatenate_arer[i_7q];
  }

  for (i_7r = 0; i_7r < 3; i_7r = i_7r + 1) {
    b_VectorConcatenate_g5kk[1 + 3 * i_7r] = b_VectorConcatenate1_eeyd[i_7r];
  }

  for (i_7s = 0; i_7s < 3; i_7s = i_7s + 1) {
    b_VectorConcatenate_g5kk[2 + 3 * i_7s] =
      RMT_FDM_RT_ConstB.VectorConcatenate2_nsel[i_7s];
  }

  /* End of Concatenate: '<S377>/Vector Concatenate3' */

  /* Concatenate: '<S375>/Vector Concatenate3' incorporates:
   *  Concatenate: '<S375>/Vector Concatenate'
   *  Concatenate: '<S375>/Vector Concatenate1'
   *  Concatenate: '<S375>/Vector Concatenate2'
   */
  for (i_7t = 0; i_7t < 3; i_7t = i_7t + 1) {
    tmp_d[3 * i_7t] = RMT_FDM_RT_ConstB.VectorConcatenate_icwp[i_7t];
  }

  for (i_7u = 0; i_7u < 3; i_7u = i_7u + 1) {
    tmp_d[1 + 3 * i_7u] = b_VectorConcatenate1_llo0[i_7u];
  }

  for (i_7v = 0; i_7v < 3; i_7v = i_7v + 1) {
    tmp_d[2 + 3 * i_7v] = b_VectorConcatenate2_akq5[i_7v];
  }

  /* End of Concatenate: '<S375>/Vector Concatenate3' */

  /* Product: '<S374>/Product10' */
  for (i_7w = 0; i_7w < 3; i_7w = i_7w + 1) {
    for (i_7x = 0; i_7x < 3; i_7x = i_7x + 1) {
      b_VectorConcatenate_iewf_tmp = i_7w + 3 * i_7x;
      b_VectorConcatenate_iewf_0[b_VectorConcatenate_iewf_tmp] = 0.0;
      for (i_7y = 0; i_7y < 3; i_7y = i_7y + 1) {
        b_VectorConcatenate_iewf_0[b_VectorConcatenate_iewf_tmp] =
          b_VectorConcatenate_iewf_0[b_VectorConcatenate_iewf_tmp] +
          b_VectorConcatenate_iewf[i_7w + 3 * i_7y] *
          b_VectorConcatenate_g5kk[i_7y + 3 * i_7x];
      }
    }
  }

  for (i_7z = 0; i_7z < 3; i_7z = i_7z + 1) {
    for (i_80 = 0; i_80 < 3; i_80 = i_80 + 1) {
      tmp_16 = i_7z + 3 * i_80;
      tmp_e[tmp_16] = 0.0;
      for (i_81 = 0; i_81 < 3; i_81 = i_81 + 1) {
        tmp_e[tmp_16] = tmp_e[tmp_16] + tmp_d[i_7z + 3 * i_81] *
          b_VectorConcatenate_iewf_0[i_81 + 3 * i_80];
      }
    }
  }

  /* End of Product: '<S374>/Product10' */

  /* Sum: '<S365>/Sum' incorporates:
   *  BusCreator generated from: '<S28>/Bus Assignment'
   *  Product: '<S365>/Product'
   *  Reshape: '<S365>/Reshape1'
   *  Switch: '<S348>/Switch'
   *  Switch: '<S367>/Switch'
   */
  for (i_82 = 0; i_82 < 3; i_82 = i_82 + 1) {
    tmp_14 = 0.0;
    for (i_83 = 0; i_83 < 3; i_83 = i_83 + 1) {
      tmp_14 = tmp_14 + tmp_e[i_82 + 3 * i_83] *
        localB->Gravitation.acc_G_R_OO_O_mDs2[i_83];
    }

    b_Switch_jzso[i_82] = b_Switch_jlc4[i_82] - tmp_14;
  }

  /* End of Sum: '<S365>/Sum' */

  /* Integrator: '<S372>/w_z_int_PRot_P_err_radDs' incorporates:
   *  Constant: '<S370>/Constant2'
   */
  if (rtsiIsModeUpdateTimeStep(RMT_FDM_RT_M->solverInfo)) {
    zcEvent_1 = rt_ZCFcn(RISING_ZERO_CROSSING,
                         &localZCE->w_z_int_PRot_P_err_radDs_Reset_ZCE_c4n4,
                         (1.0));

    /* evaluate zero-crossings */
    if ((zcEvent_1 != NO_ZCEVENT) ||
        localDW->w_z_int_PRot_P_err_radDs_DWORK1_ev2m) {
      for (i_1a = 0; i_1a < 3; i_1a = i_1a + 1) {
        localX->w_z_int_PRot_P_err_radDs_auhp[i_1a] =
          RMT_FDM_RT_ConstB.Constant3_ngx0;
      }
    }
  }

  /* Sum: '<S368>/Sum' incorporates:
   *  Abs: '<S366>/Abs'
   *  Constant: '<S369>/Constant1'
   *  Constant: '<S369>/Constant3'
   *  DataTypeConversion: '<S184>/Data Type Conversion'
   *  Integrator: '<S372>/w_z_int_PRot_P_err_radDs'
   *  Product: '<S366>/Product'
   *  Product: '<S366>/Product1'
   *  Product: '<S366>/Product2'
   *  Product: '<S369>/Product1'
   *  Reshape: '<S365>/Reshape2'
   *  Sum: '<S366>/Add'
   *  Sum: '<S366>/Add1'
   *  Sum: '<S366>/Add2'
   *  Sum: '<S366>/Sum'
   *  Sum: '<S369>/Add'
   *  Sum: '<S369>/Sum'
   *  Switch: '<S348>/Switch'
   */
  for (i_84 = 0; i_84 < 3; i_84 = i_84 + 1) {
    tmp_15 = 0.0;
    for (i_85 = 0; i_85 < 3; i_85 = i_85 + 1) {
      tmp_15 = tmp_15 + RMT_FDM_RT_ConstB.Add_gddl[i_84 + 3 * i_85] *
        b_Switch_jzso[i_85];
    }

    tmp_f[i_84] = ((tmp_15 + (fabs(b_Switch_jzso[i_84]) * b_Switch_jzso[i_84] *
      0.0 + 0.0003 * b_Switch_jzso[i_84] * b_Switch_jzso[i_84])) + ((b_Sum1_hc1q
      - 298.0) * 0.0006 + rtCP_Constant3_Value_dn01[i_84])) -
      localX->w_z_int_PRot_P_err_radDs_auhp[i_84];
  }

  /* End of Sum: '<S368>/Sum' */
  for (i_86 = 0; i_86 < 3; i_86 = i_86 + 1) {
    /* Product: '<S372>/Product' incorporates:
     *  Constant: '<S368>/Constant'
     *  Product: '<S368>/Product'
     */
    localB->Product_dhil[i_86] = 157.07963267948966 * tmp_f[i_86];
  }

  /* Integrator: '<S373>/w_z_int_PRot_P_err_radDs' incorporates:
   *  Constant: '<S371>/Constant2'
   */
  if (rtsiIsModeUpdateTimeStep(RMT_FDM_RT_M->solverInfo)) {
    zcEvent_2 = rt_ZCFcn(RISING_ZERO_CROSSING,
                         &localZCE->w_z_int_PRot_P_err_radDs_Reset_ZCE_gyn1,
                         (1.0));

    /* evaluate zero-crossings */
    if ((zcEvent_2 != NO_ZCEVENT) ||
        localDW->w_z_int_PRot_P_err_radDs_DWORK1_kugd) {
      for (i_1b = 0; i_1b < 3; i_1b = i_1b + 1) {
        localX->w_z_int_PRot_P_err_radDs_nmyl[i_1b] =
          RMT_FDM_RT_ConstB.Constant3_jham;
      }
    }
  }

  for (i_1c = 0; i_1c < 3; i_1c = i_1c + 1) {
    /* Product: '<S373>/Product' incorporates:
     *  Constant: '<S368>/Constant'
     *  Integrator: '<S372>/w_z_int_PRot_P_err_radDs'
     *  Integrator: '<S373>/w_z_int_PRot_P_err_radDs'
     *  Product: '<S368>/Product1'
     *  Sum: '<S368>/Sum1'
     */
    localB->Product_eh41[i_1c] = 157.07963267948966 *
      (localX->w_z_int_PRot_P_err_radDs_auhp[i_1c] -
       localX->w_z_int_PRot_P_err_radDs_nmyl[i_1c]);
  }

  if (rtmIsMajorTimeStep(RMT_FDM_RT_M)) {
    /* RandomNumber: '<S364>/Random Number2' incorporates:
     *  RandomNumber: '<S316>/Random Number2'
     */
    for (iU_0 = 0; iU_0 < 3; iU_0 = iU_0 + 1) {
      b_RandomNumber2_ouvm[iU_0] = localDW->NextOutput_k1ay[iU_0];
    }

    /* End of RandomNumber: '<S364>/Random Number2' */
    for (i_87 = 0; i_87 < 3; i_87 = i_87 + 1) {
      /* Gain: '<S364>/Gain' incorporates:
       *  RandomNumber: '<S316>/Random Number2'
       */
      localB->Gain_nkvy[i_87] = 0.0;
      for (i_88 = 0; i_88 < 3; i_88 = i_88 + 1) {
        localB->Gain_nkvy[i_87] = localB->Gain_nkvy[i_87] +
          rtCP_Gain_Gain_hoji[i_87 + 3 * i_88] * b_RandomNumber2_ouvm[i_88];
      }
    }
  }

  /* Switch: '<S367>/Switch' incorporates:
   *  Gain: '<S364>/Gain'
   *  Reshape: '<S365>/Reshape2'
   *  Sum: '<S364>/Add'
   *  Switch: '<S348>/Switch'
   */
  if (rtu_Simulation_Control->flg_Enable_Sensor_Errors) {
    for (i_1d = 0; i_1d < 3; i_1d = i_1d + 1) {
      /* Integrator: '<S373>/w_z_int_PRot_P_err_radDs' */
      u0_1 = localX->w_z_int_PRot_P_err_radDs_nmyl[i_1d];

      /* Saturate: '<S364>/Saturation' */
      if (u0_1 > 49.033249999999995) {
        y_2 = 49.033249999999995;
      } else if (u0_1 < -49.033249999999995) {
        y_2 = -49.033249999999995;
      } else {
        y_2 = u0_1;
      }

      /* End of Saturate: '<S364>/Saturation' */
      b_Switch_jlc4[i_1d] = y_2 + localB->Gain_nkvy[i_1d];
    }
  } else {
    for (i_25 = 0; i_25 < 3; i_25 = i_25 + 1) {
      b_Switch_jlc4[i_25] = b_Switch_jzso[i_25];
    }
  }

  /* End of Switch: '<S367>/Switch' */

  /* Reshape: '<S344>/Reshape1' incorporates:
   *  Integrator: '<S21>/vel_x_K'
   *  Integrator: '<S22>/vel_y_K'
   *  Integrator: '<S23>/vel_w_K'
   */
  tmp_g[0] = localX->u_K_R_E_B_mDs;
  tmp_g[1] = localX->v_K_R_E_B_mDs;
  tmp_g[2] = localX->w_K_R_E_B_mDs;

  /* Product: '<S344>/Product' incorporates:
   *  Math: '<S344>/Math Function'
   *  Switch: '<S346>/Switch'
   */
  for (i_89 = 0; i_89 < 3; i_89 = i_89 + 1) {
    b_Switch_dxts[i_89] = 0.0;
    for (i_8a = 0; i_8a < 3; i_8a = i_8a + 1) {
      b_Switch_dxts[i_89] = b_Switch_dxts[i_89] + b_M_OB_k2bs[i_89 + 3 * i_8a] *
        tmp_g[i_8a];
    }
  }

  /* End of Product: '<S344>/Product' */

  /* SignalConversion generated from: '<S342>/Vector Concatenate3' incorporates:
   *  Concatenate: '<S342>/Vector Concatenate3'
   *  Reshape: '<S344>/Reshape2'
   *  Switch: '<S346>/Switch'
   */
  localB->VectorConcatenate3[0] = b_Switch_dxts[0];

  /* SignalConversion generated from: '<S342>/Vector Concatenate3' incorporates:
   *  Concatenate: '<S342>/Vector Concatenate3'
   *  Reshape: '<S344>/Reshape2'
   *  Switch: '<S346>/Switch'
   */
  localB->VectorConcatenate3[1] = b_Switch_dxts[1];

  /* SignalConversion generated from: '<S342>/Vector Concatenate3' incorporates:
   *  Concatenate: '<S342>/Vector Concatenate3'
   *  Reshape: '<S344>/Reshape2'
   *  Switch: '<S346>/Switch'
   */
  localB->VectorConcatenate3[2] = b_Switch_dxts[2];

  /* SignalConversion generated from: '<S379>/Vector Concatenate' incorporates:
   *  Integrator: '<S18>/rot_x_K_IB_B_radDs'
   */
  b_Switch_kohd[0] = localX->w_x_K_IB_B_radDs;

  /* SignalConversion generated from: '<S379>/Vector Concatenate' incorporates:
   *  Integrator: '<S19>/rot_y_K_IB_B_radDs'
   */
  b_Switch_kohd[1] = localX->w_y_K_IB_B_radDs;

  /* SignalConversion generated from: '<S379>/Vector Concatenate' incorporates:
   *  Integrator: '<S20>/rot_z_K_IB_B_radDs'
   */
  b_Switch_kohd[2] = localX->w_z_K_IB_B_radDs;

  /* Reshape: '<S379>/Reshape' */
  for (i_1e = 0; i_1e < 3; i_1e = i_1e + 1) {
    b_Reshape_j045[i_1e] = b_Switch_kohd[i_1e];
  }

  /* Product: '<S381>/Product' incorporates:
   *  Reshape: '<S379>/Reshape'
   *  Sum: '<S381>/Add'
   *  Switch: '<S382>/Switch'
   */
  for (i_8b = 0; i_8b < 3; i_8b = i_8b + 1) {
    tmp_h[i_8b] = 0.0;
    for (i_8c = 0; i_8c < 3; i_8c = i_8c + 1) {
      tmp_h[i_8b] = tmp_h[i_8b] + RMT_FDM_RT_ConstB.Add_gfwn[i_8b + 3 * i_8c] *
        b_Switch_kohd[i_8c];
    }
  }

  for (i_8d = 0; i_8d < 3; i_8d = i_8d + 1) {
    b_Switch_kohd[i_8d] = tmp_h[i_8d];
  }

  /* End of Product: '<S381>/Product' */

  /* Integrator: '<S387>/w_z_int_PRot_P_err_radDs' incorporates:
   *  Constant: '<S385>/Constant2'
   */
  if (rtsiIsModeUpdateTimeStep(RMT_FDM_RT_M->solverInfo)) {
    zcEvent_3 = rt_ZCFcn(RISING_ZERO_CROSSING,
                         &localZCE->w_z_int_PRot_P_err_radDs_Reset_ZCE_om2w,
                         (1.0));

    /* evaluate zero-crossings */
    if ((zcEvent_3 != NO_ZCEVENT) ||
        localDW->w_z_int_PRot_P_err_radDs_DWORK1_h3i2) {
      for (i_1f = 0; i_1f < 3; i_1f = i_1f + 1) {
        localX->w_z_int_PRot_P_err_radDs_fg2g[i_1f] =
          RMT_FDM_RT_ConstB.Constant3_fb5g;
      }
    }
  }

  for (i_1g = 0; i_1g < 3; i_1g = i_1g + 1) {
    /* Product: '<S387>/Product' incorporates:
     *  Abs: '<S381>/Abs'
     *  Constant: '<S383>/Constant'
     *  Constant: '<S384>/Constant1'
     *  Constant: '<S384>/Constant3'
     *  DataTypeConversion: '<S184>/Data Type Conversion'
     *  Integrator: '<S387>/w_z_int_PRot_P_err_radDs'
     *  Product: '<S381>/Product1'
     *  Product: '<S381>/Product2'
     *  Product: '<S383>/Product'
     *  Product: '<S384>/Product1'
     *  Reshape: '<S379>/Reshape'
     *  Sum: '<S381>/Add1'
     *  Sum: '<S381>/Add2'
     *  Sum: '<S381>/Sum'
     *  Sum: '<S383>/Sum'
     *  Sum: '<S384>/Add'
     *  Sum: '<S384>/Sum'
     *  Switch: '<S382>/Switch'
     */
    localB->Product_f5uz[i_1g] = 157.07963267948966 * (((b_Switch_kohd[i_1g] +
      (fabs(b_Reshape_j045[i_1g]) * b_Reshape_j045[i_1g] * 0.0 + 0.0003 *
       b_Reshape_j045[i_1g] * b_Reshape_j045[i_1g])) + ((b_Sum1_hc1q - 298.0) *
      0.0005 + rtCP_Constant3_Value_h5nx[i_1g])) -
      localX->w_z_int_PRot_P_err_radDs_fg2g[i_1g]);
  }

  /* Integrator: '<S388>/w_z_int_PRot_P_err_radDs' incorporates:
   *  Constant: '<S386>/Constant2'
   */
  if (rtsiIsModeUpdateTimeStep(RMT_FDM_RT_M->solverInfo)) {
    zcEvent_4 = rt_ZCFcn(RISING_ZERO_CROSSING,
                         &localZCE->w_z_int_PRot_P_err_radDs_Reset_ZCE_jte2,
                         (1.0));

    /* evaluate zero-crossings */
    if ((zcEvent_4 != NO_ZCEVENT) ||
        localDW->w_z_int_PRot_P_err_radDs_DWORK1_l3ag) {
      for (i_1h = 0; i_1h < 3; i_1h = i_1h + 1) {
        localX->w_z_int_PRot_P_err_radDs_babv[i_1h] =
          RMT_FDM_RT_ConstB.Constant3_i22d;
      }
    }
  }

  for (i_1i = 0; i_1i < 3; i_1i = i_1i + 1) {
    /* Product: '<S388>/Product' incorporates:
     *  Constant: '<S383>/Constant'
     *  Integrator: '<S387>/w_z_int_PRot_P_err_radDs'
     *  Integrator: '<S388>/w_z_int_PRot_P_err_radDs'
     *  Product: '<S383>/Product1'
     *  Sum: '<S383>/Sum1'
     */
    localB->Product_a2ds[i_1i] = 157.07963267948966 *
      (localX->w_z_int_PRot_P_err_radDs_fg2g[i_1i] -
       localX->w_z_int_PRot_P_err_radDs_babv[i_1i]);
  }

  /* RateTransition: '<S342>/Rate Transition2' */
  if (rtmIsMajorTimeStep(RMT_FDM_RT_M)) {
    /* RandomNumber: '<S380>/Random Number2' incorporates:
     *  RandomNumber: '<S316>/Random Number2'
     */
    for (iU_1 = 0; iU_1 < 3; iU_1 = iU_1 + 1) {
      b_RandomNumber2_ouvm[iU_1] = localDW->NextOutput_pvtx[iU_1];
    }

    /* End of RandomNumber: '<S380>/Random Number2' */
    for (i_8e = 0; i_8e < 3; i_8e = i_8e + 1) {
      /* Gain: '<S380>/Gain' incorporates:
       *  RandomNumber: '<S316>/Random Number2'
       */
      localB->Gain_g3gl[i_8e] = 0.0;
      for (i_8f = 0; i_8f < 3; i_8f = i_8f + 1) {
        localB->Gain_g3gl[i_8e] = localB->Gain_g3gl[i_8e] +
          rtCP_Gain_Gain_joui[i_8e + 3 * i_8f] * b_RandomNumber2_ouvm[i_8f];
      }
    }

    /* RandomNumber: '<S316>/Random Number2' */
    for (iU_2 = 0; iU_2 < 3; iU_2 = iU_2 + 1) {
      b_RandomNumber2_ouvm[iU_2] = localDW->NextOutput_ba35[iU_2];
    }

    /* End of RandomNumber: '<S316>/Random Number2' */

    /* RateTransition: '<S342>/Rate Transition2' */
    for (i_1o = 0; i_1o < 3; i_1o = i_1o + 1) {
      localB->RateTransition2[i_1o] = localB->VectorConcatenate3[i_1o];
    }

    /* End of RateTransition: '<S342>/Rate Transition2' */
  }

  /* End of RateTransition: '<S342>/Rate Transition2' */

  /* Switch: '<S382>/Switch' incorporates:
   *  Gain: '<S380>/Gain'
   *  Reshape: '<S379>/Reshape'
   *  SignalConversion: '<S380>/Signal Conversion1'
   *  Sum: '<S380>/Add'
   */
  if (rtu_Simulation_Control->flg_Enable_Sensor_Errors) {
    for (i_1j = 0; i_1j < 3; i_1j = i_1j + 1) {
      /* Integrator: '<S388>/w_z_int_PRot_P_err_radDs' */
      u0_2 = localX->w_z_int_PRot_P_err_radDs_babv[i_1j];

      /* Saturate: '<S380>/Saturation' */
      if (u0_2 > 5.2359877559829888) {
        y_3 = 5.2359877559829888;
      } else if (u0_2 < -5.2359877559829888) {
        y_3 = -5.2359877559829888;
      } else {
        y_3 = u0_2;
      }

      /* End of Saturate: '<S380>/Saturation' */
      b_Switch_kohd[i_1j] = y_3 + localB->Gain_g3gl[i_1j];
    }
  } else {
    for (i_24 = 0; i_24 < 3; i_24 = i_24 + 1) {
      b_Switch_kohd[i_24] = b_Reshape_j045[i_24];
    }
  }

  /* End of Switch: '<S382>/Switch' */
  if (rtmIsMajorTimeStep(RMT_FDM_RT_M) && rtmIsSampleHit(RMT_FDM_RT_M, 2)) {
    /* RandomNumber: '<S354>/Random Number' incorporates:
     *  Sum: '<S342>/Sum5'
     */
    for (iU_3 = 0; iU_3 < 3; iU_3 = iU_3 + 1) {
      b_Sum5_hbb1[iU_3] = localDW->NextOutput_kxhu[iU_3];
    }

    /* End of RandomNumber: '<S354>/Random Number' */
    for (i_1k = 0; i_1k < 3; i_1k = i_1k + 1) {
      /* DiscreteIntegrator: '<S354>/Discrete-Time Integrator2' */
      localB->DiscreteTimeIntegrator2[i_1k] =
        localDW->DiscreteTimeIntegrator2_DSTATE[i_1k];
    }

    for (i_1l = 0; i_1l < 3; i_1l = i_1l + 1) {
      /* Sum: '<S354>/Add' incorporates:
       *  Constant: '<S345>/C2'
       *  DiscreteIntegrator: '<S354>/Discrete-Time Integrator2'
       *  Gain: '<S354>/Gain2'
       *  Product: '<S354>/Divide1'
       *  Product: '<S354>/Product'
       *  Product: '<S354>/Product1'
       *  Sqrt: '<S354>/Sqrt'
       *  Sum: '<S342>/Sum5'
       */
      localB->w_dot[i_1l] = rtCP_C2_Value[i_1l] * b_Sum5_hbb1[i_1l] *
        RMT_FDM_RT_ConstB.Sqrt[i_1l] + -localB->DiscreteTimeIntegrator2[i_1l] /
        100.0;
    }

    for (i_1m = 0; i_1m < 3; i_1m = i_1m + 1) {
      /* DiscreteIntegrator: '<S345>/Discrete-Time Integrator' */
      localB->DiscreteTimeIntegrator[i_1m] =
        localDW->DiscreteTimeIntegrator_DSTATE[i_1m];
    }

    for (i_1n = 0; i_1n < 3; i_1n = i_1n + 1) {
      /* Gain: '<S345>/Gain1' incorporates:
       *  DiscreteIntegrator: '<S345>/Discrete-Time Integrator'
       *  DiscreteIntegrator: '<S354>/Discrete-Time Integrator2'
       *  Sum: '<S345>/Sum1'
       */
      localB->Gain1[i_1n] = 0.05 * (localB->DiscreteTimeIntegrator2[i_1n] -
        localB->DiscreteTimeIntegrator[i_1n]);
    }

    for (i_1p = 0; i_1p < 3; i_1p = i_1p + 1) {
      /* Reshape: '<S352>/Reshape1' */
      localB->Reshape1[i_1p] = localB->RateTransition2[i_1p];
    }

    /* DiscreteFir: '<S352>/Discrete FIR Filter' incorporates:
     *  Reshape: '<S352>/Reshape1'
     *  Sum: '<S342>/Sum5'
     */
    uIdx = 0;
    for (k = 0; k < 3; k = k + 1) {
      acc1 = localB->Reshape1[uIdx] * 0.5;
      uIdx = uIdx + 1;
      b_Sum5_hbb1[k] = acc1 + localDW->DiscreteFIRFilter_states[k] * 0.5;
    }

    /* End of DiscreteFir: '<S352>/Discrete FIR Filter' */

    /* RandomNumber: '<S352>/Random Number' incorporates:
     *  Sum: '<S342>/Sum1'
     */
    for (iU_4 = 0; iU_4 < 3; iU_4 = iU_4 + 1) {
      b_Sum1_pk2u[iU_4] = localDW->NextOutput_h3vk[iU_4];
    }

    /* End of RandomNumber: '<S352>/Random Number' */
    for (i_1q = 0; i_1q < 3; i_1q = i_1q + 1) {
      /* Sum: '<S352>/Sum2' incorporates:
       *  Gain: '<S345>/Gain1'
       *  Sum: '<S342>/Sum1'
       *  Sum: '<S342>/Sum5'
       */
      localB->Sum2[i_1q] = (b_Sum5_hbb1[i_1q] + localB->Gain1[i_1q]) +
        b_Sum1_pk2u[i_1q];
    }
  }

  /* RateTransition: '<S342>/Rate Transition1' */
  if (rtmIsMajorTimeStep(RMT_FDM_RT_M)) {
    tmp_i = localDW->RateTransition1_ActiveBufIdx * 3;
    for (i_8g = 0; i_8g < 3; i_8g = i_8g + 1) {
      localB->RateTransition1[i_8g] = localDW->RateTransition1_Buffer[i_8g +
        tmp_i];
    }
  }

  /* End of RateTransition: '<S342>/Rate Transition1' */

  /* Switch: '<S348>/Switch' incorporates:
   *  RateTransition: '<S342>/Rate Transition1'
   *  SignalConversion: '<S342>/Signal Conversion1'
   */
  if (rtu_Simulation_Control->flg_Enable_Sensor_Errors) {
    for (i_1r = 0; i_1r < 3; i_1r = i_1r + 1) {
      b_Switch_jzso[i_1r] = localB->RateTransition1[i_1r];
    }
  } else {
    for (i_23 = 0; i_23 < 3; i_23 = i_23 + 1) {
      b_Switch_jzso[i_23] = localB->VectorConcatenate3[i_23];
    }
  }

  /* End of Switch: '<S348>/Switch' */

  /* SignalConversion generated from: '<S351>/Vector Concatenate' */
  b_VectorConcatenate_gaq1[0] = b_Switch_jzso[0];

  /* SignalConversion generated from: '<S351>/Vector Concatenate' */
  b_VectorConcatenate_gaq1[1] = b_Switch_jzso[1];

  /* SignalConversion generated from: '<S351>/Vector Concatenate' */
  b_VectorConcatenate_gaq1[2] = b_Switch_jzso[2];
  if (rtmIsMajorTimeStep(RMT_FDM_RT_M) && rtmIsSampleHit(RMT_FDM_RT_M, 2)) {
    /* RandomNumber: '<S342>/Random Number1' incorporates:
     *  Sum: '<S342>/Sum1'
     */
    for (iU_5 = 0; iU_5 < 3; iU_5 = iU_5 + 1) {
      b_Sum1_pk2u[iU_5] = localDW->NextOutput_kg2s[iU_5];
    }

    /* End of RandomNumber: '<S342>/Random Number1' */

    /* Sum: '<S342>/Sum5' incorporates:
     *  DiscreteIntegrator: '<S345>/Discrete-Time Integrator'
     *  Sum: '<S342>/Sum1'
     */
    for (i_1s = 0; i_1s < 3; i_1s = i_1s + 1) {
      b_Sum5_hbb1[i_1s] = localB->DiscreteTimeIntegrator[i_1s] +
        b_Sum1_pk2u[i_1s];
    }

    /* End of Sum: '<S342>/Sum5' */

    /* RateTransition: '<S342>/Rate Transition4' */
    if (rtmIsMajorTimeStep(RMT_FDM_RT_M) && rtmIsSampleHit(RMT_FDM_RT_M, 2)) {
      /* RateTransition: '<S342>/Rate Transition4' incorporates:
       *  Sum: '<S342>/Sum5'
       */
      for (i_1t = 0; i_1t < 3; i_1t = i_1t + 1) {
        localB->RateTransition4[i_1t] = b_Sum5_hbb1[i_1t];
      }
    }

    /* End of RateTransition: '<S342>/Rate Transition4' */
  }

  /* Integrator: '<S15>/pos_x' incorporates:
   *  Integrator: '<S16>/pos_y'
   */
  if (rtsiIsModeUpdateTimeStep(RMT_FDM_RT_M->solverInfo)) {
    didZcEventOccur_9 = (rtu_Simulation_Control->flg_Reset &&
                         (localZCE->pos_x_Reset_ZCE != POS_ZCSIG));
    localZCE->pos_x_Reset_ZCE = (uint8_T)rtu_Simulation_Control->flg_Reset;

    /* evaluate zero-crossings */
    if (didZcEventOccur_9 || localDW->pos_x_DWORK1) {
      localX->x_R_O_m = rtu_States_Init->pos_R_O_m.x_R_O_m;
    }

    didZcEventOccur_a = (rtu_Simulation_Control->flg_Reset &&
                         (localZCE->pos_y_Reset_ZCE != POS_ZCSIG));
    localZCE->pos_y_Reset_ZCE = (uint8_T)rtu_Simulation_Control->flg_Reset;

    /* evaluate zero-crossings */
    if (didZcEventOccur_a || localDW->pos_y_DWORK1) {
      localX->y_R_O_m = rtu_States_Init->pos_R_O_m.y_R_O_m;
    }
  }

  /* SignalConversion generated from: '<S342>/Vector Concatenate4' incorporates:
   *  Integrator: '<S15>/pos_x'
   *  Reshape: '<S342>/Reshape2'
   */
  localB->Reshape2[0] = localX->x_R_O_m;

  /* SignalConversion generated from: '<S342>/Vector Concatenate4' incorporates:
   *  Integrator: '<S16>/pos_y'
   *  Reshape: '<S342>/Reshape2'
   */
  localB->Reshape2[1] = localX->y_R_O_m;

  /* SignalConversion generated from: '<S342>/Vector Concatenate4' incorporates:
   *  Integrator: '<S17>/pos_z'
   *  Reshape: '<S342>/Reshape2'
   */
  localB->Reshape2[2] = localX->z_R_O_m;

  /* RateTransition: '<S342>/Rate Transition6' incorporates:
   *  RateTransition: '<S342>/Rate Transition5'
   */
  if (rtmIsMajorTimeStep(RMT_FDM_RT_M)) {
    /* RateTransition: '<S342>/Rate Transition6' incorporates:
     *  Reshape: '<S342>/Reshape2'
     */
    for (i_1u = 0; i_1u < 3; i_1u = i_1u + 1) {
      localB->RateTransition6[i_1u] = localB->Reshape2[i_1u];
    }

    if (rtmIsMajorTimeStep(RMT_FDM_RT_M) && rtmIsSampleHit(RMT_FDM_RT_M, 2)) {
      /* RateTransition: '<S342>/Rate Transition5' */
      for (i_1w = 0; i_1w < 3; i_1w = i_1w + 1) {
        localB->RateTransition5[i_1w] = localDW->RateTransition5_Buffer0[i_1w];
      }
    }
  }

  /* End of RateTransition: '<S342>/Rate Transition6' */
  if (rtmIsMajorTimeStep(RMT_FDM_RT_M) && rtmIsSampleHit(RMT_FDM_RT_M, 2)) {
    for (i_1v = 0; i_1v < 3; i_1v = i_1v + 1) {
      /* Reshape: '<S342>/Reshape3' incorporates:
       *  RateTransition: '<S342>/Rate Transition4'
       *  RateTransition: '<S342>/Rate Transition6'
       *  Sum: '<S342>/Sum1'
       */
      localB->Reshape3[i_1v] = localB->RateTransition6[i_1v] +
        localB->RateTransition4[i_1v];
    }

    /* DiscreteFir: '<S350>/Discrete FIR Filter' incorporates:
     *  Reshape: '<S342>/Reshape3'
     */
    uIdx_0 = 0;
    for (k_0 = 0; k_0 < 3; k_0 = k_0 + 1) {
      acc1_0 = localB->Reshape3[uIdx_0] * 0.5;
      uIdx_0 = uIdx_0 + 1;

      /* DiscreteFir: '<S350>/Discrete FIR Filter' incorporates:
       *  Reshape: '<S342>/Reshape3'
       */
      localB->DiscreteFIRFilter[k_0] = acc1_0 +
        localDW->DiscreteFIRFilter_states_jj3r[k_0] * 0.5;
    }

    /* End of DiscreteFir: '<S350>/Discrete FIR Filter' */

    /* SignalConversion generated from: '<S342>/Vector Concatenate' incorporates:
     *  Constant: '<S353>/constant1'
     */
    b_Reshape_aw0z[2] = -1.0;
  }

  /* Switch: '<S347>/Switch' incorporates:
   *  RateTransition: '<S342>/Rate Transition5'
   *  Reshape: '<S342>/Reshape2'
   */
  if (rtu_Simulation_Control->flg_Enable_Sensor_Errors) {
    for (i_1x = 0; i_1x < 3; i_1x = i_1x + 1) {
      b_Switch_jgoc[i_1x] = localB->RateTransition5[i_1x];
    }
  } else {
    for (i_22 = 0; i_22 < 3; i_22 = i_22 + 1) {
      b_Switch_jgoc[i_22] = localB->Reshape2[i_22];
    }
  }

  /* End of Switch: '<S347>/Switch' */

  /* Sum: '<S356>/Sum' incorporates:
   *  Constant: '<S356>/r__earth_m'
   *  Integrator: '<S15>/pos_x'
   *  Product: '<S356>/Divide'
   */
  localB->Sum = localX->x_R_O_m / 6.378E+6 +
    rtu_States_Init->pos_R_WGS84.mue_R_WGS84_rad;

  /* RateTransition generated from: '<S342>/Rate Transition3' */
  if (rtmIsMajorTimeStep(RMT_FDM_RT_M)) {
    /* RateTransition generated from: '<S342>/Rate Transition3' */
    localB->mue_R_WGS84_rad = localB->Sum;
  }

  if (rtmIsMajorTimeStep(RMT_FDM_RT_M) && rtmIsSampleHit(RMT_FDM_RT_M, 2)) {
    /* Trigonometry: '<S353>/Trigonometric Function1' */
    b_N = cos(localB->mue_R_WGS84_rad);

    /* Product: '<S353>/Product2' incorporates:
     *  Math: '<S353>/u^1'
     */
    b_Product2_b3um = b_N * b_N * RMT_FDM_RT_ConstB.e_2;

    /* Trigonometry: '<S353>/Trigonometric Function' */
    b_N = sin(localB->mue_R_WGS84_rad);

    /* Product: '<S353>/Divide' incorporates:
     *  Constant: '<S353>/Constant1'
     *  Constant: '<S353>/Constant3'
     *  Math: '<S353>/u^2'
     *  Product: '<S353>/Product'
     *  Sqrt: '<S353>/sqrt'
     *  Sum: '<S353>/Subtract'
     */
    b_N = 6.378137E+6 / sqrt(1.0 - RMT_FDM_RT_ConstB.e_2 * (b_N * b_N));

    /* Product: '<S353>/Product3' incorporates:
     *  Constant: '<S353>/constant2'
     *  Sum: '<S353>/Subtract2'
     */
    b_Product3 = (1.0 - b_Product2_b3um) * b_N;
  }

  /* Sum: '<S356>/Sum2' incorporates:
   *  Integrator: '<S17>/pos_z'
   *  UnaryMinus: '<S356>/Unary Minus'
   */
  localB->Sum2_iphy = -localX->z_R_O_m +
    rtu_States_Init->pos_R_WGS84.h_R_WGS84_m;

  /* RateTransition generated from: '<S342>/Rate Transition3' */
  if (rtmIsMajorTimeStep(RMT_FDM_RT_M)) {
    /* RateTransition generated from: '<S342>/Rate Transition3' */
    localB->h_R_WGS84_m = localB->Sum2_iphy;
  }

  if (rtmIsMajorTimeStep(RMT_FDM_RT_M) && rtmIsSampleHit(RMT_FDM_RT_M, 2)) {
    /* Sum: '<S353>/Add' */
    b_Reshape_aw0z[0] = b_Product3 + localB->h_R_WGS84_m;

    /* Product: '<S353>/Product4' incorporates:
     *  Sum: '<S353>/Add1'
     *  Trigonometry: '<S353>/Trigonometric Function2'
     */
    b_Reshape_aw0z[1] = (b_N + localB->h_R_WGS84_m) * cos
      (localB->mue_R_WGS84_rad);

    /* Product: '<S342>/Divide' incorporates:
     *  Reshape: '<S342>/Reshape'
     *  Sum: '<S342>/Sum5'
     */
    for (i_1y = 0; i_1y < 3; i_1y = i_1y + 1) {
      b_Divide_bizu[i_1y] = 1.0 / b_Reshape_aw0z[i_1y] * b_Sum5_hbb1[i_1y];
    }

    /* End of Product: '<S342>/Divide' */

    /* SignalConversion generated from: '<S342>/Vector Concatenate1' incorporates:
     *  Concatenate: '<S342>/Vector Concatenate1'
     */
    localB->VectorConcatenate1[1] = localB->mue_R_WGS84_rad;

    /* SignalConversion generated from: '<S342>/Vector Concatenate1' incorporates:
     *  Concatenate: '<S342>/Vector Concatenate1'
     */
    localB->VectorConcatenate1[2] = localB->h_R_WGS84_m;
  }

  /* Product: '<S356>/Divide2' incorporates:
   *  Constant: '<S356>/r__earth_m'
   *  Integrator: '<S16>/pos_y'
   *  Product: '<S356>/Divide1'
   *  Sum: '<S356>/Sum1'
   */
  localB->Divide2 = (localX->y_R_O_m / 6.378E+6 +
                     rtu_States_Init->pos_R_WGS84.lambda_R_WGS84_rad) /
    rtu_States_Init->pos_R_WGS84.h_R_WGS84_m;

  /* RateTransition generated from: '<S342>/Rate Transition3' incorporates:
   *  Concatenate: '<S342>/Vector Concatenate1'
   */
  if (rtmIsMajorTimeStep(RMT_FDM_RT_M)) {
    localB->VectorConcatenate1[0] = localB->Divide2;

    /* RandomNumber: '<S317>/Random Number2' incorporates:
     *  Concatenate: '<S342>/Vector Concatenate1'
     */
    for (iU_6 = 0; iU_6 < 3; iU_6 = iU_6 + 1) {
      b_RandomNumber2[iU_6] = localDW->NextOutput_d0v2[iU_6];
    }

    /* End of RandomNumber: '<S317>/Random Number2' */

    /* RandomNumber: '<S315>/Random Number2' */
    for (iU_7 = 0; iU_7 < 3; iU_7 = iU_7 + 1) {
      b_RandomNumber2_mjrt[iU_7] = localDW->NextOutput_oxco[iU_7];
    }

    /* End of RandomNumber: '<S315>/Random Number2' */

    /* RandomNumber: '<S243>/Random Number2' */
    for (iU_8 = 0; iU_8 < 3; iU_8 = iU_8 + 1) {
      b_RandomNumber2_lwaa[iU_8] = localDW->NextOutput_myry[iU_8];
    }

    /* End of RandomNumber: '<S243>/Random Number2' */

    /* RandomNumber: '<S244>/Random Number2' */
    for (iU_9 = 0; iU_9 < 3; iU_9 = iU_9 + 1) {
      b_RandomNumber2_b4yr[iU_9] = localDW->NextOutput_psbc[iU_9];
    }

    /* End of RandomNumber: '<S244>/Random Number2' */

    /* RandomNumber: '<S245>/Random Number2' */
    for (iU_a = 0; iU_a < 3; iU_a = iU_a + 1) {
      b_RandomNumber2_k5jx[iU_a] = localDW->NextOutput_ps3h[iU_a];
    }

    /* End of RandomNumber: '<S245>/Random Number2' */

    /* RandomNumber: '<S246>/Random Number2' */
    for (iU_b = 0; iU_b < 3; iU_b = iU_b + 1) {
      b_RandomNumber2_muso[iU_b] = localDW->NextOutput_ivlt[iU_b];
    }

    /* End of RandomNumber: '<S246>/Random Number2' */

    /* RandomNumber: '<S247>/Random Number2' */
    for (iU_c = 0; iU_c < 3; iU_c = iU_c + 1) {
      b_RandomNumber2_dn0u[iU_c] = localDW->NextOutput_hejj[iU_c];
    }

    /* End of RandomNumber: '<S247>/Random Number2' */

    /* RandomNumber: '<S248>/Random Number2' */
    for (iU_d = 0; iU_d < 3; iU_d = iU_d + 1) {
      b_RandomNumber2_e2nc[iU_d] = localDW->NextOutput_nqkk[iU_d];
    }

    /* End of RandomNumber: '<S248>/Random Number2' */

    /* RandomNumber: '<S249>/Random Number2' */
    for (iU_e = 0; iU_e < 3; iU_e = iU_e + 1) {
      b_RandomNumber2_gjti[iU_e] = localDW->NextOutput_op4z[iU_e];
    }

    /* End of RandomNumber: '<S249>/Random Number2' */

    /* RandomNumber: '<S250>/Random Number2' */
    for (iU_f = 0; iU_f < 3; iU_f = iU_f + 1) {
      b_RandomNumber2_p3bk[iU_f] = localDW->NextOutput_ejvr[iU_f];
    }

    /* End of RandomNumber: '<S250>/Random Number2' */

    /* RandomNumber: '<S390>/Random Number2' */
    for (iU_g = 0; iU_g < 3; iU_g = iU_g + 1) {
      b_RandomNumber2_nzfy[iU_g] = localDW->NextOutput_klkk[iU_g];
    }

    /* End of RandomNumber: '<S390>/Random Number2' */

    /* RateTransition: '<S342>/Rate Transition' */
    tmp_j = localDW->RateTransition_ActiveBufIdx * 3;
    for (i_8h = 0; i_8h < 3; i_8h = i_8h + 1) {
      localB->RateTransition[i_8h] = localDW->RateTransition_Buffer[i_8h + tmp_j];
    }

    /* End of RateTransition: '<S342>/Rate Transition' */
  }

  if (rtmIsMajorTimeStep(RMT_FDM_RT_M) && rtmIsSampleHit(RMT_FDM_RT_M, 2)) {
    for (i_1z = 0; i_1z < 3; i_1z = i_1z + 1) {
      /* Sum: '<S342>/Sum2' incorporates:
       *  Product: '<S342>/Divide'
       *  Reshape: '<S342>/Reshape'
       */
      localB->Sum2_czfu[i_1z] = localB->VectorConcatenate1[i_1z] +
        b_Divide_bizu[i_1z];
    }

    /* DiscreteFir: '<S349>/Discrete FIR Filter' incorporates:
     *  Sum: '<S342>/Sum2'
     */
    uIdx_1 = 0;
    for (k_1 = 0; k_1 < 3; k_1 = k_1 + 1) {
      acc1_1 = localB->Sum2_czfu[uIdx_1] * 0.5;
      uIdx_1 = uIdx_1 + 1;

      /* DiscreteFir: '<S349>/Discrete FIR Filter' incorporates:
       *  Sum: '<S342>/Sum2'
       */
      localB->DiscreteFIRFilter_gsnn[k_1] = acc1_1 +
        localDW->DiscreteFIRFilter_states_m0pu[k_1] * 0.5;
    }

    /* End of DiscreteFir: '<S349>/Discrete FIR Filter' */
  }

  /* Switch: '<S346>/Switch' incorporates:
   *  RateTransition: '<S342>/Rate Transition'
   */
  if (rtu_Simulation_Control->flg_Enable_Sensor_Errors) {
    for (i_20 = 0; i_20 < 3; i_20 = i_20 + 1) {
      b_Switch_dxts[i_20] = localB->RateTransition[i_20];
    }
  } else {
    /* SignalConversion generated from: '<S342>/Vector Concatenate2' incorporates:
     *  Switch: '<S346>/Switch'
     */
    b_Switch_dxts[2] = localB->Sum2_iphy;

    /* SignalConversion generated from: '<S342>/Vector Concatenate2' incorporates:
     *  Switch: '<S346>/Switch'
     */
    b_Switch_dxts[1] = localB->Sum;

    /* SignalConversion generated from: '<S342>/Vector Concatenate2' incorporates:
     *  Switch: '<S346>/Switch'
     */
    b_Switch_dxts[0] = localB->Divide2;
  }

  /* End of Switch: '<S346>/Switch' */

  /* Math: '<S355>/u^2' */
  for (i_21 = 0; i_21 < 3; i_21 = i_21 + 1) {
    b_u2_oitx[i_21] = b_VectorConcatenate_gaq1[i_21] *
      b_VectorConcatenate_gaq1[i_21];
  }

  /* End of Math: '<S355>/u^2' */

  /* Sum: '<S355>/Sum of Elements' */
  tmp_3 = b_u2_oitx[0];
  for (i_4 = 1; i_4 < 3; i_4 = i_4 + 1) {
    tmp_3 = tmp_3 + b_u2_oitx[i_4];
  }

  /* Sqrt: '<S355>/sqrt' incorporates:
   *  Sum: '<S355>/Sum of Elements'
   *
   * About '<S355>/sqrt':
   *  Operator: signedSqrt
   */
  if (tmp_3 < 0.0) {
    b_Add_cf0u = -sqrt(fabs(tmp_3));
  } else {
    b_Add_cf0u = sqrt(tmp_3);
  }

  /* End of Sqrt: '<S355>/sqrt' */

  /* Saturate: '<S351>/Saturation1' */
  if (b_Add_cf0u <= 1.0E-6) {
    b_w_z_int_PRot_P_err_radDs_alwh = 1.0E-6;
  } else {
    b_w_z_int_PRot_P_err_radDs_alwh = b_Add_cf0u;
  }

  /* End of Saturate: '<S351>/Saturation1' */

  /* Product: '<S351>/Product' incorporates:
   *  Gain: '<S351>/Gain'
   */
  u0_4 = -b_Switch_jzso[2] / b_w_z_int_PRot_P_err_radDs_alwh;

  /* Trigonometry: '<S351>/Trigonometric Function' */
  if (u0_4 > 1.0) {
    y_g = 1.0;
  } else if (u0_4 < -1.0) {
    y_g = -1.0;
  } else {
    y_g = u0_4;
  }

  u0_3 = asin(y_g);

  /* End of Trigonometry: '<S351>/Trigonometric Function' */

  /* Saturate: '<S351>/Saturation' */
  if (u0_3 > 3.1415926535897931) {
    /* BusCreator generated from: '<Root>/Measurements' */
    rty_Measurements->gps_meas.Translation_K_R_meas.path_K_R_meas_rad.gamma_K_R_meas_rad
      = 3.1415926535897931;
  } else if (u0_3 < -3.1415926535897931) {
    /* BusCreator generated from: '<Root>/Measurements' */
    rty_Measurements->gps_meas.Translation_K_R_meas.path_K_R_meas_rad.gamma_K_R_meas_rad
      = -3.1415926535897931;
  } else {
    /* BusCreator generated from: '<Root>/Measurements' */
    rty_Measurements->gps_meas.Translation_K_R_meas.path_K_R_meas_rad.gamma_K_R_meas_rad
      = u0_3;
  }

  /* End of Saturate: '<S351>/Saturation' */

  /* BusCreator generated from: '<Root>/Measurements' incorporates:
   *  Trigonometry: '<S351>/Trigonometric Function1'
   */
  rty_Measurements->gps_meas.Translation_K_R_meas.path_K_R_meas_rad.chi_K_R_meas_rad
    = rt_atan2d_snf(b_Switch_jzso[1], b_Switch_jzso[0]);

  /* BusCreator generated from: '<Root>/Measurements' */
  rty_Measurements->gps_meas.Translation_K_R_meas.vel_K_R_abs_meas_mDs =
    b_Add_cf0u;

  /* BusCreator generated from: '<Root>/Measurements' */
  rty_Measurements->gps_meas.pos_R_WGS84_meas.lambda_R_WGS84_meas_rad =
    b_Switch_dxts[0];
  rty_Measurements->gps_meas.pos_R_WGS84_meas.mue_R_WGS84_meas_rad =
    b_Switch_dxts[1];
  rty_Measurements->gps_meas.pos_R_WGS84_meas.h_R_WGS84_meas_m = b_Switch_dxts[2];

  /* BusCreator generated from: '<Root>/Measurements' */
  rty_Measurements->gps_meas.pos_R_local_meas.x_R_O_meas_m = b_Switch_jgoc[0];
  rty_Measurements->gps_meas.pos_R_local_meas.y_R_O_meas_m = b_Switch_jgoc[1];
  rty_Measurements->gps_meas.pos_R_local_meas.z_R_O_meas_m = b_Switch_jgoc[2];

  /* BusCreator generated from: '<Root>/Measurements' */
  rty_Measurements->gps_meas.vel_K_R_E_O_meas.u_K_R_E_O_meas_mDs =
    b_Switch_jzso[0];
  rty_Measurements->gps_meas.vel_K_R_E_O_meas.v_K_R_E_O_meas_mDs =
    b_Switch_jzso[1];
  rty_Measurements->gps_meas.vel_K_R_E_O_meas.w_K_R_E_O_meas_mDs =
    b_Switch_jzso[2];

  /* Integrator: '<S333>/w_z_int_PRot_P_err_radDs' incorporates:
   *  Constant: '<S331>/Constant2'
   */
  if (rtsiIsModeUpdateTimeStep(RMT_FDM_RT_M->solverInfo)) {
    zcEvent_5 = rt_ZCFcn(RISING_ZERO_CROSSING,
                         &localZCE->w_z_int_PRot_P_err_radDs_Reset_ZCE_cpmd,
                         (1.0));

    /* evaluate zero-crossings */
    if ((zcEvent_5 != NO_ZCEVENT) ||
        localDW->w_z_int_PRot_P_err_radDs_DWORK1_mvtc) {
      localX->w_z_int_PRot_P_err_radDs_cg5d = RMT_FDM_RT_ConstB.Constant3_cbnt;
    }
  }

  if (rtmIsMajorTimeStep(RMT_FDM_RT_M)) {
    /* Gain: '<S316>/Gain' incorporates:
     *  RandomNumber: '<S316>/Random Number2'
     */
    tmp_k = 0.0;
    for (i_8i = 0; i_8i < 3; i_8i = i_8i + 1) {
      tmp_k = tmp_k + rtCP_Gain_Gain_mhkw[i_8i] * b_RandomNumber2_ouvm[i_8i];
    }

    /* Gain: '<S316>/Gain' */
    localB->Gain_eods = tmp_k;
  }

  /* Switch: '<S327>/Switch' */
  if (rtu_Simulation_Control->flg_Enable_Sensor_Errors) {
    /* Saturate: '<S316>/Saturation' */
    if (localX->w_z_int_PRot_P_err_radDs_cg5d > 115000.0) {
      y_4 = 115000.0;
    } else if (localX->w_z_int_PRot_P_err_radDs_cg5d < -15000.0) {
      y_4 = -15000.0;
    } else {
      y_4 = localX->w_z_int_PRot_P_err_radDs_cg5d;
    }

    /* End of Saturate: '<S316>/Saturation' */

    /* BusCreator generated from: '<Root>/Measurements' incorporates:
     *  Sum: '<S316>/Add'
     */
    rty_Measurements->baro_meas.Static_Pressure_meas_NDm2 = y_4 +
      localB->Gain_eods;
  } else {
    /* BusCreator generated from: '<Root>/Measurements' incorporates:
     *  BusCreator generated from: '<S28>/Bus Assignment'
     *  SignalConversion: '<S316>/Signal Conversion1'
     */
    rty_Measurements->baro_meas.Static_Pressure_meas_NDm2 =
      b_Atmosphere.Static_Pressure_ATM_NDm2;
  }

  /* End of Switch: '<S327>/Switch' */

  /* Integrator: '<S341>/w_z_int_PRot_P_err_radDs' incorporates:
   *  Constant: '<S339>/Constant2'
   */
  if (rtsiIsModeUpdateTimeStep(RMT_FDM_RT_M->solverInfo)) {
    zcEvent_6 = rt_ZCFcn(RISING_ZERO_CROSSING,
                         &localZCE->w_z_int_PRot_P_err_radDs_Reset_ZCE_k4ow,
                         (1.0));

    /* evaluate zero-crossings */
    if ((zcEvent_6 != NO_ZCEVENT) ||
        localDW->w_z_int_PRot_P_err_radDs_DWORK1_ik1k) {
      localX->w_z_int_PRot_P_err_radDs_dftl = RMT_FDM_RT_ConstB.Constant3_ohwx;
    }
  }

  if (rtmIsMajorTimeStep(RMT_FDM_RT_M)) {
    /* Gain: '<S317>/Gain' incorporates:
     *  RandomNumber: '<S317>/Random Number2'
     */
    tmp_l = 0.0;
    for (i_8j = 0; i_8j < 3; i_8j = i_8j + 1) {
      tmp_l = tmp_l + rtCP_Gain_Gain_jmhp[i_8j] * b_RandomNumber2[i_8j];
    }

    /* Gain: '<S317>/Gain' */
    localB->Gain_cczd = tmp_l;
  }

  /* Switch: '<S335>/Switch' */
  if (rtu_Simulation_Control->flg_Enable_Sensor_Errors) {
    /* Saturate: '<S317>/Saturation' */
    if (localX->w_z_int_PRot_P_err_radDs_dftl > 350.0) {
      y_5 = 350.0;
    } else if (localX->w_z_int_PRot_P_err_radDs_dftl < 273.0) {
      y_5 = 273.0;
    } else {
      y_5 = localX->w_z_int_PRot_P_err_radDs_dftl;
    }

    /* End of Saturate: '<S317>/Saturation' */

    /* BusCreator generated from: '<Root>/Measurements' incorporates:
     *  Sum: '<S317>/Add'
     */
    rty_Measurements->baro_meas.Static_Temperature_meas_K = y_5 +
      localB->Gain_cczd;
  } else {
    /* BusCreator generated from: '<Root>/Measurements' incorporates:
     *  DataTypeConversion: '<S184>/Data Type Conversion'
     */
    rty_Measurements->baro_meas.Static_Temperature_meas_K = b_Sum1_hc1q;
  }

  /* End of Switch: '<S335>/Switch' */

  /* Integrator: '<S325>/w_z_int_PRot_P_err_radDs' incorporates:
   *  Constant: '<S323>/Constant2'
   */
  if (rtsiIsModeUpdateTimeStep(RMT_FDM_RT_M->solverInfo)) {
    zcEvent_7 = rt_ZCFcn(RISING_ZERO_CROSSING,
                         &localZCE->w_z_int_PRot_P_err_radDs_Reset_ZCE_gvbs,
                         (1.0));

    /* evaluate zero-crossings */
    if ((zcEvent_7 != NO_ZCEVENT) ||
        localDW->w_z_int_PRot_P_err_radDs_DWORK1_bsyt) {
      localX->w_z_int_PRot_P_err_radDs_jowp = RMT_FDM_RT_ConstB.Constant3_mlqd;
    }
  }

  if (rtmIsMajorTimeStep(RMT_FDM_RT_M)) {
    /* Gain: '<S315>/Gain' incorporates:
     *  RandomNumber: '<S315>/Random Number2'
     */
    tmp_m = 0.0;
    for (i_8k = 0; i_8k < 3; i_8k = i_8k + 1) {
      tmp_m = tmp_m + rtCP_Gain_Gain_nqmx[i_8k] * b_RandomNumber2_mjrt[i_8k];
    }

    /* Gain: '<S315>/Gain' */
    localB->Gain_hlmc = tmp_m;
  }

  /* Switch: '<S319>/Switch' */
  if (rtu_Simulation_Control->flg_Enable_Sensor_Errors) {
    /* Saturate: '<S315>/Saturation' */
    if (localX->w_z_int_PRot_P_err_radDs_jowp > 115000.0) {
      y_6 = 115000.0;
    } else if (localX->w_z_int_PRot_P_err_radDs_jowp < -15000.0) {
      y_6 = -15000.0;
    } else {
      y_6 = localX->w_z_int_PRot_P_err_radDs_jowp;
    }

    /* End of Saturate: '<S315>/Saturation' */

    /* BusCreator generated from: '<Root>/Measurements' incorporates:
     *  Sum: '<S315>/Add'
     */
    rty_Measurements->baro_meas.h_Baro_meas_m = y_6 + localB->Gain_hlmc;
  } else {
    /* BusCreator generated from: '<Root>/Measurements' incorporates:
     *  Gain: '<S224>/Gain'
     *  Integrator: '<S17>/pos_z'
     */
    rty_Measurements->baro_meas.h_Baro_meas_m = -localX->z_R_O_m;
  }

  /* End of Switch: '<S319>/Switch' */

  /* BusCreator generated from: '<Root>/Measurements' */
  rty_Measurements->imu_meas.gyro_meas.w_x_K_IB_B_IMU_meas_radDs =
    b_Switch_kohd[0];
  rty_Measurements->imu_meas.gyro_meas.w_y_K_IB_B_IMU_meas_radDs =
    b_Switch_kohd[1];
  rty_Measurements->imu_meas.gyro_meas.w_z_K_IB_B_IMU_meas_radDs =
    b_Switch_kohd[2];

  /* BusCreator generated from: '<Root>/Measurements' */
  rty_Measurements->imu_meas.acc_meas.f_x_P_B_IMU_meas_mDs2 = b_Switch_jlc4[0];
  rty_Measurements->imu_meas.acc_meas.f_y_P_B_IMU_meas_mDs2 = b_Switch_jlc4[1];
  rty_Measurements->imu_meas.acc_meas.f_z_P_B_IMU_meas_mDs2 = b_Switch_jlc4[2];

  /* BusCreator generated from: '<Root>/Measurements' incorporates:
   *  Product: '<S239>/Product10'
   */
  rty_Measurements->ahrs_meas.Phi_meas_rad = b_Switch[0];
  rty_Measurements->ahrs_meas.Theta_meas_rad = b_Switch[1];
  rty_Measurements->ahrs_meas.Psi_meas_rad = b_Switch[2];
  memcpy(&rty_Measurements->ahrs_meas.M_BO_meas[0], &b_Product10_pps0[0], 9U *
         sizeof(real_T));

  /* Integrator: '<S258>/w_z_int_PRot_P_err_radDs' incorporates:
   *  Constant: '<S256>/Constant2'
   */
  if (rtsiIsModeUpdateTimeStep(RMT_FDM_RT_M->solverInfo)) {
    zcEvent_8 = rt_ZCFcn(RISING_ZERO_CROSSING,
                         &localZCE->w_z_int_PRot_P_err_radDs_Reset_ZCE_i5ww,
                         (1.0));

    /* evaluate zero-crossings */
    if ((zcEvent_8 != NO_ZCEVENT) ||
        localDW->w_z_int_PRot_P_err_radDs_DWORK1_f02p) {
      localX->w_z_int_PRot_P_err_radDs_baxu = RMT_FDM_RT_ConstB.Constant3_gxp5;
    }
  }

  if (rtmIsMajorTimeStep(RMT_FDM_RT_M)) {
    /* Gain: '<S243>/Gain' incorporates:
     *  RandomNumber: '<S243>/Random Number2'
     */
    tmp_n = 0.0;
    for (i_8l = 0; i_8l < 3; i_8l = i_8l + 1) {
      tmp_n = tmp_n + rtCP_Gain_Gain_o55y[i_8l] * b_RandomNumber2_lwaa[i_8l];
    }

    /* Gain: '<S243>/Gain' */
    localB->Gain_b5my = tmp_n;
  }

  /* Switch: '<S252>/Switch' */
  if (rtu_Simulation_Control->flg_Enable_Sensor_Errors) {
    /* Saturate: '<S243>/Saturation' */
    if (localX->w_z_int_PRot_P_err_radDs_baxu > 2712.0) {
      y_7 = 2712.0;
    } else if (localX->w_z_int_PRot_P_err_radDs_baxu < 0.0) {
      y_7 = 0.0;
    } else {
      y_7 = localX->w_z_int_PRot_P_err_radDs_baxu;
    }

    /* End of Saturate: '<S243>/Saturation' */

    /* BusCreator generated from: '<Root>/Measurements' incorporates:
     *  Sum: '<S243>/Add'
     */
    rty_Measurements->motor_meas.w1_meas_radDs = y_7 + localB->Gain_b5my;
  } else {
    /* BusCreator generated from: '<Root>/Measurements' incorporates:
     *  SignalConversion: '<S243>/Signal Conversion1'
     */
    rty_Measurements->motor_meas.w1_meas_radDs =
      b_ImpAsg_InsertedFor_w_act_radDs_at_inport_0[0];
  }

  /* End of Switch: '<S252>/Switch' */

  /* Integrator: '<S266>/w_z_int_PRot_P_err_radDs' incorporates:
   *  Constant: '<S264>/Constant2'
   */
  if (rtsiIsModeUpdateTimeStep(RMT_FDM_RT_M->solverInfo)) {
    zcEvent_9 = rt_ZCFcn(RISING_ZERO_CROSSING,
                         &localZCE->w_z_int_PRot_P_err_radDs_Reset_ZCE_g2qz,
                         (1.0));

    /* evaluate zero-crossings */
    if ((zcEvent_9 != NO_ZCEVENT) ||
        localDW->w_z_int_PRot_P_err_radDs_DWORK1_nx4h) {
      localX->w_z_int_PRot_P_err_radDs_cjc1 = RMT_FDM_RT_ConstB.Constant3_iicg;
    }
  }

  if (rtmIsMajorTimeStep(RMT_FDM_RT_M)) {
    /* Gain: '<S244>/Gain' incorporates:
     *  RandomNumber: '<S244>/Random Number2'
     */
    tmp_o = 0.0;
    for (i_8m = 0; i_8m < 3; i_8m = i_8m + 1) {
      tmp_o = tmp_o + rtCP_Gain_Gain_odic[i_8m] * b_RandomNumber2_b4yr[i_8m];
    }

    /* Gain: '<S244>/Gain' */
    localB->Gain_jznf = tmp_o;
  }

  /* Switch: '<S260>/Switch' */
  if (rtu_Simulation_Control->flg_Enable_Sensor_Errors) {
    /* Saturate: '<S244>/Saturation' */
    if (localX->w_z_int_PRot_P_err_radDs_cjc1 > 2712.0) {
      y_8 = 2712.0;
    } else if (localX->w_z_int_PRot_P_err_radDs_cjc1 < 0.0) {
      y_8 = 0.0;
    } else {
      y_8 = localX->w_z_int_PRot_P_err_radDs_cjc1;
    }

    /* End of Saturate: '<S244>/Saturation' */

    /* BusCreator generated from: '<Root>/Measurements' incorporates:
     *  Sum: '<S244>/Add'
     */
    rty_Measurements->motor_meas.w2_meas_radDs = y_8 + localB->Gain_jznf;
  } else {
    /* BusCreator generated from: '<Root>/Measurements' incorporates:
     *  SignalConversion: '<S244>/Signal Conversion1'
     */
    rty_Measurements->motor_meas.w2_meas_radDs =
      b_ImpAsg_InsertedFor_w_act_radDs_at_inport_0[1];
  }

  /* End of Switch: '<S260>/Switch' */

  /* Integrator: '<S274>/w_z_int_PRot_P_err_radDs' incorporates:
   *  Constant: '<S272>/Constant2'
   */
  if (rtsiIsModeUpdateTimeStep(RMT_FDM_RT_M->solverInfo)) {
    zcEvent_a = rt_ZCFcn(RISING_ZERO_CROSSING,
                         &localZCE->w_z_int_PRot_P_err_radDs_Reset_ZCE_lcew,
                         (1.0));

    /* evaluate zero-crossings */
    if ((zcEvent_a != NO_ZCEVENT) ||
        localDW->w_z_int_PRot_P_err_radDs_DWORK1_jzmo) {
      localX->w_z_int_PRot_P_err_radDs_aexu = RMT_FDM_RT_ConstB.Constant3_no2m;
    }
  }

  if (rtmIsMajorTimeStep(RMT_FDM_RT_M)) {
    /* Gain: '<S245>/Gain' incorporates:
     *  RandomNumber: '<S245>/Random Number2'
     */
    tmp_p = 0.0;
    for (i_8n = 0; i_8n < 3; i_8n = i_8n + 1) {
      tmp_p = tmp_p + rtCP_Gain_Gain_lekx[i_8n] * b_RandomNumber2_k5jx[i_8n];
    }

    /* Gain: '<S245>/Gain' */
    localB->Gain_gjq3 = tmp_p;
  }

  /* Switch: '<S268>/Switch' */
  if (rtu_Simulation_Control->flg_Enable_Sensor_Errors) {
    /* Saturate: '<S245>/Saturation' */
    if (localX->w_z_int_PRot_P_err_radDs_aexu > 2712.0) {
      y_9 = 2712.0;
    } else if (localX->w_z_int_PRot_P_err_radDs_aexu < 0.0) {
      y_9 = 0.0;
    } else {
      y_9 = localX->w_z_int_PRot_P_err_radDs_aexu;
    }

    /* End of Saturate: '<S245>/Saturation' */

    /* BusCreator generated from: '<Root>/Measurements' incorporates:
     *  Sum: '<S245>/Add'
     */
    rty_Measurements->motor_meas.w3_meas_radDs = y_9 + localB->Gain_gjq3;
  } else {
    /* BusCreator generated from: '<Root>/Measurements' incorporates:
     *  SignalConversion: '<S245>/Signal Conversion1'
     */
    rty_Measurements->motor_meas.w3_meas_radDs =
      b_ImpAsg_InsertedFor_w_act_radDs_at_inport_0[2];
  }

  /* End of Switch: '<S268>/Switch' */

  /* Integrator: '<S282>/w_z_int_PRot_P_err_radDs' incorporates:
   *  Constant: '<S280>/Constant2'
   */
  if (rtsiIsModeUpdateTimeStep(RMT_FDM_RT_M->solverInfo)) {
    zcEvent_b = rt_ZCFcn(RISING_ZERO_CROSSING,
                         &localZCE->w_z_int_PRot_P_err_radDs_Reset_ZCE_aahy,
                         (1.0));

    /* evaluate zero-crossings */
    if ((zcEvent_b != NO_ZCEVENT) ||
        localDW->w_z_int_PRot_P_err_radDs_DWORK1_avwp) {
      localX->w_z_int_PRot_P_err_radDs_njv5 = RMT_FDM_RT_ConstB.Constant3_olbr;
    }
  }

  if (rtmIsMajorTimeStep(RMT_FDM_RT_M)) {
    /* Gain: '<S246>/Gain' incorporates:
     *  RandomNumber: '<S246>/Random Number2'
     */
    tmp_q = 0.0;
    for (i_8o = 0; i_8o < 3; i_8o = i_8o + 1) {
      tmp_q = tmp_q + rtCP_Gain_Gain_ax5s[i_8o] * b_RandomNumber2_muso[i_8o];
    }

    /* Gain: '<S246>/Gain' */
    localB->Gain_d3cc = tmp_q;
  }

  /* Switch: '<S276>/Switch' */
  if (rtu_Simulation_Control->flg_Enable_Sensor_Errors) {
    /* Saturate: '<S246>/Saturation' */
    if (localX->w_z_int_PRot_P_err_radDs_njv5 > 2712.0) {
      y_a = 2712.0;
    } else if (localX->w_z_int_PRot_P_err_radDs_njv5 < 0.0) {
      y_a = 0.0;
    } else {
      y_a = localX->w_z_int_PRot_P_err_radDs_njv5;
    }

    /* End of Saturate: '<S246>/Saturation' */

    /* BusCreator generated from: '<Root>/Measurements' incorporates:
     *  Sum: '<S246>/Add'
     */
    rty_Measurements->motor_meas.w4_meas_radDs = y_a + localB->Gain_d3cc;
  } else {
    /* BusCreator generated from: '<Root>/Measurements' incorporates:
     *  SignalConversion: '<S246>/Signal Conversion1'
     */
    rty_Measurements->motor_meas.w4_meas_radDs =
      b_ImpAsg_InsertedFor_w_act_radDs_at_inport_0[3];
  }

  /* End of Switch: '<S276>/Switch' */

  /* Integrator: '<S290>/w_z_int_PRot_P_err_radDs' incorporates:
   *  Constant: '<S288>/Constant2'
   */
  if (rtsiIsModeUpdateTimeStep(RMT_FDM_RT_M->solverInfo)) {
    zcEvent_c = rt_ZCFcn(RISING_ZERO_CROSSING,
                         &localZCE->w_z_int_PRot_P_err_radDs_Reset_ZCE_fh0g,
                         (1.0));

    /* evaluate zero-crossings */
    if ((zcEvent_c != NO_ZCEVENT) ||
        localDW->w_z_int_PRot_P_err_radDs_DWORK1_disd) {
      localX->w_z_int_PRot_P_err_radDs_adwj = RMT_FDM_RT_ConstB.Constant3_djky;
    }
  }

  if (rtmIsMajorTimeStep(RMT_FDM_RT_M)) {
    /* Gain: '<S247>/Gain' incorporates:
     *  RandomNumber: '<S247>/Random Number2'
     */
    tmp_r = 0.0;
    for (i_8p = 0; i_8p < 3; i_8p = i_8p + 1) {
      tmp_r = tmp_r + rtCP_Gain_Gain_nv2m[i_8p] * b_RandomNumber2_dn0u[i_8p];
    }

    /* Gain: '<S247>/Gain' */
    localB->Gain_na4s = tmp_r;
  }

  /* Switch: '<S284>/Switch' */
  if (rtu_Simulation_Control->flg_Enable_Sensor_Errors) {
    /* Saturate: '<S247>/Saturation' */
    if (localX->w_z_int_PRot_P_err_radDs_adwj > 2712.0) {
      y_b = 2712.0;
    } else if (localX->w_z_int_PRot_P_err_radDs_adwj < 0.0) {
      y_b = 0.0;
    } else {
      y_b = localX->w_z_int_PRot_P_err_radDs_adwj;
    }

    /* End of Saturate: '<S247>/Saturation' */

    /* BusCreator generated from: '<Root>/Measurements' incorporates:
     *  Sum: '<S247>/Add'
     */
    rty_Measurements->motor_meas.w5_meas_radDs = y_b + localB->Gain_na4s;
  } else {
    /* BusCreator generated from: '<Root>/Measurements' incorporates:
     *  SignalConversion: '<S247>/Signal Conversion1'
     */
    rty_Measurements->motor_meas.w5_meas_radDs =
      b_ImpAsg_InsertedFor_w_act_radDs_at_inport_0[4];
  }

  /* End of Switch: '<S284>/Switch' */

  /* Integrator: '<S298>/w_z_int_PRot_P_err_radDs' incorporates:
   *  Constant: '<S296>/Constant2'
   */
  if (rtsiIsModeUpdateTimeStep(RMT_FDM_RT_M->solverInfo)) {
    zcEvent_d = rt_ZCFcn(RISING_ZERO_CROSSING,
                         &localZCE->w_z_int_PRot_P_err_radDs_Reset_ZCE_ly0m,
                         (1.0));

    /* evaluate zero-crossings */
    if ((zcEvent_d != NO_ZCEVENT) ||
        localDW->w_z_int_PRot_P_err_radDs_DWORK1_dcuw) {
      localX->w_z_int_PRot_P_err_radDs_l00j = RMT_FDM_RT_ConstB.Constant3_mgjl;
    }
  }

  if (rtmIsMajorTimeStep(RMT_FDM_RT_M)) {
    /* Gain: '<S248>/Gain' incorporates:
     *  RandomNumber: '<S248>/Random Number2'
     */
    tmp_s = 0.0;
    for (i_8q = 0; i_8q < 3; i_8q = i_8q + 1) {
      tmp_s = tmp_s + rtCP_Gain_Gain_io0i[i_8q] * b_RandomNumber2_e2nc[i_8q];
    }

    /* Gain: '<S248>/Gain' */
    localB->Gain_palv = tmp_s;
  }

  /* Switch: '<S292>/Switch' */
  if (rtu_Simulation_Control->flg_Enable_Sensor_Errors) {
    /* Saturate: '<S248>/Saturation' */
    if (localX->w_z_int_PRot_P_err_radDs_l00j > 2712.0) {
      y_c = 2712.0;
    } else if (localX->w_z_int_PRot_P_err_radDs_l00j < 0.0) {
      y_c = 0.0;
    } else {
      y_c = localX->w_z_int_PRot_P_err_radDs_l00j;
    }

    /* End of Saturate: '<S248>/Saturation' */

    /* BusCreator generated from: '<Root>/Measurements' incorporates:
     *  Sum: '<S248>/Add'
     */
    rty_Measurements->motor_meas.w6_meas_radDs = y_c + localB->Gain_palv;
  } else {
    /* BusCreator generated from: '<Root>/Measurements' incorporates:
     *  SignalConversion: '<S248>/Signal Conversion1'
     */
    rty_Measurements->motor_meas.w6_meas_radDs =
      b_ImpAsg_InsertedFor_w_act_radDs_at_inport_0[5];
  }

  /* End of Switch: '<S292>/Switch' */

  /* Integrator: '<S306>/w_z_int_PRot_P_err_radDs' incorporates:
   *  Constant: '<S304>/Constant2'
   */
  if (rtsiIsModeUpdateTimeStep(RMT_FDM_RT_M->solverInfo)) {
    zcEvent_e = rt_ZCFcn(RISING_ZERO_CROSSING,
                         &localZCE->w_z_int_PRot_P_err_radDs_Reset_ZCE_n0z5,
                         (1.0));

    /* evaluate zero-crossings */
    if ((zcEvent_e != NO_ZCEVENT) ||
        localDW->w_z_int_PRot_P_err_radDs_DWORK1_fmga) {
      localX->w_z_int_PRot_P_err_radDs_ir34 = RMT_FDM_RT_ConstB.Constant3_k3xf;
    }
  }

  if (rtmIsMajorTimeStep(RMT_FDM_RT_M)) {
    /* Gain: '<S249>/Gain' incorporates:
     *  RandomNumber: '<S249>/Random Number2'
     */
    tmp_t = 0.0;
    for (i_8r = 0; i_8r < 3; i_8r = i_8r + 1) {
      tmp_t = tmp_t + rtCP_Gain_Gain_m1t0[i_8r] * b_RandomNumber2_gjti[i_8r];
    }

    /* Gain: '<S249>/Gain' */
    localB->Gain_cid3 = tmp_t;
  }

  /* Switch: '<S300>/Switch' */
  if (rtu_Simulation_Control->flg_Enable_Sensor_Errors) {
    /* Saturate: '<S249>/Saturation' */
    if (localX->w_z_int_PRot_P_err_radDs_ir34 > 2712.0) {
      y_d = 2712.0;
    } else if (localX->w_z_int_PRot_P_err_radDs_ir34 < 0.0) {
      y_d = 0.0;
    } else {
      y_d = localX->w_z_int_PRot_P_err_radDs_ir34;
    }

    /* End of Saturate: '<S249>/Saturation' */

    /* BusCreator generated from: '<Root>/Measurements' incorporates:
     *  Sum: '<S249>/Add'
     */
    rty_Measurements->motor_meas.w7_meas_radDs = y_d + localB->Gain_cid3;
  } else {
    /* BusCreator generated from: '<Root>/Measurements' incorporates:
     *  SignalConversion: '<S249>/Signal Conversion1'
     */
    rty_Measurements->motor_meas.w7_meas_radDs =
      b_ImpAsg_InsertedFor_w_act_radDs_at_inport_0[6];
  }

  /* End of Switch: '<S300>/Switch' */

  /* Integrator: '<S314>/w_z_int_PRot_P_err_radDs' incorporates:
   *  Constant: '<S312>/Constant2'
   */
  if (rtsiIsModeUpdateTimeStep(RMT_FDM_RT_M->solverInfo)) {
    zcEvent_f = rt_ZCFcn(RISING_ZERO_CROSSING,
                         &localZCE->w_z_int_PRot_P_err_radDs_Reset_ZCE_fwzs,
                         (1.0));

    /* evaluate zero-crossings */
    if ((zcEvent_f != NO_ZCEVENT) ||
        localDW->w_z_int_PRot_P_err_radDs_DWORK1_ncdx) {
      localX->w_z_int_PRot_P_err_radDs_kbfn = RMT_FDM_RT_ConstB.Constant3_dgfh;
    }
  }

  if (rtmIsMajorTimeStep(RMT_FDM_RT_M)) {
    /* Gain: '<S250>/Gain' incorporates:
     *  RandomNumber: '<S250>/Random Number2'
     */
    tmp_u = 0.0;
    for (i_8s = 0; i_8s < 3; i_8s = i_8s + 1) {
      tmp_u = tmp_u + rtCP_Gain_Gain_cpem[i_8s] * b_RandomNumber2_p3bk[i_8s];
    }

    /* Gain: '<S250>/Gain' */
    localB->Gain_ao53 = tmp_u;
  }

  /* Switch: '<S308>/Switch' */
  if (rtu_Simulation_Control->flg_Enable_Sensor_Errors) {
    /* Saturate: '<S250>/Saturation' */
    if (localX->w_z_int_PRot_P_err_radDs_kbfn > 2712.0) {
      y_e = 2712.0;
    } else if (localX->w_z_int_PRot_P_err_radDs_kbfn < 0.0) {
      y_e = 0.0;
    } else {
      y_e = localX->w_z_int_PRot_P_err_radDs_kbfn;
    }

    /* End of Saturate: '<S250>/Saturation' */

    /* BusCreator generated from: '<Root>/Measurements' incorporates:
     *  Sum: '<S250>/Add'
     */
    rty_Measurements->motor_meas.w8_meas_radDs = y_e + localB->Gain_ao53;
  } else {
    /* BusCreator generated from: '<Root>/Measurements' incorporates:
     *  SignalConversion: '<S250>/Signal Conversion1'
     */
    rty_Measurements->motor_meas.w8_meas_radDs =
      b_ImpAsg_InsertedFor_w_act_radDs_at_inport_0[7];
  }

  /* End of Switch: '<S308>/Switch' */

  /* Integrator: '<S398>/w_z_int_PRot_P_err_radDs' incorporates:
   *  Constant: '<S396>/Constant2'
   */
  if (rtsiIsModeUpdateTimeStep(RMT_FDM_RT_M->solverInfo)) {
    zcEvent_g = rt_ZCFcn(RISING_ZERO_CROSSING,
                         &localZCE->w_z_int_PRot_P_err_radDs_Reset_ZCE_epvd,
                         (1.0));

    /* evaluate zero-crossings */
    if ((zcEvent_g != NO_ZCEVENT) ||
        localDW->w_z_int_PRot_P_err_radDs_DWORK1_itla) {
      localX->w_z_int_PRot_P_err_radDs_oqys = RMT_FDM_RT_ConstB.Constant3_n2ml;
    }
  }

  if (rtmIsMajorTimeStep(RMT_FDM_RT_M)) {
    /* Gain: '<S390>/Gain' incorporates:
     *  RandomNumber: '<S390>/Random Number2'
     */
    tmp_v = 0.0;
    for (i_8t = 0; i_8t < 3; i_8t = i_8t + 1) {
      tmp_v = tmp_v + rtCP_Gain_Gain_enbz[i_8t] * b_RandomNumber2_nzfy[i_8t];
    }

    /* Gain: '<S390>/Gain' */
    localB->Gain_kx5f = tmp_v;
  }

  /* RelationalOperator: '<S389>/Compare' incorporates:
   *  Constant: '<S389>/Constant'
   *  Integrator: '<S17>/pos_z'
   */
  b_LogicalOperator = (localX->z_R_O_m >= 0.0);

  /* DataTypeConversion: '<S227>/Data Type Conversion' incorporates:
   *  Constant: '<S389>/Constant'
   *  Integrator: '<S17>/pos_z'
   *  RelationalOperator: '<S389>/Compare'
   */
  b_DataTypeConversion = (real_T)(localX->z_R_O_m >= 0.0);

  /* Switch: '<S392>/Switch' */
  if (rtu_Simulation_Control->flg_Enable_Sensor_Errors) {
    /* Saturate: '<S390>/Saturation' */
    if (localX->w_z_int_PRot_P_err_radDs_oqys > 1.0) {
      y_f = 1.0;
    } else if (localX->w_z_int_PRot_P_err_radDs_oqys < 0.0) {
      y_f = 0.0;
    } else {
      y_f = localX->w_z_int_PRot_P_err_radDs_oqys;
    }

    /* End of Saturate: '<S390>/Saturation' */

    /* BusCreator generated from: '<Root>/Measurements' incorporates:
     *  Sum: '<S390>/Add'
     */
    rty_Measurements->switches_meas.wow_switch_1_meas = y_f + localB->Gain_kx5f;
  } else {
    /* BusCreator generated from: '<Root>/Measurements' incorporates:
     *  DataTypeConversion: '<S227>/Data Type Conversion'
     */
    rty_Measurements->switches_meas.wow_switch_1_meas = (real_T)
      b_LogicalOperator;
  }

  /* End of Switch: '<S392>/Switch' */

  /* Integrator: '<S397>/w_z_int_PRot_P_err_radDs' incorporates:
   *  Constant: '<S395>/Constant2'
   */
  if (rtsiIsModeUpdateTimeStep(RMT_FDM_RT_M->solverInfo)) {
    zcEvent_h = rt_ZCFcn(RISING_ZERO_CROSSING,
                         &localZCE->w_z_int_PRot_P_err_radDs_Reset_ZCE_g1z1,
                         (1.0));

    /* evaluate zero-crossings */
    if ((zcEvent_h != NO_ZCEVENT) ||
        localDW->w_z_int_PRot_P_err_radDs_DWORK1_psoo) {
      localX->w_z_int_PRot_P_err_radDs_fldy = RMT_FDM_RT_ConstB.Constant3_dicm;
    }
  }

  /* Product: '<S394>/Product1' incorporates:
   *  Constant: '<S394>/Constant1'
   *  Constant: '<S394>/Constant2'
   *  DataTypeConversion: '<S184>/Data Type Conversion'
   *  Product: '<S310>/Product1'
   *  Product: '<S337>/Product1'
   *  Sum: '<S394>/Add'
   */
  Product_mmjp_tmp = (b_Sum1_hc1q - 293.15) * 0.0;

  /* Product: '<S397>/Product' incorporates:
   *  Abs: '<S391>/Abs'
   *  Constant: '<S391>/Constant2'
   *  Constant: '<S391>/Constant3'
   *  Constant: '<S393>/Constant'
   *  Constant: '<S394>/Constant3'
   *  DataTypeConversion: '<S227>/Data Type Conversion'
   *  Integrator: '<S397>/w_z_int_PRot_P_err_radDs'
   *  Product: '<S391>/Product'
   *  Product: '<S391>/Product1'
   *  Product: '<S391>/Product2'
   *  Product: '<S393>/Product'
   *  Product: '<S394>/Product1'
   *  Sum: '<S391>/Add'
   *  Sum: '<S391>/Add1'
   *  Sum: '<S391>/Add2'
   *  Sum: '<S391>/Sum'
   *  Sum: '<S393>/Sum'
   *  Sum: '<S394>/Sum'
   */
  localB->Product_mmjp = 0.62831853071795862 * (((RMT_FDM_RT_ConstB.Add_dw0h *
    b_DataTypeConversion + (fabs(b_DataTypeConversion) * (real_T)
    b_LogicalOperator * 0.0 + 0.0 * (real_T)b_LogicalOperator * (real_T)
    b_LogicalOperator)) + (Product_mmjp_tmp + 0.01)) -
    localX->w_z_int_PRot_P_err_radDs_fldy);

  /* Product: '<S398>/Product' incorporates:
   *  Constant: '<S393>/Constant'
   *  Integrator: '<S397>/w_z_int_PRot_P_err_radDs'
   *  Integrator: '<S398>/w_z_int_PRot_P_err_radDs'
   *  Product: '<S393>/Product1'
   *  Sum: '<S393>/Sum1'
   */
  localB->Product_aaq4 = 0.62831853071795862 *
    (localX->w_z_int_PRot_P_err_radDs_fldy -
     localX->w_z_int_PRot_P_err_radDs_oqys);

  /* Integrator: '<S313>/w_z_int_PRot_P_err_radDs' incorporates:
   *  Constant: '<S311>/Constant2'
   */
  if (rtsiIsModeUpdateTimeStep(RMT_FDM_RT_M->solverInfo)) {
    zcEvent_i = rt_ZCFcn(RISING_ZERO_CROSSING,
                         &localZCE->w_z_int_PRot_P_err_radDs_Reset_ZCE_ednt,
                         (1.0));

    /* evaluate zero-crossings */
    if ((zcEvent_i != NO_ZCEVENT) ||
        localDW->w_z_int_PRot_P_err_radDs_DWORK1_f3vl) {
      localX->w_z_int_PRot_P_err_radDs_czdk = RMT_FDM_RT_ConstB.Constant3_kqhj;
    }
  }

  /* Product: '<S314>/Product' incorporates:
   *  Constant: '<S309>/Constant'
   *  Integrator: '<S313>/w_z_int_PRot_P_err_radDs'
   *  Integrator: '<S314>/w_z_int_PRot_P_err_radDs'
   *  Product: '<S309>/Product1'
   *  Sum: '<S309>/Sum1'
   */
  localB->Product_earu = 0.62831853071795862 *
    (localX->w_z_int_PRot_P_err_radDs_czdk -
     localX->w_z_int_PRot_P_err_radDs_kbfn);

  /* Product: '<S313>/Product' incorporates:
   *  Abs: '<S307>/Abs'
   *  Constant: '<S307>/Constant2'
   *  Constant: '<S307>/Constant3'
   *  Constant: '<S309>/Constant'
   *  Constant: '<S310>/Constant3'
   *  Integrator: '<S313>/w_z_int_PRot_P_err_radDs'
   *  Product: '<S307>/Product'
   *  Product: '<S307>/Product1'
   *  Product: '<S307>/Product2'
   *  Product: '<S309>/Product'
   *  Sum: '<S307>/Add'
   *  Sum: '<S307>/Add1'
   *  Sum: '<S307>/Add2'
   *  Sum: '<S307>/Sum'
   *  Sum: '<S309>/Sum'
   *  Sum: '<S310>/Sum'
   */
  localB->Product_nb2v = 0.62831853071795862 * (((RMT_FDM_RT_ConstB.Add_ddhg *
    b_ImpAsg_InsertedFor_w_act_radDs_at_inport_0[7] + (fabs
    (b_ImpAsg_InsertedFor_w_act_radDs_at_inport_0[7]) *
    b_ImpAsg_InsertedFor_w_act_radDs_at_inport_0[7] * 0.0 + 0.0 *
    b_ImpAsg_InsertedFor_w_act_radDs_at_inport_0[7] *
    b_ImpAsg_InsertedFor_w_act_radDs_at_inport_0[7])) + (Product_mmjp_tmp +
    0.0008726646259971648)) - localX->w_z_int_PRot_P_err_radDs_czdk);

  /* Integrator: '<S305>/w_z_int_PRot_P_err_radDs' incorporates:
   *  Constant: '<S303>/Constant2'
   */
  if (rtsiIsModeUpdateTimeStep(RMT_FDM_RT_M->solverInfo)) {
    zcEvent_j = rt_ZCFcn(RISING_ZERO_CROSSING,
                         &localZCE->w_z_int_PRot_P_err_radDs_Reset_ZCE_c1ao,
                         (1.0));

    /* evaluate zero-crossings */
    if ((zcEvent_j != NO_ZCEVENT) ||
        localDW->w_z_int_PRot_P_err_radDs_DWORK1_iirx) {
      localX->w_z_int_PRot_P_err_radDs_pct4 = RMT_FDM_RT_ConstB.Constant3_cxlc;
    }
  }

  /* Product: '<S306>/Product' incorporates:
   *  Constant: '<S301>/Constant'
   *  Integrator: '<S305>/w_z_int_PRot_P_err_radDs'
   *  Integrator: '<S306>/w_z_int_PRot_P_err_radDs'
   *  Product: '<S301>/Product1'
   *  Sum: '<S301>/Sum1'
   */
  localB->Product_hoxf = 0.62831853071795862 *
    (localX->w_z_int_PRot_P_err_radDs_pct4 -
     localX->w_z_int_PRot_P_err_radDs_ir34);

  /* Product: '<S305>/Product' incorporates:
   *  Abs: '<S299>/Abs'
   *  Constant: '<S299>/Constant2'
   *  Constant: '<S299>/Constant3'
   *  Constant: '<S301>/Constant'
   *  Constant: '<S310>/Constant3'
   *  Integrator: '<S305>/w_z_int_PRot_P_err_radDs'
   *  Product: '<S299>/Product'
   *  Product: '<S299>/Product1'
   *  Product: '<S299>/Product2'
   *  Product: '<S301>/Product'
   *  Sum: '<S299>/Add'
   *  Sum: '<S299>/Add1'
   *  Sum: '<S299>/Add2'
   *  Sum: '<S299>/Sum'
   *  Sum: '<S301>/Sum'
   *  Sum: '<S310>/Sum'
   */
  localB->Product_a2bg = 0.62831853071795862 * (((RMT_FDM_RT_ConstB.Add_cmk0 *
    b_ImpAsg_InsertedFor_w_act_radDs_at_inport_0[6] + (fabs
    (b_ImpAsg_InsertedFor_w_act_radDs_at_inport_0[6]) *
    b_ImpAsg_InsertedFor_w_act_radDs_at_inport_0[6] * 0.0 + 0.0 *
    b_ImpAsg_InsertedFor_w_act_radDs_at_inport_0[6] *
    b_ImpAsg_InsertedFor_w_act_radDs_at_inport_0[6])) + (Product_mmjp_tmp +
    0.0008726646259971648)) - localX->w_z_int_PRot_P_err_radDs_pct4);

  /* Integrator: '<S297>/w_z_int_PRot_P_err_radDs' incorporates:
   *  Constant: '<S295>/Constant2'
   */
  if (rtsiIsModeUpdateTimeStep(RMT_FDM_RT_M->solverInfo)) {
    zcEvent_k = rt_ZCFcn(RISING_ZERO_CROSSING,
                         &localZCE->w_z_int_PRot_P_err_radDs_Reset_ZCE_cc4d,
                         (1.0));

    /* evaluate zero-crossings */
    if ((zcEvent_k != NO_ZCEVENT) ||
        localDW->w_z_int_PRot_P_err_radDs_DWORK1_caav) {
      localX->w_z_int_PRot_P_err_radDs_oaeq = RMT_FDM_RT_ConstB.Constant3_foac;
    }
  }

  /* Product: '<S298>/Product' incorporates:
   *  Constant: '<S293>/Constant'
   *  Integrator: '<S297>/w_z_int_PRot_P_err_radDs'
   *  Integrator: '<S298>/w_z_int_PRot_P_err_radDs'
   *  Product: '<S293>/Product1'
   *  Sum: '<S293>/Sum1'
   */
  localB->Product_fis5 = 0.62831853071795862 *
    (localX->w_z_int_PRot_P_err_radDs_oaeq -
     localX->w_z_int_PRot_P_err_radDs_l00j);

  /* Product: '<S297>/Product' incorporates:
   *  Abs: '<S291>/Abs'
   *  Constant: '<S291>/Constant2'
   *  Constant: '<S291>/Constant3'
   *  Constant: '<S293>/Constant'
   *  Constant: '<S310>/Constant3'
   *  Integrator: '<S297>/w_z_int_PRot_P_err_radDs'
   *  Product: '<S291>/Product'
   *  Product: '<S291>/Product1'
   *  Product: '<S291>/Product2'
   *  Product: '<S293>/Product'
   *  Sum: '<S291>/Add'
   *  Sum: '<S291>/Add1'
   *  Sum: '<S291>/Add2'
   *  Sum: '<S291>/Sum'
   *  Sum: '<S293>/Sum'
   *  Sum: '<S310>/Sum'
   */
  localB->Product_cgbz = 0.62831853071795862 * (((RMT_FDM_RT_ConstB.Add_ohj5 *
    b_ImpAsg_InsertedFor_w_act_radDs_at_inport_0[5] + (fabs
    (b_ImpAsg_InsertedFor_w_act_radDs_at_inport_0[5]) *
    b_ImpAsg_InsertedFor_w_act_radDs_at_inport_0[5] * 0.0 + 0.0 *
    b_ImpAsg_InsertedFor_w_act_radDs_at_inport_0[5] *
    b_ImpAsg_InsertedFor_w_act_radDs_at_inport_0[5])) + (Product_mmjp_tmp +
    0.0008726646259971648)) - localX->w_z_int_PRot_P_err_radDs_oaeq);

  /* Integrator: '<S289>/w_z_int_PRot_P_err_radDs' incorporates:
   *  Constant: '<S287>/Constant2'
   */
  if (rtsiIsModeUpdateTimeStep(RMT_FDM_RT_M->solverInfo)) {
    zcEvent_l = rt_ZCFcn(RISING_ZERO_CROSSING,
                         &localZCE->w_z_int_PRot_P_err_radDs_Reset_ZCE_aq0k,
                         (1.0));

    /* evaluate zero-crossings */
    if ((zcEvent_l != NO_ZCEVENT) ||
        localDW->w_z_int_PRot_P_err_radDs_DWORK1_cogt) {
      localX->w_z_int_PRot_P_err_radDs_nhxo = RMT_FDM_RT_ConstB.Constant3_ghn0;
    }
  }

  /* Product: '<S290>/Product' incorporates:
   *  Constant: '<S285>/Constant'
   *  Integrator: '<S289>/w_z_int_PRot_P_err_radDs'
   *  Integrator: '<S290>/w_z_int_PRot_P_err_radDs'
   *  Product: '<S285>/Product1'
   *  Sum: '<S285>/Sum1'
   */
  localB->Product_hkbl = 0.62831853071795862 *
    (localX->w_z_int_PRot_P_err_radDs_nhxo -
     localX->w_z_int_PRot_P_err_radDs_adwj);

  /* Product: '<S289>/Product' incorporates:
   *  Abs: '<S283>/Abs'
   *  Constant: '<S283>/Constant2'
   *  Constant: '<S283>/Constant3'
   *  Constant: '<S285>/Constant'
   *  Constant: '<S310>/Constant3'
   *  Integrator: '<S289>/w_z_int_PRot_P_err_radDs'
   *  Product: '<S283>/Product'
   *  Product: '<S283>/Product1'
   *  Product: '<S283>/Product2'
   *  Product: '<S285>/Product'
   *  Sum: '<S283>/Add'
   *  Sum: '<S283>/Add1'
   *  Sum: '<S283>/Add2'
   *  Sum: '<S283>/Sum'
   *  Sum: '<S285>/Sum'
   *  Sum: '<S310>/Sum'
   */
  localB->Product_butr = 0.62831853071795862 * (((RMT_FDM_RT_ConstB.Add_l53g *
    b_ImpAsg_InsertedFor_w_act_radDs_at_inport_0[4] + (fabs
    (b_ImpAsg_InsertedFor_w_act_radDs_at_inport_0[4]) *
    b_ImpAsg_InsertedFor_w_act_radDs_at_inport_0[4] * 0.0 + 0.0 *
    b_ImpAsg_InsertedFor_w_act_radDs_at_inport_0[4] *
    b_ImpAsg_InsertedFor_w_act_radDs_at_inport_0[4])) + (Product_mmjp_tmp +
    0.0008726646259971648)) - localX->w_z_int_PRot_P_err_radDs_nhxo);

  /* Integrator: '<S281>/w_z_int_PRot_P_err_radDs' incorporates:
   *  Constant: '<S279>/Constant2'
   */
  if (rtsiIsModeUpdateTimeStep(RMT_FDM_RT_M->solverInfo)) {
    zcEvent_m = rt_ZCFcn(RISING_ZERO_CROSSING,
                         &localZCE->w_z_int_PRot_P_err_radDs_Reset_ZCE_adnv,
                         (1.0));

    /* evaluate zero-crossings */
    if ((zcEvent_m != NO_ZCEVENT) ||
        localDW->w_z_int_PRot_P_err_radDs_DWORK1_jhud) {
      localX->w_z_int_PRot_P_err_radDs_l5ua = RMT_FDM_RT_ConstB.Constant3_cziw;
    }
  }

  /* Product: '<S282>/Product' incorporates:
   *  Constant: '<S277>/Constant'
   *  Integrator: '<S281>/w_z_int_PRot_P_err_radDs'
   *  Integrator: '<S282>/w_z_int_PRot_P_err_radDs'
   *  Product: '<S277>/Product1'
   *  Sum: '<S277>/Sum1'
   */
  localB->Product_o353 = 0.62831853071795862 *
    (localX->w_z_int_PRot_P_err_radDs_l5ua -
     localX->w_z_int_PRot_P_err_radDs_njv5);

  /* Product: '<S281>/Product' incorporates:
   *  Abs: '<S275>/Abs'
   *  Constant: '<S275>/Constant2'
   *  Constant: '<S275>/Constant3'
   *  Constant: '<S277>/Constant'
   *  Constant: '<S310>/Constant3'
   *  Integrator: '<S281>/w_z_int_PRot_P_err_radDs'
   *  Product: '<S275>/Product'
   *  Product: '<S275>/Product1'
   *  Product: '<S275>/Product2'
   *  Product: '<S277>/Product'
   *  Sum: '<S275>/Add'
   *  Sum: '<S275>/Add1'
   *  Sum: '<S275>/Add2'
   *  Sum: '<S275>/Sum'
   *  Sum: '<S277>/Sum'
   *  Sum: '<S310>/Sum'
   */
  localB->Product_m1vo = 0.62831853071795862 * (((RMT_FDM_RT_ConstB.Add_ihsl *
    b_ImpAsg_InsertedFor_w_act_radDs_at_inport_0[3] + (fabs
    (b_ImpAsg_InsertedFor_w_act_radDs_at_inport_0[3]) *
    b_ImpAsg_InsertedFor_w_act_radDs_at_inport_0[3] * 0.0 + 0.0 *
    b_ImpAsg_InsertedFor_w_act_radDs_at_inport_0[3] *
    b_ImpAsg_InsertedFor_w_act_radDs_at_inport_0[3])) + (Product_mmjp_tmp +
    0.0008726646259971648)) - localX->w_z_int_PRot_P_err_radDs_l5ua);

  /* Integrator: '<S273>/w_z_int_PRot_P_err_radDs' incorporates:
   *  Constant: '<S271>/Constant2'
   */
  if (rtsiIsModeUpdateTimeStep(RMT_FDM_RT_M->solverInfo)) {
    zcEvent_n = rt_ZCFcn(RISING_ZERO_CROSSING,
                         &localZCE->w_z_int_PRot_P_err_radDs_Reset_ZCE_napy,
                         (1.0));

    /* evaluate zero-crossings */
    if ((zcEvent_n != NO_ZCEVENT) ||
        localDW->w_z_int_PRot_P_err_radDs_DWORK1_no0f) {
      localX->w_z_int_PRot_P_err_radDs_c3cm = RMT_FDM_RT_ConstB.Constant3_g2iw;
    }
  }

  /* Product: '<S274>/Product' incorporates:
   *  Constant: '<S269>/Constant'
   *  Integrator: '<S273>/w_z_int_PRot_P_err_radDs'
   *  Integrator: '<S274>/w_z_int_PRot_P_err_radDs'
   *  Product: '<S269>/Product1'
   *  Sum: '<S269>/Sum1'
   */
  localB->Product_jjey = 0.62831853071795862 *
    (localX->w_z_int_PRot_P_err_radDs_c3cm -
     localX->w_z_int_PRot_P_err_radDs_aexu);

  /* Product: '<S273>/Product' incorporates:
   *  Abs: '<S267>/Abs'
   *  Constant: '<S267>/Constant2'
   *  Constant: '<S267>/Constant3'
   *  Constant: '<S269>/Constant'
   *  Constant: '<S310>/Constant3'
   *  Integrator: '<S273>/w_z_int_PRot_P_err_radDs'
   *  Product: '<S267>/Product'
   *  Product: '<S267>/Product1'
   *  Product: '<S267>/Product2'
   *  Product: '<S269>/Product'
   *  Sum: '<S267>/Add'
   *  Sum: '<S267>/Add1'
   *  Sum: '<S267>/Add2'
   *  Sum: '<S267>/Sum'
   *  Sum: '<S269>/Sum'
   *  Sum: '<S310>/Sum'
   */
  localB->Product_nn4o = 0.62831853071795862 * (((RMT_FDM_RT_ConstB.Add_avhk *
    b_ImpAsg_InsertedFor_w_act_radDs_at_inport_0[2] + (fabs
    (b_ImpAsg_InsertedFor_w_act_radDs_at_inport_0[2]) *
    b_ImpAsg_InsertedFor_w_act_radDs_at_inport_0[2] * 0.0 + 0.0 *
    b_ImpAsg_InsertedFor_w_act_radDs_at_inport_0[2] *
    b_ImpAsg_InsertedFor_w_act_radDs_at_inport_0[2])) + (Product_mmjp_tmp +
    0.0008726646259971648)) - localX->w_z_int_PRot_P_err_radDs_c3cm);

  /* Integrator: '<S265>/w_z_int_PRot_P_err_radDs' incorporates:
   *  Constant: '<S263>/Constant2'
   */
  if (rtsiIsModeUpdateTimeStep(RMT_FDM_RT_M->solverInfo)) {
    zcEvent_o = rt_ZCFcn(RISING_ZERO_CROSSING,
                         &localZCE->w_z_int_PRot_P_err_radDs_Reset_ZCE_cobq,
                         (1.0));

    /* evaluate zero-crossings */
    if ((zcEvent_o != NO_ZCEVENT) ||
        localDW->w_z_int_PRot_P_err_radDs_DWORK1_da4c) {
      localX->w_z_int_PRot_P_err_radDs_j2wc = RMT_FDM_RT_ConstB.Constant3_pmct;
    }
  }

  /* Product: '<S266>/Product' incorporates:
   *  Constant: '<S261>/Constant'
   *  Integrator: '<S265>/w_z_int_PRot_P_err_radDs'
   *  Integrator: '<S266>/w_z_int_PRot_P_err_radDs'
   *  Product: '<S261>/Product1'
   *  Sum: '<S261>/Sum1'
   */
  localB->Product_esat = 0.62831853071795862 *
    (localX->w_z_int_PRot_P_err_radDs_j2wc -
     localX->w_z_int_PRot_P_err_radDs_cjc1);

  /* Product: '<S265>/Product' incorporates:
   *  Abs: '<S259>/Abs'
   *  Constant: '<S259>/Constant2'
   *  Constant: '<S259>/Constant3'
   *  Constant: '<S261>/Constant'
   *  Constant: '<S310>/Constant3'
   *  Integrator: '<S265>/w_z_int_PRot_P_err_radDs'
   *  Product: '<S259>/Product'
   *  Product: '<S259>/Product1'
   *  Product: '<S259>/Product2'
   *  Product: '<S261>/Product'
   *  Sum: '<S259>/Add'
   *  Sum: '<S259>/Add1'
   *  Sum: '<S259>/Add2'
   *  Sum: '<S259>/Sum'
   *  Sum: '<S261>/Sum'
   *  Sum: '<S310>/Sum'
   */
  localB->Product_e45n = 0.62831853071795862 * (((RMT_FDM_RT_ConstB.Add_ld10 *
    b_ImpAsg_InsertedFor_w_act_radDs_at_inport_0[1] + (fabs
    (b_ImpAsg_InsertedFor_w_act_radDs_at_inport_0[1]) *
    b_ImpAsg_InsertedFor_w_act_radDs_at_inport_0[1] * 0.0 + 0.0 *
    b_ImpAsg_InsertedFor_w_act_radDs_at_inport_0[1] *
    b_ImpAsg_InsertedFor_w_act_radDs_at_inport_0[1])) + (Product_mmjp_tmp +
    0.0008726646259971648)) - localX->w_z_int_PRot_P_err_radDs_j2wc);

  /* Integrator: '<S257>/w_z_int_PRot_P_err_radDs' incorporates:
   *  Constant: '<S255>/Constant2'
   */
  if (rtsiIsModeUpdateTimeStep(RMT_FDM_RT_M->solverInfo)) {
    zcEvent_p = rt_ZCFcn(RISING_ZERO_CROSSING,
                         &localZCE->w_z_int_PRot_P_err_radDs_Reset_ZCE_bwxm,
                         (1.0));

    /* evaluate zero-crossings */
    if ((zcEvent_p != NO_ZCEVENT) ||
        localDW->w_z_int_PRot_P_err_radDs_DWORK1_does) {
      localX->w_z_int_PRot_P_err_radDs_puds = RMT_FDM_RT_ConstB.Constant3_g0qm;
    }
  }

  /* Product: '<S258>/Product' incorporates:
   *  Constant: '<S253>/Constant'
   *  Integrator: '<S257>/w_z_int_PRot_P_err_radDs'
   *  Integrator: '<S258>/w_z_int_PRot_P_err_radDs'
   *  Product: '<S253>/Product1'
   *  Sum: '<S253>/Sum1'
   */
  localB->Product_h3kv = 0.62831853071795862 *
    (localX->w_z_int_PRot_P_err_radDs_puds -
     localX->w_z_int_PRot_P_err_radDs_baxu);

  /* Product: '<S257>/Product' incorporates:
   *  Abs: '<S251>/Abs'
   *  Constant: '<S251>/Constant2'
   *  Constant: '<S251>/Constant3'
   *  Constant: '<S253>/Constant'
   *  Constant: '<S310>/Constant3'
   *  Integrator: '<S257>/w_z_int_PRot_P_err_radDs'
   *  Product: '<S251>/Product'
   *  Product: '<S251>/Product1'
   *  Product: '<S251>/Product2'
   *  Product: '<S253>/Product'
   *  Sum: '<S251>/Add'
   *  Sum: '<S251>/Add1'
   *  Sum: '<S251>/Add2'
   *  Sum: '<S251>/Sum'
   *  Sum: '<S253>/Sum'
   *  Sum: '<S310>/Sum'
   */
  localB->Product_j1jn = 0.62831853071795862 * (((RMT_FDM_RT_ConstB.Add_ezdo *
    b_ImpAsg_InsertedFor_w_act_radDs_at_inport_0[0] + (fabs
    (b_ImpAsg_InsertedFor_w_act_radDs_at_inport_0[0]) *
    b_ImpAsg_InsertedFor_w_act_radDs_at_inport_0[0] * 0.0 + 0.0 *
    b_ImpAsg_InsertedFor_w_act_radDs_at_inport_0[0] *
    b_ImpAsg_InsertedFor_w_act_radDs_at_inport_0[0])) + (Product_mmjp_tmp +
    0.0008726646259971648)) - localX->w_z_int_PRot_P_err_radDs_puds);

  /* Integrator: '<S324>/w_z_int_PRot_P_err_radDs' incorporates:
   *  Constant: '<S322>/Constant2'
   */
  if (rtsiIsModeUpdateTimeStep(RMT_FDM_RT_M->solverInfo)) {
    zcEvent_q = rt_ZCFcn(RISING_ZERO_CROSSING,
                         &localZCE->w_z_int_PRot_P_err_radDs_Reset_ZCE_pbyv,
                         (1.0));

    /* evaluate zero-crossings */
    if ((zcEvent_q != NO_ZCEVENT) ||
        localDW->w_z_int_PRot_P_err_radDs_DWORK1_mmow) {
      localX->w_z_int_PRot_P_err_radDs_ons5 = RMT_FDM_RT_ConstB.Constant3_h21r;
    }
  }

  /* Sum: '<S321>/Sum' incorporates:
   *  Constant: '<S321>/Constant1'
   *  Constant: '<S321>/Constant2'
   *  Constant: '<S321>/Constant3'
   *  DataTypeConversion: '<S184>/Data Type Conversion'
   *  Product: '<S321>/Product1'
   *  Sum: '<S321>/Add'
   *  Sum: '<S329>/Sum'
   */
  Product_hwmn_tmp = (b_Sum1_hc1q - 293.15) * 0.001 + 0.5;

  /* Product: '<S324>/Product' incorporates:
   *  Abs: '<S318>/Abs'
   *  Constant: '<S318>/Constant2'
   *  Constant: '<S318>/Constant3'
   *  Constant: '<S320>/Constant'
   *  Gain: '<S224>/Gain'
   *  Integrator: '<S17>/pos_z'
   *  Integrator: '<S324>/w_z_int_PRot_P_err_radDs'
   *  Product: '<S318>/Product'
   *  Product: '<S318>/Product1'
   *  Product: '<S318>/Product2'
   *  Product: '<S320>/Product'
   *  Sum: '<S318>/Add'
   *  Sum: '<S318>/Add1'
   *  Sum: '<S318>/Add2'
   *  Sum: '<S318>/Sum'
   *  Sum: '<S320>/Sum'
   *  Sum: '<S321>/Sum'
   */
  localB->Product_hwmn = 157.07963267948966 * (((RMT_FDM_RT_ConstB.Add_dbyu *
    -localX->z_R_O_m + (fabs(-localX->z_R_O_m) * -localX->z_R_O_m * 0.0 + 0.0 *
                        -localX->z_R_O_m * -localX->z_R_O_m)) + Product_hwmn_tmp)
    - localX->w_z_int_PRot_P_err_radDs_ons5);

  /* Product: '<S325>/Product' incorporates:
   *  Constant: '<S320>/Constant'
   *  Integrator: '<S324>/w_z_int_PRot_P_err_radDs'
   *  Integrator: '<S325>/w_z_int_PRot_P_err_radDs'
   *  Product: '<S320>/Product1'
   *  Sum: '<S320>/Sum1'
   */
  localB->Product_eeeg = 157.07963267948966 *
    (localX->w_z_int_PRot_P_err_radDs_ons5 -
     localX->w_z_int_PRot_P_err_radDs_jowp);

  /* Integrator: '<S340>/w_z_int_PRot_P_err_radDs' incorporates:
   *  Constant: '<S338>/Constant2'
   */
  if (rtsiIsModeUpdateTimeStep(RMT_FDM_RT_M->solverInfo)) {
    zcEvent_r = rt_ZCFcn(RISING_ZERO_CROSSING,
                         &localZCE->w_z_int_PRot_P_err_radDs_Reset_ZCE_amgb,
                         (1.0));

    /* evaluate zero-crossings */
    if ((zcEvent_r != NO_ZCEVENT) ||
        localDW->w_z_int_PRot_P_err_radDs_DWORK1_hg1y) {
      localX->w_z_int_PRot_P_err_radDs_a2pk = RMT_FDM_RT_ConstB.Constant3_kapz;
    }
  }

  /* Product: '<S341>/Product' incorporates:
   *  Constant: '<S336>/Constant'
   *  Integrator: '<S340>/w_z_int_PRot_P_err_radDs'
   *  Integrator: '<S341>/w_z_int_PRot_P_err_radDs'
   *  Product: '<S336>/Product1'
   *  Sum: '<S336>/Sum1'
   */
  localB->Product_koc0 = 0.62831853071795862 *
    (localX->w_z_int_PRot_P_err_radDs_a2pk -
     localX->w_z_int_PRot_P_err_radDs_dftl);

  /* Product: '<S340>/Product' incorporates:
   *  Abs: '<S334>/Abs'
   *  Constant: '<S334>/Constant2'
   *  Constant: '<S334>/Constant3'
   *  Constant: '<S336>/Constant'
   *  Constant: '<S337>/Constant3'
   *  DataTypeConversion: '<S184>/Data Type Conversion'
   *  Integrator: '<S340>/w_z_int_PRot_P_err_radDs'
   *  Product: '<S334>/Product'
   *  Product: '<S334>/Product1'
   *  Product: '<S334>/Product2'
   *  Product: '<S336>/Product'
   *  Sum: '<S334>/Add'
   *  Sum: '<S334>/Add1'
   *  Sum: '<S334>/Add2'
   *  Sum: '<S334>/Sum'
   *  Sum: '<S336>/Sum'
   *  Sum: '<S337>/Sum'
   */
  localB->Product_nmeo = 0.62831853071795862 * (((RMT_FDM_RT_ConstB.Add_dggw *
    b_Sum1_hc1q + (fabs(b_Sum1_hc1q) * b_Sum1_hc1q * 0.0 + 0.0 * b_Sum1_hc1q *
                   b_Sum1_hc1q)) + (Product_mmjp_tmp + 0.5)) -
    localX->w_z_int_PRot_P_err_radDs_a2pk);

  /* Integrator: '<S332>/w_z_int_PRot_P_err_radDs' incorporates:
   *  Constant: '<S330>/Constant2'
   */
  if (rtsiIsModeUpdateTimeStep(RMT_FDM_RT_M->solverInfo)) {
    zcEvent_s = rt_ZCFcn(RISING_ZERO_CROSSING,
                         &localZCE->w_z_int_PRot_P_err_radDs_Reset_ZCE_ff4n,
                         (1.0));

    /* evaluate zero-crossings */
    if ((zcEvent_s != NO_ZCEVENT) ||
        localDW->w_z_int_PRot_P_err_radDs_DWORK1_plxf) {
      localX->w_z_int_PRot_P_err_radDs_mh2t = RMT_FDM_RT_ConstB.Constant3_ilkj;
    }
  }

  /* Product: '<S333>/Product' incorporates:
   *  Constant: '<S328>/Constant'
   *  Integrator: '<S332>/w_z_int_PRot_P_err_radDs'
   *  Integrator: '<S333>/w_z_int_PRot_P_err_radDs'
   *  Product: '<S328>/Product1'
   *  Sum: '<S328>/Sum1'
   */
  localB->Product_jcdq = 157.07963267948966 *
    (localX->w_z_int_PRot_P_err_radDs_mh2t -
     localX->w_z_int_PRot_P_err_radDs_cg5d);

  /* Product: '<S332>/Product' incorporates:
   *  Abs: '<S326>/Abs'
   *  BusCreator generated from: '<S28>/Bus Assignment'
   *  Constant: '<S326>/Constant2'
   *  Constant: '<S326>/Constant3'
   *  Constant: '<S328>/Constant'
   *  Integrator: '<S332>/w_z_int_PRot_P_err_radDs'
   *  Product: '<S326>/Product'
   *  Product: '<S326>/Product1'
   *  Product: '<S326>/Product2'
   *  Product: '<S328>/Product'
   *  Sum: '<S326>/Add'
   *  Sum: '<S326>/Add1'
   *  Sum: '<S326>/Add2'
   *  Sum: '<S326>/Sum'
   *  Sum: '<S328>/Sum'
   */
  localB->Product_f0j2 = 157.07963267948966 * (((RMT_FDM_RT_ConstB.Add_n1j0 *
    b_Atmosphere.Static_Pressure_ATM_NDm2 + (fabs
    (b_Atmosphere.Static_Pressure_ATM_NDm2) *
    b_Atmosphere.Static_Pressure_ATM_NDm2 * 0.0 + 0.0 *
    b_Atmosphere.Static_Pressure_ATM_NDm2 *
    b_Atmosphere.Static_Pressure_ATM_NDm2)) + Product_hwmn_tmp) -
    localX->w_z_int_PRot_P_err_radDs_mh2t);

  /* BusCreator generated from: '<Root>/Vehicle' incorporates:
   *  Integrator: '<S15>/pos_x'
   *  Integrator: '<S16>/pos_y'
   *  Integrator: '<S17>/pos_z'
   */
  rty_Vehicle->States.pos_R_O_m.x_R_O_m = localX->x_R_O_m;
  rty_Vehicle->States.pos_R_O_m.y_R_O_m = localX->y_R_O_m;
  rty_Vehicle->States.pos_R_O_m.z_R_O_m = localX->z_R_O_m;

  /* BusCreator generated from: '<Root>/Vehicle' incorporates:
   *  Integrator: '<S18>/rot_x_K_IB_B_radDs'
   *  Integrator: '<S19>/rot_y_K_IB_B_radDs'
   *  Integrator: '<S20>/rot_z_K_IB_B_radDs'
   */
  rty_Vehicle->States.rot_K_IB_B_radDs.w_x_K_IB_B_radDs =
    localX->w_x_K_IB_B_radDs;
  rty_Vehicle->States.rot_K_IB_B_radDs.w_y_K_IB_B_radDs =
    localX->w_y_K_IB_B_radDs;
  rty_Vehicle->States.rot_K_IB_B_radDs.w_z_K_IB_B_radDs =
    localX->w_z_K_IB_B_radDs;

  /* BusCreator generated from: '<Root>/Vehicle' incorporates:
   *  Integrator: '<S12>/att_phi_rad'
   *  Integrator: '<S13>/att_psi_rad'
   *  Integrator: '<S14>/att_theta_rad'
   */
  rty_Vehicle->States.att_euler_rad.Phi_rad = localX->Phi_rad;
  rty_Vehicle->States.att_euler_rad.Theta_rad = localX->Theta_rad;
  rty_Vehicle->States.att_euler_rad.Psi_rad = localX->Psi_rad;

  /* BusCreator generated from: '<Root>/Vehicle' incorporates:
   *  Integrator: '<S21>/vel_x_K'
   *  Integrator: '<S22>/vel_y_K'
   *  Integrator: '<S23>/vel_w_K'
   */
  rty_Vehicle->States.vel_K_R_E_B_mDs.u_K_R_E_B_mDs = localX->u_K_R_E_B_mDs;
  rty_Vehicle->States.vel_K_R_E_B_mDs.v_K_R_E_B_mDs = localX->v_K_R_E_B_mDs;
  rty_Vehicle->States.vel_K_R_E_B_mDs.w_K_R_E_B_mDs = localX->w_K_R_E_B_mDs;

  /* BusCreator generated from: '<Root>/Vehicle' */
  rty_Vehicle->Commands.w1_act_radDs =
    b_ImpAsg_InsertedFor_w_act_radDs_at_inport_0[0];
  rty_Vehicle->Commands.w2_act_radDs =
    b_ImpAsg_InsertedFor_w_act_radDs_at_inport_0[1];
  rty_Vehicle->Commands.w3_act_radDs =
    b_ImpAsg_InsertedFor_w_act_radDs_at_inport_0[2];
  rty_Vehicle->Commands.w4_act_radDs =
    b_ImpAsg_InsertedFor_w_act_radDs_at_inport_0[3];
  rty_Vehicle->Commands.w5_act_radDs =
    b_ImpAsg_InsertedFor_w_act_radDs_at_inport_0[4];
  rty_Vehicle->Commands.w6_act_radDs =
    b_ImpAsg_InsertedFor_w_act_radDs_at_inport_0[5];
  rty_Vehicle->Commands.w7_act_radDs =
    b_ImpAsg_InsertedFor_w_act_radDs_at_inport_0[6];
  rty_Vehicle->Commands.w8_act_radDs =
    b_ImpAsg_InsertedFor_w_act_radDs_at_inport_0[7];

  /* BusCreator generated from: '<Root>/Vehicle' incorporates:
   *  BusAssignment: '<S28>/Bus Assignment'
   */
  rty_Vehicle->Outputs = b_Outputs;

  /* Product: '<S15>/Product' incorporates:
   *  DataTypeConversion: '<S15>/Data Type Conversion'
   *  Logic: '<S15>/Logical Operator'
   *  Product: '<S188>/Product'
   *  Reshape: '<S188>/Reshape'
   */
  localB->Product_etkr = b_vel_K_R_E_O_mDs[0] * (real_T)
    (rtu_Simulation_Control->flg_Run && rtu_Simulation_Control->flg_Run_pos_x);

  /* Product: '<S16>/Product' incorporates:
   *  DataTypeConversion: '<S16>/Data Type Conversion'
   *  Logic: '<S16>/Logical Operator'
   *  Product: '<S188>/Product'
   *  Reshape: '<S188>/Reshape'
   */
  localB->Product_hvg4 = b_vel_K_R_E_O_mDs[1] * (real_T)
    (rtu_Simulation_Control->flg_Run && rtu_Simulation_Control->flg_Run_pos_y);

  /* Product: '<S17>/Product' incorporates:
   *  DataTypeConversion: '<S17>/Data Type Conversion'
   *  Logic: '<S17>/Logical Operator'
   *  Product: '<S188>/Product'
   *  Reshape: '<S188>/Reshape'
   */
  localB->Product_mhkc = b_vel_K_R_E_O_mDs[2] * (real_T)
    (rtu_Simulation_Control->flg_Run && rtu_Simulation_Control->flg_Run_pos_z);

  /* Product: '<S12>/Product' incorporates:
   *  DataTypeConversion: '<S12>/Data Type Conversion'
   *  Logic: '<S12>/Logical Operator'
   */
  localB->Product_ldwx = b_Reshape3_czqe[0] * (real_T)
    (rtu_Simulation_Control->flg_Run && rtu_Simulation_Control->flg_Run_Phi);

  /* Product: '<S13>/Product' incorporates:
   *  DataTypeConversion: '<S13>/Data Type Conversion'
   *  Logic: '<S13>/Logical Operator'
   */
  localB->Product_nlow = b_Reshape3_czqe[2] * (real_T)
    (rtu_Simulation_Control->flg_Run && rtu_Simulation_Control->flg_Run_Psi);

  /* Product: '<S14>/Product' incorporates:
   *  DataTypeConversion: '<S14>/Data Type Conversion'
   *  Logic: '<S14>/Logical Operator'
   */
  localB->Product_ciqr = b_Reshape3_czqe[1] * (real_T)
    (rtu_Simulation_Control->flg_Run && rtu_Simulation_Control->flg_Run_Theta);

  /* Product: '<S21>/Product' incorporates:
   *  DataTypeConversion: '<S21>/Data Type Conversion'
   *  Logic: '<S21>/Logical Operator'
   */
  localB->Product_oxzs = b_Reshape_jgsm[0] * (real_T)
    (rtu_Simulation_Control->flg_Run && rtu_Simulation_Control->flg_Run_vel_x);

  /* DataTypeConversion: '<S22>/Data Type Conversion' incorporates:
   *  DataTypeConversion: '<S23>/Data Type Conversion'
   *  Logic: '<S22>/Logical Operator'
   */
  Product_p0uf_tmp = (real_T)(rtu_Simulation_Control->flg_Run &&
    rtu_Simulation_Control->flg_Run_vel_y);

  /* Product: '<S22>/Product' incorporates:
   *  DataTypeConversion: '<S22>/Data Type Conversion'
   */
  localB->Product_p0uf = b_Reshape_jgsm[1] * Product_p0uf_tmp;

  /* Product: '<S23>/Product' */
  localB->Product_neht = b_Reshape_jgsm[2] * Product_p0uf_tmp;

  /* Product: '<S18>/Product' incorporates:
   *  DataTypeConversion: '<S18>/Data Type Conversion'
   *  Logic: '<S18>/Logical Operator'
   */
  localB->Product_den3 = b_Reshape1_ejex[0] * (real_T)
    (rtu_Simulation_Control->flg_Run && rtu_Simulation_Control->flg_Run_p);

  /* Product: '<S19>/Product' incorporates:
   *  DataTypeConversion: '<S19>/Data Type Conversion'
   *  Logic: '<S19>/Logical Operator'
   */
  localB->Product_n25e = b_Reshape1_ejex[1] * (real_T)
    (rtu_Simulation_Control->flg_Run && rtu_Simulation_Control->flg_Run_q);

  /* Product: '<S20>/Product' incorporates:
   *  DataTypeConversion: '<S20>/Data Type Conversion'
   *  Logic: '<S20>/Logical Operator'
   */
  localB->Product_dcml = b_Reshape1_ejex[2] * (real_T)
    (rtu_Simulation_Control->flg_Run && rtu_Simulation_Control->flg_Run_r);
}

/* Update for referenced model: 'RMT_FDM_RT' */
void RMT_FDM_RT_Update(RT_MODEL_RMT_FDM_RT_T * const RMT_FDM_RT_M,
  B_RMT_FDM_RT_caua_T *localB, DW_RMT_FDM_RT_fwu4_T *localDW)
{
  /* local scratch DWork variables */
  int32_T ForEach_itr_gq2o;
  int32_T i;
  int32_T iU;
  int32_T iU_0;
  int32_T iU_1;
  int32_T iU_2;
  int32_T iU_3;
  int32_T iU_4;
  int32_T iU_5;
  int32_T iU_6;
  int32_T iU_7;
  int32_T iU_8;
  int32_T iU_9;
  int32_T iU_a;
  int32_T iU_b;
  int32_T iU_c;
  int32_T iU_d;
  int32_T iU_e;
  int32_T iU_f;
  int32_T iU_g;
  int32_T i_0;
  int32_T i_1;
  int32_T i_2;
  int32_T i_3;
  int32_T k;
  int32_T k_0;
  int32_T k_1;

  /* Update for Integrator: '<S12>/att_phi_rad' */
  localDW->att_phi_rad_DWORK1 = false;

  /* Update for Integrator: '<S14>/att_theta_rad' */
  localDW->att_theta_rad_DWORK1 = false;

  /* Update for Integrator: '<S13>/att_psi_rad' */
  localDW->att_psi_rad_DWORK1 = false;

  /* Update for Integrator: '<S21>/vel_x_K' */
  localDW->vel_x_K_DWORK1 = false;

  /* Update for Integrator: '<S22>/vel_y_K' */
  localDW->vel_y_K_DWORK1 = false;

  /* Update for Integrator: '<S23>/vel_w_K' */
  localDW->vel_w_K_DWORK1 = false;

  /* Update for Integrator: '<S238>/w_z_int_PRot_P_err_radDs' */
  localDW->w_z_int_PRot_P_err_radDs_DWORK1 = false;
  if (rtmIsMajorTimeStep(RMT_FDM_RT_M)) {
    /* Update for RandomNumber: '<S228>/Random Number2' */
    for (iU = 0; iU < 3; iU = iU + 1) {
      localDW->NextOutput[iU] = rt_nrand_Upu32_Yd_f_pw_snf(&localDW->RandSeed[iU]);
    }

    /* End of Update for RandomNumber: '<S228>/Random Number2' */
  }

  /* Update for Iterator SubSystem: '<S1>/Actuator_Ext_Reset' */
  for (ForEach_itr_gq2o = 0; ForEach_itr_gq2o < 8; ForEach_itr_gq2o =
       ForEach_itr_gq2o + 1) {
    /* Update for Integrator: '<S5>/Integrator' */
    localDW->CoreSubsys[ForEach_itr_gq2o].Integrator_DWORK1 = false;
  }

  /* End of Update for SubSystem: '<S1>/Actuator_Ext_Reset' */

  /* Update for Integrator: '<S18>/rot_x_K_IB_B_radDs' */
  localDW->rot_x_K_IB_B_radDs_DWORK1 = false;

  /* Update for Integrator: '<S19>/rot_y_K_IB_B_radDs' */
  localDW->rot_y_K_IB_B_radDs_DWORK1 = false;

  /* Update for Integrator: '<S20>/rot_z_K_IB_B_radDs' */
  localDW->rot_z_K_IB_B_radDs_DWORK1 = false;

  /* Update for Integrator: '<S17>/pos_z' */
  localDW->pos_z_DWORK1 = false;

  /* Update for Integrator: '<S237>/w_z_int_PRot_P_err_radDs' */
  localDW->w_z_int_PRot_P_err_radDs_DWORK1_ndwy = false;

  /* Update for Integrator: '<S372>/w_z_int_PRot_P_err_radDs' */
  localDW->w_z_int_PRot_P_err_radDs_DWORK1_ev2m = false;

  /* Update for Integrator: '<S373>/w_z_int_PRot_P_err_radDs' */
  localDW->w_z_int_PRot_P_err_radDs_DWORK1_kugd = false;
  if (rtmIsMajorTimeStep(RMT_FDM_RT_M)) {
    /* Update for RandomNumber: '<S364>/Random Number2' */
    for (iU_0 = 0; iU_0 < 3; iU_0 = iU_0 + 1) {
      localDW->NextOutput_k1ay[iU_0] = rt_nrand_Upu32_Yd_f_pw_snf
        (&localDW->RandSeed_icpv[iU_0]);
    }

    /* End of Update for RandomNumber: '<S364>/Random Number2' */

    /* Update for RandomNumber: '<S380>/Random Number2' */
    for (iU_1 = 0; iU_1 < 3; iU_1 = iU_1 + 1) {
      localDW->NextOutput_pvtx[iU_1] = rt_nrand_Upu32_Yd_f_pw_snf
        (&localDW->RandSeed_ju0n[iU_1]);
    }

    /* End of Update for RandomNumber: '<S380>/Random Number2' */

    /* Update for RandomNumber: '<S316>/Random Number2' */
    for (iU_2 = 0; iU_2 < 3; iU_2 = iU_2 + 1) {
      localDW->NextOutput_ba35[iU_2] = rt_nrand_Upu32_Yd_f_pw_snf
        (&localDW->RandSeed_h21n[iU_2]);
    }

    /* End of Update for RandomNumber: '<S316>/Random Number2' */
  }

  /* Update for Integrator: '<S387>/w_z_int_PRot_P_err_radDs' */
  localDW->w_z_int_PRot_P_err_radDs_DWORK1_h3i2 = false;

  /* Update for Integrator: '<S388>/w_z_int_PRot_P_err_radDs' */
  localDW->w_z_int_PRot_P_err_radDs_DWORK1_l3ag = false;
  if (rtmIsMajorTimeStep(RMT_FDM_RT_M) && rtmIsSampleHit(RMT_FDM_RT_M, 2)) {
    /* Update for RandomNumber: '<S354>/Random Number' */
    for (iU_3 = 0; iU_3 < 3; iU_3 = iU_3 + 1) {
      localDW->NextOutput_kxhu[iU_3] = rt_nrand_Upu32_Yd_f_pw_snf
        (&localDW->RandSeed_hc1z[iU_3]);
    }

    /* End of Update for RandomNumber: '<S354>/Random Number' */

    /* Update for DiscreteIntegrator: '<S354>/Discrete-Time Integrator2' incorporates:
     *  Sum: '<S354>/Add'
     */
    for (i_2 = 0; i_2 < 3; i_2 = i_2 + 1) {
      localDW->DiscreteTimeIntegrator2_DSTATE[i_2] =
        localDW->DiscreteTimeIntegrator2_DSTATE[i_2] + 0.2 * localB->w_dot[i_2];
    }

    /* End of Update for DiscreteIntegrator: '<S354>/Discrete-Time Integrator2' */

    /* Update for DiscreteIntegrator: '<S345>/Discrete-Time Integrator' incorporates:
     *  Gain: '<S345>/Gain1'
     */
    for (i_3 = 0; i_3 < 3; i_3 = i_3 + 1) {
      localDW->DiscreteTimeIntegrator_DSTATE[i_3] =
        localDW->DiscreteTimeIntegrator_DSTATE[i_3] + 0.2 * localB->Gain1[i_3];
    }

    /* End of Update for DiscreteIntegrator: '<S345>/Discrete-Time Integrator' */

    /* Update for DiscreteFir: '<S352>/Discrete FIR Filter' incorporates:
     *  Reshape: '<S352>/Reshape1'
     */
    /* Update states */
    for (k = 0; k < 3; k = k + 1) {
      localDW->DiscreteFIRFilter_states[k] = localB->Reshape1[k];
    }

    /* End of Update for DiscreteFir: '<S352>/Discrete FIR Filter' */

    /* Update for RandomNumber: '<S352>/Random Number' */
    for (iU_4 = 0; iU_4 < 3; iU_4 = iU_4 + 1) {
      localDW->NextOutput_h3vk[iU_4] = rt_nrand_Upu32_Yd_f_pw_snf
        (&localDW->RandSeed_c3st[iU_4]) * rtCP_RandomNumber_StdDev_azwi[iU_4];
    }

    /* End of Update for RandomNumber: '<S352>/Random Number' */

    /* Update for RateTransition: '<S342>/Rate Transition1' incorporates:
     *  Sum: '<S352>/Sum2'
     */
    for (i = 0; i < 3; i = i + 1) {
      localDW->RateTransition1_Buffer[i + (localDW->RateTransition1_ActiveBufIdx
        == 0) * 3] = localB->Sum2[i];
    }

    localDW->RateTransition1_ActiveBufIdx = (int8_T)
      (localDW->RateTransition1_ActiveBufIdx == 0);

    /* End of Update for RateTransition: '<S342>/Rate Transition1' */

    /* Update for RandomNumber: '<S342>/Random Number1' */
    for (iU_5 = 0; iU_5 < 3; iU_5 = iU_5 + 1) {
      localDW->NextOutput_kg2s[iU_5] = rt_nrand_Upu32_Yd_f_pw_snf
        (&localDW->RandSeed_adgi[iU_5]) * rtCP_RandomNumber1_StdDev[iU_5];
    }

    /* End of Update for RandomNumber: '<S342>/Random Number1' */

    /* Update for DiscreteFir: '<S350>/Discrete FIR Filter' incorporates:
     *  Reshape: '<S342>/Reshape3'
     */
    /* Update states */
    for (k_0 = 0; k_0 < 3; k_0 = k_0 + 1) {
      localDW->DiscreteFIRFilter_states_jj3r[k_0] = localB->Reshape3[k_0];
    }

    /* End of Update for DiscreteFir: '<S350>/Discrete FIR Filter' */

    /* Update for RateTransition: '<S342>/Rate Transition5' incorporates:
     *  DiscreteFir: '<S350>/Discrete FIR Filter'
     */
    for (i_0 = 0; i_0 < 3; i_0 = i_0 + 1) {
      localDW->RateTransition5_Buffer0[i_0] = localB->DiscreteFIRFilter[i_0];
    }

    /* End of Update for RateTransition: '<S342>/Rate Transition5' */

    /* Update for DiscreteFir: '<S349>/Discrete FIR Filter' incorporates:
     *  Sum: '<S342>/Sum2'
     */
    /* Update states */
    for (k_1 = 0; k_1 < 3; k_1 = k_1 + 1) {
      localDW->DiscreteFIRFilter_states_m0pu[k_1] = localB->Sum2_czfu[k_1];
    }

    /* End of Update for DiscreteFir: '<S349>/Discrete FIR Filter' */
  }

  /* Update for Integrator: '<S15>/pos_x' */
  localDW->pos_x_DWORK1 = false;

  /* Update for Integrator: '<S16>/pos_y' */
  localDW->pos_y_DWORK1 = false;
  if (rtmIsMajorTimeStep(RMT_FDM_RT_M)) {
    /* Update for RandomNumber: '<S317>/Random Number2' */
    for (iU_6 = 0; iU_6 < 3; iU_6 = iU_6 + 1) {
      localDW->NextOutput_d0v2[iU_6] = rt_nrand_Upu32_Yd_f_pw_snf
        (&localDW->RandSeed_bfrf[iU_6]);
    }

    /* End of Update for RandomNumber: '<S317>/Random Number2' */

    /* Update for RandomNumber: '<S315>/Random Number2' */
    for (iU_7 = 0; iU_7 < 3; iU_7 = iU_7 + 1) {
      localDW->NextOutput_oxco[iU_7] = rt_nrand_Upu32_Yd_f_pw_snf
        (&localDW->RandSeed_hwhk[iU_7]);
    }

    /* End of Update for RandomNumber: '<S315>/Random Number2' */

    /* Update for RandomNumber: '<S243>/Random Number2' */
    for (iU_8 = 0; iU_8 < 3; iU_8 = iU_8 + 1) {
      localDW->NextOutput_myry[iU_8] = rt_nrand_Upu32_Yd_f_pw_snf
        (&localDW->RandSeed_cfee[iU_8]);
    }

    /* End of Update for RandomNumber: '<S243>/Random Number2' */

    /* Update for RandomNumber: '<S244>/Random Number2' */
    for (iU_9 = 0; iU_9 < 3; iU_9 = iU_9 + 1) {
      localDW->NextOutput_psbc[iU_9] = rt_nrand_Upu32_Yd_f_pw_snf
        (&localDW->RandSeed_dfqp[iU_9]);
    }

    /* End of Update for RandomNumber: '<S244>/Random Number2' */

    /* Update for RandomNumber: '<S245>/Random Number2' */
    for (iU_a = 0; iU_a < 3; iU_a = iU_a + 1) {
      localDW->NextOutput_ps3h[iU_a] = rt_nrand_Upu32_Yd_f_pw_snf
        (&localDW->RandSeed_hhkq[iU_a]);
    }

    /* End of Update for RandomNumber: '<S245>/Random Number2' */

    /* Update for RandomNumber: '<S246>/Random Number2' */
    for (iU_b = 0; iU_b < 3; iU_b = iU_b + 1) {
      localDW->NextOutput_ivlt[iU_b] = rt_nrand_Upu32_Yd_f_pw_snf
        (&localDW->RandSeed_i5sw[iU_b]);
    }

    /* End of Update for RandomNumber: '<S246>/Random Number2' */

    /* Update for RandomNumber: '<S247>/Random Number2' */
    for (iU_c = 0; iU_c < 3; iU_c = iU_c + 1) {
      localDW->NextOutput_hejj[iU_c] = rt_nrand_Upu32_Yd_f_pw_snf
        (&localDW->RandSeed_bmmn[iU_c]);
    }

    /* End of Update for RandomNumber: '<S247>/Random Number2' */

    /* Update for RandomNumber: '<S248>/Random Number2' */
    for (iU_d = 0; iU_d < 3; iU_d = iU_d + 1) {
      localDW->NextOutput_nqkk[iU_d] = rt_nrand_Upu32_Yd_f_pw_snf
        (&localDW->RandSeed_gbxp[iU_d]);
    }

    /* End of Update for RandomNumber: '<S248>/Random Number2' */

    /* Update for RandomNumber: '<S249>/Random Number2' */
    for (iU_e = 0; iU_e < 3; iU_e = iU_e + 1) {
      localDW->NextOutput_op4z[iU_e] = rt_nrand_Upu32_Yd_f_pw_snf
        (&localDW->RandSeed_h5zc[iU_e]);
    }

    /* End of Update for RandomNumber: '<S249>/Random Number2' */

    /* Update for RandomNumber: '<S250>/Random Number2' */
    for (iU_f = 0; iU_f < 3; iU_f = iU_f + 1) {
      localDW->NextOutput_ejvr[iU_f] = rt_nrand_Upu32_Yd_f_pw_snf
        (&localDW->RandSeed_lduk[iU_f]);
    }

    /* End of Update for RandomNumber: '<S250>/Random Number2' */

    /* Update for RandomNumber: '<S390>/Random Number2' */
    for (iU_g = 0; iU_g < 3; iU_g = iU_g + 1) {
      localDW->NextOutput_klkk[iU_g] = rt_nrand_Upu32_Yd_f_pw_snf
        (&localDW->RandSeed_pu2v[iU_g]);
    }

    /* End of Update for RandomNumber: '<S390>/Random Number2' */
  }

  /* Update for RateTransition: '<S342>/Rate Transition' incorporates:
   *  DiscreteFir: '<S349>/Discrete FIR Filter'
   */
  if (rtmIsMajorTimeStep(RMT_FDM_RT_M) && rtmIsSampleHit(RMT_FDM_RT_M, 2)) {
    for (i_1 = 0; i_1 < 3; i_1 = i_1 + 1) {
      localDW->RateTransition_Buffer[i_1 + (localDW->RateTransition_ActiveBufIdx
        == 0) * 3] = localB->DiscreteFIRFilter_gsnn[i_1];
    }

    localDW->RateTransition_ActiveBufIdx = (int8_T)
      (localDW->RateTransition_ActiveBufIdx == 0);
  }

  /* End of Update for RateTransition: '<S342>/Rate Transition' */

  /* Update for Integrator: '<S333>/w_z_int_PRot_P_err_radDs' */
  localDW->w_z_int_PRot_P_err_radDs_DWORK1_mvtc = false;

  /* Update for Integrator: '<S341>/w_z_int_PRot_P_err_radDs' */
  localDW->w_z_int_PRot_P_err_radDs_DWORK1_ik1k = false;

  /* Update for Integrator: '<S325>/w_z_int_PRot_P_err_radDs' */
  localDW->w_z_int_PRot_P_err_radDs_DWORK1_bsyt = false;

  /* Update for Integrator: '<S258>/w_z_int_PRot_P_err_radDs' */
  localDW->w_z_int_PRot_P_err_radDs_DWORK1_f02p = false;

  /* Update for Integrator: '<S266>/w_z_int_PRot_P_err_radDs' */
  localDW->w_z_int_PRot_P_err_radDs_DWORK1_nx4h = false;

  /* Update for Integrator: '<S274>/w_z_int_PRot_P_err_radDs' */
  localDW->w_z_int_PRot_P_err_radDs_DWORK1_jzmo = false;

  /* Update for Integrator: '<S282>/w_z_int_PRot_P_err_radDs' */
  localDW->w_z_int_PRot_P_err_radDs_DWORK1_avwp = false;

  /* Update for Integrator: '<S290>/w_z_int_PRot_P_err_radDs' */
  localDW->w_z_int_PRot_P_err_radDs_DWORK1_disd = false;

  /* Update for Integrator: '<S298>/w_z_int_PRot_P_err_radDs' */
  localDW->w_z_int_PRot_P_err_radDs_DWORK1_dcuw = false;

  /* Update for Integrator: '<S306>/w_z_int_PRot_P_err_radDs' */
  localDW->w_z_int_PRot_P_err_radDs_DWORK1_fmga = false;

  /* Update for Integrator: '<S314>/w_z_int_PRot_P_err_radDs' */
  localDW->w_z_int_PRot_P_err_radDs_DWORK1_ncdx = false;

  /* Update for Integrator: '<S398>/w_z_int_PRot_P_err_radDs' */
  localDW->w_z_int_PRot_P_err_radDs_DWORK1_itla = false;

  /* Update for Integrator: '<S397>/w_z_int_PRot_P_err_radDs' */
  localDW->w_z_int_PRot_P_err_radDs_DWORK1_psoo = false;

  /* Update for Integrator: '<S313>/w_z_int_PRot_P_err_radDs' */
  localDW->w_z_int_PRot_P_err_radDs_DWORK1_f3vl = false;

  /* Update for Integrator: '<S305>/w_z_int_PRot_P_err_radDs' */
  localDW->w_z_int_PRot_P_err_radDs_DWORK1_iirx = false;

  /* Update for Integrator: '<S297>/w_z_int_PRot_P_err_radDs' */
  localDW->w_z_int_PRot_P_err_radDs_DWORK1_caav = false;

  /* Update for Integrator: '<S289>/w_z_int_PRot_P_err_radDs' */
  localDW->w_z_int_PRot_P_err_radDs_DWORK1_cogt = false;

  /* Update for Integrator: '<S281>/w_z_int_PRot_P_err_radDs' */
  localDW->w_z_int_PRot_P_err_radDs_DWORK1_jhud = false;

  /* Update for Integrator: '<S273>/w_z_int_PRot_P_err_radDs' */
  localDW->w_z_int_PRot_P_err_radDs_DWORK1_no0f = false;

  /* Update for Integrator: '<S265>/w_z_int_PRot_P_err_radDs' */
  localDW->w_z_int_PRot_P_err_radDs_DWORK1_da4c = false;

  /* Update for Integrator: '<S257>/w_z_int_PRot_P_err_radDs' */
  localDW->w_z_int_PRot_P_err_radDs_DWORK1_does = false;

  /* Update for Integrator: '<S324>/w_z_int_PRot_P_err_radDs' */
  localDW->w_z_int_PRot_P_err_radDs_DWORK1_mmow = false;

  /* Update for Integrator: '<S340>/w_z_int_PRot_P_err_radDs' */
  localDW->w_z_int_PRot_P_err_radDs_DWORK1_hg1y = false;

  /* Update for Integrator: '<S332>/w_z_int_PRot_P_err_radDs' */
  localDW->w_z_int_PRot_P_err_radDs_DWORK1_plxf = false;
}

/* Derivatives for referenced model: 'RMT_FDM_RT' */
void RMT_FDM_RT_Deriv(B_RMT_FDM_RT_caua_T *localB, X_RMT_FDM_RT_nymf_T *localX,
                      XDot_RMT_FDM_RT_n1mv_T *localXdot)
{
  /* local scratch DWork variables */
  int32_T ForEach_itr_gq2o;
  int32_T i;
  int32_T i_0;
  int32_T i_1;
  int32_T i_2;
  int32_T i_3;
  int32_T i_4;
  boolean_T lsat;
  boolean_T usat;

  /* Derivatives for Integrator: '<S12>/att_phi_rad' */
  localXdot->Phi_rad = localB->Product_ldwx;

  /* Derivatives for Integrator: '<S14>/att_theta_rad' */
  localXdot->Theta_rad = localB->Product_ciqr;

  /* Derivatives for Integrator: '<S13>/att_psi_rad' */
  localXdot->Psi_rad = localB->Product_nlow;

  /* Derivatives for Integrator: '<S21>/vel_x_K' */
  localXdot->u_K_R_E_B_mDs = localB->Product_oxzs;

  /* Derivatives for Integrator: '<S22>/vel_y_K' */
  localXdot->v_K_R_E_B_mDs = localB->Product_p0uf;

  /* Derivatives for Integrator: '<S23>/vel_w_K' */
  localXdot->w_K_R_E_B_mDs = localB->Product_neht;

  /* Derivatives for Integrator: '<S238>/w_z_int_PRot_P_err_radDs' incorporates:
   *  Product: '<S238>/Product'
   */
  for (i = 0; i < 3; i = i + 1) {
    localXdot->w_z_int_PRot_P_err_radDs[i] = localB->Product_jgrl[i];
  }

  /* End of Derivatives for Integrator: '<S238>/w_z_int_PRot_P_err_radDs' */

  /* Derivatives for Iterator SubSystem: '<S1>/Actuator_Ext_Reset' */
  for (ForEach_itr_gq2o = 0; ForEach_itr_gq2o < 8; ForEach_itr_gq2o =
       ForEach_itr_gq2o + 1) {
    /* Derivatives for Integrator: '<S5>/Integrator' */
    lsat = (localX->CoreSubsys[ForEach_itr_gq2o].w_act_radDs <= 0.0);
    usat = (localX->CoreSubsys[ForEach_itr_gq2o].w_act_radDs >= 2712.0);
    if (((!lsat) && (!usat)) || (lsat && (localB->CoreSubsys[ForEach_itr_gq2o].
          w_act_dot_radDs2 > 0.0)) || (usat && (localB->
          CoreSubsys[ForEach_itr_gq2o].w_act_dot_radDs2 < 0.0))) {
      localXdot->CoreSubsys[ForEach_itr_gq2o].w_act_radDs = localB->
        CoreSubsys[ForEach_itr_gq2o].w_act_dot_radDs2;
    } else {
      /* in saturation */
      localXdot->CoreSubsys[ForEach_itr_gq2o].w_act_radDs = 0.0;
    }

    /* End of Derivatives for Integrator: '<S5>/Integrator' */
  }

  /* End of Derivatives for SubSystem: '<S1>/Actuator_Ext_Reset' */

  /* Derivatives for Integrator: '<S18>/rot_x_K_IB_B_radDs' */
  localXdot->w_x_K_IB_B_radDs = localB->Product_den3;

  /* Derivatives for Integrator: '<S19>/rot_y_K_IB_B_radDs' */
  localXdot->w_y_K_IB_B_radDs = localB->Product_n25e;

  /* Derivatives for Integrator: '<S20>/rot_z_K_IB_B_radDs' */
  localXdot->w_z_K_IB_B_radDs = localB->Product_dcml;

  /* Derivatives for Integrator: '<S17>/pos_z' */
  localXdot->z_R_O_m = localB->Product_mhkc;

  /* Derivatives for Integrator: '<S237>/w_z_int_PRot_P_err_radDs' incorporates:
   *  Product: '<S237>/Product'
   */
  for (i_0 = 0; i_0 < 3; i_0 = i_0 + 1) {
    localXdot->w_z_int_PRot_P_err_radDs_iwjk[i_0] = localB->Product[i_0];
  }

  /* End of Derivatives for Integrator: '<S237>/w_z_int_PRot_P_err_radDs' */

  /* Derivatives for Integrator: '<S372>/w_z_int_PRot_P_err_radDs' incorporates:
   *  Product: '<S372>/Product'
   */
  for (i_1 = 0; i_1 < 3; i_1 = i_1 + 1) {
    localXdot->w_z_int_PRot_P_err_radDs_auhp[i_1] = localB->Product_dhil[i_1];
  }

  /* End of Derivatives for Integrator: '<S372>/w_z_int_PRot_P_err_radDs' */

  /* Derivatives for Integrator: '<S373>/w_z_int_PRot_P_err_radDs' incorporates:
   *  Product: '<S373>/Product'
   */
  for (i_2 = 0; i_2 < 3; i_2 = i_2 + 1) {
    localXdot->w_z_int_PRot_P_err_radDs_nmyl[i_2] = localB->Product_eh41[i_2];
  }

  /* End of Derivatives for Integrator: '<S373>/w_z_int_PRot_P_err_radDs' */

  /* Derivatives for Integrator: '<S387>/w_z_int_PRot_P_err_radDs' incorporates:
   *  Product: '<S387>/Product'
   */
  for (i_3 = 0; i_3 < 3; i_3 = i_3 + 1) {
    localXdot->w_z_int_PRot_P_err_radDs_fg2g[i_3] = localB->Product_f5uz[i_3];
  }

  /* End of Derivatives for Integrator: '<S387>/w_z_int_PRot_P_err_radDs' */

  /* Derivatives for Integrator: '<S388>/w_z_int_PRot_P_err_radDs' incorporates:
   *  Product: '<S388>/Product'
   */
  for (i_4 = 0; i_4 < 3; i_4 = i_4 + 1) {
    localXdot->w_z_int_PRot_P_err_radDs_babv[i_4] = localB->Product_a2ds[i_4];
  }

  /* End of Derivatives for Integrator: '<S388>/w_z_int_PRot_P_err_radDs' */

  /* Derivatives for Integrator: '<S15>/pos_x' */
  localXdot->x_R_O_m = localB->Product_etkr;

  /* Derivatives for Integrator: '<S16>/pos_y' */
  localXdot->y_R_O_m = localB->Product_hvg4;

  /* Derivatives for Integrator: '<S333>/w_z_int_PRot_P_err_radDs' */
  localXdot->w_z_int_PRot_P_err_radDs_cg5d = localB->Product_jcdq;

  /* Derivatives for Integrator: '<S341>/w_z_int_PRot_P_err_radDs' */
  localXdot->w_z_int_PRot_P_err_radDs_dftl = localB->Product_koc0;

  /* Derivatives for Integrator: '<S325>/w_z_int_PRot_P_err_radDs' */
  localXdot->w_z_int_PRot_P_err_radDs_jowp = localB->Product_eeeg;

  /* Derivatives for Integrator: '<S258>/w_z_int_PRot_P_err_radDs' */
  localXdot->w_z_int_PRot_P_err_radDs_baxu = localB->Product_h3kv;

  /* Derivatives for Integrator: '<S266>/w_z_int_PRot_P_err_radDs' */
  localXdot->w_z_int_PRot_P_err_radDs_cjc1 = localB->Product_esat;

  /* Derivatives for Integrator: '<S274>/w_z_int_PRot_P_err_radDs' */
  localXdot->w_z_int_PRot_P_err_radDs_aexu = localB->Product_jjey;

  /* Derivatives for Integrator: '<S282>/w_z_int_PRot_P_err_radDs' */
  localXdot->w_z_int_PRot_P_err_radDs_njv5 = localB->Product_o353;

  /* Derivatives for Integrator: '<S290>/w_z_int_PRot_P_err_radDs' */
  localXdot->w_z_int_PRot_P_err_radDs_adwj = localB->Product_hkbl;

  /* Derivatives for Integrator: '<S298>/w_z_int_PRot_P_err_radDs' */
  localXdot->w_z_int_PRot_P_err_radDs_l00j = localB->Product_fis5;

  /* Derivatives for Integrator: '<S306>/w_z_int_PRot_P_err_radDs' */
  localXdot->w_z_int_PRot_P_err_radDs_ir34 = localB->Product_hoxf;

  /* Derivatives for Integrator: '<S314>/w_z_int_PRot_P_err_radDs' */
  localXdot->w_z_int_PRot_P_err_radDs_kbfn = localB->Product_earu;

  /* Derivatives for Integrator: '<S398>/w_z_int_PRot_P_err_radDs' */
  localXdot->w_z_int_PRot_P_err_radDs_oqys = localB->Product_aaq4;

  /* Derivatives for Integrator: '<S397>/w_z_int_PRot_P_err_radDs' */
  localXdot->w_z_int_PRot_P_err_radDs_fldy = localB->Product_mmjp;

  /* Derivatives for Integrator: '<S313>/w_z_int_PRot_P_err_radDs' */
  localXdot->w_z_int_PRot_P_err_radDs_czdk = localB->Product_nb2v;

  /* Derivatives for Integrator: '<S305>/w_z_int_PRot_P_err_radDs' */
  localXdot->w_z_int_PRot_P_err_radDs_pct4 = localB->Product_a2bg;

  /* Derivatives for Integrator: '<S297>/w_z_int_PRot_P_err_radDs' */
  localXdot->w_z_int_PRot_P_err_radDs_oaeq = localB->Product_cgbz;

  /* Derivatives for Integrator: '<S289>/w_z_int_PRot_P_err_radDs' */
  localXdot->w_z_int_PRot_P_err_radDs_nhxo = localB->Product_butr;

  /* Derivatives for Integrator: '<S281>/w_z_int_PRot_P_err_radDs' */
  localXdot->w_z_int_PRot_P_err_radDs_l5ua = localB->Product_m1vo;

  /* Derivatives for Integrator: '<S273>/w_z_int_PRot_P_err_radDs' */
  localXdot->w_z_int_PRot_P_err_radDs_c3cm = localB->Product_nn4o;

  /* Derivatives for Integrator: '<S265>/w_z_int_PRot_P_err_radDs' */
  localXdot->w_z_int_PRot_P_err_radDs_j2wc = localB->Product_e45n;

  /* Derivatives for Integrator: '<S257>/w_z_int_PRot_P_err_radDs' */
  localXdot->w_z_int_PRot_P_err_radDs_puds = localB->Product_j1jn;

  /* Derivatives for Integrator: '<S324>/w_z_int_PRot_P_err_radDs' */
  localXdot->w_z_int_PRot_P_err_radDs_ons5 = localB->Product_hwmn;

  /* Derivatives for Integrator: '<S340>/w_z_int_PRot_P_err_radDs' */
  localXdot->w_z_int_PRot_P_err_radDs_a2pk = localB->Product_nmeo;

  /* Derivatives for Integrator: '<S332>/w_z_int_PRot_P_err_radDs' */
  localXdot->w_z_int_PRot_P_err_radDs_mh2t = localB->Product_f0j2;
}

/* Model initialize function */
void RMT_FDM_RT_initialize(const char_T **rt_errorStatus, boolean_T
  *rt_stopRequested, RTWSolverInfo *rt_solverInfo, const rtTimingBridge
  *timingBridge, int_T mdlref_TID0, int_T mdlref_TID1, int_T mdlref_TID2,
  RT_MODEL_RMT_FDM_RT_T *const RMT_FDM_RT_M, B_RMT_FDM_RT_caua_T *localB,
  DW_RMT_FDM_RT_fwu4_T *localDW, ZCE_RMT_FDM_RT_T *localZCE)
{
  /* Registration code */

  /* initialize real-time model */
  (void) memset((void *)RMT_FDM_RT_M, 0,
                sizeof(RT_MODEL_RMT_FDM_RT_T));

  /* setup the global timing engine */
  RMT_FDM_RT_M->Timing.mdlref_GlobalTID[0] = mdlref_TID0;
  RMT_FDM_RT_M->Timing.mdlref_GlobalTID[1] = mdlref_TID1;
  RMT_FDM_RT_M->Timing.mdlref_GlobalTID[2] = mdlref_TID2;
  RMT_FDM_RT_M->timingBridge = (timingBridge);

  /* initialize error status */
  rtmSetErrorStatusPointer(RMT_FDM_RT_M, rt_errorStatus);

  /* initialize stop requested flag */
  rtmSetStopRequestedPtr(RMT_FDM_RT_M, rt_stopRequested);

  /* initialize RTWSolverInfo */
  RMT_FDM_RT_M->solverInfo = (rt_solverInfo);

  /* Set the Timing fields to the appropriate data in the RTWSolverInfo */
  rtmSetSimTimeStepPointer(RMT_FDM_RT_M, rtsiGetSimTimeStepPtr
    (RMT_FDM_RT_M->solverInfo));
  RMT_FDM_RT_M->Timing.stepSize0 = (rtsiGetStepSize(RMT_FDM_RT_M->solverInfo));

  /* block I/O */
  (void) memset(((void *) localB), 0,
                sizeof(B_RMT_FDM_RT_caua_T));

  /* states (dwork) */
  (void) memset((void *)localDW, 0,
                sizeof(DW_RMT_FDM_RT_fwu4_T));
  localZCE->att_phi_rad_Reset_ZCE = UNINITIALIZED_ZCSIG;
  localZCE->att_theta_rad_Reset_ZCE = UNINITIALIZED_ZCSIG;
  localZCE->att_psi_rad_Reset_ZCE = UNINITIALIZED_ZCSIG;
  localZCE->vel_x_K_Reset_ZCE = UNINITIALIZED_ZCSIG;
  localZCE->vel_y_K_Reset_ZCE = UNINITIALIZED_ZCSIG;
  localZCE->vel_w_K_Reset_ZCE = UNINITIALIZED_ZCSIG;
  localZCE->w_z_int_PRot_P_err_radDs_Reset_ZCE = UNINITIALIZED_ZCSIG;
  localZCE->rot_x_K_IB_B_radDs_Reset_ZCE = UNINITIALIZED_ZCSIG;
  localZCE->rot_y_K_IB_B_radDs_Reset_ZCE = UNINITIALIZED_ZCSIG;
  localZCE->rot_z_K_IB_B_radDs_Reset_ZCE = UNINITIALIZED_ZCSIG;
  localZCE->pos_z_Reset_ZCE = UNINITIALIZED_ZCSIG;
  localZCE->w_z_int_PRot_P_err_radDs_Reset_ZCE_e11l = UNINITIALIZED_ZCSIG;
  localZCE->w_z_int_PRot_P_err_radDs_Reset_ZCE_c4n4 = UNINITIALIZED_ZCSIG;
  localZCE->w_z_int_PRot_P_err_radDs_Reset_ZCE_gyn1 = UNINITIALIZED_ZCSIG;
  localZCE->w_z_int_PRot_P_err_radDs_Reset_ZCE_om2w = UNINITIALIZED_ZCSIG;
  localZCE->w_z_int_PRot_P_err_radDs_Reset_ZCE_jte2 = UNINITIALIZED_ZCSIG;
  localZCE->pos_x_Reset_ZCE = UNINITIALIZED_ZCSIG;
  localZCE->pos_y_Reset_ZCE = UNINITIALIZED_ZCSIG;
  localZCE->w_z_int_PRot_P_err_radDs_Reset_ZCE_cpmd = UNINITIALIZED_ZCSIG;
  localZCE->w_z_int_PRot_P_err_radDs_Reset_ZCE_k4ow = UNINITIALIZED_ZCSIG;
  localZCE->w_z_int_PRot_P_err_radDs_Reset_ZCE_gvbs = UNINITIALIZED_ZCSIG;
  localZCE->w_z_int_PRot_P_err_radDs_Reset_ZCE_i5ww = UNINITIALIZED_ZCSIG;
  localZCE->w_z_int_PRot_P_err_radDs_Reset_ZCE_g2qz = UNINITIALIZED_ZCSIG;
  localZCE->w_z_int_PRot_P_err_radDs_Reset_ZCE_lcew = UNINITIALIZED_ZCSIG;
  localZCE->w_z_int_PRot_P_err_radDs_Reset_ZCE_aahy = UNINITIALIZED_ZCSIG;
  localZCE->w_z_int_PRot_P_err_radDs_Reset_ZCE_fh0g = UNINITIALIZED_ZCSIG;
  localZCE->w_z_int_PRot_P_err_radDs_Reset_ZCE_ly0m = UNINITIALIZED_ZCSIG;
  localZCE->w_z_int_PRot_P_err_radDs_Reset_ZCE_n0z5 = UNINITIALIZED_ZCSIG;
  localZCE->w_z_int_PRot_P_err_radDs_Reset_ZCE_fwzs = UNINITIALIZED_ZCSIG;
  localZCE->w_z_int_PRot_P_err_radDs_Reset_ZCE_epvd = UNINITIALIZED_ZCSIG;
  localZCE->w_z_int_PRot_P_err_radDs_Reset_ZCE_g1z1 = UNINITIALIZED_ZCSIG;
  localZCE->w_z_int_PRot_P_err_radDs_Reset_ZCE_ednt = UNINITIALIZED_ZCSIG;
  localZCE->w_z_int_PRot_P_err_radDs_Reset_ZCE_c1ao = UNINITIALIZED_ZCSIG;
  localZCE->w_z_int_PRot_P_err_radDs_Reset_ZCE_cc4d = UNINITIALIZED_ZCSIG;
  localZCE->w_z_int_PRot_P_err_radDs_Reset_ZCE_aq0k = UNINITIALIZED_ZCSIG;
  localZCE->w_z_int_PRot_P_err_radDs_Reset_ZCE_adnv = UNINITIALIZED_ZCSIG;
  localZCE->w_z_int_PRot_P_err_radDs_Reset_ZCE_napy = UNINITIALIZED_ZCSIG;
  localZCE->w_z_int_PRot_P_err_radDs_Reset_ZCE_cobq = UNINITIALIZED_ZCSIG;
  localZCE->w_z_int_PRot_P_err_radDs_Reset_ZCE_bwxm = UNINITIALIZED_ZCSIG;
  localZCE->w_z_int_PRot_P_err_radDs_Reset_ZCE_pbyv = UNINITIALIZED_ZCSIG;
  localZCE->w_z_int_PRot_P_err_radDs_Reset_ZCE_amgb = UNINITIALIZED_ZCSIG;
  localZCE->w_z_int_PRot_P_err_radDs_Reset_ZCE_ff4n = UNINITIALIZED_ZCSIG;
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
