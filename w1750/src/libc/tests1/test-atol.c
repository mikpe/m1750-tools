/*
 * Test for ANSI Standard C: 7.10.1.3
 * 
 * #include <stdlib.h>
 * long atol (const char *nptr);
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


static char *_test_atol_id =
  "$Id$";

void do_test ()
{
  /* Case 1 */
  if (!(atol ("0") == 0)) {
    failed ("Case 1: atol (\"0\") == 0");
  }
  
  /* Case 2 */
  if (!(atol ("1") == 1)) {
    failed ("Case 2: atol (\"1\") == 1");
  }
  
  /* Case 3 */
  if (!(atol ("-1") == -1)) {
    failed ("Case 3: atol (\"-1\") == -1");
  }
  
  /* Case 4 */
  if (!(atol (" 0") == 0)) {
    failed ("Case 4: atol (\" 0\") == 0");
  }
  
  /* Case 5 */
  if (!(atol ("   1") == 1)) {
    failed ("Case 5: atol (\"   1\") == 1");
  }
  
  /* Case 6 */
  if (!(atol ("   +1") == 1)) {
    failed ("Case 6: atol (\"   +1\") == 1");
  }
  
  /* Case 7 */
  if (!(atol ("   -1") == -1)) {
    failed ("Case 7: atol (\"   -1\") == -1");
  }
  
  /* Case 8 */
  if (!(atol ("1234") == 1234)) {
    failed ("Case 8: atol (\"1234\") == 1234");
  }
  
  /* Case 9 */
  if (!(atol ("-1234") == -1234)) {
    failed ("Case 9: atol (\"-1234\") == -1234");
  }
  
  /* Case 10 */
  if (!(atol ("2147483647") == 2147483647L)) {
    failed ("Case 10: atol (\"2147483647\") == 2147483647L");
  }
  
  /* Case 11 */
  if (!(atol ("-2147483647") == -2147483647L)) {
    failed ("Case 11: atol (\"-2147483647\") == -2147483647L");
  }
  
  /* Case 12 */
  if (!(atol ("-2147483648") == 0x80000000L)) {
    failed ("Case 12: atol (\"-2147483648\") == 0x80000000L");
  }
  
}


void main ()
{
  test ("test-atol", "Test for ANSI Standard C: 7.10.1.3");

  do_test ();

  result ();
}

