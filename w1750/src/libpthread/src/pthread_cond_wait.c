/*
 * pthread_cond_wait - POSIX 11.4.4.
 *  
 * #include <pthread.h>
 * int pthread_cond_wait (
 *    pthread_cond_t *cond,
 *    pthread_mutex_t *mutex);
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
 * $Log: pthread_cond_wait.c,v $
 * Revision 1.1  1997/07/17 09:40:21  nettleto
 * Initial revision
 *
 */

#include "pthread_internals.h"


/*
 * Atomically releases the mutex and causes the
 * thread to block on condition variable cond. The thread is taken
 * off the thread queues and queued onto condition variable with the
 * state changed to indicate the wait. The thread is then blocked
 * waiting for an event. This will be a signal event meaning that the
 * condition has been signalled or broadcast.  If it was signalled
 * the thread has already been reactivated and so the mutex is reaquired
 * and return.
 */
int
pthread_cond_wait (
		    pthread_cond_t * cond,
		    pthread_mutex_t * mutex)
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

  /*
   * clear error number before suspending
   */
  set_errno (0);

  cond->mutex = mutex;
  cond->waiters++;
  p->cond = cond;

  mac_mutex_unlock (mutex, p, pthread_q_sleep (&cond->queue));
  p->state |= T_INTR_POINT;
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
