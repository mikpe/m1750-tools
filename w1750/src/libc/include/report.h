/*
 * m1750-coff/include/report.h
 *
 * ANSI Standard C:  Test Support
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
 * $Log: report.h,v $
 * Revision 1.2  1997/05/09 17:37:45  nettleto
 * *** empty log message ***
 *
 * Revision 1.1  1997/05/09 17:31:44  nettleto
 * Initial revision
 *
 */

#ifndef _REPORT_H_
#define _REPORT_H_

#include <sys/cdefs.h>

__BEGIN_DECLS

void
test (char *name, char *description, ...);
  /*
    --------------------------------------------------------------------
    Indicate the start of a test with the given test name
    --------------------------------------------------------------------
  */

void 
failed (char *description, ...);
  /*
    --------------------------------------------------------------------
    Indicate that the running test has failed. Output the description.
    --------------------------------------------------------------------
  */

void 
comment (char *description, ...);
  /*
    --------------------------------------------------------------------
    Just output the description as a comment.
    --------------------------------------------------------------------
  */

void 
result ();
  /*
    --------------------------------------------------------------------
    To be called at the end of a test to print the result.
    --------------------------------------------------------------------
  */


int
ident_int (int i);
  /*
    --------------------------------------------------------------------
    Return the integer i
    --------------------------------------------------------------------
  */

long
ident_long (long i);
  /*
    --------------------------------------------------------------------
    Return the long integer i
    --------------------------------------------------------------------
  */

long long
ident_long_long (long long i);
  /*
    --------------------------------------------------------------------
    Return the long long integer i
    --------------------------------------------------------------------
  */

float
ident_float (float i);
  /*
    --------------------------------------------------------------------
    Return the float f
    --------------------------------------------------------------------
  */


double
ident_double (double i);
  /*
    --------------------------------------------------------------------
    Return the double float i
    --------------------------------------------------------------------
  */

__END_DECLS

#endif /* not _REPORT_H_ */

