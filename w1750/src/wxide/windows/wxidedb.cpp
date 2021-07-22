//------------------------------------------------------------------------------
// FILE                                  :  wxidedb.cc
// SCCS                                  :  @(#) %M%, %I%, %H%
//                                    @(#)  wxIDE
// PROGRAM NAME                          :  wxIDE
// MODULE NAME                           :  Construction of the dialog boxes
// DATE                                  :  01 may 1996
//                                          01 may 1997
// PROGRAMMER(s)                         :  WME
// LANGUAGE                              :  Borland C++ 4.51
// TYPE                                  :  Integrated Development Environment
//------------------------------------------------------------------------------
// Comment:
// Dialog Box = dbox
//------------------------------------------------------------------------------
#include <string.h>
#include <ctype.h>
#include "wx.h"
#include "wxide.h"

// +-----------+
// | dbox FIND |
// +-----------+
// Constructor
DialogBoxClassFind::DialogBoxClassFind(wxFrame *parent, char *title,
                                       Bool modal, int x, int y, int width,
                                       int height, long style, char *name):
wxDialogBox(parent, title, modal, x, y, width, height, style, name)
{
  // Construction of a TXT line
  GetFindText = new wxText(this, (wxFunction)TextProc42,"Text:", "", 20,
                           32,366, 29, 0, "GetFindText");
  // Construction of a check box
  GetFindCaseSensitive = new wxCheckBox(this, (wxFunction)CheckBoxProc44,
                                        "Case sensitive", 62, 82, -1, -1, 0,
                                        "GetFindCaseSensitive");
  // Construction of buttons
  FinOK = new wxButton(this, (wxFunction)ButtonProc36,
                       "OK", 44, 124, 66, 26, 0, "FinOK");
  FindCancel = new wxButton(this, (wxFunction)ButtonProc38, "Cancel", 170, 125,
                            66, 26, 0, "FindCancel");
  FindHelp = new wxButton(this, (wxFunction)ButtonProc40, "Help", 290, 124, 66,
                          26, 0, "FindHelp");

  FinOK->SetDefault();

  // Fit the objects on the panel
  Fit();
}

// Destructor
DialogBoxClassFind::~DialogBoxClassFind(void)
{
}

// Active the panel's resize by the user
void DialogBoxClassFind::OnSize(int w, int h)
{
  wxDialogBox::OnSize(w, h);
}

// Recall function for the button OK
void ButtonProc36(wxButton& but, wxCommandEvent& event)
{
  // If the pannel exists
  if (theApp.find)
  {
    iAnswer = OK;
    // Take the value from the checkbox (1 if checked)
    iCheckSensitive = theApp.find->GetFindCaseSensitive->GetValue();

    // Take the TXT line given by the user
    sscanf(theApp.find->GetFindText->GetValue(),"%s", azStringUser);

    // Undisplay the panel from the screen
    theApp.find->Show(FALSE);

    // Remove the object from memory
    delete theApp.find;

    // NULL object
    theApp.find = NULL;
  }
}

// Recall function for the button CANCEL
void ButtonProc38(wxButton& but, wxCommandEvent& event)
{
  // If the pannel exists
  if (theApp.find)
  {
    iAnswer = CANCEL;

    // Undisplay the panel from the screen
    theApp.find->Show(FALSE);

    // Remove the object from memory
    delete theApp.find;

    // NULL object
    theApp.find = NULL;
  }
}

// Recall function for the button HELP
void ButtonProc40(wxButton& but, wxCommandEvent& event)
{
}

// Recall function for the TXT
void TextProc42(wxText& text, wxCommandEvent& event)
{
}

// Recall function for the CHECKBOX
void CheckBoxProc44(wxCheckBox& but, wxCommandEvent& event)
{
}


// +--------------+
// | dbox REPLACE |
// +--------------+
DialogBoxClassReplace::DialogBoxClassReplace(wxFrame *parent, char *title,
                                             Bool modal, int x, int y, int width,
                                             int height, long style, char *name):
