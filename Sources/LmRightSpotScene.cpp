/*
 * LmRightSpot.cpp
 *
 *  Created on: 16 sept. 2015
 *      Author: IHMTEKDev4
 */

#include "../Include/LmRightSpotScene.h"



using namespace cocos2d;

LmRightSpotScene::LmRightSpotScene(
		std::string l_sFilenameSpriteBackground,
		std::string l_sFilenameSpriteCollideZone,
		std::vector<std::string> l_aFilenamesWrongImmages,
		std::string l_sFilenameRightImage,
		int l_iHoleOnX,
		int l_iHoleOnY,
		std::vector<std::pair<int,int>> l_aLocationOfHole)
{

	//json parameters
	m_sFilenameSpriteBackground=l_sFilenameSpriteBackground;
	m_sFilenameSpriteCollideZone=l_sFilenameSpriteCollideZone;
	m_aFilenamesWrongImmages = l_aFilenamesWrongImmages;
	m_sFilenameRightImage = l_sFilenameRightImage;
	m_iHoleOnX=l_iHoleOnX;
	m_iHoleOnY=l_iHoleOnY;
	m_aLocationOfHole = l_aLocationOfHole;

	//primitive type
	m_bFinishButtonSync=true;
	m_iBufferId=-1;
	m_bSameGameComponent=false;
	m_bSpriteSelected=false;

	//pointer
	m_pBackDashboardButton=nullptr;
	m_pBufferSprite=nullptr;
	m_pDashboardBandLayer=nullptr;
	m_pFinishButton=nullptr;
	m_pGuiElementsLayer=nullptr;
	m_pLabelScore=nullptr;
	m_pLabelUserName=nullptr;
	m_pLayerGame=nullptr;
	m_pLayerScrollView=nullptr;
	m_pLayerUserChild=nullptr;
	m_pLayerUserParent=nullptr;
	m_pListener=nullptr;
	m_pMoveLayerButton=nullptr;
	m_pScrollView=nullptr;
	m_pSendingArea=nullptr;
	m_pSpriteBackground=nullptr;
	m_pSpriteDashboardBand=nullptr;
	m_pUser=nullptr;
}

LmRightSpotScene::~LmRightSpotScene()
{

	//test
	m_pLayerUserChild->release();
	m_pLayerUserParent->release();

	//destroy all gamecomponent

	delete m_pSendingArea;

	for(it_type it=m_aIdTable.begin();it!=m_aIdTable.end();++it)
	{
		//destroy the pointer on the LmGameComponent
		delete it->second;
	}

	for(std::vector<LmGameComponent*>::iterator it=m_aHolesRightImage.begin();it!=m_aHolesRightImage.end();++it)
	{
		//destroy holes of the right image
		delete (*it);
	}

	for(std::vector<LmGameComponent*>::iterator it=m_aHolesScrollView.begin();it!=m_aHolesScrollView.end();++it)
	{
		//destroy holes in scroll view
		delete (*it);
	}

	Director::getInstance()->getEventDispatcher()->removeEventListener(m_pListener);

}

void LmRightSpotScene::runGame()
{
	initGame();
}

