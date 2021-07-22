/*
 * pthread_q_timed_enq - internal.
 * pthread_timed_sigwait - internal.
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
 * $Log: pthread_timed_sigwait.c,v $
 * Revision 1.3  1997/07/23 09:47:46  nettleto
 * Removed LE0_NTIME test on relative delays to agree with
 * POSIX, and introduced a tmp so that we don't modify the
 * argument 'timeout'.
 *
 * Revision 1.2  1997/07/18 16:33:51  nettleto
 * Added L to long numeric literals
 *
 * Revision 1.1  1997/07/17 09:40:28  nettleto
 * Initial revision
 *
 */

#include "pthread_internals.h"


/*
 * enqueing a pthread into a list sorted by time
 */
static inline void
pthread_q_timed_enq (
		      pthread_t p)
{
  pthread_t prev = NO_PTHREAD, next = pthread_timer;

  while (next != NO_PTHREAD && GT_NTIME (p->tp, next->tp))
    {
      prev = next;
      next = next->next_in_timer_q;
    }
  p->next_in_timer_q = next;
  if (prev == NO_PTHREAD)
    pthread_timer = p;
  else
    prev->next_in_timer_q = p;
}

/*-- - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/
/*
 * suspend running thread until specified time
 * Return -1 if error, 0 otherwise
 * assumes SET_KERNEL_FLAG
 */
int
pthread_timed_sigwait (
			pthread_t p,
			struct timespec *timeout,
			int mode)
{
  struct timespec now;

  if (!timeout || timeout->tv_sec < 0L ||
      timeout->tv_nsec < 0L || timeout->tv_nsec >= 1000000000L)
    {
      set_errno (EINVAL);
      return (-1);
    }
  clock_gettime (CLOCK_REALTIME, &now);

  if (mode == ABS_TIME)
    {
      if (GTEQ_NTIME (now, *timeout))
	{
	  set_errno (EAGAIN);
	  return (-1);
	}
      p->tp = *timeout;
    }
  else if (mode == REL_TIME)
    {
      struct timespec tmp = *timeout;

      PLUS_NTIME (tmp, now, *timeout);
      p->tp = tmp;
    }
  else
    {
      set_errno (EINVAL);
      return (-1);
    }

  /*
   * queue up current thread on the timer queue
   */
  pthread_q_timed_enq (p);

  return (0);
}
