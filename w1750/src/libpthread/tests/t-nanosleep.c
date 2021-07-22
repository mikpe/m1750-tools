/*
 * t-nanosleep.c - measure time for nanosleep (0)
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
 * $Log: t-nanosleep.c,v $
 * Revision 1.1  1997/07/27 10:29:11  nettleto
 * Initial revision
 *
 */

#include <pthread.h>
#include <report.h>
#include <time.h>

#define ntimes 100

void
run_test ()
{
  struct timespec rqtp, rmtp;
  int ans;
  int cnt;
  clock_t t0, t1;
  double tans;

  rqtp.tv_sec = 0;
  rqtp.tv_nsec = 0;

  t0 = clock ();
  for (cnt = 1; cnt <= ntimes; cnt++)
    {
      ans = nanosleep (&rqtp, &rmtp);
      if (ans < 0)
        {
          failed ("nanosleep returned %d", ans);
          return;
        }
    }
  t1 = clock ();

  if (rmtp.tv_sec != 0 || rmtp.tv_nsec != 0)
    failed ("nanosleep remainder non zero");

  tans = (double)(t1 - t0) / ntimes / CLOCKS_PER_SEC * 1.0e6;
  comment ("time for one call of nanosleep = %ld uSec", (long)tans);

  /* nanosleep (0) should delay for one clock tick (10 mSec) */
  if (tans < 9.9e-3)
    failed ("nanosleep returned too soon");
}


int
main (int argc, char *argv[])
{
  pthread_init ();

  test ("t-nanosleep", "measure time for nanosleep (0)");

  run_test ();

  result ();
}