bool LmRightSpotScene::initGame()
{
	//use to place elements
	Size l_oVisibleSize = Director::getInstance()->getVisibleSize();
	Point l_oOrigin = Director::getInstance()->getVisibleOrigin();

	//create layer game and add to this
	m_pLayerGame = Layer::create();
	this->addChild(m_pLayerGame,0);

	//init the two other layer
	m_pLayerUserParent = Layer::create();
	m_pLayerUserChild = Layer::create();

	//test
	m_pLayerUserChild->retain();
	m_pLayerUserParent->retain();

	//init the background
	m_pSpriteBackground = Sprite::create(m_sFilenameSpriteBackground);
	m_pSpriteBackground->setPosition(l_oVisibleSize.width*0.5f+l_oOrigin.x,l_oVisibleSize.height*0.5f+l_oOrigin.y);
	m_pLayerGame->addChild(m_pSpriteBackground);

	//init Sending Area
	m_pSendingArea = new LmGameComponent;
	m_pSendingArea->initSpriteComponent(m_sFilenameSpriteCollideZone);
	m_pSendingArea->setPosition(Vec2(l_oVisibleSize.width-m_pSendingArea->getContentSize().width*0.5f+l_oOrigin.x,l_oVisibleSize.height*0.5));
	m_pSendingArea->addTo(m_pLayerGame);

	//init some usefull point
	Point l_oMiddleOfPlayableArea = Point(l_oOrigin.x+(l_oVisibleSize.width-m_pSendingArea->getContentSize().width)*0.5f,l_oVisibleSize.height*0.5f+l_oOrigin.y);
	Size l_oPlayableScreenSize = Size(l_oOrigin.x-s_fMarginLeft+(l_oVisibleSize.width-m_pSendingArea->getContentSize().width),l_oVisibleSize.height);

	//finish button
	m_pFinishButton = ui::Button::create("nextButtonNormal.png","nextButtonPressed.png");
	m_pFinishButton->setTouchEnabled(true);
	m_pFinishButton -> setPosition(Vect(l_oVisibleSize.width-m_pFinishButton->getContentSize().width*0.8,m_pFinishButton->getContentSize().height*0.7));
	m_pFinishButton->addTouchEventListener(CC_CALLBACK_0(LmRightSpotScene::endGame, this));
	m_pLayerGame->addChild(m_pFinishButton,1);

	//we get dimension of the right image ( /!\ guessing that all ressources are making same resolution /!\ )
	auto l_oSpriteRightImgSpot = Sprite::create(m_sFilenameRightImage);
	float l_fWidthRightImage = l_oSpriteRightImgSpot->getContentSize().width;
	float l_fHeightRightImage = l_oSpriteRightImgSpot->getContentSize().height;
	float l_fWidthRect = l_fWidthRightImage/m_iHoleOnX;
	float l_fHeightRect = l_fHeightRightImage/m_iHoleOnY;

	//for each wrong image
	int l_iIndex=0;
	Rect l_oRectStencil;


	for (std::vector<std::string>::iterator it = m_aFilenamesWrongImmages.begin(); it != m_aFilenamesWrongImmages.end(); ++it)
	{

		for(int i=0;i<m_iHoleOnX;i++)
		{
			for(int j=0;j<m_iHoleOnY;j++)
			{
				//get the stencil
				l_oRectStencil = Rect(l_fWidthRect*i,l_fHeightRect*j,l_fWidthRect,l_fHeightRect);
				//add new gamecomponent
				m_aScrollViewImages.push_back(new LmGameComponent);
				//cut the right rect on the source file
				m_aScrollViewImages.at(l_iIndex)->initSpriteComponent((*it),l_oRectStencil);
				//register it into the id table
				m_aIdTable.insert(std::pair<int,LmGameComponent*>(m_aScrollViewImages.at(l_iIndex)->getIId(),m_aScrollViewImages.at(l_iIndex)));

				m_aScrollViewImages.at(l_iIndex)->setAnchorPoint(Vec2(0,0));
				l_iIndex++;

			}
		}
	}

	l_iIndex=0;

	//init vector of the right image
	Point l_oPointToPlaceRightImage = Point(l_oMiddleOfPlayableArea.x-l_fWidthRightImage*0.5,l_oMiddleOfPlayableArea.y-l_fHeightRightImage*0.5);

	for(int i=0;i<m_iHoleOnX;i++)
	{
		for(int j=0;j<m_iHoleOnY;j++)
		{
			Vec2 l_oVectorPosition = Vec2(l_fWidthRect*i+l_oPointToPlaceRightImage.x,(m_iHoleOnY-(j+1))*l_fHeightRect+l_oPointToPlaceRightImage.y);


			l_oRectStencil = Rect(l_fWidthRect*i,l_fHeightRect*j,l_fWidthRect,l_fHeightRect);
			m_aRightImage.push_back(new LmGameComponent);
			m_aRightImage.at(l_iIndex)->initSpriteComponent(m_sFilenameRightImage,l_oRectStencil);

			//check if this piece is a hole
			std::vector<std::pair<int,int>>::iterator it;
			std::pair<int,int> l_PairBuffer = {i,j};
			it=std::find(m_aLocationOfHole.begin(), m_aLocationOfHole.end(),l_PairBuffer);
			if(it != m_aLocationOfHole.end())
			{
				//yes we also add this piece to the scrollview
				m_aScrollViewImages.push_back(m_aRightImage.at(l_iIndex));
				m_aRightImage.at(l_iIndex)->setAnchorPoint(Vec2(0,0));

				//we add an hole
				m_aHolesRightImage.push_back(new LmGameComponent);
				//we get the element just pushed
				auto l_oHole = m_aHolesRightImage.at(m_aHolesRightImage.size()-1);
				l_oHole->initSpriteComponent("transparency.png");
				l_oHole->setAnchorPoint(Vec2(0,0));
				l_oHole->setPosition(l_oVectorPosition);
				//so the bounding box will the same as an image
				l_oHole->setSize(Size(l_fWidthRect,l_fHeightRect));
				l_oHole->addTo(m_pLayerUserChild);

			}
			else
			{
				//no we set position and add it to layer child
				m_aRightImage.at(l_iIndex)->setAnchorPoint(Vec2(0,0));
				m_aRightImage.at(l_iIndex)->setPosition(l_oVectorPosition);
				m_aRightImage.at(l_iIndex)->addTo(m_pLayerUserChild);
			}

			//register it into the id table
			m_aIdTable.insert(std::pair<int,LmGameComponent*>(m_aRightImage.at(l_iIndex)->getIId(),m_aRightImage.at(l_iIndex)));
			l_iIndex++;
		}
	}



	//test set one layer first
	m_bChildSet=m_pUser->isBParent();


	//we check what type of user is playing to display good stuff
	if(!m_bChildSet)
	{
		//parent view

		//use to place elements
		auto l_fWidthImage = l_fWidthRect + s_fMarginBetweenImage;
		auto l_fHeightImage = l_fHeightRect + s_fMarginBetweenImage;

		//init the scroll view
		m_pScrollView = ui::ScrollView::create();
		m_pScrollView->setContentSize(l_oPlayableScreenSize);
		m_pScrollView->setAnchorPoint(Vec2(0,0));
		m_pScrollView->setPosition(Vec2(s_fMarginLeft,0));
		m_pScrollView->setDirection(cocos2d::ui::ScrollView::Direction::HORIZONTAL);

		Size l_oContainerSize;
		//check height of piece to know how many to display in a row
		int numberOfImageInLine = (int)l_oPlayableScreenSize.height/l_fHeightImage;
		//if there is no enough image
		if((m_aScrollViewImages.size()/(float)numberOfImageInLine+0.5)*(l_fWidthImage)<=l_oPlayableScreenSize.width)
		{
			//container = framesize
			l_oContainerSize = l_oPlayableScreenSize ;
		}
		else
		{
			l_oContainerSize = Size((m_aScrollViewImages.size()/(float)numberOfImageInLine+0.5)*(l_fWidthImage),l_oPlayableScreenSize.height);
		}

		//set container
		m_pScrollView->setInnerContainerSize(l_oContainerSize);

		//shuffle the vector of scrollimages
		std::random_device rd;
		std::mt19937 g(rd());
		std::shuffle(m_aScrollViewImages.begin(), m_aScrollViewImages.end(), g);

		l_iIndex=0;

		//the layer which contain all the sprites
		m_pLayerScrollView = Layer::create();
		m_pScrollView->addChild(m_pLayerScrollView);

		int l_iLineIndex=1;

		for (std::vector<LmGameComponent*>::iterator it = m_aScrollViewImages.begin(); it != m_aScrollViewImages.end(); ++it)
		{
			(*it)->setPosition(Vec2((l_iIndex)*(l_fWidthImage)
					,-l_fHeightImage*0.5+(l_oOrigin.y+l_oPlayableScreenSize.height)*((float)l_iLineIndex/(float)(numberOfImageInLine+1))));
			(*it)->addTo(m_pLayerScrollView);
			l_iLineIndex++;

			//last line
			if(l_iLineIndex==numberOfImageInLine+1)
			{
				l_iLineIndex=1;
				l_iIndex++;
			}
		}

		m_pScrollView->setBounceEnabled(true);
		m_pScrollView->setTouchEnabled(true);
		m_pLayerUserParent->addChild(m_pScrollView);


		//to listen on touch began etc on the scrollview
		m_pScrollView->setSwallowTouches(false);

		//init listener
		m_pListener = EventListenerTouchOneByOne::create();
		m_pListener->onTouchBegan = CC_CALLBACK_2(LmRightSpotScene::onTouchBeganParent, this);
		m_pListener->onTouchMoved = CC_CALLBACK_2(LmRightSpotScene::onTouchMovedParent, this);
		m_pListener->onTouchEnded = CC_CALLBACK_2(LmRightSpotScene::onTouchEndedParent, this);
		Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(m_pListener,m_pScrollView);

		//add the layer to the game
		m_pLayerGame->addChild(m_pLayerUserParent);
	}
	else
	{

		//init listener
		m_pListener = EventListenerTouchOneByOne::create();
		m_pListener->onTouchBegan = CC_CALLBACK_2(LmRightSpotScene::onTouchBeganChild, this);
		m_pListener->onTouchMoved = CC_CALLBACK_2(LmRightSpotScene::onTouchMovedChild, this);
		m_pListener->onTouchEnded = CC_CALLBACK_2(LmRightSpotScene::onTouchEndedChild, this);
		Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(m_pListener,m_pLayerUserChild);

		m_pLayerGame->addChild(m_pLayerUserChild);
	}

	return true;
}

