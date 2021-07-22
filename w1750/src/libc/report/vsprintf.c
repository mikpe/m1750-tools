/*
 * ANSI Standard C: 
 * 
 * #include <report.h>
 * void vsprintf (const char *s, const char *format, va_list ap);
 * 
 * Copyright (c) 1996, Free Software Foundation, Inc.
 *
 * This file is part of the GNU C Library. The GNU C Library is free 
 * software; you can redistribute it and/or modify it under the terms of 
 * the GNU Library General Public License as published by the Free 
 * Software Foundation; either version 2 of the License, or (at your 
 * option) any later version. The GNU C Library is distributed in the 
 * hope that it will be useful, but WITHOUT ANY WARRANTY; without even 
 * the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR 
 * PURPOSE. See the GNU Library General Public License for more details. 
 * You should have received a copy of the GNU Library General Public 
 * License along with the GNU C Library; see the file COPYING.LIB. If 
 * not, write to the Free Software Foundation, Inc., 675 Mass Ave, 
 * Cambridge, MA 02139, USA. 
 *
 * $Log: vsprintf.c,v $
 * Revision 1.1  1997/03/18 12:52:29  nettleto
 * Initial revision
 *
 */

#include <report.h>

#include <stdarg.h>
#include <string.h>
#include <ctype.h>

/* 
 * Buffer used for numbers, integers up to 64 bits (printed base 2),
 * double precision fixed point (39 digs left of point, 40 right of
 * the point) + point + exponent + terminating zero.
 */
#define BUFSIZ 90

/*
 * Function to convert an integer to an ascii string. Use by all integer formats
 * including unsigned. Handles base in the range 2 to 16, and up to 36 using the
 * alphabet.
 */
static char *
_ulltoa (unsigned long long value, char *buflim, int base, int upper_case)
{
  char *bp = buflim;

  if (value == 0)
    {
      *--bp = '0';
    }
  else
    {
      while (value > 0)
        {
          int dig = 0;
          int i;
          unsigned long long tmp;

          /* divide 'value' by 10, put remainder in 'dig' */
          tmp = value;
          value = 0;
          for (i = 0; i < 8; i++)
            {
              int n = ((tmp >> 56) & 0xff) + (dig << 8);
              int q = n / base;
          
              dig = n % base;
              value = (value << 8) + q;
              tmp <<= 8;
            }
 
          if (dig < 10)
            *--bp = dig + '0';
          else
            *--bp = dig - 10 + (upper_case? 'A' : 'a');

        }
    }

  return bp;
}

/*
 * This is an ANSI C compliant function that supports the printf
 * function, and its various alternatives. The output characters are
 * copied into a buffer from wher they can be used by sprintf, or sent
 * to a file or other peripheral device. All the ANSI feartures are
 * supported for all the data types supported by the compiler.
 */
