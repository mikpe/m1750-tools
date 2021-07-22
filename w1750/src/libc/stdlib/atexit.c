/*
 * ANSI Standard C: 7.10.4.2
 * 
 * #include <stdlib.h>
 * void atexit (void (*func)(void));
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
 * $Log: atexit.c,v $
 * Revision 1.2  1997/07/17 18:55:41  nettleto
 * Updated for long calls.
 *
 * Revision 1.1  1997/05/09 16:55:36  nettleto
 * Initial revision
 *
 * Revision 1.1  1997/03/21 14:08:26  nettleto
 * Initial revision
 *
 */

#include <stdlib.h>

#include <sys/atexit.h>

/*
 * Global data.
 */
struct _atexit *_atexit = NULL;
struct _atexit _atexit0;


int
atexit (void (*func)(void))
{
  struct _atexit *p;
  unsigned long addr;

  if ((p = _atexit) == NULL)
    _atexit = p = &_atexit0;

  if (p->_ind >= _ATEXIT_SIZE)
    {
      return -1;
    }

  /* Build 24-bit word (long) address using 8 bits of address from 
     register SW and given address.  */
  asm volatile (
       "xio    %0,rsw
        lr     %d0,%0
        srl    %d0,4
        andm   %d0,0x00f0
        andm   %0,0x000f
        orr    %0,%d0
        lr     %d0,%1" : "=&r" (addr) : "r" (func));

  /* Write long address to exit table.  */  
  p->_fns[p->_ind++] = addr;

  return 0;
}


