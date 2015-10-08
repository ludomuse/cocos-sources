/*
 * LmAudioHintScene.cpp
 *
 *  Created on: 7 oct. 2015
 *      Author: IHMTEKDev4
 */

#include "../Include/LmAudioHintScene.h"

using namespace cocos2d;

LmAudioHintScene::LmAudioHintScene(const LmAudioHintSceneSeed &l_Seed)
{
	//from json
	m_sFilenameSpriteBackground = l_Seed.FilenameSpriteBackground;
	m_sFilenameSpriteMainImage = l_Seed.FilenameSpriteMainImage;
	m_aLabelsFilenameSprite = l_Seed.LabelsFilenameSprite;
	m_aLabelsFilenameAudio = l_Seed.LabelsFilenameAudio;
	m_aLabelsCoordonateHole = l_Seed.LabelsCoordonateHole;

	//primitive type
	m_bBufferSpriteFillHole = false;
	m_iBufferId = -1;
	m_iHoleTouchedIndex = -1;
	m_bSpriteSelected = false;

	//pointer
	m_pSpriteBackground = nullptr;
	m_pSpriteMainImage = nullptr;
	m_pBufferSprite = nullptr;

}

LmAudioHintScene::~LmAudioHintScene()
{

}

void LmAudioHintScene::restart()
{

}

void LmAudioHintScene::resetScene()
{

}

void LmAudioHintScene::runGame()
{
	if (!initGame())
	{
		CCLOG("initGame failed");
	}

	//preload all sound
	for (std::map<int, std::string>::iterator it =
			m_aLabelsFilenameAudio.begin(); it != m_aLabelsFilenameAudio.end();
			++it)
	{
		CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic(
				it->second.c_str());
	}

}

bool LmAudioHintScene::initGame()
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

	//init main image so we can get his dimension
	m_pSpriteMainImage = Sprite::create(m_sFilenameSpriteMainImage);
	m_pSpriteMainImage->setAnchorPoint(Vec2(0, 0.5));
	m_pSpriteMainImage->setPosition(s_fMarginLeft,
			l_oVisibleSize.height * 0.5f);
	m_pLayerGame->addChild(m_pSpriteMainImage);

	//init buffer sprite
	m_pBufferSprite = Sprite::create();
	m_pLayerGame->addChild(m_pBufferSprite, 1);

	//use to place element
	int l_iIndex = 0;
	LmGameComponent* l_pGameComponentCreated;
	MenuItemImage* l_pMenuItemImageCreated;

	// create menu, it's an autorelease object
	auto l_oMenu = Menu::create();
	l_oMenu->setPosition(Vec2::ZERO);
	m_pLayerGame->addChild(l_oMenu, 1);

	//init labels gamecomponent
	for (std::map<int, std::string>::iterator it =
			m_aLabelsFilenameSprite.begin();
			it != m_aLabelsFilenameSprite.end(); ++it)
	{
		//init game component
		l_pGameComponentCreated = makeGameComponent();
		m_aLabelsGameComponent.insert(
		{ it->first, l_pGameComponentCreated });
		l_pGameComponentCreated->initSpriteComponent(it->second);
		//place on the game
		l_pGameComponentCreated->setAnchorPoint(Vec2(1, 0.5));
		l_pGameComponentCreated->setPosition(
				Vec2(l_oVisibleSize.width,
						(l_iIndex + 1) * l_oVisibleSize.height
								/ (s_iNumberLabel + 1)));
		l_pGameComponentCreated->addTo(m_pLayerGame);
		l_pGameComponentCreated->setVisible(false);

		//init menuitem image

		l_pMenuItemImageCreated = MenuItemImage::create();

		l_pMenuItemImageCreated = MenuItemImage::create(
				"Ludomuse/GUIElements/logNormal.png",
				"Ludomuse/GUIElements/logPressed.png",
				CC_CALLBACK_1(LmAudioHintScene::menuItemImagePressed, this));

		//we get coordonnate in percent from json
		Vec2 l_oPosition = Vec2(
				(m_aLabelsCoordonateHole.find(it->first)->second.x
						* m_pSpriteMainImage->getContentSize().width / 100)
						+ s_fMarginLeft,
				((m_aLabelsCoordonateHole.find(it->first)->second.y - 50)
						* m_pSpriteMainImage->getContentSize().height / 100)
						+ l_oVisibleSize.height * 0.5);

		//init menuitemiamge
		l_pMenuItemImageCreated->setAnchorPoint(Vec2(0.5, 0.5));
		l_pMenuItemImageCreated->setPosition(l_oPosition);
		l_pMenuItemImageCreated->setVisible(false);

		m_aLabelsMenuItemImage.insert(
		{ l_pMenuItemImageCreated, it->first });
		l_oMenu->addChild(l_pMenuItemImageCreated);

		//init hole set aposition according the anchor point
		m_aLabelsHole.insert(
				{ it->first,
						Rect(
								l_oPosition.x
										- l_pGameComponentCreated->getContentSize().width
												* 0.5,
								l_oPosition.y
										- l_pGameComponentCreated->getContentSize().height
												* 0.5,
								l_pGameComponentCreated->getContentSize().width,
								l_pGameComponentCreated->getContentSize().height) });

		l_iIndex++;
	}

	//check what type of user
	if (m_pUser->isBParent())
	{
		//put label visible
		for (std::map<int, LmGameComponent*>::iterator it =
				m_aLabelsGameComponent.begin();
				it != m_aLabelsGameComponent.end(); ++it)
		{
			it->second->setVisible(true);
		}

		//init listener
		m_pListener = EventListenerTouchOneByOne::create();
		m_pListener->onTouchBegan = CC_CALLBACK_2(
				LmAudioHintScene::onTouchBeganParent, this);
		m_pListener->onTouchMoved = CC_CALLBACK_2(
				LmAudioHintScene::onTouchMovedParent, this);
		m_pListener->onTouchEnded = CC_CALLBACK_2(
				LmAudioHintScene::onTouchEndedParent, this);
		Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(
				m_pListener, m_pLayerGame);
	}
	else
	{
		//put button visible
		for (std::map<MenuItemImage*, int>::iterator it =
				m_aLabelsMenuItemImage.begin();
				it != m_aLabelsMenuItemImage.end(); ++it)
		{
			it->first->setVisible(true);
		}
	}

	return true;
}

