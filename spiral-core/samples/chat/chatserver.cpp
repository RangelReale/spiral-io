/*
The most basic chat protocol possible.

run me, and then connect with multiple
telnet clients to port 1025
*/

#include <spiral/internet/boostreactor/BoostReactor.h>
#include <spiral/protocols/basic/LineReceiver.h>
#include <spiral/internet/protocol/ServerFactory.h>
#include <deque>

using namespace spiral;
using namespace spiral::internet;
using namespace spiral::internet::interfaces;
using namespace std;

class MyChat;

class MyChatFactory : public protocol::ServerFactory
{
public:
	virtual interfaces::IProtocol *buildProtocol(interfaces::IAddress addr);

	void client_add(MyChat *c) { clients_.push_back(c); }
	void client_remove(MyChat *c) { clients_.erase( std::remove_if(clients_.begin(), clients_.end(), bind2nd(equal_to<MyChat*>(), c)) , clients_.end());  }
	void client_broadcast(const string &line);
private:
	deque<MyChat*> clients_;
};

class MyChat : public protocols::basic::LineReceiver
{
public:
	MyChat(MyChatFactory *factory) : protocols::basic::LineReceiver(), factory_(factory) {}

	virtual void connectionMade()
	{
		cout << "Got new client!" << endl;
		factory_->client_add(this);
	}

	virtual void connectionLost(const Exception &reason) 
	{
		cout << "Lost a client!" << endl;
		factory_->client_remove(this);
	}

	virtual void lineReceived(const string &line)
	{
		cout << "Received: " << line << endl;
		factory_->client_broadcast(line);
	}
private:
	MyChatFactory *factory_;
};


interfaces::IProtocol *MyChatFactory::buildProtocol(interfaces::IAddress addr) { return new MyChat(this); }

void MyChatFactory::client_broadcast(const string &line)
{
	for (deque<MyChat*>::iterator i=clients_.begin(); i!=clients_.end(); i++)
		(*i)->sendLine(line);
}

int main(int argc, char *argv[])
{
	boostreactor::BoostReactor reactor;

	MyChatFactory factory;

	reactor.listenTCP(1025, &factory);
	reactor.run();

	return 0;
}
