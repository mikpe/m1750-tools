/*
 * ANSI Standard C: 7.5.2.2
 * 
 * #include <math.h>
 * double asin (double x);
 * 
 * Copyright (c) 1997, Chris Nettleton Software
 *
 * The contents of this file are based on the algorithms and 
 * coefficients given in "Software Manual for the Elementry Functions" 
 * by William J. Cody, Jr. and William Waite, Prentice_Hall, 1980. 
 *
 * $Log: asin.c,v $
 * Revision 1.1  1997/03/17 17:10:53  nettleto
 * Initial revision
 *
 */

#include <math.h>

#include <errno.h>
#include <float.h>

static double
asin_r (double g)
{
  const double p1 = - 0.27368494524164255994e+2;
  const double p2 = 0.57208227877891731407e+2;
  const double p3 = - 0.39688862997504877339e+2;
  const double p4 = 0.10152522233806463645e+2;
  const double p5 = - 0.69674573447350646411e+0;
  const double q0 = - 0.16421096714498560795e+3;
  const double q1 = 0.41714430248260412556e+3;
  const double q2 = - 0.38186303361750149284e+3;
  const double q3 = 0.15095270841030604719e+3;
  const double q4 = - 0.23823859153670238830e+2;

  return (((((p5 * g + p4) * g + p3) * g + p2) * g + p1) * g) /
    (((((g + q4) * g + q3) * g + q2) * g + q1) * g + q0);
}
/*asin_r*/

double
asin (double x)
{
  double g, y;
  double result;
  const double pi_over_four = 0.78539816339744830962;

  y = fabs (x);

  if ( y > 0.5 )
    {
      if ( y > 1.0 )
        {
          errno = EDOM;
          y = 1.0;
        }

      g      = ((0.5 - y) + 0.5) / 2.0;
      y      = - 2.0 * sqrt (g);
      result = y + y * asin_r (g);
      result = (pi_over_four + result) + pi_over_four;
    }
  else
    {
      g = y * y;

      if ( g < DBL_EPSILON )
        result = y;
      else
        result = y + y * asin_r (g);
    }

  if ( x < 0.0 )
    result = - result;

  return result;
}
/*asin*/


