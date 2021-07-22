/*
 * pthread_setschedparam - POSIX 13.5.2.
 *  
 * #include <pthread.h>
 * int pthread_setschedparam (
 *    pthread_t thread,
 *    int policy,
 *    struct sched_param *param);
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
 * $Log: pthread_setschedparam.c,v $
 * Revision 1.1  1997/07/17 09:40:27  nettleto
 * Initial revision
 *
 */

#include "pthread_internals.h"


/*
 * Set the thread specific scheduling attributes
 */
int
pthread_setschedparam (
			pthread_t thread,
			int policy,
			struct sched_param *param)
{
  pthread_t p = mac_pthread_self ();
  pthread_queue_t q;
  int run_prio;

  if (thread == NO_PTHREAD)
    {
      set_errno (ESRCH);
      return (-1);
    }

  if (policy != SCHED_FIFO
      || param->sched_priority < MIN_PRIORITY
      || param->sched_priority > MAX_PRIORITY)
    {
      set_errno (EINVAL);
      return (-1);
    }

  SET_KERNEL_FLAG;

  if (thread->state & T_RETURNED)
    {
      CLEAR_KERNEL_FLAG;
      set_errno (EINVAL);
      return (-1);
    }

  thread->attr.sched = policy;
  run_prio = thread->attr.prio;
  thread->attr.prio = param->sched_priority;
  q = thread->queue;
  if (q->head != thread ||
      (q->head != q->tail && thread->attr.prio < run_prio &&
       thread->attr.prio < thread->next_in_primary_q->attr.prio))
    {
      pthread_q_deq (q, thread);
      pthread_q_enq (q, thread);
    }

  CLEAR_KERNEL_FLAG;

  return (0);
}
