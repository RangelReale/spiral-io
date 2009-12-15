#ifndef _SPIRAL_INTERNET_INTERFACES_IREACTOR_H__
#define _SPIRAL_INTERNET_INTERFACES_IREACTOR_H__

#include "spiral/internet/interfaces/IReactorCore.h"
#include "spiral/internet/interfaces/IReactorTime.h"

namespace spiral {
namespace internet {
namespace interfaces {

class IReactor : public IReactorCore, public IReactorTime
{
public:
	virtual ~IReactor() {}
};

}}} // spiral::internet::interfaces

#endif // _SPIRAL_INTERNET_INTERFACES_IREACTOR_H__
