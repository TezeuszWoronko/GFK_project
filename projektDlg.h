///-----------------------------------------------------------------
///
/// @file      projektDlg.h
/// @author    Tezi
/// Created:   14.12.2016 11:36:29
/// @section   DESCRIPTION
///            projektDlg class declaration
///
///------------------------------------------------------------------

#ifndef __PROJEKTDLG_H__
#define __PROJEKTDLG_H__

#ifdef __BORLANDC__
	#pragma hdrstop
#endif

#ifndef WX_PRECOMP
	#include <wx/wx.h>
	#include <wx/dialog.h>
#else
	#include <wx/wxprec.h>
#endif

//Do not add custom headers between 
//Header Include Start and Header Include End.
//wxDev-C++ designer will remove them. Add custom headers after the block.
////Header Include Start
#include <wx/filedlg.h>
#include <wx/scrolbar.h>
#include <wx/panel.h>
#include <wx/textctrl.h>
#include <wx/choice.h>
#include <wx/button.h>
#include <wx/sizer.h>
////Header Include End
#include <wx/image.h>
#include <wx/dcbuffer.h>
#include "utils.h"
#include <string>
#include <cstdlib>
////Dialog Style Start
#undef projektDlg_STYLE
#define projektDlg_STYLE wxCAPTION | wxSYSTEM_MENU | wxDIALOG_NO_PARENT | wxMINIMIZE_BOX | wxCLOSE_BOX
////Dialog Style End

class projektDlg : public wxDialog
{
	private:
		DECLARE_EVENT_TABLE();
		
	public:
		projektDlg(wxWindow *parent, wxWindowID id = 1, const wxString &title = wxT("projekt"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = projektDlg_STYLE);
		virtual ~projektDlg();
		void WxButton1Click(wxCommandEvent& event);
		void LoadImage1Click(wxCommandEvent& event);
		void LoadImage2Click(wxCommandEvent& event);
		void PreviewUpdateUI(wxUpdateUIEvent& event);
		void TYPESelected(wxCommandEvent& event );
		void OKButtonClick(wxCommandEvent& event);
		void CurrentFrameScroll(wxScrollEvent& event);
		void SaveSeqClick(wxCommandEvent& event);
	
	private:
		//Do not add custom control declarations between 
		//GUI Control Declaration Start and GUI Control Declaration End.
		//wxDev-C++ will remove them. Add custom code after the block.
		////GUI Control Declaration Start
		wxFileDialog *WxOpenFileDialog2;
		wxFileDialog *WxSaveFileDialog1;
		wxFileDialog *WxOpenFileDialog1;
		wxScrollBar *CurrentFrame;
		wxBoxSizer *WxBoxSizer5;
		wxPanel *Preview;
		wxBoxSizer *WxBoxSizer4;
		wxBoxSizer *WxBoxSizer3;
		wxButton *SaveSeq;
		wxBoxSizer *WxBoxSizer8;
		wxButton *OKButton;
		wxTextCtrl *NoOfFrames;
		wxBoxSizer *WxBoxSizer9;
		wxChoice *TYPE;
		wxBoxSizer *WxBoxSizer7;
		wxButton *LoadImage2;
		wxButton *LoadImage1;
		wxBoxSizer *WxBoxSizer6;
		wxBoxSizer *WxBoxSizer2;
		wxBoxSizer *WxBoxSizer1;
		////GUI Control Declaration End
		
	private:
		//Note: if you receive any error with these enum IDs, then you need to
		//change your old form code that are based on the #define control IDs.
		//#defines may replace a numeric value for the enum names.
		//Try copy and pasting the below block in your old form header files.
		enum
		{
			////GUI Enum Control ID Start
			ID_CURRENTFRAME = 1008,
			ID_PREVIEW = 1009,
			ID_SAVESEQ = 1015,
			ID_OKBUTTON = 1019,
			ID_NOOFFRAMES = 1018,
			ID_TYPE = 1013,
			ID_LOADIMAGE2 = 1016,
			ID_LOADIMAGE1 = 1012,
			////GUI Enum Control ID End
			ID_DUMMY_VALUE_ //don't remove this value unless you have other enum values
		};
	
	private:
		void OnClose(wxCloseEvent& event);
		void CreateGUIControls();
		wxImage* image1;
		wxImage* image2;
		wxImage* result;
		void (*process)(wxImage*, wxImage*, wxImage*, int, int);
		unsigned int noFrames;
        unsigned int current; 
};
#endif
