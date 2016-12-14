//---------------------------------------------------------------------------
//
// Name:        projektApp.h
// Author:      Tezi
// Created:     14.12.2016 11:36:29
// Description: 
//
//---------------------------------------------------------------------------

#ifndef __PROJEKTDLGApp_h__
#define __PROJEKTDLGApp_h__

#ifdef __BORLANDC__
	#pragma hdrstop
#endif

#ifndef WX_PRECOMP
	#include <wx/wx.h>
#else
	#include <wx/wxprec.h>
#endif

class projektDlgApp : public wxApp
{
	public:
		bool OnInit();
		int OnExit();
};

#endif
