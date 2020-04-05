///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version 3.9.0 Mar 24 2020)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "TablePanel.h"

#include "MainFrame_B.h"

///////////////////////////////////////////////////////////////////////////

MainFrame_B::MainFrame_B( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	m_menubar1 = new wxMenuBar( 0 );
	m_menu1 = new wxMenu();
	start_server_menu_item_ = new wxMenuItem( m_menu1, wxID_ANY, wxString( wxT("Start Server") ) , wxEmptyString, wxITEM_NORMAL );
	m_menu1->Append( start_server_menu_item_ );

	wxMenuItem* connect_menu_item_;
	connect_menu_item_ = new wxMenuItem( m_menu1, wxID_ANY, wxString( wxT("Connect To Server") ) , wxEmptyString, wxITEM_NORMAL );
	m_menu1->Append( connect_menu_item_ );

	wxMenuItem* quit_menu_item_;
	quit_menu_item_ = new wxMenuItem( m_menu1, wxID_ANY, wxString( wxT("Quit") ) , wxEmptyString, wxITEM_NORMAL );
	m_menu1->Append( quit_menu_item_ );

	m_menubar1->Append( m_menu1, wxT("File") );

	m_menu2 = new wxMenu();
	wxMenuItem* undo_menu_item_;
	undo_menu_item_ = new wxMenuItem( m_menu2, wxID_ANY, wxString( wxT("Undo") ) , wxEmptyString, wxITEM_NORMAL );
	m_menu2->Append( undo_menu_item_ );

	m_menubar1->Append( m_menu2, wxT("Edit") );

	this->SetMenuBar( m_menubar1 );

	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer( wxHORIZONTAL );

	table_panel_ = new TablePanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxBORDER_SUNKEN|wxFULL_REPAINT_ON_RESIZE|wxTAB_TRAVERSAL );
	bSizer1->Add( table_panel_, 1, wxEXPAND | wxALL, 0 );

	wxBoxSizer* bSizer3;
	bSizer3 = new wxBoxSizer( wxVERTICAL );

	bSizer3->SetMinSize( wxSize( 200,-1 ) );
	wxBoxSizer* bSizer4;
	bSizer4 = new wxBoxSizer( wxVERTICAL );

	next_button_ = new wxButton( this, wxID_ANY, wxT("Next"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer4->Add( next_button_, 0, wxALL, 5 );

	back_button_ = new wxButton( this, wxID_ANY, wxT("Back"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer4->Add( back_button_, 0, wxALL, 5 );

	Shuffle = new wxButton( this, wxID_ANY, wxT("Shuffle"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer4->Add( Shuffle, 0, wxALL, 5 );


	bSizer3->Add( bSizer4, 0, wxEXPAND, 5 );

	info_sizer_ = new wxBoxSizer( wxVERTICAL );

	info_sizer_->SetMinSize( wxSize( 200,-1 ) );

	bSizer3->Add( info_sizer_, 1, wxEXPAND, 5 );


	bSizer1->Add( bSizer3, 0, wxEXPAND, 5 );


	this->SetSizer( bSizer1 );
	this->Layout();

	this->Centre( wxBOTH );

	// Connect Events
	m_menu1->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrame_B::startServer ), this, start_server_menu_item_->GetId());
	m_menu1->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrame_B::connect ), this, connect_menu_item_->GetId());
	m_menu1->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrame_B::quit ), this, quit_menu_item_->GetId());
	m_menu2->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrame_B::undo ), this, undo_menu_item_->GetId());
	next_button_->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrame_B::next ), NULL, this );
	back_button_->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrame_B::back ), NULL, this );
	Shuffle->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrame_B::shuffle ), NULL, this );
}

MainFrame_B::~MainFrame_B()
{
	// Disconnect Events
	next_button_->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrame_B::next ), NULL, this );
	back_button_->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrame_B::back ), NULL, this );
	Shuffle->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrame_B::shuffle ), NULL, this );

}
