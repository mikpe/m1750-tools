/*
 * Test for ANSI Standard C: 7.11.5.4
 * 
 * #include <string.h>
 * size_t strpbrk (const char *s1, const char *s2);
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


static char *_test_strpbrk_id =
  "$Id$";

void do_test ()
{
  /* Case 1 */
  if (!(strpbrk ("", "") == NULL)) {
    failed ("Case 1: strpbrk (\"\", \"\") == NULL");
  }
  
  /* Case 2 */
  if (!(strpbrk ("", "a") == NULL)) {
    failed ("Case 2: strpbrk (\"\", \"a\") == NULL");
  }
  
  /* Case 3 */
  if (!(strpbrk ("", "abc") == NULL)) {
    failed ("Case 3: strpbrk (\"\", \"abc\") == NULL");
  }
  
  /* Case 4 */
  if (!(strpbrk ("1", "") == NULL)) {
    failed ("Case 4: strpbrk (\"1\", \"\") == NULL");
  }
  
  /* Case 5 */
  if (!(strpbrk ("12", "a") == NULL)) {
    failed ("Case 5: strpbrk (\"12\", \"a\") == NULL");
  }
  
  /* Case 6 */
  if (!(strpbrk ("123", "abc") == NULL)) {
    failed ("Case 6: strpbrk (\"123\", \"abc\") == NULL");
  }
  
  /* Case 7 */
  if (!(strcmp (strpbrk ("1", "1"), "1") == 0)) {
    failed ("Case 7: strcmp (strpbrk (\"1\", \"1\"), \"1\") == 0");
  }
  
  /* Case 8 */
  if (!(strcmp (strpbrk ("11111", "1"), "11111") == 0)) {
    failed ("Case 8: strcmp (strpbrk (\"11111\", \"1\"), \"11111\") == 0");
  }
  
  /* Case 9 */
  if (!(strcmp (strpbrk ("1234", "1234"), "1234") == 0)) {
    failed ("Case 9: strcmp (strpbrk (\"1234\", \"1234\"), \"1234\") == 0");
  }
  
  /* Case 10 */
  if (!(strcmp (strpbrk ("1234", "4321"), "1234") == 0)) {
    failed ("Case 10: strcmp (strpbrk (\"1234\", \"4321\"), \"1234\") == 0");
  }
  
  /* Case 11 */
  if (!(strcmp (strpbrk ("zzzz1234", "1"), "1234") == 0)) {
    failed ("Case 11: strcmp (strpbrk (\"zzzz1234\", \"1\"), \"1234\") == 0");
  }
  
}


void main ()
{
  test ("test-strpbrk", "Test for ANSI Standard C: 7.11.5.4");

  do_test ();

  result ();
}

