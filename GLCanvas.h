#ifndef GLCANVAS_H
#define GLCANVAS_H

#include <wx/glcanvas.h>
#include <wx/wx.h>
#include <wx/panel.h>
#include <wx/slider.h>
#include <wx/checkbox.h>

class GLCanvas : public wxGLCanvas {
public:
    GLCanvas(wxWindow* parent, const wxGLAttributes& dispAttrs);
    virtual ~GLCanvas();

    void ToggleControlPanel();
    wxPanel* GetControlPanel() const { return m_controlPanel; }

//private:
    wxGLContext* m_context;
    wxPanel* m_controlPanel;
    GLuint m_buttonTexture;
    float m_rotationAngle;
    bool m_showFeature;

    void OnPaint(wxPaintEvent& event);
    void OnSize(wxSizeEvent& event);
    void OnMouseClick(wxMouseEvent& event);
    void Render();
    GLuint LoadTexture(const wxString& path);

    void OnSliderChange(wxCommandEvent& event);
    void OnCheckboxToggle(wxCommandEvent& event);

    wxDECLARE_EVENT_TABLE();
};

#endif
