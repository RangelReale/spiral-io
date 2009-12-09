#include "spiral/Exception.h"
#include <typeinfo>
#include <assert.h>
#include <string.h>

namespace spiral {

Exception::Exception(const std::string& msg) throw() : message(msg) {
    //QPID_LOG_IF(debug, !msg.empty(), "Exception constructed: " << message);
}

Exception::~Exception() throw() {}

std::string Exception::getPrefix() const { return ""; }

std::string Exception::getMessage() const { return message; }

const char* Exception::what() const throw() {
    // Construct the what string the first time it is needed.
    if (whatStr.empty()) {
        whatStr = getPrefix();
        if (!whatStr.empty()) whatStr +=  ": ";
        whatStr += message;
    }
    return whatStr.c_str();
}

/*
ClosedException::ClosedException(const std::string& msg)
  : Exception(msg) {}

std::string ClosedException::getPrefix() const { return "Closed"; }
*/

} // namespace spiral
