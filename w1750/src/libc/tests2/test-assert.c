/*
 * Test for ANSI Standard C: 7.2 Diagnostics
 * 
 * #include <assert.h>
 * assert (expr);
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
 * $Log: test-assert.c,v $
 * Revision 1.1  1997/08/01 16:05:36  nettleto
 * Initial revision
 *
 */

#include <assert.h>

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

  test ("test-assert", "test for ANSI C macro assert");

  signal (SIGABRT, abort_handler);
  atexit (exit_handler);

  /* Now assert something that is false. This should result in
     a call of 'abort' followed by a call of 'exit' */
  assert (x < 99);

  exit (0);
}

