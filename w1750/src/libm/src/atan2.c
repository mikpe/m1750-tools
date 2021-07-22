/*
 * ANSI Standard C: 7.5.2.4
 * 
 * #include <math.h>
 * double atan2 (double y, double x);
 * 
 * Copyright (c) 1997, Chris Nettleton Software
 *
 * The contents of this file are based on the algorithms and 
 * coefficients given in "Software Manual for the Elementry Functions" 
 * by William J. Cody, Jr. and William Waite, Prentice_Hall, 1980. 
 *
 * $Log: atan2.c,v $
 * Revision 1.1  1997/03/17 17:12:24  nettleto
 * Initial revision
 *
 */

#include <math.h>

#include <math.h>

double
atan2 (double v, double u)
{
  double result;
  const double pi          = 3.14159265358979323846;
  const double pi_over_two = 1.57079632679489661923;

  if ( v == 0.0 && u == 0.0 )
    {
      result = 0.0;
    }
  else if ( fabs (v) <= fabs (u) )
    {
      result = atan (v / u);

      if (u <= 0)
        {
          if (v <= 0)
            result -= pi;
          else
            result += pi;
        }
    }
  else
    {
      result = atan (- u / v);

      if (v <= 0)
        result -= pi_over_two;
      else
        result += pi_over_two;
    }

  return result;
}
/*atan2*/


