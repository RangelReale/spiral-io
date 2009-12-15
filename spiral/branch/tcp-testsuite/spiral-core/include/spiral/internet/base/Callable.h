#ifndef _SPIRAL_INTERNET_BASE_CALLABLE_H__
#define _SPIRAL_INTERNET_BASE_CALLABLE_H__

#include <boost/function.hpp>
#include <boost/bind.hpp>

namespace spiral {
namespace internet {
namespace base {

typedef boost::function<void(void)> Callable;

}}} // spiral::internet::base

#endif // _SPIRAL_INTERNET_BASE_CALLABLE_H__
