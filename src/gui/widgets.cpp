/*
 * widgets.cpp
 *
 *  Created on: Mar 8, 2017
 *      Author: kobus
 */

#include <boost/thread/pthread/thread_data.hpp>
#include "widgets.h"


// ----------------------------------------------------------------------------
// private classes
// ----------------------------------------------------------------------------

TiDspParameters tiDspParams;
TiCameraParameters tiCameraParams;

// ----------------------------------------------------------------------------
// constants
// ----------------------------------------------------------------------------

// IDs for the controls and the menu commands
enum
{
    // menu items
    Minimal_Quit = wxID_EXIT,

    // it is important for the id corresponding to the "About" command to have
    // this standard value as otherwise it won't be handled properly under Mac
    // (where it is special and put into the "Apple" menu)
    Minimal_About = wxID_ABOUT,
    QUEUE_TIMER
};

// ----------------------------------------------------------------------------
// event tables and other macros for wxWidgets
// ----------------------------------------------------------------------------

// the event tables connect the wxWidgets events with the functions (event
// handlers) which process them. It can be also done at run-time, but for the
// simple menu events like this the static method is much simpler.
wxBEGIN_EVENT_TABLE(MyFrame1, wxFrame)
    EVT_MENU(Minimal_Quit,  MyFrame1::OnQuit)
    EVT_MENU(Minimal_About, MyFrame1::OnAbout)
    EVT_TIMER(QUEUE_TIMER, MyFrame1::OnQueueTimer)
wxEND_EVENT_TABLE()

// Create a new application object: this macro will allow wxWidgets to create
// the application object during program execution (it's better than using a
// static object for many reasons) and also implements the accessor function
// wxGetApp() which will return the reference of the right type (i.e. MyApp and
// not wxApp)
wxIMPLEMENT_APP_NO_MAIN(MyApp);
IMPLEMENT_WX_THEME_SUPPORT;


// ============================================================================
// implementation
// ============================================================================

// ----------------------------------------------------------------------------
// the application class
// ----------------------------------------------------------------------------

// 'Main program' equivalent: the program execution "starts" here
bool MyApp::OnInit()
{
    // call the base class initialization method, currently it only parses a
    // few common command-line options but it could be do more in the future
    if ( !wxApp::OnInit() )
        return false;

    // create the main application window
    myFrame = new MyFrame1("Thermal imager pipeline");

    // and show it (the frames, unlike simple controls, are not shown when
    // created initially)
    myFrame->Show(true);

    // success: wxApp::OnRun() will be called which will enter the main message
    // loop and the application will run. If we returneCannyd false here, the
    // application would exit immediately.
    return true;
}

void MyApp::InitQueues(Queues* qs)
{
	queues = qs;
	myFrame->InitQueues(qs);

    static const int INTERVAL = 1000; // milliseconds
    myFrame->qTimer = new wxTimer(myFrame, QUEUE_TIMER);
    myFrame->qTimer->Start(INTERVAL);
};



// ----------------------------------------------------------------------------
// main frame
// ----------------------------------------------------------------------------

