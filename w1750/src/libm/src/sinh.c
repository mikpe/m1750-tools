/*
 * ANSI Standard C: 7.5.3.2
 * 
 * #include <math.h>
 * double sinh (double x);
 * 
 * Copyright (c) 1997, Chris Nettleton Software
 *
 * The contents of this file are based on the algorithms and 
 * coefficients given in "Software Manual for the Elementry Functions" 
 * by William J. Cody, Jr. and William Waite, Prentice_Hall, 1980. 
 *
 * $Log: sinh.c,v $
 * Revision 1.1  1997/03/17 17:13:27  nettleto
 * Initial revision
 *
 */

#include <math.h>

#include <errno.h>
#include <float.h>

static inline double
sinh_r (double g)
{
  const double p0 = 0.10622288837151e4;
  const double p1 = 0.31359756456058e2;
  const double p2 = 0.34364140358506;
  const double q0 = 0.63733733021822e4;
  const double q1 = - 0.13051012509199e3;

  return (((p2 * g + p1) * g + p0) * g) / ((g + q1) * g + q0);
}
/*sinh_r*/

double
sinh (double x)
{
  double g, w, y, z;
  double result;
  const double ybar             = (double) DBL_MAX_EXP * 0.69314718;
  const double ln_v             = 0.6931610107421875;
  const double v_over_2_minus_1 = 0.13830277879601902638e-4;
  const double wmax             = ybar - ln_v + 0.69;

  y = fabs (x);

  if ( y <= 1.0 )
    {
      g = x * x;

      if ( g < DBL_EPSILON )
        result = x;
      else
        result = x + x * sinh_r (g);
    }
  else
    {
      if ( y <= ybar )
        {
          z      = exp (y);
          result = (z - 1.0 / z) / 2.0;
        }
      else
        {
          w = y - ln_v;

          if ( w > wmax )
            {
              errno = ERANGE;
              return ( x < 0.0 ) ? - HUGE_VAL : HUGE_VAL;
            }

          z      = exp (w);
          result = z + v_over_2_minus_1 * z;
        }

      if ( x < 0.0 )
        result = - result;
    }
  return result;
}
/*sinh*/

