/*
 * sbrk
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
 * $Log: sbrk.c,v $
 * Revision 1.1  1997/07/17 18:48:26  nettleto
 * Initial revision
 *
 */

#include <stddef.h>
#include <errno.h>

extern unsigned char _end [];

#define stack_size 4096

void *
sbrk (unsigned nbytes)
{
  /*
   * Increments a program's data space by increment nbytes. On success
   * sbrk returns a pointer to the start of the new area. On error, -1
   * is returned, and errno is set appropriately.
   */
  static unsigned char *heap_ptr = _end;

  if (nbytes < 32768 && (unsigned long)(unsigned)heap_ptr + nbytes < (0xFFFFUL - stack_size))
    {
      void *base = (void *)heap_ptr;
      heap_ptr += nbytes;
      return base;
    }
  else 
    {
      errno = ENOMEM;
      return (void *)-1;
    }
}

