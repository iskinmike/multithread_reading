cmake_minimum_required(VERSION 3.5.1)

project(gatherer)

set(SOURCES multithread_reading.cpp StatAggregator.cpp StatGatherer.cpp StatElement.cpp)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -pthread")

include_directories("./" "./rapidjson/include/")

add_executable(gatherer ${SOURCES})

