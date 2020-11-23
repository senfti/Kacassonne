///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version 3.9.0 Nov 14 2020)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#pragma once

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/string.h>
#include <wx/font.h>
#include <wx/grid.h>
#include <wx/gdicmn.h>
#include <wx/sizer.h>
#include <wx/frame.h>

///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// Class PointHistoryWindow
///////////////////////////////////////////////////////////////////////////////
class PointHistoryWindow : public wxFrame
{
	private:

	protected:
		wxGrid* pts_grid_;

	public:

		PointHistoryWindow( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Point History"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 500,300 ), long style = wxCAPTION|wxSTAY_ON_TOP|wxTAB_TRAVERSAL );

		~PointHistoryWindow();

};

