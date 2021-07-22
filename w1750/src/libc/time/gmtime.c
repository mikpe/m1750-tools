/*
 * ANSI Standard C: 7.12.3.3
 * 
 * #include <time.h>
 * struct tm *gmtime (const time *timer);
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
 * $Log: gmtime.c,v $
 * Revision 1.1  1997/02/14 09:44:28  nettleto
 * Initial revision
 *
 */

#include <time.h>

#define _GMT_OFFSET 0

struct tm *
gmtime (const time_t *timer)
{
  time_t tim = *timer + _GMT_OFFSET;

  return localtime (&tim);
}

