//use for the debug
#define COCOS2D_DEBUG 1

#include "../Include/LmInteractionScene.h"

USING_NS_CC;

LmInteractionScene::LmInteractionScene()
{
	//object ludomuse
	m_pLmSetPointBegin = new LmSetPoint; //need to be delete
	m_pLmSetPointEnd = new LmSetPoint; //need to be delete
	m_pLmReward = nullptr;

	//primitive type
	m_bDone = false;
	m_bActionRunning = false;
	m_bDashboardIsHidden = true;
	m_bMoveDone = true;
	m_bBackPressed = false;
	m_iNumberOfGameComponent = 0;
	m_bFinishGameButtonSync = true;
	m_bReplayButtonSync = true;
	m_bSetPointBegin = true;
	m_bSetPointFinished = false;
	m_bWin = false;

	//pointer
	m_pBackDashboardButton = nullptr;
	m_pUser = nullptr;
	m_pDashboardBandLayer = nullptr;
	m_pMoveLayerButton = nullptr;
	m_pLayerGame = nullptr;
	m_pLabelScore = nullptr;
	m_pLabelUserName = nullptr;
	m_pSpriteDashboardBand = nullptr;
	m_pFinishGameButton = nullptr;
	m_pReplayButton = nullptr;
	m_pSendingArea = nullptr;
	m_pNextButton = nullptr;
	m_pPreviousButton = nullptr;

}

LmInteractionScene::~LmInteractionScene()
{
	//if this scene own a reward delete it
	if (m_pLmReward)
	{
		delete m_pLmReward;
	}

	m_pLayerGame->release();
	m_pNextButton->release();
	m_pPreviousButton->release();

	delete m_pLmSetPointBegin;
	delete m_pLmSetPointEnd;

}

bool LmInteractionScene::init(LmUser* l_pUser)
{

	//init user
	m_pUser = l_pUser;

	initDashboardLayer();
	if (!m_pLmSetPointBegin->init(this))
	{
		CCLOG("LmSetPoint init failed");
		return false;
	}

	//use to place elements
	Size l_oVisibleSize = Director::getInstance()->getVisibleSize();
	Point l_oOrigin = Director::getInstance()->getVisibleOrigin();

	//next button
	m_pNextButton = ui::Button::create("GUIElements/nextButtonNormal.png",
			"GUIElements/nextButtonPressed.png");
	m_pNextButton->setTouchEnabled(true);
	m_pNextButton->setPosition(
			Vect(
					l_oVisibleSize.width
							- m_pNextButton->getContentSize().width * 0.8,
					m_pNextButton->getContentSize().height * 0.7));
	m_pNextButton->addTouchEventListener(
			CC_CALLBACK_0(LmInteractionScene::nextSetPointLayer, this));
	m_pNextButton->retain();
	addChild(m_pNextButton, 1);

	//previous button
	m_pPreviousButton = ui::Button::create("GUIElements/previousButtonNormal.png",
			"GUIElements/previousButtonPressed.png");
	m_pPreviousButton->setTouchEnabled(true);
	m_pPreviousButton->setPosition(
			Vect(m_pPreviousButton->getContentSize().width * 0.8,
					m_pPreviousButton->getContentSize().height * 0.7));
	m_pPreviousButton->addTouchEventListener(
			CC_CALLBACK_0(LmInteractionScene::previousSetPointLayer, this));
	m_pPreviousButton->setVisible(false);
	m_pPreviousButton->retain();
	addChild(m_pPreviousButton, 1);

	//create the game layer
	m_pLayerGame = Layer::create();
	m_pLayerGame->retain();

	//finish button
	m_pFinishGameButton = ui::Button::create("GUIElements/nextButtonNormal.png",
			"GUIElements/nextButtonPressed.png");

	//if there is a reward we init the button with the appropriate sprite
	if (m_pLmReward)
	{
		//init sprite reward
		m_pLmReward->init();
		//init background button
		m_pFinishGameButton->loadTextures(
				m_pLmReward->getSFilenameSpriteBackground(),
				m_pLmReward->getSFilenameSpriteBackground(),
				m_pLmReward->getSFilenameSpriteBackground());
		//add the sprite to the button
		m_pLmReward->getPSpriteReward()->setPosition(
				Vec2(l_oVisibleSize.width * 0.5 + l_oOrigin.x,
						l_oVisibleSize.height * 0.5 + l_oOrigin.y));
		m_pFinishGameButton->addChild(m_pLmReward->getPSpriteReward());
	}

	m_pFinishGameButton->setTouchEnabled(true);
	m_pFinishGameButton->setPosition(
			Vect(l_oVisibleSize.width * 0.5 + l_oOrigin.x,
					l_oVisibleSize.height * 0.5 + l_oOrigin.y));
	m_pFinishGameButton->addTouchEventListener(
			CC_CALLBACK_0(LmInteractionScene::endGame, this));
	m_pFinishGameButton->setVisible(false);
	m_pLayerGame->addChild(m_pFinishGameButton, 1);

	//replay button
	m_pReplayButton = ui::Button::create("GUIElements/answerBackground.png",
			"GUIElements/answerBackgroundSelected.png");

	m_pReplayButton->setTouchEnabled(true);
	m_pReplayButton->setPosition(
			Vect(l_oVisibleSize.width * 0.5 + l_oOrigin.x,
					l_oVisibleSize.height * 0.3 + l_oOrigin.y));
	m_pReplayButton->addTouchEventListener(
			CC_CALLBACK_0(LmInteractionScene::resetScene, this));
	m_pReplayButton->setVisible(false);
	m_pLayerGame->addChild(m_pReplayButton, 1);

	return true;
}

