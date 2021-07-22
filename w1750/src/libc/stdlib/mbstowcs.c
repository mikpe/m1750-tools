/*
 * ANSI Standard C: 7.10.8.1
 * 
 * #include <stdlib.h>
 * size_t mbstowcs (wchar_t *pwcs, const char *s, size_t n);
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
 * $Log: mbstowcs.c,v $
 * Revision 1.1  1997/05/09 16:55:41  nettleto
 * Initial revision
 *
 */

#include <stdlib.h>

/*
 * The mbtowcs function converts a sequence of multibyte characters that
 * begin the initial shift state from the array pointed to by s into a
 * sequence of corresponding codes and stores not more than n codes into
 * the array pointed  to by pwcs. No multibyte characters that follow a
 * null character (which is  converted into a code with value zero) will
 * be examined or converted. Each multi byte character si converted as if
 * by a call to the mbtowc function, except the shift state of the mbtowc
 * function is not affected.
 * 
 * If an invalid multibyte character is encountered, the mbstowcs function
 * returns (size_t) -1. Otherewise the mbstowcs function returns the
 * number of array elements modified, not including a terminating zero
 * code, if any.
 */

size_t
mbstowcs (wchar_t *pwcs, const char *s, size_t n)
{
  int count = 0;

  if (n != 0) {
    do {
      if ((*pwcs++ = (wchar_t) *s++) == 0)
        break;
      count++;
    } while (--n != 0);
  }

  return count;
}

