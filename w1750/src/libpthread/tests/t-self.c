/*
 * t-self.c - measure time for pthread_self ()
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
 * $Log: t-self.c,v $
 * Revision 1.1  1997/07/27 10:29:12  nettleto
 * Initial revision
 *
 */

#include <pthread.h>
#include <report.h>
#include <time.h>

#define ntimes 10000

void
run_test ()
{
  int ans;
  int cnt;
  clock_t t0, t1, t2, t3;

  t0 = clock ();
  for (cnt = 1; cnt <= ntimes; cnt++)
    {
      pthread_self ();
    }
  t1 = clock ();

  t2 = clock ();
  for (cnt = 1; cnt <= ntimes; cnt++)
    {
      pthread_self ();
      pthread_self ();
      pthread_self ();
      pthread_self ();
      pthread_self ();
      pthread_self ();
      pthread_self ();
      pthread_self ();
      pthread_self ();
      pthread_self ();
      pthread_self ();
    }
  t3 = clock ();

  comment ("t1 - t1 = %ld", t1 - t0);
  comment ("t3 - t2 = %ld", t3 - t2);

  if (t1 - t0 < 10)
    failed ("ntimes too low to get significant result");
  else
    comment ("time for one call of pthread_self = %ld uSec",
    (long)((double)((t3 - t2) - (t1 - t0)) / ntimes / 10 / CLOCKS_PER_SEC * 1.0e6));
}


int
main (int argc, char *argv[])
{
  pthread_init ();

  test ("t-self", "measure time for pthread_self ()");

  run_test ();

  result ();
}
