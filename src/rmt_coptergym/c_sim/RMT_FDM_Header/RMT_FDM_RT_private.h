/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: RMT_FDM_RT_private.h
 *
 * Code generated for Simulink model 'RMT_FDM_RT'.
 *
 * Model version                  : 11.18
 * Simulink Coder version         : 24.2 (R2024b) 21-Jun-2024
 * C/C++ source code generated on : Mon Mar 30 13:53:24 2026
 *
 * Target selection: ert_shrlib.tlc
 * Embedded hardware selection: Intel->x86-64 (Windows64)
 * Emulation hardware selection:
 *    Differs from embedded hardware (MATLAB Host)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef RMT_FDM_RT_private_h_
#define RMT_FDM_RT_private_h_
#include "rtwtypes.h"
#include "model_reference_types.h"
#include "zero_crossing_types.h"
#include "RMT_FDM_RT_types.h"
#include "RMT_FDM_RT.h"
#include "rtw_continuous.h"
#include "rtw_solver.h"

/* Private macros used by the generated code to access rtModel */
#ifndef rtmIsFirstInitCond
#define rtmIsFirstInitCond(rtm)        ( *((rtm)->timingBridge->firstInitCond) )
#endif

#ifndef rtmIsMajorTimeStep
#define rtmIsMajorTimeStep(rtm)        ((rtmGetSimTimeStep((rtm))) == MAJOR_TIME_STEP)
#endif

#ifndef rtmIsMinorTimeStep
#define rtmIsMinorTimeStep(rtm)        ((rtmGetSimTimeStep((rtm))) == MINOR_TIME_STEP)
#endif

#ifndef rtmIsSampleHit
#define rtmIsSampleHit(rtm, sti)       ((rtm)->timingBridge->taskCounter[(rtm)->Timing.mdlref_GlobalTID[sti]] == 0)
#endif

/* Macros for accessing real-time model data structure */
#ifndef rtmGetClockTick0
#define rtmGetClockTick0(rtm)          ( *(((rtm)->timingBridge->clockTick[(rtm)->Timing.mdlref_GlobalTID[0]])) )
#endif

#ifndef rtmGetClockTick1
#define rtmGetClockTick1(rtm)          ( *(((rtm)->timingBridge->clockTick[(rtm)->Timing.mdlref_GlobalTID[1]])) )
#endif

#ifndef rtmGetClockTick2
#define rtmGetClockTick2(rtm)          ( *(((rtm)->timingBridge->clockTick[(rtm)->Timing.mdlref_GlobalTID[2]])) )
#endif

#ifndef rtmGetClockTickH0
#define rtmGetClockTickH0(rtm)         ( *((rtm)->timingBridge->clockTickH[(rtm)->Timing.mdlref_GlobalTID[0]]) )
#endif

#ifndef rtmGetClockTickH1
#define rtmGetClockTickH1(rtm)         ( *((rtm)->timingBridge->clockTickH[(rtm)->Timing.mdlref_GlobalTID[1]]) )
#endif

#ifndef rtmGetClockTickH2
#define rtmGetClockTickH2(rtm)         ( *((rtm)->timingBridge->clockTickH[(rtm)->Timing.mdlref_GlobalTID[2]]) )
#endif

#ifndef rtmGetErrorStatus
#define rtmGetErrorStatus(rtm)         (*((rtm)->errorStatus))
#endif

#ifndef rtmSetErrorStatus
#define rtmSetErrorStatus(rtm, val)    (*((rtm)->errorStatus) = (val))
#endif

#ifndef rtmGetErrorStatusPointer
#define rtmGetErrorStatusPointer(rtm)  (rtm)->errorStatus
#endif

#ifndef rtmSetErrorStatusPointer
#define rtmSetErrorStatusPointer(rtm, val) ((rtm)->errorStatus = (val))
#endif

#ifndef rtmGetSimTimeStep
#define rtmGetSimTimeStep(rtm)         (*((rtm)->Timing.simTimeStep))
#endif

#ifndef rtmGetSimTimeStepPointer
#define rtmGetSimTimeStepPointer(rtm)  (rtm)->Timing.simTimeStep
#endif

#ifndef rtmSetSimTimeStepPointer
#define rtmSetSimTimeStepPointer(rtm, val) ((rtm)->Timing.simTimeStep = (val))
#endif

#ifndef rtmGetStopRequested
#define rtmGetStopRequested(rtm)       (*((rtm)->Timing.stopRequestedFlag))
#endif

