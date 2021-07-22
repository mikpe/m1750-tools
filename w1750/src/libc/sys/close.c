/*
 * close
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
 * $Log: close.c,v $
 * Revision 1.1  1997/07/17 18:46:03  nettleto
 * Initial revision
 *
 */

#include <errno.h>

int 
close (int fd)
{
  /*
   * Closes a file descriptor so that it may be reused. Returns zero
   * if successful, otherwise returns -1, and errno is set appropriately.
   */

  /*
   * In this implementation, the only files are stdin, stdout, and stderr,
   * and none of these may be closed.
  */
  errno = ENODEV;
  return -1;
}

