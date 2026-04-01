/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: RMT_FDM_DLL_FrameWork_FCS_RT_private.h
 *
 * Code generated for Simulink model 'RMT_FDM_DLL_FrameWork_FCS_RT'.
 *
 * Model version                  : 11.39
 * Simulink Coder version         : 24.2 (R2024b) 21-Jun-2024
 * C/C++ source code generated on : Mon Mar 30 13:54:53 2026
 *
 * Target selection: ert_shrlib.tlc
 * Embedded hardware selection: Intel->x86-64 (Windows64)
 * Emulation hardware selection:
 *    Differs from embedded hardware (MATLAB Host)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef RMT_FDM_DLL_FrameWork_FCS_RT_private_h_
#define RMT_FDM_DLL_FrameWork_FCS_RT_private_h_
#include "rtwtypes.h"
#include "model_reference_types.h"
#include "zero_crossing_types.h"
#include "RMT_FDM_DLL_FrameWork_FCS_RT_types.h"
#include "rtw_continuous.h"
#include "rtw_solver.h"

/* Private macros used by the generated code to access rtModel */
#ifndef rtmSetFirstInitCond
#define rtmSetFirstInitCond(rtm, val)  ((rtm)->Timing.firstInitCondFlag = (val))
#endif

#ifndef rtmIsFirstInitCond
#define rtmIsFirstInitCond(rtm)        ((rtm)->Timing.firstInitCondFlag)
#endif

#ifndef rtmIsMajorTimeStep
#define rtmIsMajorTimeStep(rtm)        (((rtm)->Timing.simTimeStep) == MAJOR_TIME_STEP)
#endif

#ifndef rtmIsMinorTimeStep
#define rtmIsMinorTimeStep(rtm)        (((rtm)->Timing.simTimeStep) == MINOR_TIME_STEP)
#endif

#ifndef rtmSetTPtr
#define rtmSetTPtr(rtm, val)           ((rtm)->Timing.t = (val))
#endif

#if !defined(rt_VALIDATE_MEMORY)
#define rt_VALIDATE_MEMORY(S, ptr)     if(!(ptr)) {\
 rtmSetErrorStatus(RMT_FDM_DLL_FrameWork_FCS_RT_M, RT_MEMORY_ALLOCATION_ERROR);\
 }
#endif

#if !defined(rt_FREE)
#if !defined(_WIN32)
#define rt_FREE(ptr)                   if((ptr) != (NULL)) {\
 free((ptr));\
 (ptr) = (NULL);\
 }
#else

/* Visual and other windows compilers declare free without const */
#define rt_FREE(ptr)                   if((ptr) != (NULL)) {\
 free((void *)(ptr));\
 (ptr) = (NULL);\
 }
#endif
#endif

extern const real_T rtCP_pooled_raz31ZrIdy7n[60];
extern const real_T rtCP_pooled_Cz3Vgwc5I3f1[10];
extern const real_T rtCP_pooled_bIDTE93hldEm[10];
extern const real_T rtCP_pooled_dCengxmYRl69[40];
extern const real_T rtCP_pooled_VJqELOq8aki6;

#define rtCP_Constant1_Value_brmz      rtCP_pooled_raz31ZrIdy7n  /* Expression: B_nu
                                                                  * Referenced by: '<S17>/Constant1' (Parameter: Value)
                                                                  */
#define rtCP_Constant2_Value           rtCP_pooled_Cz3Vgwc5I3f1  /* Expression: fcs_du_min
                                                                  * Referenced by: '<S17>/Constant2' (Parameter: Value)
                                                                  */
#define rtCP_Constant3_Value           rtCP_pooled_bIDTE93hldEm  /* Expression: fcs_du_max
                                                                  * Referenced by: '<S17>/Constant3' (Parameter: Value)
                                                                  */
#define rtCP_Constant4_Value           rtCP_pooled_bIDTE93hldEm  /* Expression: fcs_du_max
                                                                  * Referenced by: '<S17>/Constant4' (Parameter: Value)
                                                                  */
#define rtCP_Constant5_Value           rtCP_pooled_Cz3Vgwc5I3f1  /* Expression: fcs_du_min
                                                                  * Referenced by: '<S17>/Constant5' (Parameter: Value)
                                                                  */
#define rtCP_Constant6_Value           rtCP_pooled_dCengxmYRl69  /* Expression: B_c(1:4,:)
                                                                  * Referenced by: '<S17>/Constant6' (Parameter: Value)
                                                                  */
#define rtCP_Saturation_UpperSat       rtCP_pooled_bIDTE93hldEm  /* Expression: fcs_du_max
                                                                  * Referenced by: '<S17>/Saturation' (Parameter: UpperLimit)
                                                                  */
#define rtCP_Saturation_LowerSat       rtCP_pooled_Cz3Vgwc5I3f1  /* Expression: fcs_du_min
                                                                  * Referenced by: '<S17>/Saturation' (Parameter: LowerLimit)
                                                                  */
#define rtCP_Constant_Value_omib       rtCP_pooled_VJqELOq8aki6  /* Expression: External_Inputs.Wind.Rotation.w_x_radDs
                                                                  * Referenced by: '<S4>/Constant' (Parameter: Value)
                                                                  */
#define rtCP_Constant1_Value_p5to      rtCP_pooled_VJqELOq8aki6  /* Expression: External_Inputs.Wind.Rotation.w_y_radDs
                                                                  * Referenced by: '<S4>/Constant1' (Parameter: Value)
                                                                  */
#define rtCP_Constant2_Value_nrpy      rtCP_pooled_VJqELOq8aki6  /* Expression: External_Inputs.Wind.Rotation.w_z_radDs
                                                                  * Referenced by: '<S4>/Constant2' (Parameter: Value)
                                                                  */
#define rtCP_Constant3_Value_je5h      rtCP_pooled_VJqELOq8aki6  /* Expression: External_Inputs.Navigation_Frame.psi0_rad
                                                                  * Referenced by: '<S4>/Constant3' (Parameter: Value)
                                                                  */
#define rtCP_Constant6_Value_pzmj      rtCP_pooled_VJqELOq8aki6  /* Expression: External_Inputs.Wind.Velocity.u_W_0_mDs
                                                                  * Referenced by: '<S4>/Constant6' (Parameter: Value)
                                                                  */
#define rtCP_Constant7_Value_daeb      rtCP_pooled_VJqELOq8aki6  /* Expression: External_Inputs.Wind.Velocity.v_W_0_mDs
                                                                  * Referenced by: '<S4>/Constant7' (Parameter: Value)
                                                                  */
#define rtCP_Constant8_Value           rtCP_pooled_VJqELOq8aki6  /* Expression: External_Inputs.Wind.Velocity.w_W_0_mDs
                                                                  * Referenced by: '<S4>/Constant8' (Parameter: Value)
                                                                  */

/* private model entry point functions */
extern void RMT_FDM_DLL_FrameWork_FCS_RT_derivatives
  (RT_MODEL_RMT_FDM_DLL_FrameWork_FCS_RT_T *const RMT_FDM_DLL_FrameWork_FCS_RT_M);

#endif                             /* RMT_FDM_DLL_FrameWork_FCS_RT_private_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
