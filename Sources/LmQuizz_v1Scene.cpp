/*
 * LmQuizz_v1.cpp
 *
 *  Created on: 24 sept. 2015
 *      Author: IHMTEKDev4
 */

#include "../Include/LmQuizz_v1Scene.h"

using namespace cocos2d;
using namespace cocos2d::ui;

LmQuizz_v1Scene::LmQuizz_v1Scene()
{
	//json
	m_sFilenameSpriteBackground="log.png";

	std::map<std::string,bool> response1;
	response1.insert(std::pair<std::string,bool>("marc",true));
	response1.insert(std::pair<std::string,bool>("jean",false));
	response1.insert(std::pair<std::string,bool>("patrick",false));
	response1.insert(std::pair<std::string,bool>("emile",false));
	std::map<std::string,bool> response2;
	response2.insert(std::pair<std::string,bool>("orange",false));
	response2.insert(std::pair<std::string,bool>("noir",false));
	response2.insert(std::pair<std::string,bool>("rouge",true));
	response2.insert(std::pair<std::string,bool>("vert",false));

	m_aQuestionResponseMap.insert(std::pair<std::string,std::map<std::string,bool>> ("Comment t'appelle tuje fais un test pour voir quelle est l'effet quand on raconte sa vie dans la question?",response1));
	m_aQuestionResponseMap.insert(std::pair<std::string,std::map<std::string,bool>> ("Quelle est la couleur du cheval bllanc d'henri III",response2));

	m_iAttemptByQuestion=3;

	//pointer
	m_pFinishButton=nullptr;
	m_pSpriteBackground=nullptr;
	m_pTimer=nullptr;
	m_pSpriteAnswerSelected=nullptr;
	m_pListener=nullptr;

	//primitive type
	m_bFinishButtonSync=true;
	m_iCounter=0;
	m_iAnswerSlected=-1;
	m_fHeight=0;
	m_iIndexLayer=0;
	m_bQuestionNotFinish=false;
	m_iNumberOfAttempt=m_iAttemptByQuestion;
}

LmQuizz_v1Scene::LmQuizz_v1Scene(std::string l_sFilenameSpriteBackground,std::map<std::string,std::map<std::string,bool>> l_aQuestionResponseMap)
{

}

LmQuizz_v1Scene::~LmQuizz_v1Scene()
{
	for (std::vector<Layer*>::iterator it = m_aLayers.begin(); it != m_aLayers.end(); ++it)
	{
		(*it)->release();
	}

	Director::getInstance()->getEventDispatcher()->removeEventListener(m_pListener);
}

void LmQuizz_v1Scene::runGame()
{
	initGame();
	//we preload the sound
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("audio/son.mp3");
}

bool LmQuizz_v1Scene::initGame()
{

	//use to place elements
	Size l_oVisibleSize = Director::getInstance()->getVisibleSize();
	Point l_oOrigin = Director::getInstance()->getVisibleOrigin();

	//create layer game and add to this
	m_pLayerGame = Layer::create();
	this->addChild(m_pLayerGame,0);

	//init the background
	m_pSpriteBackground = Sprite::create(m_sFilenameSpriteBackground);
	m_pSpriteBackground->setPosition(l_oVisibleSize.width*0.5f+l_oOrigin.x,l_oVisibleSize.height*0.5f+l_oOrigin.y);
	m_pLayerGame->addChild(m_pSpriteBackground);

	/*//finish button
	m_pFinishButton = ui::Button::create("nextButtonNormal.png","nextButtonPressed.png");
	m_pFinishButton->setTouchEnabled(true);
	m_pFinishButton -> setPosition(Vect(l_oVisibleSize.width-m_pFinishButton->getContentSize().width*0.8,m_pFinishButton->getContentSize().height*0.7));
	m_pFinishButton->addTouchEventListener(CC_CALLBACK_0(LmQuizz_v1Scene::endGame, this));
	m_pLayerGame->addChild(m_pFinishButton,1);*/

	//loading bar to show timer progression
	m_pTimer = LoadingBar::create();
	m_pTimer->setName("LoadingBar");
	m_pTimer->loadTexture("bandMid.png");
	m_pTimer->setPercent(0);
	m_pTimer->setPosition(Point(l_oVisibleSize.width*0.5f+l_oOrigin.x,l_oVisibleSize.height*0.05+l_oOrigin.y));
	m_pLayerGame->addChild(m_pTimer,1);

	//init the sprite to show what answer is lselected
	m_pSpriteAnswerSelected = Sprite::create("answerSelected.png");
	m_pSpriteAnswerSelected->setVisible(false);
	m_pLayerGame->addChild(m_pSpriteAnswerSelected,1);

	//init layer end question
	m_pLayerEndQuestion = Layer::create();

	//init the background of this layer
	auto l_pSpriteBackgroundLayerEnd = Sprite::create("endQuestionBackground.png");
	l_pSpriteBackgroundLayerEnd->setPosition(l_oVisibleSize.width*0.5f+l_oOrigin.x,l_oVisibleSize.height*0.5f+l_oOrigin.y);
	m_pLayerEndQuestion->addChild(l_pSpriteBackgroundLayerEnd);
	m_pLayerEndQuestion->setVisible(false);
	m_pLayerGame->addChild(m_pLayerEndQuestion,2);

	//init its listener
	m_pListener = EventListenerTouchOneByOne::create();
	m_pListener->onTouchBegan = CC_CALLBACK_2(LmQuizz_v1Scene::onTouchBeganLayerEnd, this);
	m_pListener->setEnabled(false);
	m_pListener->setSwallowTouches(true);

	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(m_pListener,m_pLayerEndQuestion);

	//one layer per question
	initLayers();


	beginQuestion();

}

