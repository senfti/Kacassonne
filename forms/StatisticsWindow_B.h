///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version 3.9.0 Nov 14 2020)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#pragma once

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/panel.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/string.h>
#include <wx/grid.h>
#include <wx/sizer.h>
#include <wx/frame.h>

///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// Class StatisticsWindow_B
///////////////////////////////////////////////////////////////////////////////
class StatisticsWindow_B : public wxFrame
{
	private:

	protected:
		wxBoxSizer* sizer_;
		wxPanel* graph_panel_;
		wxGrid* stats_grid_;

		// Virtual event handlers, override them in your derived class
		virtual void paint( wxPaintEvent& event ) { event.Skip(); }


	public:

		StatisticsWindow_B( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Statistics"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( -1,-1 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );

		~StatisticsWindow_B();

};

