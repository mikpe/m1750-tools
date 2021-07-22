/*
 *::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
 *TESTMATH
 *::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
 */


#include <errno.h>
#include <stdio.h>
#include <limits.h>
#include <float.h>
#include <math.h>


/*
 *::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
 *Functions used by Tests only.
 *::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
 */


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

double
sign (double x, double y)
{
/*
 * Returns the value of X with the sign of Y (sic)
 */
  return ( y >= 0.0 ) ? x : -x;
}
/*sign*/


double
max (double x, double y)
{
/*
 * Returns the algebraically larger of X and Y
 */
  return ( x >= y ) ? x : y;
}
/*max*/


double
min (double x, double y)
{
/*
 * Returns the algebraically smaller of X and Y
 */
  return ( x <= y ) ? x : y;
}
/*min*/


int
itrunc (double x)
{
/*
 * Returns the integer value of the integer no larger than X
 * Truncates toward zero
 */
  return ( x >= 0.0 ) ? (int) (x) : -(int) (-x);
}
/*itrunc*/


int
iround (double x)
{
/*
 * Returns the integer value of the integer nearest X
 */
  return ( x >= 0.0 ) ? (int) (x+0.5) : -(int) (-x+0.5);
}
/*iround*/


double
trunc (double x)
{
/*
 * Returns the floating value of the integer no larger than X
 * Truncates toward zero
 */
  return ( x >= 0.0 ) ? floor (x) : ceil (x);
}
/*trunc*/


double
round (double x)
{
/*
 * Returns the floating value of the integer nearest X
 */
  return floor (x+0.5);
}
/*round*/


double
powi (double x, int i)
{
  /* Replace by Square-&-Shift */
  double result = 1.0;

  if (i > 0)
    while (i--) result *= x;
  else if (i < 0)
    while (i++) result /= x;
    /* Multiplying, then taking the reciprocal, can overflow. */
  return result;
}
/*powi*/


double
force (double item)
{
/*
 * The aim of this function is to Force the Item out of the
 * coprocessor into a Long_Float representation on the stack.
 * It is only needed on some machines (not 1750?) and will
 * only work with some compilers (Meridian, not XD-Ada?).
 * Giving the body last would reduce the risk of in-lining.
 * (For machines which pass both parameters and results in
 * registers, the Item could be written a packed array,
 * then read back via an index that the compiler cannot
 * tell is the same: also then in-lining would not matter).
 */

  return item;
}
/*force*/


/*
 * This package is a floating mantissa definition of a binary floating
 * The parameters are obtained by initializing on the actual hardware
 * Otherwise the parameters could be set in the spec if known
 * The constants are those required by the routines described in
 * "Software Manual for the Elementary Functions" W. Cody & W. Waite
 * Prentice-Hall 1980
 * Actually most are needed only for the test programs
 * rather than the functions themselves and are reproduced there
 * Many of these could be in the form of attributes for hardware float types
 * but some are not easily available for the machine hardware base
 * So we use the Cody-Waite names and derive them from an adaptation of the
 * MACHAR routine as given by Cody-Waite in Appendix B
 */
int ibeta;
/*
 * The radix of the floating-point representation
 */
int it;
/*
 * The number of base IBETA digits in the floating significand
 */
int irnd;
/*
 * TRUE (1) if floating addition rounds, FALSE (0) if truncates
 */
int ngrd;
/*
 * Number of guard digits for multiplication
 */
int machep;
/*
 * The largest negative integer such that
 *   1.0 + floating(IBETA) ** MACHEP /= 1.0
 * except that MACHEP is bounded below by -(IT + 3)
 */
int negep;
/*
 * The largest negative integer such that
 *   1.0 -0 floating(IBETA) ** NEGEP /= 1.0
 * except that NEGEP is bounded below by -(IT + 3)
 */
int iexp;
/*
 * The number of bits (decimal places if IBETA = 10)
 * reserved for the representation of the exponent (including
 * the bias or sign) of a floating-point number
 */
int minexp;
/*
 * The largest in magnitude negative integer such that
 * floating(IBETA) ** MINEXP is a positive floating-point number
 */
int maxexp;
/*
 * The largest positive exponent for a finite floating-point number
 */
double eps;
/*
 * The smallest positive floating-point number such that
 *                             1.0 + EPS /= 1.0
 * In particular, if IBETA = 2 or IRND = 0,
 * EPS = floating(IBETA) ** MACHEP
 * Otherwise, EPS = (floating(IBETA) ** MACHEP) / 2
 */
double epsneg;
/*
 * A small positive floating-point number such that 1.0-EPSNEG /= 1.0
 */
double xmin;
/*
 * The smallest non-vanishing floating-point power of the radix
 * In particular, XMIN = floating(IBETA) ** MINEXP
 */
double xmax;
/*
 * The largest finite floating-point number
 */


void
machar (void)
{
/*
 * This initialization is the MACHAR routine of Cody and Waite Appendix B.
 */
  double a, b, y, z;
  int    i, k, mx, iz;
  double beta, betam1, betain;

  a = 1.0;
  while ( ((force(a + 1.0) - a) - 1.0) == 0.0 )
    {
      a = a + a;
    }

  b = 1.0;
  while ( (force(a + b) - a) == 0.0 )
    {
      b = b + b;
    }

  ibeta = iround (force(a + b) - a);
  beta  = (double) (ibeta);
  it    = 0;
  b     = 1.0;
  while ( ((force(b + 1.0) - b) - 1.0) == 0.0 )
    {
      it = it + 1;
      b  = b * beta;
    }

  irnd   = 0;
  betam1 = beta - 1.0;
  if ( (force(a + betam1) - a) != 0.0 )
    {
      irnd = 1;
    }
  negep  = it + 3;
  betain = 1.0 / beta;
  a      = 1.0;
  for ( i = 1; i <= negep; i ++ )
    {
      a = a * betain;
    }
  b = a;
  while ( (force(1.0 - a) - 1.0) == 0.0 )
    {
      a     = a * beta;
      negep = negep - 1;
    }
  negep  = - negep;
  epsneg = a;
  if ( (ibeta != 2) & (irnd != 0) )
    {
      a = (a * (1.0 + a)) / 2.0;
      if ( (force(1.0 - a) - 1.0) != 0.0 )
        {
          epsneg = a;
        }
    }
  machep = - it - 3;
  a      = b;
  while ( (force(1.0 + a) - 1.0) == 0.0 )
    {
      a      = a * beta;
      machep = machep + 1;
    }
  eps = a;
  if ( (ibeta != 2) & (irnd != 0) )
    {
      a = (a * (1.0 + a)) / 2.0;
      if ( (force(1.0 + a) - 1.0) != 0.0 )
        {
          eps = a;
        }
    }
  ngrd = 0;
  if ( ((irnd == 0) & (force(force(1.0 + eps) * 1.0) - 1.0) != 0.0) )
    {
      ngrd = 1;
    }
  find_iexp:
    {
      double a = betain;
      double y;
      int    i = 0;

      for (;;)
        {
          y = force(a * a);
          if ( y == 0.0) break;
          i = i + 1;
          a = y;
        }
      iexp = i;
    }
    /*find_iexp*/
  find_smallest:
    {
      double a = 1.0;
      double y;
      int    i = 0;

      for (;;)
        {
          y = force(a / beta);
          if ( y == 0.0) break;
          i = i - 1;
          a = y;
        }
      minexp = i;
      xmin   = a;
    }
    /*find_smallest*/
  xmax = DBL_MAX;
  find_largest:
    {
      double y = xmax;
      int    i = 0;

      while ( y > 1.0 )
        {
          y = force(y / beta);
          i = i + 1;
        }
      maxexp = i;
    }
    /*find_largest*/
}
/*machar*/


struct
{
  int x;
  int y;
  int z;
}
key =
{
  10001,
  20001,
  30001
};


double
ran (void)
{
/*
 * A random number between zero and one
 * This uses a portable algorithm and is included at this point so that
 * an implementation could take advantage of unique machine characteristics
 * This rectangular random number routine is adapted from a report
 * "A Pseudo-Random Number Generator" by B. A. Wichmann and I. D. Hill
 * NPL Report DNACS XX (to be published)
 * In this stripped version, it is suitable for machines supporting
 * INTEGER at only 16 bits and is portable
 */
  double w;

  key.x = 171 * (key.x % 177) - 2 * (key.x / 177);
  if ( key.x < 0 ) key.x += 30269;
  key.y = 172 * (key.y % 176) - 35 * (key.y / 176);
  if ( key.y < 0 ) key.y += 30307;
  key.z = 170 * (key.z % 178) - 63 * (key.z / 178);
  if ( key.z < 0 ) key.z += 30323;
  w = (double) (key.x) / 30269.0
    + (double) (key.y) / 30307.0
    + (double) (key.z) / 30323.0;
  while ( w >= 1.0 ) w -= 1.0;
  return w;
}
/*ran*/


void
set_ran_key (double k)
{
/*
 * Can reset the random number generator
 */
  int i;

  if ( k == 0.0 )
    {
      key.x = 10001;
      key.y = 20001;
      key.z = 30001;
    }
  else
    {
      for ( i = 1; i <= iround (k - round (fabs (k) / 31247.0)
          * 31247.0) % 31247; i ++ )
        ran ();
    }
}
/*set_ran_key*/


/*
 *::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
 *TESTSQRT
 *::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
 */
void
test_sqrt (void)
{
  int    n = 2000;
  int    i, j, k1, k2, k3;
  double r6, r7;
  double w, x, y, z;
  double x1;
  double a, b, c;
  const double beta   = (double) (ibeta);
  const double sqbeta = sqrt (beta);
  const double albeta = log (beta);
  const double ait    = (double) (it);
  const double xn     = (double) (n);

/*
 *---------------------------------------------------------
 *               RANDOM ARGUMENT TESTS
 *---------------------------------------------------------
 */
  a = 1.0 / sqbeta;
  b = 1.0;
  for ( j = 1; j <= 2; j ++ )
    {
      c  = log (b / a);
      k1 = 0;
      k3 = 0;
      x1 = 0.0;
      r6 = 0.0;
      r7 = 0.0;
      for ( i = 1; i <= n; i ++ )
        {
          x = a * exp (c * ran ());
          y = x * x;
          z = sqrt (y);
          w = (z - x) / x;
          if ( w > 0.0 ) k1++;
          if ( w < 0.0 ) k3++;
          w = fabs (w);
          if ( w > r6 )
            {
              r6 = w;
              x1 = x;
            }
          r7 = r7 + (w * w);
        }
      k2 = n - k1 - k3;
      r7 = sqrt (r7 / xn);

      printf ("TEST OF SQRT(X*X)-X\n");

      printf (" ");
      printf ("%d", n);
      printf (" RANDOM ARGUMENTS WERE TESTED FROM THE INTERVAL ");
      printf ("\n");
      printf ("%.14e", a);
      printf (",  ");
      printf ("%.14e", b);
      printf ("\n");
      printf (" SQRT(X) WAS LARGER ");
      printf ("%6d", k1);
      printf (" TIMES\n");
      printf (" AGREED             ");
      printf ("%6d", k2);
      printf (" TIMES\n");
      printf (" WAS SMALLER        ");
      printf ("%6d", k3);
      printf (" TIMES\n");
      printf ("\n");
      printf (" THERE ARE ");
      printf ("%4d", it);
      printf (" BASE ");
      printf ("%4d", ibeta);
      printf (" SIGNIFICANT DIGITS IN A FLOATING-POINT NUMBER");

      w = - 999.0e0;
      if ( (r6 != 0.0) )
        {
          w = log (fabs (r6)) / albeta;
        }
      printf (" THE MAXIMUM RELATIVE ERROR OF ");
      printf ("%10.4e", r6);
      printf (" = ");
      printf ("%4d", ibeta);
      printf (" **");
      printf ("%7.2f", w);
      printf ("\n");
      printf ("    OCCURED FOR X = ");
      printf ("%12.6e", x1);
      printf ("\n");
      w = max (ait + w, 0.0);
      printf (" THE ESTIMATED LOSS OF BASE ");
      printf ("%4d", ibeta);
      printf (" SIGNIFICANT DIGITS IS ");
      printf ("%7.2f", w);
      printf ("\n\n");
      w = - 999.0e0;
      if ( (r7 != 0.0) )
        {
          w = log (fabs (r7)) / albeta;
        }
      printf (" THE ROOT MEAN SQUARE RELATIVE ERROR WAS ");
      printf ("%10.4e", r7);
      printf (" = ");
      printf ("%4d", ibeta);
      printf (" **");
      printf ("%7.2f", w);
      printf ("\n");
      w = max (ait + w, 0.0);
      printf (" THE ESTIMATED LOSS OF BASE ");
      printf ("%4d", ibeta);
      printf (" SIGNIFICANT DIGITS IS ");
      printf ("%7.2f", w);
      printf ("\n\n");
      a = 1.0;
      b = sqbeta;
    }
/*
 *----------------------------------------------------------
 *               SPECIAL TESTS
 *----------------------------------------------------------
 */

  printf (" TEST OF SPECIAL ARGUMENTS\n");

  x = xmin;
  y = sqrt (x);
  printf (" SQRT(XMIN) =       SQRT(");
  printf ("%.14e", xmin);
  printf (") =    ");
  printf ("%.14e", y);

  x = 1.0 - epsneg;
  y = sqrt (x);
  printf (" SQRT(1 - EPSNEG) = SQRT(1 - ");
  printf ("%.14e", epsneg);
  printf (") = ");
  printf ("%.14e", y);

  x = 1.0;
  y = sqrt (x);
  printf (" SQRT(1.0) =        SQRT(");
  printf ("%.14e", x);
  printf (") =     ");
  printf ("%.14e", y);

  x = 1.0 + eps;
  y = sqrt (x);
  printf (" SQRT(1 + EPS) =    SQRT(1 + ");
  printf ("%.14e", eps);
  printf (") = ");
  printf ("%.14e", y);

  x = xmax;
  y = sqrt (x);
  printf (" SQRT(XMAX) =       SQRT(");
  printf ("%.14e", xmax);
  printf (") =    ");
  printf ("%.14e", y);

/*
 *----------------------------------------------------------
 *               TESTS OF ERROR RETURNS\n
 *----------------------------------------------------------
 */

  printf (" TEST OF ERROR RETURNS\n\n");

  x = 0.0;
  printf (" SQRT WILL BE CALLED WITH THE ARGUMENT ");
  printf ("%.14e", x);
  printf ("\n");
  printf (" THIS SHOULD NOT TRIGGER AN ERROR MESSAGE");
  printf ("\n\n");
  y = sqrt (x);
  printf (" SQRT RETURNED THE VALUE ");
  printf ("%.14e", y);
  printf ("\n");
  x = - 1.0;
  printf (" SQRT WILL BE CALLED WITH THE ARGUMENT ");
  printf ("%.14e", x);
  printf ("\n");
  printf (" THIS SHOULD TRIGGER AN ERROR MESSAGE");
  printf ("\n\n");
  y = sqrt (x);
  printf (" SQRT RETURNED THE VALUE ");
  printf ("%.14e", y);
  printf ("\n");
  printf (" THIS CONCLUDES THE TESTS");
  printf ("\n");
}
/*test_sqrt*/


