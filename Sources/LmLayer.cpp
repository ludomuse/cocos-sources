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

LmLayer::LmLayer(std::string l_sImageURL,std::string l_sSoundURL,const char* l_pText)
{
	m_sImageURL = l_sImageURL;
	m_sSoundURL = l_sSoundURL;
	m_pText = l_pText;
}

bool LmLayer::init()
{

	//use to place elements
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();

    //we add the background sprite
	auto l_oSprite = Sprite::create(m_sImageURL);
	l_oSprite->setPosition(origin.x+visibleSize.width/2,origin.y+visibleSize.height/2);
	addChild(l_oSprite);


	return true;
}



