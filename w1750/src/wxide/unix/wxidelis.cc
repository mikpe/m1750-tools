//------------------------------------------------------------------------------
// FILE                                  :  wxidelis.cc
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

#include <string.h>
#include <ctype.h>
#include "wx.h"
#include "wxide.h"
#include "wx_cmdlg.h"
#include "wx_popup.h"
#include "srchdlg.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
// Include for MSW
#ifdef wx_msw
#include <io.h>
#include <process.h>
#define MAX_WXPOPUP 3
#else
#define MAX_WXPOPUP 2
#endif

void wxPopupMenuViewButton(wxButton& but, wxEvent& event);
void wxPopupMenuExitButton(wxButton& but, wxEvent& event);

void wxPopupMenuViewButton(wxButton& but, wxEvent& event)
{
   wxPanel *panel = (wxPanel *)but.GetParent();
   while (!panel->IsKindOf(CLASSINFO(wxDialogBox)))
           panel = (wxPanel*) panel->GetParent() ;

   wxPopupMenu *dialog = (wxPopupMenu *)panel;
   dialog->SelectOk();
//   dialog->Show(FALSE);
}

void wxPopupMenuExitButton(wxButton& but, wxEvent& event)
{
    wxPanel *panel = (wxPanel *)but.GetParent();
    while (!panel->IsKindOf(CLASSINFO(wxDialogBox)))
            panel = (wxPanel*) panel->GetParent() ;

    wxPopupMenu *dialog = (wxPopupMenu *)panel;
    dialog->Show(FALSE);
}

void wxPopupMenuProc(wxVirtListBox& list, wxCommandEvent& event)
{
    wxPopupMenu * popup = (wxPopupMenu *)list.wxWindow::GetParent();
    popup->ProcessCommand(event);
}

wxPopupMenu::wxPopupMenu(wxFrame * parent, wxFunction func,
                int x, int y, int width, int height,
                char * Title,
                CPFPCPI get_optx, char *garg,
                FPCPPI execf, char *earg[],
                int nrows, long style):
            GetOptx(get_optx), gArg(garg),
            ExecF(execf), eArg(earg),
            Style(style), nRows(nrows),
            Width(width), Height(height),
            wxDialogBox(parent, Title, FALSE, x, y, width, height,
                style)
{
    SearchStr[0] = 0;
    SearchDown = TRUE;
    IgnoreCase = FALSE;
    Callback(func);
    vListBox = NULL;
}

wxPopupMenu::~wxPopupMenu(void)
{
   	if (vListBox)
   		delete vListBox;
}

