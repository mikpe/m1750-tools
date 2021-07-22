/*
 * Test for ANSI Standard C: 7.5.3.2
 * 
 * #include <math.h>
 * double sinh (double x);
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
 * $Log: test-sinh.c,v $
 * Revision 1.1  1997/05/07 09:29:41  nettleto
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
  -4.134659046875854e+00, -3.122614027935458e+01, 
  -2.602186889368570e+00, -6.709551315762159e+00, 
  -5.046662302998213e-01, -5.263627601322348e-01, 
  -4.476208103335553e+00, -4.394467649200175e+01, 
  3.501978925116530e+00, 1.657545607970527e+01, 
  3.104281081844118e+00, 1.112416474060455e+01, 
  4.335924022262465e+00, 3.819121383576991e+01, 
  -4.711298462392759e+00, -5.559372876196214e+01, 
  -3.242728245842960e+00, -1.278221096997753e+01, 
  2.552401112587275e+00, 6.379998810479591e+00, 
  -7.749497003704700e-01, -8.548779975690546e-01, 
  1.782060688670895e+00, 2.886898805605008e+00, 
  1.993730061171970e+00, 3.603342806493359e+00, 
  -6.440505698615970e-01, -6.895086887174010e-01, 
  4.339413554819595e+00, 3.832476179193343e+01, 
  -4.421694686377042e+00, -4.161260651896749e+01, 
  -9.765607711479971e-01, -1.139352102640983e+00, 
  -1.723757061122651e+00, -2.713577347510485e+00, 
  -6.723078367055987e+00, -4.156858221435323e+02, 
  -4.404573369906650e-01, -4.548377723080488e-01, 
  3.670005308337482e+00, 1.961331894425566e+01, 
  -4.247175934108083e+00, -3.494670238170955e+01, 
  2.689841018182316e+00, 7.330721152962862e+00, 
  5.997633897221622e+00, 2.012364416378757e+02, 
  -1.005185494458636e+00, -1.183218665819862e+00, 
  5.836615777688174e-01, 6.173690664675596e-01, 
  -3.082017030820308e-01, -3.131041879642932e-01, 
  -1.748111676728735e+00, -2.784821992167608e+00, 
  4.523814793330777e+00, 4.608787665876230e+01, 
  3.726016696498139e+00, 2.074466462292129e+01, 
  5.057154003317493e+00, 7.856814410236977e+01, 
  -4.397400886731567e+00, -4.061356710893777e+01, 
  4.993024642955757e+00, 7.368737070129922e+01, 
  4.524975301475751e+00, 4.614140565080264e+01, 
  4.874906983653984e+00, 6.547716761790163e+01, 
  1.879651067722596e+00, 3.199287586532384e+00, 
  -8.230315458590658e-01, -9.191474590852350e-01, 
  4.948403476623469e+00, 7.047132994420159e+01, 
  -4.971094961202781e+00, -7.208887102317632e+01, 
  -4.672048626639397e+00, -5.345359861618556e+01, 
  9.504975798233630e-01, 1.100223969812322e+00, 
  -5.949278415887438e-01, -6.306488785326502e-01, 
  5.238177961593559e+00, 9.416067064783411e+01, 
  -2.635565846493556e+00, -6.939763035644878e+00, 
  -2.497483538637687e+00, -6.034791951920014e+00, 
  5.233217043265336e+00, 9.369467767566215e+01, 
  -5.763782067600573e+00, -1.592738475396409e+02, 
  -4.678199987293416e+00, -5.378348191269308e+01, 
  -4.881051015996837e+00, -6.588074675649062e+01, 
};


int
main ()
{
  int len;
  int i;
  double ms = 0.0;

  test ("test-sinh", "test for the sinh function");

  len = sizeof (tests) / sizeof (struct test);

  for (i = 0; i < len; i++)
    {
      double x = tests [i].x;
      double y = sinh (x);
      double err = y - tests [i].y;

      ms += err * err;
      if (abs (err) >= 100.0 * DBL_EPSILON)
        failed ("x = %.10e, err = %+e, y = %.12e", x, err, y);
    }

  comment ("rms error = %.3e", sqrt (ms / len));

  result ();
}


