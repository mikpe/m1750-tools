/*
 * Test for ANSI Standard C: 7.10.6.1
 * 
 * #include <stdlib.h>
 * int abs (int);
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


static char *_test_abs_id =
  "$Id$";

void do_test ()
{
  /* Case 1 */
  if (!(abs (0) == 0)) {
    failed ("Case 1: abs (0) == 0");
  }
  
  /* Case 2 */
  if (!(abs (1) == 1)) {
    failed ("Case 2: abs (1) == 1");
  }
  
  /* Case 3 */
  if (!(abs (-1) == 1)) {
    failed ("Case 3: abs (-1) == 1");
  }
  
  /* Case 4 */
  if (!(abs (32767) == 32767)) {
    failed ("Case 4: abs (32767) == 32767");
  }
  
  /* Case 5 */
  if (!(abs (-32767) == 32767)) {
    failed ("Case 5: abs (-32767) == 32767");
  }
  
  /* Case 6 */
  if (!(abs (-32768) == -32768)) {
    failed ("Case 6: abs (-32768) == -32768");
  }
  
}


void main ()
{
  test ("test-abs", "Test for ANSI Standard C: 7.10.6.1");

  do_test ();

  result ();
}

