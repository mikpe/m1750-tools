/*
 * _dtoa
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
 * $Log: _dtoa.c,v $
 * Revision 1.1  1997/03/18 12:51:09  nettleto
 * Initial revision
 *
 */

#include <report.h>
#include <math.h>

/* Table of powers of 10, up to 10**38. Exact up to 10**11.
*/
static const double powers_of_10 [] = {
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


int
_dtoa (
  int *sign,   /* gets set to -ve, zero or +ve */
  char *buf,   /* the output asciiz string, prec+5 chars + term zero */
  int prec,    /* number of digits after the point */ 
  double v,    /* number to convert */ 
  int echar)   /* char to use to prefix the exponent (usually 'e') */
{
  int n = prec + 1;   /* num digs to convert */
  int e10;            /* radix 10 exponent */
  double f;
  int s, e2;          /* mantissa sign and radix 2 exponent */
  int carry;
  int digit;
  long ltmp;
  char *p = buf;      /* current output pointer */

  /*
   * The first word of extended precision float is enough to indicate
   * whether the float is zero, negative or positive. Save this word for
   * later. The rest of this function deals with the positive number f.
   */
  asm volatile (
       "lr     %0,%1" :"=r" (s): "r" (v));
  *sign = s;

  /* FIXME: special case if v is the largest negative number, which cannot
     be negated. (v == -170141183460469231731687303715884105728.0). */
  v = fabs (v);
  
  /*
   * Now extract the signed radix 2 exponent, and widen it to 16 bits. Then
   * compute the equivalent radix 10 exponent using the fraction 19728/65536,
   * which is approx log(2)/log(10) 
   */
  asm volatile (
       "lr     %1,%d2
        sll    %1,8
        sra    %1,8
        mim    %1,19728
        lr     %0,%1" :"=r" (e10), "=r" (ltmp): "r" (v));

  /* Select a power of ten, then scale the given number to 
     between 0.5 and 9 (range about 20:1). Then scale to 
     between 1 and 9 */
  if (e10 == -39)
    f = v * powers_of_10 [38] * 10.0;
  else if (e10 > 0)
    f = v / powers_of_10 [e10];
  else
    f = v * powers_of_10 [-e10];

  /* Get new exponent, which will be in the range -1 .. 4 */
  asm volatile (
       "lr     %0,%d1
        sll    %0,8
        sra    %0,8" :"=r" (e2): "r" (f));

  /* If we got the wrong power of ten, then correct this now */
  if (e2 <= 0)
    {
      e10--;
      if (e10 == -39)
        f = v * powers_of_10 [38] * 10.0;
      else if (e10 > 0)
        f = v / powers_of_10 [e10];
      else
        f = v * powers_of_10 [-e10];

      asm volatile (
       "lr     %0,%d1
        sll    %0,8
        sra    %0,8" :"=r" (e2): "r" (f));
    }

  /*
   * Unfortunately getting the next power of ten and using that to
   * recompute f does not guarantee that f will be in range. This is
   * because the powers_of_ten table is not exact above 10**11, and 
   * the computation for f may introduce rounding errors. We allow 
   * for this later.
   */

  /*
   * Reorganize the floating point number to get rid of the 8-bit hole where
   * the exponent was. The result is a 48-bit number with the top 8 bits
   * set to zero.
   */
  asm volatile (
       "dsrl   %0,8" : "=r" (f): "0" (f));

  /*
   * Now denormalize the number by shifting left and decrementing the
   * exponent. Note that we aim for -1 because we wish to move into the sign
   * bit. Any bits moved into the top 8 bits are the first decimal
   * digit.
   */
  while (e2-- > -1)
    {
      asm volatile (
       "lr     %1,%t0
        dsll   %0,1
        sll    %t0,1
        srl    %1,15
        orr    %d0,%1" : "=r" (f), "=r" (carry): "0" (f));
    }

  /*
   * Multiply by 10, n times, each time appending the carry (range 0 .. 9)
   * to the output buffer. Use exact 48-bit mutiplication rather than 1750
   * 40 bit extended float. (Note the exact product is 44 bits wide). 
   */
  while (n-- > 0)
    {
      double ff;

      /* get next digit and reset top 8 bits to sign bit */
      asm volatile (
       "lr     %0,%1
        srl    %0,8
        sll    %1,8
        srl    %1,8" : "=r" (digit), "=r" (f) : "1" (f));

      /* put decimal digit in buffer */
      if (digit == 10)
        {
          *p++ = '1';
          n--;
          digit = 0;
          e10++;
        }
      *p++ = '0' + digit;

      /* prepare for multiply by 10 */
      ff = f;

      /* f <<= 2 */
      asm volatile (
       "lr     %1,%t0
        dsll   %0,2
        sll    %t0,2
        srl    %1,14
        orr    %d0,%1" : "=r" (f), "=r" (carry): "0" (f));

      /*  f += ff; FIXME: this should be an unsigned add */
      asm volatile (
       "lisp   %1,1
        dar    %d0,%d3
        jc     cy,.+6
        xorr   %1,%1
        ar     %0,%3
        ar     %0,%1" : "=r" (f), "=r" (carry): "0" (f), "r" (ff));

      /* f <<= 1 */
      asm volatile (
       "lr     %1,%t0
        dsll   %0,1
        sll    %t0,1
        srl    %1,15
        orr    %d0,%1" : "=r" (f), "=r" (carry): "0" (f));
    }

  /* get next digit */
  asm volatile (
       "lr     %0,%1
        srl    %0,8" : "=r" (digit): "r" (f));

  /* 
   * Now round the digits in buf. Special action is needed where 
   * 9999 goes to 10000. Not too tricky, just replace the leading
   * zero with a '1' (all the other chars have already been 
   * changed to zeros), and bump up the exponent. 
   */
  if (digit >= 5)
    {
      int c = 1;
      char *pp = p;
      int nn = p - buf;

      while (c && nn-- > 0) 
        {
          pp--;
          *pp += 1;
          if (*pp > '9')
            *pp = '0';
          else
            c = 0;
        }

      if (c)
        {
          *pp = '1';
          e10++;
        }
    }

  /* 
   * Finally append the exponent. This is always 4 chars.
   * The first char is the printf format char, usually given to
   * this function as a 'e' or 'E'. Th next is the sign, either
   * '+' or '-'. The next two are the tens and units of the exponent.
   * We always write a zero exponent where the mantissa is zero
   */
  *p++ = echar;

  if (s == 0)
    e10 = 0;

  if (e10 < 0)
    {
      *p++ = '-';
      e10 = -e10;
    }
  else
    *p++ = '+';

  *p++ = e10 / 10 + '0';
  *p++ = e10 % 10 + '0';

  *p = '\0';

  return p - buf;
}

