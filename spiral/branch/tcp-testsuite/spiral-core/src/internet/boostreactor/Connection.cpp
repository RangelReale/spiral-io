#include <boost/bind.hpp>
#include "spiral/internet/boostreactor/Connection.h"
#include "spiral/internet/address/IPv4Address.h"
#include "spiral/log/Logger.h"
#include "spiral/log/Statement.h"
#include "spiral/internet/interfaces/IHalfCloseableProtocol.h"
#include "spiral/internet/interfaces/IPushProducer.h"
#include "spiral/internet/interfaces/IPullProducer.h"

namespace spiral {
namespace internet {
namespace boostreactor {


Connection::Connection(IProtocol *protocol, BoostReactor *reactor) :
	protocol_(protocol), reactor_(reactor), socket_(reactor->getIoService()),
	connected_(false), disconnected_(false), disconnecting_(false),
	reading_(false), writing_(false), readbuffers_(), writebuffers_(),
	readscheduled_(NULL), readScheduledInOS_(false), readbuffer_(),
	writeDisconnecting_(false), writeDisconnected_(false), writescheduled_(NULL),
	writebuffer_(), producerPaused_(false), streamingProducer_(false), producer_(NULL),
	writebufferssize_(0),
	writeBufferSize_(256) // 2**2**2**2
{

}

Connection::~Connection()
{
	if (readscheduled_)
	{
		readscheduled_->cancel();
		//delete readscheduled_;
		readscheduled_=NULL;
	}
	if (writescheduled_)
	{
		writescheduled_->cancel();
		//delete writescheduled_;
		writescheduled_=NULL;
	}
}

void Connection::handle_error(const bs::error_code& error)
{
	SPIRAL_LOG(debug, "CONNECTION: error: " << error.message() );
}

void Connection::connectionLost(const Exception &reason)
{
	setDisconnected(true);
	setConnected(false);

	if (producer_)
	{
		producer_->stopProducing();
		producer_=NULL;
	}

	stopReading();
	stopWriting();
	//self.reactor.removeActiveHandle(self)

/*
	abstract.FileHandle.connectionLost(self, reason)
*/
    closeSocket();

	boost::shared_ptr<IProtocol> p=protocol_;
	protocol_.reset();

	p->connectionLost(reason);
}

void Connection::loseConnection()
{
	if (getConnected() && !getDisconnecting())
	{
		if (writeDisconnected_)
		{
			stopReading();
			stopWriting();
			connectionLost(error::ConnectionDone(""));
		}
		else
		{
			stopReading();
			startWriting();
			disconnecting_=true;
		}
	}
}

IAddress Connection::getPeer()
{
	return address::IPv4Address();
}

IAddress Connection::getHost()
{
	return address::IPv4Address();
}

// ITCPTransport
void Connection::loseWriteConnection()
{
	writeDisconnecting_=true;
	startWriting();
}


void Connection::startReading()
{
	//self.reactor.addActiveHandle(self)
	if (!readscheduled_ && !reading_)
	{
		reading_=true;
		readscheduled_=reactor_->callLater(0, boost::bind(&Connection::resumeReading, this));
	}
}

void Connection::stopReading()
{
	if (readscheduled_)
	{
		readscheduled_->cancel();
		//delete readscheduled_;
		readscheduled_=NULL;
	}
	reading_=false;
}


void Connection::resumeReading()
{
	if (readscheduled_)
	{
		//delete readscheduled_;
		readscheduled_=NULL;
	}
	if (dispatchData() && ! readScheduledInOS_)
		doRead();
}

void Connection::readConnectionLost(const Exception &reason) 
{ 
	IHalfCloseableProtocol *p=dynamic_cast<IHalfCloseableProtocol*>(protocol_.get());
	if (p)
	{
		try
		{
			p->readConnectionLost();
		} catch (Exception &e) {
			connectionLost(e);
		} catch (...) {
			connectionLost(error::ConnectionLost());
		}
	} else
		connectionLost(reason); 
}

bool Connection::dispatchData()
{
	if (readbuffers_.size()==0)
		return reading_;
	boost::shared_ptr<Buffer> rb;
	while (!readbuffers_.empty())
	{
		rb=readbuffers_.front();
		readbuffers_.pop_front();
		dataReceived(rb->data, rb->datasize);
		if (!reading_)
			return false;
	}
	//if self.dynamicReadBuffers:
	// TODO?
	return reading_;
}

void Connection::cbRead(const bs::error_code& error,
	size_t bytes_transferred)
{
	readScheduledInOS_=false;
	if (handleRead(error, bytes_transferred))
		doRead();
}

bool Connection::handleRead(const bs::error_code& error, size_t bytes_transferred)
{
	if (disconnected_)
		return false;

	if (error == ba::error::eof || error == ba::error::connection_aborted || error == ba::error::connection_reset)
	{
		//self.reactor.removeActiveHandle(self)
		readConnectionLost(error::ConnectionDone(error.message()));
		return false;
	}
	else if (error)
	{
		connectionLost(error::ConnectionLost(error.message()));
		return false;
	}
	else
	{
		readbuffer_->datasize=bytes_transferred;
		readbuffers_.push_back(boost::shared_ptr<Buffer>(readbuffer_));	
		readbuffer_.reset();
		return dispatchData();
	}
}

void Connection::doRead()
{
	readbuffer_.reset(new Buffer(READBUFFERSIZE));
	//readbuffer_.reset(new Buffer(READBUFFERSIZE));
	
	ba::async_read(socket_, ba::buffer(readbuffer_->data, readbuffer_->buffersize),
		ba::transfer_at_least(1),
		boost::bind(&Connection::cbRead, this,
			ba::placeholders::error,
			ba::placeholders::bytes_transferred));
	readScheduledInOS_=true;
}


void Connection::startWriting()
{
	//self.reactor.addActiveHandle(self)
	writing_=true;
	if (!writescheduled_)
	{
		writescheduled_=reactor_->callLater(0.0, boost::bind(&Connection::resumeWriting, this));
	}
}

void Connection::stopWriting()
{
	if (writescheduled_)
	{
		writescheduled_->cancel();
		//delete writescheduled_;
		writescheduled_=NULL;
	}
	writing_=false;
}

void Connection::resumeWriting()
{
	if (writescheduled_)
	{
		//delete writescheduled_;
		writescheduled_=NULL;
	}
	doWrite();
}

void Connection::cbWrite(const bs::error_code& error,
	size_t bytes_transferred)
{
	if (handleWrite(error, bytes_transferred))
		doWrite();
}

bool Connection::handleWrite(const bs::error_code& error, size_t bytes_transferred)
{
	if (disconnected_ || writeDisconnected_)
		return false;

	if (error)
	{
		connectionLost(error::ConnectionLost(error.message()));
		return false;
	}
	else
	{
		// If there is nothing left to send,
		if (writebuffers_.empty())
		{
			stopWriting();
			// If I've got a producer who is supposed to supply me with data
			if (producer_ && (!streamingProducer_ || producerPaused_))
			{
				// tell them to supply some more.
				producerPaused_=true;
				dynamic_cast<IPullProducer*>(producer_)->resumeProducing();
			}
			else if (disconnecting_)
				connectionLost(error::ConnectionDone());
			else if (writeDisconnecting_)
			{
				closeWriteConnection();
				writeDisconnected_=true;
			}
			return false;
		}
		else
			return true;
	}
}

void Connection::doWrite()
{
	if (writebuffers_.size()>0)
	{
		writebuffer_=writebuffers_.front();
		writebuffers_.pop_front();
		writebufferssize_-=writebuffer_->datasize;

		ba::async_write(getSocket(), ba::buffer(writebuffer_->data, writebuffer_->datasize),
			boost::bind(&Connection::cbWrite, this,
				ba::placeholders::error,
				ba::placeholders::bytes_transferred));
	}
}

void Connection::write(const char *data, size_t size)
{
	if (!connected_ || writeDisconnected_)
		return;
	if (size>0)
	{
		writebuffers_.push_back(boost::shared_ptr<Buffer>(new Buffer(data, size)));
		writebufferssize_+=size;
		if (producer_)
		{
			if (writebufferssize_ > writeBufferSize_)
			{
				producerPaused_=true;
				IPushProducer *p=dynamic_cast<IPushProducer*>(producer_);
				if (p)
					p->pauseProducing();
			}
		}
		startWriting();
	}
}

//virtual void writeSequence() = 0;


void Connection::closeWriteConnection()
{
	IHalfCloseableProtocol *p=dynamic_cast<IHalfCloseableProtocol*>(protocol_.get());
	if (p)
	{
		try
		{
			p->writeConnectionLost();
		} catch (Exception &e) {
			connectionLost(e);
		} catch (...) {
			connectionLost(error::ConnectionLost());
		}
	}
}

bool Connection::getTcpNoDelay()
{
	ba::ip::tcp::no_delay nd;
	socket_.get_option(nd);
	return nd.value();
}

void Connection::setTcpNoDelay(bool enabled)
{
	ba::ip::tcp::no_delay nd(enabled);
	socket_.set_option(nd);
}

bool Connection::getTcpKeepAlive()
{
	ba::socket_base::keep_alive ka;
	socket_.get_option(ka);
	return ka.value();
}

void Connection::setTcpKeepAlive(bool enabled)
{
	ba::socket_base::keep_alive ka(enabled);
	socket_.set_option(ka);
}

void Connection::registerProducer(IProducer *producer)
{
	if (producer_)
		throw new RuntimeError("Cannot register producer, because previous producer was never unregistered");
	if (disconnected_)
		producer->stopProducing();
	else
	{
		producer_=producer;
		IPullProducer *p=dynamic_cast<IPullProducer*>(producer);
		streamingProducer_=!p;
		if (p)
			p->resumeProducing();
	}
}

void Connection::unregisterProducer()
{
	producer_=NULL;
}

void Connection::stopConsuming()
{
	unregisterProducer();
	loseConnection();
}

void Connection::pauseProducing()
{
	stopReading();
}

void Connection::resumeProducing()
{
	assert(connected_ &&  !disconnecting_);
	startReading();
}

void Connection::stopProducing()
{
	loseConnection();
}



}}} // spiral::internet::boostreactor
