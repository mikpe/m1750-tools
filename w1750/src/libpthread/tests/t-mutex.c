/*
 * t-mutex.c - mutex timing tests
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
 * $Log: t-mutex.c,v $
 * Revision 1.1  1997/07/27 10:29:11  nettleto
 * Initial revision
 *
 */

#include <pthread.h>

#include <errno.h>
#include <report.h>


static double timer_b_period = 100.0;
static int ntimes = 10000;


int
test_mutex_1 ()
{
  pthread_mutex_t m;
  unsigned t1, t2;
  int i;

  asm ("xio    %0,otb": :"r" (0));
  asm ("xio    %0,itb":"=r" (t1));

  for (i = 1; i <= ntimes; i++)
    {
      int ans = pthread_mutex_init (&m, NULL);

      if (ans)
	{
	  failed ("pthread_mutex_init returned %d", ans);
	  return;
	}
    }

  asm ("xio    %0,itb":"=r" (t2));

  comment ("Time for pthread_mutex_init = %d usecs",
	   (int)((double) (t2 - t1) * timer_b_period / ntimes));
}


int
test_mutex_2 ()
{
  pthread_mutex_t m;
  unsigned t1, t2;
  int i;

  asm ("xio    %0,otb": :"r" (0));
  asm ("xio    %0,itb":"=r" (t1));

  for (i = 1; i <= ntimes; i++)
    {
      pthread_mutex_lock (&m);
      pthread_mutex_unlock (&m);
    }

  asm ("xio    %0,itb":"=r" (t2));

  comment ("Time for lock and unlock = %d usecs",
	   (int)((double) (t2 - t1) * timer_b_period / ntimes));
}


int
main ()
{
  pthread_init ();

  test ("t-mutex", "mutex timing tests");

  test_mutex_1 ();
  test_mutex_2 ();

  result ();
}

