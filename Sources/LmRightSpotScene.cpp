/*
 * LmRightSpot.cpp
 *
 *  Created on: 16 sept. 2015
 *      Author: IHMTEKDev4
 */

#include "../Include/LmRightSpotScene.h"

using namespace cocos2d;

LmRightSpotScene::LmRightSpotScene(const LmRightSpotSceneSeed &l_Seed ) :
		LmInteractionScene()
{

	//json parameters we need to make deep copy
	m_sFilenameSpriteBackground = l_Seed.FilenameSpriteBackground;
	m_sFilenameSpriteSendingArea = l_Seed.FilenameSpriteSendingArea;
	m_sFilenameMainImage = l_Seed.FilenameMainImage;
	m_iHoleOnX = l_Seed.HoleOnX;
	m_iHoleOnY = l_Seed.HoleOnY;
	m_aLocationOfHole = l_Seed.LocationOfHole;
	if(m_aLocationOfHole.size()==0)
	{
		CCLOG("No Hole in LmRightSpot");
	}

	//primitive type
	m_iBufferId = -1;
	m_bSpriteSelected = false;
	m_bBufferSpriteFillHole = false;
	m_iHoleTouchedIndex = -1;
	m_fHeightRect = 0;
	m_fWidthRect = 0;
	m_bSendingAreaElementTouched = false;

	//pointer
	m_pSendingAreaElement=nullptr;
	m_pBufferSprite = nullptr;
	m_pListener = nullptr;
	m_pSpriteBackground = nullptr;
	m_pSendingArea=nullptr;


}

LmRightSpotScene::~LmRightSpotScene()
{


}

void LmRightSpotScene::restart()
{

}

void LmRightSpotScene::resetScene()
{
	//use to place elements
	Size l_oVisibleSize = Director::getInstance()->getVisibleSize();
	Point l_oOrigin = Director::getInstance()->getVisibleOrigin();
	Size l_oPlayableScreenSize = Size(
			l_oOrigin.x - s_fMarginLeft
					+ (l_oVisibleSize.width
							- m_pSendingArea->getContentSize().width),
			l_oVisibleSize.height);

	if (m_bReplayButtonSync)
	{
		m_bReplayButtonSync = false;

		//all pieces go invisible then we replace it
		for (it_type it = m_aIdTable.begin(); it != m_aIdTable.end(); ++it)
		{
			it->second->setVisible(false);
		}

		m_pSendingArea->setVisible(true);

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

			//reset vector of hole
			m_aHolesLayerParent.clear();

			for (std::vector<LmGameComponent*>::iterator it =
					m_aDynamicGameComponents.begin();
					it != m_aDynamicGameComponents.end(); ++it)
			{
				(*it)->setAnchorPoint(Vec2(0, 0.5));

				(*it)->setPosition(
						Vec2((l_iIndex) * (l_fWidthImage) + s_fMarginLeft,
								l_oPlayableScreenSize.height
										* ((float) l_iLineIndex
												/ (float) (numberOfImageInLine
														+ 1))));

				//create hole associated
				m_aHolesLayerParent.push_back(
						{ Rect((*it)->getPosition().x,
								(*it)->getPosition().y - m_fHeightRect * 0.5,
								m_fWidthRect, m_fHeightRect), (*it)->getIId() });

				(*it)->setVisible(true);

				l_iLineIndex++;

				//last line
				if (l_iLineIndex == numberOfImageInLine + 1)
				{
					l_iLineIndex = 1;
					l_iIndex++;
				}
			}
		}
		else
		{
			//child view

			//set visible all the static element
			for (std::vector<LmGameComponent*>::iterator it =
					m_aStaticGameComponents.begin();
					it != m_aStaticGameComponents.end(); ++it)
			{

				(*it)->setVisible(true);

			}
		}

		m_pReplayButton->setVisible(false);
		m_bReplayButtonSync = false;

	}
}

void LmRightSpotScene::runGame()
{
	if (!initGame())
	{
		CCLOG("initGame failed");
	}

}

