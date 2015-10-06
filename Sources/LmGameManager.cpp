//use for the debug
#define COCOS2D_DEBUG 1

#include "../Include/LmGameManager.h"

USING_NS_CC;

LmGameManager::LmGameManager()
{
	//object
	m_pLmServerManager = new LmServerManager; //need to be delete

	//primitive type
	m_iIndexInteractionScene = 0;
	m_iInteractionDone = 0;
	m_bBackToDashboard = false;
	m_bActionIsDone = true;

	//pointer
	m_pLabelInteractionDone = nullptr;
	m_pSpriteBackgroundBlue = nullptr;
	m_pSpriteBackgroundBlueProfile = nullptr;
	m_pSpriteBackgroundPink = nullptr;
	m_pSpriteBackgroundPinkProfile = nullptr;
	m_pSpriteBandTop = nullptr;
	m_pGameManagerScene = nullptr;
	m_pBackButton = nullptr;
	m_pBlueLayer = nullptr;
	m_pCompareButton == nullptr;
	m_pLabelCompareButton = nullptr;
	m_pLabelScore = nullptr;
	m_pLabelTitleApplication = nullptr;
	m_pLabelUser1Name = nullptr;
	m_pUser1 = nullptr; //need to be delete
	m_pUser2 = nullptr; //need to be delete
	m_pCompareButton = nullptr;
	m_pScrollView = nullptr;
	m_pPlayNextInteractionButton = nullptr;
	m_pPinkLayer = nullptr;
	m_pSpriteBandMid = nullptr;

}

LmGameManager::~LmGameManager()
{
	//delete users created by LmMenu
	delete m_pUser1;
	delete m_pUser2;

	//we release our button
	m_pCompareButton->release();
	m_pLabelCompareButton->release();
	m_pBackButton->release();
	m_pSpriteBandTop->release();

	//destroy the ServerManager
	delete m_pLmServerManager;

	//Browse the vector of scene and delete them
	for (std::vector<LmInteractionScene*>::iterator it =
			m_aInteractionSceneOfTheGame.begin();
			it != m_aInteractionSceneOfTheGame.end(); ++it)
	{
		delete (*it);
	}

	//remove the custom event
	Director::getInstance()->getEventDispatcher()->removeCustomEventListeners(
			"InteractionSceneFinished");
	Director::getInstance()->getEventDispatcher()->removeCustomEventListeners(
			"BackToDashboard");

}

bool LmGameManager::init()
{

	if (!m_pLmServerManager->init())
	{
		CCLOG("Initialization Server Manager failed");
		return false;
	}

	//init splashscreen
	if (!initSplashScreen())
	{
		CCLOG("Initialization splash screen failed");
		return false;
	}


	//get the vector of scene through the serverManager and indicate if it's for child or parent
	m_aInteractionSceneOfTheGame =
			m_pLmServerManager->getInteractionSceneOfTheGame(
					m_pUser1->isBParent());

	//init callback method of the custom event (use to know when an interactionScene want to communicate with this)
	auto InteractionSceneFinished = [=](EventCustom * event)
	{

		//TODO
		//check if t's done and win etc and update sprite (for now its everytime done)
			m_aSpritesInteractions.at(m_iIndexInteractionScene)->setTexture("Ludomuse/GUIElements/interactionDone.png");
			m_iInteractionDone++;

		//update index
			m_iIndexInteractionScene++;

		//update label of dashboard
			updateDashboard();

		//it's not a back to dashboard
			m_bBackToDashboard=false;

		//reset touch enable
			removeListeners(false);

		};

	auto BackToDashboard = [=](EventCustom * event)
	{

		m_bBackToDashboard=true;

		//reset touch enable
			removeListeners(false);

		};

	//add the custom event to the event dispatcher
	Director::getInstance()->getEventDispatcher()->addCustomEventListener(
			"InteractionSceneFinished", InteractionSceneFinished);
	Director::getInstance()->getEventDispatcher()->addCustomEventListener(
			"BackToDashboard", BackToDashboard);

	return true;
}

