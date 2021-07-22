/*
 * m1750-coff/include/stdlib.h
 *
 * ANSI Standard C: 7.10 General utilities
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
 * $Log: stdlib.h,v $
 * Revision 1.2  1997/05/09 17:37:47  nettleto
 * *** empty log message ***
 *
 * Revision 1.1  1997/05/09 17:31:46  nettleto
 * Initial revision
 *
 */

#ifndef _STDLIB_H_
#define _STDLIB_H_

#include <sys/cdefs.h>

__BEGIN_DECLS

#include <stddef.h>

typedef struct 
{
  int quot;  /* quotient */
  int rem;   /* remainder */
} div_t;

typedef struct 
{
  long quot; /* quotient */
  long rem;  /* remainder */
} ldiv_t;

#ifndef NULL
#ifdef __cplusplus
#define NULL    0
#else
#define NULL    ((void *) 0)
#endif
#endif

#define EXIT_FAILURE 1
#define EXIT_SUCCESS 0

#define RAND_MAX 0x7fff

#define MB_CUR_MAX 1 

/* 7.10.1 1 */
double 
atof (const char *nptr);

/* 7.10.1.2 */
int 
atoi (const char *nptr);

/* 7.10.1.3 */
long 
atol (const char *nptr);

/* 7.10.1.4 */
double 
strtod (const char *nptr, char **endptr);

/* 7.10.1.5 */
long 
strtol (const char *nptr, char **endptr, int base);

/* 7.10.1.6 */
unsigned long 
strtoul (const char *nptr, char **endptr, int base);

/* 7.10.2.1 */
int 
rand (void);

/* 7.10.2.2 */
void 
srand (unsigned seed);

/* 7.10.3.1 */
void *
calloc (size_t nmemb, size_t size);

/* 7.10.3.2 */
void 
free (void *ptr);

/* 7.10.3.3 */
void *
malloc (size_t size);

/* 7.10.3.4 */
void *
realloc (void *ptr, size_t size);

/* 7.10.4.1 */
void 
abort (void);

/* 7.10.4.2 */
int 
atexit (void (*func)(void));

/* 7.10.4.3 */
void 
exit (int status);

/* 7.10.4.4 */
char *
getenv (const char *name);

/* 7.10.4.5 */
int 
system (const char *string);

/* 7.10.5.1 */
void *
bsearch (const void *key, const void *base, size_t nmemb, size_t size,
         int (*compar) (const void *, const void *));

/* 7.10.5.2 */
void 
qsort (void *base, size_t nmemb, size_t size, 
       int(*compar)(const void *, const void *));

/* 7.10.6.1 */
int 
abs (int j);

/* 7.10.6.2 */
div_t 
div (int numer, int denom);

/* 7.10.6.3 */
long 
labs (long int j);

/* 7.10.6.4 */
ldiv_t 
ldiv (long int numer, long int denom);

/* 7.10.7.1 */
int 
mblen (const char *s, size_t n);

/* 7.10.7.2 */
int 
mbtowc (wchar_t *pwc, const char *s, size_t n);

/* 7.10.7.3 */
int 
wctomb (char *s, wchar_t wchar);

/* 7.10.8.1 */
size_t 
mbstowcs (wchar_t *pwcs, const char *s, size_t n);

/* 7.10.8.2 */
size_t 
wcstombs (char *s, const wchar_t *pwcs, size_t n);

__END_DECLS

#endif /* not _STDLIB_H_ */

