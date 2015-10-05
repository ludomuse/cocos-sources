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
#include "SimpleAudioEngine.h"

class LmReward
{
public:

	/*
	 * 4 parameters
	 * FilenameSpriteBackground
	 * FilenameSpriteReward
	 * RewardScore
	 * FilenameSound
	 */
	LmReward(std::string, std::string, int, std::string);
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

	//play the reward sound
	void playRewardSound();


private:

	//ATTRIBUTES

	//get from json
	std::string m_sFilenameSpriteBackground;
	std::string m_sFilenameSpriteReward;
	int m_iRewardScore;
	std::string m_sFilenameSound;

	//sprite to add to the button
	cocos2d::Sprite* m_pSpriteReward;

	//METHODS


};

#endif /* CLASSES_INCLUDE_LMREWARD_H_ */
