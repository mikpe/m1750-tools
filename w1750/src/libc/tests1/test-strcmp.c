/*
 * Test for ANSI Standard C: 7.11.4.2
 * 
 * #include <string.h>
 * void *strcmp (const char *s1, const char *s2);
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


static char *_test_strcmp_id =
  "$Id$";

void do_test ()
{
  /* Case 1 */
  if (!(strcmp ("","") == 0)) {
    failed ("Case 1: strcmp (\"\",\"\") == 0");
  }
  
  /* Case 2 */
  if (!(strcmp ("1","1") == 0)) {
    failed ("Case 2: strcmp (\"1\",\"1\") == 0");
  }
  
  /* Case 3 */
  if (!(strcmp ("a","a") == 0)) {
    failed ("Case 3: strcmp (\"a\",\"a\") == 0");
  }
  
  /* Case 4 */
  if (!(strcmp ("A","A") == 0)) {
    failed ("Case 4: strcmp (\"A\",\"A\") == 0");
  }
  
  /* Case 5 */
  if (!(strcmp ("abcdefg","abcdefg") == 0)) {
    failed ("Case 5: strcmp (\"abcdefg\",\"abcdefg\") == 0");
  }
  
  /* Case 6 */
  if (!(strcmp ("........","........") == 0)) {
    failed ("Case 6: strcmp (\"........\",\"........\") == 0");
  }
  
  /* Case 7 */
  if (!(strcmp ("\1\1\1\1","\1\1\1\1") == 0)) {
    failed ("Case 7: strcmp (\"\\1\\1\\1\\1\",\"\\1\\1\\1\\1\") == 0");
  }
  
  /* Case 8 */
  if (!(strcmp ("ZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZ","ZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZ") == 0)) {
    failed ("Case 8: strcmp (\"ZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZ\",\"ZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZ\") == 0");
  }
  
  /* Case 9 */
  if (!(strcmp ("zzz","zzz") == 0)) {
    failed ("Case 9: strcmp (\"zzz\",\"zzz\") == 0");
  }
  
  /* Case 10 */
  if (!(strcmp ("    ","    ") == 0)) {
    failed ("Case 10: strcmp (\"    \",\"    \") == 0");
  }
  
  /* Case 11 */
  if (!(strcmp ("0","1") < 0)) {
    failed ("Case 11: strcmp (\"0\",\"1\") < 0");
  }
  
  /* Case 12 */
  if (!(strcmp ("a","b") < 0)) {
    failed ("Case 12: strcmp (\"a\",\"b\") < 0");
  }
  
  /* Case 13 */
  if (!(strcmp ("A","a") < 0)) {
    failed ("Case 13: strcmp (\"A\",\"a\") < 0");
  }
  
  /* Case 14 */
  if (!(strcmp ("a","aa") < 0)) {
    failed ("Case 14: strcmp (\"a\",\"aa\") < 0");
  }
  
  /* Case 15 */
  if (!(strcmp ("b","ba") < 0)) {
    failed ("Case 15: strcmp (\"b\",\"ba\") < 0");
  }
  
  /* Case 16 */
  if (!(strcmp ("abcd1","abcd2") < 0)) {
    failed ("Case 16: strcmp (\"abcd1\",\"abcd2\") < 0");
  }
  
  /* Case 17 */
  if (!(strcmp ("abcd1","abcd1     ") < 0)) {
    failed ("Case 17: strcmp (\"abcd1\",\"abcd1     \") < 0");
  }
  
  /* Case 18 */
  if (!(strcmp ("[","]]") < 0)) {
    failed ("Case 18: strcmp (\"[\",\"]]\") < 0");
  }
  
  /* Case 19 */
  if (!(strcmp ("////////0////////","////////1////////") < 0)) {
    failed ("Case 19: strcmp (\"////////0////////\",\"////////1////////\") < 0");
  }
  
  /* Case 20 */
  if (!(strcmp ("HELLO","hello") < 0)) {
    failed ("Case 20: strcmp (\"HELLO\",\"hello\") < 0");
  }
  
  /* Case 21 */
  if (!(strcmp ("1","0") > 0)) {
    failed ("Case 21: strcmp (\"1\",\"0\") > 0");
  }
  
  /* Case 22 */
  if (!(strcmp ("11","1") > 0)) {
    failed ("Case 22: strcmp (\"11\",\"1\") > 0");
  }
  
  /* Case 23 */
  if (!(strcmp (" ","") > 0)) {
    failed ("Case 23: strcmp (\" \",\"\") > 0");
  }
  
  /* Case 24 */
  if (!(strcmp ("  ","") > 0)) {
    failed ("Case 24: strcmp (\"  \",\"\") > 0");
  }
  
  /* Case 25 */
  if (!(strcmp ("1","") > 0)) {
    failed ("Case 25: strcmp (\"1\",\"\") > 0");
  }
  
  /* Case 26 */
  if (!(strcmp ("z","Z") > 0)) {
    failed ("Case 26: strcmp (\"z\",\"Z\") > 0");
  }
  
  /* Case 27 */
  if (!(strcmp ("1234","123") > 0)) {
    failed ("Case 27: strcmp (\"1234\",\"123\") > 0");
  }
  
  /* Case 28 */
  if (!(strcmp ("1234 ","123") > 0)) {
    failed ("Case 28: strcmp (\"1234 \",\"123\") > 0");
  }
  
  /* Case 29 */
  if (!(strcmp ("\2","\1") > 0)) {
    failed ("Case 29: strcmp (\"\\2\",\"\\1\") > 0");
  }
  
  /* Case 30 */
  if (!(strcmp ("\177","\0") > 0)) {
    failed ("Case 30: strcmp (\"\\177\",\"\\0\") > 0");
  }
  
}


void main ()
{
  test ("test-strcmp", "Test for ANSI Standard C: 7.11.4.2");

  do_test ();

  result ();
}

