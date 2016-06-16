cmake_minimum_required(VERSION 2.8.9)
project(polarview-aggregator)
find_package (Threads)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11 -Werror -Wall")

file(GLOB SOURCES "source/include/*.hpp")
file(GLOB SOURCES_GTEST "../adt/source/include/ADT_Base.hpp"
                        "../adt/source/include/Angle.hpp"
                        "../adt/source/include/Length.hpp"
                        "../adt/source/include/Translation.hpp"
                        "../adt/source/include/Coordinate.hpp"
                        "../adt/source/src/Angle.cpp"
                        "../adt/source/src/Length.cpp"
                        "../adt/source/src/Translation.cpp"
                        "../adt/source/src/Coordinate.cpp"
                        "../polarview/source/include/DistanceReading.hpp"
                        "../polarview/source/src/DistanceReading.cpp"
                        "../polarview/source/include/PolarView.hpp"
                        "../polarview/source/include/MapPolarView.hpp"
                        "../polarview/source/src/MapPolarView.cpp"
                        "../sensorInterfaces/source/include/Sensor.hpp"
                        "../sensorInterfaces/source/src/Sensor.cpp"
                        "source/src/*.cpp"
                        "source/include/*.hpp"
                        "test/*.cpp"
                        "test/*.hpp")

include_directories(
    ../polarview/source/include
   ../sensorInterfaces/source/include
   ../adt/source/include
  ../deps/gtest-1.7.0/include
  ../deps/gtest-1.7.0)

link_directories(../deps/gtest-1.7.0/src ../polarview/source/src ../sensorInterfaces/source/src ../adt/source/src)
ADD_LIBRARY(gtest ../deps/gtest-1.7.0/src/gtest-all.cc)
ADD_LIBRARY(gtest_main ../deps/gtest-1.7.0/src/gtest_main.cc)

add_executable(polarview-aggregator_test ${GTEST} ${SOURCES_GTEST})
target_link_libraries(polarview-aggregator_test gtest gtest_main ${CMAKE_THREAD_LIBS_INIT})
