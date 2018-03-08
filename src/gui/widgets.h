/*
 * widgets.h
 *
 *  Created on: 13 Mar 2017
 *      Author: kc
 */

#pragma once

#include <wx/string.h>
#include <wx/stattext.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/button.h>
#include <wx/checkbox.h>
#include <wx/sizer.h>
#include <wx/panel.h>
#include <wx/slider.h>
#include <wx/choicebk.h>
#include <wx/frame.h>
#include "widgets.h"
#include "../util/threads.h"

// For compilers that support precompilation, includes "wx/wx.h".
#include "wx/wxprec.h"

#ifdef __BORLANDC__
    #pragma hdrstop
#endif

// for all others, include the necessary headers (this file is usually all you
// need because it includes almost all "standard" wxWidgets headers)
#ifndef WX_PRECOMP
    #include "wx/wx.h"
#endif

// ----------------------------------------------------------------------------
// resources
// ----------------------------------------------------------------------------

// the application icon (under Windows it is in resources and even
// though we could still include the XPM here it would be unused)
#ifndef wxHAS_IMAGES_IN_RESOURCES
    #include "sample.xpm"
#endif

// Define a new frame type: this is going to be our main frame
class MyFrame1 : public wxFrame
{
public:
    // ctor(s)
    MyFrame1(const wxString& title);
    ~MyFrame1();
    void InitQueues(Queues* qs) { queues = qs; };
    wxTimer* qTimer;
    // event handlers (these functions should _not_ be virtual)
    void OnQuit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);
    void OnQueueTimer(wxTimerEvent& event);

private:
    Queues* queues;
    wxTimer* queueTimer;
    // any class wishing to process wxWidgets events must use this macro
    wxDECLARE_EVENT_TABLE();

