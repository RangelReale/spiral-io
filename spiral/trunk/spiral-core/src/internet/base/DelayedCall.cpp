#include "spiral/internet/base/DelayedCall.h"
#include "spiral/internet/base/Callable.h"
#include "spiral/internet/Error.h"

namespace spiral {
namespace internet {
namespace base {

DelayedCall::DelayedCall(float time, Callable callable) :
	time_(time), callable_(callable), delayed_time_(0), called_(false), cancelled_(false)
{

}

void DelayedCall::cancel()
{
	if (cancelled_)
		throw new error::AlreadyCancelled();
	else if (called_)
		throw new error::AlreadyCalled();
	else
	{
		//canceller();
		cancelled_=true;
	}
}

void DelayedCall::delay(float secondsLater)
{
	if (cancelled_)
		throw new error::AlreadyCancelled();
	else if (called_)
		throw new error::AlreadyCalled();
	else
	{
		delayed_time_+=secondsLater;
		if (delayed_time_<0)
		{
			activate_delay();
			//resetter();
		}
	}
}

void DelayedCall::reset(float secondsFromNow)
{
	if (cancelled_)
		throw new error::AlreadyCancelled();
	else if (called_)
		throw new error::AlreadyCalled();
	else
	{
/*
            newTime = self.seconds() + secondsFromNow
            if newTime < self.time:
                self.delayed_time = 0
                self.time = newTime
                self.resetter(self)
            else:
                self.delayed_time = newTime - self.time
*/	
	}
}

void DelayedCall::activate_delay()
{
	time_+=delayed_time_;
	delayed_time_=0;
}

bool DelayedCall::active()
{
	return !(cancelled_ || called_);
}


}}} // spiral::internet::base
