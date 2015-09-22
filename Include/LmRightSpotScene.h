/*
 * LmRightSpotScene.h
 *
 *  Created on: 16 sept. 2015
 *      Author: IHMTEKDev4
 *
 *      the parent player choose image in a scrollview and can pass it to the child player
 *      through the sending area, so this latter can fill holes in his image
 */

#ifndef CLASSES_INCLUDE_LMRIGHTSPOTSCENE_H_
#define CLASSES_INCLUDE_LMRIGHTSPOTSCENE_H_

#include "LmInteractionScene.h"

#include <random>
#include <algorithm>
#include <iterator>
#include <iostream>
#include <tuple>

//id of this scene
static const int s_iId = 0;
//margiin between image in the scrollview
static const float s_fMarginBetweenImage = 10.0f;
//the time of a long click to select image in the scrollview
static const float s_fLongClickDuration = 1.0f;



class LmRightSpotScene : public LmInteractionScene
{
private:

	//ATTRIBUTES

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
	std::vector<LmGameComponent*> m_aHolesRightImage;
	std::vector<LmGameComponent*> m_aHolesScrollView;

	//attributes gui
	cocos2d::Sprite* m_pSpriteBackground;

	cocos2d::ui::Button* m_pFinishButton;
	bool m_bFinishButtonSync;

	//collide zone
	LmGameComponent* m_pSendingArea;

	//scrollview
	cocos2d::ui::ScrollView* m_pScrollView;
	cocos2d::Layer* m_pLayerScrollView;

	//listener
	cocos2d::EventListenerTouchOneByOne* m_pListener;

	//use for long click
	int m_iBufferId;
	bool m_bSameGameComponent;

	//where we stock the sprite while moving with listener
	cocos2d::Sprite* m_pBufferSprite;
	bool m_bSpriteSelected;

	//METHODS

	//inherit method main of the scene
	void runGame();
	bool init();

	//call to finished this interaction
	void endGame();

	//callback method of parent layer
	bool onTouchBeganParent(cocos2d::Touch*, cocos2d::Event*);
	void onTouchMovedParent(cocos2d::Touch*, cocos2d::Event*);
	void onTouchEndedParent(cocos2d::Touch*, cocos2d::Event*);
	//callback method of child layer
	bool onTouchBeganChild(cocos2d::Touch*, cocos2d::Event*);
	void onTouchMovedChild(cocos2d::Touch*, cocos2d::Event*);
	void onTouchEndedChild(cocos2d::Touch*, cocos2d::Event*);

	//return the id of the gameobject touched -1 otherwise
	int idLmGameComponentTouched(cocos2d::Touch* touch,cocos2d::Event* event);

	//use for long click
	void checkLongClick();

	//to know if the sprite that we are moving collide sending area
	bool bufferCollideSendingArea();

	//test
	void test();
	bool m_bChildSet;

public:

	/*6 parameters =>
	 *  FilenameSpriteBackground
	 *  FilenameSpriteCollideZone
	 *  FilenamesWrongImmages
	 *  FilenameRightImage
	 *  HoleOnX
	 *  HoleOnY
	 *  LocationOfHole*/
	LmRightSpotScene(std::string,std::string,std::vector<std::string>,std::string,int,int,std::vector<std::pair<int,int>>);
	~LmRightSpotScene();

};



#endif /* CLASSES_INCLUDE_LMRIGHTSPOTSCENE_H_ */
