/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: xzlascl_ze48YLp0.c
 *
 * Code generated for Simulink model 'RMT_FDM_DLL_FrameWork_FCS_RT'.
 *
 * Model version                  : 11.34
 * Simulink Coder version         : 24.2 (R2024b) 21-Jun-2024
 * C/C++ source code generated on : Thu Dec  4 22:28:01 2025
 */

#include "rtwtypes.h"
#include "xzlascl_ze48YLp0.h"
#include <math.h>

/* Function for MATLAB Function: '<S19>/Pseudoinverse' */
void xzlascl_ze48YLp0(real_T cfrom, real_T cto, real_T A[16])
{
  real_T cfrom1;
  real_T cfromc;
  real_T cto1;
  real_T ctoc;
  real_T mul;
  int32_T b_i;
  int32_T j;
  int32_T offset;
  int32_T tmp;
  boolean_T notdone;
  cfromc = cfrom;
  ctoc = cto;
  notdone = true;
  while (notdone) {
    cfrom1 = cfromc * 2.0041683600089728E-292;
    cto1 = ctoc / 4.9896007738368E+291;
    if ((fabs(cfrom1) > fabs(ctoc)) && (ctoc != 0.0)) {
      mul = 2.0041683600089728E-292;
      notdone = true;
      cfromc = cfrom1;
    } else if (fabs(cto1) > fabs(cfromc)) {
      mul = 4.9896007738368E+291;
      notdone = true;
      ctoc = cto1;
    } else {
      mul = ctoc / cfromc;
      notdone = false;
    }

    for (j = 0; j < 4; j = j + 1) {
      offset = ((((j + 1) - 1) << 2) + 1) - 1;
      for (b_i = 0; b_i < 4; b_i = b_i + 1) {
        tmp = (offset + (b_i + 1)) - 1;
        A[tmp] = A[tmp] * mul;
      }
    }
  }
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
