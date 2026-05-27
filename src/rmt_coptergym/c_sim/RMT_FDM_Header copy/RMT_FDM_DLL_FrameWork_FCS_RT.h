/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: RMT_FDM_DLL_FrameWork_FCS_RT.h
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

#ifndef RMT_FDM_DLL_FrameWork_FCS_RT_h_
#define RMT_FDM_DLL_FrameWork_FCS_RT_h_
#ifndef RMT_FDM_DLL_FrameWork_FCS_RT_COMMON_INCLUDES_
#define RMT_FDM_DLL_FrameWork_FCS_RT_COMMON_INCLUDES_
#include <stdlib.h>
#include "rtwtypes.h"
#include "rtw_continuous.h"
#include "rtw_solver.h"
#include "rt_nonfinite.h"
#include "math.h"
#endif                       /* RMT_FDM_DLL_FrameWork_FCS_RT_COMMON_INCLUDES_ */

#include "RMT_FDM_DLL_FrameWork_FCS_RT_types.h"
#include "fc_pilot_cmd_Bus.h"
#include "RMT_FDM_RT.h"
#include "rtGetNaN.h"
#include "model_reference_types.h"
#include <string.h>
#include <stddef.h>
#include "zero_crossing_types.h"

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
#define rtmGetErrorStatus(rtm)         ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
#define rtmSetErrorStatus(rtm, val)    ((rtm)->errorStatus = (val))
#endif

#ifndef rtmGetErrorStatusPointer
#define rtmGetErrorStatusPointer(rtm)  ((const char_T **)(&((rtm)->errorStatus)))
#endif

#ifndef rtmGetStopRequested
#define rtmGetStopRequested(rtm)       ((rtm)->Timing.stopRequestedFlag)
#endif

#ifndef rtmSetStopRequested
#define rtmSetStopRequested(rtm, val)  ((rtm)->Timing.stopRequestedFlag = (val))
#endif

#ifndef rtmGetStopRequestedPtr
#define rtmGetStopRequestedPtr(rtm)    (&((rtm)->Timing.stopRequestedFlag))
#endif

#ifndef rtmGetT
#define rtmGetT(rtm)                   (rtmGetTPtr((rtm))[0])
#endif

#ifndef rtmGetTPtr
#define rtmGetTPtr(rtm)                ((rtm)->Timing.t)
#endif

#ifndef rtmGetTStart
#define rtmGetTStart(rtm)              ((rtm)->Timing.tStart)
#endif

/* Block signals (default storage) */
typedef struct {
  Vehicle_Bus Vehicle;                 /* '<Root>/RMT_Plant' (Output 1) */
  Measurements_Bus Measurements;       /* '<Root>/RMT_Plant' (Output 2) */
  fc_measurements_Bus RT2;             /* '<Root>/RT2' (Output 1) */
  States_Init_Bus RT3;                 /* '<Root>/RT3' (Output 1) */
  fc_est_Bus BusAssignment;            /* '<S14>/Bus Assignment' (Output 1) */
  fc_pilot_cmd_Bus RT1;                /* '<Root>/RT1' (Output 1) */
  fc_ctrl_cmd_Bus RT_itkc;             /* '<Root>/RT' (Output 1) */
  fc_ctrl_cmd_Bus fc_ctrl_cmd;         /* '<S11>/Bus Assignment' (Output 1) */
  Controller_Commands_Bus Contoller_cmd_faults;/* '<S3>/Bus Creaor' (Output 1) */
  Controller_Commands_Bus RT4;         /* '<Root>/RT4' (Output 1) */
  Controller_Commands_Bus Switch;      /* '<Root>/Switch' (Output 1) */
  real_T RT7[8];                       /* '<Root>/RT7' (Output 1) */
  real_T RT6[8];                       /* '<Root>/RT6' (Output 1) */
  real_T Product2[3];                  /* '<S2>/Product2' (Output 1) */
  real_T Product[3];                   /* '<S2>/Product' (Output 1) */
} B_RMT_FDM_DLL_FrameWork_FCS_RT_T;

