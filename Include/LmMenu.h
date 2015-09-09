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
#include "LmUser.h"

static float s_fSplashScreenDuration = 3.0f;

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
	cocos2d::Sprite* m_pSpriteWifiBackground;;
	cocos2d::Sprite* m_pSpriteSplashScreen;

	//textfield
	cocos2d::ui::EditBox* m_pLogEditBox;

	//callback button methods
	bool log();
	void menuIsFinished();

	//callback method of splashscreen
	bool logScreen();

	//both users (1=local & 2=2nd user)
	LmUser* m_pUser1;
	LmUser* m_pUser2;

public:

	LmMenu();
	~LmMenu();

	//display a sprite during s_fSplashScreenDuration then call logscreen method
	void splashScreen();

	LmUser* getPUser1() const {
		return m_pUser1;
	}

	LmUser* getPUser2() const {
		return m_pUser2;
	}
};



#endif /* CLASSES_INCLUDE_LMMENU_H_ */
