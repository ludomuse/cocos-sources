//use for the debug
#define COCOS2D_DEBUG 1

#include "../Include/LmLayer.h"

USING_NS_CC;

LmLayer::~LmLayer()
{

}

LmLayer::LmLayer(std::vector<std::pair<std::string, int>> l_aImagesURL,
		std::string l_pSoundURL, std::string l_pText)
{
	m_aImagesURL = l_aImagesURL;
	m_sSoundURL = l_pSoundURL;
	m_sText = l_pText;
}

bool LmLayer::init()
{

	//use to place elements
	Size l_oVisibleSize = Director::getInstance()->getVisibleSize();
	Point l_oOrigin = Director::getInstance()->getVisibleOrigin();

	//we add sprites
	for (std::vector<std::pair<std::string, int>>::iterator it =
			m_aImagesURL.begin(); it != m_aImagesURL.end(); ++it)
	{
		auto l_oSprite = Sprite::create(it->first);
		switch (it->second)
		{

		//center
		case 0:
			l_oSprite->setPosition(l_oVisibleSize.width / 2 + l_oOrigin.x,
					l_oVisibleSize.height / 2 + l_oOrigin.y);
			break;

			//top left
		case 1:
			l_oSprite->setPosition(l_oVisibleSize.width / 4 + l_oOrigin.x,
					3 * l_oVisibleSize.height / 4 + l_oOrigin.y);
			break;

			//top right
		case 2:
			l_oSprite->setPosition(3 * l_oVisibleSize.width / 4 + l_oOrigin.x,
					3 * l_oVisibleSize.height / 4 + l_oOrigin.y);
			break;

			//bottom left
		case 3:
			l_oSprite->setPosition(l_oVisibleSize.width / 4 + l_oOrigin.x,
					l_oVisibleSize.height / 4 + l_oOrigin.y);
			break;

			//bottom right
		case 4:
			l_oSprite->setPosition(3 * l_oVisibleSize.width / 4 + l_oOrigin.x,
					l_oVisibleSize.height / 4 + l_oOrigin.y);
			break;

		default:
			break;
		}
		addChild(l_oSprite, 0);
	}

	//we preload the sound
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic(
			m_sSoundURL.c_str());

	//we add text to the center of the screen
	auto l_oLabel = Label::createWithTTF(m_sText,
			"fonts/JosefinSans-Regular.ttf", 50);
	l_oLabel->setPosition(l_oVisibleSize.width / 2 + l_oOrigin.x,
			l_oVisibleSize.height / 2 + l_oOrigin.y);
	addChild(l_oLabel, 1);

	return true;
}

void LmLayer::playSound()
{
	//play sound
	CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic(
			m_sSoundURL.c_str(), false);
}

void LmLayer::pauseSound()
{
	//pause sound
	CocosDenshion::SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

