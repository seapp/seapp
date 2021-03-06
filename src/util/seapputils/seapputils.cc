/**
 * @file	seapputils.cc
 * @author	Francesco Racciatti <racciatti.francesco@gmail.com>
 */
 

#include "seapputils.h"
#include <sstream>
#include <map>


void tokenize (vector<string>& tokens, const string str, const char delim) {
	string word;
	stringstream stream(str);
	while (getline(stream, word, delim)) {
		tokens.push_back(word);
	}
}


vector<string> tokenize (const string stringToTokenize, const char delimiter) {
	
	// vector of tokenized strings
	vector<string> tokens;
	
	string word;
	stringstream stream(stringToTokenize);
	
	while (getline(stream, word, delimiter)) {
		tokens.push_back(word);
	}
	
	return tokens;
}


cPacket* getDeepestEncapsulatedPacket (cPacket* packet) {

	cPacket* encapsulatedPacket = packet;
	while (encapsulatedPacket != nullptr) {
		encapsulatedPacket = encapsulatedPacket->getEncapsulatedPacket();
	}
	return encapsulatedPacket;
	
}


int getPacketLayer(cPacket* packet){

	string packetClassName = packet->getClassName();

	// TODO add all the other packets


	if(packetClassName == "cPacket"){
		return 5;	
	}
	
	if (packetClassName == "TrafficLightPacket"){
		return 5;
	}
	
	if(packetClassName == "TrafficLightStatus"){
		return 5;
	}
	
	if(packetClassName == "TrafficLightCmd"){
		return 5;
	}

	if(packetClassName == "UDPPacket"){
		return 4;
	}
	
	if(packetClassName == "IPv4Datagram"){
		return 3;
	}
	
	if(packetClassName == "PPPFrame"){
		return 2;
	}
	
	opp_error(("getPacketLayer can't recognize the layer or the packet " + packetClassName).c_str());
	
}


int layertoi(const string layer) {

	if (layer == "APP") {
		return 5;
	}
	
	if (layer == "TRA") {
		return 4;
	}
	
	if(layer == "NET") {
		return 3;
	}
	
	if(layer == "MAC") {
		return 2;
	}
	
	opp_error("layertoi function can't recognize the layer");

}


void setParameterRecursively (cMessage* msg, const string parameterName, const bool parameterValue) {

	bool hasPar = false;
	cMessage* encapsulatedMsg = msg;
	
	while (encapsulatedMsg != nullptr) {
	
		hasPar = encapsulatedMsg->hasPar(parameterName.c_str());
		if (hasPar) {
			encapsulatedMsg->par(parameterName.c_str()).setBoolValue(parameterValue);
			encapsulatedMsg = (cMessage*) ((cPacket*) encapsulatedMsg)->getEncapsulatedPacket();		
		}
		else {
			opp_error(("setParameterRecursively can't find the parameter " + parameterName).c_str());	
		}
		
	}
	
	return;

}


cPacket* hardCopy (cPacket* packetToCopy) {

	cPacket* layer2Packet = nullptr;
	cPacket* layer3Packet = nullptr;
	cPacket* layer4Packet = nullptr;
	cPacket* layer5Packet = nullptr;

	if (packetToCopy == nullptr) {
		return nullptr;
	}

	// only the outer packet can have an associated ControlInfo object
	cObject* controlInfo = (packetToCopy->getControlInfo())->dup();
	int packetLayer = getPacketLayer(packetToCopy);

	switch (packetLayer) {
	
		case 2: {
			layer2Packet = packetToCopy->dup();	
			layer2Packet->setControlInfo(controlInfo);
			layer3Packet = layer2Packet->decapsulate();
			if (layer3Packet == nullptr){
				return layer2Packet;
			}
		}
	
		case 3: {
			if (layer3Packet == nullptr) {
				// is outer packet, append control info
				layer3Packet = packetToCopy->dup();
				layer3Packet->setControlInfo(controlInfo);
			}
			layer4Packet = layer3Packet->decapsulate();	
			
			if (layer4Packet == nullptr) {
				if (layer2Packet != nullptr) {
					layer2Packet->encapsulate(layer3Packet);
					return layer2Packet;
				}
				else{
					return layer3Packet;
				}
			}
		}
	
		case 4: {
			if (layer4Packet == nullptr) {
				// is outer packet, append control info			
				layer4Packet = packetToCopy->dup();
				layer4Packet->setControlInfo(controlInfo);
			}
			layer5Packet = layer4Packet->decapsulate();
			if (layer5Packet == nullptr) {	
				if (layer3Packet != nullptr) {
					layer3Packet->encapsulate(layer4Packet);
					if (layer2Packet != nullptr) {
						layer2Packet->encapsulate(layer3Packet);
						return layer2Packet;
					}
					else{
						return layer3Packet;
					}
				}
				else{
					return layer4Packet;
				}
			}
		}

		case 5: {
			if (layer5Packet == nullptr) {
				// is outer packet, append control info
				layer5Packet = packetToCopy->dup();
				layer5Packet->setControlInfo(controlInfo);
			}
			if (layer4Packet != nullptr) {
				layer4Packet->encapsulate(layer5Packet);
				if (layer3Packet != nullptr) {
					layer3Packet->encapsulate(layer4Packet);
					if (layer2Packet != nullptr) {
						layer2Packet->encapsulate(layer3Packet);
						return layer2Packet;
					}
					else{
						return layer3Packet;
					}
				}
				else{
					return layer4Packet;
				}
			}
			else{
				return layer5Packet;
			}

		}	
		
	}
	
}
