/*
 * settime
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
 * $Log: settime.c,v $
 * Revision 1.1  1997/07/17 18:49:11  nettleto
 * Initial revision
 *
 */

#include <sys/time.h>

#include <time.h>

int
settimeofday (const struct timeval *__tp,
               const struct timezone *__tz)
{
  extern struct timeval sys_time;

  asm volatile ( "xio    r0,dsbl");
  sys_time = *__tp;
  asm volatile ( "xio    r0,enbl");

  return 0;
}


