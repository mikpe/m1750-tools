/*
 * ANSI Standard C: 7.7.1.1
 * 
 * #include <signal.h>
 * (*signal (int sig, void (*func)(int))) signal (int);
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
 * $Log: signal.c,v $
 * Revision 1.2  1997/07/17 18:56:56  nettleto
 * Removed 1750-specific signals. These are now interrupts.
 *
 * Revision 1.1  1997/05/09 17:45:56  nettleto
 * Initial revision
 *
 */

#include <signal.h>

#include <errno.h>

__sighandler_t _sig_func [32];

__sighandler_t 
signal (int sig, __sighandler_t func)
{
  __sighandler_t old_func;

  switch (sig)
    {
    case SIGHUP:
    case SIGINT:
    case SIGQUIT:
    case SIGILL:
    case SIGTRAP:
    case SIGIOT:
    case SIGEMT:
    case SIGFPE:
    case SIGKILL:
    case SIGBUS:
    case SIGSEGV:
    case SIGSYS:
    case SIGPIPE:
    case SIGALRM:
    case SIGTERM:
    case SIGUSR1:
    case SIGUSR2:
    case SIGCHLD:
    case SIGPWR:
      old_func = _sig_func [sig];
      _sig_func [sig] = func;
      break;

    default:
      old_func = SIG_ERR;
      errno = EINVAL;
      break;
    }

  return old_func;
}

