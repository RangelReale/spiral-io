set(SOURCES src/Exception.cpp src/Options.cpp include/spiral/Exception.h include/spiral/memory.h include/spiral/Msg.h include/spiral/Options.h include/spiral/sys/IntegerTypes.h )

# internet
set(SOURCES ${SOURCES} include/spiral/internet/Error.h include/spiral/internet/address/IPv4Address.h )

# internet/interfaces
set(SOURCES ${SOURCES} include/spiral/internet/interfaces/IAddress.h include/spiral/internet/interfaces/IConnector.h include/spiral/internet/interfaces/IDelayedCall.h include/spiral/internet/interfaces/IListeningPort.h include/spiral/internet/interfaces/IProtocol.h include/spiral/internet/interfaces/IProtocolFactory.h include/spiral/internet/interfaces/IReactorCore.h include/spiral/internet/interfaces/IReactorTCP.h include/spiral/internet/interfaces/IReactorTime.h include/spiral/internet/interfaces/ITCPTransport.h include/spiral/internet/interfaces/ITransport.h include/spiral/internet/interfaces/IHalfCloseableProtocol.h include/spiral/internet/interfaces/IReactor.h )

# internet/base
set(SOURCES ${SOURCES} src/internet/base/BaseConnector.cpp src/internet/base/DelayedCall.cpp src/internet/base/ReactorBase.cpp include/spiral/internet/base/BaseConnector.h include/spiral/internet/base/DelayedCall.h include/spiral/internet/base/ReactorBase.h include/spiral/internet/base/Callable.h )

# internet/boostreactor
set(SOURCES ${SOURCES} src/internet/boostreactor/BoostReactor.cpp src/internet/boostreactor/Client.cpp src/internet/boostreactor/Connection.cpp src/internet/boostreactor/Connector.cpp src/internet/boostreactor/Port.cpp src/internet/boostreactor/Server.cpp src/internet/boostreactor/DelayedCall.cpp include/spiral/internet/boostreactor/BoostReactor.h include/spiral/internet/boostreactor/Client.h include/spiral/internet/boostreactor/Connection.h include/spiral/internet/boostreactor/Connector.h include/spiral/internet/boostreactor/Port.h include/spiral/internet/boostreactor/Server.h include/spiral/internet/boostreactor/SocketCloser.h include/spiral/internet/boostreactor/DelayedCall.h )

# internet/protocol
set(SOURCES ${SOURCES} src/internet/protocol/ReconnectingClientFactory.cpp include/spiral/internet/protocol/BaseProtocol.h include/spiral/internet/protocol/ClientFactory.h include/spiral/internet/protocol/Protocol.h include/spiral/internet/protocol/ProtocolFactory.h include/spiral/internet/protocol/ReconnectingClientFactory.h include/spiral/internet/protocol/ServerFactory.h )

# log
set(SOURCES ${SOURCES} src/log/Logger.cpp src/log/Options.cpp src/log/OstreamOutput.cpp src/log/Selector.cpp src/log/Statement.cpp include/spiral/log/Helpers.h include/spiral/log/Logger.h include/spiral/log/Options.h include/spiral/log/OstreamOutput.h include/spiral/log/Selector.h include/spiral/log/SinkOptions.h include/spiral/log/Statement.h )

# application
set(SOURCES ${SOURCES} src/application/Application.cpp include/spiral/application/Application.h )

# protocols/basic
set(SOURCES ${SOURCES} src/protocols/basic/LineOnlyReceiver.cpp src/protocols/basic/LineReceiver.cpp include/spiral/protocols/basic/LineOnlyReceiver.h include/spiral/protocols/basic/LineReceiver.h )

IF(UNIX)
	set(SOURCES ${SOURCES} src/log/posix/SinkOptions.cpp include/spiral/log/posix/SinkOptions.h include/spiral/sys/posix/IntegerTypes.h )
ELSE(UNIX)
  IF(WIN32)
	set(SOURCES ${SOURCES} src/log/windows/SinkOptions.cpp include/spiral/log/windows/SinkOptions.h include/spiral/sys/windows/IntegerTypes.h)
  ENDIF(WIN32)
ENDIF(UNIX)


add_library(spiral-core ${SOURCES})





add_subdirectory(samples)