
//use for the debug
#define COCOS2D_DEBUG 1

#include "../Include/LmSetPoint.h"

USING_NS_CC;

LmSetPoint::LmSetPoint()
{
	//primitive type
	m_iIndex=0;
	m_iSize=0;
	m_bActionDone = true;

	//pointer
	m_pCurrentLayer=nullptr;
	m_pLayerTransition=nullptr;
	m_pInteractionScene=nullptr;

}

LmSetPoint::~LmSetPoint()
{
	//Browse the vector of LmLayer and delete them
	for (std::vector<LmLayer*>::iterator it = m_aLayers.begin(); it != m_aLayers.end(); ++it)
	{
		delete (*it);
	}

}

bool LmSetPoint::init(cocos2d::Scene* l_pInteractionScene)
{

	m_pInteractionScene = l_pInteractionScene;

	//use to place elements
	Size l_oVisibleSize = Director::getInstance()->getVisibleSize();

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

	return true;
}

bool LmSetPoint::nextLayer()
{

	if(m_bActionDone)
	{
		m_bActionDone=false;

		if(m_iIndex>=m_iSize-1)
		{
			m_bActionDone=true;
			//we indicate to the inyeractionscene that introduction is over
			m_pInteractionScene->removeChild(m_pLayerTransition);
			m_pInteractionScene->removeChild(m_pCurrentLayer);
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

			auto l_pMoveLeft = MoveBy::create(s_fTimeBetweenLmLayer,Vect(-l_oVisibleSize.width,0));
			//callback function
			auto l_pMoveLeftDone = CallFunc::create( std::bind(&LmSetPoint::moveLeftDone,this) );

			m_iIndex++;

			//run the sequence so we know when its finished then callback function
			m_pLayerTransition->runAction(Sequence::create(l_pMoveLeft,l_pMoveLeftDone,nullptr));

			return true;
		}

	}

	return false;

}

bool LmSetPoint::previousLayer()
{
	if(m_bActionDone)
	{
		m_bActionDone=false;

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

			auto l_pMoveRight = MoveBy::create(s_fTimeBetweenLmLayer,Vect(l_oVisibleSize.width,0));
			//callback function
			auto l_pMoveRightDone = CallFunc::create( std::bind(&LmSetPoint::moveRightDone,this) );

			m_iIndex--;

			//run the sequence so we know when its finished then callback function
			m_pLayerTransition->runAction(Sequence::create(l_pMoveRight,l_pMoveRightDone,nullptr));

			return true;
		}

	}

	return false;

}

void LmSetPoint::moveRightDone()
{
	//we remove the current to put the next one as current
	m_pLayerTransition->removeChild(m_pCurrentLayer);
	m_pCurrentLayer = m_aLayers.at(m_iIndex);
	m_pCurrentLayer->playSound();

	//set the new position of the layer transition  and of the current layer
	m_pLayerTransition->setPosition(Point(0,0));
	m_pCurrentLayer->setPosition(Point(0,0));

	//possible to perform another action
	m_bActionDone = true;

}

void LmSetPoint::moveLeftDone()
{
	//we remove the current to put the next one as current
	m_pLayerTransition->removeChild(m_pCurrentLayer);
	m_pCurrentLayer = m_aLayers.at(m_iIndex);
	m_pCurrentLayer->playSound();

	//set the new position of the layer transition  and of the current layer
	m_pLayerTransition->setPosition(Point(0,0));
	m_pCurrentLayer->setPosition(Point(0,0));

	//possible to perform another action
	m_bActionDone = true;
}

void LmSetPoint::add(LmLayer* layer)
{
	m_aLayers.push_back(layer);
}





