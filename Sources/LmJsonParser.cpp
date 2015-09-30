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
	//primitive type
	m_sTitleApplication = "";
	//default value
	m_bIsParent = true;
}

LmJsonParser::~LmJsonParser()
{
}

bool LmJsonParser::initJsonDocument(string l_sFilename)
{

	string l_sJsonString = FileUtils::getInstance()->getStringFromFile(
			l_sFilename);
	m_oDocument.Parse<0>(l_sJsonString.c_str());

	//check if the json file has a ludomuse object and an array of scenes
	if (m_oDocument.HasMember("Ludomuse"))
	{
		return true;
	}
	else
	{
		return false;
	}

}

const std::vector<LmInteractionScene*>& LmJsonParser::getAInteractionSceneOfTheGame(
		bool l_bIsParent)
{
	m_bIsParent = l_bIsParent;

	if (!m_aInteractionSceneOfTheGame.size())
	{
		initInteractionSceneOfTheGame();
	}

	return m_aInteractionSceneOfTheGame;
}

std::string LmJsonParser::getSTitleApplication()
{
	if (m_sTitleApplication == "")
	{
		//init the string
		assert(m_oDocument["Ludomuse"]["Configuration"].IsObject());
		assert(m_oDocument["Ludomuse"]["Configuration"]["Title"].IsString());

		string l_sBuffer =
				m_oDocument["Ludomuse"]["Configuration"]["Title"].GetString();

		m_sTitleApplication = l_sBuffer.c_str();

	}

	return m_sTitleApplication;
}

std::string LmJsonParser::getSFilenameSpriteSplashScreen()
{
	if (m_sFilenameSpriteSplashScreen == "")
	{
		//init the string
		assert(m_oDocument["Ludomuse"]["Configuration"].IsObject());
		assert(
				m_oDocument["Ludomuse"]["Configuration"]["FilenameSpriteSplashScreen"].IsString());

		string l_sBuffer =
				m_oDocument["Ludomuse"]["Configuration"]["FilenameSpriteSplashScreen"].GetString();

		m_sFilenameSpriteSplashScreen = l_sBuffer.c_str();

	}

	return m_sFilenameSpriteSplashScreen;
}

void LmJsonParser::initInteractionSceneOfTheGame()
{
	// Using a reference for consecutive access is handy and faster.
	assert(m_oDocument["Ludomuse"]["SceneArray"].IsArray());
	const rapidjson::Value& l_aSceneArray =
			m_oDocument["Ludomuse"]["SceneArray"];

	int l_iIdScene = 0;

	for (int i = 0; i < l_aSceneArray.Size(); i++)
	{

		assert(l_aSceneArray[i].IsObject());
		assert(l_aSceneArray[i]["Id"].IsInt());
		l_iIdScene = l_aSceneArray[i]["Id"].GetInt();

		switch (l_iIdScene)
		{

		case LmRightSpotScene::s_iId:
			makeLmRightSpotScene(l_aSceneArray[i]);
			break;
		case LmQuizz_v1Scene::s_iId:
			makeLmQuizz_v1Scene(l_aSceneArray[i]);
			break;
		default:
			CCLOG(
					"default switch @ LmJsonParser::initInteractionSceneOfTheGame");
		}
	}

}

