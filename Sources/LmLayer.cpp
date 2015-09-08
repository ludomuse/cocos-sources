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
	auto l_oSprite = Sprite::create(m_sImageURL);
	l_oSprite->addChild(this);

	return true;
}

//this is a test for sourcetree



