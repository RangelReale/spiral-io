#ifndef _SPIRAL_INTERNET_ADDRESS_IPV4ADDRESS_H__
#define _SPIRAL_INTERNET_ADDRESS_IPV4ADDRESS_H__

#include <string>
#include "spiral/internet/interfaces/IAddress.h"
#include "spiral/sys/IntegerTypes.h"

namespace spiral {
namespace internet {
namespace address {

using namespace interfaces;
using namespace std;

class IPv4Address : public IAddress
{
public:
	enum type_t { TCP, UDP };

	IPv4Address() : type_(TCP), host_(), port_(0) {}
	IPv4Address(type_t type, const string &host, int32_t port) : type_(type), host_(host), port_(port) {}

	type_t getType() const { return type_; }
	const string &getHost() const { return host_; }
	int32_t getPort() const { return port_; }
private:
	type_t type_;
	string host_;
	int32_t port_;
};


}}} // spiral::internet::address

#endif // _SPIRAL_INTERNET_ADDRESS_IPV4ADDRESS_H__
