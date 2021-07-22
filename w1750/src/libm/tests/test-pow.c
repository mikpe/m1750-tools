/*
 * Test for ANSI Standard C: 7.5.5.1
 * 
 * #include <math.h>
 * double pow (double x, double y);
 * 
 * Copyright (c) 1997, Chris Nettleton Software
 *
 * This test program was developed for European Space Agency contract 
 * 11935/96/NL/JG. Permission to use copy, modify, and distribute this 
 * software for any purpose without fee is hereby granted, provided that 
 * this entire notice is included in all copies of any software which is 
 * or includes a copy or modification of this software and in all copies 
 * of the supporting documentation for such software. This software is 
 * provided "as is", without any express or implied warranty. In 
 * particular, neither the author nor the European Space Agency makes 
 * any representation or warranty of any kind concerning the 
 * merchantability of this software or its fitness for any particular 
 * purpose. 
 *
 * $Log: test-pow.c,v $
 * Revision 1.1  1997/05/07 09:29:40  nettleto
 * Initial revision
 *
 */

#include <math.h>

#include <report.h>
#include <float.h>


static struct test {
  double x;
  double y;
  double p;
} tests [] = {
 3.0, 3.0, 27.0,
 3.0, -3.0, .03703703703703703703,
};


int
main ()
{
  int len;
  int i;

  test ("test-pow", "test for the pow function");

  len = sizeof (tests) / sizeof (struct test);

  for (i = 0; i < len; i++)
    {
      double x = tests [i].x;
      double y = tests [i].y;
      double p = pow (x, y);
      double err = p / tests [i].p - 1;

      if (fabs (err) >= DBL_EPSILON) 
        failed ("x = %.10e, y = %.10e, pow (x,y) = %.10e, err = %e",
                 x, y, err);
    }

  result ();
}


