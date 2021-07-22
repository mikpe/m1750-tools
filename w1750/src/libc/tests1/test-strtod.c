/*
 * Test for ANSI Standard C: 7.10.1.4
 * 
 * #include <stdlib.h>
 * double strtod (const char *nptr, char **endptr);
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

#include <math.h>

static char *_test_strtod_id =
  "$Id$";

void do_test ()
{
  /* Case 1 */
  if (!({char *p; strtod ("0.0", &p) == 0.0;})) {
    failed ("Case 1: {char *p; strtod (\"0.0\", &p) == 0.0;}");
  }
  
  /* Case 2 */
  if (!({char *p; (fabs (strtod ("1.0", &p) / 1.0 - 1.0) < 1.0e-10);})) {
    failed ("Case 2: {char *p; (fabs (strtod (\"1.0\", &p) / 1.0 - 1.0) < 1.0e-10);}");
  }
  
  /* Case 3 */
  if (!({char *p; (fabs (strtod ("2.0", &p) / 2.0 - 1.0) < 1.0e-10);})) {
    failed ("Case 3: {char *p; (fabs (strtod (\"2.0\", &p) / 2.0 - 1.0) < 1.0e-10);}");
  }
  
  /* Case 4 */
  if (!({char *p; (fabs (strtod ("3.0", &p) / 3.0 - 1.0) < 1.0e-10);})) {
    failed ("Case 4: {char *p; (fabs (strtod (\"3.0\", &p) / 3.0 - 1.0) < 1.0e-10);}");
  }
  
  /* Case 5 */
  if (!({char *p; (fabs (strtod ("4.0", &p) / 4.0 - 1.0) < 1.0e-10);})) {
    failed ("Case 5: {char *p; (fabs (strtod (\"4.0\", &p) / 4.0 - 1.0) < 1.0e-10);}");
  }
  
  /* Case 6 */
  if (!({char *p; (fabs (strtod ("5.0", &p) / 5.0 - 1.0) < 1.0e-10);})) {
    failed ("Case 6: {char *p; (fabs (strtod (\"5.0\", &p) / 5.0 - 1.0) < 1.0e-10);}");
  }
  
  /* Case 7 */
  if (!({char *p; (fabs (strtod ("6.0", &p) / 6.0 - 1.0) < 1.0e-10);})) {
    failed ("Case 7: {char *p; (fabs (strtod (\"6.0\", &p) / 6.0 - 1.0) < 1.0e-10);}");
  }
  
  /* Case 8 */
  if (!({char *p; (fabs (strtod ("7.0", &p) / 7.0 - 1.0) < 1.0e-10);})) {
    failed ("Case 8: {char *p; (fabs (strtod (\"7.0\", &p) / 7.0 - 1.0) < 1.0e-10);}");
  }
  
  /* Case 9 */
  if (!({char *p; (fabs (strtod ("8.0", &p) / 8.0 - 1.0) < 1.0e-10);})) {
    failed ("Case 9: {char *p; (fabs (strtod (\"8.0\", &p) / 8.0 - 1.0) < 1.0e-10);}");
  }
  
  /* Case 10 */
  if (!({char *p; (fabs (strtod ("9.0", &p) / 9.0 - 1.0) < 1.0e-10);})) {
    failed ("Case 10: {char *p; (fabs (strtod (\"9.0\", &p) / 9.0 - 1.0) < 1.0e-10);}");
  }
  
  /* Case 11 */
  if (!({char *p; (fabs (strtod ("-1.0", &p) / -1.0 - 1.0) < 1.0e-10);})) {
    failed ("Case 11: {char *p; (fabs (strtod (\"-1.0\", &p) / -1.0 - 1.0) < 1.0e-10);}");
  }
  
  /* Case 12 */
  if (!({char *p; (fabs (strtod ("-2.0", &p) / -2.0 - 1.0) < 1.0e-10);})) {
    failed ("Case 12: {char *p; (fabs (strtod (\"-2.0\", &p) / -2.0 - 1.0) < 1.0e-10);}");
  }
  
  /* Case 13 */
  if (!({char *p; (fabs (strtod ("-3.0", &p) / -3.0 - 1.0) < 1.0e-10);})) {
    failed ("Case 13: {char *p; (fabs (strtod (\"-3.0\", &p) / -3.0 - 1.0) < 1.0e-10);}");
  }
  
  /* Case 14 */
  if (!({char *p; (fabs (strtod ("-4.0", &p) / -4.0 - 1.0) < 1.0e-10);})) {
    failed ("Case 14: {char *p; (fabs (strtod (\"-4.0\", &p) / -4.0 - 1.0) < 1.0e-10);}");
  }
  
  /* Case 15 */
  if (!({char *p; (fabs (strtod ("-5.0", &p) / -5.0 - 1.0) < 1.0e-10);})) {
    failed ("Case 15: {char *p; (fabs (strtod (\"-5.0\", &p) / -5.0 - 1.0) < 1.0e-10);}");
  }
  
  /* Case 16 */
  if (!({char *p; (fabs (strtod ("-6.0", &p) / -6.0 - 1.0) < 1.0e-10);})) {
    failed ("Case 16: {char *p; (fabs (strtod (\"-6.0\", &p) / -6.0 - 1.0) < 1.0e-10);}");
  }
  
  /* Case 17 */
  if (!({char *p; (fabs (strtod ("-7.0", &p) / -7.0 - 1.0) < 1.0e-10);})) {
    failed ("Case 17: {char *p; (fabs (strtod (\"-7.0\", &p) / -7.0 - 1.0) < 1.0e-10);}");
  }
  
  /* Case 18 */
  if (!({char *p; (fabs (strtod ("-8.0", &p) / -8.0 - 1.0) < 1.0e-10);})) {
    failed ("Case 18: {char *p; (fabs (strtod (\"-8.0\", &p) / -8.0 - 1.0) < 1.0e-10);}");
  }
  
  /* Case 19 */
  if (!({char *p; (fabs (strtod ("-9.0", &p) / -9.0 - 1.0) < 1.0e-10);})) {
    failed ("Case 19: {char *p; (fabs (strtod (\"-9.0\", &p) / -9.0 - 1.0) < 1.0e-10);}");
  }
  
  /* Case 20 */
  if (!({char *p; (fabs (strtod ("1.0e1", &p) / 1.0e1 - 1.0) < 1.0e-10);})) {
    failed ("Case 20: {char *p; (fabs (strtod (\"1.0e1\", &p) / 1.0e1 - 1.0) < 1.0e-10);}");
  }
  
  /* Case 21 */
  if (!({char *p; (fabs (strtod ("2.0e2", &p) / 2.0e2 - 1.0) < 1.0e-10);})) {
    failed ("Case 21: {char *p; (fabs (strtod (\"2.0e2\", &p) / 2.0e2 - 1.0) < 1.0e-10);}");
  }
  
  /* Case 22 */
  if (!({char *p; (fabs (strtod ("3.0e3", &p) / 3.0e3 - 1.0) < 1.0e-10);})) {
    failed ("Case 22: {char *p; (fabs (strtod (\"3.0e3\", &p) / 3.0e3 - 1.0) < 1.0e-10);}");
  }
  
  /* Case 23 */
  if (!({char *p; (fabs (strtod ("4.0e4", &p) / 4.0e4 - 1.0) < 1.0e-10);})) {
    failed ("Case 23: {char *p; (fabs (strtod (\"4.0e4\", &p) / 4.0e4 - 1.0) < 1.0e-10);}");
  }
  
  /* Case 24 */
  if (!({char *p; (fabs (strtod ("5.0e5", &p) / 5.0e5 - 1.0) < 1.0e-10);})) {
    failed ("Case 24: {char *p; (fabs (strtod (\"5.0e5\", &p) / 5.0e5 - 1.0) < 1.0e-10);}");
  }
  
  /* Case 25 */
  if (!({char *p; (fabs (strtod ("6.0e6", &p) / 6.0e6 - 1.0) < 1.0e-10);})) {
    failed ("Case 25: {char *p; (fabs (strtod (\"6.0e6\", &p) / 6.0e6 - 1.0) < 1.0e-10);}");
  }
  
  /* Case 26 */
  if (!({char *p; (fabs (strtod ("7.0e7", &p) / 7.0e7 - 1.0) < 1.0e-10);})) {
    failed ("Case 26: {char *p; (fabs (strtod (\"7.0e7\", &p) / 7.0e7 - 1.0) < 1.0e-10);}");
  }
  
  /* Case 27 */
  if (!({char *p; (fabs (strtod ("8.0e8", &p) / 8.0e8 - 1.0) < 1.0e-10);})) {
    failed ("Case 27: {char *p; (fabs (strtod (\"8.0e8\", &p) / 8.0e8 - 1.0) < 1.0e-10);}");
  }
  
  /* Case 28 */
  if (!({char *p; (fabs (strtod ("9.0e9", &p) / 9.0e9 - 1.0) < 1.0e-10);})) {
    failed ("Case 28: {char *p; (fabs (strtod (\"9.0e9\", &p) / 9.0e9 - 1.0) < 1.0e-10);}");
  }
  
  /* Case 29 */
  if (!({char *p; (fabs (strtod ("0.00000000000000000000000000000000000001", &p) / 1.0e-38 - 1.0) < 1.0e-10);})) {
    failed ("Case 29: {char *p; (fabs (strtod (\"0.00000000000000000000000000000000000001\", &p) / 1.0e-38 - 1.0) < 1.0e-10);}");
  }
  
  /* Case 30 */
  if (!({char *p; (fabs (strtod ("0.0000000000000000000000000000000000001", &p) / 1.0e-37 - 1.0) < 1.0e-10);})) {
    failed ("Case 30: {char *p; (fabs (strtod (\"0.0000000000000000000000000000000000001\", &p) / 1.0e-37 - 1.0) < 1.0e-10);}");
  }
  
  /* Case 31 */
  if (!({char *p; (fabs (strtod ("0.000000000000000000000000000000000001", &p) / 1.0e-36 - 1.0) < 1.0e-10);})) {
    failed ("Case 31: {char *p; (fabs (strtod (\"0.000000000000000000000000000000000001\", &p) / 1.0e-36 - 1.0) < 1.0e-10);}");
  }
  
  /* Case 32 */
  if (!({char *p; (fabs (strtod ("0.00000000000000000000000000000000001", &p) / 1.0e-35 - 1.0) < 1.0e-10);})) {
    failed ("Case 32: {char *p; (fabs (strtod (\"0.00000000000000000000000000000000001\", &p) / 1.0e-35 - 1.0) < 1.0e-10);}");
  }
  
  /* Case 33 */
  if (!({char *p; (fabs (strtod ("0.0000000000000000000000000000000001", &p) / 1.0e-34 - 1.0) < 1.0e-10);})) {
    failed ("Case 33: {char *p; (fabs (strtod (\"0.0000000000000000000000000000000001\", &p) / 1.0e-34 - 1.0) < 1.0e-10);}");
  }
  
  /* Case 34 */
  if (!({char *p; (fabs (strtod ("0.000000000000000000000000000000001", &p) / 1.0e-33 - 1.0) < 1.0e-10);})) {
    failed ("Case 34: {char *p; (fabs (strtod (\"0.000000000000000000000000000000001\", &p) / 1.0e-33 - 1.0) < 1.0e-10);}");
  }
  
  /* Case 35 */
  if (!({char *p; (fabs (strtod ("0.00000000000000000000000000000001", &p) / 1.0e-32 - 1.0) < 1.0e-10);})) {
    failed ("Case 35: {char *p; (fabs (strtod (\"0.00000000000000000000000000000001\", &p) / 1.0e-32 - 1.0) < 1.0e-10);}");
  }
  
  /* Case 36 */
  if (!({char *p; (fabs (strtod ("0.0000000000000000000000000000001", &p) / 1.0e-31 - 1.0) < 1.0e-10);})) {
    failed ("Case 36: {char *p; (fabs (strtod (\"0.0000000000000000000000000000001\", &p) / 1.0e-31 - 1.0) < 1.0e-10);}");
  }
  
  /* Case 37 */
  if (!({char *p; (fabs (strtod ("0.000000000000000000000000000001", &p) / 1.0e-30 - 1.0) < 1.0e-10);})) {
    failed ("Case 37: {char *p; (fabs (strtod (\"0.000000000000000000000000000001\", &p) / 1.0e-30 - 1.0) < 1.0e-10);}");
  }
  
  /* Case 38 */
  if (!({char *p; (fabs (strtod ("0.00000000000000000000000000001", &p) / 1.0e-29 - 1.0) < 1.0e-10);})) {
    failed ("Case 38: {char *p; (fabs (strtod (\"0.00000000000000000000000000001\", &p) / 1.0e-29 - 1.0) < 1.0e-10);}");
  }
  
  /* Case 39 */
  if (!({char *p; (fabs (strtod ("0.0000000000000000000000000001", &p) / 1.0e-28 - 1.0) < 1.0e-10);})) {
    failed ("Case 39: {char *p; (fabs (strtod (\"0.0000000000000000000000000001\", &p) / 1.0e-28 - 1.0) < 1.0e-10);}");
  }
  
  /* Case 40 */
  if (!({char *p; (fabs (strtod ("0.000000000000000000000000001", &p) / 1.0e-27 - 1.0) < 1.0e-10);})) {
    failed ("Case 40: {char *p; (fabs (strtod (\"0.000000000000000000000000001\", &p) / 1.0e-27 - 1.0) < 1.0e-10);}");
  }
  
  /* Case 41 */
  if (!({char *p; (fabs (strtod ("0.00000000000000000000000001", &p) / 1.0e-26 - 1.0) < 1.0e-10);})) {
    failed ("Case 41: {char *p; (fabs (strtod (\"0.00000000000000000000000001\", &p) / 1.0e-26 - 1.0) < 1.0e-10);}");
  }
  
  /* Case 42 */
  if (!({char *p; (fabs (strtod ("0.0000000000000000000000001", &p) / 1.0e-25 - 1.0) < 1.0e-10);})) {
    failed ("Case 42: {char *p; (fabs (strtod (\"0.0000000000000000000000001\", &p) / 1.0e-25 - 1.0) < 1.0e-10);}");
  }
  
  /* Case 43 */
  if (!({char *p; (fabs (strtod ("0.000000000000000000000001", &p) / 1.0e-24 - 1.0) < 1.0e-10);})) {
    failed ("Case 43: {char *p; (fabs (strtod (\"0.000000000000000000000001\", &p) / 1.0e-24 - 1.0) < 1.0e-10);}");
  }
  
  /* Case 44 */
  if (!({char *p; (fabs (strtod ("0.00000000000000000000001", &p) / 1.0e-23 - 1.0) < 1.0e-10);})) {
    failed ("Case 44: {char *p; (fabs (strtod (\"0.00000000000000000000001\", &p) / 1.0e-23 - 1.0) < 1.0e-10);}");
  }
  
  /* Case 45 */
  if (!({char *p; (fabs (strtod ("0.0000000000000000000001", &p) / 1.0e-22 - 1.0) < 1.0e-10);})) {
    failed ("Case 45: {char *p; (fabs (strtod (\"0.0000000000000000000001\", &p) / 1.0e-22 - 1.0) < 1.0e-10);}");
  }
  
  /* Case 46 */
  if (!({char *p; (fabs (strtod ("0.000000000000000000001", &p) / 1.0e-21 - 1.0) < 1.0e-10);})) {
    failed ("Case 46: {char *p; (fabs (strtod (\"0.000000000000000000001\", &p) / 1.0e-21 - 1.0) < 1.0e-10);}");
  }
  
  /* Case 47 */
  if (!({char *p; (fabs (strtod ("0.00000000000000000001", &p) / 1.0e-20 - 1.0) < 1.0e-10);})) {
    failed ("Case 47: {char *p; (fabs (strtod (\"0.00000000000000000001\", &p) / 1.0e-20 - 1.0) < 1.0e-10);}");
  }
  
  /* Case 48 */
  if (!({char *p; (fabs (strtod ("0.0000000000000000001", &p) / 1.0e-19 - 1.0) < 1.0e-10);})) {
    failed ("Case 48: {char *p; (fabs (strtod (\"0.0000000000000000001\", &p) / 1.0e-19 - 1.0) < 1.0e-10);}");
  }
  
  /* Case 49 */
  if (!({char *p; (fabs (strtod ("0.000000000000000001", &p) / 1.0e-18 - 1.0) < 1.0e-10);})) {
    failed ("Case 49: {char *p; (fabs (strtod (\"0.000000000000000001\", &p) / 1.0e-18 - 1.0) < 1.0e-10);}");
  }
  
  /* Case 50 */
  if (!({char *p; (fabs (strtod ("0.00000000000000001", &p) / 1.0e-17 - 1.0) < 1.0e-10);})) {
    failed ("Case 50: {char *p; (fabs (strtod (\"0.00000000000000001\", &p) / 1.0e-17 - 1.0) < 1.0e-10);}");
  }
  
  /* Case 51 */
  if (!({char *p; (fabs (strtod ("0.0000000000000001", &p) / 1.0e-16 - 1.0) < 1.0e-10);})) {
    failed ("Case 51: {char *p; (fabs (strtod (\"0.0000000000000001\", &p) / 1.0e-16 - 1.0) < 1.0e-10);}");
  }
  
  /* Case 52 */
  if (!({char *p; (fabs (strtod ("0.000000000000001", &p) / 1.0e-15 - 1.0) < 1.0e-10);})) {
    failed ("Case 52: {char *p; (fabs (strtod (\"0.000000000000001\", &p) / 1.0e-15 - 1.0) < 1.0e-10);}");
  }
  
  /* Case 53 */
  if (!({char *p; (fabs (strtod ("0.00000000000001", &p) / 1.0e-14 - 1.0) < 1.0e-10);})) {
    failed ("Case 53: {char *p; (fabs (strtod (\"0.00000000000001\", &p) / 1.0e-14 - 1.0) < 1.0e-10);}");
  }
  
  /* Case 54 */
  if (!({char *p; (fabs (strtod ("0.0000000000001", &p) / 1.0e-13 - 1.0) < 1.0e-10);})) {
    failed ("Case 54: {char *p; (fabs (strtod (\"0.0000000000001\", &p) / 1.0e-13 - 1.0) < 1.0e-10);}");
  }
  
  /* Case 55 */
  if (!({char *p; (fabs (strtod ("0.000000000001", &p) / 1.0e-12 - 1.0) < 1.0e-10);})) {
    failed ("Case 55: {char *p; (fabs (strtod (\"0.000000000001\", &p) / 1.0e-12 - 1.0) < 1.0e-10);}");
  }
  
  /* Case 56 */
  if (!({char *p; (fabs (strtod ("0.00000000001", &p) / 1.0e-11 - 1.0) < 1.0e-10);})) {
    failed ("Case 56: {char *p; (fabs (strtod (\"0.00000000001\", &p) / 1.0e-11 - 1.0) < 1.0e-10);}");
  }
  
  /* Case 57 */
  if (!({char *p; (fabs (strtod ("0.0000000001", &p) / 1.0e-10 - 1.0) < 1.0e-10);})) {
    failed ("Case 57: {char *p; (fabs (strtod (\"0.0000000001\", &p) / 1.0e-10 - 1.0) < 1.0e-10);}");
  }
  
  /* Case 58 */
  if (!({char *p; (fabs (strtod ("0.000000001", &p) / 1.0e-09 - 1.0) < 1.0e-10);})) {
    failed ("Case 58: {char *p; (fabs (strtod (\"0.000000001\", &p) / 1.0e-09 - 1.0) < 1.0e-10);}");
  }
  
  /* Case 59 */
  if (!({char *p; (fabs (strtod ("0.00000001", &p) / 1.0e-08 - 1.0) < 1.0e-10);})) {
    failed ("Case 59: {char *p; (fabs (strtod (\"0.00000001\", &p) / 1.0e-08 - 1.0) < 1.0e-10);}");
  }
  
  /* Case 60 */
  if (!({char *p; (fabs (strtod ("0.0000001", &p) / 1.0e-07 - 1.0) < 1.0e-10);})) {
    failed ("Case 60: {char *p; (fabs (strtod (\"0.0000001\", &p) / 1.0e-07 - 1.0) < 1.0e-10);}");
  }
  
  /* Case 61 */
  if (!({char *p; (fabs (strtod ("0.000001", &p) / 1.0e-06 - 1.0) < 1.0e-10);})) {
    failed ("Case 61: {char *p; (fabs (strtod (\"0.000001\", &p) / 1.0e-06 - 1.0) < 1.0e-10);}");
  }
  
  /* Case 62 */
  if (!({char *p; (fabs (strtod ("0.00001", &p) / 1.0e-05 - 1.0) < 1.0e-10);})) {
    failed ("Case 62: {char *p; (fabs (strtod (\"0.00001\", &p) / 1.0e-05 - 1.0) < 1.0e-10);}");
  }
  
  /* Case 63 */
  if (!({char *p; (fabs (strtod ("0.0001", &p) / 1.0e-04 - 1.0) < 1.0e-10);})) {
    failed ("Case 63: {char *p; (fabs (strtod (\"0.0001\", &p) / 1.0e-04 - 1.0) < 1.0e-10);}");
  }
  
  /* Case 64 */
  if (!({char *p; (fabs (strtod ("0.001", &p) / 1.0e-03 - 1.0) < 1.0e-10);})) {
    failed ("Case 64: {char *p; (fabs (strtod (\"0.001\", &p) / 1.0e-03 - 1.0) < 1.0e-10);}");
  }
  
  /* Case 65 */
  if (!({char *p; (fabs (strtod ("0.01", &p) / 1.0e-02 - 1.0) < 1.0e-10);})) {
    failed ("Case 65: {char *p; (fabs (strtod (\"0.01\", &p) / 1.0e-02 - 1.0) < 1.0e-10);}");
  }
  
  /* Case 66 */
  if (!({char *p; (fabs (strtod ("0.1", &p) / 1.0e-01 - 1.0) < 1.0e-10);})) {
    failed ("Case 66: {char *p; (fabs (strtod (\"0.1\", &p) / 1.0e-01 - 1.0) < 1.0e-10);}");
  }
  
  /* Case 67 */
  if (!({char *p; (fabs (strtod ("1.0", &p) / 1.0e00 - 1.0) < 1.0e-10);})) {
    failed ("Case 67: {char *p; (fabs (strtod (\"1.0\", &p) / 1.0e00 - 1.0) < 1.0e-10);}");
  }
  
  /* Case 68 */
  if (!({char *p; (fabs (strtod ("10.0", &p) / 1.0e01 - 1.0) < 1.0e-10);})) {
    failed ("Case 68: {char *p; (fabs (strtod (\"10.0\", &p) / 1.0e01 - 1.0) < 1.0e-10);}");
  }
  
  /* Case 69 */
  if (!({char *p; (fabs (strtod ("100.0", &p) / 1.0e02 - 1.0) < 1.0e-10);})) {
    failed ("Case 69: {char *p; (fabs (strtod (\"100.0\", &p) / 1.0e02 - 1.0) < 1.0e-10);}");
  }
  
  /* Case 70 */
  if (!({char *p; (fabs (strtod ("1000.0", &p) / 1.0e03 - 1.0) < 1.0e-10);})) {
    failed ("Case 70: {char *p; (fabs (strtod (\"1000.0\", &p) / 1.0e03 - 1.0) < 1.0e-10);}");
  }
  
  /* Case 71 */
  if (!({char *p; (fabs (strtod ("10000.0", &p) / 1.0e04 - 1.0) < 1.0e-10);})) {
    failed ("Case 71: {char *p; (fabs (strtod (\"10000.0\", &p) / 1.0e04 - 1.0) < 1.0e-10);}");
  }
  
  /* Case 72 */
  if (!({char *p; (fabs (strtod ("100000.0", &p) / 1.0e05 - 1.0) < 1.0e-10);})) {
    failed ("Case 72: {char *p; (fabs (strtod (\"100000.0\", &p) / 1.0e05 - 1.0) < 1.0e-10);}");
  }
  
  /* Case 73 */
  if (!({char *p; (fabs (strtod ("1000000.0", &p) / 1.0e06 - 1.0) < 1.0e-10);})) {
    failed ("Case 73: {char *p; (fabs (strtod (\"1000000.0\", &p) / 1.0e06 - 1.0) < 1.0e-10);}");
  }
  
  /* Case 74 */
  if (!({char *p; (fabs (strtod ("10000000.0", &p) / 1.0e07 - 1.0) < 1.0e-10);})) {
    failed ("Case 74: {char *p; (fabs (strtod (\"10000000.0\", &p) / 1.0e07 - 1.0) < 1.0e-10);}");
  }
  
  /* Case 75 */
  if (!({char *p; (fabs (strtod ("100000000.0", &p) / 1.0e08 - 1.0) < 1.0e-10);})) {
    failed ("Case 75: {char *p; (fabs (strtod (\"100000000.0\", &p) / 1.0e08 - 1.0) < 1.0e-10);}");
  }
  
  /* Case 76 */
  if (!({char *p; (fabs (strtod ("1000000000.0", &p) / 1.0e09 - 1.0) < 1.0e-10);})) {
    failed ("Case 76: {char *p; (fabs (strtod (\"1000000000.0\", &p) / 1.0e09 - 1.0) < 1.0e-10);}");
  }
  
  /* Case 77 */
  if (!({char *p; (fabs (strtod ("10000000000.0", &p) / 1.0e10 - 1.0) < 1.0e-10);})) {
    failed ("Case 77: {char *p; (fabs (strtod (\"10000000000.0\", &p) / 1.0e10 - 1.0) < 1.0e-10);}");
  }
  
  /* Case 78 */
  if (!({char *p; (fabs (strtod ("100000000000.0", &p) / 1.0e11 - 1.0) < 1.0e-10);})) {
    failed ("Case 78: {char *p; (fabs (strtod (\"100000000000.0\", &p) / 1.0e11 - 1.0) < 1.0e-10);}");
  }
  
  /* Case 79 */
  if (!({char *p; (fabs (strtod ("1000000000000.0", &p) / 1.0e12 - 1.0) < 1.0e-10);})) {
    failed ("Case 79: {char *p; (fabs (strtod (\"1000000000000.0\", &p) / 1.0e12 - 1.0) < 1.0e-10);}");
  }
  
  /* Case 80 */
  if (!({char *p; (fabs (strtod ("10000000000000.0", &p) / 1.0e13 - 1.0) < 1.0e-10);})) {
    failed ("Case 80: {char *p; (fabs (strtod (\"10000000000000.0\", &p) / 1.0e13 - 1.0) < 1.0e-10);}");
  }
  
  /* Case 81 */
  if (!({char *p; (fabs (strtod ("100000000000000.0", &p) / 1.0e14 - 1.0) < 1.0e-10);})) {
    failed ("Case 81: {char *p; (fabs (strtod (\"100000000000000.0\", &p) / 1.0e14 - 1.0) < 1.0e-10);}");
  }
  
  /* Case 82 */
  if (!({char *p; (fabs (strtod ("1000000000000000.0", &p) / 1.0e15 - 1.0) < 1.0e-10);})) {
    failed ("Case 82: {char *p; (fabs (strtod (\"1000000000000000.0\", &p) / 1.0e15 - 1.0) < 1.0e-10);}");
  }
  
  /* Case 83 */
  if (!({char *p; (fabs (strtod ("10000000000000000.0", &p) / 1.0e16 - 1.0) < 1.0e-10);})) {
    failed ("Case 83: {char *p; (fabs (strtod (\"10000000000000000.0\", &p) / 1.0e16 - 1.0) < 1.0e-10);}");
  }
  
  /* Case 84 */
  if (!({char *p; (fabs (strtod ("100000000000000000.0", &p) / 1.0e17 - 1.0) < 1.0e-10);})) {
    failed ("Case 84: {char *p; (fabs (strtod (\"100000000000000000.0\", &p) / 1.0e17 - 1.0) < 1.0e-10);}");
  }
  
  /* Case 85 */
  if (!({char *p; (fabs (strtod ("1000000000000000000.0", &p) / 1.0e18 - 1.0) < 1.0e-10);})) {
    failed ("Case 85: {char *p; (fabs (strtod (\"1000000000000000000.0\", &p) / 1.0e18 - 1.0) < 1.0e-10);}");
  }
  
  /* Case 86 */
  if (!({char *p; (fabs (strtod ("10000000000000000000.0", &p) / 1.0e19 - 1.0) < 1.0e-10);})) {
    failed ("Case 86: {char *p; (fabs (strtod (\"10000000000000000000.0\", &p) / 1.0e19 - 1.0) < 1.0e-10);}");
  }
  
  /* Case 87 */
  if (!({char *p; (fabs (strtod ("100000000000000000000.0", &p) / 1.0e20 - 1.0) < 1.0e-10);})) {
    failed ("Case 87: {char *p; (fabs (strtod (\"100000000000000000000.0\", &p) / 1.0e20 - 1.0) < 1.0e-10);}");
  }
  
  /* Case 88 */
  if (!({char *p; (fabs (strtod ("1000000000000000000000.0", &p) / 1.0e21 - 1.0) < 1.0e-10);})) {
    failed ("Case 88: {char *p; (fabs (strtod (\"1000000000000000000000.0\", &p) / 1.0e21 - 1.0) < 1.0e-10);}");
  }
  
  /* Case 89 */
  if (!({char *p; (fabs (strtod ("10000000000000000000000.0", &p) / 1.0e22 - 1.0) < 1.0e-10);})) {
    failed ("Case 89: {char *p; (fabs (strtod (\"10000000000000000000000.0\", &p) / 1.0e22 - 1.0) < 1.0e-10);}");
  }
  
  /* Case 90 */
  if (!({char *p; (fabs (strtod ("100000000000000000000000.0", &p) / 1.0e23 - 1.0) < 1.0e-10);})) {
    failed ("Case 90: {char *p; (fabs (strtod (\"100000000000000000000000.0\", &p) / 1.0e23 - 1.0) < 1.0e-10);}");
  }
  
  /* Case 91 */
  if (!({char *p; (fabs (strtod ("1000000000000000000000000.0", &p) / 1.0e24 - 1.0) < 1.0e-10);})) {
    failed ("Case 91: {char *p; (fabs (strtod (\"1000000000000000000000000.0\", &p) / 1.0e24 - 1.0) < 1.0e-10);}");
  }
  
  /* Case 92 */
  if (!({char *p; (fabs (strtod ("10000000000000000000000000.0", &p) / 1.0e25 - 1.0) < 1.0e-10);})) {
    failed ("Case 92: {char *p; (fabs (strtod (\"10000000000000000000000000.0\", &p) / 1.0e25 - 1.0) < 1.0e-10);}");
  }
  
  /* Case 93 */
  if (!({char *p; (fabs (strtod ("100000000000000000000000000.0", &p) / 1.0e26 - 1.0) < 1.0e-10);})) {
    failed ("Case 93: {char *p; (fabs (strtod (\"100000000000000000000000000.0\", &p) / 1.0e26 - 1.0) < 1.0e-10);}");
  }
  
  /* Case 94 */
  if (!({char *p; (fabs (strtod ("1000000000000000000000000000.0", &p) / 1.0e27 - 1.0) < 1.0e-10);})) {
    failed ("Case 94: {char *p; (fabs (strtod (\"1000000000000000000000000000.0\", &p) / 1.0e27 - 1.0) < 1.0e-10);}");
  }
  
  /* Case 95 */
  if (!({char *p; (fabs (strtod ("10000000000000000000000000000.0", &p) / 1.0e28 - 1.0) < 1.0e-10);})) {
    failed ("Case 95: {char *p; (fabs (strtod (\"10000000000000000000000000000.0\", &p) / 1.0e28 - 1.0) < 1.0e-10);}");
  }
  
  /* Case 96 */
  if (!({char *p; (fabs (strtod ("100000000000000000000000000000.0", &p) / 1.0e29 - 1.0) < 1.0e-10);})) {
    failed ("Case 96: {char *p; (fabs (strtod (\"100000000000000000000000000000.0\", &p) / 1.0e29 - 1.0) < 1.0e-10);}");
  }
  
  /* Case 97 */
  if (!({char *p; (fabs (strtod ("1000000000000000000000000000000.0", &p) / 1.0e30 - 1.0) < 1.0e-10);})) {
    failed ("Case 97: {char *p; (fabs (strtod (\"1000000000000000000000000000000.0\", &p) / 1.0e30 - 1.0) < 1.0e-10);}");
  }
  
  /* Case 98 */
  if (!({char *p; (fabs (strtod ("10000000000000000000000000000000.0", &p) / 1.0e31 - 1.0) < 1.0e-10);})) {
    failed ("Case 98: {char *p; (fabs (strtod (\"10000000000000000000000000000000.0\", &p) / 1.0e31 - 1.0) < 1.0e-10);}");
  }
  
  /* Case 99 */
  if (!({char *p; (fabs (strtod ("100000000000000000000000000000000.0", &p) / 1.0e32 - 1.0) < 1.0e-10);})) {
    failed ("Case 99: {char *p; (fabs (strtod (\"100000000000000000000000000000000.0\", &p) / 1.0e32 - 1.0) < 1.0e-10);}");
  }
  
  /* Case 100 */
  if (!({char *p; (fabs (strtod ("1000000000000000000000000000000000.0", &p) / 1.0e33 - 1.0) < 1.0e-10);})) {
    failed ("Case 100: {char *p; (fabs (strtod (\"1000000000000000000000000000000000.0\", &p) / 1.0e33 - 1.0) < 1.0e-10);}");
  }
  
  /* Case 101 */
  if (!({char *p; (fabs (strtod ("10000000000000000000000000000000000.0", &p) / 1.0e34 - 1.0) < 1.0e-10);})) {
    failed ("Case 101: {char *p; (fabs (strtod (\"10000000000000000000000000000000000.0\", &p) / 1.0e34 - 1.0) < 1.0e-10);}");
  }
  
  /* Case 102 */
  if (!({char *p; (fabs (strtod ("100000000000000000000000000000000000.0", &p) / 1.0e35 - 1.0) < 1.0e-10);})) {
    failed ("Case 102: {char *p; (fabs (strtod (\"100000000000000000000000000000000000.0\", &p) / 1.0e35 - 1.0) < 1.0e-10);}");
  }
  
  /* Case 103 */
  if (!({char *p; (fabs (strtod ("1000000000000000000000000000000000000.0", &p) / 1.0e36 - 1.0) < 1.0e-10);})) {
    failed ("Case 103: {char *p; (fabs (strtod (\"1000000000000000000000000000000000000.0\", &p) / 1.0e36 - 1.0) < 1.0e-10);}");
  }
  
  /* Case 104 */
  if (!({char *p; (fabs (strtod ("10000000000000000000000000000000000000.0", &p) / 1.0e37 - 1.0) < 1.0e-10);})) {
    failed ("Case 104: {char *p; (fabs (strtod (\"10000000000000000000000000000000000000.0\", &p) / 1.0e37 - 1.0) < 1.0e-10);}");
  }
  
  /* Case 105 */
  if (!({char *p; (fabs (strtod ("100000000000000000000000000000000000000.0", &p) / 1.0e38 - 1.0) < 1.0e-10);})) {
    failed ("Case 105: {char *p; (fabs (strtod (\"100000000000000000000000000000000000000.0\", &p) / 1.0e38 - 1.0) < 1.0e-10);}");
  }
  
}


void main ()
{
  test ("test-strtod", "Test for ANSI Standard C: 7.10.1.4");

  do_test ();

  result ();
}