// frame constructor
MyFrame1::MyFrame1(const wxString& title)
       : wxFrame(NULL, wxID_ANY, title)
{
    this->SetSizeHints( wxDefaultSize, wxDefaultSize );

    wxBoxSizer* bSizer1;
    bSizer1 = new wxBoxSizer( wxHORIZONTAL );

    wxBoxSizer* bSizer2;
    bSizer2 = new wxBoxSizer( wxVERTICAL );

    wxGridSizer* gSizer1;
    gSizer1 = new wxGridSizer( 13, 2, 0, 0 );

    m_staticText1 = new wxStaticText( this, wxID_ANY, wxT("Output select"), wxDefaultPosition, wxDefaultSize, 0 );
    m_staticText1->Wrap( -1 );
    m_staticText1->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, true, wxEmptyString ) );

    gSizer1->Add( m_staticText1, 0, wxALL, 5 );

    m_staticText2 = new wxStaticText( this, wxID_ANY, wxT("Active"), wxDefaultPosition, wxDefaultSize, 0 );
    m_staticText2->Wrap( -1 );
    m_staticText2->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, true, wxEmptyString ) );

    gSizer1->Add( m_staticText2, 0, wxALL, 5 );

    m_buttonRaw = new wxButton( this, wxID_ANY, wxT("Raw"), wxDefaultPosition, wxDefaultSize, 0 );
    gSizer1->Add( m_buttonRaw, 0, wxALL, 5 );

    m_checkBoxRaw = new wxCheckBox( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
    m_checkBoxRaw->SetValue(true);
    m_checkBoxRaw->Enable( false );

    gSizer1->Add( m_checkBoxRaw, 0, wxALL, 5 );

    m_buttonGrayScale = new wxButton( this, wxID_ANY, wxT("Gray scale"), wxDefaultPosition, wxDefaultSize, 0 );
    gSizer1->Add( m_buttonGrayScale, 0, wxALL, 5 );

    m_checkBoxGrayScale = new wxCheckBox( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
    m_checkBoxGrayScale->SetValue(true);
    gSizer1->Add( m_checkBoxGrayScale, 0, wxALL, 5 );

    m_buttonNonU = new wxButton( this, wxID_ANY, wxT("Non uniformity"), wxDefaultPosition, wxDefaultSize, 0 );
    gSizer1->Add( m_buttonNonU, 0, wxALL, 5 );

    m_checkBoxNonUniformity = new wxCheckBox( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
    m_checkBoxNonUniformity->SetValue(true);
    gSizer1->Add( m_checkBoxNonUniformity, 0, wxALL, 5 );

    m_buttonFrameAverager = new wxButton( this, wxID_ANY, wxT("Frame averager"), wxDefaultPosition, wxDefaultSize, 0 );
    gSizer1->Add( m_buttonFrameAverager, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxALL, 5 );

    m_checkBoxFrameAverager = new wxCheckBox( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
    m_checkBoxFrameAverager->SetValue(true);
    gSizer1->Add( m_checkBoxFrameAverager, 0, wxALL, 5 );

    m_buttonNuc = new wxButton( this, wxID_ANY, wxT("NUC"), wxDefaultPosition, wxDefaultSize, 0 );
    m_buttonNuc->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_GRAYTEXT ) );

    gSizer1->Add( m_buttonNuc, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxALL, 5 );

    m_checkBoxNuc = new wxCheckBox( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
    m_checkBoxNuc->SetValue(true);
    gSizer1->Add( m_checkBoxNuc, 0, wxALL, 5 );

    m_buttonTFilter = new wxButton( this, wxID_ANY, wxT("Temporal filter"), wxDefaultPosition, wxDefaultSize, 0 );
    m_buttonTFilter->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_GRAYTEXT ) );

    gSizer1->Add( m_buttonTFilter, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxALL, 5 );

    m_checkBoxTFilter = new wxCheckBox( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
    m_checkBoxTFilter->SetValue(true);
    gSizer1->Add( m_checkBoxTFilter, 0, wxALL, 5 );

    m_buttonSFilter = new wxButton( this, wxID_ANY, wxT("Spatial filter"), wxDefaultPosition, wxDefaultSize, 0 );
    m_buttonSFilter->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_GRAYTEXT ) );

    gSizer1->Add( m_buttonSFilter, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxALL, 5 );

    m_checkBoxSFilter = new wxCheckBox( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
    m_checkBoxSFilter->SetValue(true);
    gSizer1->Add( m_checkBoxSFilter, 0, wxALL, 5 );

    m_buttonEdgeEnhance = new wxButton( this, wxID_ANY, wxT("Edge enhance"), wxDefaultPosition, wxDefaultSize, 0 );
    gSizer1->Add( m_buttonEdgeEnhance, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxALL, 5 );

    m_checkBoxEdgeEnhance = new wxCheckBox( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
    m_checkBoxEdgeEnhance->SetValue(true);
    gSizer1->Add( m_checkBoxEdgeEnhance, 0, wxALL, 5 );

    m_buttonStab = new wxButton( this, wxID_ANY, wxT("Stab"), wxDefaultPosition, wxDefaultSize, 0 );
    m_buttonStab->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_GRAYTEXT ) );

    gSizer1->Add( m_buttonStab, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxALL, 5 );

    m_checkBoxAgc = new wxCheckBox( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
    m_checkBoxAgc->SetValue(true);
    gSizer1->Add( m_checkBoxAgc, 0, wxALL, 5 );

    m_buttonEzoom = new wxButton( this, wxID_ANY, wxT("E-Zoom"), wxDefaultPosition, wxDefaultSize, 0 );
    gSizer1->Add( m_buttonEzoom, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxALL, 5 );

    m_checkBoxEzoom = new wxCheckBox( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
    m_checkBoxEzoom->SetValue(true);
    gSizer1->Add( m_checkBoxEzoom, 0, wxALL, 5 );

    m_buttonStretch = new wxButton( this, wxID_ANY, wxT("Stretch"), wxDefaultPosition, wxDefaultSize, 0 );
    gSizer1->Add( m_buttonStretch, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxALL, 5 );

    m_checkBoxStretch = new wxCheckBox( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
    m_checkBoxStretch->SetValue(true);
    gSizer1->Add( m_checkBoxStretch, 0, wxALL, 5 );

    m_buttonColorize = new wxButton( this, wxID_ANY, wxT("Colorize"), wxDefaultPosition, wxDefaultSize, 0 );
    m_buttonColorize->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_GRAYTEXT ) );

    gSizer1->Add( m_buttonColorize, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxALL, 5 );

    m_checkBoxColorize = new wxCheckBox( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
    m_checkBoxColorize->SetValue(true);
    gSizer1->Add( m_checkBoxColorize, 0, wxALL, 5 );


    bSizer2->Add( gSizer1, 0, wxALIGN_LEFT|wxFIXED_MINSIZE, 5 );


    bSizer1->Add( bSizer2, 0, 0, 5 );

    wxBoxSizer* bSizer9;
    bSizer9 = new wxBoxSizer( wxVERTICAL );

    m_choicebook2 = new wxChoicebook( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxCHB_DEFAULT );
    m_panel1 = new wxPanel( m_choicebook2, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
    wxBoxSizer* bSizer16;
    bSizer16 = new wxBoxSizer( wxVERTICAL );

    m_staticText26 = new wxStaticText( m_panel1, wxID_ANY, wxT("Threshold:"), wxDefaultPosition, wxDefaultSize, 0 );
    m_staticText26->Wrap( -1 );
    bSizer16->Add( m_staticText26, 0, wxALL, 5 );

    m_sliderFrameAveragerThreshold = new wxSlider( m_panel1, wxID_ANY, 50, 0, 100, wxDefaultPosition, wxDefaultSize, wxSL_HORIZONTAL );
    bSizer16->Add( m_sliderFrameAveragerThreshold, 0, wxALL|wxEXPAND, 5 );


    m_panel1->SetSizer( bSizer16 );
    m_panel1->Layout();
    bSizer16->Fit( m_panel1 );
    m_choicebook2->AddPage( m_panel1, wxT("Frame averager"), false );
    m_panel2 = new wxPanel( m_choicebook2, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
    wxBoxSizer* bSizer18;
    bSizer18 = new wxBoxSizer( wxVERTICAL );

    m_buttonSample = new wxButton( m_panel2, wxID_ANY, wxT("Sample"), wxDefaultPosition, wxDefaultSize, 0 );
    bSizer18->Add( m_buttonSample, 0, wxALL, 5 );


    m_panel2->SetSizer( bSizer18 );
    m_panel2->Layout();
    bSizer18->Fit( m_panel2 );
    m_choicebook2->AddPage( m_panel2, wxT("NUC"), false );
    m_panel3 = new wxPanel( m_choicebook2, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
    m_choicebook2->AddPage( m_panel3, wxT("Temporal filter"), false );
    m_panel4 = new wxPanel( m_choicebook2, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
    m_choicebook2->AddPage( m_panel4, wxT("Spatial filter"), false );
    m_panel5 = new wxPanel( m_choicebook2, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
    wxBoxSizer* bSizer14;
    bSizer14 = new wxBoxSizer( wxVERTICAL );

    wxBoxSizer* bSizer3;
    bSizer3 = new wxBoxSizer( wxHORIZONTAL );

    m_panelGaussian = new wxPanel( m_panel5, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxRAISED_BORDER|wxTAB_TRAVERSAL );
    m_panelGaussian->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_GRAYTEXT ) );

    wxBoxSizer* bSizer4;
    bSizer4 = new wxBoxSizer( wxVERTICAL );

    m_buttonGaussian = new wxButton( m_panelGaussian, wxID_ANY, wxT("Gaussian"), wxDefaultPosition, wxDefaultSize, 0 );
    bSizer4->Add( m_buttonGaussian, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5 );


    m_panelGaussian->SetSizer( bSizer4 );
    m_panelGaussian->Layout();
    bSizer4->Fit( m_panelGaussian );
    bSizer3->Add( m_panelGaussian, 1, wxEXPAND | wxALL, 5 );

    m_panelSharpen = new wxPanel( m_panel5, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxRAISED_BORDER|wxTAB_TRAVERSAL );
    m_panelSharpen->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_WINDOW ) );

    wxBoxSizer* bSizer7;
    bSizer7 = new wxBoxSizer( wxVERTICAL );

    m_buttonSharpen = new wxButton( m_panelSharpen, wxID_ANY, wxT("Sharpen"), wxDefaultPosition, wxDefaultSize, 0 );
    bSizer7->Add( m_buttonSharpen, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5 );


    m_panelSharpen->SetSizer( bSizer7 );
    m_panelSharpen->Layout();
    bSizer7->Fit( m_panelSharpen );
    bSizer3->Add( m_panelSharpen, 1, wxEXPAND | wxALL, 5 );

    m_panelUnsharpMask = new wxPanel( m_panel5, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxRAISED_BORDER|wxTAB_TRAVERSAL );
    m_panelUnsharpMask->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_WINDOW ) );

    wxBoxSizer* bSizer8;
    bSizer8 = new wxBoxSizer( wxVERTICAL );

    m_buttonUnsharpMask = new wxButton( m_panelUnsharpMask, wxID_ANY, wxT("Unsharp mask"), wxDefaultPosition, wxDefaultSize, 0 );
    bSizer8->Add( m_buttonUnsharpMask, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5 );


    m_panelUnsharpMask->SetSizer( bSizer8 );
    m_panelUnsharpMask->Layout();
    bSizer8->Fit( m_panelUnsharpMask );
    bSizer3->Add( m_panelUnsharpMask, 1, wxEXPAND | wxALL, 5 );


    bSizer14->Add( bSizer3, 1, wxEXPAND, 5 );


    m_panel5->SetSizer( bSizer14 );
    m_panel5->Layout();
    bSizer14->Fit( m_panel5 );
    m_choicebook2->AddPage( m_panel5, wxT("Edge enhance"), false );
    m_panel6 = new wxPanel( m_choicebook2, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
    wxBoxSizer* bSizer19;
    bSizer19 = new wxBoxSizer( wxVERTICAL );

    m_buttonStabLock = new wxButton( m_panel6, wxID_ANY, wxT("Lock"), wxDefaultPosition, wxDefaultSize, 0 );
    bSizer19->Add( m_buttonStabLock, 0, wxALL, 5 );

    m_buttonStabLetGo = new wxButton( m_panel6, wxID_ANY, wxT("Let go"), wxDefaultPosition, wxDefaultSize, 0 );
    bSizer19->Add( m_buttonStabLetGo, 0, wxALL, 5 );


    m_panel6->SetSizer( bSizer19 );
    m_panel6->Layout();
    bSizer19->Fit( m_panel6 );
    m_choicebook2->AddPage( m_panel6, wxT("Stab"), true );
    m_panel7 = new wxPanel( m_choicebook2, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
    wxBoxSizer* bSizer161;
    bSizer161 = new wxBoxSizer( wxVERTICAL );

    wxBoxSizer* bSizer17;
    bSizer17 = new wxBoxSizer( wxHORIZONTAL );

    m_radioBtnNoZoom = new wxRadioButton( m_panel7, wxID_ANY, wxT("No Zoom"), wxDefaultPosition, wxDefaultSize, 0 );
    bSizer17->Add( m_radioBtnNoZoom, 0, wxALL, 5 );

    m_radioBtn2xZoom = new wxRadioButton( m_panel7, wxID_ANY, wxT("2x"), wxDefaultPosition, wxDefaultSize, 0 );
    bSizer17->Add( m_radioBtn2xZoom, 0, wxALL, 5 );

    radioBtn4xZoom = new wxRadioButton( m_panel7, wxID_ANY, wxT("4x"), wxDefaultPosition, wxDefaultSize, 0 );
    bSizer17->Add( radioBtn4xZoom, 0, wxALL, 5 );

    radioBtn8xZoom = new wxRadioButton( m_panel7, wxID_ANY, wxT("8x"), wxDefaultPosition, wxDefaultSize, 0 );
    bSizer17->Add( radioBtn8xZoom, 0, wxALL, 5 );


    bSizer161->Add( bSizer17, 0, wxEXPAND, 5 );

    m_staticText181 = new wxStaticText( m_panel7, wxID_ANY, wxT("Vertical offset"), wxDefaultPosition, wxDefaultSize, 0 );
    m_staticText181->Wrap( -1 );
    bSizer161->Add( m_staticText181, 0, wxALL, 5 );

    m_sliderEzoomVerticalOffset = new wxSlider( m_panel7, wxID_ANY, 50, 0, 100, wxDefaultPosition, wxDefaultSize, wxSL_HORIZONTAL );
    bSizer161->Add( m_sliderEzoomVerticalOffset, 0, wxALL|wxEXPAND, 5 );

    m_staticText19 = new wxStaticText( m_panel7, wxID_ANY, wxT("Horisontal offset"), wxDefaultPosition, wxDefaultSize, 0 );
    m_staticText19->Wrap( -1 );
    bSizer161->Add( m_staticText19, 0, wxALL, 5 );

    m_sliderEzoomHorisontalOffset = new wxSlider( m_panel7, wxID_ANY, 50, 0, 100, wxDefaultPosition, wxDefaultSize, wxSL_HORIZONTAL );
    bSizer161->Add( m_sliderEzoomHorisontalOffset, 0, wxALL|wxEXPAND, 5 );


    m_panel7->SetSizer( bSizer161 );
    m_panel7->Layout();
    bSizer161->Fit( m_panel7 );
    m_choicebook2->AddPage( m_panel7, wxT("E-Zoom"), false );
    m_panel8 = new wxPanel( m_choicebook2, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
    m_choicebook2->AddPage( m_panel8, wxT("Stretch"), false );
    m_panel9 = new wxPanel( m_choicebook2, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
    m_choicebook2->AddPage( m_panel9, wxT("Colorize"), false );
    bSizer9->Add( m_choicebook2, 1, wxEXPAND, 5 );

    wxBoxSizer* bSizer10;
    bSizer10 = new wxBoxSizer( wxVERTICAL );

    wxBoxSizer* bSizer11;
    bSizer11 = new wxBoxSizer( wxHORIZONTAL );

    m_staticText16 = new wxStaticText( this, wxID_ANY, wxT("Horisontal pixels:"), wxDefaultPosition, wxDefaultSize, 0 );
    m_staticText16->Wrap( -1 );
    bSizer11->Add( m_staticText16, 0, wxALL, 5 );

    m_staticTextHorisontalPixels = new wxStaticText( this, wxID_ANY, wxT("0"), wxDefaultPosition, wxDefaultSize, 0 );
    m_staticTextHorisontalPixels->Wrap( -1 );
    bSizer11->Add( m_staticTextHorisontalPixels, 0, wxALL, 5 );


    bSizer10->Add( bSizer11, 1, wxEXPAND, 5 );

    wxBoxSizer* bSizer12;
    bSizer12 = new wxBoxSizer( wxHORIZONTAL );

    m_staticText18 = new wxStaticText( this, wxID_ANY, wxT("Vertical pixels:"), wxDefaultPosition, wxDefaultSize, 0 );
    m_staticText18->Wrap( -1 );
    bSizer12->Add( m_staticText18, 0, wxALL, 5 );

    m_staticTextVerticalPixels = new wxStaticText( this, wxID_ANY, wxT("0"), wxDefaultPosition, wxDefaultSize, 0 );
    m_staticTextVerticalPixels->Wrap( -1 );
    bSizer12->Add( m_staticTextVerticalPixels, 0, wxALL, 5 );


    bSizer10->Add( bSizer12, 1, wxEXPAND, 5 );

    wxBoxSizer* bSizer13;
    bSizer13 = new wxBoxSizer( wxHORIZONTAL );

    m_staticText20 = new wxStaticText( this, wxID_ANY, wxT("Framerate"), wxDefaultPosition, wxDefaultSize, 0 );
    m_staticText20->Wrap( -1 );
    bSizer13->Add( m_staticText20, 0, wxALL, 5 );

    m_staticTextFramerate = new wxStaticText( this, wxID_ANY, wxT("0 Hz"), wxDefaultPosition, wxDefaultSize, 0 );
    m_staticTextFramerate->Wrap( -1 );
    bSizer13->Add( m_staticTextFramerate, 0, wxALL, 5 );


    bSizer10->Add( bSizer13, 1, wxEXPAND, 5 );

    wxBoxSizer* bSizer141;
    bSizer141 = new wxBoxSizer( wxHORIZONTAL );

    m_staticText22 = new wxStaticText( this, wxID_ANY, wxT("Pipeline"), wxDefaultPosition, wxDefaultSize, 0 );
    m_staticText22->Wrap( -1 );
    bSizer141->Add( m_staticText22, 0, wxALL, 5 );

    m_staticTextPipeline = new wxStaticText( this, wxID_ANY, wxT("0 Hz"), wxDefaultPosition, wxDefaultSize, 0 );
    m_staticTextPipeline->Wrap( -1 );
    bSizer141->Add( m_staticTextPipeline, 0, wxALL, 5 );


    bSizer10->Add( bSizer141, 1, wxEXPAND, 5 );

    wxBoxSizer* bSizer15;
    bSizer15 = new wxBoxSizer( wxHORIZONTAL );

    m_staticText24 = new wxStaticText( this, wxID_ANY, wxT("Colour space:"), wxDefaultPosition, wxDefaultSize, 0 );
    m_staticText24->Wrap( -1 );
    bSizer15->Add( m_staticText24, 0, wxALL, 5 );

    m_staticTextColourSpace = new wxStaticText( this, wxID_ANY, wxT("0 : 0"), wxDefaultPosition, wxDefaultSize, 0 );
    m_staticTextColourSpace->Wrap( -1 );
    bSizer15->Add( m_staticTextColourSpace, 0, wxALL, 5 );


    bSizer10->Add( bSizer15, 1, wxEXPAND, 5 );


    bSizer9->Add( bSizer10, 0, wxEXPAND, 5 );


    bSizer1->Add( bSizer9, 1, wxEXPAND, 5 );


    this->SetSizer( bSizer1 );
    this->Layout();

    // Connect Events
    m_buttonRaw->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MyFrame1::m_buttonRawOnButtonClick ), NULL, this );
    m_checkBoxRaw->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( MyFrame1::m_checkBox10OnCheckBox ), NULL, this );
    m_buttonGrayScale->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MyFrame1::m_buttonGrayScaleOnButtonClick ), NULL, this );
    m_checkBoxGrayScale->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( MyFrame1::m_checkBoxGrayScaleOnCheckBox ), NULL, this );
    m_buttonNonU->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MyFrame1::m_buttonNonUOnButtonClick ), NULL, this );
    m_checkBoxNonUniformity->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( MyFrame1::m_checkBoxNonUniformityOnCheckBox ), NULL, this );
    m_buttonFrameAverager->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MyFrame1::m_buttonFrameAveragerOnButtonClick ), NULL, this );
    m_checkBoxFrameAverager->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( MyFrame1::m_checkBoxFrameAveragerOnCheckBox ), NULL, this );
    m_buttonNuc->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MyFrame1::m_buttonNucOnButtonClick ), NULL, this );
    m_checkBoxNuc->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( MyFrame1::m_checkBoxNucOnCheckBox ), NULL, this );
    m_buttonTFilter->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MyFrame1::m_buttonTFilterOnButtonClick ), NULL, this );
    m_checkBoxTFilter->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( MyFrame1::m_checkBoxTFilterOnCheckBox ), NULL, this );
    m_buttonSFilter->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MyFrame1::m_buttonSFilterOnButtonClick ), NULL, this );
    m_checkBoxSFilter->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( MyFrame1::m_checkBoxSFilterOnCheckBox ), NULL, this );
    m_buttonEdgeEnhance->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MyFrame1::m_buttonEdgeEnhanceOnButtonClick ), NULL, this );
    m_checkBoxEdgeEnhance->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( MyFrame1::m_checkBoxEdgeEnhanceOnCheckBox ), NULL, this );
    m_buttonStab->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MyFrame1::m_buttonStabOnButtonClick ), NULL, this );
    m_checkBoxAgc->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( MyFrame1::m_checkBoxAgcOnCheckBox ), NULL, this );
    m_buttonEzoom->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MyFrame1::m_buttonEzoomOnButtonClick ), NULL, this );
    m_checkBoxEzoom->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( MyFrame1::m_checkBoxEzoomOnCheckBox ), NULL, this );
    m_buttonStretch->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MyFrame1::m_buttonStretchOnButtonClick ), NULL, this );
    m_checkBoxStretch->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( MyFrame1::m_checkBoxStretchOnCheckBox ), NULL, this );
    m_buttonColorize->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MyFrame1::m_buttonColorizeOnButtonClick ), NULL, this );
    m_checkBoxColorize->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( MyFrame1::m_checkBoxColorizeOnCheckBox ), NULL, this );
    m_sliderFrameAveragerThreshold->Connect( wxEVT_SCROLL_TOP, wxScrollEventHandler( MyFrame1::m_sliderFrameAveragerThresholdOnScroll ), NULL, this );
    m_sliderFrameAveragerThreshold->Connect( wxEVT_SCROLL_BOTTOM, wxScrollEventHandler( MyFrame1::m_sliderFrameAveragerThresholdOnScroll ), NULL, this );
    m_sliderFrameAveragerThreshold->Connect( wxEVT_SCROLL_LINEUP, wxScrollEventHandler( MyFrame1::m_sliderFrameAveragerThresholdOnScroll ), NULL, this );
    m_sliderFrameAveragerThreshold->Connect( wxEVT_SCROLL_LINEDOWN, wxScrollEventHandler( MyFrame1::m_sliderFrameAveragerThresholdOnScroll ), NULL, this );
    m_sliderFrameAveragerThreshold->Connect( wxEVT_SCROLL_PAGEUP, wxScrollEventHandler( MyFrame1::m_sliderFrameAveragerThresholdOnScroll ), NULL, this );
    m_sliderFrameAveragerThreshold->Connect( wxEVT_SCROLL_PAGEDOWN, wxScrollEventHandler( MyFrame1::m_sliderFrameAveragerThresholdOnScroll ), NULL, this );
    m_sliderFrameAveragerThreshold->Connect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( MyFrame1::m_sliderFrameAveragerThresholdOnScroll ), NULL, this );
    m_sliderFrameAveragerThreshold->Connect( wxEVT_SCROLL_THUMBRELEASE, wxScrollEventHandler( MyFrame1::m_sliderFrameAveragerThresholdOnScroll ), NULL, this );
    m_sliderFrameAveragerThreshold->Connect( wxEVT_SCROLL_CHANGED, wxScrollEventHandler( MyFrame1::m_sliderFrameAveragerThresholdOnScroll ), NULL, this );
    m_buttonSample->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MyFrame1::m_buttonSampleOnButtonClick ), NULL, this );
    m_buttonGaussian->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MyFrame1::m_buttonGaussianOnButtonClick ), NULL, this );
    m_buttonSharpen->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MyFrame1::m_buttonSharpenOnButtonClick ), NULL, this );
    m_buttonUnsharpMask->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MyFrame1::m_buttonUnsharpMaskOnButtonClick ), NULL, this );
    m_buttonStabLock->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MyFrame1::m_buttonStabLockOnButtonClick ), NULL, this );
    m_buttonStabLetGo->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MyFrame1::m_buttonStabLetGoOnButtonClick ), NULL, this );
    m_radioBtnNoZoom->Connect( wxEVT_COMMAND_RADIOBUTTON_SELECTED, wxCommandEventHandler( MyFrame1::m_radioBtnNoZoomOnRadioButton ), NULL, this );
    m_radioBtn2xZoom->Connect( wxEVT_COMMAND_RADIOBUTTON_SELECTED, wxCommandEventHandler( MyFrame1::m_radioBtn2xZoomOnRadioButton ), NULL, this );
    radioBtn4xZoom->Connect( wxEVT_COMMAND_RADIOBUTTON_SELECTED, wxCommandEventHandler( MyFrame1::radioBtn4xZoomOnRadioButton ), NULL, this );
    radioBtn8xZoom->Connect( wxEVT_COMMAND_RADIOBUTTON_SELECTED, wxCommandEventHandler( MyFrame1::radioBtn8xZoomOnRadioButton ), NULL, this );
    m_sliderEzoomVerticalOffset->Connect( wxEVT_SCROLL_TOP, wxScrollEventHandler( MyFrame1::m_sliderEzoomVerticalOffsetOnScroll ), NULL, this );
    m_sliderEzoomVerticalOffset->Connect( wxEVT_SCROLL_BOTTOM, wxScrollEventHandler( MyFrame1::m_sliderEzoomVerticalOffsetOnScroll ), NULL, this );
    m_sliderEzoomVerticalOffset->Connect( wxEVT_SCROLL_LINEUP, wxScrollEventHandler( MyFrame1::m_sliderEzoomVerticalOffsetOnScroll ), NULL, this );
    m_sliderEzoomVerticalOffset->Connect( wxEVT_SCROLL_LINEDOWN, wxScrollEventHandler( MyFrame1::m_sliderEzoomVerticalOffsetOnScroll ), NULL, this );
    m_sliderEzoomVerticalOffset->Connect( wxEVT_SCROLL_PAGEUP, wxScrollEventHandler( MyFrame1::m_sliderEzoomVerticalOffsetOnScroll ), NULL, this );
    m_sliderEzoomVerticalOffset->Connect( wxEVT_SCROLL_PAGEDOWN, wxScrollEventHandler( MyFrame1::m_sliderEzoomVerticalOffsetOnScroll ), NULL, this );
    m_sliderEzoomVerticalOffset->Connect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( MyFrame1::m_sliderEzoomVerticalOffsetOnScroll ), NULL, this );
    m_sliderEzoomVerticalOffset->Connect( wxEVT_SCROLL_THUMBRELEASE, wxScrollEventHandler( MyFrame1::m_sliderEzoomVerticalOffsetOnScroll ), NULL, this );
    m_sliderEzoomVerticalOffset->Connect( wxEVT_SCROLL_CHANGED, wxScrollEventHandler( MyFrame1::m_sliderEzoomVerticalOffsetOnScroll ), NULL, this );
    m_sliderEzoomHorisontalOffset->Connect( wxEVT_SCROLL_TOP, wxScrollEventHandler( MyFrame1::m_sliderEzoomHorisontalOffsetOnScroll ), NULL, this );
    m_sliderEzoomHorisontalOffset->Connect( wxEVT_SCROLL_BOTTOM, wxScrollEventHandler( MyFrame1::m_sliderEzoomHorisontalOffsetOnScroll ), NULL, this );
    m_sliderEzoomHorisontalOffset->Connect( wxEVT_SCROLL_LINEUP, wxScrollEventHandler( MyFrame1::m_sliderEzoomHorisontalOffsetOnScroll ), NULL, this );
    m_sliderEzoomHorisontalOffset->Connect( wxEVT_SCROLL_LINEDOWN, wxScrollEventHandler( MyFrame1::m_sliderEzoomHorisontalOffsetOnScroll ), NULL, this );
    m_sliderEzoomHorisontalOffset->Connect( wxEVT_SCROLL_PAGEUP, wxScrollEventHandler( MyFrame1::m_sliderEzoomHorisontalOffsetOnScroll ), NULL, this );
    m_sliderEzoomHorisontalOffset->Connect( wxEVT_SCROLL_PAGEDOWN, wxScrollEventHandler( MyFrame1::m_sliderEzoomHorisontalOffsetOnScroll ), NULL, this );
    m_sliderEzoomHorisontalOffset->Connect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( MyFrame1::m_sliderEzoomHorisontalOffsetOnScroll ), NULL, this );
    m_sliderEzoomHorisontalOffset->Connect( wxEVT_SCROLL_THUMBRELEASE, wxScrollEventHandler( MyFrame1::m_sliderEzoomHorisontalOffsetOnScroll ), NULL, this );
    m_sliderEzoomHorisontalOffset->Connect( wxEVT_SCROLL_CHANGED, wxScrollEventHandler( MyFrame1::m_sliderEzoomHorisontalOffsetOnScroll ), NULL, this );
}

