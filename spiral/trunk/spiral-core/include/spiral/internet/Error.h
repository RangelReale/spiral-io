#ifndef _SPIRAL_INTERNET_ERROR_H__
#define _SPIRAL_INTERNET_ERROR_H__

#include "spiral/Exception.h"

namespace spiral {
namespace internet {
namespace error {

struct BindError : public Exception {
	BindError(const std::string& msg="") : Exception(msg) {}
};

struct CannotListenError : public BindError {
	CannotListenError(const std::string& msg="") : BindError(msg) {}
};

struct ConnectInProgressError : public Exception {
	ConnectInProgressError(const std::string& msg="") : Exception(msg) {}
};

// Connection errors

struct ConnectError : public Exception {
	ConnectError(const std::string& msg="") : Exception(msg) {}
};

struct ConnectBindError : public ConnectError {
	ConnectBindError(const std::string& msg="") : ConnectError(msg) {}
};

struct UnknownHostError : public ConnectError {
	UnknownHostError(const std::string& msg="") : ConnectError(msg) {}
};

struct NoRouteError : public ConnectError {
	NoRouteError(const std::string& msg="") : ConnectError(msg) {}
};

struct ConnectionRefusedError : public ConnectError {
	ConnectionRefusedError(const std::string& msg="") : ConnectError(msg) {}
};

struct TCPTimedOutError : public ConnectError {
	TCPTimedOutError(const std::string& msg="") : ConnectError(msg) {}
};

struct BadFileError : public ConnectError {
	BadFileError(const std::string& msg="") : ConnectError(msg) {}
};

struct ServiceNameUnknownError : public ConnectError {
	ServiceNameUnknownError(const std::string& msg="") : ConnectError(msg) {}
};

struct UserError : public ConnectError {
	UserError(const std::string& msg="") : ConnectError(msg) {}
};

struct TimeoutError : public UserError {
	TimeoutError(const std::string& msg="") : UserError(msg) {}
};

struct SSLError : public ConnectError {
	SSLError(const std::string& msg="") : ConnectError(msg) {}
};

struct VerifyError : public Exception {
	VerifyError(const std::string& msg="") : Exception(msg) {}
};

struct PeerVerifyError : public VerifyError {
	PeerVerifyError(const std::string& msg="") : VerifyError(msg) {}
};

struct CertificateError : public Exception {
	CertificateError(const std::string& msg="") : Exception(msg) {}
};

struct ConnectionClosed : public Exception {
	ConnectionClosed(const std::string& msg="") : Exception(msg) {}
};

struct ConnectionLost : public ConnectionClosed {
	ConnectionLost(const std::string& msg="") : ConnectionClosed(msg) {}
};

struct ConnectionDone : public ConnectionClosed {
	ConnectionDone(const std::string& msg="") : ConnectionClosed(msg) {}
};

struct ConnectionFdescWentAway : public ConnectionLost {
	ConnectionFdescWentAway(const std::string& msg="") : ConnectionLost(msg) {}
};

struct AlreadyCalled : public ValueError {
	AlreadyCalled(const std::string& msg="") : ValueError(msg) {}
};

struct AlreadyCancelled : public ValueError {
	AlreadyCancelled(const std::string& msg="") : ValueError(msg) {}
};

struct ProcessDone : public ConnectionDone {
	ProcessDone(const std::string& msg="") : ConnectionDone(msg) {}
};

struct ProcessTerminated : public ConnectionLost {
	ProcessTerminated(const std::string& msg="") : ConnectionLost(msg) {}
};

struct ProcessExitedAlready : public Exception {
	ProcessExitedAlready(const std::string& msg="") : Exception(msg) {}
};


struct NotConnectingError : public RuntimeError {
	NotConnectingError(const std::string& msg="") : RuntimeError(msg) {}
};

struct NotListeningError : public RuntimeError {
	NotListeningError(const std::string& msg="") : RuntimeError(msg) {}
};

struct ReactorNotRunning : public RuntimeError {
	ReactorNotRunning(const std::string& msg="") : RuntimeError(msg) {}
};

struct ReactorAlreadyRunning : public RuntimeError {
	ReactorAlreadyRunning(const std::string& msg="") : RuntimeError(msg) {}
};


}}} // spiral::internet::error

#endif // _SPIRAL_INTERNET_ERROR_H__
