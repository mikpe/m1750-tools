/*
 * Test for ANSI Standard C: 7.11.2.2
 * 
 * #include <string.h>
 * void *memmove (void *s1, const void *s2, size_t n);
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
 * $Log$
 */

#include <report.h>

#include <string.h>


static char *_test_memmove_id =
  "$Id$";

void do_test ()
{
  /* Case 1 */
  if (!({char tmp [100]; memcpy (tmp, "123", 4); strcmp (tmp, "123") == 0;})) {
    failed ("Case 1: {char tmp [100]; memcpy (tmp, \"123\", 4); strcmp (tmp, \"123\") == 0;}");
  }
  
  /* Case 2 */
  if (!({char tmp [100]; strcpy (tmp, "tar"); memmove (&tmp [3], tmp, 4); strcmp (tmp, "tartar") == 0;})) {
    failed ("Case 2: {char tmp [100]; strcpy (tmp, \"tar\"); memmove (&tmp [3], tmp, 4); strcmp (tmp, \"tartar\") == 0;}");
  }
  
  /* Case 3 */
  if (!({char tmp [100]; strcpy (tmp, "qwertyuiop"); memmove (tmp, &tmp [5], 5); strcmp (tmp, "yuiopyuiop") == 0;})) {
    failed ("Case 3: {char tmp [100]; strcpy (tmp, \"qwertyuiop\"); memmove (tmp, &tmp [5], 5); strcmp (tmp, \"yuiopyuiop\") == 0;}");
  }
  
}


void main ()
{
  test ("test-memmove", "Test for ANSI Standard C: 7.11.2.2");

  do_test ();

  result ();
}

