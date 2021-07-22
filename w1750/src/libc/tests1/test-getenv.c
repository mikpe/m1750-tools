/*
 * Test for ANSI Standard C: 7.10.4.4
 * 
 * #include <stdlib.h>
 * char *getenv (char *name);
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


static char *_test_getenv_id =
  "$Id$";

void do_test ()
{
  /* Case 1 */
  if (!(getenv ("") == NULL)) {
    failed ("Case 1: getenv (\"\") == NULL");
  }
  
  /* Case 2 */
  if (!(getenv ("a") == NULL)) {
    failed ("Case 2: getenv (\"a\") == NULL");
  }
  
  /* Case 3 */
  if (!(getenv ("abc") == NULL)) {
    failed ("Case 3: getenv (\"abc\") == NULL");
  }
  
  /* Case 4 */
  if (!(getenv ("path") == NULL)) {
    failed ("Case 4: getenv (\"path\") == NULL");
  }
  
  /* Case 5 */
  if (!(getenv ("target") == NULL)) {
    failed ("Case 5: getenv (\"target\") == NULL");
  }
  
  /* Case 6 */
  if (!(getenv ("date") != NULL)) {
    failed ("Case 6: getenv (\"date\") != NULL");
  }
  
}


void main ()
{
  test ("test-getenv", "Test for ANSI Standard C: 7.10.4.4");

  do_test ();

  result ();
}

