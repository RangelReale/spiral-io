#ifndef _SPIRAL_INTERNET_PROTOCOL_PROTOCOL_H__
#define _SPIRAL_INTERNET_PROTOCOL_PROTOCOL_H__

#include "spiral/internet/protocol/BaseProtocol.h"
#include "spiral/internet/interfaces/IProtocol.h"

namespace spiral {
namespace internet {
namespace protocol {

using namespace interfaces;

class Protocol : public IProtocol, public BaseProtocol
{
public:
	virtual void makeConnection(ITransport *transport) { BaseProtocol::makeConnection(transport); }
	virtual void connectionMade() { BaseProtocol::connectionMade(); }
	virtual void dataReceived(const char *data, size_t size) {}
	virtual void connectionLost(const Exception &reason) {}

	virtual ITransport &transport() { return BaseProtocol::transport(); }
	virtual IReactor &reactor() { return transport().reactor(); }
};

}}} // spiral::internet::protocol

#endif // _SPIRAL_INTERNET_PROTOCOL_PROTOCOL_H__
