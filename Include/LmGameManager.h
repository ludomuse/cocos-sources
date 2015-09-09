/*************************************************************************
                           LmGameManager  -  Manage all steps
 *************************************************************************/
#ifndef LMGAMEMANAGER_H__
#define LMGAMEMANAGER_H__

#include "cocos2d.h"
#include "LmServerManager.h"

//Differents Scene of the application
#include "LmInteractionScene.h"

//Different resolution
static cocos2d::Size s_DesignResolutionSize = cocos2d::Size(480, 300);
static cocos2d::Size s_SmallResolutionSize = cocos2d::Size(480, 300);
static cocos2d::Size s_MediumResolutionSize = cocos2d::Size(1280, 800);
static cocos2d::Size s_LargeResolutionSize = cocos2d::Size(1900, 1200);

class LmGameManager
{
private:

	std::vector<LmInteractionScene*> m_aInteractionSceneOfTheGame;

	//use to get the vector of interactionScene
	LmServerManager* m_pLmServerManager;

	//call server manager and init m_vectorSceneOfTheGame
	bool init();

public:

	LmGameManager();
	~LmGameManager();

	//call different method of gamemanager, init launch scene and handle layers of interactions
	void runGame();
};

#endif // LMGAMEMANAGER_H
