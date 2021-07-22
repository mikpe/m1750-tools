//------------------------------------------------------------------------------
// FILE                                  :  executor.c
// SCCS                                  :  @(#) %M%, %I%, %H%
//                                    @(#)  wxIDE
// PROGRAM NAME                          :  wxIDE
// MODULE NAME                           :  execute a process
// DATE                                  :  01 may 1996
//                                          01 may 1997
// PROGRAMMER(s)                         :  WME
// LANGUAGE                              :  Borland C++ 4.51
// TYPE                                  :  Integrated Development Environment
//------------------------------------------------------------------------------
// Comments:
// Dialog Box = dbox
//-----------------------------------------------------------------------------

// Compilation options
#ifdef wx_msw
#include <io.h>
#else
#include <unistd.h>
#endif

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define COMMLEN 1024
#define FOUTERR "message.out"
#define IMDONE "imdone.dat"
#define _EXEC_STDOUT 1
#define _EXEC_STDERR 2

char azCommand[COMMLEN+1];

void main(int argc, char *argv[])
{
  int i;
  FILE *pFOutErr;
  FILE *pFDone;
  time_t t;

  // If no argument
  if (argc == 1)
  {
    goto end;
  }

  // Unlink STDERR and STDOUT
  unlink(FOUTERR);
  if ((pFOutErr = fopen(FOUTERR, "w")) != (FILE *) NULL)
  {
    // Write an header with time information
    t = time(NULL);
    fprintf(pFOutErr, "Message file generated at %s\n", ctime(&t));
    fflush(pFOutErr);

    // Redirect STDOUT
    close(_EXEC_STDOUT);
    dup(fileno(pFOutErr));

    // Redirect STDERR
    close(_EXEC_STDERR);
    dup(fileno(pFOutErr));

    // Prepare the command line
    azCommand[0] = '\0';
    for (i=1; i<argc; i++)
    {
      strcat(azCommand, argv[i]);
      strcat(azCommand, " ");
    }
    // Call child application
    system(azCommand);
    fclose(pFOutErr);
  }

end:

  // As soon as the process ends, writes a file to inform wxIDE
  if ((pFDone = fopen(IMDONE, "w")) != (FILE *) NULL)
  {
    fprintf(pFDone, "I'm done!\n");
    fclose(pFDone);
  }

  exit(0);
}
