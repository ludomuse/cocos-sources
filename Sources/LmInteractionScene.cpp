//use for the debug
#define COCOS2D_DEBUG 1

#include "../Include/LmInteractionScene.h"

USING_NS_CC;

LmInteractionScene::LmInteractionScene()
{
	//create the introduction
	m_pLmIntroduction = new LmIntroduction;

	m_bDone=false;

}

LmInteractionScene::~LmInteractionScene()
{

	delete m_pLmIntroduction;

	//remove the custom event
	Director::getInstance()->getEventDispatcher()->removeCustomEventListeners("IntroductionFinished");

}



bool LmInteractionScene::init()
{

	if(!m_pLmIntroduction->init(this))
	{
		CCLOG("LmIntroduction init failed");
		return false;
	}

	//init callback method of the custom event (use to know when an interactionScene want to communicate with this)
	auto IntroductionFinished = [=](EventCustom * event)
			{
				runGame();
			};

	//add the custom event to the event dispatcher
	Director::getInstance()->getEventDispatcher()->addCustomEventListener("IntroductionFinished",IntroductionFinished);


	return true;
}
