/*
 * pthread_once - POSIX 16.2.8.
 *  
 * #include <pthread.h>
 * int pthread_once (
 *    pthread_once_t * once_control,
 *    void (*init_routine) (void));
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
 * $Log: pthread_once.c,v $
 * Revision 1.1  1997/07/17 09:40:25  nettleto
 * Initial revision
 *
 */

#include "pthread_internals.h"


/*
 * The first call to this will call the init_routine()
 * with no arguments. Subsequent calls to pthread_once()
 * will not call the init_routine.
 */
int
pthread_once (
	       pthread_once_t * once_control,
	       void (*init_routine) (void))
{
  SET_KERNEL_FLAG;
  if (!once_control->init)
    {
      once_control->init = TRUE;
      pthread_mutex_init (&once_control->mutex, NULL);
    }
  CLEAR_KERNEL_FLAG;

  pthread_mutex_lock (&once_control->mutex);
  if (!once_control->exec)
    {
      once_control->exec = TRUE;
      (*init_routine) ();
    }
  pthread_mutex_unlock (&once_control->mutex);

  return (0);
}
