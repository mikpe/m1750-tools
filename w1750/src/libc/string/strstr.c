/*
 * ANSI Standard C: 7.11.5.7
 * 
 * #include <string.h>
 * char *strstr (char *s1, const char *s2);
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
 * $Log: strstr.c,v $
 * Revision 1.1  1997/05/09 16:59:21  nettleto
 * Initial revision
 *
 */

#include <string.h>

char *
strstr (const char *s1, const char *s2)
{
  if (*s1 == 0)
    {
      if (*s2)
	return (char *) NULL;
      return (char *) s1;
    }

  while (*s1)
    {
      size_t i = 0;

      while (1)
	{
	  if (s2 [i] == 0)
            return (char *) s1;

	  if (s2 [i] != s1 [i])
            break;

	  i++;
	}
      s1++;
    }

  return (char *) NULL;
}