wxDialogBox(parent, title, modal, x, y, width, height, style, name)
{
  // Construction of TXT lines
  GetReplaceOldText = new wxText(this, (wxFunction)TextProc56, "Old text: ",
                                 "", 14, 24, 362, 26, 0, "GetReplaceOldText");
  GetReplaceNewText = new wxText(this, (wxFunction)TextProc58, "New text:",
                                 "", 12, 102, 362, 26, 0, "GetReplaceNewText");

  // Construction of check boxes
  GetReplaceCaseSensitive = new wxCheckBox(this, (wxFunction)CheckBoxProc60,
                                           "Case sensitive", 102, 153, -1, -1, 0,
                                           "GetReplaceCaseSensitive");
  GetReplaceChangeAll = new wxCheckBox(this, (wxFunction)CheckBoxProc62,
                                       "Change all", 246, 153, -1, -1, 0,
                                       "GetReplaceChangeAll");
  // Construction of buttons 
  ReplaceOK = new wxButton(this, (wxFunction)ButtonProc50, "OK", 46, 191, 66,
                                  26, 0, "ReplaceOK");
  ReplaceCancel = new wxButton(this, (wxFunction)ButtonProc52, "Cancel", 158,
                               193, 66, 26, 0, "ReplaceCancel");
  ReplceHelp = new wxButton(this, (wxFunction)ButtonProc54, "Help", 277, 192,
                            66, 26, 0, "ReplceHelp");

  ReplaceOK->SetDefault();

  // Fit the objects on the panel
  Fit();
}

// Destructor
DialogBoxClassReplace::~DialogBoxClassReplace(void)
{
}

// Active the panel's resize by the user
void DialogBoxClassReplace::OnSize(int w, int h)
{
  wxDialogBox::OnSize(w, h);
}

// Recall function OK
void ButtonProc50(wxButton& but, wxCommandEvent& event)
{
  // If the panel exists
  if (theApp.replace)
  {
    iAnswer = OK;

    // Take the value from the checkbox (1 if checked)
    iCheckSensitive =
    theApp.replace->GetReplaceCaseSensitive->GetValue();

    // Take the value from the checkbox
    iCheckAll = theApp.replace->GetReplaceChangeAll->GetValue();

    // Take the TXT line given by the user
    strcpy(azStringUser,theApp.replace->GetReplaceOldText->GetValue());

    // Take the TXT line given by the user
    strcpy(azStringUser2,theApp.replace->GetReplaceNewText->GetValue());

    // Take off the panel from the screen
    theApp.replace->Show(FALSE);

    // Remove the object from the screen
    delete theApp.replace;

    // NULL object
    theApp.replace = NULL;
  }
}

// Recall function for the CANCEL button
void ButtonProc52(wxButton& but, wxCommandEvent& event)
{
  // If the panel exist
  if (theApp.replace)
  {
    iAnswer = CANCEL;

    // Take off the panel from the screen
    theApp.replace->Show(FALSE);

    // Remove the object from memory
    delete theApp.replace;

    // NULL object
    theApp.replace = NULL;
  }
}

// Recall function from the HELP button
void ButtonProc54(wxButton& but, wxCommandEvent& event)
{
}

// Recall function for the TXT
void TextProc56(wxText& text, wxCommandEvent& event)
{
}

// Recall function for the TXT
void TextProc58(wxText& text, wxCommandEvent& event)
{
}

// Recall function for the check box
void CheckBoxProc60(wxCheckBox& but, wxCommandEvent& event)
{
}

// Recall function for the check box
void CheckBoxProc62(wxCheckBox& but, wxCommandEvent& event)
{
}


// +---------------+
// | dbox GOTOLINE |
// +---------------+
DialogBoxClassGotoline::DialogBoxClassGotoline(wxFrame *parent, char *title,
                                               Bool modal, int x, int y,
                                               int width, int height, long style,
                                               char *name):
wxDialogBox(parent, title, modal, x, y, width, height, style, name)
{
  // TXT line's construction
  GetGotoLineNumber = new wxText(this, NULL, "Line number:",
                                 "\0", 20, 35, 264, 26, 0, "GetGotoLineNumber");

  // Button's construction
  GotoLineOK = new wxButton(this, (wxFunction)ButtonProc68, "OK", 25, 104, 66,
                            26, 0, "GotoLineOK");
  GotoLineCancel = new wxButton(this, (wxFunction)ButtonProc70, "Cancel", 117,
                                104, 66, 26, 0, "GotoLineCancel");
//  GotoLineHelp = new wxButton(this, (wxFunction)ButtonProc72, "Help", 209, 105,
//                              66, 26, 0, "GotoLineHelp");

  GotoLineOK->SetDefault();

  // Fit the objects in the panel
  Fit();
}

// Destructor
DialogBoxClassGotoline::~DialogBoxClassGotoline(void)
{
}

// Active the panel's resize by the user
void DialogBoxClassGotoline::OnSize(int w, int h)
{
  wxDialogBox::OnSize(w, h);
}

