/*
 * Test for ANSI Standard C: 7.11.5.7
 * 
 * #include <string.h>
 * char *strstr (const char *s1, const char *s2);
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


static char *_test_strstr_id =
  "$Id$";

void do_test ()
{
  /* Case 1 */
  if (!(strstr ("ABCabcABCxyz", " ") == NULL)) {
    failed ("Case 1: strstr (\"ABCabcABCxyz\", \" \") == NULL");
  }
  
  /* Case 2 */
  if (!(strstr ("1", " ") == NULL)) {
    failed ("Case 2: strstr (\"1\", \" \") == NULL");
  }
  
  /* Case 3 */
  if (!(strstr ("12", " ") == NULL)) {
    failed ("Case 3: strstr (\"12\", \" \") == NULL");
  }
  
  /* Case 4 */
  if (!(strstr ("123", "34") == NULL)) {
    failed ("Case 4: strstr (\"123\", \"34\") == NULL");
  }
  
  /* Case 5 */
  if (!(strstr ("1234", "13") == NULL)) {
    failed ("Case 5: strstr (\"1234\", \"13\") == NULL");
  }
  
  /* Case 6 */
  if (!(strcmp (strstr (" ", " "), " ") == 0)) {
    failed ("Case 6: strcmp (strstr (\" \", \" \"), \" \") == 0");
  }
  
  /* Case 7 */
  if (!(strcmp (strstr ("1 ", " "), " ") == 0)) {
    failed ("Case 7: strcmp (strstr (\"1 \", \" \"), \" \") == 0");
  }
  
  /* Case 8 */
  if (!(strcmp (strstr ("12 ", " "), " ") == 0)) {
    failed ("Case 8: strcmp (strstr (\"12 \", \" \"), \" \") == 0");
  }
  
  /* Case 9 */
  if (!(strcmp (strstr ("123 ", " "), " ") == 0)) {
    failed ("Case 9: strcmp (strstr (\"123 \", \" \"), \" \") == 0");
  }
  
  /* Case 10 */
  if (!(strcmp (strstr ("1234 ", " "), " ") == 0)) {
    failed ("Case 10: strcmp (strstr (\"1234 \", \" \"), \" \") == 0");
  }
  
  /* Case 11 */
  if (!(strcmp (strstr ("ABCabcABCxyz", "A"), "ABCabcABCxyz") == 0)) {
    failed ("Case 11: strcmp (strstr (\"ABCabcABCxyz\", \"A\"), \"ABCabcABCxyz\") == 0");
  }
  
  /* Case 12 */
  if (!(strcmp (strstr ("ABCabcABCxyz", "B"), "BCabcABCxyz") == 0)) {
    failed ("Case 12: strcmp (strstr (\"ABCabcABCxyz\", \"B\"), \"BCabcABCxyz\") == 0");
  }
  
  /* Case 13 */
  if (!(strcmp (strstr ("ABCabcABCxyz", "C"), "CabcABCxyz") == 0)) {
    failed ("Case 13: strcmp (strstr (\"ABCabcABCxyz\", \"C\"), \"CabcABCxyz\") == 0");
  }
  
  /* Case 14 */
  if (!(strcmp (strstr ("ABCabcABCxyz", "a"), "abcABCxyz") == 0)) {
    failed ("Case 14: strcmp (strstr (\"ABCabcABCxyz\", \"a\"), \"abcABCxyz\") == 0");
  }
  
  /* Case 15 */
  if (!(strcmp (strstr ("ABCabcABCxyz", "b"), "bcABCxyz") == 0)) {
    failed ("Case 15: strcmp (strstr (\"ABCabcABCxyz\", \"b\"), \"bcABCxyz\") == 0");
  }
  
  /* Case 16 */
  if (!(strcmp (strstr ("ABCabcABCxyz", "ABC"), "ABCabcABCxyz") == 0)) {
    failed ("Case 16: strcmp (strstr (\"ABCabcABCxyz\", \"ABC\"), \"ABCabcABCxyz\") == 0");
  }
  
  /* Case 17 */
  if (!(strcmp (strstr ("ABCabcABCxyz", "BCa"), "BCabcABCxyz") == 0)) {
    failed ("Case 17: strcmp (strstr (\"ABCabcABCxyz\", \"BCa\"), \"BCabcABCxyz\") == 0");
  }
  
  /* Case 18 */
  if (!(strcmp (strstr ("ABCabcABCxyz", "Cab"), "CabcABCxyz") == 0)) {
    failed ("Case 18: strcmp (strstr (\"ABCabcABCxyz\", \"Cab\"), \"CabcABCxyz\") == 0");
  }
  
  /* Case 19 */
  if (!(strcmp (strstr ("ABCabcABCxyz", "ABCx"), "ABCxyz") == 0)) {
    failed ("Case 19: strcmp (strstr (\"ABCabcABCxyz\", \"ABCx\"), \"ABCxyz\") == 0");
  }
  
  /* Case 20 */
  if (!(strcmp (strstr ("ABCabcABCxyz", "xyz"), "xyz") == 0)) {
    failed ("Case 20: strcmp (strstr (\"ABCabcABCxyz\", \"xyz\"), \"xyz\") == 0");
  }
  
  /* Case 21 */
  if (!(strcmp (strstr ("ABCabcABCxyz", "\0"), "ABCabcABCxyz") == 0)) {
    failed ("Case 21: strcmp (strstr (\"ABCabcABCxyz\", \"\\0\"), \"ABCabcABCxyz\") == 0");
  }
  
  /* Case 22 */
  if (!(strcmp (strstr ("", ""), "") == 0)) {
    failed ("Case 22: strcmp (strstr (\"\", \"\"), \"\") == 0");
  }
  
  /* Case 23 */
  if (!(strcmp (strstr ("a", ""), "a") == 0)) {
    failed ("Case 23: strcmp (strstr (\"a\", \"\"), \"a\") == 0");
  }
  
  /* Case 24 */
  if (!(strcmp (strstr ("The strstr function", ""), "The strstr function") == 0)) {
    failed ("Case 24: strcmp (strstr (\"The strstr function\", \"\"), \"The strstr function\") == 0");
  }
  
}


void main ()
{
  test ("test-strstr", "Test for ANSI Standard C: 7.11.5.7");

  do_test ();

  result ();
}

