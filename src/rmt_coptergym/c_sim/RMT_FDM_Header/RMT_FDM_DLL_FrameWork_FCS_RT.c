/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: RMT_FDM_DLL_FrameWork_FCS_RT.c
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

#include "RMT_FDM_DLL_FrameWork_FCS_RT.h"
#include "rtwtypes.h"
#include <math.h>
#include <string.h>
#include "svd_o1L0Nv3Z.h"
#include "rt_nonfinite.h"
#include "svd_i5n8QqSI.h"
#include "svd_I60xL6TN.h"
#include "svd_NJw3JjRP.h"
#include "svd_LrtoIvAo.h"
#include "eml_find_Ejmjtket.h"
#include "RMT_FDM_DLL_FrameWork_FCS_RT_types.h"
#include "fc_pilot_cmd_Bus.h"
#include "RMT_FDM_DLL_FrameWork_FCS_RT_private.h"
#include "RMT_FDM_RT.h"

/* Named constants for MATLAB Function: '<S19>/Pseudoinverse' */
#define RMT_FDM_DLL_FrameWork_FCS_RT_CALL_EVENT (-1)

static void rate_scheduler(RT_MODEL_RMT_FDM_DLL_FrameWork_FCS_RT_T *const
  RMT_FDM_DLL_FrameWork_FCS_RT_M);
const Failure_Bus RMT_FDM_DLL_FrameWork_FCS_RT_rtZFailure_Bus = { { 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0 }     /* motor_loss */
};

const Measurements_Bus RMT_FDM_DLL_FrameWork_FCS_RT_rtZMeasurements_Bus = { {
    0.0,                               /* Static_Pressure_meas_NDm2 */
    0.0,                               /* Static_Temperature_meas_K */
    0.0                                /* h_Baro_meas_m */
  },                                   /* baro_meas */

  { { 0.0,                             /* w_x_K_IB_B_IMU_meas_radDs */
      0.0,                             /* w_y_K_IB_B_IMU_meas_radDs */
      0.0                              /* w_z_K_IB_B_IMU_meas_radDs */
    },                                 /* gyro_meas */

    { 0.0,                             /* f_x_P_B_IMU_meas_mDs2 */
      0.0,                             /* f_y_P_B_IMU_meas_mDs2 */
      0.0                              /* f_z_P_B_IMU_meas_mDs2 */
    }                                  /* acc_meas */
  },                                   /* imu_meas */

  { { 0.0,                             /* lambda_R_WGS84_meas_rad */
      0.0,                             /* mue_R_WGS84_meas_rad */
      0.0                              /* h_R_WGS84_meas_m */
    },                                 /* pos_R_WGS84_meas */

    { 0.0,                             /* x_R_O_meas_m */
      0.0,                             /* y_R_O_meas_m */
      0.0                              /* z_R_O_meas_m */
    },                                 /* pos_R_local_meas */

    { 0.0,                             /* u_K_R_E_O_meas_mDs */
      0.0,                             /* v_K_R_E_O_meas_mDs */
      0.0                              /* w_K_R_E_O_meas_mDs */
    },                                 /* vel_K_R_E_O_meas */

    { 0.0,                             /* vel_K_R_abs_meas_mDs */
      { 0.0,                           /* gamma_K_R_meas_rad */
        0.0                            /* chi_K_R_meas_rad */
      }                                /* path_K_R_meas_rad */
    }                                  /* Translation_K_R_meas */
  },                                   /* gps_meas */

  { 0.0,                               /* Phi_meas_rad */
    0.0,                               /* Theta_meas_rad */
    0.0,                               /* Psi_meas_rad */

    { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 },/* M_BO_meas */

    { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 }/* M_OB_meas */
  },                                   /* ahrs_meas */

  { 0.0,                               /* w1_meas_radDs */
    0.0,                               /* w2_meas_radDs */
    0.0,                               /* w3_meas_radDs */
    0.0,                               /* w4_meas_radDs */
    0.0,                               /* w5_meas_radDs */
    0.0,                               /* w6_meas_radDs */
    0.0,                               /* w7_meas_radDs */
    0.0                                /* w8_meas_radDs */
  },                                   /* motor_meas */

  { 0.0                                /* wow_switch_1_meas */
  }                                    /* switches_meas */
};

const Simulation_Control_Bus
  RMT_FDM_DLL_FrameWork_FCS_RT_rtZSimulation_Control_Bus = { false,/* flg_Reset */
  false,                               /* flg_Run */
  false,                               /* flg_Run_p */
  false,                               /* flg_Run_q */
  false,                               /* flg_Run_r */
  false,                               /* flg_Run_Phi */
  false,                               /* flg_Run_Theta */
  false,                               /* flg_Run_Psi */
  false,                               /* flg_Run_vel_x */
  false,                               /* flg_Run_vel_y */
  false,                               /* flg_Run_vel_z */
  false,                               /* flg_Run_pos_x */
  false,                               /* flg_Run_pos_y */
  false,                               /* flg_Run_pos_z */
  false,                               /* flg_Propulsion_On */
  false,                               /* flg_Aerodynamics_On */
  false,                               /* flg_Weight_Balance_On */
  false,                               /* flg_Ground_Contacts_On */
  false,                               /* flg_Enable_Sensor_Errors */
  false                                /* flg_Enable_Controller */
};

const States_Init_Bus RMT_FDM_DLL_FrameWork_FCS_RT_rtZStates_Init_Bus = { { 0.0,/* w_x_K_IB_B_radDs */
    0.0,                               /* w_y_K_IB_B_radDs */
    0.0                                /* w_z_K_IB_B_radDs */
  },                                   /* rot_K_IB_B_radDs */

  { 0.0,                               /* Phi_rad */
    0.0,                               /* Theta_rad */
    0.0                                /* Psi_rad */
  },                                   /* att_euler_rad */

  { 0.0,                               /* u_K_R_E_B_mDs */
    0.0,                               /* v_K_R_E_B_mDs */
    0.0                                /* w_K_R_E_B_mDs */
  },                                   /* vel_K_R_E_B_mDs */

  { 0.0,                               /* x_R_O_m */
    0.0,                               /* y_R_O_m */
    0.0                                /* z_R_O_m */
  },                                   /* pos_R_O_m */

  { 0.0,                               /* lambda_R_WGS84_rad */
    0.0,                               /* mue_R_WGS84_rad */
    0.0                                /* h_R_WGS84_m */
  },                                   /* pos_R_WGS84 */

  { { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 }/* u_0_radDs */
  }                                    /* actuator */
};

const Vehicle_Bus RMT_FDM_DLL_FrameWork_FCS_RT_rtZVehicle_Bus = { { { 0.0,/* w_x_K_IB_B_radDs */
      0.0,                             /* w_y_K_IB_B_radDs */
      0.0                              /* w_z_K_IB_B_radDs */
    },                                 /* rot_K_IB_B_radDs */

    { 0.0,                             /* Phi_rad */
      0.0,                             /* Theta_rad */
      0.0                              /* Psi_rad */
    },                                 /* att_euler_rad */

    { 0.0,                             /* u_K_R_E_B_mDs */
      0.0,                             /* v_K_R_E_B_mDs */
      0.0                              /* w_K_R_E_B_mDs */
    },                                 /* vel_K_R_E_B_mDs */

    { 0.0,                             /* x_R_O_m */
      0.0,                             /* y_R_O_m */
      0.0                              /* z_R_O_m */
    }                                  /* pos_R_O_m */
  },                                   /* States */

  { { { 0.0,                           /* u_dot_K_R_EB_B_mDs2 */
        0.0,                           /* v_dot_K_R_EB_B_mDs2 */
        0.0                            /* w_dot_K_R_EB_B_mDs2 */
      },                               /* vel_dot_K_R_EB_B_mDs2 */

      { 0.0,                           /* w_x_dot_K_IB_B_B_radDs2 */
        0.0,                           /* w_y_dot_K_IB_B_B_radDs2 */
        0.0                            /* w_z_dot_K_IB_B_B_radDs2 */
      },                               /* rot_dot_K_IB_B_B_radDs2 */

      { 0.0,                           /* Phi_dot_radDs */
        0.0,                           /* Theta_dot_radDs */
        0.0                            /* Psi_dot_radDs */
      },                               /* att_dot_euler_radDs */

      { 0.0,                           /* x_dot_R_E_O_mDs */
        0.0,                           /* y_dot_R_E_O_mDs */
        0.0                            /* z_dot_R_E_O_mDs */
      }                                /* pos_dot_R_E_O_mDs */
    },                                 /* States_Dot */

    { { { 0.0,                         /* X_T_R_B_N */
          0.0,                         /* Y_T_R_B_N */
          0.0                          /* Z_P_R_B_N */
        },                             /* for_T_R_B_N */

        { 0.0,                         /* L_T_R_B_Nm */
          0.0,                         /* M_T_R_B_Nm */
          0.0                          /* N_T_R_B_Nm */
        }                              /* mom_T_R_B_Nm */
      },                               /* for_mom_T_R_B */

      { { { 0.0,                       /* X_P_R_B_N */
            0.0,                       /* Y_P_R_B_N */
            0.0                        /* Z_P_R_B_N */
          },                           /* for_P_R_B_N */

          { 0.0,                       /* L_P_R_B_Nm */
            0.0,                       /* M_P_R_B_Nm */
            0.0                        /* N_P_R_B_Nm */
          }                            /* mom_P_R_B_Nm */
        },                             /* for_mom_P_R_B */
        0.0                            /* Propulsion_Out */
      },                               /* Propulsion_Data_Out */

      { { 0.0,                         /* X_A_R_B_N */
          0.0,                         /* Y_A_R_B_N */
          0.0                          /* Z_A_R_B_N */
        },                             /* for_A_R_B_N */

        { 0.0,                         /* L_A_R_B_Nm */
          0.0,                         /* M_A_R_B_Nm */
          0.0                          /* N_A_R_B_Nm */
        }                              /* mom_A_R_B_Nm */
      },                               /* for_mom_A_R_B */

      { { 0.0,                         /* X_LDG_R_B_N */
          0.0,                         /* Y_LDG_R_B_N */
          0.0                          /* Z_LDG_R_B_N */
        },                             /* for_LDG_R_B_N */

        { 0.0,                         /* L_LDG_R_B_Nm */
          0.0,                         /* M_LDG_R_B_Nm */
          0.0                          /* N_LDG_R_B_Nm */
        }                              /* mom_LDG_R_B_Nm */
      },                               /* for_mom_LDG_R_B */

      { { 0.0,                         /* X_G_R_B_N */
          0.0,                         /* Y_G_R_B_N */
          0.0                          /* Z_G_R_B_N */
        },                             /* for_G_R_B_N */

        { 0.0,                         /* L_G_R_B_Nm */
          0.0,                         /* M_G_R_B_Nm */
          0.0                          /* N_G_R_B_Nm */
        }                              /* mom_G_R_B_Nm */
      },                               /* for_mom_G_R_B */

      { { 0.0, 0.0, 0.0 },             /* pos_RG_B_m */
        0.0,                           /* m_kg */

        { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 }/* I_R_BB_kgm2 */
      }                                /* Weight_Balance */
    },                                 /* Airframe_Outputs */

    { { 0.0,                           /* Static_Temperature_ATM_K */
        0.0,                           /* Speed_of_Sound_mDs */
        0.0,                           /* Static_Pressure_ATM_NDm2 */
        0.0                            /* rho_kgDm3 */
      },                               /* Atmosphere */

      { { 0.0, 0.0, 0.0 }              /* acc_G_R_OO_O_mDs2 */
      }                                /* Gravitation */
    },                                 /* Environment */

    { { { 0.0,                         /* w_x_K_IB_B_radDs */
          0.0,                         /* w_y_K_IB_B_radDs */
          0.0                          /* w_z_K_IB_B_radDs */
        },                             /* rot_K_IB_B_radDs */

        { 0.0,                         /* u_K_R_E_B_mDs */
          0.0,                         /* v_K_R_E_B_mDs */
          0.0                          /* w_K_R_E_B_mDs */
        },                             /* vel_K_R_E_B_mDs */

        { 0.0,                         /* w_x_K_EB_B_radDs */
          0.0,                         /* w_y_K_EB_B_radDs */
          0.0                          /* w_z_K_EB_B_radDs */
        },                             /* rot_K_EB_B_radDs */

        { 0.0,                         /* w_x_K_OB_B_radDs */
          0.0,                         /* w_y_K_OB_B_radDs */
          0.0                          /* w_z_K_OB_B_radDs */
        },                             /* rot_K_OB_B_radDs */

        { { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 },/* M_BO */

          { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 },/* M_OB */

          { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 },/* M_NO */

          { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 }/* M_ON */
        }                              /* Kin_Trafo_Matrices */
      },                               /* Kinematic_Data */

      { { { 0.0,                       /* u_A_R_E_0_mDs */
            0.0,                       /* v_A_R_E_0_mDs */
            0.0                        /* w_A_R_E_0_mDs */
          },                           /* vel_A_R_E_0_mDs */

          { 0.0,                       /* u_A_R_E_B_mDs */
            0.0,                       /* v_A_R_E_B_mDs */
            0.0                        /* w_A_R_E_B_mDs */
          }                            /* vel_A_R_E_B_mDs */
        },                             /* Aero_Velocities */

        { 0.0,                         /* VEL_A_R_abs_mDs */
          0.0,                         /* alpha_A_R_rad */
          0.0                          /* beta_A_R_rad */
        },                             /* Translation_A_R */

        { { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 },/* M_BS */

          { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 },/* M_SB */

          { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 },/* M_BA */

          { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 },/* M_AB */

          { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 },/* M_AO */

          { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 }/* M_OA */
        },                             /* Aero_Trafo_Matrices */

        { { 0.0,                       /* w_x_A_AB_B_radDs */
            0.0,                       /* w_y_A_AB_B_radDs */
            0.0                        /* w_z_A_AB_B_radDs */
          },                           /* rot_A_AB_B_radDs */

          { 0.0,                       /* w_x_A_AB_A_radDs */
            0.0,                       /* w_y_A_AB_A_radDs */
            0.0                        /* w_z_A_AB_A_radDs */
          },                           /* rot_A_AB_A_radDs */

          { 0.0,                       /* w_x_A_AB_S_radDs */
            0.0,                       /* w_y_A_AB_S_radDs */
            0.0                        /* w_z_A_AB_S_radDs */
          }                            /* rot_A_AB_S_radDs */
        }                              /* Aero_Angular_Rates */
      },                               /* Airdata */

      { { { 0.0,                       /* u_W_R_E_B_mDs */
            0.0,                       /* v_W_R_E_B_mDs */
            0.0                        /* w_W_R_E_B_mDs */
          },                           /* vel_W_R_E_B_mDs */

          { 0.0,                       /* u_W_R_E_O_mDs */
            0.0,                       /* v_W_R_E_O_mDs */
            0.0                        /* w_W_R_E_O_mDs */
          }                            /* vel_W_R_E_O_mDs */
        },                             /* Wind_Velocities */

        { { 0.0,                       /* w_x_W_0W_0_radDs */
            0.0,                       /* w_y_W_0W_0_radDs */
            0.0                        /* w_z_W_0W_0_radDs */
          },                           /* rot_W_0W_0_radDs */

          { 0.0,                       /* w_x_W_OW_B_radDs */
            0.0,                       /* w_y_W_OW_B_radDs */
            0.0                        /* w_z_W_OW_B_radDs */
          }                            /* rot_W_OW_B_radDs */
        }                              /* Wind_Angular_Rates */
      }                                /* Wind_Data */
    }                                  /* Motion_Kinematics */
  },                                   /* Outputs */

  { 0.0,                               /* w1_act_radDs */
    0.0,                               /* w2_act_radDs */
    0.0,                               /* w3_act_radDs */
    0.0,                               /* w4_act_radDs */
    0.0,                               /* w5_act_radDs */
    0.0,                               /* w6_act_radDs */
    0.0,                               /* w7_act_radDs */
    0.0                                /* w8_act_radDs */
  }                                    /* Commands */
};

const fc_est_Bus RMT_FDM_DLL_FrameWork_FCS_RT_rtZfc_est_Bus = { { 0.0,/* u_K_R_E_C_est_mDs */
    0.0,                               /* v_K_R_E_C_est_mDs */
    0.0                                /* w_K_R_E_C_est_mDs */
  },                                   /* vel_est */

  { 0.0,                               /* u_dot_K_R_EC_C_est_mDs2 */
    0.0,                               /* v_dot_K_R_EC_C_est_mDs2 */
    0.0                                /* w_dot_K_R_EC_C_est_mDs2 */
  },                                   /* vel_dot_es */

  { 0.0,                               /* p_est_radDs */
    0.0,                               /* q_est_radDs */
    0.0                                /* r_est_radDs */
  },                                   /* rate_est */

  { 0.0,                               /* p_Dot_est_radDs2 */
    0.0,                               /* q_Dot_est_radDs2 */
    0.0                                /* r_Dot_est_radDs2 */
  },                                   /* rate_dot_est */

  { 0.0,                               /* Phi_est_rad */
    0.0,                               /* Theta_est_rad */
    0.0                                /* Psi_Dot_est_radDs */
  }                                    /* att_est */
};

const fc_pilot_cmd_Bus RMT_FDM_DLL_FrameWork_FCS_RT_rtZfc_pilot_cmd_Bus = { 0.0,/* w_y_D_cmd_radDs */
  { 0.0,                               /* u_K_R_E_C_cmd_mDs */
    0.0,                               /* v_K_R_E_C_cmd_mDs */
    0.0                                /* w_K_R_E_C_cmd_mDs */
  },                                   /* vel_K_R_E_C_cmd_mDs */

  { 0.0,                               /* Phi_cmd_rad */
    0.0,                               /* Theta_cmd_rad */
    0.0                                /* Psi_dot_cmd_radDs */
  },                                   /* att_euler_cmd */
  false,                               /* vel_att_mode_swi */
  false,                               /* arm_swi */
  false,                               /* override_swi */
  false,                               /* power_swi */
  false                                /* rotor_start_swi */
};

/*
 *         This function updates active task flag for each subrate.
 *         The function is called at model base rate, hence the
 *         generated code self-manages all its subrates.
 */
static void rate_scheduler(RT_MODEL_RMT_FDM_DLL_FrameWork_FCS_RT_T *const
  RMT_FDM_DLL_FrameWork_FCS_RT_M)
{
  /* Compute which subrates run during the next base time step.  Subrates
   * are an integer multiple of the base rate counter.  Therefore, the subtask
   * counter is reset when it reaches its limit (zero means run).
   */
  (RMT_FDM_DLL_FrameWork_FCS_RT_M->Timing.TaskCounters.TID[2])++;
  if ((RMT_FDM_DLL_FrameWork_FCS_RT_M->Timing.TaskCounters.TID[2]) > 49) {/* Sample time: [0.2s, 0.0s] */
    RMT_FDM_DLL_FrameWork_FCS_RT_M->Timing.TaskCounters.TID[2] = 0;
  }
}

/*
 * This function updates continuous states using the ODE4 fixed-step
 * solver algorithm
 */
static void rt_ertODEUpdateContinuousStates(RTWSolverInfo *si ,
  RT_MODEL_RMT_FDM_DLL_FrameWork_FCS_RT_T *const RMT_FDM_DLL_FrameWork_FCS_RT_M,
  Simulation_Control_Bus *RMT_FDM_DLL_FrameWork_FCS_RT_U_Simulation_Control,
  States_Init_Bus *RMT_FDM_DLL_FrameWork_FCS_RT_U_States_Init, real_T
  RMT_FDM_DLL_FrameWork_FCS_RT_U_w_cmd_radDs[8], fc_pilot_cmd_Bus
  *RMT_FDM_DLL_FrameWork_FCS_RT_U_fc_pilot_cmd, Failure_Bus
  *RMT_FDM_DLL_FrameWork_FCS_RT_U_Failures, Vehicle_Bus
  *RMT_FDM_DLL_FrameWork_FCS_RT_Y_Vehicle, Measurements_Bus
  *RMT_FDM_DLL_FrameWork_FCS_RT_Y_Measurements, fc_est_Bus
  *RMT_FDM_DLL_FrameWork_FCS_RT_Y_fc_estimation)
{
  time_T t = rtsiGetT(si);
  time_T tnew = rtsiGetSolverStopTime(si);
  time_T h = rtsiGetStepSize(si);
  real_T *x = rtsiGetContStates(si);
  ODE4_IntgData *id = (ODE4_IntgData *)rtsiGetSolverData(si);
  real_T *y = id->y;
  real_T *f0 = id->f[0];
  real_T *f1 = id->f[1];
  real_T *f2 = id->f[2];
  real_T *f3 = id->f[3];
  real_T temp;
  int_T i;
  int_T nXc = 62;
  rtsiSetSimTimeStep(si,MINOR_TIME_STEP);

  /* Save the state values at time t in y, we'll use x as ynew. */
  (void) memcpy(y, x,
                (uint_T)nXc*sizeof(real_T));

  /* Assumes that rtsiSetT and ModelOutputs are up-to-date */
  /* f0 = f(t,y) */
  rtsiSetdX(si, f0);
  RMT_FDM_DLL_FrameWork_FCS_RT_derivatives(RMT_FDM_DLL_FrameWork_FCS_RT_M);

  /* f1 = f(t + (h/2), y + (h/2)*f0) */
  temp = 0.5 * h;
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (temp*f0[i]);
  }

  rtsiSetT(si, t + temp);
  rtsiSetdX(si, f1);
  RMT_FDM_DLL_FrameWork_FCS_RT_step(RMT_FDM_DLL_FrameWork_FCS_RT_M,
    RMT_FDM_DLL_FrameWork_FCS_RT_U_Simulation_Control,
    RMT_FDM_DLL_FrameWork_FCS_RT_U_States_Init,
    RMT_FDM_DLL_FrameWork_FCS_RT_U_w_cmd_radDs,
    RMT_FDM_DLL_FrameWork_FCS_RT_U_fc_pilot_cmd,
    RMT_FDM_DLL_FrameWork_FCS_RT_U_Failures,
    RMT_FDM_DLL_FrameWork_FCS_RT_Y_Vehicle,
    RMT_FDM_DLL_FrameWork_FCS_RT_Y_Measurements,
    RMT_FDM_DLL_FrameWork_FCS_RT_Y_fc_estimation);
  RMT_FDM_DLL_FrameWork_FCS_RT_derivatives(RMT_FDM_DLL_FrameWork_FCS_RT_M);

  /* f2 = f(t + (h/2), y + (h/2)*f1) */
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (temp*f1[i]);
  }

  rtsiSetdX(si, f2);
  RMT_FDM_DLL_FrameWork_FCS_RT_step(RMT_FDM_DLL_FrameWork_FCS_RT_M,
    RMT_FDM_DLL_FrameWork_FCS_RT_U_Simulation_Control,
    RMT_FDM_DLL_FrameWork_FCS_RT_U_States_Init,
    RMT_FDM_DLL_FrameWork_FCS_RT_U_w_cmd_radDs,
    RMT_FDM_DLL_FrameWork_FCS_RT_U_fc_pilot_cmd,
    RMT_FDM_DLL_FrameWork_FCS_RT_U_Failures,
    RMT_FDM_DLL_FrameWork_FCS_RT_Y_Vehicle,
    RMT_FDM_DLL_FrameWork_FCS_RT_Y_Measurements,
    RMT_FDM_DLL_FrameWork_FCS_RT_Y_fc_estimation);
  RMT_FDM_DLL_FrameWork_FCS_RT_derivatives(RMT_FDM_DLL_FrameWork_FCS_RT_M);

  /* f3 = f(t + h, y + h*f2) */
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (h*f2[i]);
  }

  rtsiSetT(si, tnew);
  rtsiSetdX(si, f3);
  RMT_FDM_DLL_FrameWork_FCS_RT_step(RMT_FDM_DLL_FrameWork_FCS_RT_M,
    RMT_FDM_DLL_FrameWork_FCS_RT_U_Simulation_Control,
    RMT_FDM_DLL_FrameWork_FCS_RT_U_States_Init,
    RMT_FDM_DLL_FrameWork_FCS_RT_U_w_cmd_radDs,
    RMT_FDM_DLL_FrameWork_FCS_RT_U_fc_pilot_cmd,
    RMT_FDM_DLL_FrameWork_FCS_RT_U_Failures,
    RMT_FDM_DLL_FrameWork_FCS_RT_Y_Vehicle,
    RMT_FDM_DLL_FrameWork_FCS_RT_Y_Measurements,
    RMT_FDM_DLL_FrameWork_FCS_RT_Y_fc_estimation);
  RMT_FDM_DLL_FrameWork_FCS_RT_derivatives(RMT_FDM_DLL_FrameWork_FCS_RT_M);

  /* tnew = t + h
     ynew = y + (h/6)*(f0 + 2*f1 + 2*f2 + 2*f3) */
  temp = h / 6.0;
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + temp*(f0[i] + 2.0*f1[i] + 2.0*f2[i] + f3[i]);
  }

  rtsiSetSimTimeStep(si,MAJOR_TIME_STEP);
}

