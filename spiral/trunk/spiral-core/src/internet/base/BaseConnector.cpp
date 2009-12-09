#include "spiral/internet/base/BaseConnector.h"
#include "spiral/internet/Error.h"

namespace spiral {
namespace internet {
namespace base {

//using namespace interfaces;

BaseConnector::BaseConnector(protocol::ClientFactory *factory, int32_t timeout, IReactorCore *reactor) :
	state_(DISCONNECTED), factory_(factory), 
	timeout_(timeout), reactor_(reactor), factorystarted_(false), transport_()
{

}

IProtocol *BaseConnector::buildProtocol(IAddress addr)
{
	state_=CONNECTED;
	//canceltimeout();
	IProtocol *ret=factory_->buildProtocol(addr);
	return ret;
}

void BaseConnector::connectionFailed(const Exception &reason)
{
	transport_.reset();
	state_=DISCONNECTED;
	factory_->clientConnectionFailed(this, reason);
	if (state_==DISCONNECTED)
	{
		factory_->doStop();
		factorystarted_=false;
	}
}

void BaseConnector::connectionLost(const Exception &reason)
{
	state_=DISCONNECTED;
	factory_->clientConnectionLost(this, reason);
	if (state_==DISCONNECTED)
	{
		factory_->doStop();
		factorystarted_=false;
	}
}

void BaseConnector::stopConnecting()
{
    if (state_!=CONNECTING)
		throw new error::NotConnectingError("we're not trying to connect");
	state_=DISCONNECTED;
	
	transport_->failIfNotConnected(error::UserError(""));

	transport_.release();
}

void BaseConnector::disconnect() 
{ 
	if (state_==CONNECTING) 
		stopConnecting(); 
	else if (state_==CONNECTED) 
		getTransport().loseConnection(); 
}

void BaseConnector::connect()
{
	if (state_!=DISCONNECTED)
		throw new RuntimeError("can't connect in this state");
	state_=CONNECTING;
	if (!factorystarted_)
	{
		factory_->doStart();
		factorystarted_=true;
	}
	transport_.reset(makeTransport());
	// TODO: timeout
	factory_->startedConnecting(*this);
}


}}} // spiral::internet::base
