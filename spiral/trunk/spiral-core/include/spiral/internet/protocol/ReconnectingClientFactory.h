#ifndef _SPIRAL_INTERNET_PROTOCOL_RECONNECTINGCLIENTFACTORY_H__
#define _SPIRAL_INTERNET_PROTOCOL_RECONNECTINGCLIENTFACTORY_H__

#include "spiral/Exception.h"
#include "spiral/internet/protocol/ClientFactory.h"

namespace spiral {
namespace internet {
namespace protocol {

using namespace interfaces;

class ReconnectingClientFactory : public ClientFactory
{
public:
	ReconnectingClientFactory();

	virtual void startedConnecting(IConnector &connector);
	virtual void clientConnectionFailed(IConnector *connector, const Exception &reason);
	virtual void clientConnectionLost(IConnector *connector, const Exception &reason);

	void stopTrying();
	void resetDelay();
private:
	void retry(IConnector *connector=NULL);

	void reconnector(IConnector *connector);

	int32_t maxdelay_, retries_, maxretries_;
	float initialdelay_, delay_;
	bool continuetrying_;
	IConnector *connector_;

	static const double FACTOR; // (math.e)
	static const double JITTER; // molar Planck constant times c, joule meter/mole
};

}}} // spiral::internet::protocol

#endif // _SPIRAL_INTERNET_PROTOCOL_RECONNECTINGCLIENTFACTORY_H__

