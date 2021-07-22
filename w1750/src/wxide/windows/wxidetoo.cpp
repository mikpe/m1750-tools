//------------------------------------------------------------------------------
// FILE                                  :  idetool.cc
// SCCS                                  :  @(#) %M%, %I%, %H%
//                                    @(#)  wxIDE
// PROGRAM NAME                          :  wxIDE
// MODULE NAME                           :  TOOL menu
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

// +------+
// | Grep |
// +------+
void vGrep(void)
{
  // If the box doesn't exist
  if (!theApp.execute)
  {
    // Call the constructor
    theApp.execute =
    new DialogBoxClassExecute(NULL, "Execute:", TRUE, 132, 132, 458, 180,
                              wxCAPTION | wxDEFAULT_DIALOG_STYLE, "execute");
  }
  // Call the function to concat the arguments
  strcpy(azTmp,azCatDir(azSetOption[0],azSetOption[12],"","",""));

  // On ERR
  if (strcmp(azTmp,"Error")!=0)
  {
    // Return the result in the dbox
    theApp.execute->GetExecuteCommandeLine->SetValue(azTmp);
    theApp.execute->Show(TRUE);
  }
  return;
}
