/*
 * m1750-coff/include/sys/times.h
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
 * $Log: times.h,v $
 * Revision 1.1  1997/05/09 17:32:54  nettleto
 * Initial revision
 *
 */

#ifndef _SYS_TIMES_H_
#define _SYS_TIMES_H_

#include <sys/cdefs.h>

__BEGIN_DECLS

#include <time.h>

struct tms {
  clock_t tms_utime;   /* user time */
  clock_t tms_stime;   /* system time */
  clock_t tms_cutime;  /* user time, children */
  clock_t tms_cstime;  /* system time, children */
};

clock_t times (struct tms *);

__END_DECLS

#endif /* not _SYS_TIMES_H_ */

