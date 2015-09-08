/*************************************************************************
                           LmServerManager  -  Get the Json from the server
 *************************************************************************/

#ifndef LMSERVERMANAGER_H__
#define LMSERVERMANAGER_H__

#include <vector>
#include "LmJsonParser.h"
#include "LmFactory.h"

//Differents Scene of the application
#include "LmInteractionScene.h"
#include "LmPuzzleScene.h"



class LmServerManager
{

private:

	//JsonParser to read our Json File couple with a factory to instanciate InteractionScene and GameComponent
	LmJsonParser* m_pLmJsonparser;

	//our factory to create InteractionScene and GameComponent
	LmFactory* m_pLmFactory;

	//our vector of Scene
	std::vector<LmInteractionScene*> m_aInteractionSceneOfTheGame;

public:

	LmServerManager();
	~LmServerManager();

	//return the vector of InteractionScene
	std::vector<LmInteractionScene*> getInteractionSceneOfTheGame();

	//init
	bool init();

};


#endif // LMSERVERMANAGER_H__
