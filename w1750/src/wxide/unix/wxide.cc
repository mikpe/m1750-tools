//------------------------------------------------------------------------------
// FILE                                  :  wxide.cc
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

#define Main
#include <string.h>
#include <stdio.h>
#include "wx.h"
#include <wx_timer.h>
#include "wxide.h"

FILE *f;

// +------------------------+
// | Objects Initialisation |
// +------------------------+
wxFrame *AppClass::OnInit(void)
{
  int i;
  
  for (i=0; i < (NB_EDITORS + 2); i++)
  {
    win[i] = NULL;
    azTitle[i][0]='\0';
  }

  find = NULL;
  replace = NULL;
  gotoline = NULL;
  settarget = NULL;
  execute = NULL;
  set = NULL;
  confirmation = NULL;

  if (!ParseCommandLine()) return NULL;

  // Build the title, extension, new file name
  for (i = 0; i < 14; i++)
  {
    azSetOption[i][0] = NULL;
  }

  strcpy(azExtension, azSetOption[13]);
  vFormatExtensions();
  strcpy(azFileEdit[NB_EDITORS+1],"noname.mak");
  strcpy(azFileEdit[0],"noname.c");
  for (i=1;i<NB_EDITORS;i++)
  {
    strcpy(azFileEdit[i],"");
  }
  
  for (i=0;i<NB_EDITORS;i++)
  {
    sprintf (azTitle[i],"wxIDE -%d- [%s]",i+1,azFileEdit[i]);
  }
  sprintf (azTitle[NB_EDITORS],"Message");
  
  // Affects the window to the pointer
  win[0] =
  new FrameClassWin(NULL,azTitle[0],0,0,640,480,wxSDI|wxDEFAULT_FRAME,
                    azTitle[0],0);
  theApp.win[0]->SetTitle(WXIDE_VERSION);
  vUpdateViewMenu (0);
  my_timer = new MyTimer();
  my_timer->Start(TIMER_DELAY);
  azSTDFile[0] = NULL;

  return win[0];
}

// +-----------------------+
// | Command line analysis |
// +-----------------------+
Bool AppClass::ParseCommandLine(void)
{
  return TRUE;
}


// X Compilation option
#ifdef wx_x
#include "win.xpm"
#endif

// +----------------------------+
// | Construction of the editor |
// +----------------------------+
FrameClassWin::FrameClassWin(wxFrame *parent, char *title, int x, int y,
                               int width, int height, long style, char *name,
                               int Nb):
