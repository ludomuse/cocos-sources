/*
 * LmQuizz_v1.cpp
 *
 *  Created on: 24 sept. 2015
 *      Author: IHMTEKDev4
 */

#include "../Include/LmQuizz_v1Scene.h"

using namespace cocos2d;
using namespace cocos2d::ui;

LmQuizz_v1Scene::LmQuizz_v1Scene(std::string l_sFilenameSpriteBackground,
		std::string l_sFilenameSpriteBandTop,
		std::string l_sFilenameSpriteAnswerBackground,
		std::string l_sFilenameSpriteAnswerCross,
		std::string l_sFilenameSpriteGoodAnswerButton,
		std::string l_sFilenameSpriteBadAnswerButton,
		std::vector<LmQuestion*> l_aQuestions, int l_iAttemptByQuestion,
		float l_fTimerDuration, bool l_bTimerEnbaled) :
		LmInteractionScene()
{

	//json
	m_sFilenameSpriteBackground = l_sFilenameSpriteBackground;
	m_sFilenameSpriteBandTop = l_sFilenameSpriteBandTop;
	m_sFilenameSpriteAnswerBackground = l_sFilenameSpriteAnswerBackground;
	m_sFilenameSpriteAnswerCross = l_sFilenameSpriteAnswerCross;
	m_aQuestions = l_aQuestions;
	m_iAttemptByQuestion = l_iAttemptByQuestion;
	m_fTimerDuration = l_fTimerDuration;
	m_bTimerEnbaled = l_bTimerEnbaled;
	m_sFilenameSpriteGoodAnswerButton = l_sFilenameSpriteGoodAnswerButton;
	m_sFilenameSpriteBadAnswerButton = l_sFilenameSpriteBadAnswerButton;

	//pointer
	m_pSpriteBackground = nullptr;
	m_pTimer = nullptr;
	m_pNextQuestionButton = nullptr;
	m_pAnswerLabel1 = nullptr;
	m_pAnswerLabel2 = nullptr;
	m_pAnswerLabel3 = nullptr;
	m_pAnswerLabel4 = nullptr;
	m_pQuestionLabel = nullptr;
	m_pBandTopSprite = nullptr;
	m_pCheckBoxAnswer1 = nullptr;
	m_pCheckBoxAnswer2 = nullptr;
	m_pCheckBoxAnswer3 = nullptr;
	m_pCheckBoxAnswer4 = nullptr;

	//primitive type
	m_iCounter = 0;
	m_iAnswerSelected = -1;
	m_fHeight = 0;
	m_iIndexQuestion = -1;
	m_iNumberOfAttempt = m_iAttemptByQuestion;
	m_bNextQuestionButtonCanBePress = true;
}

LmQuizz_v1Scene::~LmQuizz_v1Scene()
{
	for (std::vector<LmQuestion*>::iterator it = m_aQuestions.begin();
			it != m_aQuestions.end(); ++it)
	{
		delete (*it);
	}
}

void LmQuizz_v1Scene::runGame()
{
	initGame();
	//we preload the sound
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic(
			"audio/son.mp3");
}

