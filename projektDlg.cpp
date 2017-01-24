///-----------------------------------------------------------------
///
/// @file      projektDlg.cpp
/// @author    Tezi
/// Created:   14.12.2016 11:36:29
/// @section   DESCRIPTION
///            projektDlg class implementation
///
///------------------------------------------------------------------

#include "projektDlg.h"

//Do not add custom headers
//wxDev-C++ designer will remove them
////Header Include Start
////Header Include End
#include "effects.h"
//----------------------------------------------------------------------------
// projektDlg
//----------------------------------------------------------------------------
//Add Custom Events only in the appropriate block.
//Code added in other places will be removed by wxDev-C++
////Event Table Start
BEGIN_EVENT_TABLE(projektDlg,wxDialog)
	////Manual Code Start
	////Manual Code End
	
	EVT_CLOSE(projektDlg::OnClose)
	
	EVT_COMMAND_SCROLL(ID_CURRENTFRAME,projektDlg::CurrentFrameScroll)
	
	EVT_UPDATE_UI(ID_PREVIEW,projektDlg::PreviewUpdateUI)
	EVT_BUTTON(ID_SAVESEQ,projektDlg::SaveSeqClick)
	EVT_BUTTON(ID_OKBUTTON,projektDlg::OKButtonClick)
	EVT_CHOICE(ID_TYPE,projektDlg::TYPESelected)
	EVT_BUTTON(ID_LOADIMAGE2,projektDlg::LoadImage2Click)
	EVT_BUTTON(ID_LOADIMAGE1,projektDlg::LoadImage1Click)
END_EVENT_TABLE()
////Event Table End

projektDlg::projektDlg(wxWindow *parent, wxWindowID id, const wxString &title, const wxPoint &position, const wxSize& size, long style)
: wxDialog(parent, id, title, position, size, style)
{
	CreateGUIControls();
	image1 = NULL;
	image2 = NULL;
	result = NULL;
}

projektDlg::~projektDlg()
{
} 

