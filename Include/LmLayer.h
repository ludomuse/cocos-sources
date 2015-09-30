/*************************************************************************
 LmLayer  - object that contain a sound an img
 and a texte to make intro of each InteractionScene
 *************************************************************************/
#ifndef LMLAYER_H
#define LMLAYER_H

#include "cocos2d.h"
#include "SimpleAudioEngine.h"

class LmLayer: public cocos2d::Layer
{

private:

	//url of the img
	std::vector<std::pair<std::string, int>> m_aImagesURL;
	std::string m_sSoundURL;
	std::string m_sText;

public:

	//use to init img, sound, text
	LmLayer(std::vector<std::pair<std::string, int>>, std::string, std::string);
	~LmLayer();

	bool init();
	void playSound();
	void pauseSound();

};

#endif // LMLAYER_H