/* Model step function */
void RMT_FDM_DLL_FrameWork_FCS_RT_step(RT_MODEL_RMT_FDM_DLL_FrameWork_FCS_RT_T *
  const RMT_FDM_DLL_FrameWork_FCS_RT_M, Simulation_Control_Bus
  *RMT_FDM_DLL_FrameWork_FCS_RT_U_Simulation_Control, States_Init_Bus
  *RMT_FDM_DLL_FrameWork_FCS_RT_U_States_Init, real_T
  RMT_FDM_DLL_FrameWork_FCS_RT_U_w_cmd_radDs[8], fc_pilot_cmd_Bus
  *RMT_FDM_DLL_FrameWork_FCS_RT_U_fc_pilot_cmd, Failure_Bus
  *RMT_FDM_DLL_FrameWork_FCS_RT_U_Failures, Vehicle_Bus
  *RMT_FDM_DLL_FrameWork_FCS_RT_Y_Vehicle, Measurements_Bus
  *RMT_FDM_DLL_FrameWork_FCS_RT_Y_Measurements, fc_est_Bus
  *RMT_FDM_DLL_FrameWork_FCS_RT_Y_fc_estimation)
{
  B_RMT_FDM_DLL_FrameWork_FCS_RT_T *RMT_FDM_DLL_FrameWork_FCS_RT_B =
    RMT_FDM_DLL_FrameWork_FCS_RT_M->ModelData.blockIO;
  DW_RMT_FDM_DLL_FrameWork_FCS_RT_T *RMT_FDM_DLL_FrameWork_FCS_RT_DW =
    RMT_FDM_DLL_FrameWork_FCS_RT_M->ModelData.dwork;
  X_RMT_FDM_DLL_FrameWork_FCS_RT_T *RMT_FDM_DLL_FrameWork_FCS_RT_X =
    RMT_FDM_DLL_FrameWork_FCS_RT_M->ModelData.contStates;
  PrevZCX_RMT_FDM_DLL_FrameWork_FCS_RT_T *RMT_FDM_DLL_FrameWork_FCS_RT_PrevZCX =
    RMT_FDM_DLL_FrameWork_FCS_RT_M->ModelData.prevZCSigState;

  /* local block i/o variables */
  fc_pilot_cmd_Bus b_Switch;
  Controller_Commands_Bus b_BusAssignment_eew0;
  RM_vel_Bus b_BusAssignment_gwea;
  att_est_Bus b_BusConversion_InsertedFor_BusAssignment_at_inport_3_BusCreator;
  fc_RM_Bus b_fc_RM;
  fc_ctrl_cmd_Bus b_fc_ctrl_cmd;
  fc_est_Bus b_BusAssignment;
  fc_measurements_Bus b_fc_measurements;
  fc_pilot_cmd_Bus b_BusAssignment1;
  fc_pilot_cmd_Bus b_Switch_gbzj;
  real_T N_M_tmp_data[100];
  real_T V_0[100];
  real_T A[60];
  real_T B[60];
  real_T B_0[60];
  real_T U[60];
  real_T W_0[60];
  real_T X[60];
  real_T b_nu_r[60];
  real_T b_N_M[40];
  real_T V[36];
  real_T a__1[36];
  real_T varargin_1_data[18];
  real_T y_data[18];
  real_T U_0[16];
  real_T V_1[16];
  real_T b_Product6[16];
  real_T b_X[16];
  real_T b_N_M_0[10];
  real_T b_Product1[10];
  real_T b_Saturation[10];
  real_T b_s_data[10];
  real_T b_u[10];
  real_T idx_insult_max_tmp_data[10];
  real_T idx_insult_min_tmp_data[10];
  real_T minval[10];
  real_T u_tmp[10];
  real_T b_M_BO[9];
  real_T b_Reshape1_kwvo[9];
  real_T b_VectorConcatenate_dvzb[9];
  real_T b_VectorConcatenate_dvzb_0[9];
  real_T b_VectorConcatenate_htsf[9];
  real_T b_VectorConcatenate_itjq[9];
  real_T b_VectorConcatenate_itjq_0[9];
  real_T b_VectorConcatenate_kzgt[9];
  real_T b_VectorConcatenate_kzgt_0[9];
  real_T b_VectorConcatenate_ls3d[9];
  real_T b_VectorConcatenate_p0sg[9];
  real_T scaling_max_data[9];
  real_T scaling_min_data[9];
  real_T tmp[9];
  real_T tmp_3[9];
  real_T b_w_cmd_INDI_radDs[8];
  real_T b_delta_nu[6];
  real_T b_nu_est[6];
  real_T b_nu_ref[6];
  real_T nu[6];
  real_T nu_tmp[6];
  real_T s[6];
  real_T s_0[6];
  real_T b_VectorConcatenate_c4eb[4];
  real_T b_X_0[4];
  real_T s_1[4];
  real_T tmp_4[4];
  real_T tmp_5[4];
  real_T tmp_6[4];
  real_T b_Diff[3];
  real_T b_Product4[3];
  real_T b_Reshape[3];
  real_T b_Reshape1_bgqi[3];
  real_T b_Reshape1_km21[3];
  real_T b_Reshape1_kwvo_0[3];
  real_T b_Reshape2[3];
  real_T b_Reshape2_dywf[3];
  real_T b_Reshape2_fzce[3];
  real_T b_Reshape2_izpf[3];
  real_T b_Reshape2_k1zx[3];
  real_T b_Reshape3[3];
  real_T b_Reshape_emto[3];
  real_T b_Reshape_m3a1[3];
  real_T b_Reshape_pne4[3];
  real_T b_Sum1_kkm0[3];
  real_T b_Sum_ihvy[3];
  real_T b_TSamp[3];
  real_T b_VectorConcatenate1[3];
  real_T b_VectorConcatenate1_aieq[3];
  real_T b_VectorConcatenate1_fuwu[3];
  real_T b_VectorConcatenate1_kxda[3];
  real_T b_VectorConcatenate2[3];
  real_T b_VectorConcatenate2_fdcl[3];
  real_T b_VectorConcatenate2_it5a[3];
  real_T b_VectorConcatenate2_jjfd[3];
  real_T b_VectorConcatenate2_kz0u[3];
  real_T b_VectorConcatenate_dmot[3];
  real_T b_VectorConcatenate_eemv[3];
  real_T b_VectorConcatenate_fye3[3];
  real_T b_VectorConcatenate_gvog[3];
  real_T b_VectorConcatenate_iw4s[3];
  real_T b_VectorConcatenate_kzgt_1[3];
  real_T b_VectorConcatenate_np2w[3];
  real_T b_VectorConcatenate_p0sg_0[3];
  real_T b_VectorConcatenate_pt2w[3];
  real_T tmp_0[3];
  real_T tmp_1[3];
  real_T tmp_2[3];
  real_T b_Sum1_kku3[2];
  real_T b_Sum_ndgx[2];
  real_T b_VectorConcatenate1_j0rp[2];
  real_T b_VectorConcatenate1_o2ke[2];
  real_T a;
  real_T a_0;
  real_T absx;
  real_T absx_0;
  real_T absx_1;
  real_T b_Gain1_il4c;
  real_T b_Gain1_j3wv;
  real_T b_Gain2;
  real_T b_Gain21;
  real_T b_Gain7;
  real_T b_Product4_tmp;
  real_T b_Product4_tmp_0;
  real_T b_Product4_tmp_1;
  real_T b_Product4_tmp_2;
  real_T b_Reshape1_kwvo_tmp;
  real_T b_Sum1;
  real_T b_Sum1_o2dx;
  real_T b_Sum2;
  real_T b_Sum2_b2z0;
  real_T b_Sum5_odvj;
  real_T b_Switch2;
  real_T b_Switch2_gt5e;
  real_T b_Switch_h4q0;
  real_T b_Switch_ljfr;
  real_T b_TrigonometricFunction1_hmbf;
  real_T b_TrigonometricFunction_hrln;
  real_T b_absx;
  real_T b_absx_0;
  real_T b_b;
  real_T b_du_C_EC_mDs2;
  real_T b_dv_C_EC_mDs;
  real_T b_dw_C_EC_mDs;
  real_T b_nu_limit;
  real_T b_nu_limit_abb3;
  real_T b_nu_limit_occu;
  real_T b_p_Ref_o2;
  real_T b_p_Ref_radDs;
  real_T b_r;
  real_T b_r_0;
  real_T b_r_1;
  real_T b_u_K_R_E_C_est_mDs;
  real_T b_v_C_ref_mDs;
  real_T b_v_K_R_E_C_est_mDs;
  real_T b_w_K_R_E_C_est_mDs;
  real_T b_x;
  real_T b_x_0;
  real_T b_x_1;
  real_T d_x;
  real_T d_x_0;
  real_T ex;
  real_T tol;
  real_T tol_0;
  real_T tol_1;
  real_T u0;
  real_T u0_0;
  real_T u1;
  real_T u2;
  real_T y_0;
  int32_T tmp_data[10];
  int32_T tmp_data_0[10];
  int32_T ar;
  int32_T ar_0;
  int32_T b;
  int32_T b_cr;
  int32_T b_cr_0;
  int32_T b_exponent;
  int32_T b_exponent_0;
  int32_T b_ic;
  int32_T b_ic_0;
  int32_T b_idx_0;
  int32_T b_j;
  int32_T b_k;
  int32_T b_k_0;
  int32_T b_k_1;
  int32_T br;
  int32_T br_0;
  int32_T c_j;
  int32_T c_k;
  int32_T c_k_0;
  int32_T cr;
  int32_T cr_0;
  int32_T d;
  int32_T d_0;
  int32_T d_1;
  int32_T d_k;
  int32_T d_k_0;
  int32_T d_k_1;
  int32_T e;
  int32_T e_0;
  int32_T e_k;
  int32_T e_k_0;
  int32_T end;
  int32_T end_0;
  int32_T exponent;
  int32_T exponent_0;
  int32_T exponent_1;
  int32_T f;
  int32_T f_0;
  int32_T f_k;
  int32_T f_k_0;
  int32_T g;
  int32_T g_0;
  int32_T g_1;
  int32_T g_k;
  int32_T h;
  int32_T h_0;
  int32_T h_k;
  int32_T h_k_0;
  int32_T i;
  int32_T i_0;
  int32_T i_1;
  int32_T i_10;
  int32_T i_11;
  int32_T i_12;
  int32_T i_13;
  int32_T i_14;
  int32_T i_15;
  int32_T i_16;
  int32_T i_17;
  int32_T i_18;
  int32_T i_19;
  int32_T i_1a;
  int32_T i_1b;
  int32_T i_1c;
  int32_T i_1d;
  int32_T i_1e;
  int32_T i_1f;
  int32_T i_1g;
  int32_T i_1h;
  int32_T i_1i;
  int32_T i_1j;
  int32_T i_1k;
  int32_T i_1l;
  int32_T i_1m;
  int32_T i_1n;
  int32_T i_1o;
  int32_T i_1p;
  int32_T i_1q;
  int32_T i_1r;
  int32_T i_1s;
  int32_T i_1t;
  int32_T i_1u;
  int32_T i_1v;
  int32_T i_1w;
  int32_T i_1x;
  int32_T i_1y;
  int32_T i_1z;
  int32_T i_2;
  int32_T i_20;
  int32_T i_21;
  int32_T i_22;
  int32_T i_23;
  int32_T i_24;
  int32_T i_25;
  int32_T i_26;
  int32_T i_27;
  int32_T i_28;
  int32_T i_29;
  int32_T i_2a;
  int32_T i_2b;
  int32_T i_2c;
  int32_T i_2d;
  int32_T i_2e;
  int32_T i_2f;
  int32_T i_2g;
  int32_T i_2h;
  int32_T i_2i;
  int32_T i_2j;
  int32_T i_2k;
  int32_T i_2l;
  int32_T i_2m;
  int32_T i_2n;
  int32_T i_2o;
  int32_T i_2p;
  int32_T i_2q;
  int32_T i_2r;
  int32_T i_2s;
  int32_T i_2t;
  int32_T i_2u;
  int32_T i_2v;
  int32_T i_2w;
  int32_T i_2x;
  int32_T i_2y;
  int32_T i_2z;
  int32_T i_3;
  int32_T i_30;
  int32_T i_31;
  int32_T i_32;
  int32_T i_33;
  int32_T i_34;
  int32_T i_35;
  int32_T i_36;
  int32_T i_37;
  int32_T i_38;
  int32_T i_39;
  int32_T i_3a;
  int32_T i_3b;
  int32_T i_3c;
  int32_T i_3d;
  int32_T i_3e;
  int32_T i_3f;
  int32_T i_3g;
  int32_T i_3h;
  int32_T i_3i;
  int32_T i_3j;
  int32_T i_3k;
  int32_T i_3l;
  int32_T i_3m;
  int32_T i_4;
  int32_T i_5;
  int32_T i_6;
  int32_T i_7;
  int32_T i_8;
  int32_T i_9;
  int32_T i_a;
  int32_T i_b;
  int32_T i_c;
  int32_T i_d;
  int32_T i_e;
  int32_T i_f;
  int32_T i_g;
  int32_T i_h;
  int32_T i_i;
  int32_T i_j;
  int32_T i_k;
  int32_T i_l;
  int32_T i_m;
  int32_T i_n;
  int32_T i_o;
  int32_T i_p;
  int32_T i_q;
  int32_T i_r;
  int32_T i_s;
  int32_T i_t;
  int32_T i_u;
  int32_T i_v;
  int32_T i_w;
  int32_T i_x;
  int32_T i_y;
  int32_T i_z;
  int32_T ia;
  int32_T ia_0;
  int32_T ib;
  int32_T ib_0;
  int32_T idx;
  int32_T j;
  int32_T j_k;
  int32_T k;
  int32_T k_0;
  int32_T k_1;
  int32_T l;
  int32_T last;
  int32_T loop_ub;
  int32_T loop_ub_0;
  int32_T loop_ub_1;
  int32_T loop_ub_2;
  int32_T loop_ub_3;
  int32_T loop_ub_4;
  int32_T loop_ub_5;
  int32_T m;
  int32_T r;
  int32_T r_0;
  int32_T r_1;
  int32_T vcol;
  int32_T vcol_0;
  boolean_T W[100];
  boolean_T b_Product1_0[10];
  boolean_T b_VectorConcatenate_mbmr[10];
  boolean_T ls[10];
  boolean_T sf[10];
  boolean_T tmp_7[10];
  boolean_T us[10];
  boolean_T b_p;
  boolean_T b_p_0;
  boolean_T b_y;
  boolean_T n;
  boolean_T p;
  boolean_T p_0;
  boolean_T p_1;
  boolean_T y;
  static real_T e_1[100] = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 };

  static const real_T o[60] = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0 };

  static const int32_T f_1[4] = { 0, 1, 2, 3 };

  static const real_T l_0[16] = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 };

  static real_T m_0[4] = { 0.0, 0.0, 0.0, 0.0 };

  real_T b_du_C_EC_mDs2_tmp;
  real_T b_du_C_EC_mDs2_tmp_0;
  real_T b_dv_C_EC_mDs_tmp;
  real_T b_v_K_R_E_C_est_mDs_tmp;
  real_T b_v_K_R_E_C_est_mDs_tmp_0;
  real_T b_v_K_R_E_C_est_mDs_tmp_1;
  real_T tmp_8;
  real_T tmp_9;
  real_T tmp_a;
  real_T tmp_b;
  real_T tmp_c;
  int32_T N_M_tmp_size[2];
  int32_T B_tmp;
  int32_T W_tmp;
  int32_T b_M_BO_tmp;
  int32_T b_Product6_tmp;
  int32_T b_VectorConcatenate_dvzb_tmp;
  int32_T b_VectorConcatenate_itjq_tmp;
  int32_T b_VectorConcatenate_kzgt_tmp;
  int32_T b_nu_r_tmp;
  int32_T b_nu_r_tmp_0;
  int32_T b_s_size;
  int32_T scaling_max_data_tmp;
  int32_T scaling_min_data_tmp;
  int32_T tmp_size;
  int32_T tmp_size_0;
  int32_T y_size;
  boolean_T exitg1;
  boolean_T exitg2;
  if (rtmIsMajorTimeStep(RMT_FDM_DLL_FrameWork_FCS_RT_M)) {
    /* set solver stop time */
    rtsiSetSolverStopTime(RMT_FDM_DLL_FrameWork_FCS_RT_M->solverInfo,
                          ((RMT_FDM_DLL_FrameWork_FCS_RT_M->Timing.clockTick0+1)*
      RMT_FDM_DLL_FrameWork_FCS_RT_M->Timing.stepSize0));
  }                                    /* end MajorTimeStep */

  /* Update absolute time of base rate at minor time step */
  if (rtmIsMinorTimeStep(RMT_FDM_DLL_FrameWork_FCS_RT_M)) {
    RMT_FDM_DLL_FrameWork_FCS_RT_M->Timing.t[0] = rtsiGetT
      (RMT_FDM_DLL_FrameWork_FCS_RT_M->solverInfo);
  }

  /* Outputs for Atomic SubSystem: '<Root>/FCS_INDI_Control' */
  /* MATLAB Function: '<S19>/Pseudoinverse' */
  m_0[0U] = (rtNaN);
  m_0[1U] = (rtNaN);
  m_0[2U] = (rtNaN);
  m_0[3U] = (rtNaN);

  /* MATLAB Function: '<S19>/nullspace' */
  e_1[0U] = (rtNaN);
  e_1[1U] = (rtNaN);
  e_1[2U] = (rtNaN);
  e_1[3U] = (rtNaN);
  e_1[4U] = (rtNaN);
  e_1[5U] = (rtNaN);
  e_1[6U] = (rtNaN);
  e_1[7U] = (rtNaN);
  e_1[8U] = (rtNaN);
  e_1[9U] = (rtNaN);
  e_1[10U] = (rtNaN);
  e_1[11U] = (rtNaN);
  e_1[12U] = (rtNaN);
  e_1[13U] = (rtNaN);
  e_1[14U] = (rtNaN);
  e_1[15U] = (rtNaN);
  e_1[16U] = (rtNaN);
  e_1[17U] = (rtNaN);
  e_1[18U] = (rtNaN);
  e_1[19U] = (rtNaN);
  e_1[20U] = (rtNaN);
  e_1[21U] = (rtNaN);
  e_1[22U] = (rtNaN);
  e_1[23U] = (rtNaN);
  e_1[24U] = (rtNaN);
  e_1[25U] = (rtNaN);
  e_1[26U] = (rtNaN);
  e_1[27U] = (rtNaN);
  e_1[28U] = (rtNaN);
  e_1[29U] = (rtNaN);
  e_1[30U] = (rtNaN);
  e_1[31U] = (rtNaN);
  e_1[32U] = (rtNaN);
  e_1[33U] = (rtNaN);
  e_1[34U] = (rtNaN);
  e_1[35U] = (rtNaN);
  e_1[36U] = (rtNaN);
  e_1[37U] = (rtNaN);
  e_1[38U] = (rtNaN);
  e_1[39U] = (rtNaN);
  e_1[40U] = (rtNaN);
  e_1[41U] = (rtNaN);
  e_1[42U] = (rtNaN);
  e_1[43U] = (rtNaN);
  e_1[44U] = (rtNaN);
  e_1[45U] = (rtNaN);
  e_1[46U] = (rtNaN);
  e_1[47U] = (rtNaN);
  e_1[48U] = (rtNaN);
  e_1[49U] = (rtNaN);
  e_1[50U] = (rtNaN);
  e_1[51U] = (rtNaN);
  e_1[52U] = (rtNaN);
  e_1[53U] = (rtNaN);
  e_1[54U] = (rtNaN);
  e_1[55U] = (rtNaN);
  e_1[56U] = (rtNaN);
  e_1[57U] = (rtNaN);
  e_1[58U] = (rtNaN);
  e_1[59U] = (rtNaN);
  e_1[60U] = (rtNaN);
  e_1[61U] = (rtNaN);
  e_1[62U] = (rtNaN);
  e_1[63U] = (rtNaN);
  e_1[64U] = (rtNaN);
  e_1[65U] = (rtNaN);
  e_1[66U] = (rtNaN);
  e_1[67U] = (rtNaN);
  e_1[68U] = (rtNaN);
  e_1[69U] = (rtNaN);
  e_1[70U] = (rtNaN);
  e_1[71U] = (rtNaN);
  e_1[72U] = (rtNaN);
  e_1[73U] = (rtNaN);
  e_1[74U] = (rtNaN);
  e_1[75U] = (rtNaN);
  e_1[76U] = (rtNaN);
  e_1[77U] = (rtNaN);
  e_1[78U] = (rtNaN);
  e_1[79U] = (rtNaN);
  e_1[80U] = (rtNaN);
  e_1[81U] = (rtNaN);
  e_1[82U] = (rtNaN);
  e_1[83U] = (rtNaN);
  e_1[84U] = (rtNaN);
  e_1[85U] = (rtNaN);
  e_1[86U] = (rtNaN);
  e_1[87U] = (rtNaN);
  e_1[88U] = (rtNaN);
  e_1[89U] = (rtNaN);
  e_1[90U] = (rtNaN);
  e_1[91U] = (rtNaN);
  e_1[92U] = (rtNaN);
  e_1[93U] = (rtNaN);
  e_1[94U] = (rtNaN);
  e_1[95U] = (rtNaN);
  e_1[96U] = (rtNaN);
  e_1[97U] = (rtNaN);
  e_1[98U] = (rtNaN);
  e_1[99U] = (rtNaN);

  /* End of Outputs for SubSystem: '<Root>/FCS_INDI_Control' */

  /* SignalConversion generated from: '<S7>/Vector Concatenate1' incorporates:
   *  Constant: '<S7>/Constant'
   */
  b_VectorConcatenate1[0] = 0.0;

  /* Trigonometry: '<S7>/Trigonometric Function' incorporates:
   *  Inport: '<Root>/States_Init'
   *  SignalConversion generated from: '<S2>/Vector Concatenate'
   */
  b_TrigonometricFunction1_hmbf = cos
    (RMT_FDM_DLL_FrameWork_FCS_RT_U_States_Init->att_euler_rad.Phi_rad);

  /* SignalConversion generated from: '<S7>/Vector Concatenate1' */
  b_VectorConcatenate1[1] = b_TrigonometricFunction1_hmbf;

  /* Trigonometry: '<S7>/Trigonometric Function1' incorporates:
   *  Inport: '<Root>/States_Init'
   *  SignalConversion generated from: '<S2>/Vector Concatenate'
   */
  b_TrigonometricFunction_hrln = sin
    (RMT_FDM_DLL_FrameWork_FCS_RT_U_States_Init->att_euler_rad.Phi_rad);

  /* SignalConversion generated from: '<S7>/Vector Concatenate1' */
  b_VectorConcatenate1[2] = b_TrigonometricFunction_hrln;

  /* SignalConversion generated from: '<S7>/Vector Concatenate2' incorporates:
   *  Constant: '<S7>/Constant'
   */
  b_VectorConcatenate2[0] = 0.0;

  /* Gain: '<S7>/Gain' */
  b_VectorConcatenate2[1] = -b_TrigonometricFunction_hrln;

  /* SignalConversion generated from: '<S7>/Vector Concatenate2' */
  b_VectorConcatenate2[2] = b_TrigonometricFunction1_hmbf;

  /* Trigonometry: '<S8>/Trigonometric Function' incorporates:
   *  Inport: '<Root>/States_Init'
   *  SignalConversion generated from: '<S2>/Vector Concatenate'
   */
  b_TrigonometricFunction_hrln = cos
    (RMT_FDM_DLL_FrameWork_FCS_RT_U_States_Init->att_euler_rad.Theta_rad);

  /* SignalConversion generated from: '<S8>/Vector Concatenate' */
  b_VectorConcatenate_fye3[0] = b_TrigonometricFunction_hrln;

  /* SignalConversion generated from: '<S8>/Vector Concatenate' incorporates:
   *  Constant: '<S8>/Constant'
   */
  b_VectorConcatenate_fye3[1] = 0.0;

  /* Trigonometry: '<S8>/Trigonometric Function1' incorporates:
   *  Inport: '<Root>/States_Init'
   *  SignalConversion generated from: '<S2>/Vector Concatenate'
   */
  b_TrigonometricFunction1_hmbf = sin
    (RMT_FDM_DLL_FrameWork_FCS_RT_U_States_Init->att_euler_rad.Theta_rad);

  /* Gain: '<S8>/Gain' */
  b_VectorConcatenate_fye3[2] = -b_TrigonometricFunction1_hmbf;

  /* SignalConversion generated from: '<S8>/Vector Concatenate2' */
  b_VectorConcatenate2_kz0u[0] = b_TrigonometricFunction1_hmbf;

  /* SignalConversion generated from: '<S8>/Vector Concatenate2' incorporates:
   *  Constant: '<S8>/Constant'
   */
  b_VectorConcatenate2_kz0u[1] = 0.0;

  /* SignalConversion generated from: '<S8>/Vector Concatenate2' */
  b_VectorConcatenate2_kz0u[2] = b_TrigonometricFunction_hrln;

  /* Trigonometry: '<S9>/Trigonometric Function' incorporates:
   *  Inport: '<Root>/States_Init'
   *  SignalConversion generated from: '<S2>/Vector Concatenate'
   */
  b_TrigonometricFunction_hrln = cos
    (RMT_FDM_DLL_FrameWork_FCS_RT_U_States_Init->att_euler_rad.Psi_rad);

  /* SignalConversion generated from: '<S9>/Vector Concatenate' */
  b_VectorConcatenate_dmot[0] = b_TrigonometricFunction_hrln;

  /* Trigonometry: '<S9>/Trigonometric Function1' incorporates:
   *  Inport: '<Root>/States_Init'
   *  SignalConversion generated from: '<S2>/Vector Concatenate'
   */
  b_TrigonometricFunction1_hmbf = sin
    (RMT_FDM_DLL_FrameWork_FCS_RT_U_States_Init->att_euler_rad.Psi_rad);

  /* SignalConversion generated from: '<S9>/Vector Concatenate' */
  b_VectorConcatenate_dmot[1] = b_TrigonometricFunction1_hmbf;

  /* SignalConversion generated from: '<S9>/Vector Concatenate' incorporates:
   *  Constant: '<S9>/Constant'
   */
  b_VectorConcatenate_dmot[2] = 0.0;

  /* Gain: '<S9>/Gain' */
  b_Reshape[0] = -b_TrigonometricFunction1_hmbf;

  /* SignalConversion generated from: '<S9>/Vector Concatenate1' */
  b_Reshape[1] = b_TrigonometricFunction_hrln;

  /* SignalConversion generated from: '<S9>/Vector Concatenate1' incorporates:
   *  Constant: '<S9>/Constant'
   */
  b_Reshape[2] = 0.0;

  /* Concatenate: '<S8>/Vector Concatenate3' incorporates:
   *  Concatenate: '<S8>/Vector Concatenate'
   *  Concatenate: '<S8>/Vector Concatenate1'
   *  Concatenate: '<S8>/Vector Concatenate2'
   */
  for (i_p = 0; i_p < 3; i_p = i_p + 1) {
    b_VectorConcatenate_dvzb[3 * i_p] = b_VectorConcatenate_fye3[i_p];
  }

  for (i_q = 0; i_q < 3; i_q = i_q + 1) {
    b_VectorConcatenate_dvzb[1 + 3 * i_q] =
      RMT_FDM_DLL_FrameWork_FCS_RT_ConstB.VectorConcatenate1[i_q];
  }

  for (i_r = 0; i_r < 3; i_r = i_r + 1) {
    b_VectorConcatenate_dvzb[2 + 3 * i_r] = b_VectorConcatenate2_kz0u[i_r];
  }

  /* End of Concatenate: '<S8>/Vector Concatenate3' */

  /* Concatenate: '<S9>/Vector Concatenate3' incorporates:
   *  Concatenate: '<S9>/Vector Concatenate'
   *  Concatenate: '<S9>/Vector Concatenate2'
   *  Reshape: '<S2>/Reshape'
   */
  for (i_s = 0; i_s < 3; i_s = i_s + 1) {
    b_VectorConcatenate_ls3d[3 * i_s] = b_VectorConcatenate_dmot[i_s];
  }

  for (i_t = 0; i_t < 3; i_t = i_t + 1) {
    b_VectorConcatenate_ls3d[1 + 3 * i_t] = b_Reshape[i_t];
  }

  for (i_u = 0; i_u < 3; i_u = i_u + 1) {
    b_VectorConcatenate_ls3d[2 + 3 * i_u] =
      RMT_FDM_DLL_FrameWork_FCS_RT_ConstB.VectorConcatenate2[i_u];
  }

  /* End of Concatenate: '<S9>/Vector Concatenate3' */

  /* Concatenate: '<S7>/Vector Concatenate3' incorporates:
   *  Concatenate: '<S7>/Vector Concatenate'
   *  Concatenate: '<S7>/Vector Concatenate1'
   *  Concatenate: '<S7>/Vector Concatenate2'
   */
  for (i_v = 0; i_v < 3; i_v = i_v + 1) {
    tmp[3 * i_v] = RMT_FDM_DLL_FrameWork_FCS_RT_ConstB.VectorConcatenate[i_v];
  }

  for (i_w = 0; i_w < 3; i_w = i_w + 1) {
    tmp[1 + 3 * i_w] = b_VectorConcatenate1[i_w];
  }

  for (i_x = 0; i_x < 3; i_x = i_x + 1) {
    tmp[2 + 3 * i_x] = b_VectorConcatenate2[i_x];
  }

  /* End of Concatenate: '<S7>/Vector Concatenate3' */

  /* Product: '<S6>/Product10' */
  for (i_y = 0; i_y < 3; i_y = i_y + 1) {
    for (i_z = 0; i_z < 3; i_z = i_z + 1) {
      b_VectorConcatenate_dvzb_tmp = i_y + 3 * i_z;
      b_VectorConcatenate_dvzb_0[b_VectorConcatenate_dvzb_tmp] = 0.0;
      for (i_10 = 0; i_10 < 3; i_10 = i_10 + 1) {
        b_VectorConcatenate_dvzb_0[b_VectorConcatenate_dvzb_tmp] =
          b_VectorConcatenate_dvzb_0[b_VectorConcatenate_dvzb_tmp] +
          b_VectorConcatenate_dvzb[i_y + 3 * i_10] *
          b_VectorConcatenate_ls3d[i_10 + 3 * i_z];
      }
    }
  }

  for (i_11 = 0; i_11 < 3; i_11 = i_11 + 1) {
    for (i_12 = 0; i_12 < 3; i_12 = i_12 + 1) {
      b_M_BO_tmp = i_11 + 3 * i_12;
      b_M_BO[b_M_BO_tmp] = 0.0;
      for (i_13 = 0; i_13 < 3; i_13 = i_13 + 1) {
        b_M_BO[b_M_BO_tmp] = b_M_BO[b_M_BO_tmp] + tmp[i_11 + 3 * i_13] *
          b_VectorConcatenate_dvzb_0[i_13 + 3 * i_12];
      }
    }
  }

  /* End of Product: '<S6>/Product10' */

  /* SignalConversion generated from: '<S2>/Vector Concatenate1' incorporates:
   *  Inport: '<Root>/States_Init'
   */
  b_VectorConcatenate1_kxda[0] =
    RMT_FDM_DLL_FrameWork_FCS_RT_U_States_Init->vel_K_R_E_B_mDs.u_K_R_E_B_mDs;

  /* SignalConversion generated from: '<S2>/Vector Concatenate1' incorporates:
   *  Inport: '<Root>/States_Init'
   */
  b_VectorConcatenate1_kxda[1] =
    RMT_FDM_DLL_FrameWork_FCS_RT_U_States_Init->vel_K_R_E_B_mDs.v_K_R_E_B_mDs;

  /* SignalConversion generated from: '<S2>/Vector Concatenate1' incorporates:
   *  Inport: '<Root>/States_Init'
   */
  b_VectorConcatenate1_kxda[2] =
    RMT_FDM_DLL_FrameWork_FCS_RT_U_States_Init->vel_K_R_E_B_mDs.w_K_R_E_B_mDs;
  for (i_14 = 0; i_14 < 3; i_14 = i_14 + 1) {
    /* Product: '<S2>/Product' incorporates:
     *  Math: '<S2>/Transpose'
     *  Product: '<S6>/Product10'
     *  Reshape: '<S2>/Reshape'
     */
    RMT_FDM_DLL_FrameWork_FCS_RT_B->Product[i_14] = 0.0;
    for (i_15 = 0; i_15 < 3; i_15 = i_15 + 1) {
      RMT_FDM_DLL_FrameWork_FCS_RT_B->Product[i_14] =
        RMT_FDM_DLL_FrameWork_FCS_RT_B->Product[i_14] + b_M_BO[i_15 + 3 * i_14] *
        b_VectorConcatenate1_kxda[i_15];
    }

    /* End of Product: '<S2>/Product' */
  }

  for (i_16 = 0; i_16 < 3; i_16 = i_16 + 1) {
    /* Product: '<S2>/Product2' incorporates:
     *  Product: '<S6>/Product10'
     *  Reshape: '<S2>/Reshape1'
     */
    RMT_FDM_DLL_FrameWork_FCS_RT_B->Product2[i_16] = 0.0;
    for (i_17 = 0; i_17 < 3; i_17 = i_17 + 1) {
      RMT_FDM_DLL_FrameWork_FCS_RT_B->Product2[i_16] =
        RMT_FDM_DLL_FrameWork_FCS_RT_B->Product2[i_16] + b_M_BO[i_16 + 3 * i_17]
        * RMT_FDM_DLL_FrameWork_FCS_RT_ConstB.Reshape1[i_17];
    }

    /* End of Product: '<S2>/Product2' */
  }

  if (rtmIsMajorTimeStep(RMT_FDM_DLL_FrameWork_FCS_RT_M) &&
      RMT_FDM_DLL_FrameWork_FCS_RT_M->Timing.TaskCounters.TID[1] == 0) {
    /* Delay: '<S2>/Delay16' incorporates:
     *  Inport: '<Root>/Simulation_Control'
     */
    if (RMT_FDM_DLL_FrameWork_FCS_RT_U_Simulation_Control->flg_Reset &&
        (RMT_FDM_DLL_FrameWork_FCS_RT_PrevZCX->Delay16_Reset_ZCE != POS_ZCSIG))
    {
      RMT_FDM_DLL_FrameWork_FCS_RT_DW->icLoad = true;
    }

    RMT_FDM_DLL_FrameWork_FCS_RT_PrevZCX->Delay16_Reset_ZCE = (uint8_T)
      RMT_FDM_DLL_FrameWork_FCS_RT_U_Simulation_Control->flg_Reset;
    if (RMT_FDM_DLL_FrameWork_FCS_RT_DW->icLoad) {
      RMT_FDM_DLL_FrameWork_FCS_RT_DW->Delay16_DSTATE =
        RMT_FDM_DLL_FrameWork_FCS_RT_B->Product2[0];
    }

    /* Delay: '<S2>/Delay' incorporates:
     *  Delay: '<S2>/Delay16'
     *  Inport: '<Root>/Simulation_Control'
     *  Inport: '<Root>/States_Init'
     */
    if (RMT_FDM_DLL_FrameWork_FCS_RT_U_Simulation_Control->flg_Reset &&
        (RMT_FDM_DLL_FrameWork_FCS_RT_PrevZCX->Delay_Reset_ZCE != POS_ZCSIG)) {
      RMT_FDM_DLL_FrameWork_FCS_RT_DW->icLoad_ooxy = true;
    }

    RMT_FDM_DLL_FrameWork_FCS_RT_PrevZCX->Delay_Reset_ZCE = (uint8_T)
      RMT_FDM_DLL_FrameWork_FCS_RT_U_Simulation_Control->flg_Reset;
    if (RMT_FDM_DLL_FrameWork_FCS_RT_DW->icLoad_ooxy) {
      RMT_FDM_DLL_FrameWork_FCS_RT_DW->Delay_DSTATE =
        RMT_FDM_DLL_FrameWork_FCS_RT_U_States_Init->pos_R_WGS84.h_R_WGS84_m;
    }

    /* Delay: '<S2>/Delay1' incorporates:
     *  Delay: '<S2>/Delay16'
     *  Inport: '<Root>/Simulation_Control'
     *  Inport: '<Root>/States_Init'
     */
    if (RMT_FDM_DLL_FrameWork_FCS_RT_U_Simulation_Control->flg_Reset &&
        (RMT_FDM_DLL_FrameWork_FCS_RT_PrevZCX->Delay1_Reset_ZCE != POS_ZCSIG)) {
      RMT_FDM_DLL_FrameWork_FCS_RT_DW->icLoad_hvp0 = true;
    }

    RMT_FDM_DLL_FrameWork_FCS_RT_PrevZCX->Delay1_Reset_ZCE = (uint8_T)
      RMT_FDM_DLL_FrameWork_FCS_RT_U_Simulation_Control->flg_Reset;
    if (RMT_FDM_DLL_FrameWork_FCS_RT_DW->icLoad_hvp0) {
      RMT_FDM_DLL_FrameWork_FCS_RT_DW->Delay1_DSTATE =
        RMT_FDM_DLL_FrameWork_FCS_RT_U_States_Init->rot_K_IB_B_radDs.w_x_K_IB_B_radDs;
    }

    /* Delay: '<S2>/Delay2' incorporates:
     *  Delay: '<S2>/Delay16'
     *  Inport: '<Root>/Simulation_Control'
     *  Inport: '<Root>/States_Init'
     */
    if (RMT_FDM_DLL_FrameWork_FCS_RT_U_Simulation_Control->flg_Reset &&
        (RMT_FDM_DLL_FrameWork_FCS_RT_PrevZCX->Delay2_Reset_ZCE != POS_ZCSIG)) {
      RMT_FDM_DLL_FrameWork_FCS_RT_DW->icLoad_agwh = true;
    }

    RMT_FDM_DLL_FrameWork_FCS_RT_PrevZCX->Delay2_Reset_ZCE = (uint8_T)
      RMT_FDM_DLL_FrameWork_FCS_RT_U_Simulation_Control->flg_Reset;
    if (RMT_FDM_DLL_FrameWork_FCS_RT_DW->icLoad_agwh) {
      RMT_FDM_DLL_FrameWork_FCS_RT_DW->Delay2_DSTATE =
        RMT_FDM_DLL_FrameWork_FCS_RT_U_States_Init->rot_K_IB_B_radDs.w_y_K_IB_B_radDs;
    }

    /* Delay: '<S2>/Delay3' incorporates:
     *  Delay: '<S2>/Delay16'
     *  Inport: '<Root>/Simulation_Control'
     *  Inport: '<Root>/States_Init'
     */
    if (RMT_FDM_DLL_FrameWork_FCS_RT_U_Simulation_Control->flg_Reset &&
        (RMT_FDM_DLL_FrameWork_FCS_RT_PrevZCX->Delay3_Reset_ZCE != POS_ZCSIG)) {
      RMT_FDM_DLL_FrameWork_FCS_RT_DW->icLoad_k4aw = true;
    }

    RMT_FDM_DLL_FrameWork_FCS_RT_PrevZCX->Delay3_Reset_ZCE = (uint8_T)
      RMT_FDM_DLL_FrameWork_FCS_RT_U_Simulation_Control->flg_Reset;
    if (RMT_FDM_DLL_FrameWork_FCS_RT_DW->icLoad_k4aw) {
      RMT_FDM_DLL_FrameWork_FCS_RT_DW->Delay3_DSTATE =
        RMT_FDM_DLL_FrameWork_FCS_RT_U_States_Init->rot_K_IB_B_radDs.w_z_K_IB_B_radDs;
    }

    /* Delay: '<S2>/Delay17' incorporates:
     *  Delay: '<S2>/Delay16'
     *  Inport: '<Root>/Simulation_Control'
     */
    if (RMT_FDM_DLL_FrameWork_FCS_RT_U_Simulation_Control->flg_Reset &&
        (RMT_FDM_DLL_FrameWork_FCS_RT_PrevZCX->Delay17_Reset_ZCE != POS_ZCSIG))
    {
      RMT_FDM_DLL_FrameWork_FCS_RT_DW->icLoad_eux1 = true;
    }

    RMT_FDM_DLL_FrameWork_FCS_RT_PrevZCX->Delay17_Reset_ZCE = (uint8_T)
      RMT_FDM_DLL_FrameWork_FCS_RT_U_Simulation_Control->flg_Reset;
    if (RMT_FDM_DLL_FrameWork_FCS_RT_DW->icLoad_eux1) {
      RMT_FDM_DLL_FrameWork_FCS_RT_DW->Delay17_DSTATE =
        RMT_FDM_DLL_FrameWork_FCS_RT_B->Product2[1];
    }

    /* Delay: '<S2>/Delay18' incorporates:
     *  Delay: '<S2>/Delay16'
     *  Inport: '<Root>/Simulation_Control'
     */
    if (RMT_FDM_DLL_FrameWork_FCS_RT_U_Simulation_Control->flg_Reset &&
        (RMT_FDM_DLL_FrameWork_FCS_RT_PrevZCX->Delay18_Reset_ZCE != POS_ZCSIG))
    {
      RMT_FDM_DLL_FrameWork_FCS_RT_DW->icLoad_mxgu = true;
    }

    RMT_FDM_DLL_FrameWork_FCS_RT_PrevZCX->Delay18_Reset_ZCE = (uint8_T)
      RMT_FDM_DLL_FrameWork_FCS_RT_U_Simulation_Control->flg_Reset;
    if (RMT_FDM_DLL_FrameWork_FCS_RT_DW->icLoad_mxgu) {
      RMT_FDM_DLL_FrameWork_FCS_RT_DW->Delay18_DSTATE =
        RMT_FDM_DLL_FrameWork_FCS_RT_B->Product2[2];
    }

    /* Delay: '<S2>/Delay4' incorporates:
     *  Delay: '<S2>/Delay16'
     *  Inport: '<Root>/Simulation_Control'
     *  Inport: '<Root>/States_Init'
     */
    if (RMT_FDM_DLL_FrameWork_FCS_RT_U_Simulation_Control->flg_Reset &&
        (RMT_FDM_DLL_FrameWork_FCS_RT_PrevZCX->Delay4_Reset_ZCE != POS_ZCSIG)) {
      RMT_FDM_DLL_FrameWork_FCS_RT_DW->icLoad_pbo0 = true;
    }

    RMT_FDM_DLL_FrameWork_FCS_RT_PrevZCX->Delay4_Reset_ZCE = (uint8_T)
      RMT_FDM_DLL_FrameWork_FCS_RT_U_Simulation_Control->flg_Reset;
    if (RMT_FDM_DLL_FrameWork_FCS_RT_DW->icLoad_pbo0) {
      RMT_FDM_DLL_FrameWork_FCS_RT_DW->Delay4_DSTATE =
        RMT_FDM_DLL_FrameWork_FCS_RT_U_States_Init->pos_R_WGS84.lambda_R_WGS84_rad;
    }

    /* Delay: '<S2>/Delay5' incorporates:
     *  Delay: '<S2>/Delay16'
     *  Inport: '<Root>/Simulation_Control'
     *  Inport: '<Root>/States_Init'
     */
    if (RMT_FDM_DLL_FrameWork_FCS_RT_U_Simulation_Control->flg_Reset &&
        (RMT_FDM_DLL_FrameWork_FCS_RT_PrevZCX->Delay5_Reset_ZCE != POS_ZCSIG)) {
      RMT_FDM_DLL_FrameWork_FCS_RT_DW->icLoad_dtzm = true;
    }

    RMT_FDM_DLL_FrameWork_FCS_RT_PrevZCX->Delay5_Reset_ZCE = (uint8_T)
      RMT_FDM_DLL_FrameWork_FCS_RT_U_Simulation_Control->flg_Reset;
    if (RMT_FDM_DLL_FrameWork_FCS_RT_DW->icLoad_dtzm) {
      RMT_FDM_DLL_FrameWork_FCS_RT_DW->Delay5_DSTATE =
        RMT_FDM_DLL_FrameWork_FCS_RT_U_States_Init->pos_R_WGS84.mue_R_WGS84_rad;
    }

    /* Delay: '<S2>/Delay6' incorporates:
     *  Delay: '<S2>/Delay16'
     *  Inport: '<Root>/Simulation_Control'
     *  Inport: '<Root>/States_Init'
     */
    if (RMT_FDM_DLL_FrameWork_FCS_RT_U_Simulation_Control->flg_Reset &&
        (RMT_FDM_DLL_FrameWork_FCS_RT_PrevZCX->Delay6_Reset_ZCE != POS_ZCSIG)) {
      RMT_FDM_DLL_FrameWork_FCS_RT_DW->icLoad_mfcp = true;
    }

    RMT_FDM_DLL_FrameWork_FCS_RT_PrevZCX->Delay6_Reset_ZCE = (uint8_T)
      RMT_FDM_DLL_FrameWork_FCS_RT_U_Simulation_Control->flg_Reset;
    if (RMT_FDM_DLL_FrameWork_FCS_RT_DW->icLoad_mfcp) {
      RMT_FDM_DLL_FrameWork_FCS_RT_DW->Delay6_DSTATE =
        RMT_FDM_DLL_FrameWork_FCS_RT_U_States_Init->pos_R_WGS84.h_R_WGS84_m;
    }

    /* Delay: '<S2>/Delay7' incorporates:
     *  Delay: '<S2>/Delay16'
     *  Inport: '<Root>/Simulation_Control'
     *  Inport: '<Root>/States_Init'
     */
    if (RMT_FDM_DLL_FrameWork_FCS_RT_U_Simulation_Control->flg_Reset &&
        (RMT_FDM_DLL_FrameWork_FCS_RT_PrevZCX->Delay7_Reset_ZCE != POS_ZCSIG)) {
      RMT_FDM_DLL_FrameWork_FCS_RT_DW->icLoad_js0i = true;
    }

    RMT_FDM_DLL_FrameWork_FCS_RT_PrevZCX->Delay7_Reset_ZCE = (uint8_T)
      RMT_FDM_DLL_FrameWork_FCS_RT_U_Simulation_Control->flg_Reset;
    if (RMT_FDM_DLL_FrameWork_FCS_RT_DW->icLoad_js0i) {
      RMT_FDM_DLL_FrameWork_FCS_RT_DW->Delay7_DSTATE =
        RMT_FDM_DLL_FrameWork_FCS_RT_U_States_Init->att_euler_rad.Phi_rad;
    }

    /* Delay: '<S2>/Delay8' incorporates:
     *  Delay: '<S2>/Delay16'
     *  Inport: '<Root>/Simulation_Control'
     *  Inport: '<Root>/States_Init'
     */
    if (RMT_FDM_DLL_FrameWork_FCS_RT_U_Simulation_Control->flg_Reset &&
        (RMT_FDM_DLL_FrameWork_FCS_RT_PrevZCX->Delay8_Reset_ZCE != POS_ZCSIG)) {
      RMT_FDM_DLL_FrameWork_FCS_RT_DW->icLoad_doan = true;
    }

    RMT_FDM_DLL_FrameWork_FCS_RT_PrevZCX->Delay8_Reset_ZCE = (uint8_T)
      RMT_FDM_DLL_FrameWork_FCS_RT_U_Simulation_Control->flg_Reset;
    if (RMT_FDM_DLL_FrameWork_FCS_RT_DW->icLoad_doan) {
      RMT_FDM_DLL_FrameWork_FCS_RT_DW->Delay8_DSTATE =
        RMT_FDM_DLL_FrameWork_FCS_RT_U_States_Init->att_euler_rad.Theta_rad;
    }

    /* Delay: '<S2>/Delay9' incorporates:
     *  Delay: '<S2>/Delay16'
     *  Inport: '<Root>/Simulation_Control'
     *  Inport: '<Root>/States_Init'
     */
    if (RMT_FDM_DLL_FrameWork_FCS_RT_U_Simulation_Control->flg_Reset &&
        (RMT_FDM_DLL_FrameWork_FCS_RT_PrevZCX->Delay9_Reset_ZCE != POS_ZCSIG)) {
      RMT_FDM_DLL_FrameWork_FCS_RT_DW->icLoad_mzf4 = true;
    }

    RMT_FDM_DLL_FrameWork_FCS_RT_PrevZCX->Delay9_Reset_ZCE = (uint8_T)
      RMT_FDM_DLL_FrameWork_FCS_RT_U_Simulation_Control->flg_Reset;
    if (RMT_FDM_DLL_FrameWork_FCS_RT_DW->icLoad_mzf4) {
      RMT_FDM_DLL_FrameWork_FCS_RT_DW->Delay9_DSTATE =
        RMT_FDM_DLL_FrameWork_FCS_RT_U_States_Init->att_euler_rad.Psi_rad;
    }

    /* Delay: '<S2>/Delay10' incorporates:
     *  Delay: '<S2>/Delay16'
     *  Inport: '<Root>/Simulation_Control'
     */
    if (RMT_FDM_DLL_FrameWork_FCS_RT_U_Simulation_Control->flg_Reset &&
        (RMT_FDM_DLL_FrameWork_FCS_RT_PrevZCX->Delay10_Reset_ZCE != POS_ZCSIG))
    {
      RMT_FDM_DLL_FrameWork_FCS_RT_DW->icLoad_chzd = true;
    }

    RMT_FDM_DLL_FrameWork_FCS_RT_PrevZCX->Delay10_Reset_ZCE = (uint8_T)
      RMT_FDM_DLL_FrameWork_FCS_RT_U_Simulation_Control->flg_Reset;
    if (RMT_FDM_DLL_FrameWork_FCS_RT_DW->icLoad_chzd) {
      RMT_FDM_DLL_FrameWork_FCS_RT_DW->Delay10_DSTATE =
        RMT_FDM_DLL_FrameWork_FCS_RT_B->Product[0];
    }

    /* Delay: '<S2>/Delay11' incorporates:
     *  Delay: '<S2>/Delay16'
     *  Inport: '<Root>/Simulation_Control'
     */
    if (RMT_FDM_DLL_FrameWork_FCS_RT_U_Simulation_Control->flg_Reset &&
        (RMT_FDM_DLL_FrameWork_FCS_RT_PrevZCX->Delay11_Reset_ZCE != POS_ZCSIG))
    {
      RMT_FDM_DLL_FrameWork_FCS_RT_DW->icLoad_giyv = true;
    }

    RMT_FDM_DLL_FrameWork_FCS_RT_PrevZCX->Delay11_Reset_ZCE = (uint8_T)
      RMT_FDM_DLL_FrameWork_FCS_RT_U_Simulation_Control->flg_Reset;
    if (RMT_FDM_DLL_FrameWork_FCS_RT_DW->icLoad_giyv) {
      RMT_FDM_DLL_FrameWork_FCS_RT_DW->Delay11_DSTATE =
        RMT_FDM_DLL_FrameWork_FCS_RT_B->Product[1];
    }

    /* Delay: '<S2>/Delay12' incorporates:
     *  Delay: '<S2>/Delay16'
     *  Inport: '<Root>/Simulation_Control'
     */
    if (RMT_FDM_DLL_FrameWork_FCS_RT_U_Simulation_Control->flg_Reset &&
        (RMT_FDM_DLL_FrameWork_FCS_RT_PrevZCX->Delay12_Reset_ZCE != POS_ZCSIG))
    {
      RMT_FDM_DLL_FrameWork_FCS_RT_DW->icLoad_lwdp = true;
    }

    RMT_FDM_DLL_FrameWork_FCS_RT_PrevZCX->Delay12_Reset_ZCE = (uint8_T)
      RMT_FDM_DLL_FrameWork_FCS_RT_U_Simulation_Control->flg_Reset;
    if (RMT_FDM_DLL_FrameWork_FCS_RT_DW->icLoad_lwdp) {
      RMT_FDM_DLL_FrameWork_FCS_RT_DW->Delay12_DSTATE =
        RMT_FDM_DLL_FrameWork_FCS_RT_B->Product[2];
    }

    /* Delay: '<S2>/Delay13' incorporates:
     *  Delay: '<S2>/Delay16'
     *  Inport: '<Root>/Simulation_Control'
     *  Inport: '<Root>/States_Init'
     */
    if (RMT_FDM_DLL_FrameWork_FCS_RT_U_Simulation_Control->flg_Reset &&
        (RMT_FDM_DLL_FrameWork_FCS_RT_PrevZCX->Delay13_Reset_ZCE != POS_ZCSIG))
    {
      RMT_FDM_DLL_FrameWork_FCS_RT_DW->icLoad_bu4u = true;
    }

    RMT_FDM_DLL_FrameWork_FCS_RT_PrevZCX->Delay13_Reset_ZCE = (uint8_T)
      RMT_FDM_DLL_FrameWork_FCS_RT_U_Simulation_Control->flg_Reset;
    if (RMT_FDM_DLL_FrameWork_FCS_RT_DW->icLoad_bu4u) {
      RMT_FDM_DLL_FrameWork_FCS_RT_DW->Delay13_DSTATE =
        RMT_FDM_DLL_FrameWork_FCS_RT_U_States_Init->pos_R_O_m.x_R_O_m;
    }

    /* Delay: '<S2>/Delay14' incorporates:
     *  Delay: '<S2>/Delay16'
     *  Inport: '<Root>/Simulation_Control'
     *  Inport: '<Root>/States_Init'
     */
    if (RMT_FDM_DLL_FrameWork_FCS_RT_U_Simulation_Control->flg_Reset &&
        (RMT_FDM_DLL_FrameWork_FCS_RT_PrevZCX->Delay14_Reset_ZCE != POS_ZCSIG))
    {
      RMT_FDM_DLL_FrameWork_FCS_RT_DW->icLoad_atsy = true;
    }

    RMT_FDM_DLL_FrameWork_FCS_RT_PrevZCX->Delay14_Reset_ZCE = (uint8_T)
      RMT_FDM_DLL_FrameWork_FCS_RT_U_Simulation_Control->flg_Reset;
    if (RMT_FDM_DLL_FrameWork_FCS_RT_DW->icLoad_atsy) {
      RMT_FDM_DLL_FrameWork_FCS_RT_DW->Delay14_DSTATE =
        RMT_FDM_DLL_FrameWork_FCS_RT_U_States_Init->pos_R_O_m.y_R_O_m;
    }

    /* Delay: '<S2>/Delay15' incorporates:
     *  Delay: '<S2>/Delay16'
     *  Inport: '<Root>/Simulation_Control'
     *  Inport: '<Root>/States_Init'
     */
    if (RMT_FDM_DLL_FrameWork_FCS_RT_U_Simulation_Control->flg_Reset &&
        (RMT_FDM_DLL_FrameWork_FCS_RT_PrevZCX->Delay15_Reset_ZCE != POS_ZCSIG))
    {
      RMT_FDM_DLL_FrameWork_FCS_RT_DW->icLoad_nbvc = true;
    }

    RMT_FDM_DLL_FrameWork_FCS_RT_PrevZCX->Delay15_Reset_ZCE = (uint8_T)
      RMT_FDM_DLL_FrameWork_FCS_RT_U_Simulation_Control->flg_Reset;
    if (RMT_FDM_DLL_FrameWork_FCS_RT_DW->icLoad_nbvc) {
      RMT_FDM_DLL_FrameWork_FCS_RT_DW->Delay15_DSTATE =
        RMT_FDM_DLL_FrameWork_FCS_RT_U_States_Init->pos_R_O_m.z_R_O_m;
    }

    /* BusAssignment: '<S2>/Bus Assignment' incorporates:
     *  Delay: '<S2>/Delay'
     *  Delay: '<S2>/Delay1'
     *  Delay: '<S2>/Delay10'
     *  Delay: '<S2>/Delay11'
     *  Delay: '<S2>/Delay12'
     *  Delay: '<S2>/Delay13'
     *  Delay: '<S2>/Delay14'
     *  Delay: '<S2>/Delay15'
     *  Delay: '<S2>/Delay16'
     *  Delay: '<S2>/Delay17'
     *  Delay: '<S2>/Delay18'
     *  Delay: '<S2>/Delay2'
     *  Delay: '<S2>/Delay3'
     *  Delay: '<S2>/Delay4'
     *  Delay: '<S2>/Delay5'
     *  Delay: '<S2>/Delay6'
     *  Delay: '<S2>/Delay7'
     *  Delay: '<S2>/Delay8'
     *  Delay: '<S2>/Delay9'
     */
    memset(&b_fc_measurements, 0, sizeof(fc_measurements_Bus));
    b_fc_measurements.baro_meas.h_Alt_Baro_meas_m =
      RMT_FDM_DLL_FrameWork_FCS_RT_DW->Delay_DSTATE;
    b_fc_measurements.imu_meas.gyro_meas.w_x_K_IB_B_IMU_meas_radDs =
      RMT_FDM_DLL_FrameWork_FCS_RT_DW->Delay1_DSTATE;
    b_fc_measurements.imu_meas.gyro_meas.w_y_K_IB_B_IMU_meas_radDs =
      RMT_FDM_DLL_FrameWork_FCS_RT_DW->Delay2_DSTATE;
    b_fc_measurements.imu_meas.gyro_meas.w_z_K_IB_B_IMU_meas_radDs =
      RMT_FDM_DLL_FrameWork_FCS_RT_DW->Delay3_DSTATE;
    b_fc_measurements.imu_meas.acc_meas.f_x_P_B_IMU_meas_mDs2 =
      RMT_FDM_DLL_FrameWork_FCS_RT_DW->Delay16_DSTATE;
    b_fc_measurements.imu_meas.acc_meas.f_y_P_B_IMU_meas_mDs2 =
      RMT_FDM_DLL_FrameWork_FCS_RT_DW->Delay17_DSTATE;
    b_fc_measurements.imu_meas.acc_meas.f_z_P_B_IMU_meas_mDs2 =
      RMT_FDM_DLL_FrameWork_FCS_RT_DW->Delay18_DSTATE;
    b_fc_measurements.gps_meas.pos_R_WGS84_meas.lambda_R_WGS84_meas_rad =
      RMT_FDM_DLL_FrameWork_FCS_RT_DW->Delay4_DSTATE;
    b_fc_measurements.gps_meas.pos_R_WGS84_meas.mue_R_WGS84_meas_rad =
      RMT_FDM_DLL_FrameWork_FCS_RT_DW->Delay5_DSTATE;
    b_fc_measurements.gps_meas.pos_R_WGS84_meas.h_R_WGS84_meas_m =
      RMT_FDM_DLL_FrameWork_FCS_RT_DW->Delay6_DSTATE;
    b_fc_measurements.ahrs_meas.Phi_meas_rad =
      RMT_FDM_DLL_FrameWork_FCS_RT_DW->Delay7_DSTATE;
    b_fc_measurements.ahrs_meas.Theta_meas_rad =
      RMT_FDM_DLL_FrameWork_FCS_RT_DW->Delay8_DSTATE;
    b_fc_measurements.ahrs_meas.Psi_meas_rad =
      RMT_FDM_DLL_FrameWork_FCS_RT_DW->Delay9_DSTATE;
    b_fc_measurements.gps_meas.vel_K_R_E_O_meas.u_K_R_E_O_meas_mDs =
      RMT_FDM_DLL_FrameWork_FCS_RT_DW->Delay10_DSTATE;
    b_fc_measurements.gps_meas.vel_K_R_E_O_meas.v_K_R_E_O_meas_mDs =
      RMT_FDM_DLL_FrameWork_FCS_RT_DW->Delay11_DSTATE;
    b_fc_measurements.gps_meas.vel_K_R_E_O_meas.w_K_R_E_O_meas_mDs =
      RMT_FDM_DLL_FrameWork_FCS_RT_DW->Delay12_DSTATE;
    b_fc_measurements.gps_meas.pos_R_local_meas.x_R_O_meas_m =
      RMT_FDM_DLL_FrameWork_FCS_RT_DW->Delay13_DSTATE;
    b_fc_measurements.gps_meas.pos_R_local_meas.y_R_O_meas_m =
      RMT_FDM_DLL_FrameWork_FCS_RT_DW->Delay14_DSTATE;
    b_fc_measurements.gps_meas.pos_R_local_meas.z_R_O_meas_m =
      RMT_FDM_DLL_FrameWork_FCS_RT_DW->Delay15_DSTATE;

    /* RateTransition: '<Root>/RT2' incorporates:
     *  RateTransition: '<Root>/RT1'
     *  RateTransition: '<Root>/RT3'
     */
    if (rtmIsMajorTimeStep(RMT_FDM_DLL_FrameWork_FCS_RT_M) &&
        RMT_FDM_DLL_FrameWork_FCS_RT_M->Timing.TaskCounters.TID[1] == 0) {
      /* RateTransition: '<Root>/RT2' incorporates:
       *  BusAssignment: '<S2>/Bus Assignment'
       */
      RMT_FDM_DLL_FrameWork_FCS_RT_B->RT2 = b_fc_measurements;

      /* RateTransition: '<Root>/RT3' incorporates:
       *  Inport: '<Root>/States_Init'
       */
      RMT_FDM_DLL_FrameWork_FCS_RT_B->RT3 =
        *RMT_FDM_DLL_FrameWork_FCS_RT_U_States_Init;

      /* RateTransition: '<Root>/RT1' incorporates:
       *  Inport: '<Root>/fc_pilot_cmd'
       */
      RMT_FDM_DLL_FrameWork_FCS_RT_B->RT1 =
        *RMT_FDM_DLL_FrameWork_FCS_RT_U_fc_pilot_cmd;
    }

    /* End of RateTransition: '<Root>/RT2' */

    /* Outputs for Atomic SubSystem: '<Root>/FCS_INDI_Control' */
    /* Constant: '<S37>/Constant1' */
    b_VectorConcatenate_np2w[0] = 1.0;

    /* SignalConversion generated from: '<S37>/Vector Concatenate' incorporates:
     *  Constant: '<S37>/Constant'
     */
    b_VectorConcatenate_np2w[1] = 0.0;

    /* SignalConversion generated from: '<S37>/Vector Concatenate' incorporates:
     *  Constant: '<S37>/Constant'
     */
    b_VectorConcatenate_np2w[2] = 0.0;

    /* SignalConversion generated from: '<S37>/Vector Concatenate1' incorporates:
     *  Constant: '<S37>/Constant'
     */
    b_VectorConcatenate1_fuwu[0] = 0.0;

    /* SignalConversion generated from: '<S14>/Vector Concatenate1' */
    b_VectorConcatenate1_o2ke[0] =
      RMT_FDM_DLL_FrameWork_FCS_RT_B->RT2.ahrs_meas.Phi_meas_rad;

    /* SignalConversion generated from: '<S14>/Vector Concatenate1' */
    b_VectorConcatenate1_o2ke[1] =
      RMT_FDM_DLL_FrameWork_FCS_RT_B->RT2.ahrs_meas.Theta_meas_rad;

    /* SignalConversion generated from: '<S14>/Vector Concatenate2' */
    for (i_3 = 0; i_3 < 2; i_3 = i_3 + 1) {
      b_VectorConcatenate2_fdcl[i_3] = b_VectorConcatenate1_o2ke[i_3];
    }

    /* End of SignalConversion generated from: '<S14>/Vector Concatenate2' */

    /* Trigonometry: '<S37>/Trigonometric Function' incorporates:
     *  Reshape: '<S14>/Reshape1'
     */
    b_p_Ref_o2 = cos(b_VectorConcatenate2_fdcl[0]);

    /* SignalConversion generated from: '<S37>/Vector Concatenate1' */
    b_VectorConcatenate1_fuwu[1] = b_p_Ref_o2;

    /* Trigonometry: '<S37>/Trigonometric Function1' incorporates:
     *  Reshape: '<S14>/Reshape1'
     */
    b_p_Ref_radDs = sin(b_VectorConcatenate2_fdcl[0]);

    /* SignalConversion generated from: '<S37>/Vector Concatenate1' */
    b_VectorConcatenate1_fuwu[2] = b_p_Ref_radDs;

    /* SignalConversion generated from: '<S37>/Vector Concatenate2' incorporates:
     *  Constant: '<S37>/Constant'
     */
    b_VectorConcatenate2_it5a[0] = 0.0;

    /* Gain: '<S37>/Gain' */
    b_VectorConcatenate2_it5a[1] = -b_p_Ref_radDs;

    /* SignalConversion generated from: '<S37>/Vector Concatenate2' */
    b_VectorConcatenate2_it5a[2] = b_p_Ref_o2;

    /* Trigonometry: '<S38>/Trigonometric Function' incorporates:
     *  Reshape: '<S14>/Reshape1'
     */
    b_p_Ref_radDs = cos(b_VectorConcatenate2_fdcl[1]);

    /* SignalConversion generated from: '<S38>/Vector Concatenate' */
    b_VectorConcatenate_eemv[0] = b_p_Ref_radDs;

    /* SignalConversion generated from: '<S38>/Vector Concatenate' incorporates:
     *  Constant: '<S38>/Constant'
     */
    b_VectorConcatenate_eemv[1] = 0.0;

    /* Trigonometry: '<S38>/Trigonometric Function1' incorporates:
     *  Reshape: '<S14>/Reshape1'
     */
    b_p_Ref_o2 = sin(b_VectorConcatenate2_fdcl[1]);

    /* Gain: '<S38>/Gain' */
    b_VectorConcatenate_eemv[2] = -b_p_Ref_o2;

    /* SignalConversion generated from: '<S38>/Vector Concatenate1' incorporates:
     *  Constant: '<S38>/Constant'
     */
    b_VectorConcatenate1_aieq[0] = 0.0;

    /* Constant: '<S38>/Constant1' */
    b_VectorConcatenate1_aieq[1] = 1.0;

    /* SignalConversion generated from: '<S38>/Vector Concatenate1' incorporates:
     *  Constant: '<S38>/Constant'
     */
    b_VectorConcatenate1_aieq[2] = 0.0;

    /* SignalConversion generated from: '<S38>/Vector Concatenate2' */
    b_VectorConcatenate2_jjfd[0] = b_p_Ref_o2;

    /* SignalConversion generated from: '<S38>/Vector Concatenate2' incorporates:
     *  Constant: '<S38>/Constant'
     */
    b_VectorConcatenate2_jjfd[1] = 0.0;

    /* SignalConversion generated from: '<S38>/Vector Concatenate2' */
    b_VectorConcatenate2_jjfd[2] = b_p_Ref_radDs;

    /* SignalConversion generated from: '<S39>/Vector Concatenate' */
    b_VectorConcatenate_gvog[0] = 1.0;

    /* SignalConversion generated from: '<S39>/Vector Concatenate' */
    b_VectorConcatenate_gvog[1] = 0.0;

    /* SignalConversion generated from: '<S39>/Vector Concatenate' incorporates:
     *  Constant: '<S39>/Constant'
     */
    b_VectorConcatenate_gvog[2] = 0.0;

    /* Gain: '<S39>/Gain' */
    b_Sum_ihvy[0] = -0.0;

    /* SignalConversion generated from: '<S39>/Vector Concatenate1' */
    b_Sum_ihvy[1] = 1.0;

    /* SignalConversion generated from: '<S39>/Vector Concatenate1' incorporates:
     *  Constant: '<S39>/Constant'
     */
    b_Sum_ihvy[2] = 0.0;

    /* SignalConversion generated from: '<S39>/Vector Concatenate2' incorporates:
     *  Constant: '<S39>/Constant'
     */
    b_Reshape2_izpf[0] = 0.0;

    /* SignalConversion generated from: '<S39>/Vector Concatenate2' incorporates:
     *  Constant: '<S39>/Constant'
     */
    b_Reshape2_izpf[1] = 0.0;

    /* Constant: '<S39>/Constant1' */
    b_Reshape2_izpf[2] = 1.0;

    /* SignalConversion generated from: '<S14>/Vector Concatenate3' */
    b_Reshape3[0] =
      RMT_FDM_DLL_FrameWork_FCS_RT_B->RT2.imu_meas.acc_meas.f_x_P_B_IMU_meas_mDs2;

    /* SignalConversion generated from: '<S14>/Vector Concatenate3' */
    b_Reshape3[1] =
      RMT_FDM_DLL_FrameWork_FCS_RT_B->RT2.imu_meas.acc_meas.f_y_P_B_IMU_meas_mDs2;

    /* SignalConversion generated from: '<S14>/Vector Concatenate3' */
    b_Reshape3[2] =
      RMT_FDM_DLL_FrameWork_FCS_RT_B->RT2.imu_meas.acc_meas.f_z_P_B_IMU_meas_mDs2;

    /* Concatenate: '<S38>/Vector Concatenate3' incorporates:
     *  Concatenate: '<S38>/Vector Concatenate'
     *  Concatenate: '<S38>/Vector Concatenate1'
     *  Concatenate: '<S38>/Vector Concatenate2'
     */
    for (i_18 = 0; i_18 < 3; i_18 = i_18 + 1) {
      b_VectorConcatenate_itjq[3 * i_18] = b_VectorConcatenate_eemv[i_18];
    }

    for (i_19 = 0; i_19 < 3; i_19 = i_19 + 1) {
      b_VectorConcatenate_itjq[1 + 3 * i_19] = b_VectorConcatenate1_aieq[i_19];
    }

    for (i_1a = 0; i_1a < 3; i_1a = i_1a + 1) {
      b_VectorConcatenate_itjq[2 + 3 * i_1a] = b_VectorConcatenate2_jjfd[i_1a];
    }

    /* End of Concatenate: '<S38>/Vector Concatenate3' */

    /* Concatenate: '<S39>/Vector Concatenate3' incorporates:
     *  Concatenate: '<S39>/Vector Concatenate'
     *  Reshape: '<S14>/Reshape2'
     *  Sum: '<S14>/Sum'
     */
    for (i_1b = 0; i_1b < 3; i_1b = i_1b + 1) {
      b_VectorConcatenate_htsf[3 * i_1b] = b_VectorConcatenate_gvog[i_1b];
    }

    for (i_1c = 0; i_1c < 3; i_1c = i_1c + 1) {
      b_VectorConcatenate_htsf[1 + 3 * i_1c] = b_Sum_ihvy[i_1c];
    }

    for (i_1d = 0; i_1d < 3; i_1d = i_1d + 1) {
      b_VectorConcatenate_htsf[2 + 3 * i_1d] = b_Reshape2_izpf[i_1d];
    }

    /* End of Concatenate: '<S39>/Vector Concatenate3' */

    /* Concatenate: '<S37>/Vector Concatenate3' incorporates:
     *  Concatenate: '<S37>/Vector Concatenate'
     *  Concatenate: '<S37>/Vector Concatenate1'
     *  Concatenate: '<S37>/Vector Concatenate2'
     */
    for (i_1e = 0; i_1e < 3; i_1e = i_1e + 1) {
      b_VectorConcatenate_kzgt[3 * i_1e] = b_VectorConcatenate_np2w[i_1e];
    }

    for (i_1f = 0; i_1f < 3; i_1f = i_1f + 1) {
      b_VectorConcatenate_kzgt[1 + 3 * i_1f] = b_VectorConcatenate1_fuwu[i_1f];
    }

    for (i_1g = 0; i_1g < 3; i_1g = i_1g + 1) {
      b_VectorConcatenate_kzgt[2 + 3 * i_1g] = b_VectorConcatenate2_it5a[i_1g];
    }

    /* End of Concatenate: '<S37>/Vector Concatenate3' */

    /* Product: '<S36>/Product10' */
    for (i_1h = 0; i_1h < 3; i_1h = i_1h + 1) {
      for (i_1i = 0; i_1i < 3; i_1i = i_1i + 1) {
        b_VectorConcatenate_itjq_tmp = i_1h + 3 * i_1i;
        b_VectorConcatenate_itjq_0[b_VectorConcatenate_itjq_tmp] = 0.0;
        for (i_1j = 0; i_1j < 3; i_1j = i_1j + 1) {
          b_VectorConcatenate_itjq_0[b_VectorConcatenate_itjq_tmp] =
            b_VectorConcatenate_itjq_0[b_VectorConcatenate_itjq_tmp] +
            b_VectorConcatenate_itjq[i_1h + 3 * i_1j] *
            b_VectorConcatenate_htsf[i_1j + 3 * i_1i];
        }
      }
    }

    /* Math: '<S14>/Transpose' incorporates:
     *  Product: '<S36>/Product10'
     */
    for (i_1k = 0; i_1k < 3; i_1k = i_1k + 1) {
      for (i_1l = 0; i_1l < 3; i_1l = i_1l + 1) {
        b_VectorConcatenate_kzgt_tmp = i_1k + 3 * i_1l;
        b_VectorConcatenate_kzgt_0[b_VectorConcatenate_kzgt_tmp] = 0.0;
        for (i_1m = 0; i_1m < 3; i_1m = i_1m + 1) {
          b_VectorConcatenate_kzgt_0[b_VectorConcatenate_kzgt_tmp] =
            b_VectorConcatenate_kzgt_0[b_VectorConcatenate_kzgt_tmp] +
            b_VectorConcatenate_kzgt[i_1l + 3 * i_1m] *
            b_VectorConcatenate_itjq_0[i_1m + 3 * i_1k];
        }
      }
    }

    /* End of Math: '<S14>/Transpose' */

    /* Product: '<S14>/Product' incorporates:
     *  Reshape: '<S14>/Reshape'
     *  Reshape: '<S14>/Reshape3'
     */
    for (i_1n = 0; i_1n < 3; i_1n = i_1n + 1) {
      b_VectorConcatenate_kzgt_1[i_1n] = 0.0;
      for (i_1o = 0; i_1o < 3; i_1o = i_1o + 1) {
        b_VectorConcatenate_kzgt_1[i_1n] = b_VectorConcatenate_kzgt_1[i_1n] +
          b_VectorConcatenate_kzgt_0[i_1n + 3 * i_1o] * b_Reshape3[i_1o];
      }
    }

    for (i_1p = 0; i_1p < 3; i_1p = i_1p + 1) {
      b_Reshape3[i_1p] = b_VectorConcatenate_kzgt_1[i_1p];
    }

    /* End of Product: '<S14>/Product' */

    /* Sum: '<S14>/Sum' incorporates:
     *  Constant: '<S14>/Constant1'
     *  Reshape: '<S14>/Reshape2'
     *  Reshape: '<S14>/Reshape3'
     */
    for (i_4 = 0; i_4 < 3; i_4 = i_4 + 1) {
      b_Sum_ihvy[i_4] = b_Reshape3[i_4] + rtCP_Constant1_Value_pg2h[i_4];
    }

    /* End of Sum: '<S14>/Sum' */

    /* Trigonometry: '<S33>/Trigonometric Function' */
    b_p_Ref_radDs = cos
      (RMT_FDM_DLL_FrameWork_FCS_RT_B->RT2.ahrs_meas.Psi_meas_rad);

    /* SignalConversion generated from: '<S33>/Vector Concatenate' */
    b_VectorConcatenate_pt2w[0] = b_p_Ref_radDs;

    /* Trigonometry: '<S33>/Trigonometric Function1' */
    b_p_Ref_o2 = sin(RMT_FDM_DLL_FrameWork_FCS_RT_B->RT2.ahrs_meas.Psi_meas_rad);

    /* SignalConversion generated from: '<S33>/Vector Concatenate' */
    b_VectorConcatenate_pt2w[1] = b_p_Ref_o2;

    /* SignalConversion generated from: '<S33>/Vector Concatenate' incorporates:
     *  Constant: '<S33>/Constant'
     */
    b_VectorConcatenate_pt2w[2] = 0.0;

    /* Gain: '<S33>/Gain' */
    b_Reshape2[0] = -b_p_Ref_o2;

    /* SignalConversion generated from: '<S33>/Vector Concatenate1' */
    b_Reshape2[1] = b_p_Ref_radDs;

    /* SignalConversion generated from: '<S33>/Vector Concatenate1' incorporates:
     *  Constant: '<S33>/Constant'
     */
    b_Reshape2[2] = 0.0;

    /* SignalConversion generated from: '<S33>/Vector Concatenate2' incorporates:
     *  Constant: '<S33>/Constant'
     */
    b_Reshape1_bgqi[0] = 0.0;

    /* SignalConversion generated from: '<S33>/Vector Concatenate2' incorporates:
     *  Constant: '<S33>/Constant'
     */
    b_Reshape1_bgqi[1] = 0.0;

    /* Constant: '<S33>/Constant1' */
    b_Reshape1_bgqi[2] = 1.0;

    /* SignalConversion generated from: '<S14>/Vector Concatenate4' */
    b_Reshape_pne4[0] =
      RMT_FDM_DLL_FrameWork_FCS_RT_B->RT2.gps_meas.vel_K_R_E_O_meas.u_K_R_E_O_meas_mDs;

    /* SignalConversion generated from: '<S14>/Vector Concatenate4' */
    b_Reshape_pne4[1] =
      RMT_FDM_DLL_FrameWork_FCS_RT_B->RT2.gps_meas.vel_K_R_E_O_meas.v_K_R_E_O_meas_mDs;

    /* SignalConversion generated from: '<S14>/Vector Concatenate4' */
    b_Reshape_pne4[2] =
      RMT_FDM_DLL_FrameWork_FCS_RT_B->RT2.gps_meas.vel_K_R_E_O_meas.w_K_R_E_O_meas_mDs;

    /* Concatenate: '<S33>/Vector Concatenate3' incorporates:
     *  Concatenate: '<S33>/Vector Concatenate'
     *  Reshape: '<S45>/Reshape1'
     *  Reshape: '<S45>/Reshape2'
     */
    for (i_1q = 0; i_1q < 3; i_1q = i_1q + 1) {
      b_VectorConcatenate_p0sg[3 * i_1q] = b_VectorConcatenate_pt2w[i_1q];
    }

    for (i_1r = 0; i_1r < 3; i_1r = i_1r + 1) {
      b_VectorConcatenate_p0sg[1 + 3 * i_1r] = b_Reshape2[i_1r];
    }

    for (i_1s = 0; i_1s < 3; i_1s = i_1s + 1) {
      b_VectorConcatenate_p0sg[2 + 3 * i_1s] = b_Reshape1_bgqi[i_1s];
    }

    /* End of Concatenate: '<S33>/Vector Concatenate3' */

    /* Product: '<S14>/Product1' incorporates:
     *  Reshape: '<S14>/Reshape4'
     *  Reshape: '<S45>/Reshape'
     */
    for (i_1t = 0; i_1t < 3; i_1t = i_1t + 1) {
      b_VectorConcatenate_p0sg_0[i_1t] = 0.0;
      for (i_1u = 0; i_1u < 3; i_1u = i_1u + 1) {
        b_VectorConcatenate_p0sg_0[i_1t] = b_VectorConcatenate_p0sg_0[i_1t] +
          b_VectorConcatenate_p0sg[i_1t + 3 * i_1u] * b_Reshape_pne4[i_1u];
      }
    }

    for (i_1v = 0; i_1v < 3; i_1v = i_1v + 1) {
      b_Reshape_pne4[i_1v] = b_VectorConcatenate_p0sg_0[i_1v];
    }

    /* End of Product: '<S14>/Product1' */

    /* SignalConversion generated from: '<S14>/Vector Concatenate' */
    b_VectorConcatenate_iw4s[0] =
      RMT_FDM_DLL_FrameWork_FCS_RT_B->RT2.imu_meas.gyro_meas.w_x_K_IB_B_IMU_meas_radDs;

    /* SignalConversion generated from: '<S14>/Vector Concatenate' */
    b_VectorConcatenate_iw4s[1] =
      RMT_FDM_DLL_FrameWork_FCS_RT_B->RT2.imu_meas.gyro_meas.w_y_K_IB_B_IMU_meas_radDs;

    /* SignalConversion generated from: '<S14>/Vector Concatenate' */
    b_VectorConcatenate_iw4s[2] =
      RMT_FDM_DLL_FrameWork_FCS_RT_B->RT2.imu_meas.gyro_meas.w_z_K_IB_B_IMU_meas_radDs;

    /* BusCreator generated from: '<S14>/Bus Assignment' incorporates:
     *  BusAssignment: '<S14>/Bus Assignment'
     *  SignalConversion generated from: '<S14>/Vector Concatenate'
     * */
    b_BusAssignment.rate_est.p_est_radDs =
      RMT_FDM_DLL_FrameWork_FCS_RT_B->RT2.imu_meas.gyro_meas.w_x_K_IB_B_IMU_meas_radDs;
    b_BusAssignment.rate_est.q_est_radDs =
      RMT_FDM_DLL_FrameWork_FCS_RT_B->RT2.imu_meas.gyro_meas.w_y_K_IB_B_IMU_meas_radDs;
    b_BusAssignment.rate_est.r_est_radDs =
      RMT_FDM_DLL_FrameWork_FCS_RT_B->RT2.imu_meas.gyro_meas.w_z_K_IB_B_IMU_meas_radDs;

    /* SampleTimeMath: '<S32>/TSamp'
     *
     * About '<S32>/TSamp':
     *  y = u * K where K = 1 / ( w * Ts )
     *   */
    for (i_5 = 0; i_5 < 3; i_5 = i_5 + 1) {
      b_TSamp[i_5] = b_VectorConcatenate_iw4s[i_5] * 250.0;
    }

    /* End of SampleTimeMath: '<S32>/TSamp' */

    /* Sum: '<S32>/Diff' incorporates:
     *  UnitDelay: '<S32>/UD'
     *
     * Block description for '<S32>/Diff':
     *
     *  Add in CPU
     *
     * Block description for '<S32>/UD':
     *
     *  Store in Global RAM
     */
    for (i_6 = 0; i_6 < 3; i_6 = i_6 + 1) {
      b_Diff[i_6] = b_TSamp[i_6] - RMT_FDM_DLL_FrameWork_FCS_RT_DW->
        UD_DSTATE[i_6];
    }

    /* End of Sum: '<S32>/Diff' */

    /* BusCreator generated from: '<S14>/Bus Assignment' incorporates:
     *  BusAssignment: '<S14>/Bus Assignment'
     */
    b_BusAssignment.rate_dot_est.p_Dot_est_radDs2 = b_Diff[0];
    b_BusAssignment.rate_dot_est.q_Dot_est_radDs2 = b_Diff[1];
    b_BusAssignment.rate_dot_est.r_Dot_est_radDs2 = b_Diff[2];

    /* Trigonometry: '<S34>/Trigonometric Function1' incorporates:
     *  SignalConversion generated from: '<S14>/Vector Concatenate1'
     */
    b_p_Ref_o2 = cos
      (RMT_FDM_DLL_FrameWork_FCS_RT_B->RT2.ahrs_meas.Theta_meas_rad);

    /* BusCreator generated from: '<S14>/Bus Assignment' incorporates:
     *  Product: '<S34>/Divide'
     *  Product: '<S34>/Divide1'
     *  Product: '<S34>/Product'
     *  Product: '<S34>/Product1'
     *  SignalConversion generated from: '<S14>/Vector Concatenate1'
     *  SignalConversion generated from: '<S14>/Vector Concatenate'
     *  Sum: '<S34>/Sum'
     *  Trigonometry: '<S34>/Trigonometric Function'
     *  Trigonometry: '<S34>/Trigonometric Function2'
     * */
    b_BusConversion_InsertedFor_BusAssignment_at_inport_3_BusCreator.Phi_est_rad
      = RMT_FDM_DLL_FrameWork_FCS_RT_B->RT2.ahrs_meas.Phi_meas_rad;
    b_BusConversion_InsertedFor_BusAssignment_at_inport_3_BusCreator.Theta_est_rad
      = RMT_FDM_DLL_FrameWork_FCS_RT_B->RT2.ahrs_meas.Theta_meas_rad;
    b_BusConversion_InsertedFor_BusAssignment_at_inport_3_BusCreator.Psi_Dot_est_radDs
      =
      RMT_FDM_DLL_FrameWork_FCS_RT_B->RT2.imu_meas.gyro_meas.w_y_K_IB_B_IMU_meas_radDs
      * (sin(RMT_FDM_DLL_FrameWork_FCS_RT_B->RT2.ahrs_meas.Phi_meas_rad) /
         b_p_Ref_o2) +
      RMT_FDM_DLL_FrameWork_FCS_RT_B->RT2.imu_meas.gyro_meas.w_z_K_IB_B_IMU_meas_radDs
      * (cos(RMT_FDM_DLL_FrameWork_FCS_RT_B->RT2.ahrs_meas.Phi_meas_rad) /
         b_p_Ref_o2);

    /* BusAssignment: '<S14>/Bus Assignment' incorporates:
     *  Reshape: '<S14>/Reshape5'
     *  Reshape: '<S45>/Reshape'
     */
    b_BusAssignment.att_est =
      b_BusConversion_InsertedFor_BusAssignment_at_inport_3_BusCreator;
    b_BusAssignment.vel_dot_es.u_dot_K_R_EC_C_est_mDs2 = b_Sum_ihvy[0];
    b_BusAssignment.vel_dot_es.v_dot_K_R_EC_C_est_mDs2 = b_Sum_ihvy[1];
    b_BusAssignment.vel_dot_es.w_dot_K_R_EC_C_est_mDs2 = b_Sum_ihvy[2];
    b_BusAssignment.vel_est.u_K_R_E_C_est_mDs = b_Reshape_pne4[0];
    b_BusAssignment.vel_est.v_K_R_E_C_est_mDs = b_Reshape_pne4[1];
    b_BusAssignment.vel_est.w_K_R_E_C_est_mDs = b_Reshape_pne4[2];

    /* SignalConversion generated from: '<S5>/Vector Concatenate1' incorporates:
     *  BusAssignment: '<S14>/Bus Assignment'
     */
    b_nu_est[0] = b_Sum_ihvy[0];

    /* SignalConversion generated from: '<S5>/Vector Concatenate1' incorporates:
     *  BusAssignment: '<S14>/Bus Assignment'
     */
    b_nu_est[1] = b_Sum_ihvy[1];

    /* SignalConversion generated from: '<S5>/Vector Concatenate1' incorporates:
     *  BusAssignment: '<S14>/Bus Assignment'
     */
    b_nu_est[2] = b_Sum_ihvy[2];

    /* SignalConversion generated from: '<S5>/Vector Concatenate1' incorporates:
     *  BusCreator generated from: '<S14>/Bus Assignment'
     */
    b_nu_est[3] = b_Diff[0];

    /* SignalConversion generated from: '<S5>/Vector Concatenate1' incorporates:
     *  BusCreator generated from: '<S14>/Bus Assignment'
     */
    b_nu_est[4] = b_Diff[1];

    /* SignalConversion generated from: '<S5>/Vector Concatenate1' incorporates:
     *  BusCreator generated from: '<S14>/Bus Assignment'
     */
    b_nu_est[5] = b_Diff[2];

    /* Switch: '<S5>/Switch' */
    if (RMT_FDM_DLL_FrameWork_FCS_RT_B->RT1.override_swi) {
      b_Switch_gbzj = RMT_FDM_DLL_FrameWork_FCS_RT_B->RT1;
    } else {
      memset(&b_Switch_gbzj, 0, sizeof(fc_pilot_cmd_Bus));
    }

    /* End of Switch: '<S5>/Switch' */

    /* Delay: '<S5>/Delay' */
    if (RMT_FDM_DLL_FrameWork_FCS_RT_B->RT1.arm_swi &&
        (RMT_FDM_DLL_FrameWork_FCS_RT_PrevZCX->Delay_Reset_ZCE_pegz != POS_ZCSIG))
    {
      memset(&RMT_FDM_DLL_FrameWork_FCS_RT_DW->Delay_DSTATE_oj24[0], 0, 10U *
             sizeof(real_T));
    }

    RMT_FDM_DLL_FrameWork_FCS_RT_PrevZCX->Delay_Reset_ZCE_pegz = (uint8_T)
      RMT_FDM_DLL_FrameWork_FCS_RT_B->RT1.arm_swi;

    /* SignalConversion generated from: '<S40>/Vector Concatenate1' incorporates:
     *  SignalConversion generated from: '<S14>/Vector Concatenate1'
     */
    b_VectorConcatenate1_j0rp[0] =
      RMT_FDM_DLL_FrameWork_FCS_RT_B->RT2.ahrs_meas.Phi_meas_rad;

    /* SignalConversion generated from: '<S40>/Vector Concatenate1' incorporates:
     *  SignalConversion generated from: '<S14>/Vector Concatenate1'
     */
    b_VectorConcatenate1_j0rp[1] =
      RMT_FDM_DLL_FrameWork_FCS_RT_B->RT2.ahrs_meas.Theta_meas_rad;

    /* Sum: '<S40>/Sum' incorporates:
     *  Delay: '<S5>/Delay'
     *  Reshape: '<S40>/Reshape'
     */
    for (i_7 = 0; i_7 < 2; i_7 = i_7 + 1) {
      b_Sum_ndgx[i_7] = RMT_FDM_DLL_FrameWork_FCS_RT_DW->Delay_DSTATE_oj24[i_7]
        + b_VectorConcatenate1_j0rp[i_7];
    }

    /* End of Sum: '<S40>/Sum' */

    /* BusAssignment: '<S40>/Bus Assignment1' */
    b_BusAssignment1 = b_Switch_gbzj;
    b_BusAssignment1.att_euler_cmd.Phi_cmd_rad = b_Sum_ndgx[0];
    b_BusAssignment1.att_euler_cmd.Theta_cmd_rad = b_Sum_ndgx[1];

    /* Switch: '<S40>/Switch' incorporates:
     *  RelationalOperator: '<S41>/Compare'
     */
    if (!b_Switch_gbzj.vel_att_mode_swi) {
      /* Switch: '<S40>/Switch' */
      b_Switch = b_Switch_gbzj;
    } else {
      /* Switch: '<S40>/Switch' */
      b_Switch = b_BusAssignment1;
    }

    /* End of Switch: '<S40>/Switch' */

    /* DiscreteIntegrator: '<S47>/Phi_Ref' */
    if (b_Switch.arm_swi &&
        (RMT_FDM_DLL_FrameWork_FCS_RT_DW->Phi_Ref_PrevResetState <= 0)) {
      RMT_FDM_DLL_FrameWork_FCS_RT_DW->Phi_Ref_DSTATE = 0.0;
    }

    /* Switch: '<S57>/Switch' incorporates:
     *  Constant: '<S47>/Constant1'
     *  DiscreteIntegrator: '<S47>/Phi_Ref'
     *  RelationalOperator: '<S57>/UpperRelop'
     */
    if (RMT_FDM_DLL_FrameWork_FCS_RT_DW->Phi_Ref_DSTATE < -0.52359877559829882)
    {
      b_Switch_h4q0 = -0.52359877559829882;
    } else {
      b_Switch_h4q0 = RMT_FDM_DLL_FrameWork_FCS_RT_DW->Phi_Ref_DSTATE;
    }

    /* End of Switch: '<S57>/Switch' */

    /* Switch: '<S57>/Switch2' incorporates:
     *  Constant: '<S47>/Constant'
     *  DiscreteIntegrator: '<S47>/Phi_Ref'
     *  RelationalOperator: '<S57>/LowerRelop1'
     */
    if (RMT_FDM_DLL_FrameWork_FCS_RT_DW->Phi_Ref_DSTATE > 0.52359877559829882) {
      b_Switch2 = 0.52359877559829882;
    } else {
      b_Switch2 = b_Switch_h4q0;
    }

    /* End of Switch: '<S57>/Switch2' */

    /* DiscreteIntegrator: '<S47>/Theta_Ref' */
    if (b_Switch.arm_swi &&
        (RMT_FDM_DLL_FrameWork_FCS_RT_DW->Theta_Ref_PrevResetState <= 0)) {
      RMT_FDM_DLL_FrameWork_FCS_RT_DW->Theta_Ref_DSTATE = 0.0;
    }

    /* Switch: '<S58>/Switch' incorporates:
     *  Constant: '<S47>/Constant3'
     *  DiscreteIntegrator: '<S47>/Theta_Ref'
     *  RelationalOperator: '<S58>/UpperRelop'
     */
    if (RMT_FDM_DLL_FrameWork_FCS_RT_DW->Theta_Ref_DSTATE < -0.52359877559829882)
    {
      b_Switch_ljfr = -0.52359877559829882;
    } else {
      b_Switch_ljfr = RMT_FDM_DLL_FrameWork_FCS_RT_DW->Theta_Ref_DSTATE;
    }

    /* End of Switch: '<S58>/Switch' */

    /* Switch: '<S58>/Switch2' incorporates:
     *  Constant: '<S47>/Constant2'
     *  DiscreteIntegrator: '<S47>/Theta_Ref'
     *  RelationalOperator: '<S58>/LowerRelop1'
     */
    if (RMT_FDM_DLL_FrameWork_FCS_RT_DW->Theta_Ref_DSTATE > 0.52359877559829882)
    {
      b_Switch2_gt5e = 0.52359877559829882;
    } else {
      b_Switch2_gt5e = b_Switch_ljfr;
    }

    /* End of Switch: '<S58>/Switch2' */

    /* DiscreteIntegrator: '<S48>/p_Ref' */
    if (b_Switch.arm_swi &&
        (RMT_FDM_DLL_FrameWork_FCS_RT_DW->p_Ref_PrevResetState <= 0)) {
      RMT_FDM_DLL_FrameWork_FCS_RT_DW->p_Ref_DSTATE = 0.0;
    }

    /* SignalConversion generated from: '<S45>/Vector Concatenate' incorporates:
     *  DiscreteIntegrator: '<S48>/p_Ref'
     */
    b_Reshape_emto[0] = RMT_FDM_DLL_FrameWork_FCS_RT_DW->p_Ref_DSTATE;

    /* DiscreteIntegrator: '<S48>/q_Ref' */
    if (b_Switch.arm_swi &&
        (RMT_FDM_DLL_FrameWork_FCS_RT_DW->q_Ref_PrevResetState <= 0)) {
      RMT_FDM_DLL_FrameWork_FCS_RT_DW->q_Ref_DSTATE = 0.0;
    }

    b_dw_C_EC_mDs = RMT_FDM_DLL_FrameWork_FCS_RT_DW->q_Ref_DSTATE;

    /* End of DiscreteIntegrator: '<S48>/q_Ref' */

    /* SignalConversion generated from: '<S45>/Vector Concatenate' */
    b_Reshape_emto[1] = b_dw_C_EC_mDs;

    /* DiscreteIntegrator: '<S48>/r_Ref' */
    if (b_Switch.arm_swi &&
        (RMT_FDM_DLL_FrameWork_FCS_RT_DW->r_Ref_PrevResetState <= 0)) {
      RMT_FDM_DLL_FrameWork_FCS_RT_DW->r_Ref_DSTATE = 0.0;
    }

    b_w_K_R_E_C_est_mDs = RMT_FDM_DLL_FrameWork_FCS_RT_DW->r_Ref_DSTATE;

    /* End of DiscreteIntegrator: '<S48>/r_Ref' */

    /* SignalConversion generated from: '<S45>/Vector Concatenate' */
    b_Reshape_emto[2] = b_w_K_R_E_C_est_mDs;

    /* Trigonometry: '<S45>/Trigonometric Function2' incorporates:
     *  SignalConversion: '<S47>/Signal Copy1'
     *  Trigonometry: '<S45>/Trigonometric Function3'
     *  Trigonometry: '<S49>/Trigonometric Function2'
     *  Trigonometry: '<S51>/Trigonometric Function5'
     */
    b_Product4_tmp = tan(b_Switch2_gt5e);

    /* Trigonometry: '<S45>/Trigonometric Function' incorporates:
     *  SignalConversion: '<S47>/Signal Copy'
     *  Trigonometry: '<S45>/Trigonometric Function5'
     *  Trigonometry: '<S45>/Trigonometric Function6'
     *  Trigonometry: '<S52>/Trigonometric Function'
     *  Trigonometry: '<S52>/Trigonometric Function6'
     */
    b_Product4_tmp_0 = sin(b_Switch2);

    /* Trigonometry: '<S45>/Trigonometric Function1' incorporates:
     *  SignalConversion: '<S47>/Signal Copy'
     *  Trigonometry: '<S45>/Trigonometric Function4'
     *  Trigonometry: '<S45>/Trigonometric Function9'
     *  Trigonometry: '<S52>/Trigonometric Function4'
     *  Trigonometry: '<S52>/Trigonometric Function9'
     */
    b_Product4_tmp_1 = cos(b_Switch2);

    /* Trigonometry: '<S45>/Trigonometric Function7' incorporates:
     *  SignalConversion: '<S47>/Signal Copy1'
     *  Trigonometry: '<S45>/Trigonometric Function8'
     *  Trigonometry: '<S49>/Trigonometric Function'
     *  Trigonometry: '<S50>/Trigonometric Function3'
     *  Trigonometry: '<S51>/Trigonometric Function4'
     *  Trigonometry: '<S52>/Trigonometric Function1'
     *  Trigonometry: '<S52>/Trigonometric Function8'
     */
    b_Product4_tmp_2 = cos(b_Switch2_gt5e);

    /* Reshape: '<S45>/Reshape' incorporates:
     *  Constant: '<S45>/Constant'
     *  Product: '<S45>/Product'
     *  Product: '<S45>/Product1'
     *  Trigonometry: '<S45>/Trigonometric Function'
     *  Trigonometry: '<S45>/Trigonometric Function1'
     *  Trigonometry: '<S45>/Trigonometric Function2'
     */
    tmp_0[0] = 1.0;
    tmp_0[1] = b_Product4_tmp_0 * b_Product4_tmp;
    tmp_0[2] = b_Product4_tmp_1 * b_Product4_tmp;

    /* Reshape: '<S45>/Reshape1' incorporates:
     *  Constant: '<S45>/Constant1'
     *  Trigonometry: '<S45>/Trigonometric Function4'
     *  UnaryMinus: '<S45>/Unary Minus'
     */
    tmp_1[0] = 0.0;
    tmp_1[1] = b_Product4_tmp_1;
    tmp_1[2] = -b_Product4_tmp_0;

    /* Reshape: '<S45>/Reshape2' incorporates:
     *  Constant: '<S45>/Constant2'
     *  Product: '<S45>/Product2'
     *  Product: '<S45>/Product3'
     *  Trigonometry: '<S45>/Trigonometric Function7'
     */
    tmp_2[0] = 0.0;
    tmp_2[1] = b_Product4_tmp_0 / b_Product4_tmp_2;
    tmp_2[2] = b_Product4_tmp_1 / b_Product4_tmp_2;

    /* Concatenate: '<S45>/Matrix Concatenate' */
    for (i_1w = 0; i_1w < 3; i_1w = i_1w + 1) {
      tmp_3[3 * i_1w] = tmp_0[i_1w];
    }

    for (i_1x = 0; i_1x < 3; i_1x = i_1x + 1) {
      tmp_3[1 + 3 * i_1x] = tmp_1[i_1x];
    }

    for (i_1y = 0; i_1y < 3; i_1y = i_1y + 1) {
      tmp_3[2 + 3 * i_1y] = tmp_2[i_1y];
    }

    /* End of Concatenate: '<S45>/Matrix Concatenate' */

    /* Product: '<S45>/Product4' incorporates:
     *  Reshape: '<S52>/Reshape'
     */
    for (i_1z = 0; i_1z < 3; i_1z = i_1z + 1) {
      b_Product4[i_1z] = 0.0;
      for (i_20 = 0; i_20 < 3; i_20 = i_20 + 1) {
        b_Product4[i_1z] = b_Product4[i_1z] + tmp_3[i_1z + 3 * i_20] *
          b_Reshape_emto[i_20];
      }
    }

    /* End of Product: '<S45>/Product4' */

    /* DiscreteIntegrator: '<S62>/Discrete-Time Integrator' */
    if (b_Switch.arm_swi &&
        (RMT_FDM_DLL_FrameWork_FCS_RT_DW->DiscreteTimeIntegrator_PrevResetState <=
         0)) {
      RMT_FDM_DLL_FrameWork_FCS_RT_DW->DiscreteTimeIntegrator_DSTATE = 0.0;
    }

    b_du_C_EC_mDs2 =
      RMT_FDM_DLL_FrameWork_FCS_RT_DW->DiscreteTimeIntegrator_DSTATE;

    /* End of DiscreteIntegrator: '<S62>/Discrete-Time Integrator' */

    /* Saturate: '<S62>/cmd_lim' */
    if (b_Switch.vel_K_R_E_C_cmd_mDs.u_K_R_E_C_cmd_mDs > 2.0) {
      b_v_K_R_E_C_est_mDs = 2.0;
    } else if (b_Switch.vel_K_R_E_C_cmd_mDs.u_K_R_E_C_cmd_mDs < -2.0) {
      b_v_K_R_E_C_est_mDs = -2.0;
    } else {
      b_v_K_R_E_C_est_mDs = b_Switch.vel_K_R_E_C_cmd_mDs.u_K_R_E_C_cmd_mDs;
    }

    /* End of Saturate: '<S62>/cmd_lim' */

    /* Product: '<S62>/Divide' incorporates:
     *  Constant: '<S62>/Constant'
     *  Sum: '<S62>/Sum'
     */
    b_v_K_R_E_C_est_mDs = 1.6666666666666667 * (b_v_K_R_E_C_est_mDs -
      b_du_C_EC_mDs2);

    /* Saturate: '<S62>/nu_limit' */
    if (b_v_K_R_E_C_est_mDs > 10.0) {
      b_nu_limit = 10.0;
    } else if (b_v_K_R_E_C_est_mDs < -10.0) {
      b_nu_limit = -10.0;
    } else {
      b_nu_limit = b_v_K_R_E_C_est_mDs;
    }

    /* End of Saturate: '<S62>/nu_limit' */

    /* DiscreteIntegrator: '<S63>/Discrete-Time Integrator' */
    if (b_Switch.arm_swi &&
        (RMT_FDM_DLL_FrameWork_FCS_RT_DW->DiscreteTimeIntegrator_PrevResetState_nmap
         <= 0)) {
      RMT_FDM_DLL_FrameWork_FCS_RT_DW->DiscreteTimeIntegrator_DSTATE_hs0d = 0.0;
    }

    b_v_K_R_E_C_est_mDs =
      RMT_FDM_DLL_FrameWork_FCS_RT_DW->DiscreteTimeIntegrator_DSTATE_hs0d;

    /* End of DiscreteIntegrator: '<S63>/Discrete-Time Integrator' */

    /* Saturate: '<S63>/cmd_lim' */
    if (b_Switch.vel_K_R_E_C_cmd_mDs.v_K_R_E_C_cmd_mDs > 2.0) {
      b_v_C_ref_mDs = 2.0;
    } else if (b_Switch.vel_K_R_E_C_cmd_mDs.v_K_R_E_C_cmd_mDs < -2.0) {
      b_v_C_ref_mDs = -2.0;
    } else {
      b_v_C_ref_mDs = b_Switch.vel_K_R_E_C_cmd_mDs.v_K_R_E_C_cmd_mDs;
    }

    /* End of Saturate: '<S63>/cmd_lim' */

    /* Product: '<S63>/Divide' incorporates:
     *  Constant: '<S63>/Constant'
     *  Sum: '<S63>/Sum'
     */
    b_v_C_ref_mDs = 5.5555555555555554 * (b_v_C_ref_mDs - b_v_K_R_E_C_est_mDs);

    /* Saturate: '<S63>/nu_limit' */
    if (b_v_C_ref_mDs > 10.0) {
      b_nu_limit_occu = 10.0;
    } else if (b_v_C_ref_mDs < -10.0) {
      b_nu_limit_occu = -10.0;
    } else {
      b_nu_limit_occu = b_v_C_ref_mDs;
    }

    /* End of Saturate: '<S63>/nu_limit' */

    /* DiscreteIntegrator: '<S64>/Discrete-Time Integrator' */
    if (b_Switch.arm_swi &&
        (RMT_FDM_DLL_FrameWork_FCS_RT_DW->DiscreteTimeIntegrator_PrevResetState_fwtq
         <= 0)) {
      RMT_FDM_DLL_FrameWork_FCS_RT_DW->DiscreteTimeIntegrator_DSTATE_japy = 0.0;
    }

    b_v_C_ref_mDs =
      RMT_FDM_DLL_FrameWork_FCS_RT_DW->DiscreteTimeIntegrator_DSTATE_japy;

    /* End of DiscreteIntegrator: '<S64>/Discrete-Time Integrator' */

    /* Saturate: '<S64>/cmd_lim' */
    if (b_Switch.vel_K_R_E_C_cmd_mDs.w_K_R_E_C_cmd_mDs > 2.0) {
      b_u_K_R_E_C_est_mDs = 2.0;
    } else if (b_Switch.vel_K_R_E_C_cmd_mDs.w_K_R_E_C_cmd_mDs < -2.0) {
      b_u_K_R_E_C_est_mDs = -2.0;
    } else {
      b_u_K_R_E_C_est_mDs = b_Switch.vel_K_R_E_C_cmd_mDs.w_K_R_E_C_cmd_mDs;
    }

    /* End of Saturate: '<S64>/cmd_lim' */

    /* Product: '<S64>/Divide' incorporates:
     *  Constant: '<S64>/Constant'
     *  Sum: '<S64>/Sum'
     */
    b_u_K_R_E_C_est_mDs = 1.6666666666666667 * (b_u_K_R_E_C_est_mDs -
      b_v_C_ref_mDs);

    /* Saturate: '<S64>/nu_limit' */
    if (b_u_K_R_E_C_est_mDs > 10.0) {
      b_nu_limit_abb3 = 10.0;
    } else if (b_u_K_R_E_C_est_mDs < -10.0) {
      b_nu_limit_abb3 = -10.0;
    } else {
      b_nu_limit_abb3 = b_u_K_R_E_C_est_mDs;
    }

    /* End of Saturate: '<S64>/nu_limit' */

    /* BusAssignment: '<S43>/Bus Assignment' */
    b_BusAssignment_gwea.RM_u_C.u_C_ref_mDs = b_du_C_EC_mDs2;
    b_BusAssignment_gwea.RM_v_C.v_C_ref_mDs = b_v_K_R_E_C_est_mDs;
    b_BusAssignment_gwea.RM_w_C.w_C_ref_mDs = b_v_C_ref_mDs;

    /* Constant: '<S52>/Constant' */
    b_Reshape1_km21[0] = 1.0;

    /* Constant: '<S52>/Constant3' */
    b_Reshape1_km21[1] = 0.0;

    /* Trigonometry: '<S52>/Trigonometric Function5' incorporates:
     *  SignalConversion: '<S47>/Signal Copy1'
     *  Trigonometry: '<S49>/Trigonometric Function1'
     */
    b_Reshape1_kwvo_tmp = sin(b_Switch2_gt5e);

    /* Gain: '<S52>/Gain' incorporates:
     *  Trigonometry: '<S52>/Trigonometric Function5'
     */
    b_Reshape1_km21[2] = -b_Reshape1_kwvo_tmp;

    /* Constant: '<S52>/Constant1' */
    b_Reshape2_fzce[0] = 0.0;

    /* Trigonometry: '<S52>/Trigonometric Function4' */
    b_Reshape2_fzce[1] = b_Product4_tmp_1;

    /* Product: '<S52>/Product' */
    b_Reshape2_fzce[2] = b_Product4_tmp_0 * b_Product4_tmp_2;

    /* Constant: '<S52>/Constant2' */
    b_Reshape2_k1zx[0] = 0.0;

    /* Gain: '<S52>/Gain1' */
    b_Reshape2_k1zx[1] = -b_Product4_tmp_0;

    /* Product: '<S52>/Product3' */
    b_Reshape2_k1zx[2] = b_Product4_tmp_1 * b_Product4_tmp_2;

    /* Trigonometry: '<S49>/Trigonometric Function2' */
    b_u_K_R_E_C_est_mDs = b_Product4_tmp;

    /* Product: '<S49>/Product' */
    b_v_C_ref_mDs = b_u_K_R_E_C_est_mDs * b_Product4[0] * b_Product4[1];

    /* Trigonometry: '<S49>/Trigonometric Function' */
    b_u_K_R_E_C_est_mDs = b_Product4_tmp_2;

    /* Product: '<S49>/Product1' incorporates:
     *  Product: '<S51>/Product5'
     */
    b_v_K_R_E_C_est_mDs_tmp = b_Product4[1] * b_Product4[2];
    b_v_K_R_E_C_est_mDs = b_v_K_R_E_C_est_mDs_tmp / b_u_K_R_E_C_est_mDs;

    /* Math: '<S49>/Math Function' */
    b_u_K_R_E_C_est_mDs = b_Product4[0] * b_Product4[0];

    /* Trigonometry: '<S49>/Trigonometric Function1' */
    b_du_C_EC_mDs2 = b_Reshape1_kwvo_tmp;

    /* Product: '<S49>/Product2' incorporates:
     *  Product: '<S50>/Product3'
     */
    b_dv_C_EC_mDs_tmp = b_Product4[0] * b_Product4[2];
    b_dv_C_EC_mDs = b_dv_C_EC_mDs_tmp * b_du_C_EC_mDs2;

    /* Sum: '<S49>/Add' */
    b_Reshape_m3a1[0] = ((b_v_C_ref_mDs + b_v_K_R_E_C_est_mDs) +
                         b_u_K_R_E_C_est_mDs) - b_dv_C_EC_mDs;

    /* UnaryMinus: '<S50>/Unary Minus' */
    b_dv_C_EC_mDs = -b_Product4_tmp_2;

    /* Product: '<S50>/Product3' */
    b_Reshape_m3a1[1] = b_dv_C_EC_mDs_tmp * b_dv_C_EC_mDs;

    /* Trigonometry: '<S51>/Trigonometric Function4' */
    b_dv_C_EC_mDs = b_Product4_tmp_2;

    /* Product: '<S51>/Product4' */
    b_u_K_R_E_C_est_mDs = b_Product4[0] * b_Product4[1] / b_dv_C_EC_mDs;

    /* Trigonometry: '<S51>/Trigonometric Function5' */
    b_dv_C_EC_mDs = b_Product4_tmp;

    /* Product: '<S51>/Product5' */
    b_v_C_ref_mDs = b_v_K_R_E_C_est_mDs_tmp * b_dv_C_EC_mDs;

    /* Sum: '<S51>/Add1' */
    b_Reshape_m3a1[2] = b_u_K_R_E_C_est_mDs + b_v_C_ref_mDs;

    /* Saturate: '<S46>/Phi_lim' */
    if (b_Switch.att_euler_cmd.Phi_cmd_rad > 0.52359879016876221) {
      b_dv_C_EC_mDs = 0.52359879016876221;
    } else if (b_Switch.att_euler_cmd.Phi_cmd_rad < -0.52359879016876221) {
      b_dv_C_EC_mDs = -0.52359879016876221;
    } else {
      b_dv_C_EC_mDs = b_Switch.att_euler_cmd.Phi_cmd_rad;
    }

    /* End of Saturate: '<S46>/Phi_lim' */

    /* Sum: '<S46>/Sum4' incorporates:
     *  SignalConversion: '<S47>/Signal Copy'
     */
    b_u_K_R_E_C_est_mDs = b_dv_C_EC_mDs - b_Switch2;

    /* Saturate: '<S46>/Phi_Error_Lim' */
    if (b_u_K_R_E_C_est_mDs > 0.52359879016876221) {
      b_dv_C_EC_mDs = 0.52359879016876221;
    } else if (b_u_K_R_E_C_est_mDs < -0.52359879016876221) {
      b_dv_C_EC_mDs = -0.52359879016876221;
    } else {
      b_dv_C_EC_mDs = b_u_K_R_E_C_est_mDs;
    }

    /* End of Saturate: '<S46>/Phi_Error_Lim' */

    /* Gain: '<S46>/Gain2' */
    b_Gain2 = 64.0 * b_dv_C_EC_mDs;

    /* Gain: '<S46>/Gain5' */
    b_dv_C_EC_mDs = 2.0 * b_Product4[0];

    /* Sum: '<S46>/Sum6' incorporates:
     *  Gain: '<S46>/Gain10'
     *  Gain: '<S46>/Gain11'
     */
    b_Reshape2_dywf[0] = b_Gain2 - 0.6 * (8.0 * b_dv_C_EC_mDs);

    /* Saturate: '<S46>/Saturation1' */
    if (b_Switch.att_euler_cmd.Theta_cmd_rad > 0.52359879) {
      b_dv_C_EC_mDs = 0.52359879;
    } else if (b_Switch.att_euler_cmd.Theta_cmd_rad < -0.52359879) {
      b_dv_C_EC_mDs = -0.52359879;
    } else {
      b_dv_C_EC_mDs = b_Switch.att_euler_cmd.Theta_cmd_rad;
    }

    /* End of Saturate: '<S46>/Saturation1' */

    /* Sum: '<S46>/Sum3' incorporates:
     *  SignalConversion: '<S47>/Signal Copy1'
     */
    b_u_K_R_E_C_est_mDs = b_dv_C_EC_mDs - b_Switch2_gt5e;

    /* Saturate: '<S46>/Theta_Error_Lim' */
    if (b_u_K_R_E_C_est_mDs > 0.52359879) {
      b_dv_C_EC_mDs = 0.52359879;
    } else if (b_u_K_R_E_C_est_mDs < -0.52359879) {
      b_dv_C_EC_mDs = -0.52359879;
    } else {
      b_dv_C_EC_mDs = b_u_K_R_E_C_est_mDs;
    }

    /* End of Saturate: '<S46>/Theta_Error_Lim' */

    /* Gain: '<S46>/Gain7' */
    b_Gain7 = 64.0 * b_dv_C_EC_mDs;

    /* Gain: '<S46>/Gain4' */
    b_dv_C_EC_mDs = 2.0 * b_Product4[1];

    /* Sum: '<S46>/Sum7' incorporates:
     *  Gain: '<S46>/Gain8'
     *  Gain: '<S46>/Gain9'
     */
    b_Reshape2_dywf[1] = b_Gain7 - 0.6 * (8.0 * b_dv_C_EC_mDs);

    /* Saturate: '<S46>/Limit_Psi_dot' */
    if (b_Switch.att_euler_cmd.Psi_dot_cmd_radDs > 0.52359879016876221) {
      b_dv_C_EC_mDs = 0.52359879016876221;
    } else if (b_Switch.att_euler_cmd.Psi_dot_cmd_radDs < -0.52359879016876221)
    {
      b_dv_C_EC_mDs = -0.52359879016876221;
    } else {
      b_dv_C_EC_mDs = b_Switch.att_euler_cmd.Psi_dot_cmd_radDs;
    }

    /* End of Saturate: '<S46>/Limit_Psi_dot' */

    /* Sum: '<S46>/Sum8' */
    b_u_K_R_E_C_est_mDs = b_dv_C_EC_mDs - b_Product4[2];

    /* Saturate: '<S46>/Limit_Psi_dot1' */
    if (b_u_K_R_E_C_est_mDs > 0.52359879016876221) {
      b_dv_C_EC_mDs = 0.52359879016876221;
    } else if (b_u_K_R_E_C_est_mDs < -0.52359879016876221) {
      b_dv_C_EC_mDs = -0.52359879016876221;
    } else {
      b_dv_C_EC_mDs = b_u_K_R_E_C_est_mDs;
    }

    /* End of Saturate: '<S46>/Limit_Psi_dot1' */

    /* Product: '<S46>/Divide' incorporates:
     *  Constant: '<S46>/Constant'
     */
    b_Reshape2_dywf[2] = b_dv_C_EC_mDs / 0.1;

    /* Sum: '<S44>/Add2' incorporates:
     *  Reshape: '<S40>/Reshape2'
     *  Reshape: '<S44>/Reshape'
     *  Reshape: '<S44>/Reshape1'
     *  Reshape: '<S44>/Reshape2'
     */
    for (i_21 = 0; i_21 < 3; i_21 = i_21 + 1) {
      b_Reshape2_dywf[i_21] = b_Reshape2_dywf[i_21] - b_Reshape_m3a1[i_21];
    }

    /* End of Sum: '<S44>/Add2' */

    /* Concatenate: '<S52>/Matrix Concatenate' incorporates:
     *  Reshape: '<S44>/Reshape2'
     *  Reshape: '<S52>/Reshape'
     *  Reshape: '<S52>/Reshape1'
     *  Reshape: '<S52>/Reshape2'
     */
    for (i_22 = 0; i_22 < 3; i_22 = i_22 + 1) {
      b_Reshape1_kwvo[3 * i_22] = b_Reshape1_km21[i_22];
    }

    for (i_23 = 0; i_23 < 3; i_23 = i_23 + 1) {
      b_Reshape1_kwvo[1 + 3 * i_23] = b_Reshape2_fzce[i_23];
    }

    for (i_24 = 0; i_24 < 3; i_24 = i_24 + 1) {
      b_Reshape1_kwvo[2 + 3 * i_24] = b_Reshape2_k1zx[i_24];
    }

    /* End of Concatenate: '<S52>/Matrix Concatenate' */

    /* Product: '<S44>/Product6' incorporates:
     *  Reshape: '<S40>/Reshape2'
     *  Reshape: '<S44>/Reshape3'
     */
    for (i_25 = 0; i_25 < 3; i_25 = i_25 + 1) {
      b_Reshape1_kwvo_0[i_25] = 0.0;
      for (i_26 = 0; i_26 < 3; i_26 = i_26 + 1) {
        b_Reshape1_kwvo_0[i_25] = b_Reshape1_kwvo_0[i_25] + b_Reshape1_kwvo[i_25
          + 3 * i_26] * b_Reshape2_dywf[i_26];
      }
    }

    for (i_27 = 0; i_27 < 3; i_27 = i_27 + 1) {
      b_Reshape2_dywf[i_27] = b_Reshape1_kwvo_0[i_27];
    }

    /* End of Product: '<S44>/Product6' */

    /* Saturate: '<S44>/Limit Roll Acceleration' incorporates:
     *  Reshape: '<S40>/Reshape2'
     *  Reshape: '<S44>/Reshape'
     */
    if (b_Reshape2_dywf[0] > 18.849555921538759) {
      b_dv_C_EC_mDs = 18.849555921538759;
    } else if (b_Reshape2_dywf[0] < -18.849555921538759) {
      b_dv_C_EC_mDs = -18.849555921538759;
    } else {
      b_dv_C_EC_mDs = b_Reshape2_dywf[0];
    }

    /* End of Saturate: '<S44>/Limit Roll Acceleration' */

    /* Saturate: '<S44>/Limit_Pitch_Acceleration' incorporates:
     *  Reshape: '<S40>/Reshape2'
     *  Reshape: '<S44>/Reshape'
     */
    if (b_Reshape2_dywf[1] > 18.849555921538759) {
      b_u_K_R_E_C_est_mDs = 18.849555921538759;
    } else if (b_Reshape2_dywf[1] < -18.849555921538759) {
      b_u_K_R_E_C_est_mDs = -18.849555921538759;
    } else {
      b_u_K_R_E_C_est_mDs = b_Reshape2_dywf[1];
    }

    /* End of Saturate: '<S44>/Limit_Pitch_Acceleration' */

    /* Saturate: '<S44>/Limit_Yaw_Acceleration' incorporates:
     *  Reshape: '<S40>/Reshape2'
     *  Reshape: '<S44>/Reshape'
     */
    if (b_Reshape2_dywf[2] > 62.831853071795862) {
      b_v_C_ref_mDs = 62.831853071795862;
    } else if (b_Reshape2_dywf[2] < -62.831853071795862) {
      b_v_C_ref_mDs = -62.831853071795862;
    } else {
      b_v_C_ref_mDs = b_Reshape2_dywf[2];
    }

    /* End of Saturate: '<S44>/Limit_Yaw_Acceleration' */

    /* BusAssignment: '<S40>/Bus Assignment' */
    b_fc_RM.RM_rate.RM_q.q_ref_radDs = b_dw_C_EC_mDs;
    b_fc_RM.RM_rate.RM_r.r_ref_radDs = b_w_K_R_E_C_est_mDs;
    b_fc_RM.RM_rate.RM_p.nu_p_radDs2 = b_dv_C_EC_mDs;
    b_fc_RM.RM_rate.RM_q.nu_q_radDs2 = b_u_K_R_E_C_est_mDs;
    b_fc_RM.RM_rate.RM_r.nu_r_radDs2 = b_v_C_ref_mDs;

    /* SignalConversion generated from: '<S5>/Vector Concatenate' incorporates:
     *  BusAssignment: '<S43>/Bus Assignment'
     */
    b_nu_ref[0] = b_nu_limit;

    /* SignalConversion generated from: '<S5>/Vector Concatenate' incorporates:
     *  BusAssignment: '<S43>/Bus Assignment'
     */
    b_nu_ref[1] = b_nu_limit_occu;

    /* SignalConversion generated from: '<S5>/Vector Concatenate' incorporates:
     *  BusAssignment: '<S43>/Bus Assignment'
     */
    b_nu_ref[2] = b_nu_limit_abb3;

    /* SignalConversion generated from: '<S5>/Vector Concatenate' incorporates:
     *  BusAssignment: '<S40>/Bus Assignment'
     */
    b_nu_ref[3] = b_dv_C_EC_mDs;

    /* SignalConversion generated from: '<S5>/Vector Concatenate' incorporates:
     *  BusAssignment: '<S40>/Bus Assignment'
     */
    b_nu_ref[4] = b_u_K_R_E_C_est_mDs;

    /* SignalConversion generated from: '<S5>/Vector Concatenate' incorporates:
     *  BusAssignment: '<S40>/Bus Assignment'
     */
    b_nu_ref[5] = b_v_C_ref_mDs;

    /* Sum: '<S28>/Sum2' incorporates:
     *  BusAssignment: '<S40>/Bus Assignment'
     *  Reshape: '<S14>/Reshape5'
     *  Reshape: '<S45>/Reshape'
     *  SignalConversion generated from: '<S13>/Vector Concatenate7'
     *  Sum: '<S28>/Sum1'
     */
    b_delta_nu[0] = b_BusAssignment_gwea.RM_u_C.u_C_ref_mDs - b_Reshape_pne4[0];

    /* Sum: '<S29>/Sum2' incorporates:
     *  BusAssignment: '<S40>/Bus Assignment'
     *  Reshape: '<S14>/Reshape5'
     *  Reshape: '<S45>/Reshape'
     *  SignalConversion generated from: '<S13>/Vector Concatenate8'
     *  Sum: '<S29>/Sum1'
     */
    b_delta_nu[1] = b_BusAssignment_gwea.RM_v_C.v_C_ref_mDs - b_Reshape_pne4[1];

    /* Sum: '<S30>/Sum1' incorporates:
     *  BusAssignment: '<S40>/Bus Assignment'
     *  Reshape: '<S14>/Reshape5'
     *  Reshape: '<S45>/Reshape'
     *  SignalConversion generated from: '<S13>/Vector Concatenate9'
     */
    b_v_K_R_E_C_est_mDs = b_BusAssignment_gwea.RM_w_C.w_C_ref_mDs -
      b_Reshape_pne4[2];

    /* Sum: '<S30>/Sum2' incorporates:
     *  Gain: '<S30>/Gain1'
     */
    b_delta_nu[2] = 1.5 * b_v_K_R_E_C_est_mDs;

    /* Sum: '<S25>/Sum1' incorporates:
     *  SignalConversion generated from: '<S14>/Vector Concatenate1'
     *  SignalConversion: '<S47>/Signal Copy'
     */
    b_v_K_R_E_C_est_mDs = b_Switch2 -
      RMT_FDM_DLL_FrameWork_FCS_RT_B->RT2.ahrs_meas.Phi_meas_rad;

    /* Gain: '<S25>/Gain1' */
    b_Gain1_il4c = 4.0 * b_v_K_R_E_C_est_mDs;

    /* Sum: '<S25>/Sum' incorporates:
     *  DiscreteIntegrator: '<S48>/p_Ref'
     *  SignalConversion generated from: '<S14>/Vector Concatenate'
     */
    b_v_K_R_E_C_est_mDs = RMT_FDM_DLL_FrameWork_FCS_RT_DW->p_Ref_DSTATE -
      RMT_FDM_DLL_FrameWork_FCS_RT_B->RT2.imu_meas.gyro_meas.w_x_K_IB_B_IMU_meas_radDs;

    /* Sum: '<S25>/Sum2' incorporates:
     *  Gain: '<S25>/Gain'
     */
    b_delta_nu[3] = b_Gain1_il4c + 4.0 * b_v_K_R_E_C_est_mDs;

    /* Sum: '<S27>/Sum1' incorporates:
     *  SignalConversion generated from: '<S14>/Vector Concatenate1'
     *  SignalConversion: '<S47>/Signal Copy1'
     */
    b_v_K_R_E_C_est_mDs = b_Switch2_gt5e -
      RMT_FDM_DLL_FrameWork_FCS_RT_B->RT2.ahrs_meas.Theta_meas_rad;

    /* Gain: '<S27>/Gain1' */
    b_Gain1_j3wv = 8.0 * b_v_K_R_E_C_est_mDs;

    /* Sum: '<S27>/Sum' incorporates:
     *  BusAssignment: '<S40>/Bus Assignment'
     *  SignalConversion generated from: '<S14>/Vector Concatenate'
     */
    b_v_K_R_E_C_est_mDs = b_dw_C_EC_mDs -
      RMT_FDM_DLL_FrameWork_FCS_RT_B->RT2.imu_meas.gyro_meas.w_y_K_IB_B_IMU_meas_radDs;

    /* Sum: '<S27>/Sum2' incorporates:
     *  Gain: '<S27>/Gain'
     */
    b_delta_nu[4] = b_Gain1_j3wv + 8.0 * b_v_K_R_E_C_est_mDs;

    /* Sum: '<S26>/Sum' incorporates:
     *  BusAssignment: '<S14>/Bus Assignment'
     *  BusAssignment: '<S40>/Bus Assignment'
     *  SignalConversion generated from: '<S13>/Vector Concatenate5'
     */
    b_v_K_R_E_C_est_mDs = b_Product4[2] -
      b_BusConversion_InsertedFor_BusAssignment_at_inport_3_BusCreator.Psi_Dot_est_radDs;

    /* Sum: '<S26>/Sum2' incorporates:
     *  Gain: '<S26>/Gain'
     */
    b_delta_nu[5] = 4.0 * b_v_K_R_E_C_est_mDs;

    /* Sum: '<S5>/Sum1' incorporates:
     *  Sum: '<S5>/Sum'
     */
    for (i_28 = 0; i_28 < 6; i_28 = i_28 + 1) {
      b_delta_nu[i_28] = (b_nu_ref[i_28] + b_delta_nu[i_28]) - b_nu_est[i_28];
    }

    /* End of Sum: '<S5>/Sum1' */

    /* Constant: '<S17>/Constant8' */
    for (i_8 = 0; i_8 < 2; i_8 = i_8 + 1) {
      b_VectorConcatenate_mbmr[i_8] = false;
    }

    /* End of Constant: '<S17>/Constant8' */

    /* DataTypeConversion: '<S17>/Data Type Conversion' */
    for (i_9 = 0; i_9 < 8; i_9 = i_9 + 1) {
      b_VectorConcatenate_mbmr[i_9 + 2] = false;
    }

    /* End of DataTypeConversion: '<S17>/Data Type Conversion' */

    /* MATLAB Function: '<S17>/Redistribution' incorporates:
     *  Constant: '<S17>/Constant1'
     *  Reshape: '<S17>/Reshape'
     */
    memcpy(&B[0], &rtCP_Constant1_Value_brmz[0], 60U * sizeof(real_T));
    for (i_29 = 0; i_29 < 6; i_29 = i_29 + 1) {
      nu[i_29] = b_delta_nu[i_29];
    }

    for (i_a = 0; i_a < 10; i_a = i_a + 1) {
      sf[i_a] = b_VectorConcatenate_mbmr[i_a];
    }

    memset(&b_nu_r[0], 0, 60U * sizeof(real_T));
    memset(&b_u[0], 0, 10U * sizeof(real_T));
    b_idx_0 = 0;
    exitg1 = false;
    while ((exitg1 == false) && (b_idx_0 < 10)) {
      for (i_b = 0; i_b < 10; i_b = i_b + 1) {
        ls[i_b] = !sf[i_b];
      }

      memset(&W[0], 0, 100U * sizeof(boolean_T));
      for (b_j = 0; b_j < 10; b_j = b_j + 1) {
        W[((b_j + 1) - 1) + 10 * ((b_j + 1) - 1)] = ls[(b_j + 1) - 1];
      }

      for (i_2a = 0; i_2a < 6; i_2a = i_2a + 1) {
        for (i_2b = 0; i_2b < 10; i_2b = i_2b + 1) {
          B_tmp = i_2a + 6 * i_2b;
          B_0[B_tmp] = 0.0;
          for (i_2c = 0; i_2c < 10; i_2c = i_2c + 1) {
            B_0[B_tmp] = B_0[B_tmp] + B[i_2a + 6 * i_2c] * (real_T)W[i_2c + 10 *
              i_2b];
          }
        }
      }

      memcpy(&B[0], &B_0[0], 60U * sizeof(real_T));
      for (i_2e = 0; i_2e < 6; i_2e = i_2e + 1) {
        for (i_2d = 0; i_2d < 10; i_2d = i_2d + 1) {
          A[i_2d + 10 * i_2e] = B[i_2e + 6 * i_2d];
        }
      }

      memcpy(&X[0], &o[0], 60U * sizeof(real_T));
      p = true;
      for (d_k = 0; d_k < 60; d_k = d_k + 1) {
        if (p) {
          b_x = A[(d_k + 1) - 1];
          if ((!rtIsInf(b_x)) && (!rtIsNaN(b_x))) {
            p = true;
          } else {
            p = false;
          }
        } else {
          p = false;
        }
      }

      if (!p) {
        for (i_2f = 0; i_2f < 60; i_2f = i_2f + 1) {
          X[i_2f] = (rtNaN);
        }
      } else {
        svd_i5n8QqSI(A, U, s, V);
        absx = fabs(s[0]);
        if ((!!rtIsInf(absx)) || (!!rtIsNaN(absx))) {
          b_r = (rtNaN);
        } else if (absx < 4.4501477170144028E-308) {
          b_r = 4.94065645841247E-324;
        } else {
          frexp(absx, &exponent);
          b_r = ldexp(1.0, exponent - 53);
        }

        tol = 10.0 * b_r;
        i = 0;
        exitg2 = false;
        while ((exitg2 == false) && (i < 6)) {
          tmp_9 = s[(i + 1) - 1];
          if ((!!rtIsInf(tmp_9)) || (!!rtIsNaN(tmp_9))) {
            tol = 1.7976931348623157E+308;
            exitg2 = true;
          } else {
            i = i + 1;
          }
        }

        r = 0;
        k = 0;
        while ((k < 6) && (s[(k + 1) - 1] > tol)) {
          r = r + 1;
          k = k + 1;
        }

        if (r > 0) {
          vcol = 1;
          d = (int32_T)(uint32_T)r;
          for (c_j = 0; c_j < d; c_j = c_j + 1) {
            a = 1.0 / s[(c_j + 1) - 1];
            m = vcol + 5;
            for (c_k = vcol; c_k <= m; c_k = c_k + 1) {
              V[c_k - 1] = a * V[c_k - 1];
            }

            vcol = vcol + 6;
          }

          for (cr = 0; cr <= 54; cr = cr + 6) {
            if (cr + 1 <= cr + 6) {
              memset(&X[(cr + 1) + -1], 0, (uint32_T)(((cr + 6) - (cr + 1)) + 1)
                     * sizeof(real_T));
            }
          }

          br = 0;
          for (b_cr = 0; b_cr <= 54; b_cr = b_cr + 6) {
            ar = 0;
            br = br + 1;
            g = br + 10 * (r - 1);
            for (ib = br; ib <= g; ib = ib + 10) {
              ia = ar;
              h = b_cr + 1;
              l = b_cr + 6;
              for (b_ic = h; b_ic <= l; b_ic = b_ic + 1) {
                ia = ia + 1;
                X[b_ic - 1] = X[b_ic - 1] + U[ib - 1] * V[ia - 1];
              }

              ar = ar + 6;
            }
          }
        }
      }

      for (i_2g = 0; i_2g < 10; i_2g = i_2g + 1) {
        for (i_2h = 0; i_2h < 6; i_2h = i_2h + 1) {
          W_tmp = i_2g + 10 * i_2h;
          W_0[W_tmp] = 0.0;
          for (i_2i = 0; i_2i < 10; i_2i = i_2i + 1) {
            W_0[W_tmp] = W_0[W_tmp] + (real_T)W[i_2g + 10 * i_2i] * X[i_2h + 6 *
              i_2i];
          }
        }
      }

      for (i_2j = 0; i_2j < 10; i_2j = i_2j + 1) {
        u_tmp[i_2j] = 0.0;
        for (i_2k = 0; i_2k < 6; i_2k = i_2k + 1) {
          u_tmp[i_2j] = u_tmp[i_2j] + W_0[i_2j + 10 * i_2k] * nu[i_2k];
        }
      }

      for (i_c = 0; i_c < 10; i_c = i_c + 1) {
        ls[i_c] = (u_tmp[i_c] <= rtCP_Constant2_Value[i_c]);
      }

      for (i_d = 0; i_d < 10; i_d = i_d + 1) {
        us[i_d] = (u_tmp[i_d] >= rtCP_Constant3_Value[i_d]);
      }

      for (i_2m = 0; i_2m < 10; i_2m = i_2m + 1) {
        sf[i_2m] = (sf[i_2m] || ls[i_2m] || us[i_2m]);
      }

      y = false;
      e_k = 0;
      exitg2 = false;
      while ((exitg2 == false) && (e_k < 10)) {
        if ((!ls[(e_k + 1) - 1]) && (!us[(e_k + 1) - 1])) {
          n = true;
        } else {
          n = false;
        }

        if (!n) {
          y = true;
          exitg2 = true;
        } else {
          e_k = e_k + 1;
        }
      }

      if (!y) {
        for (i_2t = 0; i_2t < 10; i_2t = i_2t + 1) {
          b_u[i_2t] = b_u[i_2t] + u_tmp[i_2t];
        }

        for (i_2u = 0; i_2u < 6; i_2u = i_2u + 1) {
          b_nu_r_tmp = i_2u + 6 * ((b_idx_0 + 1) - 1);
          b_nu_r[b_nu_r_tmp] = 0.0;
          for (i_2v = 0; i_2v < 10; i_2v = i_2v + 1) {
            b_nu_r[b_nu_r_tmp] = b_nu_r[b_nu_r_tmp] + B[i_2u + 6 * i_2v] *
              b_u[i_2v];
          }
        }

        exitg1 = true;
      } else {
        b_y = true;
        f_k = 0;
        exitg2 = false;
        while ((exitg2 == false) && (f_k < 10)) {
          if (!sf[(f_k + 1) - 1]) {
            b_y = false;
            exitg2 = true;
          } else {
            f_k = f_k + 1;
          }
        }

        if (b_y) {
          for (h_k = 0; h_k < 10; h_k = h_k + 1) {
            minval[(h_k + 1) - 1] = fmin(u_tmp[(h_k + 1) - 1],
              rtCP_Constant3_Value[(h_k + 1) - 1]);
          }

          for (j_k = 0; j_k < 10; j_k = j_k + 1) {
            u_tmp[(j_k + 1) - 1] = fmax(rtCP_Constant2_Value[(j_k + 1) - 1],
              minval[(j_k + 1) - 1]);
          }

          for (i_2w = 0; i_2w < 10; i_2w = i_2w + 1) {
            b_u[i_2w] = b_u[i_2w] + u_tmp[i_2w];
          }

          for (i_2z = 0; i_2z < 6; i_2z = i_2z + 1) {
            b_nu_r_tmp_0 = i_2z + 6 * ((b_idx_0 + 1) - 1);
            b_nu_r[b_nu_r_tmp_0] = 0.0;
            for (i_30 = 0; i_30 < 10; i_30 = i_30 + 1) {
              b_nu_r[b_nu_r_tmp_0] = b_nu_r[b_nu_r_tmp_0] + B[i_2z + 6 * i_30] *
                b_u[i_30];
            }
          }

          exitg1 = true;
        } else {
          for (i_l = 0; i_l < 10; i_l = i_l + 1) {
            if (ls[i_l]) {
              b_u[i_l] = rtCP_Constant2_Value[i_l];
            }
          }

          for (i_m = 0; i_m < 10; i_m = i_m + 1) {
            if (us[i_m]) {
              b_u[i_m] = rtCP_Constant3_Value[i_m];
            }
          }

          for (i_2x = 0; i_2x < 6; i_2x = i_2x + 1) {
            nu_tmp[i_2x] = 0.0;
            for (i_2y = 0; i_2y < 10; i_2y = i_2y + 1) {
              nu_tmp[i_2x] = nu_tmp[i_2x] + B[i_2x + 6 * i_2y] * b_u[i_2y];
            }
          }

          for (i_31 = 0; i_31 < 6; i_31 = i_31 + 1) {
            nu[i_31] = nu[i_31] - nu_tmp[i_31];
          }

          for (i_32 = 0; i_32 < 6; i_32 = i_32 + 1) {
            b_nu_r[i_32 + 6 * ((b_idx_0 + 1) - 1)] = nu_tmp[i_32];
          }

          b_idx_0 = b_idx_0 + 1;
        }
      }
    }

    /* End of MATLAB Function: '<S17>/Redistribution' */
    /* MATLAB Function: '<S19>/nullspace' incorporates:
     *  Constant: '<S17>/Constant1'
     */
    p_0 = true;
    for (b_k = 0; b_k < 60; b_k = b_k + 1) {
      if (p_0) {
        b_x_0 = rtCP_Constant1_Value_brmz[(b_k + 1) - 1];
        if ((!rtIsInf(b_x_0)) && (!rtIsNaN(b_x_0))) {
          p_0 = true;
        } else {
          p_0 = false;
        }
      } else {
        p_0 = false;
      }
    }

    if (!p_0) {
      N_M_tmp_size[0] = 10;
      N_M_tmp_size[1] = 10;
      memcpy(&N_M_tmp_data[0], &e_1[0], 100U * sizeof(real_T));
    } else {
      svd_o1L0Nv3Z(rtCP_Constant1_Value_brmz, a__1, s_0, V_0);
      r_0 = 1;
      absx_0 = fabs(s_0[0]);
      if ((!!rtIsInf(absx_0)) || (!!rtIsNaN(absx_0))) {
        b_r_0 = (rtNaN);
      } else if (absx_0 < 4.4501477170144028E-308) {
        b_r_0 = 4.94065645841247E-324;
      } else {
        frexp(absx_0, &exponent_0);
        b_r_0 = ldexp(1.0, exponent_0 - 53);
      }

      tol_0 = 10.0 * b_r_0;
      i_0 = 0;
      exitg1 = false;
      while ((exitg1 == false) && (i_0 < 6)) {
        tmp_8 = s_0[(i_0 + 1) - 1];
        if ((!!rtIsInf(tmp_8)) || (!!rtIsNaN(tmp_8))) {
          tol_0 = 1.7976931348623157E+308;
          exitg1 = true;
        } else {
          i_0 = i_0 + 1;
        }
      }

      for (k_0 = 0; k_0 < 6; k_0 = k_0 + 1) {
        r_0 = r_0 + (s_0[(k_0 + 1) - 1] > tol_0);
      }

      N_M_tmp_size[0] = 10;
      N_M_tmp_size[1] = (9 - (r_0 - 1)) + 1;
      loop_ub_0 = ((9 - (r_0 - 1)) + 1) - 1;
      for (i_2n = 0; i_2n <= loop_ub_0; i_2n = i_2n + 1) {
        memcpy(&N_M_tmp_data[i_2n * 10], &V_0[(i_2n * 10 + r_0 * 10) + -10], 10U
               * sizeof(real_T));
      }
    }

    b_p = true;
    d_0 = (uint8_T)(10 * N_M_tmp_size[1]);
    for (d_k_0 = 0; d_k_0 < d_0; d_k_0 = d_k_0 + 1) {
      if (b_p) {
        d_x = N_M_tmp_data[(d_k_0 + 1) - 1];
        if ((!rtIsInf(d_x)) && (!rtIsNaN(d_x))) {
          b_p = true;
        } else {
          b_p = false;
        }
      } else {
        b_p = false;
      }
    }

    if (!!b_p) {
      svd_I60xL6TN(N_M_tmp_data, N_M_tmp_size, b_s_data, &b_s_size);
    } else {
      loop_ub = (int32_T)(real_T)N_M_tmp_size[1] - 1;
      for (i_2l = 0; i_2l <= loop_ub; i_2l = i_2l + 1) {
        b_s_data[i_2l] = (rtNaN);
      }
    }

    b_absx = fabs(b_s_data[0]);
    if ((!rtIsInf(b_absx)) && (!rtIsNaN(b_absx)) && (!(b_absx <
          4.4501477170144028E-308))) {
      frexp(b_absx, &b_exponent);
    }

    for (i_2p = 0; i_2p < 4; i_2p = i_2p + 1) {
      for (i_2o = 0; i_2o < 10; i_2o = i_2o + 1) {
        b_N_M[i_2o + 10 * i_2p] = N_M_tmp_data[i_2o + 10 * f_1[i_2p]];
      }
    }

    /* Product: '<S19>/Product6' incorporates:
     *  Constant: '<S17>/Constant6'
     */
    for (i_2q = 0; i_2q < 4; i_2q = i_2q + 1) {
      for (i_2r = 0; i_2r < 4; i_2r = i_2r + 1) {
        b_Product6_tmp = i_2q + (i_2r << 2);
        b_Product6[b_Product6_tmp] = 0.0;
        for (i_2s = 0; i_2s < 10; i_2s = i_2s + 1) {
          b_Product6[b_Product6_tmp] = b_Product6[b_Product6_tmp] +
            rtCP_Constant6_Value_kakl[i_2q + (i_2s << 2)] * b_N_M[i_2s + 10 *
            i_2r];
        }
      }
    }

    /* End of Product: '<S19>/Product6' */

    /* MATLAB Function: '<S19>/Pseudoinverse' incorporates:
     *  Product: '<S19>/Product6'
     */
    memcpy(&b_X[0], &l_0[0], 16U * sizeof(real_T));
    p_1 = true;
    for (c_k_0 = 0; c_k_0 < 16; c_k_0 = c_k_0 + 1) {
      if (p_1) {
        b_x_1 = b_Product6[(c_k_0 + 1) - 1];
        if ((!rtIsInf(b_x_1)) && (!rtIsNaN(b_x_1))) {
          p_1 = true;
        } else {
          p_1 = false;
        }
      } else {
        p_1 = false;
      }
    }

    if (!p_1) {
      for (i_e = 0; i_e < 16; i_e = i_e + 1) {
        b_X[i_e] = (rtNaN);
      }
    } else {
      svd_NJw3JjRP(b_Product6, U_0, s_1, V_1);
      absx_1 = fabs(s_1[0]);
      if ((!!rtIsInf(absx_1)) || (!!rtIsNaN(absx_1))) {
        b_r_1 = (rtNaN);
      } else if (absx_1 < 4.4501477170144028E-308) {
        b_r_1 = 4.94065645841247E-324;
      } else {
        frexp(absx_1, &exponent_1);
        b_r_1 = ldexp(1.0, exponent_1 - 53);
      }

      tol_1 = 4.0 * b_r_1;
      i_1 = 0;
      exitg1 = false;
      while ((exitg1 == false) && (i_1 < 4)) {
        tmp_a = s_1[(i_1 + 1) - 1];
        if ((!!rtIsInf(tmp_a)) || (!!rtIsNaN(tmp_a))) {
          tol_1 = 1.7976931348623157E+308;
          exitg1 = true;
        } else {
          i_1 = i_1 + 1;
        }
      }

      r_1 = 0;
      k_1 = 0;
      while ((k_1 < 4) && (s_1[(k_1 + 1) - 1] > tol_1)) {
        r_1 = r_1 + 1;
        k_1 = k_1 + 1;
      }

      if (r_1 > 0) {
        vcol_0 = 1;
        b = (int32_T)(uint32_T)r_1;
        for (j = 0; j < b; j = j + 1) {
          a_0 = 1.0 / s_1[(j + 1) - 1];
          h_0 = vcol_0 + 3;
          for (b_k_0 = vcol_0; b_k_0 <= h_0; b_k_0 = b_k_0 + 1) {
            V_1[b_k_0 - 1] = a_0 * V_1[b_k_0 - 1];
          }

          vcol_0 = vcol_0 + 4;
        }

        for (cr_0 = 0; cr_0 <= 12; cr_0 = cr_0 + 4) {
          if (cr_0 + 1 <= cr_0 + 4) {
            memset(&b_X[(cr_0 + 1) + -1], 0, (uint32_T)(((cr_0 + 4) - (cr_0 + 1))
                    + 1) * sizeof(real_T));
          }
        }

        br_0 = 0;
        for (b_cr_0 = 0; b_cr_0 <= 12; b_cr_0 = b_cr_0 + 4) {
          ar_0 = 0;
          br_0 = br_0 + 1;
          e = br_0 + ((r_1 - 1) << 2);
          for (ib_0 = br_0; ib_0 <= e; ib_0 = ib_0 + 4) {
            ia_0 = ar_0;
            f = b_cr_0 + 1;
            g_0 = b_cr_0 + 4;
            for (b_ic_0 = f; b_ic_0 <= g_0; b_ic_0 = b_ic_0 + 1) {
              ia_0 = ia_0 + 1;
              b_X[b_ic_0 - 1] = b_X[b_ic_0 - 1] + U_0[ib_0 - 1] * V_1[ia_0 - 1];
            }

            ar_0 = ar_0 + 4;
          }
        }
      }
    }

    b_p_0 = true;
    for (e_k_0 = 0; e_k_0 < 16; e_k_0 = e_k_0 + 1) {
      if (b_p_0) {
        d_x_0 = b_Product6[(e_k_0 + 1) - 1];
        if ((!rtIsInf(d_x_0)) && (!rtIsNaN(d_x_0))) {
          b_p_0 = true;
        } else {
          b_p_0 = false;
        }
      } else {
        b_p_0 = false;
      }
    }

    if (!!b_p_0) {
      svd_LrtoIvAo(b_Product6, s_1);
    } else {
      for (i_k = 0; i_k < 4; i_k = i_k + 1) {
        s_1[i_k] = m_0[i_k];
      }
    }

    b_absx_0 = fabs(s_1[0]);
    if ((!rtIsInf(b_absx_0)) && (!rtIsNaN(b_absx_0)) && (!(b_absx_0 <
          4.4501477170144028E-308))) {
      frexp(b_absx_0, &b_exponent_0);
    }

    /* DiscreteIntegrator: '<S10>/Discrete-Time Integrator' */
    if (RMT_FDM_DLL_FrameWork_FCS_RT_DW->DiscreteTimeIntegrator_IC_LOADING != 0)
    {
      memcpy
        (&RMT_FDM_DLL_FrameWork_FCS_RT_DW->DiscreteTimeIntegrator_DSTATE_avov[0],
         &RMT_FDM_DLL_FrameWork_FCS_RT_B->RT3.actuator.u_0_radDs[0], 8U * sizeof
         (real_T));
      for (i_2 = 0; i_2 < 8; i_2 = i_2 + 1) {
        if (RMT_FDM_DLL_FrameWork_FCS_RT_DW->
            DiscreteTimeIntegrator_DSTATE_avov[i_2] > 2712.0) {
          RMT_FDM_DLL_FrameWork_FCS_RT_DW->
            DiscreteTimeIntegrator_DSTATE_avov[i_2] = 2712.0;
        } else if
            (RMT_FDM_DLL_FrameWork_FCS_RT_DW->
             DiscreteTimeIntegrator_DSTATE_avov[i_2] < 0.0) {
          RMT_FDM_DLL_FrameWork_FCS_RT_DW->
            DiscreteTimeIntegrator_DSTATE_avov[i_2] = 0.0;
        }
      }
    }

    if (RMT_FDM_DLL_FrameWork_FCS_RT_B->RT1.arm_swi &&
        (RMT_FDM_DLL_FrameWork_FCS_RT_DW->DiscreteTimeIntegrator_PrevResetState_dbpn
         <= 0)) {
      memcpy
        (&RMT_FDM_DLL_FrameWork_FCS_RT_DW->DiscreteTimeIntegrator_DSTATE_avov[0],
         &RMT_FDM_DLL_FrameWork_FCS_RT_B->RT3.actuator.u_0_radDs[0], 8U * sizeof
         (real_T));
      for (i_2 = 0; i_2 < 8; i_2 = i_2 + 1) {
        if (RMT_FDM_DLL_FrameWork_FCS_RT_DW->
            DiscreteTimeIntegrator_DSTATE_avov[i_2] > 2712.0) {
          RMT_FDM_DLL_FrameWork_FCS_RT_DW->
            DiscreteTimeIntegrator_DSTATE_avov[i_2] = 2712.0;
        } else if
            (RMT_FDM_DLL_FrameWork_FCS_RT_DW->
             DiscreteTimeIntegrator_DSTATE_avov[i_2] < 0.0) {
          RMT_FDM_DLL_FrameWork_FCS_RT_DW->
            DiscreteTimeIntegrator_DSTATE_avov[i_2] = 0.0;
        }
      }
    }

    /* Gain: '<S18>/Gain' incorporates:
     *  DiscreteIntegrator: '<S10>/Discrete-Time Integrator'
     */
    b_v_K_R_E_C_est_mDs = 0.00032552083333333332 *
      RMT_FDM_DLL_FrameWork_FCS_RT_DW->DiscreteTimeIntegrator_DSTATE_avov[0];

    /* Gain: '<S18>/Gain3' incorporates:
     *  DiscreteIntegrator: '<S10>/Discrete-Time Integrator'
     */
    b_du_C_EC_mDs2 = 0.00032552083333333332 *
      RMT_FDM_DLL_FrameWork_FCS_RT_DW->DiscreteTimeIntegrator_DSTATE_avov[1];

    /* Gain: '<S18>/Gain4' incorporates:
     *  DiscreteIntegrator: '<S10>/Discrete-Time Integrator'
     */
    b_w_K_R_E_C_est_mDs = 0.00032552083333333332 *
      RMT_FDM_DLL_FrameWork_FCS_RT_DW->DiscreteTimeIntegrator_DSTATE_avov[2];

    /* Gain: '<S18>/Gain5' incorporates:
     *  DiscreteIntegrator: '<S10>/Discrete-Time Integrator'
     */
    b_dw_C_EC_mDs = 0.00032552083333333332 *
      RMT_FDM_DLL_FrameWork_FCS_RT_DW->DiscreteTimeIntegrator_DSTATE_avov[3];

    /* Gain: '<S18>/Gain10' incorporates:
     *  DiscreteIntegrator: '<S10>/Discrete-Time Integrator'
     *  Gain: '<S18>/Gain6'
     *  Gain: '<S18>/Gain7'
     *  Gain: '<S18>/Gain8'
     *  Gain: '<S18>/Gain9'
     *  Sum: '<S18>/Sum6'
     */
    b_VectorConcatenate_c4eb[0] = 0.125 * (((((((b_v_K_R_E_C_est_mDs +
      b_du_C_EC_mDs2) + b_w_K_R_E_C_est_mDs) + b_dw_C_EC_mDs) -
      0.00032552083333333332 *
      RMT_FDM_DLL_FrameWork_FCS_RT_DW->DiscreteTimeIntegrator_DSTATE_avov[4]) -
      0.00032552083333333332 *
      RMT_FDM_DLL_FrameWork_FCS_RT_DW->DiscreteTimeIntegrator_DSTATE_avov[5]) -
      0.00032552083333333332 *
      RMT_FDM_DLL_FrameWork_FCS_RT_DW->DiscreteTimeIntegrator_DSTATE_avov[6]) -
      0.00032552083333333332 *
      RMT_FDM_DLL_FrameWork_FCS_RT_DW->DiscreteTimeIntegrator_DSTATE_avov[7]);

    /* Gain: '<S18>/Gain11' incorporates:
     *  DiscreteIntegrator: '<S10>/Discrete-Time Integrator'
     */
    b_v_K_R_E_C_est_mDs = 0.00032552083333333332 *
      RMT_FDM_DLL_FrameWork_FCS_RT_DW->DiscreteTimeIntegrator_DSTATE_avov[0];

    /* Gain: '<S18>/Gain12' incorporates:
     *  DiscreteIntegrator: '<S10>/Discrete-Time Integrator'
     */
    b_du_C_EC_mDs2 = 0.00032552083333333332 *
      RMT_FDM_DLL_FrameWork_FCS_RT_DW->DiscreteTimeIntegrator_DSTATE_avov[5];

    /* Sum: '<S18>/Sum1' */
    b_Sum1 = b_v_K_R_E_C_est_mDs - b_du_C_EC_mDs2;

    /* Gain: '<S18>/Gain13' incorporates:
     *  DiscreteIntegrator: '<S10>/Discrete-Time Integrator'
     *  Gain: '<S18>/Gain22'
     */
    b_v_K_R_E_C_est_mDs_tmp_1 = 0.00032552083333333332 *
      RMT_FDM_DLL_FrameWork_FCS_RT_DW->DiscreteTimeIntegrator_DSTATE_avov[2];
    b_v_K_R_E_C_est_mDs = b_v_K_R_E_C_est_mDs_tmp_1;

    /* Gain: '<S18>/Gain14' incorporates:
     *  DiscreteIntegrator: '<S10>/Discrete-Time Integrator'
     *  Gain: '<S18>/Gain23'
     */
    b_du_C_EC_mDs2_tmp_0 = 0.00032552083333333332 *
      RMT_FDM_DLL_FrameWork_FCS_RT_DW->DiscreteTimeIntegrator_DSTATE_avov[7];
    b_du_C_EC_mDs2 = b_du_C_EC_mDs2_tmp_0;

    /* Gain: '<S18>/Gain1' incorporates:
     *  Sum: '<S18>/Sum3'
     *  Sum: '<S18>/Sum5'
     */
    b_VectorConcatenate_c4eb[1] = b_Sum1 - (b_v_K_R_E_C_est_mDs - b_du_C_EC_mDs2);

    /* Gain: '<S18>/Gain15' incorporates:
     *  DiscreteIntegrator: '<S10>/Discrete-Time Integrator'
     *  Gain: '<S18>/Gain19'
     */
    b_v_K_R_E_C_est_mDs_tmp_0 = 0.00032552083333333332 *
      RMT_FDM_DLL_FrameWork_FCS_RT_DW->DiscreteTimeIntegrator_DSTATE_avov[1];
    b_v_K_R_E_C_est_mDs = b_v_K_R_E_C_est_mDs_tmp_0;

    /* Gain: '<S18>/Gain16' incorporates:
     *  DiscreteIntegrator: '<S10>/Discrete-Time Integrator'
     *  Gain: '<S18>/Gain20'
     */
    b_du_C_EC_mDs2_tmp = 0.00032552083333333332 *
      RMT_FDM_DLL_FrameWork_FCS_RT_DW->DiscreteTimeIntegrator_DSTATE_avov[4];
    b_du_C_EC_mDs2 = b_du_C_EC_mDs2_tmp;

    /* Sum: '<S18>/Sum2' */
    b_Sum2 = b_v_K_R_E_C_est_mDs - b_du_C_EC_mDs2;

    /* Gain: '<S18>/Gain17' incorporates:
     *  DiscreteIntegrator: '<S10>/Discrete-Time Integrator'
     */
    b_v_K_R_E_C_est_mDs = 0.00032552083333333332 *
      RMT_FDM_DLL_FrameWork_FCS_RT_DW->DiscreteTimeIntegrator_DSTATE_avov[3];

    /* Gain: '<S18>/Gain18' incorporates:
     *  DiscreteIntegrator: '<S10>/Discrete-Time Integrator'
     */
    b_du_C_EC_mDs2 = 0.00032552083333333332 *
      RMT_FDM_DLL_FrameWork_FCS_RT_DW->DiscreteTimeIntegrator_DSTATE_avov[6];

    /* Gain: '<S18>/Gain2' incorporates:
     *  Sum: '<S18>/Sum'
     *  Sum: '<S18>/Sum4'
     */
    b_VectorConcatenate_c4eb[2] = b_Sum2 - (b_v_K_R_E_C_est_mDs - b_du_C_EC_mDs2);

    /* Gain: '<S18>/Gain19' */
    b_v_K_R_E_C_est_mDs = b_v_K_R_E_C_est_mDs_tmp_0;

    /* Gain: '<S18>/Gain20' */
    b_du_C_EC_mDs2 = b_du_C_EC_mDs2_tmp;

    /* Gain: '<S18>/Gain21' incorporates:
     *  Sum: '<S18>/Sum7'
     */
    b_Gain21 = 0.5 * (b_v_K_R_E_C_est_mDs + b_du_C_EC_mDs2);

    /* Gain: '<S18>/Gain22' */
    b_v_K_R_E_C_est_mDs = b_v_K_R_E_C_est_mDs_tmp_1;

    /* Gain: '<S18>/Gain23' */
    b_du_C_EC_mDs2 = b_du_C_EC_mDs2_tmp_0;

    /* Gain: '<S18>/Gain29' incorporates:
     *  Gain: '<S18>/Gain24'
     *  Sum: '<S18>/Sum8'
     *  Sum: '<S18>/Sum9'
     */
    b_VectorConcatenate_c4eb[3] = 0.5 * (b_Gain21 - 0.5 * (b_v_K_R_E_C_est_mDs +
      b_du_C_EC_mDs2));

    /* Product: '<S19>/Product12' incorporates:
     *  Constant: '<S17>/Constant6'
     */
    for (i_33 = 0; i_33 < 4; i_33 = i_33 + 1) {
      tmp_4[i_33] = 0.0;
      for (i_34 = 0; i_34 < 10; i_34 = i_34 + 1) {
        tmp_4[i_33] = tmp_4[i_33] + rtCP_Constant6_Value_kakl[i_33 + (i_34 << 2)]
          * b_u[i_34];
      }
    }

    /* End of Product: '<S19>/Product12' */

    /* Gain: '<S19>/Gain4' incorporates:
     *  Concatenate: '<S18>/Vector Concatenate'
     *  Gain: '<S19>/Gain1'
     *  Sum: '<S19>/Sum10'
     */
    for (i_35 = 0; i_35 < 4; i_35 = i_35 + 1) {
      tmp_5[i_35] = -(b_VectorConcatenate_c4eb[i_35] + tmp_4[i_35]);
    }

    /* End of Gain: '<S19>/Gain4' */

    /* Product: '<S19>/Product7' */
    for (i_36 = 0; i_36 < 4; i_36 = i_36 + 1) {
      b_X_0[i_36] = 0.0;
      for (i_37 = 0; i_37 < 4; i_37 = i_37 + 1) {
        b_X_0[i_36] = b_X_0[i_36] + b_X[i_36 + (i_37 << 2)] * tmp_5[i_37];
      }
    }

    /* End of Product: '<S19>/Product7' */

    /* Product: '<S19>/Product10' */
    for (i_38 = 0; i_38 < 4; i_38 = i_38 + 1) {
      tmp_6[i_38] = b_X_0[i_38];
    }

    /* End of Product: '<S19>/Product10' */

    /* Product: '<S19>/Product11' */
    for (i_39 = 0; i_39 < 10; i_39 = i_39 + 1) {
      b_N_M_0[i_39] = 0.0;
      for (i_3a = 0; i_3a < 4; i_3a = i_3a + 1) {
        b_N_M_0[i_39] = b_N_M_0[i_39] + b_N_M[i_39 + 10 * i_3a] * tmp_6[i_3a];
      }
    }

    /* End of Product: '<S19>/Product11' */

    /* Product: '<S17>/Product1' */
    memcpy(&b_Product1[0], &b_N_M_0[0], 10U * sizeof(real_T));

    /* MATLAB Function: '<S17>/Scale_NST_Solution' incorporates:
     *  Constant: '<S17>/Constant4'
     *  Constant: '<S17>/Constant5'
     *  Product: '<S17>/Product1'
     */
    for (i_3b = 0; i_3b < 10; i_3b = i_3b + 1) {
      tmp_7[i_3b] = ((rtCP_Constant4_Value_nvih[i_3b] - b_u[i_3b]) -
                     b_Product1[i_3b] < 0.0);
    }

    eml_find_Ejmjtket(tmp_7, tmp_data, &tmp_size);
    loop_ub_1 = tmp_size - 1;
    for (i_3c = 0; i_3c <= loop_ub_1; i_3c = i_3c + 1) {
      idx_insult_max_tmp_data[i_3c] = (real_T)tmp_data[i_3c];
    }

    RMT_FDM_DLL_FrameWork_FCS_RT_DW->SFunction_DIMS5 = tmp_size;
    for (i_3d = 0; i_3d < 10; i_3d = i_3d + 1) {
      b_Product1_0[i_3d] = (b_Product1[i_3d] - (-(b_u[i_3d] -
        rtCP_Constant5_Value_b1up[i_3d])) < 0.0);
    }

    eml_find_Ejmjtket(b_Product1_0, tmp_data_0, &tmp_size_0);
    loop_ub_2 = tmp_size_0 - 1;
    for (i_3e = 0; i_3e <= loop_ub_2; i_3e = i_3e + 1) {
      idx_insult_min_tmp_data[i_3e] = (real_T)tmp_data_0[i_3e];
    }

    RMT_FDM_DLL_FrameWork_FCS_RT_DW->SFunction_DIMS6 = tmp_size_0;
    loop_ub_3 = tmp_size - 1;
    for (i_3f = 0; i_3f <= loop_ub_3; i_3f = i_3f + 1) {
      scaling_max_data_tmp = (int32_T)idx_insult_max_tmp_data[i_3f] - 1;
      scaling_max_data[i_3f] = rtCP_Constant4_Value_nvih[scaling_max_data_tmp] /
        b_Product1[scaling_max_data_tmp];
    }

    loop_ub_4 = tmp_size_0 - 1;
    for (i_3g = 0; i_3g <= loop_ub_4; i_3g = i_3g + 1) {
      scaling_min_data_tmp = (int32_T)idx_insult_min_tmp_data[i_3g] - 1;
      scaling_min_data[i_3g] = rtCP_Constant5_Value_b1up[scaling_min_data_tmp] /
        b_Product1[scaling_min_data_tmp];
    }

    d_1 = (uint8_T)tmp_size;
    for (b_k_1 = 0; b_k_1 < d_1; b_k_1 = b_k_1 + 1) {
      y_data[(b_k_1 + 1) - 1] = fabs(b_Product1[(int32_T)
        idx_insult_max_tmp_data[(b_k_1 + 1) - 1] - 1]);
    }

    end = (int32_T)(real_T)tmp_size;

    /* End of Outputs for SubSystem: '<Root>/FCS_INDI_Control' */
    for (i_n = 0; i_n < end; i_n = i_n + 1) {
      /* Outputs for Atomic SubSystem: '<Root>/FCS_INDI_Control' */
      /* MATLAB Function: '<S17>/Scale_NST_Solution' */
      if (y_data[i_n] < 0.01) {
        scaling_max_data[i_n] = 0.0;
      }

      /* End of Outputs for SubSystem: '<Root>/FCS_INDI_Control' */
    }

    /* Outputs for Atomic SubSystem: '<Root>/FCS_INDI_Control' */
    /* MATLAB Function: '<S17>/Scale_NST_Solution' incorporates:
     *  Product: '<S17>/Product1'
     */
    e_0 = (uint8_T)tmp_size_0;
    for (d_k_1 = 0; d_k_1 < e_0; d_k_1 = d_k_1 + 1) {
      y_data[(d_k_1 + 1) - 1] = fabs(b_Product1[(int32_T)
        idx_insult_min_tmp_data[(d_k_1 + 1) - 1] - 1]);
    }

    end_0 = (int32_T)(real_T)tmp_size_0;

    /* End of Outputs for SubSystem: '<Root>/FCS_INDI_Control' */
    for (i_o = 0; i_o < end_0; i_o = i_o + 1) {
      /* Outputs for Atomic SubSystem: '<Root>/FCS_INDI_Control' */
      /* MATLAB Function: '<S17>/Scale_NST_Solution' */
      if (y_data[i_o] < 0.01) {
        scaling_min_data[i_o] = 0.0;
      }

      /* End of Outputs for SubSystem: '<Root>/FCS_INDI_Control' */
    }

    /* Outputs for Atomic SubSystem: '<Root>/FCS_INDI_Control' */
    /* MATLAB Function: '<S17>/Scale_NST_Solution' */
    if ((tmp_size == 0) && (tmp_size_0 == 0)) {
      b_b = 1.0;
    } else {
      y_size = tmp_size + tmp_size_0;
      if (0 <= tmp_size - 1) {
        memcpy(&y_data[0], &scaling_max_data[0], (uint32_T)((tmp_size - 1) + 1) *
               sizeof(real_T));
      }

      loop_ub_5 = tmp_size_0 - 1;
      for (i_3h = 0; i_3h <= loop_ub_5; i_3h = i_3h + 1) {
        y_data[i_3h + tmp_size] = scaling_min_data[i_3h];
      }

      f_0 = (uint8_T)y_size;
      for (f_k_0 = 0; f_k_0 < f_0; f_k_0 = f_k_0 + 1) {
        varargin_1_data[(f_k_0 + 1) - 1] = fabs(y_data[(f_k_0 + 1) - 1]);
      }

      last = (int32_T)(real_T)y_size;
      if (1 + (uint8_T)((int32_T)(real_T)y_size - 1) <= 2) {
        if (1 + (uint8_T)((int32_T)(real_T)y_size - 1) == 1) {
          b_b = varargin_1_data[0];
        } else {
          tmp_b = varargin_1_data[(int32_T)(real_T)y_size - 1];
          if (varargin_1_data[0] > tmp_b) {
            b_b = tmp_b;
          } else if (rtIsNaN(varargin_1_data[0])) {
            if (!rtIsNaN(tmp_b)) {
              b_b = tmp_b;
            } else {
              b_b = varargin_1_data[0];
            }
          } else {
            b_b = varargin_1_data[0];
          }
        }
      } else {
        if (!rtIsNaN(varargin_1_data[0])) {
          idx = 1;
        } else {
          idx = 0;
          g_k = 2;
          exitg1 = false;
          while ((exitg1 == false) && (g_k <= (int32_T)(real_T)y_size)) {
            if (!rtIsNaN(varargin_1_data[g_k - 1])) {
              idx = g_k;
              exitg1 = true;
            } else {
              g_k = g_k + 1;
            }
          }
        }

        if (idx == 0) {
          b_b = varargin_1_data[0];
        } else {
          ex = varargin_1_data[idx - 1];
          g_1 = idx + 1;
          for (h_k_0 = g_1; h_k_0 <= last; h_k_0 = h_k_0 + 1) {
            tmp_c = varargin_1_data[h_k_0 - 1];
            if (ex > tmp_c) {
              ex = tmp_c;
            }
          }

          b_b = ex;
        }
      }
    }

    RMT_FDM_DLL_FrameWork_FCS_RT_DW->SFunction_DIMS5 = tmp_size;
    RMT_FDM_DLL_FrameWork_FCS_RT_DW->SFunction_DIMS6 = tmp_size_0;

    /* Saturate: '<S17>/Saturation' */
    for (i_f = 0; i_f < 10; i_f = i_f + 1) {
      /* Sum: '<S17>/Add' incorporates:
       *  MATLAB Function: '<S17>/Scale_NST_Solution'
       *  Product: '<S17>/Product1'
       */
      u0 = b_u[i_f] + b_Product1[i_f] * b_b;
      u1 = rtCP_Saturation_LowerSat[i_f];
      u2 = rtCP_Saturation_UpperSat[i_f];
      if (u0 > u2) {
        /* Saturate: '<S17>/Saturation' */
        b_Saturation[i_f] = u2;
      } else if (u0 < u1) {
        /* Saturate: '<S17>/Saturation' */
        b_Saturation[i_f] = u1;
      } else {
        /* Saturate: '<S17>/Saturation' */
        b_Saturation[i_f] = u0;
      }
    }

    /* End of Saturate: '<S17>/Saturation' */
    /* DataTypeConversion: '<S5>/Data Type Conversion' */
    b_v_K_R_E_C_est_mDs = (real_T)RMT_FDM_DLL_FrameWork_FCS_RT_B->RT1.arm_swi;

    /* Product: '<S5>/Product' */
    for (i_g = 0; i_g < 8; i_g = i_g + 1) {
      /* Sum: '<S5>/Sum2' incorporates:
       *  DiscreteIntegrator: '<S10>/Discrete-Time Integrator'
       */
      u0_0 = b_Saturation[i_g + 2] +
        RMT_FDM_DLL_FrameWork_FCS_RT_DW->DiscreteTimeIntegrator_DSTATE_avov[i_g];

      /* Saturate: '<S5>/Saturation1' */
      if (u0_0 > 2712.0) {
        y_0 = 2712.0;
      } else if (u0_0 < 0.0) {
        y_0 = 0.0;
      } else {
        y_0 = u0_0;
      }

      /* End of Saturate: '<S5>/Saturation1' */
      b_w_cmd_INDI_radDs[i_g] = b_v_K_R_E_C_est_mDs * y_0;
    }

    /* End of Product: '<S5>/Product' */

    /* Sum: '<S35>/Sum1' incorporates:
     *  DiscreteIntegrator: '<S35>/Discrete-Time Integrator'
     *  DiscreteIntegrator: '<S35>/Discrete-Time Integrator1'
     *  Gain: '<S35>/Gain2'
     *  Gain: '<S35>/Gain3'
     */
    for (i_h = 0; i_h < 3; i_h = i_h + 1) {
      b_Sum1_kkm0[i_h] = 250000.0 *
        RMT_FDM_DLL_FrameWork_FCS_RT_DW->DiscreteTimeIntegrator1_DSTATE[i_h] +
        1000.0 *
        RMT_FDM_DLL_FrameWork_FCS_RT_DW->DiscreteTimeIntegrator_DSTATE_pv2o[i_h];
    }

    /* End of Sum: '<S35>/Sum1' */

    /* Sum: '<S31>/Sum1' incorporates:
     *  DiscreteIntegrator: '<S31>/Discrete-Time Integrator'
     *  DiscreteIntegrator: '<S31>/Discrete-Time Integrator1'
     *  Gain: '<S31>/Gain2'
     *  Gain: '<S31>/Gain3'
     */
    for (i_i = 0; i_i < 2; i_i = i_i + 1) {
      b_Sum1_kku3[i_i] = 250000.0 *
        RMT_FDM_DLL_FrameWork_FCS_RT_DW->DiscreteTimeIntegrator1_DSTATE_lwvn[i_i]
        + 1000.0 *
        RMT_FDM_DLL_FrameWork_FCS_RT_DW->DiscreteTimeIntegrator_DSTATE_ajjv[i_i];
    }

    /* End of Sum: '<S31>/Sum1' */

    /* Sum: '<S48>/Sum5' */
    b_Sum5_odvj = b_dv_C_EC_mDs;

    /* Sum: '<S48>/Sum1' */
    b_Sum1_o2dx = b_u_K_R_E_C_est_mDs;

    /* Sum: '<S48>/Sum2' */
    b_Sum2_b2z0 = b_v_C_ref_mDs;

    /* BusAssignment: '<S11>/Bus Assignment' */
    b_fc_ctrl_cmd.w1_cmd_radDs = b_w_cmd_INDI_radDs[0];
    b_fc_ctrl_cmd.w2_cmd_radDs = b_w_cmd_INDI_radDs[1];
    b_fc_ctrl_cmd.w3_cmd_radDs = b_w_cmd_INDI_radDs[2];
    b_fc_ctrl_cmd.w4_cmd_radDs = b_w_cmd_INDI_radDs[3];
    b_fc_ctrl_cmd.w5_cmd_radDs = b_w_cmd_INDI_radDs[4];
    b_fc_ctrl_cmd.w6_cmd_radDs = b_w_cmd_INDI_radDs[5];
    b_fc_ctrl_cmd.w7_cmd_radDs = b_w_cmd_INDI_radDs[6];
    b_fc_ctrl_cmd.w8_cmd_radDs = b_w_cmd_INDI_radDs[7];

    /* SignalConversion generated from: '<S24>/Bus Selector18' incorporates:
     *  SignalConversion: '<S47>/Signal Copy'
     */
    b_dv_C_EC_mDs = b_Switch2;

    /* SignalConversion generated from: '<S24>/Bus Selector19' incorporates:
     *  SignalConversion generated from: '<S14>/Vector Concatenate1'
     */
    b_u_K_R_E_C_est_mDs =
      RMT_FDM_DLL_FrameWork_FCS_RT_B->RT2.ahrs_meas.Phi_meas_rad;

    /* SignalConversion generated from: '<S24>/Bus Selector20' incorporates:
     *  SignalConversion: '<S47>/Signal Copy1'
     */
    b_v_C_ref_mDs = b_Switch2_gt5e;

    /* SignalConversion generated from: '<S24>/Bus Selector21' incorporates:
     *  SignalConversion generated from: '<S14>/Vector Concatenate1'
     */
    b_v_K_R_E_C_est_mDs =
      RMT_FDM_DLL_FrameWork_FCS_RT_B->RT2.ahrs_meas.Theta_meas_rad;

    /* SignalConversion generated from: '<S24>/Bus Selector22' incorporates:
     *  BusAssignment: '<S40>/Bus Assignment'
     */
    b_du_C_EC_mDs2 = b_Product4[2];

    /* SignalConversion generated from: '<S24>/Bus Selector23' incorporates:
     *  BusAssignment: '<S14>/Bus Assignment'
     */
    b_w_K_R_E_C_est_mDs =
      b_BusConversion_InsertedFor_BusAssignment_at_inport_3_BusCreator.Psi_Dot_est_radDs;

    /* SignalConversion generated from: '<S24>/Bus Selector6' incorporates:
     *  BusAssignment: '<S43>/Bus Assignment'
     */
    b_dv_C_EC_mDs = b_nu_limit;

    /* SignalConversion generated from: '<S24>/Bus Selector5' incorporates:
     *  BusAssignment: '<S14>/Bus Assignment'
     */
    b_u_K_R_E_C_est_mDs = b_Sum_ihvy[0];

    /* SignalConversion generated from: '<S24>/Bus Selector6' incorporates:
     *  BusAssignment: '<S43>/Bus Assignment'
     */
    b_v_C_ref_mDs = b_nu_limit_occu;

    /* SignalConversion generated from: '<S24>/Bus Selector5' incorporates:
     *  BusAssignment: '<S14>/Bus Assignment'
     */
    b_v_K_R_E_C_est_mDs = b_Sum_ihvy[1];

    /* SignalConversion generated from: '<S24>/Bus Selector6' incorporates:
     *  BusAssignment: '<S43>/Bus Assignment'
     */
    b_du_C_EC_mDs2 = b_nu_limit_abb3;

    /* SignalConversion generated from: '<S24>/Bus Selector5' incorporates:
     *  BusAssignment: '<S14>/Bus Assignment'
     */
    b_w_K_R_E_C_est_mDs = b_Sum_ihvy[2];

    /* SignalConversion generated from: '<S24>/Bus Selector2' incorporates:
     *  DiscreteIntegrator: '<S48>/p_Ref'
     */
    b_dv_C_EC_mDs = RMT_FDM_DLL_FrameWork_FCS_RT_DW->p_Ref_DSTATE;

    /* SignalConversion generated from: '<S24>/Bus Selector1' incorporates:
     *  SignalConversion generated from: '<S14>/Vector Concatenate'
     */
    b_u_K_R_E_C_est_mDs =
      RMT_FDM_DLL_FrameWork_FCS_RT_B->RT2.imu_meas.gyro_meas.w_x_K_IB_B_IMU_meas_radDs;

    /* SignalConversion generated from: '<S24>/Bus Selector2' */
    b_v_C_ref_mDs = b_fc_RM.RM_rate.RM_q.q_ref_radDs;

    /* SignalConversion generated from: '<S24>/Bus Selector1' incorporates:
     *  SignalConversion generated from: '<S14>/Vector Concatenate'
     */
    b_v_K_R_E_C_est_mDs =
      RMT_FDM_DLL_FrameWork_FCS_RT_B->RT2.imu_meas.gyro_meas.w_y_K_IB_B_IMU_meas_radDs;

    /* SignalConversion generated from: '<S24>/Bus Selector2' */
    b_du_C_EC_mDs2 = b_fc_RM.RM_rate.RM_r.r_ref_radDs;

    /* SignalConversion generated from: '<S24>/Bus Selector1' incorporates:
     *  SignalConversion generated from: '<S14>/Vector Concatenate'
     */
    b_w_K_R_E_C_est_mDs =
      RMT_FDM_DLL_FrameWork_FCS_RT_B->RT2.imu_meas.gyro_meas.w_z_K_IB_B_IMU_meas_radDs;

    /* SignalConversion generated from: '<S24>/Bus Selector4' */
    b_dv_C_EC_mDs = b_fc_RM.RM_rate.RM_p.nu_p_radDs2;

    /* SignalConversion generated from: '<S24>/Bus Selector3' incorporates:
     *  BusCreator generated from: '<S14>/Bus Assignment'
     */
    b_u_K_R_E_C_est_mDs = b_Diff[0];

    /* SignalConversion generated from: '<S24>/Bus Selector4' */
    b_v_C_ref_mDs = b_fc_RM.RM_rate.RM_q.nu_q_radDs2;

    /* SignalConversion generated from: '<S24>/Bus Selector3' incorporates:
     *  BusCreator generated from: '<S14>/Bus Assignment'
     */
    b_v_K_R_E_C_est_mDs = b_Diff[1];

    /* SignalConversion generated from: '<S24>/Bus Selector4' */
    b_du_C_EC_mDs2 = b_fc_RM.RM_rate.RM_r.nu_r_radDs2;

    /* SignalConversion generated from: '<S24>/Bus Selector3' incorporates:
     *  BusCreator generated from: '<S14>/Bus Assignment'
     */
    b_w_K_R_E_C_est_mDs = b_Diff[2];

    /* SignalConversion generated from: '<S24>/Bus Selector12' incorporates:
     *  BusAssignment: '<S40>/Bus Assignment'
     */
    b_dv_C_EC_mDs = b_BusAssignment_gwea.RM_u_C.u_C_ref_mDs;

    /* SignalConversion generated from: '<S24>/Bus Selector13' incorporates:
     *  Reshape: '<S14>/Reshape5'
     *  Reshape: '<S45>/Reshape'
     */
    b_u_K_R_E_C_est_mDs = b_Reshape_pne4[0];

    /* SignalConversion generated from: '<S24>/Bus Selector14' incorporates:
     *  BusAssignment: '<S40>/Bus Assignment'
     */
    b_v_C_ref_mDs = b_BusAssignment_gwea.RM_v_C.v_C_ref_mDs;

    /* SignalConversion generated from: '<S24>/Bus Selector15' incorporates:
     *  Reshape: '<S14>/Reshape5'
     *  Reshape: '<S45>/Reshape'
     */
    b_v_K_R_E_C_est_mDs = b_Reshape_pne4[1];

    /* SignalConversion generated from: '<S24>/Bus Selector16' incorporates:
     *  BusAssignment: '<S40>/Bus Assignment'
     */
    b_du_C_EC_mDs2 = b_BusAssignment_gwea.RM_w_C.w_C_ref_mDs;

    /* SignalConversion generated from: '<S24>/Bus Selector17' incorporates:
     *  Reshape: '<S14>/Reshape5'
     *  Reshape: '<S45>/Reshape'
     */
    b_w_K_R_E_C_est_mDs = b_Reshape_pne4[2];

    /* Sum: '<S24>/Sum2' */
    b_dw_C_EC_mDs = b_du_C_EC_mDs2 - b_w_K_R_E_C_est_mDs;

    /* Sum: '<S24>/Sum' */
    b_du_C_EC_mDs2 = b_dv_C_EC_mDs - b_u_K_R_E_C_est_mDs;

    /* Sum: '<S24>/Sum1' */
    b_dv_C_EC_mDs = b_v_C_ref_mDs - b_v_K_R_E_C_est_mDs;

    /* Update for UnitDelay: '<S32>/UD'
     *
     * Block description for '<S32>/UD':
     *
     *  Store in Global RAM
     */
    for (i_j = 0; i_j < 3; i_j = i_j + 1) {
      RMT_FDM_DLL_FrameWork_FCS_RT_DW->UD_DSTATE[i_j] = b_TSamp[i_j];
    }

    /* End of Update for UnitDelay: '<S32>/UD' */

    /* Update for Delay: '<S5>/Delay' incorporates:
     *  Saturate: '<S17>/Saturation'
     */
    memcpy(&RMT_FDM_DLL_FrameWork_FCS_RT_DW->Delay_DSTATE_oj24[0],
           &b_Saturation[0], 10U * sizeof(real_T));

    /* Update for DiscreteIntegrator: '<S47>/Phi_Ref' incorporates:
     *  DiscreteIntegrator: '<S47>/Theta_Ref'
     */
    RMT_FDM_DLL_FrameWork_FCS_RT_DW->Phi_Ref_DSTATE =
      RMT_FDM_DLL_FrameWork_FCS_RT_DW->Phi_Ref_DSTATE + 0.004 * b_Product4[0];
    if (b_Switch.arm_swi) {
      RMT_FDM_DLL_FrameWork_FCS_RT_DW->Phi_Ref_PrevResetState = 1;
      RMT_FDM_DLL_FrameWork_FCS_RT_DW->Theta_Ref_PrevResetState = 1;
    } else if ((int32_T)b_Switch.arm_swi < 0) {
      RMT_FDM_DLL_FrameWork_FCS_RT_DW->Phi_Ref_PrevResetState = -1;
      RMT_FDM_DLL_FrameWork_FCS_RT_DW->Theta_Ref_PrevResetState = -1;
    } else {
      RMT_FDM_DLL_FrameWork_FCS_RT_DW->Phi_Ref_PrevResetState = 0;
      RMT_FDM_DLL_FrameWork_FCS_RT_DW->Theta_Ref_PrevResetState = 0;
    }

    /* End of Update for DiscreteIntegrator: '<S47>/Phi_Ref' */

    /* Update for DiscreteIntegrator: '<S47>/Theta_Ref' */
    RMT_FDM_DLL_FrameWork_FCS_RT_DW->Theta_Ref_DSTATE =
      RMT_FDM_DLL_FrameWork_FCS_RT_DW->Theta_Ref_DSTATE + 0.004 * b_Product4[1];

    /* Update for DiscreteIntegrator: '<S48>/p_Ref' */
    RMT_FDM_DLL_FrameWork_FCS_RT_DW->p_Ref_DSTATE =
      RMT_FDM_DLL_FrameWork_FCS_RT_DW->p_Ref_DSTATE + 0.004 * b_Sum5_odvj;
    if (RMT_FDM_DLL_FrameWork_FCS_RT_DW->p_Ref_DSTATE > 6.2831853071795862) {
      RMT_FDM_DLL_FrameWork_FCS_RT_DW->p_Ref_DSTATE = 6.2831853071795862;
    } else if (RMT_FDM_DLL_FrameWork_FCS_RT_DW->p_Ref_DSTATE <
               -6.2831853071795862) {
      RMT_FDM_DLL_FrameWork_FCS_RT_DW->p_Ref_DSTATE = -6.2831853071795862;
    }

    if (b_Switch.arm_swi) {
      RMT_FDM_DLL_FrameWork_FCS_RT_DW->p_Ref_PrevResetState = 1;
    } else if ((int32_T)b_Switch.arm_swi < 0) {
      RMT_FDM_DLL_FrameWork_FCS_RT_DW->p_Ref_PrevResetState = -1;
    } else {
      RMT_FDM_DLL_FrameWork_FCS_RT_DW->p_Ref_PrevResetState = 0;
    }

    /* End of Update for DiscreteIntegrator: '<S48>/p_Ref' */

    /* Update for DiscreteIntegrator: '<S48>/q_Ref' */
    RMT_FDM_DLL_FrameWork_FCS_RT_DW->q_Ref_DSTATE =
      RMT_FDM_DLL_FrameWork_FCS_RT_DW->q_Ref_DSTATE + 0.004 * b_Sum1_o2dx;
    if (RMT_FDM_DLL_FrameWork_FCS_RT_DW->q_Ref_DSTATE > 6.2831853071795862) {
      RMT_FDM_DLL_FrameWork_FCS_RT_DW->q_Ref_DSTATE = 6.2831853071795862;
    } else if (RMT_FDM_DLL_FrameWork_FCS_RT_DW->q_Ref_DSTATE <
               -6.2831853071795862) {
      RMT_FDM_DLL_FrameWork_FCS_RT_DW->q_Ref_DSTATE = -6.2831853071795862;
    }

    if (b_Switch.arm_swi) {
      RMT_FDM_DLL_FrameWork_FCS_RT_DW->q_Ref_PrevResetState = 1;
    } else if ((int32_T)b_Switch.arm_swi < 0) {
      RMT_FDM_DLL_FrameWork_FCS_RT_DW->q_Ref_PrevResetState = -1;
    } else {
      RMT_FDM_DLL_FrameWork_FCS_RT_DW->q_Ref_PrevResetState = 0;
    }

    /* End of Update for DiscreteIntegrator: '<S48>/q_Ref' */

    /* Update for DiscreteIntegrator: '<S48>/r_Ref' */
    RMT_FDM_DLL_FrameWork_FCS_RT_DW->r_Ref_DSTATE =
      RMT_FDM_DLL_FrameWork_FCS_RT_DW->r_Ref_DSTATE + 0.004 * b_Sum2_b2z0;
    if (RMT_FDM_DLL_FrameWork_FCS_RT_DW->r_Ref_DSTATE > 1.0471975511965976) {
      RMT_FDM_DLL_FrameWork_FCS_RT_DW->r_Ref_DSTATE = 1.0471975511965976;
    } else if (RMT_FDM_DLL_FrameWork_FCS_RT_DW->r_Ref_DSTATE <
               -1.0471975511965976) {
      RMT_FDM_DLL_FrameWork_FCS_RT_DW->r_Ref_DSTATE = -1.0471975511965976;
    }

    if (b_Switch.arm_swi) {
      RMT_FDM_DLL_FrameWork_FCS_RT_DW->r_Ref_PrevResetState = 1;
    } else if ((int32_T)b_Switch.arm_swi < 0) {
      RMT_FDM_DLL_FrameWork_FCS_RT_DW->r_Ref_PrevResetState = -1;
    } else {
      RMT_FDM_DLL_FrameWork_FCS_RT_DW->r_Ref_PrevResetState = 0;
    }

    /* End of Update for DiscreteIntegrator: '<S48>/r_Ref' */

    /* Update for DiscreteIntegrator: '<S62>/Discrete-Time Integrator' */
    RMT_FDM_DLL_FrameWork_FCS_RT_DW->DiscreteTimeIntegrator_DSTATE =
      RMT_FDM_DLL_FrameWork_FCS_RT_DW->DiscreteTimeIntegrator_DSTATE + 0.004 *
      b_nu_limit;
    if (RMT_FDM_DLL_FrameWork_FCS_RT_DW->DiscreteTimeIntegrator_DSTATE > 2.0) {
      RMT_FDM_DLL_FrameWork_FCS_RT_DW->DiscreteTimeIntegrator_DSTATE = 2.0;
    } else if (RMT_FDM_DLL_FrameWork_FCS_RT_DW->DiscreteTimeIntegrator_DSTATE <
               -2.0) {
      RMT_FDM_DLL_FrameWork_FCS_RT_DW->DiscreteTimeIntegrator_DSTATE = -2.0;
    }

    if (b_Switch.arm_swi) {
      RMT_FDM_DLL_FrameWork_FCS_RT_DW->DiscreteTimeIntegrator_PrevResetState = 1;
    } else if ((int32_T)b_Switch.arm_swi < 0) {
      RMT_FDM_DLL_FrameWork_FCS_RT_DW->DiscreteTimeIntegrator_PrevResetState =
        -1;
    } else {
      RMT_FDM_DLL_FrameWork_FCS_RT_DW->DiscreteTimeIntegrator_PrevResetState = 0;
    }

    /* End of Update for DiscreteIntegrator: '<S62>/Discrete-Time Integrator' */

    /* Update for DiscreteIntegrator: '<S63>/Discrete-Time Integrator' */
    RMT_FDM_DLL_FrameWork_FCS_RT_DW->DiscreteTimeIntegrator_DSTATE_hs0d =
      RMT_FDM_DLL_FrameWork_FCS_RT_DW->DiscreteTimeIntegrator_DSTATE_hs0d +
      0.004 * b_nu_limit_occu;
    if (RMT_FDM_DLL_FrameWork_FCS_RT_DW->DiscreteTimeIntegrator_DSTATE_hs0d >
        2.0) {
      RMT_FDM_DLL_FrameWork_FCS_RT_DW->DiscreteTimeIntegrator_DSTATE_hs0d = 2.0;
    } else if
        (RMT_FDM_DLL_FrameWork_FCS_RT_DW->DiscreteTimeIntegrator_DSTATE_hs0d <
         -2.0) {
      RMT_FDM_DLL_FrameWork_FCS_RT_DW->DiscreteTimeIntegrator_DSTATE_hs0d = -2.0;
    }

    if (b_Switch.arm_swi) {
      RMT_FDM_DLL_FrameWork_FCS_RT_DW->DiscreteTimeIntegrator_PrevResetState_nmap
        = 1;
    } else if ((int32_T)b_Switch.arm_swi < 0) {
      RMT_FDM_DLL_FrameWork_FCS_RT_DW->DiscreteTimeIntegrator_PrevResetState_nmap
        = -1;
    } else {
      RMT_FDM_DLL_FrameWork_FCS_RT_DW->DiscreteTimeIntegrator_PrevResetState_nmap
        = 0;
    }

    /* End of Update for DiscreteIntegrator: '<S63>/Discrete-Time Integrator' */

    /* Update for DiscreteIntegrator: '<S64>/Discrete-Time Integrator' */
    RMT_FDM_DLL_FrameWork_FCS_RT_DW->DiscreteTimeIntegrator_DSTATE_japy =
      RMT_FDM_DLL_FrameWork_FCS_RT_DW->DiscreteTimeIntegrator_DSTATE_japy +
      0.004 * b_nu_limit_abb3;
    if (RMT_FDM_DLL_FrameWork_FCS_RT_DW->DiscreteTimeIntegrator_DSTATE_japy >
        2.0) {
      RMT_FDM_DLL_FrameWork_FCS_RT_DW->DiscreteTimeIntegrator_DSTATE_japy = 2.0;
    } else if
        (RMT_FDM_DLL_FrameWork_FCS_RT_DW->DiscreteTimeIntegrator_DSTATE_japy <
         -2.0) {
      RMT_FDM_DLL_FrameWork_FCS_RT_DW->DiscreteTimeIntegrator_DSTATE_japy = -2.0;
    }

    if (b_Switch.arm_swi) {
      RMT_FDM_DLL_FrameWork_FCS_RT_DW->DiscreteTimeIntegrator_PrevResetState_fwtq
        = 1;
    } else if ((int32_T)b_Switch.arm_swi < 0) {
      RMT_FDM_DLL_FrameWork_FCS_RT_DW->DiscreteTimeIntegrator_PrevResetState_fwtq
        = -1;
    } else {
      RMT_FDM_DLL_FrameWork_FCS_RT_DW->DiscreteTimeIntegrator_PrevResetState_fwtq
        = 0;
    }

    /* End of Update for DiscreteIntegrator: '<S64>/Discrete-Time Integrator' */

    /* Update for DiscreteIntegrator: '<S10>/Discrete-Time Integrator' incorporates:
     *  Gain: '<S10>/Gain'
     *  Product: '<S5>/Product'
     *  Sum: '<S10>/Subtract'
     */
    RMT_FDM_DLL_FrameWork_FCS_RT_DW->DiscreteTimeIntegrator_IC_LOADING = 0;
    for (i_3i = 0; i_3i < 8; i_3i = i_3i + 1) {
      RMT_FDM_DLL_FrameWork_FCS_RT_DW->DiscreteTimeIntegrator_DSTATE_avov[i_3i] =
        RMT_FDM_DLL_FrameWork_FCS_RT_DW->DiscreteTimeIntegrator_DSTATE_avov[i_3i]
        + 0.004 * (100.0 * (b_w_cmd_INDI_radDs[i_3i] -
                            RMT_FDM_DLL_FrameWork_FCS_RT_DW->DiscreteTimeIntegrator_DSTATE_avov
                            [i_3i]));
    }

    for (i_2 = 0; i_2 < 8; i_2 = i_2 + 1) {
      if (RMT_FDM_DLL_FrameWork_FCS_RT_DW->
          DiscreteTimeIntegrator_DSTATE_avov[i_2] > 2712.0) {
        RMT_FDM_DLL_FrameWork_FCS_RT_DW->DiscreteTimeIntegrator_DSTATE_avov[i_2]
          = 2712.0;
      } else if
          (RMT_FDM_DLL_FrameWork_FCS_RT_DW->
           DiscreteTimeIntegrator_DSTATE_avov[i_2] < 0.0) {
        RMT_FDM_DLL_FrameWork_FCS_RT_DW->DiscreteTimeIntegrator_DSTATE_avov[i_2]
          = 0.0;
      }
    }

    if (RMT_FDM_DLL_FrameWork_FCS_RT_B->RT1.arm_swi) {
      RMT_FDM_DLL_FrameWork_FCS_RT_DW->DiscreteTimeIntegrator_PrevResetState_dbpn
        = 1;
    } else if ((int32_T)RMT_FDM_DLL_FrameWork_FCS_RT_B->RT1.arm_swi < 0) {
      RMT_FDM_DLL_FrameWork_FCS_RT_DW->DiscreteTimeIntegrator_PrevResetState_dbpn
        = -1;
    } else {
      RMT_FDM_DLL_FrameWork_FCS_RT_DW->DiscreteTimeIntegrator_PrevResetState_dbpn
        = 0;
    }

    /* End of Update for DiscreteIntegrator: '<S10>/Discrete-Time Integrator' */

    /* Update for DiscreteIntegrator: '<S35>/Discrete-Time Integrator1' incorporates:
     *  DiscreteIntegrator: '<S35>/Discrete-Time Integrator'
     */
    for (i_3j = 0; i_3j < 3; i_3j = i_3j + 1) {
      RMT_FDM_DLL_FrameWork_FCS_RT_DW->DiscreteTimeIntegrator1_DSTATE[i_3j] =
        RMT_FDM_DLL_FrameWork_FCS_RT_DW->DiscreteTimeIntegrator1_DSTATE[i_3j] +
        0.004 *
        RMT_FDM_DLL_FrameWork_FCS_RT_DW->DiscreteTimeIntegrator_DSTATE_pv2o[i_3j];
    }

    /* End of Update for DiscreteIntegrator: '<S35>/Discrete-Time Integrator1' */

    /* Update for DiscreteIntegrator: '<S35>/Discrete-Time Integrator' incorporates:
     *  Gain: '<S35>/Gain'
     *  Gain: '<S35>/Gain1'
     *  Sum: '<S35>/Sum'
     */
    for (i_3k = 0; i_3k < 3; i_3k = i_3k + 1) {
      RMT_FDM_DLL_FrameWork_FCS_RT_DW->DiscreteTimeIntegrator_DSTATE_pv2o[i_3k] =
        RMT_FDM_DLL_FrameWork_FCS_RT_DW->DiscreteTimeIntegrator_DSTATE_pv2o[i_3k]
        + 0.004 * (250000.0 * b_VectorConcatenate_iw4s[i_3k] - b_Sum1_kkm0[i_3k]);
    }

    /* End of Update for DiscreteIntegrator: '<S35>/Discrete-Time Integrator' */

    /* Update for DiscreteIntegrator: '<S31>/Discrete-Time Integrator1' incorporates:
     *  DiscreteIntegrator: '<S31>/Discrete-Time Integrator'
     */
    for (i_3l = 0; i_3l < 2; i_3l = i_3l + 1) {
      RMT_FDM_DLL_FrameWork_FCS_RT_DW->DiscreteTimeIntegrator1_DSTATE_lwvn[i_3l]
        = RMT_FDM_DLL_FrameWork_FCS_RT_DW->
        DiscreteTimeIntegrator1_DSTATE_lwvn[i_3l] + 0.004 *
        RMT_FDM_DLL_FrameWork_FCS_RT_DW->DiscreteTimeIntegrator_DSTATE_ajjv[i_3l];
    }

    /* End of Update for DiscreteIntegrator: '<S31>/Discrete-Time Integrator1' */

    /* Update for DiscreteIntegrator: '<S31>/Discrete-Time Integrator' incorporates:
     *  Gain: '<S31>/Gain'
     *  Gain: '<S31>/Gain1'
     *  Sum: '<S31>/Sum'
     */
    for (i_3m = 0; i_3m < 2; i_3m = i_3m + 1) {
      RMT_FDM_DLL_FrameWork_FCS_RT_DW->DiscreteTimeIntegrator_DSTATE_ajjv[i_3m] =
        RMT_FDM_DLL_FrameWork_FCS_RT_DW->DiscreteTimeIntegrator_DSTATE_ajjv[i_3m]
        + 0.004 * (250000.0 * b_VectorConcatenate1_o2ke[i_3m] - b_Sum1_kku3[i_3m]);
    }

    /* End of Update for DiscreteIntegrator: '<S31>/Discrete-Time Integrator' */
    /* End of Outputs for SubSystem: '<Root>/FCS_INDI_Control' */

    /* BusAssignment: '<S1>/Bus Assignment' incorporates:
     *  Inport: '<Root>/w_cmd_radDs'
     */
    b_BusAssignment_eew0.w1_cmd_radDs =
      RMT_FDM_DLL_FrameWork_FCS_RT_U_w_cmd_radDs[0];
    b_BusAssignment_eew0.w2_cmd_radDs =
      RMT_FDM_DLL_FrameWork_FCS_RT_U_w_cmd_radDs[1];
    b_BusAssignment_eew0.w3_cmd_radDs =
      RMT_FDM_DLL_FrameWork_FCS_RT_U_w_cmd_radDs[2];
    b_BusAssignment_eew0.w4_cmd_radDs =
      RMT_FDM_DLL_FrameWork_FCS_RT_U_w_cmd_radDs[3];
    b_BusAssignment_eew0.w5_cmd_radDs =
      RMT_FDM_DLL_FrameWork_FCS_RT_U_w_cmd_radDs[4];
    b_BusAssignment_eew0.w6_cmd_radDs =
      RMT_FDM_DLL_FrameWork_FCS_RT_U_w_cmd_radDs[5];
    b_BusAssignment_eew0.w7_cmd_radDs =
      RMT_FDM_DLL_FrameWork_FCS_RT_U_w_cmd_radDs[6];
    b_BusAssignment_eew0.w8_cmd_radDs =
      RMT_FDM_DLL_FrameWork_FCS_RT_U_w_cmd_radDs[7];

    /* RateTransition: '<Root>/RT5' incorporates:
     *  RateTransition: '<Root>/RT'
     *  RateTransition: '<Root>/RT4'
     */
    if (rtmIsMajorTimeStep(RMT_FDM_DLL_FrameWork_FCS_RT_M) &&
        RMT_FDM_DLL_FrameWork_FCS_RT_M->Timing.TaskCounters.TID[1] == 0) {
      /* Outport: '<Root>/fc_estimation' */
      *RMT_FDM_DLL_FrameWork_FCS_RT_Y_fc_estimation = b_BusAssignment;

      /* RateTransition: '<Root>/RT4' */
      RMT_FDM_DLL_FrameWork_FCS_RT_B->RT4 = b_BusAssignment_eew0;

      /* RateTransition: '<Root>/RT' */
      RMT_FDM_DLL_FrameWork_FCS_RT_B->RT_itkc = b_fc_ctrl_cmd;
    }

    /* End of RateTransition: '<Root>/RT5' */

    /* BusCreator: '<S3>/Bus Creaor' incorporates:
     *  DataTypeConversion: '<S3>/Data Type Conversion1'
     *  DataTypeConversion: '<S3>/Data Type Conversion2'
     *  DataTypeConversion: '<S3>/Data Type Conversion3'
     *  DataTypeConversion: '<S3>/Data Type Conversion4'
     *  DataTypeConversion: '<S3>/Data Type Conversion5'
     *  DataTypeConversion: '<S3>/Data Type Conversion6'
     *  DataTypeConversion: '<S3>/Data Type Conversion7'
     *  DataTypeConversion: '<S3>/Data Type Conversion8'
     */
    RMT_FDM_DLL_FrameWork_FCS_RT_B->Contoller_cmd_faults.w1_cmd_radDs =
      RMT_FDM_DLL_FrameWork_FCS_RT_B->RT_itkc.w1_cmd_radDs;
    RMT_FDM_DLL_FrameWork_FCS_RT_B->Contoller_cmd_faults.w2_cmd_radDs =
      RMT_FDM_DLL_FrameWork_FCS_RT_B->RT_itkc.w2_cmd_radDs;
    RMT_FDM_DLL_FrameWork_FCS_RT_B->Contoller_cmd_faults.w3_cmd_radDs =
      RMT_FDM_DLL_FrameWork_FCS_RT_B->RT_itkc.w3_cmd_radDs;
    RMT_FDM_DLL_FrameWork_FCS_RT_B->Contoller_cmd_faults.w4_cmd_radDs =
      RMT_FDM_DLL_FrameWork_FCS_RT_B->RT_itkc.w4_cmd_radDs;
    RMT_FDM_DLL_FrameWork_FCS_RT_B->Contoller_cmd_faults.w5_cmd_radDs =
      RMT_FDM_DLL_FrameWork_FCS_RT_B->RT_itkc.w5_cmd_radDs;
    RMT_FDM_DLL_FrameWork_FCS_RT_B->Contoller_cmd_faults.w6_cmd_radDs =
      RMT_FDM_DLL_FrameWork_FCS_RT_B->RT_itkc.w6_cmd_radDs;
    RMT_FDM_DLL_FrameWork_FCS_RT_B->Contoller_cmd_faults.w7_cmd_radDs =
      RMT_FDM_DLL_FrameWork_FCS_RT_B->RT_itkc.w7_cmd_radDs;
    RMT_FDM_DLL_FrameWork_FCS_RT_B->Contoller_cmd_faults.w8_cmd_radDs =
      RMT_FDM_DLL_FrameWork_FCS_RT_B->RT_itkc.w8_cmd_radDs;
  }

  /* Switch: '<Root>/Switch' incorporates:
   *  Inport: '<Root>/Simulation_Control'
   *  Logic: '<Root>/NOT'
   */
  if (!RMT_FDM_DLL_FrameWork_FCS_RT_U_Simulation_Control->flg_Enable_Controller)
  {
    /* Switch: '<Root>/Switch' */
    RMT_FDM_DLL_FrameWork_FCS_RT_B->Switch = RMT_FDM_DLL_FrameWork_FCS_RT_B->RT4;
  } else {
    /* Switch: '<Root>/Switch' */
    RMT_FDM_DLL_FrameWork_FCS_RT_B->Switch =
      RMT_FDM_DLL_FrameWork_FCS_RT_B->Contoller_cmd_faults;
  }

  /* End of Switch: '<Root>/Switch' */

  /* ModelReference generated from: '<Root>/RMT_Plant' incorporates:
   *  Constant: '<S4>/Constant'
   *  Constant: '<S4>/Constant1'
   *  Constant: '<S4>/Constant2'
   *  Constant: '<S4>/Constant3'
   *  Constant: '<S4>/Constant6'
   *  Constant: '<S4>/Constant7'
   *  Constant: '<S4>/Constant8'
   *  Inport: '<Root>/Failures'
   *  Inport: '<Root>/Simulation_Control'
   *  Inport: '<Root>/States_Init'
   */
  RMT_FDM_RT(&(RMT_FDM_DLL_FrameWork_FCS_RT_DW->RMT_Plant_InstanceData.rtm),
             RMT_FDM_DLL_FrameWork_FCS_RT_U_Simulation_Control,
             &rtCP_Constant3_Value_je5h, &rtCP_Constant_Value_omib,
             &rtCP_Constant1_Value_p5to, &rtCP_Constant2_Value_nrpy,
             &rtCP_Constant6_Value_pzmj, &rtCP_Constant7_Value_daeb,
             &rtCP_Constant8_Value, RMT_FDM_DLL_FrameWork_FCS_RT_U_States_Init,
             RMT_FDM_DLL_FrameWork_FCS_RT_U_Failures,
             &RMT_FDM_DLL_FrameWork_FCS_RT_B->Switch,
             &RMT_FDM_DLL_FrameWork_FCS_RT_B->Vehicle,
             &RMT_FDM_DLL_FrameWork_FCS_RT_B->Measurements,
             &(RMT_FDM_DLL_FrameWork_FCS_RT_DW->RMT_Plant_InstanceData.rtb),
             &(RMT_FDM_DLL_FrameWork_FCS_RT_DW->RMT_Plant_InstanceData.rtdw),
             &(RMT_FDM_DLL_FrameWork_FCS_RT_X->RMT_Plant_CSTATE),
             &(RMT_FDM_DLL_FrameWork_FCS_RT_DW->RMT_Plant_InstanceData.rtzce));

  /* Outport: '<Root>/Vehicle' incorporates:
   *  ModelReference generated from: '<Root>/RMT_Plant'
   */
  *RMT_FDM_DLL_FrameWork_FCS_RT_Y_Vehicle =
    RMT_FDM_DLL_FrameWork_FCS_RT_B->Vehicle;

  /* Outport: '<Root>/Measurements' incorporates:
   *  ModelReference generated from: '<Root>/RMT_Plant'
   */
  *RMT_FDM_DLL_FrameWork_FCS_RT_Y_Measurements =
    RMT_FDM_DLL_FrameWork_FCS_RT_B->Measurements;
  if (rtmIsMajorTimeStep(RMT_FDM_DLL_FrameWork_FCS_RT_M)) {
    if (rtmIsMajorTimeStep(RMT_FDM_DLL_FrameWork_FCS_RT_M) &&
        RMT_FDM_DLL_FrameWork_FCS_RT_M->Timing.TaskCounters.TID[1] == 0) {
      /* Update for Delay: '<S2>/Delay16' */
      RMT_FDM_DLL_FrameWork_FCS_RT_DW->icLoad = false;
      RMT_FDM_DLL_FrameWork_FCS_RT_DW->Delay16_DSTATE =
        RMT_FDM_DLL_FrameWork_FCS_RT_B->Measurements.imu_meas.acc_meas.f_x_P_B_IMU_meas_mDs2;

      /* Update for Delay: '<S2>/Delay' */
      RMT_FDM_DLL_FrameWork_FCS_RT_DW->icLoad_ooxy = false;
      RMT_FDM_DLL_FrameWork_FCS_RT_DW->Delay_DSTATE =
        RMT_FDM_DLL_FrameWork_FCS_RT_B->Measurements.baro_meas.h_Baro_meas_m;

      /* Update for Delay: '<S2>/Delay1' */
      RMT_FDM_DLL_FrameWork_FCS_RT_DW->icLoad_hvp0 = false;
      RMT_FDM_DLL_FrameWork_FCS_RT_DW->Delay1_DSTATE =
        RMT_FDM_DLL_FrameWork_FCS_RT_B->Measurements.imu_meas.gyro_meas.w_x_K_IB_B_IMU_meas_radDs;

      /* Update for Delay: '<S2>/Delay2' */
      RMT_FDM_DLL_FrameWork_FCS_RT_DW->icLoad_agwh = false;
      RMT_FDM_DLL_FrameWork_FCS_RT_DW->Delay2_DSTATE =
        RMT_FDM_DLL_FrameWork_FCS_RT_B->Measurements.imu_meas.gyro_meas.w_y_K_IB_B_IMU_meas_radDs;

      /* Update for Delay: '<S2>/Delay3' */
      RMT_FDM_DLL_FrameWork_FCS_RT_DW->icLoad_k4aw = false;
      RMT_FDM_DLL_FrameWork_FCS_RT_DW->Delay3_DSTATE =
        RMT_FDM_DLL_FrameWork_FCS_RT_B->Measurements.imu_meas.gyro_meas.w_z_K_IB_B_IMU_meas_radDs;

      /* Update for Delay: '<S2>/Delay17' */
      RMT_FDM_DLL_FrameWork_FCS_RT_DW->icLoad_eux1 = false;
      RMT_FDM_DLL_FrameWork_FCS_RT_DW->Delay17_DSTATE =
        RMT_FDM_DLL_FrameWork_FCS_RT_B->Measurements.imu_meas.acc_meas.f_y_P_B_IMU_meas_mDs2;

      /* Update for Delay: '<S2>/Delay18' */
      RMT_FDM_DLL_FrameWork_FCS_RT_DW->icLoad_mxgu = false;
      RMT_FDM_DLL_FrameWork_FCS_RT_DW->Delay18_DSTATE =
        RMT_FDM_DLL_FrameWork_FCS_RT_B->Measurements.imu_meas.acc_meas.f_z_P_B_IMU_meas_mDs2;

      /* Update for Delay: '<S2>/Delay4' */
      RMT_FDM_DLL_FrameWork_FCS_RT_DW->icLoad_pbo0 = false;
      RMT_FDM_DLL_FrameWork_FCS_RT_DW->Delay4_DSTATE =
        RMT_FDM_DLL_FrameWork_FCS_RT_B->Measurements.gps_meas.pos_R_WGS84_meas.lambda_R_WGS84_meas_rad;

      /* Update for Delay: '<S2>/Delay5' */
      RMT_FDM_DLL_FrameWork_FCS_RT_DW->icLoad_dtzm = false;
      RMT_FDM_DLL_FrameWork_FCS_RT_DW->Delay5_DSTATE =
        RMT_FDM_DLL_FrameWork_FCS_RT_B->Measurements.gps_meas.pos_R_WGS84_meas.mue_R_WGS84_meas_rad;

      /* Update for Delay: '<S2>/Delay6' */
      RMT_FDM_DLL_FrameWork_FCS_RT_DW->icLoad_mfcp = false;
      RMT_FDM_DLL_FrameWork_FCS_RT_DW->Delay6_DSTATE =
        RMT_FDM_DLL_FrameWork_FCS_RT_B->Measurements.gps_meas.pos_R_WGS84_meas.h_R_WGS84_meas_m;

      /* Update for Delay: '<S2>/Delay7' */
      RMT_FDM_DLL_FrameWork_FCS_RT_DW->icLoad_js0i = false;
      RMT_FDM_DLL_FrameWork_FCS_RT_DW->Delay7_DSTATE =
        RMT_FDM_DLL_FrameWork_FCS_RT_B->Measurements.ahrs_meas.Phi_meas_rad;

      /* Update for Delay: '<S2>/Delay8' */
      RMT_FDM_DLL_FrameWork_FCS_RT_DW->icLoad_doan = false;
      RMT_FDM_DLL_FrameWork_FCS_RT_DW->Delay8_DSTATE =
        RMT_FDM_DLL_FrameWork_FCS_RT_B->Measurements.ahrs_meas.Theta_meas_rad;

      /* Update for Delay: '<S2>/Delay9' */
      RMT_FDM_DLL_FrameWork_FCS_RT_DW->icLoad_mzf4 = false;
      RMT_FDM_DLL_FrameWork_FCS_RT_DW->Delay9_DSTATE =
        RMT_FDM_DLL_FrameWork_FCS_RT_B->Measurements.ahrs_meas.Psi_meas_rad;

      /* Update for Delay: '<S2>/Delay10' */
      RMT_FDM_DLL_FrameWork_FCS_RT_DW->icLoad_chzd = false;
      RMT_FDM_DLL_FrameWork_FCS_RT_DW->Delay10_DSTATE =
        RMT_FDM_DLL_FrameWork_FCS_RT_B->Measurements.gps_meas.vel_K_R_E_O_meas.u_K_R_E_O_meas_mDs;

      /* Update for Delay: '<S2>/Delay11' */
      RMT_FDM_DLL_FrameWork_FCS_RT_DW->icLoad_giyv = false;
      RMT_FDM_DLL_FrameWork_FCS_RT_DW->Delay11_DSTATE =
        RMT_FDM_DLL_FrameWork_FCS_RT_B->Measurements.gps_meas.vel_K_R_E_O_meas.v_K_R_E_O_meas_mDs;

      /* Update for Delay: '<S2>/Delay12' */
      RMT_FDM_DLL_FrameWork_FCS_RT_DW->icLoad_lwdp = false;
      RMT_FDM_DLL_FrameWork_FCS_RT_DW->Delay12_DSTATE =
        RMT_FDM_DLL_FrameWork_FCS_RT_B->Measurements.gps_meas.vel_K_R_E_O_meas.w_K_R_E_O_meas_mDs;

      /* Update for Delay: '<S2>/Delay13' */
      RMT_FDM_DLL_FrameWork_FCS_RT_DW->icLoad_bu4u = false;
      RMT_FDM_DLL_FrameWork_FCS_RT_DW->Delay13_DSTATE =
        RMT_FDM_DLL_FrameWork_FCS_RT_B->Measurements.gps_meas.pos_R_local_meas.x_R_O_meas_m;

      /* Update for Delay: '<S2>/Delay14' */
      RMT_FDM_DLL_FrameWork_FCS_RT_DW->icLoad_atsy = false;
      RMT_FDM_DLL_FrameWork_FCS_RT_DW->Delay14_DSTATE =
        RMT_FDM_DLL_FrameWork_FCS_RT_B->Measurements.gps_meas.pos_R_local_meas.y_R_O_meas_m;

      /* Update for Delay: '<S2>/Delay15' */
      RMT_FDM_DLL_FrameWork_FCS_RT_DW->icLoad_nbvc = false;
      RMT_FDM_DLL_FrameWork_FCS_RT_DW->Delay15_DSTATE =
        RMT_FDM_DLL_FrameWork_FCS_RT_B->Measurements.gps_meas.pos_R_local_meas.z_R_O_meas_m;
    }

    /* Update for ModelReference generated from: '<Root>/RMT_Plant' */
    RMT_FDM_RT_Update
      (&(RMT_FDM_DLL_FrameWork_FCS_RT_DW->RMT_Plant_InstanceData.rtm),
       &(RMT_FDM_DLL_FrameWork_FCS_RT_DW->RMT_Plant_InstanceData.rtb),
       &(RMT_FDM_DLL_FrameWork_FCS_RT_DW->RMT_Plant_InstanceData.rtdw));
  }                                    /* end MajorTimeStep */

  if (rtmIsMajorTimeStep(RMT_FDM_DLL_FrameWork_FCS_RT_M)) {
    rt_ertODEUpdateContinuousStates(RMT_FDM_DLL_FrameWork_FCS_RT_M->solverInfo,
      RMT_FDM_DLL_FrameWork_FCS_RT_M,
      RMT_FDM_DLL_FrameWork_FCS_RT_U_Simulation_Control,
      RMT_FDM_DLL_FrameWork_FCS_RT_U_States_Init,
      RMT_FDM_DLL_FrameWork_FCS_RT_U_w_cmd_radDs,
      RMT_FDM_DLL_FrameWork_FCS_RT_U_fc_pilot_cmd,
      RMT_FDM_DLL_FrameWork_FCS_RT_U_Failures,
      RMT_FDM_DLL_FrameWork_FCS_RT_Y_Vehicle,
      RMT_FDM_DLL_FrameWork_FCS_RT_Y_Measurements,
      RMT_FDM_DLL_FrameWork_FCS_RT_Y_fc_estimation);

    /* Update absolute time for base rate */
    /* The "clockTick0" counts the number of times the code of this task has
     * been executed. The absolute time is the multiplication of "clockTick0"
     * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
     * overflow during the application lifespan selected.
     */
    ++RMT_FDM_DLL_FrameWork_FCS_RT_M->Timing.clockTick0;
    RMT_FDM_DLL_FrameWork_FCS_RT_M->Timing.t[0] = rtsiGetSolverStopTime
      (RMT_FDM_DLL_FrameWork_FCS_RT_M->solverInfo);

    {
      /* Update absolute timer for sample time: [0.004s, 0.0s] */
      /* The "clockTick1" counts the number of times the code of this task has
       * been executed. The resolution of this integer timer is 0.004, which is the step size
       * of the task. Size of "clockTick1" ensures timer will not overflow during the
       * application lifespan selected.
       */
      RMT_FDM_DLL_FrameWork_FCS_RT_M->Timing.clockTick1++;
    }

    if (rtmIsMajorTimeStep(RMT_FDM_DLL_FrameWork_FCS_RT_M) &&
        RMT_FDM_DLL_FrameWork_FCS_RT_M->Timing.TaskCounters.TID[2] == 0) {
      /* Update absolute timer for sample time: [0.2s, 0.0s] */
      /* The "clockTick2" counts the number of times the code of this task has
       * been executed. The resolution of this integer timer is 0.2, which is the step size
       * of the task. Size of "clockTick2" ensures timer will not overflow during the
       * application lifespan selected.
       */
      RMT_FDM_DLL_FrameWork_FCS_RT_M->Timing.clockTick2++;
    }

    rate_scheduler(RMT_FDM_DLL_FrameWork_FCS_RT_M);
  }                                    /* end MajorTimeStep */
}

