#include <boost/bind.hpp>
#include "spiral/internet/boostreactor/Port.h"

namespace spiral {
namespace internet {
namespace boostreactor {

Port::Port(int32_t port, protocol::ServerFactory *factory, int32_t backlog, const string &interface, BoostReactor *reactor) :
	port_(port), factory_(factory), backlog_(backlog), interface_(interface), reactor_(reactor), sessionno_(0), maxaccepts_(100),
	acceptor_(reactor->getIoService(), tcp::endpoint(tcp::v4(), port)),
	connected_(false), disconnected_(false), disconnecting_(false)
	
{

}

void Port::connectionLost(const Exception &reason)
{
	setDisconnected(true);
	setConnected(false);
	acceptor_.close();
	factory_->doStop();
}

void Port::loseConnection(const Exception &reason)
{
	setDisconnecting(true);
	if (getConnected())
		connectionLost(reason);
}

void Port::startListening()
{
	factory_->doStart();
	setConnected(true);
	setDisconnected(false);
	doAccept();
}

void Port::stopListening()
{
	loseConnection();
}

IAddress Port::getHost()
{
	return address::IPv4Address();
}

void Port::doAccept()
{
    // create new connection
	Server *new_connection = new Server(reactor_);
    // start acceptor in async mode
    acceptor_.async_accept(new_connection->getSocket(),
                           boost::bind(&Port::handle_accept, this, new_connection,
                                       ba::placeholders::error));
}

void Port::handle_accept(Server *new_connection,
	const bs::error_code& error)  
{
	if (getDisconnecting() || getDisconnected())
		return;

    if (!error) {
        IProtocol *protocol=factory_->buildProtocol(address::IPv4Address());
		new_connection->start(protocol, address::IPv4Address(), 
			address::IPv4Address(), ++sessionno_);
		protocol->makeConnection(new_connection);
        doAccept();
    } else
		delete new_connection;
}


}}} // spiral::internet::boostreactor
