/*
 * t-signal.c - measure time for pthread_cond_signal
 *
 * Copyright (c) 1997 Chris Nettleton Software
 *
 * This file is part of the GCC-1750 test suite. It was developed under 
 * European Space Agency contract 11935/96/NL/JG. Permission to use 
 * copy, modify, and distribute this software for any purpose without 
 * fee is hereby granted, provided that this entire notice is included 
 * in all copies of any software which is or includes a copy or 
 * modification of this software and in all copies of the supporting 
 * documentation for such software. This software is provided "as is", 
 * without any express or implied warranty. In particular, neither the 
 * author nor the European Space Agency makes any representation or 
 * warranty of any kind concerning the merchantability of this software 
 * or its fitness for any particular purpose. 
 *
 * $Log: t-signal.c,v $
 * Revision 1.2  1997/08/06 15:11:15  nettleto
 * Corrected final time check.
 *
 * Revision 1.1  1997/07/27 10:29:12  nettleto
 * Initial revision
 *
 */

#include <time.h>
#include <pthread.h>
#include <report.h>


int
main ()
{
  clock_t t1, t2;
  pthread_cond_t c1;
  int ntimes = 10000;
  int i;
  double ans;

  pthread_init ();
  pthread_cond_init (&c1, NULL);

  test ("t-signal", "measure time for pthread_cond_signal");

  t1 = clock ();
  for (i = 1; i <= ntimes; i++)
    pthread_cond_signal (&c1);
  t2 = clock ();

  ans = (double)(t2 - t1) / (double)CLOCKS_PER_SEC / ntimes * 1.0e6;

  comment ("total time = %ld clock ticks", t2 - t1);
  comment ("time for 1 call of pthread_cond_signal = %ld uSec", (long)ans);

  /* results in the range 1 uSec to 1 mSec are OK */
  if (ans < 1.0 || ans > 1000.0)
    failed ("result out of range");

  result ();
}


