#include <spiral/internet/boostreactor/BoostReactor.h>
#include <spiral/internet/protocol/Protocol.h>
#include <spiral/internet/protocol/ServerFactory.h>
#define BOOST_TEST_MODULE spiral
#include <boost/test/unit_test.hpp>

using namespace spiral::internet;

class R
{
public:
    boostreactor::BoostReactor reactor;
};

class MyProtocol : public protocol::Protocol
{
};

class MyServerFactory : public protocol::ServerFactory
{
public:
    /*
     * Create a L{MyProtocol} and set it up to be able to perform
     * callbacks.
     */
    virtual interfaces::IProtocol *buildProtocol(interfaces::IAddress addr) { 
        //self.peerAddresses.append(addr)
        //self.called += 1
        interfaces::IProtocol* p = new MyProtocol;
        //p.factory = self
        //p.closedDeferred = self.protocolConnectionLost
        //self.protocolConnectionLost = None
        //self.protocol = p
        return p;
    }
};

// @twisted: test_tcp.ListeningTestCase
BOOST_FIXTURE_TEST_SUITE(ListeningTestCase, R)

// @twisted: test_tcp.ListeningTestCase.test_listen
BOOST_AUTO_TEST_CASE(test_listen)
{
    MyServerFactory f;
    interfaces::IListeningPort* p1 = reactor.listenTCP(
        0, &f, /*backlog=*/50, /*interface=*/"127.0.0.1");
    p1->stopListening();
}

BOOST_AUTO_TEST_SUITE_END()