MyFrame1::~MyFrame1()
{
	/* -------------- Generated code (wxFormBuilder) ----------------------------------------------------------------*/
    // Disconnect Events
    m_buttonRaw->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MyFrame1::m_buttonRawOnButtonClick ), NULL, this );
    m_checkBoxRaw->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( MyFrame1::m_checkBox10OnCheckBox ), NULL, this );
    m_buttonGrayScale->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MyFrame1::m_buttonGrayScaleOnButtonClick ), NULL, this );
    m_checkBoxGrayScale->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( MyFrame1::m_checkBoxGrayScaleOnCheckBox ), NULL, this );
    m_buttonNonU->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MyFrame1::m_buttonNonUOnButtonClick ), NULL, this );
    m_checkBoxNonUniformity->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( MyFrame1::m_checkBoxNonUniformityOnCheckBox ), NULL, this );
    m_buttonFrameAverager->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MyFrame1::m_buttonFrameAveragerOnButtonClick ), NULL, this );
    m_checkBoxFrameAverager->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( MyFrame1::m_checkBoxFrameAveragerOnCheckBox ), NULL, this );
    m_buttonNuc->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MyFrame1::m_buttonNucOnButtonClick ), NULL, this );
    m_checkBoxNuc->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( MyFrame1::m_checkBoxNucOnCheckBox ), NULL, this );
    m_buttonTFilter->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MyFrame1::m_buttonTFilterOnButtonClick ), NULL, this );
    m_checkBoxTFilter->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( MyFrame1::m_checkBoxTFilterOnCheckBox ), NULL, this );
    m_buttonSFilter->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MyFrame1::m_buttonSFilterOnButtonClick ), NULL, this );
    m_checkBoxSFilter->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( MyFrame1::m_checkBoxSFilterOnCheckBox ), NULL, this );
    m_buttonEdgeEnhance->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MyFrame1::m_buttonEdgeEnhanceOnButtonClick ), NULL, this );
    m_checkBoxEdgeEnhance->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( MyFrame1::m_checkBoxEdgeEnhanceOnCheckBox ), NULL, this );
    m_buttonStab->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MyFrame1::m_buttonStabOnButtonClick ), NULL, this );
    m_checkBoxAgc->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( MyFrame1::m_checkBoxAgcOnCheckBox ), NULL, this );
    m_buttonEzoom->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MyFrame1::m_buttonEzoomOnButtonClick ), NULL, this );
    m_checkBoxEzoom->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( MyFrame1::m_checkBoxEzoomOnCheckBox ), NULL, this );
    m_buttonStretch->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MyFrame1::m_buttonStretchOnButtonClick ), NULL, this );
    m_checkBoxStretch->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( MyFrame1::m_checkBoxStretchOnCheckBox ), NULL, this );
    m_buttonColorize->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MyFrame1::m_buttonColorizeOnButtonClick ), NULL, this );
    m_checkBoxColorize->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( MyFrame1::m_checkBoxColorizeOnCheckBox ), NULL, this );
    m_sliderFrameAveragerThreshold->Disconnect( wxEVT_SCROLL_TOP, wxScrollEventHandler( MyFrame1::m_sliderFrameAveragerThresholdOnScroll ), NULL, this );
    m_sliderFrameAveragerThreshold->Disconnect( wxEVT_SCROLL_BOTTOM, wxScrollEventHandler( MyFrame1::m_sliderFrameAveragerThresholdOnScroll ), NULL, this );
    m_sliderFrameAveragerThreshold->Disconnect( wxEVT_SCROLL_LINEUP, wxScrollEventHandler( MyFrame1::m_sliderFrameAveragerThresholdOnScroll ), NULL, this );
    m_sliderFrameAveragerThreshold->Disconnect( wxEVT_SCROLL_LINEDOWN, wxScrollEventHandler( MyFrame1::m_sliderFrameAveragerThresholdOnScroll ), NULL, this );
    m_sliderFrameAveragerThreshold->Disconnect( wxEVT_SCROLL_PAGEUP, wxScrollEventHandler( MyFrame1::m_sliderFrameAveragerThresholdOnScroll ), NULL, this );
    m_sliderFrameAveragerThreshold->Disconnect( wxEVT_SCROLL_PAGEDOWN, wxScrollEventHandler( MyFrame1::m_sliderFrameAveragerThresholdOnScroll ), NULL, this );
    m_sliderFrameAveragerThreshold->Disconnect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( MyFrame1::m_sliderFrameAveragerThresholdOnScroll ), NULL, this );
    m_sliderFrameAveragerThreshold->Disconnect( wxEVT_SCROLL_THUMBRELEASE, wxScrollEventHandler( MyFrame1::m_sliderFrameAveragerThresholdOnScroll ), NULL, this );
    m_sliderFrameAveragerThreshold->Disconnect( wxEVT_SCROLL_CHANGED, wxScrollEventHandler( MyFrame1::m_sliderFrameAveragerThresholdOnScroll ), NULL, this );
    m_buttonSample->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MyFrame1::m_buttonSampleOnButtonClick ), NULL, this );
    m_buttonGaussian->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MyFrame1::m_buttonGaussianOnButtonClick ), NULL, this );
    m_buttonSharpen->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MyFrame1::m_buttonSharpenOnButtonClick ), NULL, this );
    m_buttonUnsharpMask->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MyFrame1::m_buttonUnsharpMaskOnButtonClick ), NULL, this );
    m_buttonStabLock->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MyFrame1::m_buttonStabLockOnButtonClick ), NULL, this );
    m_buttonStabLetGo->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MyFrame1::m_buttonStabLetGoOnButtonClick ), NULL, this );
    m_radioBtnNoZoom->Disconnect( wxEVT_COMMAND_RADIOBUTTON_SELECTED, wxCommandEventHandler( MyFrame1::m_radioBtnNoZoomOnRadioButton ), NULL, this );
    m_radioBtn2xZoom->Disconnect( wxEVT_COMMAND_RADIOBUTTON_SELECTED, wxCommandEventHandler( MyFrame1::m_radioBtn2xZoomOnRadioButton ), NULL, this );
    radioBtn4xZoom->Disconnect( wxEVT_COMMAND_RADIOBUTTON_SELECTED, wxCommandEventHandler( MyFrame1::radioBtn4xZoomOnRadioButton ), NULL, this );
    radioBtn8xZoom->Disconnect( wxEVT_COMMAND_RADIOBUTTON_SELECTED, wxCommandEventHandler( MyFrame1::radioBtn8xZoomOnRadioButton ), NULL, this );
    m_sliderEzoomVerticalOffset->Disconnect( wxEVT_SCROLL_TOP, wxScrollEventHandler( MyFrame1::m_sliderEzoomVerticalOffsetOnScroll ), NULL, this );
    m_sliderEzoomVerticalOffset->Disconnect( wxEVT_SCROLL_BOTTOM, wxScrollEventHandler( MyFrame1::m_sliderEzoomVerticalOffsetOnScroll ), NULL, this );
    m_sliderEzoomVerticalOffset->Disconnect( wxEVT_SCROLL_LINEUP, wxScrollEventHandler( MyFrame1::m_sliderEzoomVerticalOffsetOnScroll ), NULL, this );
    m_sliderEzoomVerticalOffset->Disconnect( wxEVT_SCROLL_LINEDOWN, wxScrollEventHandler( MyFrame1::m_sliderEzoomVerticalOffsetOnScroll ), NULL, this );
    m_sliderEzoomVerticalOffset->Disconnect( wxEVT_SCROLL_PAGEUP, wxScrollEventHandler( MyFrame1::m_sliderEzoomVerticalOffsetOnScroll ), NULL, this );
    m_sliderEzoomVerticalOffset->Disconnect( wxEVT_SCROLL_PAGEDOWN, wxScrollEventHandler( MyFrame1::m_sliderEzoomVerticalOffsetOnScroll ), NULL, this );
    m_sliderEzoomVerticalOffset->Disconnect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( MyFrame1::m_sliderEzoomVerticalOffsetOnScroll ), NULL, this );
    m_sliderEzoomVerticalOffset->Disconnect( wxEVT_SCROLL_THUMBRELEASE, wxScrollEventHandler( MyFrame1::m_sliderEzoomVerticalOffsetOnScroll ), NULL, this );
    m_sliderEzoomVerticalOffset->Disconnect( wxEVT_SCROLL_CHANGED, wxScrollEventHandler( MyFrame1::m_sliderEzoomVerticalOffsetOnScroll ), NULL, this );
    m_sliderEzoomHorisontalOffset->Disconnect( wxEVT_SCROLL_TOP, wxScrollEventHandler( MyFrame1::m_sliderEzoomHorisontalOffsetOnScroll ), NULL, this );
    m_sliderEzoomHorisontalOffset->Disconnect( wxEVT_SCROLL_BOTTOM, wxScrollEventHandler( MyFrame1::m_sliderEzoomHorisontalOffsetOnScroll ), NULL, this );
    m_sliderEzoomHorisontalOffset->Disconnect( wxEVT_SCROLL_LINEUP, wxScrollEventHandler( MyFrame1::m_sliderEzoomHorisontalOffsetOnScroll ), NULL, this );
    m_sliderEzoomHorisontalOffset->Disconnect( wxEVT_SCROLL_LINEDOWN, wxScrollEventHandler( MyFrame1::m_sliderEzoomHorisontalOffsetOnScroll ), NULL, this );
    m_sliderEzoomHorisontalOffset->Disconnect( wxEVT_SCROLL_PAGEUP, wxScrollEventHandler( MyFrame1::m_sliderEzoomHorisontalOffsetOnScroll ), NULL, this );
    m_sliderEzoomHorisontalOffset->Disconnect( wxEVT_SCROLL_PAGEDOWN, wxScrollEventHandler( MyFrame1::m_sliderEzoomHorisontalOffsetOnScroll ), NULL, this );
    m_sliderEzoomHorisontalOffset->Disconnect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( MyFrame1::m_sliderEzoomHorisontalOffsetOnScroll ), NULL, this );
    m_sliderEzoomHorisontalOffset->Disconnect( wxEVT_SCROLL_THUMBRELEASE, wxScrollEventHandler( MyFrame1::m_sliderEzoomHorisontalOffsetOnScroll ), NULL, this );
    m_sliderEzoomHorisontalOffset->Disconnect( wxEVT_SCROLL_CHANGED, wxScrollEventHandler( MyFrame1::m_sliderEzoomHorisontalOffsetOnScroll ), NULL, this );
    /* -------------- Generated code (wxFormBuilder) ----------------------------------------------------------------*/
}



