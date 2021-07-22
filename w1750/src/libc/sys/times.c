/*
 * ANSI Standard C: 
 * 
 * #include <sys/times.h>
 *  times ;
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
 * $Log: times.c,v $
 * Revision 1.1  1997/07/17 18:48:46  nettleto
 * Initial revision
 *
 */

#include <sys/times.h>

#include <time.h>
#include <sys/times.h>

clock_t 
times (struct tms *buf)
{
  /*
   * Gets cpu times. 
   */
  extern struct tms sys_times;

  asm volatile ("xio    r0,dsbl");
  *buf = sys_times;
  asm volatile ("xio    r0,enbl");

  return 0L;
}

