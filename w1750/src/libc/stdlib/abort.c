/*
 * ANSI Standard C: 7.10.4.1
 * 
 * #include <stdlib.h>
 * void abort (void);
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
 * $Log: abort.c,v $
 * Revision 1.2  1997/07/17 18:55:13  nettleto
 * Removed loop.
 *
 * Revision 1.1  1997/05/09 16:55:32  nettleto
 * Initial revision
 *
 */

#include <stdlib.h>

#include <signal.h>

void 
abort (void)
{
  raise (SIGABRT);
  exit (1);
}

