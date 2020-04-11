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
#include <wx/sizer.h>
#include <wx/button.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/dialog.h>

///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// Class GameDialog_B
///////////////////////////////////////////////////////////////////////////////
class GameDialog_B : public wxDialog
{
	private:

	protected:
		wxBoxSizer* sizer_;
		wxStaticText* m_staticText2;
		wxStaticText* players_textctrl_;
		wxButton* quit_button_;
		wxButton* start_button_;

		// Virtual event handlers, overide them in your derived class
		virtual void quit( wxCommandEvent& event ) { event.Skip(); }
		virtual void start( wxCommandEvent& event ) { event.Skip(); }


	public:
		wxTextCtrl* numcard_textctrl_;

		GameDialog_B( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Game Lobby"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxDEFAULT_DIALOG_STYLE );
		~GameDialog_B();

};

