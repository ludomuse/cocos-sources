/*
 * LmGameComponent.h
 *
 * Object which compose our games extend cocos2d::node
 *
 *  Created on: 2 sept. 2015
 *      Author: IHMTEKDev4
 */

#ifndef CLASSES_LMGAMECOMPONENT_H_
#define CLASSES_LMGAMECOMPONENT_H_

#include "cocos2d.h"

class LmGameComponent : public cocos2d::Node
{
public:

	LmGameComponent();
	~LmGameComponent();

	//init the sprite component with a filename then add it to this
	void initSpriteComponent(std::string);
	void initSpriteComponent(std::string,const cocos2d::Rect&);

	cocos2d::Size getSpriteSize()const;

	int getIId() const {
		return m_iId;
	}

	static int s_iNumberOfGameComponent;


private:

	cocos2d::Sprite* m_pSpriteComponent;

	int m_iId;

};



#endif /* CLASSES_LMGAMECOMPONENT_H_ */
