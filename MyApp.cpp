#include "MyApp.h"
#include "GLCanvas.h"

wxIMPLEMENT_APP(MyApp);

bool MyApp::OnInit() {
    wxGLAttributes dispAttrs;
    dispAttrs.PlatformDefaults().Defaults().EndList();
    
    wxFrame* frame = new wxFrame(nullptr, wxID_ANY, "OpenGL wxWidgets App", 
                               wxPoint(50, 50), wxSize(800, 600));
    
    // Create main sizer
    wxBoxSizer* mainSizer = new wxBoxSizer(wxHORIZONTAL);
    
    // Create GLCanvas
    GLCanvas* canvas = new GLCanvas(frame, dispAttrs);
    mainSizer->Add(canvas, 1, wxEXPAND);
    
    // Create control panel
    wxPanel* panel = new wxPanel(frame);
    wxBoxSizer* panelSizer = new wxBoxSizer(wxVERTICAL);
    
    wxSlider* slider = new wxSlider(panel, wxID_ANY, 0, 0, 360, 
                                  wxDefaultPosition, wxDefaultSize,
                                  wxSL_HORIZONTAL | wxSL_LABELS);
    slider->Bind(wxEVT_SLIDER, &GLCanvas::OnSliderChange, canvas);
    
    wxCheckBox* checkbox = new wxCheckBox(panel, wxID_ANY, "Show Shapes");
    checkbox->SetValue(true);
    checkbox->Bind(wxEVT_CHECKBOX, &GLCanvas::OnCheckboxToggle, canvas);
    
    panelSizer->Add(slider, 0, wxALL, 5);
    panelSizer->Add(checkbox, 0, wxALL, 5);
    panel->SetSizer(panelSizer);
    panel->Hide();
    
    mainSizer->Add(panel, 0, wxEXPAND);
    frame->SetSizer(mainSizer);
    
    canvas->m_controlPanel = panel;
    
    frame->Show(true);
    return true;
}
