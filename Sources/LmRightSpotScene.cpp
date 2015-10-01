/*
 * LmRightSpot.cpp
 *
 *  Created on: 16 sept. 2015
 *      Author: IHMTEKDev4
 */

#include "../Include/LmRightSpotScene.h"

using namespace cocos2d;

LmRightSpotScene::LmRightSpotScene(std::string l_sFilenameSpriteBackground,
		std::string l_sFilenameSpriteCollideZone,
		std::string l_sFilenameRightImage, int l_iHoleOnX, int l_iHoleOnY,
		std::vector<std::pair<int, int>> l_aLocationOfHole) :
		LmInteractionScene()
{

	//json parameters we need to make deep copy
	m_sFilenameSpriteBackground = l_sFilenameSpriteBackground.c_str();
	m_sFilenameSpriteCollideZone = l_sFilenameSpriteCollideZone.c_str();

	m_sFilenameRightImage = l_sFilenameRightImage.c_str();
	m_iHoleOnX = l_iHoleOnX;
	m_iHoleOnY = l_iHoleOnY;
	m_aLocationOfHole = l_aLocationOfHole;

	//primitive type
	m_iBufferId = -1;
	m_bSpriteSelected = false;
	m_bBufferSpriteFillHole = false;
	m_iHoleTouchedIndex = -1;
	m_fHeightRect = 0;
	m_fWidthRect = 0;
	m_bWin = false;
	m_bSendingAreaElementTouched = false;

	//pointer
	m_pBufferSprite = nullptr;
	m_pListener = nullptr;
	m_pSpriteBackground = nullptr;

}

LmRightSpotScene::~LmRightSpotScene()
{
	//destroy all gamecomponent

	for (it_type it = m_aIdTable.begin(); it != m_aIdTable.end(); ++it)
	{
		//destroy the pointer on the LmGameComponent
		delete it->second;
	}

	Director::getInstance()->getEventDispatcher()->removeEventListener(
			m_pListener);

}

void LmRightSpotScene::restart()
{

}


void LmRightSpotScene::runGame()
{
	if (!initGame())
	{
		CCLOG("initGame failed");
	}

	//we preload the sound
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic(
			"audio/son.mp3");
}

