#ifndef _SPIRAL_INTERNET_INTERFACES_IPROTOCOLFACTORY_H__
#define _SPIRAL_INTERNET_INTERFACES_IPROTOCOLFACTORY_H__

#include "spiral/internet/interfaces/IProtocol.h"
#include "spiral/internet/interfaces/IAddress.h"

namespace spiral {
namespace internet {
namespace interfaces {

class IProtocolFactory
{
public:
	virtual IProtocol *buildProtocol(IAddress addr) = 0;

	virtual void doStart() = 0;
	virtual void doStop() = 0;

	virtual ~IProtocolFactory() {}
};

}}} // spiral::internet::interfaces

#endif // _SPIRAL_INTERNET_INTERFACES_IPROTOCOLFACTORY_H__
