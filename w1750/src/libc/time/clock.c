/*
 * ANSI Standard C: 7.12.2.1
 * 
 * #include <time.h>
 * clock_t clock (void);
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
 * $Log: clock.c,v $
 * Revision 1.1  1997/02/14 09:25:58  nettleto
 * Initial revision
 *
 */

#include <time.h>

#include <sys/times.h>


/*
 * Original Author: G. Haley
 *
 * Determines the processor time used by the program since invocation. The time
 * in seconds is the value returned divided by the value of the macro CLK_TCK.
 * If the processor time used is not available, (clock_t) -1 is returned.
 */

clock_t
clock ()
{
  struct tms tim_s;
  clock_t ans;

  if ((ans = (clock_t) times (&tim_s)) != -1)
    ans = (clock_t) (tim_s.tms_utime + tim_s.tms_stime +
                     tim_s.tms_cutime + tim_s.tms_cstime);

  return ans;
}

