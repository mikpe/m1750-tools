/*
 * ANSI Standard C: 7.5.4.2
 * 
 * #include <math.h>
 * double frexp (double value, int *exp);
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
 * $Log: frexp.c,v $
 * Revision 1.1  1997/03/17 17:20:40  nettleto
 * Initial revision
 *
 */

#include <math.h>

/*
 * The frexp() function returns the normalized fraction. If the argument
 * value is not zero, the normalized fraction is value times a power of two,
 * and is always in the range 1/2 (inclusive) to 1 (exclusive). If x is zero,
 * then the normalized fraction is zero and zero is stored in exp.
 */

double
frexp (double value, int *exp)
{
  double ans = value;
  int e2;

  /* read and clear signed radix 2 exponent */
  asm volatile (
       "xbr    %d1
        lr     %0,%d1
        sra    %0,8
        sll    %d1,8" : "=r" (e2), "=r" (ans) : "1" (ans));

  /* adjust exponent if fraction is -1 */
  if (ans == -1)
    {
      e2++;
      asm volatile (
       "orim   %d0,0xff" : "=r" (ans) : "0" (ans));
    }
  
  *exp = e2;
  return ans;
}

