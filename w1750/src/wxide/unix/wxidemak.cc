//------------------------------------------------------------------------------
// FILE                                  :  idemake.cc
// SCCS                                  :  @(#) %M%, %I%, %H%
//                                    @(#)  wxIDE
// PROGRAM NAME                          :  wxIDE
// MODULE NAME                           :  Make Menu
// DATE                                  :  01 may 1996
//                                          01 may 1997
// PROGRAMMER(s)                         :  WME
// LANGUAGE                              :  Borland C++ 4.51
// TYPE                                  :  Integrated Development Environment
//------------------------------------------------------------------------------
// Comment:
// Dialog Box = dbox
//-----------------------------------------------------------------------------

#include "wx.h"
#include "wxide.h"

// +--------------+
// | New Makefile |
// +--------------+
void vNewMakefile(void)
{
  char azMessage[FILELEN + 1];
  int a,b,x,y;
  
  // If the window doesn't exist
  if (!theApp.win[NB_EDITORS + 1])
  {
    // Call the constructor
    theApp.win[NB_EDITORS + 1] =
    new FrameClassWin(NULL, azTitle[NB_EDITORS + 1], 0,0, 640, 300,
                           wxSDI | wxDEFAULT_FRAME, "makefile",NB_EDITORS + 1);
    theApp.win[NB_EDITORS + 1]->Iconize(FALSE);

    // Prepare the Title
    sprintf(azTitle[NB_EDITORS + 1],"wxIDE -%d- [%s]\0",NB_EDITORS + 2,
           "noname.mak");
    theApp.win[NB_EDITORS + 1]->SetTitle(azTitle[NB_EDITORS + 1]);

    // Display
    theApp.win[NB_EDITORS + 1]->Show(TRUE);
    return;
  }

  // If the window exists
  else
  {
    // If the TXT was modified
    if (theApp.win[NB_EDITORS + 1]->textedit->Modified() )
    {
      // Prepare the position of the child's window
      theApp.win[NB_EDITORS + 1]->GetPosition(&x,&y);
      a = x + SHIFT;
      b = y + SHIFT;
        
      // Call the constructor
      sprintf(azMessage,"%s\n%s", azFileEdit[NB_EDITORS + 1],
              "has been changed, SAVE file ?");

      iAnswer = wxMessageBox(azMessage, "Confirmation", wxYES_NO | wxCANCEL
                             | wxCENTRE, theApp.win[NB_EDITORS + 1], a, b);

      // If answer is YES
      if (iAnswer == wxYES)
      {
        iAnswer = 0;
        if (strcmp(azFileEdit[NB_EDITORS + 1],"noname.mak")==0)
        {
          // Display the file selection box
          // If no file selected, exit
          if ((pazF=wxFileSelector("Save file...", NULL, azFileEdit[NB_EDITORS + 1],
                                   "*.mak", "*.mak", wxSAVE | wxOVERWRITE_PROMPT,
                                   theApp.win[NB_EDITORS + 1], a, b))==NULL)
            return;
          strcpy(azFileEdit[NB_EDITORS + 1],pazF);

          // Save the active TXT
          theApp.win[NB_EDITORS + 1]->textedit->
                                  SaveFile(azFileEdit[NB_EDITORS + 1]);
        }
      }
      // If answer is CANCEL
      else if (iAnswer == wxCANCEL)
      {
        iAnswer = 0;
        // Exit
        return;
      }
    }

    // Initialise the TXT page
    theApp.win[NB_EDITORS + 1]->textedit->Clear();

    // Prepare the Title
    sprintf(azTitle[NB_EDITORS + 1],"wxIDE -%d- [%s]\0",NB_EDITORS + 2,
            "noname.mak");
    theApp.win[NB_EDITORS + 1]->SetTitle(azTitle[NB_EDITORS + 1]);

    // Display
    theApp.win[NB_EDITORS + 1]->Show(TRUE);
    return;
  }
}