// Recall function for button OK
void ButtonProc68(wxButton& but, wxCommandEvent& event)
{
  if (strcmp( pazOnlyDigits (theApp.gotoline->GetGotoLineNumber->GetValue()), "Error") !=0)
  {
    // If the panel exists
    if (theApp.gotoline)
    {
      iAnswer = OK;

      // Take the TXT line given by the user
      sscanf(theApp.gotoline->GetGotoLineNumber->GetValue(),"%d", &iLinenumber);

      // Remove the panel from the screen
      theApp.gotoline->Show(FALSE);

      // Remove the object from memory
      delete theApp.gotoline;

      // NULL object
      theApp.gotoline = NULL;
    }
  }
  else
  {
    wxBell();
    wxMessageBox ("Please enter only digits", "Type mismatch");
  }
}

// Recall function for button CANCEL
void ButtonProc70(wxButton& but, wxCommandEvent& event)
{
  // If the panel exists
  if (theApp.gotoline)
  {
    iAnswer = CANCEL;

    // Remove the panel from the screen
    theApp.gotoline->Show(FALSE);

    // Remove the object from memory
    delete theApp.gotoline;

    // NULL object
    theApp.gotoline = NULL;
  }
}

// Recall function for button HELP
void ButtonProc72(wxButton& but, wxCommandEvent& event)
{
}

// +------------------------------+
// | dbox SETTARGET's constructor |
// +------------------------------+
DialogBoxClassSettarget::DialogBoxClassSettarget(wxFrame *parent, char *title,
                                                 Bool modal, int x, int y,
                                                 int width, int height,
                                                 long style, char *name):
wxDialogBox(parent, title, modal, x, y, width, height, style, name)
{
  // TXT line's construction
  GetSetTarget = new wxText(this, (wxFunction)TextProc95, "Target:", "", 53, 36,
                            200, 26, 0, "GetSetTarget");

  // buttons' construction
  SetTargetOK = new wxButton(this, (wxFunction)ButtonProc93, "OK", 27, 104, 66,
                             26, 0, "SetTargetOK");
  SetTargetCancel = new wxButton(this, (wxFunction)ButtonProc91, "Cancel", 121,
                                 103, 66, 26, 0, "SetTargetCancel");
  SetTargetHelp = new wxButton(this, (wxFunction)ButtonProc89, "Help", 224, 104,
                               66, 26, 0, "SetTargetHelp");

  SetTargetOK->SetDefault();

  // Fit the objects on the panel
  Fit();
}

// Destructor
DialogBoxClassSettarget::~DialogBoxClassSettarget(void)
{
}

// Active the panel's resize by the user
void DialogBoxClassSettarget::OnSize(int w, int h)
{
  wxDialogBox::OnSize(w, h);
}

// Recall function for button OK
void ButtonProc93(wxButton& but, wxCommandEvent& event)
{
  // If the panel exists
  if (theApp.settarget)
  {
    // Take the TXT line given by the user
    strcpy(azTarget, theApp.settarget->GetSetTarget->GetValue());

    // Take of the panel from the screen
    theApp.settarget->Show(FALSE);

    // Remove the object from memory
    delete theApp.settarget;

    // NULL object
    theApp.settarget = NULL;
  }
}

// Recall function for button CANCEL
void ButtonProc91(wxButton& but, wxCommandEvent& event)
{
  // If the panel exists
  if (theApp.settarget)
  {
    // Take of the panel from the screen
    theApp.settarget->Show(FALSE);

    // Remove the object from memory
     delete theApp.settarget;

    // NULL object
    theApp.settarget = NULL;
  }
}

// Recall function for button HELP
void ButtonProc89(wxButton& but, wxCommandEvent& event)
{
}

// Recall function for the TXT
void TextProc95(wxText& text, wxCommandEvent& event)
{
}


// +--------------+
// | dbox EXECUTE |
// +--------------+
DialogBoxClassExecute::DialogBoxClassExecute(wxFrame *parent, char *title,
                                             Bool modal, int x, int y,
                                             int width, int height, long style,
                                             char *name):
wxDialogBox(parent, title, modal, x, y, width, height, style, name)
{
  // TXT line's construction
  GetExecuteCommandeLine = new wxText(this, (wxFunction)TextProc101,
                                      "Command line:", "", 11, 41, 429, 28, 0,
                                      "GetExecuteCommandeLine");
  // buttons' construction
  ExecuteOK = new wxButton(this, (wxFunction)ButtonProc107, "OK", 57, 116, 66,
                           26, 0, "ExecuteOK");
  ExecuteCancel = new wxButton(this, (wxFunction)ButtonProc105, "Cancel", 198,
                               117, 66, 26, 0, "ExecuteCancel");
  ExecuteHelp = new wxButton(this, (wxFunction)ButtonProc103, "Help", 337, 116,
                             66, 26, 0, "ExecuteHelp");

  ExecuteOK->SetDefault();

  // Fit the objects on the panel
  Fit();
}

