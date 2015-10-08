/*************************************************************************
 JSONParser  -  description

 -------------------
 début                : 2015
 copyright            : (C) 2015 par Rani Baghezza
 *************************************************************************/

//---------- Réalisation de la classe <JSONParser> (fichier JSONParser.cpp) --
//---------------------------------------------------------------- INCLUDE
//-------------------------------------------------------- Include système
using namespace std;

#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include "../../../cocos2d/external/json/rapidjson.h"
#include "../../../cocos2d/external/json/document.h"
#include "../../../cocos2d/external/json/reader.h"
#include "../../../cocos2d/external/json/filestream.h"
#include "../../../cocos2d/external/json/stringbuffer.h"
#include "../../../cocos2d/external/json/writer.h"
#include "../../../cocos2d/external/json/prettywriter.h"

//------------------------------------------------------ Include personnel
#include "../Includes/LmJParserWifiDirect.h"

//------------------------------------------------------------- Constantes

//---------------------------------------------------- Variables de classe

//----------------------------------------------------------- Types privés

//----------------------------------------------------------------- PUBLIC
//-------------------------------------------------------- Fonctions amies

//----------------------------------------------------- Méthodes publiques
// type JSONParser::Méthode ( liste de paramètres )
// Algorithme :
//
//{
//} //----- Fin de Méthode

/**
 *   This method is very similar to parseDevices but it also takes care of the String to CString conversion
 *   so it basically does everything. It takes a JSON String and returns a vector full of device names.
 *
 */

std::vector<std::string> LmJParserWifiDirect::ParseJSONDeviceOperation(
		std::string sJSONDevice) {
	std::vector < std::string > deviceList;
	LmJParserWifiDirect::StringToCString(sJSONDevice);
	deviceList = this->parseDevices();
	return deviceList;
}

void LmJParserWifiDirect::StringToCString(std::string inString) {
	this->cJson = inString.c_str();
}

/**
 *   This method allows us to parse the JSON String that was returned by the Java layer (DiscoverPeers()).
 *
 */

std::vector<std::string> LmJParserWifiDirect::parseDevices() {
	rapidjson::Value name;
	std::string deviceName;
	std::vector < std::string > deviceList;
	assert(this->document.HasMember("deviceArray"));
	//Used to read JSON array
	const rapidjson::Value& arrObjects = this->document["deviceArray"];
	assert(arrObjects.IsArray());
	for (rapidjson::Value::ConstValueIterator itrO = arrObjects.Begin();
			itrO != arrObjects.End(); itrO++) {
		assert(this->document.HasMember("name"));
		//Recover each name value
		//Store them in the list
		//Return the list
		name = this->document["name"];
		deviceName = name.GetString();
		deviceList.push_back(deviceName);
	}
	return deviceList;
}

void LmJParserWifiDirect::SetcJson(std::string sFilePath) {
	fstream oFileToParse;
	string sLine;
	if (oFileToParse.is_open()) {
		while (getline(oFileToParse, sLine)) {

		}
		oFileToParse.close();
	}
	this->cJson = sLine.c_str();
}

void LmJParserWifiDirect::SetDocument() {
	this->document.Parse<0>(this->cJson);
}

void LmJParserWifiDirect::DocumentCheckup() {
	//These variables will store the number of mini-games of each type.
	int nRightSpot, nPuzzle, nMCQ;

	//The following variables will be used to store data from the JSON file
	//in order to call the appropriate constructors to create all the Steps
	std::string sRSImageName;
	int nRSSubImageNb, nRSId;
	std::string arrsRSImageHoles[8][8];

	if (this->document.IsObject()) {
		/*assert(this->document.HasMember("Ludomuse"));
		 //Used to read JSON array
		 const rapidjson::Value& arrObjects = this->document["Ludomuse"];
		 assert(arrObjects.IsArray());
		 for(rapidjson::Value::ConstValueIterator itrO = arrObjects.onBegin(); itrO != arrObjects.onEnd(); itrO++)
		 {
		 assert(this->document.HasMember("RightSpot"));
		 const rapidjson::Value& arrRightSpot = this->document["RightSpot"];
		 assert(arrRightSpot.IsArray());
		 for(rapidjson::Value::ConstValueIterator itrRS = arrRightSpot.onBegin(); itrRS !=arrRightSpot.onEnd(); itrRS++)
		 {

		 }

		 assert(this->document.HasMember("Quizz"));
		 const rapidjson::Value& arrQuizz = this->document["Quizz"];
		 assert(arrQuizz.IsArray());
		 for(rapidjson::Value::ConstValueIterator itrQ = arrRightSpot.onBegin(); itrQ !=arrRightSpot.onEnd(); itrQ++)
		 {


		 }




		 }*/

	} else {
		cout << "Invalid document format" << endl;

	}

	/*

	 //Checking the existence of the variable "nRightSpot" in the JSON document,
	 //Then we make sure it's an int, and we store it in the nRightSpot variable.
	 assert(this->document.HasMember("nRightSpot"));
	 assert(this-document["nRightSpot"].IsInt());
	 nRightSpot = this->document["nRightSpot"].GetInt();

	 //Checking the existence of the variable "nPuzzle" in the JSON document,
	 //Then we make sure it's an int, and we store it in the nPuzzle variable.
	 assert(this->document.HasMember("nPuzzle"));
	 assert(this-document["nPuzzle"].IsInt());
	 nRightSpot = this->document["nPuzzle"].GetInt();

	 //Checking the existence of the variable "nMCQ" in the JSON document,
	 //Then we make sure it's an int, and we store it in the nMCQ variable.
	 assert(this->document.HasMember("nMCQ"));
	 assert(this-document["nMCQ"].IsInt());
	 nRightSpot = this->document["nMCQ"].GetInt();

	 */

	/* if(nRightSpot!=0)
	 {


	 assert(this->document.HasMember("RightSpotAttributes"));
	 //Used to read JSON array
	 const rapidjson::Value& a = this->document["RightSpotAttributes"];
	 assert(a.IsArray());
	 for (rapidjson::SizeType i = 0; i < a.Size(); i++)
	 {


	 } // Uses SizeType instead of size_t
	 //  printf("a[%d] = %d\n", i, a[i].GetInt());

	 //Query Array
	 //for (Value::ConstValueIterator itr = a.Begin(); itr != a.End(); ++itr)
	 // printf("%d ", itr->GetInt());
	 }

	 if(nPuzzle!=0)
	 {
	 assert(this->document.HasMember("Puzzle"));
	 }

	 if(nMCQ!=0)
	 {
	 assert(this->document.HasMember("MCQ"));
	 }

	 if(this->document.HasMember("RightSpot"))
	 {

	 }*/

}

