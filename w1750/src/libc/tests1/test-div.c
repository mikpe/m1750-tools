/*
 * Test for ANSI Standard C: 7.10.6.2
 * 
 * #include <stdlib.h>
 * div_t div (int _numer, int _denom);
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


static char *_test_div_id =
  "$Id$";

void do_test ()
{
  /* Case 1 */
  if (!({div_t d = div (1, 1); (d.quot == 1 && d.rem == 0);})) {
    failed ("Case 1: {div_t d = div (1, 1); (d.quot == 1 && d.rem == 0);}");
  }
  
  /* Case 2 */
  if (!({div_t d = div (-1, 1); (d.quot == -1 && d.rem == 0);})) {
    failed ("Case 2: {div_t d = div (-1, 1); (d.quot == -1 && d.rem == 0);}");
  }
  
  /* Case 3 */
  if (!({div_t d = div (1, -1); (d.quot == -1 && d.rem == 0);})) {
    failed ("Case 3: {div_t d = div (1, -1); (d.quot == -1 && d.rem == 0);}");
  }
  
  /* Case 4 */
  if (!({div_t d = div (-1, -1); (d.quot == 1 && d.rem == 0);})) {
    failed ("Case 4: {div_t d = div (-1, -1); (d.quot == 1 && d.rem == 0);}");
  }
  
  /* Case 5 */
  if (!({div_t d = div (10, 5); (d.quot == 2 && d.rem == 0);})) {
    failed ("Case 5: {div_t d = div (10, 5); (d.quot == 2 && d.rem == 0);}");
  }
  
  /* Case 6 */
  if (!({div_t d = div (11, 5); (d.quot == 2 && d.rem == 1);})) {
    failed ("Case 6: {div_t d = div (11, 5); (d.quot == 2 && d.rem == 1);}");
  }
  
  /* Case 7 */
  if (!({div_t d = div (12, 5); (d.quot == 2 && d.rem == 2);})) {
    failed ("Case 7: {div_t d = div (12, 5); (d.quot == 2 && d.rem == 2);}");
  }
  
  /* Case 8 */
  if (!({div_t d = div (13, 5); (d.quot == 2 && d.rem == 3);})) {
    failed ("Case 8: {div_t d = div (13, 5); (d.quot == 2 && d.rem == 3);}");
  }
  
  /* Case 9 */
  if (!({div_t d = div (14, 5); (d.quot == 2 && d.rem == 4);})) {
    failed ("Case 9: {div_t d = div (14, 5); (d.quot == 2 && d.rem == 4);}");
  }
  
  /* Case 10 */
  if (!({div_t d = div (15, 5); (d.quot == 3 && d.rem == 0);})) {
    failed ("Case 10: {div_t d = div (15, 5); (d.quot == 3 && d.rem == 0);}");
  }
  
  /* Case 11 */
  if (!({div_t d = div (-10, 5); (d.quot == -2 && d.rem == 0);})) {
    failed ("Case 11: {div_t d = div (-10, 5); (d.quot == -2 && d.rem == 0);}");
  }
  
  /* Case 12 */
  if (!({div_t d = div (-11, 5); (d.quot == -2 && d.rem == -1);})) {
    failed ("Case 12: {div_t d = div (-11, 5); (d.quot == -2 && d.rem == -1);}");
  }
  
  /* Case 13 */
  if (!({div_t d = div (-12, 5); (d.quot == -2 && d.rem == -2);})) {
    failed ("Case 13: {div_t d = div (-12, 5); (d.quot == -2 && d.rem == -2);}");
  }
  
  /* Case 14 */
  if (!({div_t d = div (-13, 5); (d.quot == -2 && d.rem == -3);})) {
    failed ("Case 14: {div_t d = div (-13, 5); (d.quot == -2 && d.rem == -3);}");
  }
  
  /* Case 15 */
  if (!({div_t d = div (-14, 5); (d.quot == -2 && d.rem == -4);})) {
    failed ("Case 15: {div_t d = div (-14, 5); (d.quot == -2 && d.rem == -4);}");
  }
  
  /* Case 16 */
  if (!({div_t d = div (-15, 5); (d.quot == -3 && d.rem == 0);})) {
    failed ("Case 16: {div_t d = div (-15, 5); (d.quot == -3 && d.rem == 0);}");
  }
  
  /* Case 17 */
  if (!({div_t d = div (10, -5); (d.quot == -2 && d.rem == 0);})) {
    failed ("Case 17: {div_t d = div (10, -5); (d.quot == -2 && d.rem == 0);}");
  }
  
  /* Case 18 */
  if (!({div_t d = div (11, -5); (d.quot == -2 && d.rem == 1);})) {
    failed ("Case 18: {div_t d = div (11, -5); (d.quot == -2 && d.rem == 1);}");
  }
  
  /* Case 19 */
  if (!({div_t d = div (12, -5); (d.quot == -2 && d.rem == 2);})) {
    failed ("Case 19: {div_t d = div (12, -5); (d.quot == -2 && d.rem == 2);}");
  }
  
  /* Case 20 */
  if (!({div_t d = div (13, -5); (d.quot == -2 && d.rem == 3);})) {
    failed ("Case 20: {div_t d = div (13, -5); (d.quot == -2 && d.rem == 3);}");
  }
  
  /* Case 21 */
  if (!({div_t d = div (14, -5); (d.quot == -2 && d.rem == 4);})) {
    failed ("Case 21: {div_t d = div (14, -5); (d.quot == -2 && d.rem == 4);}");
  }
  
  /* Case 22 */
  if (!({div_t d = div (15, -5); (d.quot == -3 && d.rem == 0);})) {
    failed ("Case 22: {div_t d = div (15, -5); (d.quot == -3 && d.rem == 0);}");
  }
  
  /* Case 23 */
  if (!({div_t d = div (-10, -5); (d.quot == 2 && d.rem == 0);})) {
    failed ("Case 23: {div_t d = div (-10, -5); (d.quot == 2 && d.rem == 0);}");
  }
  
  /* Case 24 */
  if (!({div_t d = div (-11, -5); (d.quot == 2 && d.rem == -1);})) {
    failed ("Case 24: {div_t d = div (-11, -5); (d.quot == 2 && d.rem == -1);}");
  }
  
  /* Case 25 */
  if (!({div_t d = div (-12, -5); (d.quot == 2 && d.rem == -2);})) {
    failed ("Case 25: {div_t d = div (-12, -5); (d.quot == 2 && d.rem == -2);}");
  }
  
  /* Case 26 */
  if (!({div_t d = div (-13, -5); (d.quot == 2 && d.rem == -3);})) {
    failed ("Case 26: {div_t d = div (-13, -5); (d.quot == 2 && d.rem == -3);}");
  }
  
  /* Case 27 */
  if (!({div_t d = div (-14, -5); (d.quot == 2 && d.rem == -4);})) {
    failed ("Case 27: {div_t d = div (-14, -5); (d.quot == 2 && d.rem == -4);}");
  }
  
  /* Case 28 */
  if (!({div_t d = div (-15, -5); (d.quot == 3 && d.rem == 0);})) {
    failed ("Case 28: {div_t d = div (-15, -5); (d.quot == 3 && d.rem == 0);}");
  }
  
}


void main ()
{
  test ("test-div", "Test for ANSI Standard C: 7.10.6.2");

  do_test ();

  result ();
}

