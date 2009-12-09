// An example client. Run core-echoserver first before running this.

#include <iostream>
#include <spiral/internet/boostreactor/BoostReactor.h>
#include <spiral/internet/protocol/Protocol.h>
#include <spiral/internet/protocol/ClientFactory.h>
#include <string>

using namespace spiral;
using namespace spiral::internet;
using namespace spiral::internet::interfaces;
using namespace std;

// a client protocol
// Once connected, send a message, then print the result.
class Echo : public protocol::Protocol
{
public:
	virtual void connectionMade()
	{
		string s("hello, world!");
		transport().write(s.c_str(), s.size());
	}
	// As soon as any data is received, write it back.
	virtual void dataReceived(const char *data, size_t size)
	{
		string s(data, size);
		cout << "Server said: " << s << endl;
		transport().loseConnection();
	}
	virtual void connectionLost(const spiral::Exception &reason)
	{
		cout << "connection lost" << endl;
	}
};

class EchoFactory : public protocol::ClientFactory
{
public:
	virtual void clientConnectionFailed(IConnector *connector, const Exception &reason) 
	{
		cout << "Connection failed - goodbye!" << endl;
		connector->reactor().stop();
	}
	virtual void clientConnectionLost(IConnector *connector, const Exception &reason) 
	{
		cout << "Connection lost - goodbye!" << endl;
		connector->reactor().stop();
	}
	virtual interfaces::IProtocol *buildProtocol(interfaces::IAddress addr) { return new Echo(); }
};

// this connects the protocol to a server runing on port 8000
int main(int argc, char *argv[])
{
	boostreactor::BoostReactor reactor;

	EchoFactory factory;

	reactor.connectTCP("localhost", 8000, &factory);
	reactor.run();

	return 0;
}
