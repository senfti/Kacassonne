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
#include <wx/checkbox.h>
#include <wx/sizer.h>
#include <wx/choice.h>
#include <wx/dialog.h>

///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// Class PointEntryDialog_B
///////////////////////////////////////////////////////////////////////////////
class PointEntryDialog_B : public wxDialog
{
	private:

	protected:
		wxStaticText* m_staticText7;
		wxTextCtrl* points_textctrl_;
		wxCheckBox* add_checkbox_;
		wxChoice* player_choice_;

		// Virtual event handlers, overide them in your derived class
		virtual void keyDown( wxKeyEvent& event ) { event.Skip(); }


	public:

		PointEntryDialog_B( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Add Points"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxDEFAULT_DIALOG_STYLE );
		~PointEntryDialog_B();

};

