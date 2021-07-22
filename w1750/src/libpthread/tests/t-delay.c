/*
 * t-delay.c - check accuracy of nanosleep
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
 * $Log: t-delay.c,v $
 * Revision 1.1  1997/07/27 10:29:08  nettleto
 * Initial revision
 *
 */

#include <pthread.h>
#include <math.h>
#include <report.h>


#define N 5

int done;


void
delay (double s)
{
  struct timespec rqtp, rmtp;
  double i;
  double nsec = modf (s, &i) * 1.0e9;
  int ans;

  rqtp.tv_sec = (long)i; 
  rqtp.tv_nsec = (long)nsec;

  ans = nanosleep (&rqtp, &rmtp);
  if (ans < 0)
    failed ("nanosleep returned %d", ans);

  if (rmtp.tv_sec != 0 || rmtp.tv_nsec != 0)
    failed ("nanosleep remainder non zero");
}


void *
body (void *arg)
{
  int i;
  int priority = (int) arg;

  while (!done)
    {
      for (i = 0; i < 500; i++)
        ;
      delay (0.01);
    }
}


int
t1 (double d)
{
  unsigned t1, t2;
  double timer_b_period = 100.0e-6;
  double average_d;
  double total_time = 0.0;
  int cnt;
  int ntimes;
  int too_short = 0;

  asm volatile ("xio    %0,otb" :: "r" (0));

  /* work out how many times we should do the delay to get
     a statically good result, but without making the test
     test too long.
  */
  if (d >= 0.01)
    ntimes = (int)(2.0 / d);
  else
    ntimes = 200;

  for (cnt = 1; cnt <= ntimes; cnt++)
    {
      double measured_d;

      asm volatile ("xio    %0,itb" : "=r" (t1));
      delay (d);
      asm volatile ("xio    %0,itb" : "=r" (t2));

      measured_d = (double)(t2 - t1) * timer_b_period;
      total_time += measured_d;

      if (measured_d < d - 0.005)
        too_short = 1;
    }

  average_d = total_time / ntimes;
  
  if (too_short)
    {
      failed ("delay too short, d = %e, average_d = %e, err = %e", d, average_d, d - average_d);
    }

  comment ("ntimes = %d, d = %e, average delay = %e", ntimes, d, average_d);

  /* Keep the watchdog timer happy.  */
  asm ("xio    r0,go");
}


int
main (int argc, char *argv [])
{
  double d;
  double step = pow (10.0, 1.0 / 5.0);
  pthread_t t[N];
  int i;

  struct sched_param param;

  pthread_init ();

  /* Set priority of main thread. */
  param.sched_priority = 100;
  pthread_setschedparam (pthread_self (), SCHED_FIFO, &param);

  test ("t-delay", "accuracy of nanosleep");

  /* Create N competing threads, lowest priority first. */
  for (i = 0; i < N; i++)
    {
      if (pthread_create (&t[i], NULL, body, (void *) (50 + i)))
        {
          printf ("pthread_create failed\n");
          exit (2);
        }

      param.sched_priority = 50 + i;
      pthread_setschedparam (t[i], SCHED_FIFO, &param);
    }

  /* Set priority of main thread. */
  param.sched_priority = 53;
  pthread_setschedparam (pthread_self (), SCHED_FIFO, &param);

  d = 1.0;
  while (d > 1.0e-4)
    {
      t1 (d);
      d /= step;
    }
  done =1;

  result ();  
}