void LmRightSpotScene::endGame()
{
	if(m_bFinishButtonSync)
	{
		//m_bFinishButtonSync=false;

		//test
		if(m_bChildSet)
		{
			m_bChildSet=false;
			m_pLayerGame->removeChild(m_pLayerUserChild);
			m_pLayerGame->addChild(m_pLayerUserParent,1);
		}
		else
		{
			m_bChildSet=true;
			m_pLayerGame->addChild(m_pLayerUserChild,1);
			m_pLayerGame->removeChild(m_pLayerUserParent);
		}

		/*removeChild(m_pLayerGame);
		CCLOG("popscene");
		Director::getInstance()->popScene();
		Director::getInstance()->getEventDispatcher()->dispatchCustomEvent("InteractionSceneFinished");*/
	}

}

bool LmRightSpotScene::onTouchBeganParent(Touch* touch,Event* event)
{
	//get the id of the gameobject touched or -1 otherwise
	m_iBufferId=idLmGameComponentTouchedInScrollView(touch);

	//if something is touched
	if(m_iBufferId>=0)
	{
		//init bool to know if we leave the location
		m_bSameGameComponent=true;
		//begin a click
		auto delay = DelayTime::create(s_fLongClickDuration);
		m_pLayerScrollView -> runAction( Sequence::create(delay, CallFunc::create( std::bind(&LmRightSpotScene::checkLongClick,this) ), nullptr));
	}
	else
	{
		m_bSameGameComponent=false;
	}

	return true;
}

