#ifndef _SPIRAL_INTERFACES_IREACTORCORE_H__
#define _SPIRAL_INTERFACES_IREACTORCORE_H__

#include "spiral/sys/IntegerTypes.h"
#include "spiral/internet/base/Callable.h"

namespace spiral {
namespace internet {
namespace interfaces {

class IReactorCore
{
public:
	typedef int32_t triggerid_t;
	enum eventtype_t
	{
		STARTUP,
		SHUTDOWN,
		PERSIST
	};
	enum phase_t
	{
		BEFORE,
		DURING,
		AFTER
	};

	//virtual void resolve(name, timeout=10);
	virtual void run() = 0;
	virtual void stop() = 0;
	virtual void crash() = 0;
	//virtual void iterate(delay=0) = 0;
	virtual void fireSystemEvent(eventtype_t eventtype) = 0;
	virtual triggerid_t addSystemEventTrigger(phase_t phase, eventtype_t eventtype, base::Callable callable) = 0;
	virtual void removeSystemEventTrigger(triggerid_t triggerID) = 0;
	virtual triggerid_t callWhenRunning(base::Callable callable) = 0;

	virtual bool getRunning() = 0;
};

}}} // spiral::internet::interfaces

#endif // _SPIRAL_INTERFACES_IREACTORCORE_H__