// event handlers
void MyFrame1::OnQueueTimer(wxTimerEvent& event)
{
    FromTiDspThread tiDspMsg;
    if(!(queues->fromTiDspToGui.empty()))
    {
        queues->fromTiDspToGui.pop(tiDspMsg);
        m_staticTextPipeline->SetLabel(wxString::Format(wxT("%i %s"), tiDspMsg.info.pipeLineFrameRate, " Hz"));
    }

    FromTiCameraThread tiCameraMsg;
    if (!(queues->fromTiCameraToGui.empty()))
    {
        queues->fromTiCameraToGui.pop(tiCameraMsg);
        m_staticTextFramerate->SetLabel(wxString::Format(wxT("%i %s"), tiCameraMsg.info.frameRate, " Hz"));
        m_staticTextHorisontalPixels->SetLabel(wxString::Format(wxT("%i"), tiCameraMsg.info.horisontalPixels));
        m_staticTextVerticalPixels->SetLabel(wxString::Format(wxT("%i"), tiCameraMsg.info.verticalPixels));
        m_staticTextColourSpace->SetLabel(wxString::Format(wxT("%i : %i"), tiCameraMsg.info.colourSpace, tiCameraMsg.info.bitDepth));
    }
    boost::this_thread::yield();
}


void MyFrame1::OnQuit(wxCommandEvent& WXUNUSED(event))
{
    // true is to force the frame to close
    exit(0);
}

