#ifndef __H_SPIRAL_APPLICATION_APPLICATION_H__
#define __H_SPIRAL_APPLICATION_APPLICATION_H__

#include <string>

#include "spiral/Options.h"
#include "spiral/RefCounted.h"
#include "spiral/sys/Runnable.h"
#include "spiral/sys/IntegerTypes.h"

namespace spiral
{

class Application : public sys::Runnable, public RefCounted {
public:
	class Options : public spiral::Options {
	public:
        Options(const std::string& name="Application Options");
    };
public:
	Application(const Options& configuration);
	virtual ~Application() {}

	virtual void run();
private:
	Options config_;
};

}

#endif // __H_SPIRAL_APPLICATION_APPLICATION_H__
