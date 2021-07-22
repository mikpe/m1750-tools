/*
 * m1750-coff/include/sys/atexit.h
 *
 * GCC-1750 system header file:  
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
 * $Log: atexit.h,v $
 * Revision 1.2  1997/07/17 19:04:11  nettleto
 * Made the exit function addresses long.
 *
 * Revision 1.1  1997/05/09 17:32:53  nettleto
 * Initial revision
 *
 */

#ifndef _SYS_ATEXIT_H_
#define _SYS_ATEXIT_H_

#include <sys/cdefs.h>

__BEGIN_DECLS

/* 
 * Must be at least 32 to guarantee ANSI conformance 
 */
#define _ATEXIT_SIZE 32 

struct _atexit {
  struct _atexit *_next;             /* next in list */
  int    _ind;                       /* next index in this table */
  unsigned long _fns[_ATEXIT_SIZE];  /* the table itself */
};

/*
 * _atexit points to head of LIFO stack
 * _atexit0 is a guaranteed table, required by ANSI
 */
extern struct _atexit *_atexit;
extern struct _atexit _atexit0;

__END_DECLS

#endif /* not _SYS_ATEXIT_H_ */

