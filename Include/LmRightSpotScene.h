/*
 * LmRightSpotScene.h
 *
 *  Created on: 16 sept. 2015
 *      Author: IHMTEKDev4
 */

#ifndef CLASSES_INCLUDE_LMRIGHTSPOTSCENE_H_
#define CLASSES_INCLUDE_LMRIGHTSPOTSCENE_H_

#include "LmInteractionScene.h"

#include <random>
#include <algorithm>
#include <iterator>
#include <iostream>
#include <tuple>

static const float s_fMarginBetweenImage = 10.0f;
static const float s_fLongClickDuration = 1.0f;


class LmRightSpotScene : public LmInteractionScene
{
private:

	void runGame();

	//what we need to get from the json file
	std::string m_sFilenameSpriteBackground;
	std::string m_sFilenameSpriteCollideZone;
	std::vector<std::string>m_aFilenamesWrongImmages;
	std::string m_sFilenameRightImage;
	int m_iHoleOnX;
	int m_iHoleOnY;
	std::vector<std::pair<int,int>> m_aLocationOfHole;

	//where we stock img sprite
	std::vector<LmGameComponent*> m_aScrollViewImages;
	std::vector<LmGameComponent*> m_aRightImage;

	//attributes gui
	cocos2d::Sprite* m_pSpriteBackground;

	cocos2d::ui::Button* m_pFinishButton;
	bool m_bFinishButtonSync;

	//call to finished this interaction
	void endGame();

	//collide zone
	LmGameComponent* m_pSendingArea;

	//scrollview
	cocos2d::ui::ScrollView* m_pScrollView;
	cocos2d::Layer* m_pLayerScrollView;
	//callback method of parent layer
	bool onTouchBeganParent(cocos2d::Touch*, cocos2d::Event*);
	void onTouchMovedParent(cocos2d::Touch*, cocos2d::Event*);
	void onTouchEndedParent(cocos2d::Touch*, cocos2d::Event*);

	//listener
	cocos2d::EventListenerTouchOneByOne* m_pListener;

	//return the id of the gameobject touched -1 otherwise
	int idLmGameComponentTouched(cocos2d::Touch* touch,cocos2d::Event* event);
	//use for long click
	int m_iBufferId;
	bool m_bSameGameComponent;
	void checkLongClick();

	//test
	void test();
	bool m_bChildSet;

	bool init();

	//where we stock the sprite while moving with listener
	cocos2d::Sprite* m_pBufferSprite;
	bool m_bSpriteSelected;

	//to know if the sprite that we are moving collide sending area
	bool bufferCollideSendingArea();


public:

	LmRightSpotScene();
	~LmRightSpotScene();



};



#endif /* CLASSES_INCLUDE_LMRIGHTSPOTSCENE_H_ */
