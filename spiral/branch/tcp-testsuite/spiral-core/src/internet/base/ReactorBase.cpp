#include "spiral/internet/base/ReactorBase.h"
#include "spiral/internet/Error.h"
#include "spiral/log/Logger.h"
#include "spiral/log/Statement.h"

namespace spiral {
namespace internet {
namespace base {

ReactorBase::ReactorBase() : running_(false), stopped_(true), installed_(false), usingThreads_(false),
	started_(false), juststopped_(false), eventtriggers_()
{
	addSystemEventTrigger(DURING, STARTUP, boost::bind(&ReactorBase::reallyStartRunning, this));
	addSystemEventTrigger(DURING, SHUTDOWN, boost::bind(&ReactorBase::crash, this));
	addSystemEventTrigger(DURING, SHUTDOWN, boost::bind(&ReactorBase::disconnectAll, this));
}

void ReactorBase::startRunning()
{
	if (started_)
		throw new error::ReactorAlreadyRunning();
	started_=true;
	stopped_=false;
	fireSystemEvent(STARTUP);
}

void ReactorBase::reallyStartRunning()
{
	running_=true;
}

void ReactorBase::disconnectAll()
{

}

void ReactorBase::run()
{
	startRunning();
	do_run();
	if (juststopped_)
	{
		juststopped_=false;
		fireSystemEvent(SHUTDOWN);
	}
}

void ReactorBase::stop()
{
	if (stopped_)
		throw new error::ReactorNotRunning("Can't stop reactor that isn't running.");
	stopped_=true;
	juststopped_=true;
	do_stop();
}

void ReactorBase::crash()
{
	started_=false;
	running_=false;
	addSystemEventTrigger(DURING, STARTUP, boost::bind(&ReactorBase::reallyStartRunning, this));
}

void ReactorBase::fireSystemEvent(eventtype_t eventtype)
{
	eventtriggers_t::iterator e=eventtriggers_.find(eventtype);
	if (e!=eventtriggers_.end())
		e->second->fireEvent();
}

IReactorCore::triggerid_t ReactorBase::addSystemEventTrigger(IReactorCore::phase_t phase, IReactorCore::eventtype_t eventtype, base::Callable callable)
{
	eventtriggers_t::iterator e=eventtriggers_.find(eventtype);
	if (e==eventtriggers_.end())
		eventtriggers_[eventtype]=boost::shared_ptr<ThreePhaseEvent>(new ThreePhaseEvent);
	return eventtriggers_[eventtype]->addTrigger(phase, callable);
}

void ReactorBase::removeSystemEventTrigger(IReactorCore::triggerid_t triggerID)
{
	// TODO
}

IReactorCore::triggerid_t ReactorBase::callWhenRunning(base::Callable callable)
{
	if (running_)
	{
		callable();
		return 0;
	}
	else
		return addSystemEventTrigger(AFTER, STARTUP, callable);
}

// ThreePhaseEvent
IReactorCore::triggerid_t ThreePhaseEvent::addTrigger(IReactorCore::phase_t phase, base::Callable callable) 
{ 
	phasecallable_t::iterator e=phasecallable_.find(phase);
	if (e==phasecallable_.end())
		phasecallable_[phase]=boost::shared_ptr<callablelist_t>(new callablelist_t);
	phasecallable_[phase]->push_back(callable); return 0; 
}

void ThreePhaseEvent::removeTrigger(IReactorCore::triggerid_t triggerid)
{

}

void ThreePhaseEvent::fireEvent()
{
	state_=BEFORE;
	phasecallable_t::iterator p;
	if ((p=phasecallable_.find(ReactorBase::BEFORE))!=phasecallable_.end())
	{
		while (p->second->size()>0)
		{
			base::Callable call=p->second->front();
			p->second->pop_front();

			try
			{
				call();
			} catch (std::exception &e) {
				SPIRAL_LOG(error, "Fire event error: " << e.what());
			}
		}
	}
	continueFiring();
}

void ThreePhaseEvent::continueFiring()
{
	state_=BASE;
	continueFiring(IReactorCore::DURING);
	continueFiring(IReactorCore::AFTER);
}

void ThreePhaseEvent::continueFiring(IReactorCore::phase_t phase)
{
	phasecallable_t::iterator p;
	if ((p=phasecallable_.find(phase))!=phasecallable_.end())
	{
		while (p->second->size()>0)
		{
			base::Callable call=p->second->front();
			p->second->pop_front();
			try
			{
				call();
			} catch (std::exception &e) {
				SPIRAL_LOG(error, "Fire event error: " << e.what());
			}
		}
	}
}

}}} // spiral::internet::base
