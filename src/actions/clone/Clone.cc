/**
 * @file	Clone.cc
 * @author	Francesco Racciatti <racciatti.francesco@gmail.com>
 * @version	1.0
 * @date	2015 jun 22
 */


#include "Clone.h"
#include "seapputils.h"
#include "omnetpp.h"


Clone::Clone (const string clonePacketName, const string originalPacketName) : ActionBase (action_t::CLONE) {

	setPacketName(originalPacketName);
	this->clonePacketName = clonePacketName;
	// the packet filter matching is a sufficient condition to perform the Clone action, further infos are useless
	involvedLayer = NONE_LAYER;
	
}


Clone::~Clone() {

}


string Clone::getClonePacketName() const {

	return clonePacketName;

}


void Clone::execute(cMessage** clonePacket, const cMessage* originalPacket) const {

	*clonePacket = (cMessage*) hardCopy((cPacket*) originalPacket);
	
}
