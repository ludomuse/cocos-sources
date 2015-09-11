/*************************************************************************
                           LmGameManager  -  Manage all steps
 *************************************************************************/
#ifndef LMGAMEMANAGER_H__
#define LMGAMEMANAGER_H__

#include "cocos2d.h"
#include "LmServerManager.h"
#include "LmUser.h"

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

	//both users (1=local & 2=2nd user) get via LmMenu
	LmUser* m_pUser1;
	LmUser* m_pUser2;

	//scene of the dashboard
	cocos2d::Scene* m_pDashboardScene;

	//layer of user profile
	cocos2d::Layer* m_pUserLayer;

	//init the dashboard
	bool initDashboard();

public:

	LmGameManager();
	~LmGameManager();

	//call different method of gamemanager, init launch scene and handle layers of interactions
	void runGame();

	void setPUser1( LmUser* pUser1) {
		m_pUser1 = pUser1;
	}

	void setPUser2( LmUser* pUser2) {
		m_pUser2 = pUser2;
	}
};

#endif // LMGAMEMANAGER_H
