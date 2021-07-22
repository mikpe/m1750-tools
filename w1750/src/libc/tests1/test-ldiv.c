/*
 * Test for ANSI Standard C: 7.10.6.4
 * 
 * #include <stdlib.h>
 * ldiv_t ldiv (long _numer, long _denom);
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


static char *_test_ldiv_id =
  "$Id$";

void do_test ()
{
  /* Case 1 */
  if (!({ldiv_t d = ldiv (1, 1); (d.quot == 1 && d.rem == 0);})) {
    failed ("Case 1: {ldiv_t d = ldiv (1, 1); (d.quot == 1 && d.rem == 0);}");
  }
  
  /* Case 2 */
  if (!({ldiv_t d = ldiv (-1, 1); (d.quot == -1 && d.rem == 0);})) {
    failed ("Case 2: {ldiv_t d = ldiv (-1, 1); (d.quot == -1 && d.rem == 0);}");
  }
  
  /* Case 3 */
  if (!({ldiv_t d = ldiv (1, -1); (d.quot == -1 && d.rem == 0);})) {
    failed ("Case 3: {ldiv_t d = ldiv (1, -1); (d.quot == -1 && d.rem == 0);}");
  }
  
  /* Case 4 */
  if (!({ldiv_t d = ldiv (-1, -1); (d.quot == 1 && d.rem == 0);})) {
    failed ("Case 4: {ldiv_t d = ldiv (-1, -1); (d.quot == 1 && d.rem == 0);}");
  }
  
  /* Case 5 */
  if (!({ldiv_t d = ldiv (10, 5); (d.quot == 2 && d.rem == 0);})) {
    failed ("Case 5: {ldiv_t d = ldiv (10, 5); (d.quot == 2 && d.rem == 0);}");
  }
  
  /* Case 6 */
  if (!({ldiv_t d = ldiv (11, 5); (d.quot == 2 && d.rem == 1);})) {
    failed ("Case 6: {ldiv_t d = ldiv (11, 5); (d.quot == 2 && d.rem == 1);}");
  }
  
  /* Case 7 */
  if (!({ldiv_t d = ldiv (12, 5); (d.quot == 2 && d.rem == 2);})) {
    failed ("Case 7: {ldiv_t d = ldiv (12, 5); (d.quot == 2 && d.rem == 2);}");
  }
  
  /* Case 8 */
  if (!({ldiv_t d = ldiv (13, 5); (d.quot == 2 && d.rem == 3);})) {
    failed ("Case 8: {ldiv_t d = ldiv (13, 5); (d.quot == 2 && d.rem == 3);}");
  }
  
  /* Case 9 */
  if (!({ldiv_t d = ldiv (14, 5); (d.quot == 2 && d.rem == 4);})) {
    failed ("Case 9: {ldiv_t d = ldiv (14, 5); (d.quot == 2 && d.rem == 4);}");
  }
  
  /* Case 10 */
  if (!({ldiv_t d = ldiv (15, 5); (d.quot == 3 && d.rem == 0);})) {
    failed ("Case 10: {ldiv_t d = ldiv (15, 5); (d.quot == 3 && d.rem == 0);}");
  }
  
  /* Case 11 */
  if (!({ldiv_t d = ldiv (-10, 5); (d.quot == -2 && d.rem == 0);})) {
    failed ("Case 11: {ldiv_t d = ldiv (-10, 5); (d.quot == -2 && d.rem == 0);}");
  }
  
  /* Case 12 */
  if (!({ldiv_t d = ldiv (-11, 5); (d.quot == -2 && d.rem == -1);})) {
    failed ("Case 12: {ldiv_t d = ldiv (-11, 5); (d.quot == -2 && d.rem == -1);}");
  }
  
  /* Case 13 */
  if (!({ldiv_t d = ldiv (-12, 5); (d.quot == -2 && d.rem == -2);})) {
    failed ("Case 13: {ldiv_t d = ldiv (-12, 5); (d.quot == -2 && d.rem == -2);}");
  }
  
  /* Case 14 */
  if (!({ldiv_t d = ldiv (-13, 5); (d.quot == -2 && d.rem == -3);})) {
    failed ("Case 14: {ldiv_t d = ldiv (-13, 5); (d.quot == -2 && d.rem == -3);}");
  }
  
  /* Case 15 */
  if (!({ldiv_t d = ldiv (-14, 5); (d.quot == -2 && d.rem == -4);})) {
    failed ("Case 15: {ldiv_t d = ldiv (-14, 5); (d.quot == -2 && d.rem == -4);}");
  }
  
  /* Case 16 */
  if (!({ldiv_t d = ldiv (-15, 5); (d.quot == -3 && d.rem == 0);})) {
    failed ("Case 16: {ldiv_t d = ldiv (-15, 5); (d.quot == -3 && d.rem == 0);}");
  }
  
  /* Case 17 */
  if (!({ldiv_t d = ldiv (10, -5); (d.quot == -2 && d.rem == 0);})) {
    failed ("Case 17: {ldiv_t d = ldiv (10, -5); (d.quot == -2 && d.rem == 0);}");
  }
  
  /* Case 18 */
  if (!({ldiv_t d = ldiv (11, -5); (d.quot == -2 && d.rem == 1);})) {
    failed ("Case 18: {ldiv_t d = ldiv (11, -5); (d.quot == -2 && d.rem == 1);}");
  }
  
  /* Case 19 */
  if (!({ldiv_t d = ldiv (12, -5); (d.quot == -2 && d.rem == 2);})) {
    failed ("Case 19: {ldiv_t d = ldiv (12, -5); (d.quot == -2 && d.rem == 2);}");
  }
  
  /* Case 20 */
  if (!({ldiv_t d = ldiv (13, -5); (d.quot == -2 && d.rem == 3);})) {
    failed ("Case 20: {ldiv_t d = ldiv (13, -5); (d.quot == -2 && d.rem == 3);}");
  }
  
  /* Case 21 */
  if (!({ldiv_t d = ldiv (14, -5); (d.quot == -2 && d.rem == 4);})) {
    failed ("Case 21: {ldiv_t d = ldiv (14, -5); (d.quot == -2 && d.rem == 4);}");
  }
  
  /* Case 22 */
  if (!({ldiv_t d = ldiv (15, -5); (d.quot == -3 && d.rem == 0);})) {
    failed ("Case 22: {ldiv_t d = ldiv (15, -5); (d.quot == -3 && d.rem == 0);}");
  }
  
  /* Case 23 */
  if (!({ldiv_t d = ldiv (-10, -5); (d.quot == 2 && d.rem == 0);})) {
    failed ("Case 23: {ldiv_t d = ldiv (-10, -5); (d.quot == 2 && d.rem == 0);}");
  }
  
  /* Case 24 */
  if (!({ldiv_t d = ldiv (-11, -5); (d.quot == 2 && d.rem == -1);})) {
    failed ("Case 24: {ldiv_t d = ldiv (-11, -5); (d.quot == 2 && d.rem == -1);}");
  }
  
  /* Case 25 */
  if (!({ldiv_t d = ldiv (-12, -5); (d.quot == 2 && d.rem == -2);})) {
    failed ("Case 25: {ldiv_t d = ldiv (-12, -5); (d.quot == 2 && d.rem == -2);}");
  }
  
  /* Case 26 */
  if (!({ldiv_t d = ldiv (-13, -5); (d.quot == 2 && d.rem == -3);})) {
    failed ("Case 26: {ldiv_t d = ldiv (-13, -5); (d.quot == 2 && d.rem == -3);}");
  }
  
  /* Case 27 */
  if (!({ldiv_t d = ldiv (-14, -5); (d.quot == 2 && d.rem == -4);})) {
    failed ("Case 27: {ldiv_t d = ldiv (-14, -5); (d.quot == 2 && d.rem == -4);}");
  }
  
  /* Case 28 */
  if (!({ldiv_t d = ldiv (-15, -5); (d.quot == 3 && d.rem == 0);})) {
    failed ("Case 28: {ldiv_t d = ldiv (-15, -5); (d.quot == 3 && d.rem == 0);}");
  }
  
}


void main ()
{
  test ("test-ldiv", "Test for ANSI Standard C: 7.10.6.4");

  do_test ();

  result ();
}