void projektDlg::CreateGUIControls()
{
	//Do not add custom code between
	//GUI Items Creation Start and GUI Items Creation End.
	//wxDev-C++ designer will remove them.
	//Add the custom code before or after the blocks
	////GUI Items Creation Start

	WxBoxSizer1 = new wxBoxSizer(wxHORIZONTAL);
	this->SetSizer(WxBoxSizer1);
	this->SetAutoLayout(true);

	WxBoxSizer2 = new wxBoxSizer(wxVERTICAL);
	WxBoxSizer1->Add(WxBoxSizer2, 0, wxALIGN_CENTER | wxALL, 5);

	WxBoxSizer6 = new wxBoxSizer(wxHORIZONTAL);
	WxBoxSizer2->Add(WxBoxSizer6, 0, wxALIGN_CENTER | wxALL, 5);

	LoadImage1 = new wxButton(this, ID_LOADIMAGE1, _("Wczytaj pierwszy\nobraz"), wxPoint(5, 5), wxSize(100, 50), 0, wxDefaultValidator, _("LoadImage1"));
	WxBoxSizer6->Add(LoadImage1, 0, wxALIGN_CENTER | wxALL, 5);

	LoadImage2 = new wxButton(this, ID_LOADIMAGE2, _("Wczytaj drugi\nobraz"), wxPoint(115, 5), wxSize(100, 50), 0, wxDefaultValidator, _("LoadImage2"));
	WxBoxSizer6->Add(LoadImage2, 0, wxALIGN_CENTER | wxALL, 5);

	WxBoxSizer7 = new wxBoxSizer(wxHORIZONTAL);
	WxBoxSizer2->Add(WxBoxSizer7, 0, wxALIGN_CENTER | wxALL, 5);

	wxArrayString arrayStringFor_TYPE;
	arrayStringFor_TYPE.Add(_("Wjazd z lewej"));
	arrayStringFor_TYPE.Add(_("Wjazd z prawej"));
	arrayStringFor_TYPE.Add(_("Wjazd z góry"));
	arrayStringFor_TYPE.Add(_("Wjzad z do³u"));
	arrayStringFor_TYPE.Add(_("Boks wchodz¹cy"));
	arrayStringFor_TYPE.Add(_("Boks wychodz¹cy"));
	arrayStringFor_TYPE.Add(_("Œciemnianie"));
	arrayStringFor_TYPE.Add(_("Przejœcie"));
	arrayStringFor_TYPE.Add(_("Obrót poziomy"));
	arrayStringFor_TYPE.Add(_("Obrót pionowy"));
	arrayStringFor_TYPE.Add(_("Wejœcie"));
	TYPE = new wxChoice(this, ID_TYPE, wxPoint(5, 5), wxSize(200, 23), arrayStringFor_TYPE, 0, wxDefaultValidator, _("TYPE"));
	TYPE->Enable(false);
	TYPE->SetSelection(-1);
	WxBoxSizer7->Add(TYPE, 0, wxALIGN_CENTER | wxALL, 5);

	WxBoxSizer9 = new wxBoxSizer(wxHORIZONTAL);
	WxBoxSizer2->Add(WxBoxSizer9, 0, wxALIGN_CENTER | wxALL, 5);

	NoOfFrames = new wxTextCtrl(this, ID_NOOFFRAMES, _("Podaj liczbê klatek"), wxPoint(5, 8), wxSize(121, 19), 0, wxDefaultValidator, _("NoOfFrames"));
	NoOfFrames->Enable(false);
	WxBoxSizer9->Add(NoOfFrames, 0, wxALIGN_CENTER | wxALL, 5);

	OKButton = new wxButton(this, ID_OKBUTTON, _("OK"), wxPoint(136, 5), wxSize(75, 25), 0, wxDefaultValidator, _("OKButton"));
	OKButton->Enable(false);
	WxBoxSizer9->Add(OKButton, 0, wxALIGN_CENTER | wxALL, 5);

	WxBoxSizer8 = new wxBoxSizer(wxHORIZONTAL);
	WxBoxSizer2->Add(WxBoxSizer8, 0, wxALIGN_CENTER | wxALL, 5);

	SaveSeq = new wxButton(this, ID_SAVESEQ, _("Zapisz sekwencje"), wxPoint(5, 5), wxSize(100, 50), 0, wxDefaultValidator, _("SaveSeq"));
	SaveSeq->Enable(false);
	WxBoxSizer8->Add(SaveSeq, 0, wxALIGN_CENTER | wxALL, 5);

	WxBoxSizer3 = new wxBoxSizer(wxVERTICAL);
	WxBoxSizer1->Add(WxBoxSizer3, 1, wxALIGN_RIGHT | wxALIGN_CENTER | wxALL, 5);

	WxBoxSizer4 = new wxBoxSizer(wxHORIZONTAL);
	WxBoxSizer3->Add(WxBoxSizer4, 1, wxALIGN_CENTER | wxALL, 5);

	Preview = new wxPanel(this, ID_PREVIEW, wxPoint(5, 5), wxSize(500, 500));
	WxBoxSizer4->Add(Preview, 1, wxALIGN_CENTER | wxALL, 5);

	WxBoxSizer5 = new wxBoxSizer(wxHORIZONTAL);
	WxBoxSizer3->Add(WxBoxSizer5, 0, wxALIGN_BOTTOM | wxALIGN_CENTER | wxALL, 5);

	CurrentFrame = new wxScrollBar(this, ID_CURRENTFRAME, wxPoint(5, 5), wxSize(121, 17), wxSB_HORIZONTAL, wxDefaultValidator, _("CurrentFrame"));
	CurrentFrame->Enable(false);
	WxBoxSizer5->Add(CurrentFrame, 0, wxALIGN_BOTTOM | wxALIGN_CENTER | wxALL, 5);

	WxOpenFileDialog1 =  new wxFileDialog(this, _("Choose a file"), _(""), _(""), _("*.jpg"), wxFD_OPEN);

	WxSaveFileDialog1 =  new wxFileDialog(this, _("Choose a file"), _(""), _(""), _("*.jpg"), wxFD_SAVE);

	WxOpenFileDialog2 =  new wxFileDialog(this, _("Choose a file"), _(""), _(""), _("*.jpg"), wxFD_OPEN);

	SetTitle(_("projekt"));
	SetIcon(wxNullIcon);
	
	Layout();
	GetSizer()->Fit(this);
	GetSizer()->SetSizeHints(this);
	Center();
	
	////GUI Items Creation End
	wxInitAllImageHandlers();	
    return;
}

void projektDlg::OnClose(wxCloseEvent& /*event*/)
{
	Destroy();
	return;
}

/*
 * LoadImage1Click
 */
void projektDlg::LoadImage1Click(wxCommandEvent& event)
{
	if(WxOpenFileDialog1->ShowModal() == wxID_CANCEL)
	   return;
	else {
        if(image1)
            delete image1;
        image1 = new wxImage(WxOpenFileDialog1->GetPath(),wxBITMAP_TYPE_JPEG);
        if(image1 && image2) {
            if(image1->IsOk() && image2->IsOk()) {
                int w, h;
                if(image1->GetWidth()*image1->GetHeight() > image2->GetWidth()*image2->GetHeight()) {
                    w = image1->GetWidth();
                    h = image1->GetHeight();
                }
                else {
                    w = image2->GetWidth();
                    h = image2->GetHeight();
                }
                image1->Rescale(w,h);
                image2->Rescale(w,h);
                TYPE->Enable(true);
            }
             else {
                TYPE->Enable(false);
                NoOfFrames->Enable(false);
                OKButton->Enable(false);
                SaveSeq->Enable(false);
                CurrentFrame->Enable(false);
            }
        }
        else {
                TYPE->Enable(false);
                NoOfFrames->Enable(false);
                OKButton->Enable(false);
                SaveSeq->Enable(false);
                CurrentFrame->Enable(false);
        }
    }
    return;
}

/*
 * LoadImage2Click
 */
