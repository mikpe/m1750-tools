/*
 * ANSI Standard C: 7.12.2.4
 * 
 * #include <time.h>
 * time_t time (time_t *timer);
 * 
 * Copyright (c) 1996, Chris Nettleton Software
 *
 * The authors hereby grant permission to use, copy, modify, distribute, 
 * and license this software and its documentation for any purpose, 
 * provided that existing copyright notices are retained in all copies 
 * and that this notice is included verbatim in any distributions. No 
 * written agreement, license, or royalty fee is required for any of the 
 * authorized uses. Modifications to this software may be copyrighted by 
 * their authors and need not follow the licensing terms described here, 
 * provided that the new terms are clearly indicated on the first page 
 * of each file where they apply. 
 *
 * $Log: time.c,v $
 * Revision 1.2  1997/07/16 21:49:32  nettleto
 * Removed underscore from _gettimeofday.
 *
 * Revision 1.1  1997/02/14 09:45:13  nettleto
 * Initial revision
 *
 */

#include <time.h>

#include <sys/time.h>

time_t
time (time_t *t)
{
  struct timeval now;

  if (gettimeofday (&now, (struct timezone *) 0) >= 0)
    {
      if (t)
	*t = now.tv_sec;
      return now.tv_sec;
    }
  return -1;
}

