#include "spiral/internet/boostreactor/Server.h"

namespace spiral {
namespace internet {
namespace boostreactor {

Server::Server(BoostReactor *reactor) :
		Connection(NULL, reactor), clientAddress_(), serverAddress_(), sessionno_(-1)
{

}

void Server::start(IProtocol *protocol, const address::IPv4Address &clientAddr, const address::IPv4Address &serverAddr, 
		int32_t sessionno)
{
	setProtocol(protocol);
	clientAddress_=clientAddr;
	serverAddress_=serverAddr;
	sessionno_=sessionno;
	
	setConnected(true);
	startReading();
}

// ITransport
IAddress Server::getPeer()
{
	return clientAddress_;
}

IAddress Server::getHost()
{
	return serverAddress_;
}

}}} // spiral::internet::boostreactor
