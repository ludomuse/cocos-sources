/*************************************************************************
                           LmGameManager  -  Manage all steps
 *************************************************************************/
#ifndef LMGAMEMANAGER_H__
#define LMGAMEMANAGER_H__

#include "cocos2d.h"
#include "LmServerManager.h"

//Differents Scene of the application
#include "LmInteractionScene.h"


class LmIntroductionScene;

//Different resolution
static cocos2d::Size s_DesignResolutionSize = cocos2d::Size(426, 320);
static cocos2d::Size s_SmallResolutionSize = cocos2d::Size(426, 320);
static cocos2d::Size s_MediumResolutionSize = cocos2d::Size(1024, 768);
static cocos2d::Size s_LargeResolutionSize = cocos2d::Size(2048, 1536);

class LmGameManager
{
private:

	std::vector<LmInteractionScene*> m_aInteractionSceneOfTheGame;

	//use to get the vector of interactionScene
	LmServerManager* m_pLmServerManager;

	//call server manager and init m_vectorSceneOfTheGame
	bool init();
	void initPathsForResolution();

public:

	LmGameManager();
	~LmGameManager();

	//call different method of gamemanager, init launch scene and handle layers of interactions
	void runGame();
};

#endif // LMGAMEMANAGER_H
