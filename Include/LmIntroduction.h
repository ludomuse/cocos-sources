/*************************************************************************
                           LmIntroduction  - one on each InteractionScene
 *************************************************************************/
#ifndef LMINTRODUCTION_H
#define LMINTRODUCTION_H

#include "cocos2d.h"
#include "LmLayer.h"


class LmIntroduction
{

private:

	std::vector<LmLayer*> m_pLayers;

public:

	LmIntroduction();
	LmIntroduction(std::vector<std::string>,std::vector<std::string>,std::vector<const char*>);
	~LmIntroduction();

	bool init();

	LmLayer* getLayer(int)const;

};

#endif // LMINTRODUCTION_H
