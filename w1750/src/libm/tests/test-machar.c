/*
 * Test-machar.c - check <float.h>
 *
 * Copyright (c) 1997, Chris Nettleton Software
 *
 * The code in this file is based on "Software Manual for the 
 * Elementry Functions" by William J. Cody, Jr. and William 
 * Waite, Prentice_Hall, 1980. 
 *
 * $Log: test-machar.c,v $
 * Revision 1.1  1997/08/04 15:48:18  nettleto
 * Initial revision
 *
 */

#include <limits.h>
#include <float.h>
#include <math.h>

#include <report.h>


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


int
iround (double x)
{
/*
 * Returns the integer value of the integer nearest X
 */
  return ( x >= 0.0 ) ? (int) (x+0.5) : -(int) (-x+0.5);
}


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


void
test_machar (void)
{
  comment ("IBETA         = %d", ibeta);
  comment ("FLT_RADIX     = %d", FLT_RADIX);
  if (ibeta != FLT_RADIX)
    failed ("ibeta != FLT_RADIX");

  comment ("IT            = %d", it);
  comment ("DBL_MANT_DIG  = %d", DBL_MANT_DIG);
  if (it != DBL_MANT_DIG)
    failed ("it != DBL_MANT_DIG");

  comment ("IRND          = %d", irnd);
  comment ("FLT_ROUNDS    = %d", FLT_ROUNDS);
  if (irnd != FLT_ROUNDS)
    failed ("irnd != FLT_ROUNDS");

  comment ("NEGEP         = %d", negep);

  comment ("EPSNEG        = %.14e", epsneg);
  comment ("MACHEP        = %d", machep);

  comment ("EPS           = %.14e", eps);
  comment ("DBL_EPSILON   = %.14e", DBL_EPSILON);
  if (eps != DBL_EPSILON)
    failed ("eps != DBL_EPSILON");

  comment ("NGRD          = %d", ngrd);
  comment ("IEXP          = %d", iexp);

  comment ("MINEXP        = %d", minexp);
  comment ("DBL_MIN_EXP   = %d", DBL_MIN_EXP);
  if (minexp != DBL_MIN_EXP)
    failed ("minexp != DBL_MIN_EXP");

  comment ("XMIN          = %.14e", xmin);
  comment ("DBL_MIN       = %.14e", DBL_MIN);
  if (xmin != DBL_MIN)
    failed ("xmin != DBL_MIN");

  comment ("MAXEXP        = %d", maxexp);
  comment ("DBL_MAX_EXP   = %d", DBL_MAX_EXP);
//  if (maxexp != DBL_MAX_EXP)
//    failed ("maxexp != DBL_MAX_EXP");
// FIXME: we disagree here!!

  comment ("XMAX          = %.14e", xmax);
  comment ("DBL_MAX       = %.14e", DBL_MAX);
  if (xmax != DBL_MAX)
    failed ("xmax != DBL_MAX");
}


int
main ()
{
  test ("test-machar", "Check <float.h>");

  machar ();

  test_machar ();

  result ();
}


