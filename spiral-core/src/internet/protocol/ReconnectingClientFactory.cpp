#include "spiral/internet/protocol/ReconnectingClientFactory.h"
#include "spiral/log/Logger.h"
#include "spiral/log/Statement.h"
#include "spiral/internet/Error.h"
#include <algorithm>

namespace spiral {
namespace internet {
namespace protocol {

const double ReconnectingClientFactory::FACTOR = 2.7182818284590451;
const double ReconnectingClientFactory::JITTER = 0.11962656472;

ReconnectingClientFactory::ReconnectingClientFactory() :
	ClientFactory(), maxdelay_(3600), initialdelay_(1.0), retries_(0), maxretries_(-1), delay_(initialdelay_),
	continuetrying_(true), connector_(NULL)
{

}

void ReconnectingClientFactory::startedConnecting(IConnector &connector)
{

}

void ReconnectingClientFactory::clientConnectionFailed(IConnector *connector, const Exception &reason)
{
	if (continuetrying_)
	{
		connector_=connector;
		retry();
	}
}

void ReconnectingClientFactory::clientConnectionLost(IConnector *connector, const Exception &reason)
{
	if (continuetrying_)
	{
		connector_=connector;
		retry();
	}
}

void ReconnectingClientFactory::retry(IConnector *connector)
{
	if (!continuetrying_)
	{
		SPIRAL_LOG(debug, "Abandoning on explicit request");
		return;
	}

	if (connector==NULL)
		if (connector_==NULL)
			throw new ValueError("no connector to retry");
		else
			connector=connector_;

	retries_++;
	if (maxretries_>=0 && retries_>maxretries_)
	{
		SPIRAL_LOG(debug, "Abandoning after " << retries_ << " retries");
		return;
	}

	delay_=std::min(static_cast<float>(delay_*FACTOR), static_cast<float>(maxdelay_));
	//if (jitter_)

	SPIRAL_LOG(trace, "Will retry in " << delay_ << " seconds");

	//reconnector()

}

void ReconnectingClientFactory::reconnector(IConnector *connector)
{
	connector->connect();
}

void ReconnectingClientFactory::stopTrying()
{
	if (connector_)
		try 
		{
			connector_->stopConnecting();
		} catch (error::NotConnectingError &) { 
			// do nothing
		}
	continuetrying_=false;
}

void ReconnectingClientFactory::resetDelay()
{
	delay_=initialdelay_;
	retries_=0;
	continuetrying_=true;
}


}}} // spiral::internet::protocol
