/*
 * ANSI Standard C: 7.10.1.5
 * 
 * #include <stdlib.h>
 * long strtol (const char *nptr, char **endptr, int base);
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
 * $Log: strtol.c,v $
 * Revision 1.2  1997/05/13 18:54:48  nettleto
 * Complete rewrite.
 *
 * Revision 1.1  1997/05/09 16:55:43  nettleto
 * Initial revision
 *
 */

#include <stdlib.h>

#include <ctype.h>
#include <errno.h>
#include <limits.h>


long
strtol (const char *nptr, char **endptr, int base)
{
  const char *p = nptr;
  int sign;
  long result;
  int overflow;

  /* Deal with part 1, the initial, possibly empty, sequence of white 
     space characters, as deined by the 'isspace' function. */
  while (isspace (*p))
    p++;

  /* Deal with part 2, the sequence resembling an integer, defined in 
     ANSI C Section 6.1.3.2. */

  /* Get any sign, default is +ve. */
  sign = '+';
  if (*p == '+' || *p == '-')
    sign = *p++;

  /* The default base is as given in string, with leading zero
     meaning octal, and prefix 0x meaning hexadecimal. */
  if (base == 0)
    {
      if (*p == '0')
	{
	  if (tolower (p[1]) == 'x')
	    {
	      p += 2;
	      base = 16;
	    }
	  else
	    {
	      base = 8;
	    }
	}
      else
	base = 10;
    }
  else if (base == 16 && *p == '0' && tolower (p[1]) == 'x')
    p += 2;

  /* Read in the number, accumulate as a -ve number */
  result = 0;
  overflow = 0;
  while (isalnum (*p))
    {
      int d;

      if (isdigit (*p))
	d = *p - '0';
      else if (isupper (*p))
	d = *p - 'A' + 10;
      else
	d = *p - 'a' + 10;

      if (d >= base)
	break;

      if (result < LONG_MIN / base || (result == LONG_MIN / base && -d <= LONG_MIN % base))
	{
	  overflow = 1;
	  break;
	}

      result = result * base - d;
      p++;
    }

  /* Catch the special case that cannot be negated */
  if (sign == '+' && result == LONG_MIN)
    overflow = 1;

  /* Update the end pointer. */
  if (endptr != NULL)
    *endptr = (char *) (overflow ? nptr : p - 1);

  if (overflow)
    {
      errno = ERANGE;
      result = (sign == '-' ? LONG_MIN : LONG_MAX);
    }
  else if (sign == '+')
    result = -result;

  return result;
}
