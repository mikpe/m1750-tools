/*
 * m1750-coff/include/assert.h
 *
 * ANSI Standard C: 7.2 Diagnostics
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
 * $Log: assert.h,v $
 * Revision 1.2  1997/05/09 17:37:39  nettleto
 * *** empty log message ***
 *
 * Revision 1.1  1997/05/09 17:31:41  nettleto
 * Initial revision
 *
 */

#ifndef _ASSERT_H_
#define _ASSERT_H_

#include <sys/cdefs.h>

__BEGIN_DECLS

#undef assert

#ifdef NDEBUG
#define assert(ignore) ((void) 0)
#else
#define __STRING(x)     #x
#define assert(expr) \
  ((void) ((expr) || \
           (_assert (__STRING(expr), __FILE__, __LINE__), 0)))

extern void _assert (
  const char *__assertion,
  const char *__file,
  unsigned int __line);

#endif /* NDEBUG */

__END_DECLS

#endif /* not _ASSERT_H_ */

