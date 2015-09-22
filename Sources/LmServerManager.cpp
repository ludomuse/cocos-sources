//use for the debug
#define COCOS2D_DEBUG 1

#include "../Include/LmServerManager.h"

LmServerManager::LmServerManager()
{
	m_pLmJsonparser = new LmJsonParser;
}

LmServerManager::~LmServerManager()
{
	delete m_pLmJsonparser;
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

		//m_aInteractionSceneOfTheGame.push_back(m_pLmJsonparser->makeInteractionScene(l_iIdScene));

		m_pLmJsonparser->moveToTheNextScene();
	}

	//test
	m_aInteractionSceneOfTheGame.push_back(new LmPuzzleScene(1));

	return m_aInteractionSceneOfTheGame;
}

std::string LmServerManager::getSTitleApplication()
{
	return m_pLmJsonparser->getSTitleApplication();
}