// +---------------+
// | Open Makefile |
// +---------------+
void vOpenMakefile(void)
{
  char azMessage[FILELEN + 1];
  int a,b,x,y;
    
  // If the window doesn't exist
  if (!theApp.win[NB_EDITORS + 1])
  {
    // Call the constructor
    theApp.win[NB_EDITORS + 1] =
    new FrameClassWin(NULL, azTitle[NB_EDITORS + 1], 0,0, 640, 300,
                           wxSDI | wxDEFAULT_FRAME, "makefile",NB_EDITORS + 1);
    theApp.win[NB_EDITORS + 1]->Iconize(FALSE);
  }

  theApp.win[NB_EDITORS + 1]->Show(TRUE);
  
  // Prepare the position of the child's window
  theApp.win[NB_EDITORS + 1]->GetPosition(&x,&y);
  a = x + SHIFT;
  b = y + SHIFT;
        
  // If the active TXT was modified
  if (theApp.win[NB_EDITORS + 1]->textedit->Modified() )
  {
    // Call the constructor
    sprintf(azMessage,"%s\n%s", azFileEdit[NB_EDITORS + 1],
            "has been changed, SAVE file ?");

    iAnswer = wxMessageBox(azMessage, "Confirmation", wxYES_NO | wxCANCEL
                           | wxCENTRE, theApp.win[NB_EDITORS + 1], a, b);

    // If answer is YES
    if ( iAnswer == wxYES )
    {
      if (strcmp(azFileEdit[NB_EDITORS + 1],"noname.mak")==0)
      {
        // Display the file selection box
        // If no file selected, exit
        if ((pazF = wxFileSelector("Save file...", NULL,
                                   azFileEdit[NB_EDITORS + 1], "*.mak",
                                   "*.mak", wxSAVE | wxOVERWRITE_PROMPT,
                                   theApp.win[NB_EDITORS + 1], a, b))==NULL)
          return;
        strcpy(azFileEdit[NB_EDITORS + 1],pazF);
      }

      // Save the active TXT
      theApp.win[NB_EDITORS + 1]->textedit->
                                  SaveFile(azFileEdit[NB_EDITORS + 1]);
    }
    // If answer is CANCEL
    else if (iAnswer == wxCANCEL)
    {
      iAnswer = 0;
      // exit
      return;
    }

    iAnswer = 0;
  }

  // Display the file selection box
  // If no file selected, exit
  if ((pazF = wxFileSelector("Open file...", NULL, "*.mak", "*.mak", "*.mak",
                             wxOPEN | wxOVERWRITE_PROMPT,
                             theApp.win[NB_EDITORS + 1], a, b))==NULL )
    return;
  strcpy(azFileEdit[NB_EDITORS + 1],pazF);

  // Open the file
  theApp.win[NB_EDITORS + 1]->textedit->LoadFile(azFileEdit[NB_EDITORS + 1]);

  // Prepare the title
  sprintf(azTitle[NB_EDITORS + 1],"wxIDE -%d- [%s]\0",NB_EDITORS + 2,
          azFileEdit[NB_EDITORS + 1]);
  theApp.win[NB_EDITORS + 1]->SetTitle(azTitle[NB_EDITORS + 1]);

  // Display
  theApp.win[NB_EDITORS + 1]->Show(TRUE);
  return;
}


// +---------------+
// | Save Makefile |
// +---------------+
void vSaveMakefile(void)
{
  int a,b,x,y;
    
  if (theApp.win[NB_EDITORS + 1] && theApp.win[NB_EDITORS + 1]->textedit->
      Modified())
  {
    // Prepare the position of the child's window
    theApp.win[NB_EDITORS + 1]->GetPosition(&x,&y);
    a = x + SHIFT;
    b = y + SHIFT;

    // If file name is "noname.mak"
    if (strcmp(azFileEdit[NB_EDITORS + 1],"noname.mak")==0)
    {
      // Display the file selection box
      // If no file selected, exit
      if ((pazF = wxFileSelector("Save file...", NULL,
                                 azFileEdit[NB_EDITORS + 1], "*.mak",
                                 "*.mak", wxSAVE | wxOVERWRITE_PROMPT,
                                 theApp.win[NB_EDITORS + 1], a, b)) ==NULL)
        return;
      strcpy(azFileEdit[NB_EDITORS + 1],pazF);
    }

    // Save the current TXT
    theApp.win[NB_EDITORS + 1]->textedit->SaveFile(azFileEdit[NB_EDITORS + 1]);

    // Prepare the title
    sprintf(azTitle[NB_EDITORS + 1],"wxIDE -%d- [%s]\0",NB_EDITORS + 2,
            azFileEdit[NB_EDITORS + 1]);
    theApp.win[NB_EDITORS + 1]->SetTitle(azTitle[NB_EDITORS + 1]);

    // Display
    theApp.win[NB_EDITORS + 1]->Show(TRUE);
  }
  return;
}

