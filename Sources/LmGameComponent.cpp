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
	m_pSpriteComponent = Sprite::create("background");
}

void LmGameComponent::addTo(Layer* l_Layer,int l_iOrder)
{
	m_pSpriteComponent->addChild(l_Layer,l_iOrder);
}
