//---------------------------------------------------------------------------
//
// Name:        projektApp.cpp
// Author:      Tezi
// Created:     14.12.2016 11:36:29
// Description: 
//
//---------------------------------------------------------------------------

#include "projektApp.h"
#include "projektDlg.h"

IMPLEMENT_APP(projektDlgApp)

bool projektDlgApp::OnInit()
{
	projektDlg* dialog = new projektDlg(NULL);
	SetTopWindow(dialog);
	dialog->Show(true);		
	return true;
}
 
int projektDlgApp::OnExit()
{
	return 0;
}
