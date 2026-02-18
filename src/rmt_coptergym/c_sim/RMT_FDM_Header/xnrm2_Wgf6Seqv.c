/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: xnrm2_Wgf6Seqv.c
 *
 * Code generated for Simulink model 'RMT_FDM_DLL_FrameWork_FCS_RT'.
 *
 * Model version                  : 11.34
 * Simulink Coder version         : 24.2 (R2024b) 21-Jun-2024
 * C/C++ source code generated on : Thu Dec  4 22:28:01 2025
 */

#include "rtwtypes.h"
#include "xnrm2_Wgf6Seqv.h"
#include <math.h>

/* Function for MATLAB Function: '<S19>/nullspace' */
real_T xnrm2_Wgf6Seqv(int32_T n, const real_T x[60], int32_T ix0)
{
  real_T absxk;
  real_T scale;
  real_T t;
  real_T y;
  int32_T k;
  int32_T kend;
  y = 0.0;
  if (n == 1) {
    y = fabs(x[ix0 - 1]);
  } else {
    scale = 3.3121686421112381E-170;
    kend = ix0 + (n - 1);
    for (k = ix0; k <= kend; k = k + 1) {
      absxk = fabs(x[k - 1]);
      if (absxk > scale) {
        t = scale / absxk;
        y = 1.0 + y * t * t;
        scale = absxk;
      } else {
        t = absxk / scale;
        y = y + t * t;
      }
    }

    y = scale * sqrt(y);
  }

  return y;
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