bool LmGameManager::initDashboard()
{
	//use to place elements
	Size l_oVisibleSize = Director::getInstance()->getVisibleSize();
	Point l_oOrigin = Director::getInstance()->getVisibleOrigin();

	//create the main layer and put element on it
	m_pBlueLayer = Layer::create();
	m_pPinkLayer = Layer::create();
	m_pGameManagerScene->addChild(m_pBlueLayer);
	m_pGameManagerScene->addChild(m_pPinkLayer);

	//we add the different background with different zorder

	//background blue
	m_pSpriteBackgroundBlue = Sprite::create("Ludomuse/GUIElements/fullBlue.png");
	m_pSpriteBackgroundBlue->setPosition(l_oVisibleSize.width * 0.5f,
			l_oVisibleSize.height * 0.5f);
	m_pBlueLayer->addChild(m_pSpriteBackgroundBlue);

	//background pink
	m_pSpriteBackgroundPink = Sprite::create("Ludomuse/GUIElements/halfPink.png");
	m_pSpriteBackgroundPink->setPosition(l_oVisibleSize.width * 0.5f,
			m_pSpriteBackgroundPink->getContentSize().height
					* (-0.5f + s_fMagingRatioOfSpriteBackgroundUser2Profile));
	m_pPinkLayer->addChild(m_pSpriteBackgroundPink);

	//background profile blue
	m_pSpriteBackgroundBlueProfile = Sprite::create(
			"Ludomuse/GUIElements/spriteBackgroundUser1Profile.png");
	m_pSpriteBackgroundBlueProfile->setPosition(
			m_pSpriteBackgroundBlueProfile->getContentSize().width * 0.5f,
			l_oVisibleSize.height * 0.5);
	m_pBlueLayer->addChild(m_pSpriteBackgroundBlueProfile, 1);

	//user1 name
	m_pLabelUser1Name = Label::createWithTTF(m_pUser1->getPUserName(),
			"Fonts/JosefinSans-Regular.ttf", l_oVisibleSize.width*0.04);
	m_pLabelUser1Name->setPosition(
			m_pSpriteBackgroundBlueProfile->getContentSize().width * 0.5f,
			m_pSpriteBackgroundBlueProfile->getContentSize().height * 0.95f);
	m_pLabelUser1Name->setMaxLineWidth(
			m_pSpriteBackgroundBlueProfile->getContentSize().width);
	m_pSpriteBackgroundBlueProfile->addChild(m_pLabelUser1Name, 1);

	//label score
	char l_aScoreString[20];
	sprintf(l_aScoreString, "%d pts", m_pUser1->getPScore());
	m_pLabelScore = Label::createWithTTF(l_aScoreString,
			"Fonts/JosefinSans-Regular.ttf", l_oVisibleSize.width*0.04);
	m_pLabelScore->setPosition(
			m_pSpriteBackgroundBlueProfile->getContentSize().width * 0.5f,
			m_pSpriteBackgroundBlueProfile->getContentSize().height * 0.65f);
	m_pSpriteBackgroundBlueProfile->addChild(m_pLabelScore, 1);

	//how manny interaction done label
	char l_aInteractionDoneString[20];
	sprintf(l_aInteractionDoneString, "%d/%d", m_iInteractionDone,
			m_aInteractionSceneOfTheGame.size());
	m_pLabelInteractionDone = Label::createWithTTF(l_aInteractionDoneString,
			"Fonts/JosefinSans-Regular.ttf", l_oVisibleSize.width*0.04);
	m_pLabelInteractionDone->setPosition(
			m_pSpriteBackgroundBlueProfile->getContentSize().width * 0.5f,
			m_pSpriteBackgroundBlueProfile->getContentSize().height * 0.55f);
	m_pSpriteBackgroundBlueProfile->addChild(m_pLabelInteractionDone, 1);

	//background profil pink
	auto m_pSpriteBackgroundPinkProfile = Sprite::create(
			"Ludomuse/GUIElements/spriteBackgroundUser2Profile.png");
	m_pSpriteBackgroundPinkProfile->setPosition(
			m_pSpriteBackgroundPinkProfile->getContentSize().width * 0.5f,
			m_pSpriteBackgroundPinkProfile->getContentSize().height
					* (-0.5f + s_fMagingRatioOfSpriteBackgroundUser2Profile));
	m_pPinkLayer->addChild(m_pSpriteBackgroundPinkProfile, 1);

	//add the band mid at the top of the pink background
	m_pSpriteBandMid = Sprite::create("Ludomuse/GUIElements/bandMid.png");
	m_pSpriteBandMid->setAnchorPoint(Vec2(0, 0.5));
	m_pSpriteBandMid->setPosition(
			m_pSpriteBackgroundBlueProfile->getContentSize().width,
			m_pSpriteBackgroundPink->getContentSize().height
					* s_fMagingRatioOfSpriteBackgroundUser2Profile);
	m_pPinkLayer->addChild(m_pSpriteBandMid);

	//compare button with ui::Button
	m_pCompareButton = ui::Button::create("Ludomuse/GUIElements/compareNormal.png");
	m_pCompareButton->setTouchEnabled(true);
	m_pCompareButton->setPosition(
			Vect(l_oVisibleSize.width * 0.5f, l_oVisibleSize.height * 0.1f));
	m_pCompareButton->addTouchEventListener(
			CC_CALLBACK_0(LmGameManager::compare, this));
	m_pPinkLayer->addChild(m_pCompareButton);
	m_pCompareButton->retain();

	//label compare button
	m_pLabelCompareButton = Label::createWithTTF("comparer",
			"Fonts/JosefinSans-Regular.ttf", l_oVisibleSize.width*0.04);
	m_pLabelCompareButton->setPosition(
			l_oVisibleSize.width * 0.6f
					+ m_pCompareButton->getContentSize().width,
			l_oVisibleSize.height * 0.1f);
	m_pPinkLayer->addChild(m_pLabelCompareButton);
	m_pLabelCompareButton->retain();

	//back button
	m_pBackButton = ui::Button::create("Ludomuse/GUIElements/backNormal.png");
	m_pBackButton->setTouchEnabled(true);
	m_pBackButton->setPosition(
			Vect(
					(l_oVisibleSize.width
							- m_pSpriteBackgroundBlueProfile->getContentSize().width)
							* 0.5f
							+ m_pSpriteBackgroundBlueProfile->getContentSize().width,
					l_oVisibleSize.height * 0.95f));
	m_pBackButton->addTouchEventListener(
			CC_CALLBACK_0(LmGameManager::back, this));
	m_pBackButton->retain();

	//put the top band
	m_pSpriteBandTop = Sprite::create("Ludomuse/GUIElements/bandTop.png");
	m_pSpriteBandTop->setAnchorPoint(Vec2(0, 1));
	m_pSpriteBandTop->setPosition(Vec2(0, l_oVisibleSize.height + l_oOrigin.y));
	m_pBlueLayer->addChild(m_pSpriteBandTop);
	m_pSpriteBandTop->retain();

	//title label app
	m_sTitleApplication = m_pLmServerManager->getSTitleApplication();
	m_pLabelTitleApplication = Label::createWithTTF(m_sTitleApplication,
			"Fonts/JosefinSans-Regular.ttf", l_oVisibleSize.width*0.04);
	m_pLabelTitleApplication->setPosition(
			Vec2(
					(l_oVisibleSize.width
							- m_pSpriteBackgroundBlueProfile->getContentSize().width)
							* 0.5
							+ m_pSpriteBackgroundBlueProfile->getContentSize().width,
					m_pSpriteBandTop->getContentSize().height * 0.5f));
	m_pLabelTitleApplication->setColor(Color3B::BLACK);
	m_pLabelTitleApplication->setMaxLineWidth(
			(l_oVisibleSize.width
					- m_pSpriteBackgroundBlueProfile->getContentSize().width)
					* 0.9);
	m_pSpriteBandTop->addChild(m_pLabelTitleApplication);

	//init interactions
	initDashboardInteraction();

	//play next interaction button
	m_pPlayNextInteractionButton = ui::Button::create(
			"Ludomuse/GUIElements/playNextInteraction.png");
	m_pPlayNextInteractionButton->setTouchEnabled(true);
	m_pPlayNextInteractionButton->setAnchorPoint(Vec2(1, 0.5));
	m_pPlayNextInteractionButton->setPosition(
			Vec2(m_pSpriteBandMid->getContentSize().width,
					m_pSpriteBandMid->getContentSize().height * 0.5f));
	m_pPlayNextInteractionButton->addTouchEventListener(
			CC_CALLBACK_0(LmGameManager::runNextInteraction, this));
	m_pSpriteBandMid->addChild(m_pPlayNextInteractionButton, 2);

	return true;
}

