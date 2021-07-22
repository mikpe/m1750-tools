/*
 * ANSI Standard C: 7.10.5.1
 * 
 * #include <stdlib.h>
 * void *bsearch (const void * _key, const void * _base, size_t _nmemb, size_t _size, int (*_compar) (const void *, const void *));
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
 * $Log: bsearch.c,v $
 * Revision 1.1  1997/05/09 16:55:37  nettleto
 * Initial revision
 *
 */

#include <stdlib.h>

/*
 * Original Author: G. Haley
 * 
 * Searches an array of nmemb members, the initial member of which is
 * pointed to by base, for a member that matches the object pointed to by
 * key. The contents of the array shall be in ascending order according to
 * a comparison function pointed to by compar. The function shall return
 * an integer less than, equal to or greater than zero if the first
 * argument is considered to be respectively less than, equal to or
 * greater than the second. Returns a pointer to the matching member of
 * the array, or a null pointer if no match is found.
 */

void *
bsearch (const void *key, const void *base,
  size_t nmemb, size_t size,
  int (*compar)(const void *, const void *))
{
  void *current;
  int result;

  if (nmemb == 0 || size == 0)
    return NULL;

  while (nmemb) 
    {
      current = (void *) (((char *) base) + ((nmemb / 2) * size));
      result = compar (key, current);

      if (result < 0)
        nmemb /= 2;
      else if (result > 0) 
        {
          base = (void *) (((char *) current) + size);
          nmemb = (nmemb / 2) - (nmemb % 2 ? 0 : 1);
        }
      else
  	return current;
    } 

  if (compar (key, base) == 0)
    return (void *) base;

  return NULL;
}

