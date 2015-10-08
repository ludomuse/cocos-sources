/*
 * WifiDirectFacade.h
 *
 *  Created on: 7 oct. 2015
 *      Author: Gregoire
 */

#ifndef WIFIDIRECTFACADE_H_
#define WIFIDIRECTFACADE_H_


#include <vector>
#include <list>
#include "../Includes/helpers.h"
#include "../Includes/WifiObserver.h"
#include <string>

class WifiDirectFacade {
public:

	WifiDirectFacade();

	void onGettingPeers(std::vector<std::string> peers);

	void onReceiving(std::string s);

	void onReceiving(int i);

	void onReceiving(bool b);

	void onReceiving(long l);

	void onReceivingFile(std::string path);

	void onReceiving(double d);

	void onReceiving(float f);

	void onReceiving(char c);

	void onReceivingByte(byte b);

	void onReceiving(bytes byteArray);

	void discoverPeers();

	void connectTo(std::string deviceName);

	void send(std::string s);

	void send(int i);

	void send(bool b);

	void send(long l);

	void sendFile(std::string filePath);

	void send(double d);

	void send(float f);

	void send(char c);

	void sendByte(byte b);

	void sendBytes(bytes bytes);

	int addObserver(WifiObserver* wo);

	void removeObserver(int index);

private:
	std::list<WifiObserver*> _observers;
};

#endif /* WIFIDIRECTFACADE_H_ */
