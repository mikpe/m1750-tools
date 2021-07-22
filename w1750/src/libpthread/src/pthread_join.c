/*
 * pthread_join - POSIX 16.2.3.
 *  
 * #include <pthread.h>
 * int pthread_join (
 *    pthread_t thread,
 *    any_t *status);
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
 * $Log: pthread_join.c,v $
 * Revision 1.1  1997/07/17 09:40:23  nettleto
 * Initial revision
 *
 */

#include "pthread_internals.h"


/*
 * Wait for a thread to exit. If the status parameter is
 * non-NULL then that threads exit status is stored in it.
 */
int
pthread_join (
	       pthread_t thread,
	       any_t * status)
{
  register pthread_t p = mac_pthread_self ();

  if (thread == NO_PTHREAD)
    {
      set_errno (EINVAL);
      return (-1);
    }

  if (thread == p)
    {
      set_errno (EDEADLK);
      return (-1);
    }

  SET_KERNEL_FLAG;

  if (thread->state & T_RETURNED)
    {
      if (thread->state & T_DETACHED)
	{
	  CLEAR_KERNEL_FLAG;
	  set_errno (ESRCH);
	  return (-1);
	}

      if (status)
	*status = thread->result;

      thread->state |= T_DETACHED;

      free (thread->stack_base);
      free (thread);

      CLEAR_KERNEL_FLAG;
      return (0);
    }

  /*
   * clear error number before suspending
   */
  set_errno (0);

  pthread_q_sleep (&thread->joinq);
  p->state |= T_INTR_POINT;
  CLEAR_KERNEL_FLAG;

  if (get_errno () == EINTR)
    return (-1);

  /*
   * status was copied into result field of current TCB by other thread
   */
  if (status)
    *status = p->result;

  return (0);
}
