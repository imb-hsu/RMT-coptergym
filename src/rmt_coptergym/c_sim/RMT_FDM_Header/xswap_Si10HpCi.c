/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: xswap_Si10HpCi.c
 *
 * Code generated for Simulink model 'RMT_FDM_DLL_FrameWork_FCS_RT'.
 *
 * Model version                  : 11.39
 * Simulink Coder version         : 24.2 (R2024b) 21-Jun-2024
 * C/C++ source code generated on : Mon Mar 30 13:54:53 2026
 */

#include "rtwtypes.h"
#include "xswap_Si10HpCi.h"

/* Function for MATLAB Function: '<S19>/Pseudoinverse' */
void xswap_Si10HpCi(real_T x[16], int32_T ix0, int32_T iy0)
{
  real_T temp;
  int32_T ix;
  int32_T iy;
  int32_T k;
  ix = ix0;
  iy = iy0;
  for (k = 0; k < 4; k = k + 1) {
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
