/*
 * pthread_mutex_lock - POSIX 11.3.3.
 *  
 * #include <pthread.h>
 * int pthread_mutex_lock (pthread_mutex_t * mutex);
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
 * $Log: pthread_mutex_lock.c,v $
 * Revision 1.1  1997/07/17 09:40:24  nettleto
 * Initial revision
 *
 */

#include "pthread_internals.h"

/*
 * Checks are made to see if the mutex is
 * currently in use or not.  If the mutex is not in use, then its
 * locked. Otherwise the currently executing thread is put in the
 * wait queue and a new thread is selected.
 */
int
pthread_mutex_lock (pthread_mutex_t * mutex)
{
  pthread_t p = mac_pthread_self ();

  if (mutex == NO_MUTEX)
    {
      set_errno (EINVAL);
      return (-1);
    }

  if (mutex->owner == p)
    {
      set_errno (EDEADLK);
      return (-1);
    }

  SET_KERNEL_FLAG;
  mac_mutex_lock (mutex, p);
  CLEAR_KERNEL_FLAG;

  return (0);
}