bool LmQuizz_v1Scene::initGame()
{

	//use to place elements
	Size l_oVisibleSize = Director::getInstance()->getVisibleSize();
	Point l_oOrigin = Director::getInstance()->getVisibleOrigin();

	//add the layer game
	this->addChild(m_pLayerGame, 0);

	//init the background
	m_pSpriteBackground = Sprite::create(m_sFilenameSpriteBackground);
	m_pSpriteBackground->setPosition(l_oVisibleSize.width * 0.5f + l_oOrigin.x,
			l_oVisibleSize.height * 0.5f + l_oOrigin.y);
	m_pLayerGame->addChild(m_pSpriteBackground);

	//init timer
	m_pTimer = LoadingBar::create();
	m_pTimer->setName("LoadingBar");
	m_pTimer->loadTexture("bandMid.png");
	m_pTimer->setPercent(0);
	m_pTimer->setPosition(
			Point(l_oVisibleSize.width * 0.5f + l_oOrigin.x,
					l_oVisibleSize.height * 0.05 + l_oOrigin.y));
	if (m_bTimerEnbaled)
	{
		m_pLayerGame->addChild(m_pTimer, 1);
	}

	//band top sprite
	m_pBandTopSprite = Sprite::create(m_sFilenameSpriteBandTop);
	m_pBandTopSprite->setAnchorPoint(Vec2(0, 1));
	m_pBandTopSprite->setPosition(Vec2(0, l_oVisibleSize.height + l_oOrigin.y));
	m_pLayerGame->addChild(m_pBandTopSprite);

	//usefull height to scale
	m_fHeight = l_oVisibleSize.height
			- m_pBandTopSprite->getContentSize().height
			- m_pTimer->getContentSize().height;

	//menuitem answer create + set position
	//1
	m_pCheckBoxAnswer1 = CheckBox::create(m_sFilenameSpriteAnswerBackground,
			m_sFilenameSpriteAnswerCross);
	m_pCheckBoxAnswer1->setTouchEnabled(true);
	m_pCheckBoxAnswer1->setSwallowTouches(false);
	m_pCheckBoxAnswer1->setPosition(
			Vec2(l_oVisibleSize.width * 0.25,
					m_fHeight * 0.75f + m_pTimer->getContentSize().height));
	m_pCheckBoxAnswer1->addEventListener(
			CC_CALLBACK_2(LmQuizz_v1Scene::answerSelected, this));
	m_pLayerGame->addChild(m_pCheckBoxAnswer1);
	//2
	m_pCheckBoxAnswer2 = CheckBox::create(m_sFilenameSpriteAnswerBackground,
			m_sFilenameSpriteAnswerCross);
	m_pCheckBoxAnswer2->setTouchEnabled(true);
	m_pCheckBoxAnswer2->setSwallowTouches(false);
	m_pCheckBoxAnswer2->setPosition(
			Vec2(l_oVisibleSize.width * 0.75,
					m_fHeight * 0.75f + m_pTimer->getContentSize().height));
	m_pCheckBoxAnswer2->addEventListener(
			CC_CALLBACK_2(LmQuizz_v1Scene::answerSelected, this));
	m_pLayerGame->addChild(m_pCheckBoxAnswer2);
	//3
	m_pCheckBoxAnswer3 = CheckBox::create(m_sFilenameSpriteAnswerBackground,
			m_sFilenameSpriteAnswerCross);
	m_pCheckBoxAnswer3->setTouchEnabled(true);
	m_pCheckBoxAnswer3->setSwallowTouches(false);
	m_pCheckBoxAnswer3->setPosition(
			Vec2(l_oVisibleSize.width * 0.25,
					m_fHeight * 0.25f + m_pTimer->getContentSize().height));
	m_pCheckBoxAnswer3->addEventListener(
			CC_CALLBACK_2(LmQuizz_v1Scene::answerSelected, this));
	m_pLayerGame->addChild(m_pCheckBoxAnswer3);
	//4
	m_pCheckBoxAnswer4 = CheckBox::create(m_sFilenameSpriteAnswerBackground,
			m_sFilenameSpriteAnswerCross);
	m_pCheckBoxAnswer4->setTouchEnabled(true);
	m_pCheckBoxAnswer4->setSwallowTouches(false);
	m_pCheckBoxAnswer4->setPosition(
			Vec2(l_oVisibleSize.width * 0.75,
					m_fHeight * 0.25f + m_pTimer->getContentSize().height));
	m_pCheckBoxAnswer4->addEventListener(
			CC_CALLBACK_2(LmQuizz_v1Scene::answerSelected, this));
	m_pLayerGame->addChild(m_pCheckBoxAnswer4);

	//init label question
	m_pQuestionLabel = Label::createWithTTF("", "fonts/JosefinSans-Regular.ttf",
			20);
	m_pBandTopSprite->addChild(m_pQuestionLabel);
	m_pQuestionLabel->setPosition(
			Vec2(m_pBandTopSprite->getContentSize().width * 0.5,
					m_pBandTopSprite->getContentSize().height * 0.5));
	m_pQuestionLabel->setColor(Color3B::BLACK);
	m_pQuestionLabel->setMaxLineWidth(l_oVisibleSize.width * 0.9);

	//init label answer and add them to their menuitemiamge
	//1
	m_pAnswerLabel1 = Label::createWithTTF("", "fonts/JosefinSans-Regular.ttf",
			20);
	m_pCheckBoxAnswer1->addChild(m_pAnswerLabel1);
	m_pAnswerLabel1->setPosition(
			Vec2(m_pCheckBoxAnswer1->getContentSize().width * 0.5,
					m_pCheckBoxAnswer1->getContentSize().height * 0.5));
	m_pAnswerLabel1->setColor(Color3B::BLACK);
	m_pAnswerLabel1->setMaxLineWidth(
			m_pCheckBoxAnswer1->getContentSize().width * 0.9);
	//2
	m_pAnswerLabel2 = Label::createWithTTF("", "fonts/JosefinSans-Regular.ttf",
			20);
	m_pCheckBoxAnswer2->addChild(m_pAnswerLabel2);
	m_pAnswerLabel2->setPosition(
			Vec2(m_pCheckBoxAnswer2->getContentSize().width * 0.5,
					m_pCheckBoxAnswer2->getContentSize().height * 0.5));
	m_pAnswerLabel2->setColor(Color3B::BLACK);
	m_pAnswerLabel2->setMaxLineWidth(
			m_pCheckBoxAnswer2->getContentSize().width * 0.9);
	//3
	m_pAnswerLabel3 = Label::createWithTTF("", "fonts/JosefinSans-Regular.ttf",
			20);
	m_pCheckBoxAnswer3->addChild(m_pAnswerLabel3);
	m_pAnswerLabel3->setPosition(
			Vec2(m_pCheckBoxAnswer3->getContentSize().width * 0.5,
					m_pCheckBoxAnswer3->getContentSize().height * 0.5));
	m_pAnswerLabel3->setColor(Color3B::BLACK);
	m_pAnswerLabel3->setMaxLineWidth(
			m_pCheckBoxAnswer3->getContentSize().width * 0.9);
	//4
	m_pAnswerLabel4 = Label::createWithTTF("", "fonts/JosefinSans-Regular.ttf",
			20);
	m_pCheckBoxAnswer4->addChild(m_pAnswerLabel4);
	m_pAnswerLabel4->setPosition(
			Vec2(m_pCheckBoxAnswer4->getContentSize().width * 0.5,
					m_pCheckBoxAnswer4->getContentSize().height * 0.5));
	m_pAnswerLabel4->setColor(Color3B::BLACK);
	m_pAnswerLabel4->setMaxLineWidth(
			m_pCheckBoxAnswer4->getContentSize().width * 0.9);

	//init next question button
	m_pNextQuestionButton = ui::Button::create("nextButtonNormal.png",
			"nextButtonPressed.png");
	m_pNextQuestionButton->setTouchEnabled(true);
	m_pNextQuestionButton->setPosition(
			Vec2(l_oVisibleSize.width * 0.5, l_oVisibleSize.height * 0.5));
	m_pNextQuestionButton->addTouchEventListener(
			CC_CALLBACK_0(LmQuizz_v1Scene::beginQuestion, this));
	m_pNextQuestionButton->setVisible(false);
	m_pLayerGame->addChild(m_pNextQuestionButton);

	//one layer per question
	m_iIndexQuestion = -1;	//so when we init the next question index = 0
	beginQuestion();

}

