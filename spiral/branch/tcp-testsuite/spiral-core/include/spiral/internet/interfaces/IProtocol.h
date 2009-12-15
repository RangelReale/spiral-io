#ifndef _SPIRAL_INTERNET_INTERFACES_IPROTOCOL_H__
#define _SPIRAL_INTERNET_INTERFACES_IPROTOCOL_H__

#include "spiral/Exception.h"
#include "spiral/sys/IntegerTypes.h"
#include "spiral/internet/interfaces/ITransport.h"
#include "spiral/internet/interfaces/IReactor.h"

namespace spiral {
namespace internet {
namespace interfaces {

class IProtocol 
{
public:
	virtual void dataReceived(const char *data, size_t size) = 0;
	virtual void connectionLost(const Exception &reason) = 0;
	virtual void makeConnection(ITransport *transport) = 0;
	virtual void connectionMade() = 0;

	virtual ITransport &transport() = 0;
	virtual IReactor &reactor() = 0;

	virtual ~IProtocol() {}
};

}}} // spiral::internet::interfaces

#endif // _SPIRAL_INTERNET_INTERFACES_IPROTOCOL_H__
