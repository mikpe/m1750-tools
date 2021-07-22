/*
 * m1750-coff/include/signal.h
 *
 * POSIX/ANSI Standard C: 7.7 Signal handling
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
 * :$Log: signal.h,v $
 * :Revision 1.3  1997/07/17 19:01:34  nettleto
 * :Removed 1750-specific signal names.
 * :
 * :Revision 1.2  1997/05/09 17:37:45  nettleto
 * :*** empty log message ***
 * :
 * :Revision 1.1  1997/05/09 17:31:45  nettleto
 * :Initial revision
 * :
 */

#ifndef _SIGNAL_H_
#define _SIGNAL_H_

#include <sys/cdefs.h>

__BEGIN_DECLS

typedef int sig_atomic_t;

typedef void (*__sighandler_t)(int);


#define SIG_DFL ((__sighandler_t)0)     /* default signal handling */
#define SIG_ERR ((__sighandler_t)-1)    /* error return from signal */
#define SIG_IGN ((__sighandler_t)1)     /* ignore signal */

#define SIGHUP          1       /* Hangup (POSIX).  */
#define SIGINT          2       /* Interrupt (ANSI).  */
#define SIGQUIT         3       /* Quit (POSIX).  */
#define SIGILL          4       /* Illegal instruction (ANSI).  */
#define SIGABRT         SIGIOT  /* Abort (ANSI).  */
#define SIGTRAP         5       /* Trace trap (POSIX).  */
#define SIGIOT          6       /* IOT trap (4.2 BSD).  */
#define SIGEMT          7       /* EMT trap (4.2 BSD).  */
#define SIGFPE          8       /* Floating-point exception (ANSI).  */
#define SIGKILL         9       /* Kill, unblockable (POSIX).  */
#define SIGBUS          10      /* Bus error (4.2 BSD).  */
#define SIGSEGV         11      /* Segmentation violation (ANSI).  */
#define SIGSYS          12      /* Bad argument to system call (4.2 BSD)*/
#define SIGPIPE         13      /* Broken pipe (POSIX).  */
#define SIGALRM         14      /* Alarm clock (POSIX).  */
#define SIGTERM         15      /* Termination (ANSI).  */
#define SIGUSR1         16      /* User-defined signal 1 (POSIX).  */
#define SIGUSR2         17      /* User-defined signal 2 (POSIX).  */
#define SIGCHLD         18      /* Child status has changed (POSIX).  */
#define SIGCLD          SIGCHLD /* Same as SIGCHLD (System V).  */
#define SIGPWR          19      /* Power failure restart (System V).  */

/*
 * 7.7.1.1 Specify new handling for signal sig. If successful return the 
 * return the previous handler, otherwise return SIG_ERR.
 */
__sighandler_t signal (int sig, __sighandler_t func);


/*
 * 7.7.2.1 Sends the signal sig, and returns 0 if the signal is 
 * successfully reported
 */
int raise (int sig);

__END_DECLS

#endif /* not _SIGNAL_H_ */

