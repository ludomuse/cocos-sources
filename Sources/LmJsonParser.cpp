/*
 * LmJsonParser.cpp
 *
 *  Created on: 3 sept. 2015
 *      Author: IHMTEKDev4
 */

//use for the debug
#define COCOS2D_DEBUG 1

#include "../Include/LmJsonParser.h"

using namespace std;
using namespace cocos2d;

LmJsonParser::LmJsonParser() : m_iIndexDocument(0), m_iIdInteractionScene(0)
{

}

LmJsonParser::~LmJsonParser()
{

}


bool LmJsonParser::initJsonDocument(string l_sFilename)
{

	string l_sJsonString = FileUtils::getInstance()->getStringFromFile(l_sFilename);
	m_oDocument.Parse<0>(l_sJsonString.c_str());


	//check if the json file has a ludomuse object and an array of scenes
	if(m_oDocument.HasMember("Ludomuse"))
	{
		return true;
	}
	else
	{
		return false;
	}

}

bool LmJsonParser::thereIsAnotherInteractionScene()
{
	// Using a reference for consecutive access is handy and faster.
	assert(m_oDocument["Ludomuse"]["SceneArray"].IsArray());
	const rapidjson::Value& l_aSceneArray = m_oDocument["Ludomuse"]["SceneArray"];

	//if there is still scene
	if(m_iIndexDocument<l_aSceneArray.Size())
	{
		assert(l_aSceneArray[m_iIndexDocument]["id"].IsInt());
		m_iIdInteractionScene = l_aSceneArray[m_iIndexDocument]["id"].GetInt();
		return true;
	}
	else
	{
		return false;
	}

}

void LmJsonParser::moveToTheNextScene()
{
	m_iIndexDocument++;
}

