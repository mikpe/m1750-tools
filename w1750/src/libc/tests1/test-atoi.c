/*
 * Test for ANSI Standard C: 7.10.1.2
 * 
 * #include <stdlib.h>
 * int atoi (const char *nptr);
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


static char *_test_atoi_id =
  "$Id$";

void do_test ()
{
  /* Case 1 */
  if (!(atoi ("0") == 0)) {
    failed ("Case 1: atoi (\"0\") == 0");
  }
  
  /* Case 2 */
  if (!(atoi ("1") == 1)) {
    failed ("Case 2: atoi (\"1\") == 1");
  }
  
  /* Case 3 */
  if (!(atoi ("-1") == -1)) {
    failed ("Case 3: atoi (\"-1\") == -1");
  }
  
  /* Case 4 */
  if (!(atoi (" 0") == 0)) {
    failed ("Case 4: atoi (\" 0\") == 0");
  }
  
  /* Case 5 */
  if (!(atoi ("   1") == 1)) {
    failed ("Case 5: atoi (\"   1\") == 1");
  }
  
  /* Case 6 */
  if (!(atoi ("   +1") == 1)) {
    failed ("Case 6: atoi (\"   +1\") == 1");
  }
  
  /* Case 7 */
  if (!(atoi ("   -1") == -1)) {
    failed ("Case 7: atoi (\"   -1\") == -1");
  }
  
  /* Case 8 */
  if (!(atoi ("1234") == 1234)) {
    failed ("Case 8: atoi (\"1234\") == 1234");
  }
  
  /* Case 9 */
  if (!(atoi ("-1234") == -1234)) {
    failed ("Case 9: atoi (\"-1234\") == -1234");
  }
  
  /* Case 10 */
  if (!(atoi ("32767") == 32767)) {
    failed ("Case 10: atoi (\"32767\") == 32767");
  }
  
  /* Case 11 */
  if (!(atoi ("-32767") == -32767)) {
    failed ("Case 11: atoi (\"-32767\") == -32767");
  }
  
  /* Case 12 */
  if (!(atoi ("-32768") == -32768)) {
    failed ("Case 12: atoi (\"-32768\") == -32768");
  }
  
}


void main ()
{
  test ("test-atoi", "Test for ANSI Standard C: 7.10.1.2");

  do_test ();

  result ();
}

