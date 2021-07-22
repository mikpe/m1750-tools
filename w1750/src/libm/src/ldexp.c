/*
 * ANSI Standard C: 7.5.4.3
 * 
 * #include <math.h>
 * double ldexp (double x, int exp);
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
 * $Log: ldexp.c,v $
 * Revision 1.1  1997/03/17 17:22:06  nettleto
 * Initial revision
 *
 */

#include <math.h>

#include <float.h>

double
ldexp (double x, int exp)
{
  /* The ldexp() function returns the result of multiplying the
     floating-point number x by 2 raised to the power exp. */

  int e2;
  double ans = x;

  /* read clear old signed radix 2 exponent */
      asm volatile (
       "xbr    %d1
        lr     %0,%d1
        sra    %0,8
        sll    %d1,8" : "=r" (e2), "=r" (ans) : "1" (ans));

  /* calculate new exponent */
  e2 += exp;

  if (e2 > 127)
    ans = DBL_MAX;

  else if (e2 < -128)
    ans = 0.0;

  else
    /* put new exponent into answer */
    asm volatile (
       "orr    %d0,%2" : "=&r" (ans) : "0" (ans), "r" (e2 & 0xff));

  return ans;
 
}


