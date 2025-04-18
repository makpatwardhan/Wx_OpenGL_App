// MyApp.cpp
#include "MyApp.h"
#include "GLCanvas.h"

wxIMPLEMENT_APP(MyApp);

bool MyApp::OnInit() {
    wxGLAttributes dispAttrs;
    dispAttrs.PlatformDefaults().Defaults().EndList();
    
    wxFrame* frame = new wxFrame(nullptr, wxID_ANY, "My OpenGL wxWidgets App", 
                               wxPoint(50, 50), wxSize(800, 600));
                               
    new GLCanvas(frame, dispAttrs);
    frame->Show(true);
    return true;
}
