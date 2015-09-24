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
	//object
	m_pUser1 = new LmUser;//delete in LmGameManager
	m_pUser2 = new LmUser;//delete in LmGameManager

	//pointer
	m_pLmMenuScene=nullptr;
	m_pLogEditBox=nullptr;
	m_pLogLayer=nullptr;
	m_pSpriteLogBackground=nullptr;
	m_pSpriteSplashScreen=nullptr;
	m_pSpriteWifiBackground=nullptr;
	m_pWifiLayer=nullptr;

	//primitive type
	m_bPlayButtonClicked = false;//the play has not been clicked yet
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
	m_pLogLayer -> runAction( Sequence::create(delay, CallFunc::create( std::bind(&LmMenu::logScreen,this) ), nullptr));

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
	auto l_oLogButton = MenuItemImage::create("logNormal.png","logPressed.png",CC_CALLBACK_1(LmMenu::wifiDirectScreen, this));
	l_oLogButton->setAnchorPoint(Point(0.5, 0));
	l_oLogButton -> setPosition(Vect(l_oVisibleSize.width*0.5f,l_oVisibleSize.height*0.2f));

	// Create the textfield
	m_pLogEditBox = EditBox::create(Size(300,50),Scale9Sprite::create("textfieldBackground.png"));
	m_pLogEditBox->setPosition(Point(l_oVisibleSize.width*0.5f,l_oVisibleSize.height*0.5f));
	m_pLogEditBox->setPlaceHolder(" Name");
	m_pLogEditBox->setFontSize(20);
	m_pLogEditBox->setFontName("fonts/JosefinSans-Regular.ttf");
	m_pLogEditBox->setFontColor(Color3B::BLACK);
	m_pLogEditBox->setMaxLength(s_iMaxLenghtUserName);
	m_pLogEditBox->setReturnType(ui::EditBox::KeyboardReturnType::DONE);
	m_pLogLayer->addChild(m_pLogEditBox,1);

	//the string which contain the user name is contain is an autorelease object editbox and will disapear when use in the gamemanager
	//we retain it here to release it in the destructor
	m_pLogEditBox->retain();

	// create menu, it's an autorelease object
	auto l_oMenu = Menu::create(l_oLogButton, nullptr);
	l_oMenu->setPosition(Vec2::ZERO);
	m_pLogLayer->addChild(l_oMenu, 1);


	return true;
}

bool LmMenu::wifiDirectScreen(cocos2d::Ref* l_oSender)
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

		//Play button
		auto l_oPlayButton = MenuItemImage::create("playNormal.png","playPressed.png",CC_CALLBACK_1(LmMenu::menuIsFinished, this));
		l_oPlayButton->setAnchorPoint(Point(0.5, 0));
		l_oPlayButton -> setPosition(Vect(l_oVisibleSize.width*0.5f,l_oVisibleSize.height*0.2f));

		// create menu, it's an autorelease object
		auto l_oMenu = Menu::create(l_oPlayButton, nullptr);
		l_oMenu->setPosition(Vec2::ZERO);
		m_pWifiLayer->addChild(l_oMenu, 1);

		//TODO find peers and set attributes and instanciate socket

		//tablet are connected create both user
		m_pUser1->setPScore(0);
		m_pUser1->setPUserName(m_pLogEditBox->getText());
		m_pUser1->setPUserTabletName("tablet1_name");

		//to know what part of the game he is going to play

		//test if P alors we play parent role
		if(strcmp(m_pLogEditBox->getText(),"P"))
		{
			m_pUser1->setBParent(true);
			m_pUser2->setBParent(false);
		}
		else
		{
			m_pUser1->setBParent(false);
			m_pUser2->setBParent(true);
		}

		m_pUser2->setPScore(0);
		m_pUser2->setPUserName("2nd user");
		m_pUser2->setPUserTabletName("tablet2_name");

		return true;

	}
}

bool LmMenu::menuIsFinished(cocos2d::Ref* l_oSender)
{
	if(!m_bPlayButtonClicked)
	{
		m_bPlayButtonClicked=true;
		Director::getInstance()->getEventDispatcher()->dispatchCustomEvent("MenuFinished");
	}

}
