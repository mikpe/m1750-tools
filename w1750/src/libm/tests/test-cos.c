/*
 * Test for ANSI Standard C: 7.5.2.5
 * 
 * #include <math.h>
 * double cos (double x);
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
 * $Log: test-cos.c,v $
 * Revision 1.2  1997/08/04 11:00:48  nettleto
 * Reduced error margin to +/- 2 epsilons
 *
 * Revision 1.1  1997/05/07 09:29:35  nettleto
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
  -6.28318530717958647688, 1.00000000000000000000,
  -5.94985197384625314355, .94495694631473766437,
  -5.61651864051291981022, .78588726077694800070,
  -5.28318530717958647689, .54030230586813971737,
  -4.94985197384625314356, .23523757330298934298,
  -4.61651864051291981023, -.09572354801437558414,
  -4.28318530717958647690, -.41614683654714238701,
  -3.94985197384625314357, -.69075813974987629274,
  -3.61651864051291981024, -.88932656821304143104,
  -3.28318530717958647691, -.98999249660044545727,
  -2.94985197384625314358, -.98167400471107906433,
  -2.61651864051291981025, -.86528684293623587958,
  -2.28318530717958647692, -.65364362086361191463,
  -1.94985197384625314359, -.37004331696253784832,
  -1.61651864051291981026, -.04570638473858074709,
  -1.28318530717958647693, .28366218546322626446,
  -.94985197384625314360, .58180348985917086689,
  -.61651864051291981027, .81589631280193282355,
  -.28318530717958647694, .96017028665036602054,
  .05014802615374685639, .99874285122861957242,
  .38348135948708018972, .92736770305097536200,
  .71681469282041352305, .75390225434330463815,
  1.05014802615374685638, .49744264111711628025,
  1.38348135948708018971, .18622150389023168894,
  1.71681469282041352304, -.14550003380861352583,
  2.05014802615374685637, -.46120403916318874229,
  2.38348135948708018970, -.72613588714272549743,
  2.71681469282041352303, -.91113026188467698834,
  3.05014802615374685636, -.99582185278825766593,
  3.38348135948708018969, -.97088729228387539717,
  3.71681469282041352302, -.83907152907645245228,
  4.05014802615374685635, -.61488564742756884912,
  4.38348135948708018968, -.32300939837537932453,
  4.71681469282041352301, .00442569798805078568,
  5.05014802615374685634, .33137358648757882208,
  5.38348135948708018967, .62184184676527941293,
  5.71681469282041352300, .84385395873249210461,
  6.05014802615374685633, .97296947319363737547,
};


int
main ()
{
  int len;
  int i;
  double ms = 0.0;

  test ("test-cos", "test for the cos function");

  len = sizeof (tests) / sizeof (struct test);

  for (i = 0; i < len; i++)
    {
      double x = tests [i].x;
      double y = cos (x);
      double err = y - tests [i].y;

      ms += err * err;

      if (fabs (err) >= 2.0 * DBL_EPSILON) 
        failed ("x = %.10e, cos (x) = %.10e, err = %e",
                 x, y, err);
    }

  comment ("rms error = %.3e", sqrt (ms / len));

  result ();
}


