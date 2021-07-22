/*
 * File:	wx_popup.h
 * Purpose: Popup menu
 * Author:  Sergey Krasnov
 * Created: 1995
 * Updated:
 * Copyright:
 */

#ifndef wx_popuph
#define wx_popuph

#ifdef __GNUG__
#pragma interface
#endif

#include "wx_defs.h"
#include "wx_dialg.h"
#include "wx_vlbox.h"

typedef void (*FPCPPI)(char **, int);

class wxPopupMenu: public wxDialogBox
{
public:
    wxPopupMenu(wxFrame * parent, wxFunction func,
                int x, int y, int width, int height, char * Title,
                CPFPCPI get_optx, char *garg,
                FPCPPI execf, char *earg[],
                int nrows = -1, long style = wxDEFAULT_DIALOG_STYLE);
    ~wxPopupMenu();
	int Execute(void);
	void SelectOk(void);
	inline int GetSelection(void) 	{ return vListBox->GetSelection(); }
	void SetSelection(int n);
	void OnSearch(int SearchType);
	void Refresh(void);
    virtual void Fit(void);
    void ProcessCommand (wxCommandEvent & event);
private:
    	char * Title;
    	CPFPCPI GetOptx;
    	char *gArg;
        FPCPPI ExecF;
        char **eArg;
    	long Style;
		int nRows;
		int Width, Height;
		Bool SearchDown;
		Bool IgnoreCase;
		char SearchStr[256];
		wxButton *view, *exit;
        wxVirtListBox * vListBox;
		int Search(int SearchType);
protected:
};

#endif // wx_popuph
