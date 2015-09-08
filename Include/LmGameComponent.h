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

class LmGameComponent
{
public:

	LmGameComponent();
	~LmGameComponent();

	//add this gameobject to this layer and specify the z-order
	void addTo(cocos2d::Layer*, int);



private:

	cocos2d::Sprite* m_pSpriteComponent;


};



#endif /* CLASSES_LMGAMECOMPONENT_H_ */