void LmGameManager::runGame()
{
	//Init of the GameManager
	init();

	//replace the menu scene with the first one of the game
	Director::getInstance()->replaceScene(
			TransitionFade::create(s_fTimeBetweenLmLayer, m_pGameManagerScene));

}

void LmGameManager::compare()
{
	if (m_bActionIsDone)
	{
		m_bActionIsDone = false;
		auto l_oCompareAction = MoveBy::create(s_fTimeCompareAction,
				Vect(0,
						(m_pSpriteBackgroundPink->getContentSize().height)
								* 0.5f
								- s_fMagingRatioOfSpriteBackgroundUser2Profile));
		auto l_oCompareActionIsDone = CallFunc::create(
				std::bind(&LmGameManager::compareDone, this));
		m_pPinkLayer->runAction(
				Sequence::create(l_oCompareAction, l_oCompareActionIsDone,
						nullptr));

	}
}

void LmGameManager::compareDone()
{
	m_bActionIsDone = true;
	m_pPinkLayer->removeChild(m_pCompareButton);
	m_pPinkLayer->removeChild(m_pLabelCompareButton);
	m_pBlueLayer->removeChild(m_pSpriteBandTop);
	m_pBlueLayer->addChild(m_pBackButton);
}

void LmGameManager::back()
{
	if (m_bActionIsDone)
	{
		m_bActionIsDone = false;
		auto l_oBackAction = MoveBy::create(s_fTimeCompareAction,
				Vect(0,
						-(m_pSpriteBackgroundPink->getContentSize().height)
								* 0.5f
								- s_fMagingRatioOfSpriteBackgroundUser2Profile));
		auto l_oBackActionIsDone = CallFunc::create(
				std::bind(&LmGameManager::backDone, this));
		m_pPinkLayer->runAction(
				Sequence::create(l_oBackAction, l_oBackActionIsDone, nullptr));

	}
}

