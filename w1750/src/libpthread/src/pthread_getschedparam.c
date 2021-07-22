/*
 * pthread_getschedparam - POSIX 13.5.2.
 *  
 * #include <pthread.h>
 * int pthread_getschedparam (
 *    pthread_t thread,
 *    int *policy,
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
 * $Log: pthread_getschedparam.c,v $
 * Revision 1.1  1997/07/17 09:40:22  nettleto
 * Initial revision
 *
 */

#include "pthread_internals.h"


/*
 * get the thread scheduling attributes
 */
int
pthread_getschedparam (
			pthread_t thread,
			int *policy,
			struct sched_param *param)
{
  if (thread == NO_PTHREAD)
    {
      set_errno (ESRCH);
      return (-1);
    }

  *policy = thread->attr.sched;
  param->sched_priority = thread->attr.prio;

  return (0);
}
