/*
 * ANSI Standard C: 7.5.2.3
 * 
 * #include <math.h>
 * double atan (double x);
 * 
 * Copyright (c) 1997, Chris Nettleton Software
 *
 * The contents of this file are based on the algorithms and 
 * coefficients given in "Software Manual for the Elementry Functions" 
 * by William J. Cody, Jr. and William Waite, Prentice_Hall, 1980. 
 *
 * $Log: atan.c,v $
 * Revision 1.1  1997/03/17 17:12:09  nettleto
 * Initial revision
 *
 */

#include <math.h>

#include <float.h>

static inline double
atan_r (double g)
{
  const double p0 = - 0.13688768894191926929e+2;
  const double p1 = - 0.20505855195861651981e+2;
  const double p2 = - 0.84946240351320683534e+1;
  const double p3 = - 0.83758299368150059274e+0;
  const double q0 = 0.41066306682575781263e+2;
  const double q1 = 0.86157349597130242515e+2;
  const double q2 = 0.59578436142597344465e+2;
  const double q3 = 0.15024001160028576121e+2;

  return ((((p3 * g + p2) * g + p1) * g + p0) * g) /
    ((((g + q3) * g + q2) * g + q1) * g + q0);
}
/*atan_r*/

double
atan (double x)
{
  double f, g;
  int    n;
  double result;
  const double sqrt_3           = 1.73205080756887729353;
  const double sqrt_3_minus_1   = 0.73205080756887729353;
  const double two_minus_sqrt_3 = 0.26794919243112270647;
  const double pi_over_two      = 1.57079632679489661923;
  const double pi_over_three    = 1.04719755119659774615;
  const double pi_over_six      = 0.52359877559829887308;

  f = fabs (x);

  if ( f > 1.0 )
    {
      f = 1.0 / f;
      n = 2;
    }
  else
    {
      n = 0;
    }

  if ( f > two_minus_sqrt_3 )
    {
      f = (((sqrt_3_minus_1 * f - 0.5) - 0.5) + f) / (sqrt_3 + f);
      n = n + 1;
    }

  g = f * f;

  if ( g < DBL_EPSILON )
    result = f;
  else
    result = f + f * atan_r (g);

  if ( n > 1 )
    result = - result;

  switch ( n )
    {
      case 0:
        result = result;
        break;
      case 1:
        result = pi_over_six + result;
        break;
      case 2:
        result = pi_over_two + result;
        break;
      case 3:
        result = pi_over_three + result;
        break;
    }

  if ( x < 0.0 )
    result = - result;

  return result;
}
/*atan*/


