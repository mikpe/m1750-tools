/*
 * m1750-coff/include/limits.h
 *
 * ANSI Standard C: 7.1.5 Limits
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
 * $Log: limits.h,v $
 * Revision 1.3  1997/05/13 18:38:20  nettleto
 * Updated LONG_MIN to avoid overflow.
 *
 * Revision 1.2  1997/05/09 17:37:44  nettleto
 * *** empty log message ***
 *
 * Revision 1.1  1997/05/09 17:31:44  nettleto
 * Initial revision
 *
 */

#ifndef _LIMITS_H_
#define _LIMITS_H_

#include <sys/cdefs.h>

__BEGIN_DECLS

#define CHAR_BIT   (16)
#define CHAR_MAX   (32767)
#define CHAR_MIN   (-32768)

#define INT_MAX    (32767)
#define INT_MIN    (-32768)

#define LONG_MAX   (2147483647L)
#define LONG_MIN   (-LONG_MAX-1)

#define MB_LEN_MAX (1)

#define SCHAR_MAX  (32767)
#define SCHAR_MIN  (-32768)

#define SHRT_MAX   (32767)
#define SHRT_MIN   (-32768)

#define UCHAR_MAX  (65535U)
#define UINT_MAX   (65535U)
#define ULONG_MAX  (4294967295U)
#define USHRT_MAX  (65535U)

__END_DECLS

#endif /* not _LIMITS_H_ */

