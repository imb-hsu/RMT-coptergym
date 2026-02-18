/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: xrot_J8BGxLKW.c
 *
 * Code generated for Simulink model 'RMT_FDM_DLL_FrameWork_FCS_RT'.
 *
 * Model version                  : 11.34
 * Simulink Coder version         : 24.2 (R2024b) 21-Jun-2024
 * C/C++ source code generated on : Thu Dec  4 22:28:01 2025
 */

#include "rtwtypes.h"
#include "xrot_J8BGxLKW.h"

/* Function for MATLAB Function: '<S19>/nullspace' */
void xrot_J8BGxLKW(real_T x[100], int32_T ix0, int32_T iy0, real_T c, real_T s)
{
  real_T temp_tmp;
  real_T temp_tmp_0;
  int32_T ix;
  int32_T iy;
  int32_T k;
  ix = ix0;
  iy = iy0;
  for (k = 0; k < 10; k = k + 1) {
    temp_tmp = x[iy - 1];
    temp_tmp_0 = x[ix - 1];
    x[iy - 1] = c * temp_tmp - s * temp_tmp_0;
    x[ix - 1] = c * temp_tmp_0 + s * temp_tmp;
    iy = iy + 1;
    ix = ix + 1;
  }
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
