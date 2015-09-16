/*
 * LmRightSpot.cpp
 *
 *  Created on: 16 sept. 2015
 *      Author: IHMTEKDev4
 */

#include "../Include/LmRightSpotScene.h"

using namespace cocos2d;

LmRightSpotScene::LmRightSpotScene()
{
	//json
	m_sFilenameSpriteBackground="log.png";
	m_sFilenameSpriteCollideZone="sendingArea.png";
	m_aFilenamesSources.push_back("ing.png");


	//other
	m_bFinishButtonSync=true;
}

LmRightSpotScene::~LmRightSpotScene()
{

}

void LmRightSpotScene::runGame()
{
	//use to place elements
	Size l_oVisibleSize = Director::getInstance()->getVisibleSize();
	Point l_oOrigin = Director::getInstance()->getVisibleOrigin();

	//create layer game and add to this
	m_pLayerGame = Layer::create();
	this->addChild(m_pLayerGame);

	//init the two other layer
	m_pLayerUserParent = Layer::create();
	m_pLayerUserChild = Layer::create();

	//init the background
	m_pSpriteBackground = Sprite::create(m_sFilenameSpriteBackground);
	m_pSpriteBackground->setPosition(l_oVisibleSize.width*0.5f+l_oOrigin.x,l_oVisibleSize.height*0.5f+l_oOrigin.y);
	m_pLayerGame->addChild(m_pSpriteBackground);

	//init Sending Area
	m_pSendingArea = new LmGameComponent;
	m_pSendingArea->initSpriteComponent(m_sFilenameSpriteCollideZone);
	m_pSendingArea->setPosition(Vec2(l_oVisibleSize.width-m_pSendingArea->getSpriteSize().width*0.5f+l_oOrigin.x,l_oVisibleSize.height*0.5));
	m_pLayerGame->addChild(m_pSendingArea);

	//finish button
	m_pFinishButton = ui::Button::create("nextButtonNormal.png","nextButtonPressed.png");
	m_pFinishButton->setTouchEnabled(true);
	m_pFinishButton -> setPosition(Vect(l_oVisibleSize.width-m_pFinishButton->getContentSize().width*0.8,m_pFinishButton->getContentSize().height*0.7));
	m_pFinishButton->addTouchEventListener(CC_CALLBACK_0(LmRightSpotScene::endGame, this));
	m_pLayerGame->addChild(m_pFinishButton,1);

	//init


	//we check what type of user is playing to display good stuff
	if(m_pUser->isBParent())
	{
		m_pLayerGame->addChild(m_pLayerUserParent);
	}
	else
	{
		m_pLayerGame->addChild(m_pLayerUserChild);
	}
}

void LmRightSpotScene::endGame()
{
	if(m_bFinishButtonSync)
	{
		m_bFinishButtonSync=false;
		removeChild(m_pLayerGame);
		CCLOG("popscene");
		Director::getInstance()->popScene();
		Director::getInstance()->getEventDispatcher()->dispatchCustomEvent("InteractionSceneFinished");
	}

}
