/*
 * pthread_switch_handler - internal.
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
 * $Log: pthread_switch_handler.c,v $
 * Revision 1.3  1997/08/11 08:22:05  nettleto
 * Added null thread check
 *
 * Revision 1.2  1997/07/18 16:31:37  nettleto
 * Tidied logic of context switch
 *
 * Revision 1.1  1997/07/17 09:40:28  nettleto
 * Initial revision
 *
 */

#include "pthread_internals.h"


/*
 * dispatcher, assumes SET_KERNEL_FLAG.
 */
void
pthread_switch_handler (int i)
{
  pthread_t old, new;

  DISABLE_INTERRUPTS;
  old = mac_pthread_self ();
  new = ready.head;

  /* Stop here if new thread is null. The watchdog
     timer will catch this condition sooner or later. */
  while (!new)
    ;

  if (old != new)
    {
      old->errno = errno;
      errno = new->errno;

      mac_pthread_self () = new;
      old->sp = set_sp (new->sp);

      if (old && old->state & T_RETURNED && old->state & T_DETACHED)
	{
	  free (old->stack_base);
	  free (old);
	}
    }

  ENABLE_INTERRUPTS;
}
