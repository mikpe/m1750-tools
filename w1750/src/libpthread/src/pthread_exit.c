/*
 * pthread_exit - POSIX 16.2.5.
 *  
 * #include <pthread.h>
 * void pthread_exit (any_t status);
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
 * $Log: pthread_exit.c,v $
 * Revision 1.1  1997/07/17 09:40:22  nettleto
 * Initial revision
 *
 */

#include "pthread_internals.h"


/*
 * Save the exit status of the thread so that other
 * threads joining with this thread can find it.
 */
void
pthread_exit (
	       any_t status)
{
  void pthread_terminate ();

  register pthread_t t = mac_pthread_self ();
  t->result = status;
  pthread_terminate ();
}
