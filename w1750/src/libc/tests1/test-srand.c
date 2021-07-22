/*
 * Test for ANSI Standard C: 7.10.2.2
 * 
 * #include <stdlib.h>
 * void srand (unsigned int seed);
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


static char *_test_srand_id =
  "$Id$";

void do_test ()
{
  /* Case 1 */
  if (!({int i = 1234; srand (i); (rand () != i);})) {
    failed ("Case 1: {int i = 1234; srand (i); (rand () != i);}");
  }
  
}


void main ()
{
  test ("test-srand", "Test for ANSI Standard C: 7.10.2.2");

  do_test ();

  result ();
}

