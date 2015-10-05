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
static const float s_fMarginBetweenImage = 30.0f;

struct LmRightSpotSceneSeed
{
	/*
	 * 6 parameters =>
	 *  FilenameSpriteBackground
	 *  FilenameSpriteCollideZone
	 *  FilenameRightImage
	 *  HoleOnX
	 *  HoleOnY
	 *  LocationOfHole
	 */

	std::string FilenameSpriteBackground;
	std::string FilenameSpriteCollideZone;
	std::string FilenameRightImage;
	int HoleOnX;
	int HoleOnY;
	std::vector<std::pair<int, int>> LocationOfHole;

};

class LmRightSpotScene: public LmInteractionScene
{

public:

	//id of this scene
	static const int s_iId = 0;

	LmRightSpotScene(const LmRightSpotSceneSeed&);
	~LmRightSpotScene();

	//methods to call from gamemanager to indicate that a gameobject appear in the sending area
	void layerChildReceive(int);

	//restart
	void restart();

	//to reset the game
	void resetScene();

private:

	//ATTRIBUTES

	//what we need to get from the json file
	std::string m_sFilenameSpriteBackground;
	std::string m_sFilenameSpriteCollideZone;
	std::string m_sFilenameRightImage;
	int m_iHoleOnX;
	int m_iHoleOnY;
	std::vector<std::pair<int, int>> m_aLocationOfHole;

	//different vector of gamecomponent
	//dynamic element parent/child game
	std::vector<LmGameComponent*> m_aDynamicGameComponents;
	//element fix child game
	std::vector<LmGameComponent*> m_aStaticGameComponents;
	//holes in  image the int is to know the ifd of the gamecomponent
	std::vector<std::pair<cocos2d::Rect, int>> m_aHolesImageChild;
	//hole in  view parent
	std::vector<std::pair<cocos2d::Rect, int>> m_aHolesLayerParent;

	//element in sending area
	LmGameComponent* m_pSendingAreaElement;

	//rect stencil dimension
	float m_fHeightRect;
	float m_fWidthRect;

	//attributes gui
	cocos2d::Sprite* m_pSpriteBackground;

	//listener
	cocos2d::EventListenerTouchOneByOne* m_pListener;

	//use to handle touch event
	int m_iBufferId;
	int m_iHoleTouchedIndex;
	bool m_bSendingAreaElementTouched;

	//where we stock the sprite while moving with listener
	cocos2d::Sprite* m_pBufferSprite;
	bool m_bSpriteSelected;
	//to know if the buffer fill an hole
	bool m_bBufferSpriteFillHole;

	//METHODS

	//inherit method main of the scene
	void runGame();
	bool initGame();

	//callback method of parent layer
	bool onTouchBeganParent(cocos2d::Touch*, cocos2d::Event*);
	void onTouchMovedParent(cocos2d::Touch*, cocos2d::Event*);
	void onTouchEndedParent(cocos2d::Touch*, cocos2d::Event*);
	//callback method of child layer
	bool onTouchBeganChild(cocos2d::Touch*, cocos2d::Event*);
	void onTouchMovedChild(cocos2d::Touch*, cocos2d::Event*);
	void onTouchEndedChild(cocos2d::Touch*, cocos2d::Event*);

	//return the id of the gameobject touched -1 otherwise
	int idDynamicLmGameComponent(cocos2d::Touch*);
	int idLmGameComponentTouchedInSendingArea(cocos2d::Touch*);

	//move pieces received in child layer
	void moveBufferSprite(cocos2d::Touch*);

	//to know if the sprite that we are moving collide sending area
	bool bufferCollideSendingArea();

	//init texture and position of the buffer and set to invisible the gamecomponent touched /!\ change the anchor point of the buffer sprite
	void initBufferSprite(int);

	//use to know what hole need to be fill with the buffer img
	int touchCollideHoleInRightImage(cocos2d::Touch*);

	//check if the right image is complete
	bool win();

	//set position of the gamecomponent id in the  sending area
	void setPositionInSendingArea(int);

	//id hole + id element to know if it's well placed
	bool imageWellPlaced(int, int);

	//get the hole of this id dynamic element
	cocos2d::Rect holeOfThisDynamicElement(int);

};

#endif /* CLASSES_INCLUDE_LMRIGHTSPOTSCENE_H_ */
