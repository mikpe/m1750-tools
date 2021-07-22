/*
 * open
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
 * $Log: open.c,v $
 * Revision 1.1  1997/07/17 18:48:02  nettleto
 * Initial revision
 *
 */

#include <errno.h>

int 
open (const char *pathname, int flags)
{
  /*
   * Attempts to open a file and return a file descriptor (a small
   * non-negative integer for use in read, write etc). In this
   * implementation the only files supported are already open by default,
   * so open simply returns -1, and errno is set appropriately.
   */

  errno = ENODEV;
  return -1;
}

