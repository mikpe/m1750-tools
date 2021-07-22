/*
 * Test for ANSI Standard C: 7.10.4.3
 * 
 * #include <stdlib.h>
 * void exit (int status);
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


static char *_test_exit_id =
  "$Id$";

void do_test ()
{
  /* Case 1 */
  if (!({exit (0); 0;})) {
    failed ("Case 1: {exit (0); 0;}");
  }
  
}


void main ()
{
  test ("test-exit", "Test for ANSI Standard C: 7.10.4.3");

  do_test ();

  result ();
}

