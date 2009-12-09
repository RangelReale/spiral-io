#ifndef _SPIRAL_PROTOCOLS_BASIC_LINEONLYRECEIVER_H__
#define _SPIRAL_PROTOCOLS_BASIC_LINEONLYRECEIVER_H__

#include "spiral/sys/IntegerTypes.h"
#include "spiral/internet/protocol/Protocol.h"
#include <string>

namespace spiral {
namespace protocols {
namespace basic {

using namespace internet;
using namespace std;

/**
 *   A protocol that receives only lines.
 *
 *   This is purely a speed optimisation over LineReceiver, for the
 *   cases that raw mode is known to be unnecessary.
 *
 *   @cvar delimiter: The line-ending delimiter to use. By default this is
 *                    '\\r\\n'.
 *   @cvar MAX_LENGTH: The maximum length of a line to allow (If a
 *                     sent line is longer than this, the connection is dropped).
 *                     Default is 16384.
 */
class LineOnlyReceiver : public protocol::Protocol
{
public:
	LineOnlyReceiver() : protocol::Protocol(), buffer_(), delimiter_("\r\n") {}
	LineOnlyReceiver(const string &delimiter) : protocol::Protocol(), buffer_(), delimiter_(delimiter) {}

	// Translates bytes into lines, and calls lineReceived.
	virtual void dataReceived(const char *data, size_t size);

	// Override this for when each line is received.
	virtual void lineReceived(const string &line) {}

	// Sends a line to the other end of the connection.
	void sendLine(const string &line);
protected:
	// Called when the maximum line length has been reached.
	// Override if it needs to be dealt with in some special way.
	virtual void lineLengthExceeded(const string &data) {}
private:
	string buffer_, delimiter_;
	static const int32_t MAX_LENGTH = 16384;
};

}}} // spiral::protocols::basic

#endif // _SPIRAL_PROTOCOLS_BASIC_LINEONLYRECEIVER_H__
