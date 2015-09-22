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

LmJsonParser::LmJsonParser()
{
	m_sTitleApplication="";
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

const std::vector<LmInteractionScene*>& LmJsonParser::getAInteractionSceneOfTheGame()
{
	if(!m_aInteractionSceneOfTheGame.size())
	{
		initInteractionSceneOfTheGame();
	}

	return m_aInteractionSceneOfTheGame;
}

std::string LmJsonParser::getSTitleApplication()
{
	if(m_sTitleApplication=="")
	{
		//init the string
		assert(m_oDocument["Ludomuse"]["Configuration"].IsObject());
		assert(m_oDocument["Ludomuse"]["Configuration"]["Title"].IsString());

		string l_sBuffer = m_oDocument["Ludomuse"]["Configuration"]["Title"].GetString();

		m_sTitleApplication = l_sBuffer.c_str();

	}

	return m_sTitleApplication;
}

void LmJsonParser::initInteractionSceneOfTheGame()
{
	// Using a reference for consecutive access is handy and faster.
	assert(m_oDocument["Ludomuse"]["SceneArray"].IsArray());
	const rapidjson::Value& l_aSceneArray = m_oDocument["Ludomuse"]["SceneArray"];

	int l_iIdScene=0;

	for (int i=0;i<l_aSceneArray.Size();i++)
	{
		assert(l_aSceneArray[i].IsObject());
		assert(l_aSceneArray[i]["Id"].IsInt());
		l_iIdScene = l_aSceneArray[i]["Id"].GetInt();

		switch (l_iIdScene)
		{

		case LmRightSpotScene::s_iId:
			makeLmRightSpotScene(l_aSceneArray[i]);
		default:
			CCLOG("default switch @ LmJsonParser::initInteractionSceneOfTheGame");
		}


	}

}

LmIntroduction* LmJsonParser::getLmIntroduction(const rapidjson::Value& l_oScene)
{
	LmIntroduction * l_pLmIntroduction = new LmIntroduction;

	//buffers
	std::string imgBuffer;
	std::string soundBuffer;
	std::string textBuffer;


	assert(l_oScene["Introduction"].IsArray());
	for(int i=0;i<l_oScene["Introduction"].Size();i++)
	{
		assert(l_oScene["Introduction"][i].IsObject());
		assert(l_oScene["Introduction"][i]["img"].IsString());
		imgBuffer = l_oScene["Introduction"][i]["img"].GetString();
		assert(l_oScene["Introduction"][i]["sound"].IsString());
		soundBuffer = l_oScene["Introduction"][i]["sound"].GetString();
		assert(l_oScene["Introduction"][i]["text"].IsString());
		textBuffer = l_oScene["Introduction"][i]["text"].GetString();

		l_pLmIntroduction->add(new LmLayer(imgBuffer.c_str(),soundBuffer.c_str(),textBuffer.c_str()));
	}

	return l_pLmIntroduction;
}

void LmJsonParser::makeLmRightSpotScene(const rapidjson::Value& l_oScene)
{
	/*6 parameters =>
	 *  FilenameSpriteBackground
	 *  FilenameSpriteCollideZone
	 *  FilenamesWrongImmages
	 *  FilenameRightImage
	 *  HoleOnX
	 *  HoleOnY
	 *  LocationOfHole*/

	//buffers
	std::string l_sFilenameSpriteBackgroundBuffer;
	std::string l_sFilenameSpriteCollideZoneBuffer;
	std::vector<std::string> l_aFilenamesWrongImagesBuffer;
	std::string l_sFilenameRightImageBuffer;
	int l_iHoleOnXBuffer;
	int l_iHoleOnYBuffer;
	std::vector<std::pair<int,int>> l_aLocationOfHoleBuffer;

	//init buffers
	std::string l_sBuffer;//use to parse to c string to make a deep copy

	assert(l_oScene["FilenameSpriteBackground"].IsString());
	l_sBuffer = l_oScene["FilenameSpriteBackground"].GetString();
	l_sFilenameSpriteBackgroundBuffer = l_sBuffer.c_str();

	assert(l_oScene["FilenameSpriteCollideZone"].IsString());
	l_sBuffer = l_oScene["FilenameSpriteCollideZone"].GetString();
	l_sFilenameSpriteCollideZoneBuffer = l_sBuffer.c_str();

	assert(l_oScene["FilenamesWrongImages"].IsArray());
	for(int i=0;i<l_oScene["FilenamesWrongImages"].Size();i++)
	{
		assert(l_oScene["FilenamesWrongImages"][i].IsString());
		l_sBuffer = l_oScene["FilenamesWrongImages"][i].GetString();
		l_aFilenamesWrongImagesBuffer.push_back(l_sBuffer.c_str());
	}

	assert(l_oScene["FilenameRightImage"].IsString());
	l_sBuffer = l_oScene["FilenameRightImage"].GetString();
	l_sFilenameRightImageBuffer = l_sBuffer.c_str();

	assert(l_oScene["HoleOnX"].IsInt());
	l_iHoleOnXBuffer = l_oScene["HoleOnX"].GetInt();

	assert(l_oScene["HoleOnY"].IsInt());
	l_iHoleOnYBuffer = l_oScene["HoleOnY"].GetInt();

	int x=0;
	int y=0;
	assert(l_oScene["LocationOfHole"].IsArray());
	for(int i=0;i<l_oScene["LocationOfHole"].Size();i++)
	{
		assert(l_oScene["LocationOfHole"][i].IsObject());
		assert(l_oScene["LocationOfHole"][i]["x"].IsInt());
		assert(l_oScene["LocationOfHole"][i]["y"].IsInt());

		x = l_oScene["LocationOfHole"][i]["x"].GetInt();
		y = l_oScene["LocationOfHole"][i]["y"].GetInt();

		l_aLocationOfHoleBuffer.push_back({x,y});
	}



	//create the scene delete in the game manager
	m_aInteractionSceneOfTheGame.push_back(new LmRightSpotScene(
			l_sFilenameSpriteBackgroundBuffer,
			l_sFilenameSpriteCollideZoneBuffer,
			l_aFilenamesWrongImagesBuffer,
			l_sFilenameRightImageBuffer,
			l_iHoleOnXBuffer,
			l_iHoleOnYBuffer,
			l_aLocationOfHoleBuffer));

	//get the element we just push to set the introduction
	m_aInteractionSceneOfTheGame.at(m_aInteractionSceneOfTheGame.size()-1)->setPLmIntroduction(getLmIntroduction(l_oScene));
}


