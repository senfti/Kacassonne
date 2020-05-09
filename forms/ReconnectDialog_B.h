///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version 3.9.0 Mar 24 2020)
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
#include <wx/button.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/sizer.h>
#include <wx/dialog.h>

///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// Class ReconnectDialog_B
///////////////////////////////////////////////////////////////////////////////
class ReconnectDialog_B : public wxDialog
{
	private:

	protected:
		wxStaticText* m_staticText3;
		wxTextCtrl* game_id_textctrl_;
		wxStaticText* m_staticText4;
		wxTextCtrl* player_id_textctrl_;
		wxButton* m_button3;
		wxButton* m_button4;

		// Virtual event handlers, overide them in your derived class
		virtual void cancel( wxCommandEvent& event ) { event.Skip(); }
		virtual void connect( wxCommandEvent& event ) { event.Skip(); }


	public:

		ReconnectDialog_B( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Reconnect to Game"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxDEFAULT_DIALOG_STYLE );
		~ReconnectDialog_B();

};