void MyFrame1::OnAbout(wxCommandEvent& WXUNUSED(event))
{
    wxMessageBox(wxString::Format
                 (
                    "Welcome to %s!\n"
                    "\n"
                    "This is the minimal wxWidgets sample\n"
                    "running under %s.",
                    wxVERSION_STRING,
                    wxGetOsDescription()
                 ),
                 "About wxWidgets minimal sample",
                 wxOK | wxICON_INFORMATION,
                 this);
}

void MyFrame1::m_buttonRawOnButtonClick( wxCommandEvent& event )
{
    tiDspParams.outputSelect = OutputSelect::Raw;
    queues->fromGuiToTiDsp.push(ToTiDspThread{
            .reason = ToTiDspReason::OutputSelectChange,
            .params = tiDspParams
    });
}

void MyFrame1::m_buttonGrayScaleOnButtonClick( wxCommandEvent& event )
{
    tiDspParams.outputSelect = OutputSelect::GrayScale;
    queues->fromGuiToTiDsp.push(ToTiDspThread{
            .reason = ToTiDspReason::OutputSelectChange,
            .params = tiDspParams
    });
}

void MyFrame1::m_checkBoxGrayScaleOnCheckBox( wxCommandEvent& event )
{

}

void MyFrame1::m_buttonNonUOnButtonClick( wxCommandEvent& event )
{
    tiDspParams.outputSelect = OutputSelect::NonUniformity;
    queues->fromGuiToTiDsp.push(ToTiDspThread{
            .reason = ToTiDspReason::OutputSelectChange,
            .params = tiDspParams
    });
}

