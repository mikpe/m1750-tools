/*
 * ANSI Standard C: 7.5.3.1
 * 
 * #include <math.h>
 * double cosh (double x);
 * 
 * Copyright (c) 1997, Chris Nettleton Software
 *
 * The contents of this file are based on the algorithms and 
 * coefficients given in "Software Manual for the Elementry Functions" 
 * by William J. Cody, Jr. and William Waite, Prentice_Hall, 1980. 
 *
 * $Log: cosh.c,v $
 * Revision 1.1  1997/03/17 17:13:40  nettleto
 * Initial revision
 *
 */

#include <math.h>

#include <errno.h>
#include <float.h>

double
cosh (double x)
{
  double w, y, z;
  double result;
  const double ybar             = (double) DBL_MAX_EXP * 0.69314718;
  const double ln_v             = 0.6931610107421875;
  const double v_over_2_minus_1 = 0.13830277879601902638e-4;
  const double wmax             = ybar - ln_v + 0.69;

  y = fabs (x);

  if ( y <= ybar )
    {
      z      = exp (y);
      result = (z + 1.0 / z) / 2.0;
    }
  else
    {
      w = y - ln_v;

      if ( w > wmax )
        {
          errno = ERANGE;
          return HUGE_VAL;
        }

      z      = exp (w);
      result = z + v_over_2_minus_1 * z;
    }

  return result;
}
/*cosh*/


