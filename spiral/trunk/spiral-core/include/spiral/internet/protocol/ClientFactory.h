#ifndef _SPIRAL_INTERNET_PROTOCOL_CLIENTFACTORY_H__
#define _SPIRAL_INTERNET_PROTOCOL_CLIENTFACTORY_H__

#include "spiral/Exception.h"
#include "spiral/internet/interfaces/IConnector.h"
#include "spiral/internet/protocol/ProtocolFactory.h"

namespace spiral {
namespace internet {
namespace protocol {

using namespace interfaces;

class ClientFactory : public ProtocolFactory
{
public:
	virtual void startedConnecting(IConnector &connector) {}
	virtual void clientConnectionFailed(IConnector *connector, const Exception &reason) {}
	virtual void clientConnectionLost(IConnector *connector, const Exception &reason) {}
};

class ClientFactorySimple : public ClientFactory
{
public:
	ClientFactorySimple(IProtocol &protocol) : ClientFactory(), protocol_(protocol) { }

	virtual IProtocol *buildProtocol(IAddress addr) { return &protocol_; }
private:
	IProtocol &protocol_;
};

}}} // spiral::internet::protocol

#endif // _SPIRAL_INTERNET_PROTOCOL_CLIENTFACTORY_H__

