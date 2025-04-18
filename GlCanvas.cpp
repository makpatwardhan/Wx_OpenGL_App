// GLCanvas.cpp
#include "GLCanvas.h"
#include <GL/gl.h>
#include <GL/glu.h>

wxBEGIN_EVENT_TABLE(GLCanvas, wxGLCanvas)
    EVT_PAINT(GLCanvas::OnPaint)
    EVT_SIZE(GLCanvas::OnSize)
wxEND_EVENT_TABLE()

GLCanvas::GLCanvas(wxWindow* parent, const wxGLAttributes& dispAttrs)
    : wxGLCanvas(parent, dispAttrs) {
    m_context = new wxGLContext(this);
    SetCurrent(*m_context);
}

GLCanvas::~GLCanvas() {
    delete m_context;
}

void GLCanvas::OnPaint(wxPaintEvent& WXUNUSED(event)) {
    wxPaintDC(this);
    Render();
}

void GLCanvas::OnSize(wxSizeEvent& event) {
    Refresh();
    event.Skip();
}

void GLCanvas::Render() {
    SetCurrent(*m_context);
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    const wxSize clientSize = GetClientSize() * GetContentScaleFactor();
    glViewport(0, 0, clientSize.x, clientSize.y);
    
    // Set up 2D orthogonal projection
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, clientSize.x, clientSize.y, 0);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Draw red triangle
    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_TRIANGLES);
        glVertex2f(100.0f, 100.0f);
        glVertex2f(200.0f, 100.0f);
        glVertex2f(150.0f, 200.0f);
    glEnd();

    // Draw green circle
    glColor3f(0.0f, 1.0f, 0.0f);
    glBegin(GL_LINE_LOOP);
    for(int i = 0; i < 360; i++) {
        float degInRad = i * M_PI / 180.0f;
        glVertex2f(cos(degInRad)*50 + 300, sin(degInRad)*50 + 150);
    }
    glEnd();

    glFlush();
    SwapBuffers();
}