bool LmRightSpotScene::initGame()
{
	//use to place elements
	Size l_oVisibleSize = Director::getInstance()->getVisibleSize();
	Point l_oOrigin = Director::getInstance()->getVisibleOrigin();

	//add the layer game
	this->addChild(m_pLayerGame, 0);

	//init the two other layer
	m_pLayerUserParent = Layer::create();
	m_pLayerUserChild = Layer::create();

	//init the background
	m_pSpriteBackground = Sprite::create(m_sFilenameSpriteBackground);
	m_pSpriteBackground->setPosition(l_oVisibleSize.width * 0.5f + l_oOrigin.x,
			l_oVisibleSize.height * 0.5f + l_oOrigin.y);
	m_pLayerGame->addChild(m_pSpriteBackground);

	//init Sending Area
	m_pSendingArea = makeGameComponent();
	m_pSendingArea->initSpriteComponent(m_sFilenameSpriteCollideZone);
	m_pSendingArea->setPosition(
			Vec2(
					l_oVisibleSize.width
							- m_pSendingArea->getContentSize().width * 0.5f
							+ l_oOrigin.x, l_oVisibleSize.height * 0.5));
	m_pSendingArea->addTo(m_pLayerGame);

	//init some usefull variable
	Point l_oMiddleOfPlayableArea = Point(
			l_oOrigin.x
					+ (l_oVisibleSize.width
							- m_pSendingArea->getContentSize().width) * 0.5f,
			l_oVisibleSize.height * 0.5f + l_oOrigin.y);
	Size l_oPlayableScreenSize = Size(
			l_oOrigin.x - s_fMarginLeft
					+ (l_oVisibleSize.width
							- m_pSendingArea->getContentSize().width),
			l_oVisibleSize.height);

	//we get dimension of the image
	auto l_oSpriteRightImgSpot = Sprite::create(m_sFilenameRightImage);
	float l_fWidthRightImage = l_oSpriteRightImgSpot->getContentSize().width;
	float l_fHeightRightImage = l_oSpriteRightImgSpot->getContentSize().height;
	m_fWidthRect = l_fWidthRightImage / m_iHoleOnX;
	m_fHeightRect = l_fHeightRightImage / m_iHoleOnY;

	Rect l_oRectStencil;

	//test
	int id;
	m_pFinishGameButton->setVisible(true);

	//init vector of the right image
	Point l_oPointToPlaceRightImage = Point(
			l_oMiddleOfPlayableArea.x - l_fWidthRightImage * 0.5,
			l_oMiddleOfPlayableArea.y - l_fHeightRightImage * 0.5);

	for (int i = 0; i < m_iHoleOnX; i++)
	{
		for (int j = 0; j < m_iHoleOnY; j++)
		{
			//get the stencil
			l_oRectStencil = Rect(m_fWidthRect * i, m_fHeightRect * j,
					m_fWidthRect, m_fHeightRect);

			//position to place hole and fix elements
			Vec2 l_oVectorPosition = Vec2(
					m_fWidthRect * i + l_oPointToPlaceRightImage.x,
					(m_iHoleOnY - (j + 1)) * m_fHeightRect
							+ l_oPointToPlaceRightImage.y);
			//create gamecomponent
			LmGameComponent* GameComponentCreated = makeGameComponent();
			GameComponentCreated->initSpriteComponent(m_sFilenameRightImage,
					l_oRectStencil);

			//check if this piece is a hole
			std::vector<std::pair<int, int>>::iterator it;
			std::pair<int, int> l_PairBuffer =
			{ i, j };
			it = std::find(m_aLocationOfHole.begin(), m_aLocationOfHole.end(),
					l_PairBuffer);
			//yes
			if (it != m_aLocationOfHole.end())
			{
				//add this piece to the dynamic elements
				m_aDynamicGameComponents.push_back(GameComponentCreated);

				//test to have dynamic piece already in the layer child
				id = GameComponentCreated->getIId();

				//we add an hole to the image layer child
				m_aHolesImageChild.push_back(
						{ Rect(l_oVectorPosition.x, l_oVectorPosition.y,
								m_fWidthRect, m_fHeightRect),
								GameComponentCreated->getIId() });

			}
			else
			{

				//push to the fix element vector
				m_aStaticGameComponents.push_back(GameComponentCreated);

				//we set position and add it to layer child
				GameComponentCreated->setAnchorPoint(Vec2(0, 0));
				GameComponentCreated->setPosition(l_oVectorPosition);
				GameComponentCreated->addTo(m_pLayerUserChild);

			}
		}
	}

	//we check what type of user is playing to display good stuff
	if (m_pUser->isBParent())
	{
		//parent view

		//use to place elements
		auto l_fWidthImage = m_fWidthRect + s_fMarginBetweenImage;
		auto l_fHeightImage = m_fHeightRect + s_fMarginBetweenImage;

		//check height of piece to know how many to display in a row
		int numberOfImageInLine = (int) l_oPlayableScreenSize.height
				/ l_fHeightImage;

		//shuffle the vector
		std::random_device rd;
		std::mt19937 g(rd());
		std::shuffle(m_aDynamicGameComponents.begin(),
				m_aDynamicGameComponents.end(), g);

		int l_iIndex = 0;

		int l_iLineIndex = 1;

		for (std::vector<LmGameComponent*>::iterator it =
				m_aDynamicGameComponents.begin();
				it != m_aDynamicGameComponents.end(); ++it)
		{
			(*it)->setAnchorPoint(Vec2(0, 0.5));

			(*it)->setPosition(
					Vec2((l_iIndex) * (l_fWidthImage) + s_fMarginLeft,
							l_oPlayableScreenSize.height
									* ((float) l_iLineIndex
											/ (float) (numberOfImageInLine + 1))));

			//create hole associated
			m_aHolesLayerParent.push_back(
					{	Rect((*it)->getPosition().x,(*it)->getPosition().y-m_fHeightRect*0.5,m_fWidthRect,m_fHeightRect),(*it)->getIId()});


			(*it)->addTo(m_pLayerUserParent);

			l_iLineIndex++;

			//last line
			if (l_iLineIndex == numberOfImageInLine + 1)
			{
				l_iLineIndex = 1;
				l_iIndex++;
			}
		}

		//init listener
		m_pListener = EventListenerTouchOneByOne::create();
		m_pListener->onTouchBegan = CC_CALLBACK_2(
				LmRightSpotScene::onTouchBeganParent, this);
		m_pListener->onTouchMoved = CC_CALLBACK_2(
				LmRightSpotScene::onTouchMovedParent, this);
		m_pListener->onTouchEnded = CC_CALLBACK_2(
				LmRightSpotScene::onTouchEndedParent, this);
		Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(
				m_pListener, m_pLayerUserParent);

		//add the layer to the game
		m_pLayerGame->addChild(m_pLayerUserParent);

	}
	else
	{
		//child view

		layerChildReceive(id);

		//init listener
		m_pListener = EventListenerTouchOneByOne::create();
		m_pListener->onTouchBegan = CC_CALLBACK_2(
				LmRightSpotScene::onTouchBeganChild, this);
		m_pListener->onTouchMoved = CC_CALLBACK_2(
				LmRightSpotScene::onTouchMovedChild, this);
		m_pListener->onTouchEnded = CC_CALLBACK_2(
				LmRightSpotScene::onTouchEndedChild, this);
		Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(
				m_pListener, m_pLayerUserChild);

		//add the layer to the game
		m_pLayerGame->addChild(m_pLayerUserChild);
	}

	return true;
}

