#include "AppDelegate.h"
#include "audio/include/AudioEngine.h"

#include "HelloWorldScene.h"
#include "LLL_GLView.h"



std::string g_gamename = "Migame Editor";
//////////////////////////////////////////////////////////////////////////
AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{

}

//if you want a different context,just modify the value of glContextAttrs
//it will takes effect on all platforms
void AppDelegate::initGLContextAttrs()
{
    //set OpenGL context attributions,now can only set six attributions:
    //red,green,blue,alpha,depth,stencil
#if(CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 32, 8};
#else
	GLContextAttrs glContextAttrs = { 8, 8, 8, 8, 24, 8 };
#endif

    GLView::setGLContextAttrs(glContextAttrs);
}

// If you want to use packages manager to install more packages, 
// don't modify or remove this function
static int register_all_packages()
{
    return 0; //flag for packages manager
}

bool AppDelegate::applicationDidFinishLaunching() {	


	//InitCrashReport();
	// initialize director
	auto director = Director::getInstance();
	auto glview = director->getOpenGLView();
	if (!glview) {

        const int nDefWidth = 1280;
        const int nDefHeight = 720;

		//glview = GLViewImpl::createWithRect(g_gamename,Rect(0,0,nDefWidth,nDefHeight));
        glview = LLLGLView::GetInstance(_pCanvas);
		director->setOpenGLView(glview);
        (static_cast<LLLGLView*>(glview))->Resize();
	}
	// initialize director
//	auto director = Director::getInstance();
//	auto glview = director->getOpenGLView();
//	if (!glview) {
//
//        /*const int nDefWidth = 812 * 2;
//        const int nDefHeight = 375 * 2;*/
//
//        const int nDefWidth = 1280;
//        const int nDefHeight = 720;
//
//		int nWidht = nDefWidth;
//		int nHeight = nDefWidth;
//
//		RECT rt;
//		SystemParametersInfo(SPI_GETWORKAREA, 0, (PVOID)&rt, 0);
//#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
//		if (rt.right - rt.left < nWidht)
//#else
//		if (rt.right - rt.left != nWidht)
//#endif
//		{
//			nWidht = rt.right - rt.left;
//		}
//
//		nHeight = nWidht*nDefHeight / nDefWidth;			
//		
//		glview = GLViewImpl::createWithFullScreen(g_gamename);
//
//		
//
//		director->setOpenGLView(glview);
//
//	}
//#endif
	
	// add search pathes


#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#ifdef _DEBUG
	//AllocConsole(); freopen("CONIN$", "r", stdin); freopen("CONOUT$", "w", stdout); freopen("CONOUT$", "w", stderr);
#endif
	
#endif
	const int DesignWidth = 1280;
	const int DesignHeight = 720;
	glview->setDesignResolutionSize(DesignWidth, DesignHeight, ResolutionPolicy::FIXED_WIDTH);
	
	director->setMyPollEvent([=](){
        /*if (m_pGlobalServer)
        {
        if (!CCDirector::getInstance()->getOpenGLView()->windowShouldClose())
        {
        static bool bInit = false;
        if (!bInit)
        {
        bInit = true;
        m_pGlobalServer->Create();
        }
        else
        {
        m_pGlobalServer->OnUpDate();
        }
        }
        else
        m_pGlobalServer->GetAgentSocketSink()->CloseLink();
        }*/
	});

    // turn on display FPS
#ifdef _DEBUG
    //director->setDisplayStats( true );
#endif
    director->setDisplayStats( true );

    // set FPS. the default value is 1.0/60 if you don't call this
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
    director->setAnimationInterval(1.0 / 60);
#else
	director->setAnimationInterval(1.0 / 50);
#endif

    register_all_packages();

    auto scene = HelloWorld::scene();
    director->runWithScene(scene);
    director->drawScene();

    return true;
}




// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {

	
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {

	//if (time(nullptr) - m_nDidTime >= 10 && g_pGlobalServer->GetSceneManager()->GetCurSceneId() == PAGE_SCENE_PLAY)
	//	g_pGlobalServer->GetAgentSocketSink()->CloseLink();


    
}