void projektDlg::LoadImage2Click(wxCommandEvent& event)
{
	if(WxOpenFileDialog2->ShowModal() == wxID_CANCEL)
	   return;
	else {
        if(image2)
            delete image2;
        image2 = new wxImage(WxOpenFileDialog2->GetPath(),wxBITMAP_TYPE_JPEG);
        if(image1 && image2) {
            if(image1->IsOk() && image2->IsOk()) {
                int w, h;
                if(image1->GetWidth()*image1->GetHeight() > image2->GetWidth()*image2->GetHeight()) {
                    w = image1->GetWidth();
                    h = image1->GetHeight();
                }
                else {
                    w = image2->GetWidth();
                    h = image2->GetHeight();
                }
                image1->Rescale(w,h);
                image2->Rescale(w,h);
                TYPE->Enable(true);
            }
             else {
                TYPE->Enable(false);
                NoOfFrames->Enable(false);
                OKButton->Enable(false);
                SaveSeq->Enable(false);
                CurrentFrame->Enable(false);
            }
        }
        else {
                TYPE->Enable(false);
                NoOfFrames->Enable(false);
                OKButton->Enable(false);
                SaveSeq->Enable(false);
                CurrentFrame->Enable(false);
        }
    }
    return;
}

/*
 * PreviewUpdateUI
 */
void projektDlg::PreviewUpdateUI(wxUpdateUIEvent& event)
{
    if(image1 && image2 && result) {
        if(image1->IsOk() && image2->IsOk() && result->IsOk()) {
            wxClientDC dc(Preview);
            wxBufferedDC buff(&dc);
            wxCoord w, h;
            Preview->GetClientSize(&w, &h);
            wxImage img;               
	        img = result->Scale(w,h);
            wxBitmap bitmap(img);
            buff.Clear();
            buff.DrawBitmap(bitmap, 0, 0, true);
        }
    }
    return;
}

/*
 * TYPESelected
 */
void projektDlg::TYPESelected(wxCommandEvent& event )
{
	switch(TYPE->GetSelection()) {
        case 0:
            process = enterLeft;  
            NoOfFrames->Enable(true);
            OKButton->Enable(true);
            break;
        case 1:
            process = enterRight;
            NoOfFrames->Enable(true);
            OKButton->Enable(true);
            break;
        case 2:
            process = enterUp;
            NoOfFrames->Enable(true);
            OKButton->Enable(true);
            break;
        case 3:
            process = enterDown;
            NoOfFrames->Enable(true);
            OKButton->Enable(true);
            break;
        case 7:
            process = transition;  
            NoOfFrames->Enable(true);
            OKButton->Enable(true);
            break;
        case 8:
            process = horizontalFlip;  
            NoOfFrames->Enable(true);
            OKButton->Enable(true);
            break;
        case 9:
            process = verticalFlip;  
            NoOfFrames->Enable(true);
            OKButton->Enable(true);
            break;
        default:
            process = NULL;
            NoOfFrames->Enable(false);
            OKButton->Enable(false);
            SaveSeq->Enable(false);
            CurrentFrame->Enable(false);
    }
    return;
}



/*
 * OKButtonClick
 */
void projektDlg::OKButtonClick(wxCommandEvent& event)
{
	std::string s = (NoOfFrames->GetLineText(0)).ToStdString();
	if(is_number(s)) {
        noFrames = atoi(s.c_str());
        SaveSeq->Enable(true);
        CurrentFrame->SetScrollbar(0,1,noFrames,1);
        CurrentFrame->Enable(true);
        wxScrollEvent temp = wxScrollEvent(wxEVT_NULL,0,CurrentFrame->GetThumbPosition());
        CurrentFrameScroll(temp);
    }
    else {
        wxMessageBox("Niepoprawna iloœæ klatek");
        SaveSeq->Enable(false);
        CurrentFrame->Enable(false);
    }
	return;
}

/*
 * CurrentFrameScroll
 */
void projektDlg::CurrentFrameScroll(wxScrollEvent& event)
{
    if(image1 && image2) {
	   if(image1->IsOk() && image2->IsOk()) {
            if(result)
	           delete result;
	        result = new wxImage(image1->GetWidth(),image1->GetHeight());
            process(result,image1,image2,CurrentFrame->GetThumbPosition(),noFrames);
        }    
    }
    return;
}

/*
 * SaveSeqClick
 */
void projektDlg::SaveSeqClick(wxCommandEvent& event)
{
	if(WxSaveFileDialog1->ShowModal() == wxID_CANCEL)
	   return;
	else {
        if(CurrentFrame->IsEnabled()) {
            char buff[16];
            wxImage* toSave = NULL;
            for(int i = 0; i < noFrames; i++) {
                if(toSave)
                    delete toSave;
                toSave = new wxImage(image1->GetWidth(),image1->GetHeight());
                process(toSave,image1,image2,i,noFrames); 
                wxString path = WxSaveFileDialog1->GetPath();
                path = path.SubString(0,path.Length()-5);
                toSave->SaveFile(path + wxString(itoa(i+1,buff,10)) + wxString(".jpg"),wxBITMAP_TYPE_JPEG);
            }
        }
        else {
            wxMessageBox("B³¹d");
        }
    }
    return;
}
