/*
 * ANSI Standard C: 
 * 
 * #include <report.h>
 * void vprintf (const char *format, va_list ap);
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
 * $Log: vprintf.c,v $
 * Revision 1.1  1997/03/18 12:51:39  nettleto
 * Initial revision
 *
 */

#include <report.h>

#include <stdarg.h>

int
vprintf (const char *format, va_list ap)
{
  char buf [256];
  int ans;

  ans = vsprintf (buf, format, ap);
 
  write (1, buf, ans);
 
  return ans;
}

