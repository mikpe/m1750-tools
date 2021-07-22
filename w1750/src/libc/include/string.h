/*
 * m1750-coff/include/string.h
 *
 * ANSI Standard C: 7.11 String handling
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
 * $Log: string.h,v $
 * Revision 1.2  1997/05/09 17:37:48  nettleto
 * *** empty log message ***
 *
 * Revision 1.1  1997/05/09 17:31:46  nettleto
 * Initial revision
 *
 */

#ifndef _STRING_H_
#define _STRING_H_

#include <sys/cdefs.h>

__BEGIN_DECLS

#ifndef NULL
#define NULL ((void *)0)
#endif

#ifndef _SIZE_T_
#define _SIZE_T_
typedef unsigned int size_t;
#endif

/* 7.11.2.1 */
void *
memcpy (void *s1, const void *s2, size_t n);

/* 7.11.2.2 */
void *
memmove (void *s1, const void *s2, size_t n);

/* 7.11.2.3 */
char *
strcpy (char *s1, const char *s2);

/* 7.11.2.4 */
char *
strncpy (char *s1, const char *s2, size_t n);

/* 7.11.3.1 */
char *
strcat (char *s1, const char *s2);

/* 7.11.3.2 */
char *
strncat (char *s1, const char *s2, size_t n);

/* 7.11.4.1 */
int  
memcmp (const void *s1, const void *s2, size_t n);

/* 7.11.4.2 */
int 
strcmp (const char *s1, const char *s2);

/* 7.11.4.3 */
int 
strcoll (const char *s1, const char *s2);

/* 7.11.4.4 */
int 
strncmp (const char *s1, const char *s2, size_t n);

/* 7.11.4.5 */
size_t 
strxfrm (char *s1, const char *s2, size_t n);

/* 7.11.5.1 */
void *
memchr (const void *s, int c, size_t n);

/* 7.11.5.2 */
char *
strchr (const char *s, int c);

/* 7.11.5.3 */
size_t 
strcspn (const char *s1, const char *s2);

/* 7.11.5.4 */
char *
strpbrk (const char *s1, const char *s2);

/* 7.11.5.5 */
char *
strrchr (const char *s1, int c);

/* 7.11.5.6 */
size_t 
strspn (const char *s1, const char *s2);

/* 7.11.5.7 */
char *
strstr (const char *s1, const char *s2);

/* 7.11.5.8 */
char *
strtok (char *s1, const char *s2);

/* 7.11.6.1 */
void *
memset (void *s, int c, size_t n);

/* 7.11.6.2 */
char *
strerror (int errnum);

/* 7.11.6.3 */
size_t 
strlen (const char *s);

__END_DECLS

#endif /* not _STRING_H_ */

