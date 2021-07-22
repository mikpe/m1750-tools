/*
 * Test for ANSI Standard C: 5.2.4.2.1
 * 
 * #include <limits.h>
 * #define LONG_MIN <#if expression >= 8>;
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
 * $Log: test-LONG_MIN.c,v $
 * Revision 1.1  1997/08/04 13:52:19  nettleto
 * Initial revision
 *
 */

#include <report.h>

#include <limits.h>


static char *_test_LONG_MIN_id =
  "$Id: test-LONG_MIN.c,v 1.1 1997/08/04 13:52:19 nettleto Exp $";

void do_test ()
{
  /* Case 1 */
  if (!(LONG_MIN == 0x80000000)) {
    failed ("Case 1: LONG_MIN == 0x80000000");
  }
  
}


void main ()
{
  test ("test-LONG_MIN", "Test for ANSI Standard C: 5.2.4.2.1");

  do_test ();

  result ();
}