void LmQuizz_v1Scene::updateLoadingBar(float dt)
{
	m_iCounter++;
	if (m_iCounter > 100)
	{
		scheduleOnce(schedule_selector(LmQuizz_v1Scene::timerEnd), 0);
		unschedule(schedule_selector(LmQuizz_v1Scene::updateLoadingBar));
	}
	m_pTimer->setPercent(m_iCounter);
}

void LmQuizz_v1Scene::timerEnd(float dt)
{
	m_iNumberOfAttempt = 0;
	checkAnswer();
}

void LmQuizz_v1Scene::beginQuestion()
{
	if (m_bNextQuestionButtonCanBePress)
	{
		m_bNextQuestionButtonCanBePress = false;
		m_pNextQuestionButton->setVisible(false);

		//no more layers end of the game
		if ((int) m_iIndexQuestion >= (int) (m_aQuestions.size() - 1))
		{
			m_pFinishGameButton->setVisible(true);
		}
		else
		{
			//reset checkbox
			m_pCheckBoxAnswer1->setSelected(false);
			m_pCheckBoxAnswer2->setSelected(false);
			m_pCheckBoxAnswer3->setSelected(false);
			m_pCheckBoxAnswer4->setSelected(false);

			m_iNumberOfAttempt = m_iAttemptByQuestion;

			if (m_bTimerEnbaled)
			{
				//reset timer
				m_pTimer->setPercent(0);
				m_iCounter = 0;
				schedule(schedule_selector(LmQuizz_v1Scene::updateLoadingBar),
						m_fTimerDuration);
			}

			//disable answer selected
			m_iAnswerSelected = -1;

			//next layer
			initNextQuestion();
			checkBoxTouchEnabled(true);
		}

	}

}

void LmQuizz_v1Scene::initNextQuestion()
{
	//increment index
	m_iIndexQuestion++;
	auto l_pQuestion = m_aQuestions.at(m_iIndexQuestion);

	//set label string
	m_pQuestionLabel->setString(l_pQuestion->getSQuestion());
	m_pAnswerLabel1->setString(l_pQuestion->getSAnswer1());
	m_pAnswerLabel2->setString(l_pQuestion->getSAnswer2());
	m_pAnswerLabel3->setString(l_pQuestion->getSAnswer3());
	m_pAnswerLabel4->setString(l_pQuestion->getSAnswer4());

}

