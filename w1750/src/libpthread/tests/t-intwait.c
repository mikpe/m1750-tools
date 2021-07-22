/*
 * t-intwait.c - measure interrupt latency time using intwait
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
 * $Log: t-intwait.c,v $
 * Revision 1.1  1997/07/27 10:29:10  nettleto
 * Initial revision
 *
 */

#include <pthread.h>
#include <report.h>
#include <intrrpt.h>

/*
 * Recorded times, in 10 usec steps
 */
static volatile unsigned t0;   /* interrupt raised */
static volatile unsigned t1;   /* thread started */


void *
new_thread (void *arg)
{
  sleep (1);

  /* Get time for interrupt */
  asm volatile ("xio    %0,ita" : "=r" (t0));

  /* Raise level 1 interrupt.  */
  asm volatile ("xio   %0,spi" :: "r" (_intmask (INTLEVEL1)));
}


int
main ()
{
  pthread_t thread;
  struct sched_param param;
  int ans;
  int r;

  pthread_init ();

  test ("t-intwait", "measure interrupt latency time using intwait");

  if (ans = pthread_create (&thread, NULL, new_thread, (void *) 0xdeadbeef))
    {
      failed ("pthread_create, ans = %d", ans);
    }

  /* Set main thread to high priority.  */
  param.sched_priority = 100;
  pthread_setschedparam (pthread_self (), SCHED_FIFO, &param);

  /* Set thread that raises interrupt to low priority.  */
  param.sched_priority = 0;
  pthread_setschedparam (thread, SCHED_FIFO, &param);

  /* Set timer B to interrupt 1000 uSecs from now */
  asm volatile ("xio    %0,otb" :: "r" (-100));

  /* Wait for timer B interrupt */
  ans = intwait (_intmask (INTTIMERB));
  if (ans != INTTIMERB)
    failed ("first intwait returned %d", ans);

  /* Wait for level 1 interrupt (about one second) */
  ans = intwait (_intmask (INTLEVEL1));

  /* Read timer A */
  asm volatile ("xio    %0,ita" : "=r" (t1));

  if (ans != INTLEVEL1)
    failed ("second intwait return %d", ans); 

  /* Print report.  */
  comment ("t0 = %d", t0);
  comment ("t1 = %d, t1 - t0 = %d, = %d usec", t1, t1 - t0, (t1 - t0) * 10);

  result ();
}


