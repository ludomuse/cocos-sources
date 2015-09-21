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

	//init the sprite component with a filename then add it to this
	void initSpriteComponent(std::string);
	void initSpriteComponent(std::string,const cocos2d::Rect&);

	cocos2d::Size getContentSize()const;

	int getIId() const {
		return m_iId;
	}

	cocos2d::Sprite* getPSpriteComponent() const {
		return m_pSpriteComponent;
	}

	static int s_iNumberOfGameComponent;


	void addTo(cocos2d::Layer*);
	void addTo(cocos2d::Layer*,int);
	void removeFrom(cocos2d::Layer*);
	void setPosition(cocos2d::Vec2);
	void setAnchorPoint(cocos2d::Vec2);
	void setTexture(std::string);

	bool m_bSpriteIsInit;

	//return the bounding in the UIWindow space
	cocos2d::Rect getBoundingBoxInWorldSpace(cocos2d::Node*);

	cocos2d::Size m_oSize;

	void setVisible(bool);



private:

	cocos2d::Sprite* m_pSpriteComponent;

	int m_iId;

};



#endif /* CLASSES_LMGAMECOMPONENT_H_ */
