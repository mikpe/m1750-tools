/*
 * Test for ANSI Standard C: 7.11.4.4
 * 
 * #include <string.h>
 * void *strncmp (const char *s1, const char *s2, size_t n);
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


static char *_test_strncmp_id =
  "$Id$";

void do_test ()
{
  /* Case 1 */
  if (!(strncmp ("", "", 0) == 0)) {
    failed ("Case 1: strncmp (\"\", \"\", 0) == 0");
  }
  
  /* Case 2 */
  if (!(strncmp ("12345678", "zzzzzzzz", 0) == 0)) {
    failed ("Case 2: strncmp (\"12345678\", \"zzzzzzzz\", 0) == 0");
  }
  
  /* Case 3 */
  if (!(strncmp ("1234", "1qqq", 1) == 0)) {
    failed ("Case 3: strncmp (\"1234\", \"1qqq\", 1) == 0");
  }
  
  /* Case 4 */
  if (!(strncmp ("1234", "5678", 4) < 0)) {
    failed ("Case 4: strncmp (\"1234\", \"5678\", 4) < 0");
  }
  
  /* Case 5 */
  if (!(strncmp ("abcd", "5678", 4) > 0)) {
    failed ("Case 5: strncmp (\"abcd\", \"5678\", 4) > 0");
  }
  
}


void main ()
{
  test ("test-strncmp", "Test for ANSI Standard C: 7.11.4.4");

  do_test ();

  result ();
}

