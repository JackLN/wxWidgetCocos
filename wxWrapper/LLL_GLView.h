#pragma once
#include "ComDefine.h"
#include "cocos2d.h"
#include "LLL_GLWidget.h"


NS_CC_BEGIN

class LLLGLView : public GLViewImpl
{
public:
    LLLGLView();
    virtual ~LLLGLView();

    /* override functions */
	virtual bool isOpenGLReady() override;
	virtual void end() override;
	virtual void swapBuffers() override;
	virtual void setFrameSize(float width, float height) override;
	virtual void setIMEKeyboardState(bool bOpen) override;
    virtual void setViewName(const char* pszViewName);
    virtual bool windowShouldClose();
    HWND getWin32Window();
    void pollEvents() override;

    static LLLGLView* GetInstance(LLL_GLWidget* window);

    void   MouseEvent(wxMouseEvent& evt);
    void   MousePress(wxMouseEvent& evt);
    void   MouseMove(wxMouseEvent& evt);
    void   MouseRelease(wxMouseEvent& evt);
    void   MouseWheel(wxMouseEvent& evt);

    void   Resize();

private:
    virtual bool Create(LLL_GLWidget* window);

    bool             _bIsInit;
    float            _fScreenScaleFactor;
    LLL_GLWidget*    _pWindow;

};


NS_END;