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
	//delete users created by LmMenu
	delete m_pUser1;
	delete m_pUser2;

	//destroy the ServerManager
	delete m_pLmServerManager;

	//Browse the vector of scene and delete them
	for (std::vector<LmInteractionScene*>::iterator it = m_aInteractionSceneOfTheGame.begin(); it != m_aInteractionSceneOfTheGame.end(); ++it)
	{
		delete (*it);
	}

	//remove listener
	Director::getInstance()->getEventDispatcher()->removeCustomEventListeners("InteractionSceneFinished");

}

bool LmGameManager::initDashboard()
{
	//use to place elements
	Size l_oVisibleSize = Director::getInstance()->getVisibleSize();
	Point l_oOrigin = Director::getInstance()->getVisibleOrigin();

	//create thhe scene the main layer and put element on it
	m_pDashboardScene = Scene::create();
	m_pUserLayer = Layer::create();
	m_pDashboardScene->addChild(m_pUserLayer);

	//we add the different background with different zorder

	//background
	auto l_oSpriteBackground = Sprite::create("fullBlue.png");
	l_oSpriteBackground->setPosition(l_oVisibleSize.width*0.5f,l_oVisibleSize.height*0.5f);
	m_pUserLayer->addChild(l_oSpriteBackground,0);

	/*auto l_oSpriteBackgroundUser1Profile = Sprite::create("spriteBackgroundUser1Profile.png");
	l_oSpriteBackgroundUser1Profile->setAnchorPoint(Point(1, 1));
	l_oSpriteBackgroundUser1Profile->setPosition(l_oOrigin.x,l_oVisibleSize.height);
	m_pUserLayer->addChild(l_oSpriteBackgroundUser1Profile,1);*/

	//we add text to the center of the screen
	auto l_oLabel1 = Label::createWithTTF(m_pUser1->getPUserName(), "fonts/Marker Felt.ttf",20);
	l_oLabel1->setPosition(l_oVisibleSize.width/2+l_oOrigin.x,l_oVisibleSize.height/2+l_oOrigin.y);
	m_pUserLayer->addChild(l_oLabel1,1);
	char score[5];
	sprintf(score,"Score: %d",m_pUser1->getPScore());
	auto l_oLabel2 = Label::createWithTTF(score, "fonts/Marker Felt.ttf",20);
	l_oLabel2->setPosition(l_oVisibleSize.width/2+l_oOrigin.x,l_oVisibleSize.height*0.2);
	m_pUserLayer->addChild(l_oLabel2,1);

	return true;
}

bool LmGameManager::init()
{

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

	if(!initDashboard())
	{
		CCLOG("Init DashBoard failed");
		return false;
	}


	//init callback method of the custom event (use to know when an interactionScene want to communicate with this)
	auto InteractionSceneFinished = [=](EventCustom * event)
								{
		Director::getInstance()->replaceScene(TransitionFlipX::create(2,m_aInteractionSceneOfTheGame.at(0)));
								};

	//add the custom event to the event dispatcher
	Director::getInstance()->getEventDispatcher()->addCustomEventListener("InteractionSceneFinished",InteractionSceneFinished);

	return true;
}

void LmGameManager::runGame()
{
	//Init of the GameManager (resolution, vector of InteractionScene with server manager)
	init();

	//replace the menu scene with the first one of the game
	Director::getInstance()->replaceScene(m_pDashboardScene);

}
