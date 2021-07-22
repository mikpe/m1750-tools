/*
 * ANSI Standard C: 7.5.5.1
 * 
 * #include <math.h>
 * double pow (double x, double y);
 * 
 * Copyright (c) 1997, Chris Nettleton Software
 *
 * The contents of this file are based on the algorithms and 
 * coefficients given in "Software Manual for the Elementry Functions" 
 * by William J. Cody, Jr. and William Waite, Prentice_Hall, 1980. 
 *
 * $Log: pow.c,v $
 * Revision 1.1  1997/03/17 17:14:28  nettleto
 * Initial revision
 *
 */

#include <math.h>

#include <errno.h>
#include <float.h>

double
pow (double x, double y)
{
  int    m;
  double g;
  int    p, iw1, i;
  double z, v, r, u1, u2, w1, w2, w3, y1, y2;
  double w, result;
  const double k    = 0.44269504088896340736;
  const int ibigx   = (DBL_MAX_EXP << 4) - 1;
  const int ismallx = ((DBL_MIN_EXP-1) << 4) + 1;
  #define reduce(v) floor (16.0 * (v) + 0.5) * 0.0625

  if ( x <= 0.0 )
    {
      if ( x < 0.0 )
        {
          errno = EDOM;
          result = 0.0;
        }
      else
        {
          if ( y <= 0.0 )
            {
              if ( y == 0.0 )
                {
                  result = 1.0;
                }
              else
                {
                  errno = EDOM;
                  result = HUGE_VAL;
                }
            }
          else
            {
              result = 0.0;
            }
        }
    }
  else
    {
      g = frexp (x, &m);
        {
          static double a1 [18] =
            {
              0.0,
              1.0,
              0.95760328069857358901,
              0.91700404320467121533,
              0.87812608018664972676,
              0.84089641525371450204,
              0.80524516597462714174,
              0.77110541270397037206,
              0.73841307296974956209,
              0.70710678118654746172,
              0.67712777346844632564,
              0.64841977732550482028,
              0.62092890603674200101,
              0.59460355750136051345,
              0.56939431737834578229,
              0.54525386633262873382,
              0.52213689121370687740,
              0.5
            };
          static double a2 [9] =
            {
              0.0,
              0.000000000000000057922572181599855684,
              0.000000000000000014800703477186887541,
              0.000000000000000012353596284702224819,
              0.000000000000000093602329678172515612,
              0.000000000000000038504741898901862865,
              0.000000000000000023290137959059464613,
              0.000000000000000044564063380522338321,
              0.000000000000000042759448527536717653
            };

          p = 1;
          if ( g <= a1 [9] ) p = 9;
          if ( g <= a1 [p + 4] ) p += 4;
          if ( g <= a1 [p + 2] ) p += 2;
          z = ((g - a1 [p + 1]) - a2 [(p + 1) / 2]) /
            (g + a1 [p + 1]);
        }
      z = z + z;
      v = z * z;
        {
          const double p1 = 0.83333333333333211405e-1;
          const double p2 = 0.12500000000503799174e-1;
          const double p3 = 0.22321421285924258967e-2;
          const double p4 = 0.43445775672163119635e-3;

          r = (((p4 * v + p3) * v + p2) * v + p1) * v * z;
        }
      r   = r + k * r;
      u2  = (r + z * k) + z;
      u1  = (double) (m * 16 - p) * 0.0625;
      y1  = reduce (y);
      y2  = y - y1;
      w   = u2 * y + u1 * y2;
      w1  = reduce (w);
      w2  = w - w1;
      w   = w1 + u1 * y1;
      w1  = reduce (w);
      w2  = w2 + (w - w1);
      w3  = reduce (w2);
      iw1 = (int) (16.0 * (w1 + w3));
      w2  = w2 - w3;

      if ( w > (double) (ibigx) )
        {
          errno = ERANGE;
          result = HUGE_VAL;
        }
      else if ( w < (double) (ismallx) )
        {
          result = 0.0;
        }
      else
        {
          if ( w2 > 0.0 )
            {
              w2  = w2 - 0.0625;
              iw1 = iw1 + 1;
            }

          i = ( iw1 < 0 ) ? 0 : 1;
          m = i + iw1 / 16;
          p = 16 * m - iw1;
            {
              const double q1 = 0.693147180556341;
              const double q2 = 0.240226506144710;
              const double q3 = 0.555040488130765e-1;
              const double q4 = 0.961620659583789e-2;
              const double q5 = 0.130525515942810e-2;

              z = ((((q5 * w2 + q4) * w2 + q3) * w2 + q2)
                 * w2 + q1) * w2;
            }
            {
              static double a1 [18] =
                {
                  0.0,
                  1.0,
                  0.95760328069857358901,
                  0.91700404320467121533,
                  0.87812608018664972676,
                  0.84089641525371450204,
                  0.80524516597462714174,
                  0.77110541270397037206,
                  0.73841307296974956209,
                  0.70710678118654746172,
                  0.67712777346844632564,
                  0.64841977732550482028,
                  0.62092890603674200101,
                  0.59460355750136051345,
                  0.56939431737834578229,
                  0.54525386633262873382,
                  0.52213689121370687740,
                  0.5
                };

              z = a1 [p + 1] + (a1 [p + 1] * z);
            }
          result = ldexp (z, m);
        }
    }
  return result;
}
/*pow*/


