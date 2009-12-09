#ifndef _SPIRAL_INTERNET_INTERFACES_ITCPTRANSPORT_H__
#define _SPIRAL_INTERNET_INTERFACES_ITCPTRANSPORT_H__

#include "spiral/sys/IntegerTypes.h"
#include "spiral/internet/interfaces/ITransport.h"
#include "spiral/internet/address/IPv4Address.h"

namespace spiral {
namespace internet {
namespace interfaces {

class ITCPTransport : public ITransport
{
public:
	virtual void loseWriteConnection() = 0;
	virtual bool getTcpNoDelay() = 0;
    virtual void setTcpNoDelay(bool enabled) = 0;
	virtual bool getTcpKeepAlive() = 0;
    virtual void setTcpKeepAlive(bool enabled) = 0;
	//virtual address::IPv4Address getPeer() = 0;
	//virtual address::IPv4Address getHost() = 0;

	virtual ~ITCPTransport() {}
};

}}} // spiral::internet::interfaces

#endif // _SPIRAL_INTERNET_INTERFACES_ITCPTRANSPORT_H__
