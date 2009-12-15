#ifndef _SPIRAL_INTERNET_PROTOCOL_SERVERFACTORY_H__
#define _SPIRAL_INTERNET_PROTOCOL_SERVERFACTORY_H__

#include "spiral/internet/interfaces/IConnector.h"
#include "spiral/internet/protocol/ProtocolFactory.h"

namespace spiral {
namespace internet {
namespace protocol {

using namespace interfaces;

class ServerFactory : public ProtocolFactory
{
};

class ServerFactorySimple : public ServerFactory
{
public:
	ServerFactorySimple(IProtocol &protocol) : ServerFactory(), protocol_(protocol) { }

	virtual IProtocol *buildProtocol(IAddress addr) { return &protocol_; }
private:
	IProtocol &protocol_;
};


}}} // spiral::internet::protocol

#endif // _SPIRAL_INTERNET_PROTOCOL_SERVERFACTORY_H__

