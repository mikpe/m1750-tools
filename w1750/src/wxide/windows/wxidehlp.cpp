//------------------------------------------------------------------------------
// FILE                                  :  wxidehlp.cc
// SCCS                                  :  @(#) %M%, %I%, %H%
//                                    @(#)  wxIDE
// PROGRAM NAME                          :  wxIDE
// MODULE NAME                           :  help Menu
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
#include "wx_help.h"
#include "wxide.h"

// +------+
// | Help |
// +------+
void vHelp(int WinNb)
{
  #ifdef wx_msw
  wxExecute("WINHELP.EXE" ,TRUE);
  #else
  // Nothing
  #endif
}


// +-------+
// | About |
// +-------+
void vAbout(int WinNb)
{
  int a,b,x,y;
    
  // Prepare the position of the child's window
  theApp.win[WinNb]->GetPosition(&x,&y);
  a = x + SHIFT;
  b = y + SHIFT;
        
  int answer = wxMessageBox ("Portable Integrated Development Environment\nVer. 0.2 - May 1997\nCopyright © 1997 ESA/ESTEC/WME\nmaurizio@wm.estec.esa.nl\nESA/ESTEC/WME\nKeplerlaan 1, 2200AG Noodwijk, The Nethetherlands",
                              "About wxIDE",
                              wxOK | wxICON_INFORMATION | wxCENTRE,
                              theApp.win[WinNb], a, b);
}
