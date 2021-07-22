/*
 * Test for ANSI Standard C: 5.2.4.2.1
 * 
 * #include <limits.h>
 * #define INT_MIN <#if expression >= 8>;
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
 * $Log: test-INT_MIN.c,v $
 * Revision 1.1  1997/08/04 13:52:18  nettleto
 * Initial revision
 *
 */

#include <report.h>

#include <limits.h>


static char *_test_INT_MIN_id =
  "$Id: test-INT_MIN.c,v 1.1 1997/08/04 13:52:18 nettleto Exp $";

void do_test ()
{
  /* Case 1 */
  if (!(INT_MIN == 0x8000)) {
    failed ("Case 1: INT_MIN == 0x8000");
  }
  
}


void main ()
{
  test ("test-INT_MIN", "Test for ANSI Standard C: 5.2.4.2.1");

  do_test ();

  result ();
}