void MyFrame1::m_checkBoxNonUniformityOnCheckBox( wxCommandEvent& event )
{

}

void MyFrame1::m_buttonFrameAveragerOnButtonClick( wxCommandEvent& event )
{
    tiDspParams.outputSelect = OutputSelect::FrameAverage;
    queues->fromGuiToTiDsp.push(ToTiDspThread{
            .reason = ToTiDspReason::OutputSelectChange,
            .params = tiDspParams
    });
}

void MyFrame1::m_checkBoxFrameAveragerOnCheckBox( wxCommandEvent& event )
{
    if (event.IsChecked())
    {
        tiDspParams.frameAverageOn = true;
    }
    else
    {
        tiDspParams.frameAverageOn = false;
    }
    queues->fromGuiToTiDsp.push(ToTiDspThread{
            .reason = ToTiDspReason::PipelineStageActiveChange,
            .params = tiDspParams
    });
}

void MyFrame1::m_buttonNucOnButtonClick( wxCommandEvent& event )
{
    tiDspParams.outputSelect = OutputSelect::Nuc;
    queues->fromGuiToTiDsp.push(ToTiDspThread{
            .reason = ToTiDspReason::OutputSelectChange,
            .params = tiDspParams
    });
}

void MyFrame1::m_checkBoxNucOnCheckBox( wxCommandEvent& event )
{
    if (event.IsChecked())
    {
        tiDspParams.nucOn = true;
    }
    else
    {
        tiDspParams.nucOn = false;
    }
    queues->fromGuiToTiDsp.push(ToTiDspThread{
            .reason = ToTiDspReason::NucChange,
            .params = tiDspParams
    });
}