int
vsprintf (const char *s, const char *format, va_list ap)
{
  char *obuf = s;    /* pointer to output buffer */
  char *f = format;  /* Pointer into the format string.  */

  /* Reset multibyte characters to their initial state.  */
  (void) mblen((char *) NULL, 0);

  /* read characters from the the format string */
  while (*f)
    {
      if (*f & 0x80)
        {
          /* Non-ASCII, may be a multibyte.  */
          int len = mblen (f, strlen (f));
          if (len > 0)
            {
              while (len-- > 0)
                *obuf++ = *f++;
              continue;
            }
        }

      /* write everything up to the next percent (or end) */
      while (*f && *f != '%')
        {
          *obuf++ = *f;
          f++;
        }

      /* deal with what follows the percent */
      if (*f == '%')
        {
          unsigned long long num;    /* number to be printed */
          long long signed_num;
          char *str;            /* string to be printed */

          int base;       /* base for format spec, 8 10 or 16 */

          int width;      /* given or default field width */
          int prec;       /* given or default precision */
          char pad;       /* padding char */     

          int space;      /* Output a space in place of a sign */
          int showsign;   /* Always output + or - for numbers */
          int left;       /* Left-justify things. */

          int alt;        /* Use the "alternate form" */
          char fc;        /* the format char */

          char is_long_long;
          char is_long;
          char is_short;
          char is_long_double;

          char is_neg;    /* signed number is negative */
          f++;

          /* check for %%, and write one % */
          if (*f == '%')
            {
              *obuf++ = '%';
              f++;
              continue;
            }
  
          /* Check for spec modifiers. */
          space = showsign = left = alt = 0;
          pad = ' ';
          while (*f == ' ' || *f == '+' || *f == '-' 
                 || *f == '#' || *f == '0')
            switch (*f++)
              {
              case ' ':
                /* Output a space in place of a sign, when there is no sign. */
                space = 1;
                break;
              case '+':
                /* Always output + or - for numbers. */
                showsign = 1;
                break;
              case '-':
                /* Left-justify things. */
                left = 1;
                break;
              case '#':
                /* Use the "alternate form":
                   Hex has 0x or 0X, FP always has a decimal point */
                alt = 1;
                break;
              case '0':
                /* Pad with 0s */
                pad = '0';
                break;
              }

          /* Get the field width */
          width = 0;
          if (*f == '*')
            {
              /* The field width is given in an argument.
                 A negative field width indicates left justification */
              width = va_arg (ap, int);

              if (width < 0)
                {
                  width = - width;
                  left = 1;
                }
              f++;
            }
          else
            while (isdigit (*f))
              {
                width *= 10;
                width += *f++ - '0';
              }

          /* Get the prec */
          /* -1 means none given; 0 means explicit 0 */
          prec = -1;
          if (*f == '.')
            {
              f++;
              if (*f == '*')
                {
                  /* The prec is given in an argument */
                  prec = va_arg (ap, int);

                  /* Avoid idiocy */
                  if (prec < 0)
                    prec = -1;
                  f++;
                }
              else if (isdigit (*f))
                {
                  prec = 0;
                  while (*f != '\0' && isdigit (*f))
                    {
                      prec *= 10;
                      prec += *f++ - '0';
                    }
                }
            }

	  /* Check for type modifiers. */
	  is_short = is_long = is_long_double = 0;
          is_long_long = 0;
	  while (*f == 'h' || *f == 'l' || *f == 'L' || *f == 'q')
            switch (*f++)
              {
              case 'h':
        	/* int's are short int's */
        	is_short = 1;
        	break;

              case 'l':
        	if (is_long)
        	  /* A double `l' is equivalent to an `L' */
        	  is_long_long = 1;
        	else
        	  /* int's are long int's */
        	  is_long = 1;
        	break;

              case 'L':
        	/* double's are long double's, and int's are long long int's */
                is_long_long = 1;
        	is_long_double = 1;
        	break;

              case 'q':
        	/* 4.4 uses this for long long */
        	is_long_long = 1;
        	break;
              }

          /* Deal with format specification */
          fc = *f++;
          switch (fc)
            {
              case 'i':
              case 'd':
                base = 10;
                if (is_long_long)
                  {
                    signed_num = va_arg (ap, long long);
                  }
                else if (is_long)
                  {
                    signed_num = va_arg (ap, long);
                  }
                else 
                  {
                    signed_num = va_arg (ap, int);
                  }
                is_neg = (signed_num & 0x8000000000000000LL) != 0;
                num = is_neg ? (-signed_num) : signed_num;

              number:
        	/* Number of base BASE */
        	{
        	  char work [BUFSIZ];
        	  char *const workend = &work [sizeof (work) - 1];
        	  char *w;

        	  /* Use default precision if none was given */
        	  if (prec == -1)
                    prec = 1;

        	  /* Convert number to chars */
        	  w = _ulltoa (num, workend + 1, base, fc == 'X') - 1;
        	  width -= workend - w;
        	  prec -= workend - w;

        	  if (alt && base == 8 && prec <= 0)
                    {
                      *w-- = '0';
                      --width;
                    }

        	  if (prec > 0)
                    {
                      width -= prec;
                      while (prec-- > 0)
                	*w-- = '0';
                    }

        	  if (alt && base == 16)
                    width -= 2;

        	  if (is_neg || showsign || space)
                    --width;

        	  if (!left && pad == ' ')
                    while (width-- > 0)
                      *obuf++ = ' ';

        	  if (is_neg)
                    *obuf++ = '-';
        	  else if (showsign)
                    *obuf++ = '+';
        	  else if (space)
                    *obuf++ = ' ';

        	  if (alt && base == 16)
                    {
                      *obuf++ = '0';
                      *obuf++ = fc;
                    }

        	  if (!left && pad == '0')
                    while (width-- > 0)
                      *obuf++ = '0';

        	  /* Write the number */
        	  while (++w <= workend)
                    *obuf++ = *w;

        	  if (left)
                    while (width-- > 0)
                      *obuf++ = ' ';
        	}
        	break;

              case 'c':
                /* Character */
                {
                  char c = va_arg (ap, int);
                  
                  if (!left)
                    while (--width > 0)
                      *obuf++ = ' ';

                  *obuf++ = c;

                  if (left)
                    while (--width > 0)
                      *obuf++ = ' ';
                }
                break;

              case 's':
                /* String */
                {
        	  static const char null [] = "(null)";
        	  size_t len;

        	  str = va_arg (ap, char *);

        	  if (str == NULL)
                    /* Write "(null)" if there's space */
                    if (prec == -1 || prec >= (int) sizeof(null) - 1)
                      {
                	str = null;
                	len = sizeof (null) - 1;
                      }
                    else
                      {
                	str = "";
                	len = 0;
                      }
        	  else
                    len = strlen (str);

        	  if (prec != -1 && (size_t) prec < len)
                    len = prec;
        	  width -= len;

        	  if (!left)
                    while (width-- > 0)
                      *obuf++ = ' ';
        	  if (len < 20)
                    while (len-- > 0)
                      *obuf++ = *str++;
        	  else
                    {
                      int i;

                      for (i = 0; i < len; i++)
                        *obuf++ = str [i];
                    }

        	  if (left)
                    while (width-- > 0)
                      *obuf++ = ' ';
        	}
        	break;

              case 'e':
              case 'E':
              case 'f':
              case 'F':
              case 'g':
              case 'G':
                /* Double precision floating point number */
                {
                  double arg = va_arg (ap, double);
        	  char work [BUFSIZ];
        	  char *const workend = &work [sizeof (work) - 2];
        	  char *w;

                  int sign;  /* -1 for-ve, 0 for zero, +1 for +ve */
                  int e;     /* signed exponent */

                  /* set default precision, and precision limit */
                  if (prec < 0)
                    prec = 6;
                  else if (prec > 40)
                    prec = 40;

                  /* get prec+1 digits */
                  w = workend - (prec + 1 + 4);
                  _dtoa (&sign, w + 1, prec, arg, fc);

        	  width -= workend - w;
                  if (alt || prec > 0)
                    width--;  /* for point */

                  if (sign < 0 || showsign || space)
                    width--;

                  if (!left && pad == ' ')
                    while (width-- > 0)
                      *obuf++ = ' ';

                  if (sign < 0)
                    *obuf++ = '-';
                  else if (showsign)
                    *obuf++ = '+';
                  else if (space)
                    *obuf++ = ' ';

                  if (!left && pad == '0')
                    while (width-- > 0)
                      *obuf++ = '0';

                  /* Write the number */
                  *obuf++ = *++w;

                  if (alt || prec > 0)
                    *obuf++ = '.';

                  while (++w <= workend)
                    *obuf++ = *w;

        	  if (left)
                    while (width-- > 0)
                      *obuf++ = ' ';
                }
                break;

              case 'o':
                /* Unsigned octal number */
                 base = 8;
                 goto unsigned_number;
                 
              case 'u':
                /* Unsigned decimal number */
                base = 10;
                goto unsigned_number;

              case 'x':
              case 'X':
                /* Unsigned hexadecimal number */
                base = 16;
                
            unsigned_number:
                if (is_long_long)
                  {
                    num = va_arg (ap, unsigned long long);
                  }
                else if (is_long)
                  {
                    num = va_arg (ap, unsigned long);
                  }
                else 
                  {
                    num = va_arg (ap, unsigned);
                  }
                /* ANSI only specifies the `+' and
                   ` ' flags for signed conversions.  */
                is_neg = showsign = space = 0;
                goto number;

              case 'p':
                /* Generic pointer */
                {
                  num = va_arg (ap, unsigned);

                  if (num != 0)
                    {
                      /* If the pointer is not NULL, write it as a %#x spec. */
                      base = 16;
                      fc = 'x';
                      alt = 1;
                      is_neg = 0;
                      goto number;
                    }
                  else
                    {
                      /* Write "(nil)" for a nil pointer */
                      static const char nil [] = "(nil)";
                      const char *p;

                      width -= sizeof (nil) - 1;
                      if (!left)
                        while (width-- > 0)
                          *obuf++ = ' ';
                      for (p = nil; *p != '\0'; ++p)
                        *obuf++ = *p;
                      if (left)
                        while (width-- > 0)
                          *obuf++ = ' ';
                    }
                }
                break;

              case 'n':
                /* Answer the count of characters written */
                if (is_long_long)
                  {
                    long long int *p;

                    p = va_arg (ap, long long int *);
                    *p = obuf - s;
                  }
                else if (is_long)
                  {
                    long int *p;

                    p = va_arg (ap, long int *);
                    *p = obuf - s;
                  }
                else
                  {
                    int *p;

                    p = va_arg (ap, int *);
                    *p = obuf - s;
                  }
                break;

              default:
                {
                }
            }
        }
    }

  *obuf = '\0';
  return obuf - s;
}