/*
 *::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
 *TESTCBRT
 *::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
 */
void
test_cbrt (void)
{
  int    n = 2000;
  int    i, j, k1, k2, k3;
  double r6, r7;
  double w, x, y, z;
  double x1;
  double a, b, c;
  const double beta   = (double) (ibeta);
  const double cbbeta = cbrt (beta);
  const double albeta = log (beta);
  const double ait    = (double) (it);
  const double xn     = (double) (n);

  
/*
 *---------------------------------------------------------
 *               RANDOM ARGUMENT TESTS
 *---------------------------------------------------------
 */
  a = 1.0 / cbbeta / cbbeta;
  for ( j = 1; j <= 3; j ++ )
    {
      a  = a * cbbeta;
      b  = a * cbbeta;
      c  = log (b / a);
      k1 = 0;
      k3 = 0;
      x1 = 0.0;
      r6 = 0.0;
      r7 = 0.0;
      for ( i = 1; i <= n; i ++ )
        {
           a * exp (c * ran ());
          y = x * x * x;
          z = cbrt (y);
          w = (z - x) / x;
          if ( w > 0.0 ) k1++;
          if ( w < 0.0 ) k3++;
          w = fabs (w);
          if ( w > r6 )
            {
              r6 = w;
              x1 = x;
            }
          r7 = r7 + (w * w * w);
        }
      k2 = n - k1 - k3;
      r7 = cbrt (r7 / xn);

      printf (" TEST OF CBRT(X*X*X)-X");

      printf (" ");
      printf ("%d", n);
      printf (" RANDOM ARGUMENTS WERE TESTED FROM THE INTERVAL ");
      printf ("\n");
      printf ("%.14e", a);
      printf (",  ");
      printf ("%.14e", b);
      printf ("\n");
      printf (" CBRT(X) WAS LARGER ");
      printf ("%6d", k1);
      printf (" TIMES");
      printf ("\n");
      printf (" AGREED ");
      printf ("%6d", k2);
      printf (" TIMES");
      printf ("\n");
      printf (" WAS SMALLER ");
      printf ("%6d", k3);
      printf (" TIMES");
      printf ("\n");
      printf ("\n");
      printf (" THERE ARE ");
      printf ("%4d", it);
      printf (" BASE ");
      printf ("%4d", ibeta);
      printf (" SIGNIFICANT DIGITS IN A FLOATING-POINT NUMBER");

      w = - 999.0e0;
      if ( (r6 != 0.0) )
        {
          w = log (fabs (r6)) / albeta;
        }
      printf (" THE MAXIMUM RELATIVE ERROR OF ");
      printf ("%10.4e", r6);
      printf (" = ");
      printf ("%4d", ibeta);
      printf (" **");
      printf ("%7.2f", w);
      printf ("\n");
      printf ("    OCCURED FOR X = ");
      printf ("%12.6e", x1);
      printf ("\n");
      w = max (ait + w, 0.0);
      printf (" THE ESTIMATED LOSS OF BASE ");
      printf ("%4d", ibeta);
      printf (" SIGNIFICANT DIGITS IS ");
      printf ("%7.2f", w);
      printf ("\n\n");
      w = - 999.0e0;
      if ( (r7 != 0.0) )
        {
          w = log (fabs (r7)) / albeta;
        }
      printf (" THE ROOT MEAN SQUARE RELATIVE ERROR WAS ");
      printf ("%10.4e", r7);
      printf (" = ");
      printf ("%4d", ibeta);
      printf (" **");
      printf ("%7.2f", w);
      printf ("\n");
      w = max (ait + w, 0.0);
      printf (" THE ESTIMATED LOSS OF BASE ");
      printf ("%4d", ibeta);
      printf (" SIGNIFICANT DIGITS IS ");
      printf ("%7.2f", w);
      printf ("\n\n");
    }
/*
 *----------------------------------------------------------
 *               SPECIAL TESTS
 *----------------------------------------------------------
 */

  printf (" TEST OF SPECIAL ARGUMENTS");

  x = xmin;
  y = cbrt (x);
  printf (" CBRT(XMIN) = CBRT(");
  printf ("%.14e", xmin);
  printf (") = ");
  printf ("%.14e", y);

  x = 1.0 - epsneg;
  y = cbrt (x);
  printf (" CBRT(1 - EPSNEG) = CBRT(1 - ");
  printf ("%.14e", epsneg);
  printf (") = ");
  printf ("%.14e", y);

  x = 1.0;
  y = cbrt (x);
  printf (" CBRT(1.0) = CBRT(");
  printf ("%.14e", x);
  printf (") = ");
  printf ("%.14e", y);

  x = 1.0 + eps;
  y = cbrt (x);
  printf (" CBRT(1 + EPS) = CBRT(1 + ");
  printf ("%.14e", eps);
  printf (") = ");
  printf ("%.14e", y);

  x = xmax;
  y = cbrt (x);
  printf (" CBRT(XMAX) = CBRT(");
  printf ("%.14e", xmax);
  printf (") = ");
  printf ("%.14e", y);

/*
 *----------------------------------------------------------
 *               TESTS OF ERROR RETURNS\n
 *----------------------------------------------------------
 */

  printf (" TEST OF ERROR RETURNS\n");

  x = 0.0;
  printf (" CBRT WILL BE CALLED WITH THE ARGUMENT ");
  printf ("%.14e", x);
  printf ("\n");
  printf (" THIS SHOULD NOT TRIGGER AN ERROR MESSAGE");

  y = cbrt (x);
  printf (" CBRT RETURNED THE VALUE ");
  printf ("%.14e", y);
  printf ("\n");
  x = - 1.0;
  printf (" CBRT WILL BE CALLED WITH THE ARGUMENT ");
  printf ("%.14e", x);
  printf ("\n");
  printf (" THIS SHOULD NOT TRIGGER AN ERROR MESSAGE");

  y = cbrt (x);
  printf (" CBRT RETURNED THE VALUE ");
  printf ("%.14e", y);
  printf ("\n");
  printf (" THIS CONCLUDES THE TESTS");
  printf ("\n");
}
/*test_cbrt*/


/*
 *::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
 *TESTLOG
 *::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
 */
void
test_log (void)
{
  int    n = 2000;
  int    i, j, k1, k2, k3;
  double r6, r7;
  double w, x, xl, y, z, zz;
  double x1;
  double a, b, c, del;
  const double tenth  = 0.1;
  const double eight  = 8.0;
  const double beta   = (double) (ibeta);
  const double albeta = log (beta);
  const double ait    = (double) (it);
  const double xn     = (double) (n);

  
/*
 *---------------------------------------------------------
 *               RANDOM ARGUMENT TESTS
 *---------------------------------------------------------
 */
  for ( j = 1; j <= 4; j ++ )
    {
      switch ( j )
        {
          case 1:
            c = 1.0;
            for ( i = 1; i <= it / 3; i ++ )
              {
                c = c / beta;
              }
            a = 1.0 - c;
            b = 1.0 + c;
            break;
          case 2:
            a = sqrt (0.5);
            b = 15.0 / 16.0;
            break;
          case 3:
            a = sqrt (tenth);
            b = 0.9;
            break;
          case 4:
            a = 16.0;
            b = 240.0;
            break;
        }
/*
 *       C   := Log (B / A);
 */
      k1  = 0;
      k3  = 0;
      x1  = 0.0;
      r6  = 0.0;
      r7  = 0.0;
      del = (b - a) / xn;
      xl  = a;
      for ( i = 1; i <= n; i ++ )
        {
          x = del * ran () + xl;
          switch ( j )
            {
              case 1:
                y  = (x - 0.5) - 0.5;
                zz = log (x);
                z  = 1.0 / 3.0;
                z  = y * (z - y / 4.0);
                z  = (z - 0.5) * y * y + y;
                break;
              case 2:
                x  = force(x + eight) - eight;
                y  = x + x / 16.0;
                z  = log (x);
                zz = log (y) - 7.7746816434842581e-5;
                zz = zz - 31.0 / 512.0;
                break;
              case 3:
                x  = force(x + eight) - eight;
                y  = x + x * tenth;
                z  = log10 (x);
                zz = log10 (y) - 3.7706015822504075e-4;
                zz = zz - 21.0 / 512.0;
                break;
              case 4:
                z  = log (x * x);
                zz = log (x);
                zz = zz + zz;
                break;
            }
          w = 1.0;
          if ( z != 0.0 )
            {
              w = (z - zz) / z;
            }
          z = sign (w, z);
          if ( z > 0.0 ) k1++;
          if ( z < 0.0 ) k3++;
          w = fabs (w);
          if ( w > r6 )
            {
              r6 = w;
              x1 = x;
            }
          r7 = r7 + w * w;
          xl = xl + del;
        }
      k2 = n - k1 - k3;
      r7 = sqrt (r7 / xn);

      switch ( j )
        {
          case 1:
            printf (" TEST OF LOG(X) VS T.S. EXPANSION OF LOG(1+Y)  ");
      
            break;
          case 2:
            printf (" TEST OF LOG(X) VS LOG(17X/16) - LOG(17/16)  ");
      
            break;
          case 3:
            printf (" TEST OF LOG(X*X) VS 2 * LOG(X)  ");
      
            break;
          case 4:
            printf (" TEST OF LOG10(X) VS LOG10(11X/10) - LOG10(11/10)  ");
      
            break;
        }
      printf ("%d", n);
      printf (" RANDOM ARGUMENTS WERE TESTED FROM THE INTERVAL ");
      printf ("\n");
      switch ( j )
        {
          case 1:
            printf ("      (1-EPS, 1+EPS), WHERE EPS = ");
            printf ("%.14e", c);
      
            break;
          case 2: case 3: case 4:
            printf ("      (");
            printf ("%.14e", a);
            printf (",");
            printf ("%.14e", b);
            printf (")");
            printf ("\n");
            break;
        }
      switch ( j )
        {
          case 1: case 2: case 4:
            printf ("   LOG(X) WAS LARGER  ");
            break;
          case 3:
            printf (" LOG10(X) WAS LARGER  ");
            break;
        }
      printf ("%6d", k1);
      printf (" TIMES");
      printf ("\n");
      printf ("              AGREED  ");
      printf ("%6d", k2);
      printf (" TIMES");
      printf ("\n");
      printf ("          WAS SMALLER ");
      printf ("%6d", k3);
      printf (" TIMES");

      printf (" THERE ARE ");
      printf ("%4d", it);
      printf (" BASE ");
      printf ("%4d", ibeta);
      printf (" SIGNIFICANT DIGITS IN A FLOATING-POINT NUMBER");

      w = - 999.0e0;
      if ( (r6 != 0.0) )
        {
          w = log (fabs (r6)) / albeta;
        }
      printf (" THE MAXIMUM RELATIVE ERROR OF ");
      printf ("%10.4e", r6);
      printf (" = ");
      printf ("%4d", ibeta);
      printf (" **");
      printf ("%7.2f", w);
      printf ("\n");
      printf ("    OCCURED FOR X = ");
      printf ("%.14e", x1);
      printf ("\n");
      w = max (ait + w, 0.0);
      printf (" THE ESTIMATED LOSS OF BASE ");
      printf ("%4d", ibeta);
      printf (" SIGNIFICANT DIGITS IS ");
      printf ("%7.2f", w);
      printf ("\n\n");
      w = - 999.0e0;
      if ( (r7 != 0.0) )
        {
          w = log (fabs (r7)) / albeta;
        }
      printf (" THE ROOT MEAN SQUARE RELATIVE ERROR WAS ");
      printf ("%10.4e", r7);
      printf (" = ");
      printf ("%4d", ibeta);
      printf (" **");
      printf ("%7.2f", w);
      printf ("\n");
      w = max (ait + w, 0.0);
      printf (" THE ESTIMATED LOSS OF BASE ");
      printf ("%4d", ibeta);
      printf (" SIGNIFICANT DIGITS IS ");
      printf ("%7.2f", w);
      printf ("\n\n");
    }
/*
 *----------------------------------------------------------
 *               SPECIAL TESTS
 *----------------------------------------------------------
 */

  printf (" SPECIAL TESTS\n");

  printf (" THE IDENTITY LOG(X) = -LOG(1/X) WILL BE TESTED.");
  printf ("\n");
  for ( i = 1; i <= 5; i ++ )
    {
      x = ran ();
      x = x + x + 15.0;
      y = 1.0 / x;
      z = log (x) + log (y);
      printf ("%.14e", x);
      printf ("    ");
      printf ("%.14e", z);
      printf ("\n");
    }
  printf ("\n\n");
  printf (" TEST OF SPECIAL ARGUMENTS ");
  printf ("\n\n");
  x = 1.0;
  y = log (x);
  printf (" LOG(1.0) = ");
  printf ("%.14e", y);

  x = xmin;
  y = log (x);
  printf (" LOG(XMIN) = LOG(");
  printf ("%.14e", xmin);
  printf (") = ");
  printf ("%.14e", y);

  x = xmax;
  y = log (x);
  printf (" LOG(XMAX) = LOG(");
  printf ("%.14e", xmax);
  printf (") = ");
  printf ("%.14e", y);

/*
 *----------------------------------------------------------
 *               TESTS OF ERROR RETURNS\n
 *----------------------------------------------------------
 */

  printf (" TEST OF ERROR RETURNS\n\n");
  printf ("\n\n");
  x = - 2.0;
  printf (" LOG WILL BE CALLED WITH THE ARGUMENT ");
  printf ("%.14e", x);
  printf ("\n");
  printf (" THIS SHOULD TRIGGER AN ERROR MESSAGE");

  y = log (x);
  printf (" LOG RETURNED THE VALUE ");
  printf ("%.14e", y);
  printf ("\n");
  x = 0.0;
  printf (" LOG WILL BE CALLED WITH THE ARGUMENT ");
  printf ("%.14e", x);
  printf ("\n");
  printf (" THIS SHOULD TRIGGER AN ERROR MESSAGE");

  y = log (x);
  printf (" LOG RETURNED THE VALUE ");
  printf ("%.14e", y);
  printf ("\n");
  printf (" THIS CONCLUDES THE TESTS\n");
}
/*test_log*/


