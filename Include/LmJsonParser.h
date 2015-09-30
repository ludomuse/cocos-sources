/*
 * LmJsonParser.h
 *
 *  Created on: 3 sept. 2015
 *      Author: IHMTEKDev4
 */

#ifndef CLASSES_LMJSONPARSER_H_
#define CLASSES_LMJSONPARSER_H_

#include "../../cocos2d/external/json/rapidjson.h"
#include "../../cocos2d/external/json/document.h"
#include "../../cocos2d/external/json/reader.h"
#include "../../cocos2d/external/json/filestream.h"
#include "../../cocos2d/external/json/stringbuffer.h"
#include "../../cocos2d/external/json/writer.h"
#include "../../cocos2d/external/json/prettywriter.h"

#include <string>
#include <iostream>
#include <fstream>
#include "cocos2d.h"

//use to make introduction of each scene
#include "LmInteractionScene.h"
#include "LmPuzzleScene.h"
#include "LmRightSpotScene.h"
#include "LmQuizz_v1Scene.h"
#include "LmSetPoint.h"

class LmJsonParser
{
public:

	LmJsonParser();
	~LmJsonParser();

	//read json file and init his document object in which we can querying value
	//return true if json file open correctly and has a member Ludomuse
	bool initJsonDocument(std::string);

	//init and return the title of the app
	std::string getSTitleApplication();

	//init and return the filename of the sprite splash screen
	std::string getSFilenameSpriteSplashScreen();

	const std::vector<LmInteractionScene*>& getAInteractionSceneOfTheGame(bool);

private:

	//ATTRIBUTES

	//to know which setpoint to get in json file
	bool m_bIsParent;

	//Where we parse the json file
	rapidjson::Document m_oDocument;

	//title of the application
	std::string m_sTitleApplication;

	//title of the application
	std::string m_sFilenameSpriteSplashScreen;

	//our vector of Scene
	std::vector<LmInteractionScene*> m_aInteractionSceneOfTheGame;

	//METHODS

	//init
	void initInteractionSceneOfTheGame();

	//generic method to make all the setpoint 2nd precise which one to take
	LmSetPoint* getLmSetPoint(const rapidjson::Value&, const char*);

	//init the setpoint of an interaction according to the json
	void initSetPoint(const rapidjson::Value& , LmInteractionScene* );

	//our function which make scene
	void makeLmRightSpotScene(const rapidjson::Value&);
	void makeLmQuizz_v1Scene(const rapidjson::Value&);
};

#endif /* CLASSES_LMJSONPARSER_H_ */
