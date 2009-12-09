#ifndef _SPIRAL_INTERNET_BOOSTREACTOR_CONNECTION_H__
#define _SPIRAL_INTERNET_BOOSTREACTOR_CONNECTION_H__

#include "spiral/internet/boostreactor/BoostReactor.h"
#include "spiral/internet/boostreactor/SocketCloser.h"
#include "spiral/internet/interfaces/ITCPTransport.h"
#include "spiral/internet/interfaces/IProtocol.h"
#include "spiral/internet/interfaces/IProtocolFactory.h"
#include "spiral/internet/Error.h"
#include "spiral/log/Logger.h"
#include "spiral/log/Statement.h"

#include <boost/asio.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <deque>
#include <cstring>

namespace spiral {
namespace internet {
namespace boostreactor {

using namespace interfaces;

namespace ba=boost::asio;
namespace bs=boost::system;

using ba::ip::tcp;

class Connection : public ITCPTransport, public SocketCloser
{
public:
	Connection(IProtocol *protocol, BoostReactor *reactor);
	virtual ~Connection();

	void startReading();
	void stopReading();
	void startWriting();
	void stopWriting();

	virtual void dataReceived(const char *data, size_t size) { protocol_->dataReceived(data, size);  }
	virtual void connectionLost(const Exception &reason);

	void setProtocol(IProtocol *protocol) { protocol_.reset(protocol); }

	// ITransport
	virtual void write(const char *data, size_t size);
	//virtual void writeSequence() = 0;
	virtual void loseConnection();
	virtual IAddress getPeer();
	virtual IAddress getHost();

	virtual bool disconnecting() { return getDisconnecting(); }

	virtual IReactor &reactor() { return *reactor_; }

	// ITCPTransport
	virtual void loseWriteConnection();
	virtual bool getTcpNoDelay();
    virtual void setTcpNoDelay(bool enabled);
	virtual bool getTcpKeepAlive();
    virtual void setTcpKeepAlive(bool enabled);

	virtual tcp::socket &getSocket() { return socket_; }
protected:
	virtual IProtocol *getProtocol() { return &*protocol_; }

	void handle_error(const bs::error_code& error);

	virtual void closeWriteConnection();

	void setConnected(bool v) { connected_=v; }
	void setDisconnected(bool v) { disconnected_=v; }
	void setDisconnecting(bool v) { disconnecting_=v; }
	bool getConnected() { return connected_; }
	bool getDisconnected() { return disconnected_; }
	bool getDisconnecting() { return disconnecting_; }
private:
	struct Buffer
	{
		Buffer(int32_t size) : buffersize(size), datasize(0), data(new char[size]) {}
		Buffer(const char *d, int32_t size) : datasize(size), buffersize(size), data(new char[size]) { memcpy(data, d, size); }
		virtual ~Buffer() { delete [] data; }

		char *data;
		int32_t buffersize, datasize;
	};

	// read stuff
	static const int32_t READBUFFERSIZE = 4096;
	static const int32_t MAXREADBUFFERS = 16;
	bool reading_, readScheduledInOS_;
	//char read[READBUFFERSIZE];
	std::deque< boost::shared_ptr<Buffer> > readbuffers_;
	boost::shared_ptr<Buffer> readbuffer_;
	IDelayedCall *readscheduled_;

	void cbRead(const bs::error_code& error, size_t bytes_transferred);
	void resumeReading();
	void readConnectionLost(const Exception &reason);
	bool dispatchData();
	bool handleRead(const bs::error_code& error, size_t bytes_transferred);
	void doRead();

	// write stuff
	bool writing_, writeDisconnecting_, writeDisconnected_;
	std::deque< boost::shared_ptr<Buffer> > writebuffers_;
	boost::shared_ptr<Buffer> writebuffer_;
	IDelayedCall *writescheduled_;

	void cbWrite(const bs::error_code& error, size_t bytes_transferred);
	void resumeWriting();
	void writeConnectionLost(const Exception &reason) { connectionLost(reason); }
	bool handleWrite(const bs::error_code& error, size_t bytes_transferred);
	void doWrite();


	BoostReactor *reactor_;
	boost::shared_ptr<IProtocol> protocol_;

	tcp::socket socket_;

    bool connected_;
    bool disconnected_;
    bool disconnecting_;
};

}}} // spiral::internet::boostreactor

#endif // _SPIRAL_INTERNET_BOOSTREACTOR_CONNECTION_H__
