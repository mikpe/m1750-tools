/*
 * Test for ANSI Standard C: 7.5.2.1
 * 
 * #include <math.h>
 * double acos (double x);
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
 * $Log: test-acos.c,v $
 * Revision 1.1  1997/05/07 09:29:29  nettleto
 * Initial revision
 *
 */

#include <math.h>

#include <report.h>
#include <float.h>


static struct test {
  double x;
  double y;
} tests [] = {
  -2.0000000000000e+00, 3.1415926535898e+00,
  -1.0000000000000e+00, 3.1415926535898e+00,
  -8.7654232110000e-01, 2.6394271786556e+00,
  -7.5308464220000e-01, 2.4235343594783e+00,
  -6.2962696330000e-01, 2.2518692828872e+00,
  -5.0616928440000e-01, 2.1015335491153e+00,
  -3.8271160550000e-01, 1.9635259030677e+00,
  -2.5925392660000e-01, 1.8330459642249e+00,
  -1.3579624770000e-01, 1.7070134375613e+00,
  -1.2338568800000e-02, 1.5831352086875e+00,
  1.1111911010000e-01, 1.4594472636230e+00,
  2.3457678900000e-01, 1.3340131401368e+00,
  3.5803446790000e-01, 1.2046343665919e+00,
  4.8149214680000e-01, 1.0684399204121e+00,
  6.0494982570000e-01, 9.2109347305288e-01,
  7.2840750460000e-01, 7.5480157886626e-01,
  8.5186518350000e-01, 5.5126014527892e-01,
  9.7532286240000e-01, 2.2261762890562e-01,
  1.0000000000000e+00, 0.0000000000000e+00,
  2.0000000000000e+00, 0.0000000000000e+00,
};


int
main ()
{
  int len;
  int i;
  double ms = 0;

  test ("test-acos", "test for the acos function");

  len = sizeof (tests) / sizeof (struct test);

  for (i = 0; i < len; i++)
    {
      double x = tests [i].x;
      double y = acos (x);
      double err = y - tests [i].y;

      ms += err * err;
      if (fabs (err) >= 4 * DBL_EPSILON) 
        failed ("x = %.10e, acos (x) = %.10e, err = %e",
                 x, y, err);
    }

  comment ("rms error = %.3e", sqrt (ms / len));

  result ();
}