void LmGameManager::backDone()
{
	m_bActionIsDone = true;
	m_pPinkLayer->addChild(m_pCompareButton);
	m_pPinkLayer->addChild(m_pLabelCompareButton);
	m_pBlueLayer->removeChild(m_pBackButton);
	m_pBlueLayer->addChild(m_pSpriteBandTop);

}

void LmGameManager::initDashboardInteraction()
{
	//use to place elements
	Size l_oVisibleSize = Director::getInstance()->getVisibleSize();
	Point l_oOrigin = Director::getInstance()->getVisibleOrigin();

	Sprite* l_pSpriteBuffer;
	int l_iIndex(0);

	//Browse the vector and init sprite then add to the vector
	for (std::vector<LmInteractionScene*>::iterator it =
			m_aInteractionSceneOfTheGame.begin();
			it != m_aInteractionSceneOfTheGame.end(); ++it)
	{
		l_pSpriteBuffer = Sprite::create("Ludomuse/GUIElements/interactionNotDone.png");
		l_pSpriteBuffer->setAnchorPoint(Vec2(0, 0));
		l_pSpriteBuffer->setPosition(
				Vec2((l_iIndex) * s_fMarginBetweenInteraction, 0));
		l_iIndex++;
		m_aSpritesInteractions.push_back(l_pSpriteBuffer);
	}

	//init the scroll view
	m_pScrollView = ui::ScrollView::create();
	Size l_oScrollFrameSize = Size(m_pSpriteBandMid->getContentSize().width,
			m_pSpriteBandMid->getContentSize().height
					+ l_pSpriteBuffer->getContentSize().height);
	m_pScrollView->setContentSize(l_oScrollFrameSize);
	m_pScrollView->setAnchorPoint(Vec2(0, 0));
	m_pScrollView->setPosition(Vec2(0, 0));
	m_pScrollView->setDirection(cocos2d::ui::ScrollView::Direction::HORIZONTAL);

	//if there is no enough interaction to fill the frame size
	Size l_oContainerSize;
	if ((l_iIndex) * (s_fMarginBetweenInteraction)
			<= m_pSpriteBandMid->getContentSize().width)
	{
		l_oContainerSize = Size(m_pSpriteBandMid->getContentSize().width,
				m_pSpriteBandMid->getContentSize().height
						+ l_pSpriteBuffer->getContentSize().height);
	}
	else
	{
		l_oContainerSize = Size((l_iIndex) * (s_fMarginBetweenInteraction),
				m_pSpriteBandMid->getContentSize().height
						+ l_pSpriteBuffer->getContentSize().height);
	}

	m_pScrollView->setInnerContainerSize(l_oContainerSize);

	for (std::vector<Sprite*>::iterator it = m_aSpritesInteractions.begin();
			it != m_aSpritesInteractions.end(); ++it)
	{
		m_pScrollView->addChild((*it));
	}

	m_pScrollView->setBounceEnabled(true);
	m_pScrollView->setTouchEnabled(true);
	m_pScrollView->setInertiaScrollEnabled(true);
	m_pSpriteBandMid->addChild(m_pScrollView);

}

