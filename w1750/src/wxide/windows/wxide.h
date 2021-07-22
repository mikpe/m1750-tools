//------------------------------------------------------------------------------
// FILE                                  :  wxide.h
// SCCS                                  :  @(#) %M%, %I%, %H%
//                                    @(#)  wxIDE
// PROGRAM NAME                          :  wxIDE
// MODULE NAME                           :  Define, Class,
//                                          Variable and prototype
// DATE                                  :  01 may 1996
//                                          01 may 1997
// PROGRAMMER(s)                         :  WME
// LANGUAGE                              :  Borland C++ 4.51
// TYPE                                  :  Integrated Development Environment
//------------------------------------------------------------------------------

// Compilation options
#ifndef _INC_IDE_H
#define _INC_IDE_H
#include <wx_timer.h>

#ifndef Main
#define EXTERN extern
#else
#define EXTERN
#endif

#define NB_EDITORS 5				 // Number of editors
#define WXIDE_VERSION "wxIDE Version 0.2\0"	 // Number of status lines


// +---------------------+
// | Classes' definition |
// +---------------------+
class  FrameClassWin;
class  DialogBoxClassFind;
class  DialogBoxClassReplace;
class  DialogBoxClassGotoline;
class  DialogBoxClassSettarget;
class  DialogBoxClassExecute;
class  DialogBoxClassSet;
class  DialogBoxClassConfirm;


// +-------------------------------------------------------------+
// | Declaration of the class AppClass containing the definition |
// | of the objects and their pointers                           |
// +-------------------------------------------------------------+
class AppClass: public wxApp
{
 public:
  FrameClassWin			*win[NB_EDITORS + 2];
  DialogBoxClassFind		*find;
  DialogBoxClassReplace 	*replace;
  DialogBoxClassGotoline	*gotoline;
  DialogBoxClassSettarget	*settarget;
  DialogBoxClassExecute		*execute;
  DialogBoxClassSet		*set;
  DialogBoxClassConfirm		*confirmation;
  wxFrame			*OnInit(void);
  Bool				ParseCommandLine(void);
};

// +-------------------------------------+
// | Declaration of the window class Win |
// +-------------------------------------+
class TextWindowClassWin;
class FrameClassWin: public wxFrame
{
 private:
 protected:
 public:

  TextWindowClassWin *textedit;
  wxMenu             *Menu4;		// The View menu
  int                WinNb;		// The window's number
  
  // Constructor and destructor
  FrameClassWin(wxFrame *parent, char *title, int x, int y,
                int width, int height, long style, char *name, int nb);
  ~FrameClassWin(void);
  wxKeyEvent(wxEVENT_TYPE_CHAR);

  Bool OnClose(void);                            // Close by upper left corner
  void OnSize(int w, int h);                     // Resize the window
  void OnMenuCommand(int commandId);             // menu command
};

// menu definition
#define FILE_ID		1
#define NEWEDITWIN_ID	2
#define NEW_ID		3
#define OPEN_ID		4
#define SAVE_ID		5
#define SAVEAS_ID	6
#define PRINT_ID	7
#define CLOSE_ID	8
#define EXIT_ID		9
#define EDIT_ID		10
#define UNDO_ID		11
#define CUT_ID		12
#define COPY_ID		13
#define PASTE_ID	14
#define DELETE_ID	15
#define SEARCH_ID	16
#define FIND_ID		17
#define REPLACE_ID	18
#define SHEARCHAGAIN_ID 19
#define GOTOLINE_ID	20
#define VIEW_ID		21
#define EDITOR1_ID	23
#define EDITOR2_ID	24
#define EDITOR3_ID	25
#define EDITOR4_ID	26
#define EDITOR5_ID	27
#define MESSAGE_ID	28
#define MAKEFILE_ID	29
#define MAKE_ID		30
#define NEWMAKEF_ID	31
#define OPENMAKEF_ID	32
#define SAVEMAKEF_ID	33
#define SAVEASMAKEF_ID	34
#define COMPILE_ID	35
#define ASSEMBLE_ID	36
#define SETTARGET_ID	37
#define MAKETARGET_ID	38
#define BUILDTARGET_ID	39
#define RUN_ID		40
#define EXECUTE_ID	41
#define DEBUG_ID	42
#define TOOL_ID		43
#define GREP_ID 	44
#define OPTIONS_ID	45
#define SET_ID		46
#define LOADOPTION_ID	47
#define SAVEOPTION_ID	48
#define HELP_ID		49
#define CONTENTS_ID	50
#define ABOUT_ID	51
#define ERRORS_ID	52

