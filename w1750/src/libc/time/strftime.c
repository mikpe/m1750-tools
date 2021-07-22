/*
 * ANSI Standard C: 7.12.3.5
 * 
 * #include <time.h>
 * size_t strftime (char *s, size_t maxsize, const char *format, const struct tm *timeptr);
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
 * $Log: strftime.c,v $
 * Revision 1.1  1997/02/14 09:37:53  nettleto
 * Initial revision
 *
 */

#include <time.h>

/*
 * Original Author: G. Haley
 *
 * Places characters into the array pointed to by s as controlled by the string
 * pointed to by format. If the total number of resulting characters including
 * the terminating null character is not more than maxsize, returns the number
 * of characters placed into the array pointed to by s (not including the
 * terminating null character); otherwise zero is returned and the contents of
 * the array indeterminate.
 */

#include <stddef.h>
#include <stdio.h>

static const int dname_len [7] =
{6, 6, 7, 9, 8, 6, 8};

static const char *const dname [7] =
{"Sunday", "Monday", "Tuesday", "Wednesday",
 "Thursday", "Friday", "Saturday"};

static const int mname_len [12] =
{7, 8, 5, 5, 3, 4, 4, 6, 9, 7, 8, 8};

static const char *const mname [12] =
{"January", "February", "March", "April",
 "May", "June", "July", "August", "September", "October", "November",
 "December"};

