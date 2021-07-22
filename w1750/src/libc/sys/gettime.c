/*
 * gettime
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
 * $Log: gettime.c,v $
 * Revision 1.1  1997/07/17 18:47:17  nettleto
 * Initial revision
 *
 */

#include <sys/time.h>

#include <time.h>

int
gettimeofday (struct timeval *tp,
               struct timezone *tz)
{
  extern volatile struct timeval sys_time;
  int ta;
  long sec, usec;

  asm volatile ("xio    r0,dsbl");
  asm volatile ("xio    %0,ita" : "=r" (ta));
  sec = sys_time.tv_sec;
  usec = sys_time.tv_usec;
  asm volatile ("xio    r0,enbl");

  usec += (500 + ta) * 200L;
  if (usec >= 1000000L)
    {
      sec++;
      usec -= 1000000;
    }
 
  tp->tv_sec = sec;
  tp->tv_usec = usec;

  if (tz != NULL)
    {
      tz->tz_minuteswest = 0;
      tz->tz_dsttime = 0;
    }

  return 0;
}

