/*
 * ANSI Standard C: 7.11.5.8
 * 
 * #include <string.h>
 * char *strtok (char *s1, const char *s2);
 * 
 * Copyright (c) 1997, Chris Nettleton Software
 *
 * This file is part of the GCC-1750 library. It was developed under 
 * European Space Agency contract 11935/96/NL/JG. Permission to use 
 * copy, modify, and distribute this software for any purpose without 
 * fee is hereby granted, provided that this entire notice is included 
 * in all copies of any software which is or includes a copy or 
 * modification of this software and in all copies of the supporting 
 * documentation for such software. This software is provided "as is", 
 * without any express or implied warranty. In particular, neither the 
 * author nor the European Space Agency makes any representation or 
 * warranty of any kind concerning the merchantability of this software 
 * or its fitness for any particular purpose. 
 *
 * $Log: strtok.c,v $
 * Revision 1.1  1997/05/09 16:59:21  nettleto
 * Initial revision
 *
 */

#include <string.h>

char *
strtok (char *s1, const char *s2)
{
  char *spanp;
  int c, sc;
  char *tok;

  static char *lasts;

  if (s1 == NULL && (s1 = lasts) == NULL)
    return NULL;

  /*
   * Skip (span) leading delimiters (s += strspn(s, delim), sort of).
   */
cont:
  c = *s1++;
  for (spanp = (char *)s2; (sc = *spanp++) != 0;) {
    if (c == sc)
      goto cont;
  }

  if (c == 0) {    /* no non-delimiter characters */
    lasts = NULL;
    return NULL;
  }
  tok = s1 - 1;

  /*
   * Scan token (scan for delimiters: s += strcspn(s, delim), sort of).
   * Note that delim must have one NUL; we stop if we see that, too.
   */
  for (;;) {
    c = *s1++;
    spanp = (char *)s2;
    do {
      if ((sc = *spanp++) == c) {
        if (c == 0)
          s1 = NULL;
        else
          s1[-1] = 0;
        lasts = s1;
        return tok;
      }
    } while (sc != 0);
  }
  /* NOTREACHED */
}

