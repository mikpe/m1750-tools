/*
 * ANSI Standard C: 7.10.4.3
 * 
 * #include <stdlib.h>
 * void exit (int status);
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
 * $Log: exit.c,v $
 * Revision 1.3  1997/08/06 16:49:52  nettleto
 * Updated for 2-word expanded memory links
 *
 * Revision 1.2  1997/07/17 18:52:53  nettleto
 * Update for expanded memory.
 *
 * Revision 1.1  1997/05/09 16:55:38  nettleto
 * Initial revision
 *
 * Revision 1.1  1997/03/21 16:06:03  nettleto
 * Initial revision
 *
 */

#include <stdlib.h>

#include <sys/atexit.h>

void 
exit (int code)
{
  struct _atexit *p;
  int n;

  for (p = _atexit; p; p = p->_next)
    for (n = p->_ind; --n >= 0;)
      {
#ifdef MMU
    asm volatile ( 
       "dlr    r11,%0
        bex    0" :: "r" (p->_fns[n]) 
        : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", 
          "r8", "r9", "r10", "r11", "r12", "r13");
#else
    asm volatile ( 
       "dlr    r11,%0
        sjs    r15,0,r12" :: "r" (p->_fns[n])
        : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", 
          "r8", "r9", "r10", "r11", "r12", "r13");
#endif
      }

  _exit (code);
}

