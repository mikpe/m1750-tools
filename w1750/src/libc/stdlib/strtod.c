/*
 * ANSI Standard C: 7.10.1.4
 * 
 * #include <stdlib.h>
 * double strtod (const char *nptr, char **endptr);
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
 * $Log: strtod.c,v $
 * Revision 1.1  1997/05/09 16:55:43  nettleto
 * Initial revision
 *
 */

#include <stdlib.h>

#include <ctype.h>
#include <float.h>

/*
 * strtod converts the initial portion of the string pointed to by 'nptr'
 * to double representation. First it decomposes the string into three
 * parts: an initial, possibly empty, sequence of white space characters
 * (as specified by the 'isspace' function), a subject sequence resembling
 * a floating point constant: and a final string of one or more
 * unrecognized characters, including the terminating null character of
 * the input string. Then it attempts to convert the subject sequence to a
 * floating point number, and return the result.
 */

/* Table of powers of 10, up to 10**38. Exact up to 10**11.
*/
static const double powers_of_ten [] = {
  1.0,
  10.0,
  100.0,
  1000.0,
  10000.0,
  100000.0,
  1000000.0,
  10000000.0,
  100000000.0,
  1000000000.0,
  10000000000.0,
  100000000000.0,
  1000000000000.0,
  10000000000000.0,
  100000000000000.0,
  1000000000000000.0,
  10000000000000000.0,
  100000000000000000.0,
  1000000000000000000.0,
  10000000000000000000.0,
  100000000000000000000.0,
  1000000000000000000000.0,
  10000000000000000000000.0,
  100000000000000000000000.0,
  1000000000000000000000000.0,
  10000000000000000000000000.0,
  100000000000000000000000000.0,
  1000000000000000000000000000.0,
  10000000000000000000000000000.0,
  100000000000000000000000000000.0,
  1000000000000000000000000000000.0,
  10000000000000000000000000000000.0,
  100000000000000000000000000000000.0,
  1000000000000000000000000000000000.0,
  10000000000000000000000000000000000.0,
  100000000000000000000000000000000000.0,
  1000000000000000000000000000000000000.0,
  10000000000000000000000000000000000000.0,
  100000000000000000000000000000000000000.0};


double
strtod (const char *nptr, char **endptr)
{
  char *s = nptr;
  double ans = 0.0;
  char sign = '+';    /* default sign is plus */
  int left = 0;       /* number of digits left of point */
  int e = 0;          /* e of current digit */
  int e10;            /* exponent radix 10 */

  /* skip leading blank space */
  while (isspace (*s))
    s++;

  /* read sign if given */
  if (*s == '+' || *s == '-')
    sign = *s++;

  /* rest number must begin with digit or point digit */
  if (!(isdigit (*s) || 
        (*s == '.' && isdigit (s [1]))))
    {
      if (endptr != NULL)
        *endptr = nptr;
      return 0.0;
    }

  /* skip leading integer part zeros */
  while (*s == '0')
    s++;

  /* skip leading fraction part zeros, then read fraction */
  if (*s == '.')
    {
      s++;
      while (*s == '0')
        {
          left--;
          s++;
        }
      while (isdigit (*s))
        {
          int digit = *s - '0';

          if (e > -12)
            ans += digit / powers_of_ten [-e--];
          s++; 
        }
    }

  else if (isdigit (*s))
    {
      /* read integer part, remember how many digits */
      while (isdigit (*s))
        {
          int digit = *s - '0';

          if (e > -12)
            ans += digit / powers_of_ten [-e--];
          s++; 
          left++;
        }
 
      /* read fraction part */ 
      if (*s == '.')
        {
          s++;
          while (isdigit (*s))
            {
              int digit = *s - '0';

              if (e > -12)
                ans += digit / powers_of_ten [-e--];
              s++; 
            }
        }
    }

  /* set default exponent */ 
  e10 = left - 1;

  /* read signed exponent */
  if (*s == 'e' || *s == 'E')
    {
      char esign;
      int ee;

      s++;
      esign = '+';
      if (*s == '+' || *s == '-')
        esign = *s++;

      ee = 0;
      if (isdigit (*s))
        {
          ee = *s - '0';
          s++;

          while (isdigit (*s))
            {
              if (ee < 38)
                ee = ee * 10.0 + *s - '0';
              s++;
            }
        }

       e10 += (esign == '-'? -ee: ee);
    }

  if (e10 > 38)
    ans = DBL_MAX;
  else if (e10 < -39)
    ans = DBL_MIN;
  else if (e10 > 0)
    ans *= powers_of_ten [e10];
  else
    ans /= powers_of_ten [-e10];

  /* update endptr to indicate success */
  if (endptr != NULL)
    *endptr = s;

  return sign == '-' ? -ans : ans;
}

