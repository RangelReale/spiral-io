#include "spiral/internet/boostreactor/BoostReactor.h"
#include "spiral/internet/boostreactor/Connector.h"
#include "spiral/internet/boostreactor/Port.h"
#include "spiral/internet/boostreactor/DelayedCall.h"
#include <ctime>

namespace spiral {
namespace internet {
namespace boostreactor {

using namespace interfaces;

BoostReactor::BoostReactor() : ReactorBase(), io_service_(), io_service_work_(io_service_),
	connectors_(), listeningports_(), delayedcalls_()
{

}

void BoostReactor::do_run()
{
	io_service_.run();
	ReactorBase::do_run();
}

void BoostReactor::do_stop()
{
	ReactorBase::do_stop();
	io_service_.stop();
}


// IReactorTCP
IListeningPort *BoostReactor::listenTCP(int32_t port, protocol::ServerFactory *factory, int32_t backlog, const std::string &interface) 
{ 
	IListeningPort *ret=new Port(port, factory, backlog, interface, this); 
	listeningports_.push_back(boost::shared_ptr<IListeningPort>(ret));
	ret->startListening();
	return ret;
}

IConnector *BoostReactor::connectTCP(const std::string &host, int32_t port, protocol::ClientFactory *factory, int32_t timeout)  //, bindAddress=None)
{ 
	IConnector *ret=new Connector(host, port, factory, timeout, this);
	connectors_.push_back(boost::shared_ptr<IConnector>(ret));
	ret->connect();
	return ret;
}

// IReactorTime
uint32_t BoostReactor::seconds()
{
	return std::time(0);
	//return ba::deadline_timer::traits_type::now();
}

IDelayedCall *BoostReactor::callLater(float delay, base::Callable callable)
{
	assert(delay >= 0);

	IDelayedCall *call = new DelayedCall(delay, callable, this);
	delayedcalls_.push_back(boost::shared_ptr<IDelayedCall>(call));
	
	return call;
}

void BoostReactor::cancelCallLater(IDelayedCall *callid)
{
	callid->cancel();
}


}}} // spiral::internet::boostreactor
