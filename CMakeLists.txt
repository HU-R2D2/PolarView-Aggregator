cmake_minimum_required(VERSION 2.8.9)
project(polarview-aggregator)
find_package (Threads)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11 -Werror -Wall")

file(GLOB SOURCES "source/include/*.hpp")
file(GLOB SOURCES_GTEST
                        "../polarview/source/include/DistanceReading.hpp"
                        "../polarview/source/include/PolarView.hpp"
                        "../polarview/source/include/MapPolarView.hpp"
                        "source/src/*.cpp"
                        "source/include/*.hpp"
                        "test/*.cpp"
                        "test/*.hpp")

include_directories(
   ../adt/source/include
  ../deps/gtest-1.7.0/include
  ../deps/gtest-1.7.0)

link_directories(../deps/gtest-1.7.0/src)
ADD_LIBRARY(gtest ../deps/gtest-1.7.0/src/gtest-all.cc)
ADD_LIBRARY(gtest_main ../deps/gtest-1.7.0/src/gtest_main.cc)

add_executable(polarview-aggregator_test ${GTEST} ${SOURCES_GTEST})
target_link_libraries(polarview-aggregator_test gtest gtest_main ${CMAKE_THREAD_LIBS_INIT})
