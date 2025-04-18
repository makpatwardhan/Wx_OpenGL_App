#include "MyApp.h"
#include <wx/wx.h>

int main(int argc, char** argv)
{
    // Initialize wxWidgets library
    wxDISABLE_DEBUG_SUPPORT();

    wxEntryStart(argc, argv);
    wxApp::SetInstance(new MyApp());
    int exitCode = wxEntry(argc, argv);
    wxEntryCleanup();

    return exitCode;
}