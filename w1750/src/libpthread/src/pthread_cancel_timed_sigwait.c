/*
 * pthread_q_timed_deq - internal.
 * pthread_q_timed_wakeup_thread - internal.
 * pthread_cancel_timed_sigwait - internal.
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
 * $Log: pthread_cancel_timed_sigwait.c,v $
 * Revision 1.2  1997/07/18 16:32:16  nettleto
 * Added inline to functions called once
 *
 * Revision 1.1  1997/07/17 09:40:19  nettleto
 * Initial revision
 *
 */

#include "pthread_internals.h"


/*
 * dequeue thread from (timer) queue
 */
static inline void
pthread_q_timed_deq (
		      pthread_t t)
{
  pthread_t prev = NO_PTHREAD, next = pthread_timer;

  while (next && next != t)
    {
      prev = next;
      next = next->next_in_timer_q;
    }
  if (next == NO_PTHREAD)
    return;

  if (prev == NO_PTHREAD)
    pthread_timer = next->next_in_timer_q;
  else
    prev->next_in_timer_q = next->next_in_timer_q;

  t->next_in_timer_q = NO_PTHREAD;
}

/*-- - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/
/*
 * same as pthread_q_wakeup_thread but for timer queue
 */
static inline void
pthread_q_timed_wakeup_thread (
				pthread_t p,
				int activate)
{
  pthread_q_timed_deq (p);

  if (activate && p != NO_PTHREAD && !(p->state & T_RUNNING))
    {
      p->state &= ~(T_BLOCKED | T_INTR_POINT);
      p->state |= T_RUNNING;
      pthread_q_enq (&ready, p);
    }
}

/*-- - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/
/*
 * dequeue thread waiting on timer only
 * set error in both thread structure and global errno
 * assumes SET_KERNEL_FLAG
 */
void
pthread_cancel_timed_sigwait (
			       pthread_t p,
			       int signaled,
			       int activate)
{
  struct timespec now;
  int time_read = 0;

  if (pthread_timer != NO_PTHREAD)
    {

      do
	{
	  if (p->state & T_CONDTIMER)
	    {
	      p->state &= ~(T_CONDTIMER | T_SYNCTIMER);
	      pthread_q_deq (p->queue, p);
	      if (signaled)
		{
		  p->errno = EAGAIN;

		  if (p == mac_pthread_self ())
		    set_errno (EAGAIN);
		}
	    }
	  else
	    {
	      p->state &= ~T_SYNCTIMER;
	    }

	  pthread_q_timed_wakeup_thread (p, activate);

	  p = pthread_timer;
	  if (p != NO_PTHREAD && !time_read)
	    {
	      clock_gettime (CLOCK_REALTIME, &now);
	      time_read++;
	    }

	  signaled = TRUE;
	  activate = TRUE;

	}
      while (p && GTEQ_NTIME (now, p->tp));
    }
}
