#ifndef _SPIRAL_INTERFACES_IREACTORTIME_H__
#define _SPIRAL_INTERFACES_IREACTORTIME_H__

#include <string>
#include "spiral/sys/IntegerTypes.h"
#include "spiral/internet/interfaces/IDelayedCall.h"

namespace spiral {
namespace internet {
namespace interfaces {

class IReactorTime
{
public:
	virtual uint32_t seconds() = 0;
	virtual IDelayedCall *callLater(float delay, base::Callable callable) = 0;
	virtual void cancelCallLater(IDelayedCall *callid) = 0;

	//void getDelayedCalls() = 0;

	virtual ~IReactorTime() {}
};

}}} // spiral::internet::interfaces

#endif // _SPIRAL_INTERFACES_IREACTORTIME_H__
