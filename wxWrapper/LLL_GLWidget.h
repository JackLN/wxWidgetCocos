#pragma once

#include "ComDefine.h"
#include "cocos2d.h"
#include <wx/glcanvas.h>
#include <wx/timer.h>

NS_CC_BEGIN

#define  TIMER_GAMELOOP 100001

typedef void(*MOUSE_PTRFUN)(wxMouseEvent& event);

class LLL_GLWidget : public wxGLCanvas
{
private:

    wxGLContext*       _pContext;
    wxTimer            _Timer;

    void OnTimer(wxTimerEvent& evt);

public:
    LLL_GLWidget(wxWindow* parent, int* args,wxSize size)
        :wxGLCanvas(parent,wxID_ANY,args,wxDefaultPosition,size)
        , _Timer(this,TIMER_GAMELOOP)
    {
        _pContext = new wxGLContext(this);
        SetCurrent(*_pContext);
    }

    virtual ~LLL_GLWidget()
    {
        CC_SAFE_DELETE(_pContext);
    }

    void resized(wxSizeEvent& evt)
    {
        Refresh();
    }

    void OnPaint(wxPaintEvent& evt);
    void SetMouseFunc(MOUSE_PTRFUN func);
    void OnMouseEvent(wxMouseEvent& evt);

    void StartGameLoop();

private:
    MOUSE_PTRFUN _MouseFunc;


    wxDECLARE_EVENT_TABLE();

};

NS_END

