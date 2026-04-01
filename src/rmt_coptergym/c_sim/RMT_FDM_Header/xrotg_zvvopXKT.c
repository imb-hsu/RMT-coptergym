/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: xrotg_zvvopXKT.c
 *
 * Code generated for Simulink model 'RMT_FDM_DLL_FrameWork_FCS_RT'.
 *
 * Model version                  : 11.39
 * Simulink Coder version         : 24.2 (R2024b) 21-Jun-2024
 * C/C++ source code generated on : Mon Mar 30 13:54:53 2026
 */

#include "rtwtypes.h"
#include "xrotg_zvvopXKT.h"
#include <math.h>

/* Function for MATLAB Function: '<S19>/nullspace' */
void xrotg_zvvopXKT(real_T *a, real_T *b, real_T *c, real_T *s)
{
  real_T absa;
  real_T absb;
  real_T ads;
  real_T b_c;
  real_T b_s;
  real_T bds;
  real_T r;
  real_T roe;
  real_T scale;
  roe = *b;
  absa = fabs(*a);
  absb = fabs(*b);
  if (absa > absb) {
    roe = *a;
  }

  scale = absa + absb;
  if (scale == 0.0) {
    b_s = 0.0;
    b_c = 1.0;
    *a = 0.0;
    *b = 0.0;
  } else {
    ads = absa / scale;
    bds = absb / scale;
    r = scale * sqrt(ads * ads + bds * bds);
    if (roe < 0.0) {
      r = -r;
    }

    b_c = *a / r;
    b_s = *b / r;
    if (absa > absb) {
      *b = b_s;
    } else if (b_c != 0.0) {
      *b = 1.0 / b_c;
    } else {
      *b = 1.0;
    }

    *a = r;
  }

  *c = b_c;
  *s = b_s;
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
