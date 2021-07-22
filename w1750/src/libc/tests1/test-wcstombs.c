/*
 * Test for ANSI Standard C: 7.10.8.2
 * 
 * #include <stdlib.h>
 * size_t wcstombs (char *s, const wchar_t *pwcs, size_t n);
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


static char *_test_wcstombs_id =
  "$Id$";

void do_test ()
{
  /* Case 1 */
  if (!({char s [10]; wcstombs (s, L"123", 3); s [0] == '1' && s [1] == '2' && s [2] == '3';})) {
    failed ("Case 1: {char s [10]; wcstombs (s, L\"123\", 3); s [0] == '1' && s [1] == '2' && s [2] == '3';}");
  }
  
}


void main ()
{
  test ("test-wcstombs", "Test for ANSI Standard C: 7.10.8.2");

  do_test ();

  result ();
}