/* Derivatives for root system: '<Root>' */
void RMT_FDM_DLL_FrameWork_FCS_RT_derivatives
  (RT_MODEL_RMT_FDM_DLL_FrameWork_FCS_RT_T *const RMT_FDM_DLL_FrameWork_FCS_RT_M)
{
  DW_RMT_FDM_DLL_FrameWork_FCS_RT_T *RMT_FDM_DLL_FrameWork_FCS_RT_DW =
    RMT_FDM_DLL_FrameWork_FCS_RT_M->ModelData.dwork;
  X_RMT_FDM_DLL_FrameWork_FCS_RT_T *RMT_FDM_DLL_FrameWork_FCS_RT_X =
    RMT_FDM_DLL_FrameWork_FCS_RT_M->ModelData.contStates;

  /* Derivatives for ModelReference generated from: '<Root>/RMT_Plant' */
  RMT_FDM_RT_Deriv(&(RMT_FDM_DLL_FrameWork_FCS_RT_DW->RMT_Plant_InstanceData.rtb),
                   &(RMT_FDM_DLL_FrameWork_FCS_RT_X->RMT_Plant_CSTATE),
                   &(((XDot_RMT_FDM_DLL_FrameWork_FCS_RT_T *)
                      RMT_FDM_DLL_FrameWork_FCS_RT_M->ModelData.derivs)
                     ->RMT_Plant_CSTATE));
}