bool LmAudioHintScene::menuItemImagePressed(cocos2d::Ref* pSender)
{

	CocosDenshion::SimpleAudioEngine::getInstance()->stopAllEffects();

	auto l_pMenuItemPressed = dynamic_cast<MenuItemImage*>(pSender);

	int l_iIdLabel = m_aLabelsMenuItemImage.find(l_pMenuItemPressed)->second;

	//play sound
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(
			m_aLabelsFilenameAudio.find(l_iIdLabel)->second.c_str(), false);

	return true;
}

//callback method of parent layer
bool LmAudioHintScene::onTouchBeganParent(cocos2d::Touch* touch,
		cocos2d::Event* event)
{
	//to avoid to bein a touch when the previous is not finish
	if (m_bUserIsTouchingScreen)
	{
		return false;
	}
	else
	{
		m_bUserIsTouchingScreen = true;
	}
	//get id label
	m_iBufferId = idLabel(touch);
	//if something is touched
	if (m_iBufferId >= 0)
	{
		//init buffer gamecomponent set buffer sprite with his attributes and go invisible
		initBufferSprite(m_iBufferId);
		CCLOG("after init");
		moveBufferSprite(touch);
		CCLOG("afetr move");
	}
	else
	{
		m_bSpriteSelected = false;
	}

	return true;
}

void LmAudioHintScene::onTouchMovedParent(cocos2d::Touch* touch,
		cocos2d::Event* event)
{
	if (m_bSpriteSelected)
	{
		moveBufferSprite(touch);

		m_iHoleTouchedIndex = touchCollideHole(touch);

		if (m_iHoleTouchedIndex >= 0)
		{

			auto l_oHoleTouched =
					m_aLabelsHole.find(m_iHoleTouchedIndex)->second;
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

void LmAudioHintScene::onTouchEndedParent(cocos2d::Touch* touch,
		cocos2d::Event* event)
{
	if (m_bSpriteSelected)
	{

		//no sprite selected anymore
		m_bSpriteSelected = false;

		//if when we end movement an hole is filled we operate change in vector
		if (m_bBufferSpriteFillHole)
		{

			//check if its good position
			if (m_iHoleTouchedIndex == m_iBufferId)
			{

				//we change position of this gameobject to that hole
				m_aLabelsGameComponent.find(m_iBufferId)->second->setAnchorPoint(
						Vec2(0, 0));
				m_aLabelsGameComponent.find(m_iBufferId)->second->setPosition(
						Vec2(
								m_aLabelsHole.find(m_iHoleTouchedIndex)->second.origin.x,
								m_aLabelsHole.find(m_iHoleTouchedIndex)->second.origin.y));

				//test
				m_pFinishGameButton->setVisible(true);

			}
			else
			{

				//send back to the void
				CCLOG("not well placed");
			}

		}

		//put it invisible
		m_pBufferSprite->setVisible(false);
		//we put the gamecomponent visible again
		m_aLabelsGameComponent.find(m_iBufferId)->second->setVisible(true);

	}
	m_bUserIsTouchingScreen = false;
}

int LmAudioHintScene::idLabel(cocos2d::Touch* touch)
{
	auto l_oTouchLocation = touch->getLocation();

	for (std::map<int, LmGameComponent*>::iterator it =
			m_aLabelsGameComponent.begin(); it != m_aLabelsGameComponent.end();
			++it)
	{

		if (it->second->getPSpriteComponent()->getBoundingBox().containsPoint(
				l_oTouchLocation))
		{
			return it->first;
		}
	}
	return -1;
}

void LmAudioHintScene::initBufferSprite(int l_iIdGameComponent)
{
	//the sprite is selected
	m_bSpriteSelected = true;
	//the gamecomponent selected is copy in the buffer
	CCLOG("0");
	m_pBufferSprite->setSpriteFrame(
			m_aLabelsGameComponent.find(l_iIdGameComponent)->second->getPSpriteComponent()->getSpriteFrame());
	CCLOG("1");
	m_pBufferSprite->setAnchorPoint(Vec2(0.5, 0.5));
	m_pBufferSprite->setPosition(
			m_aLabelsGameComponent.find(l_iIdGameComponent)->second->getPosition());
	m_aLabelsGameComponent.find(l_iIdGameComponent)->second->setVisible(false);
	CCLOG("2");
	m_pBufferSprite->setVisible(true);
}

void LmAudioHintScene::moveBufferSprite(Touch* touch)
{
	auto l_oTouchLocation = touch->getLocation();
	m_pBufferSprite->setPosition(Vec2(l_oTouchLocation.x, l_oTouchLocation.y));
}

int LmAudioHintScene::touchCollideHole(Touch* touch)
{
	auto l_oTouchLocation = touch->getLocation();

	for (std::map<int, Rect>::iterator it = m_aLabelsHole.begin();
			it != m_aLabelsHole.end(); ++it)
	{
		if (it->second.containsPoint(l_oTouchLocation))
		{
			return it->first;
		}
	}

	return -1;
}

