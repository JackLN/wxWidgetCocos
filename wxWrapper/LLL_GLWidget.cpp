#include "LLL_GLWidget.h"
#include <wx/dcclient.h>

NS_CC_BEGIN

BEGIN_EVENT_TABLE(LLL_GLWidget, wxGLCanvas)
EVT_PAINT(LLL_GLWidget::OnPaint)
EVT_MOUSE_EVENTS(LLL_GLWidget::OnMouseEvent)
EVT_TIMER(TIMER_GAMELOOP,LLL_GLWidget::OnTimer)
END_EVENT_TABLE()

void LLL_GLWidget::OnMouseEvent(wxMouseEvent& evt)
{
    if (_MouseFunc)
        _MouseFunc(evt);
}

void LLL_GLWidget::OnPaint(wxPaintEvent& evt)
{
    /*auto director = Director::getInstance();
    if (director && director->getRunningScene())
    director->drawScene();*/

    Director::getInstance()->mainLoop();

}

void LLL_GLWidget::SetMouseFunc(MOUSE_PTRFUN func)
{
    _MouseFunc = func;
}

void LLL_GLWidget::OnTimer(wxTimerEvent& evt)
{
    Refresh();
}

void LLL_GLWidget::StartGameLoop()
{
    _Timer.Start(1000 / 60);
}

NS_CC_END
