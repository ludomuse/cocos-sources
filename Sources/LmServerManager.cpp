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
	return m_pLmJsonparser->getAInteractionSceneOfTheGame();
}

std::string LmServerManager::getSTitleApplication()
{
	return m_pLmJsonparser->getSTitleApplication();
}

