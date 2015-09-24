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

LmGameComponent::LmGameComponent(int l_iId)
{
	//primitive type
	m_iId=l_iId;

	//pointer
	m_pSpriteComponent=nullptr;
}

LmGameComponent::~LmGameComponent()
{
}

void LmGameComponent::initSpriteComponent(std::string l_sFilename)
{
	m_pSpriteComponent = Sprite::create(l_sFilename);
	if(m_pSpriteComponent)
	{
		m_oSize = m_pSpriteComponent->getContentSize();
	}}

void LmGameComponent::initSpriteComponent(std::string l_sFilename,const Rect& rect)
{
	m_pSpriteComponent = Sprite::create(l_sFilename,rect);
	if(m_pSpriteComponent)
	{
		m_oSize = m_pSpriteComponent->getContentSize();
	}
}

Size LmGameComponent::getContentSize()const
{
	return m_oSize;
}

void LmGameComponent::addTo(cocos2d::Layer* layer)
{
	if(m_pSpriteComponent)
	{
		layer->addChild(m_pSpriteComponent);
	}
}

void LmGameComponent::addTo(cocos2d::Layer* layer,int zOrder)
{
	if(m_pSpriteComponent)
	{
		layer->addChild(m_pSpriteComponent, zOrder);
	}
}

void  LmGameComponent::removeFrom(Layer* layer)
{
	if(m_pSpriteComponent)
	{
		layer->removeChild(m_pSpriteComponent);
	}

}

void LmGameComponent::setPosition(cocos2d::Vec2 vector)
{
	if(m_pSpriteComponent)
	{
		m_pSpriteComponent->setPosition(vector);
	}

}

void LmGameComponent::setAnchorPoint(cocos2d::Vec2 vector)
{
	if(m_pSpriteComponent)
	{
		m_pSpriteComponent->setAnchorPoint(vector);
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

cocos2d::Vec2 LmGameComponent::getPosition()const
{
	return m_pSpriteComponent->getPosition();
}


void LmGameComponent::setTexture(std::string filename)
{
	m_pSpriteComponent->setTexture(filename);
}

void LmGameComponent::setVisible(bool visible)
{
	m_pSpriteComponent->setVisible(visible);
}

void LmGameComponent::setTexture(cocos2d::Texture2D* texture)
{
	m_pSpriteComponent->setTexture(texture);
}

bool LmGameComponent::sortFromTopLeftToRightBottom(LmGameComponent* l_pLmGameComponent1,LmGameComponent* l_pLmGameComponent2)
{
	bool result=true;

	//order x increasing
	if((l_pLmGameComponent1->getPosition().x)>(l_pLmGameComponent2->getPosition().x))
	{
		result = true;
	}
	else if((l_pLmGameComponent1->getPosition().x)==(l_pLmGameComponent2->getPosition().x))//they are on the same line
	{
		result = ((l_pLmGameComponent1->getPosition().y)<(l_pLmGameComponent2->getPosition().y));
	}
	else
	{
		result = false;
	}

	return !result;
}






