/*
 * Test for ANSI Standard C: 7.10.4.5
 * 
 * #include <stdlib.h>
 * int system (const char *string);
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


static char *_test_system_id =
  "$Id$";

void do_test ()
{
  /* Case 1 */
  if (!(system (NULL) == 0)) {
    failed ("Case 1: system (NULL) == 0");
  }
  
  /* Case 2 */
  if (!(system ("") == -1)) {
    failed ("Case 2: system (\"\") == -1");
  }
  
  /* Case 3 */
  if (!(system ("z") == -1)) {
    failed ("Case 3: system (\"z\") == -1");
  }
  
  /* Case 4 */
  if (!(system ("zz") == -1)) {
    failed ("Case 4: system (\"zz\") == -1");
  }
  
}


void main ()
{
  test ("test-system", "Test for ANSI Standard C: 7.10.4.5");

  do_test ();

  result ();
}

