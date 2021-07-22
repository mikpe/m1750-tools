/*
 * Test for ANSI Standard C: 7.11.4.1
 * 
 * #include <string.h>
 * void *memcmp (const void *s1, const void *s2, size_t n);
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


static char *_test_memcmp_id =
  "$Id$";

void do_test ()
{
  /* Case 1 */
  if (!(memcmp ("", "", 1) == 0)) {
    failed ("Case 1: memcmp (\"\", \"\", 1) == 0");
  }
  
  /* Case 2 */
  if (!(memcmp ("1", "1", 2) == 0)) {
    failed ("Case 2: memcmp (\"1\", \"1\", 2) == 0");
  }
  
  /* Case 3 */
  if (!(memcmp ("12345678", "12345678", 9) == 0)) {
    failed ("Case 3: memcmp (\"12345678\", \"12345678\", 9) == 0");
  }
  
  /* Case 4 */
  if (!(memcmp ("12345678", "12345789", 6) != 0)) {
    failed ("Case 4: memcmp (\"12345678\", \"12345789\", 6) != 0");
  }
  
  /* Case 5 */
  if (!(memcmp ("12345678", "12345789", 5) == 0)) {
    failed ("Case 5: memcmp (\"12345678\", \"12345789\", 5) == 0");
  }
  
}


void main ()
{
  test ("test-memcmp", "Test for ANSI Standard C: 7.11.4.1");

  do_test ();

  result ();
}

