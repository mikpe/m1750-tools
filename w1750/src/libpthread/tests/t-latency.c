/*
 * t-latency.c - measure interrupt latency time using pthread_cond_wait
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
 * $Log: t-latency.c,v $
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
static volatile unsigned t1;   /* handler entered */
static volatile unsigned t2;   /* thread started */

pthread_mutex_t m1;
pthread_cond_t c1;


void
level1_handler (int i)
{
  asm volatile ("xio    %0,ita" : "=r" (t1));

  pthread_cond_signal (&c1);
}


void *
new_thread (void *arg)
{
  sleep (1);

  /* Get time for interrupt */
  asm volatile ("xio    %0,ita" : "=r" (t0));

  /* Raise level 1 interrupt.  */
  asm volatile ("xio   %0,spi" :: "r" (0x0008));
}


int
main ()
{
  pthread_t thread;
  struct sched_param param;
  int ans;
  int r;

  pthread_init ();

  test ("t-latency", "measure interrupt latency time using pthread_cond_wait");

  handler (INTLEVEL1, level1_handler);
  set_mk (0xc108);

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

  pthread_mutex_init (&m1, NULL);
  pthread_cond_init (&c1, NULL);

  pthread_mutex_lock (&m1);

  pthread_cond_wait (&c1, &m1);

  asm volatile ("xio    %0,ita" : "=r" (t2));
 
  pthread_mutex_unlock (&m1);


  /* Print report.  */
  comment ("t0 = %d", t0);
  comment ("t1 = %d, t1 - t0 = %d, = %d usec", t1, t1 - t0, (t1 - t0) * 10);
  comment ("t2 = %d, t2 - t0 = %d, = %d usec", t2, t2 - t0, (t2 - t0) * 10);

  result ();
}


