#ifndef _SPIRAL_INTERNET_BASE_BASECONNECTOR_H__
#define _SPIRAL_INTERNET_BASE_BASECONNECTOR_H__

#include "spiral/Exception.h"
#include "spiral/internet/interfaces/IConnector.h"
#include "spiral/internet/protocol/ClientFactory.h"
#include "spiral/internet/interfaces/IReactorCore.h"
#include "spiral/sys/IntegerTypes.h"
#include <boost/shared_ptr.hpp>

namespace spiral {
namespace internet {
namespace base {

using namespace interfaces;

class BaseConnector : public IConnector
{
public:
	enum state_t
	{
		CONNECTING,
		CONNECTED,
		DISCONNECTED
	};

	BaseConnector(protocol::ClientFactory *factory, int32_t timeout, IReactorCore *reactor);

	virtual IProtocol *buildProtocol(IAddress addr);

	virtual void connectionFailed(const Exception &reason);
	virtual void connectionLost(const Exception &reason);

	// IConnector
	virtual void stopConnecting();
	virtual void disconnect();
    virtual void connect();
	virtual ITransport &getTransport() { return *transport_; }
	virtual IReactorCore &reactor() { return *reactor_; }
protected:
	virtual ITransport *makeTransport() = 0;

	
private:
	state_t state_;
	protocol::ClientFactory *factory_;
	int32_t timeout_;
	IReactorCore *reactor_;
	bool factorystarted_;
	std::auto_ptr<ITransport> transport_;
};

}}} // spiral::internet::base

#endif // _SPIRAL_INTERNET_BASE_BASECONNECTOR_H__
