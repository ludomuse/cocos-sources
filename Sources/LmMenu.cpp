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

LmMenu::LmMenu()
{

}

LmMenu::~LmMenu()
{

}

bool LmMenu::initGame()
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

	//add a background img
	m_pSpriteLogBackground = Sprite::create("titre.png");
	m_pSpriteLogBackground->setPosition(l_oVisibleSize.width/2+l_oOrigin.x,l_oVisibleSize.height/2+l_oOrigin.y);
	m_pLogLayer->addChild(m_pSpriteLogBackground);

	//test button
	//next button
	auto m_pNextButton = ui::Button::create("nextButtonNormal.png","nextButtonPressed.png");
	m_pNextButton->setTouchEnabled(true);
	m_pNextButton -> setPosition(Vect(l_oVisibleSize.width/2+l_oOrigin.x,l_oOrigin.y));
	m_pNextButton->addTouchEventListener(CC_CALLBACK_0(LmMenu::log, this));
	m_pLogLayer->addChild(m_pNextButton,0);

	//user loging
	m_pLogTextfield = ui::TextField::create();
	m_pLogTextfield->setTouchEnabled(true);
	m_pLogTextfield->setPlaceHolder("User name");
	m_pLogTextfield->setPosition(Vect(l_oVisibleSize.width/2+l_oOrigin.x,l_oVisibleSize.height/2+l_oOrigin.y));
	m_pLogLayer->addChild(m_pLogTextfield,1);




	return true;
}

bool LmMenu::log()
{
	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent("MenuFinished");
	return true;
}
