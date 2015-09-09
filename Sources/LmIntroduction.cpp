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

	//release action because they have been retain() in init function
	m_pMoveLeft->release();
	m_pMoveLeftDone->release();
	m_pMoveRight->release();
	m_pMoveRightDone->release();
}

bool LmIntroduction::init(Scene* l_pInteractionScene)
{
	//init scene pass by LmInteractionScene
	m_pInteractionScene = l_pInteractionScene;

	//init action
	Size l_oVisibleSize = Director::getInstance()->getVisibleSize();
	m_pMoveRight = MoveBy::create(s_fTimeBetweenLmLayer,Vect(l_oVisibleSize.width,0));
	m_pMoveLeft = MoveBy::create(s_fTimeBetweenLmLayer,Vect(-l_oVisibleSize.width,0));
	//callback function
	m_pMoveLeftDone = CallFunc::create( std::bind(&LmIntroduction::moveLeftDone,this) );
	m_pMoveRightDone = CallFunc::create( std::bind(&LmIntroduction::moveRightDone,this) );

	//we have to retain these action because they are going to be call in callback method of button
	m_pMoveLeft->retain();
	m_pMoveLeftDone->retain();
	m_pMoveRight->retain();
	m_pMoveRightDone->retain();

	//init bool to sync actions
	m_bActionDone = true;

	//init buttons

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
	m_aLayers.push_back(new LmLayer("titre.png","audio/son.mp3","hello"));
	m_aLayers.push_back(new LmLayer("perso.png","audio/son.mp3","suivez moi les enfants"));
	m_aLayers.push_back(new LmLayer("ing.png","audio/son.mp3","recompense"));

	//we begin by the first one of the vector
	m_iIndex = 0;
	m_iSize = m_aLayers.size();

	//check if not empty
	if(!m_iSize)
	{
		CCLOG("No LmLayer");
		return false;
	}

	//init layer transition
	m_pLayerTransition = Layer::create();
	m_pInteractionScene->addChild(m_pLayerTransition);

	//init m_pCurrentLayer
	m_pCurrentLayer = m_aLayers.at(m_iIndex);
	m_pCurrentLayer->init();
	m_pLayerTransition->addChild(m_pCurrentLayer,0);
	m_pCurrentLayer->playSound();


	return true;
}

bool LmIntroduction::nextLayer()
{

	if(m_bActionDone)
	{
		m_bActionDone=false;

		//we were pointing the 1st LmLayer
		if(m_iIndex>=m_iSize-1)
		{
			m_bActionDone=true;
			return false;
		}
		else
		{
			//the current layer and the one after move to the left
			Size l_oVisibleSize = Director::getInstance()->getVisibleSize();
			Point l_oOrigin = Director::getInstance()->getVisibleOrigin();

			//add the the newt layer
			m_pLayerTransition->addChild(m_aLayers.at(m_iIndex+1));

			//init the next one
			m_aLayers.at(m_iIndex+1)->init();

			//set position to the right out of screen
			m_aLayers.at(m_iIndex+1)->setPosition((3/2)*l_oVisibleSize.width+l_oOrigin.x,0);

			//run the sequence so we know when its finished then callback function
			m_pLayerTransition->runAction(Sequence::create(m_pMoveLeft,m_pMoveLeftDone,NULL));

			return true;
		}

	}

}

bool LmIntroduction::previousLayer()
{
	if(m_bActionDone)
	{
		m_bActionDone=false;

		//we were pointing the 1st LmLayer
		if(m_iIndex<=0)
		{
			m_bActionDone=true;
			return false;
		}
		else
		{
			//the current layer and the one after move to the left
			Size l_oVisibleSize = Director::getInstance()->getVisibleSize();
			Point l_oOrigin = Director::getInstance()->getVisibleOrigin();

			//add the the previous layer
			m_pLayerTransition->addChild(m_aLayers.at(m_iIndex-1));

			//init the previous one
			m_aLayers.at(m_iIndex-1)->init();

			//set position to the left out of screen
			m_aLayers.at(m_iIndex-1)->setPosition((-3/2)*l_oVisibleSize.width+l_oOrigin.x,0);

			//run the sequence so we know when its finished then callback function
			m_pLayerTransition->runAction(Sequence::create(m_pMoveRight,m_pMoveRightDone,NULL));

			return true;
		}

	}

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

void LmIntroduction::moveRightDone()
{
	//we remove the current to put the next one as current
	m_pLayerTransition->removeChild(m_pCurrentLayer);
	m_iIndex--;
	m_pCurrentLayer = m_aLayers.at(m_iIndex);
	m_pCurrentLayer->playSound();

	//set the new position of the layer transition  and of the current layer
	m_pLayerTransition->setPosition(Point(0,0));
	m_pCurrentLayer->setPosition(Point(0,0));

	//possible to perform another action
	m_bActionDone = true;

}

void LmIntroduction::moveLeftDone()
{
	//we remove the current to put the next one as current
	m_pLayerTransition->removeChild(m_pCurrentLayer);
	m_iIndex++;
	m_pCurrentLayer = m_aLayers.at(m_iIndex);
	m_pCurrentLayer->playSound();

	//set the new position of the layer transition  and of the current layer
	m_pLayerTransition->setPosition(Point(0,0));
	m_pCurrentLayer->setPosition(Point(0,0));

	//possible to perform another action
	m_bActionDone = true;
}