bool LmRightSpotScene::onTouchBeganParent(Touch* touch, Event* event)
{
	m_iBufferId = idDynamicLmGameComponent(touch);

	//if something is touched
	if (m_iBufferId >= 0)
	{
		//check if its the sending area element
		if (m_pSendingAreaElement)
		{
			if (m_pSendingAreaElement->getIId() == m_iBufferId)
			{
				m_bSendingAreaElementTouched = true;
			}
			else
			{
				m_bSendingAreaElementTouched = false;
			}
		}

		//init buffer gamecomponent set buffer sprite with his attributes and go invisible
		initBufferSprite(m_iBufferId);
		moveBufferSprite(touch);
		m_pLayerUserParent->addChild(m_pBufferSprite);
	}
	else
	{
		m_bSpriteSelected = false;
	}

	return true;
}

void LmRightSpotScene::onTouchMovedParent(Touch* touch, Event* event)
{
	if (m_bSpriteSelected)
	{

		moveBufferSprite(touch);
	}

}

void LmRightSpotScene::onTouchEndedParent(cocos2d::Touch*, cocos2d::Event*)
{
	if (m_bSpriteSelected)
	{
		//no sprite selected anymore
		m_bSpriteSelected = false;

		if (bufferCollideSendingArea() && !m_bSendingAreaElementTouched)
		{
			//we send the id to the other tablet test
			CCLOG("we send the %d gamecomponent",
					m_aIdTable.find(m_iBufferId)->first);

			//create an hole
			m_aIdTable.find(m_iBufferId)->second->setAnchorPoint(Vec2(0, 0)); // get good position

			//move gamecomponent
			setPositionInSendingArea(m_iBufferId);
			m_pSendingAreaElement = m_aIdTable.find(m_iBufferId)->second;

		}
		else if (m_bSendingAreaElementTouched && !bufferCollideSendingArea())
		{

			//place to his last position
			auto m_oHoleToFill = holeOfThisDynamicElement(m_iBufferId);
			m_pSendingAreaElement->setAnchorPoint(Vec2(0, 0));
			m_pSendingAreaElement->setPosition(
					Vec2(m_oHoleToFill.origin.x, m_oHoleToFill.origin.y));

			//remove the element of the sending area
			m_pSendingAreaElement = nullptr;
		}

		if (m_pSendingAreaElement)
		{
			CCLOG("there is an element in the sending area");
		}

		m_bSendingAreaElementTouched = false;
		//remove the buffer sprite froim the layer
		m_pLayerUserParent->removeChild(m_pBufferSprite);
		//we put the gamecomponent visible again
		m_aIdTable.find(m_iBufferId)->second->setVisible(true);
	}

}