void MyFrame1::m_buttonTFilterOnButtonClick( wxCommandEvent& event )
{
    tiDspParams.outputSelect = OutputSelect::TemporalFilter;
    queues->fromGuiToTiDsp.push(ToTiDspThread{
            .reason = ToTiDspReason::OutputSelectChange,
            .params = tiDspParams
    });
}

void MyFrame1::m_checkBoxTFilterOnCheckBox( wxCommandEvent& event )
{
    if (event.IsChecked())
    {
        tiDspParams.temporalFilterOn = true;
    }
    else
    {
        tiDspParams.temporalFilterOn = false;
    }
    queues->fromGuiToTiDsp.push(ToTiDspThread{
            .reason = ToTiDspReason::PipelineStageActiveChange,
            .params = tiDspParams
    });
}

void MyFrame1::m_buttonSFilterOnButtonClick( wxCommandEvent& event )
{
    tiDspParams.outputSelect = OutputSelect::SpatialFilter;
    queues->fromGuiToTiDsp.push(ToTiDspThread{
            .reason = ToTiDspReason::OutputSelectChange,
            .params = tiDspParams
    });
}

void MyFrame1::m_checkBoxSFilterOnCheckBox( wxCommandEvent& event )
{
    if (event.IsChecked())
    {
        tiDspParams.spatialFilterOn = true;
    }
    else
    {
        tiDspParams.spatialFilterOn = false;
    }
    queues->fromGuiToTiDsp.push(ToTiDspThread{
            .reason = ToTiDspReason::PipelineStageActiveChange,
            .params = tiDspParams
    });
}

void MyFrame1::m_buttonEdgeEnhanceOnButtonClick( wxCommandEvent& event )
{
    tiDspParams.outputSelect = OutputSelect::EdgeEnhance;
    queues->fromGuiToTiDsp.push(ToTiDspThread{
            .reason = ToTiDspReason::OutputSelectChange,
            .params = tiDspParams
    });
}

void MyFrame1::m_checkBoxEdgeEnhanceOnCheckBox( wxCommandEvent& event )
{
	static EdgeEnhanceType previousType = EdgeEnhanceType::Gaussian;

	if (event.IsChecked())
	{
        tiDspParams.edgeEnhanceOn = true;
	}
	else
	{
		tiDspParams.edgeEnhanceOn = false;
	}
    queues->fromGuiToTiDsp.push(ToTiDspThread{
            .reason = ToTiDspReason::PipelineStageActiveChange,
            .params = tiDspParams
    });
}

