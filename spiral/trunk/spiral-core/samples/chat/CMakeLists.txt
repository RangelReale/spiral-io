link_directories (${SPIRAL_SOURCE_DIR}/lib/$(ConfigurationName))

add_executable(core-chat chatserver.cpp)

target_link_libraries (core-chat spiral-core ${Boost_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT}) 