/* Block states (default storage) for system '<Root>' */
typedef struct {
  real_T Delay_DSTATE;                 /* '<S2>/Delay' (DWork 1) */
  real_T Delay1_DSTATE;                /* '<S2>/Delay1' (DWork 1) */
  real_T Delay2_DSTATE;                /* '<S2>/Delay2' (DWork 1) */
  real_T Delay3_DSTATE;                /* '<S2>/Delay3' (DWork 1) */
  real_T Delay16_DSTATE;               /* '<S2>/Delay16' (DWork 1) */
  real_T Delay17_DSTATE;               /* '<S2>/Delay17' (DWork 1) */
  real_T Delay18_DSTATE;               /* '<S2>/Delay18' (DWork 1) */
  real_T Delay4_DSTATE;                /* '<S2>/Delay4' (DWork 1) */
  real_T Delay5_DSTATE;                /* '<S2>/Delay5' (DWork 1) */
  real_T Delay6_DSTATE;                /* '<S2>/Delay6' (DWork 1) */
  real_T Delay7_DSTATE;                /* '<S2>/Delay7' (DWork 1) */
  real_T Delay8_DSTATE;                /* '<S2>/Delay8' (DWork 1) */
  real_T Delay9_DSTATE;                /* '<S2>/Delay9' (DWork 1) */
  real_T Delay10_DSTATE;               /* '<S2>/Delay10' (DWork 1) */
  real_T Delay11_DSTATE;               /* '<S2>/Delay11' (DWork 1) */
  real_T Delay12_DSTATE;               /* '<S2>/Delay12' (DWork 1) */
  real_T Delay13_DSTATE;               /* '<S2>/Delay13' (DWork 1) */
  real_T Delay14_DSTATE;               /* '<S2>/Delay14' (DWork 1) */
  real_T Delay15_DSTATE;               /* '<S2>/Delay15' (DWork 1) */
  real_T UD_DSTATE[3];                 /* '<S32>/UD' (DWork 1) */
  real_T Delay_DSTATE_oj24[10];        /* '<S5>/Delay' (DWork 1) */
  real_T Phi_Ref_DSTATE;               /* '<S47>/Phi_Ref' (DWork 1) */
  real_T Theta_Ref_DSTATE;             /* '<S47>/Theta_Ref' (DWork 1) */
  real_T p_Ref_DSTATE;                 /* '<S48>/p_Ref' (DWork 1) */
  real_T q_Ref_DSTATE;                 /* '<S48>/q_Ref' (DWork 1) */
  real_T r_Ref_DSTATE;                 /* '<S48>/r_Ref' (DWork 1) */
  real_T DiscreteTimeIntegrator_DSTATE;
                                /* '<S62>/Discrete-Time Integrator' (DWork 1) */
  real_T DiscreteTimeIntegrator_DSTATE_hs0d;
                                /* '<S63>/Discrete-Time Integrator' (DWork 1) */
  real_T DiscreteTimeIntegrator_DSTATE_japy;
                                /* '<S64>/Discrete-Time Integrator' (DWork 1) */
  real_T DiscreteTimeIntegrator_DSTATE_avov[8];
                                /* '<S10>/Discrete-Time Integrator' (DWork 1) */
  real_T DiscreteTimeIntegrator1_DSTATE[3];
                               /* '<S35>/Discrete-Time Integrator1' (DWork 1) */
  real_T DiscreteTimeIntegrator_DSTATE_pv2o[3];
                                /* '<S35>/Discrete-Time Integrator' (DWork 1) */
  real_T DiscreteTimeIntegrator1_DSTATE_lwvn[2];
                               /* '<S31>/Discrete-Time Integrator1' (DWork 1) */
  real_T DiscreteTimeIntegrator_DSTATE_ajjv[2];
                                /* '<S31>/Discrete-Time Integrator' (DWork 1) */
  int32_T SFunction_DIMS5;            /* '<S17>/Scale_NST_Solution' (DWork 1) */
  int32_T SFunction_DIMS6;            /* '<S17>/Scale_NST_Solution' (DWork 2) */
  int8_T Phi_Ref_PrevResetState;       /* '<S47>/Phi_Ref' (DWork 2) */
  int8_T Theta_Ref_PrevResetState;     /* '<S47>/Theta_Ref' (DWork 2) */
  int8_T p_Ref_PrevResetState;         /* '<S48>/p_Ref' (DWork 2) */
  int8_T q_Ref_PrevResetState;         /* '<S48>/q_Ref' (DWork 2) */
  int8_T r_Ref_PrevResetState;         /* '<S48>/r_Ref' (DWork 2) */
  int8_T DiscreteTimeIntegrator_PrevResetState;
                                /* '<S62>/Discrete-Time Integrator' (DWork 2) */
  int8_T DiscreteTimeIntegrator_PrevResetState_nmap;
                                /* '<S63>/Discrete-Time Integrator' (DWork 2) */
  int8_T DiscreteTimeIntegrator_PrevResetState_fwtq;
                                /* '<S64>/Discrete-Time Integrator' (DWork 2) */
  int8_T DiscreteTimeIntegrator_PrevResetState_dbpn;
                                /* '<S10>/Discrete-Time Integrator' (DWork 2) */
  uint8_T DiscreteTimeIntegrator_IC_LOADING;
                                /* '<S10>/Discrete-Time Integrator' (DWork 3) */
  boolean_T icLoad;                    /* '<S2>/Delay' (DWork 2) */
  boolean_T icLoad_hvp0;               /* '<S2>/Delay1' (DWork 2) */
  boolean_T icLoad_agwh;               /* '<S2>/Delay2' (DWork 2) */
  boolean_T icLoad_k4aw;               /* '<S2>/Delay3' (DWork 2) */
  boolean_T icLoad_finj;               /* '<S2>/Delay16' (DWork 2) */
  boolean_T icLoad_eux1;               /* '<S2>/Delay17' (DWork 2) */
  boolean_T icLoad_mxgu;               /* '<S2>/Delay18' (DWork 2) */
  boolean_T icLoad_pbo0;               /* '<S2>/Delay4' (DWork 2) */
  boolean_T icLoad_dtzm;               /* '<S2>/Delay5' (DWork 2) */
  boolean_T icLoad_mfcp;               /* '<S2>/Delay6' (DWork 2) */
  boolean_T icLoad_js0i;               /* '<S2>/Delay7' (DWork 2) */
  boolean_T icLoad_doan;               /* '<S2>/Delay8' (DWork 2) */
  boolean_T icLoad_mzf4;               /* '<S2>/Delay9' (DWork 2) */
  boolean_T icLoad_chzd;               /* '<S2>/Delay10' (DWork 2) */
  boolean_T icLoad_giyv;               /* '<S2>/Delay11' (DWork 2) */
  boolean_T icLoad_lwdp;               /* '<S2>/Delay12' (DWork 2) */
  boolean_T icLoad_bu4u;               /* '<S2>/Delay13' (DWork 2) */
  boolean_T icLoad_atsy;               /* '<S2>/Delay14' (DWork 2) */
  boolean_T icLoad_nbvc;               /* '<S2>/Delay15' (DWork 2) */
  boolean_T FCS_INDI_Control_MODE;     /* '<Root>/FCS_INDI_Control' (DWork 1) */
  MdlrefDW_RMT_FDM_RT_T RMT_Plant_InstanceData;/* '<Root>/RMT_Plant' (DWork 1) */
} DW_RMT_FDM_DLL_FrameWork_FCS_RT_T;

