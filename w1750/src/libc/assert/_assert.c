/*
 * _assert
 * 
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms are permitted 
 * provided that the above copyright notice and this paragraph are 
 * duplicated in all such forms and that any documentation, advertising 
 * materials, and other materials related to such distribution and use 
 * acknowledge that the software was developed by the University of 
 * California, Berkeley. The name of the University may not be used to 
 * endorse or promote products derived from this software without 
 * specific prior written permission. THIS SOFTWARE IS PROVIDED "AS IS" 
 * AND WITHOUT ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, WITHOUT 
 * LIMITATION, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR 
 * A PARTICULAR PURPOSE. 
 *
 * $Log: _assert.c,v $
 * Revision 1.1  1997/05/09 17:04:35  nettleto
 * Initial revision
 *
 */


/* 
 * This function, when passed a filename, and a line number, 
 * prints a message on the standard error stream of the form:
 *      a.c:10: (a == 2) Assertion failed
 * It then aborts program execution via a call to `abort'.
 */

void
_assert (const char *expr, const char *file, const int line) 
{
  printf ("%s:%u: (%s) Assertion failed\n", file, line, expr);

  abort ();
  /* NOTREACHED */
}