void LmRightSpotScene::onTouchMovedParent(Touch* touch,Event* event)
{
	if(m_iBufferId==idLmGameComponentTouchedInScrollView(touch) && m_bSameGameComponent)
	{
		//we are on the same object
		m_bSameGameComponent=true;
	}
	else
	{
		m_bSameGameComponent=false;
	}

	if(m_bSpriteSelected)
	{
		auto l_oTouchLocation = touch->getLocation();
		m_pBufferSprite->setPosition(l_oTouchLocation.x,l_oTouchLocation.y);
		m_pBufferSprite->setAnchorPoint(Vec2(0.5,0.5));

		if(bufferCollideSendingArea())
		{
			//we send the id to the other tablet test
			CCLOG("we send the %d gamecomponent",m_aIdTable.find(m_iBufferId)->first);

			m_bSpriteSelected=false;
			m_pScrollView->setTouchEnabled(true);
			//remove the buffer sprite from the layer
			m_pLayerUserParent->removeChild(m_pBufferSprite);

			//we put the gamecomponent visible again (local)
			m_aIdTable.find(m_iBufferId)->second->setVisible(true);

			//remove the element of the scrollview vector
			m_aScrollViewImages.erase(std::remove(m_aScrollViewImages.begin(),m_aScrollViewImages.end(),m_aIdTable.find(m_iBufferId)->second), m_aScrollViewImages.end());

			//test remove it from this layer
			m_aIdTable.find(m_iBufferId)->second->removeFrom(m_pLayerUserParent);

			layerChildReceive(m_iBufferId);


		}
	}

}