/* Model initialize function */
void RMT_FDM_DLL_FrameWork_FCS_RT_initialize
  (RT_MODEL_RMT_FDM_DLL_FrameWork_FCS_RT_T *const RMT_FDM_DLL_FrameWork_FCS_RT_M)
{
  DW_RMT_FDM_DLL_FrameWork_FCS_RT_T *RMT_FDM_DLL_FrameWork_FCS_RT_DW =
    RMT_FDM_DLL_FrameWork_FCS_RT_M->ModelData.dwork;
  X_RMT_FDM_DLL_FrameWork_FCS_RT_T *RMT_FDM_DLL_FrameWork_FCS_RT_X =
    RMT_FDM_DLL_FrameWork_FCS_RT_M->ModelData.contStates;
  PrevZCX_RMT_FDM_DLL_FrameWork_FCS_RT_T *RMT_FDM_DLL_FrameWork_FCS_RT_PrevZCX =
    RMT_FDM_DLL_FrameWork_FCS_RT_M->ModelData.prevZCSigState;
  RMT_FDM_DLL_FrameWork_FCS_RT_PrevZCX->Delay16_Reset_ZCE = POS_ZCSIG;
  RMT_FDM_DLL_FrameWork_FCS_RT_PrevZCX->Delay_Reset_ZCE = POS_ZCSIG;
  RMT_FDM_DLL_FrameWork_FCS_RT_PrevZCX->Delay1_Reset_ZCE = POS_ZCSIG;
  RMT_FDM_DLL_FrameWork_FCS_RT_PrevZCX->Delay2_Reset_ZCE = POS_ZCSIG;
  RMT_FDM_DLL_FrameWork_FCS_RT_PrevZCX->Delay3_Reset_ZCE = POS_ZCSIG;
  RMT_FDM_DLL_FrameWork_FCS_RT_PrevZCX->Delay17_Reset_ZCE = POS_ZCSIG;
  RMT_FDM_DLL_FrameWork_FCS_RT_PrevZCX->Delay18_Reset_ZCE = POS_ZCSIG;
  RMT_FDM_DLL_FrameWork_FCS_RT_PrevZCX->Delay4_Reset_ZCE = POS_ZCSIG;
  RMT_FDM_DLL_FrameWork_FCS_RT_PrevZCX->Delay5_Reset_ZCE = POS_ZCSIG;
  RMT_FDM_DLL_FrameWork_FCS_RT_PrevZCX->Delay6_Reset_ZCE = POS_ZCSIG;
  RMT_FDM_DLL_FrameWork_FCS_RT_PrevZCX->Delay7_Reset_ZCE = POS_ZCSIG;
  RMT_FDM_DLL_FrameWork_FCS_RT_PrevZCX->Delay8_Reset_ZCE = POS_ZCSIG;
  RMT_FDM_DLL_FrameWork_FCS_RT_PrevZCX->Delay9_Reset_ZCE = POS_ZCSIG;
  RMT_FDM_DLL_FrameWork_FCS_RT_PrevZCX->Delay10_Reset_ZCE = POS_ZCSIG;
  RMT_FDM_DLL_FrameWork_FCS_RT_PrevZCX->Delay11_Reset_ZCE = POS_ZCSIG;
  RMT_FDM_DLL_FrameWork_FCS_RT_PrevZCX->Delay12_Reset_ZCE = POS_ZCSIG;
  RMT_FDM_DLL_FrameWork_FCS_RT_PrevZCX->Delay13_Reset_ZCE = POS_ZCSIG;
  RMT_FDM_DLL_FrameWork_FCS_RT_PrevZCX->Delay14_Reset_ZCE = POS_ZCSIG;
  RMT_FDM_DLL_FrameWork_FCS_RT_PrevZCX->Delay15_Reset_ZCE = POS_ZCSIG;
  RMT_FDM_DLL_FrameWork_FCS_RT_PrevZCX->Delay_Reset_ZCE_pegz = POS_ZCSIG;

  /* InitializeConditions for Delay: '<S2>/Delay16' */
  RMT_FDM_DLL_FrameWork_FCS_RT_DW->icLoad = true;

  /* InitializeConditions for Delay: '<S2>/Delay' */
  RMT_FDM_DLL_FrameWork_FCS_RT_DW->icLoad_ooxy = true;

  /* InitializeConditions for Delay: '<S2>/Delay1' */
  RMT_FDM_DLL_FrameWork_FCS_RT_DW->icLoad_hvp0 = true;

  /* InitializeConditions for Delay: '<S2>/Delay2' */
  RMT_FDM_DLL_FrameWork_FCS_RT_DW->icLoad_agwh = true;

  /* InitializeConditions for Delay: '<S2>/Delay3' */
  RMT_FDM_DLL_FrameWork_FCS_RT_DW->icLoad_k4aw = true;

  /* InitializeConditions for Delay: '<S2>/Delay17' */
  RMT_FDM_DLL_FrameWork_FCS_RT_DW->icLoad_eux1 = true;

  /* InitializeConditions for Delay: '<S2>/Delay18' */
  RMT_FDM_DLL_FrameWork_FCS_RT_DW->icLoad_mxgu = true;

  /* InitializeConditions for Delay: '<S2>/Delay4' */
  RMT_FDM_DLL_FrameWork_FCS_RT_DW->icLoad_pbo0 = true;

  /* InitializeConditions for Delay: '<S2>/Delay5' */
  RMT_FDM_DLL_FrameWork_FCS_RT_DW->icLoad_dtzm = true;

  /* InitializeConditions for Delay: '<S2>/Delay6' */
  RMT_FDM_DLL_FrameWork_FCS_RT_DW->icLoad_mfcp = true;

  /* InitializeConditions for Delay: '<S2>/Delay7' */
  RMT_FDM_DLL_FrameWork_FCS_RT_DW->icLoad_js0i = true;

  /* InitializeConditions for Delay: '<S2>/Delay8' */
  RMT_FDM_DLL_FrameWork_FCS_RT_DW->icLoad_doan = true;

  /* InitializeConditions for Delay: '<S2>/Delay9' */
  RMT_FDM_DLL_FrameWork_FCS_RT_DW->icLoad_mzf4 = true;

  /* InitializeConditions for Delay: '<S2>/Delay10' */
  RMT_FDM_DLL_FrameWork_FCS_RT_DW->icLoad_chzd = true;

  /* InitializeConditions for Delay: '<S2>/Delay11' */
  RMT_FDM_DLL_FrameWork_FCS_RT_DW->icLoad_giyv = true;

  /* InitializeConditions for Delay: '<S2>/Delay12' */
  RMT_FDM_DLL_FrameWork_FCS_RT_DW->icLoad_lwdp = true;

  /* InitializeConditions for Delay: '<S2>/Delay13' */
  RMT_FDM_DLL_FrameWork_FCS_RT_DW->icLoad_bu4u = true;

  /* InitializeConditions for Delay: '<S2>/Delay14' */
  RMT_FDM_DLL_FrameWork_FCS_RT_DW->icLoad_atsy = true;

  /* InitializeConditions for Delay: '<S2>/Delay15' */
  RMT_FDM_DLL_FrameWork_FCS_RT_DW->icLoad_nbvc = true;

  /* InitializeConditions for Delay: '<S5>/Delay' */
  memset(&RMT_FDM_DLL_FrameWork_FCS_RT_DW->Delay_DSTATE_oj24[0], 0, 10U * sizeof
         (real_T));

  /* InitializeConditions for DiscreteIntegrator: '<S47>/Phi_Ref' */
  RMT_FDM_DLL_FrameWork_FCS_RT_DW->Phi_Ref_PrevResetState = 2;

  /* InitializeConditions for DiscreteIntegrator: '<S47>/Theta_Ref' */
  RMT_FDM_DLL_FrameWork_FCS_RT_DW->Theta_Ref_PrevResetState = 2;

  /* InitializeConditions for DiscreteIntegrator: '<S48>/p_Ref' */
  RMT_FDM_DLL_FrameWork_FCS_RT_DW->p_Ref_PrevResetState = 2;

  /* InitializeConditions for DiscreteIntegrator: '<S48>/q_Ref' */
  RMT_FDM_DLL_FrameWork_FCS_RT_DW->q_Ref_PrevResetState = 2;

  /* InitializeConditions for DiscreteIntegrator: '<S48>/r_Ref' */
  RMT_FDM_DLL_FrameWork_FCS_RT_DW->r_Ref_PrevResetState = 2;

  /* InitializeConditions for DiscreteIntegrator: '<S62>/Discrete-Time Integrator' */
  RMT_FDM_DLL_FrameWork_FCS_RT_DW->DiscreteTimeIntegrator_PrevResetState = 2;

  /* InitializeConditions for DiscreteIntegrator: '<S63>/Discrete-Time Integrator' */
  RMT_FDM_DLL_FrameWork_FCS_RT_DW->DiscreteTimeIntegrator_PrevResetState_nmap =
    2;

  /* InitializeConditions for DiscreteIntegrator: '<S64>/Discrete-Time Integrator' */
  RMT_FDM_DLL_FrameWork_FCS_RT_DW->DiscreteTimeIntegrator_PrevResetState_fwtq =
    2;

  /* InitializeConditions for DiscreteIntegrator: '<S10>/Discrete-Time Integrator' */
  RMT_FDM_DLL_FrameWork_FCS_RT_DW->DiscreteTimeIntegrator_PrevResetState_dbpn =
    2;
  RMT_FDM_DLL_FrameWork_FCS_RT_DW->DiscreteTimeIntegrator_IC_LOADING = 1;

  /* End of SystemInitialize for SubSystem: '<Root>/FCS_INDI_Control' */

  /* SystemInitialize for ModelReference generated from: '<Root>/RMT_Plant' */
  RMT_FDM_RT_Init(&(RMT_FDM_DLL_FrameWork_FCS_RT_DW->RMT_Plant_InstanceData.rtm),
                  &(RMT_FDM_DLL_FrameWork_FCS_RT_DW->RMT_Plant_InstanceData.rtb),
                  &(RMT_FDM_DLL_FrameWork_FCS_RT_DW->RMT_Plant_InstanceData.rtdw),
                  &(RMT_FDM_DLL_FrameWork_FCS_RT_X->RMT_Plant_CSTATE),
                  &(RMT_FDM_DLL_FrameWork_FCS_RT_DW->RMT_Plant_InstanceData.rtzce));

  /* set "at time zero" to false */
  if (rtmIsFirstInitCond(RMT_FDM_DLL_FrameWork_FCS_RT_M)) {
    rtmSetFirstInitCond(RMT_FDM_DLL_FrameWork_FCS_RT_M, 0);
  }
}

