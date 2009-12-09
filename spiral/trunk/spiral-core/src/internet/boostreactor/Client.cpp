#include <boost/bind.hpp>
#include <boost/lexical_cast.hpp>
#include "spiral/internet/boostreactor/Client.h"
#include "spiral/internet/Error.h"

namespace spiral {
namespace internet {
namespace boostreactor {

Client::Client(const string &host, int32_t port, /*bindAddress,*/ Connector *connector, BoostReactor *reactor) :
	Connection(NULL, reactor), connector_(connector), address_(address::IPv4Address::TCP, host, port), reactor_(reactor),
	resolver_(reactor->getIoService())
{
	connect();
}

void Client::connect()
{
	tcp::resolver::query query(address_.getHost(), boost::lexical_cast<string>(address_.getPort()));
    resolver_.async_resolve(query,
        boost::bind(&Client::handle_resolve, this,
          ba::placeholders::error,
          ba::placeholders::iterator));
}

void Client::failIfNotConnected(const Exception &err)
{
	if (getConnected() || getDisconnected())
		//or not hasattr(self, "connector")):
		return;

	closeSocket();

	connector_->connectionFailed(err);

	//delete connector_;
}

void Client::stopConnecting()
{
	failIfNotConnected(error::UserError(""));
}

IAddress Client::getPeer()
{
	return address::IPv4Address();
}

IAddress Client::getHost()
{
	return address::IPv4Address();
}

void Client::connectionLost(const Exception &reason)
{
    if (!getConnected())
		failIfNotConnected(error::ConnectError(reason.getMessage()));
    else
	{
		Connection::connectionLost(reason);
        connector_->connectionLost(reason);
	}
}

void Client::handle_resolve(const bs::error_code& err,
	tcp::resolver::iterator endpoint_iterator)
{
	if (!err)
	{
		// Attempt a connection to the first endpoint in the list. Each endpoint
		// will be tried until we successfully establish a connection.
		tcp::endpoint endpoint = *endpoint_iterator;
		getSocket().async_connect(endpoint,
			boost::bind(&Client::handle_connect, this,
			ba::placeholders::error, ++endpoint_iterator));
	}
	else
	{
		failIfNotConnected(error::UnknownHostError(err.message()));
		//handle_error(err);
	}
}

void Client::handle_connect(const bs::error_code& err,
	tcp::resolver::iterator endpoint_iterator)
{
	if (!err)
	{
		setProtocol(connector_->buildProtocol(address::IPv4Address()));
		setConnected(true);
		getProtocol()->makeConnection(this);
		startReading();
	}
	else if (endpoint_iterator != tcp::resolver::iterator())
	{
		// The connection failed. Try the next endpoint in the list.
		getSocket().close();
		tcp::endpoint endpoint = *endpoint_iterator;
		getSocket().async_connect(endpoint,
			boost::bind(&Client::handle_connect, this,
			ba::placeholders::error, ++endpoint_iterator));
	}
	else
	{
		failIfNotConnected(error::ConnectError(err.message()));
		//handle_error(err);
	}
}

}}} // spiral::internet::boostreactor
