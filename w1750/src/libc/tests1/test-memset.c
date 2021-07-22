/*
 * Test for ANSI Standard C: 7.11.6.1
 * 
 * #include <string.h>
 * void *memset (void *s, int c, size_t n);
 * 
 * Copyright (c) 1996, Free Software Foundation, Inc.
 *
 * This file is part of the GNU C Library. The GNU C Library is free 
 * software; you can redistribute it and/or modify it under the terms of 
 * the GNU Library General Public License as published by the Free 
 * Software Foundation; either version 2 of the License, or (at your 
 * option) any later version. The GNU C Library is distributed in the 
 * hope that it will be useful, but WITHOUT ANY WARRANTY; without even 
 * the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR 
 * PURPOSE. See the GNU Library General Public License for more details. 
 * You should have received a copy of the GNU Library General Public 
 * License along with the GNU C Library; see the file COPYING.LIB. If 
 * not, write to the Free Software Foundation, Inc., 675 Mass Ave, 
 * Cambridge, MA 02139, USA. 
 *
 * $Log$
 */

#include <report.h>

#include <string.h>


static char *_test_memset_id =
  "$Id$";

void do_test ()
{
  /* Case 1 */
  if (!({char buf [10]; (memset (buf, 12345, 10) == buf && buf [0] == 12345 &&  buf [9] == 12345);})) {
    failed ("Case 1: {char buf [10]; (memset (buf, 12345, 10) == buf && buf [0] == 12345 &&  buf [9] == 12345);}");
  }
  
}


void main ()
{
  test ("test-memset", "Test for ANSI Standard C: 7.11.6.1");

  do_test ();

  result ();
}

