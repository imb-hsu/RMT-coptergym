/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: svd_I60xL6TN.c
 *
 * Code generated for Simulink model 'RMT_FDM_DLL_FrameWork_FCS_RT'.
 *
 * Model version                  : 11.39
 * Simulink Coder version         : 24.2 (R2024b) 21-Jun-2024
 * C/C++ source code generated on : Mon Mar 30 13:54:53 2026
 */

#include "rtwtypes.h"
#include "svd_I60xL6TN.h"
#include <string.h>
#include "xzlangeM_d3RDx07R.h"
#include "xzlascl_jaH7XzNd.h"
#include "xnrm2_AL5aFZZW.h"
#include "xnrm2_kHsVTR5O.h"
#include "xdotc_p0qvOGUu.h"
#include "xaxpy_ZvFxXzD7.h"
#include <math.h>
#include "xzlascl_6I4v9nni.h"
#include "xaxpy_KwxR7ZHj.h"
#include "xaxpy_4ZMPT4dQ.h"
#include "xrotg_zvvopXKT.h"

/* Function for MATLAB Function: '<S19>/nullspace' */
void svd_I60xL6TN(const real_T A_data[], const int32_T A_size[2], real_T U_data[],
                  int32_T *U_size)
{
  real_T b_A_data[100];
  real_T e_data[10];
  real_T s_data[10];
  real_T work[10];
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
  int32_T b_A_size[2];
  int32_T b_ii;
  int32_T b_jj;
  int32_T b_q;
  int32_T c_ii;
  int32_T c_jj;
  int32_T c_k;
  int32_T c_q;
  int32_T d_ii;
  int32_T d_k;
  int32_T e_ii;
  int32_T e_k;
  int32_T e_size;
  int32_T g_k;
  int32_T h;
  int32_T h_k;
  int32_T i_k;
  int32_T i_tmp;
  int32_T j_k;
  int32_T jj;
  int32_T loop_ub;
  int32_T loop_ub_tmp;
  int32_T m;
  int32_T nct;
  int32_T o;
  int32_T p;
  int32_T pmq;
  int32_T q;
  int32_T q_tmp;
  int32_T qjj;
  int32_T qp1;
  int32_T qp1_tmp;
  int32_T qq;
  int32_T qq_tmp;
  int32_T qs;
  int32_T t;
  int32_T u;
  int32_T v;
  int32_T y;
  boolean_T apply_transform;
  boolean_T doscale;
  boolean_T exitg1;
  b_A_size[0] = 10;
  b_A_size[1] = A_size[1];
  loop_ub = A_size[0] * A_size[1] - 1;
  if (0 <= loop_ub) {
    memcpy(&b_A_data[0], &A_data[0], (uint32_T)(loop_ub + 1) * sizeof(real_T));
  }

  p = A_size[1];
  loop_ub_tmp = A_size[1] - 1;
  if (0 <= loop_ub_tmp) {
    memset(&s_data[0], 0, (uint32_T)(loop_ub_tmp + 1) * sizeof(real_T));
  }

  e_size = A_size[1];
  if (0 <= loop_ub_tmp) {
    memset(&e_data[0], 0, (uint32_T)(loop_ub_tmp + 1) * sizeof(real_T));
  }

  memset(&work[0], 0, 10U * sizeof(real_T));
  doscale = false;
  anrm = xzlangeM_d3RDx07R(A_data, A_size);
  cscale = anrm;
  if ((anrm > 0.0) && (anrm < 6.7178761075670888E-139)) {
    doscale = true;
    cscale = 6.7178761075670888E-139;
  } else if (anrm > 1.4885657073574029E+138) {
    doscale = true;
    cscale = 1.4885657073574029E+138;
  }

  if (doscale) {
    xzlascl_jaH7XzNd(anrm, cscale, A_size[1], b_A_data);
  }

  if (9 <= A_size[1]) {
    nct = 9;
  } else {
    nct = A_size[1];
  }

  if (nct >= A_size[1] - 2) {
    y = nct;
  } else {
    y = A_size[1] - 2;
  }

  h = (uint8_T)y;
  for (b_q = 0; b_q < h; b_q = b_q + 1) {
    qp1_tmp = (b_q + 1) + 1;
    qq_tmp = 10 * ((b_q + 1) - 1);
    qq = (b_q + 1) + qq_tmp;
    apply_transform = false;
    if (b_q + 1 <= nct) {
      nrm = xnrm2_AL5aFZZW((10 - (b_q + 1)) + 1, b_A_data, qq);
      if (nrm > 0.0) {
        apply_transform = true;
        if (b_A_data[qq - 1] < 0.0) {
          s_data[(b_q + 1) - 1] = -nrm;
        } else {
          s_data[(b_q + 1) - 1] = nrm;
        }

        tmp_0 = s_data[(b_q + 1) - 1];
        if (fabs(tmp_0) >= 1.0020841800044864E-292) {
          b_a = 1.0 / tmp_0;
          u = qq + (((10 - (b_q + 1)) + 1) - 1);
          for (i_k = qq; i_k <= u; i_k = i_k + 1) {
            b_A_data[i_k - 1] = b_a * b_A_data[i_k - 1];
          }
        } else {
          o = qq + (((10 - (b_q + 1)) + 1) - 1);
          for (g_k = qq; g_k <= o; g_k = g_k + 1) {
            b_A_data[g_k - 1] = b_A_data[g_k - 1] / tmp_0;
          }
        }

        b_A_data[qq - 1] = b_A_data[qq - 1] + 1.0;
        s_data[(b_q + 1) - 1] = -tmp_0;
      } else {
        s_data[(b_q + 1) - 1] = 0.0;
      }
    }

    for (jj = qp1_tmp; jj <= p; jj = jj + 1) {
      qjj = (b_q + 1) + 10 * (jj - 1);
      if (apply_transform) {
        xaxpy_ZvFxXzD7((10 - (b_q + 1)) + 1, -(xdotc_p0qvOGUu((10 - (b_q + 1)) +
          1, b_A_data, qq, b_A_data, qjj) / b_A_data[((b_q + 1) - 1) + qq_tmp]),
                       qq, b_A_data, qjj);
      }

      e_data[jj - 1] = b_A_data[qjj - 1];
    }

    if (b_q + 1 <= p - 2) {
      pmq = p - (b_q + 1);
      nrm = xnrm2_kHsVTR5O(pmq, e_data, (b_q + 1) + 1);
      if (nrm == 0.0) {
        e_data[(b_q + 1) - 1] = 0.0;
      } else {
        if (e_data[((b_q + 1) + 1) - 1] < 0.0) {
          e_data[(b_q + 1) - 1] = -nrm;
        } else {
          e_data[(b_q + 1) - 1] = nrm;
        }

        a_tmp = e_data[(b_q + 1) - 1];
        if (fabs(a_tmp) >= 1.0020841800044864E-292) {
          c_a = 1.0 / a_tmp;
          v = ((b_q + 1) + 1) + (pmq - 1);
          for (j_k = qp1_tmp; j_k <= v; j_k = j_k + 1) {
            e_data[j_k - 1] = c_a * e_data[j_k - 1];
          }
        } else {
          t = ((b_q + 1) + 1) + (pmq - 1);
          for (h_k = qp1_tmp; h_k <= t; h_k = h_k + 1) {
            e_data[h_k - 1] = e_data[h_k - 1] / a_tmp;
          }
        }

        e_data[((b_q + 1) + 1) - 1] = e_data[((b_q + 1) + 1) - 1] + 1.0;
        e_data[(b_q + 1) - 1] = -e_data[(b_q + 1) - 1];
        for (b_ii = qp1_tmp; b_ii < 11; b_ii = b_ii + 1) {
          work[b_ii - 1] = 0.0;
        }

        for (b_jj = qp1_tmp; b_jj <= p; b_jj = b_jj + 1) {
          xaxpy_KwxR7ZHj(10 - (b_q + 1), e_data[b_jj - 1], b_A_data, ((b_q + 1)
            + 1) + 10 * (b_jj - 1), work, (b_q + 1) + 1);
        }

        for (c_jj = qp1_tmp; c_jj <= p; c_jj = c_jj + 1) {
          xaxpy_4ZMPT4dQ(10 - (b_q + 1), -e_data[c_jj - 1] / e_data[((b_q + 1) +
            1) - 1], work, (b_q + 1) + 1, b_A_data, ((b_q + 1) + 1) + 10 * (c_jj
            - 1));
        }
      }
    }
  }

  m = A_size[1];
  if (nct < A_size[1]) {
    s_data[(nct + 1) - 1] = b_A_data[((nct + 1) - 1) + 10 * ((nct + 1) - 1)];
  }

  if ((A_size[1] - 2) + 1 < A_size[1]) {
    e_data[((A_size[1] - 2) + 1) - 1] = b_A_data[(((A_size[1] - 2) + 1) - 1) +
      10 * (A_size[1] - 1)];
  }

  e_data[A_size[1] - 1] = 0.0;
  i_tmp = (uint8_T)A_size[1];
  for (c_q = 0; c_q < i_tmp; c_q = c_q + 1) {
    tmp = s_data[(c_q + 1) - 1];
    if (tmp != 0.0) {
      rt = fabs(tmp);
      s_data[(c_q + 1) - 1] = rt;
      if (c_q + 1 < p) {
        e_data[(c_q + 1) - 1] = e_data[(c_q + 1) - 1] / (tmp / rt);
      }
    }

    if (c_q + 1 < p) {
      tmp_1 = e_data[(c_q + 1) - 1];
      if (tmp_1 != 0.0) {
        rt = fabs(tmp_1);
        e_data[(c_q + 1) - 1] = rt;
        s_data[((c_q + 1) + 1) - 1] = s_data[((c_q + 1) + 1) - 1] * (rt / tmp_1);
      }
    }
  }

  iter = 0.0;
  snorm = 0.0;
  for (c_ii = 0; c_ii < i_tmp; c_ii = c_ii + 1) {
    snorm = fmax(snorm, fmax(fabs(s_data[(c_ii + 1) - 1]), fabs(e_data[(c_ii + 1)
      - 1])));
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
        ztest0 = fabs(e_data[d_ii - 1]);
        if (ztest0 <= 2.2204460492503131E-16 * (fabs(s_data[d_ii - 1]) + fabs
             (s_data[(d_ii + 1) - 1]))) {
          e_data[d_ii - 1] = 0.0;
          exitg1 = true;
        } else if ((ztest0 <= 1.0020841800044864E-292) || ((iter > 20.0) &&
                    (ztest0 <= 2.2204460492503131E-16 * snorm))) {
          e_data[d_ii - 1] = 0.0;
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
            test = fabs(e_data[e_ii - 1]);
          }

          if (e_ii > q + 1) {
            test = test + fabs(e_data[(e_ii - 1) - 1]);
          }

          ztest = fabs(s_data[e_ii - 1]);
          if ((ztest <= 2.2204460492503131E-16 * test) || (ztest <=
               1.0020841800044864E-292)) {
            s_data[e_ii - 1] = 0.0;
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
      f = e_data[(m - 1) - 1];
      e_data[(m - 1) - 1] = 0.0;
      for (c_k = q_tmp; c_k >= q; c_k = c_k - 1) {
        xrotg_zvvopXKT(&s_data[c_k - 1], &f, &cs, &sn);
        if (c_k > q) {
          f_tmp_0 = e_data[(c_k - 1) - 1];
          f = -sn * f_tmp_0;
          e_data[(c_k - 1) - 1] = f_tmp_0 * cs;
        }
      }
      break;

     case 2:
      f = e_data[(q - 1) - 1];
      e_data[(q - 1) - 1] = 0.0;
      for (d_k = q; d_k <= m; d_k = d_k + 1) {
        a__1 = f;
        xrotg_zvvopXKT(&s_data[d_k - 1], &a__1, &b_cs, &b_sn);
        f_tmp = e_data[d_k - 1];
        f = -b_sn * f_tmp;
        e_data[d_k - 1] = f_tmp * b_cs;
      }
      break;

     case 3:
      scale_tmp = s_data[m - 1];
      scale_tmp_0 = s_data[(m - 1) - 1];
      scale_tmp_1 = e_data[(m - 1) - 1];
      scale = fmax(fmax(fmax(fmax(fabs(scale_tmp), fabs(scale_tmp_0)), fabs
        (scale_tmp_1)), fabs(s_data[q - 1])), fabs(e_data[q - 1]));
      sm = scale_tmp / scale;
      smm1 = scale_tmp_0 / scale;
      emm1 = scale_tmp_1 / scale;
      sqds = s_data[q - 1] / scale;
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
      g = sqds * (e_data[q - 1] / scale);
      for (e_k = q; e_k <= q_tmp; e_k = e_k + 1) {
        b_f = f;
        a__2 = g;
        xrotg_zvvopXKT(&b_f, &a__2, &c_cs, &c_sn);
        if (e_k > q) {
          e_data[(e_k - 1) - 1] = b_f;
        }

        f_tmp_1 = e_data[e_k - 1];
        f_tmp_2 = s_data[e_k - 1];
        e_data[e_k - 1] = c_cs * f_tmp_1 - c_sn * f_tmp_2;
        a__3_tmp = s_data[(e_k + 1) - 1];
        a__3 = c_sn * a__3_tmp;
        s_data[(e_k + 1) - 1] = a__3_tmp * c_cs;
        s_data[e_k - 1] = c_cs * f_tmp_2 + c_sn * f_tmp_1;
        xrotg_zvvopXKT(&s_data[e_k - 1], &a__3, &d_cs, &d_sn);
        f = d_cs * e_data[e_k - 1] + d_sn * s_data[(e_k + 1) - 1];
        s_data[(e_k + 1) - 1] = -d_sn * e_data[e_k - 1] + d_cs * s_data[(e_k + 1)
          - 1];
        g_tmp = e_data[(e_k + 1) - 1];
        g = d_sn * g_tmp;
        e_data[(e_k + 1) - 1] = g_tmp * d_cs;
      }

      e_data[(m - 1) - 1] = f;
      iter = iter + 1.0;
      break;

     default:
      tmp_2 = s_data[q - 1];
      if (tmp_2 < 0.0) {
        s_data[q - 1] = -tmp_2;
      }

      qp1 = q + 1;
      exitg1 = false;
      while ((exitg1 == false) && (q < p)) {
        tmp_3 = s_data[q - 1];
        tmp_4 = s_data[qp1 - 1];
        if (tmp_3 < tmp_4) {
          s_data[q - 1] = tmp_4;
          s_data[qp1 - 1] = tmp_3;
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

  *U_size = A_size[1];
  memcpy(&U_data[0], &s_data[0], (uint32_T)i_tmp * sizeof(real_T));
  if (doscale) {
    xzlascl_6I4v9nni(cscale, anrm, A_size[1], U_data);
  }
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
