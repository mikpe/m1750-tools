/*
 * m1750-coff/include/float.h
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
 * $Log: float.h,v $
 * Revision 1.2  1997/05/09 17:37:42  nettleto
 * *** empty log message ***
 *
 * Revision 1.1  1997/05/09 17:31:43  nettleto
 * Initial revision
 *
 */

#ifndef _FLOAT_H_
#define _FLOAT_H_

#include <sys/cdefs.h>

__BEGIN_DECLS

/*
 * FLT_EPSILON  = 2^(-22)
 * FLT_MAX      = (1 - 2^(-23)) * 2^127
 * FLT_MIN      = 0.5 * 2^(-128)
 * 
 * DBL_EPSILON  = 2^(-38)
 * DBL_MAX      = (1 - 2^(-39)) * 2^127
 * DBL_MIN      = 0.5 * 2^(-128)
 */

#define FLT_RADIX       (2)
#define FLT_ROUNDS      (0)

#define FLT_DIG         (6)

/* FIXME: value should be 2.38418579e-7, but
   compiler changes it. Why? */
#define FLT_EPSILON     (2.38418595E-7)
#define FLT_MANT_DIG    (23)
#define FLT_MAX         (1.7014116E38)
#define FLT_MAX_10_EXP  (38)
#define FLT_MAX_EXP     (126)
#define FLT_MIN         (1.46936794E-39)
#define FLT_MIN_10_EXP  (-39)
#define FLT_MIN_EXP     (-129)

#define DBL_DIG         (11)
#define DBL_EPSILON     (3.637978807092E-12)
#define DBL_MANT_DIG    (39)
#define DBL_MAX         (1.701411834602E38)
#define DBL_MAX_10_EXP  (38)
#define DBL_MAX_EXP     (126)
#define DBL_MIN         (1.469367938528E-39)
#define DBL_MIN_10_EXP  (-39)
#define DBL_MIN_EXP     (-129)

__END_DECLS

#endif /* not _FLOAT_H_ */

