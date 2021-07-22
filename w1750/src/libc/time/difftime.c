/*
 * ANSI Standard C: 7.12.2.2
 * 
 * #include <time.h>
 * double difftime (time_t time1, time_t time0);
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
 * $Log: difftime.c,v $
 * Revision 1.1  1997/02/14 09:29:29  nettleto
 * Initial revision
 *
 */

#include <time.h>

/*
 * Original Author: G. Haley
 */

double
difftime (time_t time1, time_t time0)
{
  return (double) (time1 - time0);
}

