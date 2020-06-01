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
#include <wx/choice.h>
#include <wx/sizer.h>
#include <wx/textctrl.h>
#include <wx/button.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/dialog.h>

///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// Class SettingsWindow_B
///////////////////////////////////////////////////////////////////////////////
class SettingsWindow_B : public wxDialog
{
	private:

	protected:
		wxStaticText* m_staticText2;
		wxChoice* setting_choice_;
		wxGridSizer* image_sizer_;
		wxStaticText* m_staticText1;
		wxTextCtrl* name_textctrl_;
		wxButton* save_button_;
		wxButton* ok_button_;

		// Virtual event handlers, overide them in your derived class
		virtual void changeSetting( wxCommandEvent& event ) { event.Skip(); }
		virtual void save( wxCommandEvent& event ) { event.Skip(); }
		virtual void ok( wxCommandEvent& event ) { event.Skip(); }


	public:

		SettingsWindow_B( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Settings"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 1200,800 ), long style = wxDEFAULT_DIALOG_STYLE );
		~SettingsWindow_B();

};

