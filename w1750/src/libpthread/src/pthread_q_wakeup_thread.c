/* Copyright (C) 1992, 1993, 1994, 1995, 1996 the Florida State University
   Distributed by the Florida State University under the terms of the
   GNU Library General Public License.

   This file is part of Pthreads.

   Pthreads is free software; you can redistribute it and/or
   modify it under the terms of the GNU Library General Public
   License as published by the Free Software Foundation (version 2).

   Pthreads is distributed "AS IS" in the hope that it will be
   useful, but WITHOUT ANY WARRANTY; without even the implied
   warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
   See the GNU Library General Public License for more details.

   You should have received a copy of the GNU Library General Public
   License along with Pthreads; see the file COPYING.  If not, write
   to the Free Software Foundation, 675 Mass Ave, Cambridge,
   MA 02139, USA.

   ==================================================
   This version was cut down for the 1750 target,
   by Chris Nettleton Software, July 1997.
   ==================================================

 */

#include "pthread_internals.h"


/*
 * pthread_q_wakeup_thread - internal.
 * same as pthread_q_wakeup but for specific thread
 * return pointer to thread if thread found in queue, NO_PTHREAD otherwise
 */
void
pthread_q_wakeup_thread (
			  pthread_queue_t q,
			  pthread_t p)
{
  if (q != NO_QUEUE)
    pthread_q_deq (q, p);

  if (p != NO_PTHREAD && !(p->state & T_RUNNING))
    {
      p->state &= ~(T_BLOCKED | T_INTR_POINT);
      p->state |= T_RUNNING;
      pthread_q_enq (&ready, p);
    }
}
