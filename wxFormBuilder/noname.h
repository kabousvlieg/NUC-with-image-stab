///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Sep 20 2017)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __NONAME_H__
#define __NONAME_H__

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/string.h>
#include <wx/stattext.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/button.h>
#include <wx/checkbox.h>
#include <wx/sizer.h>
#include <wx/slider.h>
#include <wx/panel.h>
#include <wx/radiobut.h>
#include <wx/choicebk.h>
#include <wx/frame.h>

///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// Class MyFrame1
///////////////////////////////////////////////////////////////////////////////
class MyFrame1 : public wxFrame 
{
	private:
	
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
		wxCheckBox* m_checkBoxStab;
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
		virtual void m_buttonRawOnButtonClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void m_checkBox10OnCheckBox( wxCommandEvent& event ) { event.Skip(); }
		virtual void m_buttonGrayScaleOnButtonClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void m_checkBoxGrayScaleOnCheckBox( wxCommandEvent& event ) { event.Skip(); }
		virtual void m_buttonNonUOnButtonClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void m_checkBoxNonUniformityOnCheckBox( wxCommandEvent& event ) { event.Skip(); }
		virtual void m_buttonFrameAveragerOnButtonClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void m_checkBoxFrameAveragerOnCheckBox( wxCommandEvent& event ) { event.Skip(); }
		virtual void m_buttonNucOnButtonClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void m_checkBoxNucOnCheckBox( wxCommandEvent& event ) { event.Skip(); }
		virtual void m_buttonTFilterOnButtonClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void m_checkBoxTFilterOnCheckBox( wxCommandEvent& event ) { event.Skip(); }
		virtual void m_buttonSFilterOnButtonClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void m_checkBoxSFilterOnCheckBox( wxCommandEvent& event ) { event.Skip(); }
		virtual void m_buttonEdgeEnhanceOnButtonClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void m_checkBoxEdgeEnhanceOnCheckBox( wxCommandEvent& event ) { event.Skip(); }
		virtual void m_buttonStabOnButtonClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void m_checkBoxStabOnCheckBox( wxCommandEvent& event ) { event.Skip(); }
		virtual void m_buttonEzoomOnButtonClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void m_checkBoxEzoomOnCheckBox( wxCommandEvent& event ) { event.Skip(); }
		virtual void m_buttonStretchOnButtonClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void m_checkBoxStretchOnCheckBox( wxCommandEvent& event ) { event.Skip(); }
		virtual void m_buttonColorizeOnButtonClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void m_checkBoxColorizeOnCheckBox( wxCommandEvent& event ) { event.Skip(); }
		virtual void m_sliderFrameAveragerThresholdOnScroll( wxScrollEvent& event ) { event.Skip(); }
		virtual void m_buttonSampleOnButtonClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void m_buttonGaussianOnButtonClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void m_buttonSharpenOnButtonClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void m_buttonUnsharpMaskOnButtonClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void m_buttonStabLockOnButtonClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void m_buttonStabLetGoOnButtonClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void m_radioBtnNoZoomOnRadioButton( wxCommandEvent& event ) { event.Skip(); }
		virtual void m_radioBtn2xZoomOnRadioButton( wxCommandEvent& event ) { event.Skip(); }
		virtual void radioBtn4xZoomOnRadioButton( wxCommandEvent& event ) { event.Skip(); }
		virtual void radioBtn8xZoomOnRadioButton( wxCommandEvent& event ) { event.Skip(); }
		virtual void m_sliderEzoomVerticalOffsetOnScroll( wxScrollEvent& event ) { event.Skip(); }
		virtual void m_sliderEzoomHorisontalOffsetOnScroll( wxScrollEvent& event ) { event.Skip(); }
		
	
	public:
		
		MyFrame1( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxEmptyString, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 1000,500 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );
		
		~MyFrame1();
	
};

#endif //__NONAME_H__
