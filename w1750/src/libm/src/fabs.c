/*
 * ANSI Standard C: 7.5.6.2
 * 
 * #include <math.h>
 * double fabs (double x);
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
 * $Log: fabs.c,v $
 * Revision 1.1  1997/03/17 17:17:46  nettleto
 * Initial revision
 *
 */

#include <math.h>

double
fabs (double x)
{
  if (x < 0.0)
    return -x;

  return x;
}