bool LmRightSpotScene::onTouchBeganChild(Touch* touch, Event* event)
{
	m_iBufferId = idLmGameComponentTouchedInSendingArea(touch);

	//if something is touched
	if (m_iBufferId >= 0)
	{
		//init buffer gamecomponent set buffer sprite with his attributes and go invisible
		initBufferSprite(m_iBufferId);
		moveBufferSprite(touch);
		m_pLayerUserChild->addChild(m_pBufferSprite);
	}
	else
	{
		m_bSpriteSelected = false;
	}

	return true;
}

void LmRightSpotScene::onTouchMovedChild(Touch* touch, Event* event)
{
	if (m_bSpriteSelected)
	{
		moveBufferSprite(touch);

		m_iHoleTouchedIndex = touchCollideHoleInRightImage(touch);

		if (m_iHoleTouchedIndex >= 0)
		{

			auto l_oHoleTouched =
					m_aHolesImageChild.at(m_iHoleTouchedIndex).first;
			//we move the buffer sprite to this position
			m_pBufferSprite->setAnchorPoint(Vec2(0, 0));
			m_pBufferSprite->setPosition(
					Vec2(l_oHoleTouched.origin.x, l_oHoleTouched.origin.y));
			m_bBufferSpriteFillHole = true;
		}
		else
		{
			m_bBufferSpriteFillHole = false;
		}

	}
}

void LmRightSpotScene::onTouchEndedChild(Touch* touch, Event* event)
{
	if (m_bSpriteSelected)
	{

		//no sprite selected anymore
		m_bSpriteSelected = false;

		//if when we end movement an hole is filled we operate change in vector
		if (m_bBufferSpriteFillHole)
		{

			//check if its good position
			if (imageWellPlaced(m_iHoleTouchedIndex, m_iBufferId))
			{

				//we change position of this gameobject to that hole
				m_pSendingAreaElement->setAnchorPoint(Vec2(0, 0));
				m_pSendingAreaElement->setPosition(
						Vec2(
								m_aHolesImageChild.at(m_iHoleTouchedIndex).first.origin.x,
								m_aHolesImageChild.at(m_iHoleTouchedIndex).first.origin.y));

				//reset sendingelement
				m_pSendingAreaElement = nullptr;

			}
			else
			{

				//send back to the void

				CCLOG("send back to parent");
			}

		}

		//remove the buffer sprite froim the layer
		m_pLayerUserChild->removeChild(m_pBufferSprite);
		//we put the gamecomponent visible again
		m_aIdTable.find(m_iBufferId)->second->setVisible(true);

	}

}

int LmRightSpotScene::idDynamicLmGameComponent(Touch* touch)
{
	auto l_oTouchLocation = touch->getLocation();

	for (std::vector<LmGameComponent*>::iterator it =
			m_aDynamicGameComponents.begin();
			it != m_aDynamicGameComponents.end(); ++it)
	{

		if ((*it)->getPSpriteComponent()->getBoundingBox().containsPoint(
				l_oTouchLocation))
		{
			return (*it)->getIId();
		}
	}
	return -1;
}

