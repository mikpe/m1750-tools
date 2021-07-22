//------------------------------------------------------------------------------
// FILE                                  :  wxidesea.cc
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
#ifdef wx_msw
#define PLATFORM 1
#else
#define PLATFORM 0
#endif

// +------+
// | Find |
// +------+
void vFind(int WinNb)
{
  // Points the TXT
  char *azText=theApp.win[WinNb]->textedit->GetContents();
  char *azStringToSearch;
  long lLengthStringToSearch;
  long lLengthStringText;
  long i;
  int  x,y; // position of the parent window on the screen
  int  w,h; // size of the parent window
  int  a,b; // position for the Find Window

  // If the dbox doesn't exist
  if (!theApp.find)
  {
    // Prepare the position of the child's window
    theApp.win[WinNb]->GetPosition(&x,&y);
    theApp.win[WinNb]->GetSize(&w,&h);
    a = x + (w - 404)/2;
    b = y + (h - 188)/2;
    
    // Call the constructor
    theApp.find =
    new DialogBoxClassFind(theApp.win[WinNb], "Find", TRUE, a, b, 404, 188,
                           wxCAPTION | wxDEFAULT_DIALOG_STYLE, "find");
  }
  // Display with the old value
  theApp.find->GetFindText->SetValue(azStringUser);
  theApp.find->Show(TRUE);

  // If answer is OK
  if ( iAnswer==OK )
  {
    iAnswer = 0;
    azStringToSearch = strdup (azStringUser);

    // Length of the string given by the user
    lLengthStringToSearch = strlen(azStringToSearch);

    // TXT's length
    lLengthStringText = strlen(azText);

    // If not keysensitive
    if (iCheckSensitive==FALSE)
    {
      // Not keysensitive
      vMyStrlwr(azStringToSearch);
      vMyStrlwr(azText);
    }

    // i is the current TXT position
    for (i=0; i<(lLengthStringText - lLengthStringToSearch); i++)
    {
      // Compare both strings, if string found, select it
      if ( strncmp(azText+i,azStringToSearch,lLengthStringToSearch) == 0)
      {
        theApp.win[WinNb]->textedit->SetSelection(i,i+lLengthStringToSearch);
        break;
      }
    }
    delete azText;
    delete azStringToSearch;
    wxBell();
  }
  return;
}


// +---------+
// | Replace |
// +---------+
void vReplace (int WinNb)
{
  // Same method than FIND, here we replace what we found
  // with the new string given by the user
  // Ask the user for confrmation before each change
  char *pazText=theApp.win[WinNb]->textedit->GetContents();
  char *pazStringToSearch;
  long lLengthStringToSearch;
  long lLengthStringText;
  long i;
  long j;
  int  x,y; // position of the parent window on the screen
  int  w,h; // size of the parent window
  int  a,b; // position for the Find Window

    
  // If the dbox doesn't exist
  if (!theApp.replace)
  {
    // Prepare the position of the child's window
    theApp.win[WinNb]->GetPosition(&x,&y);
    theApp.win[WinNb]->GetSize(&w,&h);
    a = x + (w - 394)/2;
    b = y + (h - 256)/2;

    theApp.replace =
    new DialogBoxClassReplace(theApp.win[WinNb], "Replace", TRUE, a, b, 394, 256,
                              wxCAPTION | wxDEFAULT_DIALOG_STYLE, "replace");
  }
  // Display with the old values
  theApp.replace->GetReplaceOldText->SetValue(azStringUser);
  theApp.replace->GetReplaceNewText->SetValue(azStringUser2);
  theApp.replace->Show(TRUE);

  if ( iAnswer == OK )
  {
    iAnswer = 0;
    pazStringToSearch = strdup (azStringUser);

    // Length of the strings
    lLengthStringToSearch = strlen(azStringUser);
    lLengthStringText = strlen(pazText);

    // If not casesensitive
    if (iCheckSensitive==FALSE)
    {
      vMyStrlwr(pazStringToSearch);
      vMyStrlwr(pazText);
    }

    // Find and replace while the pointer is not at the end of the file
    i=0;
    j=0;
    while ( i<=(lLengthStringText - lLengthStringToSearch) )
    {
      if ( strncmp(pazText+i,pazStringToSearch,lLengthStringToSearch) == 0)
      {
        theApp.win[WinNb]->textedit->SetSelection(j,j+lLengthStringToSearch);

        if (iCheckAll == FALSE)
        {
          a = x + SHIFT;
          b = y + SHIFT;
          iAnswer = wxMessageBox("Replace this occurrence ?", "Confirmation",
                                 wxYES_NO | wxCANCEL | wxICON_QUESTION,
                                 theApp.win[WinNb],a,b);
          // If CANCEL exit
          if (iAnswer == wxCANCEL)
          {
            iAnswer = 0;
            break;
          }
        }
        if (iAnswer == wxYES || iCheckAll == TRUE)
        {
          theApp.win[WinNb]->textedit->Remove(j,j+lLengthStringToSearch);
          theApp.win[WinNb]->textedit->WriteText(azStringUser2);
          j = j + strlen(azStringUser2) - 1;
          i = i + lLengthStringToSearch - 1;
        }
      }
      iAnswer = 0;
      i++;
      j++;
    }
    delete pazText;
    delete pazStringToSearch;
  }
  return;
}