/*
 *::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
 *TESTEXP
 *::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
 */
void
test_exp (void)
{
  int    n = 2000;
  int    i, j, k1, k2, k3;
  double r6, r7;
  double w, x, xl, y, z, zz;
  double x1;
  double a, b, c, d, del;
  const double tenth = 0.1;
  const double ten   = 10.0;
  double v      = 0.0625;
  double beta   = (double) (ibeta);
  double albeta = log (beta);
  double ait    = (double) (it);
  double xn     = (double) (n);

  
/*
 *---------------------------------------------------------
 *               RANDOM ARGUMENT TESTS
 *---------------------------------------------------------
 */
  for ( j = 1; j <= 3; j ++ )
    {
      switch ( j )
        {
          case 1:
            a = 2.0;
            b = log (a) * 0.5;
            a = - b + v;
            break;
          case 2:
            v = 45.0 / 16.0;
            a = - ten * b;
            b = ten * xmin * powi (beta, it);  /* Occasional underflow when 4.0 */
            b = log (b);
            break;
          case 3:
            a = - 2.0 * a;
            b = ten * a;
            d = log ((1.0 - tenth) * xmax);
  /*
   *     if B < D  then       Cody-Waite seems to err here
   */
            if ( b > d )
              {
                b = d;
              }
            break;
        }
      k1  = 0;
      k3  = 0;
      x1  = 0.0;
      r6  = 0.0;
      r7  = 0.0;
      del = (b - a) / xn;
      xl  = a;
      for ( i = 1; i <= n; i ++ )
        {
          x = del * ran () + xl;
  /*
   *---------------------------------------------------------
   *                      PURIFY ARGUMENTS
   *---------------------------------------------------------
   */
          y = x - v;
          if ( y < 0.0 )
            {
              x = y + v;
            }
          z  = exp (x);
          zz = exp (y);
          if ( j == 1 )
            {
              z = z - z * 6.058693718652421388e-2;
            }
          else
            {
              if ( ibeta != 10 )
                {
                  z = z * 0.0625 - z * 2.4453321046920570389e-3;
                }
              else
                {
                  z = z * 6.0e-2 + z * 5.466789530794296106e-5;
                }
            }
          w = 1.0;
          if ( zz != 0.0 )
            {
              w = (z - zz) / z;
            }
          if ( w > 0.0 ) k1++;
          if ( w < 0.0 ) k3++;
          w = fabs (w);
          if ( w > r6 )
            {
              r6 = w;
              x1 = x;
            }
          r7 = r7 + w * w;
          xl = xl + del;
        }
      k2 = n - k1 - k3;
      r7 = sqrt (r7 / xn);

      printf (" TEST OF EXP(X - ");
      printf ("%7.4f", v);
      printf (") VS EXP(X)/EXP(");
      printf ("%7.4f", v);
      printf (") ");

      printf (" RANDOM ARGUMENTS WERE TESTED FROM THE INTERVAL ");
      printf ("\n");
      printf ("      (");
      printf ("%.14e", a);
      printf (",");
      printf ("%.14e", b);
      printf (")");
      printf ("\n");
      printf (" EXP(X-V) WAS LARGER  ");
      printf ("%6d", k1);
      printf (" TIMES");
      printf ("\n");
      printf ("              AGREED  ");
      printf ("%6d", k2);
      printf (" TIMES");
      printf ("\n");
      printf ("          WAS SMALLER ");
      printf ("%6d", k3);
      printf (" TIMES");

      printf (" THERE ARE ");
      printf ("%4d", it);
      printf (" BASE ");
      printf ("%4d", ibeta);
      printf (" SIGNIFICANT DIGITS IN A FLOATING-POINT NUMBER");

      w = - 999.0e0;
      if ( (r6 != 0.0) )
        {
          w = log (fabs (r6)) / albeta;
        }
      printf (" THE MAXIMUM RELATIVE ERROR OF ");
      printf ("%10.4e", r6);
      printf (" = ");
      printf ("%4d", ibeta);
      printf (" **");
      printf ("%7.2f", w);
      printf ("\n");
      printf ("    OCCURED FOR X = ");
      printf ("%12.6e", x1);
      printf ("\n");
      w = max (ait + w, 0.0);
      printf (" THE ESTIMATED LOSS OF BASE ");
      printf ("%4d", ibeta);
      printf (" SIGNIFICANT DIGITS IS ");
      printf ("%7.2f", w);
      printf ("\n\n");
      w = - 999.0e0;
      if ( (r7 != 0.0) )
        {
          w = log (fabs (r7)) / albeta;
        }
      printf (" THE ROOT MEAN SQUARE RELATIVE ERROR WAS ");
      printf ("%10.4e", r7);
      printf (" = ");
      printf ("%4d", ibeta);
      printf (" **");
      printf ("%7.2f", w);
      printf ("\n");
      w = max (ait + w, 0.0);
      printf (" THE ESTIMATED LOSS OF BASE ");
      printf ("%4d", ibeta);
      printf (" SIGNIFICANT DIGITS IS ");
      printf ("%7.2f", w);
      printf ("\n\n");
    }
/*
 *----------------------------------------------------------
 *               SPECIAL TESTS
 *----------------------------------------------------------
 */

  printf (" SPECIAL TESTS\n");

  printf (" THE IDENTITY EXP(X)*EXP(-X) = 1.0) WILL BE TESTED.");
  printf ("\n");
  for ( i = 1; i <= 5; i ++ )
    {
      x = ran () * beta;
      y = - x;
      z = exp (x) * exp (y) - 1.0;
      printf ("%.14e", x);
      printf ("    ");
      printf ("%.14e", z);
      printf ("\n");
    }
  printf ("\n\n");
  printf (" TEST OF SPECIAL ARGUMENTS ");
  printf ("\n\n");
  x = 0.0;
  y = exp (x) - 1.0;
  printf (" EXP(0.0) - 1.0             = ");
  printf ("%.14e", y);

  x = trunc (log (xmin));
  y = exp (x);
  printf (" EXP(");
  printf ("%.14e", x);
  printf (") = ");
  printf ("%.14e", y);
  printf ("\n\n");
  x = trunc (log (xmax));
  y = exp (x);
  printf (" EXP(");
  printf ("%.14e", x);
  printf (") = ");
  printf ("%.14e", y);
  printf ("\n\n");
  x = x / 2.0;
  c = x / 2.0;
  y = exp (x);
  z = exp (c);
  z = z * z;
  printf ("\n");
  printf (" IF EXP(");
  printf ("%.14e", x);
  printf (") = ");
  printf ("%.14e", y);
  printf (" IS NOT ABOUT ");
  printf ("\n");
  printf (" EXP(");
  printf ("%.14e", c);
  printf (")**2 = ");
  printf ("%.14e", z);
  printf (" THERE IS AN ARG RED ERROR");
  printf ("\n");
/*
 *----------------------------------------------------------
 *               TESTS OF ERROR RETURNS\n
 *----------------------------------------------------------
 */

  printf (" TEST OF ERROR RETURNS\n\n");

  x = - 1.0 / sqrt (xmin);
  printf (" EXP WILL BE CALLED WITH THE ARGUMENT ");
  printf ("%.14e", x);
  printf ("\n");
  printf (" THIS SHOULD TRIGGER AN ERROR MESSAGE");
  printf ("\n\n");
  y = exp (x);
  printf (" EXP RETURNED THE VALUE ");
  printf ("%.14e", y);
  printf ("\n");
  x = - x;
  printf (" EXP WILL BE CALLED WITH THE ARGUMENT ");
  printf ("%.14e", x);
  printf ("\n");
  printf (" THIS SHOULD TRIGGER AN ERROR MESSAGE");
  printf ("\n\n");
  y = exp (x);
  printf (" EXP RETURNED THE VALUE ");
  printf ("%.14e", y);
  printf ("\n");
  printf (" THIS CONCLUDES THE TESTS");
  printf ("\n");
}
/*test_exp*/


/*
 *::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
 *TESTPOWER
 *::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
 */
