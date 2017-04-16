#include <wx/wx.h>

class MyApp : public wxApp
{
public:
    virtual bool OnInit() wxOVERRIDE;
};

class MyFrame : public wxFrame {
public:
  MyFrame();
  void OnClick(wxCommandEvent& event);
};

class MyModalDialog : public wxDialog
{
public:

  MyModalDialog(wxWindow *parent = NULL);

  void OnInit(wxInitDialogEvent& event);
  
private:
    wxDECLARE_EVENT_TABLE();
};


BEGIN_EVENT_TABLE( MyModalDialog, wxDialog )
EVT_INIT_DIALOG( MyModalDialog::OnInit )
END_EVENT_TABLE()

wxIMPLEMENT_APP(MyApp);

bool MyApp::OnInit()
{
  MyFrame* frame= new MyFrame();
  frame -> Show();
    return true;
}

MyModalDialog::MyModalDialog( wxWindow* parent )
  : wxDialog(parent,wxID_ANY,  wxString(_T("Modal dialog") ))
{
}

void MyModalDialog::OnInit(wxInitDialogEvent& WXUNUSED(event))
{
	printf("On Init\n");
	EndModal(wxID_OK);
	if ( !IsModal() )
    wxMessageBox(_T("not modal"));
  
}

MyFrame::MyFrame() : wxFrame(NULL, wxID_ANY, wxT("Prueba"), wxDefaultPosition, wxSize(200,150))
{
  wxPanel *panel = new wxPanel(this, wxID_ANY);

  wxButton *button = new wxButton(panel, wxID_EXIT, wxT("Modal"),
				  wxPoint(20,20));
  Connect(wxID_EXIT, wxEVT_COMMAND_BUTTON_CLICKED,
	  wxCommandEventHandler(MyFrame::OnClick));
  button -> SetFocus();
  Centre();
  
}

void MyFrame::OnClick(wxCommandEvent& WXUNUSED(event))
{
    MyModalDialog d;

    int a = d.ShowModal();  
}
