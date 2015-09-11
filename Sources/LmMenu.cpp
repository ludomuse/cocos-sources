/*
 * LmMenu.cpp
 *
 *  Created on: 9 sept. 2015
 *      Author: IHMTEKDev4
 */

//use for the debug
#define COCOS2D_DEBUG 1

#include "../Include/LmMenu.h"

USING_NS_CC;
using namespace cocos2d::ui;

LmMenu::LmMenu()
{
	m_pUser1 = new LmUser;
	m_pUser2 = new LmUser;

	//the play has not been clicked yet
	m_bPlayButtonClicked = false;
}

LmMenu::~LmMenu()
{
	//we don't user because gamemanger get pointer on them and it's him which is gonna to delete them

	//release the editbox
	m_pLogEditBox->release();
}

void LmMenu::splashScreen()
{
	//use to place elements
	Size l_oVisibleSize = Director::getInstance()->getVisibleSize();
	Point l_oOrigin = Director::getInstance()->getVisibleOrigin();

	//init scene
	m_pLmMenuScene = Scene::create();

	//call director to run the scene
	Director::getInstance()->runWithScene(m_pLmMenuScene);

	//init log layer
	m_pLogLayer = Layer::create();

	//firstable we add the log layer
	m_pLmMenuScene->addChild(m_pLogLayer);

	//init splash screen and display it for a while
	m_pSpriteSplashScreen = Sprite::create("splash.png");
	m_pSpriteSplashScreen->setPosition(l_oVisibleSize.width/2+l_oOrigin.x,l_oVisibleSize.height/2+l_oOrigin.y);
	m_pLogLayer->addChild(m_pSpriteSplashScreen);

	//wait a while
	auto delay = DelayTime::create(s_fSplashScreenDuration);
	m_pLogLayer -> runAction( Sequence::create(delay, CallFunc::create( std::bind(&LmMenu::logScreen,this) ), NULL));

}

bool LmMenu::logScreen()
{

	//use to place elements
	Size l_oVisibleSize = Director::getInstance()->getVisibleSize();
	Point l_oOrigin = Director::getInstance()->getVisibleOrigin();

	//remove the splash screen
	m_pLogLayer->removeChild(m_pSpriteSplashScreen);

	//add a background img for the log layer
	m_pSpriteLogBackground = Sprite::create("log.png");
	m_pSpriteLogBackground->setPosition(l_oVisibleSize.width/2+l_oOrigin.x,l_oVisibleSize.height/2+l_oOrigin.y);
	m_pLogLayer->addChild(m_pSpriteLogBackground);

	//log button
	auto l_oLogButton = Button::create("logNormal.png","logPressed.png");
	l_oLogButton->setTouchEnabled(true);
	l_oLogButton->setAnchorPoint(Point(0.5, 0));
	l_oLogButton -> setPosition(Vect(l_oVisibleSize.width*0.5f,l_oVisibleSize.height*0.2f));
	l_oLogButton->addTouchEventListener(CC_CALLBACK_0(LmMenu::wifiDirectScreen, this));
	m_pLogLayer->addChild(l_oLogButton);

	// Create the textfield
	m_pLogEditBox = EditBox::create(Size(300,50),Scale9Sprite::create("textfieldBackground.png"));
	m_pLogEditBox->setPosition(Point(l_oVisibleSize.width*0.5f,l_oVisibleSize.height*0.5f));
	m_pLogEditBox->setPlaceHolder("Name");
	m_pLogEditBox->setFontSize(25);
	m_pLogEditBox->setMaxLength(s_iMaxLenghtUserName);
	m_pLogEditBox->setReturnType(ui::EditBox::KeyboardReturnType::DONE);
	m_pLogLayer->addChild(m_pLogEditBox);

	//the string which contain the user name is contain is an autorelease object editbox and will disapear when use in the gamemanager
	//we retain it here to release it in the destructor
	m_pLogEditBox->retain();


	return true;
}

bool LmMenu::wifiDirectScreen()
{
	//check if the user enter smthg
	if(!strcmp(m_pLogEditBox->getText(),""))
	{
		return false;
	}
	else
	{

		//use to place elements
		Size l_oVisibleSize = Director::getInstance()->getVisibleSize();
		Point l_oOrigin = Director::getInstance()->getVisibleOrigin();

		//remove the log layer
		m_pLmMenuScene->removeChild(m_pLogLayer);

		//create wifi layer
		m_pWifiLayer = Layer::create();

		//add the wifilayer
		m_pLmMenuScene->addChild(m_pWifiLayer);

		//add a background img for the wifi layer
		m_pSpriteWifiBackground = Sprite::create("log.png");
		m_pSpriteWifiBackground->setPosition(l_oVisibleSize.width/2,l_oVisibleSize.height/2+l_oOrigin.y);
		m_pWifiLayer->addChild(m_pSpriteWifiBackground);

		//TODO find peers and set attributes and instanciate socket

		//tablet are connected create both user
		m_pUser1->setPScore(54);
		m_pUser1->setPUserName(m_pLogEditBox->getText());
		m_pUser1->setPUserTabletName("tablet1_name");

		m_pUser2->setPScore(20);
		m_pUser2->setPUserName("2nd user");
		m_pUser2->setPUserTabletName("tablet2_name");


		//Play button
		auto l_oPlayButton = Button::create("playNormal.png","playPressed.png");
		l_oPlayButton->setTouchEnabled(true);
		l_oPlayButton->setAnchorPoint(Point(0.5, 0));
		l_oPlayButton -> setPosition(Vect(l_oVisibleSize.width*0.5f,l_oVisibleSize.height*0.2f));
		l_oPlayButton->addTouchEventListener(CC_CALLBACK_0(LmMenu::menuIsFinished, this));
		m_pLogLayer->addChild(l_oPlayButton);

		return true;

	}
}

void LmMenu::menuIsFinished()
{
	if(!m_bPlayButtonClicked)
	{
		m_bPlayButtonClicked=true;
		Director::getInstance()->getEventDispatcher()->dispatchCustomEvent("MenuFinished");
	}

}