void LmRightSpotScene::onTouchEndedParent(cocos2d::Touch*, cocos2d::Event*)
{

	//reset the action
	m_bSameGameComponent=false;


	if(m_bSpriteSelected)
	{
		//no sprite selected anymore
		m_bSpriteSelected=false;
		m_pScrollView->setTouchEnabled(true);

		//remove the buffer sprite froim the layer
		m_pLayerUserParent->removeChild(m_pBufferSprite);
		//we put the gamecomponent visible again
		m_aIdTable.find(m_iBufferId)->second->setVisible(true);
	}



}

int LmRightSpotScene::idLmGameComponentTouchedInScrollView(Touch* touch)
{
	auto l_oTouchLocation = touch->getLocation();

	for (std::vector<LmGameComponent*>::iterator it = m_aScrollViewImages.begin(); it != m_aScrollViewImages.end(); ++it)
	{

		if((*it)->getBoundingBoxInWorldSpace(m_pLayerScrollView).containsPoint(l_oTouchLocation))
		{
			return (*it)->getIId();
		}
	}
	return -1;
}

void LmRightSpotScene::checkLongClick()
{
	if(m_bSameGameComponent)
	{
		//with the buffer id we know which game component is selected
		CCLOG("lond click on %d",m_aIdTable.find(m_iBufferId)->first);

		//the sprite is selected
		m_bSpriteSelected=true;
		m_pScrollView->setTouchEnabled(false);
		//the gamecomponent selected is copy in the buffer
		m_pBufferSprite = Sprite::createWithSpriteFrame(m_aIdTable.find(m_iBufferId)->second->getPSpriteComponent()->getSpriteFrame());
		m_pBufferSprite->setPosition(m_aIdTable.find(m_iBufferId)->second->getPositionInWorldSpace(m_pLayerScrollView));
		m_pBufferSprite->setAnchorPoint(Vec2(0,0));
		//then gameobject is invisible and we add the buffer
		m_aIdTable.find(m_iBufferId)->second->setVisible(false);
		m_pLayerUserParent->addChild(m_pBufferSprite);
	}

}

bool LmRightSpotScene::bufferCollideSendingArea()
{
	return m_pBufferSprite->getBoundingBox().intersectsRect(m_pSendingArea->getPSpriteComponent()->getBoundingBox());
}

bool LmRightSpotScene::onTouchBeganChild(Touch* touch,Event* event)
{
	m_iBufferId = idLmGameComponentTouchedInSendingArea(touch);

	movePieceReceived(touch,m_iBufferId);
	return true;
}

void LmRightSpotScene::onTouchMovedChild(Touch* touch,Event* event)
{
	movePieceReceived(touch,m_iBufferId);
}

void LmRightSpotScene::onTouchEndedChild(Touch* touch,Event* event)
{

}

void LmRightSpotScene::layerChildReceive(int l_iIdLmGameComponent)
{
	//use to place elements
	Size l_oVisibleSize = Director::getInstance()->getVisibleSize();
	Point l_oOrigin = Director::getInstance()->getVisibleOrigin();

	//we get the gamecomponent with id
	auto l_pGameComponentReceived = m_aIdTable.find(l_iIdLmGameComponent)->second;

	//put it approximatly in the sending area
	l_pGameComponentReceived->setPosition(Vec2(l_oVisibleSize.width*0.9,l_oVisibleSize.height*0.5));
	l_pGameComponentReceived->setAnchorPoint(Vec2(0,0));
	m_aSendingAreaElements.push_back(l_pGameComponentReceived);
	l_pGameComponentReceived->addTo(m_pLayerUserChild);

}

int LmRightSpotScene::idLmGameComponentTouchedInSendingArea(Touch* touch)
{
	auto l_oTouchLocation = touch->getLocation();

	for (std::vector<LmGameComponent*>::iterator it = m_aSendingAreaElements.begin(); it != m_aSendingAreaElements.end(); ++it)
	{
		if((*it)->getBoundingBoxInWorldSpace(m_pLayerUserChild).containsPoint(l_oTouchLocation))
		{
			return (*it)->getIId();
		}
	}
	return -1;
}

void LmRightSpotScene::movePieceReceived(Touch* touch,int id)
{
	auto l_oTouchLocation = touch->getLocation();
	m_aIdTable.find(id)->second->setPosition(Vec2(l_oTouchLocation.x,l_oTouchLocation.y));
	m_aIdTable.find(id)->second->setAnchorPoint(Vec2(0.5,0.5));

}
