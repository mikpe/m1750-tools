/*
 * pthread_q_deq - internal.
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
 * $Log: pthread_q_deq.c,v $
 * Revision 1.1  1997/07/17 09:40:25  nettleto
 * Initial revision
 *
 */

#include "pthread_internals.h"


/*
 * dequeue a thread from a queue
 */
void
pthread_q_deq (
		pthread_queue_t q,
		pthread_t t)
{
  pthread_t prev = NO_PTHREAD;
  pthread_t next = q->head;

  while (next != NO_PTHREAD && next != t)
    {
      prev = next;
      next = next->next_in_primary_q;
    }

  if (next == NO_PTHREAD)
    return;

  if ((next = next->next_in_primary_q) == NO_PTHREAD)
    q->tail = prev;

  if (prev == NO_PTHREAD)
    {
      q->head = next;
      if (q == &ready)
	state_change = TRUE;
    }
  else
    prev->next_in_primary_q = next;

  t->next_in_primary_q = NO_PTHREAD;

  t->queue = NULL;
}
