/*
 * LmQuizz_v1.h
 *
 *  Created on: 24 sept. 2015
 *      Author: IHMTEKDev4
 */

#ifndef CLASSES_INCLUDE_LMQUIZZ_V1SCENE_H_
#define CLASSES_INCLUDE_LMQUIZZ_V1SCENE_H_

#include "LmInteractionScene.h"
#include "ui/CocosGUI.h"

static const int s_fTimerDuration = 0.5f;//time between each percent of the timer bar

class LmQuizz_v1Scene : public LmInteractionScene
{
public:

	//id of this scene
	static const int s_iId = 1;

	LmQuizz_v1Scene();//default one
	LmQuizz_v1Scene(std::string,std::map<std::string,std::map<std::string,bool>> );
	~LmQuizz_v1Scene();

private:

	//ATTRIBUTES

	//json parameters
	std::string m_sFilenameSpriteBackground;
	std::map<std::string,std::map<std::string,bool>>  m_aQuestionResponseMap;
	std::vector<int> m_aNumberGoodAnswer;
	int m_iAttemptByQuestion;


	//gui elements

	cocos2d::Sprite* m_pSpriteBackground;
	//finish button
	cocos2d::ui::Button* m_pFinishButton;
	bool m_bFinishButtonSync;

	int m_iAnswerSlected;
	cocos2d::Sprite* m_pSpriteAnswerSelected;
	//use to place element
	float m_fHeight;

	//timer
	cocos2d::ui::LoadingBar* m_pTimer;
	//timer counter
	int m_iCounter;

	//index of the map which contain question/answer
	std::vector<cocos2d::Layer*> m_aLayers;

	//layer to print at the end of each question
	cocos2d::Layer* m_pLayerEndQuestion;
	//listener
	cocos2d::EventListenerTouchOneByOne* m_pListener;

	//index of question
	int m_iIndexLayer;

	//to know when a question is finish
	bool m_bQuestionNotFinish;

	//buffer to know how attempt remain
	int m_iNumberOfAttempt;


	//METHODS

	//inherit method main of the scene
	void runGame();
	//init method
	bool initGame();
	//call to finished this interaction
	void endGame();

	//timer
	void updateLoadingBar(float);
	void timerEnd(float);

	//utility method
	void beginQuestion();

	//init layer with good label
	void initLayers();

	//callback method of answer box
	bool firstAnswerSelected(cocos2d::Ref*);
	bool secondAnswerSelected(cocos2d::Ref*);
	bool thirdAnswerSelected(cocos2d::Ref*);
	bool fourthAnswerSelected(cocos2d::Ref*);

	//check the answer
	void checkAnswer();

	//callback method for the layer end
	bool onTouchBeganLayerEnd(cocos2d::Touch* , cocos2d::Event*);







};



#endif /* CLASSES_INCLUDE_LMQUIZZ_V1SCENE_H_ */
