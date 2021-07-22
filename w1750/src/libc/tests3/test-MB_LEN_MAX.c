/*
 * Test for ANSI Standard C: 5.2.4.2.1
 * 
 * #include <limits.h>
 * #define MB_LEN_MAX <#if expression >= 8>;
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
 * $Log: test-MB_LEN_MAX.c,v $
 * Revision 1.1  1997/08/04 13:52:19  nettleto
 * Initial revision
 *
 */

#include <report.h>

#include <limits.h>


static char *_test_MB_LEN_MAX_id =
  "$Id: test-MB_LEN_MAX.c,v 1.1 1997/08/04 13:52:19 nettleto Exp $";

void do_test ()
{
  /* Case 1 */
  if (!(MB_LEN_MAX == 1)) {
    failed ("Case 1: MB_LEN_MAX == 1");
  }
  
}


void main ()
{
  test ("test-MB_LEN_MAX", "Test for ANSI Standard C: 5.2.4.2.1");

  do_test ();

  result ();
}