void
test_power (void)
{
  int    n = 2000;
  int    i, j, k1, k2, k3;
  double r6, r7;
  double w, x, x1, xl, xsq, y, y2, z, zz;
  double a, b, c, d, del, dely, scale;
  double y1 = 1.0;
  const double beta   = (double) (ibeta);
  const double albeta = log (beta);
  double ait = (double) (it);
  double xn  = (double) (n);
  const double alxmax = log (xmax);

  
  scale = 1.0;
  j     = (it + 1) / 2;
  for ( i = 1; i <= j; i ++ )
    {
      scale = scale * beta;
    }
  a    = 1.0 / beta;
  b    = 1.0;
  c    = max (alxmax, log (xmin)) / log (100.0);
  dely = - c - c;
/*
 *---------------------------------------------------------------------
 * RANDOM   ARGUMENT   ACCURACY   TESTS
 *---------------------------------------------------------------------
 */
  for ( j = 1; j <= 4; j ++ )
    {
      k1  = 0;
      k3  = 0;
      x1  = 0.0;
      r6  = 0.0;
      r7  = 0.0;
      del = (b - a) / xn;
      xl  = a;
      for ( i = 1; i <= n; i ++ )
        {
          x = del * ran () + xl;
          switch ( j )
            {
              case 1:
                zz = pow (x, 1.0);
                z  = x;
                break;
              case 2: case 3:
                w   = scale * x;
                x   = force(x + w) - w;
                xsq = x * x;
                zz  = pow (xsq, 1.5);
                z   = x * xsq;
                break;
              case 4:
                w   = scale * x;
                x   = force(x + w) - w;
                xsq = x * x;
                y   = dely * ran () + c;
                y2  = (y / 2.0 + y) - y;
                y   = y2 + y2;
                z   = pow (x, y);
                zz  = pow (xsq, y2);
                break;
            }
          w = 1.0;
          if ( z != 0.0 )
            {
              w = (z - zz) / z;
            }
          if ( w > 0.0 ) k1++;
          if ( w < 0.0 ) k3++;
          w = fabs (w);
          if ( w > r6 )
            {
              r6 = w;
              x1 = x;
              if ( j == 4 )
                {
                  y1 = y;
                }
            }
          else
            {
              r7 = r7 + w * w;
              xl = xl + del;
            }
        }
      k2 = n - k3 - k1;
      r7 = sqrt (r7 / xn);

      switch ( j )
        {
          case 1:
            printf ("TEST OF X ** 1.0 VS X");
            printf ("\n\n");
            printf ("%d", n);
            printf (" RANDOM ARGUMENTS WERE TESTED FROM THE INTERVAL");
            printf ("\n");
            printf ("       (");
            printf ("%.14e", a);
            printf (", ");
            printf ("%.14e", b);
            printf (")");
            printf ("\n");
            printf ("X ** 1.0 WAS LARGER ");
            break;
          case 2: case 3:
            printf ("TEST OF XSQ ** 1.5 VS XSQ * X");
            printf ("\n\n");
            printf ("%d", n);
            printf (" RANDOM ARGUMENTS WERE TESTED FROM THE INTERVAL");
            printf ("\n");
            printf ("      (");
            printf ("%.14e", a);
            printf (", ");
            printf ("%.14e", b);
            printf (")");
            printf ("\n");
            printf ("X ** 1.5 WAS LARGER ");
            break;
          case 4:
            printf ("TEST OF XSQ ** 1.5 VS XSQ ** Y/2");
            printf ("\n\n");
            d = c + dely;
            printf ("%d", n);
            printf (" RANDOM ARGUMENTS WERE TESTED FROM THE REGION");
            printf ("\n");
            printf ("X IN ");
            printf ("%.14e", a);
            printf (", ");
            printf ("%.14e", b);
            printf ("\n");
            printf ("Y IN ");
            printf ("%.14e", c);
            printf (", ");
            printf ("%.14e", d);
            printf ("\n");
            printf ("X ** Y   WAS LARGER ");
            break;
        }
      printf ("%6d", k1);
      printf (" TIMES");
      printf ("\n");
      printf ("             AGREED ");
      printf ("%6d", k2);
      printf (" TIMES");
      printf ("\n");
      printf ("        WAS SMALLER ");
      printf ("%6d", k3);
      printf (" TIMES");

      printf ("THERE ARE ");
      printf ("%4d", it);
      printf (" BASE ");
      printf ("%4d", ibeta);
      printf (" SIGNIFICANT DIGITS IN A FLOATING-POINT NUMBER");
      printf ("\n");
      w = - 999.0;
      if ( r6 != 0.0 )
        {
          w = log (fabs (r6)) / albeta;
        }
      printf ("THE MAXIMUM RELATIVE ERROR OF ");
      printf ("%10.4e", r6);
      printf (" = ");
      printf ("%4d", ibeta);
      printf (" ** ");
      printf ("%7.2f", w);
      printf ("\n");
      printf (" OCCURED FOR X = ");
      printf ("%.14e", x1);
      switch ( j )
        {
          case 1: case 2: case 3:
            printf ("\n");
            break;
          case 4:
            printf (", Y = ");
            printf ("%.14e", y1);
            printf ("\n");
            break;
        }
      w = max (ait + w, 0.0);
      printf ("THE ESTIMATED LOSS OF BASE ");
      printf ("%4d", ibeta);
      printf (" SIGNIFICANT DIGITS IS");
      printf ("%7.2f", w);
      printf ("\n\n");
      w = - 999.0;
      if ( r7 != 0.0 )
        {
          w = log (fabs (r7)) / albeta;
        }
      printf ("THE ROOT MEAN SQUARE RELATIVE ERROR WAS ");
      printf ("%10.4e", r7);
      printf (" = ");
      printf ("%4d", ibeta);
      printf (" ** ");
      printf ("%7.2f", w);
      printf ("\n");
      w = max (ait + w, 0.0);
      printf ("THE ESTIMATED LOSS OF BASE ");
      printf ("%4d", ibeta);
      printf (" SIGNIFICANT DIGITS IS");
      printf ("%7.2f", w);
      printf ("\n\n");
      switch ( j )
        {
          case 1:
            /*null*/
            break;
          case 2: case 4:
            a = 1.0;
            b = exp (alxmax / 3.0);
            break;
          case 3:
            b = 10.0;
            a = 0.01;
            break;
        }
    }
/*
 *----------------------------------------------------------------------
 *    SPECIAL   TESTS
 *----------------------------------------------------------------------
 */

  printf ("SPECIAL TESTS\n");

  printf ("THE IDENTITY X ** Y = (1/X) ** (-Y) WILL BE TESTED");
  printf ("\n");
  b = 10.0;
  for ( i = 1; i <= 5; i ++ )
    {
      x  = ran () * b + 1.0;
      y  = ran () * b + 1.0;
      z  = pow (x, y);
      zz = pow ((1.0 / x), (- y));
      w  = (z - zz) / z;
      printf ("%.14e", x);
      printf ("  ");
      printf ("%.14e", y);
      printf ("  ");
      printf ("%.14e", w);
      printf ("\n");
    }
/*
 *------------------------------------------------------------------------
 *  TEST   OF   ERROR   RETURNS\n
 *------------------------------------------------------------------------
 */

  printf ("TEST OF ERROR RETURNS\n\n");
  printf ("\n\n");
  x = beta;
  y = (double) (minexp);
  printf ("%.14e", x);
  printf (" ** ");
  printf ("%.14e", y);
  printf (" WILL BE COMPUTED");
  printf ("\n");
  printf ("THIS SHOULD NOT TRIGGER AN ERROR MESSAGE");
  printf ("\n\n");
  z = pow (x, y);
  printf ("THE VALUE RETURNED IS ");
  printf ("%.14e", z);
  printf ("\n");
  y = (double) (maxexp - 1);
  printf ("%.14e", x);
  printf (" ** ");
  printf ("%.14e", y);
  printf (" WILL BE COMPUTED");
  printf ("\n");
  printf ("THIS SHOULD NOT TRIGGER AN ERROR MESSAGE");
  printf ("\n\n");
  z = pow (x, y);
  printf ("THE VALUE RETURNED IS ");
  printf ("%.14e", z);
  printf ("\n");
  x = 0.0;
  y = 2.0;
  printf ("%.14e", x);
  printf (" ** ");
  printf ("%.14e", y);
  printf (" WILL BE COMPUTED");
  printf ("\n");
  printf ("THIS SHOULD NOT TRIGGER AN ERROR MESSAGE ");
  printf ("\n\n");
  z = pow (x, y);
  printf ("THE VALUE RETURNED IS ");
  printf ("%.14e", z);
  printf ("\n");
  x = - 2.0;
  y = 0.0;
  printf ("%.14e", x);
  printf (" ** ");
  printf ("%.14e", y);
  printf (" WILL BE COMPUTED");
  printf ("\n");
  printf ("THIS SHOULD TRIGGER AN ERROR MESSAGE");
  printf ("\n\n");
  z = pow (x, y);
  printf ("THE VALUE RETURNED IS ");
  printf ("%.14e", z);
  printf ("\n");
  x = - 2.0;
  y = 2.0;
  printf ("%.14e", x);
  printf (" ** ");
  printf ("%.14e", y);
  printf (" WILL BE COMPUTED");
  printf ("\n");
  printf ("THIS SHOULD TRIGGER AN ERROR MESSAGE");
  printf ("\n\n");
  z = pow (x, y);
  printf ("THE VALUE RETURNED IS ");
  printf ("%.14e", z);
  printf ("\n");
  x = 0.0;
  y = 0.0;
  printf ("%.14e", x);
  printf (" ** ");
  printf ("%.14e", y);
  printf (" WILL BE COMPUTED");
  printf ("\n");
  printf ("THIS SHOULD TRIGGER AN ERROR MESSAGE");
  printf ("\n\n");
  z = pow (x, y);
  printf ("THE VALUE RETURNED IS ");
  printf ("%.14e", z);
  printf ("\n");
  printf ("THIS CONCLUDES THE TESTS\n");
}
/*test_power*/


/*
 *::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
 *TESTSIN
 *::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
 */
