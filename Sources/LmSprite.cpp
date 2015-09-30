/*
 * LmSprite.cpp
 *
 *  Created on: 29 sept. 2015
 *      Author: IHMTEKDev4
 */

#include "../Include/LmSprite.h"

using namespace cocos2d;

LmSprite::LmSprite()
{
	//primitive type
	m_bTouchEnabled = true;

	//pointer
	m_pListener = nullptr;
}

LmSprite::~LmSprite()
{
	Director::getInstance()->getEventDispatcher()->removeEventListener(
			m_pListener);
}

LmSprite* LmSprite::create(std::string l_sFilename)
{
	LmSprite* pSprite = new LmSprite();

	if (pSprite->initWithFile(l_sFilename))
	{
		pSprite->autorelease();

		pSprite->initOptions();

		pSprite->addEvents();

		return pSprite;
	}
	CC_SAFE_DELETE(pSprite);
	return NULL;
}

void LmSprite::initOptions()
{
	// do things here like setTag(), setPosition(), any custom logic.
}

void LmSprite::addEvents()
{
	m_pListener = cocos2d::EventListenerTouchOneByOne::create();
	m_pListener->setSwallowTouches(true);

	m_pListener->onTouchBegan =
			[&](cocos2d::Touch* touch, cocos2d::Event* event)
			{
				if(m_bTouchEnabled)
				{
					CCLOG("touch enable");
					cocos2d::Vec2 p = touch->getLocation();

					cocos2d::Rect rect = this->getBoundingBox();

					if(rect.containsPoint(p))
					{
						CCLOG("LmSpriteTouched");
						return true; // to indicate that we have consumed it.
					}

					return false; // we did not consume this event, pass thru.
				}
				else
				{
					return false;
				}

			};

	m_pListener->onTouchEnded =
			[=](cocos2d::Touch* touch, cocos2d::Event* event)
			{
				LmSprite::touchEvent(touch);
			};

	cocos2d::Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(
			m_pListener, this);
}

void LmSprite::touchEvent(cocos2d::Touch* touch)
{

}

