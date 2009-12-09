#ifndef _SPIRAL_INTERNET_PROTOCOL_PROTOCOLFACTORY_H__
#define _SPIRAL_INTERNET_PROTOCOL_PROTOCOLFACTORY_H__

#include <iostream>
#include "spiral/internet/interfaces/IProtocolFactory.h"

namespace spiral {
namespace internet {
namespace protocol {

using namespace interfaces;

class ProtocolFactory : public IProtocolFactory
{
public:
	ProtocolFactory() : numports_(0) {}

	virtual void startFactory() {}
	virtual void stopFactory() {}

	// IProtocolFactory
	virtual IProtocol *buildProtocol(IAddress addr) { return NULL; }

	virtual void doStart() { if (numports_==0) startFactory(); numports_++; }
	virtual void doStop() { numports_--; if (numports_==0) stopFactory(); }
private:
	int32_t numports_;
};

class ProtocolFactorySimple : public ProtocolFactory
{
public:
	ProtocolFactorySimple(IProtocol &protocol) : ProtocolFactory(), protocol_(protocol) { }

	virtual IProtocol *buildProtocol(IAddress addr) { return &protocol_; }
private:
	IProtocol &protocol_;
};

}}} // spiral::internet::protocol

#endif // _SPIRAL_INTERNET_PROTOCOL_PROTOCOLFACTORY_H__