void
test_sin_cos (void)
{
  int    n = 2000;
  int    i, j, k1, k2, k3;
  double r6, r7;
  double w, x, xl, y, z, zz;
  double x1;
  double a, b, c, d, del;
  const double beta   = (double) (ibeta);
  const double albeta = log (beta);
  double betap = powi (beta, it);
  double ait   = (double) (it);
  double xn    = (double) (n);

  
  a = 0.0;
  b = 1.57079632679489661923;
  c = b;
/*
 *---------------------------------------------------------
 *               RANDOM ARGUMENT TESTS
 *---------------------------------------------------------
 */
  for ( j = 1; j <= 3; j ++ )
    {
      k1  = 0;
      k3  = 0;
      x1  = 0.0;
      r6  = 0.0;
      r7  = 0.0;
      del = (b - a) / xn;
      xl  = a;
      for ( i = 1; i <= n; i ++ )
        {
          x = del * ran () + xl;
  /*
   *---------------------------------------------------------
   *                      PURIFY ARGUMENTS
   *---------------------------------------------------------
   */
          y = x / 3.0;
          y = force(x + y) - x;
          x = 3.0 * y;
          switch ( j )
            {
              case 1: case 2:
                z  = sin (x);
                zz = sin (y);
                if ( z == 0.0 )
                  {
                    w = 1.0;
                  }
                else
                  {
                    w = (z - zz * (3.0 - 4.0 * zz * zz)) / z;
                  }
                break;
              case 3:
                z  = cos (x);
                zz = cos (y);
                if ( z == 0.0 )
                  {
                    w = 1.0;
                  }
                else
                  {
                    w = (z + zz * (3.0 - 4.0 * zz * zz)) / z;
                  }
                break;
            }
          if ( w > 0.0 ) k1++;
          if ( w < 0.0 ) k3++;
          w = fabs (w);
          if ( w > r6 )
            {
              r6 = w;
              x1 = x;
            }
          r7 = r7 + w * w;
          xl = xl + del;
        }
      k2 = n - k1 - k3;
      r7 = sqrt (r7 / xn);

      switch ( j )
        {
          case 1: case 2:
            printf (" TEST OF SIN(X) VS 3*SIN(X/3) - 4*SIN(X/3)**3 ");
      
            printf ("%d", n);
            printf (" RANDOM ARGUMENTS WERE TESTED FROM THE INTERVAL ");
            printf ("\n");
            printf ("      (");
            printf ("%.14e", a);
            printf (",");
            printf ("%.14e", b);
            printf (")");
            printf ("\n");
            printf ("   SIN(X) WAS LARGER  ");
            printf ("%d", k1);
            printf (" TIMES");
            printf ("\n");
            printf ("              AGREED  ");
            printf ("%d", k2);
            printf (" TIMES");
            printf ("\n");
            printf ("         WAS SMALLER  ");
            printf ("%d", k3);
            printf (" TIMES");
            printf ("\n");
            printf ("\n");
            printf ("\n");
            break;
          case 3:
            printf (" TEST OF COS(X) VS 4*COS(X/3)**3 - 3*COS(X/3) ");
      
            printf ("%d", n);
            printf (" RANDOM ARGUMENTS WERE TESTED FROM THE INTERVAL ");
            printf ("\n");
            printf ("      (");
            printf ("%.14e", a);
            printf (",");
            printf ("%.14e", b);
            printf (")");
            printf ("\n");
            printf ("   COS(X) WAS LARGER  ");
            printf ("%6d", k1);
            printf (" TIMES");
            printf ("\n");
            printf ("              AGREED  ");
            printf ("%6d", k2);
            printf (" TIMES");
            printf ("\n");
            printf ("          WAS SMALLER ");
            printf ("%6d", k3);
            printf (" TIMES");
      
            break;
        }
      printf (" THERE ARE ");
      printf ("%4d", it);
      printf (" BASE ");
      printf ("%4d", ibeta);
      printf (" SIGNIFICANT DIGITS IN A FLOATING-POINT NUMBER");

      w = - 999.0e0;
      if ( (r6 != 0.0) )
        {
          w = log (fabs (r6)) / albeta;
        }
      printf (" THE MAXIMUM RELATIVE ERROR OF ");
      printf ("%10.4e", r6);
      printf (" = ");
      printf ("%4d", ibeta);
      printf (" **");
      printf ("%7.2f", w);
      printf ("\n");
      printf ("    OCCURED FOR X = ");
      printf ("%15.9e", x1);
      printf ("\n");
      w = max (ait + w, 0.0);
      printf (" THE ESTIMATED LOSS OF BASE ");
      printf ("%4d", ibeta);
      printf (" SIGNIFICANT DIGITS IS ");
      printf ("%7.2f", w);
      printf ("\n\n");
      w = - 999.0e0;
      if ( (r7 != 0.0) )
        {
          w = log (fabs (r7)) / albeta;
        }
      printf (" THE ROOT MEAN SQUARE RELATIVE ERROR WAS ");
      printf ("%10.4e", r7);
      printf (" = ");
      printf ("%4d", ibeta);
      printf (" **");
      printf ("%7.2f", w);
      printf ("\n");
      w = max (ait + w, 0.0);
      printf (" THE ESTIMATED LOSS OF BASE ");
      printf ("%4d", ibeta);
      printf (" SIGNIFICANT DIGITS IS ");
      printf ("%7.2f", w);
      printf ("\n\n");
      a = 18.84955592;
      if ( j == 2 )
        {
          a = b + c;
        }
      b = a + c;
    }
/*
 *----------------------------------------------------------
 *               SPECIAL TESTS
 *----------------------------------------------------------
 */

  printf (" SPECIAL TESTS\n");

  c = 1.0 / powi (beta, it / 2);
  z = (sin (a + c) - sin (a - c)) / (c + c);
  printf (" IF ");
  printf ("%.14e", z);
  printf (" IS NOT ALMOST 1.0,    SIN HAS THE WRONG PERIOD. ");

  printf (" THE IDENTITY    SIN(-X) = -SIN(X)    WILL BE TESTED.");

  printf ("        X         F(X) + F(-X)");
  printf ("\n\n");
  for ( i = 1; i <= 5; i ++ )
    {
      x = ran () * a;
      z = sin (x) + sin (- x);
      printf ("%.14e", x);
      printf ("    ");
      printf ("%.14e", z);
      printf ("\n");
    }
  printf ("\n\n");
  printf (" THE IDENTITY   SIN(X) = X   X SMALL, WILL BE TESTED");
  printf ("\n\n");
  printf ("         X         X - F(X)");
  printf ("\n");
  x = ran () / betap;
  for ( i = 1; i <= 5; i ++ )
    {
      z = x - sin (x);
      printf ("%.14e", x);
      printf ("    ");
      printf ("%.14e", z);
      printf ("\n");
      x = x / beta;
    }

  printf (" THE IDENTITY   COS(-X) = COS(X)   WILL BE TESTED");
  printf ("\n\n");
  printf ("        X         F(X) - F(-X)");
  printf ("\n\n");
  for ( i = 1; i <= 5; i ++ )
    {
      x = ran () * a;
      z = cos (x) - cos (- x);
      printf ("%.14e", x);
      printf ("    ");
      printf ("%.14e", z);
      printf ("\n");
    }

  printf (" TEST OF UNDERFLOW FOR VERY SMALL ARGUMENT. ");
  printf ("\n");
  x = powi (beta, - it);
  y = sin (x);
  printf ("\n");
  printf ("       SIN(");
  printf ("%.14e", x);
  printf (") = ");
  printf ("%.14e", y);
  printf ("\n");
  printf (" THE FOLLOWING 3 LINES ILLUSTRATE THE LOSS IN SIGNIFICANCE");
  printf ("\n");
  printf (" FOR LARGE ARGUMENTS. ");
  printf (" THE ARGUMENTS ARE CONSECUTIVE.");
  printf ("\n");
  z = sqrt (betap);
  x = z * (1.0 - epsneg);
  y = sin (x);
  printf ("       SIN(");
  printf ("%.14e", x);
  printf (") = ");
  printf ("%.14e", y);
  printf ("\n");
  y = sin (z);
  printf ("       SIN(");
  printf ("%.14e", x);
  printf (") = ");
  printf ("%.14e", y);
  printf ("\n");
  x = z * (1.0 + eps);
  y = sin (x);
  printf ("       SIN(");
  printf ("%.14e", x);
  printf (") = ");
  printf ("%.14e", y);
  printf ("\n");
/*
 *----------------------------------------------------------
 *               TESTS OF ERROR RETURNS\n
 *----------------------------------------------------------
 */

  printf (" TEST OF ERROR RETURNS\n\n");

  x = betap;
  printf (" SIN WILL BE CALLED WITH THE ARGUMENT ");
  printf ("%.14e", x);
  printf ("\n");
  printf (" THIS SHOULD TRIGGER AN ERROR MESSAGE");
  printf ("\n");
  y = sin (x);
  printf (" SIN RETURNED THE VALUE ");
  printf ("%.14e", y);
  printf ("\n");
  printf (" THIS CONCLUDES THE TESTS");
  printf ("\n");
}
/*test_sin_cos*/


/*
 *::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
 *TESTTAN
 *::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
 */
void
test_tan_cot (void)
{
  int    n = 2000;
  int    i, j, k1, k2, k3;
  double r6, r7;
  double w, x, xl, y, z, zz;
  double x1;
  double a, b, c, d, del;
  double beta   = (double) (ibeta);
  double albeta = log (beta);
  double betap  = powi (beta, it);
  double ait    = (double) (it);
  double xn     = (double) (n);
  const double pi = 3.14159265358979323846;

  
  a = 0.0;
  b = pi * 0.25;
/*
 *---------------------------------------------------------
 *               RANDOM ARGUMENT TESTS
 *---------------------------------------------------------
 */
  for ( j = 1; j <= 4; j ++ )
    {
      k1  = 0;
      k3  = 0;
      x1  = 0.0;
      r6  = 0.0;
      r7  = 0.0;
      del = (b - a) / xn;
      xl  = a;
      for ( i = 1; i <= n; i ++ )
        {
          x = del * ran () + xl;
  /*
   *---------------------------------------------------------
   *                      PURIFY ARGUMENTS
   *---------------------------------------------------------
   */
          y = x * 0.5;
          x = y + y;
          switch ( j )
            {
              case 1: case 2: case 3:
                z  = tan (x);
                zz = tan (y);
                if ( z == 0.0 )
                  {
                    w = 1.0;
                  }
                else
                  {
                    w = ((0.5 - zz) + 0.5) * ((0.5 + zz) + 0.5);
                    w = (z - (zz + zz) / w) / z;
                  }
                break;
              case 4:
                z  = cot (x);
                zz = cot (y);
                if ( z == 0.0 )
                  {
                    w = 1.0;
                  }
                else
                  {
                    w = ((0.5 - zz) + 0.5) * ((0.5 + zz) + 0.5);
                    w = (z + w / (zz + zz)) / z;
                  }
                break;
            }
          if ( w > 0.0 ) k1++;
          if ( w < 0.0 ) k3++;
          w = fabs (w);
          if ( w > r6 )
            {
              r6 = w;
              x1 = x;
            }
          r7 = r7 + w * w;
          xl = xl + del;
        }
      k2 = n - k1 - k3;
      r7 = sqrt (r7 / xn);

      switch ( j )
        {
          case 1: case 2: case 3:
            printf (" TEST OF TAN(X) VS 2*TAN(X/2) / (1-TAN(X/2)**2) ");
      
            printf ("%d", n);
            printf (" RANDOM ARGUMENTS WERE TESTED FROM THE INTERVAL ");
            printf ("\n");
            printf ("      (");
            printf ("%.14e", a);
            printf (",");
            printf ("%.14e", b);
            printf (")");
            printf ("\n");
            printf ("   TAN(X) WAS LARGER  ");
            printf ("%d", k1);
            printf (" TIMES");
            printf ("\n");
            printf ("              AGREED  ");
            printf ("%d", k2);
            printf (" TIMES");
            printf ("\n");
            printf ("          WAS SMALLER ");
            printf ("%d", k3);
            printf (" TIMES");
      
            break;
          case 4:
            printf (" TEST OF COT(X) VS (COT(X/2)**2-1) / (2*COT(X/2)) ");
      
            printf ("%d", n);
            printf (" RANDOM ARGUMENTS WERE TESTED FROM THE INTERVAL ");
            printf ("\n");
            printf ("      (");
            printf ("%.14e", a);
            printf (",");
            printf ("%.14e", b);
            printf (")");
            printf ("\n");
            printf ("   COT(X) WAS LARGER  ");
            printf ("%d", k1);
            printf (" TIMES");
            printf ("\n");
            printf ("              AGREED  ");
            printf ("%d", k2);
            printf (" TIMES");
            printf ("\n");
            printf ("          WAS SMALLER ");
            printf ("%d", k3);
            printf (" TIMES");
            printf ("\n");
            printf ("\n");
            printf ("\n");
            break;
        }
      printf (" THERE ARE ");
      printf ("%4d", it);
      printf (" BASE ");
      printf ("%4d", ibeta);
      printf (" SIGNIFICANT DIGITS IN A FLOATING-POINT NUMBER");

      w = - 999.0e0;
      if ( (r6 != 0.0) )
        {
          w = log (fabs (r6)) / albeta;
        }
      printf (" THE MAXIMUM RELATIVE ERROR OF ");
      printf ("%10.4e", r6);
      printf (" = ");
      printf ("%4d", ibeta);
      printf (" **");
      printf ("%7.2f", w);
      printf ("\n");
      printf ("    OCCURED FOR X = ");
      printf ("%.14e", x1);
      printf ("\n");
      w = max (ait + w, 0.0);
      printf (" THE ESTIMATED LOSS OF BASE ");
      printf ("%4d", ibeta);
      printf (" SIGNIFICANT DIGITS IS ");
      printf ("%7.2f", w);
      printf ("\n\n");
      w = - 999.0e0;
      if ( (r7 != 0.0) )
        {
          w = log (fabs (r7)) / albeta;
        }
      printf (" THE ROOT MEAN SQUARE RELATIVE ERROR WAS ");
      printf ("%10.4e", r7);
      printf (" = ");
      printf ("%4d", ibeta);
      printf (" **");
      printf ("%7.2f", w);
      printf ("\n");
      w = max (ait + w, 0.0);
      printf (" THE ESTIMATED LOSS OF BASE ");
      printf ("%4d", ibeta);
      printf (" SIGNIFICANT DIGITS IS ");
      printf ("%7.2f", w);
      printf ("\n\n");
      if ( j == 1 )
        {
          a = pi * 0.875;
          b = pi * 1.125;
        }
      else
        {
          a = pi * 6.0;
          b = a + pi * 0.25;
        }
    }
/*
 *----------------------------------------------------------
 *               SPECIAL TESTS
 *----------------------------------------------------------
 */

  printf (" SPECIAL TESTS\n");

  printf (" THE IDENTITY    TAN(-X) = -TAN(X)    WILL BE TESTED.");
  printf ("\n\n");
  printf ("        X         F(X) + F(-X)");
  printf ("\n\n");
  for ( i = 1; i <= 5; i ++ )
    {
      x = ran () * a;
      z = tan (x) + tan (- x);
      printf ("%.14e", x);
      printf ("    ");
      printf ("%.14e", z);
      printf ("\n");
    }

  printf (" THE IDENTITY    TAN(X) = X   X SMALL   WILL BE TESTED.");
  printf ("\n\n");
  printf ("        X         X - F(X) ");
  printf ("\n\n");
  x = ran () / betap;
  for ( i = 1; i <= 5; i ++ )
    {
      z = x - tan (x);
      printf ("%.14e", x);
      printf ("    ");
      printf ("%.14e", z);
      printf ("\n");
      x = x / beta;
    }

  printf (" TEST OF UNDERFLOW FOR VERY SMALL ARGUMENT. ");
  printf ("\n");
  x = powi (beta, (minexp * 3) / 4);
  y = tan (x);
  printf ("       TAN(");
  printf ("%.14e", x);
  printf (") = ");
  printf ("%.14e", y);
  printf ("\n");
  a = - 225.0;
  b = - 0.950846454195142026;
  x = 11.0;
  y = tan (x);
  w = ((a - y) + b) / (a + b);
  z = log (fabs (w)) / albeta;
  printf (" THE RELATIVE ERROR IN TAN(11) IS ");
  printf ("%10.4e", w);
  printf (" = ");
  printf ("%4d", ibeta);
  printf (" **");
  printf ("%7.2f", z);
  printf (" WHERE ");
  printf ("\n");
  printf ("       TAN(");
  printf ("%.14e", x);
  printf (") = ");
  printf ("%.14e", y);
  printf ("\n");
  w = max (ait + z, 0.0);
  printf (" THE ESTIMATED LOSS OF BASE ");
  printf ("%4d", ibeta);
  printf (" SIGNIFICANT DIGITS IS ");
  printf ("%7.2f", w);
  printf ("\n\n");
/*
 *----------------------------------------------------------
 *               TESTS OF ERROR RETURNS\n
 *----------------------------------------------------------
 */

  printf (" TEST OF ERROR RETURNS\n");

  x = powi (beta, it / 2);
  printf (" TAN WILL BE CALLED WITH THE ARGUMENT ");
  printf ("%.14e", x);
  printf ("\n");
  printf (" THIS SHOULD NOT TRIGGER AN ERROR MESSAGE");
  printf ("\n");
  y = tan (x);
  printf ("\n");
  printf (" TAN RETURNED THE VALUE ");
  printf ("%.14e", y);
  printf ("\n");
  x = betap;
  printf (" TAN WILL BE CALLED WITH THE ARGUMENT ");
  printf ("%.14e", x);
  printf ("\n");
  printf (" THIS SHOULD TRIGGER AN ERROR MESSAGE");
  printf ("\n");
  y = tan (x);
  printf ("\n");
  printf (" TAN RETURNED THE VALUE ");
  printf ("%.14e", y);
  printf ("\n");
  printf (" THIS CONCLUDES THE TESTS");
  printf ("\n");
}
/*test_tan_cot*/


