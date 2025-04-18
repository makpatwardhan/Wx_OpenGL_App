// GLCanvas.h
#ifndef GLCANVAS_H
#define GLCANVAS_H

#include <wx/glcanvas.h>
#include <wx/wx.h>

class GLCanvas : public wxGLCanvas {
public:
    GLCanvas(wxWindow* parent, const wxGLAttributes& dispAttrs);
    virtual ~GLCanvas();

private:
    wxGLContext* m_context;
    void OnPaint(wxPaintEvent& event);
    void OnSize(wxSizeEvent& event);
    void Render();
    
    wxDECLARE_EVENT_TABLE();
};

#endif
