/*
 * Test for ANSI Standard C: 7.11.5.8
 * 
 * #include <string.h>
 * char *strtok (char *s1, const char *s2);
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
 * $Log: test-strtok.c,v $
 * Revision 1.1  1997/08/01 16:05:39  nettleto
 * Initial revision
 *
 */

#include <report.h>

#include <string.h>


void
t1 ()
{
  char *s = "      ,.";
  char *tok;

  tok = strtok (s, " ,.;-");

  if (tok != NULL)
    failed ("t1, tok wrong");
}


void
t2 ()
{
  char *s = "...one two, three. four-five;";
  char *tok;

  tok = strtok (s, " ,.;-");
  if (tok == NULL || strcmp (tok, "one") != 0)
    failed ("t2, expected \"one\", got \"%s\"", tok);

  tok = strtok (NULL, " ,.;-");
  if (tok == NULL || strcmp (tok, "two") != 0)
    failed ("t2, expected \"two\", got \"%s\"", tok);

  tok = strtok (NULL, " ,.;-");
  if (tok == NULL || strcmp (tok, "three") != 0)
    failed ("t2, expected \"three\", got \"%s\"", tok);

  tok = strtok (NULL, " ,.;-");
  if (tok == NULL || strcmp (tok, "four") != 0)
    failed ("t2, expected \"four\", got \"%s\"", tok);

  tok = strtok (NULL, " ,.;-");
  if (tok == NULL || strcmp (tok, "five") != 0)
    failed ("t2, expected \"five\", got \"%s\"", tok);


}
  

int
main ()
{
  test ("test-strtok", "Test for ANSI C section 7.11.5.8");

  t1 ();
  t2 ();

  result ();
}