// +----------------------+
// | Save Makefile As ... |
// +----------------------+
void vSaveAsMakefile(void)
{
  int a,b,x,y;
    
  if (theApp.win[NB_EDITORS + 1])
  {
    // Prepare the position of the child's window
    theApp.win[NB_EDITORS + 1]->GetPosition(&x,&y);
    a = x + SHIFT;
    b = y + SHIFT;

    // Display the file selection box
    // If no file selected, exit
    if ((pazF=wxFileSelector("Save As...", NULL, azFileEdit[NB_EDITORS + 1] ,
                             "*.mak", "*.mak", wxSAVE | wxOVERWRITE_PROMPT,
                             theApp.win[NB_EDITORS + 1], a, b))==NULL)
      return;
    strcpy(azFileEdit[NB_EDITORS + 1],pazF);

    // Save the current txt
    theApp.win[NB_EDITORS + 1]->textedit->
                                SaveFile(azFileEdit[NB_EDITORS + 1]);

    // Prepare the title
    sprintf(azTitle[NB_EDITORS + 1],"wxIDE -%d- [%s]\0",NB_EDITORS + 1,
            "noname.mak");
    theApp.win[NB_EDITORS + 1]->SetTitle(azTitle[NB_EDITORS + 1]);

    // Display
    theApp.win[NB_EDITORS + 1]->Show(TRUE);
    return;
  }
}


// +------------+
// | Set Target |
// +------------+
void vSetTarget(int WinNb)
{
  int a,b,x,y,w,h;
    
  // Prepare the position of the child's window
  theApp.win[WinNb]->GetPosition(&x,&y);
  theApp.win[WinNb]->GetSize(&w, &h);
  a = x + ((w - 308) / 2);
  b = y + ((h - 167) / 2);

  // If the dbox doesn't exist
  if (!theApp.settarget)
  {
    // Call the constructor
    theApp.settarget =
    new DialogBoxClassSettarget(theApp.win[WinNb], "Set target:", TRUE, a, b, 308, 167,
                                wxCAPTION | wxDEFAULT_DIALOG_STYLE,
                                "settarget");
  }
  // Display with the old value
  theApp.settarget->GetSetTarget->SetValue(azTarget);
  theApp.settarget->Show(TRUE);
}



// +-------------+
// | Make Target |
// +-------------+
void vMakeTarget(int WinNb)
{
  char *azPtr, azString[FILELEN + 1];
  int a,b,x,y,w,h;
    
  // Prepare the position of the child's window
  theApp.win[WinNb]->GetPosition(&x,&y);
  theApp.win[WinNb]->GetSize(&w, &h);
  a = x + ((w - 458) / 2);
  b = y + ((h - 180) / 2);

  // If the dbox doesn't exist
  if (!theApp.execute)
  {
    // Call the constructor
    theApp.execute =
    new DialogBoxClassExecute(theApp.win[WinNb], "Execute:", TRUE, a, b, 458,
                              180, wxCAPTION | wxDEFAULT_DIALOG_STYLE,
                              "execute");
  }
  // Call the function to concat the arguments
  strcpy(azTmp,azCatDir(azSetOption[0],azSetOption[8],
                        azSetOption[9],azFileEdit[NB_EDITORS + 1],azTarget));

  // Take the command line in the dbox
  theApp.execute->GetExecuteCommandeLine->SetValue(azTmp);

  // is this operation possible (the command line is valid) ?
  strcpy (azString, azTmp);
  azPtr = strtok (azString," ");
  wxRemoveFile(MESSAGE);

  if (!wxFileExists(azPtr))
  {
    // Give back the result in the dbox
    theApp.execute->Show(TRUE);
  }
  else
  {
    wxButton but;
    wxCommandEvent event;
    ButtonProc107(but, event);
  }
  return;
}


