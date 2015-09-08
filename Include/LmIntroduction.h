/*************************************************************************
                           LmIntroduction  - one on each InteractionScene
 *************************************************************************/
#ifndef LMINTRODUCTION_H
#define LMINTRODUCTION_H

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "LmLayer.h"


class LmIntroduction
{

private:

	std::vector<LmLayer*> m_aLayers;
	LmLayer* m_pCurrentLayer;

	//buttons next and previous
	cocos2d::ui::Button* m_pNextButton;
	cocos2d::ui::Button* m_pPreviousButton;

	//get the position of next and previous buttons
	cocos2d::Vect getNextButtonPosition(cocos2d::ui::Button*)const;
	cocos2d::Vect getPreviousButtonPosition(cocos2d::ui::Button*)const;

	//scene pointer of his interaction so it can handle the transition
	cocos2d::Scene* m_pInteractionScene;


public:

	LmIntroduction();
	LmIntroduction(std::vector<std::string>,std::vector<std::string>,std::vector<const char*>);
	~LmIntroduction();

	bool init(cocos2d::Scene*);

	LmLayer* getCurrentLayer()const{return m_pCurrentLayer;}

	//callback method of next button
	//return true if there is a next layer
	bool nextLayer();

	//callback method of  button
	//return true if there is a previous layer
	bool previousLayer();

};

#endif // LMINTRODUCTION_H
