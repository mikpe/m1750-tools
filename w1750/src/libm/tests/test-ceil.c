/*
 * Test for ANSI Standard C: 7.5.6.1
 * 
 * #include <math.h>
 * double ceil (double x);
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
 * $Log: test-ceil.c,v $
 * Revision 1.1  1997/05/07 09:29:35  nettleto
 * Initial revision
 *
 */

#include <math.h>

#include <report.h>

static struct test {
  double x;
  double y;
} tests [] = {
  0.0, 0.0,
  0.5, 1.0,
  0.99999999, 1.0,
  -0.5, 0.0,
  -1.99999999, -1.0,
  1.0, 1.0,
  -2.0, -2.0,
  3.0000001, 4.0,
  -5.0000001, -5.0,
  1.701411834602E38, 1.701411834602E38,
  1.469367938528E-39, 1.0,
};


int
main ()
{
  int len;
  int i;

  test ("test-ceil", "test for the ceil function");

  len = sizeof (tests) / sizeof (struct test);

  for (i = 0; i < len; i++)
    {
      double x = tests [i].x;
      double y = ceil (x);
      char buf1 [20];
      char buf2 [20];

      sprintf (buf1, "%.10e", y);
      sprintf (buf2, "%.10e", tests [i].y);
     
      if (strncmp (buf1, buf2, 16) != 0) 
        failed ("x = %.10e, ceil (x) = %.10e, expected = %.10e",
                 x, y, tests [i].y);
    }

  result ();
}


