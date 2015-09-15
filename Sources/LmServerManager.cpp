//use for the debug
#define COCOS2D_DEBUG 1

#include "../Include/LmServerManager.h"

LmServerManager::LmServerManager()
{
	m_pLmJsonparser = new LmJsonParser;
	m_pLmFactory = new LmFactory;
}

LmServerManager::~LmServerManager()
{
	delete m_pLmJsonparser;
	delete m_pLmFactory;
}

bool LmServerManager::init()
{
	bool l_bInit;

	if(m_pLmJsonparser->initJsonDocument("json/document.json"))
	{
		l_bInit = true;
	}
	else
	{
		l_bInit = false;
	}

	return l_bInit;
}

std::vector<LmInteractionScene*> LmServerManager::getInteractionSceneOfTheGame()
{

	while(m_pLmJsonparser->thereIsAnotherInteractionScene())
	{
		//get type and values of that scene and then pass it to the factory which create the scene then push back to the return value

		int l_iIdScene = m_pLmJsonparser->getIdInteractionScene();

		CCLOG("Scene id = %d",l_iIdScene);

		m_pLmJsonparser->moveToTheNextScene();
	}

	//test
	m_aInteractionSceneOfTheGame.push_back(new LmPuzzleScene(1));
	m_aInteractionSceneOfTheGame.push_back(new LmPuzzleScene(2));
	m_aInteractionSceneOfTheGame.push_back(new LmPuzzleScene(3));
	m_aInteractionSceneOfTheGame.push_back(new LmPuzzleScene(4));
	m_aInteractionSceneOfTheGame.push_back(new LmPuzzleScene(5));
	m_aInteractionSceneOfTheGame.push_back(new LmPuzzleScene(6));
	m_aInteractionSceneOfTheGame.push_back(new LmPuzzleScene(7));



	return m_aInteractionSceneOfTheGame;
}

const char* LmServerManager::getSTitleApplication()
{
	return m_pLmJsonparser->getSTitleApplication();
}

