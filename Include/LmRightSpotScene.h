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
#include <iterator>
#include <tuple>
// sort algorithm
#include <algorithm>    // std::sort
#include <vector>       // std::vector
#include <utility>

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

	//different vector of gamecomponent
	//scrollview images
	std::vector<LmGameComponent*> m_aScrollViewImages;
	//the right images complete
	std::vector<LmGameComponent*> m_aRightImage;
	//holes in right image
	std::vector<cocos2d::Rect> m_aHolesRightImage;
	//hole in scroll view still unused
	std::vector<cocos2d::Rect> m_aHolesScrollView;
	//elements in sending area
	std::vector<LmGameComponent*> m_aSendingAreaElements;
	//elements filling hole in right image
	std::vector<LmGameComponent*> m_aFillingHoleInRightImage;

	//good id sequence of the right image to know when it's win
	std::vector<int> m_aIdSequenceWin;

	float m_fHeightRect;
	float m_fWidthRect;

	//attributes gui
	cocos2d::Sprite* m_pSpriteBackground;

	cocos2d::ui::Button* m_pFinishButton;
	bool m_bFinishButtonSync;

	//scrollview
	cocos2d::ui::ScrollView* m_pScrollView;
	cocos2d::Layer* m_pLayerScrollView;

	//listener
	cocos2d::EventListenerTouchOneByOne* m_pListener;

	//use for long click
	int m_iBufferId;
	int m_iHoleTouchedIndex;
	int m_iBufferIdFillingImage;
	bool m_bSameGameComponent;
	bool m_bBufferCollideFillingImage;

	//where we stock the sprite while moving with listener
	cocos2d::Sprite* m_pBufferSprite;
	bool m_bSpriteSelected;
	//to avoid to set every frame on the touchmovedparent
	bool m_bBufferSpriteVisible;
	//to know if the buffer fill an hole
	bool m_bBufferSpriteFillHole;
	//to know when we deplace a piece from the right image to generate the hole again
	bool m_bGameComponentAlreadyInRightImage;

	//METHODS

	//inherit method main of the scene
	void runGame();
	bool initGame();

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
	int idLmGameComponentTouchedInScrollView(cocos2d::Touch*);
	int idLmGameComponentTouchedInSendingArea(cocos2d::Touch*);
	int idLmGameComponentTouchedInFillingHoleInRightImage(cocos2d::Touch*);

	//move pieces received in child layer
	void moveBufferSprite(cocos2d::Touch*);


	//use for long click
	void checkLongClick();

	//to know if the sprite that we are moving collide sending area
	bool bufferCollideSendingArea();

	//init texture and position of the buffer and set to invisible the gamecomponent touched /!\ change the anchor point of the buffer sprite
	void initBufferSprite(int,cocos2d::Node*);

	//use to know what hole need to be fill with the buffer img
	int touchCollideHoleInRightImage(cocos2d::Touch*);

	//check if the right image is complete
	bool win();
	bool m_bWin;




	//test
	bool m_bChildSet;

public:

	//id of this scene
	static const int s_iId = 0;

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

	//methods to call from gamemanager to indicate that a gameobject appear in the sending area
	void layerChildReceive(int);



};



#endif /* CLASSES_INCLUDE_LMRIGHTSPOTSCENE_H_ */
