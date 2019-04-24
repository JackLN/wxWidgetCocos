#include "LLL_GLView.h"

NS_CC_BEGIN

static LLLGLView* g_pMainWindow = nullptr;

static void MouseFunc(wxMouseEvent& evt)
{
    g_pMainWindow->MouseEvent(evt);
}

LLLGLView::LLLGLView()
    : _bIsInit(false)
    , _pWindow(nullptr)
    , _fScreenScaleFactor(1.0f)
{

}

LLLGLView::~LLLGLView()
{

}

bool LLLGLView::isOpenGLReady()
{
    return _bIsInit;
}

void LLLGLView::end()
{
    _pWindow->Close();
    wxDELETE(_pWindow);
    g_pMainWindow = nullptr;
    delete this;
}

void LLLGLView::swapBuffers()
{
    if (_bIsInit)
    {
        _pWindow->SwapBuffers();
    }
}

void LLLGLView::setFrameSize(float width, float height)
{
    GLView::setFrameSize(width, height);
	setDesignResolutionSize(_pWindow->GetSize().GetWidth(), _pWindow->GetSize().GetHeight(), ResolutionPolicy::NO_BORDER);
	cocos2d::Director::getInstance()->setProjection(cocos2d::Director::getInstance()->getProjection());
}

void LLLGLView::setIMEKeyboardState(bool bOpen)
{

}

void LLLGLView::setViewName(const char* pszViewName)
{
    GLViewImpl::setViewName(pszViewName);
    /*if (_pWindow)
    {
    _pWindow->setti
    }*/
}

bool LLLGLView::Create(LLL_GLWidget* window)
{
    bool ret = false;
    do 
    {
        CC_BREAK_IF(_pWindow);

        float fWidth = 1280;
        float fHeight = 720;

        _pWindow = window;
        _pWindow->SetMouseFunc(&cocos2d::MouseFunc);
        //event

        setDesignResolutionSize(fWidth, fHeight, ResolutionPolicy::EXACT_FIT);
        ret = initGlew();
        CC_BREAK_IF(!ret);

        _bIsInit = true;
        g_pMainWindow = this;
        ret = true;
    } while (0);

    return ret;
}

LLLGLView* LLLGLView::GetInstance(LLL_GLWidget* window)
{
    if (g_pMainWindow == nullptr)
    {
        LLLGLView* view = new LLLGLView();
        if (!view->Create(window))
            delete view;
    }
    return g_pMainWindow;
}

HWND LLLGLView::getWin32Window()
{
    return _pWindow->GetParent()->GetHWND();
}

void LLLGLView::pollEvents()
{

}

bool LLLGLView::windowShouldClose()
{
    return (_pWindow == nullptr);
}

void LLLGLView::MouseEvent(wxMouseEvent& evt)
{
    if (evt.LeftDown())
        MousePress(evt);
    else if (evt.LeftUp())
        MouseRelease(evt);

    if (evt.Moving())
        MouseMove(evt);

    if (evt.GetEventType() == wxEVT_MOUSEWHEEL)
        MouseWheel(evt);
}

void LLLGLView::MousePress(wxMouseEvent& evt)
{
    _captured = true;
    _mouseX = (float)(evt.GetX()) / _fScreenScaleFactor;
    _mouseY = (float)(evt.GetY()) / _fScreenScaleFactor;

    if (this->getViewPortRect().equals(Rect::ZERO) || this->getViewPortRect().containsPoint(Vec2(_mouseX, _mouseY)))
	{
		intptr_t id = 0;
		this->handleTouchesBegin(1, &id, &_mouseX, &_mouseY);
	}

	//Because OpenGL and cocos2d-x uses different Y axis, we need to convert the coordinate here
	float cursorX = (_mouseX - _viewPortRect.origin.x) / _scaleX;
	float cursorY = (_viewPortRect.origin.y + _viewPortRect.size.height - _mouseY) / _scaleY;

    EventMouse ccEvent(EventMouse::MouseEventType::MOUSE_DOWN);
	ccEvent.setCursorPosition(cursorX, cursorY);
    if (evt.GetButton() == wxMOUSE_BTN_LEFT)
    {
        ccEvent.setMouseButton(GLFW_MOUSE_BUTTON_LEFT);
    }
    else if (evt.GetButton() == wxMOUSE_BTN_RIGHT)
    {
        ccEvent.setMouseButton(GLFW_MOUSE_BUTTON_RIGHT);
    }
    else if (evt.GetButton() == wxMOUSE_BTN_MIDDLE)
    {
        ccEvent.setMouseButton(GLFW_MOUSE_BUTTON_MIDDLE);
    }
	Director::getInstance()->getEventDispatcher()->dispatchEvent(&ccEvent);
}