void LmQuizz_v1Scene::endGame()
{
	if(m_bFinishButtonSync)
	{
		m_bFinishButtonSync=false;
		removeChild(m_pLayerGame);
		CCLOG("popscene");
		Director::getInstance()->popScene();
		Director::getInstance()->getEventDispatcher()->dispatchCustomEvent("InteractionSceneFinished");
	}
}

void LmQuizz_v1Scene::updateLoadingBar(float dt)
{
	m_iCounter++;
	if (m_iCounter > 100)
	{
		scheduleOnce(schedule_selector(  LmQuizz_v1Scene::timerEnd ), 0);
		unschedule(schedule_selector(LmQuizz_v1Scene::updateLoadingBar));
	}
	m_pTimer->setPercent(m_iCounter);
}

void LmQuizz_v1Scene::timerEnd(float dt)
{
	m_iNumberOfAttempt=0;
	m_bQuestionNotFinish=false;
	checkAnswer();
}

void LmQuizz_v1Scene::beginQuestion()
{
	m_bQuestionNotFinish=true;

	m_iNumberOfAttempt=m_iAttemptByQuestion;

	//set invisible the sprite selected
	m_pSpriteAnswerSelected->setVisible(false);

	//reset timer
	unschedule(schedule_selector(LmQuizz_v1Scene::updateLoadingBar));
	m_pTimer->setPercent(0);
	m_iCounter=0;
	schedule(schedule_selector(LmQuizz_v1Scene::updateLoadingBar),s_fTimerDuration);

	//disable answer selected
	m_iAnswerSlected=-1;

	//next layer
	m_pLayerGame->addChild(m_aLayers.at(m_iIndexLayer));

}

