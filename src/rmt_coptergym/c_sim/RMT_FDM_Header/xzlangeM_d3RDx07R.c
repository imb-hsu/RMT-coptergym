/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: xzlangeM_d3RDx07R.c
 *
 * Code generated for Simulink model 'RMT_FDM_DLL_FrameWork_FCS_RT'.
 *
 * Model version                  : 11.34
 * Simulink Coder version         : 24.2 (R2024b) 21-Jun-2024
 * C/C++ source code generated on : Thu Dec  4 22:28:01 2025
 */

#include "rtwtypes.h"
#include "xzlangeM_d3RDx07R.h"
#include <math.h>
#include "rt_nonfinite.h"

/* Function for MATLAB Function: '<S19>/nullspace' */
real_T xzlangeM_d3RDx07R(const real_T x_data[], const int32_T x_size[2])
{
  real_T absxk;
  real_T y;
  int32_T b;
  int32_T k;
  boolean_T exitg1;
  y = 0.0;
  b = (int32_T)(real_T)(10 * x_size[1]);
  k = 0;
  exitg1 = false;
  while ((exitg1 == false) && (k <= b - 1)) {
    absxk = fabs(x_data[(k + 1) - 1]);
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
