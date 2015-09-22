/*************************************************************************
                           AppDelegate  -  Main of the application
                           Handle LmMenu and LmGamemanager
 *************************************************************************/
#ifndef  _APP_DELEGATE_H_
#define  _APP_DELEGATE_H_

#include "cocos2d.h"
#include "LmGameManager.h"
#include "LmMenu.h"

/**
@brief    The cocos2d Application.

The reason for implement as private inheritance is to hide some interface call by Director.
 */
class  AppDelegate : private cocos2d::Application
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

	//our gameManager which handle the good behavior of the game
	LmGameManager* m_pLmGameManager;

	//this object handle log of user & wifi direct & get info to set after gameanager
	LmMenu* m_pLmMenu;

	//init paths so the app find good ressources
	void initPathsForResolution();

	bool init();


};

#endif // _APP_DELEGATE_H_

