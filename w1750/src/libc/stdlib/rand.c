/*
 * ANSI Standard C: 7.10.2.1
 * 
 * #include <stdlib.h>
 * int rand (void);
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
 * $Log: rand.c,v $
 * Revision 1.1  1997/05/09 16:55:41  nettleto
 * Initial revision
 *
 */

#include <stdlib.h>

unsigned long _next = 1;

int
rand ()
{
   _next = _next * 1103515245L + 12345L;

  return (int)((_next >> 16) & 0x7fff);
}

