/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: xnrm2_TWLjRXVi.c
 *
 * Code generated for Simulink model 'RMT_FDM_DLL_FrameWork_FCS_RT'.
 *
 * Model version                  : 11.41
 * Simulink Coder version         : 24.2 (R2024b) 21-Jun-2024
 * C/C++ source code generated on : Mon May 11 09:57:18 2026
 */

#include "rtwtypes.h"
#include "xnrm2_TWLjRXVi.h"
#include <math.h>
#include "rt_nonfinite.h"

/* Function for MATLAB Function: '<S17>/Redistribution' */
real_T xnrm2_TWLjRXVi(int32_T n, const real_T x[60], int32_T ix0)
{
  real_T absxk;
  real_T scale;
  real_T t;
  real_T y;
  int32_T b_k;
  int32_T exitg1;
  int32_T k;
  int32_T kend;
  y = 0.0;
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
  if (rtIsNaN(y)) {
    b_k = ix0;
    do {
      exitg1 = 0;
      if (b_k <= kend) {
        if (rtIsNaN(x[b_k - 1])) {
          exitg1 = 1;
        } else {
          b_k = b_k + 1;
        }
      } else {
        y = (rtInf);
        exitg1 = 1;
      }
    } while (exitg1 == 0);
  }

  return y;
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