#ifndef rtmSetStopRequested
#define rtmSetStopRequested(rtm, val)  (*((rtm)->Timing.stopRequestedFlag) = (val))
#endif

#ifndef rtmGetStopRequestedPtr
#define rtmGetStopRequestedPtr(rtm)    ((rtm)->Timing.stopRequestedFlag)
#endif

#ifndef rtmSetStopRequestedPtr
#define rtmSetStopRequestedPtr(rtm, val) ((rtm)->Timing.stopRequestedFlag = (val))
#endif

#ifndef rtmGetT
#define rtmGetT(rtm)                   (*((rtm)->timingBridge->taskTime[0]))
#endif

#ifndef rtmGetTStart
#define rtmGetTStart(rtm)              ((rtm)->Timing.tStart)
#endif

/* Constant parameters (default storage) */
typedef struct {
  struct_qXZFuXHL3JOSsWXmuRsKx pooled1;/* Pooled Parameter (Mixed Expressions)
                                        * Referenced by:
                                        *   '<S33>/Propeller_RMT' (Parameter: System mask parameter #0)
                                        *   '<S33>/Propeller_RMT' (Parameter: System mask parameter #0)
                                        *   '<S33>/Propeller_RMT' (Parameter: System mask parameter #0)
                                        *   '<S33>/Propeller_RMT' (Parameter: System mask parameter #0)
                                        */
} ConstP_RMT_FDM_RT_T;

extern const real_T rtCP_pooled_rSWdpyOYIg74[286];
extern const real_T rtCP_pooled_6MPzFCqFsv9f[11];
extern const real_T rtCP_pooled_RRYL5L18wNzV[26];
extern const real_T rtCP_pooled_77gF061kHzP6[286];
extern const real_T rtCP_pooled_NApuNazfrZXQ[11];
extern const real_T rtCP_pooled_Gn7U3gRTnp21[26];
extern const real_T rtCP_pooled_2V4qcztE4WKe[9];
extern const real_T rtCP_pooled_o7MB5naIXTAF[3];
extern const real_T rtCP_pooled_Jd4cl5NFewNp[3];
extern const real_T rtCP_pooled_UbozXULFB58v[3];
extern const real_T rtCP_pooled_YxVQUVpyy1ZW[3];
extern const real_T rtCP_pooled_QamkoadBrzvw[3];
extern const real_T rtCP_pooled_wvqoDCxkDmXt[9];
extern const real_T rtCP_pooled_s9j6OaAnioFp[3];
extern const real_T rtCP_pooled_0fOaedqqRxfM[3];
extern const real_T rtCP_pooled_YnZRlcPCkOxc[3];
extern const real_T rtCP_pooled_zCwzTOhTFZVI[3];
extern const real_T rtCP_pooled_Qj4DzRzeKvfC[9];
extern const real_T rtCP_pooled_sTUNfpUIPpSd[3];
extern const real_T rtCP_pooled_hw6GxjthfW52[9];
extern const real_T rtCP_pooled_VvcENMMe7tfY[3];
extern const real_T rtCP_pooled_0RyAaVW2z3MA[3];
extern const real_T rtCP_pooled_s0HvNqDjfitH[3];
extern const real_T rtCP_pooled_UQ2TRgUJlJ1B[3];
extern const real_T rtCP_pooled_Cjw806MXsseM[3];
extern const real_T rtCP_pooled_babEPG1srVnA[3];
extern const real_T rtCP_pooled_UsOdXfZgGtoj[3];
extern const real_T rtCP_pooled_PNSnPc6Of7T3[3];
extern const real_T rtCP_pooled_obE6V7ylra60[3];
extern const uint32_T rtCP_pooled_L0BJOqhq6uSa[2];

#define rtCP_uDLookupTable_tableData   rtCP_pooled_rSWdpyOYIg74  /* Expression: Lookup.Cz
                                                                  * Referenced by: '<S137>/2-D Lookup Table' (Parameter: Table)
                                                                  */
#define rtCP_uDLookupTable_bp01Data    rtCP_pooled_6MPzFCqFsv9f  /* Expression: Lookup.Vel_brPts_mDs
                                                                  * Referenced by: '<S137>/2-D Lookup Table' (Parameter: BreakpointsForDimension1)
                                                                  */
#define rtCP_uDLookupTable_bp02Data    rtCP_pooled_RRYL5L18wNzV  /* Expression: Lookup.omega_brPts_radDs
                                                                  * Referenced by: '<S137>/2-D Lookup Table' (Parameter: BreakpointsForDimension2)
                                                                  */
