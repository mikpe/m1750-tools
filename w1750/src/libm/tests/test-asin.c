/*
 * Test for ANSI Standard C: 7.5.2.2
 * 
 * #include <math.h>
 * double asin (double x);
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
 * $Log: test-asin.c,v $
 * Revision 1.1  1997/05/07 09:29:33  nettleto
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
  -2.0000000000000e+00, -1.5707963267949e+00,
  -1.0000000000000e+00, -1.5707963267949e+00,
  -8.7654232110000e-01, -1.0686308518607e+00,
  -7.5308464220000e-01, -8.5273803268338e-01,
  -6.2962696330000e-01, -6.8107295609228e-01,
  -5.0616928440000e-01, -5.3073722232045e-01,
  -3.8271160550000e-01, -3.9272957627281e-01,
  -2.5925392660000e-01, -2.6224963742997e-01,
  -1.3579624770000e-01, -1.3621711076641e-01,
  -1.2338568800000e-02, -1.2338881892645e-02,
  1.1111911010000e-01, 1.1134906317189e-01,
  2.3457678900000e-01, 2.3678318665814e-01,
  3.5803446790000e-01, 3.6616196020297e-01,
  4.8149214680000e-01, 5.0235640638283e-01,
  6.0494982570000e-01, 6.4970285374201e-01,
  7.2840750460000e-01, 8.1599474792864e-01,
  8.5186518350000e-01, 1.0195361815160e+00,
  9.7532286240000e-01, 1.3481786978893e+00,
  1.0000000000000e+00, 1.5707963267949e+00,
  2.0000000000000e+00, 1.5707963267949e+00,
};


int
main ()
{
  int len;
  int i;
  double ms = 0;

  test ("test-asin", "test for the asin function");

  len = sizeof (tests) / sizeof (struct test);

  for (i = 0; i < len; i++)
    {
      double x = tests [i].x;
      double y = asin (x);
      double err = y - tests [i].y;

      ms += err * err;
      if (fabs (err) >= 4 * DBL_EPSILON) 
        failed ("x = %.10e, asin (x) = %.10e, err = %e",
                 x, y, err);
    }

  comment ("rms error = %.3e", sqrt (ms / len));

  result ();
}