// +-----------+
// | Goto Line |
// +-----------+
void vGotoLine(int WinNb)
{
  int lLength=0,i;
  int  x,y; // position of the parent window on the screen
  int  w,h; // size of the parent window
  int  a,b; // position for the Find Window

  // If the dbox doesn't exist
  if (!theApp.gotoline)
  {
    // Prepare the position of the child's window
    theApp.win[WinNb]->GetPosition(&x,&y);
    theApp.win[WinNb]->GetSize(&w,&h);
    a = x + (w - 302)/2;
    b = y + (h - 168)/2;

    // Call the constructor
    theApp.gotoline =
    new DialogBoxClassGotoline(theApp.win[WinNb], "Goto line:", TRUE, a, b,
                               302, 168, wxCAPTION | wxDEFAULT_DIALOG_STYLE,
                               "gotoline");
  }
  // Display
  theApp.gotoline->Show(TRUE);

  
  // If answer is OK
  if ( iAnswer == OK )
  {
    iAnswer =0;

    // If the number given by the user is > nb of lines of the file
    // Go to the end of the file
    if (iLinenumber > theApp.win[WinNb]->textedit->GetNumberOfLines() )
    {
      iLinenumber = theApp.win[WinNb]->textedit->GetNumberOfLines();
    }

    lLength = theApp.win[WinNb]->textedit->XYToPosition(0,(long)iLinenumber-1);
    theApp.win[WinNb]->textedit->ShowPosition (lLength);
    // Select the line found
    theApp.win[WinNb]->textedit->SetSelection(lLength,
                           lLength + theApp.win[WinNb]->
                           textedit->GetLineLength(iLinenumber-1));
    wxBell();
  }
  return;
}

// +--------------+
// | Search Again |
// +--------------+
void vSearchAgain(int WinNb)
{
  // Points the TXT
  char *azText=theApp.win[WinNb]->textedit->GetContents();
  char *azStringToSearch;
  long lLengthStringToSearch;
  long lLengthStringText;
  long i;

  azStringToSearch = strdup (azStringUser);

  if (azStringToSearch[0] != NULL)
  {
    // Length of the string given by the user
    lLengthStringToSearch = strlen(azStringToSearch);

    // TXT's length
    lLengthStringText = strlen(azText);

    // If not keysensitive
    if (iCheckSensitive==FALSE)
    {
      // Not keysensitive
      vMyStrlwr(azStringToSearch);
      vMyStrlwr(azText);
    }

    // i is the current TXT position
    for (i=theApp.win[WinNb]->textedit->GetInsertionPoint() + PLATFORM;
         i<(lLengthStringText - lLengthStringToSearch); i++)
    {
      // Compare both strings, if string found, select it
      if ( strncmp(azText+i,azStringToSearch,lLengthStringToSearch) == 0)
      {
        theApp.win[WinNb]->textedit->SetSelection(i,i+lLengthStringToSearch);
        break;
      }
    }
  }
  delete azText;
  delete azStringToSearch;
  wxBell();

  return;
}
