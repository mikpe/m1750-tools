/*
 * ANSI Standard C: 7.10.1.6
 * 
 * #include <stdlib.h>
 * long strtoul (const char *nptr, char **endptr, int base);
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
 * $Log: strtoul.c,v $
 * Revision 1.1  1997/05/09 16:55:43  nettleto
 * Initial revision
 *
 */

#include <stdlib.h>

#include <ctype.h>
#include <errno.h>
#include <stdlib.h>
#include <limits.h>

unsigned long
strtoul (const char *nptr, char **endptr, int base)
{
  const char *s = nptr;
  int c;
  unsigned long acc;
  unsigned long cutoff;
  int neg = 0;
  int any, cutlim;

  /*
   * Skip white space and pick up leading +/- sign if any.
   * If base is 0, allow 0x for hex and 0 for octal, else
   * assume decimal; if base is already 16, allow 0x.
   */
  do
    {
      c = *s++;
    }
  while (isspace (c));

  if (c == '-')
    {
      neg = 1;
      c = *s++;
    }
  else if (c == '+')
    c = *s++;

  if ((base == 0 || base == 16) &&
      c == '0' && (*s == 'x' || *s == 'X'))
    {
      c = s[1];
      s += 2;
      base = 16;
    }

  if (base == 0)
    base = c == '0' ? 8 : 10;

  /*
   * Compute the cutoff value between legal numbers and illegal
   * numbers.  That is the largest legal value, divided by the
   * base.  An input number that is greater than this value, if
   * followed by a legal input character, is too big.  One that
   * is equal to this value may be valid or not; the limit
   * between valid and invalid numbers is then based on the last
   * digit.  For instance, if the range for longs is
   * [-2147483648..2147483647] and the input base is 10,
   * cutoff will be set to 214748364 and cutlim to either
   * 7 (neg==0) or 8 (neg==1), meaning that if we have accumulated
   * a value > 214748364, or equal but the next digit is > 7 (or 8),
   * the number is too big, and we will return a range error.
   *
   * Set any if any `digits' consumed; make it negative to indicate
   * overflow.
   */
  cutoff = (unsigned long) ULONG_MAX / (unsigned long) base;
  cutlim = (unsigned long) ULONG_MAX % (unsigned long) base;

  for (acc = 0, any = 0;; c = *s++)
    {
      int d;

      if (isdigit (c))
	d = c - '0';
      else if (isalpha (c))
	d = isupper (c) ? c - 'A' + 10 : c - 'a' + 10;
      else
	break;

      if (d >= base)
	break;

      if (any < 0 || acc > cutoff || acc == cutoff && c > cutlim)
	any = -1;
      else
	{
	  any = 1;
	  acc = acc * base + d;
	}
    }

  if (endptr != 0)
    *endptr = (char *) (any ? s - 1 : nptr);

  if (any < 0)
    {
      errno = ERANGE;
      return ULONG_MAX;
    }
  else if (neg)
    {
      errno = ERANGE;
      return 0;
    }
  else
    return acc;
}
