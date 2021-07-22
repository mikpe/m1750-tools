//------------------------------------------------------------------------------
// FILE                                  :  executor.c
// SCCS                                  :  @(#) %M%, %I%, %H%
//                                    @(#)  wxIDE
// PROGRAM NAME                          :  wxIDE
// MODULE NAME                           :  exectute un process
// DATE                                  :  01 mai 1996
//                                          14 juin 1996
// PROGRAMMER(s)                         :  Jerome CANDE
// LANGUAGE                              :  Borland C++ 4.51
// TYPE                                  :  Integrated Development Environment
//------------------------------------------------------------------------------
// Commentaires:
// Dialog Box = dbox
// Attention, les commantaires ont ete tapes avec un clavier anglais donc il n'
// y a pas d'accents.
//-----------------------------------------------------------------------------

// Condition de compilation
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

  // Si pas d'argument
  if (argc == 1)
  {
    goto end;
  }

  // Efface le fichier contenant STDERR et STDOUT
  unlink(FOUTERR);
  if ((pFOutErr = fopen(FOUTERR, "w")) != (FILE *) NULL)
  {
    // Write an header with time information
    t = time(NULL);
    fprintf(pFOutErr, "Message file generated at %s\n", ctime(&t));
    fflush(pFOutErr);

    // Redirectionne STDOUT
    close(_EXEC_STDOUT);
    dup(fileno(pFOutErr));

    // Redirectionne STDERR
    close(_EXEC_STDERR);
    dup(fileno(pFOutErr));

    // Prepare le ligne de commande
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

  // Des que le process a fini de tourner, ecrit un fichier
  // pour le signaler a wxIDE
  if ((pFDone = fopen(IMDONE, "w")) != (FILE *) NULL)
  {
    fprintf(pFDone, "I'm done!\n");
    fclose(pFDone);
  }

  // Sortie de executor
  exit(0);
}
