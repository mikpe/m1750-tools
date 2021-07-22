/*
 * ANSI Standard C: 7.10.4.5
 * 
 * #include <stdlib.h>
 * int system (const char *string);
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
 * $Log: system.c,v $
 * Revision 1.1  1997/05/09 16:55:43  nettleto
 * Initial revision
 *
 */

#include <stdlib.h>

#include <errno.h>

/*
 * The system function passes the string pointed to by the argument to the
 * host environment to be executed by a command processor in an
 * implementation-defined manner. A null pointer may be used for string to
 * enquire whether a command processor exists.
 * 
 * Returns: If the argument is a null pointer, the system function returns
 * non zero only if a command processor is available. If the argument is
 * not a null pointer, the system function returns an
 * implementation-defined value.
 */

int
system (const char *string)
{
  if (string == NULL)
    return 0;  

  errno = ENOSYS;
  return -1;
}