/* Continuous states (default storage) */
typedef struct {
  X_RMT_FDM_RT_nymf_T RMT_Plant_CSTATE;/* '<Root>/RMT_Plant' */
} X_RMT_FDM_DLL_FrameWork_FCS_RT_T;

/* State derivatives (default storage) */
typedef struct {
  XDot_RMT_FDM_RT_n1mv_T RMT_Plant_CSTATE;/* '<Root>/RMT_Plant' */
} XDot_RMT_FDM_DLL_FrameWork_FCS_RT_T;

/* State disabled  */
typedef struct {
  XDis_RMT_FDM_RT_nenc_T RMT_Plant_CSTATE;/* '<Root>/RMT_Plant' */
} XDis_RMT_FDM_DLL_FrameWork_FCS_RT_T;

/* Zero-crossing (trigger) state */
typedef struct {
  ZCSigState Delay_Reset_ZCE;          /* '<S2>/Delay' */
  ZCSigState Delay1_Reset_ZCE;         /* '<S2>/Delay1' */
  ZCSigState Delay2_Reset_ZCE;         /* '<S2>/Delay2' */
  ZCSigState Delay3_Reset_ZCE;         /* '<S2>/Delay3' */
  ZCSigState Delay16_Reset_ZCE;        /* '<S2>/Delay16' */
  ZCSigState Delay17_Reset_ZCE;        /* '<S2>/Delay17' */
  ZCSigState Delay18_Reset_ZCE;        /* '<S2>/Delay18' */
  ZCSigState Delay4_Reset_ZCE;         /* '<S2>/Delay4' */
  ZCSigState Delay5_Reset_ZCE;         /* '<S2>/Delay5' */
  ZCSigState Delay6_Reset_ZCE;         /* '<S2>/Delay6' */
  ZCSigState Delay7_Reset_ZCE;         /* '<S2>/Delay7' */
  ZCSigState Delay8_Reset_ZCE;         /* '<S2>/Delay8' */
  ZCSigState Delay9_Reset_ZCE;         /* '<S2>/Delay9' */
  ZCSigState Delay10_Reset_ZCE;        /* '<S2>/Delay10' */
  ZCSigState Delay11_Reset_ZCE;        /* '<S2>/Delay11' */
  ZCSigState Delay12_Reset_ZCE;        /* '<S2>/Delay12' */
  ZCSigState Delay13_Reset_ZCE;        /* '<S2>/Delay13' */
  ZCSigState Delay14_Reset_ZCE;        /* '<S2>/Delay14' */
  ZCSigState Delay15_Reset_ZCE;        /* '<S2>/Delay15' */
  ZCSigState Delay_Reset_ZCE_pegz;     /* '<S5>/Delay' */
} PrevZCX_RMT_FDM_DLL_FrameWork_FCS_RT_T;