/*
 *::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
 *TESTASIN
 *::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
 */
void
test_asin_acos (void)
{
  int    n = 2000;
  int    i, j, k1, k2, k3, m;
  double r6, r7;
  double w, x, xl, y, z, zz;
  double x1;
  double a, b, c, d, del;
  enum routine
    {f_asin, f_acos}
  l;
  double sum, xm, ysq, s;
  double c1, c2;
  double beta   = (double) (ibeta);
  double albeta = log (beta);
  double betap  = powi (beta, it);
  double ait    = (double) (it);
  double xn     = (double) (n);
  int    k      = iround (log10 (powi (beta, it)) + 0.5) + 1;

  
/*
 *---------------------------------------------------------
 *               RANDOM ARGUMENT TESTS
 *---------------------------------------------------------
 */
  for ( j = 1; j <= 5; j ++ )
    {
      k1 = 0;
      k3 = 0;
      x1 = 0.0;
      r6 = 0.0;
      r7 = 0.0;
      switch ( j )
        {
          case 1:
            a  = - 0.125;
            b  = 0.125;
            c1 = 201.0 / 128.0;
            c2 = 4.8382679489661923132e-4;
            l  = f_asin;
            break;
          case 2:
            a = - 0.125;
            b = 0.125;
            l = f_acos;
            break;
          case 3:
            a = 0.75;
            b = 1.00;
            l = f_asin;
            break;
          case 4:
            a = 0.75;
            b = 1.00;
            l = f_acos;
            break;
          case 5:
            a  = - 1.00;
            b  = - 0.75;
            c1 = c1 + c1;
            c2 = c2 + c2;
            l  = f_acos;
            break;
        }
      del = (b - a) / xn;
      xl  = a;
      for ( i = 1; i <= n; i ++ )
        {
          x = del * ran () + xl;
          switch ( j )
            {
              case 1: case 2:
                y   = x;
                ysq = y * y;
                break;
              case 3: case 4:
                ysq = 0.5 - 0.5 * fabs (x);
                x   = (0.5 - (ysq + ysq)) + 0.5;
                y   = sqrt (ysq);
                y   = y + y;
                break;
              case 5:
                ysq = 0.5 - 0.5 * fabs (x);
                x   = (0.5 - (ysq + ysq)) + 0.5;
                x   = - x;
                y   = sqrt (ysq);
                y   = y + y;
                break;
            }
          sum = 0.0;
          xm  = (double) (k + k + 1);
          switch ( l )
            {
              case f_asin:
                z = asin (x);
                break;
              case f_acos:
                z = acos (x);
                break;
            }
          for ( m = 1; m <= k; m ++ )
            {
              sum = ysq * (sum + 1.0 / xm);
              xm  = xm - 2.0;
              sum = sum * (xm / (xm + 1.0));
            }
          sum = sum * y;
          switch ( j )
            {
              case 1: case 4:
                zz  = y + sum;
                sum = (y - zz) + sum;
                break;
              case 2: case 3: case 5:
                s   = c1 + c2;
                sum = ((c1 - s) + c2) - sum;
                zz  = s + sum;
                sum = ((s - zz) + sum) - y;
                s   = zz;
                zz  = s + sum;
                sum = (s - zz) + sum;
                break;
            }
          if ( irnd != 1 )
            {
              zz = zz + (sum + sum);
            }
          w = 1.0;
          if ( z != 0.0 )
            {
              w = (z - zz) / z;
            }
          if ( w > 0.0 ) k1++;
          if ( w < 0.0 ) k3++;
          w = fabs (w);
          if ( w > r6 )
            {
              r6 = w;
              x1 = x;
            }
          r7 = r7 + w * w;
          xl = xl + del;
        }
      k2 = n - k1 - k3;
      r7 = sqrt (r7 / xn);

      switch ( l )
        {
          case f_asin:
            printf (" TEST OF ASIN(X) VS TAYLOR SERIES ");
      
            printf ("%d", n);
            printf (" RANDOM ARGUMENTS WERE TESTED FROM THE INTERVAL ");
            printf ("\n");
            printf ("      (");
            printf ("%.14e", a);
            printf (",");
            printf ("%.14e", b);
            printf (")");
            printf ("\n");
            printf ("   ASIN(X) WAS LARGER  ");
            printf ("%d", k1);
            printf (" TIMES");
            printf ("\n");
            printf ("               AGREED  ");
            printf ("%d", k2);
            printf (" TIMES");
            printf ("\n");
            printf ("          WAS SMALLER  ");
            printf ("%d", k3);
            printf (" TIMES");
      
            break;
          case f_acos:
            printf (" TEST OF ACOS(X) VS TAYLOR SERIES ");
      
            printf ("%d", n);
            printf (" RANDOM ARGUMENTS WERE TESTED FROM THE INTERVAL ");
            printf ("\n");
            printf ("      (");
            printf ("%.14e", a);
            printf (",");
            printf ("%.14e", b);
            printf (")");
            printf ("\n");
            printf ("   ACOS(X) WAS LARGER  ");
            printf ("%d", k1);
            printf (" TIMES");
            printf ("\n");
            printf ("               AGREED  ");
            printf ("%d", k2);
            printf (" TIMES");
            printf ("\n");
            printf ("          WAS SMALLER  ");
            printf ("%d", k3);
            printf (" TIMES");
      
            break;
        }
      printf (" THERE ARE ");
      printf ("%4d", it);
      printf (" BASE ");
      printf ("%4d", ibeta);
      printf (" SIGNIFICANT DIGITS IN A FLOATING-POINT NUMBER");

      w = - 999.0e0;
      if ( (r6 != 0.0) )
        {
          w = log (fabs (r6)) / albeta;
        }
      printf (" THE MAXIMUM RELATIVE ERROR OF ");
      printf ("%10.4e", r6);
      printf (" = ");
      printf ("%4d", ibeta);
      printf (" **");
      printf ("%7.2f", w);
      printf ("\n");
      printf ("    OCCURED FOR X = ");
      printf ("%.14e", x1);
      printf ("\n");
      w = max (ait + w, 0.0);
      printf (" THE ESTIMATED LOSS OF BASE ");
      printf ("%4d", ibeta);
      printf (" SIGNIFICANT DIGITS IS ");
      printf ("%7.2f", w);
      printf ("\n\n");
      w = - 999.0e0;
      if ( (r7 != 0.0) )
        {
          w = log (fabs (r7)) / albeta;
        }
      printf (" THE ROOT MEAN SQUARE RELATIVE ERROR WAS ");
      printf ("%10.4e", r7);
      printf (" = ");
      printf ("%4d", ibeta);
      printf (" **");
      printf ("%7.2f", w);
      printf ("\n");
      w = max (ait + w, 0.0);
      printf (" THE ESTIMATED LOSS OF BASE ");
      printf ("%4d", ibeta);
      printf (" SIGNIFICANT DIGITS IS ");
      printf ("%7.2f", w);
      printf ("\n\n");
    }
/*
 *----------------------------------------------------------
 *               SPECIAL TESTS
 *----------------------------------------------------------
 */

  printf (" SPECIAL TESTS\n");

  printf (" THE IDENTITY    ASIN(-X) = -ASIN(X)    WILL BE TESTED.");
  printf ("\n\n");
  printf ("        X         F(X) + F(-X)");
  printf ("\n\n");
  for ( i = 1; i <= 5; i ++ )
    {
      x = ran () * a;
      z = asin (x) + asin (- x);
      printf ("%.14e", x);
      printf ("    ");
      printf ("%.14e", z);
      printf ("\n");
    }

  printf (" THE IDENTITY    ASIN(X) = X   X SMALL   WILL BE TESTED.");
  printf ("\n\n");
  printf ("        X         X - F(X) ");
  printf ("\n\n");
  x = ran () / betap;
  for ( i = 1; i <= 5; i ++ )
    {
      z = x - asin (x);
      printf ("%.14e", x);
      printf ("    ");
      printf ("%.14e", z);
      printf ("\n");
      x = x / beta;
    }

  printf (" TEST OF UNDERFLOW FOR VERY SMALL ARGUMENT. ");
  printf ("\n");
  x = powi (beta, (minexp * 3) / 4);
  y = asin (x);
  printf ("       ASIN(");
  printf ("%.14e", x);
  printf (") = ");
  printf ("%.14e", y);
  printf ("\n");
/*
 *----------------------------------------------------------
 *               TESTS OF ERROR RETURNS\n
 *----------------------------------------------------------
 */

  printf (" TEST OF ERROR RETURNS\n");

  x = 1.2;
  printf (" ASIN WILL BE CALLED WITH THE ARGUMENT ");
  printf ("%.14e", x);
  printf ("\n");
  printf (" THIS SHOULD TRIGGER AN ERROR MESSAGE");
  printf ("\n");
  y = asin (x);
  printf ("\n");
  printf (" ASIN RETURNED THE VALUE ");
  printf ("%.14e", y);

  printf (" THIS CONCLUDES THE TESTS");
  printf ("\n");
}
/*test_asin_acos*/


/*
 *::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
 *TESTATAN
 *::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
 */
