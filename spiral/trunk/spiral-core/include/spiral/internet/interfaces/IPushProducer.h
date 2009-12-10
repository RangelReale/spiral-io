#ifndef _SPIRAL_INTERNET_INTERFACES_IPUSHPRODUCER_H__
#define _SPIRAL_INTERNET_INTERFACES_IPUSHPRODUCER_H__

#include "spiral/internet/interfaces/IProducer.h"

namespace spiral {
namespace internet {
namespace interfaces {

/**
 *   A push producer, also known as a streaming producer is expected to
 *   produce (write to this consumer) data on a continous basis, unless
 *   it has been paused. A paused push producer will resume producing
 *   after its resumeProducing() method is called.   For a push producer
 *   which is not pauseable, these functions may be noops.
 */
class IPushProducer 
{
public:
	/**
     *   Pause producing data.
	 *
     *   Tells a producer that it has produced too much data to process for
     *   the time being, and to stop until resumeProducing() is called.
	 */
	virtual void pauseProducing() = 0;

	/**
     *   Resume producing data.
     *
     *   This tells a producer to re-add itself to the main loop and produce
     *   more data for its consumer.
	 */
	virtual void resumeProducing() = 0;

	virtual ~IPushProducer() {}
};

}}} // spiral::internet::interfaces

#endif // _SPIRAL_INTERNET_INTERFACES_IPUSHPRODUCER_H__