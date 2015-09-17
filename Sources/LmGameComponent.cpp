/*
 * LmGameComponent.cpp
 *
 *  Created on: 2 sept. 2015
 *      Author: IHMTEKDev4
 */

#include "../Include/LmGameComponent.h"

USING_NS_CC;

int LmGameComponent::s_iNumberOfGameComponent=0;

LmGameComponent::LmGameComponent()
{
	s_iNumberOfGameComponent++;
	m_iId=s_iNumberOfGameComponent;
}

LmGameComponent::~LmGameComponent()
{
	s_iNumberOfGameComponent--;
}

void LmGameComponent::initSpriteComponent(std::string l_sFilename)
{
	m_pSpriteComponent = Sprite::create(l_sFilename);
	this->addChild(m_pSpriteComponent);
}

void LmGameComponent::initSpriteComponent(std::string l_sFilename,const Rect& rect)
{
	m_pSpriteComponent = Sprite::create(l_sFilename,rect);
	this->addChild(m_pSpriteComponent);
}

Size LmGameComponent::getSpriteSize()const
{
	return m_pSpriteComponent->getContentSize();
}

