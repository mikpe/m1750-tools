/*
 * Test for ANSI Standard C: 7.5.4.3
 * 
 * #include <math.h>
 * double ldexp (double x, int exp);
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
 * $Log: test-ldexp.c,v $
 * Revision 1.1  1997/05/07 09:29:38  nettleto
 * Initial revision
 *
 */

#include <math.h>

#include <report.h>
#include <float.h>


static struct test {
  double x;
  int e;
  double y;
} tests [] = {
  0.0, 0, 0.0,
  0.5, 0, 0.5,
  0.5, 10, 512.0,
  -0.5, 10, -512.0,
  0.999999999999, 127, DBL_MAX,
  0.5, -128, DBL_MIN,
};


int
main ()
{
  int len;
  int i;

  test ("test-ldexp", "test for the ldexp function");

  len = sizeof (tests) / sizeof (struct test);

  for (i = 0; i < len; i++)
    {
      double x = tests [i].x;
      int e = tests [i].e;
      double y = ldexp (x, e);
     
      if (y != tests [i].y) 
        failed ("x = %.10e e = %d, ldexp (x,e) = %.10e, expected = %.10e",
                 x, e, y, tests [i].y);
    }

  result ();
}


