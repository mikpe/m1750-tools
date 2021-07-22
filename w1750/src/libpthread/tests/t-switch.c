/*
 * Test t-switch.c : measures time for a context switch
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
 * $Log: t-switch.c,v $
 * Revision 1.1  1997/08/02 08:17:53  nettleto
 * Initial revision
 *
 */

#include <time.h>
#include <pthread.h>
#include <report.h>

#include <errno.h>
#include <intrrpt.h>
#include <signal.h>


int timer_b_period = 100;	/* usecs */

int
test_1 ()
{
  pthread_mutex_t m;
  unsigned t1, t2;
  int i;
  int ntimes = 10000;
  double ans;

  asm ("xio    %0,otb": :"r" (0));
  asm ("xio    %0,itb":"=r" (t1));

  for (i = 1; i <= ntimes; i++)
    {
      asm volatile ("bex    1");
    }

  asm ("xio    %0,itb":"=r" (t2));
  ans = (double)(t2 - t1) * timer_b_period / ntimes;

  comment ("Time for one context switch = %ld usecs",
    (long)ans);
}


main ()
{
  pthread_init ();

  test ("t-switch", "measures time for a context switch");

  test_1 ();

  result ();
}

