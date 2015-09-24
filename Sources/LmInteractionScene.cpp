//use for the debug
#define COCOS2D_DEBUG 1

#include "../Include/LmInteractionScene.h"

USING_NS_CC;

LmInteractionScene::LmInteractionScene()
{
	//object
	m_pLmIntroduction = new LmIntroduction;//need to be delete

	//primitive type
	m_bDone=false;
	m_bActionRunning=false;
	m_bDashboardIsHidden=true;
	m_bMoveDone=true;
	m_bBackPressed=false;
	m_iNumberOfGameComponent=0;

	//pointer
	m_pBackDashboardButton=nullptr;
	m_pUser=nullptr;
	m_pDashboardBandLayer=nullptr;
	m_pMoveLayerButton=nullptr;
	m_pLayerGame=nullptr;
	m_pLabelScore=nullptr;
	m_pLayerUserChild=nullptr;
	m_pLabelUserName=nullptr;
	m_pGuiElementsLayer=nullptr;
	m_pLayerUserParent=nullptr;
	m_pSpriteDashboardBand=nullptr;

}

LmInteractionScene::~LmInteractionScene()
{

	delete m_pLmIntroduction;

}



bool LmInteractionScene::init(LmUser* l_pUser)
{

	//init user
	m_pUser = l_pUser;

	initDashboardLayer();
	if(!m_pLmIntroduction->init(this))
	{
		CCLOG("LmIntroduction init failed");
		return false;
	}

	//use to place elements
	Size l_oVisibleSize = Director::getInstance()->getVisibleSize();

	//next button
	m_pNextButton = ui::Button::create("nextButtonNormal.png","nextButtonPressed.png");
	m_pNextButton->setTouchEnabled(true);
	m_pNextButton -> setPosition(Vect(l_oVisibleSize.width-m_pNextButton->getContentSize().width*0.8,m_pNextButton->getContentSize().height*0.7));
	m_pNextButton->addTouchEventListener(CC_CALLBACK_0(LmInteractionScene::nextLayer, this));
	addChild(m_pNextButton,1);

	//previous button
	m_pPreviousButton = ui::Button::create("previousButtonNormal.png","previousButtonPressed.png");
	m_pPreviousButton->setTouchEnabled(true);
	m_pPreviousButton -> setPosition(Vect(m_pPreviousButton->getContentSize().width*0.8,m_pPreviousButton->getContentSize().height*0.7));
	m_pPreviousButton->addTouchEventListener(CC_CALLBACK_0(LmInteractionScene::previousLayer, this));
	addChild(m_pPreviousButton,1);

	return true;
}

void LmInteractionScene::previousLayer()
{
	if(m_pLmIntroduction->isBActionDone())// action is done is used to sync Lmintroduction
	{
		m_pLmIntroduction->previousLayer();
	}
}

void LmInteractionScene::nextLayer()
{
	//false => introduction is finished
	if(!m_pLmIntroduction->nextLayer() && m_pLmIntroduction->isBActionDone())
	{
		removeChild(m_pNextButton);
		removeChild(m_pPreviousButton);
		runGame();
	}
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
			m_pDashboardBandLayer->runAction(Sequence::create(l_oMoveRightAction,l_oMoveRightActionDone,nullptr));
		}
		else
		{
			auto l_oMoveLeftAction = MoveBy::create(s_fTimeMovingDashboard,Vect((-1)*s_fDashboardRatioHidden*m_pSpriteDashboardBand->getContentSize().width,0));
			auto l_oMoveLeftActionDone = CallFunc::create( std::bind(&LmInteractionScene::moveLeftDone,this) );
			m_pDashboardBandLayer->runAction(Sequence::create(l_oMoveLeftAction,l_oMoveLeftActionDone,nullptr));
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

LmGameComponent* LmInteractionScene::makeGameComponent()
{
	//generate a new id
	m_iNumberOfGameComponent++;
	//register it into the id table
	m_aIdTable.insert(std::pair<int,LmGameComponent*>(m_iNumberOfGameComponent,new LmGameComponent(m_iNumberOfGameComponent)));

	return m_aIdTable.find(m_iNumberOfGameComponent)->second;
}

