/*
 * LmGameComponent.cpp
 *
 *  Created on: 2 sept. 2015
 *      Author: IHMTEKDev4
 */

#include "../Include/LmGameComponent.h"

USING_NS_CC;

LmGameComponent::LmGameComponent()
{

}

LmGameComponent::~LmGameComponent()
{

}

void LmGameComponent::initSpriteComponent(std::string l_sFilename)
{
	m_pSpriteComponent = Sprite::create(l_sFilename);
	this->addChild(m_pSpriteComponent);
}

cocos2d::Size LmGameComponent::getSpriteContentSize()const
{
	return m_pSpriteComponent->getContentSize();
}

void LmGameComponent::setPosition(float x,float y)
{
	m_pSpriteComponent->setPosition(Vec2(x,y));
}

void LmGameComponent::setAnchorPoint(float x,float y)
{
	m_pSpriteComponent->setAnchorPoint(Vec2(x,y));
}

