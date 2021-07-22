/*
 * ANSI Standard C: 7.12.3.4
 * 
 * #include <time.h>
 * struct tm *localtime (const time *timer);
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
 * $Log: localtime.c,v $
 * Revision 1.1  1997/02/14 09:43:29  nettleto
 * Initial revision
 *
 */

#include <time.h>

/*
 * Original Author:	Adapted from tzcode maintained by Arthur David Olson.
 *
 * Converts the calendar time pointed to by timeptr into a broken-down time
 * expressed as local time. Returns a pointer to a structure containing the
 * broken-down time.
 */

#define SECSPERMIN	60L
#define MINSPERHOUR	60L
#define HOURSPERDAY	24L
#define SECSPERHOUR	(SECSPERMIN * MINSPERHOUR)
#define SECSPERDAY	(SECSPERHOUR * HOURSPERDAY)
#define DAYSPERWEEK	7
#define MONSPERYEAR	12

#define YEAR_BASE	1900
#define EPOCH_YEAR      1970
#define EPOCH_WDAY      4

#define isleap(y) ((((y) % 4) == 0 && ((y) % 100) != 0) || ((y) % 400) == 0)

static const int month_lengths [2] [MONSPERYEAR] = {
  {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
  {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
} ;

static const int year_lengths [2] = {
  365,
  366
} ;

struct tm *
localtime (const time_t *timeptr)
{
  long days, rem;
  int y;
  int yleap;
  const int *ip;
  static struct tm ans;

  days = ((long) *timeptr) / SECSPERDAY;
  rem = ((long) *timeptr) % SECSPERDAY;
  while (rem < 0) 
    {
      rem += SECSPERDAY;
      --days;
    }
  while (rem >= SECSPERDAY)
    {
      rem -= SECSPERDAY;
      ++days;
    }
 
  /* compute hour, min, and sec */  
  ans.tm_hour = (int) (rem / SECSPERHOUR);
  rem %= SECSPERHOUR;
  ans.tm_min = (int) (rem / SECSPERMIN);
  ans.tm_sec = (int) (rem % SECSPERMIN);
  ans.tm_sec = (int) (rem % SECSPERMIN);
  /* compute day of week */
  if ((ans.tm_wday = ((EPOCH_WDAY + days) % DAYSPERWEEK)) < 0)
    ans.tm_wday += DAYSPERWEEK;

  /* compute year & day of year */
  y = EPOCH_YEAR;
  if (days >= 0)
    {
      for (;;)
      {
  	yleap = isleap(y);
  	if (days < year_lengths [yleap])
  	  break;
  	y++;
  	days -= year_lengths [yleap];
      }
    }
  else
    {
      do
      {
  	--y;
  	yleap = isleap(y);
  	days += year_lengths [yleap];
      } while (days < 0);
    }

  ans.tm_year = y - YEAR_BASE;
  ans.tm_yday = days;

  ip = month_lengths [yleap];
  for (ans.tm_mon = 0; days >= ip [ans.tm_mon]; ++ans.tm_mon)
    days -= ip [ans.tm_mon];
  ans.tm_mday = days + 1;
  ans.tm_mday = days + 1;

  /* set daylight saving time flag */
  ans.tm_isdst = -1;
  
  return &ans;
}

