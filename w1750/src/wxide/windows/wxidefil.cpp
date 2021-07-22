//------------------------------------------------------------------------------
// FILE                                  :  wxidefil.cc
// SCCS                                  :  @(#) %M%, %I%, %H%
//                                    @(#)  wxIDE
// PROGRAM NAME                          :  wxIDE
// MODULE NAME                           :  editor 1
// DATE                                  :  01 may 1996
//                                          01 may 1997
// PROGRAMMER(s)                         :  WME
// LANGUAGE                              :  Borland C++ 4.51
// TYPE                                  :  Integrated Development Environment
//------------------------------------------------------------------------------
// Comment:
// Dialog Box = dbox
//-----------------------------------------------------------------------------

#include <string.h>
#include <stdio.h>
#include "wx.h"
#include "wxide.h"

// +--------------------------------+
// | New file in the current editor |
// +--------------------------------+
void vNewFile(int WinNb)
{
  char azMessage[FILELEN + 1];
  int a,b,x,y;
    
  // If the current TXT has been modified
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
      // Display the dbox for file selection
      // If no file is selected, exit
      if ((pazF = wxFileSelector("Save file...",NULL,azFileEdit[WinNb],
                                 azExtension,azExtension, wxSAVE |
                                 wxOVERWRITE_PROMPT,
                                 theApp.win[WinNb], a, b))==NULL)
        return;

      strcpy(azFileEdit[WinNb],pazF);

      // If the editor WinNb exists
      if (theApp.win[WinNb])
      {
        // Save the active TXT
        theApp.win[WinNb]->textedit->SaveFile(azFileEdit[WinNb]);
      }
    }

    // If answer is CANCEL
    else if (iAnswer == wxCANCEL)
    {
      iAnswer = 0;
      return;
    }
  }

  iAnswer = 0;

  // Initialise the TXT page
  theApp.win[WinNb]->textedit->Clear();

  // Prepare the name and the title
  strcpy(azFileEdit[WinNb],"noname.c");
  sprintf(azTitle[WinNb],"wxIDE -%d- [%s]\0",WinNb + 1,azFileEdit[WinNb]);
  theApp.win[WinNb]->SetTitle(azTitle[WinNb]);

  // Give to the other editors (if any) the new menu title
  vUpdateViewMenu (WinNb);
  
  return;
}

// +-----------+
// | Open File |
// +-----------+
void vOpen(int WinNb)
{
  char azMessage[FILELEN + 1];
  int a,b,x,y;

  // Prepare the position of the childs' windows
  theApp.win[WinNb]->GetPosition(&x,&y);
  a = x + SHIFT;
  b = y + SHIFT;

  // If the current TXT has been modified
  if (theApp.win[WinNb]->textedit->Modified() )
  {        
    // Call the constructor
    sprintf(azMessage,"%s\n%s", azFileEdit[WinNb],
            "has been changed, SAVE file ?");

    iAnswer = wxMessageBox(azMessage, "Confirmation", wxYES_NO | wxCANCEL
                           | wxCENTRE, theApp.win[WinNb], a, b);

    // If answer is YES
    if ( iAnswer == wxYES )
    {
      // Display the dbox for file selection
      // If no file is selected, exit
      if ((pazF = wxFileSelector("Save file...", NULL, azFileEdit[WinNb],
                                 azExtension, azExtension, wxSAVE |
                                 wxOVERWRITE_PROMPT,
                                 theApp.win[WinNb], a, b)) == NULL)
        return;
      strcpy(azFileEdit[WinNb],pazF);

      // Save the active TXT
      theApp.win[WinNb]->textedit->SaveFile(azFileEdit[WinNb]);
    }

    // If answer is NO
    else if (iAnswer == wxNO)
    {
      iAnswer = 0;
    }

    // if answer is CANCEL
    else if (iAnswer == wxCANCEL)
    {
      iAnswer = 0;
      return;
    }
  }

  // Display the dbox for file selection
  // If no file is selected, exit
  if ((pazF = wxFileSelector("Open file...", NULL, azExtension,
                             azExtension, azExtension, wxOPEN,
                             theApp.win[WinNb], a, b))==NULL )
    return;

  // Prepare the file and save the extension
  strcpy (azFileEdit[WinNb], pazF);
  vFormatExtensions();

  // Open the selected file
  theApp.win[WinNb]->textedit->LoadFile(azFileEdit[WinNb]);

  // Prepare the title
  sprintf(azTitle[WinNb],"wxIDE -%d- [%s]\0",WinNb + 1,
          azFileEdit[WinNb]);
  theApp.win[WinNb]->SetTitle(azTitle[WinNb]);

  // Give to the other editors (if any) the new menu title
  vUpdateViewMenu (WinNb);

  return;
}


// +------+
// | Save |
// +------+
void vSave(int WinNb)
{
  int a,b,x,y;

  // If the active TXT's name is "noname.c"
  if (strcmp(azFileEdit[WinNb],"noname.c")==0)
  {
    // Prepare the position of the child's window
    theApp.win[WinNb]->GetPosition(&x,&y);
    a = x + SHIFT;
    b = y + SHIFT;
    
    // Display the dbox for file selection
    // If no file is selected, exit
    if ((pazF = wxFileSelector("Save file...", NULL, azFileEdit[WinNb],
                               azExtension, azExtension, wxSAVE |
                               wxOVERWRITE_PROMPT,
                               theApp.win[WinNb], a, b))==NULL)
      return;

    strcpy(azFileEdit[WinNb],pazF);
  }

  // Prepare the window's title
  sprintf(azTitle[WinNb],"wxIDE -%d- [%s]\0",WinNb + 1,
          azFileEdit[WinNb]);
  theApp.win[WinNb]->SetTitle(azTitle[WinNb]);

  // Give to the other editors (if any) the new menu title
  vUpdateViewMenu (WinNb);

  // Save the file
  theApp.win[WinNb]->textedit->SaveFile(azFileEdit[WinNb]);
  
  return;
}

// +---------+
// | Save As |
// +---------+
void vSaveAs(int WinNb)
{
  int a,b,x,y;
  
  // Prepare the position of the child's window
  theApp.win[WinNb]->GetPosition(&x,&y);
  a = x + SHIFT;
  b = y + SHIFT;

  // Display the dbox for file selection
  // If no file is selected, exit
  if ((pazF =wxFileSelector("Save As...", NULL, azFileEdit[WinNb],
                            azExtension, azExtension, wxSAVE |
                            wxOVERWRITE_PROMPT,
                            theApp.win[WinNb], a, b))==NULL )
    return;

  strcpy(azFileEdit[WinNb],pazF);

  // Save the file under its new name
  theApp.win[WinNb]->textedit->SaveFile(azFileEdit[WinNb]);

  // Prepare the window's title
  sprintf(azTitle[WinNb],"wxIDE -%d- [%s]\0",WinNb + 1,
          azFileEdit[WinNb]);
  theApp.win[WinNb]->SetTitle(azTitle[WinNb]);

  // Give to the other editors (if any) the new menu title
  vUpdateViewMenu (WinNb);
  
  return;
}
