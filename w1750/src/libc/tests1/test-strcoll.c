/*
 * Test for ANSI Standard C: 7.11.4.3
 * 
 * #include <string.h>
 * void *strcoll (const char *s1, const char *s2);
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


static char *_test_strcoll_id =
  "$Id$";

void do_test ()
{
  /* Case 1 */
  if (!(strcoll ("","") == 0)) {
    failed ("Case 1: strcoll (\"\",\"\") == 0");
  }
  
  /* Case 2 */
  if (!(strcoll ("1","1") == 0)) {
    failed ("Case 2: strcoll (\"1\",\"1\") == 0");
  }
  
  /* Case 3 */
  if (!(strcoll ("a","a") == 0)) {
    failed ("Case 3: strcoll (\"a\",\"a\") == 0");
  }
  
  /* Case 4 */
  if (!(strcoll ("A","A") == 0)) {
    failed ("Case 4: strcoll (\"A\",\"A\") == 0");
  }
  
  /* Case 5 */
  if (!(strcoll ("abcdefg","abcdefg") == 0)) {
    failed ("Case 5: strcoll (\"abcdefg\",\"abcdefg\") == 0");
  }
  
  /* Case 6 */
  if (!(strcoll ("........","........") == 0)) {
    failed ("Case 6: strcoll (\"........\",\"........\") == 0");
  }
  
  /* Case 7 */
  if (!(strcoll ("\1\1\1\1","\1\1\1\1") == 0)) {
    failed ("Case 7: strcoll (\"\\1\\1\\1\\1\",\"\\1\\1\\1\\1\") == 0");
  }
  
  /* Case 8 */
  if (!(strcoll ("ZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZ","ZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZ") == 0)) {
    failed ("Case 8: strcoll (\"ZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZ\",\"ZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZ\") == 0");
  }
  
  /* Case 9 */
  if (!(strcoll ("zzz","zzz") == 0)) {
    failed ("Case 9: strcoll (\"zzz\",\"zzz\") == 0");
  }
  
  /* Case 10 */
  if (!(strcoll ("    ","    ") == 0)) {
    failed ("Case 10: strcoll (\"    \",\"    \") == 0");
  }
  
  /* Case 11 */
  if (!(strcoll ("0","1") < 0)) {
    failed ("Case 11: strcoll (\"0\",\"1\") < 0");
  }
  
  /* Case 12 */
  if (!(strcoll ("a","b") < 0)) {
    failed ("Case 12: strcoll (\"a\",\"b\") < 0");
  }
  
  /* Case 13 */
  if (!(strcoll ("A","a") < 0)) {
    failed ("Case 13: strcoll (\"A\",\"a\") < 0");
  }
  
  /* Case 14 */
  if (!(strcoll ("a","aa") < 0)) {
    failed ("Case 14: strcoll (\"a\",\"aa\") < 0");
  }
  
  /* Case 15 */
  if (!(strcoll ("b","ba") < 0)) {
    failed ("Case 15: strcoll (\"b\",\"ba\") < 0");
  }
  
  /* Case 16 */
  if (!(strcoll ("abcd1","abcd2") < 0)) {
    failed ("Case 16: strcoll (\"abcd1\",\"abcd2\") < 0");
  }
  
  /* Case 17 */
  if (!(strcoll ("abcd1","abcd1     ") < 0)) {
    failed ("Case 17: strcoll (\"abcd1\",\"abcd1     \") < 0");
  }
  
  /* Case 18 */
  if (!(strcoll ("[","]]") < 0)) {
    failed ("Case 18: strcoll (\"[\",\"]]\") < 0");
  }
  
  /* Case 19 */
  if (!(strcoll ("////////0////////","////////1////////") < 0)) {
    failed ("Case 19: strcoll (\"////////0////////\",\"////////1////////\") < 0");
  }
  
  /* Case 20 */
  if (!(strcoll ("HELLO","hello") < 0)) {
    failed ("Case 20: strcoll (\"HELLO\",\"hello\") < 0");
  }
  
  /* Case 21 */
  if (!(strcoll ("1","0") > 0)) {
    failed ("Case 21: strcoll (\"1\",\"0\") > 0");
  }
  
  /* Case 22 */
  if (!(strcoll ("11","1") > 0)) {
    failed ("Case 22: strcoll (\"11\",\"1\") > 0");
  }
  
  /* Case 23 */
  if (!(strcoll (" ","") > 0)) {
    failed ("Case 23: strcoll (\" \",\"\") > 0");
  }
  
  /* Case 24 */
  if (!(strcoll ("  ","") > 0)) {
    failed ("Case 24: strcoll (\"  \",\"\") > 0");
  }
  
  /* Case 25 */
  if (!(strcoll ("1","") > 0)) {
    failed ("Case 25: strcoll (\"1\",\"\") > 0");
  }
  
  /* Case 26 */
  if (!(strcoll ("z","Z") > 0)) {
    failed ("Case 26: strcoll (\"z\",\"Z\") > 0");
  }
  
  /* Case 27 */
  if (!(strcoll ("1234","123") > 0)) {
    failed ("Case 27: strcoll (\"1234\",\"123\") > 0");
  }
  
  /* Case 28 */
  if (!(strcoll ("1234 ","123") > 0)) {
    failed ("Case 28: strcoll (\"1234 \",\"123\") > 0");
  }
  
  /* Case 29 */
  if (!(strcoll ("\2","\1") > 0)) {
    failed ("Case 29: strcoll (\"\\2\",\"\\1\") > 0");
  }
  
  /* Case 30 */
  if (!(strcoll ("\177","\0") > 0)) {
    failed ("Case 30: strcoll (\"\\177\",\"\\0\") > 0");
  }
  
}


void main ()
{
  test ("test-strcoll", "Test for ANSI Standard C: 7.11.4.3");

  do_test ();

  result ();
}