void LmInteractionScene::previousSetPointLayer()
{

	if (m_bSetPointBegin)
	{
		if (m_pLmSetPointBegin->previousLayer())
		{
			if (m_pLmSetPointBegin->getIIndex() == 0)
			{
				m_pPreviousButton->setVisible(false);
			}
		}
	}
	else
	{
		if (m_pLmSetPointEnd->previousLayer())
		{
			if (m_pLmSetPointEnd->getIIndex() == 0)
			{
				m_pPreviousButton->setVisible(false);
			}
		}
	}
}

void LmInteractionScene::nextSetPointLayer()
{

	if (m_bSetPointBegin)
	{
		//false => setpoint begin is finished
		if (!m_pLmSetPointBegin->nextLayer()
				&& m_pLmSetPointBegin->isBActionDone() && !m_bSetPointFinished)
		{
			m_bSetPointFinished = true;
			m_pNextButton->setVisible(false);
			m_pPreviousButton->setVisible(false);

			runGame();
		}
		else
		{
			if (m_pLmSetPointBegin->getIIndex() > 0 && !m_bSetPointFinished)
			{
				m_pPreviousButton->setVisible(true);
			}
		}

	}
	else
	{
		//false => setpoint end is finished
		if (!m_pLmSetPointEnd->nextLayer() && m_pLmSetPointEnd->isBActionDone()
				&& !m_bSetPointFinished)
		{
			m_bSetPointFinished = true;
			m_pNextButton->setVisible(false);
			m_pPreviousButton->setVisible(false);
			//finish the interaction
			CCLOG("popscene");
			Director::getInstance()->popScene();
			Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(
					"InteractionSceneFinished");
		}
		else
		{
			if (m_pLmSetPointEnd->getIIndex() > 0 && !m_bSetPointFinished)
			{
				m_pPreviousButton->setVisible(true);
			}
		}
	}

}

void LmInteractionScene::initDashboardLayer()
{
	//use to place elements
	Size l_oVisibleSize = Director::getInstance()->getVisibleSize();
	Point l_oOrigin = Director::getInstance()->getVisibleOrigin();

	//layer
	m_pDashboardBandLayer = Layer::create();
	this->addChild(m_pDashboardBandLayer, 2);

	//spritebackground
	m_pSpriteDashboardBand = LmSprite::create(
			"GUIElements/spriteBackgroundUser1Profile.png");
	m_pSpriteDashboardBand->setAnchorPoint(Vec2(0, 0));
	m_pSpriteDashboardBand->setPosition(Vec2(0, 0));
	m_pDashboardBandLayer->addChild(m_pSpriteDashboardBand, 0);

	//button to move the layer
	m_pMoveLayerButton = ui::Button::create("GUIElements/moveDashboardLayer.png");
	m_pMoveLayerButton->setTouchEnabled(true);
	m_pMoveLayerButton->setPosition(
			Vec2(m_pSpriteDashboardBand->getContentSize().width,
					l_oVisibleSize.height * 0.5f));
	m_pMoveLayerButton->addTouchEventListener(
			CC_CALLBACK_0(LmInteractionScene::moveDashboardLayer, this));
	m_pDashboardBandLayer->addChild(m_pMoveLayerButton, 0);

	//user1 name
	m_pLabelUserName = Label::createWithTTF(m_pUser->getPUserName(),
			"fonts/JosefinSans-Regular.ttf", l_oVisibleSize.width*0.04);
	m_pLabelUserName->setPosition(
			m_pSpriteDashboardBand->getContentSize().width * (0.5f),
			m_pSpriteDashboardBand->getContentSize().height * 0.7f);
	m_pDashboardBandLayer->addChild(m_pLabelUserName);

	//label score
	char l_aScoreString[10];
	sprintf(l_aScoreString, "%d pts", m_pUser->getPScore());
	m_pLabelScore = Label::createWithTTF(l_aScoreString,
			"fonts/JosefinSans-Regular.ttf", l_oVisibleSize.width*0.04);
	m_pLabelScore->setPosition(
			m_pSpriteDashboardBand->getContentSize().width * (0.5f),
			m_pSpriteDashboardBand->getContentSize().height * 0.5f);
	m_pDashboardBandLayer->addChild(m_pLabelScore);

	m_pBackDashboardButton = ui::Button::create("GUIElements/backToDashboard.png");
	m_pBackDashboardButton->setTouchEnabled(true);
	m_pBackDashboardButton->setPosition(
			Vec2(m_pSpriteDashboardBand->getContentSize().width * (0.5f),
					m_pSpriteDashboardBand->getContentSize().height * 0.3f));
	m_pBackDashboardButton->addTouchEventListener(
			CC_CALLBACK_0(LmInteractionScene::backToDashboard, this));
	m_pDashboardBandLayer->addChild(m_pBackDashboardButton);

	//hide it
	auto l_oMoveLeftAction = MoveBy::create(0,
			Vect(
					(-1) * s_fDashboardRatioHidden
							* m_pSpriteDashboardBand->getContentSize().width,
					0));
	m_pDashboardBandLayer->runAction(l_oMoveLeftAction);

	m_pSpriteDashboardBand->setBTouchEnabled(!m_bDashboardIsHidden);

}

