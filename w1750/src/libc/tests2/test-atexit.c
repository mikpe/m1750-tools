/*
 * Test for ANSI Standard C: 7.10.4.2
 * 
 * #include <stdlib.h>
 * void atexit (void (*func)(void));
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
 * $Log: test-atexit.c,v $
 * Revision 1.1  1997/08/01 16:05:37  nettleto
 * Initial revision
 *
 */

#include <report.h>

#include <stdlib.h>


static int cnt = 0;

void
e1 ()
{
  comment ("function e1");
  cnt++;
}

void
e2 ()
{
  comment ("function e2");
  cnt++;
}


void
e3 ()
{
  if (cnt != 2)
    failed ("cnt = %d, expected cnt = 2 ", cnt);

  result ();
}


int
main ()
{
  test ("test-atexit", "Test for ANSI Standard C 7.10.4.2");

  atexit (e3);
  atexit (e2);
  atexit (e1);

  exit(0);
}


