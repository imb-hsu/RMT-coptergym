/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: eml_find_Ejmjtket.c
 *
 * Code generated for Simulink model 'RMT_FDM_DLL_FrameWork_FCS_RT'.
 *
 * Model version                  : 11.34
 * Simulink Coder version         : 24.2 (R2024b) 21-Jun-2024
 * C/C++ source code generated on : Thu Dec  4 22:28:01 2025
 */

#include "rtwtypes.h"
#include "eml_find_Ejmjtket.h"
#include <string.h>

/* Function for MATLAB Function: '<S17>/Scale_NST_Solution' */
void eml_find_Ejmjtket(const boolean_T x[10], int32_T i_data[], int32_T *i_size)
{
  int32_T i_data_0[10];
  int32_T b;
  int32_T b_ii;
  int32_T idx;
  boolean_T exitg1;
  idx = 0;
  b_ii = 0;
  exitg1 = false;
  while ((exitg1 == false) && (b_ii < 10)) {
    if (x[(b_ii + 1) - 1]) {
      idx = idx + 1;
      i_data[idx - 1] = b_ii + 1;
      if (idx >= 10) {
        exitg1 = true;
      } else {
        b_ii = b_ii + 1;
      }
    } else {
      b_ii = b_ii + 1;
    }
  }

  if (1 > idx) {
    b = 0;
  } else {
    b = idx;
  }

  if (0 <= ((b - 1) + 1) - 1) {
    memcpy(&i_data_0[0], &i_data[0], (uint32_T)((((b - 1) + 1) - 1) + 1) *
           sizeof(int32_T));
  }

  *i_size = (b - 1) + 1;
  if (0 <= ((b - 1) + 1) - 1) {
    memcpy(&i_data[0], &i_data_0[0], (uint32_T)((((b - 1) + 1) - 1) + 1) *
           sizeof(int32_T));
  }
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
