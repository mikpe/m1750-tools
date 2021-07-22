/*
 * isatty
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
 * $Log: isatty.c,v $
 * Revision 1.1  1997/07/17 18:49:30  nettleto
 * Initial revision
 *
 */

int 
isatty (int fd)
{
  /*
   * Returns 1 if connected to a terminal device, returns 0 if not. Since
   * we're hooked up to a serial port, we'll say yes for the three valid
   * files, and return a 1.
   */

  switch (fd)
    {
      case 0:
        /* stdin */
        return 1;
      case 1:
        /* stdout */
        return 1;
      case 2:
        /* stderr */
        return 1;
      default:
        /* unsupported fd */
        return 0;
    }
}

