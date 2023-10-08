#include <iostream>
#include <SDL.h>
#include <wx/wx.h>
#include <wx/filedlg.h>
#include <vector>

class MainFrame : public wxFrame
{
public:
    MainFrame(const wxString &title, const wxPoint &pos, const wxSize &size);

private:
    void OnOpenFile(wxCommandEvent &event);
    void OnPaint(wxPaintEvent &event);

    wxPanel *panel;
    wxButton *openButton;
    wxStaticText *infoLabel;
    
    bool fileOpened;
};
 
MainFrame::MainFrame(const wxString &title, const wxPoint &pos, const wxSize &size)
    : wxFrame(NULL, wxID_ANY, title, pos, size), fileOpened(false)
{
    // Create a custom panel to set the background color
    panel = new wxPanel(this, wxID_ANY);
    panel->Bind(wxEVT_PAINT, &MainFrame::OnPaint, this);

    // Create an "Open File" button and center it horizontally
    openButton = new wxButton(panel, wxID_ANY, "Choose File     ", wxDefaultPosition, wxDefaultSize, wxALIGN_CENTRE);
    openButton->Bind(wxEVT_BUTTON, &MainFrame::OnOpenFile, this);

    // Set a nicer font and style for the button
    wxFont buttonFont(12, wxROMAN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
    openButton->SetFont(buttonFont);
    openButton->SetForegroundColour(*wxWHITE);
    openButton->SetBackgroundColour(*wxBLACK);

    // Create a vertical box sizer to center the button vertically
    wxBoxSizer *mainSizer = new wxBoxSizer(wxVERTICAL);
    mainSizer->AddStretchSpacer();
    mainSizer->Add(openButton, 0, wxALIGN_CENTER);
    mainSizer->AddStretchSpacer();

    // Set the sizer for the custom panel
    panel->SetSizer(mainSizer);
}

void MainFrame::OnOpenFile(wxCommandEvent &event)
{
    // Create a file dialog to choose a .wav file
    wxFileDialog openFileDialog(this, "Open .wav File", "", "", "WAV files (*.wav)|*.wav", wxFD_OPEN | wxFD_FILE_MUST_EXIST);

    if (openFileDialog.ShowModal() == wxID_CANCEL)
        return;

    wxString selectedFile = openFileDialog.GetPath();

        // Remove the "Choose File" button from the layout
        openButton->Destroy();

        // Create a new "Choose File" button (recurring)
        openButton = new wxButton(panel, wxID_ANY, " Choose File     ", wxDefaultPosition, wxDefaultSize, wxALIGN_CENTRE);
        openButton->Bind(wxEVT_BUTTON, &MainFrame::OnOpenFile, this);
        openButton->SetFont(wxFont(12, wxROMAN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));
        openButton->SetForegroundColour(*wxWHITE);
        openButton->SetBackgroundColour(*wxBLACK);

        // Create a vertical box sizer to center the button vertically (recurring)
        wxBoxSizer *mainSizer = new wxBoxSizer(wxVERTICAL);
        mainSizer->AddStretchSpacer();
        mainSizer->Add(openButton, 0, wxALIGN_CENTER);
        mainSizer->AddStretchSpacer();

        // Set the sizer for the custom panel (recurring)
        panel->SetSizer(mainSizer);

        // Trigger a repaint event to draw the waveform
        panel->Refresh();
    }
    else
    {
        wxMessageBox("Error loading the selected .wav file.", "Error", wxOK | wxICON_ERROR, this);
    }
}

void MainFrame::OnPaint(wxPaintEvent &event)
{
    // Custom paint event handler to set the background color and draw the waveform
    wxPaintDC dc(panel);
    wxColor bgColor(30, 30, 30); // Dark gray background color
    dc.SetBackground(wxBrush(bgColor));
    dc.Clear();

}

int main(int argc, char *argv[])
{
    // Initialize wxWidgets
    wxApp::SetInstance(new wxApp);
    wxEntryStart(argc, argv);
    wxTheApp->OnInit();

    // Create the custom frame
    MainFrame *frame = new MainFrame("Display Waveform", wxDefaultPosition, wxSize(1000, 900));
    frame->Show(true);

    // Start the wxWidgets event loop
    wxTheApp->MainLoop();

    return 0;
}
