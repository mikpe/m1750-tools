/*
 * ANSI Standard C: 7.11.2.2
 * 
 * #include <string.h>
 * void *memmove (void *s1, void *s2, size_t n);
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
 * $Log: memmove.c,v $
 * Revision 1.1  1997/05/09 16:59:17  nettleto
 * Initial revision
 *
 */

#include <string.h>

void *
memmove (void *s1, const void *s2, size_t n)
{
  char *dst = s1;
  const char *src = s2;

  if (src < dst && dst < src + n)
    {
      /* Have to copy backwards */
      src += n;
      dst += n;
      while (n--)
	{
	  *--dst = *--src;
	}
    }
  else
    {
      while (n--)
	{
	  *dst++ = *src++;
	}
    }

  return s1;
}

