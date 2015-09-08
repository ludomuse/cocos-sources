//use for the debug
#define COCOS2D_DEBUG 1

#include "../Include/LmGameManager.h"

USING_NS_CC;

LmGameManager::LmGameManager()
{
	m_pLmServerManager = new LmServerManager;
}

LmGameManager::~LmGameManager()
{
	//destroy the ServerManager
	delete m_pLmServerManager;

	//Browse the vector of scene and delete them
	for (std::vector<LmInteractionScene*>::iterator it = m_aInteractionSceneOfTheGame.begin(); it != m_aInteractionSceneOfTheGame.end(); ++it)
	{
		delete (*it);
	}

	//remove listener
	Director::getInstance()->getEventDispatcher()->removeCustomEventListeners("NextScene");

}

void LmGameManager::initPathsForResolution()
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

bool LmGameManager::init()
{

	initPathsForResolution();

	if(!m_pLmServerManager->init())
	{
		CCLOG("Initialization Server Manager failed");
		return false;
	}

	//get the vector of scene through the serverManager
	m_aInteractionSceneOfTheGame = m_pLmServerManager->getInteractionSceneOfTheGame();

	//init all the scenes
	for (std::vector<LmInteractionScene*>::iterator it = m_aInteractionSceneOfTheGame.begin(); it != m_aInteractionSceneOfTheGame.end(); ++it)
	{
		(*it)->init();
	}


	//init callback method of the custom event (use to know when an interactionScene want to communicate with this)
	auto NextScene = [=](EventCustom * event)
						{
		Director::getInstance()->replaceScene(TransitionFlipX::create(2,m_aInteractionSceneOfTheGame.at(0)));
						};

	//add the custom event to the event dispatcher
	Director::getInstance()->getEventDispatcher()->addCustomEventListener("NextScene",NextScene);

	return true;


}

void LmGameManager::runGame()
{
	//Init of the GameManager (resolution, vector of InteractionScene with server manager)
	init();

	//test run the first scene of the app
	Director::getInstance()->runWithScene(m_aInteractionSceneOfTheGame.at(0));

}