int wxPopupMenu::Execute()
{
#define DEF_LISTBOX_WIDTH  600

  int dlg_w, dlg_h;
  int listbox_w, listbox_h;
  int button_x, button_y, button_w, button_h;
  int iMessageOutput;
  int a,b,x,y;
  
  // Prepare the position of the child's window
  theApp.win[NB_EDITORS]->GetPosition(&x,&y);
  a = x + SHIFT;
  b = y + SHIFT;

  if (GetOptx(gArg, 1) == NULL) {
    wxMessageBox("No compilation error !", "Warning", wxOK,
                 theApp.win[NB_EDITORS], a, b);
    return wxERROR;
  }

  GetClientSize(&dlg_w, &dlg_h);

  if (Width < 0 || Height < 0)
  {
    if (Width < 0)
      dlg_w = 800;
    if (Height < 0) {
      if (nRows > -1)
      dlg_h = 1280;
    else
      dlg_h = 340;
    }
    SetClientSize(dlg_w, dlg_h);
  }

  // Estimating the size of button
  view = new wxButton(this, (wxFunction)&wxPopupMenuViewButton, "View");
  view->GetSize(&button_w, &button_h);

  if (dlg_h < 5 * button_w + 6 * PANEL_VSPACING) {
    dlg_h = 5 * button_w + 6 * PANEL_VSPACING;
    SetClientSize(dlg_w, dlg_h);
  }

  // Setting the width of dialog for Width = -1
  if (Width < 0) {
    dlg_w = DEF_LISTBOX_WIDTH + 3 * PANEL_HSPACING  + button_w;
    SetClientSize(dlg_w, dlg_h);
  }

  listbox_w = dlg_w - 3 * PANEL_HSPACING - button_w;
  listbox_h = dlg_h - 2 * PANEL_VSPACING;

  // to avoid the display of a warning under UNIX
  iMessageOutput = open ("/dev/null", O_WRONLY);
  close (2);
  dup (iMessageOutput);

  vListBox = new wxVirtListBox(this, (wxFunction)&wxPopupMenuProc, GetOptx,
                               gArg, NULL, nRows, wxSINGLE|wxNEEDED_SB,
                               PANEL_HSPACING, PANEL_VSPACING,
                               listbox_w, listbox_h);
  vListBox->GetSize(&listbox_w, &listbox_h);
  button_x = listbox_w + 2 * PANEL_HSPACING;
  button_y = PANEL_VSPACING;

  view->SetSize(button_x, button_y, button_w, button_h);
  button_y += button_h + PANEL_VSPACING;

  exit = new wxButton(this, (wxFunction)&wxPopupMenuExitButton, "Close",
                      button_x, button_y);
  exit->GetSize(&button_w, &button_h);
  button_y -= button_h + PANEL_VSPACING;
  view->SetSize(button_x, button_y, button_w, button_h);

  view->SetDefault();

  if (Height < 0 || Width < 0)
    Fit();

  Show(TRUE);
  return GetSelection();
}


void wxPopupMenu::SelectOk()
{
  if (ExecF && (GetSelection() != wxERROR))
    (*ExecF)(eArg, GetSelection());
}

void wxPopupMenu::SetSelection(int n)
{
  vListBox->SetSelection(n);
}

void wxPopupMenu::Fit(void) {
  int dlg_w, dlg_h, w, h;
  int listbox_w, listbox_h;
  int button_x, button_y, button_w, button_h;

  vListBox->GetSize(&listbox_w, &listbox_h);
  exit->GetSize(&button_w, &button_h);
  exit->GetPosition(&button_x, &button_y);

  dlg_w = button_x + button_w + PANEL_HSPACING;
  dlg_h = wxMax(PANEL_VSPACING + listbox_h, button_y + button_h) + PANEL_VSPACING;
  GetClientSize(&w, &h);
  if (w != dlg_w || h != dlg_h)
    SetClientSize(dlg_w, dlg_h);
}

void wxPopupMenu::ProcessCommand (wxCommandEvent & event)
{
  if (wxNotifyEvent (event, TRUE))
    return;

  wxFunction fun = callback;
  if (fun)
    (void) (*(fun)) (*this, event);

  wxNotifyEvent (event, FALSE);
}

static int nItems  = 0;

typedef struct SList {
  int Number;
  char * String;
  SList * Next;
} List;

List *MyList, MyListFirst;
static int j=0;

char * Item(char * arg, int n)
{
  int i;
  static char sz[128];

  if (n == 1 && nItems == 1)
  {
    j++;
    if (j == 1) return ("1");
    if (j == MAX_WXPOPUP)
    {
      j = 0;
      return NULL;
    }
  }

  MyList = &MyListFirst;
  if (n < nItems)
  {
    i=0;
    while (i < n && MyList->Next != NULL)
    {
      i++;
      MyList = MyList->Next;
    }
  }
  if (n > nItems) return NULL;
  if (n == nItems && n != 1) return NULL;
  if (MyList->Next == NULL)
    return NULL;
  else
    return MyList->String;
  return NULL;
}

