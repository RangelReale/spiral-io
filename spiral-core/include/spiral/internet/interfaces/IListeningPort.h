#ifndef _SPIRAL_INTERNET_INTERFACES_ILISTENINGPORT_H__
#define _SPIRAL_INTERNET_INTERFACES_ILISTENINGPORT_H__

#include "spiral/internet/interfaces/IAddress.h"

namespace spiral {
namespace internet {
namespace interfaces {

class IListeningPort 
{
public:
	virtual void startListening() = 0;
    virtual void stopListening() = 0;
    virtual IAddress getHost() = 0;

	virtual ~IListeningPort() {}
};

}}} // spiral::internet::interfaces

#endif // _SPIRAL_INTERNET_INTERFACES_ILISTENINGPORT_H__
