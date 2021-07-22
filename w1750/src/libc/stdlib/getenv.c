/*
 * ANSI Standard C: 7.10.4.4
 * 
 * #include <stdlib.h>
 * char *getenv (char *name);
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
 * $Log: getenv.c,v $
 * Revision 1.2  1997/07/17 18:53:35  nettleto
 * Changed **environ to *environ [].
 *
 * Revision 1.1  1997/05/09 16:55:39  nettleto
 * Initial revision
 *
 */

#include <stdlib.h>

#include <string.h>

extern char *environ [];

char *
getenv (const char *name)
{
  int len;
  char **p;
  const char *c;

  c = name;
  len = 0;
  while (*c && *c != '=')
    {
      c++;
      len++;
    }

  for (p = environ; *p; ++p)
    if (strncmp (*p, name, len) == 0)
      if (*(c = *p + len) == '=')
	{
	  return (char *) (++c);
	}

  return NULL;
}

