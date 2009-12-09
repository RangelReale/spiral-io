#ifndef _SPIRAL_PROTOCOL_BASEPROTOCOL_H__
#define _SPIRAL_PROTOCOL_BASEPROTOCOL_H__

#include "spiral/internet/interfaces/ITransport.h"

namespace spiral {
namespace internet {
namespace protocol {

using namespace interfaces;

class BaseProtocol
{
public:
	BaseProtocol() : connected_(false), transport_() {}

	virtual void makeConnection(interfaces::ITransport *transport) { connected_=true; transport_=transport; connectionMade(); }
	virtual void connectionMade() {}

	virtual ITransport &transport() { return *transport_; }
private:
	bool connected_;
	ITransport *transport_;
};

}}} // spiral::internet::protocol

#endif // _SPIRAL_PROTOCOL_BASEPROTOCOL_H__
