/*************************************************************************
 AppDelegate  -  Main of the application
 Handle LmMenu and LmGamemanager
 *************************************************************************/
#ifndef  _APP_DELEGATE_H_
#define  _APP_DELEGATE_H_

#include "cocos2d.h"
#include "LmGameManager.h"
#include "LmMenu.h"

//Different resolution
static const cocos2d::Size s_DesignResolutionSize = cocos2d::Size(1280, 800);
static const cocos2d::Size s_SmallResolutionSize = cocos2d::Size(1280, 800);
static const cocos2d::Size s_MediumResolutionSize = cocos2d::Size(1440, 900);
static const cocos2d::Size s_LargeResolutionSize = cocos2d::Size(1680, 1050);

/**
 @brief    The cocos2d Application.

 The reason for implement as private inheritance is to hide some interface call by Director.
 */
class AppDelegate: private cocos2d::Application
{
public:

	AppDelegate();
	virtual ~AppDelegate();

	virtual void initGLContextAttrs();

	/**
	 @brief    Implement Director and Scene init code here.
	 @return true    Initialize success, app continue.
	 @return false   Initialize failed, app terminate.
	 */
	virtual bool applicationDidFinishLaunching();

	/**
	 @brief  The function be called when the application enter background
	 @param  the pointer of the application
	 */
	virtual void applicationDidEnterBackground();

	/**
	 @brief  The function be called when the application enter foreground
	 @param  the pointer of the application
	 */
	virtual void applicationWillEnterForeground();

private:

	//ATTRIBUTES

	//our gameManager which handle the good behavior of the game
	LmGameManager* m_pLmGameManager;

	//this object handle log of user & wifi direct & get info to set after gameanager
	LmMenu* m_pLmMenu;

	//METHODS

	//init paths so the app find good ressources
	void initPathsForResolution();

	bool init();

};

#endif // _APP_DELEGATE_H_

