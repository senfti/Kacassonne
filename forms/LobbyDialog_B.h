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
#include <wx/sizer.h>
#include <wx/statline.h>
#include <wx/button.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/filepicker.h>
#include <wx/textctrl.h>
#include <wx/valtext.h>
#include <wx/dialog.h>

///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// Class LobbyDialog_B
///////////////////////////////////////////////////////////////////////////////
class LobbyDialog_B : public wxDialog
{
	private:

	protected:
		wxBoxSizer* window_sizer_;
		wxStaticText* version_textctrl_;
		wxStaticLine* m_staticline2;
		wxButton* reconnect_button_;
		wxStaticLine* m_staticline3;
		wxFilePickerCtrl* load_file_picker_;
		wxButton* load_button_;
		wxStaticLine* m_staticline4;
		wxStaticText* m_staticText1;
		wxTextCtrl* game_name_textctrl_;
		wxButton* create_button_;
		wxStaticLine* m_staticline1;
		wxBoxSizer* games_sizer_;

		// Virtual event handlers, override them in your derived class
		virtual void reconnect( wxCommandEvent& event ) { event.Skip(); }
		virtual void load( wxCommandEvent& event ) { event.Skip(); }
		virtual void create( wxCommandEvent& event ) { event.Skip(); }


	public:
		wxString tmp_game_name_;

		LobbyDialog_B( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Lobby"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxDEFAULT_DIALOG_STYLE );
		~LobbyDialog_B();

};

