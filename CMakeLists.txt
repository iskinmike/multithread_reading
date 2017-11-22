cmake_minimum_required(VERSION 3.5.1)

project(multithread_reading)

set(SOURCES mutlithread_reading.cpp StatAggregator.cpp StatGatherer.cpp StatElement.cpp)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -pthread")

include_directories("./" "./rapidjson/include/")

add_executable(gatherer ${SOURCES})

