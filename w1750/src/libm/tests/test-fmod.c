/*
 * Test for ANSI Standard C: 7.5.6.4
 * 
 * #include <math.h>
 * double fmod (double x, double y);
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
 * $Log: test-fmod.c,v $
 * Revision 1.1  1997/05/07 09:29:37  nettleto
 * Initial revision
 *
 */

#include <math.h>

#include <report.h>
#include <float.h>


static struct test {
  double x;
  double y;
  double z;
} tests [] = {
  10.0, 5.0, 0.0,
  10.0, 3.0, 1.0,
  10.0, -3.0, 1.0,
  -10.0, 3.0, -1.0,
  -10.0, -3.0, -1.0,
};


int
main ()
{
  int len;
  int i;

  test ("test-fmod", "test for the fmod function");

  len = sizeof (tests) / sizeof (struct test);

  for (i = 0; i < len; i++)
    {
      double x = tests [i].x;
      double y = tests [i].y;
      double z = fmod (x, y);
      double err = z - tests [i].z;

      if (fabs (err) >= DBL_EPSILON) 
        failed ("x = %.10e, y = %.10e, fmod (x) = %.10e, err = %e",
                 x, y, z, err);
    }

  result ();
}


