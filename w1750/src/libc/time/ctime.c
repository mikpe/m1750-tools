/*
 * ANSI Standard C: 7.12.3.2
 * 
 * #include <time.h>
 * struct tm *ctime (const time *timer);
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
 * $Log: ctime.c,v $
 * Revision 1.1  1997/02/14 09:28:50  nettleto
 * Initial revision
 *
 */

#include <time.h>

char *
ctime (const time_t *timer)
{
  struct tm tm;
  return asctime (localtime (timer));
}

