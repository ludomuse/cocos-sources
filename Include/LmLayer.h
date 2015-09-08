/*************************************************************************
                           LmLayer  - object that contain a sound an img
                           and a texte to make intro of each InteractionScene
 *************************************************************************/
#ifndef LMLAYER_H
#define LMLAYER_H

#include "cocos2d.h"
#include "SimpleAudioEngine.h"



class LmLayer : public cocos2d::Layer
{

private:

	//url of the img
	const char* m_pImageURL;
	const char* m_pSoundURL;
	const char* m_pText;

	//method to scale the text size to the screen
	int getSizeLabel();


public:

	LmLayer();
	//use to init img, sound, text
	LmLayer(const char*,const char*,const char*);
	~LmLayer();

	bool init();


};

#endif // LMLAYER_H
