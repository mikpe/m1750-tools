/*
 * pthread_mutex_trylock - POSIX 11.3.3.
 *  
 * #include <pthread.h>
 * int pthread_mutex_trylock (pthread_mutex_t *mutex);
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
 * $Log: pthread_mutex_trylock.c,v $
 * Revision 1.1  1997/07/17 09:40:24  nettleto
 * Initial revision
 *
 */

#include "pthread_internals.h"


/*
 * Just try to lock the mutex. If lock succeeds return.
 * Otherwise return right away without getting the lock.
 */
int
pthread_mutex_trylock (
			pthread_mutex_t * mutex)
{

  pthread_t p = mac_pthread_self ();

  if (mutex == NO_MUTEX)
    {
      set_errno (EINVAL);
      return (-1);
    }

  SET_KERNEL_FLAG;
  if (mutex->lock)
    {
      CLEAR_KERNEL_FLAG;
      set_errno (EBUSY);
      return (-1);
    }

  mutex->lock = TRUE;
  mutex->owner = p;

  CLEAR_KERNEL_FLAG;

  return (0);
}
