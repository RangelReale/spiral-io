#ifndef _SPIRAL_PROTOCOLS_BASIC_LINERECEIVER_H__
#define _SPIRAL_PROTOCOLS_BASIC_LINERECEIVER_H__

#include "spiral/sys/IntegerTypes.h"
#include "spiral/internet/protocol/Protocol.h"
#include <string>

namespace spiral {
namespace protocols {
namespace basic {

using namespace internet;
using namespace std;

/**
 *   A protocol that receives lines and/or raw data, depending on mode.
 *
 *   In line mode, each line that's received becomes a callback to
 *   L{lineReceived}.  In raw data mode, each chunk of raw data becomes a
 *   callback to L{rawDataReceived}.  The L{setLineMode} and L{setRawMode}
 *   methods switch between the two modes.
 *
 *   This is useful for line-oriented protocols such as IRC, HTTP, POP, etc.
 *
 *   @cvar delimiter: The line-ending delimiter to use. By default this is
 *                    '\\r\\n'.
 *   @cvar MAX_LENGTH: The maximum length of a line to allow (If a
 *                     sent line is longer than this, the connection is dropped).
 *                     Default is 16384. 
 */
class LineReceiver : public protocol::Protocol
{
public:
	LineReceiver() : protocol::Protocol(), line_mode_(true), buffer_(), delimiter_("\r\n") {}
	LineReceiver(const string &delimiter) : protocol::Protocol(), line_mode_(true), buffer_(), delimiter_(delimiter) {}

    // Translates bytes into lines, and calls lineReceived (or
	// rawDataReceived, depending on mode.)
	virtual void dataReceived(const char *data, size_t size);

	// Override this for when each line is received.
	virtual void lineReceived(const string &line) {}

	// Override this for when raw data is received.
	virtual void rawDataReceived(const char *data, size_t size) {}

	// Sends a line to the other end of the connection.
	void sendLine(const string &line);

	void setLineMode(const string &extra = "") { line_mode_=true; if (!extra.empty()) dataReceived(extra.c_str(), extra.length()); } 
	void setRawMode() { line_mode_=false; }
protected:
	// Called when the maximum line length has been reached.
	// Override if it needs to be dealt with in some special way.
	virtual void lineLengthExceeded(const string &data) {}

	virtual string clearLineBuffer() { string b=buffer_; buffer_.clear(); return b; }
private:
	bool line_mode_;
	string buffer_, delimiter_;
	static const int32_t MAX_LENGTH = 16384;
};

}}} // spiral::protocols::basic

#endif // _SPIRAL_PROTOCOLS_BASIC_LINERECEIVER_H__