int LmRightSpotScene::idLmGameComponentTouchedInSendingArea(Touch* touch)
{
	if (m_pSendingAreaElement)
	{
		auto l_oTouchLocation = touch->getLocation();

		if (m_pSendingAreaElement->getPSpriteComponent()->getBoundingBox().containsPoint(
				l_oTouchLocation))
		{
			return m_pSendingAreaElement->getIId();
		}
	}
	else
	{
		CCLOG("sending area empty");
	}

	return -1;
}

int LmRightSpotScene::touchCollideHoleInRightImage(Touch* touch)
{
	auto l_oTouchLocation = touch->getLocation();

	for (int i = 0; i < m_aHolesImageChild.size(); i++)
	{
		if (m_aHolesImageChild.at(i).first.containsPoint(l_oTouchLocation))
		{
			return i;
		}
	}
	return -1;
}

bool LmRightSpotScene::bufferCollideSendingArea()
{
	return m_pBufferSprite->getBoundingBox().intersectsRect(
			m_pSendingArea->getPSpriteComponent()->getBoundingBox());
}

void LmRightSpotScene::setPositionInSendingArea(int id)
{
	//use to place elements
	Size l_oVisibleSize = Director::getInstance()->getVisibleSize();
	Point l_oOrigin = Director::getInstance()->getVisibleOrigin();

	m_aIdTable.find(id)->second->setAnchorPoint(Vec2(0, 0.5));
	m_aIdTable.find(id)->second->setPosition(
			Vec2(l_oVisibleSize.width - m_pSendingArea->getContentSize().width,
					l_oVisibleSize.height * 0.5));
}

void LmRightSpotScene::moveBufferSprite(Touch* touch)
{
	auto l_oTouchLocation = touch->getLocation();
	m_pBufferSprite->setPosition(Vec2(l_oTouchLocation.x, l_oTouchLocation.y));
}

void LmRightSpotScene::initBufferSprite(int l_iIdGameComponent)
{
	//the sprite is selected
	m_bSpriteSelected = true;
	//the gamecomponent selected is copy in the buffer
	m_pBufferSprite =
			Sprite::createWithSpriteFrame(
					m_aIdTable.find(l_iIdGameComponent)->second->getPSpriteComponent()->getSpriteFrame());
	m_pBufferSprite->setAnchorPoint(Vec2(0.5, 0.5));
	m_pBufferSprite->setPosition(
			m_aIdTable.find(l_iIdGameComponent)->second->getPosition());
	m_aIdTable.find(l_iIdGameComponent)->second->setVisible(false);
}

bool LmRightSpotScene::imageWellPlaced(int l_iIndexHole,
		int l_iIdGameComponentPlaced)
{
	return (m_aHolesImageChild.at(l_iIndexHole).second
			== l_iIdGameComponentPlaced);
}

void LmRightSpotScene::layerChildReceive(int l_iIdLmGameComponent)
{
	//use to place elements
	Size l_oVisibleSize = Director::getInstance()->getVisibleSize();
	Point l_oOrigin = Director::getInstance()->getVisibleOrigin();

	//we get the gamecomponent with id
	auto l_pGameComponentReceived =
			m_aIdTable.find(l_iIdLmGameComponent)->second;

	//put it approximatly in the sending area(
	setPositionInSendingArea(l_iIdLmGameComponent);
	m_pSendingAreaElement = l_pGameComponentReceived;
	l_pGameComponentReceived->addTo(m_pLayerUserChild);

}

Rect LmRightSpotScene::holeOfThisDynamicElement(int l_iIdGamecomponent)
{
	for (int i = 0; i < m_aHolesLayerParent.size(); i++)
	{
		if (m_aHolesLayerParent.at(i).second == l_iIdGamecomponent)
		{
			return m_aHolesLayerParent.at(i).first;
		}
	}

	CCLOG("error no hole found");
	return Rect::ZERO;
}

