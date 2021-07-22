/*
 * kill
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
 * $Log: kill.c,v $
 * Revision 1.1  1997/07/17 18:47:43  nettleto
 * Initial revision
 *
 */

int 
kill (int pid, int sig)
{
  /*
   * In this bare board implementation only pid == 1 is legal. Other
   * process id numbers are ignored.
  */

  if (pid == 1)
    exit (sig);

  return 0;
}