// Destructor
DialogBoxClassExecute::~DialogBoxClassExecute(void)
{
}

// Active the window's resize by the user
void DialogBoxClassExecute::OnSize(int w, int h)
{
  wxDialogBox::OnSize(w, h);
}

// Recall funtion for button OK
void ButtonProc107(wxButton& but, wxCommandEvent& event)
{
  // If the panel exists
  if (theApp.execute)
  {
    // Take the TXT line given by the user
    // and call the function to execute the process
    vExecuteProcess(theApp.execute->GetExecuteCommandeLine->GetValue());

    // Remove the panel from the screen
    theApp.execute->Show(FALSE);

    // Remove the object from memory
    delete theApp.execute;

    // NULL object
    theApp.execute = NULL;
  }
}

// Recall function for CANCEL button
void ButtonProc105(wxButton& but, wxCommandEvent& event)
{
  // If the panel exists
  if (theApp.execute)
  {
    // Remove the panel from the screen
    theApp.execute->Show(FALSE);

    // Remove the object from memory
    delete theApp.execute;

    // NULL object
    theApp.execute = NULL;
  }
}

// Recall function for HELP button
void ButtonProc103(wxButton& but, wxCommandEvent& event)
{
}

// Recall function for the TXT
void TextProc101(wxText& text, wxCommandEvent& event)
{
}


// +----------+
// | dbox SET |
// +----------+
DialogBoxClassSet::DialogBoxClassSet(wxFrame *parent, char *title, Bool modal,
                                     int x, int y, int width, int height,
                                     long style, char *name):
wxDialogBox(parent, title, modal, x, y, width, height, style, name)
{
  // frames' construction
  BoxDir = new wxGroupBox(this, "Directories:", 6, 8, 617, 104, 0, "BoxDir");
  BoxCompiler = new wxGroupBox(this, "Compiler:", 6, 123, 193, 104, 0,
                               "BoxCompiler");
  BoxAssembler = new wxGroupBox(this, "Assembler:", 218, 123, 193, 104, 0,
                                "BoxAssembler");
  BoxMakefile = new wxGroupBox(this, "Makefile:", 430, 123, 193, 104, 0,
                               "BoxMakefile");
  BoxDebugger = new wxGroupBox(this, "Debugger:", 6, 238, 193, 104, 0,
                               "BoxDebugger");
  BoxGrep = new wxGroupBox(this, "Grep:", 218, 238, 193, 52, 0, "BoxGrep");
  BoxExtensions = new wxGroupBox(this, "Extensions:", 218, 290, 193, 52, 0, "BoxExtensions");

  // TXT lines' construction
  GetSetDirBin = new wxText(this, (wxFunction)TextProc121, "Bin:", "", 15,
                            36, 286, 28, 0, "GetSetDirBin");
  GetSetDirWork = new wxText(this, (wxFunction)TextProc123, "Work:", "", 15,
                             72, 286, 28, 0, "GetSetDirWork");
  GetSetDirInclude = new wxText(this, (wxFunction)TextProc125, "Include:", "",
                                316, 36, 286, 28, 0, "GetSetDirInclude");
  GetSetDirLib = new wxText(this, (wxFunction)TextProc127, "Library: ", "",
                            316, 72, 286, 28, 0, "GetSetDirLib");
  GetSetCompilerName = new wxText(this, (wxFunction)TextProc129, "Name:   ",
                                  "", 15, 151, 163, 28, 0,
                                  "GetSetCompilerName");
  GetSetCompilerOptions = new wxText(this, (wxFunction)TextProc131, "Options:",
                                     "", 15, 187, 163, 28, 0,
                                     "GetSetCompilerOptions");
  GetSetAssemblerName = new wxText(this, (wxFunction)TextProc145, "Name:   ",
                                   "", 227, 151, 163, 28, 0,
                                   "GetSetAssemblerName");
  GetSetAssemblerOptions = new wxText(this, (wxFunction)TextProc139, "Options:",
                                      "", 227, 187, 163, 28, 0,
                                      "GetSetAssemblerOptions");
  GetSetMakefileName = new wxText(this, (wxFunction)TextProc137, "Name:   ", "",
                                  439, 151, 163, 28, 0, "GetSetMakefileName");
  GetSetMakefileOptions = new wxText(this, (wxFunction)TextProc143, "Options:",
                                     "", 439, 187, 163, 28, 0,
                                     "GetSetMakefileOptions");
  GetSetDebuggerName = new wxText(this, (wxFunction)TextProc141, "Name:   ", "",
                                  15, 266, 163, 28, 0, "GetSetDebuggerName");
  GetSetDebuggerOptions = new wxText(this, (wxFunction)TextProc135, "Options:",
                                     "", 15, 302, 163, 28, 0,
                                     "GetSetDebuggerOptions");
  GetSetGrepName = new wxText(this, (wxFunction)TextProc133, "Name:   ", "",
                              227, 260, 163, 28, 0, "GetSetGrepName");
  GetSetExtensions = new wxText(this, (wxFunction)TextProc147, "Values:   ", "",
                              227, 312, 163, 28, 0, "GetSetGrepName");
  // Buttons' construction
  SetOK = new wxButton(this, (wxFunction)ButtonProc148, "OK", 446, 254, 72, 28,
                       0, "SetOK");
  SetCancel = new wxButton(this, (wxFunction)ButtonProc150, "Cancel", 535, 254,
                           72, 28, 0, "SetCancel");
  SetHelp = new wxButton(this, (wxFunction)ButtonProc113, "Help", 446, 298, 161,
                         28, 0, "SetHelp");

  SetOK->SetDefault();

  // Fit the object in the panel
  Fit();
}

