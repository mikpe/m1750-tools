/*
 * Test for ANSI Standard C: 7.11.5.6
 * 
 * #include <string.h>
 * size_t strspn (const char *s1, const char *s2);
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


static char *_test_strspn_id =
  "$Id$";

void do_test ()
{
  /* Case 1 */
  if (!(strspn ("", "") == 0)) {
    failed ("Case 1: strspn (\"\", \"\") == 0");
  }
  
  /* Case 2 */
  if (!(strspn ("a", "") == 0)) {
    failed ("Case 2: strspn (\"a\", \"\") == 0");
  }
  
  /* Case 3 */
  if (!(strspn ("aaaa", "") == 0)) {
    failed ("Case 3: strspn (\"aaaa\", \"\") == 0");
  }
  
  /* Case 4 */
  if (!(strspn ("aaaa", "bcd") == 0)) {
    failed ("Case 4: strspn (\"aaaa\", \"bcd\") == 0");
  }
  
  /* Case 5 */
  if (!(strspn ("", "bcd") == 0)) {
    failed ("Case 5: strspn (\"\", \"bcd\") == 0");
  }
  
  /* Case 6 */
  if (!(strspn ("a", "a") == 1)) {
    failed ("Case 6: strspn (\"a\", \"a\") == 1");
  }
  
  /* Case 7 */
  if (!(strspn ("abcd", "a") == 1)) {
    failed ("Case 7: strspn (\"abcd\", \"a\") == 1");
  }
  
  /* Case 8 */
  if (!(strspn ("bcda", "a") == 0)) {
    failed ("Case 8: strspn (\"bcda\", \"a\") == 0");
  }
  
  /* Case 9 */
  if (!(strspn ("bcad", "a") == 0)) {
    failed ("Case 9: strspn (\"bcad\", \"a\") == 0");
  }
  
  /* Case 10 */
  if (!(strspn ("aaaaa", "a") == 5)) {
    failed ("Case 10: strspn (\"aaaaa\", \"a\") == 5");
  }
  
  /* Case 11 */
  if (!(strspn ("abcdefghijklmnopqrstuvwxyz", "ABC") == 0)) {
    failed ("Case 11: strspn (\"abcdefghijklmnopqrstuvwxyz\", \"ABC\") == 0");
  }
  
  /* Case 12 */
  if (!(strspn ("abcdefghijklmnopqrstuvwxyz", "a") == 1)) {
    failed ("Case 12: strspn (\"abcdefghijklmnopqrstuvwxyz\", \"a\") == 1");
  }
  
  /* Case 13 */
  if (!(strspn ("abcdefghijklmnopqrstuvwxyz", "abcd") == 4)) {
    failed ("Case 13: strspn (\"abcdefghijklmnopqrstuvwxyz\", \"abcd\") == 4");
  }
  
  /* Case 14 */
  if (!(strspn ("abcdefghijklmnopqrstuvwxyz", "xyz") == 0)) {
    failed ("Case 14: strspn (\"abcdefghijklmnopqrstuvwxyz\", \"xyz\") == 0");
  }
  
  /* Case 15 */
  if (!(strspn ("abcdefghijklmnopqrstuvwxyz", "pqr") == 0)) {
    failed ("Case 15: strspn (\"abcdefghijklmnopqrstuvwxyz\", \"pqr\") == 0");
  }
  
  /* Case 16 */
  if (!(strspn ("aababcabcdabcdeabcdefabcdefgabcdefgh", "") == 0)) {
    failed ("Case 16: strspn (\"aababcabcdabcdeabcdefabcdefgabcdefgh\", \"\") == 0");
  }
  
  /* Case 17 */
  if (!(strspn ("aababcabcdabcdeabcdefabcdefgabcdefgh", "a") == 2)) {
    failed ("Case 17: strspn (\"aababcabcdabcdeabcdefabcdefgabcdefgh\", \"a\") == 2");
  }
  
  /* Case 18 */
  if (!(strspn ("aababcabcdabcdeabcdefabcdefgabcdefgh", "ab") == 5)) {
    failed ("Case 18: strspn (\"aababcabcdabcdeabcdefabcdefgabcdefgh\", \"ab\") == 5");
  }
  
  /* Case 19 */
  if (!(strspn ("aababcabcdabcdeabcdefabcdefgabcdefgh", "abc") == 9)) {
    failed ("Case 19: strspn (\"aababcabcdabcdeabcdefabcdefgabcdefgh\", \"abc\") == 9");
  }
  
  /* Case 20 */
  if (!(strspn ("aababcabcdabcdeabcdefabcdefgabcdefgh", "abcd") == 14)) {
    failed ("Case 20: strspn (\"aababcabcdabcdeabcdefabcdefgabcdefgh\", \"abcd\") == 14");
  }
  
}


void main ()
{
  test ("test-strspn", "Test for ANSI Standard C: 7.11.5.6");

  do_test ();

  result ();
}

