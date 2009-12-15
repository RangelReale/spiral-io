#ifndef _SPIRAL_INTERNET_BOOSTREACTOR_SOCKETCLOSER_H__
#define _SPIRAL_INTERNET_BOOSTREACTOR_SOCKETCLOSER_H__

#include <boost/asio.hpp>

namespace spiral {
namespace internet {
namespace boostreactor {

namespace ba=boost::asio;
namespace bs=boost::system;

using ba::ip::tcp;

class SocketCloser
{
public:
	void closeSocket()
	{
		getSocket().close();
	}

	virtual tcp::socket &getSocket() = 0;
};

}}} // spiral::internet::boostreactor

#endif // _SPIRAL_INTERNET_BOOSTREACTOR_SOCKETCLOSER_H__