void
test_atan (void)
{
  int    n = 2000;
  int    i, j, k1, k2, k3, ii;
  double r6, r7;
  double w, x, xl, y, z, zz;
  double x1;
  double a, b, c, d, del;
  double sum, xsq, ob32, em;
  double beta   = (double) (ibeta);
  double albeta = log (beta);
  double betap  = powi (beta, it);
  double ait    = (double) (it);
  double xn     = (double) (n);

  
/*
 *---------------------------------------------------------
 *               RANDOM ARGUMENT TESTS
 *---------------------------------------------------------
 */
  for ( j = 1; j <= 4; j ++ )
    {
      k1 = 0;
      k3 = 0;
      x1 = 0.0;
      r6 = 0.0;
      r7 = 0.0;
      switch ( j )
        {
          case 1:
            a    = - 0.0625;
            b    = - a;
            ob32 = b * 0.5;
            break;
          case 2:
            a = b;
            b = 2.0 - sqrt (3.0);
            break;
          case 3:
            a = b;
            b = sqrt (2.0) - 1.0;
            break;
          case 4:
            a = b;
            b = 1.0;
            break;
        }
      del = (b - a) / xn;
      xl  = a;
      for ( i = 1; i <= n; i ++ )
        {
          x = del * ran () + xl;
          switch ( j )
            {
              case 1:
                z   = atan (x);
                xsq = x * x;
                em  = 17.0;
                sum = xsq / em;
                for ( ii = 1; ii <= 7; ii ++ )
                  {
                    em  = em - 2.0;
                    sum = (1.0 / em - sum) * xsq;
                  }
                sum = - x * sum;
                zz  = x + sum;
                sum = (x - zz) + sum;
                if ( irnd == 0 )
                  {
                    zz = zz + (sum + sum);
                  }
                break;
              case 2:
                x  = ((1.0 + x * a) - 1.0) * 16.0;
                z  = atan (x);
                y  = x - 0.0625;
                y  = y / (1.0 + x * a);
                zz = (atan (y) - 8.1190004042651526021e-5) + ob32;
                zz = zz + ob32;
                break;
              case 3: case 4:
                z  = atan (x);
                z  = z + z;
                y  = x / ((0.5 + x * 0.5) * ((0.5 - x) + 0.5));
                zz = atan (y);
                break;
            }
          w = 1.0;
          if ( z != 0.0 )
            {
              w = (z - zz) / z;
            }
          if ( w > 0.0 ) k1++;
          if ( w < 0.0 ) k3++;
          w = fabs (w);
          if ( w > r6 )
            {
              r6 = w;
              x1 = x;
            }
          r7 = r7 + w * w;
          xl = xl + del;
        }
      k2 = n - k1 - k3;
      r7 = sqrt (r7 / xn);

      switch ( j )
        {
          case 1:
            printf (" TEST OF ATAN(X) VS TRUNCATED TAYLOR SERIES ");
            break;
          case 2:
            printf (" TEST OF ATAN(X) VS ATAN(1/16) + ATAN((X-1/16)/(1+X/16))");
            break;
          case 3: case 4:
            printf (" TEST OF 2*ATAN(X) VS ATAN(2X/(1-X*X))");
            break;
        }

      printf ("%d", n);
      printf (" RANDOM ARGUMENTS WERE TESTED FROM THE INTERVAL ");
      printf ("\n");
      printf ("      (");
      printf ("%.14e", a);
      printf (",");
      printf ("%.14e", b);
      printf (")");
      printf ("\n");
      printf ("   ATAN(X) WAS LARGER  ");
      printf ("%d", k1);
      printf (" TIMES");
      printf ("\n");
      printf ("               AGREED  ");
      printf ("%d", k2);
      printf (" TIMES");
      printf ("\n");
      printf ("          WAS SMALLER  ");
      printf ("%d", k3);
      printf (" TIMES");

      printf (" THERE ARE ");
      printf ("%4d", it);
      printf (" BASE ");
      printf ("%4d", ibeta);
      printf (" SIGNIFICANT DIGITS IN A FLOATING-POINT NUMBER");

      w = - 999.0e0;
      if ( (r6 != 0.0) )
        {
          w = log (fabs (r6)) / albeta;
        }
      printf (" THE MAXIMUM RELATIVE ERROR OF ");
      printf ("%10.4e", r6);
      printf (" = ");
      printf ("%4d", ibeta);
      printf (" **");
      printf ("%7.2f", w);
      printf ("\n");
      printf ("    OCCURED FOR X = ");
      printf ("%.14e", x1);
      printf ("\n");
      w = max (ait + w, 0.0);
      printf (" THE ESTIMATED LOSS OF BASE ");
      printf ("%4d", ibeta);
      printf (" SIGNIFICANT DIGITS IS ");
      printf ("%7.2f", w);
      printf ("\n\n");
      w = - 999.0e0;
      if ( (r7 != 0.0) )
        {
          w = log (fabs (r7)) / albeta;
        }
      printf (" THE ROOT MEAN SQUARE RELATIVE ERROR WAS ");
      printf ("%10.4e", r7);
      printf (" = ");
      printf ("%4d", ibeta);
      printf (" **");
      printf ("%7.2f", w);
      printf ("\n");
      w = max (ait + w, 0.0);
      printf (" THE ESTIMATED LOSS OF BASE ");
      printf ("%4d", ibeta);
      printf (" SIGNIFICANT DIGITS IS ");
      printf ("%7.2f", w);
      printf ("\n\n");
    }
/*
 *----------------------------------------------------------
 *               SPECIAL TESTS
 *----------------------------------------------------------
 */

  printf (" SPECIAL TESTS\n");

  printf (" THE IDENTITY    ATAN(-X) = -ATAN(X)    WILL BE TESTED.");
  printf ("\n\n");
  printf ("        X         F(X) + F(-X)");
  printf ("\n\n");
  for ( i = 1; i <= 5; i ++ )
    {
      x = ran () * a;
      z = atan (x) + atan (- x);
      printf ("%.14e", x);
      printf ("    ");
      printf ("%.14e", z);
      printf ("\n");
    }

  printf (" THE IDENTITY    ATAN(X) = X   X SMALL   WILL BE TESTED.");
  printf ("\n\n");
  printf ("        X         X - F(X) ");
  printf ("\n\n");
  x = ran () / betap;
  for ( i = 1; i <= 5; i ++ )
    {
      z = x - atan (x);
      printf ("%.14e", x);
      printf ("    ");
      printf ("%.14e", z);
      printf ("\n");
      x = x / beta;
    }

  printf (" THE IDENTITY    ATAN(X/Y) = ATAN2(X,Y)    WILL BE TESTED");
  printf ("\n");
  printf (" THE FIRST COLUMN OF RESULTS SHOULD BE 0, THE SECOND +-PI");
  printf ("\n\n");
  printf ("        X              Y       ");
  printf ("F1(X/Y)-F2(X,Y)  F1(X/Y)-F2(X/(-Y))");
  printf ("\n\n");
  a = - 2.0;
  b = 4.0;
  for ( i = 1; i <= 5; i ++ )
    {
      x  = ran () * b + a;
      y  = ran ();
      w  = - y;
      z  = atan (x / y) - atan2 (x, y);
      zz = atan (x / w) - atan2 (x, w);
      printf ("%.14e", x);
      printf ("    ");
      printf ("%.14e", y);
      printf ("    ");
      printf ("%.14e", z);
      printf ("    ");
      printf ("%.14e", zz);
      printf ("\n");
    }

  printf (" TEST OF UNDERFLOW FOR VERY SMALL ARGUMENT. ");
  printf ("\n");
  x = powi (beta, (minexp * 3) / 4);
  y = atan (x);
  printf ("       ATAN(");
  printf ("%.14e", x);
  printf (") = ");
  printf ("%.14e", y);
  printf ("\n");
/*
 *----------------------------------------------------------
 *               TESTS OF ERROR RETURNS\n
 *----------------------------------------------------------
 */

  printf (" TEST OF ERROR RETURNS\n");

  x = xmax;
  printf (" ATAN WILL BE CALLED WITH THE ARGUMENT ");
  printf ("%.14e", x);
  printf ("\n");
  printf (" THIS SHOULD NOT TRIGGER AN ERROR MESSAGE");
  printf ("\n");
  z = atan (x);
  printf ("\n");
  printf (" ATAN RETURNED THE VALUE ");
  printf ("%.14e", z);
  printf ("\n");
  x = 1.0;
  y = 0.0;
  printf (" ATAN2 WILL BE CALLED WITH THE ARGUMENTS ");
  printf ("%.14e", x);
  printf ("    ");
  printf ("%.14e", y);
  printf ("\n");
  printf (" THIS SHOULD NOT TRIGGER AN ERROR MESSAGE");
  printf ("\n");
  z = atan2 (x, y);
  printf ("\n");
  printf (" ATAN2 RETURNED THE VALUE ");
  printf ("%.14e", z);
  printf ("\n");
  x = xmin;
  y = xmax;
  printf (" ATAN2 WILL BE CALLED WITH THE ARGUMENTS ");
  printf ("%.14e", x);
  printf ("    ");
  printf ("%.14e", y);
  printf ("\n");
  printf (" THIS SHOULD NOT TRIGGER AN ERROR MESSAGE");
  printf ("\n");
  z = atan2 (x, y);
  printf ("\n");
  printf (" ATAN2 RETURNED THE VALUE ");
  printf ("%.14e", z);
  printf ("\n");
  x = xmax;
  y = xmin;
  printf (" ATAN2 WILL BE CALLED WITH THE ARGUMENTS ");
  printf ("%.14e", x);
  printf ("    ");
  printf ("%.14e", y);
  printf ("\n");
  printf (" THIS SHOULD NOT TRIGGER AN ERROR MESSAGE");
  printf ("\n");
  z = atan2 (x, y);
  printf ("\n");
  printf (" ATAN2 RETURNED THE VALUE ");
  printf ("%.14e", z);
  printf ("\n");
  x = 0.0;
  y = 0.0;
  printf (" ATAN2 WILL BE CALLED WITH THE ARGUMENTS ");
  printf ("%.14e", x);
  printf ("    ");
  printf ("%.14e", y);
  printf ("\n");
  printf (" THIS SHOULD TRIGGER AN ERROR MESSAGE");
  printf ("\n");
  z = atan2 (x, y);
  printf ("\n");
  printf (" ATAN2 RETURNED THE VALUE ");
  printf ("%.14e", z);
  printf ("\n");
  printf (" THIS CONCLUDES THE TESTS");
  printf ("\n");
}
/*test_atan*/


/*
 *::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
 *TESTSINH
 *::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
 */