/* Invariant block signals (default storage) */
typedef struct {
  const real_T Reshape1[3];            /* '<S2>/Reshape1' (Output 1) */
  const real_T VectorConcatenate[3];  /* '<S7>/Vector Concatenate' (Output 1) */
  const real_T VectorConcatenate1[3];/* '<S8>/Vector Concatenate1' (Output 1) */
  const real_T VectorConcatenate2[3];/* '<S9>/Vector Concatenate2' (Output 1) */
  const real_T Static_Temperature_ATM_K;/* '<S4>/Gain1' (Output 1) */
  const real_T Static_Pressure_ATM_NDm2;/* '<S4>/Gain2' (Output 1) */
  const real_T rho_kgDm3;              /* '<S4>/Gain3' (Output 1) */
  const real_T Speed_of_Sound_mDs;     /* '<S4>/Gain4' (Output 1) */
  const real_T VectorConcatenate2_a1ra[3];
                                    /* '<S33>/Vector Concatenate2' (Output 1) */
  const real_T Reshape3[3];            /* '<S14>/Reshape3' (Output 1) */
  const real_T VectorConcatenate_kzgt[3];
                                     /* '<S37>/Vector Concatenate' (Output 1) */
  const real_T VectorConcatenate1_hoyi[3];
                                    /* '<S38>/Vector Concatenate1' (Output 1) */
  const real_T VectorConcatenate2_kahd[3];
                                    /* '<S39>/Vector Concatenate2' (Output 1) */
  const real_T Reshape2[3];            /* '<S40>/Reshape2' (Output 1) */
  const real_T Gain;                   /* '<S48>/Gain' (Output 1) */
  const real_T Gain6;                  /* '<S48>/Gain6' (Output 1) */
  const real_T Gain7;                  /* '<S48>/Gain7' (Output 1) */
  const boolean_T DataTypeConversion[8];
                                   /* '<S17>/Data Type Conversion' (Output 1) */
  const boolean_T VectorConcatenate_pyno[10];
                                     /* '<S17>/Vector Concatenate' (Output 1) */
} ConstB_RMT_FDM_DLL_FrameWork_FCS_RT_T;

#ifndef ODE4_INTG
#define ODE4_INTG

/* ODE4 Integration Data */
typedef struct {
  real_T *y;                           /* output */
  real_T *f[4];                        /* derivatives */
} ODE4_IntgData;

#endif

/* Real-time Model Data Structure */
struct tag_RTM_RMT_FDM_DLL_FrameWork_FCS_RT_T {
  const char_T *errorStatus;
  RTWSolverInfo *solverInfo;
  rtTimingBridge timingBridge;

  /*
   * ModelData:
   * The following substructure contains information regarding
   * the data used in the model.
   */
  struct {
    B_RMT_FDM_DLL_FrameWork_FCS_RT_T *blockIO;
    PrevZCX_RMT_FDM_DLL_FrameWork_FCS_RT_T *prevZCSigState;
    X_RMT_FDM_DLL_FrameWork_FCS_RT_T *contStates;
    int_T *periodicContStateIndices;
    real_T *periodicContStateRanges;
    real_T *derivs;
    XDis_RMT_FDM_DLL_FrameWork_FCS_RT_T *contStateDisabled;
    boolean_T zCCacheNeedsReset;
    boolean_T derivCacheNeedsReset;
    boolean_T CTOutputIncnstWithState;
    real_T odeY[62];
    real_T odeF[4][62];
    ODE4_IntgData intgData;
    DW_RMT_FDM_DLL_FrameWork_FCS_RT_T *dwork;
  } ModelData;

