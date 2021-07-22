/*
 * Test for ANSI Standard C: 7.10.1.6
 * 
 * #include <stdlib.h>
 * long strtoul (const char *nptr, char **endptr, int base);
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


static char *_test_strtoul_id =
  "$Id$";

void do_test ()
{
  /* Case 1 */
  if (!({char *p; strtoul ("0", &p, 10) == 0L;})) {
    failed ("Case 1: {char *p; strtoul (\"0\", &p, 10) == 0L;}");
  }
  
  /* Case 2 */
  if (!({char *p; strtoul ("+0", &p, 10) == 0L;})) {
    failed ("Case 2: {char *p; strtoul (\"+0\", &p, 10) == 0L;}");
  }
  
  /* Case 3 */
  if (!({char *p; strtoul (" 1", &p, 10) == 1L;})) {
    failed ("Case 3: {char *p; strtoul (\" 1\", &p, 10) == 1L;}");
  }
  
  /* Case 4 */
  if (!({char *p; strtoul ("  2", &p, 10) == 2L;})) {
    failed ("Case 4: {char *p; strtoul (\"  2\", &p, 10) == 2L;}");
  }
  
  /* Case 5 */
  if (!({char *p; strtoul ("   3", &p, 10) == 3L;})) {
    failed ("Case 5: {char *p; strtoul (\"   3\", &p, 10) == 3L;}");
  }
  
  /* Case 6 */
  if (!({char *p; strtoul ("    4", &p, 10) == 4L;})) {
    failed ("Case 6: {char *p; strtoul (\"    4\", &p, 10) == 4L;}");
  }
  
  /* Case 7 */
  if (!({char *p; strtoul ("     5", &p, 10) == 5L;})) {
    failed ("Case 7: {char *p; strtoul (\"     5\", &p, 10) == 5L;}");
  }
  
  /* Case 8 */
  if (!({char *p; strtoul ("      6", &p, 10) == 6L;})) {
    failed ("Case 8: {char *p; strtoul (\"      6\", &p, 10) == 6L;}");
  }
  
  /* Case 9 */
  if (!({char *p; strtoul ("       7", &p, 10) == 7L;})) {
    failed ("Case 9: {char *p; strtoul (\"       7\", &p, 10) == 7L;}");
  }
  
  /* Case 10 */
  if (!({char *p; strtoul ("        8", &p, 10) == 8L;})) {
    failed ("Case 10: {char *p; strtoul (\"        8\", &p, 10) == 8L;}");
  }
  
  /* Case 11 */
  if (!({char *p; strtoul ("         9", &p, 10) == 9L;})) {
    failed ("Case 11: {char *p; strtoul (\"         9\", &p, 10) == 9L;}");
  }
  
  /* Case 12 */
  if (!({char *p; strtoul ("123456789", &p, 10) == 123456789L;})) {
    failed ("Case 12: {char *p; strtoul (\"123456789\", &p, 10) == 123456789L;}");
  }
  
  /* Case 13 */
  if (!({char *p; strtoul ("2147483647", &p, 10) == 2147483647L;})) {
    failed ("Case 13: {char *p; strtoul (\"2147483647\", &p, 10) == 2147483647L;}");
  }
  
  /* Case 14 */
  if (!({char *p; strtoul ("4294967295", &p, 10) == 4294967295L;})) {
    failed ("Case 14: {char *p; strtoul (\"4294967295\", &p, 10) == 4294967295L;}");
  }
  
  /* Case 15 */
  if (!({char *p; strtoul ("123456aA", &p, 16) == 0x123456aaL;})) {
    failed ("Case 15: {char *p; strtoul (\"123456aA\", &p, 16) == 0x123456aaL;}");
  }
  
  /* Case 16 */
  if (!({char *p; strtoul ("223456bB", &p, 16) == 0x223456bbL;})) {
    failed ("Case 16: {char *p; strtoul (\"223456bB\", &p, 16) == 0x223456bbL;}");
  }
  
  /* Case 17 */
  if (!({char *p; strtoul ("323456cC", &p, 16) == 0x323456ccL;})) {
    failed ("Case 17: {char *p; strtoul (\"323456cC\", &p, 16) == 0x323456ccL;}");
  }
  
  /* Case 18 */
  if (!({char *p; strtoul ("423456dD", &p, 16) == 0x423456ddL;})) {
    failed ("Case 18: {char *p; strtoul (\"423456dD\", &p, 16) == 0x423456ddL;}");
  }
  
  /* Case 19 */
  if (!({char *p; strtoul ("523456eE", &p, 16) == 0x523456eeL;})) {
    failed ("Case 19: {char *p; strtoul (\"523456eE\", &p, 16) == 0x523456eeL;}");
  }
  
  /* Case 20 */
  if (!({char *p; strtoul ("623456fF", &p, 16) == 0x623456ffL;})) {
    failed ("Case 20: {char *p; strtoul (\"623456fF\", &p, 16) == 0x623456ffL;}");
  }
  
  /* Case 21 */
  if (!({char *p; strtoul ("72345677", &p, 16) == 0x72345677L;})) {
    failed ("Case 21: {char *p; strtoul (\"72345677\", &p, 16) == 0x72345677L;}");
  }
  
  /* Case 22 */
  if (!({char *p; strtoul ("823456aA", &p, 16) == 0x823456aaL;})) {
    failed ("Case 22: {char *p; strtoul (\"823456aA\", &p, 16) == 0x823456aaL;}");
  }
  
  /* Case 23 */
  if (!({char *p; strtoul ("923456bB", &p, 16) == 0x923456bbL;})) {
    failed ("Case 23: {char *p; strtoul (\"923456bB\", &p, 16) == 0x923456bbL;}");
  }
  
  /* Case 24 */
  if (!({char *p; strtoul ("a23456cC", &p, 16) == 0xa23456ccL;})) {
    failed ("Case 24: {char *p; strtoul (\"a23456cC\", &p, 16) == 0xa23456ccL;}");
  }
  
  /* Case 25 */
  if (!({char *p; strtoul ("b23456dD", &p, 16) == 0xb23456ddL;})) {
    failed ("Case 25: {char *p; strtoul (\"b23456dD\", &p, 16) == 0xb23456ddL;}");
  }
  
  /* Case 26 */
  if (!({char *p; strtoul ("c23456eE", &p, 16) == 0xc23456eeL;})) {
    failed ("Case 26: {char *p; strtoul (\"c23456eE\", &p, 16) == 0xc23456eeL;}");
  }
  
  /* Case 27 */
  if (!({char *p; strtoul ("d23456fF", &p, 16) == 0xd23456ffL;})) {
    failed ("Case 27: {char *p; strtoul (\"d23456fF\", &p, 16) == 0xd23456ffL;}");
  }
  
  /* Case 28 */
  if (!({char *p; strtoul ("e2345677", &p, 16) == 0xe2345677L;})) {
    failed ("Case 28: {char *p; strtoul (\"e2345677\", &p, 16) == 0xe2345677L;}");
  }
  
  /* Case 29 */
  if (!({char *p; strtoul ("00000000", &p, 16) == 0x00000000L;})) {
    failed ("Case 29: {char *p; strtoul (\"00000000\", &p, 16) == 0x00000000L;}");
  }
  
  /* Case 30 */
  if (!({char *p; strtoul ("ffffFFFF", &p, 16) == 0xFFFFFFFFL;})) {
    failed ("Case 30: {char *p; strtoul (\"ffffFFFF\", &p, 16) == 0xFFFFFFFFL;}");
  }
  
}


void main ()
{
  test ("test-strtoul", "Test for ANSI Standard C: 7.10.1.6");

  do_test ();

  result ();
}

