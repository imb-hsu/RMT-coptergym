/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: xzlangeM_iSKRL0D5.c
 *
 * Code generated for Simulink model 'RMT_FDM_DLL_FrameWork_FCS_RT'.
 *
 * Model version                  : 11.39
 * Simulink Coder version         : 24.2 (R2024b) 21-Jun-2024
 * C/C++ source code generated on : Mon Mar 30 13:54:53 2026
 */

#include "rtwtypes.h"
#include "xzlangeM_iSKRL0D5.h"
#include <math.h>
#include "rt_nonfinite.h"

/* Function for MATLAB Function: '<S19>/nullspace' */
real_T xzlangeM_iSKRL0D5(const real_T x[60])
{
  real_T absxk;
  real_T y;
  int32_T k;
  boolean_T exitg1;
  y = 0.0;
  k = 0;
  exitg1 = false;
  while ((exitg1 == false) && (k < 60)) {
    absxk = fabs(x[(k + 1) - 1]);
    if (rtIsNaN(absxk)) {
      y = (rtNaN);
      exitg1 = true;
    } else {
      if (absxk > y) {
        y = absxk;
      }

      k = k + 1;
    }
  }

  return y;
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
