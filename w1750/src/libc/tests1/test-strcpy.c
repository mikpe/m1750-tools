/*
 * Test for ANSI Standard C: 7.11.2.3
 * 
 * #include <string.h>
 * void *strcpy (char *s1, const char *s2);
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

#include <string.h>


static char *_test_strcpy_id =
  "$Id$";

void do_test ()
{
  /* Case 1 */
  if (!({char tmp [10]; strcpy (tmp, "123456789"); (strcmp (tmp, "123456789") == 0);})) {
    failed ("Case 1: {char tmp [10]; strcpy (tmp, \"123456789\"); (strcmp (tmp, \"123456789\") == 0);}");
  }
  
}


void main ()
{
  test ("test-strcpy", "Test for ANSI Standard C: 7.11.2.3");

  do_test ();

  result ();
}

