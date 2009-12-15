#ifndef _SPIRAL_INTERNET_INTERFACES_IDELAYEDCALL_H__
#define _SPIRAL_INTERNET_INTERFACES_IDELAYEDCALL_H__

#include <boost/function.hpp>

namespace spiral {
namespace internet {
namespace interfaces {

class IDelayedCall
{
public:
	virtual float getTime() = 0;
	virtual void cancel() = 0;
	virtual void delay(float secondsLater) = 0;
	virtual void reset(float secondsFromNow) = 0;
	virtual bool active() = 0;

	virtual ~IDelayedCall() {}
};

}}} // spiral::internet::interfaces

#endif // _SPIRAL_INTERNET_INTERFACES_IDELAYEDCALL_H__
