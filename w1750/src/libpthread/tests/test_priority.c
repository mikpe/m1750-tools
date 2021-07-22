/*
 * test-priority.c - check threads run in priority order
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
 * $Log: test_priority.c,v $
 * Revision 1.2  1997/08/11 14:16:46  nettleto
 * Fixed minor typo in comment
 *
 * Revision 1.1  1997/07/27 10:29:13  nettleto
 * Initial revision
 *
 */

#include <pthread.h>
#include <report.h>


static const int N = 5;		/* number of threads to create */
static int counts[100];		/* one for each priority level */


void *
body (void *arg)
{
  int i;
  int priority = (int) arg;

  comment ("body at priority %d", priority);

  for (i = 1; i <= 10; i++)
    {
      int j;

      counts[priority]++;
      sched_yield ();

      for (j = 0; j < priority; j++)
	counts[j] = 0;
    }

}


int
main ()
{
  pthread_t t[5];
  int i;

  int error;
  struct sched_param param;

  pthread_init ();

  /* Set priority of main thread. */
  param.sched_priority = 100;
  pthread_setschedparam (pthread_self (), SCHED_FIFO, &param);

  test ("test_priority", "%d threads run in priority order", N);

  /* Create N threads, lowest priority first. */
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

  comment ("this is the main thread at priority 100");

  for (i = 0; i < N; i++)
    counts[i] = 0;

  /* Set priority of main thread. This should allow most of the 
     threads to run. */
  param.sched_priority = 51;
  pthread_setschedparam (pthread_self (), SCHED_FIFO, &param);

  comment ("this is the main thread at priority 51");

  /* Check the lowest priority thread did not run at all.  */
  if (counts[50] != 0)
    {
      failed ("counts [50] = %d", i, counts[50]);
    }

  /* Check the next lowest priority thread ran once. (i.e. ran
     to the first sched_yield, where control was passed to the
     main thread as required by SCHED_FIFO.  */
  if (counts[51] != 1)
    {
      failed ("counts [51] = %d", i, counts[51]);
    }

  /* check each thread above main thread priority has run 10 times */
  for (i = 2; i < N; i++)
    {
      if (counts[50 + i] != 10)
	failed ("counts [%d] = %d", 50 + i, counts[50 + i]);
    }

  result ();
}
