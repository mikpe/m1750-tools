//------------------------------------------------------------------------------
// FILE                                  :  wxidefct.cc
// SCCS                                  :  @(#) %M%, %I%, %H%
//                                    @(#)  wxIDE
// PROGRAM NAME                          :  wxIDE
// MODULE NAME                           :  Functions
// DATE                                  :  01 may 1996
//                                          01 may 1997
// PROGRAMMER(s)                         :  WME
// LANGUAGE                              :  Borland C++ 4.51
// TYPE                                  :  Integrated Development Environment
//------------------------------------------------------------------------------

// Include for X and MSW
#include <string.h>
#include <ctype.h>
#include "wx.h"
#include "wxide.h"
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
// Include for MSW
#ifdef wx_msw
#include <io.h>
#include <process.h>
#endif



// +-----------------------------------+
// | Function to build the new editors |
// +-----------------------------------+
void vNewWin(void)
{
  int i;
  
  for (i=0;i<NB_EDITORS;i++)
  {
    if (!theApp.win[i])
    {
      // Prepare the title
      strcpy(azFileEdit[i],"noname.c");
      sprintf (azTitle[i],"wxIDE -%d- [%s]\0",i+1,azFileEdit[i]);

      // Build the window in memory
      theApp.win[i] = new FrameClassWin(NULL, azTitle[i], 0, 0, 640, 480,
                                     wxSDI | wxDEFAULT_FRAME, azTitle[i], i);
      theApp.win[i]->Iconize(FALSE);

      // Give to the other editors (if any) the new menu title
      vUpdateViewMenu (i);

      // Display
      theApp.win[i]->Show(TRUE);
      return;
    }
  }
}


// +--------------------------------------+
// | Filter Function to allow only digits |
// +--------------------------------------+
char * pazOnlyDigits(char * pazTxt)
{
  int i;

  // Do to the end of the string
  for (i = 0; pazTxt[i]; i++)
  {
    if (pazTxt[i] < '0' || pazTxt[i] > '9')
    {
      return("Error");
    }
  }
  return (pazTxt);
}


// +-----------------------------------------+
// | Function to concat strings (and verify) |
// +-----------------------------------------+
char *azCatDir(char *azDir, char *azCompName, char *azInclude,
               char *azOptions,char *azEditFile)
{
  char azDirEnd[FILELEN+1];
  char azDirEndSV[FILELEN+1];
  static char azCompil[FILELEN+1];
  char azIncludeEnd[FILELEN+1];
  char azOptionsEnd[FILELEN+1];
  char azEditFileEnd[FILELEN+1];
  char *azString;

  strcpy(azDirEndSV,azDir);

  // If the string azDir or azCompName is empty, return ERR
  if (strcmp(azDirEndSV,"")==0 || strcmp(azCompName,"")==0)
  {
    return("");
  }

   // Search for the first ';' in the string
  azString = strtok(azDirEndSV,";");

  // Search for a correct DIR after the ;
  while ( azString != NULL)
  {
    strcpy(azDirEnd , azString);

    // If the last string's character is not \ then add it
    if (azDirEnd[strlen(azDirEnd)-1] != SEPARATION1 )
    {
      strcat(azDirEnd, SEPARATION2 );
    }

    strcpy(azCompil, azDirEnd);
    strcat(azCompil, azCompName);

    // If the DIR + FILE is found
    if ( wxFileExists(azCompil) )
    {
      break;
    }
    azString = strtok(NULL,";");
  }

  // If none, return ERR
  if (azString == NULL) return (azCompil);

  strcpy(azIncludeEnd,azInclude);


  if (strcmp(azIncludeEnd,"")!=0)
  {
    // Check if there is an option (make -f)
    if (azIncludeEnd[0]!='-' &&
        azIncludeEnd[strlen(azIncludeEnd)-1] != SEPARATION1 )
    {
      strcat(azIncludeEnd,SEPARATION2 );
    }
    strcat(azCompil," ");
    strcat(azCompil,azIncludeEnd);
  }

  strcpy(azOptionsEnd,azOptions);
  if (strcmp(azOptionsEnd,"")!= 0)
  {
    strcat(azCompil," ");
    strcat(azCompil,azOptionsEnd);
  }

  strcpy(azEditFileEnd, azEditFile);
  if (strcmp(azEditFileEnd," ")!= 0)
  {
    strcat(azCompil," ");
    strcat(azCompil,azEditFileEnd);
  }

  // Give back the concated and checked string
  return(azCompil);
}


// +-------------------------------------------------------------------------+
// | Function which starts the execution program with the azCompil parameter |
// +-------------------------------------------------------------------------+
void vExecuteProcess(char *azExe)
{
  char azDone[FILELEN+1];
  char azExeGo[FILELEN+1];
  FILE *fOK;

  // Copy the filenames (see .h)
  strcpy(azSTDFile,MESSAGE);
  strcpy(azDone,DONE);
  strcpy (azExeGo,EXECUTOR);
  strcat (azExeGo," ");
  strcat (azExeGo,azExe);

  // If there is an older message file, delete it
  if ((fOK = fopen(azDone,"r")) != (FILE *) NULL)
  {
    fclose(fOK);
    unlink(azDone);
  }

  // Compilation options
  #ifdef wx_msw
    WinExec(azExeGo,SW_MINIMIZE);
  #else
    wxExecute(azExeGo,FALSE);
  #endif

  // While the execution program doesn't write the file of the end of the active
  // process, loop
  while ((fOK = fopen(azDone,"r")) == (FILE *) NULL)
  {
    wxSleep(1);
  }

  // Close and erase
  fclose(fOK);
  unlink(azDone);

  // If the window message doesn't exist
  if (!theApp.win[NB_EDITORS])
  {
    // Build it in memory
    theApp.win[NB_EDITORS] =
    new FrameClassWin(NULL, "Message", 0,0, 640, 300,
                      wxSDI | wxDEFAULT_FRAME, "message",NB_EDITORS);
  }
  // If the window exists
  else
  {
    // Erase the contents
    theApp.win[NB_EDITORS]->textedit->Clear();
  }
  // Load the file with STDOUT and ERR
  theApp.win[NB_EDITORS]->textedit->LoadFile(azSTDFile);
  // Display
  theApp.win[NB_EDITORS]->Iconize(FALSE);
  theApp.win[NB_EDITORS]->Show(TRUE);
}


