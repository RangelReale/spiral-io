link_directories (${SPIRAL_SOURCE_DIR}/lib/$(ConfigurationName))

add_executable(core-echoclient simpleclient.cpp)

target_link_libraries (core-echoclient spiral-core ${Boost_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT}) 


add_executable(core-echoserver simpleserver.cpp)

target_link_libraries (core-echoserver spiral-core ${Boost_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT}) 
