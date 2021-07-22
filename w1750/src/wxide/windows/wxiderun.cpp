//------------------------------------------------------------------------------
// FILE                                  :  iderun.cc
// SCCS                                  :  @(#) %M%, %I%, %H%
//                                    @(#)  wxIDE
// PROGRAM NAME                          :  wxIDE
// MODULE NAME                           :  RUNmenu
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

// +---------+
// | Execute |
// +---------+
void vExecute(void)
{
  // If the makefile exists
  if (azFileEdit[NB_EDITORS +1])
  {
    // If the dbox doesn't exist
    if (!theApp.execute)
    {
      // Call the constructor
      theApp.execute =
      new DialogBoxClassExecute(NULL, "Execute:", TRUE, 132, 132, 458, 180,
                                wxCAPTION | wxDEFAULT_DIALOG_STYLE, "execute");
    }

    // If the target is not NULL
    if (strcmp(azTarget,"")!=0)
    {
      // Send the result to the dbox
      theApp.execute->GetExecuteCommandeLine->SetValue(azTarget);
      theApp.execute->Show(TRUE);
    }
    return;
  }
}



// +-------+
// | Debug |
// +-------+
void vDebug(void)
{
  char *azPtr;
  char azString[FILELEN + 1];

  // If the dbox doesn't exist
  if (!theApp.execute)
  {
    theApp.execute =
    new DialogBoxClassExecute(NULL, "Execute", TRUE, 132, 132, 458, 180,
                              wxCAPTION | wxDEFAULT_DIALOG_STYLE, "execute");
  }
  // call the function to concat the arguments
  strcpy(azTmp,azCatDir(azSetOption[0],azSetOption[10],"","",""));

  // is this operation possible (the command line is valid) ?
  strcpy (azString, azTmp);
  azPtr = strtok (azString," ");

  if (!wxFileExists(azPtr))
  {
    theApp.execute->Show(TRUE);
    strcpy (azString, azTmp);
    azPtr = strtok (azString," ");
    if (!wxFileExists(azPtr))
    {
      wxBell();
    }
    else
    {
      wxShell(azTmp);
    }
  }
  else
  {
    wxShell(azTmp);
  }
  return;
}
