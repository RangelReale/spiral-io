#include "spiral/internet/boostreactor/Connector.h"
#include "spiral/internet/boostreactor/Client.h"
#include "spiral/internet/address/IPv4Address.h"

namespace spiral {
namespace internet {
namespace boostreactor {

Connector::Connector(const string &host, int32_t port, protocol::ClientFactory *factory, 
	int32_t timeout, /*bindAddress,*/ BoostReactor *reactor) :
		base::BaseConnector(factory, timeout, reactor), host_(host), port_(port)
{

}

ITransport *Connector::makeTransport()
{
	return new Client(host_, port_, this, dynamic_cast<BoostReactor *>(&reactor()));
}

address::IAddress Connector::getDestination()
{
	return address::IPv4Address(address::IPv4Address::TCP, host_, port_);
}

}}} // spiral::internet::boostreactor
