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

	if (m_pLmJsonparser->initJsonDocument("json/document.json"))
	{
		l_bInit = true;
	}
	else
	{
		l_bInit = false;
	}

	return l_bInit;
}

std::vector<LmInteractionScene*> LmServerManager::getInteractionSceneOfTheGame(bool l_bIsParent)
{
	return m_pLmJsonparser->getAInteractionSceneOfTheGame(l_bIsParent);
}

std::string LmServerManager::getSTitleApplication()
{
	return m_pLmJsonparser->getSTitleApplication();
}

std::string LmServerManager::getSFilenameSpriteSplashScreen()
{
	return m_pLmJsonparser->getSFilenameSpriteSplashScreen();
}

