#ifndef _SPIRAL_INTERNET_BOOSTREACTOR_PORT_H__
#define _SPIRAL_INTERNET_BOOSTREACTOR_PORT_H__

#include <string>
#include <boost/asio.hpp>
#include "spiral/Exception.h"
#include "spiral/internet/Error.h"
#include "spiral/internet/protocol/ServerFactory.h"
#include "spiral/internet/boostreactor/BoostReactor.h"
#include "spiral/internet/boostreactor/Server.h"
#include "spiral/internet/address/IPv4Address.h"
#include "spiral/internet/interfaces/IListeningPort.h"
#include "spiral/sys/IntegerTypes.h"

namespace spiral {
namespace internet {
namespace boostreactor {

using namespace std;
using namespace interfaces;

namespace ba=boost::asio;
namespace bs=boost::system;

using ba::ip::tcp;

class Port : public IListeningPort
{
public:
	Port(int32_t port, protocol::ServerFactory *factory, int32_t backlog = 50, const string &interface = "", BoostReactor *reactor = NULL);

	virtual void connectionLost(const Exception &reason);
	virtual void loseConnection(const Exception &reason=error::ConnectionDone(""));

	// IListeningPort
	virtual void startListening();
    virtual void stopListening();

	virtual IAddress getHost();
protected:
    void handle_accept(Server *new_connection,
		const boost::system::error_code& error);

	void setConnected(bool v) { connected_=v; }
	void setDisconnected(bool v) { disconnected_=v; }
	void setDisconnecting(bool v) { disconnecting_=v; }
	bool getConnected() { return connected_; }
	bool getDisconnected() { return disconnected_; }
	bool getDisconnecting() { return disconnecting_; }
private:
	void doAccept();

	int32_t port_;
	protocol::ServerFactory *factory_;
	int32_t backlog_;
	string interface_;
	int32_t sessionno_;
	int32_t maxaccepts_;
	BoostReactor *reactor_;
	tcp::acceptor acceptor_;

    bool connected_;
    bool disconnected_;
    bool disconnecting_;

};

}}} // spiral::internet::boostreactor

#endif // _SPIRAL_INTERNET_BOOSTREACTOR_PORT_H__
