/*
 * pthread_cleanup_push - POSIX 18.2.3.
 * pthread_cleanup_pop - POSIX 18.2.3.
 *  
 * #include <pthread.h>
 * int pthread_cleanup_push_body (
 *    void (*func) (),
 *    any_t arg,
 *    cleanup_t new);
 *  
 * int pthread_cleanup_pop_body (
 *    int execute);
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
 * $Log: pthread_cleanup_push_pop.c,v $
 * Revision 1.1  1997/07/17 09:40:19  nettleto
 * Initial revision
 *
 */

#include "pthread_internals.h"


/*
 * push function on current thread's cleanup stack
 * and execute it with the specified argument when the thread.
 * Notice: pthread_cleanup_push_body() receives the address of the first
 * cleanup structure in an additional parameter "new".
 * (a) exits;
 * (b) is cancelled;
 * (c) calls pthread_cleanup_pop(0 with a non-zero argument;
 * (d) NOT IMPLEMENTED, CONTROVERSIAL: when a longjump reaches past the scope.
 */
int
pthread_cleanup_push_body (
			    void (*func) (),
			    any_t arg,
			    cleanup_t new)
{
  pthread_t p = mac_pthread_self ();

  if (!func)
    {
      set_errno (EINVAL);
      return (-1);
    }

  new->func = func;
  new->arg = arg;

  SET_KERNEL_FLAG;
  new->next = p->cleanup_top;
  p->cleanup_top = new;
  CLEAR_KERNEL_FLAG;

  return (0);
}

/*-- - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/
/*
 * pop function off current thread's cleanup stack
 * and execute it with the specified argument if non-zero
 */
int
pthread_cleanup_pop_body (
			   int execute)
{
  pthread_t p = mac_pthread_self ();
  cleanup_t new;

  SET_KERNEL_FLAG;
  if (!(new = p->cleanup_top))
    {
      CLEAR_KERNEL_FLAG;
      set_errno (EINVAL);
      return (-1);
    }
  p->cleanup_top = new->next;
  CLEAR_KERNEL_FLAG;

  if (execute)
    (new->func) (new->arg);

  return (0);
}
