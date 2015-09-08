/*************************************************************************
                           LmInteractionScene  -  Generic step create an empty
                           layer create a simple scene
 *************************************************************************/
#ifndef LMINTERACTION_H__
#define LMINTERACTION_H__

#include "cocos2d.h"
#include "LmGameComponent.h"
#include "LmIntroduction.h"

class LmInteractionScene : public cocos2d::Scene
{
public:

	LmInteractionScene();
	~LmInteractionScene();

	//init
	bool init();

	//test
    bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event* event);


protected:

	//autorelease object it's the first layer of the scene
	cocos2d::Layer* m_pLayerGame;

	//an introduction to the InteractionScene
	LmIntroduction* m_pLmIntroduction;

};


#endif // LMINTERACTION_H__
