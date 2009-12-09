cmake_minimum_required(VERSION 2.6)
project(SPIRAL)
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set (CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)

include(FindBoost)
include(FindThreads)

set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_MULTITHREAD ON)

find_package(Boost 1.37 REQUIRED
             COMPONENTS system date_time thread regex program_options)
if(NOT Boost_FOUND)
  message(FATAL_ERROR "Boost C++ libraries not found.  Please install or try setting BOOST_ROOT")
endif(NOT Boost_FOUND)
include_directories( ${Boost_INCLUDE_DIR} )
link_directories( ${Boost_LIBRARY_DIRS} )

include_directories (${SPIRAL_SOURCE_DIR}/spiral-core/include) 
#include_directories (${SPIRAL_SOURCE_DIR}/dependencies/boost) 

add_subdirectory(spiral-core)

