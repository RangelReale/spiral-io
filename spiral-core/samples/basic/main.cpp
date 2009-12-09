//#include <vld.h>

#include <spiral/internet/boostreactor/BoostReactor.h>
#include <spiral/internet/protocol/Protocol.h>
#include <spiral/internet/protocol/ServerFactory.h>
#include <spiral/internet/protocol/ClientFactory.h>
#include <spiral/log/Logger.h>
#include <spiral/log/Statement.h>
#include <string>
#include <boost/bind.hpp>

using namespace spiral::internet;
using namespace spiral::internet::interfaces;
using namespace std;

class Echo : public protocol::Protocol
{
public:
	virtual void connectionMade()
	{
		protocol::Protocol::connectionMade();

		SPIRAL_LOG(debug, "ECHO: Connection made");
	}

	virtual void connectionLost(const spiral::Exception &reason)
	{
		SPIRAL_LOG(debug, "ECHO: Connection lost: " << reason.getMessage());
	}

	virtual void dataReceived(const char *data, size_t size)
	{
		SPIRAL_LOG(debug, "ECHO: Received " << size << " bytes");
	}
};


class HttpTest : public protocol::Protocol
{
public:
	virtual void connectionMade()
	{
		protocol::Protocol::connectionMade();
		SPIRAL_LOG(debug, "HttpTest: Connection made");

		reactor().callLater(30, boost::bind(&HttpTest::callme, this));

		data_="GET / HTTP/1.0\n\n";
		transport().write(data_.c_str(), data_.size());
	}

	void callme()
	{
		SPIRAL_LOG(debug, "HttpTest: CALLME!");
	}

	virtual void connectionLost(const spiral::Exception &reason)
	{
		SPIRAL_LOG(debug, "HttpTest: Connection lost: " << reason.getMessage());
		protocol::Protocol::connectionLost(reason);

		reactor().stop();
	}

	virtual void dataReceived(const char *data, size_t size)
	{
		SPIRAL_LOG(debug, "HttpTest: Received " << size << " bytes");
		protocol::Protocol::dataReceived(data, size);

		string rec(data, size);
		SPIRAL_LOG(debug, "HttpTest: Received data: " << rec);
	}
private:
	string data_;
};


class EchoFactory : public protocol::ServerFactory
{
public:
	virtual void startFactory() { SPIRAL_LOG(debug, "ECHOFACTORY: startFactory"); }
	virtual void stopFactory() { SPIRAL_LOG(debug, "ECHOFACTORY: stopFactory"); }

	// IProtocolFactory
	virtual interfaces::IProtocol *buildProtocol(interfaces::IAddress addr) { return new Echo(); }

	virtual void doStart()  { SPIRAL_LOG(debug, "ECHOFACTORY: doStart"); }
	virtual void doStop()  { SPIRAL_LOG(debug, "ECHOFACTORY: doStop"); }
};

class HttpTestFactory : public protocol::ClientFactory
{
public:
	virtual void startFactory() { SPIRAL_LOG(debug, "HttpTestFactory: startFactory"); }
	virtual void stopFactory() { SPIRAL_LOG(debug, "HttpTestFactory: stopFactory"); }

	// IProtocolFactory
	virtual interfaces::IProtocol *buildProtocol(interfaces::IAddress addr) { return new HttpTest(); }

	virtual void doStart()  { SPIRAL_LOG(debug, "HttpTestFactory: doStart"); }
	virtual void doStop()  { SPIRAL_LOG(debug, "HttpTestFactory: doStop"); }

	virtual void startedConnecting(IConnector &connector) { SPIRAL_LOG(debug, "HttpTestFactory: startedConnecting"); }
	virtual void clientConnectionFailed(IConnector *connector, const spiral::Exception &reason) { SPIRAL_LOG(debug, "HttpTestFactory: clientConnectionFailed"); connector->reactor().stop(); }
	virtual void clientConnectionLost(IConnector *connector, const spiral::Exception &reason) { SPIRAL_LOG(debug, "HttpTestFactory: clientConnectionLost"); /*connector->connect();*/ }

};

int main(int argc, char *argv[])
{
	spiral::log::Options logoptions;
	logoptions.trace=true;

	spiral::log::Logger::instance().setPrefix("basic");
	spiral::log::Logger::instance().configure(logoptions);

	boostreactor::BoostReactor reactor;

	EchoFactory factory;
	HttpTestFactory cfactory;

	//reactor.listenTCP(10000, &factory);
	reactor.connectTCP("www.uol.com.br", 80, &cfactory);
	reactor.run();

	//delete reactor;

	return 0;
}