bool LmRightSpotScene::initGame()
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

	//init Sending Area
	m_pSendingArea = makeGameComponent();
	m_pSendingArea->initSpriteComponent(m_sFilenameSpriteSendingArea);
	m_pSendingArea->setPosition(
			Vec2(
					l_oVisibleSize.width
							- m_pSendingArea->getContentSize().width * 0.5f
							+ l_oOrigin.x, l_oVisibleSize.height * 0.5));
	m_pSendingArea->addTo(m_pLayerGame);

	//init buffer sprite
	m_pBufferSprite = Sprite::create();
	m_pLayerGame->addChild(m_pBufferSprite,1);

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
	auto l_oSpriteRightImgSpot = Sprite::create(m_sFilenameMainImage);
	float l_fWidthRightImage = l_oSpriteRightImgSpot->getContentSize().width;
	float l_fHeightRightImage = l_oSpriteRightImgSpot->getContentSize().height;
	m_fWidthRect = l_fWidthRightImage / m_iHoleOnX;
	m_fHeightRect = l_fHeightRightImage / m_iHoleOnY;

	Rect l_oRectStencil;

	//test
	int id;

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
			GameComponentCreated->initSpriteComponent(m_sFilenameMainImage,
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

			}

			//all the game component are not visible initiated next
			GameComponentCreated->setVisible(false);

			//add to the both layer
			GameComponentCreated->addTo(m_pLayerGame);

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
					{ Rect((*it)->getPosition().x,
							(*it)->getPosition().y - m_fHeightRect * 0.5,
							m_fWidthRect, m_fHeightRect), (*it)->getIId() });

			(*it)->setVisible(true);

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
				m_pListener, m_pLayerGame);
	}
	else
	{
		//child view

		layerChildReceive(id);

		//set visible all the static element
		for (std::vector<LmGameComponent*>::iterator it =
				m_aStaticGameComponents.begin();
				it != m_aStaticGameComponents.end(); ++it)
		{

			(*it)->setVisible(true);

		}

		//init listener
		m_pListener = EventListenerTouchOneByOne::create();
		m_pListener->onTouchBegan = CC_CALLBACK_2(
				LmRightSpotScene::onTouchBeganChild, this);
		m_pListener->onTouchMoved = CC_CALLBACK_2(
				LmRightSpotScene::onTouchMovedChild, this);
		m_pListener->onTouchEnded = CC_CALLBACK_2(
				LmRightSpotScene::onTouchEndedChild, this);
		Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(
				m_pListener, m_pLayerGame);

		//set visible all the static element
		for (std::vector<LmGameComponent*>::iterator it =
				m_aStaticGameComponents.begin();
				it != m_aStaticGameComponents.end(); ++it)
		{

			(*it)->setVisible(true);

		}
	}

	return true;
}

bool LmRightSpotScene::onTouchBeganParent(Touch* touch, Event* event)
{
	//to avoid to bein a touch when the previous is not finish
	if(m_bUserIsTouchingScreen)
	{
		return false;
	}
	else
	{
		m_bUserIsTouchingScreen=true;
	}

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

		//if the move end on the sending area and it's not the sending area element
		if (bufferCollideSendingArea() && !m_bSendingAreaElementTouched)
		{
			//we send the id to the other tablet test
			CCLOG("we send the %d gamecomponent",
					m_aIdTable.find(m_iBufferId)->first);

			//move gamecomponent
			setPositionInSendingArea(m_iBufferId);

			//if there was already an element in the sending area
			if (m_pSendingAreaElement)
			{
				//place to his last position the current m_psending area element
				auto m_oHoleToFill = holeOfThisDynamicElement(m_pSendingAreaElement->getIId());
				m_pSendingAreaElement->setAnchorPoint(Vec2(0, 0));
				m_pSendingAreaElement->setPosition(
						Vec2(m_oHoleToFill.origin.x, m_oHoleToFill.origin.y));

				//remove the element of the sending area
				m_pSendingAreaElement = nullptr;
			}

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

		m_bSendingAreaElementTouched = false;

		//put it invisible
		m_pBufferSprite->setVisible(false);
		//we put the gamecomponent visible again
		m_aIdTable.find(m_iBufferId)->second->setVisible(true);
	}

	m_bUserIsTouchingScreen=false;


}

bool LmRightSpotScene::onTouchBeganChild(Touch* touch, Event* event)
{
	//to avoid to bein a touch when the previous is not finish
	if(m_bUserIsTouchingScreen)
	{
		return false;
	}
	else
	{
		m_bUserIsTouchingScreen=true;
	}

	m_iBufferId = idLmGameComponentTouchedInSendingArea(touch);

	//if something is touched
	if (m_iBufferId >= 0)
	{
		//init buffer gamecomponent set buffer sprite with his attributes and go invisible
		initBufferSprite(m_iBufferId);
		moveBufferSprite(touch);
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
			m_pBufferSprite->setAnchorPoint(Vec2(0.5, 0.5));
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

				//test
				m_pFinishGameButton->setVisible(true);

			}
			else
			{

				//send back to the void

				CCLOG("send back to parent");
			}

		}

		//put it invisible
		m_pBufferSprite->setVisible(false);
		//we put the gamecomponent visible again
		m_aIdTable.find(m_iBufferId)->second->setVisible(true);

	}

	m_bUserIsTouchingScreen=false;

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
			Vec2(l_oVisibleSize.width - (m_fWidthRect+m_pSendingArea->getContentSize().width)*0.5,
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

	m_pBufferSprite->setSpriteFrame(m_aIdTable.find(l_iIdGameComponent)->second->getPSpriteComponent()->getSpriteFrame());
	m_pBufferSprite->setAnchorPoint(Vec2(0.5, 0.5));
	m_pBufferSprite->setPosition(
			m_aIdTable.find(l_iIdGameComponent)->second->getPosition());
	m_aIdTable.find(l_iIdGameComponent)->second->setVisible(false);
	m_pBufferSprite->setVisible(true);
}

bool LmRightSpotScene::imageWellPlaced(int l_iIndexHole,
		int l_iIdGameComponentPlaced)
{
	return (m_aHolesImageChild.at(l_iIndexHole).second
			== l_iIdGameComponentPlaced);
}

void LmRightSpotScene::layerChildReceive(int l_iIdLmGameComponent)
{

	//we get the gamecomponent with id
	auto l_pGameComponentReceived =
			m_aIdTable.find(l_iIdLmGameComponent)->second;

	//put it approximatly in the sending area(
	setPositionInSendingArea(l_iIdLmGameComponent);
	m_pSendingAreaElement = l_pGameComponentReceived;
	l_pGameComponentReceived->setVisible(true);

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

