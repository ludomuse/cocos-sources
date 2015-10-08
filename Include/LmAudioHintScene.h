/*
 * LmAudioHintScene.h
 *
 *  Created on: 7 oct. 2015
 *      Author: IHMTEKDev4
 */

#ifndef CLASSES_INCLUDE_LMAUDIOHINTSCENE_H_
#define CLASSES_INCLUDE_LMAUDIOHINTSCENE_H_

#include "LmInteractionScene.h"

struct LmAudioHintSceneSeed
{
	std::string FilenameSpriteBackground;
	std::string FilenameSpriteMainImage;
	std::map<int, std::string> LabelsFilenameAudio;
	std::map<int, std::string> LabelsFilenameSprite;
	std::map<int, cocos2d::Vec2> LabelsCoordonateHole;

};

class LmAudioHintScene: public LmInteractionScene
{

public:

	static const int s_iId = 3;
	static const int s_iNumberLabel = 4;

	LmAudioHintScene(const LmAudioHintSceneSeed &);
	~LmAudioHintScene();

	//use in case the user back to the dashboard and we need to restore some stuff
	void restart();

	//use to replay the game
	void resetScene();

private:

	//ATTRIBUTES

	//json
	std::string m_sFilenameSpriteBackground;
	std::string m_sFilenameSpriteMainImage;
	std::map<int, std::string> m_aLabelsFilenameAudio;
	std::map<int, std::string> m_aLabelsFilenameSprite;
	std::map<int, cocos2d::Vec2> m_aLabelsCoordonateHole;

	//gui elements

	cocos2d::Sprite* m_pSpriteBackground;
	cocos2d::Sprite* m_pSpriteMainImage;

	//counter to know victory
	std::map<int,bool> m_aIdLabelWellPlaced;

	//gamecomponents
	std::map<int, cocos2d::Rect> m_aLabelsHole;

	//conversion from id gamecomponent to id label
	std::map<int, LmGameComponent*> m_aLabelsGameComponent;

	//button to listen sound
	std::map<cocos2d::MenuItemImage*, int> m_aLabelsMenuItemImage;

	//to know if a sprite has been selected
	bool m_bSpriteSelected;
	//buffer sprite use to simulmlate a move
	cocos2d::Sprite* m_pBufferSprite;
	//the id of the element touched
	int m_iBufferId;
	int m_iHoleTouchedIndex;
	bool m_bBufferSpriteFillHole;

	//METHODS

	//main
	void runGame();

	//init
	bool initGame();

	bool menuItemImagePressed(cocos2d::Ref*);

	//callback method of parent layer
	bool onTouchBeganParent(cocos2d::Touch*, cocos2d::Event*);
	void onTouchMovedParent(cocos2d::Touch*, cocos2d::Event*);
	void onTouchEndedParent(cocos2d::Touch*, cocos2d::Event*);

	//get id label with touch /!\ not id game component
	int idLabel(cocos2d::Touch* );
	//init the buffer sprite & move it with touch
	void initBufferSprite(int );
	void moveBufferSprite(cocos2d::Touch* );

	int touchCollideHole(cocos2d::Touch* );


};

#endif /* CLASSES_INCLUDE_LMAUDIOHINTSCENE_H_ */
