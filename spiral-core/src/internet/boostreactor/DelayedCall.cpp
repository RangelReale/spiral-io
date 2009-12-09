#include "spiral/internet/boostreactor/DelayedCall.h"
#include "spiral/log/Logger.h"
#include "spiral/log/Statement.h"

#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/bind.hpp>

namespace spiral {
namespace internet {
namespace boostreactor {

DelayedCall::DelayedCall(float time, base::Callable callable, BoostReactor *reactor) :
	time_(time), callable_(callable), reactor_(reactor), 
		timer_(reactor->getIoService()),
	delayed_time_(0), called_(false), cancelled_(false)
{
	activate_timer(time);
}

void DelayedCall::activate_timer(float time)
{
	timer_.expires_from_now(boost::posix_time::milliseconds(static_cast<int32_t>(time * 1000.0)));
	timer_.async_wait(boost::bind(&DelayedCall::handle_wait, this, ba::placeholders::error));
}

void DelayedCall::cancel()
{
	if (cancelled_)
		throw new error::AlreadyCancelled();
	else if (called_)
		throw new error::AlreadyCalled();
	else
	{
		timer_.cancel();
		cancelled_=true;
	}
}

void DelayedCall::delay(float secondsLater)
{
	assert(secondsLater>=0);
	
	if (cancelled_)
		throw new error::AlreadyCancelled();
	else if (called_)
		throw new error::AlreadyCalled();
	else
	{
		delayed_time_+=secondsLater;
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
		timer_.cancel();
		time_=secondsFromNow;
		delayed_time_=0;
		activate_timer(secondsFromNow);
	}
}

bool DelayedCall::active()
{
	return !(cancelled_ || called_);
}

void DelayedCall::handle_wait(const bs::error_code &error)
{
	if (!error)
	{
		if (active())
		{
			if (delayed_time_>0)
			{
				float d=delayed_time_;
				delayed_time_=0;
				activate_timer(d);
				return;
			}

			called_=true;
			if (callable_)
			{
				try
				{
					callable_();
				} catch (std::exception &e) {
					SPIRAL_LOG(error, "Exception in delayed call: " << e.what());
				}
			}
		}
	} else if (error!=ba::error::operation_aborted) {
		SPIRAL_LOG(error, "Timer failed: " << error.message());
	}
}

}}} // spiral::internet::boostreactor