  /*
   * Sizes:
   * The following substructure contains sizes information
   * for many of the model attributes such as inputs, outputs,
   * dwork, sample times, etc.
   */
  struct {
    int_T numContStates;
    int_T numPeriodicContStates;
    int_T numSampTimes;
  } Sizes;

  /*
   * Timing:
   * The following substructure contains information regarding
   * the timing information for the model.
   */
  struct {
    uint32_T clockTick0;
    time_T stepSize0;
    uint32_T clockTick1;
    uint32_T clockTick2;
    boolean_T firstInitCondFlag;
    struct {
      uint32_T TID[3];
    } TaskCounters;

    time_T tStart;
    SimTimeStep simTimeStep;
    boolean_T stopRequestedFlag;
    time_T *t;
    time_T tArray[3];
  } Timing;
};

/* External data declarations for dependent source files */
extern const Simulation_Control_Bus
  RMT_FDM_DLL_FrameWork_FCS_RT_rtZSimulation_Control_Bus;/* Simulation_Control_Bus ground */
extern const States_Init_Bus RMT_FDM_DLL_FrameWork_FCS_RT_rtZStates_Init_Bus;/* States_Init_Bus ground */
extern const fc_pilot_cmd_Bus RMT_FDM_DLL_FrameWork_FCS_RT_rtZfc_pilot_cmd_Bus;/* fc_pilot_cmd_Bus ground */
extern const Failure_Bus RMT_FDM_DLL_FrameWork_FCS_RT_rtZFailure_Bus;/* Failure_Bus ground */
extern const fc_est_Bus RMT_FDM_DLL_FrameWork_FCS_RT_rtZfc_est_Bus;/* fc_est_Bus ground */
extern const Vehicle_Bus RMT_FDM_DLL_FrameWork_FCS_RT_rtZVehicle_Bus;/* Vehicle_Bus ground */
extern const Measurements_Bus RMT_FDM_DLL_FrameWork_FCS_RT_rtZMeasurements_Bus;/* Measurements_Bus ground */
extern const char_T *RT_MEMORY_ALLOCATION_ERROR;
extern const ConstB_RMT_FDM_DLL_FrameWork_FCS_RT_T
  RMT_FDM_DLL_FrameWork_FCS_RT_ConstB; /* constant block i/o */

/* Model entry point functions */
extern RT_MODEL_RMT_FDM_DLL_FrameWork_FCS_RT_T *RMT_FDM_DLL_FrameWork_FCS_RT
  (Simulation_Control_Bus *RMT_FDM_DLL_FrameWork_FCS_RT_U_Simulation_Control,
   States_Init_Bus *RMT_FDM_DLL_FrameWork_FCS_RT_U_States_Init, real_T
   RMT_FDM_DLL_FrameWork_FCS_RT_U_w_cmd_radDs[8], fc_pilot_cmd_Bus
   *RMT_FDM_DLL_FrameWork_FCS_RT_U_fc_pilot_cmd, Failure_Bus
   *RMT_FDM_DLL_FrameWork_FCS_RT_U_Failures, Vehicle_Bus
   *RMT_FDM_DLL_FrameWork_FCS_RT_Y_Vehicle, Measurements_Bus
   *RMT_FDM_DLL_FrameWork_FCS_RT_Y_Measurements, fc_est_Bus
   *RMT_FDM_DLL_FrameWork_FCS_RT_Y_fc_estimation);
extern void RMT_FDM_DLL_FrameWork_FCS_RT_initialize
  (RT_MODEL_RMT_FDM_DLL_FrameWork_FCS_RT_T *const RMT_FDM_DLL_FrameWork_FCS_RT_M);
