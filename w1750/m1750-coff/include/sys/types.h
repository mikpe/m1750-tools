/*
 * m1750-coff/include/sys/types.h
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
 * $Log: types.h,v $
 * Revision 1.1  1997/05/09 17:32:55  nettleto
 * Initial revision
 *
 */

#ifndef _SYS_TYPES_H_
#define _SYS_TYPES_H_

#include <sys/cdefs.h>

__BEGIN_DECLS

typedef int pid_t;
typedef unsigned short uid_t;
typedef unsigned short gid_t;
typedef unsigned short dev_t;
typedef unsigned long ino_t;
typedef unsigned short mode_t;
typedef unsigned short umode_t;
typedef unsigned short nlink_t;
typedef int daddr_t;
typedef long off_t;

typedef unsigned long u_long;
typedef unsigned short u_short;
typedef unsigned int u_int;

__END_DECLS

#endif /* not _SYS_TYPES_H_ */

