#include <boost/foreach.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/iter_find.hpp>
#include <list>
#include "spiral/protocols/basic/LineOnlyReceiver.h"

namespace spiral {
namespace protocols {
namespace basic {

void LineOnlyReceiver::dataReceived(const char *data, size_t size)
{
	buffer_.append(string(data, size));

	std::list<std::string> lines;
    boost::iter_split(lines, buffer_, boost::first_finder(delimiter_));
	if (!lines.back().empty())
	{
		// no newline at end, keep the remaining data
		if (lines.size()<2)  // optimization
			return;
		buffer_=lines.back();
	}
	else
		// newline at end
		buffer_.clear();

	// remove last newline/remaining data
	lines.pop_back();

    BOOST_FOREACH(std::string token, lines)
    {    
        if (transport().disconnecting())
			return;
		if (token.length() > MAX_LENGTH)
		{
			lineLengthExceeded(token);
			return;
		}
		else if (!token.empty())
			lineReceived(token);
    }
	if (buffer_.length() > MAX_LENGTH)
	{
		lineLengthExceeded(buffer_);
		return;
	}
}

void LineOnlyReceiver::sendLine(const string &data)
{
	string s(data);
	s.append(delimiter_);
	transport().write(s.c_str(), s.length());
}

}}} // spiral::protocols::basic
