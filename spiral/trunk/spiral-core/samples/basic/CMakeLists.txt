link_directories (${SPIRAL_SOURCE_DIR}/lib/$(ConfigurationName))

add_executable(basic main.cpp)

target_link_libraries (basic spiral-core ${Boost_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT}) 
