/*
 * ANSI Standard C: 7.5.6.3
 * 
 * #include <math.h>
 * double floor (double x);
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
 * $Log: floor.c,v $
 * Revision 1.2  1997/08/05 15:05:46  nettleto
 * Fixed problem for -ve fractions.
 *
 * Revision 1.1  1997/03/17 17:16:58  nettleto
 * Initial revision
 *
 */

#include <math.h>

double
floor (double x)
{
  /* Return the largest integral value not greater
     then x, expressed as a floating point number */

  double y = x;
  int e2;

  /* read clear signed radix 2 exponent */
  asm volatile (
       "xbr    %d1
        lr     %0,%d1
        sra    %0,8
        sll    %d1,8" : "=r" (e2), "=r" (x) : "1" (x));

  /* correct e2 if x -(power of two) */
  if (x == -1)
    e2++;

  /* clear any fraction bits */ 
  if (y == 0.0 || e2 <= 0)
    {
      /* Forget the exponent and keep the sign bit */
      y = x;
      asm volatile (
       "andm   %0,0x8000
        andm   %d0,0xff
        xorr   %t0,%t0" : "=r" (y) : "0" (y));
    }
  else if (e2 <= 15)
    {
      /* truncate 1st word, zero other two */
      asm volatile (
       "andr   %0,%2
        andm   %d0,0xff
        xorr   %t0,%t0" : "=r" (y) : "0" (y), "r" (-(1 << (15 - e2))));
    } 
  else if (e2 <= 23)
    {
      /* truncate 2nd word (just top 8 bits), zero next */
      asm volatile (
       "andr   %d0,%2
        xorr   %t0,%t0" : "=r" (y) : "0" (y), "r" (-(1 << (23 - e2)) | 0xff));
    } 
  else if (e2 <= 39)
    {
      /* truncate last word */
      asm volatile (
       "andr   %t0,%2" : "=r" (y) : "0" (y), "r" (-(1 << (39 - e2))));
    } 

  return y; 
}