// Destructor
DialogBoxClassSet::~DialogBoxClassSet(void)
{
}

// Active the panels' resize by the user
void DialogBoxClassSet::OnSize(int w, int h)
{
  wxDialogBox::OnSize(w, h);
}

// Recall function for the TXT
void TextProc121(wxText& text, wxCommandEvent& event)
{
}
void TextProc123(wxText& text, wxCommandEvent& event)
{
}
void TextProc125(wxText& text, wxCommandEvent& event)
{
}
void TextProc127(wxText& text, wxCommandEvent& event)
{
}
void TextProc129(wxText& text, wxCommandEvent& event)
{
}
void TextProc131(wxText& text, wxCommandEvent& event)
{
}
void TextProc133(wxText& text, wxCommandEvent& event)
{
}
void TextProc135(wxText& text, wxCommandEvent& event)
{
}
void TextProc137(wxText& text, wxCommandEvent& event)
{
}
void TextProc139(wxText& text, wxCommandEvent& event)
{
}
void TextProc141(wxText& text, wxCommandEvent& event)
{
}
void TextProc143(wxText& text, wxCommandEvent& event)
{
}
void TextProc145(wxText& text, wxCommandEvent& event)
{
}
void TextProc147(wxText& text, wxCommandEvent& event)
{
}

// Recall function for button OK
void ButtonProc148(wxButton& but, wxCommandEvent& event)
{
  // If the panel exists
  if (theApp.set)
  {
    // Take the TXT lines given by the user
    strcpy(azSetOption[0], theApp.set->GetSetDirBin->GetValue());
    strcpy(azSetOption[1], "Not use");
    strcpy(azSetOption[2], theApp.set->GetSetDirInclude->GetValue());
    strcpy(azSetOption[3], "Not use");
    strcpy(azSetOption[4], theApp.set->GetSetCompilerName->GetValue());
    strcpy(azSetOption[5], theApp.set->GetSetCompilerOptions->GetValue());
    strcpy(azSetOption[6], theApp.set->GetSetAssemblerName->GetValue());
    strcpy(azSetOption[7], theApp.set->GetSetAssemblerOptions->GetValue());
    strcpy(azSetOption[8], theApp.set->GetSetMakefileName->GetValue());
    strcpy(azSetOption[9], theApp.set->GetSetMakefileOptions->GetValue());
    strcpy(azSetOption[10],theApp.set->GetSetDebuggerName->GetValue());
    strcpy(azSetOption[11],theApp.set->GetSetDebuggerOptions->GetValue());
    strcpy(azSetOption[12],theApp.set->GetSetGrepName->GetValue());
    strcpy(azSetOption[13],theApp.set->GetSetExtensions->GetValue());

    strcpy(azExtension, azSetOption[13]);
    vFormatExtensions ();
    // Remove the panel from the screen
    theApp.set->Show(FALSE);

    // Remove the object from memory
    delete theApp.set;

    // NULL object
    theApp.set = NULL;
  }
}

// Recall function for the button cancel
void ButtonProc150(wxButton& but, wxCommandEvent& event)
{
  // If the panel exists
  if (theApp.set)
  {
    // Remove the panel from the screen
    theApp.set->Show(FALSE);

    // Remove the object from memory
    delete theApp.set;

    // NULL object
    theApp.set = NULL;
  }
}

// Recall function for button HELP
void ButtonProc113(wxButton& but, wxCommandEvent& event)
{
}

