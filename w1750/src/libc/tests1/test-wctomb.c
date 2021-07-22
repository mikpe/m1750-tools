/*
 * Test for ANSI Standard C: 7.10.7.3
 * 
 * #include <stdlib.h>
 * int wctomb (char *s, wchar_t wchar);
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


static char *_test_wctomb_id =
  "$Id$";

void do_test ()
{
  /* Case 1 */
  if (!(wctomb (NULL, 0) == 0)) {
    failed ("Case 1: wctomb (NULL, 0) == 0");
  }
  
  /* Case 2 */
  if (!({char tmp [10]; wctomb (tmp, '0') == 1 && tmp [0] == '0';})) {
    failed ("Case 2: {char tmp [10]; wctomb (tmp, '0') == 1 && tmp [0] == '0';}");
  }
  
}


void main ()
{
  test ("test-wctomb", "Test for ANSI Standard C: 7.10.7.3");

  do_test ();

  result ();
}

