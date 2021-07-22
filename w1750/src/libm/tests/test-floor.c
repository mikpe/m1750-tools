/*
 * Test for ANSI Standard C: 7.5.6.3
 * 
 * #include <math.h>
 * double floor (double x);
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
 * $Log: test-floor.c,v $
 * Revision 1.3  1997/08/05 11:59:37  nettleto
 * Added more tests
 *
 * Revision 1.2  1997/08/05 11:11:43  nettleto
 * Added tests for -0.1 to -0.9
 *
 * Revision 1.1  1997/05/07 09:29:37  nettleto
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
 0.1, 0.0,
 0.2, 0.0,
 0.3, 0.0,
 0.4, 0.0,
 0.5, 0.0,
 0.6, 0.0,
 0.7, 0.0,
 0.8, 0.0,
 0.9, 0.0,
 1.0, 1.0,
 5.0, 5.0,
 1.1, 1.0,
 -0.1, -1.0,
 -0.2, -1.0,
 -0.3, -1.0,
 -0.4, -1.0,
 -0.5, -1.0,
 -0.6, -1.0,
 -0.7, -1.0,
 -0.8, -1.0,
 -0.9, -1.0,
 -1.0, -1.0,
 -1.0000000001, -2.0,
 -256.0, -256.0,
 -255.9999, -256.0,
 1.9999999999, 1.0,
 2.0, 2.0,
 -2048.1234, -2049.0,
 -134217728.5, -134217729.0,
 134217728.5, 134217728.0,
 0.123456789, 0.0,
 -0.123456789, -1.0,
 -1.1, -2.0,
 123456789.123, 123456789.0,
};


int
main ()
{
  int len;
  int i;

  test ("test-floor", "test for the floor function");

  len = sizeof (tests) / sizeof (struct test);

  for (i = 0; i < len; i++)
    {
      double x = tests [i].x;
      double y = floor (x);
      char buf1 [20];
      char buf2 [20];

      sprintf (buf1, "%.10e", y);
      sprintf (buf2, "%.10e", tests [i].y);
     
      if (strncmp (buf1, buf2, 16) != 0) 
        failed ("x = %.10e, floor (x) = %.10e, expected = %.10e",
                 x, y, tests [i].y);
    }

  result ();
}


