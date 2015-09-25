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
#include "LmIntroduction.h"

//Differents Scene of the application
#include "LmInteractionScene.h"
#include "LmPuzzleScene.h"
#include "LmRightSpotScene.h"
#include "LmQuizz_v1Scene.h"


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

	const std::vector<LmInteractionScene*>& getAInteractionSceneOfTheGame();

private:

	//ATTRIBUTES

	//Where we parse the json file
	rapidjson::Document m_oDocument;

	//title of the application
	std::string m_sTitleApplication;

	//our vector of Scene
	std::vector<LmInteractionScene*> m_aInteractionSceneOfTheGame;

	//METHODS

	//init
	void initInteractionSceneOfTheGame();

	//generic method to make all the introduction
	LmIntroduction* getLmIntroduction(const rapidjson::Value&);

	//our function which make scene
	void makeLmRightSpotScene(const rapidjson::Value&);
	void makeLmQuizz_v1Scene(const rapidjson::Value&);
};



#endif /* CLASSES_LMJSONPARSER_H_ */
