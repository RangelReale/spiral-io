#ifndef _SPIRAL_INTERNET_BASE_REACTORBASE_H__
#define _SPIRAL_INTERNET_BASE_REACTORBASE_H__

#include "spiral/internet/interfaces/IReactor.h"
//#include "spiral/internet/interfaces/IReactorCore.h"
//#include "spiral/internet/interfaces/IReactorTime.h"
//#include "spiral/internet/interfaces/IReactorPluggableResolver.h"
#include "spiral/internet/base/Callable.h"
#include <map>
#include <deque>

namespace spiral {
namespace internet {
namespace base {

using namespace interfaces;

class ThreePhaseEvent;

class ReactorBase : public IReactor//, public IReactorPluggableResolver
{
public:
	ReactorBase();

	void startRunning();

	virtual bool getRunning() { return running_; }

	// IReactorCore

	//virtual void resolve(name, timeout=10);
	virtual void run();
	virtual void stop();
	virtual void crash();
	//virtual void iterate(delay=0) = 0;
	virtual void fireSystemEvent(eventtype_t eventtype);
	virtual triggerid_t addSystemEventTrigger(phase_t phase, eventtype_t eventtype, base::Callable callable);
	virtual void removeSystemEventTrigger(triggerid_t triggerID);
	virtual triggerid_t callWhenRunning(base::Callable callable);
protected:
	virtual void do_run() {}
	virtual void do_stop() {}
private:
	typedef std::map<eventtype_t, boost::shared_ptr<ThreePhaseEvent> > eventtriggers_t;

	void reallyStartRunning();
	void disconnectAll();

	bool running_;
	bool started_;
	bool juststopped_;
	bool stopped_;
	bool installed_;
	bool usingThreads_;
	//resolver;

	eventtriggers_t eventtriggers_;
};

class ThreePhaseEvent
{
public:
	enum state_t
	{
		BASE,
		BEFORE,
	};

	ThreePhaseEvent() : phasecallable_(), state_(BASE) {}

	IReactorCore::triggerid_t addTrigger(IReactorCore::phase_t phase, base::Callable callable);
	void removeTrigger(IReactorCore::triggerid_t triggerid);

	void fireEvent();
private:
	void continueFiring();
	void continueFiring(IReactorCore::phase_t phase);

	typedef std::deque<base::Callable> callablelist_t;
	typedef std::map<IReactorCore::phase_t, boost::shared_ptr<callablelist_t> > phasecallable_t;
	phasecallable_t phasecallable_;
	state_t state_;
};


}}} // spiral::internet::base

#endif // _SPIRAL_INTERNET_BASE_REACTORBASE_H__
