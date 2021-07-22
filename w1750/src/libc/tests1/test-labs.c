/*
 * Test for ANSI Standard C: 7.10.6.3
 * 
 * #include <stdlib.h>
 * long labs (long);
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


static char *_test_labs_id =
  "$Id$";

void do_test ()
{
  /* Case 1 */
  if (!(labs (0) == 0)) {
    failed ("Case 1: labs (0) == 0");
  }
  
  /* Case 2 */
  if (!(labs (1) == 1)) {
    failed ("Case 2: labs (1) == 1");
  }
  
  /* Case 3 */
  if (!(labs (-1) == 1)) {
    failed ("Case 3: labs (-1) == 1");
  }
  
  /* Case 4 */
  if (!(labs (2147483647) == 2147483647)) {
    failed ("Case 4: labs (2147483647) == 2147483647");
  }
  
  /* Case 5 */
  if (!(labs (-2147483647) == 2147483647)) {
    failed ("Case 5: labs (-2147483647) == 2147483647");
  }
  
  /* Case 6 */
  if (!(labs (0x80000000L) == 0x80000000L)) {
    failed ("Case 6: labs (-2147483648) == -2147483648");
  }
  
}


void main ()
{
  test ("test-labs", "Test for ANSI Standard C: 7.10.6.3");

  do_test ();

  result ();
}

