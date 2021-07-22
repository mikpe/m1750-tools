/*
 * pthread_cond_broadcast - POSIX 11.4.3.
 *  
 * #include <pthread.h>
 * int pthread_cond_broadcast (
 *    pthread_cond_t *cond);
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
 * $Log: pthread_cond_broadcast.c,v $
 * Revision 1.1  1997/07/17 09:40:20  nettleto
 * Initial revision
 *
 */

#include "pthread_internals.h"


/*
 * Step through the queue of waiting threads
 * and send a signal event to every thread.
 * The mutex ownership is tranferred right away, unless the mutex protocol
 * is the ceiling protocol.
 */
int
pthread_cond_broadcast (
			 pthread_cond_t * cond)
{
  pthread_t p;

  if (cond == NO_COND)
    {
      set_errno (EINVAL);
      return (-1);
    }
  SET_KERNEL_FLAG;
  while ((p = cond->queue.head) != NO_PTHREAD)
    if (p->state & T_SYNCTIMER)
      pthread_cancel_timed_sigwait (p, FALSE, TRUE);
    else
      {
	p->state &= ~T_CONDTIMER;
	pthread_q_wakeup (&cond->queue);
      }
  CLEAR_KERNEL_FLAG;

  return (0);
}
