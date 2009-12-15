#ifndef _SPIRAL_INTERNET_INTERFACES_IPRODUCER_H__
#define _SPIRAL_INTERNET_INTERFACES_IPRODUCER_H__

namespace spiral {
namespace internet {
namespace interfaces {

/**
 *  A producer produces data for a consumer.
 *
 *  Typically producing is done by calling the write method of an class
 *  implementing L{IConsumer}.
 */
class IProducer 
{
public:
	/**
	 *       Stop producing data.
	 *
	 *       This tells a producer that its consumer has died, so it must stop
	 *       producing data for good.
	 */
	virtual void stopProducing() = 0;

	virtual ~IProducer() {}
};

}}} // spiral::internet::interfaces

#endif // _SPIRAL_INTERNET_INTERFACES_IPRODUCER_H__