//use for the debug
#define COCOS2D_DEBUG 1

#include "../Include/LmInteractionScene.h"

USING_NS_CC;

LmInteractionScene::LmInteractionScene()
{
	//create the introduction
	m_pLmIntroduction = new LmIntroduction;

}

LmInteractionScene::~LmInteractionScene()
{
	//layers is autorelease object

	delete m_pLmIntroduction;

	//declare a member variable
	//Director::getInstance()->getEventDispatcher()->removeEventListener(listener);
}

bool LmInteractionScene::onTouchBegan(cocos2d::Touch* touch,cocos2d::Event* event)
{
	CCLOG("screen touched");
    return true;
}

bool LmInteractionScene::init()
{

	if(!m_pLmIntroduction->init(this))
	{
		CCLOG("LmIntroduction init failed");
		return false;
	}




	//test
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
    listener->onTouchBegan = CC_CALLBACK_2(LmInteractionScene::onTouchBegan, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener,this);

	return true;
}





