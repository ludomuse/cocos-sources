/*
 * LmFindGoodCategoryScene.h
 *
 *  Created on: 5 oct. 2015
 *      Author: IHMTEKDev4
 */

#ifndef CLASSES_INCLUDE_LMFINDGOODCATEGORYSCENE_H_
#define CLASSES_INCLUDE_LMFINDGOODCATEGORYSCENE_H_

#include "LmInteractionScene.h"

struct LmFindGoodCategorySceneSeed
{

};

class LmFindGoodCategoryScene: public LmInteractionScene
{
public:

	static const int s_iId = 2;

	LmFindGoodCategoryScene(const LmFindGoodCategorySceneSeed &);
	~LmFindGoodCategoryScene();

private:

};

#endif /* CLASSES_INCLUDE_LMFINDGOODCATEGORYSCENE_H_ */
