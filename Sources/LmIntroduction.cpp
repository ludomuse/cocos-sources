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
	for (std::vector<LmLayer*>::iterator it = m_aLayers.begin(); it != m_aLayers.end(); ++it)
	{
		delete (*it);
	}
}

bool LmIntroduction::init(Scene* l_pInteractionScene)
{
	//init scene
	m_pInteractionScene = l_pInteractionScene;

	//init button

	//next button
	m_pNextButton = ui::Button::create("nextButtonNormal.png","nextButtonPressed.png");
	m_pNextButton->setTouchEnabled(true);
	m_pNextButton -> setPosition(getNextButtonPosition(m_pNextButton));
	m_pNextButton->addTouchEventListener(CC_CALLBACK_0(LmIntroduction::nextLayer, this));
	m_pInteractionScene->addChild(m_pNextButton,1);

	//previous button
	m_pPreviousButton = ui::Button::create("previousButtonNormal.png","previousButtonPressed.png");
	m_pPreviousButton->setTouchEnabled(true);
	m_pPreviousButton -> setPosition(getPreviousButtonPosition(m_pPreviousButton));
	m_pPreviousButton->addTouchEventListener(CC_CALLBACK_0(LmIntroduction::previousLayer, this));
	m_pInteractionScene->addChild(m_pPreviousButton,1);

	//test they are going to be create by the LmFactory while reading the json file
	//add two LmLayer to test
	m_aLayers.push_back(new LmLayer("background.png","audio/son.mp3","1st LmLayer"));
	m_aLayers.push_back(new LmLayer("2emeimg.png","audio/son.mp3","bla bla bla"));

	//we begin by the first one of the evctor
	m_pCurrentLayer = m_aLayers.at(0);
	m_pCurrentLayer->init();
	m_pInteractionScene->addChild(m_pCurrentLayer,0);

	return true;
}

bool LmIntroduction::nextLayer()
{

	m_pInteractionScene->removeChild(m_pCurrentLayer);
	m_pCurrentLayer = m_aLayers.at(1);
	m_pCurrentLayer->init();
	m_pInteractionScene->addChild(m_pCurrentLayer,0);

	return true;
}

bool LmIntroduction::previousLayer()
{
	m_pInteractionScene->removeChild(m_pCurrentLayer);
	m_pCurrentLayer = m_aLayers.at(0);
	m_pCurrentLayer->init();
	m_pInteractionScene->addChild(m_pCurrentLayer,0);

	return true;
}

cocos2d::Vect LmIntroduction::getNextButtonPosition(cocos2d::ui::Button* l_pButton)const
{
	Size l_oSizeOfButton = l_pButton->getSize();
	Size visibleSize = Director::getInstance()->getVisibleSize();

	float l_iXButton = visibleSize.width-l_oSizeOfButton.width/2;
	float l_iYButton = l_oSizeOfButton.height/2;

	return Vect(l_iXButton,l_iYButton);
}

cocos2d::Vect LmIntroduction::getPreviousButtonPosition(cocos2d::ui::Button* l_pButton)const
{
	Size l_oSizeOfButton = l_pButton->getSize();
	Size visibleSize = Director::getInstance()->getVisibleSize();

	float l_iXButton = l_oSizeOfButton.width/2;
	float l_iYButton = l_oSizeOfButton.height/2;

	return Vect(l_iXButton,l_iYButton);
}