void LmInteractionScene::moveDashboardLayer()
{
	if (m_bMoveDone)
	{
		m_bMoveDone = false;

		//we look if we have to move right or left
		if (m_bDashboardIsHidden)
		{
			auto l_oMoveRightAction =
					MoveBy::create(s_fTimeMovingDashboard,
							Vect(
									s_fDashboardRatioHidden
											* m_pSpriteDashboardBand->getContentSize().width,
									0));
			auto l_oMoveRightActionDone = CallFunc::create(
					std::bind(&LmInteractionScene::moveRightDone, this));
			m_pDashboardBandLayer->runAction(
					Sequence::create(l_oMoveRightAction, l_oMoveRightActionDone,
							nullptr));
			m_bDashboardIsHidden = false;
			m_pSpriteDashboardBand->setBTouchEnabled(!m_bDashboardIsHidden);
		}
		else
		{
			auto l_oMoveLeftAction =
					MoveBy::create(s_fTimeMovingDashboard,
							Vect(
									(-1) * s_fDashboardRatioHidden
											* m_pSpriteDashboardBand->getContentSize().width,
									0));
			auto l_oMoveLeftActionDone = CallFunc::create(
					std::bind(&LmInteractionScene::moveLeftDone, this));
			m_pDashboardBandLayer->runAction(
					Sequence::create(l_oMoveLeftAction, l_oMoveLeftActionDone,
							nullptr));
			m_bDashboardIsHidden = true;
			m_pSpriteDashboardBand->setBTouchEnabled(!m_bDashboardIsHidden);
		}

	}

}

void LmInteractionScene::moveRightDone()
{
	//enable back button
	m_bBackPressed = false;

	//active button
	m_bMoveDone = true;

}

void LmInteractionScene::moveLeftDone()
{
	//disable back button
	m_bBackPressed = true;

	//active button
	m_bMoveDone = true;

}

void LmInteractionScene::backToDashboard()
{
	if (!m_bBackPressed && m_bMoveDone && m_pLmSetPointBegin->isBActionDone())
	{
		m_bBackPressed = true;

		CCLOG("popscene");
		Director::getInstance()->popScene();
		Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(
				"BackToDashboard");
	}
}

LmGameComponent* LmInteractionScene::makeGameComponent()
{
	//generate a new id
	m_iNumberOfGameComponent++;
	//register it into the id table
	m_aIdTable.insert(
			std::pair<int, LmGameComponent*>(m_iNumberOfGameComponent,
					new LmGameComponent(m_iNumberOfGameComponent)));

	return m_aIdTable.find(m_iNumberOfGameComponent)->second;
}

void LmInteractionScene::endGame()
{
	if (m_bFinishGameButtonSync)
	{
		m_bFinishGameButtonSync = false;

		//if there is a reward we add score reward to the score of the user
		if (m_pLmReward && m_bWin)
		{
			m_pUser->addToScore(m_pLmReward->getIRewardScore());
		}

		//the game is finished we can remove the layer of the game
		removeChild(m_pLayerGame);

		//so the next time we print the end setpoint
		m_bSetPointBegin = false;
		//new setpoint
		m_bSetPointFinished = false;

		m_pNextButton->setVisible(true);
		m_pPreviousButton->setVisible(false);

		//init the end set point
		if (!m_pLmSetPointEnd->init(this))
		{
			CCLOG("LmSetPoint init failed");
		}

	}
}

