/*
 * LmRightSpot.cpp
 *
 *  Created on: 16 sept. 2015
 *      Author: IHMTEKDev4
 */

#include "../Include/LmRightSpotScene.h"



using namespace cocos2d;

LmRightSpotScene::LmRightSpotScene()
{
	//json
	m_sFilenameSpriteBackground="log.png";
	m_sFilenameSpriteCollideZone="sendingArea.png";
	m_aFilenamesWrongImmages.push_back("wrongImgRightSpotScene1.jpg");
	m_aFilenamesWrongImmages.push_back("wrongImgRightSpotScene2.jpg");
	m_aFilenamesWrongImmages.push_back("wrongImgRightSpotScene3.jpg");
	m_sFilenameRightImage = "imgRightSpotScene.jpg";
	m_iHoleOnX=4;
	m_iHoleOnY=3;
	m_aLocationOfHole.push_back({1,1});
	m_aLocationOfHole.push_back({2,1});
	m_aLocationOfHole.push_back({0,1});




	//other
	m_bFinishButtonSync=true;


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

}

void LmRightSpotScene::runGame()
{
	init();
}

bool LmRightSpotScene::init()
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
	m_pSendingArea->setPosition(Vec2(l_oVisibleSize.width-m_pSendingArea->getSpriteSize().width*0.5f+l_oOrigin.x,l_oVisibleSize.height*0.5));
	m_pLayerGame->addChild(m_pSendingArea);

	Point l_oMiddleOfPlayableArea = Point(l_oOrigin.x+(l_oVisibleSize.width-m_pSendingArea->getSpriteSize().width)*0.5f,l_oVisibleSize.height*0.5f+l_oOrigin.y);
	Size l_oPlayableScreenSize = Size(l_oOrigin.x-s_fMarginLeft+(l_oVisibleSize.width-m_pSendingArea->getSpriteSize().width),l_oVisibleSize.height);

	//finish button
	m_pFinishButton = ui::Button::create("nextButtonNormal.png","nextButtonPressed.png");
	m_pFinishButton->setTouchEnabled(true);
	m_pFinishButton -> setPosition(Vect(l_oVisibleSize.width-m_pFinishButton->getContentSize().width*0.8,m_pFinishButton->getContentSize().height*0.7));
	m_pFinishButton->addTouchEventListener(CC_CALLBACK_0(LmRightSpotScene::endGame, this));
	m_pLayerGame->addChild(m_pFinishButton,1);

	//we get dimension of the right image ( /!\ guessing that all ressources are making same resolution /!\ )
	auto l_oSpriteRightImgSpot = Sprite::create(m_sFilenameRightImage);
	float l_iWidthRect = l_oSpriteRightImgSpot->getContentSize().width/m_iHoleOnX;
	float l_iHeightRect = l_oSpriteRightImgSpot->getContentSize().height/m_iHoleOnY;

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
				l_oRectStencil = Rect(l_iWidthRect*i,l_iHeightRect*j,l_iWidthRect,l_iHeightRect);
				//add new gamecomponent
				m_aScrollViewImages.push_back(new LmGameComponent);
				//register it into the id table
				m_aIdTable.insert(std::pair<int,LmGameComponent*>(m_aScrollViewImages.at(l_iIndex)->getIId(),m_aScrollViewImages.at(l_iIndex)));
				//cut the right rect on the source file
				m_aScrollViewImages.at(l_iIndex)->initSpriteComponent((*it),l_oRectStencil);
				m_aScrollViewImages.at(l_iIndex)->setAnchorPoint(Vec2(0,0.5));
				l_iIndex++;

			}
		}
	}

	l_iIndex=0;

	//init vector of the right image
	Point l_oPointToPlaceRightImage = Point((-l_iWidthRect*m_iHoleOnX*0.25)+l_oMiddleOfPlayableArea.x,(l_iHeightRect*m_iHoleOnY*0.25)+l_oMiddleOfPlayableArea.y);

	for(int i=0;i<m_iHoleOnX;i++)
	{
		for(int j=0;j<m_iHoleOnY;j++)
		{
			l_oRectStencil = Rect(l_iWidthRect*i,l_iHeightRect*j,l_iWidthRect,l_iHeightRect);
			m_aRightImage.push_back(new LmGameComponent);

			//check if this piece is a hole
			std::vector<std::pair<int,int>>::iterator it;
			std::pair<int,int> l_PairBuffer = {i,j};
			it=std::find(m_aLocationOfHole.begin(), m_aLocationOfHole.end(),l_PairBuffer);
			if(it != m_aLocationOfHole.end())
			{
				//yes we also add this piece to the scrollview
				m_aScrollViewImages.push_back(m_aRightImage.at(l_iIndex));
				m_aRightImage.at(l_iIndex)->setAnchorPoint(Vec2(0,0.5));

			}
			else
			{
				//no we set position and add it to layer child
				m_aRightImage.at(l_iIndex)->setAnchorPoint(Vec2(0,0));
				m_aRightImage.at(l_iIndex)->setPosition(l_iWidthRect*i+l_oPointToPlaceRightImage.x,-l_iHeightRect*j+l_oPointToPlaceRightImage.y);
				m_pLayerUserChild->addChild(m_aRightImage.at(l_iIndex));
			}

			//register it into the id table
			m_aIdTable.insert(std::pair<int,LmGameComponent*>(m_aRightImage.at(l_iIndex)->getIId(),m_aRightImage.at(l_iIndex)));
			m_aRightImage.at(l_iIndex)->initSpriteComponent(m_sFilenameRightImage,l_oRectStencil);
			l_iIndex++;
		}
	}



	//test
	m_bChildSet=m_pUser->isBParent();

	//we check what type of user is playing to display good stuff change the bool test
	if(!m_bChildSet)
	{
		auto l_iWidthImage = l_iWidthRect + s_fMarginBetweenImage;
		auto l_iHeightImage = l_iHeightRect + s_fMarginBetweenImage;

		//init the scroll view
		m_pScrollView = ui::ScrollView::create();
		m_pScrollView->setContentSize(l_oPlayableScreenSize);
		m_pScrollView->setAnchorPoint(Vec2(0,0));
		m_pScrollView->setPosition(Vec2(s_fMarginLeft,0));
		m_pScrollView->setDirection(cocos2d::ui::ScrollView::Direction::HORIZONTAL);

		//if there is no enough image
		Size l_oContainerSize;
		//check height of piece to know how many to display in a row
		int numberOfImageInLine = (int)l_oPlayableScreenSize.height/l_iHeightImage;
		if((m_aScrollViewImages.size()+0.5)*(l_iWidthImage)<=l_oPlayableScreenSize.width)
		{
			//container = framesize
			l_oContainerSize = l_oPlayableScreenSize ;
		}
		else
		{
			l_oContainerSize = Size((m_aScrollViewImages.size()/(float)numberOfImageInLine+0.5)*(l_iWidthImage),l_oPlayableScreenSize.height);
		}

		m_pScrollView->setInnerContainerSize(l_oContainerSize);

		//shuffle the vector of scrollimages
		std::random_device rd;
		std::mt19937 g(rd());

		std::shuffle(m_aScrollViewImages.begin(), m_aScrollViewImages.end(), g);

		l_iIndex=0;


		int l_iLineIndex=1;

		for (std::vector<LmGameComponent*>::iterator it = m_aScrollViewImages.begin(); it != m_aScrollViewImages.end(); ++it)
		{
			(*it)->setPosition(Vec2((l_iIndex+0.5)*(l_iWidthImage),(l_oOrigin.y+l_oPlayableScreenSize.height)*((float)l_iLineIndex/(float)(numberOfImageInLine+1))));//l_oOrigin.y+l_oPlayableScreenSize.height*(lineIndex/numberOfImageInLine+1)));
			m_pScrollView->addChild((*it));
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
		m_pScrollView->setInertiaScrollEnabled(true);
		m_pLayerUserParent->addChild(m_pScrollView);

		//add the layer to the game
		m_pLayerGame->addChild(m_pLayerUserParent);
	}
	else
	{


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
			CCLOG("set parent");
			m_pLayerGame->removeChild(m_pLayerUserChild);
			m_pLayerGame->addChild(m_pLayerUserParent,1);
		}
		else
		{
			CCLOG("set child");
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
