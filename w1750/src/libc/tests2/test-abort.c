/*
 * Test for ANSI Standard C: 7.10.4.1
 * 
 * #include <stdlib.h>
 * abort ();
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
 * $Log: test-abort.c,v $
 * Revision 1.1  1997/08/04 14:18:34  nettleto
 * Initial revision
 *
 */

#include <stdlib.h>

#include <report.h>
#include <signal.h>

volatile static int abort_handler_called = 0;


void
abort_handler (int s)
{
  abort_handler_called = 1;
}


void
exit_handler ()
{
  if (abort_handler_called == 0)
    failed ("abort handler not called");

  result ();
}


int
main ()
{
  int x = 100;

  test ("test-abort", "Test for ANSI Standard C: 7.10.4.1");

  signal (SIGABRT, abort_handler);
  atexit (exit_handler);

  abort ();

  exit (0);
}

