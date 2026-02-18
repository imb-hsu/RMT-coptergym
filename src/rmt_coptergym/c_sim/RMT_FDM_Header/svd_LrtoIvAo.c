/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: svd_LrtoIvAo.c
 *
 * Code generated for Simulink model 'RMT_FDM_DLL_FrameWork_FCS_RT'.
 *
 * Model version                  : 11.34
 * Simulink Coder version         : 24.2 (R2024b) 21-Jun-2024
 * C/C++ source code generated on : Thu Dec  4 22:28:01 2025
 */

#include "rtwtypes.h"
#include "svd_LrtoIvAo.h"
#include <string.h>
#include "xzlangeM_LAOIK0zM.h"
#include "xzlascl_ze48YLp0.h"
#include "xnrm2_Fo3hhCrm.h"
#include <math.h>
#include "xnrm2_Kp9rP65Y.h"
#include "xdotc_HctHpm1R.h"
#include "xaxpy_0xav9hoQ.h"
#include "xzlascl_maz9QAwP.h"
#include "xrotg_zvvopXKT.h"
#include "xaxpy_yDaHKA4W.h"
#include "xaxpy_Ch3dBsmQ.h"

/* Function for MATLAB Function: '<S19>/Pseudoinverse' */
void svd_LrtoIvAo(const real_T A[16], real_T U[4])
{
  real_T b_A[16];
  real_T e[4];
  real_T s[4];
  real_T work[4];
  real_T a__1;
  real_T a__2;
  real_T a__3;
  real_T a__3_tmp;
  real_T a_tmp;
  real_T anrm;
  real_T b;
  real_T b_a;
  real_T b_cs;
  real_T b_f;
  real_T b_sn;
  real_T c;
  real_T c_a;
  real_T c_cs;
  real_T c_sn;
  real_T cs;
  real_T cscale;
  real_T d_cs;
  real_T d_sn;
  real_T emm1;
  real_T f;
  real_T f_tmp;
  real_T f_tmp_0;
  real_T f_tmp_1;
  real_T f_tmp_2;
  real_T g;
  real_T g_tmp;
  real_T iter;
  real_T kase;
  real_T nrm;
  real_T rt;
  real_T scale;
  real_T scale_tmp;
  real_T scale_tmp_0;
  real_T scale_tmp_1;
  real_T shift;
  real_T sm;
  real_T smm1;
  real_T sn;
  real_T snorm;
  real_T sqds;
  real_T test;
  real_T tmp;
  real_T tmp_0;
  real_T tmp_1;
  real_T tmp_2;
  real_T tmp_3;
  real_T tmp_4;
  real_T ztest;
  real_T ztest0;
  int32_T b_ii;
  int32_T b_jj;
  int32_T b_k;
  int32_T b_q;
  int32_T c_ii;
  int32_T c_jj;
  int32_T c_k;
  int32_T c_q;
  int32_T d_ii;
  int32_T d_k;
  int32_T e_ii;
  int32_T e_k;
  int32_T f_k;
  int32_T g_k;
  int32_T h;
  int32_T h_k;
  int32_T i;
  int32_T i_0;
  int32_T i_1;
  int32_T i_2;
  int32_T j;
  int32_T j_k;
  int32_T jj;
  int32_T l;
  int32_T m;
  int32_T q;
  int32_T q_tmp;
  int32_T qjj;
  int32_T qp1;
  int32_T qp1_tmp;
  int32_T qq;
  int32_T qq_tmp;
  int32_T qs;
  boolean_T apply_transform;
  boolean_T doscale;
  boolean_T exitg1;
  memcpy(&b_A[0], &A[0], 16U * sizeof(real_T));
  for (i_0 = 0; i_0 < 4; i_0 = i_0 + 1) {
    s[i_0] = 0.0;
  }

  for (i_1 = 0; i_1 < 4; i_1 = i_1 + 1) {
    e[i_1] = 0.0;
  }

  for (i_2 = 0; i_2 < 4; i_2 = i_2 + 1) {
    work[i_2] = 0.0;
  }

  doscale = false;
  anrm = xzlangeM_LAOIK0zM(A);
  cscale = anrm;
  if ((anrm > 0.0) && (anrm < 6.7178761075670888E-139)) {
    doscale = true;
    cscale = 6.7178761075670888E-139;
  } else if (anrm > 1.4885657073574029E+138) {
    doscale = true;
    cscale = 1.4885657073574029E+138;
  }

  if (doscale) {
    xzlascl_ze48YLp0(anrm, cscale, b_A);
  }

  for (b_q = 0; b_q < 3; b_q = b_q + 1) {
    qp1_tmp = (b_q + 1) + 1;
    qq_tmp = ((b_q + 1) - 1) << 2;
    qq = (b_q + 1) + qq_tmp;
    apply_transform = false;
    nrm = xnrm2_Fo3hhCrm((4 - (b_q + 1)) + 1, b_A, qq);
    if (nrm > 0.0) {
      apply_transform = true;
      if (b_A[qq - 1] < 0.0) {
        s[(b_q + 1) - 1] = -nrm;
      } else {
        s[(b_q + 1) - 1] = nrm;
      }

      tmp_1 = s[(b_q + 1) - 1];
      if (fabs(tmp_1) >= 1.0020841800044864E-292) {
        b_a = 1.0 / tmp_1;
        j = qq + (((4 - (b_q + 1)) + 1) - 1);
        for (h_k = qq; h_k <= j; h_k = h_k + 1) {
          b_A[h_k - 1] = b_a * b_A[h_k - 1];
        }
      } else {
        h = qq + (((4 - (b_q + 1)) + 1) - 1);
        for (f_k = qq; f_k <= h; f_k = f_k + 1) {
          b_A[f_k - 1] = b_A[f_k - 1] / tmp_1;
        }
      }

      b_A[qq - 1] = b_A[qq - 1] + 1.0;
      s[(b_q + 1) - 1] = -tmp_1;
    } else {
      s[(b_q + 1) - 1] = 0.0;
    }

    for (jj = qp1_tmp; jj < 5; jj = jj + 1) {
      qjj = (b_q + 1) + ((jj - 1) << 2);
      if (apply_transform) {
        xaxpy_0xav9hoQ((4 - (b_q + 1)) + 1, -(xdotc_HctHpm1R((4 - (b_q + 1)) + 1,
          b_A, qq, b_A, qjj) / b_A[((b_q + 1) - 1) + qq_tmp]), qq, b_A, qjj);
      }

      e[jj - 1] = b_A[qjj - 1];
    }

    if (b_q + 1 <= 2) {
      nrm = xnrm2_Kp9rP65Y(4 - (b_q + 1), e, (b_q + 1) + 1);
      if (nrm == 0.0) {
        e[(b_q + 1) - 1] = 0.0;
      } else {
        if (e[((b_q + 1) + 1) - 1] < 0.0) {
          e[(b_q + 1) - 1] = -nrm;
        } else {
          e[(b_q + 1) - 1] = nrm;
        }

        a_tmp = e[(b_q + 1) - 1];
        if (fabs(a_tmp) >= 1.0020841800044864E-292) {
          c_a = 1.0 / a_tmp;
          l = ((b_q + 1) + 1) + ((4 - (b_q + 1)) - 1);
          for (j_k = qp1_tmp; j_k <= l; j_k = j_k + 1) {
            e[j_k - 1] = c_a * e[j_k - 1];
          }
        } else {
          i = ((b_q + 1) + 1) + ((4 - (b_q + 1)) - 1);
          for (g_k = qp1_tmp; g_k <= i; g_k = g_k + 1) {
            e[g_k - 1] = e[g_k - 1] / a_tmp;
          }
        }

        e[((b_q + 1) + 1) - 1] = e[((b_q + 1) + 1) - 1] + 1.0;
        e[(b_q + 1) - 1] = -e[(b_q + 1) - 1];
        for (b_ii = qp1_tmp; b_ii < 5; b_ii = b_ii + 1) {
          work[b_ii - 1] = 0.0;
        }

        for (b_jj = qp1_tmp; b_jj < 5; b_jj = b_jj + 1) {
          xaxpy_yDaHKA4W(4 - (b_q + 1), e[b_jj - 1], b_A, ((b_q + 1) + 1) +
                         ((b_jj - 1) << 2), work, (b_q + 1) + 1);
        }

        for (c_jj = qp1_tmp; c_jj < 5; c_jj = c_jj + 1) {
          xaxpy_Ch3dBsmQ(4 - (b_q + 1), -e[c_jj - 1] / e[((b_q + 1) + 1) - 1],
                         work, (b_q + 1) + 1, b_A, ((b_q + 1) + 1) + ((c_jj - 1)
            << 2));
        }
      }
    }
  }

  m = 4;
  s[3] = b_A[15];
  e[2] = b_A[14];
  e[3] = 0.0;
  for (c_q = 0; c_q < 4; c_q = c_q + 1) {
    tmp = s[(c_q + 1) - 1];
    if (tmp != 0.0) {
      rt = fabs(tmp);
      s[(c_q + 1) - 1] = rt;
      if (c_q + 1 < 4) {
        e[(c_q + 1) - 1] = e[(c_q + 1) - 1] / (tmp / rt);
      }
    }

    if (c_q + 1 < 4) {
      tmp_0 = e[(c_q + 1) - 1];
      if (tmp_0 != 0.0) {
        rt = fabs(tmp_0);
        e[(c_q + 1) - 1] = rt;
        s[((c_q + 1) + 1) - 1] = s[((c_q + 1) + 1) - 1] * (rt / tmp_0);
      }
    }
  }

  iter = 0.0;
  snorm = 0.0;
  for (c_ii = 0; c_ii < 4; c_ii = c_ii + 1) {
    snorm = fmax(snorm, fmax(fabs(s[(c_ii + 1) - 1]), fabs(e[(c_ii + 1) - 1])));
  }

  while ((m > 0) && (!(iter >= 75.0))) {
    q_tmp = m - 1;
    q = m - 1;
    d_ii = m - 1;
    exitg1 = false;
    while ((exitg1 == false) && (d_ii > -1)) {
      q = d_ii;
      if (d_ii == 0) {
        exitg1 = true;
      } else {
        ztest0 = fabs(e[d_ii - 1]);
        if (ztest0 <= 2.2204460492503131E-16 * (fabs(s[d_ii - 1]) + fabs(s[(d_ii
               + 1) - 1]))) {
          e[d_ii - 1] = 0.0;
          exitg1 = true;
        } else if ((ztest0 <= 1.0020841800044864E-292) || ((iter > 20.0) &&
                    (ztest0 <= 2.2204460492503131E-16 * snorm))) {
          e[d_ii - 1] = 0.0;
          exitg1 = true;
        } else {
          d_ii = d_ii + -1;
        }
      }
    }

    if (q == m - 1) {
      kase = 4.0;
    } else {
      qs = m;
      e_ii = m;
      exitg1 = false;
      while ((exitg1 == false) && (e_ii >= q)) {
        qs = e_ii;
        if (e_ii == q) {
          exitg1 = true;
        } else {
          test = 0.0;
          if (e_ii < m) {
            test = fabs(e[e_ii - 1]);
          }

          if (e_ii > q + 1) {
            test = test + fabs(e[(e_ii - 1) - 1]);
          }

          ztest = fabs(s[e_ii - 1]);
          if ((ztest <= 2.2204460492503131E-16 * test) || (ztest <=
               1.0020841800044864E-292)) {
            s[e_ii - 1] = 0.0;
            exitg1 = true;
          } else {
            e_ii = e_ii + -1;
          }
        }
      }

      if (qs == q) {
        kase = 3.0;
      } else if (qs == m) {
        kase = 1.0;
      } else {
        kase = 2.0;
        q = qs;
      }
    }

    q = q + 1;
    switch ((int32_T)kase) {
     case 1:
      f = e[(m - 1) - 1];
      e[(m - 1) - 1] = 0.0;
      for (b_k = q_tmp; b_k >= q; b_k = b_k - 1) {
        xrotg_zvvopXKT(&s[b_k - 1], &f, &cs, &sn);
        if (b_k > q) {
          f_tmp_0 = e[(b_k - 1) - 1];
          f = -sn * f_tmp_0;
          e[(b_k - 1) - 1] = f_tmp_0 * cs;
        }
      }
      break;

     case 2:
      f = e[(q - 1) - 1];
      e[(q - 1) - 1] = 0.0;
      for (c_k = q; c_k <= m; c_k = c_k + 1) {
        a__1 = f;
        xrotg_zvvopXKT(&s[c_k - 1], &a__1, &b_cs, &b_sn);
        f_tmp = e[c_k - 1];
        f = -b_sn * f_tmp;
        e[c_k - 1] = f_tmp * b_cs;
      }
      break;

     case 3:
      scale_tmp = s[m - 1];
      scale_tmp_0 = s[(m - 1) - 1];
      scale_tmp_1 = e[(m - 1) - 1];
      scale = fmax(fmax(fmax(fmax(fabs(scale_tmp), fabs(scale_tmp_0)), fabs
        (scale_tmp_1)), fabs(s[q - 1])), fabs(e[q - 1]));
      sm = scale_tmp / scale;
      smm1 = scale_tmp_0 / scale;
      emm1 = scale_tmp_1 / scale;
      sqds = s[q - 1] / scale;
      b = ((smm1 + sm) * (smm1 - sm) + emm1 * emm1) / 2.0;
      c = sm * emm1;
      c = c * c;
      if ((b != 0.0) || (c != 0.0)) {
        shift = sqrt(b * b + c);
        if (b < 0.0) {
          shift = -shift;
        }

        shift = c / (b + shift);
      } else {
        shift = 0.0;
      }

      f = (sqds + sm) * (sqds - sm) + shift;
      g = sqds * (e[q - 1] / scale);
      for (d_k = q; d_k <= q_tmp; d_k = d_k + 1) {
        b_f = f;
        a__2 = g;
        xrotg_zvvopXKT(&b_f, &a__2, &c_cs, &c_sn);
        if (d_k > q) {
          e[(d_k - 1) - 1] = b_f;
        }

        f_tmp_1 = e[d_k - 1];
        f_tmp_2 = s[d_k - 1];
        e[d_k - 1] = c_cs * f_tmp_1 - c_sn * f_tmp_2;
        a__3_tmp = s[(d_k + 1) - 1];
        a__3 = c_sn * a__3_tmp;
        s[(d_k + 1) - 1] = a__3_tmp * c_cs;
        s[d_k - 1] = c_cs * f_tmp_2 + c_sn * f_tmp_1;
        xrotg_zvvopXKT(&s[d_k - 1], &a__3, &d_cs, &d_sn);
        f = d_cs * e[d_k - 1] + d_sn * s[(d_k + 1) - 1];
        s[(d_k + 1) - 1] = -d_sn * e[d_k - 1] + d_cs * s[(d_k + 1) - 1];
        g_tmp = e[(d_k + 1) - 1];
        g = d_sn * g_tmp;
        e[(d_k + 1) - 1] = g_tmp * d_cs;
      }

      e[(m - 1) - 1] = f;
      iter = iter + 1.0;
      break;

     default:
      tmp_2 = s[q - 1];
      if (tmp_2 < 0.0) {
        s[q - 1] = -tmp_2;
      }

      qp1 = q + 1;
      exitg1 = false;
      while ((exitg1 == false) && (q < 4)) {
        tmp_3 = s[q - 1];
        tmp_4 = s[qp1 - 1];
        if (tmp_3 < tmp_4) {
          s[q - 1] = tmp_4;
          s[qp1 - 1] = tmp_3;
          q = qp1;
          qp1 = qp1 + 1;
        } else {
          exitg1 = true;
        }
      }

      iter = 0.0;
      m = m - 1;
      break;
    }
  }

  for (e_k = 0; e_k < 4; e_k = e_k + 1) {
    U[(e_k + 1) - 1] = s[(e_k + 1) - 1];
  }

  if (doscale) {
    xzlascl_maz9QAwP(cscale, anrm, U);
  }
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
