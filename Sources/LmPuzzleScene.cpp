#include "../Include/LmPuzzleScene.h"

USING_NS_CC;

LmPuzzleScene::LmPuzzleScene(int number)
{
	test = number;
	sync = true;
}

LmPuzzleScene::~LmPuzzleScene()
{
}

void LmPuzzleScene::runGame()
{
	//use to place elements
	Size l_oVisibleSize = Director::getInstance()->getVisibleSize();
	Point l_oOrigin = Director::getInstance()->getVisibleOrigin();

	//create layer game and add to this
	m_pLayerGame = Layer::create();
	this->addChild(m_pLayerGame);

	//test
	auto background = Sprite::create("log.png");
	background->setPosition(l_oVisibleSize.width * 0.5f,
			l_oVisibleSize.height * 0.5f);
	m_pLayerGame->addChild(background);

	auto button = ui::Button::create("nextButtonNormal.png",
			"nextButtonPressed.png");
	button->setTouchEnabled(true);
	button->setPosition(
			Vect(l_oVisibleSize.width * 0.5f, l_oVisibleSize.height * 0.5f));
	button->addTouchEventListener(CC_CALLBACK_0(LmPuzzleScene::end, this));
	m_pLayerGame->addChild(button, 1);

	char l_aScoreString[10];
	sprintf(l_aScoreString, "number = %d", test);
	label = Label::createWithTTF(l_aScoreString,
			"fonts/JosefinSans-Regular.ttf", 20);
	label->setPosition(
			Vect(l_oVisibleSize.width * 0.4f, l_oVisibleSize.height * 0.4f));
	m_pLayerGame->addChild(label, 1);
}

void LmPuzzleScene::end()
{
	if (sync)
	{
		sync = false;
		m_bDone = true;
		removeChild(m_pLayerGame);
		CCLOG("popscene");
		Director::getInstance()->popScene();
		Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(
				"InteractionSceneFinished");
	}

}
