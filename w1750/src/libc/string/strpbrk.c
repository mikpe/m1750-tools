/*
 * ANSI Standard C: 7.11.5.4
 * 
 * #include <string.h>
 * size_t strpbrk (char *s1, char *s2);
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
 * $Log: strpbrk.c,v $
 * Revision 1.1  1997/05/09 16:59:20  nettleto
 * Initial revision
 *
 */

#include <string.h>

char *
strpbrk (const char *s1, const char *s2)
{
  const char *c = s2;

  if (!*s1)
    return (char *) NULL;

  while (*s1)
    {
      for (c = s2; *c; c++)
	{
	  if (*s1 == *c)
	    break;
	}
      if (*c)
	break;
      s1++;
    }

  if (*c == '\0')
    s1 = NULL;

  return (char *) s1;
}

