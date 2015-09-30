/*************************************************************************
 LmSetPoint  - two on each InteractionScene
 (begin & end)
 *************************************************************************/
#ifndef LMSETPOINT_H
#define LMSETPOINT_H

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "LmLayer.h"

static float s_fTimeBetweenLmLayer = 0.5f;

class LmSetPoint
{

public:

	LmSetPoint();
	LmSetPoint(std::vector<std::string>, std::vector<std::string>,
			std::vector<const char*>);
	~LmSetPoint();

	bool init(cocos2d::Scene*);

	void add(LmLayer*);

	bool isBActionDone() const
	{
		return m_bActionDone;
	}

	//callback method of next button
	//return true if there is a next layer
	bool nextLayer();

	//callback method of  button
	//return true if there is a previous layer
	bool previousLayer();

	int getIIndex() const
	{
		return m_iIndex;
	}

private:

	cocos2d::Scene* m_pInteractionScene;

	std::vector<LmLayer*> m_aLayers;
	LmLayer* m_pCurrentLayer;

	//use to make transition between Lmlayer
	cocos2d::Layer* m_pLayerTransition;

	//to know on what LmLayer m_pCurrentLayer point and to handle border
	int m_iIndex;
	int m_iSize;

	//callback function signature important
	void moveLeftDone();
	void moveRightDone();

	//bool to sync
	bool m_bActionDone;
};

#endif // LMSETPOINT_H