/* Model terminate function */
void RMT_FDM_DLL_FrameWork_FCS_RT_terminate
  (RT_MODEL_RMT_FDM_DLL_FrameWork_FCS_RT_T * RMT_FDM_DLL_FrameWork_FCS_RT_M)
{
  rt_FREE(RMT_FDM_DLL_FrameWork_FCS_RT_M->solverInfo);

  /* model code */
  rt_FREE(RMT_FDM_DLL_FrameWork_FCS_RT_M->ModelData.blockIO);
  rt_FREE(RMT_FDM_DLL_FrameWork_FCS_RT_M->ModelData.contStates);
  rt_FREE(RMT_FDM_DLL_FrameWork_FCS_RT_M->ModelData.dwork);
  rt_FREE(RMT_FDM_DLL_FrameWork_FCS_RT_M->ModelData.prevZCSigState);
  rt_FREE(RMT_FDM_DLL_FrameWork_FCS_RT_M);
}

/* Model data allocation function */
RT_MODEL_RMT_FDM_DLL_FrameWork_FCS_RT_T *RMT_FDM_DLL_FrameWork_FCS_RT
  (Simulation_Control_Bus *RMT_FDM_DLL_FrameWork_FCS_RT_U_Simulation_Control,
   States_Init_Bus *RMT_FDM_DLL_FrameWork_FCS_RT_U_States_Init, real_T
   RMT_FDM_DLL_FrameWork_FCS_RT_U_w_cmd_radDs[8], fc_pilot_cmd_Bus
   *RMT_FDM_DLL_FrameWork_FCS_RT_U_fc_pilot_cmd, Failure_Bus
   *RMT_FDM_DLL_FrameWork_FCS_RT_U_Failures, Vehicle_Bus
   *RMT_FDM_DLL_FrameWork_FCS_RT_Y_Vehicle, Measurements_Bus
   *RMT_FDM_DLL_FrameWork_FCS_RT_Y_Measurements, fc_est_Bus
   *RMT_FDM_DLL_FrameWork_FCS_RT_Y_fc_estimation)
{
  RT_MODEL_RMT_FDM_DLL_FrameWork_FCS_RT_T *RMT_FDM_DLL_FrameWork_FCS_RT_M;
  RMT_FDM_DLL_FrameWork_FCS_RT_M = (RT_MODEL_RMT_FDM_DLL_FrameWork_FCS_RT_T *)
    malloc(sizeof(RT_MODEL_RMT_FDM_DLL_FrameWork_FCS_RT_T));
  if (RMT_FDM_DLL_FrameWork_FCS_RT_M == (NULL)) {
    return (NULL);
  }

  (void) memset((char *)RMT_FDM_DLL_FrameWork_FCS_RT_M, 0,
                sizeof(RT_MODEL_RMT_FDM_DLL_FrameWork_FCS_RT_T));

  {
    /* Setup solver object */
    RTWSolverInfo *rt_SolverInfo = (RTWSolverInfo *) malloc(sizeof(RTWSolverInfo));
    rt_VALIDATE_MEMORY(RMT_FDM_DLL_FrameWork_FCS_RT_M,rt_SolverInfo);
    RMT_FDM_DLL_FrameWork_FCS_RT_M->solverInfo = (rt_SolverInfo);
    rtsiSetSimTimeStepPtr(RMT_FDM_DLL_FrameWork_FCS_RT_M->solverInfo,
                          &RMT_FDM_DLL_FrameWork_FCS_RT_M->Timing.simTimeStep);
    rtsiSetTPtr(RMT_FDM_DLL_FrameWork_FCS_RT_M->solverInfo, &rtmGetTPtr
                (RMT_FDM_DLL_FrameWork_FCS_RT_M));
    rtsiSetStepSizePtr(RMT_FDM_DLL_FrameWork_FCS_RT_M->solverInfo,
                       &RMT_FDM_DLL_FrameWork_FCS_RT_M->Timing.stepSize0);
    rtsiSetdXPtr(RMT_FDM_DLL_FrameWork_FCS_RT_M->solverInfo,
                 &RMT_FDM_DLL_FrameWork_FCS_RT_M->ModelData.derivs);
    rtsiSetContStatesPtr(RMT_FDM_DLL_FrameWork_FCS_RT_M->solverInfo, (real_T **)
                         &RMT_FDM_DLL_FrameWork_FCS_RT_M->ModelData.contStates);
    rtsiSetNumContStatesPtr(RMT_FDM_DLL_FrameWork_FCS_RT_M->solverInfo,
      &RMT_FDM_DLL_FrameWork_FCS_RT_M->Sizes.numContStates);
    rtsiSetNumPeriodicContStatesPtr(RMT_FDM_DLL_FrameWork_FCS_RT_M->solverInfo,
      &RMT_FDM_DLL_FrameWork_FCS_RT_M->Sizes.numPeriodicContStates);
    rtsiSetPeriodicContStateIndicesPtr
      (RMT_FDM_DLL_FrameWork_FCS_RT_M->solverInfo,
       &RMT_FDM_DLL_FrameWork_FCS_RT_M->ModelData.periodicContStateIndices);
    rtsiSetPeriodicContStateRangesPtr(RMT_FDM_DLL_FrameWork_FCS_RT_M->solverInfo,
      &RMT_FDM_DLL_FrameWork_FCS_RT_M->ModelData.periodicContStateRanges);
    rtsiSetContStateDisabledPtr(RMT_FDM_DLL_FrameWork_FCS_RT_M->solverInfo,
      (boolean_T**) &RMT_FDM_DLL_FrameWork_FCS_RT_M->ModelData.contStateDisabled);
    rtsiSetErrorStatusPtr(RMT_FDM_DLL_FrameWork_FCS_RT_M->solverInfo,
                          (&rtmGetErrorStatus(RMT_FDM_DLL_FrameWork_FCS_RT_M)));
    rtsiSetRTModelPtr(RMT_FDM_DLL_FrameWork_FCS_RT_M->solverInfo,
                      RMT_FDM_DLL_FrameWork_FCS_RT_M);
  }

  rtsiSetSolverName(RMT_FDM_DLL_FrameWork_FCS_RT_M->solverInfo,"ode4");

  /* block I/O */
  {
    B_RMT_FDM_DLL_FrameWork_FCS_RT_T *b = (B_RMT_FDM_DLL_FrameWork_FCS_RT_T *)
      malloc(sizeof(B_RMT_FDM_DLL_FrameWork_FCS_RT_T));
    rt_VALIDATE_MEMORY(RMT_FDM_DLL_FrameWork_FCS_RT_M,b);
    RMT_FDM_DLL_FrameWork_FCS_RT_M->ModelData.blockIO = (b);
  }

  /* states (continuous) */
  {
    X_RMT_FDM_DLL_FrameWork_FCS_RT_T *x = (X_RMT_FDM_DLL_FrameWork_FCS_RT_T *)
      malloc(sizeof(X_RMT_FDM_DLL_FrameWork_FCS_RT_T));
    rt_VALIDATE_MEMORY(RMT_FDM_DLL_FrameWork_FCS_RT_M,x);
    RMT_FDM_DLL_FrameWork_FCS_RT_M->ModelData.contStates = (x);
  }

  /* disabled states */
  {
    XDis_RMT_FDM_DLL_FrameWork_FCS_RT_T *xdis =
      (XDis_RMT_FDM_DLL_FrameWork_FCS_RT_T *) malloc(sizeof
      (XDis_RMT_FDM_DLL_FrameWork_FCS_RT_T));
    rt_VALIDATE_MEMORY(RMT_FDM_DLL_FrameWork_FCS_RT_M,xdis);
    RMT_FDM_DLL_FrameWork_FCS_RT_M->ModelData.contStateDisabled = (xdis);
  }

  /* states (dwork) */
  {
    DW_RMT_FDM_DLL_FrameWork_FCS_RT_T *dwork =
      (DW_RMT_FDM_DLL_FrameWork_FCS_RT_T *) malloc(sizeof
      (DW_RMT_FDM_DLL_FrameWork_FCS_RT_T));
    rt_VALIDATE_MEMORY(RMT_FDM_DLL_FrameWork_FCS_RT_M,dwork);
    RMT_FDM_DLL_FrameWork_FCS_RT_M->ModelData.dwork = (dwork);
  }

  /* previous zero-crossing states */
  {
    PrevZCX_RMT_FDM_DLL_FrameWork_FCS_RT_T *zc =
      (PrevZCX_RMT_FDM_DLL_FrameWork_FCS_RT_T *) malloc(sizeof
      (PrevZCX_RMT_FDM_DLL_FrameWork_FCS_RT_T));
    rt_VALIDATE_MEMORY(RMT_FDM_DLL_FrameWork_FCS_RT_M,zc);
    RMT_FDM_DLL_FrameWork_FCS_RT_M->ModelData.prevZCSigState = (zc);
  }

  {
    B_RMT_FDM_DLL_FrameWork_FCS_RT_T *RMT_FDM_DLL_FrameWork_FCS_RT_B =
      RMT_FDM_DLL_FrameWork_FCS_RT_M->ModelData.blockIO;
    DW_RMT_FDM_DLL_FrameWork_FCS_RT_T *RMT_FDM_DLL_FrameWork_FCS_RT_DW =
      RMT_FDM_DLL_FrameWork_FCS_RT_M->ModelData.dwork;
    X_RMT_FDM_DLL_FrameWork_FCS_RT_T *RMT_FDM_DLL_FrameWork_FCS_RT_X =
      RMT_FDM_DLL_FrameWork_FCS_RT_M->ModelData.contStates;
    XDis_RMT_FDM_DLL_FrameWork_FCS_RT_T *RMT_FDM_DLL_FrameWork_FCS_RT_XDis =
      ((XDis_RMT_FDM_DLL_FrameWork_FCS_RT_T *)
       RMT_FDM_DLL_FrameWork_FCS_RT_M->ModelData.contStateDisabled);
    rtsiSetSimTimeStep(RMT_FDM_DLL_FrameWork_FCS_RT_M->solverInfo,
                       MAJOR_TIME_STEP);
    rtsiSetIsMinorTimeStepWithModeChange
      (RMT_FDM_DLL_FrameWork_FCS_RT_M->solverInfo, false);
    rtsiSetIsContModeFrozen(RMT_FDM_DLL_FrameWork_FCS_RT_M->solverInfo, false);
    RMT_FDM_DLL_FrameWork_FCS_RT_M->ModelData.intgData.y =
      RMT_FDM_DLL_FrameWork_FCS_RT_M->ModelData.odeY;
    RMT_FDM_DLL_FrameWork_FCS_RT_M->ModelData.intgData.f[0] =
      RMT_FDM_DLL_FrameWork_FCS_RT_M->ModelData.odeF[0];
    RMT_FDM_DLL_FrameWork_FCS_RT_M->ModelData.intgData.f[1] =
      RMT_FDM_DLL_FrameWork_FCS_RT_M->ModelData.odeF[1];
    RMT_FDM_DLL_FrameWork_FCS_RT_M->ModelData.intgData.f[2] =
      RMT_FDM_DLL_FrameWork_FCS_RT_M->ModelData.odeF[2];
    RMT_FDM_DLL_FrameWork_FCS_RT_M->ModelData.intgData.f[3] =
      RMT_FDM_DLL_FrameWork_FCS_RT_M->ModelData.odeF[3];
    RMT_FDM_DLL_FrameWork_FCS_RT_M->ModelData.contStates =
      ((X_RMT_FDM_DLL_FrameWork_FCS_RT_T *) RMT_FDM_DLL_FrameWork_FCS_RT_X);
    RMT_FDM_DLL_FrameWork_FCS_RT_M->ModelData.contStateDisabled =
      ((XDis_RMT_FDM_DLL_FrameWork_FCS_RT_T *) RMT_FDM_DLL_FrameWork_FCS_RT_XDis);
    RMT_FDM_DLL_FrameWork_FCS_RT_M->Timing.tStart = (0.0);
    rtsiSetSolverData(RMT_FDM_DLL_FrameWork_FCS_RT_M->solverInfo, (void *)
                      &RMT_FDM_DLL_FrameWork_FCS_RT_M->ModelData.intgData);
    rtmSetTPtr(RMT_FDM_DLL_FrameWork_FCS_RT_M,
               &RMT_FDM_DLL_FrameWork_FCS_RT_M->Timing.tArray[0]);
    RMT_FDM_DLL_FrameWork_FCS_RT_M->Timing.stepSize0 = 0.004;
    rtmSetFirstInitCond(RMT_FDM_DLL_FrameWork_FCS_RT_M, 1);

    /* block I/O */
    (void) memset(((void *) RMT_FDM_DLL_FrameWork_FCS_RT_B), 0,
                  sizeof(B_RMT_FDM_DLL_FrameWork_FCS_RT_T));

    /* states (continuous) */
    {
      (void) memset((void *)RMT_FDM_DLL_FrameWork_FCS_RT_X, 0,
                    sizeof(X_RMT_FDM_DLL_FrameWork_FCS_RT_T));
    }

    /* disabled states */
    {
      (void) memset((void *)RMT_FDM_DLL_FrameWork_FCS_RT_XDis, 0,
                    sizeof(XDis_RMT_FDM_DLL_FrameWork_FCS_RT_T));
    }

    /* states (dwork) */
    (void) memset((void *)RMT_FDM_DLL_FrameWork_FCS_RT_DW, 0,
                  sizeof(DW_RMT_FDM_DLL_FrameWork_FCS_RT_T));

    /* external inputs */
    (void)memset((void *)&RMT_FDM_DLL_FrameWork_FCS_RT_U_w_cmd_radDs[0], 0, 8U *
                 sizeof(real_T));
    *RMT_FDM_DLL_FrameWork_FCS_RT_U_Simulation_Control =
      RMT_FDM_DLL_FrameWork_FCS_RT_rtZSimulation_Control_Bus;
    *RMT_FDM_DLL_FrameWork_FCS_RT_U_States_Init =
      RMT_FDM_DLL_FrameWork_FCS_RT_rtZStates_Init_Bus;
    *RMT_FDM_DLL_FrameWork_FCS_RT_U_fc_pilot_cmd =
      RMT_FDM_DLL_FrameWork_FCS_RT_rtZfc_pilot_cmd_Bus;
    *RMT_FDM_DLL_FrameWork_FCS_RT_U_Failures =
      RMT_FDM_DLL_FrameWork_FCS_RT_rtZFailure_Bus;

    /* external outputs */
    *RMT_FDM_DLL_FrameWork_FCS_RT_Y_Vehicle =
      RMT_FDM_DLL_FrameWork_FCS_RT_rtZVehicle_Bus;
    *RMT_FDM_DLL_FrameWork_FCS_RT_Y_Measurements =
      RMT_FDM_DLL_FrameWork_FCS_RT_rtZMeasurements_Bus;
    *RMT_FDM_DLL_FrameWork_FCS_RT_Y_fc_estimation =
      RMT_FDM_DLL_FrameWork_FCS_RT_rtZfc_est_Bus;

    /* previous zero-crossing states */
    {
    }

    {
      static uint32_T *clockTickPtrs[3];
      static real_T *taskTimePtrs[3];
      static uint32_T *taskCounterPtrs;
      RMT_FDM_DLL_FrameWork_FCS_RT_M->timingBridge.nTasks = 3;
      clockTickPtrs[0] = &(RMT_FDM_DLL_FrameWork_FCS_RT_M->Timing.clockTick0);
      clockTickPtrs[1] = &(RMT_FDM_DLL_FrameWork_FCS_RT_M->Timing.clockTick1);
      clockTickPtrs[2] = &(RMT_FDM_DLL_FrameWork_FCS_RT_M->Timing.clockTick2);
      RMT_FDM_DLL_FrameWork_FCS_RT_M->timingBridge.clockTick = clockTickPtrs;
      RMT_FDM_DLL_FrameWork_FCS_RT_M->timingBridge.clockTickH = (NULL);
      taskCounterPtrs =
        &(RMT_FDM_DLL_FrameWork_FCS_RT_M->Timing.TaskCounters.TID[0]);
      RMT_FDM_DLL_FrameWork_FCS_RT_M->timingBridge.taskCounter = taskCounterPtrs;
      taskTimePtrs[0] = &(RMT_FDM_DLL_FrameWork_FCS_RT_M->Timing.t[0]);
      taskTimePtrs[1] = (NULL);
      taskTimePtrs[2] = (NULL);
      RMT_FDM_DLL_FrameWork_FCS_RT_M->timingBridge.taskTime = taskTimePtrs;
      RMT_FDM_DLL_FrameWork_FCS_RT_M->timingBridge.firstInitCond =
        &rtmIsFirstInitCond(RMT_FDM_DLL_FrameWork_FCS_RT_M);
    }

    /* Model Initialize function for ModelReference Block: '<Root>/RMT_Plant' */
    RMT_FDM_RT_initialize(rtmGetErrorStatusPointer
                          (RMT_FDM_DLL_FrameWork_FCS_RT_M),
                          rtmGetStopRequestedPtr(RMT_FDM_DLL_FrameWork_FCS_RT_M),
                          RMT_FDM_DLL_FrameWork_FCS_RT_M->solverInfo,
                          &RMT_FDM_DLL_FrameWork_FCS_RT_M->timingBridge, 0, 1, 2,
                          &(RMT_FDM_DLL_FrameWork_FCS_RT_DW->RMT_Plant_InstanceData.rtm),
                          &(RMT_FDM_DLL_FrameWork_FCS_RT_DW->RMT_Plant_InstanceData.rtb),
                          &(RMT_FDM_DLL_FrameWork_FCS_RT_DW->RMT_Plant_InstanceData.rtdw),
                          &(RMT_FDM_DLL_FrameWork_FCS_RT_DW->RMT_Plant_InstanceData.rtzce));
  }

  return RMT_FDM_DLL_FrameWork_FCS_RT_M;
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