void LmQuizz_v1Scene::initLayers()
{
	//use to place elements
	Size l_oVisibleSize = Director::getInstance()->getVisibleSize();
	Point l_oOrigin = Director::getInstance()->getVisibleOrigin();

	for(const auto& element : m_aQuestionResponseMap)
	{
		//init layer
		m_aLayers.push_back(Layer::create());
		m_aLayers.at(m_aLayers.size()-1)->retain();
		//put a band sprite top to place question in it
		auto l_pBandTopSprite = Sprite::create("bandTop.png");
		l_pBandTopSprite->setAnchorPoint(Vec2(0,1));
		l_pBandTopSprite->setPosition(Vec2(0,l_oVisibleSize.height+l_oOrigin.y));
		m_aLayers.at(m_aLayers.size()-1)->addChild(l_pBandTopSprite);

		//put the label question in it
		auto l_pLabelQuestion = Label::createWithTTF(element.first, "fonts/JosefinSans-Regular.ttf",20);
		l_pBandTopSprite->addChild(l_pLabelQuestion);
		l_pLabelQuestion->setPosition(Vec2(l_pBandTopSprite->getContentSize().width*0.5,l_pBandTopSprite->getContentSize().height*0.5));
		l_pLabelQuestion->setColor(Color3B::BLACK);
		l_pLabelQuestion->setMaxLineWidth(l_oVisibleSize.width*0.9);


		int l_iIndex=0;
		m_fHeight = l_oVisibleSize.height-l_pBandTopSprite->getContentSize().height-m_pTimer->getContentSize().height;
		// create menu, it's an autorelease object
		auto l_oMenu = Menu::create();

		//init answers
		for(const auto& answer : element.second)
		{
			auto l_pLabelAnswer = Label::createWithTTF(answer.first, "fonts/JosefinSans-Regular.ttf",20);
			cocos2d::MenuItemImage* spriteBackgroundAnswer;

			//if its the good one
			if(answer.second)
			{
				m_aNumberGoodAnswer.push_back(l_iIndex);
			}
			char l_aBufferNumber[10];
			sprintf(l_aBufferNumber,"%d.",l_iIndex+1);
			auto l_pLabelNumber =  Label::createWithTTF(l_aBufferNumber, "fonts/JosefinSans-Regular.ttf",20);


			//place the sprite background
			switch(l_iIndex)
			{
			case 0:
				//first answer
				spriteBackgroundAnswer = MenuItemImage::create("answerBackground.png","answerBackground.png",
						CC_CALLBACK_1(LmQuizz_v1Scene::firstAnswerSelected, this));

				spriteBackgroundAnswer->setPosition(l_oVisibleSize.width*0.25,m_fHeight*0.75f+m_pTimer->getContentSize().height);
				break;
			case 1:
				//second answer
				spriteBackgroundAnswer = MenuItemImage::create("answerBackground.png","answerBackground.png",
						CC_CALLBACK_1(LmQuizz_v1Scene::secondAnswerSelected, this));
				spriteBackgroundAnswer->setPosition(l_oVisibleSize.width*0.75,m_fHeight*0.75f+m_pTimer->getContentSize().height);
				break;
			case 2:
				//third answer
				spriteBackgroundAnswer = MenuItemImage::create("answerBackground.png","answerBackground.png",
						CC_CALLBACK_1(LmQuizz_v1Scene::thirdAnswerSelected, this));
				spriteBackgroundAnswer->setPosition(l_oVisibleSize.width*0.25,m_fHeight*0.25f+m_pTimer->getContentSize().height);
				break;
			case 3:
				//fourth answer
				spriteBackgroundAnswer = MenuItemImage::create("answerBackground.png","answerBackground.png",
						CC_CALLBACK_1(LmQuizz_v1Scene::fourthAnswerSelected, this));
				spriteBackgroundAnswer->setPosition(l_oVisibleSize.width*0.75,m_fHeight*0.25f+m_pTimer->getContentSize().height);
				break;
			default:
				break;
			}

			l_iIndex++;

			spriteBackgroundAnswer->addChild(l_pLabelAnswer);
			spriteBackgroundAnswer->addChild(l_pLabelNumber);
			l_pLabelNumber->setPosition(Vec2(spriteBackgroundAnswer->getContentSize().width*0.1,spriteBackgroundAnswer->getContentSize().height*0.5));
			l_pLabelAnswer->setPosition(Vec2(spriteBackgroundAnswer->getContentSize().width*0.6,spriteBackgroundAnswer->getContentSize().height*0.5));
			l_pLabelAnswer->setColor(Color3B::BLACK);
			l_pLabelNumber->setColor(Color3B::BLACK);
			l_pLabelAnswer->setMaxLineWidth(spriteBackgroundAnswer->getContentSize().width*0.8);

			l_oMenu->addChild(spriteBackgroundAnswer);

		}


		l_oMenu->setPosition(Vec2::ZERO);
		m_aLayers.at(m_aLayers.size()-1)->addChild(l_oMenu);
	}
}