#define rtCP_uDLookupTable_tableData_cgkc rtCP_pooled_77gF061kHzP6/* Expression: Lookup.Cn
                                                                   * Referenced by: '<S159>/2-D Lookup Table' (Parameter: Table)
                                                                   */
#define rtCP_uDLookupTable_bp01Data_h1m0 rtCP_pooled_NApuNazfrZXQ/* Expression: Lookup.Vel_brPts_mDs
                                                                  * Referenced by: '<S159>/2-D Lookup Table' (Parameter: BreakpointsForDimension1)
                                                                  */
#define rtCP_uDLookupTable_bp02Data_knp5 rtCP_pooled_Gn7U3gRTnp21/* Expression: Lookup.omega_brPts_radDs
                                                                  * Referenced by: '<S159>/2-D Lookup Table' (Parameter: BreakpointsForDimension2)
                                                                  */
#define rtCP_Aerodynamic_BodyDrag_Value rtCP_pooled_2V4qcztE4WKe /* Expression: Aero.Body.C_D
                                                                  * Referenced by: '<S29>/Aerodynamic_Body Drag' (Parameter: Value)
                                                                  */
#define rtCP_Constant_Value_pbz0       rtCP_pooled_o7MB5naIXTAF  /* Expression: Vehicle_Frame_Data.Environment.acc_G_R_OO_O_mDs2
                                                                  * Referenced by: '<S183>/Constant' (Parameter: Value)
                                                                  */
#define rtCP_Constant_Value_lulu       rtCP_pooled_Jd4cl5NFewNp  /* Expression: GC.pos_RC_B_m
                                                                  * Referenced by: '<S44>/Constant' (Parameter: Value)
                                                                  */
#define rtCP_Constant_Value_n4di       rtCP_pooled_UbozXULFB58v  /* Expression: GC.pos_RC_B_m
                                                                  * Referenced by: '<S61>/Constant' (Parameter: Value)
                                                                  */
#define rtCP_Constant_Value_fsfs       rtCP_pooled_YxVQUVpyy1ZW  /* Expression: GC.pos_RC_B_m
                                                                  * Referenced by: '<S78>/Constant' (Parameter: Value)
                                                                  */
#define rtCP_Constant_Value_kqqp       rtCP_pooled_QamkoadBrzvw  /* Expression: GC.pos_RC_B_m
                                                                  * Referenced by: '<S95>/Constant' (Parameter: Value)
                                                                  */
#define rtCP_Constant2_Value_gfas      rtCP_pooled_wvqoDCxkDmXt  /* Expression: Weight_Balance.I_R_BB_kgm2
                                                                  * Referenced by: '<S35>/Constant2' (Parameter: Value)
                                                                  */
#define rtCP_Constant3_Value_dg45      rtCP_pooled_s9j6OaAnioFp  /* Expression: Sensor.Bias
                                                                  * Referenced by: '<S234>/Constant3' (Parameter: Value)
                                                                  */
#define rtCP_C2_Value                  rtCP_pooled_0fOaedqqRxfM  /* Expression: [5;5;10]
                                                                  * Referenced by: '<S345>/C2' (Parameter: Value)
                                                                  */
#define rtCP_Constant3_Value_dn01      rtCP_pooled_YnZRlcPCkOxc  /* Expression: Sensor.Bias
                                                                  * Referenced by: '<S369>/Constant3' (Parameter: Value)
                                                                  */
#define rtCP_Constant3_Value_h5nx      rtCP_pooled_s9j6OaAnioFp  /* Expression: Sensor.Bias
                                                                  * Referenced by: '<S384>/Constant3' (Parameter: Value)
                                                                  */
#define rtCP_RandomNumber2_Seed        rtCP_pooled_zCwzTOhTFZVI  /* Expression: Sensor.Seed
                                                                  * Referenced by: '<S228>/Random Number2' (Parameter: Seed)
                                                                  */
#define rtCP_Gain_Gain_h24a            rtCP_pooled_Qj4DzRzeKvfC  /* Expression: Sensor.Variance
                                                                  * Referenced by: '<S228>/Gain' (Parameter: Gain)
                                                                  */
#define rtCP_RandomNumber2_Seed_kuez   rtCP_pooled_sTUNfpUIPpSd  /* Expression: Sensor.Seed
                                                                  * Referenced by: '<S364>/Random Number2' (Parameter: Seed)
                                                                  */
