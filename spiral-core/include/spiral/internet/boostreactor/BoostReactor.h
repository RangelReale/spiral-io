#ifndef _SPIRAL_INTERNET_BOOSTREACTOR_BOOSTREACTOR_H__
#define _SPIRAL_INTERNET_BOOSTREACTOR_BOOSTREACTOR_H__

#include "spiral/internet/base/ReactorBase.h"
#include "spiral/internet/interfaces/IReactorTCP.h"
#include "spiral/internet/interfaces/IDelayedCall.h"

#include <boost/asio.hpp>
#include <boost/shared_ptr.hpp>
#include <deque>


namespace spiral {
namespace internet {
namespace boostreactor {

using namespace interfaces;

namespace ba=boost::asio;
namespace bs=boost::system;

class BoostReactor : public base::ReactorBase, public IReactorTCP
{
public:
	BoostReactor();

	ba::io_service &getIoService() { return io_service_; }

	// IReactorCore

	//virtual void resolve(name, timeout=10);

	// IReactorTCP
	virtual IListeningPort *listenTCP(int32_t port, protocol::ServerFactory *factory, int32_t backlog=50, const std::string &interface="");
	virtual IConnector *connectTCP(const std::string &host, int32_t port, protocol::ClientFactory *factory, int32_t timeout=30); //, bindAddress=None):

	// IReactorTime
	virtual uint32_t seconds();
	virtual IDelayedCall *callLater(float delay, base::Callable callable);
	virtual void cancelCallLater(IDelayedCall *callid);
protected:
	virtual void do_run();
	virtual void do_stop();
private:
	typedef std::deque< boost::shared_ptr<IConnector> > connector_list_t;
	typedef std::deque< boost::shared_ptr<IListeningPort> > listeningport_list_t;
	typedef std::deque< boost::shared_ptr<IDelayedCall> > delayedcall_list_t;

	ba::io_service io_service_;
	ba::io_service::work io_service_work_;

	delayedcall_list_t delayedcalls_;
	connector_list_t connectors_;
	listeningport_list_t listeningports_;
};

}}} // spiral::internet::boostreactor

#endif // _SPIRAL_INTERNET_BOOSTREACTOR_BOOSTREACTOR_H__
