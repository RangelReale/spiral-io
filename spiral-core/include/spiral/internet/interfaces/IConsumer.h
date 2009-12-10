#ifndef _SPIRAL_INTERNET_INTERFACES_ICONSUMER_H__
#define _SPIRAL_INTERNET_INTERFACES_ICONSUMER_H__

#include "spiral/sys/IntegerTypes.h"
#include "spiral/internet/interfaces/IProducer.h"

namespace spiral {
namespace internet {
namespace interfaces {

/**
 * A consumer consumes data from a producer.
 */
class IConsumer 
{
public:
	/**
	 *       Register to receive data from a producer.
	 *
	 *       This sets self to be a consumer for a producer.  When this object runs
	 *       out of data (as when a send(2) call on a socket succeeds in moving the
	 *       last data from a userspace buffer into a kernelspace buffer), it will
	 *       ask the producer to resumeProducing(). 
	 *
	 *       For L{IPullProducer} providers, C{resumeProducing} will be called once
	 *       each time data is required.
	 *
	 *       For L{IPushProducer} providers, C{pauseProducing} will be called
	 *       whenever the write buffer fills up and C{resumeProducing} will only be
	 *       called when it empties.
	 *
	 *       @type producer: L{IProducer} provider
	 *
	 *       @type streaming: C{bool}
	 *       @param streaming: C{True} if C{producer} provides L{IPushProducer},
	 *       C{False} if C{producer} provides L{IPullProducer}.
	 *
	 *       @raise RuntimeError: If a producer is already registered.
	 *
	 *       @return: C{None}
	 *
	 */
	virtual void registerProducer(IProducer *producer) = 0;

	/**
	 * Stop consuming data from a producer, without disconnecting.
	 */
	virtual void unregisterProducer() = 0;

	/**
	 * The producer will write data by calling this method.
	 */
	virtual void write(const char *data, size_t size) = 0;

	virtual ~IConsumer() {}
};

}}} // spiral::internet::interfaces

#endif // _SPIRAL_INTERNET_INTERFACES_ICONSUMER_H__