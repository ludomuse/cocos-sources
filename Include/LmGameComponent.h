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

class LmGameComponent
{
public:

	LmGameComponent();
	~LmGameComponent();

	//use to give id to all the gamecomponent
	static int s_iNumberOfGameComponent;

	//init the sprite component with a filename (and a stencil)
	void initSpriteComponent(std::string);
	void initSpriteComponent(std::string,const cocos2d::Rect&);

	//return the size of the sprite component
	cocos2d::Size getContentSize()const;

	//return the id of this gamecomponent
	int getIId() const {return m_iId;}

	//return the sprite component
	cocos2d::Sprite* getPSpriteComponent() const {return m_pSpriteComponent;}

	//to handle add/remove of a layer
	void addTo(cocos2d::Layer*);
	void addTo(cocos2d::Layer*,int);
	void removeFrom(cocos2d::Layer*);

	//handle position
	void setPosition(cocos2d::Vec2);
	void setAnchorPoint(cocos2d::Vec2);

	//change the texture of the sprite component
	void setTexture(std::string);

	//return the bounding in the UIWindow space
	cocos2d::Rect getBoundingBoxInWorldSpace(cocos2d::Node*);

	//visible or not on the screen
	void setVisible(bool);



private:

	//ATTRIBUTES

	//sprite component
	cocos2d::Sprite* m_pSpriteComponent;

	//to know if the sprite exist or not
	bool m_bSpriteIsInit;

	//size of the sprite
	cocos2d::Size m_oSize;

	//unique id
	int m_iId;

};



#endif /* CLASSES_LMGAMECOMPONENT_H_ */
