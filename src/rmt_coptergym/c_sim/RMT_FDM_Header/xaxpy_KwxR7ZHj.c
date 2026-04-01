/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: xaxpy_KwxR7ZHj.c
 *
 * Code generated for Simulink model 'RMT_FDM_DLL_FrameWork_FCS_RT'.
 *
 * Model version                  : 11.39
 * Simulink Coder version         : 24.2 (R2024b) 21-Jun-2024
 * C/C++ source code generated on : Mon Mar 30 13:54:53 2026
 */

#include "rtwtypes.h"
#include "xaxpy_KwxR7ZHj.h"

/* Function for MATLAB Function: '<S19>/nullspace' */
void xaxpy_KwxR7ZHj(int32_T n, real_T a, const real_T x_data[], int32_T ix0,
                    real_T y[10], int32_T iy0)
{
  int32_T b;
  int32_T ix;
  int32_T iy;
  int32_T k;
  if (!(a == 0.0)) {
    ix = ix0 - 1;
    iy = iy0 - 1;
    b = n - 1;
    for (k = 0; k <= b; k = k + 1) {
      y[(iy + 1) - 1] = y[(iy + 1) - 1] + a * x_data[(ix + 1) - 1];
      ix = ix + 1;
      iy = iy + 1;
    }
  }
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
