//use for the debug
#define COCOS2D_DEBUG 1

#include "../Include/LmInteractionScene.h"

USING_NS_CC;

LmInteractionScene::LmInteractionScene()
{
	//create the introduction
	m_pLmIntroduction = new LmIntroduction;

	m_bDone=false;

	m_bActionRunning=false;

}

LmInteractionScene::~LmInteractionScene()
{

	delete m_pLmIntroduction;

	//remove the custom event
	Director::getInstance()->getEventDispatcher()->removeCustomEventListeners("IntroductionFinished");

}



bool LmInteractionScene::init(LmUser* l_pUser)
{

	//init user
	m_pUser = l_pUser;

	initDashboardLayer();

	if(!m_pLmIntroduction->init(this))//will be init with parameters from json TODO
	{
		CCLOG("LmIntroduction init failed");
		return false;
	}

	//init callback method of the custom event (use to know when an interactionScene want to communicate with this)
	auto IntroductionFinished = [=](EventCustom * event)
									{
										runGame();
									};

	//add the custom event to the event dispatcher
	Director::getInstance()->getEventDispatcher()->addCustomEventListener("IntroductionFinished",IntroductionFinished);


	return true;
}

void LmInteractionScene::initDashboardLayer()
{
	//use to place elements
	Size l_oVisibleSize = Director::getInstance()->getVisibleSize();
	Point l_oOrigin = Director::getInstance()->getVisibleOrigin();

	//layer
	m_pDashboardBandLayer = Layer::create();
	this->addChild(m_pDashboardBandLayer,2);

	//spritebackground
	m_pSpriteDashboardBand = Sprite::create("spriteBackgroundUser1Profile.png");
	m_pSpriteDashboardBand->setAnchorPoint(Vec2(0,0));
	m_pSpriteDashboardBand->setPosition(Vec2(m_pSpriteDashboardBand->getContentSize().width*(-s_fDashboardRatioHidden),0));
	m_pDashboardBandLayer->addChild(m_pSpriteDashboardBand,0);

	//button to move the layer
	m_pMoveLayerButton = ui::Button::create("moveDashboardLayer.png");
	m_pMoveLayerButton->setTouchEnabled(true);
	m_pMoveLayerButton -> setPosition(Vec2((1-s_fDashboardRatioHidden)*(m_pSpriteDashboardBand->getContentSize().width*0.5f),l_oVisibleSize.height*0.5f));
	m_pMoveLayerButton->addTouchEventListener(CC_CALLBACK_0(LmInteractionScene::moveDashboardLayer, this));
	m_pDashboardBandLayer->addChild(m_pMoveLayerButton,0);

	m_bMoveDone=true;
	m_bDashboardIsHidden=true;

	//gui elements
	m_pGuiElementsLayer = Layer::create();

	//user1 name
	m_pLabelUserName = Label::createWithTTF(m_pUser->getPUserName(), "fonts/JosefinSans-Regular.ttf",20);
	m_pLabelUserName->setPosition(m_pSpriteDashboardBand->getContentSize().width*(0.5f-s_fDashboardRatioHidden)
			,m_pSpriteDashboardBand->getContentSize().height*0.7f);
	m_pGuiElementsLayer->addChild(m_pLabelUserName);

	//label score
	char l_aScoreString[10];
	sprintf(l_aScoreString,"%d pts",m_pUser->getPScore());
	m_pLabelScore = Label::createWithTTF(l_aScoreString, "fonts/JosefinSans-Regular.ttf",20);
	m_pLabelScore->setPosition(m_pSpriteDashboardBand->getContentSize().width*(0.5f-s_fDashboardRatioHidden)
			,m_pSpriteDashboardBand->getContentSize().height*0.5f);
	m_pGuiElementsLayer->addChild(m_pLabelScore);

	m_pBackDashboardButton = ui::Button::create("backToDashboard.png");
	m_pBackDashboardButton->setTouchEnabled(true);
	m_pBackDashboardButton -> setPosition(Vec2(m_pSpriteDashboardBand->getContentSize().width*(0.5f-s_fDashboardRatioHidden)
			,m_pSpriteDashboardBand->getContentSize().height*0.3f));
	m_pBackDashboardButton->addTouchEventListener(CC_CALLBACK_0(LmInteractionScene::backToDashboard, this));
	m_pGuiElementsLayer->addChild(m_pBackDashboardButton);
	m_bBackPressed=false;


	m_pDashboardBandLayer->addChild(m_pGuiElementsLayer,1);



}

void LmInteractionScene::moveDashboardLayer()
{
	if(m_bMoveDone)
	{
		m_bMoveDone=false;

		//we look if we have to move right or left
		if(m_bDashboardIsHidden)
		{
			auto l_oMoveRightAction = MoveBy::create(s_fTimeMovingDashboard,Vect(s_fDashboardRatioHidden*m_pSpriteDashboardBand->getContentSize().width,0));
			auto l_oMoveRightActionDone = CallFunc::create( std::bind(&LmInteractionScene::moveRightDone,this) );
			m_pDashboardBandLayer->runAction(Sequence::create(l_oMoveRightAction,l_oMoveRightActionDone,NULL));
		}
		else
		{
			auto l_oMoveLeftAction = MoveBy::create(s_fTimeMovingDashboard,Vect((-1)*s_fDashboardRatioHidden*m_pSpriteDashboardBand->getContentSize().width,0));
			auto l_oMoveLeftActionDone = CallFunc::create( std::bind(&LmInteractionScene::moveLeftDone,this) );
			m_pDashboardBandLayer->runAction(Sequence::create(l_oMoveLeftAction,l_oMoveLeftActionDone,NULL));
		}

	}

}

void LmInteractionScene::moveRightDone()
{
	//enable back button
	m_bBackPressed=false;

	//active button
	m_bMoveDone=true;
	m_bDashboardIsHidden=false;

}

void LmInteractionScene::moveLeftDone()
{
	//disable back button
	m_bBackPressed=true;

	//active button
	m_bMoveDone=true;
	m_bDashboardIsHidden=true;

}

void LmInteractionScene::backToDashboard()
{
	if(!m_bBackPressed && m_bMoveDone && m_pLmIntroduction->isBActionDone())
	{
		m_bBackPressed=true;

		CCLOG("popscene");
		Director::getInstance()->popScene();
		Director::getInstance()->getEventDispatcher()->dispatchCustomEvent("BackToDashboard");
	}
}

