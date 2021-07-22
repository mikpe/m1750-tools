/*
 * Test for ANSI Standard C: 7.5.4.4
 * 
 * #include <math.h>
 * double log (double x);
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
 * $Log: test-log.c,v $
 * Revision 1.1  1997/05/07 09:29:38  nettleto
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
  8.700391237685987e-24, -5.309867423735871e+01,
  2.371953037762606e-15, -3.367506271255358e+01,
  8.337008941942292e-04, -7.089635859987133e+00,
  1.146741259498870e-25, -5.742770309236118e+01,
  9.457640812050723e+18, 4.369335464023653e+01,
  6.118370222310161e+16, 3.865265724541979e+01,
  3.683613391281391e+23, 5.426335130910033e+01,
  5.826384708681277e-27, -6.040740082140942e+01,
  7.066675161223523e-19, -4.179372667181780e+01,
  5.607711985342922e+13, 3.165774899951558e+01,
  2.711576114487090e-05, -1.051539540707608e+01,
  3.224107256491090e+09, 2.189392192917982e+01,
  4.715782932387460e+10, 2.457676588364860e+01,
  1.424827901794536e-04, -8.856289336219435e+00,
  3.850191618830751e+23, 5.430758005704907e+01,
  2.288427645929077e-25, -5.673676236061296e+01,
  2.105929770435965e-06, -1.307075349217986e+01,
  1.623550017590769e-10, -2.254123580935980e+01,
  4.914271160826410e-38, -8.590609007991382e+01,
  1.881270451170903e-03, -6.275807958471877e+00,
  7.955952663684648e+19, 4.582303717809778e+01,
  2.090182081684924e-24, -5.452479104925173e+01,
  3.201329119918878e+14, 3.339975737546305e+01,
  5.166978205771997e+32, 7.532501100714006e+01,
  1.465135213664025e-06, -1.343356302373786e+01,
  8.161377420929704e+02, 6.704583142303245e+00,
  1.005677617134632e-02, -4.599508625773596e+00,
  1.192352070276336e-10, -2.284992304393768e+01,
  3.985913812354385e+24, 5.664480883082346e+01,
  1.618115778343851e+20, 4.653296423241196e+01,
  3.438107469022786e+27, 6.340471867648026e+01,
  3.113605487038500e-25, -5.642884594956202e+01,
  1.525163045890928e+27, 6.259189883052188e+01,
  4.044976259748301e+24, 5.665951791331406e+01,
  3.412965439545246e+26, 6.109479396159638e+01,
  1.110709419377324e+10, 2.313084985767284e+01,
  1.474188264439784e-05, -1.112481795585850e+01,
  8.663570225972877e+26, 6.202633932173976e+01,
  2.164396043407604e-28, -6.370024124508048e+01,
  9.581903248963623e-27, -5.990992126959442e+01,
  8.531590935363622e+04, 1.135411622668246e+01,
  2.655588938514232e-04, -8.233673919465328e+00,
  3.410158809807538e+28, 6.569914146583534e+01,
  1.553710132814633e-15, -3.409813069008437e+01,
  8.942331336831786e-15, -3.234798006378943e+01,
  3.202336672918975e+28, 6.563626335745232e+01,
  9.374586379085772e-33, -7.374730561748451e+01,
  8.863215693599768e-27, -5.998788786696933e+01,
  6.776227748390072e-28, -6.255896203601087e+01,
};


int
main ()
{
  int len;
  int i;

  test ("test-log", "test for the log function");

  len = sizeof (tests) / sizeof (struct test);

  for (i = 0; i < len; i++)
    {
      double x = tests [i].x;
      double y = log (x);
      double err = y / tests [i].y - 1;

      if (fabs (err) >= DBL_EPSILON) 
        failed ("x = %.10e, log (x) = %.10e, err = %e",
                 x, y, err);
    }

  result ();
}

