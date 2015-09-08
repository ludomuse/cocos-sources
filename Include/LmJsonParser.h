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


class LmJsonParser
{
public:

	LmJsonParser();
	~LmJsonParser();

	//read json file and init his document object in which we can querying value
	//return true if json file open correctly and has a member Ludomuse
	bool initJsonDocument(std::string);

	////return true if there is another scene to instanciate in the json file and init idInteractionscene
	bool thereIsAnotherInteractionScene();

	//get the id of the scene i
	int getIdInteractionScene()const{return m_iIdInteractionScene;}

	//put the index to the next scene
	void moveToTheNextScene();

private:

	//Where we parse the json file
	rapidjson::Document m_oDocument;

	//index to know where we are in the Document
	int m_iIndexDocument;

	//id of the interaction scene where index is pointing
	int m_iIdInteractionScene;


};



#endif /* CLASSES_LMJSONPARSER_H_ */