void MyFrame1::m_buttonStabOnButtonClick( wxCommandEvent& event )
{
    tiDspParams.outputSelect = OutputSelect::Stab;
    queues->fromGuiToTiDsp.push(ToTiDspThread{
            .reason = ToTiDspReason::OutputSelectChange,
            .params = tiDspParams
    });
}

void MyFrame1::m_buttonStabLockOnButtonClick(wxCommandEvent &event)
{
    tiDspParams.stabLockOn = true;
    queues->fromGuiToTiDsp.push(ToTiDspThread{
            .reason = ToTiDspReason::StabLock,
            .params = tiDspParams
    });
}

void MyFrame1::m_buttonStabLetGoOnButtonClick(wxCommandEvent &event)
{
    tiDspParams.stabLockOn = false;
    queues->fromGuiToTiDsp.push(ToTiDspThread{
            .reason = ToTiDspReason::StabLock,
            .params = tiDspParams
    });
}

void MyFrame1::m_checkBoxAgcOnCheckBox( wxCommandEvent& event )
{

}

void MyFrame1::m_buttonEzoomOnButtonClick( wxCommandEvent& event )
{
    tiDspParams.outputSelect = OutputSelect::Ezoom;
    queues->fromGuiToTiDsp.push(ToTiDspThread{
            .reason = ToTiDspReason::OutputSelectChange,
            .params = tiDspParams
    });
}

void MyFrame1::m_checkBoxEzoomOnCheckBox( wxCommandEvent& event )
{
    if (event.IsChecked())
    {
        tiDspParams.eZoomOn = true;
    }
    else
    {
        tiDspParams.eZoomOn = false;
    }
    queues->fromGuiToTiDsp.push(ToTiDspThread{
            .reason = ToTiDspReason::PipelineStageActiveChange,
            .params = tiDspParams
    });
}

void MyFrame1::m_buttonStretchOnButtonClick( wxCommandEvent& event )
{
    tiDspParams.outputSelect = OutputSelect::HistogramStretch;
    queues->fromGuiToTiDsp.push(ToTiDspThread{
            .reason = ToTiDspReason::OutputSelectChange,
            .params = tiDspParams
    });
}

void MyFrame1::m_checkBoxStretchOnCheckBox( wxCommandEvent& event )
{
    if (event.IsChecked())
    {
        tiDspParams.histogramStretchOn = true;
    }
    else
    {
        tiDspParams.histogramStretchOn = false;
    }
    queues->fromGuiToTiDsp.push(ToTiDspThread{
            .reason = ToTiDspReason::PipelineStageActiveChange,
            .params = tiDspParams
    });
}

void MyFrame1::m_buttonColorizeOnButtonClick( wxCommandEvent& event )
{
    tiDspParams.outputSelect = OutputSelect::Colorize;
    queues->fromGuiToTiDsp.push(ToTiDspThread{
            .reason = ToTiDspReason::OutputSelectChange,
            .params = tiDspParams
    });
}

void MyFrame1::m_checkBoxColorizeOnCheckBox( wxCommandEvent& event )
{

}

void MyFrame1::m_sliderFrameAveragerThresholdOnScroll( wxScrollEvent& event )
{
    tiDspParams.frameAveragerThreshold = event.GetPosition();
    queues->fromGuiToTiDsp.push(ToTiDspThread{
            .reason = ToTiDspReason::FrameAveragerChange,
            .params = tiDspParams
    });
}

void MyFrame1::m_buttonGaussianOnButtonClick(wxCommandEvent& event)
{
    tiDspParams.edgeEnhanceType = EdgeEnhanceType::Gaussian;
    m_panelGaussian->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_GRAYTEXT ) );
    m_panelSharpen->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_BACKGROUND ) );
    m_panelUnsharpMask->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_BACKGROUND ) );
    queues->fromGuiToTiDsp.push(ToTiDspThread{
            .reason = ToTiDspReason::EdgeEnhanceChange,
            .params = tiDspParams
    });
}

void MyFrame1::m_buttonSharpenOnButtonClick(wxCommandEvent& event)
{
    tiDspParams.edgeEnhanceType = EdgeEnhanceType::Sharpen;
    m_panelGaussian->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_BACKGROUND ) );
    m_panelSharpen->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_GRAYTEXT ) );
    m_panelUnsharpMask->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_BACKGROUND ) );
    queues->fromGuiToTiDsp.push(ToTiDspThread{
            .reason = ToTiDspReason::EdgeEnhanceChange,
            .params = tiDspParams
    });
}

void MyFrame1::m_buttonUnsharpMaskOnButtonClick(wxCommandEvent& event)
{
    tiDspParams.edgeEnhanceType = EdgeEnhanceType::Unsharp_mask;
    m_panelGaussian->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_BACKGROUND ) );
    m_panelSharpen->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_BACKGROUND ) );
    m_panelUnsharpMask->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_GRAYTEXT ) );
    queues->fromGuiToTiDsp.push(ToTiDspThread{
            .reason = ToTiDspReason::EdgeEnhanceChange,
            .params = tiDspParams
    });
}

void MyFrame1::m_radioBtnNoZoomOnRadioButton( wxCommandEvent& event )
{
    tiDspParams.ezoom = Ezoom::NoZoom;
    queues->fromGuiToTiDsp.push(ToTiDspThread{
            .reason = ToTiDspReason::EzoomChange,
            .params = tiDspParams
    });
}

void MyFrame1::m_radioBtn2xZoomOnRadioButton( wxCommandEvent& event )
{
    tiDspParams.ezoom = Ezoom::x2;
    queues->fromGuiToTiDsp.push(ToTiDspThread{
            .reason = ToTiDspReason::EzoomChange,
            .params = tiDspParams
    });
}

void MyFrame1::radioBtn4xZoomOnRadioButton( wxCommandEvent& event )
{
    tiDspParams.ezoom = Ezoom::x4;
    queues->fromGuiToTiDsp.push(ToTiDspThread{
            .reason = ToTiDspReason::EzoomChange,
            .params = tiDspParams
    });
}

void MyFrame1::radioBtn8xZoomOnRadioButton( wxCommandEvent& event )
{
    tiDspParams.ezoom = Ezoom::x8;
    queues->fromGuiToTiDsp.push(ToTiDspThread{
            .reason = ToTiDspReason::EzoomChange,
            .params = tiDspParams
    });
}

void MyFrame1::m_sliderEzoomVerticalOffsetOnScroll( wxScrollEvent& event )
{
    tiDspParams.verticalOffset = event.GetPosition();
    queues->fromGuiToTiDsp.push(ToTiDspThread{
            .reason = ToTiDspReason::EzoomChange,
            .params = tiDspParams
    });
}

void MyFrame1::m_sliderEzoomHorisontalOffsetOnScroll( wxScrollEvent& event )
{
    tiDspParams.horisontalOffset = event.GetPosition();
    queues->fromGuiToTiDsp.push(ToTiDspThread{
            .reason = ToTiDspReason::EzoomChange,
            .params = tiDspParams
    });
}

void MyFrame1::m_buttonSampleOnButtonClick(wxCommandEvent &event)
{
    queues->fromGuiToTiDsp.push(ToTiDspThread{
            .reason = ToTiDspReason::NucSample,
            .params = tiDspParams
    });
}

void MyFrame1::m_checkBox10OnCheckBox(wxCommandEvent &event) {

}
