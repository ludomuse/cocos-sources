/*
 * LmFindGoodCategoryScene.h
 *
 *  Created on: 5 oct. 2015
 *      Author: IHMTEKDev4
 */

#ifndef CLASSES_INCLUDE_LMFINDGOODCATEGORYSCENE_H_
#define CLASSES_INCLUDE_LMFINDGOODCATEGORYSCENE_H_

#include "LmInteractionScene.h"

struct LmFindGoodCategorySceneSeed
{
	std::string FilenameSpriteBackground;
	std::string FilenameSpriteSendingArea;
	std::vector<std::pair<int,std::string>> Images;
	std::vector<std::pair<int,std::string>> Categories;
};

class LmFindGoodCategoryScene: public LmInteractionScene
{
public:

	static const int s_iId = 2;

	LmFindGoodCategoryScene(const LmFindGoodCategorySceneSeed &);
	~LmFindGoodCategoryScene();

	//use in case the user back to the dashboard and we need to restore some stuff
	void restart();

	//use to replay the game
	void resetScene();

private:

	//ATTRIBUTES

	//json
	std::string m_sFilenameSpriteBackground;
	std::string m_sFilenameSpriteSendingArea;
	std::vector<std::pair<int,std::string>> m_aImages;
	std::vector<std::pair<int,std::string>> m_aCategories;


	//gui elements

	cocos2d::Sprite* m_pSpriteBackground;
	LmGameComponent* m_pSendingArea;

	//vector of gamecomponent
	std::vector<LmGameComponent*> m_aGameComponentImages;

	//hole in  view parent
	std::vector<std::pair<cocos2d::Rect, int>> m_aHolesLayerParent;

	//listener
	cocos2d::EventListenerTouchOneByOne* m_pListener;
	//the id of the element touched
	int m_iBufferId;
	//index category touched
	int m_iCategoryTouchedIndex;
	//pointer to the sending area element
	LmGameComponent* m_pSendingAreaElement;
	//to know if we touched the sending area element
	bool m_bSendingAreaElementTouched;
	//to know if a sprite has been selected
	bool m_bSpriteSelected;
	//buffer sprite use to simulmlate a move
	cocos2d::Sprite* m_pBufferSprite;

	//square diemnsion
	float m_fSquareDimension;

	//vector of lm gamecomponent categories key=id categorie
	std::map<int,LmGameComponent*> m_aCategoriesElement;

	//stock what images to what categorie
	std::map<int,int> m_aIdGamecomponentToIdCategory;


	//METHODS

	//main
	void runGame();

	//init
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
	int idImage(cocos2d::Touch*);

	//move buffer sprite with touch
	void moveBufferSprite(cocos2d::Touch* );

	//init the buffer sprite to begin a movement with an image according the id of the gamecomponent
	void initBufferSprite(int);
	//set the position of the gamecomponent with this id into the sending area
	void setPositionInSendingArea(int);
	//return the hole of that element
	cocos2d::Rect holeOfThisImage(int);

	//when the child receive an element
	void layerChildReceive(int);

	bool bufferCollideSendingArea();

	//return the id of a categorie otherwise -1
	int touchCollideCategory(cocos2d::Touch*);




};

#endif /* CLASSES_INCLUDE_LMFINDGOODCATEGORYSCENE_H_ */
