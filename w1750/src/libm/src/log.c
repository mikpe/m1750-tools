/*
 * ANSI Standard C: 7.5.4.4
 * 
 * #include <math.h>
 * double log (double x);
 * 
 * Copyright (c) 1997, Chris Nettleton Software
 *
 * The contents of this file are based on the algorithms and 
 * coefficients given in "Software Manual for the Elementry Functions" 
 * by William J. Cody, Jr. and William Waite, Prentice_Hall, 1980. 
 *
 * $Log: log.c,v $
 * Revision 1.1  1997/03/17 17:15:30  nettleto
 * Initial revision
 *
 */

#include <math.h>

#include <errno.h>

static double
log_r (double z)
{
  double w = z * z;
  const double a0 = - 0.64124943423745581147e+2;
  const double a1 = 0.16383943563021534222e+2;
  const double a2 = - 0.78956112887491257267e+0;
  const double b0 = - 0.76949932108494879777e+3;
  const double b1 = 0.31203222091924532844e+3;
  const double b2 = - 0.35667977739034646171e+2;

  return
    z + z * w * (a0 + (a1 + a2 * w) * w) /
    (b0 + (b1 + (b2 + w) * w) * w);
}
/*log_r*/

double
log (double x)
{
  double result;
  int    n;
  double xn;
  double f;
  double z, zden, znum;
  const double c0 = 0.70710678118654752440;
  const double c1 = 0.693359375;
  const double c2 = - 2.12194440054690582768e-4;

  if ( x <= 0.0 )
    {
      errno = ( x < 0.0 ) ? EDOM : ERANGE;
      result = - HUGE_VAL;
    }
  else
    {
      f = frexp (x, &n);
      znum = f - 0.5;

      if ( f > c0 )
        {
          znum = znum - 0.5;
          zden = f * 0.5 + 0.5;
        }
      else
        {
          n    = n - 1;
          zden = znum * 0.5 + 0.5;
        }

      z = znum / zden;

      if ( n == 0 )
        {
          result = log_r (z);
        }
      else
        {
          xn     = (double) (n);
          result = (xn * c2 + log_r (z)) + xn * c1;
        }
    }
  return result;
}
/*log*/


