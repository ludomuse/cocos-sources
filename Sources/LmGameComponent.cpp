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

Size LmGameComponent::getSpriteSize()const
{
	return m_pSpriteComponent->getContentSize();
}

