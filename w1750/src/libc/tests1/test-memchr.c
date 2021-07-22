/*
 * Test for ANSI Standard C: 7.11.5.1
 * 
 * #include <string.h>
 * void *memchr (const void *s, int c, size_t n);
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


static char *_test_memchr_id =
  "$Id$";

void do_test ()
{
  /* Case 1 */
  if (!(memchr ("ABCabcABCabc", ' ', 12) == NULL)) {
    failed ("Case 1: memchr (\"ABCabcABCabc\", ' ', 12) == NULL");
  }
  
  /* Case 2 */
  if (!(memchr ("1", ' ', 1) == NULL)) {
    failed ("Case 2: memchr (\"1\", ' ', 1) == NULL");
  }
  
  /* Case 3 */
  if (!(memchr ("12", ' ', 2) == NULL)) {
    failed ("Case 3: memchr (\"12\", ' ', 2) == NULL");
  }
  
  /* Case 4 */
  if (!(memchr ("123", ' ', 3) == NULL)) {
    failed ("Case 4: memchr (\"123\", ' ', 3) == NULL");
  }
  
  /* Case 5 */
  if (!(memchr ("1234", ' ', 4) == NULL)) {
    failed ("Case 5: memchr (\"1234\", ' ', 4) == NULL");
  }
  
  /* Case 6 */
  if (!(strcmp (memchr (" ", ' ', 1), " ") == 0)) {
    failed ("Case 6: strcmp (memchr (\" \", ' ', 1), \" \") == 0");
  }
  
  /* Case 7 */
  if (!(strcmp (memchr ("1 ", ' ', 2), " ") == 0)) {
    failed ("Case 7: strcmp (memchr (\"1 \", ' ', 2), \" \") == 0");
  }
  
  /* Case 8 */
  if (!(strcmp (memchr ("12 ", ' ', 3), " ") == 0)) {
    failed ("Case 8: strcmp (memchr (\"12 \", ' ', 3), \" \") == 0");
  }
  
  /* Case 9 */
  if (!(strcmp (memchr ("123 ", ' ', 4), " ") == 0)) {
    failed ("Case 9: strcmp (memchr (\"123 \", ' ', 4), \" \") == 0");
  }
  
  /* Case 10 */
  if (!(strcmp (memchr ("1234 ", ' ', 5), " ") == 0)) {
    failed ("Case 10: strcmp (memchr (\"1234 \", ' ', 5), \" \") == 0");
  }
  
  /* Case 11 */
  if (!(strcmp (memchr ("ABCabcABCabc", 'A', 12), "ABCabcABCabc") == 0)) {
    failed ("Case 11: strcmp (memchr (\"ABCabcABCabc\", 'A', 12), \"ABCabcABCabc\") == 0");
  }
  
  /* Case 12 */
  if (!(strcmp (memchr ("ABCabcABCabc", 'B', 12), "BCabcABCabc") == 0)) {
    failed ("Case 12: strcmp (memchr (\"ABCabcABCabc\", 'B', 12), \"BCabcABCabc\") == 0");
  }
  
  /* Case 13 */
  if (!(strcmp (memchr ("ABCabcABCabc", 'C', 12), "CabcABCabc") == 0)) {
    failed ("Case 13: strcmp (memchr (\"ABCabcABCabc\", 'C', 12), \"CabcABCabc\") == 0");
  }
  
  /* Case 14 */
  if (!(strcmp (memchr ("ABCabcABCabc", 'a', 12), "abcABCabc") == 0)) {
    failed ("Case 14: strcmp (memchr (\"ABCabcABCabc\", 'a', 12), \"abcABCabc\") == 0");
  }
  
  /* Case 15 */
  if (!(strcmp (memchr ("ABCabcABCabc", 'b', 12), "bcABCabc") == 0)) {
    failed ("Case 15: strcmp (memchr (\"ABCabcABCabc\", 'b', 12), \"bcABCabc\") == 0");
  }
  
  /* Case 16 */
  if (!(strcmp (memchr ("ABCabcABCabc", '\0', 13), "") == 0)) {
    failed ("Case 16: strcmp (memchr (\"ABCabcABCabc\", '\\0', 13), \"\") == 0");
  }
  
}


void main ()
{
  test ("test-memchr", "Test for ANSI Standard C: 7.11.5.1");

  do_test ();

  result ();
}

