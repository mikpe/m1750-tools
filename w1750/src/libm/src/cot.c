#include <math.h>
#include <errno.h>
#include <float.h>

static inline double
cot_r (double f, double g)
{
  const double p1 = - 0.13338350006421960681e+0;
  const double p2 = 0.34248878235890589960e-2;
  const double p3 = - 0.17861707342254426711e-4;
  const double q1 = - 0.46671683339755294240e+0;
  const double q2 = 0.25663832289440112864e-1;
  const double q3 = - 0.31181531907010027307e-3;
  const double q4 = 0.49819433993786512270e-6;

  return (((p3 * g + p2) * g + p1) * g * f + f) /
    (((((q4 * g + q3) * g + q2) * g + q1) * g + 0.5) + 0.5);
}
/*cot_r*/

double
cot (double x)
{
  double y;
  long   n;
  double xn;
  double f, g, x1, x2;
  double result;
  const double epsilon1    = 1.0 / DBL_MAX;
  const double c1          = 1.57080078125;
  const double c2          = - 0.44544551033807686783e-5;
  const double two_over_pi = 0.63661977236758134308;

  y = fabs (x);

  if ( y < epsilon1 )
    {
      errno = ERANGE;
      return ( x < 0.0 ) ? - HUGE_VAL : HUGE_VAL;
    }

  xn = floor (x * two_over_pi + 0.5);
  n  = (long) xn;
  x2 = modf (x, &x1);
  f  = ((x1 - xn * c1) + x2) - xn * c2;
  g  = f * f;

  if ( g < DBL_EPSILON )
    result = f;
  else
    result = cot_r (f, g);

  if ( n & 1 )
    return - result;
  else
    return 1.0 / result;
}
/*cot*/