wxFrame(parent, title, x, y, width, height, style, name)
{
  int i;
  char * pazString;
  
  // Empty TXT under window
  textedit = NULL;
  
  // Number of the window
  WinNb = Nb;

// X Compilation option
#ifdef wx_x
//  wxIcon *frameIcon = new wxIcon(win_bits, win_width, win_height);
  wxIcon *frameIcon = new wxIcon(win_xpm);
#endif

// MSW Compilation option
#ifdef wx_msw
  wxIcon *frameIcon = new wxIcon("win", wxBITMAP_TYPE_ICO);
#endif

  // Affectation of the icon to the window
  SetIcon(frameIcon);

  // Help bar construction at the bottom of the window
  CreateStatusLine(NB_STATUS_LINES);

  // Menu bar construction
  wxMenuBar *MenuBar = new wxMenuBar;

  // FILE menu construction (only for editors)
  // -----------------------------------------
  if (WinNb < NB_EDITORS)
  {
    wxMenu *Menu1 = new wxMenu;
    Menu1->Append(NEWEDITWIN_ID, "New edit &window",
                  "Create a new file in a new edit window.");
    Menu1->AppendSeparator();
    Menu1->Append(NEW_ID, "&New",
                  "Create a new file in the current window.");
    Menu1->Append(OPEN_ID, "&Open...",
                  "Locate and open a file in the active window.");
    Menu1->Append(SAVE_ID, "&Save",
                  "Save the file of the active window.");
    Menu1->Append(SAVEAS_ID, "Save &As...",
                  "Save the file of the active window under a new name.");
    Menu1->AppendSeparator();
    // Menu1->Append(PRINT_ID,"&Print",
    //               "Print the contents of the active edit window.");
    // Menu1->AppendSeparator();
    if (WinNb!=0)
    {
      Menu1->Append(CLOSE_ID, "&Close",
                    "Close Current Window.");
    }
    else
    {
      Menu1->Append(EXIT_ID, "&Exit",
                    "Exit wxIDE.");
    }
    MenuBar->Append(Menu1, "&File");
  }
  // EDIT menu construction
  // ----------------------
  wxMenu *Menu2 = new wxMenu;
  // Menu2->Append(UNDO_ID, "&Undo",
  //              "Undo the previous editor action.");
  // Menu2->AppendSeparator();
  Menu2->Append(CUT_ID, "Cu&t",
                "Remove the selected text and put it in the clipboard.");
  Menu2->Append(COPY_ID, "&Copy",
                "Place a copy of the selected text in the clipboard.");
  Menu2->Append(PASTE_ID, "&Paste",
                "Insert text from the clipboard at the cursor position.");
  Menu2->AppendSeparator();
  Menu2->Append(DELETE_ID, "&Delete",
                "Delete the selection text.");
  if (WinNb == NB_EDITORS) Menu2->Append(CLOSE_ID, "&Close",
                                        "Close Current Window.");
  if (WinNb <= NB_EDITORS) MenuBar->Append(Menu2, "&Edit");

  // SEARCH menu construction
  // ------------------------
  wxMenu *Menu3 = new wxMenu;
  Menu3->Append(FIND_ID, "&Find...",
                "Search for text.");
  Menu3->Append(REPLACE_ID, "&Replace...",
                "Search for text and replace in with new text.");
  Menu3->Append(SHEARCHAGAIN_ID, "&Search again",
                "Repeat the last find or replace operation.");
  Menu3->AppendSeparator();
  Menu3->Append(GOTOLINE_ID, "&Goto line...",
                "Goto the specified line.");
  if (WinNb <= NB_EDITORS) MenuBar->Append(Menu3, "&Search");

  if (WinNb != NB_EDITORS)
  {
    // MAKE menu construction
    // ----------------------
    wxMenu *Menu5 = new wxMenu;
    Menu5->Append(NEWMAKEF_ID, "&New makefile",
                  "Create a new makefile.");
    Menu5->Append(OPENMAKEF_ID,"&Open makefile...",
                  "Locate and open makefile.");
    Menu5->Append(SAVEMAKEF_ID, "&Save makefile",
                  "Save the makefile of the active window.");
    Menu5->Append(SAVEASMAKEF_ID, "Save A&s...",
                  "Save the makefile of the active window under a new name.");
    Menu5->AppendSeparator();
    if (WinNb != (NB_EDITORS + 1))
    {
      Menu5->Append(COMPILE_ID, "&Compile",
                    "Compile the active file.");
      Menu5->Append(ASSEMBLE_ID, "&Assemble",
                    "Assemble the active file.");
      Menu5->AppendSeparator();
    }
    Menu5->Append(SETTARGET_ID, "Set &target",
                  "Identifiy the target to be generated.");
    Menu5->Append(MAKETARGET_ID, "&Make target",
                  "Compile / link the necessery files.");
    Menu5->Append(BUILDTARGET_ID, "&Build target",
                  "Compile / link all the files.");
    if (WinNb > NB_EDITORS)
    {
      Menu5->AppendSeparator();
      Menu5->Append(CLOSE_ID, "&Close","Close Current Window.");
    }
    MenuBar->Append(Menu5, "&Make");
    if (WinNb > NB_EDITORS)
    {
      MenuBar->Append(Menu2, "&Edit");
      MenuBar->Append(Menu3, "&Search");
    }
  }
  else
  {
    // ERRORS menu construction
    // ----------------------
    wxMenu *Menu5 = new wxMenu;
    Menu5->Append(ERRORS_ID, "&View Errors",
                  "View the errors in the source file.");
    MenuBar->Append(Menu5, "&Errors");
  }

  if (WinNb < NB_EDITORS)
  {
    // RUN menu construction
    // ---------------------
    wxMenu *Menu6 = new wxMenu;
    Menu6->Append(EXECUTE_ID, "&Execute",
                  "Run program.");
    Menu6->Append(DEBUG_ID, "&Debug",
                  "Debug program.");
    MenuBar->Append(Menu6, "&Run");

    // TOOL menu contruction
    // ---------------------
    wxMenu *Menu7 = new wxMenu;
    Menu7->Append(GREP_ID, "&Grep",
                  "Load tool grep.");
    MenuBar->Append(Menu7, "&Tool");

    // OPTIONS menu construction
    // -------------------------
    wxMenu *Menu8 = new wxMenu;
    Menu8->Append(SET_ID, "Se&t...", "Set options.");
    Menu8->AppendSeparator();
    Menu8->Append(LOADOPTION_ID, "&Load options...",
                  "Load options.");
    Menu8->Append(SAVEOPTION_ID, "&Save options...",
                  "Save options.");
    MenuBar->Append(Menu8, "&Options");
  }

  // VIEW menu construction
  // ----------------------
  Menu4 = new wxMenu;
  for (i=0;i<NB_EDITORS;i++)
  {
    pazString = new char[strlen(azTitle[i]) + 13];
    sprintf (pazString,"View Editor %s\0",azTitle[i]);
    Menu4->Append(EDITOR1_ID+i, azTitle[i], pazString);
    delete pazString;
  }
  Menu4->AppendSeparator();
  Menu4->Append(MESSAGE_ID, "&Message",
                "View Message.");
  Menu4->Append(MAKEFILE_ID, "Ma&kefile",
                "View Makefile.");
  MenuBar->Append(Menu4, "&View");
  
  // HELP menu construction
  // ----------------------
  wxMenu *Menu9 = new wxMenu;
//  Menu9->Append(CONTENTS_ID,"&Contents",
//                "Help system.");
//  Menu9->AppendSeparator();
  Menu9->Append(ABOUT_ID, "&About wxIDE", "About wxIDE.");
  MenuBar->Append(Menu9, "&Help");
  SetMenuBar(MenuBar);

  // TXT border construction
  textedit =
  new TextWindowClassWin (this,0, 0,430,101,wxBORDER,"textedit");

  // allow windows' resize by the user
  OnSize (width,height);

  // Displays on screen all the constructions
  Show(TRUE);
}

