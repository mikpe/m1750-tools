/*
 * Test for ANSI Standard C: 7.5.2.3
 * 
 * #include <math.h>
 * double atan (double x);
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
 * $Log: test-atan.c,v $
 * Revision 1.1  1997/05/07 09:29:34  nettleto
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
  -1.0000000000000e+00, -7.8539816339745e-01,
  -8.7654232110000e-01, -7.1970285923634e-01,
  -7.5308464220000e-01, -6.4547235855609e-01,
  -6.2962696330000e-01, -5.6191965286916e-01,
  -5.0616928440000e-01, -4.6857084750193e-01,
  -3.8271160550000e-01, -3.6551433004755e-01,
  -2.5925392660000e-01, -2.5366909933448e-01,
  -1.3579624770000e-01, -1.3497064107300e-01,
  -1.2338568800000e-02, -1.2337942714798e-02,
  1.1111911010000e-01, 1.1066512260720e-01,
  2.3457678900000e-01, 2.3041086028795e-01,
  3.5803446790000e-01, 3.4381446681468e-01,
  4.8149214680000e-01, 4.4873200212296e-01,
  6.0494982570000e-01, 5.4405113142836e-01,
  7.2840750460000e-01, 6.2953809157463e-01,
  8.5186518350000e-01, 7.0557590320790e-01,
  9.7532286240000e-01, 7.7290610226617e-01,
};


int
main ()
{
  int len;
  int i;
  double ms = 0;

  test ("test-atan", "test for the atan function");

  len = sizeof (tests) / sizeof (struct test);

  for (i = 0; i < len; i++)
    {
      double x = tests [i].x;
      double y = atan (x);
      double err = y / tests [i].y - 1;

      ms += err * err;
      if (fabs (err) >= 4 * DBL_EPSILON) 
        failed ("x = %.10e, atan (x) = %.10e, err = %e",
                 x, y, err);
    }

  comment ("rms error = %.3e", sqrt (ms / len));

  result ();
}


