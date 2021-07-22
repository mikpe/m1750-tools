/*
 * Test for ANSI Standard C: 7.11.3.2
 * 
 * #include <string.h>
 * void *strncat (char *s2, const char *s2, size_t n);
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


static char *_test_strncat_id =
  "$Id$";

void do_test ()
{
  /* Case 1 */
  if (!({char tmp [10]; strcpy (tmp, "q"); strncat (tmp, "", 0); strcmp (tmp, "q") == 0;})) {
    failed ("Case 1: {char tmp [10]; strcpy (tmp, \"q\"); strncat (tmp, \"\", 0); strcmp (tmp, \"q\") == 0;}");
  }
  
  /* Case 2 */
  if (!({char tmp [10]; strcpy (tmp, "q"); strncat (tmp, "wer", 0); strcmp (tmp, "q") == 0;})) {
    failed ("Case 2: {char tmp [10]; strcpy (tmp, \"q\"); strncat (tmp, \"wer\", 0); strcmp (tmp, \"q\") == 0;}");
  }
  
  /* Case 3 */
  if (!({char tmp [10]; strcpy (tmp, "q"); strncat (tmp, "wer", 1); strcmp (tmp, "qw") == 0;})) {
    failed ("Case 3: {char tmp [10]; strcpy (tmp, \"q\"); strncat (tmp, \"wer\", 1); strcmp (tmp, \"qw\") == 0;}");
  }
  
  /* Case 4 */
  if (!({char tmp [10]; strcpy (tmp, "q"); strncat (tmp, "wer", 2); strcmp (tmp, "qwe") == 0;})) {
    failed ("Case 4: {char tmp [10]; strcpy (tmp, \"q\"); strncat (tmp, \"wer\", 2); strcmp (tmp, \"qwe\") == 0;}");
  }
  
  /* Case 5 */
  if (!({char tmp [10]; strcpy (tmp, "q"); strncat (tmp, "wer", 3); strcmp (tmp, "qwer") == 0;})) {
    failed ("Case 5: {char tmp [10]; strcpy (tmp, \"q\"); strncat (tmp, \"wer\", 3); strcmp (tmp, \"qwer\") == 0;}");
  }
  
  /* Case 6 */
  if (!({char tmp [10]; strcpy (tmp, "q"); strncat (tmp, "wer", 4); strcmp (tmp, "qwer") == 0;})) {
    failed ("Case 6: {char tmp [10]; strcpy (tmp, \"q\"); strncat (tmp, \"wer\", 4); strcmp (tmp, \"qwer\") == 0;}");
  }
  
  /* Case 7 */
  if (!({char tmp [10]; strcpy (tmp, "q"); strncat (tmp, "wer", 5); strcmp (tmp, "qwer") == 0;})) {
    failed ("Case 7: {char tmp [10]; strcpy (tmp, \"q\"); strncat (tmp, \"wer\", 5); strcmp (tmp, \"qwer\") == 0;}");
  }
  
}


void main ()
{
  test ("test-strncat", "Test for ANSI Standard C: 7.11.3.2");

  do_test ();

  result ();
}

