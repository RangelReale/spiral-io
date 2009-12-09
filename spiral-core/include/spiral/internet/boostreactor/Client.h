#ifndef _SPIRAL_INTERNET_BOOSTREACTOR_CLIENT_H__
#define _SPIRAL_INTERNET_BOOSTREACTOR_CLIENT_H__

#include <string>
#include <boost/asio.hpp>
#include "spiral/Exception.h"
#include "spiral/internet/boostreactor/Connection.h"
#include "spiral/internet/boostreactor/Connector.h"
#include "spiral/internet/boostreactor/BoostReactor.h"
#include "spiral/internet/address/IPv4Address.h"

namespace spiral {
namespace internet {
namespace boostreactor {

using namespace std;

namespace ba=boost::asio;
namespace bs=boost::system;

using ba::ip::tcp;

class Client : public Connection
{
public:
	Client(const string &host, int32_t port, /*bindAddress,*/ Connector *connector, BoostReactor *reactor);

	void stopConnecting();
	virtual void connectionLost(const Exception &reason);

	// ITransport
	virtual IAddress getPeer();
	virtual IAddress getHost();
	virtual void failIfNotConnected(const Exception &err);
protected:
	void handle_resolve(const bs::error_code& err,
		tcp::resolver::iterator endpoint_iterator);
	void handle_connect(const bs::error_code& err,
		tcp::resolver::iterator endpoint_iterator);

	void connect();
private:
	Connector *connector_;
	address::IPv4Address address_;
	BoostReactor *reactor_;
	tcp::resolver resolver_;
};

}}} // spiral::internet::boostreactor

#endif // _SPIRAL_INTERNET_BOOSTREACTOR_CLIENT_H__
