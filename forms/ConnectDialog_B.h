///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version 3.9.0 Nov 14 2020)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#pragma once

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/string.h>
#include <wx/stattext.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/textctrl.h>
#include <wx/valtext.h>
#include <wx/button.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/sizer.h>
#include <wx/dialog.h>

///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// Class ConnectDialog_B
///////////////////////////////////////////////////////////////////////////////
class ConnectDialog_B : public wxDialog
{
	private:

	protected:
		wxStaticText* m_staticText2;
		wxTextCtrl* server_ip_textctrl_;
		wxStaticText* m_staticText3;
		wxTextCtrl* pub_port_textctrl_;
		wxStaticText* m_staticText4;
		wxTextCtrl* sub_port_textctrl_;
		wxStaticText* m_staticText5;
		wxTextCtrl* name_textctrl_;
		wxButton* ok_button_;

		// Virtual event handlers, override them in your derived class
		virtual void connect( wxCommandEvent& event ) { event.Skip(); }


	public:
		wxString name_;

		ConnectDialog_B( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Connect to Server"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxDEFAULT_DIALOG_STYLE );
		~ConnectDialog_B();

};