// +--------------+
// | Build Target |
// +--------------+
void vBuildTarget(int WinNb)
{
  char *azPtr, azString[FILELEN + 1];
  int a,b,x,y,w,h;
    
  if (strcmp(azFileEdit[NB_EDITORS + 1], "noname.mak") == 0)
  {
    theApp.win[WinNb]->GetPosition(&x,&y);
    a = x + SHIFT;
    b = y + SHIFT;
    iAnswer = wxMessageBox("Please open first a makefile", "Warning", wxOK
                          | wxCENTRE, theApp.win[WinNb], a, b);
    return;
  }

  // Prepare the position of the child's window
  theApp.win[WinNb]->GetPosition(&x,&y);
  theApp.win[WinNb]->GetSize(&w, &h);
  a = x + ((w - 458) / 2);
  b = y + ((h - 180) / 2);

  // If the dbox doesn't exist
  if (!theApp.execute)
  {
    // Call the constructor
    theApp.execute =
    new DialogBoxClassExecute(theApp.win[WinNb], "Execute:", TRUE, a, b, 458,
                              180, wxCAPTION | wxDEFAULT_DIALOG_STYLE,
                              "execute");
  }
  // Call the function to concat the arguments
  strcpy(azTmp,azCatDir(azSetOption[0],azSetOption[8],
                        azSetOption[9],azFileEdit[NB_EDITORS + 1],azTarget));

  // Change the file time
  vRemoveFileTime(azFileEdit[NB_EDITORS + 1]);
  theApp.execute->GetExecuteCommandeLine->SetValue(azTmp);

  // is this operation possible (the command line is valid) ?
  strcpy (azString, azTmp);
  azPtr = strtok (azString," ");
  wxRemoveFile(MESSAGE);
  if (!wxFileExists(azPtr))
  {
    theApp.execute->Show(TRUE);
  }
  else
  {
    wxButton but;
    wxCommandEvent event;
    ButtonProc107(but, event);
  }
}


// +---------+
// | Compile |
// +---------+
void vCompile(int WinNb)
{
  char azMessage[FILELEN + 1], *azPtr, azString[FILELEN + 1];
  int a,b,x,y,w,h;

  iAnswer = 0;    
  // If the current TXT was modified
  if (theApp.win[WinNb]->textedit->Modified() )
  {
    theApp.win[WinNb]->GetPosition(&x,&y);
    a = x + SHIFT;
    b = y + SHIFT;
        
    // Call the constructor
    sprintf(azMessage,"%s\n%s", azFileEdit[WinNb],
            "has been changed, SAVE file ?");

    iAnswer = wxMessageBox(azMessage, "Confirmation", wxYES_NO | wxCANCEL
                           | wxCENTRE, theApp.win[WinNb], a, b);

    // If answer is YES
    if ( iAnswer == wxYES )
    {
      iAnswer = 0;
      if (strcmp(azFileEdit[WinNb],"noname.c")==0)
      {
        // Display the file selection box
        // If no file selected, exit
        if ((pazF=wxFileSelector("Save file...", NULL, azFileEdit[WinNb] ,
                                 azExtension, azExtension, wxSAVE |
                                 wxOVERWRITE_PROMPT,
                                 theApp.win[WinNb], a, b))==NULL)
          return;
          strcpy(azFileEdit[WinNb],pazF);
      }
      // Save the active TXT
      theApp.win[WinNb]->textedit->SaveFile(azFileEdit[WinNb]);

      sprintf(azTitle[WinNb],"wxIDE -%d- [%s]\0", WinNb,
              azFileEdit[WinNb]);
      theApp.win[WinNb]->SetTitle(azTitle[WinNb]);

      vUpdateViewMenu(WinNb);
    }
  }
  // If answer is not CANCEL
  if (iAnswer != wxCANCEL)
  {
    // Prepare the position of the child's window
    theApp.win[WinNb]->GetPosition(&x,&y);
    theApp.win[WinNb]->GetSize(&w, &h);
    a = x + ((w - 458) / 2);
    b = y + ((h - 180) / 2);

    // If the dbox doesn't exist
    if (!theApp.execute)
    {
      // Call the constructor
      theApp.execute =
      new DialogBoxClassExecute(theApp.win[WinNb], "Execute", TRUE, a, b, 458,
                                180, wxCAPTION | wxDEFAULT_DIALOG_STYLE,
                                "execute");
    }
    // Call the function to concat arguments
    strcpy(azTmp,azCatDir(azSetOption[0],azSetOption[4],azSetOption[2],
                          azSetOption[5],azFileEdit[WinNb]));
  
    // Give back the result in the dbox
    theApp.execute->GetExecuteCommandeLine->SetValue(azTmp);

    // is this operation possible (the command line is valid) ?
    strcpy (azString, azTmp);
    azPtr = strtok (azString," ");
    wxRemoveFile(MESSAGE);
    if (!wxFileExists(azPtr))
    {
      theApp.execute->Show(TRUE);
    }
    else
    {
      wxButton but;
      wxCommandEvent event;
      ButtonProc107(but, event);
    }
  }
  iAnswer=0;
  return;
}

