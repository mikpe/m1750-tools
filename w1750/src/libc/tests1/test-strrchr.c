/*
 * Test for ANSI Standard C: 7.11.5.5
 * 
 * #include <string.h>
 * char *strrchr (const char *s, int c);
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


static char *_test_strrchr_id =
  "$Id$";

void do_test ()
{
  /* Case 1 */
  if (!(strrchr ("ABCabcABCabc", ' ') == NULL)) {
    failed ("Case 1: strrchr (\"ABCabcABCabc\", ' ') == NULL");
  }
  
  /* Case 2 */
  if (!(strrchr ("1", ' ') == NULL)) {
    failed ("Case 2: strrchr (\"1\", ' ') == NULL");
  }
  
  /* Case 3 */
  if (!(strrchr ("12", ' ') == NULL)) {
    failed ("Case 3: strrchr (\"12\", ' ') == NULL");
  }
  
  /* Case 4 */
  if (!(strrchr ("123", ' ') == NULL)) {
    failed ("Case 4: strrchr (\"123\", ' ') == NULL");
  }
  
  /* Case 5 */
  if (!(strrchr ("1234", ' ') == NULL)) {
    failed ("Case 5: strrchr (\"1234\", ' ') == NULL");
  }
  
  /* Case 6 */
  if (!(strcmp (strrchr (" ", ' '), " ") == 0)) {
    failed ("Case 6: strcmp (strrchr (\" \", ' '), \" \") == 0");
  }
  
  /* Case 7 */
  if (!(strcmp (strrchr ("1 ", ' '), " ") == 0)) {
    failed ("Case 7: strcmp (strrchr (\"1 \", ' '), \" \") == 0");
  }
  
  /* Case 8 */
  if (!(strcmp (strrchr ("12 ", ' '), " ") == 0)) {
    failed ("Case 8: strcmp (strrchr (\"12 \", ' '), \" \") == 0");
  }
  
  /* Case 9 */
  if (!(strcmp (strrchr ("123 ", ' '), " ") == 0)) {
    failed ("Case 9: strcmp (strrchr (\"123 \", ' '), \" \") == 0");
  }
  
  /* Case 10 */
  if (!(strcmp (strrchr ("1234 ", ' '), " ") == 0)) {
    failed ("Case 10: strcmp (strrchr (\"1234 \", ' '), \" \") == 0");
  }
  
  /* Case 11 */
  if (!(strcmp (strrchr ("ABCabcABCabc", 'A'), "ABCabc") == 0)) {
    failed ("Case 11: strcmp (strrchr (\"ABCabcABCabc\", 'A'), \"ABCabc\") == 0");
  }
  
  /* Case 12 */
  if (!(strcmp (strrchr ("ABCabcABCabc", 'B'), "BCabc") == 0)) {
    failed ("Case 12: strcmp (strrchr (\"ABCabcABCabc\", 'B'), \"BCabc\") == 0");
  }
  
  /* Case 13 */
  if (!(strcmp (strrchr ("ABCabcABCabc", 'C'), "Cabc") == 0)) {
    failed ("Case 13: strcmp (strrchr (\"ABCabcABCabc\", 'C'), \"Cabc\") == 0");
  }
  
  /* Case 14 */
  if (!(strcmp (strrchr ("ABCabcABCabc", 'a'), "abc") == 0)) {
    failed ("Case 14: strcmp (strrchr (\"ABCabcABCabc\", 'a'), \"abc\") == 0");
  }
  
  /* Case 15 */
  if (!(strcmp (strrchr ("ABCabcABCabc", 'b'), "bc") == 0)) {
    failed ("Case 15: strcmp (strrchr (\"ABCabcABCabc\", 'b'), \"bc\") == 0");
  }
  
  /* Case 16 */
  if (!(strcmp (strrchr ("ABCabcABCabc", '\0'), "") == 0)) {
    failed ("Case 16: strcmp (strrchr (\"ABCabcABCabc\", '\\0'), \"\") == 0");
  }
  
}


void main ()
{
  test ("test-strrchr", "Test for ANSI Standard C: 7.11.5.5");

  do_test ();

  result ();
}

