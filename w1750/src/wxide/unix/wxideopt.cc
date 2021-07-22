//------------------------------------------------------------------------------
// FILE                                  :  ideopt.cc
// SCCS                                  :  @(#) %M%, %I%, %H%
//                                    @(#)  wxIDE
// PROGRAM NAME                          :  wxIDE
// MODULE NAME                           :  options menu
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


// +-------------+
// | Set Options |
// +-------------+
void vSet(int WinNb)
{
  int  x,y; // position of the parent window on the screen
  int  w,h; // size of the parent window
  int  a,b; // position for the Find Window

  // Prepare the position of the child's window
  theApp.win[WinNb]->GetPosition(&x,&y);
  theApp.win[WinNb]->GetSize(&w,&h);
  a = x + (w - 640)/2;
  b = y + (h - 380)/2;

  // If the dbox doesn't exist
  if (!theApp.set)
  {
    // Call the constructor
    theApp.set =
    new DialogBoxClassSet(theApp.win[WinNb], "Set:", TRUE, a, b, 640, 380,
                          wxCAPTION | wxDEFAULT_DIALOG_STYLE, "set");
  }
  // Put the parameters in the panel
  theApp.set->GetSetDirBin->SetValue(azSetOption[0]);
  theApp.set->GetSetDirWork->SetValue(azSetOption[1]);
  theApp.set->GetSetDirInclude->SetValue(azSetOption[2]);
  theApp.set->GetSetDirLib->SetValue(azSetOption[3]);
  theApp.set->GetSetCompilerName->SetValue(azSetOption[4]);
  theApp.set->GetSetCompilerOptions->SetValue(azSetOption[5]);
  theApp.set->GetSetAssemblerName->SetValue(azSetOption[6]);
  theApp.set->GetSetAssemblerOptions->SetValue(azSetOption[7]);
  theApp.set->GetSetMakefileName->SetValue(azSetOption[8]);
  theApp.set->GetSetMakefileOptions->SetValue(azSetOption[9]);
  theApp.set->GetSetDebuggerName->SetValue(azSetOption[10]);
  theApp.set->GetSetDebuggerOptions->SetValue(azSetOption[11]);
  theApp.set->GetSetGrepName->SetValue(azSetOption[12]);
  theApp.set->GetSetExtensions->SetValue(azSetOption[13]);
  
  strcpy (azExtension, azSetOption[13]);
  vFormatExtensions();
  
  // Display
  theApp.set->Show(TRUE);
}


// +--------------+
// | Load Options |
// +--------------+
void vLoadOptions(int WinNb)
{
  int r;
  int  x,y; // position of the parent window on the screen
  int  a,b; // position for the Find Window

  // Prepare the position of the child's window
  theApp.win[WinNb]->GetPosition(&x,&y);
  a = x + SHIFT;
  b = y + SHIFT;
  
  // Display the file selection box
  // If no file select, exit
  if ((pazF=wxFileSelector("Load...",NULL,"ide.cfg","*.cfg","*.cfg", wxOPEN, 
                           theApp.win[WinNb], a, b))==NULL)
    return;

  // If a file is selected
  if (pazF)
  {
    // clear the table
    for (r=0; r<14; r++)
    {
      azSetOption[r][0] = '\0';
    }
    pfSetOption = fopen(pazF,"r");

    // Oopen the CFG file
    for (r=0; r<14; r++)
    {
      fscanf(pfSetOption,"%[^\n]%*c",azSetOption[r]);
      if (!strcmp(azSetOption[r], "(null)"))
      {
        azSetOption[r][0] = '\0';
      }
    }
    strcpy (azExtension, azSetOption[13]);
    vFormatExtensions();
    
    fclose(pfSetOption);
  }
}


// +--------------+
// | Save Options |
// +--------------+
void vSaveOptions(int WinNb)
{
  int r;
  int  x,y; // position of the parent window on the screen
  int  a,b; // position for the Find Window

  // Prepare the position of the child's window
  theApp.win[WinNb]->GetPosition(&x,&y);
  a = x + SHIFT;
  b = y + SHIFT;
  
  // Display the file selection box
  // If no file selected, exit
  if ((pazF=wxFileSelector("Save...",NULL,"ide.cfg","*.cfg","*.cfg", wxSAVE |
                           wxOVERWRITE_PROMPT, theApp.win[WinNb], a, b))==NULL)
    return;

  // If a file is selected
  if (pazF)
  {
    pfSetOption = fopen(pazF,"w");
    // Save the CFG file
    for (r=0; r<14; r++)
    {
      if (strlen(azSetOption[r]))
      {
        fprintf(pfSetOption,"%s\n",azSetOption[r]);
      }
      else
      {
        fprintf(pfSetOption, "(null)\n");
      }
    }
    fclose(pfSetOption);
  }
}