void
test_sinh_cosh (void)
{
  int    n = 2000;
  int    i, j, k1, k2, k3, ii;
  int    i2;
  double r6, r7;
  double w, x, xl, y, z, zz;
  double x1;
  double xn = (double) (n);
  double a, b, c, d, del;
  double den, xsq;
  int    nit    = 2 - itrunc (log (eps) * 3.0) / 20;
  double aind   = (double) (nit + nit + 1);
  double beta   = (double) (ibeta);
  double alxmax = log (xmax);
  double albeta = log (beta);
  double ait    = (double) (it);
  double betap  = powi (beta, it);
  double c0     = 5.0 / 16.0 + 1.152713683194269979e-2;

  
/*
 *---------------------------------------------------------
 *               RANDOM ARGUMENT TESTS
 *---------------------------------------------------------
 */
  for ( j = 1; j <= 4; j ++ )
    {
      k1 = 0;
      k3 = 0;
      x1 = 0.0;
      r6 = 0.0;
      r7 = 0.0;
      switch ( j )
        {
          case 1:
            a = 0.0;
            b = 0.5;
            break;
          case 2:
            a    = 0.0;
            b    = 0.5;
            aind = aind - 1.0;
            break;
          case 3: case 4:
            a = 3.0;
            b = alxmax;
            break;
        }
      del = (b - a) / xn;
      xl  = a;
      for ( i = 1; i <= n; i ++ )
        {
          x = del * ran () + xl;
          switch ( j )
            {
              case 1:
                xsq = x * x;
                zz  = 1.0;
                den = aind;
                for ( ii = 2; ii <= nit; ii ++ )
                  {
                    w   = zz * xsq / (den * (den - 1.0));
                    zz  = w + 1.0;
                    den = den - 2.0;
                  }
                w  = x * xsq * zz / 6.0;
                zz = x + w;
                z  = sinh (x);
                if ( irnd == 0 )
                  {
                    w  = (x - zz) + w;
                    zz = zz + (w + w);
                  }
                break;
              case 2:
                xsq = x * x;
                zz  = 1.0;
                den = aind;
                for ( ii = 1; ii <= nit; ii ++ )
                  {
                    w   = zz * xsq / (den * (den - 1.0));
                    zz  = w + 1.0;
                    den = den - 2.0;
                  }
                z = cosh (x);
                if ( irnd == 0 )
                  {
                    w  = (1.0 - zz) + w;
                    zz = zz + (w + w);
                  }
                break;
              case 3:
                y  = x;
                x  = y - 1.0;
                w  = x - 1.0;
                z  = sinh (x);
                zz = (sinh (y) + sinh (w)) * c0;
                break;
              case 4:
                y  = x;
                x  = y - 1.0;
                w  = x - 1.0;
                z  = cosh (x);
                zz = (cosh (y) + cosh (w)) * c0;
                break;
            }
          w = 1.0;
          if ( z != 0.0 )
            {
              w = (z - zz) / z;
            }
          if ( w > 0.0 ) k1++;
          if ( w < 0.0 ) k3++;
          w = fabs (w);
          if ( w > r6 )
            {
              r6 = w;
              x1 = x;
            }
          r7 = r7 + w * w;
          xl = xl + del;
        }
      k2 = n - k1 - k3;
      r7 = sqrt (r7 / xn);

      switch ( j )
        {
          case 1:
            printf (" TEST OF SINH(X) VS TAYLOR SERIES EXPANSION OF SINH(X) ");
            break;
          case 2:
            printf (" TEST OF COSH(X) VS TAYLOR SERIES EXPANSION OF COSH(X) ");
            break;
          case 3:
            printf (" TEST OF SINH(X) VS C * (SINH(X+1) + SINH(X-1)) ");
            break;
          case 4:
            printf (" TEST OF COSH(X) VS C * (COSH(X+1) + COSH(X-1)) ");
            break;
        }

      printf ("%d", n);
      printf (" RANDOM ARGUMENTS WERE TESTED FROM THE INTERVAL ");
      printf ("\n");
      printf ("      (");
      printf ("%.14e", a);
      printf (",");
      printf ("%.14e", b);
      printf (")");
      printf ("\n");
      switch ( j )
        {
          case 1: case 3:
            printf ("   SINH(X)");
            break;
          case 2: case 4:
            printf ("   COSH(X)");
            break;
        }
      printf (" WAS LARGER  ");
      printf ("%d", k1);
      printf (" TIMES");
      printf ("\n");
      printf ("               AGREED  ");
      printf ("%d", k2);
      printf (" TIMES");
      printf ("\n");
      printf ("          WAS SMALLER  ");
      printf ("%d", k3);
      printf (" TIMES");

      printf (" THERE ARE ");
      printf ("%4d", it);
      printf (" BASE ");
      printf ("%4d", ibeta);
      printf (" SIGNIFICANT DIGITS IN A FLOATING-POINT NUMBER");

      w = - 999.0e0;
      if ( (r6 != 0.0) )
        {
          w = log (fabs (r6)) / albeta;
        }
      printf (" THE MAXIMUM RELATIVE ERROR OF ");
      printf ("%10.4e", r6);
      printf (" = ");
      printf ("%4d", ibeta);
      printf (" **");
      printf ("%7.2f", w);
      printf ("\n");
      printf ("    OCCURED FOR X = ");
      printf ("%.14e", x1);
      printf ("\n");
      w = max (ait + w, 0.0);
      printf (" THE ESTIMATED LOSS OF BASE ");
      printf ("%4d", ibeta);
      printf (" SIGNIFICANT DIGITS IS ");
      printf ("%7.2f", w);
      printf ("\n\n");
      w = - 999.0e0;
      if ( (r7 != 0.0) )
        {
          w = log (fabs (r7)) / albeta;
        }
      printf (" THE ROOT MEAN SQUARE RELATIVE ERROR WAS ");
      printf ("%10.4e", r7);
      printf (" = ");
      printf ("%4d", ibeta);
      printf (" **");
      printf ("%7.2f", w);
      printf ("\n");
      w = max (ait + w, 0.0);
      printf (" THE ESTIMATED LOSS OF BASE ");
      printf ("%4d", ibeta);
      printf (" SIGNIFICANT DIGITS IS ");
      printf ("%7.2f", w);
      printf ("\n\n");
    }
/*
 *----------------------------------------------------------
 *               SPECIAL TESTS
 *----------------------------------------------------------
 */

  printf (" SPECIAL TESTS\n");

  printf (" THE IDENTITY    SINH(-X) = -SINH(X)    WILL BE TESTED.");
  printf ("\n\n");
  printf ("        X         F(X) + F(-X)");
  printf ("\n\n");
  for ( i = 1; i <= 5; i ++ )
    {
      x = ran () * a;
      z = sinh (x) + sinh (- x);
      printf ("%.14e", x);
      printf ("    ");
      printf ("%.14e", z);
      printf ("\n");
    }

  printf (" THE IDENTITY    SINH(X) = X   X SMALL   WILL BE TESTED.");
  printf ("\n\n");
  printf ("        X         X - F(X) ");
  printf ("\n\n");
  x = ran () / betap;
  for ( i = 1; i <= 5; i ++ )
    {
      z = x - sinh (x);
      printf ("%.14e", x);
      printf ("    ");
      printf ("%.14e", z);
      printf ("\n");
      x = x / beta;
    }

  printf (" THE IDENTITY    COSH(-X) = COSH(X)    WILL BE TESTED.");
  printf ("\n\n");
  printf ("        X         F(X) + F(-X)");
  printf ("\n\n");
  for ( i = 1; i <= 5; i ++ )
    {
      x = ran () * a;
      z = cosh (x) - cosh (- x);
      printf ("%.14e", x);
      printf ("    ");
      printf ("%.14e", z);
      printf ("\n");
    }

  printf (" TEST OF UNDERFLOW FOR VERY SMALL ARGUMENT. ");
  printf ("\n");
  x = powi (beta, (minexp * 3) / 4);
  y = sinh (x);
  printf ("       SINH(");
  printf ("%.14e", x);
  printf (") = ");
  printf ("%.14e", y);
  printf ("\n");
/*
 *----------------------------------------------------------
 *               TESTS OF ERROR RETURNS\n
 *----------------------------------------------------------
 */

  printf (" TEST OF ERROR RETURNS\n");

  x = alxmax + 0.125;
  printf (" SINH WILL BE CALLED WITH THE ARGUMENT ");
  printf ("%.14e", x);
  printf ("\n");
  printf (" THIS SHOULD NOT TRIGGER AN ERROR MESSAGE");
  printf ("\n");
  z = sinh (x);
  printf ("\n");
  printf (" SINH RETURNED THE VALUE ");
  printf ("%.14e", z);
  printf ("\n");
  x = betap;
  printf (" SINH WILL BE CALLED WITH THE ARGUMENT ");
  printf ("%.14e", x);
  printf ("\n");
  printf (" THIS SHOULD TRIGGER AN ERROR MESSAGE");
  printf ("\n");
  z = sinh (x);
  printf ("\n");
  printf (" SINH RETURNED THE VALUE ");
  printf ("%.14e", z);
  printf ("\n");
  printf (" THIS CONCLUDES THE TESTS");
  printf ("\n");
}
/*test_sinh_cosh*/


/*
 *::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
 *TESTTANH
 *::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
 */
void
test_tanh (void)
{
  int    n = 2000;
  int    i, j, k1, k2, k3;
  double r6, r7;
  double w, x, xl, y, z, zz;
  double x1;
  double a, b, c, d, del;
  double den, xsq;
  double beta   = (double) (ibeta);
  double albeta = log (beta);
  double betap  = powi (beta, it);
  double ait    = (double) (it);
  double xn     = (double) (n);

  
/*
 *---------------------------------------------------------
 *               RANDOM ARGUMENT TESTS
 *---------------------------------------------------------
 */
  c = 1.2435300177159620805e-1;
  d = log (2.0) + (ait + 1.0) * log (beta) * 0.5;
  for ( j = 1; j <= 2; j ++ )
    {
      k1 = 0;
      k3 = 0;
      x1 = 0.0;
      r6 = 0.0;
      r7 = 0.0;
      switch ( j )
        {
          case 1:
            a = 0.125;
            b = log (3.0) * 0.5;
            break;
          case 2:
            a = b + a;
            b = d;
            break;
        }
      del = (b - a) / xn;
      xl  = a;
      for ( i = 1; i <= n; i ++ )
        {
          x  = del * ran () + xl;
          z  = tanh (x);
          y  = x - 0.125;
          zz = tanh (y);
          zz = (zz + c) / (1.0 + c * zz);
          w  = 1.0;
          if ( z != 0.0 )
            {
              w = (z - zz) / z;
            }
          if ( w > 0.0 ) k1++;
          if ( w < 0.0 ) k3++;
          w = fabs (w);
          if ( w > r6 )
            {
              r6 = w;
              x1 = x;
            }
          r7 = r7 + w * w;
          xl = xl + del;
        }
      k2 = n - k1 - k3;
      r7 = sqrt (r7 / xn);

      printf (" TEST OF TANH(X) VS ");
      printf ("(TANH(X-1/8)+TANH(1/8))/(1+TANH(X-1/8)TANH(1/8))\n");

      printf ("%d", n);
      printf (" RANDOM ARGUMENTS WERE TESTED FROM THE INTERVAL ");
      printf ("\n");
      printf ("      (");
      printf ("%.14e", a);
      printf (",");
      printf ("%.14e", b);
      printf (")");
      printf ("\n");
      printf ("   TANH(X) WAS LARGER  ");
      printf ("%d", k1);
      printf (" TIMES");
      printf ("\n");
      printf ("               AGREED  ");
      printf ("%d", k2);
      printf (" TIMES");
      printf ("\n");
      printf ("          WAS SMALLER  ");
      printf ("%d", k3);
      printf (" TIMES");

      printf (" THERE ARE ");
      printf ("%4d", it);
      printf (" BASE ");
      printf ("%4d", ibeta);
      printf (" SIGNIFICANT DIGITS IN A FLOATING-POINT NUMBER");

      w = - 999.0e0;
      if ( (r6 != 0.0) )
        {
          w = log (fabs (r6)) / albeta;
        }
      printf (" THE MAXIMUM RELATIVE ERROR OF ");
      printf ("%10.4e", r6);
      printf (" = ");
      printf ("%4d", ibeta);
      printf (" **");
      printf ("%7.2f", w);
      printf ("\n");
      printf ("    OCCURED FOR X = ");
      printf ("%.14e", x1);
      printf ("\n");
      w = max (ait + w, 0.0);
      printf (" THE ESTIMATED LOSS OF BASE ");
      printf ("%4d", ibeta);
      printf (" SIGNIFICANT DIGITS IS ");
      printf ("%7.2f", w);
      printf ("\n\n");
      w = - 999.0e0;
      if ( (r7 != 0.0) )
        {
          w = log (fabs (r7)) / albeta;
        }
      printf (" THE ROOT MEAN SQUARE RELATIVE ERROR WAS ");
      printf ("%10.4e", r7);
      printf (" = ");
      printf ("%4d", ibeta);
      printf (" **");
      printf ("%7.2f", w);
      printf ("\n");
      w = max (ait + w, 0.0);
      printf (" THE ESTIMATED LOSS OF BASE ");
      printf ("%4d", ibeta);
      printf (" SIGNIFICANT DIGITS IS ");
      printf ("%7.2f", w);
      printf ("\n\n");
    }
/*
 *----------------------------------------------------------
 *               SPECIAL TESTS
 *----------------------------------------------------------
 */

  printf (" SPECIAL TESTS\n");

  printf (" THE IDENTITY    TANH(-X) = -TANH(X)    WILL BE TESTED.");
  printf ("\n\n");
  printf ("        X         F(X) + F(-X)");
  printf ("\n\n");
  for ( i = 1; i <= 5; i ++ )
    {
      x = ran ();
      z = tanh (x) + tanh (- x);
      printf ("%.14e", x);
      printf ("    ");
      printf ("%.14e", z);
      printf ("\n");
    }

  printf (" THE IDENTITY    TANH(X) = X   X SMALL   WILL BE TESTED.");
  printf ("\n\n");
  printf ("        X         X - F(X) ");
  printf ("\n\n");
  x = ran () / betap;
  for ( i = 1; i <= 5; i ++ )
    {
      z = x - tanh (x);
      printf ("%.14e", x);
      printf ("    ");
      printf ("%.14e", z);
      printf ("\n");
      x = x / beta;
    }

  printf (" THE IDENTITY    TANH(X) = 1   X LARGE   WILL BE TESTED.");
  printf ("\n\n");
  printf ("        X           F(X) - 1 ");
  printf ("\n\n");
  x = d;
  b = 4.0;
  for ( i = 1; i <= 5; i ++ )
    {
      z = (tanh (x) - 0.5) - 0.5;
      printf ("%.14e", x);
      printf ("    ");
      printf ("%.14e", z);
      printf ("\n");
      x = x + b;
    }

  printf (" TEST OF UNDERFLOW FOR VERY SMALL ARGUMENT. ");
  printf ("\n");
  x = powi (beta, (minexp * 3) / 4);
  y = tanh (x);
  printf ("       TANH(");
  printf ("%.14e", x);
  printf (") = ");
  printf ("%.14e", y);
  printf ("\n");
/*
 *----------------------------------------------------------
 *               TESTS OF ERROR RETURNS\n
 *----------------------------------------------------------
 */

  printf (" TEST OF ERROR RETURNS\n");

  x = xmax;
  printf (" TANH WILL BE CALLED WITH THE ARGUMENT ");
  printf ("%.14e", x);
  printf ("\n");
  printf (" THIS SHOULD NOT TRIGGER AN ERROR MESSAGE");
  printf ("\n");
  z = tanh (x);
  printf ("\n");
  printf (" TANH RETURNED THE VALUE ");
  printf ("%.14e", z);
  printf ("\n");
  x = xmin;
  printf (" TANH WILL BE CALLED WITH THE ARGUMENT ");
  printf ("%.14e", x);
  printf ("\n");
  printf (" THIS SHOULD NOT TRIGGER AN ERROR MESSAGE");
  printf ("\n");
  z = tanh (x);
  printf ("\n");
  printf (" TANH RETURNED THE VALUE ");
  printf ("%.14e", z);
  printf ("\n");
  x = 0.0;
  printf (" TANH WILL BE CALLED WITH THE ARGUMENT ");
  printf ("%.14e", x);
  printf ("\n");
  printf (" THIS SHOULD NOT TRIGGER AN ERROR MESSAGE");
  printf ("\n");
  z = tanh (x);
  printf ("\n");
  printf (" TANH RETURNED THE VALUE ");
  printf ("%.14e", z);
  printf ("\n");
  printf (" THIS CONCLUDES THE TESTS");
  printf ("\n");
}
/*test_tanh*/


/*
 *::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
 *TESTMATH
 *::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
 */

void
main (void)
{
  /* Initialize.. */
  machar ();
  set_ran_key (0.0);

  /* and run the tests */
  test_sqrt ();
  test_cbrt ();
  test_log ();
  test_exp ();
  test_power ();
  test_sin_cos ();
  test_tan_cot ();
  test_asin_acos ();
  test_atan ();
  test_sinh_cosh ();
  test_tanh ();
}


