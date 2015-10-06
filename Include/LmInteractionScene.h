/*************************************************************************
 LmInteractionScene  -  Generic step create an empty
 layer create a simple scene
 *************************************************************************/
#ifndef LMINTERACTION_H__
#define LMINTERACTION_H__

#include "cocos2d.h"
#include "LmGameComponent.h"
#include "LmSetPoint.h"
#include "LmUser.h"
#include "LmSprite.h"
#include "LmReward.h"

typedef std::map<int, LmGameComponent*>::iterator it_type;

static const float s_fDashboardRatioHidden = 0.95f;
static const float s_fTimeMovingDashboard = 0.4f;
static const float s_fMarginLeft = 150.0f;
static const float s_fMarginBot = 20.0f;

//margiin between image when images has to be display
static const float s_fMarginBetweenImage = 20.0f;

class LmInteractionScene: public cocos2d::Scene
{

public:

	LmInteractionScene();
	virtual ~LmInteractionScene();

	//in case we need to do stuff when we get the focus again after a back
	virtual void restart()=0;

	//call by replay button
	virtual void resetScene()=0;

	//init
	bool init(LmUser*);

	bool isDone() const
	{
		return m_bDone;
	}

	void setBBackPressed(bool bBackPressed)
	{
		m_bBackPressed = bBackPressed;
	}

	void setPLmSetPointEnd(LmSetPoint* pLmSetPoint)
	{
		m_pLmSetPointEnd = pLmSetPoint;
	}

	void setPLmSetPointBegin(LmSetPoint* pLmSetPoint)
	{
		m_pLmSetPointBegin = pLmSetPoint;
	}

	void setPLmReward(LmReward* pLmReward)
	{
		m_pLmReward = pLmReward;
	}

protected:

	//ATTRIBUTES

	//to know if this has been win
	bool m_bWin;

	//reward
	LmReward* m_pLmReward;

	//sending area
	LmGameComponent* m_pSendingArea;

	//autorelease object it's the first layer of the scene
	cocos2d::Layer* m_pLayerGame;

	//an introduction to the InteractionScene
	LmSetPoint* m_pLmSetPointBegin;
	LmSetPoint* m_pLmSetPointEnd;

	cocos2d::Layer* m_pDashboardBandLayer;

	//user which play the scene to know if it's 1 or 2 init dashbord layer and modify his score
	LmUser* m_pUser;

	//finish button
	cocos2d::ui::Button* m_pFinishGameButton;
	bool m_bFinishGameButtonSync;

	//replay button
	cocos2d::ui::Button* m_pReplayButton;
	bool m_bReplayButtonSync;

	//introduction gui element
	//buttons next and previous
	cocos2d::ui::Button* m_pNextButton;
	cocos2d::ui::Button* m_pPreviousButton;
	//to know when a set point is finish
	bool m_bSetPointFinished;
	//to know if next button pass through the begion set point begin or other one
	bool m_bSetPointBegin;

	//gui elements
	LmSprite* m_pSpriteDashboardBand;

	cocos2d::ui::Button* m_pMoveLayerButton;
	bool m_bMoveDone;
	bool m_bDone;

	cocos2d::Label* m_pLabelUserName;
	cocos2d::Label* m_pLabelScore;
	cocos2d::ui::Button* m_pBackDashboardButton;

	bool m_bBackPressed;

	bool m_bActionRunning;

	std::map<int, LmGameComponent*> m_aIdTable;

	int m_iNumberOfGameComponent;

	bool m_bDashboardIsHidden;

	//METHODS

	//callback
	void nextSetPointLayer();
	void previousSetPointLayer();

	//interface for all games where we init our games and so on
	virtual void runGame()=0;

	//init the game
	virtual bool initGame()=0;

	//add the dashboard layer
	void initDashboardLayer();

	void moveDashboardLayer();
	void moveRightDone();
	void moveLeftDone();

	void backToDashboard();

	//register the gamecomponent and return a pointer to it
	LmGameComponent* makeGameComponent();

	//call when the finishgamebutton is pressed
	void endGame();

};

#endif // LMINTERACTION_H__
