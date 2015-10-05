/*************************************************************************
 LmServerManager  -  Get the Json from the server
 *************************************************************************/

#ifndef LMSERVERMANAGER_H__
#define LMSERVERMANAGER_H__

#include "LmJsonParser.h"

class LmServerManager
{
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

private:

	//JsonParser to read our Json File & to instanciate InteractionScene
	LmJsonParser* m_pLmJsonparser;

};

#endif // LMSERVERMANAGER_H__