// +------------------------------------------+
// | Function to change the time of the files |
// | used for build target                    |
// +------------------------------------------+
void vRemoveFileTime(char *azFile)
{
  char azDir[FILELEN+1];
  char azDir2[FILELEN+1];
  char *pazExtension;
  char *pazPtr;
  
  char *f;
  int fw;
  int i;
  char ch;
  
  pazExtension = strdup (azSetOption[13]);
  
  // Search for the current directory
  strcpy(azDir,wxPathOnly(azFile));
  strcat(azDir,SEPARATION2 );

  // For all the defined extensions
  pazPtr = strtok (pazExtension,";");
  
  while (pazPtr != NULL)
  {
    strcpy(azDir2,"");
    strcpy(azDir2,azDir);
    strcat(azDir2,"*");
    strcat(azDir2,pazPtr);
    
    // Search for the first file
    f = wxFindFirstFile(azDir2);
    while (f)
    {
      // Read the first character and write it at the same position,
      // it changes the file time (this works under X and MSW))
      fw = open(f, O_CREAT|O_RDWR);
      read(fw, &ch, 1);
      lseek(fw, 0l, 0);
      write(fw, &ch, 1);
      close(fw);
      f = wxFindNextFile();
    }
    
    pazPtr = strtok (NULL, ";");
  }
}

// +-------------------------------+
// | Function to close the program |
// +-------------------------------+
void vEndApp(void)
{
  int i;
  
  for (i=(NB_EDITORS + 1); i >= 0; i--)
  {
    // If the window exists
    if (theApp.win[i])
    {
      vEndWin(i);
      if (theApp.win[i]) return;
    }
  }
}

// +----------------------------+
// | Function to close a window |
// +----------------------------+
void vEndWin(int Nb)
{
  int i,a,b,x,y;
  wxFrame *frwin;
  char azStr[FILELEN+1];

  // If the TXT was modified (and if the window is not the message window)
  iAnswer = wxYES;
  if (theApp.win[Nb]->textedit->Modified() && Nb != NB_EDITORS)
  {
    sprintf (azStr,"%s\n%s",azFileEdit[Nb],"has been changed, SAVE file ?");
    
    theApp.win[Nb]->GetPosition(&x,&y);
    a = x + SHIFT;
    b = y + SHIFT;
    iAnswer = wxMessageBox(azStr, "Confirmation",
                           wxYES_NO | wxCANCEL | wxICON_QUESTION,
                           theApp.win[Nb],a,b);

    if ( iAnswer == wxYES )
    {
      // Save the active file
      theApp.win[Nb]->textedit->SaveFile(azFileEdit[Nb]);
    }
  }
  if ( iAnswer != wxCANCEL)
  {
    // point the window
    frwin = theApp.win[Nb];

    // remove it from the screen
    frwin->Show(FALSE);

    i=Nb;

    // remove it from memory
    delete frwin;
    
    // NULL object
    theApp.win[i] = NULL;
  }
  iAnswer = 0;
  return;
}

// +--------------------------------------------+
// | Function to convert UPPERCASE in lowercase |
// +--------------------------------------------+
void vMyStrlwr(char *str)
{
  long i;
  char *pazStr;
  
  pazStr = strdup (str);
  i=0;
  while (str[i])
  {
    pazStr[i] = tolower(str[i]);
    i++;
  }
  strcpy (str, pazStr);
  return;
}

// +----------------------------------+
// | Function to update the View Menu |
// +----------------------------------+
void vUpdateViewMenu (int Nb)
{
  int i;
  char *pazString;
  
  for (i=0;i<NB_EDITORS;i++)
  {
    if (theApp.win[i])
    {
      if (i==Nb)
      {
        pazString = new char[strlen(azTitle[Nb]) + 9];
        sprintf(pazString,"%s current\0",azTitle[Nb]);
      }
      else
      {
        pazString = strdup (azTitle[Nb]);
      }
      theApp.win[i]->Menu4->SetLabel(EDITOR1_ID + Nb,pazString);
      delete pazString;

      pazString = new char[strlen(azTitle[i]) + 13];
      sprintf (pazString,"View Editor %s\0",azTitle[i]);
      theApp.win[i]->Menu4->SetHelpString(EDITOR1_ID + Nb,azTitle[Nb]);
      delete pazString;
    }
  }
  return;
}
 
// +-----------------------------------+
// | Function to format the extensions |
// +-----------------------------------+

void vFormatExtensions (void)
{
#ifdef wx_msw
  char azBuffer[FILELEN + 1];
  int i,j;

  j=0;
  azBuffer[j] = '*';
  j++;

  for (i = 0; azExtension[i] != '\0'; i++)
  {
    azBuffer[j] = azExtension[i];
    j++;
    if (azExtension[i] == ';')
    {
      azBuffer[j] = '*';
      j++;
    }
  }
  azBuffer[j] = '\0';
  strcpy (azExtension, azBuffer);
  return;
#else
  strcpy (azExtension, "*");
  return;
#endif
}
