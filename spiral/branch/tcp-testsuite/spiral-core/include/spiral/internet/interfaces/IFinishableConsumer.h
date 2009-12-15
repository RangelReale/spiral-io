#ifndef _SPIRAL_INTERNET_INTERFACES_IFINISHABLECONSUMER_H__
#define _SPIRAL_INTERNET_INTERFACES_IFINISHABLECONSUMER_H__

#include "spiral/sys/IntegerTypes.h"
#include "spiral/internet/interfaces/IConsumer.h"

namespace spiral {
namespace internet {
namespace interfaces {

/**
 * A Consumer for producers that finish.
 */
class IFinishableConsumer 
{
public:
	/**
	 * The producer has finished producing.
	 */
	virtual void finish() = 0;

	virtual ~IFinishableConsumer() {}
};

}}} // spiral::internet::interfaces

#endif // _SPIRAL_INTERNET_INTERFACES_IFINISHABLECONSUMER_H__