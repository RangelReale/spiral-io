// An example client. Run core-echoserver first before running this.

#include <spiral/internet/boostreactor/BoostReactor.h>
#include <spiral/internet/protocol/Protocol.h>
#include <spiral/internet/protocol/ServerFactory.h>

using namespace spiral;
using namespace spiral::internet;
using namespace spiral::internet::interfaces;
using namespace std;

// This is just about the simplest possible protocol
class Echo : public protocol::Protocol
{
public:
	// As soon as any data is received, write it back.
	virtual void dataReceived(const char *data, size_t size)
	{
		transport().write(data, size);
	}
};

class EchoFactory : public protocol::ServerFactory
{
public:
	virtual interfaces::IProtocol *buildProtocol(interfaces::IAddress addr) { return new Echo(); }
};

// This runs the protocol on port 8000
int main(int argc, char *argv[])
{
	boostreactor::BoostReactor reactor;

	EchoFactory factory;

	reactor.listenTCP(8000, &factory);
	reactor.run();

	return 0;
}
