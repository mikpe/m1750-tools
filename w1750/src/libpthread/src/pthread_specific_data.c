/*
 * pthread_key_create - POSIX 17.1.1.
 * pthread_getspecific - POSIX 17.1.2.
 * pthread_setspecific - POSIX 17.1.2.
 *  
 * #include <pthread.h>
 * int pthread_key_create (
 *    pthread_key_t * key,
 *    void (*destructor) ());
 *
 * any_t pthread_getspecific (pthread_key_t key);
 *
 * int pthread_setspecific (
 *    pthread_key_t key,
 *    any_t value);
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
 * $Log: pthread_specific_data.c,v $
 * Revision 1.1  1997/07/17 09:40:27  nettleto
 * Initial revision
 *
 */

#include "pthread_internals.h"


/*
 * creates a new global key and spefies destructor call
 * returns -1 upon error with errno ENOMEM if name space exhausted,
 *                                  EAGAIN if insufficient memory.
 */
int
pthread_key_create (
		     pthread_key_t * key,
		     void (*destructor) ())
{
  SET_KERNEL_FLAG;

  if (n_keys >= _POSIX_DATAKEYS_MAX)
    {
      CLEAR_KERNEL_FLAG;
      set_errno (ENOMEM);
      return (-1);
    }

  key_destructor[n_keys] = destructor;
  *key = n_keys++;
  CLEAR_KERNEL_FLAG;
  return (0);
}

/*-- - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/
/*
 * associate a value with a data key for some thread
 * returns -1 upon error with errno EINVAL if the key is invalid.
 */
int
pthread_setspecific (
		      pthread_key_t key,
		      any_t value)
{
  if (key < 0 || key >= n_keys)
    {
      set_errno (EINVAL);
      return (-1);
    }

  mac_pthread_self ()->key[key] = value;
  return (0);
}

/*-- - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/
/*
 * retrieve a value from a data key for some thread
 * returns NULL upon error with errno EINVAL if the key is invalid.
 */
any_t
pthread_getspecific (
		      pthread_key_t key)
{
  if (key < 0 || key >= n_keys)
    {
      set_errno (EINVAL);
      return (NULL);
    }

  return (mac_pthread_self ()->key[key]);
}