size_t
strftime (char *s, size_t maxsize, const char *format, const struct tm *timeptr)
{
  size_t count = 0;
  int i;

  for (;;)
    {
      while (*format && *format != '%')
	{
	  if (count < maxsize - 1)
	    s [count++] = *format++;
	  else
	    return 0;
	}

      if (*format == '\0')
	break;

      format++;
      switch (*format)
	{
	case 'a':
	  for (i = 0; i < 3; i++)
	    {
	      if (count < maxsize - 1)
		s [count++] =
		  dname [timeptr->tm_wday] [i];
	      else
		return 0;
	    }
	  break;
	case 'A':
	  for (i = 0; i < dname_len [timeptr->tm_wday]; i++)
	    {
	      if (count < maxsize - 1)
		s [count++] =
		  dname [timeptr->tm_wday] [i];
	      else
		return 0;
	    }
	  break;
	case 'b':
	  for (i = 0; i < 3; i++)
	    {
	      if (count < maxsize - 1)
		s [count++] =
		  mname [timeptr->tm_mon] [i];
	      else
		return 0;
	    }
	  break;
	case 'B':
	  for (i = 0; i < mname_len [timeptr->tm_mon]; i++)
	    {
	      if (count < maxsize - 1)
		s [count++] =
		  mname [timeptr->tm_mon] [i];
	      else
		return 0;
	    }
	  break;
	case 'c':
	  if (count < maxsize - 24)
	    {
	      for (i = 0; i < 3; i++)
		s [count++] =
		  dname [timeptr->tm_wday] [i];
	      s [count++] = ' ';
	      for (i = 0; i < 3; i++)
		s [count++] =
		  mname [timeptr->tm_mon] [i];

	      sprintf (&s [count],
		       " %.2d %2.2d:%2.2d:%2.2d %.4d",
		       timeptr->tm_mday, timeptr->tm_hour,
		       timeptr->tm_min,
		       timeptr->tm_sec, 1900 +
		       timeptr->tm_year);
	      count += 17;
	    }
	  else
	    return 0;
	  break;
	case 'd':
	  if (count < maxsize - 2)
	    {
	      sprintf (&s [count], "%.2d",
		       timeptr->tm_mday);
	      count += 2;
	    }
	  else
	    return 0;
	  break;
	case 'H':
	  if (count < maxsize - 2)
	    {
	      sprintf (&s [count], "%2.2d",
		       timeptr->tm_hour);
	      count += 2;
	    }
	  else
	    return 0;
	  break;
	case 'I':
	  if (count < maxsize - 2)
	    {
	      if (timeptr->tm_hour == 0 ||
		  timeptr->tm_hour == 12)
		{
		  s [count++] = '1';
		  s [count++] = '2';
		}
	      else
		{
		  sprintf (&s [count], "%.2d",
			   timeptr->tm_hour % 12);
		  count += 2;
		}
	    }
	  else
	    return 0;
	  break;
	case 'j':
	  if (count < maxsize - 3)
	    {
	      sprintf (&s [count], "%.3d",
		       timeptr->tm_yday + 1);
	      count += 3;
	    }
	  else
	    return 0;
	  break;
	case 'm':
	  if (count < maxsize - 2)
	    {
	      sprintf (&s [count], "%.2d",
		       timeptr->tm_mon + 1);
	      count += 2;
	    }
	  else
	    return 0;
	  break;
	case 'M':
	  if (count < maxsize - 2)
	    {
	      sprintf (&s [count], "%2.2d",
		       timeptr->tm_min);
	      count += 2;
	    }
	  else
	    return 0;
	  break;
	case 'p':
	  if (count < maxsize - 2)
	    {
	      if (timeptr->tm_hour < 12)
		s [count++] = 'A';
	      else
		s [count++] = 'P';

	      s [count++] = 'M';
	    }
	  else
	    return 0;
	  break;
	case 'S':
	  if (count < maxsize - 2)
	    {
	      sprintf (&s [count], "%2.2d",
		       timeptr->tm_sec);
	      count += 2;
	    }
	  else
	    return 0;
	  break;
	case 'U':
	  if (count < maxsize - 2)
	    {
	      sprintf (&s [count], "%2.2d",
		       (timeptr->tm_yday + 7 -
			timeptr->tm_wday) / 7);
	      count += 2;
	    }
	  else
	    return 0;
	  break;
	case 'w':
	  if (count < maxsize - 1)
	    {
	      sprintf (&s [count], "%1.1d",
		       timeptr->tm_wday);
	      count++;
	    }
	  else
	    return 0;
	  break;
	case 'W':
	  if (count < maxsize - 2)
	    {
	      sprintf (&s [count], "%2.2d",
		       (timeptr->tm_yday + ((8 -
					   timeptr->tm_wday) % 7)) / 7);
	      count += 2;
	    }
	  else
	    return 0;
	  break;
	case 'x':
	  if (count < maxsize - 15)
	    {
	      for (i = 0; i < 3; i++)
		s [count++] =
		  dname [timeptr->tm_wday] [i];
	      s [count++] = ' ';
	      for (i = 0; i < 3; i++)
		s [count++] =
		  mname [timeptr->tm_mon] [i];

	      sprintf (&s [count],
		       " %.2d %.4d", timeptr->tm_mday,
		       1900 + timeptr->tm_year);
	      count += 8;
	    }
	  else
	    return 0;
	  break;
	case 'X':
	  if (count < maxsize - 8)
	    {
	      sprintf (&s [count],
		       "%2.2d:%2.2d:%2.2d",
		       timeptr->tm_hour, timeptr->tm_min,
		       timeptr->tm_sec);
	      count += 8;
	    }
	  else
	    return 0;
	  break;
	case 'y':
	  if (count < maxsize - 2)
	    {
	      sprintf (&s [count], "%2.2d",
		       timeptr->tm_year);
	      count += 2;
	    }
	  else
	    return 0;
	  break;
	case 'Y':
	  if (count < maxsize - 4)
	    {
	      sprintf (&s [count], "%.4d",
		       1900 + timeptr->tm_year);
	      count += 4;
	    }
	  else
	    return 0;
	  break;
	case 'Z':
	  break;
	case '%':
	  if (count < maxsize - 1)
	    s [count++] = '%';
	  else
	    return 0;
	  break;
	}
      if (*format)
	format++;
      else
	break;
    }
  s [count] = '\0';

  return count;
}

