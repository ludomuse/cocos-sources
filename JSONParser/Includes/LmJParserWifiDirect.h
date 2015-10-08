#if ! defined ( JSONPARSER_H )
#define JSONPARSER_H

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "../../../cocos2d/external/json/rapidjson.h"
#include "../../../cocos2d/external/json/document.h"
#include "../../../cocos2d/external/json/reader.h"
#include "../../../cocos2d/external/json/filestream.h"
#include "../../../cocos2d/external/json/stringbuffer.h"
#include "../../../cocos2d/external/json/writer.h"
#include "../../../cocos2d/external/json/prettywriter.h"

class LmJParserWifiDirect {

public:

	const char* cJson;
	rapidjson::Document document;

	std::vector<std::string> ParseJSONDeviceOperation(std::string sJSONDevice);

	void SetcJson(std::string sFilePath);

	void StringToCString(std::string inString);

	void SetDocument();

	void DocumentCheckup();

	std::vector<std::string> parseDevices();


};


#endif // JSONPARSER_H
