/*
 * ANSI Standard C: 
 * 
 * #include <>
 * int read (int fd, char *buf, size_t count);
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
 * $Log: read.c,v $
 * Revision 1.1  1997/07/17 18:49:59  nettleto
 * Initial revision
 *
 */

#include <stddef.h>
#include <errno.h>

int 
read (int fd, char *buf, size_t count)
{
  /*
   * Reads up to count bytes from the file descriptor fd into the buffer
   * starting at buf. On success the number of bytes is returned, (zero
   * indicates end of file). On error, -1 is returned, and errno is set
   * appropriately.
   */

  int i;
  const char end_of_line = '\015';
  const char end_of_file = '\004';
 
  /*
   * Check the file is stdin, no other file suppported
   */
  if (fd != 0) 
    {
      errno = EBADF;
      return -1;
    }

  /*
   * Copy from stdin until buf full or end of line of end-of-file detected
   */
  i = 0;
  while (i < count) 
    {
      char c;
      int reg;

      /* wait until receive buffer not empty */
      do 
        asm volatile ("xio    %0,0x8501" :"=r" (reg));
      while (!(reg & 0x02));

      /* get one character */
      asm volatile ("xio    %0,0x8500" : "=r" (c));
      c &= 0xff;
 
      if (c == end_of_file)
        return 0;
      
      /* handle backspace */
      if (c == 8)
        {
          if (i > 0)
            {
              i--;
              buf [i] = ' ';
              write (1, "\010 \010", 3);
            }
        }
      else if (c == end_of_line)
        {
          buf [i++] = '\n';
          write (1, "\015\012", 2);
          break;
        }
      else
        {
          buf [i] = c;
          write (1, &buf [i], 1);
          i++;
        }
    }

  /*
   * Return number of bytes read into buf
   */
  return i;
}

