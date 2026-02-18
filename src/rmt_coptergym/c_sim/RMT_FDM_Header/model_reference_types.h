/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: model_reference_types.h
 *
 * Code generated for Simulink model 'RMT_FDM_RT'.
 *
 * Model version                  : 11.18
 * Simulink Coder version         : 24.2 (R2024b) 21-Jun-2024
 * C/C++ source code generated on : Thu Dec  4 22:27:28 2025
 */

#ifndef MODEL_REFERENCE_TYPES_H
#define MODEL_REFERENCE_TYPES_H
#include "rtwtypes.h"
#ifndef MODEL_REFERENCE_TYPES
#define MODEL_REFERENCE_TYPES

/*===========================================================================*
 * Model reference type definitions                                          *
 *===========================================================================*/
/*
 * This structure is used by model reference to
 * communicate timing information through the hierarchy.
 */
typedef struct _rtTimingBridge_tag rtTimingBridge;
struct _rtTimingBridge_tag {
  uint32_T nTasks;
  uint32_T** clockTick;
  uint32_T** clockTickH;
  uint32_T* taskCounter;
  real_T** taskTime;
  boolean_T** rateTransition;
  boolean_T *firstInitCond;
};

/*
 * This structure is used by model reference to
 * communicate variable discrete rate timing information through the hierarchy.
 */
typedef struct _rtCtrlRateMdlRefTiming_tag rtCtrlRateMdlRefTiming;
struct _rtCtrlRateMdlRefTiming_tag {
  uint32_T firstCtrlRateTID;
  uint32_T* numTicksToNextHitForCtrlRate;
};

#endif                                 /* MODEL_REFERENCE_TYPES */
#endif                                 /* MODEL_REFERENCE_TYPES_H */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
