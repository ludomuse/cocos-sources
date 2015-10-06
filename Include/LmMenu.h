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

static const float s_fSplashScreenDuration = 0.5f;
static const int s_iMaxLenghtUserName = 10;
//filename sprite
static const std::string s_sFilenameSpriteBackground = "Ludomuse/Background/splash.png";
static const std::string s_sFilenameSplash = "Ludomuse/Background/splash.png";

class LmMenu
{
public:

	LmMenu();
	~LmMenu();

	//display a sprite during s_fSplashScreenDuration then call logscreen method cll from AppDelegate
	void splashScreen();

	LmUser* getPUser1() const
	{
		return m_pUser1;
	}

	LmUser* getPUser2() const
	{
		return m_pUser2;
	}

private:

	//ATTRIBUTES

	//the scene of the menu (log + wifi)
	cocos2d::Scene* m_pLmMenuScene;

	//our two layer one handle the loging the other the wifidirect
	cocos2d::Layer* m_pLogLayer;
	cocos2d::Layer* m_pWifiLayer;

	//background img
	cocos2d::Sprite* m_pSpriteLogBackground;
	cocos2d::Sprite* m_pSpriteWifiBackground;

	cocos2d::Sprite* m_pSpriteSplashScreen;

	//textfield
	cocos2d::ui::EditBox* m_pLogEditBox;

	//both users (1=local & 2=2nd user)
	LmUser* m_pUser1;
	LmUser* m_pUser2;

	//bool to be sure to click one time the play button
	bool m_bPlayButtonClicked;

	//to know gender

	cocos2d::ui::CheckBox* m_pCheckBoxMale;
	cocos2d::ui::CheckBox* m_pCheckBoxFemale;

	bool m_bNoGenderSelected;

	//METHODS

	//callback button methods
	bool wifiDirectScreen(cocos2d::Ref*);

	//function to end menu by sending a custom event
	bool menuIsFinished(cocos2d::Ref*);

	//callback method of splashscreen
	bool logScreen();

	//callback method of answer box
	void maleSelected(cocos2d::Ref*, cocos2d::ui::CheckBox::EventType);
	void femaleSelected(cocos2d::Ref*, cocos2d::ui::CheckBox::EventType);


};

#endif /* CLASSES_INCLUDE_LMMENU_H_ */
