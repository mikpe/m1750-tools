/*
 * Test for ANSI Standard C: 7.11.5.2
 * 
 * #include <string.h>
 * char *strchr (const char *s, int c);
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


static char *_test_strchr_id =
  "$Id$";

void do_test ()
{
  /* Case 1 */
  if (!(strchr ("ABCabcABCabc", ' ') == NULL)) {
    failed ("Case 1: strchr (\"ABCabcABCabc\", ' ') == NULL");
  }
  
  /* Case 2 */
  if (!(strchr ("1", ' ') == NULL)) {
    failed ("Case 2: strchr (\"1\", ' ') == NULL");
  }
  
  /* Case 3 */
  if (!(strchr ("12", ' ') == NULL)) {
    failed ("Case 3: strchr (\"12\", ' ') == NULL");
  }
  
  /* Case 4 */
  if (!(strchr ("123", ' ') == NULL)) {
    failed ("Case 4: strchr (\"123\", ' ') == NULL");
  }
  
  /* Case 5 */
  if (!(strchr ("1234", ' ') == NULL)) {
    failed ("Case 5: strchr (\"1234\", ' ') == NULL");
  }
  
  /* Case 6 */
  if (!(strcmp (strchr (" ", ' '), " ") == 0)) {
    failed ("Case 6: strcmp (strchr (\" \", ' '), \" \") == 0");
  }
  
  /* Case 7 */
  if (!(strcmp (strchr ("1 ", ' '), " ") == 0)) {
    failed ("Case 7: strcmp (strchr (\"1 \", ' '), \" \") == 0");
  }
  
  /* Case 8 */
  if (!(strcmp (strchr ("12 ", ' '), " ") == 0)) {
    failed ("Case 8: strcmp (strchr (\"12 \", ' '), \" \") == 0");
  }
  
  /* Case 9 */
  if (!(strcmp (strchr ("123 ", ' '), " ") == 0)) {
    failed ("Case 9: strcmp (strchr (\"123 \", ' '), \" \") == 0");
  }
  
  /* Case 10 */
  if (!(strcmp (strchr ("1234 ", ' '), " ") == 0)) {
    failed ("Case 10: strcmp (strchr (\"1234 \", ' '), \" \") == 0");
  }
  
  /* Case 11 */
  if (!(strcmp (strchr ("ABCabcABCabc", 'A'), "ABCabcABCabc") == 0)) {
    failed ("Case 11: strcmp (strchr (\"ABCabcABCabc\", 'A'), \"ABCabcABCabc\") == 0");
  }
  
  /* Case 12 */
  if (!(strcmp (strchr ("ABCabcABCabc", 'B'), "BCabcABCabc") == 0)) {
    failed ("Case 12: strcmp (strchr (\"ABCabcABCabc\", 'B'), \"BCabcABCabc\") == 0");
  }
  
  /* Case 13 */
  if (!(strcmp (strchr ("ABCabcABCabc", 'C'), "CabcABCabc") == 0)) {
    failed ("Case 13: strcmp (strchr (\"ABCabcABCabc\", 'C'), \"CabcABCabc\") == 0");
  }
  
  /* Case 14 */
  if (!(strcmp (strchr ("ABCabcABCabc", 'a'), "abcABCabc") == 0)) {
    failed ("Case 14: strcmp (strchr (\"ABCabcABCabc\", 'a'), \"abcABCabc\") == 0");
  }
  
  /* Case 15 */
  if (!(strcmp (strchr ("ABCabcABCabc", 'b'), "bcABCabc") == 0)) {
    failed ("Case 15: strcmp (strchr (\"ABCabcABCabc\", 'b'), \"bcABCabc\") == 0");
  }
  
  /* Case 16 */
  if (!(strcmp (strchr ("ABCabcABCabc", '\0'), "") == 0)) {
    failed ("Case 16: strcmp (strchr (\"ABCabcABCabc\", '\\0'), \"\") == 0");
  }
  
}


void main ()
{
  test ("test-strchr", "Test for ANSI Standard C: 7.11.5.2");

  do_test ();

  result ();
}

