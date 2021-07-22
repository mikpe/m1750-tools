/*
 * #include <pthread.h>
 * void pthread_init (void);
 *  
 * Copyright (C) 1992, 1993, 1994, 1995, 1996 the Florida State University
 * GCC-1750 changes Copyright (c) 1997, Chris Nettleton Software
 * 
 * This file is part of the GCC-1750 library. It is based on Pthreads
 * distributed by Florida State University and contains modifications for
 * GCC-1750 made under European Space Agency contract 11935/96/NL/JG.
 * 
 * This file is free software; you can redistribute it and/or modify it
 * under the terms of the GNU Library General Public License as published
 * by the Free Software Foundation (version 2).
 * 
 * This file is distributed "AS IS" in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Library General Public License for more details.
 * 
 * You should have received a copy of the GNU Library General Public
 * License along with Pthreads; see the file COPYING.  If not, write to
 * the Free Software Foundation, 675 Mass Ave, Cambridge, MA 02139, USA.
 * 
 * $Log: pthread_init.c,v $
 * Revision 1.3  1997/07/18 16:29:37  nettleto
 * thread id removed
 *
 * Revision 1.2  1997/07/17 14:13:14  nettleto
 * Added thread id.
 *
 * Revision 1.1  1997/07/17 09:40:23  nettleto
 * Initial revision
 *
 */

#define PTHREAD_KERNEL
#include "pthread_internals.h"


/*
 * pthread_timer_handler - internal.
 */
void
pthread_timer_handler (
			int i)
{
  pthread_t p;

  /* Increment pthread time */
  timeofday.tv_nsec += 10000000L;
  if (timeofday.tv_nsec >= 1000000000L)
    {
      timeofday.tv_nsec -= 1000000000L;
      timeofday.tv_sec++;
    }

  DISABLE_INTERRUPTS;

  if ((p = pthread_timer) && GTEQ_NTIME (timeofday, p->tp))
    pthread_cancel_timed_sigwait (p, TRUE, p->queue != &ready);

  ENABLE_INTERRUPTS;

  if (state_change)
    {
      state_change = FALSE;
      asm ("bex 1");
    }
}

/*-- - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/
/*
 * pthread_init - must be called first!
 * initialize the threads package. This function is
 * the first function that be called by any program using this package.
 * It initializes the main thread and sets up a stackspace for all the
 * threads to use. Its main purpose is to setup the mutexes and
 * condition variables and allow one to access them.
 */
void
pthread_init (
	       void)
{
  pthread_t t;
  int i;

  /*
   * initialize kernel structure
   */

  pthread_queue_init (&ready);
  pthread_timer_queue_init;

  pthread_attr_init (&pthread_attr_default);

  t = (pthread_t) calloc (1, sizeof (struct pthread));
  t->func = (pthread_func_t) 0;
  t->arg = (any_t *) NULL;
  t->state = T_MAIN | T_RUNNING | T_CONTROLLED;

  /*
   * Initialize the main thread's stack
   * with dummy stack base which can be freed
   */
  t->attr.stacksize = MAIN_STACKSIZE;
  t->stack_base = (char *) malloc (sizeof (int));

  t->attr.prio = MIN_PRIORITY;
  t->attr.sched = SCHED_FIFO;

  mac_pthread_self () = t;
  pthread_q_enq (&ready, t);
  state_change = FALSE;
  n_pthreads = 1;		/* main thread counts, fd_server does not count */
  n_keys = 0;

  timeofday.tv_sec = 0L;
  timeofday.tv_nsec = 0L;
  handler (17, pthread_switch_handler);
  handler (INTTIMERA, pthread_timer_handler);
  ENABLE_INTERRUPTS;
}