bool LmQuizz_v1Scene::firstAnswerSelected(cocos2d::Ref* l_oSender)
{

	if(m_iAnswerSlected!=0 && m_bQuestionNotFinish)
	{
		Size l_oVisibleSize = Director::getInstance()->getVisibleSize();

		m_iAnswerSlected=0;
		m_pSpriteAnswerSelected->setPosition(l_oVisibleSize.width*0.25,m_fHeight*0.75f+m_pTimer->getContentSize().height);
		m_pSpriteAnswerSelected->setVisible(true);
	}//hack because layer dont swallow touches
	else if(!m_bQuestionNotFinish)
	{
		onTouchBeganLayerEnd(nullptr,nullptr);
		return false;

	}
	checkAnswer();
	return true;
}

bool LmQuizz_v1Scene::secondAnswerSelected(cocos2d::Ref* l_oSender)
{
	if(m_iAnswerSlected!=1 && m_bQuestionNotFinish)
	{
		Size l_oVisibleSize = Director::getInstance()->getVisibleSize();

		m_iAnswerSlected=1;
		m_pSpriteAnswerSelected->setPosition(l_oVisibleSize.width*0.75,m_fHeight*0.75f+m_pTimer->getContentSize().height);
		m_pSpriteAnswerSelected->setVisible(true);
	}//hack because layer dont swallow touches
	else if(!m_bQuestionNotFinish)
	{
		onTouchBeganLayerEnd(nullptr,nullptr);
		return false;

	}

	checkAnswer();

	return true;
}

bool LmQuizz_v1Scene::thirdAnswerSelected(cocos2d::Ref* l_oSender)
{
	if(m_iAnswerSlected!=2 && m_bQuestionNotFinish)
	{
		Size l_oVisibleSize = Director::getInstance()->getVisibleSize();

		m_iAnswerSlected=2;
		m_pSpriteAnswerSelected->setPosition(l_oVisibleSize.width*0.25,m_fHeight*0.25f+m_pTimer->getContentSize().height);
		m_pSpriteAnswerSelected->setVisible(true);
	}//hack because layer dont swallow touches
	else if(!m_bQuestionNotFinish)
	{
		onTouchBeganLayerEnd(nullptr,nullptr);
		return false;
	}
	checkAnswer();

	return true;
}

bool LmQuizz_v1Scene::fourthAnswerSelected(cocos2d::Ref* l_oSender)
{
	if(m_iAnswerSlected!=3 && m_bQuestionNotFinish)
	{
		Size l_oVisibleSize = Director::getInstance()->getVisibleSize();

		m_iAnswerSlected=3;
		m_pSpriteAnswerSelected->setPosition(l_oVisibleSize.width*0.75,m_fHeight*0.25f+m_pTimer->getContentSize().height);
		m_pSpriteAnswerSelected->setVisible(true);
	}//hack because layer dont swallow touches
	else if(!m_bQuestionNotFinish)
	{
		onTouchBeganLayerEnd(nullptr,nullptr);
		return false;

	}
	checkAnswer();

	return true;
}

void LmQuizz_v1Scene::checkAnswer()
{
	if(m_aNumberGoodAnswer.at(0)==m_iAnswerSlected)
	{
		m_pLayerEndQuestion->setVisible(true);
		m_pListener->setEnabled(true);
		m_bQuestionNotFinish=false;
		CCLOG("add label and sprite to signify victory");

	}
	else
	{
		if(m_iNumberOfAttempt>0)
		{
			//we loose one attempt
			m_iNumberOfAttempt--;
			//tell player he loose with a sound
			CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("audio/son.mp3",false);
		}
		else
		{
			m_pLayerEndQuestion->setVisible(true);
			m_pListener->setEnabled(true);
			m_bQuestionNotFinish=false;
			CCLOG("add label and sprite to signify loose");
		}

	}
}

bool LmQuizz_v1Scene::onTouchBeganLayerEnd(Touch* touch, Event* event)
{
	CCLOG("click end layer");

	//continue to the next layer
	if(m_iIndexLayer>=m_aLayers.size()-1)
	{
		//no more layers end of the game
		CCLOG("end of the game");
		endGame();
	}
	else
	{
		//next question

		m_pLayerEndQuestion->setVisible(false);
		m_pListener->setEnabled(false);
		//remove the current question
		m_pLayerGame->removeChild(m_aLayers.at(m_iIndexLayer));
		//increment index
		m_iIndexLayer++;
		beginQuestion();

	}
	return true;
}
