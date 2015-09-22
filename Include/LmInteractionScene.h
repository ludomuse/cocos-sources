/*************************************************************************
                           LmInteractionScene  -  Generic step create an empty
                           layer create a simple scene
 *************************************************************************/
#ifndef LMINTERACTION_H__
#define LMINTERACTION_H__

#include "cocos2d.h"
#include "LmGameComponent.h"
#include "LmIntroduction.h"
#include "LmUser.h"

typedef std::map<int,LmGameComponent*>::iterator it_type;

static const float s_fDashboardRatioHidden = 0.95f;
static const float s_fTimeMovingDashboard = 0.5f;
static const float s_fMarginLeft = 30.0f;


class LmInteractionScene : public cocos2d::Scene
{
public:

	LmInteractionScene();
	~LmInteractionScene();

	//init
	bool init(LmUser*);

	bool isDone() const {return m_bDone;}

	void setBBackPressed(bool bBackPressed) {m_bBackPressed = bBackPressed;}

protected:

	//ATTRIBUTES

	//autorelease object it's the first layer of the scene
	cocos2d::Layer* m_pLayerGame;

	//layer of user parent or child
	cocos2d::Layer* m_pLayerUserParent;
	cocos2d::Layer* m_pLayerUserChild;

	//an introduction to the InteractionScene
	LmIntroduction* m_pLmIntroduction;

	cocos2d::Layer* m_pDashboardBandLayer;

	//user which play the scene to know if it's 1 or 2 init dashbord layer and modify his score
	LmUser* m_pUser;

	//gui elements
	cocos2d::Sprite* m_pSpriteDashboardBand;

	cocos2d::ui::Button* m_pMoveLayerButton;
	bool m_bMoveDone;
	bool m_bDone;

	cocos2d::Layer* m_pGuiElementsLayer;
	cocos2d::Label* m_pLabelUserName;
	cocos2d::Label* m_pLabelScore;
	cocos2d::ui::Button* m_pBackDashboardButton;

	bool m_bBackPressed;

	bool m_bActionRunning;

	std::map<int,LmGameComponent*> m_aIdTable;

	//METHODS

	//interface for all games where we init our games and so on
	virtual void runGame()=0;

	//add the dashboard layer
	void initDashboardLayer();

	void moveDashboardLayer();
	bool m_bDashboardIsHidden;
	void moveRightDone();
	void moveLeftDone();

	void backToDashboard();

};


#endif // LMINTERACTION_H__