void OnExit(char ** ear, int n)
{
  char sz[128], azFileNameError[FILELEN];
  char * pazS;
  int iLine;
  int iWinNb;
  long lLength;

  strcpy (sz, Item ("", n));
  pazS = strstr (sz, ":");
  pazS[0] = NULL;
  strcpy (azFileNameError,sz);
  strcpy (sz, &sz[strlen(azFileNameError) + 1]);
  pazS = strstr(sz," ");
  pazS[0] = NULL;
  sscanf (sz,"%d",&iLine);
  iWinNb = 0;
  lLength = 0;
  for (iWinNb = 0 ; iWinNb < NB_EDITORS ; iWinNb++)
  {
    if (strstr(azFileEdit[iWinNb], azFileNameError) != 0)
    {
      theApp.win[iWinNb]->Iconize(FALSE);
      theApp.win[iWinNb]->Show(TRUE);
      // If the number given is > nb of lines of the file
      // Go to the end of the file
      if (iLine > theApp.win[iWinNb]->textedit->GetNumberOfLines() )
      {
        iLine = theApp.win[iWinNb]->textedit->GetNumberOfLines();
      }

      lLength = theApp.win[iWinNb]->textedit->XYToPosition(0,(long)iLine-1);
      theApp.win[iWinNb]->textedit->ShowPosition (lLength);
      // Select the line found
      theApp.win[iWinNb]->textedit->SetSelection(lLength,
                             lLength + theApp.win[iWinNb]->
                             textedit->GetLineLength(iLine-1));
      wxBell();
      return;
    }
  }
  sprintf (sz, "The File %s is not opened.", azFileNameError);
  wxMessageBox (sz, "Error");
}

void vViewErrors()
{
  FILE *pFFile, *f;
  char azStr[FILELEN + 1], azStr2[FILELEN + 1], azName[FILELEN + 1];
  char azExt[FILELEN + 1];
  char *pazS, *pazS2, *pazS3;
  int iLine, n=-1;

  MyList = &MyListFirst;
  MyList->Next = NULL;
  
  if ((pFFile = fopen (MESSAGE,"r"))!=0)
  {
    while (!feof(pFFile))
    {
      fgets (azStr, FILELEN, pFFile);

// search for a filename
      strcpy (azExt, azSetOption[13]);
      pazS3 = strtok (azExt, ";");

      pazS = NULL;
      while (pazS3 != NULL && (pazS = strstr (azStr, pazS3)) == NULL)
      {
        pazS3 = strtok (NULL, ";");
        if (pazS3 == NULL) break;
      }

      if (pazS == NULL) continue;
      pazS2 = pazS;
      pazS2++;

      while ((pazS2[0] >= 'a' && pazS2[0] <= 'z') ||
             (pazS2[0] >= 'A' && pazS2[0] <= 'Z'))
      {
        pazS2++;
      }

// Copy the end of the string (to get the line nb and the text of the error)
      strcpy (azStr2, pazS2);

      if (strlen(azStr2) < 2) continue;

      pazS2[0] = NULL;
      pazS--;
      while ((pazS[0] >= 'a' && pazS[0] <= 'z') ||
             (pazS[0] >= 'A' && pazS[0] <= 'Z'))
      {
        pazS--;
      }
      pazS++;
      sprintf (azName,"%s",pazS);

// search for a line number
      pazS = &azStr2[0];
      while ((pazS[0] < '0' || pazS[0] > '9') && pazS[0] != NULL)
      {
        pazS++;
      }

      if (pazS[0] == NULL) continue;
      strcpy(azStr2, pazS);
      while (pazS[0] >= '0' && pazS[0] <= '9')
      {
        pazS++;
      }
      pazS[0] = NULL;
      sscanf(azStr2, "%d", &iLine);

      sprintf (azStr,"%s:%d %s", azName,iLine,&pazS[1]);
      n++;
      nItems = n + 1;

      azStr[strlen(azStr)-1] = NULL;
      MyList->String = strdup (azStr);
      MyList->Next = new List;
      MyList = MyList->Next;
      MyList->Next = NULL;
    }
    wxPopupMenu * menu = new wxPopupMenu(theApp.win[NB_EDITORS],
                                         (wxFunction) NULL, 100, 200, -1, -1,
                                         "Errors' List", Item, NULL, OnExit,
                                         NULL, 20);
    int selection = menu->Execute();
    // delete menu;
  }
}
