/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: svd_NJw3JjRP.c
 *
 * Code generated for Simulink model 'RMT_FDM_DLL_FrameWork_FCS_RT'.
 *
 * Model version                  : 11.34
 * Simulink Coder version         : 24.2 (R2024b) 21-Jun-2024
 * C/C++ source code generated on : Thu Dec  4 22:28:01 2025
 */

#include "rtwtypes.h"
#include "svd_NJw3JjRP.h"
#include <string.h>
#include "xzlangeM_LAOIK0zM.h"
#include "xzlascl_ze48YLp0.h"
#include "xnrm2_Fo3hhCrm.h"
#include <math.h>
#include "xnrm2_Kp9rP65Y.h"
#include "xdotc_HctHpm1R.h"
#include "xaxpy_0xav9hoQ.h"
#include "xzlascl_maz9QAwP.h"
#include "xaxpy_yDaHKA4W.h"
#include "xaxpy_Ch3dBsmQ.h"
#include "xrotg_zvvopXKT.h"
#include "xrot_02izWG6a.h"
#include "xswap_Si10HpCi.h"

/* Function for MATLAB Function: '<S19>/Pseudoinverse' */
void svd_NJw3JjRP(const real_T A[16], real_T U[16], real_T s[4], real_T V[16])
{
  real_T Vf[16];
  real_T b_A[16];
  real_T b_s[4];
  real_T e[4];
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
  real_T r;
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
  int32_T U_tmp;
  int32_T V_tmp;
  int32_T b_i;
  int32_T b_ix0;
  int32_T b_j;
  int32_T b_jj;
  int32_T b_k;
  int32_T b_q;
  int32_T c_ii;
  int32_T c_ix0;
  int32_T c_jj;
  int32_T c_k;
  int32_T c_q;
  int32_T d_ii;
  int32_T d_jj;
  int32_T d_k;
  int32_T d_q;
  int32_T e_ii;
  int32_T e_jj;
  int32_T e_k;
  int32_T e_q;
  int32_T f_ii;
  int32_T g_k;
  int32_T h_ii;
  int32_T h_k;
  int32_T i;
  int32_T i_0;
  int32_T i_1;
  int32_T i_ii;
  int32_T i_k;
  int32_T ix0;
  int32_T j_ii;
  int32_T j_k;
  int32_T jj;
  int32_T k_ii;
  int32_T k_k;
  int32_T l;
  int32_T l_ii;
  int32_T l_k;
  int32_T m;
  int32_T m_k;
  int32_T n;
  int32_T o;
  int32_T p;
  int32_T q;
  int32_T q_tmp;
  int32_T qjj;
  int32_T qp1;
  int32_T qp1_tmp;
  int32_T qp1jj;
  int32_T qp1q;
  int32_T qq;
  int32_T qq_tmp;
  int32_T qq_tmp_0;
  int32_T qs;
  int32_T t;
  int32_T tmp_5;
  int32_T tmp_6;
  int32_T tmp_7;
  int32_T tmp_8;
  int32_T u;
  int32_T v;
  boolean_T apply_transform;
  boolean_T doscale;
  boolean_T exitg1;
  memcpy(&b_A[0], &A[0], 16U * sizeof(real_T));
  for (i = 0; i < 4; i = i + 1) {
    b_s[i] = 0.0;
  }

  for (i_0 = 0; i_0 < 4; i_0 = i_0 + 1) {
    e[i_0] = 0.0;
  }

  for (i_1 = 0; i_1 < 4; i_1 = i_1 + 1) {
    work[i_1] = 0.0;
  }

  memset(&U[0], 0, 16U * sizeof(real_T));
  memset(&Vf[0], 0, 16U * sizeof(real_T));
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
        b_s[(b_q + 1) - 1] = -nrm;
      } else {
        b_s[(b_q + 1) - 1] = nrm;
      }

      tmp = b_s[(b_q + 1) - 1];
      if (fabs(tmp) >= 1.0020841800044864E-292) {
        b_a = 1.0 / tmp;
        p = qq + (((4 - (b_q + 1)) + 1) - 1);
        for (j_k = qq; j_k <= p; j_k = j_k + 1) {
          b_A[j_k - 1] = b_a * b_A[j_k - 1];
        }
      } else {
        l = qq + (((4 - (b_q + 1)) + 1) - 1);
        for (g_k = qq; g_k <= l; g_k = g_k + 1) {
          b_A[g_k - 1] = b_A[g_k - 1] / tmp;
        }
      }

      b_A[qq - 1] = b_A[qq - 1] + 1.0;
      b_s[(b_q + 1) - 1] = -tmp;
    } else {
      b_s[(b_q + 1) - 1] = 0.0;
    }

    for (jj = qp1_tmp; jj < 5; jj = jj + 1) {
      qjj = (b_q + 1) + ((jj - 1) << 2);
      if (apply_transform) {
        xaxpy_0xav9hoQ((4 - (b_q + 1)) + 1, -(xdotc_HctHpm1R((4 - (b_q + 1)) + 1,
          b_A, qq, b_A, qjj) / b_A[((b_q + 1) - 1) + qq_tmp]), qq, b_A, qjj);
      }

      e[jj - 1] = b_A[qjj - 1];
    }

    memcpy(&U[((b_q + 1) + qq_tmp) + -1], &b_A[((b_q + 1) + qq_tmp) + -1],
           (uint32_T)((qq_tmp - ((b_q + 1) + qq_tmp)) + 5) * sizeof(real_T));
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
          u = ((b_q + 1) + 1) + ((4 - (b_q + 1)) - 1);
          for (l_k = qp1_tmp; l_k <= u; l_k = l_k + 1) {
            e[l_k - 1] = c_a * e[l_k - 1];
          }
        } else {
          n = ((b_q + 1) + 1) + ((4 - (b_q + 1)) - 1);
          for (h_k = qp1_tmp; h_k <= n; h_k = h_k + 1) {
            e[h_k - 1] = e[h_k - 1] / a_tmp;
          }
        }

        e[((b_q + 1) + 1) - 1] = e[((b_q + 1) + 1) - 1] + 1.0;
        e[(b_q + 1) - 1] = -e[(b_q + 1) - 1];
        for (c_ii = qp1_tmp; c_ii < 5; c_ii = c_ii + 1) {
          work[c_ii - 1] = 0.0;
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

      for (d_ii = qp1_tmp; d_ii < 5; d_ii = d_ii + 1) {
        Vf[(d_ii - 1) + qq_tmp] = e[d_ii - 1];
      }
    }
  }

  m = 4;
  b_s[3] = b_A[15];
  e[2] = b_A[14];
  e[3] = 0.0;
  for (e_ii = 0; e_ii < 4; e_ii = e_ii + 1) {
    U[12 + ((e_ii + 1) - 1)] = 0.0;
  }

  U[15] = 1.0;
  for (c_q = 3; c_q >= 1; c_q = c_q - 1) {
    qp1 = c_q + 1;
    qq_tmp_0 = (c_q - 1) << 2;
    qq = c_q + qq_tmp_0;
    if (b_s[c_q - 1] != 0.0) {
      for (d_jj = qp1; d_jj < 5; d_jj = d_jj + 1) {
        qjj = c_q + ((d_jj - 1) << 2);
        xaxpy_0xav9hoQ((4 - c_q) + 1, -(xdotc_HctHpm1R((4 - c_q) + 1, U, qq, U,
          qjj) / U[qq - 1]), qq, U, qjj);
      }

      for (f_ii = c_q; f_ii < 5; f_ii = f_ii + 1) {
        U_tmp = (f_ii - 1) + qq_tmp_0;
        U[U_tmp] = -U[U_tmp];
      }

      U[qq - 1] = U[qq - 1] + 1.0;
      if (0 <= (uint8_T)(c_q - 1) - 1) {
        memset(&U[qq_tmp_0], 0, (uint32_T)(((uint8_T)(c_q - 1) + qq_tmp_0) -
                qq_tmp_0) * sizeof(real_T));
      }
    } else {
      for (h_ii = 0; h_ii < 4; h_ii = h_ii + 1) {
        U[((h_ii + 1) - 1) + qq_tmp_0] = 0.0;
      }

      U[qq - 1] = 1.0;
    }
  }

  for (d_q = 4; d_q >= 1; d_q = d_q - 1) {
    if ((d_q <= 2) && (e[d_q - 1] != 0.0)) {
      qp1 = d_q + 1;
      qp1q = (d_q + 1) + ((d_q - 1) << 2);
      for (e_jj = qp1; e_jj < 5; e_jj = e_jj + 1) {
        qp1jj = (d_q + 1) + ((e_jj - 1) << 2);
        xaxpy_0xav9hoQ(4 - d_q, -(xdotc_HctHpm1R(4 - d_q, Vf, qp1q, Vf, qp1jj) /
          Vf[qp1q - 1]), qp1q, Vf, qp1jj);
      }
    }

    for (i_ii = 0; i_ii < 4; i_ii = i_ii + 1) {
      Vf[((i_ii + 1) - 1) + ((d_q - 1) << 2)] = 0.0;
    }

    Vf[(d_q - 1) + ((d_q - 1) << 2)] = 1.0;
  }

  for (e_q = 0; e_q < 4; e_q = e_q + 1) {
    tmp_0 = b_s[(e_q + 1) - 1];
    if (tmp_0 != 0.0) {
      rt = fabs(tmp_0);
      r = tmp_0 / rt;
      b_s[(e_q + 1) - 1] = rt;
      if (e_q + 1 < 4) {
        e[(e_q + 1) - 1] = e[(e_q + 1) - 1] / r;
      }

      ix0 = (((e_q + 1) - 1) << 2) + 1;
      o = ix0 + 3;
      for (i_k = ix0; i_k <= o; i_k = i_k + 1) {
        U[i_k - 1] = r * U[i_k - 1];
      }
    }

    if (e_q + 1 < 4) {
      tmp_1 = e[(e_q + 1) - 1];
      if (tmp_1 != 0.0) {
        rt = fabs(tmp_1);
        r = rt / tmp_1;
        e[(e_q + 1) - 1] = rt;
        b_s[((e_q + 1) + 1) - 1] = b_s[((e_q + 1) + 1) - 1] * r;
        b_ix0 = ((e_q + 1) << 2) + 1;
        t = b_ix0 + 3;
        for (k_k = b_ix0; k_k <= t; k_k = k_k + 1) {
          Vf[k_k - 1] = r * Vf[k_k - 1];
        }
      }
    }
  }

  iter = 0.0;
  snorm = 0.0;
  for (j_ii = 0; j_ii < 4; j_ii = j_ii + 1) {
    snorm = fmax(snorm, fmax(fabs(b_s[(j_ii + 1) - 1]), fabs(e[(j_ii + 1) - 1])));
  }

  while ((m > 0) && (!(iter >= 75.0))) {
    q_tmp = m - 1;
    q = m - 1;
    k_ii = m - 1;
    exitg1 = false;
    while ((exitg1 == false) && (k_ii > -1)) {
      q = k_ii;
      if (k_ii == 0) {
        exitg1 = true;
      } else {
        ztest0 = fabs(e[k_ii - 1]);
        if (ztest0 <= 2.2204460492503131E-16 * (fabs(b_s[k_ii - 1]) + fabs(b_s
              [(k_ii + 1) - 1]))) {
          e[k_ii - 1] = 0.0;
          exitg1 = true;
        } else if ((ztest0 <= 1.0020841800044864E-292) || ((iter > 20.0) &&
                    (ztest0 <= 2.2204460492503131E-16 * snorm))) {
          e[k_ii - 1] = 0.0;
          exitg1 = true;
        } else {
          k_ii = k_ii + -1;
        }
      }
    }

    if (q == m - 1) {
      kase = 4.0;
    } else {
      qs = m;
      l_ii = m;
      exitg1 = false;
      while ((exitg1 == false) && (l_ii >= q)) {
        qs = l_ii;
        if (l_ii == q) {
          exitg1 = true;
        } else {
          test = 0.0;
          if (l_ii < m) {
            test = fabs(e[l_ii - 1]);
          }

          if (l_ii > q + 1) {
            test = test + fabs(e[(l_ii - 1) - 1]);
          }

          ztest = fabs(b_s[l_ii - 1]);
          if ((ztest <= 2.2204460492503131E-16 * test) || (ztest <=
               1.0020841800044864E-292)) {
            b_s[l_ii - 1] = 0.0;
            exitg1 = true;
          } else {
            l_ii = l_ii + -1;
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
        xrotg_zvvopXKT(&b_s[b_k - 1], &f, &cs, &sn);
        if (b_k > q) {
          f_tmp_0 = e[(b_k - 1) - 1];
          f = -sn * f_tmp_0;
          e[(b_k - 1) - 1] = f_tmp_0 * cs;
        }

        xrot_02izWG6a(Vf, ((b_k - 1) << 2) + 1, ((m - 1) << 2) + 1, cs, sn);
      }
      break;

     case 2:
      f = e[(q - 1) - 1];
      e[(q - 1) - 1] = 0.0;
      for (c_k = q; c_k <= m; c_k = c_k + 1) {
        a__1 = f;
        xrotg_zvvopXKT(&b_s[c_k - 1], &a__1, &b_cs, &b_sn);
        f_tmp = e[c_k - 1];
        f = -b_sn * f_tmp;
        e[c_k - 1] = f_tmp * b_cs;
        xrot_02izWG6a(U, ((c_k - 1) << 2) + 1, (((q - 1) - 1) << 2) + 1, b_cs,
                      b_sn);
      }
      break;

     case 3:
      scale_tmp = b_s[m - 1];
      scale_tmp_0 = b_s[(m - 1) - 1];
      scale_tmp_1 = e[(m - 1) - 1];
      scale = fmax(fmax(fmax(fmax(fabs(scale_tmp), fabs(scale_tmp_0)), fabs
        (scale_tmp_1)), fabs(b_s[q - 1])), fabs(e[q - 1]));
      sm = scale_tmp / scale;
      smm1 = scale_tmp_0 / scale;
      emm1 = scale_tmp_1 / scale;
      sqds = b_s[q - 1] / scale;
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
        f_tmp_2 = b_s[d_k - 1];
        e[d_k - 1] = c_cs * f_tmp_1 - c_sn * f_tmp_2;
        a__3_tmp = b_s[(d_k + 1) - 1];
        a__3 = c_sn * a__3_tmp;
        b_s[(d_k + 1) - 1] = a__3_tmp * c_cs;
        tmp_7 = ((d_k - 1) << 2) + 1;
        tmp_8 = (d_k << 2) + 1;
        xrot_02izWG6a(Vf, tmp_7, tmp_8, c_cs, c_sn);
        b_s[d_k - 1] = c_cs * f_tmp_2 + c_sn * f_tmp_1;
        xrotg_zvvopXKT(&b_s[d_k - 1], &a__3, &d_cs, &d_sn);
        f = d_cs * e[d_k - 1] + d_sn * b_s[(d_k + 1) - 1];
        b_s[(d_k + 1) - 1] = -d_sn * e[d_k - 1] + d_cs * b_s[(d_k + 1) - 1];
        g_tmp = e[(d_k + 1) - 1];
        g = d_sn * g_tmp;
        e[(d_k + 1) - 1] = g_tmp * d_cs;
        xrot_02izWG6a(U, tmp_7, tmp_8, d_cs, d_sn);
      }

      e[(m - 1) - 1] = f;
      iter = iter + 1.0;
      break;

     default:
      tmp_2 = b_s[q - 1];
      if (tmp_2 < 0.0) {
        b_s[q - 1] = -tmp_2;
        c_ix0 = ((q - 1) << 2) + 1;
        v = c_ix0 + 3;
        for (m_k = c_ix0; m_k <= v; m_k = m_k + 1) {
          Vf[m_k - 1] = -Vf[m_k - 1];
        }
      }

      qp1 = q + 1;
      exitg1 = false;
      while ((exitg1 == false) && (q < 4)) {
        tmp_3 = b_s[q - 1];
        tmp_4 = b_s[qp1 - 1];
        if (tmp_3 < tmp_4) {
          b_s[q - 1] = tmp_4;
          b_s[qp1 - 1] = tmp_3;
          tmp_5 = ((q - 1) << 2) + 1;
          tmp_6 = (q << 2) + 1;
          xswap_Si10HpCi(Vf, tmp_5, tmp_6);
          xswap_Si10HpCi(U, tmp_5, tmp_6);
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
    s[(e_k + 1) - 1] = b_s[(e_k + 1) - 1];
  }

  if (doscale) {
    xzlascl_maz9QAwP(cscale, anrm, s);
  }

  for (b_j = 0; b_j < 4; b_j = b_j + 1) {
    for (b_i = 0; b_i < 4; b_i = b_i + 1) {
      V_tmp = ((b_i + 1) - 1) + (((b_j + 1) - 1) << 2);
      V[V_tmp] = Vf[V_tmp];
    }
  }
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
