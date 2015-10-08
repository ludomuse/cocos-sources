/*
 * WifiObserver.h
 *
 *  Created on: 7 oct. 2015
 *      Author: Gregoire
 */

#ifndef WIFIOBSERVER_H_
#define WIFIOBSERVER_H_

#include <vector>
#include <string>
#include "../Includes/helpers.h"

class WifiObserver {

public:
	//attributs
	byte my_event;

	virtual void onGettingPeers(std::vector<std::string> peers) = 0;

	virtual void onReceiving(std::string s) {

	}

	virtual void onReceiving(int i) = 0;

	virtual void onReceiving(bool b) = 0;

	virtual void onReceiving(long l) = 0;

	virtual void onReceivingFile(std::string path) = 0;

	virtual void onReceiving(double d) = 0;

	virtual void onReceiving(float f) = 0;

	virtual void onReceiving(char c) = 0;

	virtual void onReceivingByte(byte b) {
		my_event = b;
	}

	virtual void onReceiving(bytes byteArray) = 0;

	virtual void discoverPeers() = 0;

	virtual ~WifiObserver();
};

#endif /* WIFIOBSERVER_H_ */
