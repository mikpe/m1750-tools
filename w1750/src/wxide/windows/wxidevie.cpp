//------------------------------------------------------------------------------
// FILE                                  :  ideview.cc
// SCCS                                  :  @(#) %M%, %I%, %H%
//                                    @(#)  wxIDE
// PROGRAM NAME                          :  wxIDE
// MODULE NAME                           :  Menu view
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

// +-----------------------------------------+
// | View an editor on the top of the screen |
// +-----------------------------------------+
void vViewEdit(int Nb)
{
  // If the editor Nb exists, put it on the front of the screen
  if (theApp.win[Nb])
  {
    theApp.win[Nb]->Iconize(FALSE);
    theApp.win[Nb]->Show(TRUE);
  }
  return;
}


// +-------------------------+
// | View the message window |
// +-------------------------+
void vViewMessage(void)
{
  // If the window doesn't exist
  if (!theApp.win[NB_EDITORS])
  {
    // Call the constructor
    theApp.win[NB_EDITORS] =
    new FrameClassWin(NULL, "Message", 0,0, 640, 300,
                          wxSDI | wxDEFAULT_FRAME, "message",NB_EDITORS);
    theApp.win[NB_EDITORS]->Iconize(FALSE);
  }

  // If the window exists
  else
  {
    // Initialise the TXT page
    theApp.win[NB_EDITORS]->textedit->Clear();
  }

  // open the file containing STDOUT STDERR
  if (azSTDFile[0] != NULL)
    theApp.win[NB_EDITORS]->textedit->LoadFile(azSTDFile);

  theApp.win[NB_EDITORS]->Iconize(FALSE);

  // Display
  theApp.win[NB_EDITORS]->Show(TRUE);
  return;
}


// +--------------------------+
// | View the makefile window |
// +--------------------------+
void vViewMakefile(void)
{
  // If the window doesn't exist
  if (!theApp.win[NB_EDITORS + 1])
  {
    // Call the constructor
    theApp.win[NB_EDITORS + 1] =
    new FrameClassWin(NULL, azTitle[NB_EDITORS + 1], 0,0, 640, 300,
                           wxSDI | wxDEFAULT_FRAME, "makefile",NB_EDITORS + 1);
    theApp.win[NB_EDITORS + 1]->Iconize(FALSE);
  }

  // If the window exists
  else
  {
    // Initialise the page
    theApp.win[NB_EDITORS + 1]->textedit->Clear();
  }

  // Open the makefile
  theApp.win[NB_EDITORS + 1]->textedit->LoadFile(azFileEdit[NB_EDITORS + 1]);

  // Prepare the title
  sprintf (azTitle[NB_EDITORS + 1],"wxIDE -%d- [%s]\0",NB_EDITORS + 1,
           azFileEdit[NB_EDITORS + 1]);
  theApp.win[NB_EDITORS + 1]->SetTitle(azTitle[NB_EDITORS + 1]);
  theApp.win[NB_EDITORS + 1]->Iconize(FALSE);

  // Display 
  theApp.win[NB_EDITORS + 1]->Show(TRUE);
  return;
}