// +------------+
// | Destructor |
// +------------+
FrameClassWin::~FrameClassWin(void)
{
}

// +-----------------------------------------+
// | Window closing by the upper left corner |
// +-----------------------------------------+
Bool FrameClassWin::OnClose(void)
{
  int i, SavWinNb = WinNb;
  char * pazString;
  
  if (SavWinNb == 0)
  {
    vEndApp();
  }
  else
  {
    vEndWin (SavWinNb);
  }
  
  // if the close function is cancelled
  if (theApp.win[SavWinNb]) return FALSE;

  azFileEdit[SavWinNb][0]='\0';
  if (SavWinNb < NB_EDITORS)
  {
    sprintf (azTitle[SavWinNb],"wxIDE -%d- [%s]",SavWinNb + 1,azFileEdit[SavWinNb]);
  }
  else
  {
    if (SavWinNb == NB_EDITORS) sprintf (azTitle[SavWinNb],"Message");
    if (SavWinNb > NB_EDITORS) sprintf (azTitle[SavWinNb],"Makefile [%s]", azFileEdit[SavWinNb]);
  }
  // Give to the other editors (if any) the new menu title
  vUpdateViewMenu (SavWinNb);
  
  // Destruction OK
  return FALSE;
}

// +-----------------------------------+
// | allow window's resize by the user |
// +-----------------------------------+
void FrameClassWin::OnSize(int w, int h)
{
   wxFrame::OnSize(w, h);
}


