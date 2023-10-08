#include <iostream>
#include <wx/wx.h>
#include <wx/filedlg.h>
#include <wx/image.h>

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
    wxBitmap imageBitmap; // Store the loaded image as a bitmap
    wxString imagePath;   // Store the path to the loaded image
};

MainFrame::MainFrame(const wxString &title, const wxPoint &pos, const wxSize &size)
    : wxFrame(NULL, wxID_ANY, title, pos, size), imagePath(wxEmptyString)
{
    // Register the TIFF image handler
    wxImage::AddHandler(new wxTIFFHandler);

    // Create a custom panel to set the background color
    panel = new wxPanel(this, wxID_ANY);
    panel->Bind(wxEVT_PAINT, &MainFrame::OnPaint, this);

    //Set the background color
    wxColor backgroundColor(30, 30, 30);
    panel->SetBackgroundColour(backgroundColor);

    // Create a vertical box sizer for the main layout
    wxBoxSizer *mainSizer = new wxBoxSizer(wxVERTICAL);

    // Create a centered horizontal box sizer for the button
    wxBoxSizer *buttonSizer = new wxBoxSizer(wxHORIZONTAL);
    buttonSizer->AddStretchSpacer();
    
    // Create an "Open File" button and center it horizontally
    openButton = new wxButton(panel, wxID_ANY, "  Choose Image     ", wxDefaultPosition, wxDefaultSize, wxALIGN_CENTER);
    openButton->Bind(wxEVT_BUTTON, &MainFrame::OnOpenFile, this);

    // Set a nicer font and style for the button
    wxFont buttonFont(12, wxROMAN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
    openButton->SetFont(buttonFont);
    openButton->SetForegroundColour(*wxWHITE);
    openButton->SetBackgroundColour(*wxBLACK);
    
    buttonSizer->Add(openButton, 0, wxALIGN_CENTER);
    buttonSizer->AddStretchSpacer();
    
    // Add the button sizer to the main sizer
    mainSizer->Add(buttonSizer, 0, wxEXPAND);
    mainSizer->AddStretchSpacer();
    
    // Set the sizer for the custom panel
    panel->SetSizer(mainSizer);
}

void MainFrame::OnOpenFile(wxCommandEvent &event)
{
    // Create a file dialog to choose a .tif file
    wxFileDialog openFileDialog(this, "Open .tif Image", "", "", "TIFF files (*.tif)|*.tif", wxFD_OPEN | wxFD_FILE_MUST_EXIST);

    if (openFileDialog.ShowModal() == wxID_CANCEL)
        return;

    imagePath = openFileDialog.GetPath();

    // Load and display the image using wxWidgets
    wxImage image;
    if (image.LoadFile(imagePath, wxBITMAP_TYPE_TIF))
    {
        imageBitmap = wxBitmap(image);

        // Trigger a repaint event to display the loaded image
        panel->Refresh();
    }
    else
    {
        wxMessageBox("Error loading the selected image.", "Error", wxOK | wxICON_ERROR, this);
    }
}

void MainFrame::OnPaint(wxPaintEvent &event)
{
    // Custom paint event handler to display the loaded image
    wxPaintDC dc(panel);

    if (imageBitmap.IsOk())
    {
        // Get the panel size
        int panelWidth, panelHeight;
        panel->GetSize(&panelWidth, &panelHeight);

        // Calculate the position to center the image
        int x = (panelWidth - imageBitmap.GetWidth()) / 2;
        int y = (panelHeight - imageBitmap.GetHeight()) / 2;

        // Draw the loaded image in the center
        dc.DrawBitmap(imageBitmap, x, y, false);
    }
}

int main(int argc, char *argv[])
{
    // Initialize wxWidgets
    wxApp::SetInstance(new wxApp);
    wxEntryStart(argc, argv);
    wxTheApp->OnInit();

    // Create the custom frame
    MainFrame *frame = new MainFrame("TIFF Image Renderer", wxDefaultPosition, wxSize(800, 600));
    frame->Show(true);

    // Start the wxWidgets event loop
    wxTheApp->MainLoop();

    return 0;
}
