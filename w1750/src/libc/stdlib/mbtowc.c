/*
 * ANSI Standard C: 7.10.7.2
 * 
 * #include <stdlib.h>
 * int mbtowc (wchar_t *pwc, const char *s, size_t n);
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
 * $Log: mbtowc.c,v $
 * Revision 1.1  1997/05/09 16:55:41  nettleto
 * Initial revision
 *
 */

#include <stdlib.h>

/*
 * If s is not a null pointer, the mbtowc function determines the number 
 * of bytes in the multi-byte character pointed to by s. It then determines
 * the code for the value of type wchar-t that corresponds to the multibyte 
 * character. If the multibyte character is valid and pwc is not a null
 * pointer then mbtowc stores the code in the object pointed to be pwc. At
 * most n bytes of the array pointed to by s will be examined.
 *
 * If s is a null pointer, mbtowc returns a non-zero or zero value, if
 * multibyte character encodings respectively do or do not have state
 * dependent encodings. If s is not a null pointer, the mbtowc function
 * either returns zero (if s points to the null character), or returns
 * the number of bytes that are contained in the converted multibyte 
 * character (if the next n or fewer bytes for a valid multibyte 
 * character), or returns -1 (if they do not form a valid multibyte 
 * character). In no case will the vaslue returned by greater than n or
 * the value of the MB_CUR_MAX macro.
 */
int
mbtowc (wchar_t *pwc, const char *s, size_t n)
{
  if (s == NULL)
    return 0;

  if (n == 0)
    return -1;

  if (pwc)
    *pwc = (wchar_t) *s;

  return (*s != '\0');
}