#define rtCP_Gain_Gain_hoji            rtCP_pooled_hw6GxjthfW52  /* Expression: Sensor.Variance
                                                                  * Referenced by: '<S364>/Gain' (Parameter: Gain)
                                                                  */
#define rtCP_RandomNumber2_Seed_g2mi   rtCP_pooled_zCwzTOhTFZVI  /* Expression: Sensor.Seed
                                                                  * Referenced by: '<S380>/Random Number2' (Parameter: Seed)
                                                                  */
#define rtCP_Gain_Gain_joui            rtCP_pooled_Qj4DzRzeKvfC  /* Expression: Sensor.Variance
                                                                  * Referenced by: '<S380>/Gain' (Parameter: Gain)
                                                                  */
#define rtCP_RandomNumber2_Seed_ndei   rtCP_pooled_VvcENMMe7tfY  /* Expression: Sensor.Seed
                                                                  * Referenced by: '<S316>/Random Number2' (Parameter: Seed)
                                                                  */
#define rtCP_RandomNumber_Seed         rtCP_pooled_0RyAaVW2z3MA  /* Expression:  cumsum(ones(dim,1))*6123
                                                                  * Referenced by: '<S354>/Random Number' (Parameter: Seed)
                                                                  */
#define rtCP_RandomNumber_StdDev_azwi  rtCP_pooled_s0HvNqDjfitH  /* Computed Parameter: rtCP_RandomNumber_StdDev_azwi
                                                                  * Referenced by: '<S352>/Random Number' (Parameter: StdDev)
                                                                  */
#define rtCP_RandomNumber_Seed_f55z    rtCP_pooled_UQ2TRgUJlJ1B  /* Expression: [7456;7567;7678]
                                                                  * Referenced by: '<S352>/Random Number' (Parameter: Seed)
                                                                  */
#define rtCP_RandomNumber1_StdDev      rtCP_pooled_Cjw806MXsseM  /* Computed Parameter: rtCP_RandomNumber1_StdDev
                                                                  * Referenced by: '<S342>/Random Number1' (Parameter: StdDev)
                                                                  */
#define rtCP_RandomNumber1_Seed        rtCP_pooled_babEPG1srVnA  /* Expression: [7123;7234;7345]
                                                                  * Referenced by: '<S342>/Random Number1' (Parameter: Seed)
                                                                  */
#define rtCP_RandomNumber2_Seed_l1ri   rtCP_pooled_UsOdXfZgGtoj  /* Expression: Sensor.Seed
                                                                  * Referenced by: '<S317>/Random Number2' (Parameter: Seed)
                                                                  */
#define rtCP_RandomNumber2_Seed_kn3y   rtCP_pooled_VvcENMMe7tfY  /* Expression: Sensor.Seed
                                                                  * Referenced by: '<S315>/Random Number2' (Parameter: Seed)
                                                                  */
#define rtCP_RandomNumber2_Seed_f0v3   rtCP_pooled_UsOdXfZgGtoj  /* Expression: Sensor.Seed
                                                                  * Referenced by: '<S243>/Random Number2' (Parameter: Seed)
                                                                  */
#define rtCP_RandomNumber2_Seed_d0me   rtCP_pooled_UsOdXfZgGtoj  /* Expression: Sensor.Seed
                                                                  * Referenced by: '<S244>/Random Number2' (Parameter: Seed)
                                                                  */
#define rtCP_RandomNumber2_Seed_bhlk   rtCP_pooled_UsOdXfZgGtoj  /* Expression: Sensor.Seed
                                                                  * Referenced by: '<S245>/Random Number2' (Parameter: Seed)
                                                                  */
#define rtCP_RandomNumber2_Seed_mev2   rtCP_pooled_UsOdXfZgGtoj  /* Expression: Sensor.Seed
                                                                  * Referenced by: '<S246>/Random Number2' (Parameter: Seed)
                                                                  */
#define rtCP_RandomNumber2_Seed_mns2   rtCP_pooled_UsOdXfZgGtoj  /* Expression: Sensor.Seed
                                                                  * Referenced by: '<S247>/Random Number2' (Parameter: Seed)
                                                                  */
#define rtCP_RandomNumber2_Seed_oc5t   rtCP_pooled_UsOdXfZgGtoj  /* Expression: Sensor.Seed
                                                                  * Referenced by: '<S248>/Random Number2' (Parameter: Seed)
                                                                  */