class MyTimer: public wxTimer
{
  private:
  protected:
  public:
   void Notify(void);
};
#define TIMER_DELAY 500
EXTERN  MyTimer *my_timer;

// Declaration of the TXT class
class TextWindowClassWin: public wxTextWindow
{
 private:
 protected:
 public:
 
  // Constructor and destructor
  TextWindowClassWin(wxFrame *parent, int x, int y, int width,
                      int height, long style, char *name);
  ~TextWindowClassWin(void);

  void OnSize(int w, int h);
};

// Declaration of the Makefile class (same as Win1)
class TextWindowClassMakefile;
class FrameClassMakefile: public wxFrame
{
 private:
 protected:
 public:
  TextWindowClassMakefile *textmakefile;

  FrameClassMakefile(wxFrame *parent, char *title, int x, int y, int width,
                     int height, long style, char *name);
  ~FrameClassMakefile(void);

  Bool OnClose(void);
  void OnSize(int w, int h);
  void OnMenuCommand(int commandId);
};

class TextWindowClassMakefile: public wxTextWindow
{
 private:
 protected:
 public:
  TextWindowClassMakefile(wxFrame *parent, int x, int y, int width,
  int height, long style, char *name);
  ~TextWindowClassMakefile(void);

  void OnSize(int w, int h);
};

// Dialog Box Find
// Declaration of the Find class
class DialogBoxClassFind: public wxDialogBox
{
 private:
 protected:
 public:

  // Pointers on objects
  wxText     *GetFindText;
  wxCheckBox *GetFindCaseSensitive;
  wxButton   *FinOK;
  wxButton   *FindCancel;
  wxButton   *FindHelp;

  // Constructor and destructor
  DialogBoxClassFind(wxFrame *parent, char *title, Bool modal, int x, int y,
                     int width, int height, long style, char *name);
  ~DialogBoxClassFind(void);

  void OnSize(int w, int h);
};


// recall functions
void TextProc42(wxText& text, wxCommandEvent& event);
void CheckBoxProc44(wxCheckBox& check, wxCommandEvent& event);
void ButtonProc36(wxButton& but, wxCommandEvent& event);
void ButtonProc38(wxButton& but, wxCommandEvent& event);
void ButtonProc40(wxButton& but, wxCommandEvent& event);


// Replace declaration in the same way then Find
class DialogBoxClassReplace: public wxDialogBox
{
 private:
 protected:
 public:
  // Pointers on objects
  wxText     *GetReplaceOldText;
  wxText     *GetReplaceNewText;
  wxCheckBox *GetReplaceCaseSensitive;
  wxCheckBox *GetReplaceChangeAll;
  wxButton   *ReplaceOK;
  wxButton   *ReplaceCancel;
  wxButton   *ReplceHelp;
  // Constructor and destructor
  DialogBoxClassReplace(wxFrame *parent, char *title, Bool modal, int x, int y,
                        int width, int height, long style, char *name);
  ~DialogBoxClassReplace(void);

  void OnSize(int w, int h);
};

// Recall functions
void TextProc56(wxText& text, wxCommandEvent& event);
void TextProc58(wxText& text, wxCommandEvent& event);
void CheckBoxProc60(wxCheckBox& check, wxCommandEvent& event);
void CheckBoxProc62(wxCheckBox& check, wxCommandEvent& event);
void ButtonProc50(wxButton& but, wxCommandEvent& event);
void ButtonProc52(wxButton& but, wxCommandEvent& event);
void ButtonProc54(wxButton& but, wxCommandEvent& event);



// Gotoline class declaration
class DialogBoxClassGotoline: public wxDialogBox
{
 private:
 protected:
 public:
  // Pointers on objects
  wxText   *GetGotoLineNumber;
  wxButton *GotoLineOK;
  wxButton *GotoLineCancel;
  wxButton *GotoLineHelp;
  // Constructor and destructor
  DialogBoxClassGotoline(wxFrame *parent, char *title, Bool modal, int x, int y,
                         int width, int height, long style, char *name);
  ~DialogBoxClassGotoline(void);

  void OnSize(int w, int h);
};

