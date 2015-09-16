/*************************************************************************
                           LmPuzzleScene  -
 *************************************************************************/
#ifndef LMPUZZLESCENE_H
#define LMPUZZLESCENE_H

#include "LmInteractionScene.h"


class LmPuzzleScene : public LmInteractionScene
{
private:

	void runGame();

	void end();

	int test;
	bool sync;

	cocos2d::Label* label;


public:

	LmPuzzleScene(int);
	~LmPuzzleScene();


};

#endif // LMPUZZLESCENE_H
