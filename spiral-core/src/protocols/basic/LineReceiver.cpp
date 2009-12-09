#include "spiral/protocols/basic/LineReceiver.h"

namespace spiral {
namespace protocols {
namespace basic {

void LineReceiver::dataReceived(const char *data, size_t size)
{
	buffer_.append(string(data, size));

	while (line_mode_)
	{
		size_t found;
		if ((found=buffer_.find(delimiter_))!=string::npos)
		{
			string s(buffer_.substr(0, found));
			buffer_.erase(0, found+delimiter_.length());

			if (transport().disconnecting())
				return;
			if (s.length() > MAX_LENGTH)
			{
				lineLengthExceeded(s);
				return;
			}
			else if (!s.empty())
				lineReceived(s);
		} else
			break;
	}
	if (!line_mode_)
		if (!buffer_.empty())
		{
			string b(buffer_);
			buffer_.clear();
			rawDataReceived(b.c_str(), b.length());
		}
}

void LineReceiver::sendLine(const string &data)
{
	string s(data);
	s.append(delimiter_);
	transport().write(s.c_str(), s.length());
}

}}} // spiral::protocols::basic