// Recall functions
void TextProc74(wxText& text, wxCommandEvent& event);
void ButtonProc68(wxButton& but, wxCommandEvent& event);
void ButtonProc70(wxButton& but, wxCommandEvent& event);
void ButtonProc72(wxButton& but, wxCommandEvent& event);


// Settarget class declaration
class DialogBoxClassSettarget: public wxDialogBox
{
 private:
 protected:
 public:
  // Pointers on objects
  wxText   *GetSetTarget;
  wxButton *SetTargetOK;
  wxButton *SetTargetCancel;
  wxButton *SetTargetHelp;
  // Construtor and destructor
  DialogBoxClassSettarget(wxFrame *parent, char *title, Bool modal, int x,
                          int y, int width, int height, long style, char *name);
  ~DialogBoxClassSettarget(void);

  void OnSize(int w, int h);
};
// recall functions
void TextProc95(wxText& text, wxCommandEvent& event);
void ButtonProc89(wxButton& but, wxCommandEvent& event);
void ButtonProc91(wxButton& but, wxCommandEvent& event);
void ButtonProc93(wxButton& but, wxCommandEvent& event);


// execute class declaration
class DialogBoxClassExecute: public wxDialogBox
{
 private:
 protected:
 public:
  // Pointers on objects
  wxText   *GetExecuteCommandeLine;
  wxButton *ExecuteHelp;
  wxButton *ExecuteCancel;
  wxButton *ExecuteOK;
  // Destructor and constructor
  DialogBoxClassExecute(wxFrame *parent, char *title, Bool modal, int x, int y,
                        int width, int height, long style, char *name);
  ~DialogBoxClassExecute(void);

  void OnSize(int w, int h);
};
// recall functions
void TextProc101(wxText& text, wxCommandEvent& event);
void ButtonProc103(wxButton& but, wxCommandEvent& event);
void ButtonProc105(wxButton& but, wxCommandEvent& event);
void ButtonProc107(wxButton& but, wxCommandEvent& event);


// Set class declaration
class DialogBoxClassSet: public wxDialogBox
{
 private:
 protected:
 public:
  // Pointer on objects
  wxGroupBox *BoxDir;
  wxGroupBox *BoxCompiler;
  wxGroupBox *BoxAssembler;
  wxGroupBox *BoxMakefile;
  wxGroupBox *BoxDebugger;
  wxGroupBox *BoxGrep;
  wxGroupBox *BoxExtensions;
  wxText *GetSetDirBin;
  wxText *GetSetDirWork;
  wxText *GetSetDirInclude;
  wxText *GetSetDirLib;
  wxText *GetSetCompilerName;
  wxText *GetSetCompilerOptions;
  wxText *GetSetAssemblerName;
  wxText *GetSetAssemblerOptions;
  wxText *GetSetMakefileName;
  wxText *GetSetMakefileOptions;
  wxText *GetSetDebuggerName;
  wxText *GetSetDebuggerOptions;
  wxText *GetSetGrepName;
  wxText *GetSetExtensions;
  wxMessage *message293;
  wxButton *SetOK;
  wxButton *SetCancel;
  wxButton * SetHelp;
  // Construtor and destructor
  DialogBoxClassSet(wxFrame *parent, char *title, Bool modal, int x, int y,
                    int width, int height, long style, char *name);
  ~DialogBoxClassSet(void);

 void OnSize(int w, int h);
};
// recall functions
void TextProc121(wxText& text, wxCommandEvent& event);
void TextProc123(wxText& text, wxCommandEvent& event);
void TextProc125(wxText& text, wxCommandEvent& event);
void TextProc127(wxText& text, wxCommandEvent& event);
void TextProc129(wxText& text, wxCommandEvent& event);
void TextProc131(wxText& text, wxCommandEvent& event);
void TextProc133(wxText& text, wxCommandEvent& event);
void TextProc135(wxText& text, wxCommandEvent& event);
void TextProc137(wxText& text, wxCommandEvent& event);
void TextProc139(wxText& text, wxCommandEvent& event);
void TextProc141(wxText& text, wxCommandEvent& event);
void TextProc143(wxText& text, wxCommandEvent& event);
void TextProc145(wxText& text, wxCommandEvent& event);
void TextProc147(wxText& text, wxCommandEvent& event);
void ButtonProc113(wxButton& but, wxCommandEvent& event);
void ButtonProc148(wxButton& but, wxCommandEvent& event);
void ButtonProc150(wxButton& but, wxCommandEvent& event);

