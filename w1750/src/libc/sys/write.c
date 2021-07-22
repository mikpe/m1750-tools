/*
 * ANSI Standard C: 
 * 
 * #include <>
 * int write (int fd, char *buf, size_t count);
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
 * $Log: write.c,v $
 * Revision 1.2  1997/08/06 16:48:12  nettleto
 * Changed LFCR to CRLF
 *
 * Revision 1.1  1997/07/17 18:51:30  nettleto
 * Initial revision
 *
 */

#include <stddef.h>
#include <errno.h>

int 
write (int fd, char *buf, size_t count)
{
  /*
   * Writes up to count bytes from the buffer to the file descriptor
   * fd. On success the number of bytes is returned, (zero indicates end
   * of file). On error, -1 is returned, and errno is set appropriately.
   */

  size_t i;
  
  /*
   * Check the file is stdout or stderr, no other files are suppported
   */
  if (fd != 1 && fd != 2) 
    {
      errno = EBADF;
      return -1;
    }

  /*
   * Copy characters from buf to output device
   */
  for (i = 0; i < count; i++) 
    {
      int c = buf [i];
      int reg;
      
      if (c == 10)
        {
          /* wait until transmit buffer empty */
          do 
            {
              asm volatile ("xio    %0,0x8501,%1" :"=r" (reg) : "x" ((fd-1) << 8));
            }
          while (!(reg & 0x04));

          /* transmit one character */
          asm volatile ("xio    %0,0x0500,%1" :: "r" ('\r'), "x" ((fd-1) << 8));
        }

      /* wait until transmit buffer empty */
      do 
        {
          asm volatile ("xio    %0,0x8501,%1" :"=r" (reg) : "x" ((fd-1) << 8));
        }
      while (!(reg & 0x04));

      /* transmit one character */
      asm volatile ("xio    %0,0x0500,%1" :: "r" (c), "x" ((fd-1) << 8));
    }

  /*
   * Return number of bytes written
   */
  return count;
}

