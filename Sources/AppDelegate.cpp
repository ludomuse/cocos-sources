//use for the debug
#define COCOS2D_DEBUG 1

#include "../Include/AppDelegate.h"

USING_NS_CC;

AppDelegate::AppDelegate()
{
	m_pLmGameManager = new LmGameManager;
	m_pLmMenu = new LmMenu;
}

AppDelegate::~AppDelegate()
{
	delete m_pLmGameManager;
	delete m_pLmMenu;

	//remove listener
	Director::getInstance()->getEventDispatcher()->removeCustomEventListeners("MenuFinished");
}

//if you want a different context,just modify the value of glContextAttrs
//it will takes effect on all platforms
void AppDelegate::initGLContextAttrs()
{
	//set OpenGL context attributions,now can only set six attributions:
	//red,green,blue,alpha,depth,stencil
	GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};

	GLView::setGLContextAttrs(glContextAttrs);
}

// If you want to use packages manager to install more packages, 
// don't modify or remove this function
static int register_all_packages()
{
	return 0; //flag for packages manager
}

bool AppDelegate::applicationDidFinishLaunching()
{
	init();

	//display a splashscreen then a log screen then a wifidirect screen and get info
	m_pLmMenu->splashScreen();
	//m_pLmGameManager->runGame();
	return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground()
{
	Director::getInstance()->stopAnimation();

	// if you use SimpleAudioEngine, it must be pause
	// SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground()
{
	Director::getInstance()->startAnimation();

	// if you use SimpleAudioEngine, it must resume here
	// SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}

void AppDelegate::initPathsForResolution()
{
	// initialize director
	auto l_director = Director::getInstance();
	auto l_glview = l_director->getOpenGLView();

	if(!l_glview)
	{
		l_glview = GLViewImpl::create("Ludomuse");
		l_director->setOpenGLView(l_glview);
	}

	// turn off display FPS
	l_director->setDisplayStats(false);

	// set FPS. the default value is 1.0/60 if you don't call this
	l_director->setAnimationInterval(1.0 / 60);

	// Set the design resolution, refer to this link for more information => http://www.cocos2d-x.org/wiki/Detailed_explanation_of_Cocos2d-x_Multi-resolution_adaptation
	//EXACT_FIT || NO_BORDER || SHOW_ALL
	l_glview->setDesignResolutionSize(s_DesignResolutionSize.width, s_DesignResolutionSize.height, ResolutionPolicy::NO_BORDER);

	//get the size of the device's screen
	Size l_frameSize = l_glview->getFrameSize();

	//use to determine in what order we search in the ressources directories
	auto l_fileUtils = FileUtils::getInstance();
	std::vector<std::string> l_resDirOrders;

	// if the frame's height is larger than the height of medium size we want to get large ressources
	if (l_frameSize.height > s_MediumResolutionSize.height)
	{
		//we are going to get ressources in the large ressources directorie then in the  medium and finally in the small
		l_resDirOrders.push_back("largeResolutionSize");
		l_resDirOrders.push_back("mediumResolutionSize");
		l_resDirOrders.push_back("smallResolutionSize");
		l_director->setContentScaleFactor(MIN(s_LargeResolutionSize.height/s_DesignResolutionSize.height, s_LargeResolutionSize.width/s_DesignResolutionSize.width));
	}
	// if the frame's height is larger than the height of small size.
	else if (l_frameSize.height > s_SmallResolutionSize.height)
	{
		l_resDirOrders.push_back("mediumResolutionSize");
		l_resDirOrders.push_back("smallResolutionSize");
		l_director->setContentScaleFactor(MIN(s_MediumResolutionSize.height/s_DesignResolutionSize.height, s_MediumResolutionSize.width/s_DesignResolutionSize.width));
	}
	// if the frame's height is smaller than the height of medium size.
	else
	{
		l_resDirOrders.push_back("smallResolutionSize");
		l_director->setContentScaleFactor(MIN(s_SmallResolutionSize.height/s_DesignResolutionSize.height, s_SmallResolutionSize.width/s_DesignResolutionSize.width));
	}

	//set the paths
	l_fileUtils->setSearchPaths(l_resDirOrders);
}

bool AppDelegate::init()
{

	//init resolution
	initPathsForResolution();

	//init callback method of the custom event (use to know when LmMenu finished )
	auto MenuFinished = [=](EventCustom * event)
								{
		//LmGameManager get users from the LmMenu
		m_pLmGameManager->setPUser1(m_pLmMenu->getPUser1());
		m_pLmGameManager->setPUser2(m_pLmMenu->getPUser2());
		m_pLmGameManager->runGame();
								};

	//add the custom event to the event dispatcher
	Director::getInstance()->getEventDispatcher()->addCustomEventListener("MenuFinished",MenuFinished);
}
