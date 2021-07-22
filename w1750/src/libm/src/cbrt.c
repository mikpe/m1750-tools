#include <math.h>

double
cbrt (double x)
{
  int    m, n;
  double f, y;
  double result;
  const double cbrt_c1 = 0.5874009;
  const double cbrt_c2 = 0.4125990;
  const double cbrt_c3 = 0.6299605249;
  const double cbrt_c4 = 0.7937005260;

  if ( x == 0.0 )
    {
      result = 0.0;
    }
  else
    {
      f = frexp (x, &n);
      f = fabs (f);
      y = cbrt_c1 + cbrt_c2 * f;

      switch ( (n % 3) )
        {
          case 0:
            /*null*/
            break;
          case -2: case 1:
            y = cbrt_c3 * y;
            f = f / 4.0;
            n = n + 2;
            break;
          case -1: case 2:
            y = cbrt_c4 * y;
            f = f / 2.0;
            n = n + 1;
            break;
          default:
            /*null*/
            break;
        }

      m = n / 3;
      y = y - (y / 3.0 - ((f / 3.0) / (y * y)));
      y = y - (y / 3.0 - ((f / 3.0) / (y * y)));
      y = y - (y / 3.0 - ((f / 3.0) / (y * y)));
      y = y - (y / 3.0 - ((f / 3.0) / (y * y)));

      if ( x < 0.0 )
        y = - y;

      result = ldexp (y, m);
    }
  return result;
}
/*cbrt*/

