/*
 * m1750-coff/include/stddef.h
 *
 * ANSI Standard C: 7.1.6 Common definitions
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
 * $Log: stddef.h,v $
 * Revision 1.2  1997/05/09 17:37:46  nettleto
 * *** empty log message ***
 *
 * Revision 1.1  1997/05/09 17:31:45  nettleto
 * Initial revision
 *
 */

#ifndef _STDDEF_H_
#define _STDDEF_H_

#include <sys/cdefs.h>

__BEGIN_DECLS

#ifndef NULL
#ifdef __cplusplus
#define NULL    0
#else
#define NULL    ((void *) 0)
#endif
#endif

#define offsetof(TYPE, MEMBER) ((size_t) &((TYPE *)0)->MEMBER)

#ifndef _PTRDIFF_T_
#define _PTRDIFF_T_
typedef int ptrdiff_t;
#endif

#ifndef _SIZE_T_
#define _SIZE_T_
typedef unsigned int size_t;
#endif

typedef int wchar_t;

__END_DECLS

#endif /* not _STDDEF_H_ */

