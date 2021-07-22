/*
 * Test for ANSI Standard C: 7.5.4.2
 * 
 * #include <math.h>
 * double frexp (double value, int *exp);
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
 * $Log: test-frexp.c,v $
 * Revision 1.1  1997/05/07 09:29:37  nettleto
 * Initial revision
 *
 */

#include <math.h>

#include <report.h>

static struct test {
  double x;
  double y;
  int e;
} tests [] = {
  0.0, 0.0, 0,
  1.0, 0.5, 1,
  -1.0, -0.5, 1,
  1312817773631141948494931860436189791.855312896, 0.987654321, 120,
  1.701411834602E38, 0.999999999999, 127,
};


int
main ()
{
  int len;
  int i;

  test ("test-frexp", "test for the frexp function");

  len = sizeof (tests) / sizeof (struct test);

  for (i = 0; i < len; i++)
    {
      double x = tests [i].x;
      int e;
      double y = frexp (x, &e);
     
      if (e != tests [i].e || y != tests [i].y) 
        failed ("x = %.10e, frexp (x,&e) = %.10e (%d), expected = %.10e (%d)",
                 x, y, e, tests [i].y, tests [i].e);
    }

  result ();
}


