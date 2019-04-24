#include "LLL_App.h"
#include "AppDelegate.h"
#include "LLL_GLWidget.h"

USING_NS_CC;


wxBEGIN_EVENT_TABLE(MyFrame, wxFrame)
EVT_MENU(ID_Hello, MyFrame::OnHello)
EVT_MENU(wxID_EXIT, MyFrame::OnExit)
EVT_MENU(wxID_ABOUT, MyFrame::OnAbout)
wxEND_EVENT_TABLE()

bool MyApp::OnInit()
{
    //MyFrame *frame = new MyFrame("Hello World", wxPoint(50, 50), wxSize(450, 340));  
    wxBoxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);

    MyFrame *frame = new MyFrame("Hello World", wxDefaultPosition, wxSize(1300,800));
    frame->Show(true);

    int args[] = { WX_GL_RGBA, WX_GL_DOUBLEBUFFER, WX_GL_DEPTH_SIZE, 16, 0 };

    LLL_GLWidget* pWidget = new LLL_GLWidget(frame, args,wxSize(1280,720));
    sizer->Add(pWidget, 1, wxEXPAND);

    frame->SetSizer(sizer);
    frame->SetAutoLayout(true);

    frame->Show();

    auto ccApp = new AppDelegate();
    ccApp->setGLCanvas(pWidget);
    ccApp->applicationDidFinishLaunching();


    pWidget->StartGameLoop();
    return true;
}
MyFrame::MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
    : wxFrame(NULL, wxID_ANY, title, pos, size)
{
    wxMenu *menuFile = new wxMenu;
    menuFile->Append(ID_Hello, "&Hello...\tCtrl-H",
        "Help string shown in status bar for this menu item");
    menuFile->AppendSeparator();
    menuFile->Append(wxID_EXIT);
    wxMenu *menuHelp = new wxMenu;
    menuHelp->Append(wxID_ABOUT);
    wxMenuBar *menuBar = new wxMenuBar;
    menuBar->Append(menuFile, "&File");
    menuBar->Append(menuHelp, "&Help");
    SetMenuBar(menuBar);
    CreateStatusBar();
    SetStatusText("Welcome to wxWidgets!");
}
void MyFrame::OnExit(wxCommandEvent& event)
{
    Close(true);
}
void MyFrame::OnAbout(wxCommandEvent& event)
{
    wxMessageBox("This is a wxWidgets' Hello world sample",
        "About Hello World", wxOK | wxICON_INFORMATION);
}
void MyFrame::OnHello(wxCommandEvent& event)
{
    wxLogMessage("Hello world from wxWidgets!");
}
