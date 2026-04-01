/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: xdotc_yqR0GheY.c
 *
 * Code generated for Simulink model 'RMT_FDM_DLL_FrameWork_FCS_RT'.
 *
 * Model version                  : 11.39
 * Simulink Coder version         : 24.2 (R2024b) 21-Jun-2024
 * C/C++ source code generated on : Mon Mar 30 13:54:53 2026
 */

#include "rtwtypes.h"
#include "xdotc_yqR0GheY.h"

/* Function for MATLAB Function: '<S19>/nullspace' */
real_T xdotc_yqR0GheY(int32_T n, const real_T x[100], int32_T ix0, const real_T
                      y[100], int32_T iy0)
{
  real_T d;
  int32_T b;
  int32_T ix;
  int32_T iy;
  int32_T k;
  ix = ix0;
  iy = iy0;
  d = 0.0;
  b = (uint8_T)n;
  for (k = 0; k < b; k = k + 1) {
    d = d + x[ix - 1] * y[iy - 1];
    ix = ix + 1;
    iy = iy + 1;
  }

  return d;
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
