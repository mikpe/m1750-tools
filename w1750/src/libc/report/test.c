/*
 * ANSI Standard C: 
 * 
 * #include <report.h>
 * void test ();
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
 * $Log: test.c,v $
 * Revision 1.1  1997/03/18 12:53:00  nettleto
 * Initial revision
 *
 */

#include <report.h>

#include <string.h>
#include <stdarg.h>

static char test_name [80];
static int test_failed = 0;


void
test (char *name, char *description, ...)
{
  va_list ap;

  printf (",.,. %s GTS Version 0.1\n", name);
  printf ("---- %s ", name);

  va_start (ap, description);
  vprintf (description, ap);
  va_end (ap);

  printf (".\n");

  strcpy (test_name, name);
  test_failed = 0;
}

void 
failed (char *description, ...)
{
  va_list ap;

  test_failed = 1;

  printf ("   * %s ", test_name);

  va_start (ap, description);
  vprintf (description, ap);
  va_end (ap);

  printf (".\n");
}

void 
comment (char *description, ...)
{
  va_list ap;

  printf ("   - %s ", test_name);

  va_start (ap, description);
  vprintf (description, ap);
  va_end (ap);

  printf (".\n");
}

void 
result ()
{
  if (test_failed)
    {
      printf ("**** %s  FAILED ****************************.\n", test_name);
    }
  else
    {
      printf ("**** %s  PASSED ============================.\n", test_name);
    }
}

int
ident_int (int i)
{
  return i;
}

long
ident_long (long i)
{
  return i;
}

long long
ident_long_long (long long i)
{
  return i;
}

float
ident_float (float i)
{
  return i;
}

double
ident_double (double i)
{
  return i;
}


