/*************************************************************************
 LmPuzzleScene  -
 *************************************************************************/
#ifndef LMPUZZLESCENE_H
#define LMPUZZLESCENE_H

#include "LmInteractionScene.h"

class LmPuzzleScene: public LmInteractionScene
{
public:

	LmPuzzleScene(int);
	~LmPuzzleScene();

private:

	void runGame();

	void end();

	int test;
	bool sync;

	cocos2d::Label* label;

};

#endif // LMPUZZLESCENE_H
