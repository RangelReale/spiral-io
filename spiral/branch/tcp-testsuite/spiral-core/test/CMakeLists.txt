link_directories (${SPIRAL_SOURCE_DIR}/lib/$(ConfigurationName))

add_executable(test_suite test_tcp.cpp)

target_link_libraries (test_suite spiral-core ${Boost_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT}) 
