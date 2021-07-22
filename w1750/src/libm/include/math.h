/*
 * m1750-coff/include/math.h
 *
 * ANSI Standard C: 7.5 Mathematics
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
 * $Log: math.h,v $
 * Revision 1.1  1997/07/27 15:16:55  nettleto
 * Initial revision
 *
 */

#ifndef _MATH_H_
#define _MATH_H_

#include <sys/cdefs.h>

__BEGIN_DECLS

#include <float.h>

#define HUGE_VAL  DBL_MAX

/* 7.5.2.1 */
double 
acos (double x);

/* 7.5.2.2 */
double 
asin (double x);

/* 7.5.2.3 */
double 
atan (double x);

/* 7.5.2.4 */
double 
atan2 (double x, double y);

/* 7.5.2.5 */
double 
cos (double x);

/* 7.5.2.6 */
double 
sin (double x);

/* 7.5.2.7 */
double 
tan (double x);

/* 7.5.3.1 */
double 
cosh (double x);

/* 7.5.3.2 */
double 
sinh (double x);

/* 7.5.3.3 */
double 
tanh (double x);

/* 7.5.4.1 */
double 
exp (double x);

/* 7.5.4.2 */
double
frexp (double value, int *exp);

/* 7.5.4.3 */
double
ldexp (double x, int exp);

/* 7.5.4.4 */
double 
log (double x);

/* 7.5.4.5 */
double 
log10 (double x);

/* 7.5.4.6 */
double
modf (double value, double *iptr);

/* 7.5.5.1 */
double
pow (double x, double y);

/* 7.5.5.2 */
double sqrt (double x);

/* 7.5.6.1 */
double
ceil (double x);

/* 7.5.6.2 */
double 
fabs (double x);

/* 7.5.6.3 */
double
floor (double x);

/* 7.5.6.4 */
double
fmod (double x, double y);


__END_DECLS

#endif /* not _MATH_H_ */