void LLLGLView::MouseMove(wxMouseEvent& evt)
{
    if (!_captured)
        return;

    _mouseX = (float)(evt.GetX()) / _fScreenScaleFactor;
	_mouseY = (float)(evt.GetY()) / _fScreenScaleFactor;

	_mouseX /= this->getFrameZoomFactor();
	_mouseY /= this->getFrameZoomFactor();

	if (_isInRetinaMonitor)
	{
		if (_retinaFactor == 1)
		{
			_mouseX *= 2;
			_mouseY *= 2;
		}
	}

	if (_captured)
	{
		intptr_t id = 0;
		this->handleTouchesMove(1, &id, &_mouseX, &_mouseY);
	}

	//Because OpenGL and cocos2d-x uses different Y axis, we need to convert the coordinate here
	float cursorX = (_mouseX - _viewPortRect.origin.x) / _scaleX;
	float cursorY = (_viewPortRect.origin.y + _viewPortRect.size.height - _mouseY) / _scaleY;

	EventMouse ccEvent(EventMouse::MouseEventType::MOUSE_MOVE);
    // Set current button
    if (evt.GetButton() == wxMOUSE_BTN_LEFT)
    {
        ccEvent.setMouseButton(GLFW_MOUSE_BUTTON_LEFT);
    }
    else if (evt.GetButton() == wxMOUSE_BTN_RIGHT)
    {
        ccEvent.setMouseButton(GLFW_MOUSE_BUTTON_RIGHT);
    }
    else if (evt.GetButton() == wxMOUSE_BTN_MIDDLE)
    {
        ccEvent.setMouseButton(GLFW_MOUSE_BUTTON_MIDDLE);
    }

    ccEvent.setCursorPosition(cursorX, cursorY);
    Director::getInstance()->getEventDispatcher()->dispatchEvent(&ccEvent);
}

void LLLGLView::MouseRelease(wxMouseEvent& evt)
{
    if (_captured)
	{
		_captured = false;
		intptr_t id = 0;
		this->handleTouchesEnd(1, &id, &_mouseX, &_mouseY);
	}

	//Because OpenGL and cocos2d-x uses different Y axis, we need to convert the coordinate here
	float cursorX = (_mouseX - _viewPortRect.origin.x) / _scaleX;
	float cursorY = (_viewPortRect.origin.y + _viewPortRect.size.height - _mouseY) / _scaleY;

	EventMouse ccEvent(EventMouse::MouseEventType::MOUSE_UP);
	ccEvent.setCursorPosition(cursorX, cursorY);
	ccEvent.setMouseButton(evt.GetButton());
	Director::getInstance()->getEventDispatcher()->dispatchEvent(&ccEvent);
}

void LLLGLView::MouseWheel(wxMouseEvent& evt)
{
    float cursorX = (_mouseX - _viewPortRect.origin.x) / _scaleX;
    float cursorY = (_viewPortRect.origin.y + _viewPortRect.size.height - _mouseY) / _scaleY;

    EventMouse ccEvent(EventMouse::MouseEventType::MOUSE_SCROLL);
    ccEvent.setScrollData((float)evt.GetX(), -(float)evt.GetY());
    ccEvent.setCursorPosition(cursorX, cursorY);
    Director::getInstance()->getEventDispatcher()->dispatchEvent(&ccEvent);
}

void LLLGLView::Resize()
{
    if (_pWindow != nullptr)
    {
        auto size = _pWindow->GetSize();

		float ratio = (float)(_pWindow->GetSize().GetWidth()) / (float)(_pWindow->GetSize().GetHeight());
		setFrameSize(_pWindow->GetSize().GetHeight() * ratio, _pWindow->GetSize().GetHeight());
	}
}

NS_END