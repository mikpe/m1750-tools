/*
 * ANSI Standard C: 7.5.2.6
 * 
 * #include <math.h>
 * double sin (double x);
 * 
 * Copyright (c) 1997, Chris Nettleton Software
 *
 * The contents of this file are based on the algorithms and 
 * coefficients given in "Software Manual for the Elementry Functions" 
 * by William J. Cody, Jr. and William Waite, Prentice_Hall, 1980. 
 *
 * $Log: sin.c,v $
 * Revision 1.2  1997/08/04 11:00:12  nettleto
 * Tuned polynomial for 1750, and reduced absolute error
 * to +/- 2 epsilons.
 *
 * Revision 1.1  1997/03/17 17:12:53  nettleto
 * Initial revision
 *
 */

#include <math.h>

#include <limits.h>
#include <float.h>

static inline double
sin_r (double g)
{
  const double r1 = - 0.16666666666666665052e+0;
  const double r2 = 0.83333333333331650314e-2;
  const double r3 = - 0.19841269841201840457e-3;
  const double r4 = 0.27557319210152756119e-5;
  const double r5 = - 0.25052106798274584544e-7;
  const double r6 = 0.16058936490371589114e-9;
  const double r7 = - 0.80000000000000000000e-12;

  return ((((((r7 * g + r6) * g + r5) * g + r4) *
    g + r3) * g + r2) * g + r1) * g;
}
/*sin_r*/

double
sin (double x)
{
  double sgn, y;
  long   n;
  double xn;
  double f, g, x1, x2;
  double result;
  const double c1          = 3.1416015625;
  const double c2          = - 0.89089102067615373566e-5;
  const double one_over_pi = 0.31830988618379067154;

  if ( x < 0.0 )
    {
      sgn = - 1.0;
      y   = - x;
    }
  else
    {
      sgn = 1.0;
      y   = x;
    }

  if ( y > (double) LONG_MAX )
    return 0.0;

  xn = floor (y * one_over_pi + 0.5);
  n  = (long) xn;

  if ( n & 1 )
    sgn = - sgn;

  x2 = modf (fabs (x), &x1);
  f  = ((x1 - xn * c1) + x2) - xn * c2;
  g  = f * f;

  if ( g < DBL_EPSILON )
    result = f;
  else
    result = f + f * sin_r (g);

  return (sgn * result);
}
/*sin*/


