/*
 * ANSI Standard C: 7.10.8.2
 * 
 * #include <stdlib.h>
 * size_t wcstombs (char *s, const wchar_t *pwcs, size_t n);
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
 * $Log: wcstombs.c,v $
 * Revision 1.1  1997/05/09 16:55:44  nettleto
 * Initial revision
 *
 */

#include <stdlib.h>

size_t
wcstombs (char *s, const wchar_t *pwcs, size_t n)
{
  int count = 0;

  while (n-- > 0)
    {
      if ((*s++ = (char) *pwcs++) == 0)
        break;
      count++;
    }

  return count;
}

