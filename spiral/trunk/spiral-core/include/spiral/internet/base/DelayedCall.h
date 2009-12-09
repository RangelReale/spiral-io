#ifndef _SPIRAL_INTERNET_BASE_DELAYEDCALL_H__
#define _SPIRAL_INTERNET_BASE_DELAYEDCALL_H__

#include "spiral/internet/interfaces/IDelayedCall.h"
#include "spiral/internet/base/Callable.h"

namespace spiral {
namespace internet {
namespace base {

using namespace interfaces;

class DelayedCall : public IDelayedCall
{
public:
	DelayedCall(float time, Callable callable); // cancel, reset, seconds

	// IDelayedCall
	virtual float getTime() { return time_+delayed_time_; }
	virtual void cancel();
	virtual void delay(float secondsLater);
	virtual void reset(float secondsFromNow);
	virtual bool active();
private:
	void activate_delay();

	float time_, delayed_time_;
	bool called_, cancelled_;
	Callable callable_;
};

}}} // spiral::internet::base

#endif // _SPIRAL_INTERNET_BASE_DELAYEDCALL_H__
