/*
 * m1750-coff/include/sys/time.h
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
 * $Log: time.h,v $
 * Revision 1.2  1997/07/17 19:04:47  nettleto
 * Removed leading underscores.
 *
 * Revision 1.1  1997/05/09 17:32:54  nettleto
 * Initial revision
 *
 */

#ifndef _SYS_TIME_H_
#define _SYS_TIME_H_

#include <sys/cdefs.h>

__BEGIN_DECLS

struct timeval {
  long tv_sec;
  long tv_usec;
};

struct timezone {
  int tz_minuteswest;
  int tz_dsttime;
};


int
gettimeofday (struct timeval * __tp,
              struct timezone * __tz);

int
settimeofday (const struct timeval *__tv,
              const struct timezone *__tz);

int
utimes (char *__path, struct timeval *tvp);


__END_DECLS

#endif /* not _SYS_TIME_H_ */