extern void RMT_FDM_DLL_FrameWork_FCS_RT_step
  (RT_MODEL_RMT_FDM_DLL_FrameWork_FCS_RT_T *const RMT_FDM_DLL_FrameWork_FCS_RT_M,
   Simulation_Control_Bus *RMT_FDM_DLL_FrameWork_FCS_RT_U_Simulation_Control,
   States_Init_Bus *RMT_FDM_DLL_FrameWork_FCS_RT_U_States_Init, real_T
   RMT_FDM_DLL_FrameWork_FCS_RT_U_w_cmd_radDs[8], fc_pilot_cmd_Bus
   *RMT_FDM_DLL_FrameWork_FCS_RT_U_fc_pilot_cmd, Failure_Bus
   *RMT_FDM_DLL_FrameWork_FCS_RT_U_Failures, Vehicle_Bus
   *RMT_FDM_DLL_FrameWork_FCS_RT_Y_Vehicle, Measurements_Bus
   *RMT_FDM_DLL_FrameWork_FCS_RT_Y_Measurements, fc_est_Bus
   *RMT_FDM_DLL_FrameWork_FCS_RT_Y_fc_estimation);
extern void RMT_FDM_DLL_FrameWork_FCS_RT_terminate
  (RT_MODEL_RMT_FDM_DLL_FrameWork_FCS_RT_T * RMT_FDM_DLL_FrameWork_FCS_RT_M);

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Use the MATLAB hilite_system command to trace the generated code back
 * to the model.  For example,
 *
 * hilite_system('<S3>')    - opens system 3
 * hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'RMT_FDM_DLL_FrameWork_FCS_RT'
 * '<S1>'   : 'RMT_FDM_DLL_FrameWork_FCS_RT/Controller_Commands'
 * '<S2>'   : 'RMT_FDM_DLL_FrameWork_FCS_RT/Data_Mapping'
 * '<S3>'   : 'RMT_FDM_DLL_FrameWork_FCS_RT/ESC'
 * '<S4>'   : 'RMT_FDM_DLL_FrameWork_FCS_RT/External_Inputs'
 * '<S5>'   : 'RMT_FDM_DLL_FrameWork_FCS_RT/FCS_INDI_Control'
 * '<S6>'   : 'RMT_FDM_DLL_FrameWork_FCS_RT/Data_Mapping/Trafo_M_B0'
 * '<S7>'   : 'RMT_FDM_DLL_FrameWork_FCS_RT/Data_Mapping/Trafo_M_B0/M_x'
 * '<S8>'   : 'RMT_FDM_DLL_FrameWork_FCS_RT/Data_Mapping/Trafo_M_B0/M_y'
 * '<S9>'   : 'RMT_FDM_DLL_FrameWork_FCS_RT/Data_Mapping/Trafo_M_B0/M_z'
 * '<S10>'  : 'RMT_FDM_DLL_FrameWork_FCS_RT/FCS_INDI_Control/Actuator'
 * '<S11>'  : 'RMT_FDM_DLL_FrameWork_FCS_RT/FCS_INDI_Control/Command_Mapping'
 * '<S12>'  : 'RMT_FDM_DLL_FrameWork_FCS_RT/FCS_INDI_Control/Control_Allocation'
 * '<S13>'  : 'RMT_FDM_DLL_FrameWork_FCS_RT/FCS_INDI_Control/EC'
 * '<S14>'  : 'RMT_FDM_DLL_FrameWork_FCS_RT/FCS_INDI_Control/Estimation'
 * '<S15>'  : 'RMT_FDM_DLL_FrameWork_FCS_RT/FCS_INDI_Control/Reference_Model'
 * '<S16>'  : 'RMT_FDM_DLL_FrameWork_FCS_RT/FCS_INDI_Control/Trajectory_Control'
 * '<S17>'  : 'RMT_FDM_DLL_FrameWork_FCS_RT/FCS_INDI_Control/Control_Allocation/Control_Allocation_RPI'
 * '<S18>'  : 'RMT_FDM_DLL_FrameWork_FCS_RT/FCS_INDI_Control/Control_Allocation/Control_Allocation_RPI/Constraints'
 * '<S19>'  : 'RMT_FDM_DLL_FrameWork_FCS_RT/FCS_INDI_Control/Control_Allocation/Control_Allocation_RPI/Nullspace_Transition'
 * '<S20>'  : 'RMT_FDM_DLL_FrameWork_FCS_RT/FCS_INDI_Control/Control_Allocation/Control_Allocation_RPI/Redistribution'
 * '<S21>'  : 'RMT_FDM_DLL_FrameWork_FCS_RT/FCS_INDI_Control/Control_Allocation/Control_Allocation_RPI/Scale_NST_Solution'
 * '<S22>'  : 'RMT_FDM_DLL_FrameWork_FCS_RT/FCS_INDI_Control/Control_Allocation/Control_Allocation_RPI/Nullspace_Transition/Pseudoinverse'
 * '<S23>'  : 'RMT_FDM_DLL_FrameWork_FCS_RT/FCS_INDI_Control/Control_Allocation/Control_Allocation_RPI/Nullspace_Transition/nullspace'
 * '<S24>'  : 'RMT_FDM_DLL_FrameWork_FCS_RT/FCS_INDI_Control/EC/EC_Visual'
 * '<S25>'  : 'RMT_FDM_DLL_FrameWork_FCS_RT/FCS_INDI_Control/EC/Phi_Ctrl'
 * '<S26>'  : 'RMT_FDM_DLL_FrameWork_FCS_RT/FCS_INDI_Control/EC/Psi_Dot_Ctrl'
 * '<S27>'  : 'RMT_FDM_DLL_FrameWork_FCS_RT/FCS_INDI_Control/EC/Theta_Ctrl'
 * '<S28>'  : 'RMT_FDM_DLL_FrameWork_FCS_RT/FCS_INDI_Control/EC/u_Ctrl'
 * '<S29>'  : 'RMT_FDM_DLL_FrameWork_FCS_RT/FCS_INDI_Control/EC/v_ctrl'
 * '<S30>'  : 'RMT_FDM_DLL_FrameWork_FCS_RT/FCS_INDI_Control/EC/w_ctrl'
 * '<S31>'  : 'RMT_FDM_DLL_FrameWork_FCS_RT/FCS_INDI_Control/Estimation/Attitude_LowPass'
 * '<S32>'  : 'RMT_FDM_DLL_FrameWork_FCS_RT/FCS_INDI_Control/Estimation/Discrete Derivative'
 * '<S33>'  : 'RMT_FDM_DLL_FrameWork_FCS_RT/FCS_INDI_Control/Estimation/M_CO'
 * '<S34>'  : 'RMT_FDM_DLL_FrameWork_FCS_RT/FCS_INDI_Control/Estimation/Psi_Dot_Calc'
 * '<S35>'  : 'RMT_FDM_DLL_FrameWork_FCS_RT/FCS_INDI_Control/Estimation/Rate_LowPass'
 * '<S36>'  : 'RMT_FDM_DLL_FrameWork_FCS_RT/FCS_INDI_Control/Estimation/Trafo_M_BC'
 * '<S37>'  : 'RMT_FDM_DLL_FrameWork_FCS_RT/FCS_INDI_Control/Estimation/Trafo_M_BC/M_x'
 * '<S38>'  : 'RMT_FDM_DLL_FrameWork_FCS_RT/FCS_INDI_Control/Estimation/Trafo_M_BC/M_y'
 * '<S39>'  : 'RMT_FDM_DLL_FrameWork_FCS_RT/FCS_INDI_Control/Estimation/Trafo_M_BC/M_z'
 * '<S40>'  : 'RMT_FDM_DLL_FrameWork_FCS_RT/FCS_INDI_Control/Reference_Model/Reference_Model_RD2'
 * '<S41>'  : 'RMT_FDM_DLL_FrameWork_FCS_RT/FCS_INDI_Control/Reference_Model/Reference_Model_RD2/Compare To Zero'
 * '<S42>'  : 'RMT_FDM_DLL_FrameWork_FCS_RT/FCS_INDI_Control/Reference_Model/Reference_Model_RD2/RM_attitude'
 * '<S43>'  : 'RMT_FDM_DLL_FrameWork_FCS_RT/FCS_INDI_Control/Reference_Model/Reference_Model_RD2/RM_vel'
 * '<S44>'  : 'RMT_FDM_DLL_FrameWork_FCS_RT/FCS_INDI_Control/Reference_Model/Reference_Model_RD2/RM_attitude/Attitude_Dynamics_Inversion'
 * '<S45>'  : 'RMT_FDM_DLL_FrameWork_FCS_RT/FCS_INDI_Control/Reference_Model/Reference_Model_RD2/RM_attitude/Attitude_Kinematics'
 * '<S46>'  : 'RMT_FDM_DLL_FrameWork_FCS_RT/FCS_INDI_Control/Reference_Model/Reference_Model_RD2/RM_attitude/att_ddot_euler_Ref_Calculation'
 * '<S47>'  : 'RMT_FDM_DLL_FrameWork_FCS_RT/FCS_INDI_Control/Reference_Model/Reference_Model_RD2/RM_attitude/att_euler_dot_Integration'
 * '<S48>'  : 'RMT_FDM_DLL_FrameWork_FCS_RT/FCS_INDI_Control/Reference_Model/Reference_Model_RD2/RM_attitude/nu_pqr_Integration'
 * '<S49>'  : 'RMT_FDM_DLL_FrameWork_FCS_RT/FCS_INDI_Control/Reference_Model/Reference_Model_RD2/RM_attitude/Attitude_Dynamics_Inversion/Calculation_v1'
 * '<S50>'  : 'RMT_FDM_DLL_FrameWork_FCS_RT/FCS_INDI_Control/Reference_Model/Reference_Model_RD2/RM_attitude/Attitude_Dynamics_Inversion/Calculation_v2'
 * '<S51>'  : 'RMT_FDM_DLL_FrameWork_FCS_RT/FCS_INDI_Control/Reference_Model/Reference_Model_RD2/RM_attitude/Attitude_Dynamics_Inversion/Calculation_v3'
 * '<S52>'  : 'RMT_FDM_DLL_FrameWork_FCS_RT/FCS_INDI_Control/Reference_Model/Reference_Model_RD2/RM_attitude/Attitude_Dynamics_Inversion/Matrix_A'
 * '<S53>'  : 'RMT_FDM_DLL_FrameWork_FCS_RT/FCS_INDI_Control/Reference_Model/Reference_Model_RD2/RM_attitude/att_euler_dot_Integration/Compare To Zero'
 * '<S54>'  : 'RMT_FDM_DLL_FrameWork_FCS_RT/FCS_INDI_Control/Reference_Model/Reference_Model_RD2/RM_attitude/att_euler_dot_Integration/Compare To Zero1'
 * '<S55>'  : 'RMT_FDM_DLL_FrameWork_FCS_RT/FCS_INDI_Control/Reference_Model/Reference_Model_RD2/RM_attitude/att_euler_dot_Integration/Limit_Phi_Ref'
 * '<S56>'  : 'RMT_FDM_DLL_FrameWork_FCS_RT/FCS_INDI_Control/Reference_Model/Reference_Model_RD2/RM_attitude/att_euler_dot_Integration/Limit_Theta_Ref'
 * '<S57>'  : 'RMT_FDM_DLL_FrameWork_FCS_RT/FCS_INDI_Control/Reference_Model/Reference_Model_RD2/RM_attitude/att_euler_dot_Integration/Limit_Phi_Ref/Saturation Dynamic'
 * '<S58>'  : 'RMT_FDM_DLL_FrameWork_FCS_RT/FCS_INDI_Control/Reference_Model/Reference_Model_RD2/RM_attitude/att_euler_dot_Integration/Limit_Theta_Ref/Saturation Dynamic'
 * '<S59>'  : 'RMT_FDM_DLL_FrameWork_FCS_RT/FCS_INDI_Control/Reference_Model/Reference_Model_RD2/RM_attitude/nu_pqr_Integration/Compare To Zero'
 * '<S60>'  : 'RMT_FDM_DLL_FrameWork_FCS_RT/FCS_INDI_Control/Reference_Model/Reference_Model_RD2/RM_attitude/nu_pqr_Integration/Compare To Zero1'
 * '<S61>'  : 'RMT_FDM_DLL_FrameWork_FCS_RT/FCS_INDI_Control/Reference_Model/Reference_Model_RD2/RM_attitude/nu_pqr_Integration/Compare To Zero2'
 * '<S62>'  : 'RMT_FDM_DLL_FrameWork_FCS_RT/FCS_INDI_Control/Reference_Model/Reference_Model_RD2/RM_vel/u_C_ref'
 * '<S63>'  : 'RMT_FDM_DLL_FrameWork_FCS_RT/FCS_INDI_Control/Reference_Model/Reference_Model_RD2/RM_vel/v_C_ref'
 * '<S64>'  : 'RMT_FDM_DLL_FrameWork_FCS_RT/FCS_INDI_Control/Reference_Model/Reference_Model_RD2/RM_vel/w_C_ref'
 */
#endif                                 /* RMT_FDM_DLL_FrameWork_FCS_RT_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
