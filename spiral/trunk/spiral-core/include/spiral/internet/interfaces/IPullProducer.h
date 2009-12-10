#ifndef _SPIRAL_INTERNET_INTERFACES_IPULLPRODUCER_H__
#define _SPIRAL_INTERNET_INTERFACES_IPULLPRODUCER_H__

#include "spiral/internet/interfaces/IProducer.h"

namespace spiral {
namespace internet {
namespace interfaces {

/**
 *   A pull producer, also known as a non-streaming producer, is
 *   expected to produce data each time resumeProducing() is called.
 */
class IPullProducer 
{
public:
	/**
     *   Produce data for the consumer a single time.
     *
     *   This tells a producer to produce data for the consumer once
     *   (not repeatedly, once only). Typically this will be done
     *   by calling the consumer's write() method a single time with
     *   produced data.
	 */
	virtual void resumeProducing() = 0;

	virtual ~IPullProducer() {}
};

}}} // spiral::internet::interfaces

#endif // _SPIRAL_INTERNET_INTERFACES_IPULLPRODUCER_H__