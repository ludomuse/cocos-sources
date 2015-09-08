/*************************************************************************
                           LmLayer  - object that contain a sound an img
                           and a texte to make intro of each InteractionScene
 *************************************************************************/
#ifndef LMLAYER_H
#define LMLAYER_H

#include "cocos2d.h"


class LmLayer : public cocos2d::Layer
{

private:

	//url of the img
	std::string m_sImageURL;
	std::string m_sSoundURL;
	const char* m_pText;


public:

	LmLayer();
	//use to init img, sound, text
	LmLayer(std::string,std::string,const char*);
	~LmLayer();

	bool init();


};

#endif // LMLAYER_H
