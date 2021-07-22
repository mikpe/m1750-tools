/*
 * ANSI Standard C: 7.10.6.3
 * 
 * #include <stdlib.h>
 * long labs (long);
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
 * $Log: labs.c,v $
 * Revision 1.1  1997/05/09 16:55:39  nettleto
 * Initial revision
 *
 */

#include <stdlib.h>

long
labs (long x)
{
  if (x < 0)
    return -x;
  else
    return x;
}

