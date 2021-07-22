/*
 * ANSI Standard C: 7.5.3.3
 * 
 * #include <math.h>
 * double tanh (double x);
 * 
 * Copyright (c) 1997, Chris Nettleton Software
 *
 * The contents of this file are based on the algorithms and 
 * coefficients given in "Software Manual for the Elementry Functions" 
 * by William J. Cody, Jr. and William Waite, Prentice_Hall, 1980. 
 *
 * $Log: tanh.c,v $
 * Revision 1.1  1997/03/17 17:13:58  nettleto
 * Initial revision
 *
 */

#include <math.h>

#include <float.h>

static inline double
tanh_r (double g)
{
  const double p0 = - 0.16134119023996228053e+4;
  const double p1 = - 0.99225929672236083313e+2;
  const double p2 = - 0.96437492777225469787e+0;
  const double q0 = 0.48402357071988688686e+4;
  const double q1 = 0.22337720718962312926e+4;
  const double q2 = 0.11274474380534949335e+3;

  return (((p2 * g + p1) * g + p0) * g) /
    (((g + q2) * g + q1) * g + q0);
}
/*tanh_r*/

double
tanh (double x)
{
  double g, y;
  double result;
  const double xbig        = (double) (DBL_MANT_DIG+2)
                   * 0.34657359027997265471; /*half_log_two*/
  const double ln_3_over_2 = 0.54930614433405484570;

  y = fabs (x);

  if ( y > xbig )
    {
      result = 1.0;
    }
  else
    {
      if ( y > ln_3_over_2 )
        {
          result = 0.5 - 1.0 / (exp (y + y) + 1.0);
          result = result + result;
        }
      else
        {
          g = y * y;

          if ( g < DBL_EPSILON )
            result = y;
          else
            result = y + y * tanh_r (g);
        }
    }

  if ( x < 0.0 )
    result = - result;

  return result;
}
/*tanh*/


