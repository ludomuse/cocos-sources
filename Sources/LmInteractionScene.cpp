//use for the debug
#define COCOS2D_DEBUG 1

#include "../Include/LmInteractionScene.h"

USING_NS_CC;

LmInteractionScene::LmInteractionScene()
{
	//create the introduction
	m_pLmIntroduction = new LmIntroduction;

	//create the Layer of the game
	m_pLayerGame=Layer::create();

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

	if(!m_pLmIntroduction->init())
	{
		CCLOG("LmIntroduction init failed");
		return false;
	}

	//we add the first layer of the introduction to this scene
	addChild(m_pLmIntroduction->getLayer(0));


	//test
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
    listener->onTouchBegan = CC_CALLBACK_2(LmInteractionScene::onTouchBegan, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener,this);

	return true;
}





