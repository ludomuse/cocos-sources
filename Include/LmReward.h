/*
 * LmReward.h
 *
 *  Created on: 1 oct. 2015
 *      Author: IHMTEKDev4
 *
 *
 */

#ifndef CLASSES_INCLUDE_LMREWARD_H_
#define CLASSES_INCLUDE_LMREWARD_H_

#include "cocos2d.h"

class LmReward
{
public:

	/*
	 * 3 parameters
	 * FilenameSpriteBackground
	 * FilenameSpriteReward
	 * RewardScore
	 */
	LmReward(std::string, std::string, int);
	~LmReward();

	int getIRewardScore() const
	{
		return m_iRewardScore;
	}

	const std::string& getSFilenameSpriteBackground() const
	{
		return m_sFilenameSpriteBackground;
	}

	cocos2d::Sprite* getPSpriteReward() const
	{
		return m_pSpriteReward;
	}

	void init();

private:

	//ATTRIBUTES

	//get from json
	std::string m_sFilenameSpriteBackground;
	std::string m_sFilenameSpriteReward;
	int m_iRewardScore;

	//sprite to add to the button

	cocos2d::Sprite* m_pSpriteReward;

	//METHODS
};

#endif /* CLASSES_INCLUDE_LMREWARD_H_ */
