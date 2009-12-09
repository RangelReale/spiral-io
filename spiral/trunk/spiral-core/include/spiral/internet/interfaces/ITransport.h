#ifndef _SPIRAL_INTERNET_INTERFACES_ITRANSPORT_H__
#define _SPIRAL_INTERNET_INTERFACES_ITRANSPORT_H__

#include "spiral/Exception.h"
#include "spiral/sys/IntegerTypes.h"
#include "spiral/internet/interfaces/IAddress.h"
#include "spiral/internet/interfaces/IReactor.h"

namespace spiral {
namespace internet {
namespace interfaces {

class ITransport
{
public:
	virtual void write(const char *data, size_t size) = 0;
	//virtual void writeSequence() = 0;
	virtual void loseConnection() = 0;
	virtual IAddress getPeer() = 0;
	virtual IAddress getHost() = 0;

	virtual bool disconnecting() = 0;

	virtual void failIfNotConnected(const Exception &err) {}

	virtual IReactor &reactor() = 0;

	virtual ~ITransport() {}
};

}}} // spiral::internet::interfaces

#endif // _SPIRAL_INTERNET_INTERFACES_ITRANSPORT_H__
