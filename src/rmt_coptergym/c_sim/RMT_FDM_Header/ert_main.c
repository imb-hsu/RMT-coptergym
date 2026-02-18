/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: ert_main.c
 *
 * Code generated for Simulink model 'RMT_FDM_DLL_FrameWork_FCS_RT'.
 *
 * Model version                  : 11.34
 * Simulink Coder version         : 24.2 (R2024b) 21-Jun-2024
 * C/C++ source code generated on : Thu Dec  4 22:28:01 2025
 *
 * Target selection: ert_shrlib.tlc
 * Embedded hardware selection: Intel->x86-64 (Windows64)
 * Emulation hardware selection:
 *    Differs from embedded hardware (MATLAB Host)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include <stddef.h>
#include <stdio.h>            /* This example main program uses printf/fflush */
#include "RMT_FDM_DLL_FrameWork_FCS_RT.h" /* Model header file */

/* '<Root>/Simulation_Control' */
static Simulation_Control_Bus RMT_FDM_DLL_FrameWork_FCS_RT_U_Simulation_Control;

/* '<Root>/States_Init' */
static States_Init_Bus RMT_FDM_DLL_FrameWork_FCS_RT_U_States_Init;

/* '<Root>/w_cmd_radDs' */
static real_T RMT_FDM_DLL_FrameWork_FCS_RT_U_w_cmd_radDs[8];

/* '<Root>/fc_pilot_cmd' */
static fc_pilot_cmd_Bus RMT_FDM_DLL_FrameWork_FCS_RT_U_fc_pilot_cmd;

/* '<Root>/Failures' */
static Failure_Bus RMT_FDM_DLL_FrameWork_FCS_RT_U_Failures;

/* '<Root>/Vehicle' */
static Vehicle_Bus RMT_FDM_DLL_FrameWork_FCS_RT_Y_Vehicle;

/* '<Root>/Measurements' */
static Measurements_Bus RMT_FDM_DLL_FrameWork_FCS_RT_Y_Measurements;

/* '<Root>/fc_estimation' */
static fc_est_Bus RMT_FDM_DLL_FrameWork_FCS_RT_Y_fc_estimation;
const char *RT_MEMORY_ALLOCATION_ERROR = "memory allocation error";

/*
 * Associating rt_OneStep with a real-time clock or interrupt service routine
 * is what makes the generated code "real-time".  The function rt_OneStep is
 * always associated with the base rate of the model.  Subrates are managed
 * by the base rate from inside the generated code.  Enabling/disabling
 * interrupts and floating point context switches are target specific.  This
 * example code indicates where these should take place relative to executing
 * the generated code step function.  Overrun behavior should be tailored to
 * your application needs.  This example simply sets an error status in the
 * real-time model and returns from rt_OneStep.
 */
void rt_OneStep(RT_MODEL_RMT_FDM_DLL_FrameWork_FCS_RT_T *const
                RMT_FDM_DLL_FrameWork_FCS_RT_M);
void rt_OneStep(RT_MODEL_RMT_FDM_DLL_FrameWork_FCS_RT_T *const
                RMT_FDM_DLL_FrameWork_FCS_RT_M)
{
  static boolean_T OverrunFlag = false;

  /* Disable interrupts here */

  /* Check for overrun */
  if (OverrunFlag) {
    rtmSetErrorStatus(RMT_FDM_DLL_FrameWork_FCS_RT_M, "Overrun");
    return;
  }

  OverrunFlag = true;

  /* Save FPU context here (if necessary) */
  /* Re-enable timer or interrupt here */
  /* Set model inputs here */

  /* Step the model */
  RMT_FDM_DLL_FrameWork_FCS_RT_step(RMT_FDM_DLL_FrameWork_FCS_RT_M,
    &RMT_FDM_DLL_FrameWork_FCS_RT_U_Simulation_Control,
    &RMT_FDM_DLL_FrameWork_FCS_RT_U_States_Init,
    RMT_FDM_DLL_FrameWork_FCS_RT_U_w_cmd_radDs,
    &RMT_FDM_DLL_FrameWork_FCS_RT_U_fc_pilot_cmd,
    &RMT_FDM_DLL_FrameWork_FCS_RT_U_Failures,
    &RMT_FDM_DLL_FrameWork_FCS_RT_Y_Vehicle,
    &RMT_FDM_DLL_FrameWork_FCS_RT_Y_Measurements,
    &RMT_FDM_DLL_FrameWork_FCS_RT_Y_fc_estimation);

  /* Get model outputs here */

  /* Indicate task complete */
  OverrunFlag = false;

  /* Disable interrupts here */
  /* Restore FPU context here (if necessary) */
  /* Enable interrupts here */
}

/*
 * The example main function illustrates what is required by your
 * application code to initialize, execute, and terminate the generated code.
 * Attaching rt_OneStep to a real-time clock is target specific. This example
 * illustrates how you do this relative to initializing the model.
 */
int_T main(int_T argc, const char *argv[])
{
  RT_MODEL_RMT_FDM_DLL_FrameWork_FCS_RT_T *RMT_FDM_DLL_FrameWork_FCS_RT_M;

  /* Unused arguments */
  (void)(argc);
  (void)(argv);

  /* Allocate model data */
  RMT_FDM_DLL_FrameWork_FCS_RT_M = RMT_FDM_DLL_FrameWork_FCS_RT
    (&RMT_FDM_DLL_FrameWork_FCS_RT_U_Simulation_Control,
     &RMT_FDM_DLL_FrameWork_FCS_RT_U_States_Init,
     RMT_FDM_DLL_FrameWork_FCS_RT_U_w_cmd_radDs,
     &RMT_FDM_DLL_FrameWork_FCS_RT_U_fc_pilot_cmd,
     &RMT_FDM_DLL_FrameWork_FCS_RT_U_Failures,
     &RMT_FDM_DLL_FrameWork_FCS_RT_Y_Vehicle,
     &RMT_FDM_DLL_FrameWork_FCS_RT_Y_Measurements,
     &RMT_FDM_DLL_FrameWork_FCS_RT_Y_fc_estimation);
  if (RMT_FDM_DLL_FrameWork_FCS_RT_M == (NULL)) {
    (void)fprintf(stderr, "Memory allocation error during model registration");
    return(1);
  }

  if (rtmGetErrorStatus(RMT_FDM_DLL_FrameWork_FCS_RT_M) != (NULL)) {
    (void)fprintf(stderr, "Error during model registration: %s\n",
                  rtmGetErrorStatus(RMT_FDM_DLL_FrameWork_FCS_RT_M));

    /* Terminate model */
    RMT_FDM_DLL_FrameWork_FCS_RT_terminate(RMT_FDM_DLL_FrameWork_FCS_RT_M);
    return(1);
  }

  /* Initialize model */
  RMT_FDM_DLL_FrameWork_FCS_RT_initialize(RMT_FDM_DLL_FrameWork_FCS_RT_M);

  /* Simulating the model step behavior (in non real-time) to
   *  simulate model behavior at stop time.
   */
  while (rtmGetErrorStatus(RMT_FDM_DLL_FrameWork_FCS_RT_M) == (NULL)&&
         !rtmGetStopRequested(RMT_FDM_DLL_FrameWork_FCS_RT_M)) {
    rt_OneStep(RMT_FDM_DLL_FrameWork_FCS_RT_M);
  }

  /* Terminate model */
  RMT_FDM_DLL_FrameWork_FCS_RT_terminate(RMT_FDM_DLL_FrameWork_FCS_RT_M);
  return 0;
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