// +----------+
// | Assemble |
// +----------+
void vAssemble(int WinNb)
{
  char azMessage[FILELEN + 1], *azPtr, azString[FILELEN + 1];
  int a,b,x,y,w,h;
  
  iAnswer = 0;

  // If the current TXT was modified
  if (theApp.win[WinNb]->textedit->Modified() )
  {
    theApp.win[WinNb]->GetPosition(&x,&y);
    a = x + SHIFT;
    b = y + SHIFT;
        
    // Call the constructor
    sprintf(azMessage,"%s\n%s", azFileEdit[WinNb],
            "has been changed, SAVE file ?");

    iAnswer = wxMessageBox(azMessage, "Confirmation", wxYES_NO | wxCANCEL
                           | wxCENTRE, theApp.win[WinNb], a, b);

    // If the answer is YES
    if ( iAnswer == wxYES )
    {
      iAnswer = 0;
      if (strcmp(azFileEdit[WinNb],"noname.c")==0)
      {
        // Display the file selection box
        // If no file selected, exit
        if ((pazF=wxFileSelector("Save file...", NULL, azFileEdit[WinNb] ,
                                 azExtension, azExtension, wxSAVE |
                                 wxOVERWRITE_PROMPT,
                                 theApp.win[WinNb], a, b))==NULL)
          return;
          strcpy(azFileEdit[WinNb],pazF);
      }
      // Save the active TXT
      theApp.win[WinNb]->textedit->SaveFile(azFileEdit[WinNb]);

      sprintf(azTitle[WinNb],"wxIDE -%d- [%s]\0", WinNb,
              azFileEdit[WinNb]);
      theApp.win[WinNb]->SetTitle(azTitle[WinNb]);

      vUpdateViewMenu(WinNb);

      // Save the active TXT
      theApp.win[WinNb]->textedit->SaveFile(azFileEdit[WinNb]);
    }
  }
  // If answer is not CANCEL
  if (iAnswer != wxCANCEL)
  {
    theApp.win[WinNb]->GetPosition(&x,&y);
    theApp.win[WinNb]->GetSize(&w, &h);
    a = x + ((w - 458) / 2);
    b = y + ((h - 180) / 2);

    // if the dbox doesn't exist
    if (!theApp.execute)
    {
      // call the constructor
      theApp.execute =
      new DialogBoxClassExecute(theApp.win[WinNb], "Execute:", TRUE, a, b, 458,
                                180, wxCAPTION | wxDEFAULT_DIALOG_STYLE,
                                "execute");
    }
    // call the function to concat the arguments
    strcpy(azTmp,azCatDir(azSetOption[0],azSetOption[6],azSetOption[2],
                          azSetOption[7],azFileEdit[WinNb]));

    // Give back the result in the dbox
    theApp.execute->GetExecuteCommandeLine->SetValue(azTmp);

    // is this operation possible (the command line is valid) ?
    strcpy (azString, azTmp);
    azPtr = strtok (azString," ");
    wxRemoveFile(MESSAGE);
    if (!wxFileExists(azPtr))
    {
      theApp.execute->Show(TRUE);
    }
    else
    {
      wxButton but;
      wxCommandEvent event;
      ButtonProc107(but, event);
    }
  }
  iAnswer=0;
  return;
}
