/*
 * Test for ANSI Standard C: 7.12.3.5
 * 
 * #include <time.h>
 * size_t strftime (char *s, size_t maxsize, const char *format, const struct tm
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
 * $Log: test-strftime.c,v $
 * Revision 1.1  1997/08/01 16:05:39  nettleto
 * Initial revision
 *
 */

#include <report.h>

#include <time.h>


void main ()
{
  time_t systime;
  struct tm tmtime;
  char ftime1 [80];
  char ftime2 [80];
  int ans;

  test ("test-strftime", "Test for strftime");

  /* try the Epoch */
  systime = 0;
  tmtime = *localtime (&systime);

  ans = strftime (ftime1, sizeof ftime1, 
            "It is %H:%M on %A %B the %d, %Y", &tmtime);

  /* try August 1, 1997 */
  systime = 870451044L;
  tmtime = *localtime (&systime);

  ans = strftime (ftime2, sizeof ftime2, 
            "It is %H:%M on %A %B the %d, %Y", &tmtime);

  if (ans == 0)
    failed ("strftime returned zero");
  else if (strcmp (ftime1, "It is 00:00 on Thursday January the 01, 1970") != 0)
    failed ("ftime1 = \"%s\"", ftime1);
  else if (strcmp (ftime2, "It is 15:57 on Friday August the 01, 1997") != 0)
    failed ("ftime2 = \"%s\"", ftime2);
  else

  result ();
}


