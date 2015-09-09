/*
 * LmMenu.h
 *
 *  Created on: 9 sept. 2015
 *      Author: IHMTEKDev4
 *
 *      this is the log screen and the menu screen
 */

#ifndef CLASSES_INCLUDE_LMMENU_H_
#define CLASSES_INCLUDE_LMMENU_H_

#include "cocos2d.h"
#include "ui/CocosGUI.h"

class LmMenu
{

private:

	//the scene of the menu (log + wifi)
	cocos2d::Scene* m_pLmMenuScene;

	//our two layer one handle the loging the other the wifidirect
	cocos2d::Layer* m_pLogLayer;
	cocos2d::Layer* m_pWifiLayer;

	//background img
	cocos2d::Sprite* m_pSpriteLogBackground;

	//textfield
	cocos2d::ui::TextField* m_pLogTextfield;

	//callback button methods
	bool log();




public:

	LmMenu();
	~LmMenu();

	//display a log screen then a wifidirect screen and get info
	bool initGame();


};



#endif /* CLASSES_INCLUDE_LMMENU_H_ */
