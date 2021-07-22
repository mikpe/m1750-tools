/*
 * ANSI Standard C: 7.5.5.2
 * 
 * #include <math.h>
 * double sqrt (double x);
 * 
 * Copyright (c) 1997, Chris Nettleton Software
 *
 * The contents of this file are based on the algorithms and 
 * coefficients given in "Software Manual for the Elementry Functions" 
 * by William J. Cody, Jr. and William Waite, Prentice_Hall, 1980. 
 *
 * $Log: sqrt.c,v $
 * Revision 1.1  1997/03/17 17:14:48  nettleto
 * Initial revision
 *
 */

#include <math.h>

#include <errno.h>

double
sqrt (double x)
{
  int    m, n;
  double f, y;
  double result;
  const double sqrt_c1 = 0.41731;
  const double sqrt_c2 = 0.59016;
  const double sqrt_c3 = 0.70710678118654752440;

  if ( x <= 0.0 )
    {
      if ( x < 0.0 )
        errno = EDOM;

      result = 0.0;
    }
  else if ( x == 1.0 )
    {
      result = 1.0;     /* To get exact SQRT(1.0) */
    }
  else
    {
      f = frexp (x, &n);
      y = sqrt_c1 + sqrt_c2 * f;

      if ( n & 1 )
        {
          y = y * sqrt_c3;
          f = f * 0.5;
          n = n + 1;
        }

      m = n / 2;
/*
 *     Since always looping to 3, unroll the loop
 */
      y = (y + f / y) * 0.5;
      y = (y + f / y) * 0.5;
      y = (y + f / y) * 0.5;
      result = ldexp (y, m);
    }
  return result;
}
/*sqrt*/


