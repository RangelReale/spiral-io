#ifndef _SPIRAL_INTERFACES_IREACTORTCP_H__
#define _SPIRAL_INTERFACES_IREACTORTCP_H__

#include <string>
#include "spiral/sys/IntegerTypes.h"
#include "spiral/internet/protocol/ClientFactory.h"
#include "spiral/internet/protocol/ServerFactory.h"
#include "spiral/internet/interfaces/IConnector.h"
#include "spiral/internet/interfaces/IListeningPort.h"

namespace spiral {
namespace internet {
namespace interfaces {

class IReactorTCP
{
public:
	virtual IListeningPort *listenTCP(int32_t port, protocol::ServerFactory *factory, int32_t backlog=50, const std::string &interface="") = 0;
	virtual IConnector *connectTCP(const std::string &host, int32_t port, protocol::ClientFactory *factory, int32_t timeout=30) = 0; //, bindAddress=None):

	virtual ~IReactorTCP() {}
};

}}} // spiral::internet::interfaces

#endif // _SPIRAL_INTERFACES_IREACTORTCP_H__
