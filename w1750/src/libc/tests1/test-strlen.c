/*
 * Test for ANSI Standard C: 7.11.6.3
 * 
 * #include <string.h>
 * size_t strlen (const char *s);
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


static char *_test_strlen_id =
  "$Id$";

void do_test ()
{
  /* Case 1 */
  if (!(strlen ("") == 0)) {
    failed ("Case 1: strlen (\"\") == 0");
  }
  
  /* Case 2 */
  if (!(strlen ("a") == 1)) {
    failed ("Case 2: strlen (\"a\") == 1");
  }
  
  /* Case 3 */
  if (!(strlen ("ab") == 2)) {
    failed ("Case 3: strlen (\"ab\") == 2");
  }
  
  /* Case 4 */
  if (!(strlen ("abc") == 3)) {
    failed ("Case 4: strlen (\"abc\") == 3");
  }
  
  /* Case 5 */
  if (!(strlen ("ABCD") == 4)) {
    failed ("Case 5: strlen (\"ABCD\") == 4");
  }
  
  /* Case 6 */
  if (!(strlen ("abcde") == 5)) {
    failed ("Case 6: strlen (\"abcde\") == 5");
  }
  
  /* Case 7 */
  if (!(strlen ("ZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZ") == 65)) {
    failed ("Case 7: strlen (\"ZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZ\") == 65");
  }
  
}


void main ()
{
  test ("test-strlen", "Test for ANSI Standard C: 7.11.6.3");

  do_test ();

  result ();
}