protected:
    wxStaticText* m_staticText1;
    wxStaticText* m_staticText2;
    wxButton* m_buttonRaw;
    wxCheckBox* m_checkBoxRaw;
    wxButton* m_buttonGrayScale;
    wxCheckBox* m_checkBoxGrayScale;
    wxButton* m_buttonNonU;
    wxCheckBox* m_checkBoxNonUniformity;
    wxButton* m_buttonFrameAverager;
    wxCheckBox* m_checkBoxFrameAverager;
    wxButton* m_buttonNuc;
    wxCheckBox* m_checkBoxNuc;
    wxButton* m_buttonTFilter;
    wxCheckBox* m_checkBoxTFilter;
    wxButton* m_buttonSFilter;
    wxCheckBox* m_checkBoxSFilter;
    wxButton* m_buttonEdgeEnhance;
    wxCheckBox* m_checkBoxEdgeEnhance;
    wxButton* m_buttonStab;
    wxCheckBox* m_checkBoxAgc;
    wxButton* m_buttonEzoom;
    wxCheckBox* m_checkBoxEzoom;
    wxButton* m_buttonStretch;
    wxCheckBox* m_checkBoxStretch;
    wxButton* m_buttonColorize;
    wxCheckBox* m_checkBoxColorize;
    wxChoicebook* m_choicebook2;
    wxPanel* m_panel1;
    wxStaticText* m_staticText26;
    wxSlider* m_sliderFrameAveragerThreshold;
    wxPanel* m_panel2;
    wxButton* m_buttonSample;
    wxPanel* m_panel3;
    wxPanel* m_panel4;
    wxPanel* m_panel5;
    wxPanel* m_panelGaussian;
    wxButton* m_buttonGaussian;
    wxPanel* m_panelSharpen;
    wxButton* m_buttonSharpen;
    wxPanel* m_panelUnsharpMask;
    wxButton* m_buttonUnsharpMask;
    wxPanel* m_panel6;
    wxButton* m_buttonStabLock;
    wxButton* m_buttonStabLetGo;
    wxPanel* m_panel7;
    wxRadioButton* m_radioBtnNoZoom;
    wxRadioButton* m_radioBtn2xZoom;
    wxRadioButton* radioBtn4xZoom;
    wxRadioButton* radioBtn8xZoom;
    wxStaticText* m_staticText181;
    wxSlider* m_sliderEzoomVerticalOffset;
    wxStaticText* m_staticText19;
    wxSlider* m_sliderEzoomHorisontalOffset;
    wxPanel* m_panel8;
    wxPanel* m_panel9;
    wxStaticText* m_staticText16;
    wxStaticText* m_staticTextHorisontalPixels;
    wxStaticText* m_staticText18;
    wxStaticText* m_staticTextVerticalPixels;
    wxStaticText* m_staticText20;
    wxStaticText* m_staticTextFramerate;
    wxStaticText* m_staticText22;
    wxStaticText* m_staticTextPipeline;
    wxStaticText* m_staticText24;
    wxStaticText* m_staticTextColourSpace;

    // Virtual event handlers, overide them in your derived class
    virtual void m_buttonRawOnButtonClick( wxCommandEvent& event );
    virtual void m_checkBox10OnCheckBox( wxCommandEvent& event );
    virtual void m_buttonGrayScaleOnButtonClick( wxCommandEvent& event );
    virtual void m_checkBoxGrayScaleOnCheckBox( wxCommandEvent& event );
    virtual void m_buttonNonUOnButtonClick( wxCommandEvent& event );
    virtual void m_checkBoxNonUniformityOnCheckBox( wxCommandEvent& event );
    virtual void m_buttonFrameAveragerOnButtonClick( wxCommandEvent& event );
    virtual void m_checkBoxFrameAveragerOnCheckBox( wxCommandEvent& event );
    virtual void m_buttonNucOnButtonClick( wxCommandEvent& event );
    virtual void m_checkBoxNucOnCheckBox( wxCommandEvent& event );
    virtual void m_buttonTFilterOnButtonClick( wxCommandEvent& event );
    virtual void m_checkBoxTFilterOnCheckBox( wxCommandEvent& event );
    virtual void m_buttonSFilterOnButtonClick( wxCommandEvent& event );
    virtual void m_checkBoxSFilterOnCheckBox( wxCommandEvent& event );
    virtual void m_buttonEdgeEnhanceOnButtonClick( wxCommandEvent& event );
    virtual void m_checkBoxEdgeEnhanceOnCheckBox( wxCommandEvent& event );
    virtual void m_buttonStabOnButtonClick( wxCommandEvent& event );
    virtual void m_checkBoxAgcOnCheckBox( wxCommandEvent& event );
    virtual void m_buttonEzoomOnButtonClick( wxCommandEvent& event );
    virtual void m_checkBoxEzoomOnCheckBox( wxCommandEvent& event );
    virtual void m_buttonStretchOnButtonClick( wxCommandEvent& event );
    virtual void m_checkBoxStretchOnCheckBox( wxCommandEvent& event );
    virtual void m_buttonColorizeOnButtonClick( wxCommandEvent& event );
    virtual void m_checkBoxColorizeOnCheckBox( wxCommandEvent& event );
    virtual void m_sliderFrameAveragerThresholdOnScroll( wxScrollEvent& event );
    virtual void m_buttonSampleOnButtonClick( wxCommandEvent& event );
    virtual void m_buttonGaussianOnButtonClick( wxCommandEvent& event );
    virtual void m_buttonSharpenOnButtonClick( wxCommandEvent& event );
    virtual void m_buttonUnsharpMaskOnButtonClick( wxCommandEvent& event );
    virtual void m_buttonStabLockOnButtonClick( wxCommandEvent& event );
    virtual void m_buttonStabLetGoOnButtonClick( wxCommandEvent& event );
    virtual void m_radioBtnNoZoomOnRadioButton( wxCommandEvent& event );
    virtual void m_radioBtn2xZoomOnRadioButton( wxCommandEvent& event );
    virtual void radioBtn4xZoomOnRadioButton( wxCommandEvent& event );
    virtual void radioBtn8xZoomOnRadioButton( wxCommandEvent& event );
    virtual void m_sliderEzoomVerticalOffsetOnScroll( wxScrollEvent& event );
    virtual void m_sliderEzoomHorisontalOffsetOnScroll( wxScrollEvent& event );
/* -------------- Generated code (wxFormBuilder) ----------------------------------------------------------------*/
};

// Define a new application type, each program should derive a class from wxApp
class MyApp : public wxApp
{

public:
    // override base class virtuals
    // ----------------------------

    // this one is called on application startup and is a good place for the app
    // initialization (doing it here and not in the ctor allows to have an error
    // return: if OnInit() returns false, the application terminates)
    virtual bool OnInit();// wxOVERRIDE;
    void InitQueues(Queues* qs);
private:
    Queues* queues;
    MyFrame1 *myFrame;
};