#define rtCP_RandomNumber2_Seed_kkhk   rtCP_pooled_UsOdXfZgGtoj  /* Expression: Sensor.Seed
                                                                  * Referenced by: '<S249>/Random Number2' (Parameter: Seed)
                                                                  */
#define rtCP_RandomNumber2_Seed_li24   rtCP_pooled_UsOdXfZgGtoj  /* Expression: Sensor.Seed
                                                                  * Referenced by: '<S250>/Random Number2' (Parameter: Seed)
                                                                  */
#define rtCP_RandomNumber2_Seed_oqyr   rtCP_pooled_UsOdXfZgGtoj  /* Expression: Sensor.Seed
                                                                  * Referenced by: '<S390>/Random Number2' (Parameter: Seed)
                                                                  */
#define rtCP_Gain_Gain_mhkw            rtCP_pooled_PNSnPc6Of7T3  /* Expression: Sensor.Variance
                                                                  * Referenced by: '<S316>/Gain' (Parameter: Gain)
                                                                  */
#define rtCP_Gain_Gain_jmhp            rtCP_pooled_obE6V7ylra60  /* Expression: Sensor.Variance
                                                                  * Referenced by: '<S317>/Gain' (Parameter: Gain)
                                                                  */
#define rtCP_Gain_Gain_nqmx            rtCP_pooled_PNSnPc6Of7T3  /* Expression: Sensor.Variance
                                                                  * Referenced by: '<S315>/Gain' (Parameter: Gain)
                                                                  */
#define rtCP_Gain_Gain_o55y            rtCP_pooled_obE6V7ylra60  /* Expression: Sensor.Variance
                                                                  * Referenced by: '<S243>/Gain' (Parameter: Gain)
                                                                  */
#define rtCP_Gain_Gain_odic            rtCP_pooled_obE6V7ylra60  /* Expression: Sensor.Variance
                                                                  * Referenced by: '<S244>/Gain' (Parameter: Gain)
                                                                  */
#define rtCP_Gain_Gain_lekx            rtCP_pooled_obE6V7ylra60  /* Expression: Sensor.Variance
                                                                  * Referenced by: '<S245>/Gain' (Parameter: Gain)
                                                                  */
#define rtCP_Gain_Gain_ax5s            rtCP_pooled_obE6V7ylra60  /* Expression: Sensor.Variance
                                                                  * Referenced by: '<S246>/Gain' (Parameter: Gain)
                                                                  */
#define rtCP_Gain_Gain_nv2m            rtCP_pooled_obE6V7ylra60  /* Expression: Sensor.Variance
                                                                  * Referenced by: '<S247>/Gain' (Parameter: Gain)
                                                                  */
#define rtCP_Gain_Gain_io0i            rtCP_pooled_obE6V7ylra60  /* Expression: Sensor.Variance
                                                                  * Referenced by: '<S248>/Gain' (Parameter: Gain)
                                                                  */
#define rtCP_Gain_Gain_m1t0            rtCP_pooled_obE6V7ylra60  /* Expression: Sensor.Variance
                                                                  * Referenced by: '<S249>/Gain' (Parameter: Gain)
                                                                  */
#define rtCP_Gain_Gain_cpem            rtCP_pooled_obE6V7ylra60  /* Expression: Sensor.Variance
                                                                  * Referenced by: '<S250>/Gain' (Parameter: Gain)
                                                                  */
#define rtCP_Gain_Gain_enbz            rtCP_pooled_obE6V7ylra60  /* Expression: Sensor.Variance
                                                                  * Referenced by: '<S390>/Gain' (Parameter: Gain)
                                                                  */
#define rtCP_uDLookupTable_maxIndex    rtCP_pooled_L0BJOqhq6uSa  /* Computed Parameter: rtCP_uDLookupTable_maxIndex
                                                                  * Referenced by: '<S137>/2-D Lookup Table' (Parameter: maxIndex)
                                                                  */
#define rtCP_uDLookupTable_maxIndex_g45d rtCP_pooled_L0BJOqhq6uSa/* Computed Parameter: rtCP_uDLookupTable_maxIndex_g45d
                                                                  * Referenced by: '<S159>/2-D Lookup Table' (Parameter: maxIndex)
                                                                  */

/* Constant parameters (default storage) */
extern const ConstP_RMT_FDM_RT_T RMT_FDM_RT_ConstP;

/* Invariant block signals (default storage) */
extern const ConstB_RMT_FDM_RT_hb4t_T RMT_FDM_RT_ConstB;

#endif                                 /* RMT_FDM_RT_private_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
