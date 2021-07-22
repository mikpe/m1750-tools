/*
 * Test for ANSI Standard C: 7.11.5.3
 * 
 * #include <string.h>
 * size_t strcspn (const char *s1, const char *s2);
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

#include <string.h>


static char *_test_strcspn_id =
  "$Id$";

void do_test ()
{
  /* Case 1 */
  if (!(strcspn ("", "") == 0)) {
    failed ("Case 1: strcspn (\"\", \"\") == 0");
  }
  
  /* Case 2 */
  if (!(strcspn ("", "1234") == 0)) {
    failed ("Case 2: strcspn (\"\", \"1234\") == 0");
  }
  
  /* Case 3 */
  if (!(strcspn ("qwertyuiop", "qwertyuiop") == 0)) {
    failed ("Case 3: strcspn (\"qwertyuiop\", \"qwertyuiop\") == 0");
  }
  
  /* Case 4 */
  if (!(strcspn ("qwertyuiop", "1234567890") == 10)) {
    failed ("Case 4: strcspn (\"qwertyuiop\", \"1234567890\") == 10");
  }
  
  /* Case 5 */
  if (!(strcspn ("qwertyuiop", "t") == 4)) {
    failed ("Case 5: strcspn (\"qwertyuiop\", \"t\") == 4");
  }
  
}


void main ()
{
  test ("test-strcspn", "Test for ANSI Standard C: 7.11.5.3");

  do_test ();

  result ();
}

