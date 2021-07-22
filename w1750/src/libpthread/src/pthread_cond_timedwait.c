/*
 * pthread_cond_timedwait - POSIX 11.4.4.
 *  
 * #include <pthread.h>
 * int pthread_cond_timedwait (
 *    pthread_cond_t * cond,
 *    pthread_mutex_t * mutex,
 *    struct timespec *timeout);
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
 * $Log: pthread_cond_timedwait.c,v $
 * Revision 1.1  1997/07/17 09:40:21  nettleto
 * Initial revision
 *
 */

#include "pthread_internals.h"


/*
 * This function works in the same way as
 * pthread_cond_wait with the exception of the added complexity of
 * the timeout. The timeout is delivered as a timeout event. If the
 * timeout happened then the thread is put back on the active queue.
 */
int
pthread_cond_timedwait (
			 pthread_cond_t * cond,
			 pthread_mutex_t * mutex,
			 struct timespec *timeout)
{
  register pthread_t p = mac_pthread_self ();

  if (cond == NO_COND || mutex == NO_MUTEX ||
      (cond->mutex != mutex && cond->mutex != NO_MUTEX) ||
      !(mutex->lock) || mutex->owner != p)
    {
      set_errno (EINVAL);
      return (-1);
    }

  SET_KERNEL_FLAG;
  if (pthread_timed_sigwait (p, timeout, ABS_TIME) == -1)
    {
      CLEAR_KERNEL_FLAG;
      return (-1);
    }

  /*
   * clear error number before suspending
   */
  set_errno (0);

  cond->mutex = mutex;
  cond->waiters++;
  p->cond = cond;

  mac_mutex_unlock (mutex, p, pthread_q_sleep (&cond->queue));
  p->state |= T_CONDTIMER | T_SYNCTIMER | T_INTR_POINT;
  CLEAR_KERNEL_FLAG;

  /*
   * relock the mutex under contention, but only if it was not already
   * locked as a side-effect of executing an signal handler.
   */
  SET_KERNEL_FLAG;
  if (mutex->owner != p)
    {
      mac_mutex_lock (mutex, p);
      if (!--p->cond->waiters)
	cond->mutex = NO_MUTEX;
      p->cond = NO_COND;
    }
  CLEAR_KERNEL_FLAG;

  if (get_errno ())
    return (-1);

  return (0);
}