// +-----------------------------+
// | Check if the menu is active |
// +-----------------------------+
void FrameClassWin::OnMenuCommand(int commandId)
{
  int i;
  char *pazString;

  
  wxBeginBusyCursor(wxHOURGLASS_CURSOR);
  switch (commandId)
  {
    // FILE MENU
    // =========
    // New window
    case NEWEDITWIN_ID:
    {
      vNewWin();
      break;
    }

    // New
    case NEW_ID:
    {
      vNewFile(WinNb);
      break;
    }

    // Open...
    case OPEN_ID:
    {
      vOpen(WinNb);
      break;
    }

    // Save
    case SAVE_ID:
    {
      vSave(WinNb);
      break;
    }

    // Save As...
    case SAVEAS_ID:
    {
      vSaveAs(WinNb);
      break;
    }

    // Print
    case PRINT_ID:
    {
      // This part is still under developpement
      break;
    }

    // Close
    case CLOSE_ID:
    {
      theApp.win[WinNb]->OnClose();
      break;
    }

    // Exit
    case EXIT_ID:
    {
      vEndApp();
      break;
    }


    // EDIT MENU
    // =========
    // Undo
    case UNDO_ID:
    {
      // This part is still under developpement
      break;
    }

    // Cut
    case CUT_ID:
    {
      theApp.win[WinNb]->textedit->Cut();
      break;
    }

    // Copy
    case COPY_ID:
    {
      theApp.win[WinNb]->textedit->Copy();
      break;
    }

    // Paste
    case PASTE_ID:
    {
      theApp.win[WinNb]->textedit->Paste();
      break;
    }

    // Delete
    case DELETE_ID:
    {
      theApp.win[WinNb]->textedit->Cut();
      break;
    }


    // SEARCH MENU
    // ===========
    // Find...
    case FIND_ID:
    {
      vFind(WinNb);
      break;
    }

    // Replace...
    case REPLACE_ID:
    {
      vReplace(WinNb);
      break;
    }

    // Search again
    case SHEARCHAGAIN_ID:
    {
      vSearchAgain(WinNb);
      break;
    }

    // Goto line...
    case GOTOLINE_ID:
    {
      vGotoLine(WinNb);
      break;
    }


    // VIEW MENU
    // =========
    // View Editor i
    case EDITOR1_ID:
    {
      vViewEdit(0);
      break;
    }
    case EDITOR2_ID:
    {
      vViewEdit(1);
      break;
    }
    case EDITOR3_ID:
    {
      vViewEdit(2);
      break;
    }
    case EDITOR4_ID:
    {
      vViewEdit(3);
      break;
    }
    case EDITOR5_ID:
    {
      vViewEdit(4);
      break;
    }

    // View Message
    case MESSAGE_ID:
    {
      // Call the function
      vViewMessage();
      break;
    }

    // View Makefile
    case MAKEFILE_ID:
    {
      // Call the function
      vViewMakefile();
      break;
    }


    // MAKEFILE MENU
    // =============
    // New makefile
    case NEWMAKEF_ID:
    {
      vNewMakefile();
      break;
    }

    // Open makefile...
    case OPENMAKEF_ID:
    {
      vOpenMakefile();
      break;
    }

    // Save makefile
    case SAVEMAKEF_ID:
    {
      vSaveMakefile();
      break;
    }

    // Save As...
    case SAVEASMAKEF_ID:
    {
      vSaveAsMakefile();
      break;
    }

    // Compile
    case COMPILE_ID:
    {
      vCompile(WinNb);
      break;
    }


    // ERRORS MENU
    // =============
    case ERRORS_ID:
    {
      // call the function
      vViewErrors();
      break;
    }

    // Assemble
    case ASSEMBLE_ID:
    {
      vAssemble(WinNb);
      return;
    }

    // Set target
    case SETTARGET_ID:
    {
      vSetTarget(WinNb);
      break;
    }

    // Make target
    case MAKETARGET_ID:
    {
      vMakeTarget(WinNb);
      break;
    }

    // Build target
    case BUILDTARGET_ID:
    {
      vBuildTarget(WinNb);
      break;
    }


    // RUN MENU ----------------------------------------
    // Execute
    case EXECUTE_ID:
    {
      vExecute();
      break;
    }

    // Debug
    case DEBUG_ID:
    {
      vDebug();
      break;
    }


    // TOOL MENU ---------------------------------------
    // Grep
    case GREP_ID:
    {
      vGrep();
      break;
    }


    // OPTION MENU ----------------------------------------
    // Set...
    case SET_ID:
    {
      vSet(WinNb);
      break;
    }

    // Load options...
    case LOADOPTION_ID:
    {
      vLoadOptions(WinNb);
      break;
    }

    // Save options...
    case SAVEOPTION_ID:
    {
      vSaveOptions(WinNb);
      break;
    }


    // HELP MENU ----------------------------------------
    // Contents
    case CONTENTS_ID:
    {
       vHelp(WinNb);
       break;
    }
    
    // About
    case ABOUT_ID:
    {
      // call the function
      vAbout(WinNb);
      break;
    }

  default:
    break;
  }
  wxEndBusyCursor();
}

// Constructor
TextWindowClassWin::TextWindowClassWin(wxFrame *parent, int x, int y,
                                         int width, int height, long style,
                                         char *name):
wxTextWindow(parent, x, y, width, height, style, name)
{
  wxFont *pFont;
  
  pFont = new wxFont(FONT_SIZE, wxMODERN, wxNORMAL, wxNORMAL);
  SetFont (pFont);
}

// Destructor
TextWindowClassWin::~TextWindowClassWin(void)
{
}

// Resize
void TextWindowClassWin::OnSize(int w, int h)
{
  wxTextWindow::OnSize(w, h);
}

void MyTimer::Notify(void)
{
  int i;
  char azBuffer[FILELEN + 1];

  for(i = 0 ; i <= NB_EDITORS + 1 ; i++)
  {
    if (theApp.win[i] && theApp.win[i]->textedit->Modified() &&
        !strstr(azTitle[i],"<modified>") && i != NB_EDITORS)
    {
      sprintf(azBuffer,"wxIDE -%d- [%s] <modified>", i+1, azFileEdit[i]);
      strcpy (azTitle[i], azBuffer);
      theApp.win[i]->SetTitle(azTitle[i]);
    }
  }
}
