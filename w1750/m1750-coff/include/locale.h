/*
 * m1750-coff/include/locale.h
 *
 * ANSI Standard C: 7.4 Localization
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
 * $Log: locale.h,v $
 * Revision 1.2  1997/05/09 17:37:44  nettleto
 * *** empty log message ***
 *
 * Revision 1.1  1997/05/09 17:31:44  nettleto
 * Initial revision
 *
 */

#ifndef _LOCALE_H_
#define _LOCALE_H_

#include <sys/cdefs.h>

__BEGIN_DECLS

#ifndef NULL
#define NULL ((void *)0)
#endif

/*
 * These are the possibilities for the first argument to setlocale. The
 * code assumes that LC_ALL is the highest value, and zero the lowest. 
 */

#define	LC_ALL		6
#define	LC_COLLATE	3
#define	LC_CTYPE	0
#define	LC_MONETARY	4
#define	LC_NUMERIC	1
#define	LC_TIME		2

#define	LC_MESSAGES	5


/* 
 * Structure giving information about numeric and monetary notation. 
 */
struct lconv
{
  char *decimal_point;		/* Decimal point character */
  char *thousands_sep;		/* Thousands separator */

  char *grouping;

  /*
   * First three chars are a currency symbol from ISO 4217. Fourth char is
   * the separator Fifth char is '\0'.
   *  
   */
  char *int_curr_symbol;        /* International currency symbol */
  
  char *currency_symbol;	/* Local currency symbol */
  char *mon_decimal_point;	/* Decimal point character */
  char *mon_thousands_sep;	/* Thousands separator */
  char *mon_grouping;		/* Like `grouping' element (above) */
  char *positive_sign;		/* Sign for positive values */
  char *negative_sign;		/* Sign for negative values */
  char int_frac_digits;		/* Int'l fractional digits */
  char frac_digits;		/* Local fractional digits */
  
  char p_cs_precedes;
  char p_sep_by_space;
  char n_cs_precedes;
  char n_sep_by_space;
  
  /*
   * Positive and negative sign positions:
   * 0 Parentheses surround the quantity and currency_symbol
   * 1 The sign string precedes the quantity and currency_symbol
   * 2 The sign string succedes the quantity and currency_symbol
   * 3 The sign string immediately precedes the currency_symbol
   * 4 The sign string immediately succedes the currency_symbol
   */
  char p_sign_posn;
  char n_sign_posn;
};

/* 
 * 7.4.1.1 Set and/or return the current locale
 */
extern char *setlocale (int __category, __const char *__locale);

/* 
 * 7.4.2.1 Return the numeric/monetary information for the current locale
 */
extern struct lconv *localeconv (void);

__END_DECLS

#endif /* not _LOCALE_H_ */

