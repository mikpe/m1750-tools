/*
 * ANSI Standard C: 7.5.4.6
 * 
 * #include <math.h>
 * double modf (double value, double *iptr);
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
 * $Log: modf.c,v $
 * Revision 1.1  1997/03/17 17:21:27  nettleto
 * Initial revision
 *
 */

#include <math.h>

double
modf (double value, double *iptr)
{
  /*
   * The modf function breaks the argument 'value' into integral and
   * fraction parts, each of which has the same sign as the argument. It
   * stores the integral part as a double in the object pointed to by 
   * 'iptr' and returns the fraction.
   */

  double i = floor (value);

  if (value < 0.0 && i < value)
    i += 1.0;

  *iptr = i;

  return value - i;
}

