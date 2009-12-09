#ifndef _SPIRAL_INTERNET_BOOSTREACTOR_DELAYEDCALL_H__
#define _SPIRAL_INTERNET_BOOSTREACTOR_DELAYEDCALL_H__

#include <string>
#include <boost/asio.hpp>
#include "spiral/Exception.h"
#include "spiral/internet/Error.h"
#include "spiral/internet/boostreactor/BoostReactor.h"
#include "spiral/internet/interfaces/IDelayedCall.h"

namespace spiral {
namespace internet {
namespace boostreactor {

using namespace std;

namespace ba=boost::asio;
namespace bs=boost::system;

class DelayedCall : public IDelayedCall
{
public:
	DelayedCall(float time, base::Callable callable, BoostReactor *reactor); // cancel, reset, seconds
	virtual ~DelayedCall() { if (active()) cancel(); }

	// IDelayedCall
	virtual float getTime() { return time_+delayed_time_; }
	virtual void cancel();
	virtual void delay(float secondsLater);
	virtual void reset(float secondsFromNow);
	virtual bool active();
private:
	void activate_timer(float time);

	void handle_wait(const bs::error_code &error);

	float time_, delayed_time_;
	bool called_, cancelled_;
	base::Callable callable_;
	BoostReactor *reactor_;

	ba::deadline_timer timer_;
};

}}} // spiral::internet::boostreactor

#endif // _SPIRAL_INTERNET_BOOSTREACTOR_DELAYEDCALL_H__