// global defines of the program
#define YES 1                                    // Button YES give back 1 if clicked
#define NO  2                                    //   "    NO      "     2   "
#define CANCEL 3                                 //   "    CANCEL  "     3   "
#define OK 4                                     //   "    OK      "     4   "
#define FILELEN 255                              // Length of a filename

#define MESSAGE  "message.out"                   // File containing STDOUT and STDERR
#define DONE     "imdone.dat"                    // File with the answer the exeution
#define EXECUTOR "executor"                      // File executing process

#ifdef wx_msw                                    // compilation for MSW
#define SEPARATION1 '\\'
#define SEPARATION2 "\\"
#else                                            // compilation for X
#define SEPARATION1 '/'
#define SEPARATION2 "/"
#endif

#define NB_STATUS_LINES	1			 // Number of status lines
#define SHIFT 20                                 // Shift of the message boxes

EXTERN  AppClass theApp;                         // theApp->AppClass
EXTERN  char azTitle[NB_EDITORS+2][FILELEN+1];   // Window title
EXTERN  char *pazF;                              // Pointer tmp on file
EXTERN  char azTmp[FILELEN+1];                   // tmp string
EXTERN  char azFileEdit[NB_EDITORS+2][FILELEN+1];// file name to edit
EXTERN  char azExtension[FILELEN+1];             // file extension
EXTERN  char azTarget[FILELEN+1];                // target's name
EXTERN  FILE *pfSetOption;                       // Pointer to the CFG file
EXTERN  int iCheckSensitive;                     // CheckSensitive value
EXTERN  int iCheckAll;                           // CheckAll value
EXTERN  int iAnswer;                             // button value
EXTERN  char azStringUser[FILELEN+1];            // DIALOG BOX's string
EXTERN  char azStringUser2[FILELEN+1];           // DIALOG BOX's string
EXTERN  int iLinenumber;                         // lines nb of a file
EXTERN  char azSetOption[14][FILELEN+1];         // CFG pannel contents
EXTERN  char azCommandeLineExecute[FILELEN+1];   // string to execute
EXTERN  char azSTDFile[FILELEN+1];               //
//EXTERN  char azDBoxConfLine1[FILELEN+1];         // DIALOG BOX CONF's string
//EXTERN  char azDBoxConfLine2[FILELEN+1];         //  "

//  Prototype
char *pazOnlyDigits(char *pazTxt);               // Only digits
char *azCatDir(char *azDir, char *azCompName, char *azInclude,
               char *azOptions,char *azEditFile);// parameters processing
void vExecuteProcess( char *azExe);              // Execute a process
void vRemoveFileTime(char *azFile);              // Change time of the files
void vNewWin(void);                              // Create a new editor
void vNewFile(int WinNb);                        // New File in the editor WinNb
void vOpen(int WinNb);                           // Open File in editor WinNb
void vSave(int WinNb);                           // Save File in editor WinNb
void vSaveAs(int WinNb);                         // Save as File in editor WinNb
void vEndApp(void);                              // Close the application
void vEndWin(int Nb);				 // Close a window
void vMyStrlwr(char *str);                       // UPPERCASE in lowercase
void vUpdateViewMenu(int Nb);			 // Update View Menu

// View Menu common to all the editors
void vViewEdit(int Nb);
void vViewMessage(void);
void vViewMakefile(void);

// Search Menu common to all the editors
void vFind(int WinNb);
void vReplace(int WinNb);
void vSearchAgain(int WinNb);
void vGotoLine(int WinNb);

// Make Menu common to all the editors
void vNewMakefile(void);
void vOpenMakefile(void);
void vSaveMakefile(void);
void vSaveAsMakefile(void);
void vSetTarget(int WinNb);
void vMakeTarget(int WinNb);
void vBuildTarget(int WinNb);
void vCompile(int WinNb);
void vAssemble(int WinNb);

// Errors menu (only for the Message window
void vViewErrors();

// Run Menu common to all the editors
void vExecute(void);
void vDebug(void);

// Tool Menu common to all the editors
void vGrep(void);

// Option Menu common to all the editors
void vSet(int WinNb);
void vLoadOptions(int WinNb);
void vSaveOptions(int WinNb);
void vFormatExtensions(void);

// Help Menu common to all the editors
void vHelp(int WinNb);
void vAbout(int WinNb);

#define FONT_SIZE 11
#endif
