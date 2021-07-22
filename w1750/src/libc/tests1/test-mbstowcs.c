/*
 * Test for ANSI Standard C: 7.10.8.1
 * 
 * #include <stdlib.h>
 * size_t mbstowcs (wchar_t *pwcs, const char *s, size_t n);
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


static char *_test_mbstowcs_id =
  "$Id$";

void do_test ()
{
  /* Case 1 */
  if (!({wchar_t w [10]; mbstowcs (w, "123", 3); w [0] == '1' && w [1] == '2' && w [2] == '3';})) {
    failed ("Case 1: {wchar_t w [10]; mbstowcs (w, \"123\", 3); w [0] == '1' && w [1] == '2' && w [2] == '3';}");
  }
  
}


void main ()
{
  test ("test-mbstowcs", "Test for ANSI Standard C: 7.10.8.1");

  do_test ();

  result ();
}

