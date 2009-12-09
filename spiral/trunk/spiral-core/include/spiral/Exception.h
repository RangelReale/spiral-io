#ifndef _SPIRAL_EXCEPTION_H__
#define _SPIRAL_EXCEPTION_H__

#include <string>

namespace spiral {

class Exception : public std::exception
{
  public:
    explicit Exception(const std::string& message=std::string()) throw();
    virtual ~Exception() throw();
    virtual const char* what() const throw(); // prefix: message
    virtual std::string getMessage() const; // Unprefixed message
    virtual std::string getPrefix() const;  // Prefix

  private:
    std::string message;
    mutable std::string whatStr;
};

struct RuntimeError : public Exception {
	RuntimeError(const std::string& msg="") : Exception(msg) {}
};

struct ValueError : public Exception {
	ValueError(const std::string& msg="") : Exception(msg) {}
};

} // spiral

#endif // _SPIRAL_EXCEPTION_H__