void LmGameManager::runNextInteraction()
{
	//if its the last interactionscene the app finished
	if (m_iIndexInteractionScene >= m_aInteractionSceneOfTheGame.size())
	{
		CCLOG("END");
		Director::getInstance()->end();
	}
	else
	{

		//if yes we need to init the scene
		if (!m_bBackToDashboard)
		{
			//we pass the local user
			if (!m_aInteractionSceneOfTheGame.at(m_iIndexInteractionScene)->init(
					m_pUser1))
			{
				CCLOG("Interaction scene init failed");
			}

		}

		//enable the back button of the interaction because it was disable before the back action (LmInteractionScene::backToDashboard)
		m_aInteractionSceneOfTheGame.at(m_iIndexInteractionScene)->setBBackPressed(
				false);

		CCLOG("pushscene");
		removeListeners(true);
		Director::getInstance()->pushScene(
				TransitionFade::create(s_fTimeBetweenLmLayer,
						m_aInteractionSceneOfTheGame.at(
								m_iIndexInteractionScene)));

		//it was a back
		if (m_bBackToDashboard)
		{
			m_aInteractionSceneOfTheGame.at(m_iIndexInteractionScene)->restart();
		}

	}

}

void LmGameManager::updateDashboard()
{
	//update interaction done
	char l_aInteractionDoneString[10];
	sprintf(l_aInteractionDoneString, "%d/%d", m_iInteractionDone,
			m_aInteractionSceneOfTheGame.size());
	//slow but we are using it just at the end of an interaction
	m_pLabelInteractionDone->setString(l_aInteractionDoneString);

	//update score
	char l_aScoreString[10];
	sprintf(l_aScoreString, "%d pts", m_pUser1->getPScore());
	m_pLabelScore->setString(l_aScoreString);

}

void LmGameManager::removeListeners(bool l_bTrue)
{
	m_pBackButton->setTouchEnabled(!l_bTrue);
	m_pCompareButton->setTouchEnabled(!l_bTrue);
	m_pPlayNextInteractionButton->setTouchEnabled(!l_bTrue);
}

bool LmGameManager::initSplashScreen()
{
	//use to place elements
	Size l_oVisibleSize = Director::getInstance()->getVisibleSize();
	Point l_oOrigin = Director::getInstance()->getVisibleOrigin();

	//create the scene
	m_pGameManagerScene = Scene::create();

	//add the layer of the splash screen
	m_pSplashSreenLayer = Layer::create();
	m_pGameManagerScene->addChild(m_pSplashSreenLayer);

	//add the sprite background get from the config json file
	auto l_pSplashScreenSprite = Sprite::create(
			m_pLmServerManager->getSFilenameSpriteSplashScreen());
	l_pSplashScreenSprite->setPosition(
			l_oVisibleSize.width * 0.5f + l_oOrigin.x,
			l_oVisibleSize.height * 0.5f + l_oOrigin.y);
	m_pSplashSreenLayer->addChild(l_pSplashScreenSprite);

	//init its listener
	m_pListener = EventListenerTouchOneByOne::create();
	m_pListener->onTouchBegan = CC_CALLBACK_2(
			LmGameManager::onTouchBeganSplashScreen, this);
	m_pListener->setSwallowTouches(true);

	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(
			m_pListener, m_pSplashSreenLayer);

	return true;
}

bool LmGameManager::onTouchBeganSplashScreen(Touch* touch, Event* event)
{

	//remove layer
	m_pGameManagerScene->removeChild(m_pSplashSreenLayer);
	//remove listener
	Director::getInstance()->getEventDispatcher()->removeEventListener(
			m_pListener);

	//init dashboard
	if (!initDashboard())
	{
		CCLOG("Initialization DashBoard failed");
		return false;
	}

	return true;
}

