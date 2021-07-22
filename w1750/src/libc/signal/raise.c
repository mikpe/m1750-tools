/*
 * ANSI Standard C: 7.7.2.1
 * 
 * #include <signal.h>
 * int raise (int sig);
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
 * $Log: raise.c,v $
 * Revision 1.3  1997/08/06 16:46:34  nettleto
 * Updated for 2-word expanded memory links
 *
 * Revision 1.2  1997/07/17 18:56:30  nettleto
 * Updated for expanded memory.
 *
 * Revision 1.1  1997/05/09 17:45:52  nettleto
 * Initial revision
 *
 */

#include <signal.h>

int
raise (int sig)
{
  extern __sighandler_t _sig_func [];

  __sighandler_t func = _sig_func [sig];

  if (func == SIG_DFL)
    ;
  else if (func == SIG_IGN)
    ;
  else if (func == SIG_ERR)
    ;
  else
#ifdef MMU
    asm volatile ("
        lr     r0,%0
        xorr   r11,r11
        lr     r12,%1
        bex    0" :: "r" (sig), "r" (func) : "r0");
#else
    asm volatile ("
        lr     r0,%0
        sjs    r15,0,%1" :: "r" (sig), "x" (func) : "r0");
#endif

}

