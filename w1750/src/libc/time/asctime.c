/*
 * ANSI Standard C: 7.12.3.1
 * 
 * #include <time.h>
 * char *asctime (const struct tm *timeptr);
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
 * $Log: asctime.c,v $
 * Revision 1.1  1997/02/14 09:28:11  nettleto
 * Initial revision
 *
 */

#include <time.h>

/*
 * Original Author:	G. Haley
 *
 * Converts the broken down time in the structure pointed to by timeptr into a
 * string of the form
 *
 * Wed Jun 15 11:38:07 1988\n\0
 */

#include <stdio.h>

char *
asctime (const struct tm *timeptr)
{
  static const char day_name[7][3] = {
	"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"
  };

  static const char mon_name[12][3] = {
	"Jan", "Feb", "Mar", "Apr", "May", "Jun", 
	"Jul", "Aug", "Sep", "Oct", "Nov", "Dec"
  };

  static char result [26];

  sprintf (result, "%.3s %.3s %.2d %.2d:%.2d:%.2d %d\n",
	   day_name[timeptr->tm_wday], 
	   mon_name[timeptr->tm_mon],
	   timeptr->tm_mday, timeptr->tm_hour, timeptr->tm_min,
	   timeptr->tm_sec, 1900 + timeptr->tm_year);

  return result;
}

