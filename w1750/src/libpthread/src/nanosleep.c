/*
 * nanosleep - POSIX 14.2.5.
 *  
 * #include <pthread.h>
 * int nanosleep (
 *    const struct timespec *rqtp,
 *    struct timespec *rmtp);
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
 * $Log: nanosleep.c,v $
 * Revision 1.1  1997/07/17 09:40:11  nettleto
 * Initial revision
 *
 */

#include "pthread_internals.h"


/*
 * suspend until time interval specified by "rqtp" has passed
 * or a user handler is invoked or the thread is canceled
 */
int
nanosleep (
	    const struct timespec *rqtp,
	    struct timespec *rmtp)
{
  register pthread_t p = mac_pthread_self ();
  struct timespec now;

  if (rmtp)
    rmtp->tv_sec = rmtp->tv_nsec = 0;

  SET_KERNEL_FLAG;

  if (pthread_timed_sigwait (p, rqtp, REL_TIME) == -1)
    {
      CLEAR_KERNEL_FLAG;
      return (-1);
    }

  /*
   * clear error number before suspending
   */
  set_errno (0);

  p->state &= ~T_RUNNING;
  p->state |= T_BLOCKED | T_SYNCTIMER | T_INTR_POINT;
  pthread_q_deq_head (&ready);
  CLEAR_KERNEL_FLAG;

  /*
   * Check if condition was signaled or time-out was exceeded.
   */
  if (get_errno () == EINTR)
    {
      clock_gettime (CLOCK_REALTIME, &now);
      if (pthread_timer = p)
	if (GT_NTIME (p->tp, now))
	  {
	    if (rmtp)
	      MINUS_NTIME (*rmtp, p->tp, now);
	    return (-1);
	  }
    }

  return (0);
}
