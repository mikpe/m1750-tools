/*
 * Test for ANSI Standard C: 7.11.4.5
 * 
 * #include <string.h>
 * size_t strxfrm (char *s1, const char *s2, size_t n);
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
 * $Log: test-strxfrm.c,v $
 * Revision 1.1  1997/08/01 16:05:40  nettleto
 * Initial revision
 *
 */

#include <report.h>

#include <string.h>


int
t1 ()
{
  char s1 [100];
  char s2 [100];
  int ans;

  strcpy (s1, "qwertyuiop");
  strcpy (s2, "asdfghjkl");
  ans = strxfrm (s1, s2, 0);

  if (ans != 9)
    failed ("t1, ans = %d", ans);

  if (strcmp (s1, "qwertyuiop") != 0)
    failed ("t1, s1 = %s", s1);
}

int
t2 ()
{
  char s1 [100];
  char s2 [100];
  int ans;

  strcpy (s1, "qwertyuiop");
  strcpy (s2, "asdfg");
  ans = strxfrm (s1, s2, 10);

  if (ans != 5)
    failed ("t2, ans = %d", ans);

  if (strcmp (s1, "asdfgyuiop") != 0)
    failed ("t2, s1 = %s", s1);
}

int
t3 ()
{
  char s1 [100];
  char s2 [100];
  int ans;

  strcpy (s1, "qwertyuiop");
  strcpy (s2, "asdfghjkl");
  ans = strxfrm (s1, s2, 5);

  if (ans != 9)
    failed ("t3, ans = %d", ans);

  if (strcmp (s1, "asdfgyuiop") != 0)
    failed ("t3, s1 = %s", s1);
}

int
t4 ()
{
  char s1 [100];
  char s2 [100];
  int ans;

  strcpy (s1, "qwertyuiop");
  strcpy (s2, "asdfghjkl;");
  ans = strxfrm (s1, s2, 10);

  if (ans != 10)
    failed ("t4, ans = %d", ans);

  if (strcmp (s1, "asdfghjkl;") != 0)
    failed ("t4, s1 = %s", s1);
}


int
main ()
{
  test ("test-strxfrm", "Test for ANSI C Section 7.11.4.5"); 

  t1 ();
  t2 ();
  t3 ();
  t4 ();

  result ();
}

