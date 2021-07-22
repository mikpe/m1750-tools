/*
 * Test for ANSI Standard C: 7.5.3.3
 * 
 * #include <math.h>
 * double tanh (double x);
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
 * $Log: test-tanh.c,v $
 * Revision 1.1  1997/05/07 09:29:42  nettleto
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
  -4.134659046875854e+00, -9.994876113507630e-01, 
  -2.602186889368570e+00, -9.890750275347029e-01, 
  -5.046662302998213e-01, -4.657789807685733e-01, 
  -4.476208103335553e+00, -9.997411853635314e-01, 
  3.501978925116530e+00, 9.981850884358568e-01, 
  3.104281081844118e+00, 9.959838240688932e-01, 
  4.335924022262465e+00, 9.996573743792005e-01, 
  -4.711298462392759e+00, -9.998382616443015e-01, 
  -3.242728245842960e+00, -9.969537185016377e-01, 
  2.552401112587275e+00, 9.879381083895171e-01, 
  -7.749497003704700e-01, -6.497984034054550e-01, 
  1.782060688670895e+00, 9.449163536874513e-01, 
  1.993730061171970e+00, 9.635819157953438e-01, 
  -6.440505698615970e-01, -5.676512279280667e-01, 
  4.339413554819595e+00, 9.996597568555231e-01, 
  -4.421694686377042e+00, -9.997113762192097e-01, 
  -9.765607711479971e-01, -7.515732310082238e-01, 
  -1.723757061122651e+00, -9.383138398402393e-01, 
  -6.723078367055987e+00, -9.999971064053359e-01, 
  -4.404573369906650e-01, -4.140234563036121e-01, 
  3.670005308337482e+00, 9.987027547083488e-01, 
  -4.247175934108083e+00, -9.995908420487349e-01, 
  2.689841018182316e+00, 9.908237215381038e-01, 
  5.997633897221622e+00, 9.999876533623525e-01, 
  -1.005185494458636e+00, -7.637633444832805e-01, 
  5.836615777688174e-01, 5.253216454633134e-01, 
  -3.082017030820308e-01, -2.988002363234565e-01, 
  -1.748111676728735e+00, -9.411602420090351e-01, 
  4.523814793330777e+00, 9.997646884245036e-01, 
  3.726016696498139e+00, 9.988401519857710e-01, 
  5.057154003317493e+00, 9.999190113325600e-01, 
  -4.397400886731567e+00, -9.996970085892103e-01, 
  4.993024642955757e+00, 9.999079287792687e-01, 
  4.524975301475751e+00, 9.997652338891324e-01, 
  4.874906983653984e+00, 9.998833957797627e-01, 
  1.879651067722596e+00, 9.544610670219195e-01, 
  -8.230315458590658e-01, -6.767165117365307e-01, 
  4.948403476623469e+00, 9.998993347705724e-01, 
  -4.971094961202781e+00, -9.999038009275796e-01, 
  -4.672048626639397e+00, -9.998250547603272e-01, 
  9.504975798233630e-01, 7.400082332193411e-01, 
  -5.949278415887438e-01, -5.334305045720531e-01, 
  5.238177961593559e+00, 9.999436110272679e-01, 
  -2.635565846493556e+00, -9.897769382188860e-01, 
  -2.497483538637687e+00, -9.865472134256524e-01, 
  5.233217043265336e+00, 9.999430487763544e-01, 
  -5.763782067600573e+00, -9.999802908351437e-01, 
  -4.678199987293416e+00, -9.998271936925672e-01, 
  -4.881051015996837e+00, -9.998848197704830e-01, 
};


int
main ()
{
  int len;
  int i;
  double ms = 0.0;

  test ("test-tanh", "test for the tanh function");

  len = sizeof (tests) / sizeof (struct test);

  for (i = 0; i < len; i++)
    {
      double x = tests [i].x;
      double y = tanh (x);
      double err = y - tests [i].y;

      ms += err * err;
      if (abs (err) >= 100.0 * DBL_EPSILON)
        failed ("x = %.10e, err = %+e, y = %.12e", x, err, y);
    }

  comment ("rms error = %.3e", sqrt (ms / len));

  result ();
}


