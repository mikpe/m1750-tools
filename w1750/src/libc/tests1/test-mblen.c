/*
 * Test for ANSI Standard C: 7.10.7.1
 * 
 * #include <stdlib.h>
 * int mblen (const char *s, size_t n);
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
 * $Log$
 */

#include <report.h>

#include <stdlib.h>


static char *_test_mblen_id =
  "$Id$";

void do_test ()
{
  /* Case 1 */
  if (!(mblen (NULL, 0) == 0)) {
    failed ("Case 1: mblen (NULL, 0) == 0");
  }
  
  /* Case 2 */
  if (!(mblen ("abcd", 4) == 1)) {
    failed ("Case 2: mblen (\"abcd\", 4) == 1");
  }
  
}


void main ()
{
  test ("test-mblen", "Test for ANSI Standard C: 7.10.7.1");

  do_test ();

  result ();
}

