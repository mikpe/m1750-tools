/*
 * m1750-coff/include/setjmp.h
 *
 * POSIX/ANSI Standard C: 7.6 Nonlocal jumps
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
 * $Log: setjmp.h,v $
 * Revision 1.2  1997/05/09 17:37:45  nettleto
 * *** empty log message ***
 *
 * Revision 1.1  1997/05/09 17:31:44  nettleto
 * Initial revision
 *
 */

#ifndef _SETJMP_H_
#define _SETJMP_H_

#include <sys/cdefs.h>

__BEGIN_DECLS

typedef struct
{
  short im, sw, ic;  
  short r14, r15;
} jmp_buf [1];

/* 7.6.1.1 */
#define setjmp(env) _setjmp (env)

/* 7.6.2.1 */
void longjmp (jmp_buf env, int val);

__END_DECLS

#endif /* not _SETJMP_H_ */

