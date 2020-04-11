///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version 3.9.0 Mar 24 2020)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#pragma once

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
class TablePanel;

#include <wx/string.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/menu.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/panel.h>
#include <wx/button.h>
#include <wx/sizer.h>
#include <wx/frame.h>

///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// Class MainFrame_B
///////////////////////////////////////////////////////////////////////////////
class MainFrame_B : public wxFrame
{
	private:

	protected:
		wxMenuBar* m_menubar1;
		wxMenu* m_menu1;
		wxMenu* m_menu2;
		wxMenu* help_menu_;
		TablePanel* table_panel_;
		wxButton* next_button_;
		wxButton* back_button_;
		wxButton* shuffle_button_;
		wxBoxSizer* info_sizer_;

		// Virtual event handlers, overide them in your derived class
		virtual void quit( wxCommandEvent& event ) { event.Skip(); }
		virtual void next( wxCommandEvent& event ) { event.Skip(); }
		virtual void back( wxCommandEvent& event ) { event.Skip(); }
		virtual void shuffle( wxCommandEvent& event ) { event.Skip(); }


	public:

		MainFrame_B( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Kacassonne"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 1257,833 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );

		~MainFrame_B();

};

