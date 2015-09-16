/*
 * LmGameComponent.h
 *
 * Object which compose our games
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

	void initSpriteComponent(std::string);

	cocos2d::Size getSpriteContentSize()const;

	void setPosition(float,float);

	void setAnchorPoint(float,float);


private:

	cocos2d::Sprite* m_pSpriteComponent;

};



#endif /* CLASSES_LMGAMECOMPONENT_H_ */
