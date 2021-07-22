/*
 * pthread_detach - POSIX 16.2.4.
 *  
 * #include <pthread.h>
 * int pthread_detach (
 *    pthread_t *thread_ptr);
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
 * $Log: pthread_detach.c,v $
 * Revision 1.1  1997/07/17 09:40:22  nettleto
 * Initial revision
 *
 */

#include "pthread_internals.h"


/*
 * Detaching a running thread simply consists of marking it as such.
 * If the thread has returned then the resources are also freed.
 */
int
pthread_detach (
		 pthread_t * thread_ptr)
{
  pthread_t thread;

  if ((thread_ptr == NULL) || (*thread_ptr == NO_PTHREAD))
    {
      set_errno (EINVAL);
      return (-1);
    }

  thread = *thread_ptr;

  SET_KERNEL_FLAG;

  if (thread->state & T_DETACHED)
    {
      CLEAR_KERNEL_FLAG;
      set_errno (ESRCH);
      return (-1);
    }

  thread->state |= T_DETACHED;

  if (thread->state & T_RETURNED)
    {
      free (thread->stack_base);
      free (thread);
      *thread_ptr = NO_PTHREAD;
    }

  CLEAR_KERNEL_FLAG;

  return (0);
}
