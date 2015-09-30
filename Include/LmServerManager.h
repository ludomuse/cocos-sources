/*************************************************************************
 LmServerManager  -  Get the Json from the server
 *************************************************************************/

#ifndef LMSERVERMANAGER_H__
#define LMSERVERMANAGER_H__

#include "LmJsonParser.h"

class LmServerManager
{

private:

	//JsonParser to read our Json File couple with a factory to instanciate InteractionScene and GameComponent
	LmJsonParser* m_pLmJsonparser;

public:

	LmServerManager();
	~LmServerManager();

	//return the vector of InteractionScene
	std::vector<LmInteractionScene*> getInteractionSceneOfTheGame(bool);

	//init
	bool init();

	//init with json and return the title
	std::string getSTitleApplication();

	std::string getSFilenameSpriteSplashScreen();
};

#endif // LMSERVERMANAGER_H__
