/*
 * Test for ANSI Standard C: 7.11.6.2
 * 
 * #include <string.h>
 * char *strerror (int errnum);
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

#include <errno.h>

static char *_test_strerror_id =
  "$Id$";

void do_test ()
{
  /* Case 1 */
  if (!(strcmp (strerror (0),       ""                      ) == 0)) {
    failed ("Case 1: strcmp (strerror (0),       \"\"                      ) == 0");
  }
  
  /* Case 2 */
  if (!(strcmp (strerror (EIO),     "I/O error"             ) == 0)) {
    failed ("Case 2: strcmp (strerror (EIO),     \"I/O error\"             ) == 0");
  }
  
  /* Case 3 */
  if (!(strcmp (strerror (ENOMEM),  "Not enough space"      ) == 0)) {
    failed ("Case 3: strcmp (strerror (ENOMEM),  \"Not enough space\"      ) == 0");
  }
  
  /* Case 4 */
  if (!(strcmp (strerror (EDOM),    "Math argument"         ) == 0)) {
    failed ("Case 4: strcmp (strerror (EDOM),    \"Math argument\"         ) == 0");
  }
  
  /* Case 5 */
  if (!(strcmp (strerror (ERANGE),  "Result too large"      ) == 0)) {
    failed ("Case 5: strcmp (strerror (ERANGE),  \"Result too large\"      ) == 0");
  }
  
  /* Case 6 */
  if (!(strcmp (strerror (EBADF),   "Bad file number"       ) == 0)) {
    failed ("Case 6: strcmp (strerror (EBADF),   \"Bad file number\"       ) == 0");
  }
  
}


void main ()
{
  test ("test-strerror", "Test for ANSI Standard C: 7.11.6.2");

  do_test ();

  result ();
}

