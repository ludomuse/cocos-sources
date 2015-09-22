/*
 * LmGameComponent.cpp
 *
 *  Created on: 2 sept. 2015
 *      Author: IHMTEKDev4
 */

//use for the debug
#define COCOS2D_DEBUG 1

#include "../Include/LmGameComponent.h"

USING_NS_CC;

int LmGameComponent::s_iNumberOfGameComponent=0;

LmGameComponent::LmGameComponent()
{
	//primitive type
	s_iNumberOfGameComponent++;
	m_iId=s_iNumberOfGameComponent;

	//pointer
	m_pSpriteComponent=nullptr;
}

LmGameComponent::~LmGameComponent()
{
	s_iNumberOfGameComponent--;
}

void LmGameComponent::initSpriteComponent(std::string l_sFilename)
{
	m_pSpriteComponent = Sprite::create(l_sFilename);
	m_oSize = m_pSpriteComponent->getContentSize();
}

void LmGameComponent::initSpriteComponent(std::string l_sFilename,const Rect& rect)
{
	m_pSpriteComponent = Sprite::create(l_sFilename,rect);
	m_oSize = m_pSpriteComponent->getContentSize();
}

Size LmGameComponent::getContentSize()const
{
	if(	m_pSpriteComponent)
	{
		return m_oSize;
	}
	else
	{
		CCLOG("LmGameComponent::getContentSize()const - sprite not init");
		return Size(0,0);
	}
}

void LmGameComponent::addTo(cocos2d::Layer* layer)
{
	if(m_pSpriteComponent)
	{
		layer->addChild(m_pSpriteComponent);
	}
	else
	{
		CCLOG("void LmGameComponent::addTo(cocos2d::Layer* layer) - sprite not init");
	}
}

void LmGameComponent::addTo(cocos2d::Layer* layer,int zOrder)
{
	if(m_pSpriteComponent)
	{
		layer->addChild(m_pSpriteComponent, zOrder);
	}
	else
	{
		CCLOG("void LmGameComponent::addTo(cocos2d::Layer* layer,int zOrder) - sprite not init");
	}

}

void  LmGameComponent::removeFrom(Layer* layer)
{
	if(m_pSpriteComponent)
	{
		layer->removeChild(m_pSpriteComponent);
	}
	else
	{
		CCLOG("void  LmGameComponent::removeFrom(Layer* layer) - sprite not init");
	}

}

void LmGameComponent::setPosition(cocos2d::Vec2 vector)
{
	if(m_pSpriteComponent)
	{
		m_pSpriteComponent->setPosition(vector);
	}
	else
	{
		CCLOG("void LmGameComponent::setPosition(cocos2d::Vec2 vector) - sprite not init");
	}

}

void LmGameComponent::setAnchorPoint(cocos2d::Vec2 vector)
{
	if(m_pSpriteComponent)
	{
		m_pSpriteComponent->setAnchorPoint(vector);
	}
	else
	{
		CCLOG("void LmGameComponent::setAnchorPoint(cocos2d::Vec2 vector) - sprite not init");
	}

}

cocos2d::Rect LmGameComponent::getBoundingBoxInWorldSpace(Node* parent)
{
	Point l_oPointInWindowSpace = parent->convertToWorldSpace(m_pSpriteComponent->getPosition());
	//CCLOG("point bounding = %f,%f",l_oPointInWindowSpace.x,l_oPointInWindowSpace.y);

	return Rect(l_oPointInWindowSpace.x,l_oPointInWindowSpace.y,m_oSize.width,m_oSize.height);
}

cocos2d::Vec2 LmGameComponent::getPositionInWorldSpace(Node* parent)const
{
	Point l_oPointInWindowSpace = parent->convertToWorldSpace( m_pSpriteComponent->getPosition());
	return Vec2(l_oPointInWindowSpace.x,l_oPointInWindowSpace.y);
}

void LmGameComponent::setTexture(std::string filename)
{
	m_pSpriteComponent->setTexture(filename);
}

void LmGameComponent::setVisible(bool visible)
{
	m_pSpriteComponent->setVisible(visible);
}




