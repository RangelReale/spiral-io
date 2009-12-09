#ifndef _SPIRAL_INTERNET_BOOSTREACTOR_SERVER_H__
#define _SPIRAL_INTERNET_BOOSTREACTOR_SERVER_H__

#include <string>
#include <boost/asio.hpp>
#include "spiral/Exception.h"
#include "spiral/internet/boostreactor/Connection.h"
#include "spiral/internet/boostreactor/BoostReactor.h"
#include "spiral/internet/address/IPv4Address.h"
#include "spiral/internet/interfaces/IProtocol.h"
#include "spiral/sys/IntegerTypes.h"

namespace spiral {
namespace internet {
namespace boostreactor {

using namespace std;
using namespace interfaces;

namespace ba=boost::asio;
namespace bs=boost::system;

using ba::ip::tcp;

class Server : public Connection
{
public:
	Server(BoostReactor *reactor);

	void start(IProtocol *protocol, const address::IPv4Address &clientAddr, const address::IPv4Address &serverAddr, 
		int32_t sessionno);

	// ITransport
	virtual IAddress getPeer();
	virtual IAddress getHost();
private:
	address::IPv4Address clientAddress_, serverAddress_;
	BoostReactor *reactor_;
	int32_t sessionno_;
};

}}} // spiral::internet::boostreactor

#endif // _SPIRAL_INTERNET_BOOSTREACTOR_CLIENT_H__
