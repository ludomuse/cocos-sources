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
