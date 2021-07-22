/*
 * Test for ANSI Standard C: 7.5.4.6
 * 
 * #include <math.h>
 * double modf (double value, double *iptr);
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
 * $Log: test-modf.c,v $
 * Revision 1.1  1997/05/07 09:29:39  nettleto
 * Initial revision
 *
 */

#include <math.h>

#include <report.h>
#include <float.h>


static struct test {
  double x;
  double j, f;
} tests [] = {
 0.0, 0.0, 0.0,
 1.0, 1.0, 0.0,
 -1.0, -1.0, 0.0,
 1.5, 1.0, 0.5,
 -1.5, -1.0, -0.5,
};


int
main ()
{
  int len;
  int i;

  test ("test-modf", "test for the modf function");

  len = sizeof (tests) / sizeof (struct test);

  for (i = 0; i < len; i++)
    {
      double x = tests [i].x;
      double j;
      double f = modf (x, &j);

      if (j != tests [i].j || f != tests [i].f) 
        failed ("x = %.10e, modf (x, &f) = %.10e, %.10e",
                 x, j, f);
    }

  result ();
}


