/*
 * m1750-coff/include/ctype.h
 *
 * ANSI Standard C: 7.3 Character handling
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
 * $Log: ctype.h,v $
 * Revision 1.2  1997/05/09 17:37:41  nettleto
 * *** empty log message ***
 *
 * Revision 1.1  1997/05/09 17:31:43  nettleto
 * Initial revision
 *
 */

#ifndef _CTYPE_H_
#define _CTYPE_H_

#include <sys/cdefs.h>

__BEGIN_DECLS

/*
 * Each function accepts an argument of type int, whose value can be
 * the value of the macro EOF or any value of type unsigned char. In 
 * this implementation, EOF is -1.
 */

extern	const char _ctype_[];

#define	_U	0x01
#define	_L	0x02
#define	_N	0x04
#define	_S	0x08
#define _P	0x10
#define _C	0x20
#define _X	0x40
#define	_B	0x80

/* 7.3.1.1 */
#define isalnum(c)  ((_ctype_+1)[c]&(_U|_L|_N))

/* 7.3.1.2 */
#define	isalpha(c)  ((_ctype_+1)[c]&(_U|_L))

/* 7.3.1.3 */
#define iscntrl(c)  ((_ctype_+1)[c]&_C)

/* 7.3.1.4 */
#define	isdigit(c)  ((_ctype_+1)[c]&_N)

/* 7.3.1.5 */
#define	isgraph(c)  ((_ctype_+1)[c]&(_P|_U|_L|_N))

/* 7.3.1.6 */
#define	islower(c)  ((_ctype_+1)[c]&_L)

/* 7.3.1.7 */
#define isprint(c)  ((_ctype_+1)[c]&(_P|_U|_L|_N|_B))

/* 7.3.1.8 */
#define ispunct(c)  ((_ctype_+1)[c]&_P)

/* 7.3.1.9 */
#define	isspace(c)  ((_ctype_+1)[c]&_S)

/* 7.3.1.10 */
#define	isupper(c)  ((_ctype_+1)[c]&_U)

/* 7.3.1.11 */
#define	isxdigit(c) ((_ctype_+1)[c]&(_X|_N))

/* 7.3.2.1 */
#define tolower(c) \
	({ int __x = (c); isupper(__x) ? (__x + 'a' - 'A') : __x;})

/* 7.3.2.2 */
#define toupper(c) \
	({ int __x = (c); islower(__x) ? (__x - 'a' + 'A') : __x;})

__END_DECLS

#endif /* not _CTYPE_H_ */

