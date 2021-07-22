/*
 * Test for ANSI Standard C: 7.6.1.1
 *
 * #include <setjmp.h>
 * int setjmp (jmp_buf env);
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
 * $Log: test-setjmp.c,v $
 * Revision 1.1  1997/08/01 16:05:38  nettleto
 * Initial revision
 *
 */

#include <report.h>
#include <setjmp.h>

#define MAX 1000

static jmp_buf env;
static int last_value, lose;

void
jump (int val)
{
  longjmp (env, val);
}

int
main ()
{
  int value;

  last_value = -1;
  lose = 0;

  test ("test_setjmp", "test for setjmp");

  value = setjmp (env);
  if (value != last_value + 1)
    {
      comment ("Shouldn't have - ");
      lose = 1;
    }
  last_value = value;
  switch (value)
    {
    case 0:
      comment ("Saved environment");
      jump (0);
    default:
      if (value < MAX)
	jump (value + 1);
      else
        comment ("Jumped to %d", value);
    }

  if (lose)
    failed ("lose set");

  if (value != MAX)
    failed ("Returned value wrong");

  result ();
}

