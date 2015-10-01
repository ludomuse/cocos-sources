/*
 * LmReward.cpp
 *
 *  Created on: 1 oct. 2015
 *      Author: IHMTEKDev4
 */

#include "../Include/LmReward.h"

using namespace cocos2d;

LmReward::LmReward(std::string l_sFilenameSpriteBackground, std::string l_sFilenameSpriteReward, int l_iRewardScore)
{
	m_sFilenameSpriteBackground=l_sFilenameSpriteBackground;
	m_sFilenameSpriteReward=l_sFilenameSpriteReward;
	m_iRewardScore=l_iRewardScore;
}

LmReward::~LmReward()
{

}

void LmReward::init()
{
	//init the sprite component
	m_pSpriteReward = Sprite::create(m_sFilenameSpriteReward);
	m_pSpriteReward->setAnchorPoint(Vec2(0.5,0.5));

}