LmSetPoint* LmJsonParser::getLmSetPoint(const rapidjson::Value& l_oScene,
		const char* l_sNameSetPoint)
{
	LmSetPoint * l_pLmSetPoint = new LmSetPoint;

	//buffers
	std::vector<std::pair<std::string, int>> l_aImgBuffer;
	std::string l_sImgURLBuffer;
	int l_iAnchorPointBuffer;
	std::string l_sSoundURLBuffer;
	std::string l_sTextURLBuffer;

	std::string l_sBuffer;

	assert(l_oScene[l_sNameSetPoint].IsArray());
	for (int i = 0; i < l_oScene[l_sNameSetPoint].Size(); i++)
	{
		//for each layer
		assert(l_oScene[l_sNameSetPoint][i].IsObject());
		assert(l_oScene[l_sNameSetPoint][i]["img"].IsArray());
		for (int j = 0; j < l_oScene[l_sNameSetPoint][i]["img"].Size(); j++)
		{
			assert(l_oScene[l_sNameSetPoint][i]["img"][j]["imgURL"].IsString());
			assert(
					l_oScene[l_sNameSetPoint][i]["img"][j]["anchorPoint"].IsInt());
			l_sBuffer =
					l_oScene[l_sNameSetPoint][i]["img"][j]["imgURL"].GetString();
			l_sImgURLBuffer = l_sBuffer.c_str();
			l_iAnchorPointBuffer =
					l_oScene[l_sNameSetPoint][i]["img"][j]["anchorPoint"].GetInt();
			l_aImgBuffer.push_back(
			{ l_sImgURLBuffer, l_iAnchorPointBuffer });
		}
		assert(l_oScene[l_sNameSetPoint][i]["sound"].IsString());
		l_sBuffer = l_oScene[l_sNameSetPoint][i]["sound"].GetString();
		l_sSoundURLBuffer = l_sBuffer.c_str();
		assert(l_oScene[l_sNameSetPoint][i]["text"].IsString());
		l_sBuffer = l_oScene[l_sNameSetPoint][i]["text"].GetString();
		l_sTextURLBuffer = l_sBuffer.c_str();

		l_pLmSetPoint->add(
				new LmLayer(l_aImgBuffer, l_sSoundURLBuffer, l_sTextURLBuffer));
	}

	return l_pLmSetPoint;
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
	std::vector<std::pair<int, int>> l_aLocationOfHoleBuffer;

	assert(l_oScene["FilenameSpriteBackground"].IsString());
	l_sFilenameSpriteBackgroundBuffer =
			l_oScene["FilenameSpriteBackground"].GetString();

	assert(l_oScene["FilenameSpriteCollideZone"].IsString());
	l_sFilenameSpriteCollideZoneBuffer =
			l_oScene["FilenameSpriteCollideZone"].GetString();

	assert(l_oScene["FilenamesWrongImages"].IsArray());
	for (int i = 0; i < l_oScene["FilenamesWrongImages"].Size(); i++)
	{
		assert(l_oScene["FilenamesWrongImages"][i].IsString());
		l_aFilenamesWrongImagesBuffer.push_back(
				l_oScene["FilenamesWrongImages"][i].GetString());
	}

	assert(l_oScene["FilenameRightImage"].IsString());
	l_sFilenameRightImageBuffer = l_oScene["FilenameRightImage"].GetString();

	assert(l_oScene["HoleOnX"].IsInt());
	l_iHoleOnXBuffer = l_oScene["HoleOnX"].GetInt();

	assert(l_oScene["HoleOnY"].IsInt());
	l_iHoleOnYBuffer = l_oScene["HoleOnY"].GetInt();

	int x = 0;
	int y = 0;
	assert(l_oScene["LocationOfHole"].IsArray());
	for (int i = 0; i < l_oScene["LocationOfHole"].Size(); i++)
	{
		assert(l_oScene["LocationOfHole"][i].IsObject());
		assert(l_oScene["LocationOfHole"][i]["x"].IsInt());
		assert(l_oScene["LocationOfHole"][i]["y"].IsInt());

		x = l_oScene["LocationOfHole"][i]["x"].GetInt();
		y = l_oScene["LocationOfHole"][i]["y"].GetInt();

		l_aLocationOfHoleBuffer.push_back(
		{ x, y });
	}

	//create the scene delete in the game manager
	m_aInteractionSceneOfTheGame.push_back(
			new LmRightSpotScene(l_sFilenameSpriteBackgroundBuffer,
					l_sFilenameSpriteCollideZoneBuffer,
					l_aFilenamesWrongImagesBuffer, l_sFilenameRightImageBuffer,
					l_iHoleOnXBuffer, l_iHoleOnYBuffer,
					l_aLocationOfHoleBuffer));

	//get the element we just push to set the introduction
	initSetPoint(l_oScene,
				m_aInteractionSceneOfTheGame.at(
						m_aInteractionSceneOfTheGame.size() - 1));
}

void LmJsonParser::makeLmQuizz_v1Scene(const rapidjson::Value& l_oScene)
{
	//TODO
	m_aInteractionSceneOfTheGame.push_back(new LmQuizz_v1Scene);

	initSetPoint(l_oScene,
			m_aInteractionSceneOfTheGame.at(
					m_aInteractionSceneOfTheGame.size() - 1));

}

void LmJsonParser::initSetPoint(const rapidjson::Value& l_oScene,
		LmInteractionScene* l_pInteractionScene)
{
	if (m_bIsParent)
	{
		//get the element we just push to set the introduction begin
		l_pInteractionScene->setPLmSetPointBegin(
				getLmSetPoint(l_oScene, "SetPointBeginParent"));
		//get the element we just push to set the introduction end
		l_pInteractionScene->setPLmSetPointEnd(
				getLmSetPoint(l_oScene, "SetPointEndParent"));
	}
	else
	{
		//get the element we just push to set the introduction begin
		l_pInteractionScene->setPLmSetPointBegin(
				getLmSetPoint(l_oScene, "SetPointBeginChild"));
		//get the element we just push to set the introduction end
		l_pInteractionScene->setPLmSetPointEnd(
				getLmSetPoint(l_oScene, "SetPointEndChild"));
	}
}

