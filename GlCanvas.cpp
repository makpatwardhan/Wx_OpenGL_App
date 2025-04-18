#include "GLCanvas.h"
#include <GL/gl.h>
#include <GL/glu.h>
#include <vector>

wxBEGIN_EVENT_TABLE(GLCanvas, wxGLCanvas)
    EVT_PAINT(GLCanvas::OnPaint)
    EVT_SIZE(GLCanvas::OnSize)
    EVT_LEFT_DOWN(GLCanvas::OnMouseClick)
wxEND_EVENT_TABLE()

GLCanvas::GLCanvas(wxWindow* parent, const wxGLAttributes& dispAttrs)
    : wxGLCanvas(parent, dispAttrs), m_rotationAngle(0.0f), m_showFeature(true) {
    m_context = new wxGLContext(this);
    SetCurrent(*m_context);
    ::wxInitAllImageHandlers();
    m_buttonTexture = LoadTexture("C:\\Users\\Makarand.Patwardhan\\source\\repos\\wx_opengl_app\\build\\Debug\\button.png");
}

GLCanvas::~GLCanvas() {
    delete m_context;
    glDeleteTextures(1, &m_buttonTexture);
}

GLuint GLCanvas::LoadTexture(const wxString& path) {
    wxImage image(path);
    std::cout << "Loading the image..........." <<std::endl;

    if(!image.IsOk()) return 0;

    std::cout << "The image is correct" <<std::endl;
    GLuint textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    unsigned char* data = image.GetData();
    unsigned char* alpha = image.GetAlpha();
    int bytesPerPixel = image.HasAlpha() ? 4 : 3;
    int width = image.GetWidth();
    int height = image.GetHeight();

    std::vector<unsigned char> glData(width * height * bytesPerPixel);
    for(int y=0; y<height; y++) {
        for(int x=0; x<width; x++) {
            int srcIdx = (y * width + x) * 3;
            int dstIdx = ((height-1-y) * width + x) * bytesPerPixel;
            
            glData[dstIdx+0] = data[srcIdx+0];
            glData[dstIdx+1] = data[srcIdx+1];
            glData[dstIdx+2] = data[srcIdx+2];
            if(bytesPerPixel == 4) {
                glData[dstIdx+3] = alpha ? alpha[y*width+x] : 255;
            }
        }
    }

    glTexImage2D(GL_TEXTURE_2D, 0, bytesPerPixel, width, height, 0,
                 bytesPerPixel == 4 ? GL_RGBA : GL_RGB, 
                 GL_UNSIGNED_BYTE, glData.data());
    return textureID;
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
    
    // Set up projection
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, clientSize.x, clientSize.y, 0);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glRotatef(m_rotationAngle, 0.0f, 0.0f, 1.0f);

    // Draw original shapes if enabled
    if(m_showFeature) {
        // Red triangle
        glColor3f(1.0f, 0.0f, 0.0f);
        glBegin(GL_TRIANGLES);
            glVertex2f(100.0f, 100.0f);
            glVertex2f(200.0f, 100.0f);
            glVertex2f(150.0f, 200.0f);
        glEnd();

        // Green circle
        glColor3f(0.0f, 1.0f, 0.0f);
        glBegin(GL_LINE_LOOP);
        for(int i = 0; i < 360; i++) {
            float degInRad = i * M_PI / 180.0f;
            glVertex2f(cos(degInRad)*50 + 300, sin(degInRad)*50 + 150);
        }
        glEnd();
    }

    // Draw overlay button
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, m_buttonTexture);
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_QUADS);
        glTexCoord2f(0,1); glVertex2f(10, 10);
        glTexCoord2f(1,1); glVertex2f(50, 10);
        glTexCoord2f(1,0); glVertex2f(50, 50);
        glTexCoord2f(0,0); glVertex2f(10, 50);
    glEnd();
    glDisable(GL_TEXTURE_2D);

    glFlush();
    SwapBuffers();
}

void GLCanvas::OnMouseClick(wxMouseEvent& event) {
    wxPoint mousePos = event.GetPosition();
    if(mousePos.x >= 10 && mousePos.x <= 50 && 
       mousePos.y >= 10 && mousePos.y <= 50) {
        ToggleControlPanel();
    }
    event.Skip();
}

void GLCanvas::ToggleControlPanel() {
    if(m_controlPanel) {
        m_controlPanel->Show(!m_controlPanel->IsShown());
        GetParent()->Layout();
    }
}

void GLCanvas::OnSliderChange(wxCommandEvent& event) {
    m_rotationAngle = dynamic_cast<wxSlider*>(event.GetEventObject())->GetValue();
    Refresh();
}

void GLCanvas::OnCheckboxToggle(wxCommandEvent& event) {
    m_showFeature = event.IsChecked();
    Refresh();
}
