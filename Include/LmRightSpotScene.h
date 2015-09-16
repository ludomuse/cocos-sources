/*
 * LmRightSpotScene.h
 *
 *  Created on: 16 sept. 2015
 *      Author: IHMTEKDev4
 */

#ifndef CLASSES_INCLUDE_LMRIGHTSPOTSCENE_H_
#define CLASSES_INCLUDE_LMRIGHTSPOTSCENE_H_

#include "LmInteractionScene.h"


class LmRightSpotScene : public LmInteractionScene
{
private:

	void runGame();

	//what we need to get from the json file
	std::string m_sFilenameSpriteBackground;
	std::string m_sFilenameSpriteCollideZone;
	std::vector<std::string>m_aFilenamesSources;

	//attributes gui
	cocos2d::Sprite* m_pSpriteBackground;

	cocos2d::ui::Button* m_pFinishButton;
	bool m_bFinishButtonSync;

	std::vector<cocos2d::Sprite*> m_aSpritesSources;

	//call to finished this interaction
	void endGame();

	//collide zone
	LmGameComponent* m_pSendingArea;





public:

	LmRightSpotScene();
	~LmRightSpotScene();



};



#endif /* CLASSES_INCLUDE_LMRIGHTSPOTSCENE_H_ */
