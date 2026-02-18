/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: xswap_GLv9Ouan.c
 *
 * Code generated for Simulink model 'RMT_FDM_DLL_FrameWork_FCS_RT'.
 *
 * Model version                  : 11.34
 * Simulink Coder version         : 24.2 (R2024b) 21-Jun-2024
 * C/C++ source code generated on : Thu Dec  4 22:28:01 2025
 */

#include "rtwtypes.h"
#include "xswap_GLv9Ouan.h"

/* Function for MATLAB Function: '<S17>/Redistribution' */
void xswap_GLv9Ouan(real_T x[60], int32_T ix0, int32_T iy0)
{
  real_T temp;
  int32_T ix;
  int32_T iy;
  int32_T k;
  ix = ix0;
  iy = iy0;
  for (k = 0; k < 10; k = k + 1) {
    temp = x[ix - 1];
    x[ix - 1] = x[iy - 1];
    x[iy - 1] = temp;
    ix = ix + 1;
    iy = iy + 1;
  }
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
