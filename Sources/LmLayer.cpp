//use for the debug
#define COCOS2D_DEBUG 1

#include "../Include/LmLayer.h"

USING_NS_CC;

LmLayer::LmLayer()
{

}

LmLayer::~LmLayer()
{

}

LmLayer::LmLayer(const char* l_pImageURL,const char* l_pSoundURL,const char* l_pText)
{
	m_pImageURL = l_pImageURL;
	m_pSoundURL = l_pSoundURL;
	m_pText = l_pText;
}

bool LmLayer::init()
{

	//use to place elements
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();

    //we add the background sprite to the center of the screen
	auto l_oSprite = Sprite::create(m_pImageURL);
	l_oSprite->setPosition(origin.x+visibleSize.width/2,origin.y+visibleSize.height/2);
	addChild(l_oSprite,0);

	//we preload the sound
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic(m_pSoundURL);
    //play sound
    CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic(m_pSoundURL,false);

    //we add text to the center of the screen
    auto l_oLabel = Label::createWithTTF(m_pText, "fonts/Marker Felt.ttf",getSizeLabel());
    l_oLabel->setPosition(origin.x+visibleSize.width/2,origin.y+visibleSize.height/2);
    addChild(l_oLabel,1);

	return true;
}

int LmLayer::getSizeLabel()
{
	return 50;
}


