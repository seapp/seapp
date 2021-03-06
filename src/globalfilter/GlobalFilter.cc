/**
 * @file	GlobalFilter.cc
 * @author	Francesco Racciatti <racciatti.francesco@gmail.com>
 * @version	0.0.1
 * @date	2015 apr 14
 */


#include "GlobalFilter.h"
#include <stdexcept>
#include "UnconditionalAttack.h"
#include "PutMessages.h"
#include "Parser.h"
#include "seapputils.h"
#include "omnetpp.h"
#include <string>




// XXX includes for fork()
//#include <stdarg.h> 
//#include <stdlib.h>    
//#include <stdio.h>     
//#include <unistd.h>

// XXX includes for interprocess communication
//#include <boost/interprocess/ipc/message_queue.hpp>
//#include <iostream>


Define_Module(GlobalFilter);


void GlobalFilter::initializeAttacks () {

	Parser* parser = nullptr;	
	try {
		parser = new Parser(static_cast<cModule*>(this));
	}
	catch (const invalid_argument& e) {
		EV << e.what() << endl;
		delete parser;
		return;
	}
	
	
	
	parser->parseConfigurationFile(attack_t::UNCONDITIONAL, unconditionalAttacks);

	// schedule selfMessages in order to trigger the unconditional attacks
	string index;
	string selfMessageName;
	for (size_t i = 0; i < unconditionalAttacks.size(); i++) {
		index.assign(to_string(i));
		selfMessageName.assign("Fire UnconditionalAttack[");
		selfMessageName.append(index);
		selfMessageName.append("]");
		cMessage* selfMessage = new cMessage(selfMessageName.c_str(), (short) attack_t::UNCONDITIONAL);
		scheduleAt(unconditionalAttacks[i]->getOccurrenceTime(), selfMessage);
	}

	// delete parser
	delete parser;

}


void GlobalFilter::initialize () {

	initializeAttacks();
	
	// XXX try fork()
	/*
	pid_t pid = fork();	

	if(pid==0){
		system("gnome-terminal -x sh -c 'cd ~/x-frameworks/asfpp/Simulations/Ciminiera && ../../bin/Castalia -c General'");//; exec bash'");
		//execve("./runcastalia", NULL, NULL);
		_exit(EXIT_SUCCESS);
	}
	else{

	}
	*/


}



void GlobalFilter::handleMessage (cMessage* msg) {

	bool isSelfMessage = msg->isSelfMessage();

	if (isSelfMessage) {


		string msgName = msg->getName();
		
		// handle unconditional attack
		if (msgName.find("Unconditional") != std::string::npos) {
			
			UnconditionalAttack* unconditionalAttack = nullptr;
			vector<cMessage*> generatedMessages;
			int index;	
			double frequency;
			double scheduleTime;
			vector<string> tokens;
			
			// get unconditional attack index			
			tokenize(tokens, msgName, '[');
			tokens[1].pop_back();
			index = atoi(tokens[1].c_str());
		
			// execute the unconditional attack
			unconditionalAttack = (UnconditionalAttack*) (unconditionalAttacks[index]->getAttack());
			unconditionalAttack->execute(generatedMessages);
		
			// deliver all the created put messages
			for (size_t i = 0; i < generatedMessages.size(); i++){
				handlePutMessage(generatedMessages[i]);
			}	
		
			// re-schedule the attack if not-zero frequency
			frequency = unconditionalAttack->getFrequency();
			if (frequency == 0){
				delete msg;
				return;			
			}
			else {
				scheduleTime = frequency + (simTime().dbl());
				cMessage* selfMessage = new cMessage( msgName.c_str(), (short) attack_t::UNCONDITIONAL);
				scheduleAt( scheduleTime, selfMessage );
			}
			
		}
		
	}
	else {
		// handle messages from another node in the network, i.e. a PutMsg	
		if (isPutMsg(msg)) {
			handlePutMessage(msg);
		}
		else {
			EV << "GlobalFilter::handleMessage can handle only PutMsg or selfMsg messages" << endl;
		}
		
	}
	
	delete msg;

}


void GlobalFilter::handlePutMessage (const cMessage* msg) {



	cMessage* encapsulatedPacket = nullptr;
	PutMsg* putMsg = nullptr;
	vector<int> recipientNodes;
	direction_t direction;
	double forwardingDelay;
	bool isStatUpdated;
	
	putMsg = (PutMsg*)(msg);
	recipientNodes = putMsg->getRecipientNodes();
	direction = putMsg->getDirection();
	
	isStatUpdated = putMsg->getStatUpdated();
	forwardingDelay = putMsg->getForwardingDelay();
	
	encapsulatedPacket = putMsg->getMsg();
	
	int gateSize = this->gateSize("nodes$o");
	cGate* gate = nullptr;
	cGate* nextGate = nullptr;
	cModule* nextGateOwner = nullptr;
	for (size_t i = 0; i < recipientNodes.size(); i++) {
		
		// scan the nodes vector gate to find the current recipient node
		for (int j = 0; j < gateSize; j++) {
			gate = this->gate("nodes$o", j);
			nextGate = gate->getNextGate();
			nextGateOwner = check_and_cast<cModule*>(nextGate->getOwner());
			
			if (recipientNodes[i] == nextGateOwner->getId()) {
				PutReq* putReq = new PutReq(encapsulatedPacket, direction, isStatUpdated);
				sendDelayed(putReq, forwardingDelay, "nodes$o", j);
				break;
			}
		
		}

	}
	
}


void GlobalFilter::finishSpecific () {

}


GlobalFilter::GlobalFilter () {

	

}


GlobalFilter::~GlobalFilter () {

}
