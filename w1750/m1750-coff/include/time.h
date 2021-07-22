/*
 * m1750-coff/include/time.h
 *
 * ANSI Standard C: 7.12 Date and time
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
 * $Log: time.h,v $
 * Revision 1.3  1997/07/17 19:02:57  nettleto
 * Changed CLOCKS_PER_SEC to 100 to agree with POSIX.
 *
 * Revision 1.2  1997/05/09 17:37:48  nettleto
 * *** empty log message ***
 *
 * Revision 1.1  1997/05/09 17:31:46  nettleto
 * Initial revision
 *
 */

#ifndef _TIME_H_
#define _TIME_H_

#include <sys/cdefs.h>

__BEGIN_DECLS

typedef long clock_t;
typedef long time_t;

#ifndef _SIZE_T_
#define _SIZE_T_
typedef unsigned int size_t;
#endif

#ifndef NULL
#ifdef __cplusplus
#define NULL	0
#else
#define NULL	((void *) 0)
#endif
#endif

#define CLOCKS_PER_SEC	100

struct tm {
  int tm_sec;    /* seconds after the minute, 0 .. 61 */
  int tm_min;    /* minutes after the hour, 0 .. 59 */
  int tm_hour;   /* hours since midnight, 0 .. 23 */
  int tm_mday;   /* day of the month, 1 .. 31 */
  int tm_mon;    /* months since January, 0 .. 11 */
  int tm_year;   /* years since 1900 */
  int tm_wday;   /* days since Sunday, 0 .. 6 */
  int tm_yday;   /* days since January 1, 0 .. 365 */
  int tm_isdst;  /* daylight saving time flag */
};

/* 7.12.2.1 */
clock_t 
clock (void);

/* 7.12.2.2 */
double 
difftime (time_t time1, time_t time0);

/* 7.12.2.13 */
time_t 
mktime (struct tm *timeptr);

/* 7.12.2.4 */
time_t 
time (time_t *timer);

/* 7.12.3.1 */
char *
asctime (const struct tm *timeptr);

/* 7.12.3.2 */
char *
ctime (const time_t *timer);

/* 7.12.3.3 */
struct tm *
gmtime (const time_t *timer);

/* 7.12.3.4 */
struct tm *
localtime (const time_t *timer);

/* 7.12.3.5 */
size_t 
strftime (char *s, size_t maxsize,
          const char *format, const struct tm *timeptr);

__END_DECLS

#endif /* not _TIME_H_ */

