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


	std::vector<LmGameComponent*> m_aScrollViewImages;
	std::vector<LmGameComponent*> m_aRightImage;


	//attributes gui
	cocos2d::Sprite* m_pSpriteBackground;

	cocos2d::ui::Button* m_pFinishButton;
	bool m_bFinishButtonSync;

	std::vector<cocos2d::Sprite*> m_aSpritesSources;

	//call to finished this interaction
	void endGame();

	//collide zone
	LmGameComponent* m_pSendingArea;

	//scrollview
	cocos2d::ui::ScrollView* m_pScrollView;


	//test
	void test();
	bool m_bChildSet;

	bool init();




public:

	LmRightSpotScene();
	~LmRightSpotScene();



};



#endif /* CLASSES_INCLUDE_LMRIGHTSPOTSCENE_H_ */
