//use for the debug
#define COCOS2D_DEBUG 1

#include "../Include/LmIntroduction.h"

USING_NS_CC;

LmIntroduction::LmIntroduction()
{

}

LmIntroduction::~LmIntroduction()
{
	//Browse the vector of LmLayer and delete them
	for (std::vector<LmLayer*>::iterator it = m_pLayers.begin(); it != m_pLayers.end(); ++it)
	{
		delete (*it);
	}
}

bool LmIntroduction::init()
{
	const char* test = "test";
	m_pLayers.push_back(new LmLayer("background.png","background.png",test));

	//init each layer
	for (std::vector<LmLayer*>::iterator it = m_pLayers.begin(); it != m_pLayers.end(); ++it)
	{
		CCLOG("for");
		if(!(*it)->init())
		{
			CCLOG("LmLayer init failed");
			return false;
		}
	}

	return true;
}

LmLayer* LmIntroduction::getLayer(int l_iIndex)const
{
	return m_pLayers.at(l_iIndex);
}
