/*
 * Test for ANSI Standard C: 7.10.1.5
 * 
 * #include <stdlib.h>
 * long strtol (const char *nptr, char **endptr, int base);
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

#include <stdlib.h>


static char *_test_strtol_id =
  "$Id$";

void do_test ()
{
  /* Case 1 */
  if (!({char *p; strtol ("0", &p, 0) == 0L;})) {
    failed ("Case 1: {char *p; strtol (\"0\", &p, 0) == 0L;}");
  }
  
  /* Case 2 */
  if (!({char *p; strtol (" 0", &p, 0) == 0L;})) {
    failed ("Case 2: {char *p; strtol (\" 0\", &p, 0) == 0L;}");
  }
  
  /* Case 3 */
  if (!({char *p; strtol ("  0 ", &p, 0) == 0L;})) {
    failed ("Case 3: {char *p; strtol (\"  0 \", &p, 0) == 0L;}");
  }
  
  /* Case 4 */
  if (!({char *p; strtol ("  0zzzz", &p, 0) == 0L;})) {
    failed ("Case 4: {char *p; strtol (\"  0zzzz\", &p, 0) == 0L;}");
  }
  
  /* Case 5 */
  if (!({char *p; strtol ("zzzz0", &p, 0) == 0L;})) {
    failed ("Case 5: {char *p; strtol (\"zzzz0\", &p, 0) == 0L;}");
  }
  
  /* Case 6 */
  if (!({char *p; strtol ("  +0", &p, 0) == 0L;})) {
    failed ("Case 6: {char *p; strtol (\"  +0\", &p, 0) == 0L;}");
  }
  
  /* Case 7 */
  if (!({char *p; strtol ("  -0", &p, 0) == 0L;})) {
    failed ("Case 7: {char *p; strtol (\"  -0\", &p, 0) == 0L;}");
  }
  
  /* Case 8 */
  if (!({char *p; strtol ("0x1234", &p, 0) == 0x1234L;})) {
    failed ("Case 8: {char *p; strtol (\"0x1234\", &p, 0) == 0x1234L;}");
  }
  
  /* Case 9 */
  if (!({char *p; strtol ("0x7fffffff", &p, 0) == 0x7fffffffL;})) {
    failed ("Case 9: {char *p; strtol (\"0x7fffffff\", &p, 0) == 0x7fffffffL;}");
  }
  
  /* Case 10 */
  if (!({char *p; strtol ("0x80000000", &p, 0) == 0x7fffffffL;})) {
    failed ("Case 10: {char *p; strtol (\"0x80000000\", &p, 0) == 0x7fffffffL;}");
  }
  
  /* Case 11 */
  if (!({char *p; strtol ("+0x80001234", &p, 0) == 0x7fffffffL;})) {
    failed ("Case 11: {char *p; strtol (\"+0x80001234\", &p, 0) == 0x7fffffffL;}");
  }
  
  /* Case 12 */
  if (!({char *p; strtol ("-0x80001234", &p, 0) == 0x80000000L;})) {
    failed ("Case 12: {char *p; strtol (\"-0x80001234\", &p, 0) == 0x80000000L;}");
  }
  
  /* Case 13 */
  if (!({char *p; strtol ("01234", &p, 0) == 01234L;})) {
    failed ("Case 13: {char *p; strtol (\"01234\", &p, 0) == 01234L;}");
  }
  
  /* Case 14 */
  if (!({char *p; strtol ("01235", &p, 0) == 01235L;})) {
    failed ("Case 14: {char *p; strtol (\"01235\", &p, 0) == 01235L;}");
  }
  
  /* Case 15 */
  if (!({char *p; strtol ("01236", &p, 0) == 01236L;})) {
    failed ("Case 15: {char *p; strtol (\"01236\", &p, 0) == 01236L;}");
  }
  
  /* Case 16 */
  if (!({char *p; strtol ("01237", &p, 0) == 01237L;})) {
    failed ("Case 16: {char *p; strtol (\"01237\", &p, 0) == 01237L;}");
  }
  
  /* Case 17 */
  if (!({char *p; strtol ("0", &p, 2) == 0L;})) {
    failed ("Case 17: {char *p; strtol (\"0\", &p, 2) == 0L;}");
  }
  
  /* Case 18 */
  if (!({char *p; strtol ("00000000", &p, 2) == 0L;})) {
    failed ("Case 18: {char *p; strtol (\"00000000\", &p, 2) == 0L;}");
  }
  
  /* Case 19 */
  if (!({char *p; strtol ("11111111", &p, 2) == 255L;})) {
    failed ("Case 19: {char *p; strtol (\"11111111\", &p, 2) == 255L;}");
  }
  
  /* Case 20 */
  if (!({char *p; strtol ("1111111111111111", &p, 2) == 65535L;})) {
    failed ("Case 20: {char *p; strtol (\"1111111111111111\", &p, 2) == 65535L;}");
  }
  
  /* Case 21 */
  if (!({char *p; strtol ("1111222211111111", &p, 2) == 15L;})) {
    failed ("Case 21: {char *p; strtol (\"1111222211111111\", &p, 2) == 15L;}");
  }
  
  /* Case 22 */
  if (!({char *p; strtol (" 1", &p, 10) == 1L;})) {
    failed ("Case 22: {char *p; strtol (\" 1\", &p, 10) == 1L;}");
  }
  
  /* Case 23 */
  if (!({char *p; strtol ("  2", &p, 10) == 2L;})) {
    failed ("Case 23: {char *p; strtol (\"  2\", &p, 10) == 2L;}");
  }
  
  /* Case 24 */
  if (!({char *p; strtol ("   3", &p, 10) == 3L;})) {
    failed ("Case 24: {char *p; strtol (\"   3\", &p, 10) == 3L;}");
  }
  
  /* Case 25 */
  if (!({char *p; strtol ("    4", &p, 10) == 4L;})) {
    failed ("Case 25: {char *p; strtol (\"    4\", &p, 10) == 4L;}");
  }
  
  /* Case 26 */
  if (!({char *p; strtol ("     5", &p, 10) == 5L;})) {
    failed ("Case 26: {char *p; strtol (\"     5\", &p, 10) == 5L;}");
  }
  
  /* Case 27 */
  if (!({char *p; strtol ("      6", &p, 10) == 6L;})) {
    failed ("Case 27: {char *p; strtol (\"      6\", &p, 10) == 6L;}");
  }
  
  /* Case 28 */
  if (!({char *p; strtol ("       7", &p, 10) == 7L;})) {
    failed ("Case 28: {char *p; strtol (\"       7\", &p, 10) == 7L;}");
  }
  
  /* Case 29 */
  if (!({char *p; strtol ("        8", &p, 10) == 8L;})) {
    failed ("Case 29: {char *p; strtol (\"        8\", &p, 10) == 8L;}");
  }
  
  /* Case 30 */
  if (!({char *p; strtol ("         9", &p, 10) == 9L;})) {
    failed ("Case 30: {char *p; strtol (\"         9\", &p, 10) == 9L;}");
  }
  
  /* Case 31 */
  if (!({char *p; strtol ("123456789", &p, 10) == 123456789L;})) {
    failed ("Case 31: {char *p; strtol (\"123456789\", &p, 10) == 123456789L;}");
  }
  
  /* Case 32 */
  if (!({char *p; strtol ("2147483647", &p, 10) == 2147483647L;})) {
    failed ("Case 32: {char *p; strtol (\"2147483647\", &p, 10) == 2147483647L;}");
  }
  
  /* Case 33 */
  if (!({char *p; strtol ("2147483649", &p, 10) == 2147483647L;})) {
    failed ("Case 33: {char *p; strtol (\"2147483649\", &p, 10) == 2147483647L;}");
  }
  
  /* Case 34 */
  if (!({char *p; strtol ("3147483647", &p, 10) == 2147483647L;})) {
    failed ("Case 34: {char *p; strtol (\"3147483647\", &p, 10) == 2147483647L;}");
  }
  
  /* Case 35 */
  if (!({char *p; strtol ("-2147483646", &p, 10) == -2147483646L;})) {
    failed ("Case 35: {char *p; strtol (\"-2147483646\", &p, 10) == -2147483646L;}");
  }
  
  /* Case 36 */
  if (!({char *p; strtol ("-2147483647", &p, 10) == -2147483647L;})) {
    failed ("Case 36: {char *p; strtol (\"-2147483647\", &p, 10) == -2147483647L;}");
  }
  
  /* Case 37 */
  if (!({char *p; strtol ("-2147483648", &p, 10) == 0x80000000;})) {
    failed ("Case 37: {char *p; strtol (\"-2147483648\", &p, 10) == 0x80000000;}");
  }
  
  /* Case 38 */
  if (!({char *p; strtol ("-2147483649", &p, 10) == 0x80000000;})) {
    failed ("Case 38: {char *p; strtol (\"-2147483649\", &p, 10) == 0x80000000;}");
  }
  
  /* Case 39 */
  if (!({char *p; strtol ("-3147483648", &p, 10) == 0x80000000;})) {
    failed ("Case 39: {char *p; strtol (\"-3147483648\", &p, 10) == 0x80000000;}");
  }
  
  /* Case 40 */
  if (!({char *p; strtol ("123456aA", &p, 16) == 0x123456aaL;})) {
    failed ("Case 40: {char *p; strtol (\"123456aA\", &p, 16) == 0x123456aaL;}");
  }
  
  /* Case 41 */
  if (!({char *p; strtol ("0x223456bB", &p, 16) == 0x223456bbL;})) {
    failed ("Case 41: {char *p; strtol (\"0x223456bB\", &p, 16) == 0x223456bbL;}");
  }
  
  /* Case 42 */
  if (!({char *p; strtol ("0x323456cC", &p, 16) == 0x323456ccL;})) {
    failed ("Case 42: {char *p; strtol (\"0x323456cC\", &p, 16) == 0x323456ccL;}");
  }
  
  /* Case 43 */
  if (!({char *p; strtol ("  0x423456dD", &p, 16) == 0x423456ddL;})) {
    failed ("Case 43: {char *p; strtol (\"  0x423456dD\", &p, 16) == 0x423456ddL;}");
  }
  
  /* Case 44 */
  if (!({char *p; strtol ("  +0x523456eE", &p, 16) == 0x523456eeL;})) {
    failed ("Case 44: {char *p; strtol (\"  +0x523456eE\", &p, 16) == 0x523456eeL;}");
  }
  
  /* Case 45 */
  if (!({char *p; strtol ("  -0x623456fF", &p, 16) == -0x623456ffL;})) {
    failed ("Case 45: {char *p; strtol (\"  -0x623456fF\", &p, 16) == -0x623456ffL;}");
  }
  
  /* Case 46 */
  if (!({char *p; strtol ("72345677", &p, 16) == 0x72345677L;})) {
    failed ("Case 46: {char *p; strtol (\"72345677\", &p, 16) == 0x72345677L;}");
  }
  
  /* Case 47 */
  if (!({char *p; strtol ("-123456aA", &p, 16) == -0x123456aaL;})) {
    failed ("Case 47: {char *p; strtol (\"-123456aA\", &p, 16) == -0x123456aaL;}");
  }
  
  /* Case 48 */
  if (!({char *p; strtol ("-223456bB", &p, 16) == -0x223456bbL;})) {
    failed ("Case 48: {char *p; strtol (\"-223456bB\", &p, 16) == -0x223456bbL;}");
  }
  
  /* Case 49 */
  if (!({char *p; strtol ("-323456cC", &p, 16) == -0x323456ccL;})) {
    failed ("Case 49: {char *p; strtol (\"-323456cC\", &p, 16) == -0x323456ccL;}");
  }
  
  /* Case 50 */
  if (!({char *p; strtol ("-423456dD", &p, 16) == -0x423456ddL;})) {
    failed ("Case 50: {char *p; strtol (\"-423456dD\", &p, 16) == -0x423456ddL;}");
  }
  
  /* Case 51 */
  if (!({char *p; strtol ("-523456eE", &p, 16) == -0x523456eeL;})) {
    failed ("Case 51: {char *p; strtol (\"-523456eE\", &p, 16) == -0x523456eeL;}");
  }
  
  /* Case 52 */
  if (!({char *p; strtol ("-623456fF", &p, 16) == -0x623456ffL;})) {
    failed ("Case 52: {char *p; strtol (\"-623456fF\", &p, 16) == -0x623456ffL;}");
  }
  
  /* Case 53 */
  if (!({char *p; strtol ("-72345677", &p, 16) == -0x72345677L;})) {
    failed ("Case 53: {char *p; strtol (\"-72345677\", &p, 16) == -0x72345677L;}");
  }
  
  /* Case 54 */
  if (!({char *p; strtol ("00000000", &p, 16) == 0x00000000L;})) {
    failed ("Case 54: {char *p; strtol (\"00000000\", &p, 16) == 0x00000000L;}");
  }
  
  /* Case 55 */
  if (!({char *p; strtol ("7FFFFFFF", &p, 16) == 0x7FFFFFFFL;})) {
    failed ("Case 55: {char *p; strtol (\"7FFFFFFF\", &p, 16) == 0x7FFFFFFFL;}");
  }
  
}


void main ()
{
  test ("test-strtol", "Test for ANSI Standard C: 7.10.1.5");

  do_test ();

  result ();
}