void LmQuizz_v1Scene::checkAnswer()
{
	//good answer
	if (m_aQuestions.at(m_iIndexQuestion)->getINumberGoodAnswer()
			== m_iAnswerSelected)
	{
		//load good texture for next button to indicate win
		m_pNextQuestionButton->loadTextureNormal(
				m_sFilenameSpriteGoodAnswerButton);
		m_pNextQuestionButton->loadTexturePressed(
				m_sFilenameSpriteGoodAnswerButton);
		switch (m_iAnswerSelected)
		{
		case 1:
			m_pCheckBoxAnswer1->setSelected(true);
			break;
		case 2:
			m_pCheckBoxAnswer2->setSelected(true);
			break;
		case 3:
			m_pCheckBoxAnswer3->setSelected(true);
			break;
		case 4:
			m_pCheckBoxAnswer4->setSelected(true);
			break;
		default:
			break;
		}
		questionFinish();
	}
	else
	{
		//still have attempt
		if (m_iNumberOfAttempt > 0)
		{
			m_iNumberOfAttempt--;
		}
		else
		{
			//load good texture for the next button to indicate loose
			m_pNextQuestionButton->loadTextureNormal(
					m_sFilenameSpriteBadAnswerButton);
			m_pNextQuestionButton->loadTexturePressed(
					m_sFilenameSpriteBadAnswerButton);
			questionFinish();
		}
	}
}

void LmQuizz_v1Scene::answerSelected(Ref* pSender, CheckBox::EventType type)
{

	auto l_pCheckBoxPressed = dynamic_cast<CheckBox*>(pSender);
	int l_iIdCheckBox = 0;

	//register the sender
	if (l_pCheckBoxPressed == m_pCheckBoxAnswer1)
	{
		l_iIdCheckBox = 1;
	}
	else if (l_pCheckBoxPressed == m_pCheckBoxAnswer2)
	{
		l_iIdCheckBox = 2;
	}
	else if (l_pCheckBoxPressed == m_pCheckBoxAnswer3)
	{
		l_iIdCheckBox = 3;
	}
	else if (l_pCheckBoxPressed == m_pCheckBoxAnswer4)
	{
		l_iIdCheckBox = 4;
	}
	else
	{
		CCLOG("callback checkbox failed");
	}

	switch (type)
	{
	case CheckBox::EventType::SELECTED:
		select(l_iIdCheckBox, true);
		break;

	case CheckBox::EventType::UNSELECTED:
		select(l_iIdCheckBox, false);
		break;

	default:
		break;
	}
	checkAnswer();

}

void LmQuizz_v1Scene::questionFinish()
{
	//disable touch on checkbox
	checkBoxTouchEnabled(false);
	if (m_bTimerEnbaled)
	{
		//stop timer
		unschedule(schedule_selector(LmQuizz_v1Scene::updateLoadingBar));
	}

	//make appear the next question button
	m_pNextQuestionButton->setVisible(true);
	m_bNextQuestionButtonCanBePress = true;

}

void LmQuizz_v1Scene::select(int l_iIdCheckBoxPressed, bool selected)
{
	if (selected)
	{
		//the answer selected is the checkbox selected
		m_iAnswerSelected = l_iIdCheckBoxPressed;

		//unselect the others
		switch (l_iIdCheckBoxPressed)
		{
		case 1:
			m_pCheckBoxAnswer2->setSelected(false);
			m_pCheckBoxAnswer3->setSelected(false);
			m_pCheckBoxAnswer4->setSelected(false);
			break;
		case 2:
			m_pCheckBoxAnswer1->setSelected(false);
			m_pCheckBoxAnswer3->setSelected(false);
			m_pCheckBoxAnswer4->setSelected(false);
			break;
		case 3:
			m_pCheckBoxAnswer1->setSelected(false);
			m_pCheckBoxAnswer2->setSelected(false);
			m_pCheckBoxAnswer4->setSelected(false);
			break;
		case 4:
			m_pCheckBoxAnswer1->setSelected(false);
			m_pCheckBoxAnswer2->setSelected(false);
			m_pCheckBoxAnswer3->setSelected(false);
			break;
		default:
			break;
		}

	}
	else
	{
		//the answer selected is reset
		m_iAnswerSelected = -1;
	}
}

void LmQuizz_v1Scene::checkBoxTouchEnabled(bool enabled)
{
	m_pCheckBoxAnswer1->setEnabled(enabled);
	m_pCheckBoxAnswer2->setEnabled(enabled);
	m_pCheckBoxAnswer3->setEnabled(enabled);
	m_pCheckBoxAnswer4->setEnabled(enabled);
}
