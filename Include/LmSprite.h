/*
 * LmSprite.h
 *
 *  Created on: 29 sept. 2015
 *      Author: http://www.cocos2d-x.org/wiki/How_To_Subclass_Sprite_And_Add_Event_Listeners
 *
 */

#ifndef CLASSES_INCLUDE_LMSPRITE_H_
#define CLASSES_INCLUDE_LMSPRITE_H_

#include "cocos2d.h"

class LmSprite: public cocos2d::Sprite
{
public:
	LmSprite();
	~LmSprite();
	static LmSprite* create(std::string);

	void initOptions();

	void addEvents();
	void touchEvent(cocos2d::Touch* touch);

	void setBTouchEnabled(bool bTouchEnabled)
	{
		m_bTouchEnabled = bTouchEnabled;
	}

private:

	cocos2d::EventListenerTouchOneByOne* m_pListener;
	bool m_bTouchEnabled;

};

#endif /* CLASSES_INCLUDE_LMSPRITE_H_ */
