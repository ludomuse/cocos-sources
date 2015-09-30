/*************************************************************************
 LmGameManager  -  Manage all steps
 *************************************************************************/
#ifndef LMGAMEMANAGER_H__
#define LMGAMEMANAGER_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "LmServerManager.h"
#include "LmUser.h"
#include "LmInteractionScene.h"

static const float s_fMagingOfSpriteBackgroundUser2Profile = 0.4f;
static const float s_fTimeCompareAction = 0.5f;
static const float s_fMarginBetweenInteraction = 100.0f;

class LmGameManager
{
private:

	//ATTRIBUTES

	//layer splash
	cocos2d::Layer* m_pSplashSreenLayer;

	std::vector<LmInteractionScene*> m_aInteractionSceneOfTheGame;

	//use to get the vector of interactionScene
	LmServerManager* m_pLmServerManager;

	//both users (1=local & 2=2nd user) get via LmMenu
	LmUser* m_pUser1;
	LmUser* m_pUser2;

	//scene of the dashboard
	cocos2d::Scene* m_pGameManagerScene;

	//layer of dashboard
	cocos2d::Layer* m_pBlueLayer;
	cocos2d::Layer* m_pPinkLayer;

	cocos2d::ui::ScrollView* m_pScrollView;

	//dashboard GUI elements
	cocos2d::Sprite* m_pSpriteBackgroundBlue;
	cocos2d::Sprite* m_pSpriteBackgroundPink;

	cocos2d::Sprite* m_pSpriteBandMid;
	cocos2d::Sprite* m_pSpriteBandTop;

	cocos2d::Sprite* m_pSpriteBackgroundBlueProfile;
	cocos2d::Sprite* m_pSpriteBackgroundPinkProfile;

	cocos2d::Label* m_pLabelUser1Name;
	cocos2d::Label* m_pLabelScore;
	cocos2d::Label* m_pLabelInteractionDone;
	cocos2d::Label* m_pLabelTitleApplication;
	std::string m_sTitleApplication;

	cocos2d::ui::Button* m_pCompareButton;
	cocos2d::Label* m_pLabelCompareButton;
	cocos2d::ui::Button* m_pBackButton;
	cocos2d::ui::Button* m_pPlayNextInteractionButton;

	//vector interaction sprite
	std::vector<cocos2d::Sprite*> m_aSpritesInteractions;

	//to know how many interaction have been played
	int m_iIndexInteractionScene;

	//to know how many inetraction done
	int m_iInteractionDone;

	//to know if it's a back to the dashboard or its interactionscenefinished
	bool m_bBackToDashboard;

	//listener
	cocos2d::EventListenerTouchOneByOne* m_pListener;

	//METHODS

	//call server manager and init m_vectorSceneOfTheGame
	bool init();

	//callback methods
	void compare();
	void compareDone();
	void back();
	void backDone();

	void runNextInteraction();

	//bool to sync when compare button is pushed
	bool m_bActionIsDone;

	//init the dashboard
	bool initDashboard();

	//init splash screen
	bool initSplashScreen();

	//put interaction sprite on the dashboard
	void initDashboardInteraction();

	//update dashboard after each interactionscene
	void updateDashboard();

	//remove listeners avoid conflict between scene true = remove false = add
	void removeListeners(bool);

	//callback method for the layer splash
	bool onTouchBeganSplashScreen(cocos2d::Touch*, cocos2d::Event*);

public:

	LmGameManager();
	~LmGameManager();

	//call different method of gamemanager, init launch scene and handle layers of interactions
	void runGame();

	void setPUser1(LmUser* pUser1)
	{
		m_pUser1 = pUser1;
	}

	void setPUser2(LmUser* pUser2)
	{
		m_pUser2 = pUser2;
	}

};

#endif // LMGAMEMANAGER_H
