#ifndef _SPIRAL_INTERNET_INTERFACES_ICONNECTOR_H__
#define _SPIRAL_INTERNET_INTERFACES_ICONNECTOR_H__

#include "spiral/internet/interfaces/IAddress.h"
#include "spiral/internet/interfaces/ITransport.h"
#include "spiral/internet/interfaces/IReactorCore.h"

namespace spiral {
namespace internet {
namespace interfaces {

class IConnector 
{
public:
	virtual void stopConnecting() = 0;
	virtual void disconnect() = 0;
    virtual void connect() = 0;
    virtual IAddress getDestination() = 0;
	virtual ITransport &getTransport() = 0;
	virtual IReactorCore &reactor() = 0;

	virtual ~IConnector() {}
};

}}} // spiral::internet::interfaces

#endif // _SPIRAL_INTERNET_INTERFACES_ICONNECTOR_H__
