/*
 * ANSI Standard C: 7.5.6.4
 * 
 * #include <math.h>
 * double fmod (double x, double y);
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
 * $Log: fmod.c,v $
 * Revision 1.1  1997/03/17 17:17:57  nettleto
 * Initial revision
 *
 */

#include <math.h>

double
fmod (double x, double y)
{
  /*
   * Return the value x - i * y for some integer i such that, if
   * y is non zero, the result has the same sign as x and magnitude 
   * less than the magnitude of y.
   */

  double i;

  if (x >= 0.0)
    {
      if (y >= 0.0)
        i = floor (x / y);
      else
        i = - floor (x / -y);
    }
  else
    {
      if (y < 0.0)
        i = floor (x / y);
      else
        i = - floor (-x / y);
    }
 
  return x - i * y;
}

