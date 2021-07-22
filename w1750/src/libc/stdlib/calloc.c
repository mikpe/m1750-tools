/*
 * ANSI Standard C: 7.10.3.1
 * 
 * #include <stdlib.h>
 * void *calloc (size_t nmemb, size_t size);
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
 * $Log: calloc.c,v $
 * Revision 1.1  1997/05/09 16:55:38  nettleto
 * Initial revision
 *
 */

#include <stdlib.h>

void *calloc (size_t nmemb, size_t size)
{
  size_t n = nmemb * size;
  char *cp;

  cp = malloc (n);
  if (cp == NULL)
    return NULL;

  memset (cp, '\0', n);

  return cp;
}

