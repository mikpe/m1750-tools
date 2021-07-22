/*
 * ANSI Standard C: 7.5.4.1
 * 
 * #include <math.h>
 * double exp (double x);
 * 
 * Copyright (c) 1997, Chris Nettleton Software
 *
 * The contents of this file are based on the algorithms and 
 * coefficients given in "Software Manual for the Elementry Functions" 
 * by William J. Cody, Jr. and William Waite, Prentice_Hall, 1980. 
 *
 * $Log: exp.c,v $
 * Revision 1.1  1997/03/17 17:14:15  nettleto
 * Initial revision
 *
 */

#include <math.h>

#include <errno.h>
#include <float.h>

static inline double
exp_r (double g)
{
  double z, gp, q;
  const double p0 = 0.249999999999999993e+0;
  const double p1 = 0.694360001511792852e-2;
  const double p2 = 0.165203300268279130e-4;
  const double q0 = 0.5;
  const double q1 = 0.555538666969001188e-1;
  const double q2 = 0.495862884905441294e-3;

  z = g * g;
  gp = (((p2 * z + p1) * z) + p0) * g;
  q  = ((q2 * z + q1) * z) + q0;
  return 0.5 + (gp / (q - gp));
}
/*exp_r*/

double
exp (double x)
{
  double result;
  int    n;
  double xn, x1, x2;
  double f, g;
  const double one_over_log_2 = 1.4426950408889634074;
  const double c1             = 0.693359375;
  const double c2             = - 2.1219444005469058277e-4;
  const double exp_large      = (double) DBL_MAX_EXP * 0.69314718;
  const double exp_small      = (double) (DBL_MIN_EXP-1) * 0.69314718;

  if ( x > exp_large )
    {
      errno = ERANGE;
      result = HUGE_VAL;
    }
  else if ( x < exp_small )
    {
      result = 0.0;
    }
  else if ( fabs (x) < DBL_EPSILON )
    {
      result = 1.0;
    }
  else
    {
      xn = floor (x * one_over_log_2 + 0.5);
      n  = (int) xn;
      x2 = modf (x, &x1);
      g  = ((x1 - xn * c1) + x2) - xn * c2;
      n  = n + 1;
      f  = exp_r (g);
      result = ldexp (f, n);
    }
  return result;
}
/*exp*/


