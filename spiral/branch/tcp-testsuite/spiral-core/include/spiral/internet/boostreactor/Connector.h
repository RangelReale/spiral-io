#ifndef _SPIRAL_INTERNET_BOOSTREACTOR_CONNECTOR_H__
#define _SPIRAL_INTERNET_BOOSTREACTOR_CONNECTOR_H__

#include <string>
#include "spiral/sys/IntegerTypes.h"
#include "spiral/internet/boostreactor/BoostReactor.h"
#include "spiral/internet/base/BaseConnector.h"

namespace spiral {
namespace internet {
namespace boostreactor {

using namespace std;

class Connector : public base::BaseConnector
{
public:
	Connector(const string &host, int32_t port, protocol::ClientFactory *factory, int32_t timeout, /*bindAddress,*/ BoostReactor *reactor);

	virtual IAddress getDestination();
protected:
	virtual ITransport *makeTransport();
private:
	string host_;
	int32_t port_;
};

}}} // spiral::internet::boostreactor

#endif // _SPIRAL_INTERNET_BOOSTREACTOR_CONNECTOR_H__
