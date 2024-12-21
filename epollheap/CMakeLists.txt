cmake_minimum_required(VERSION 3.10)

project(epollheap)

set(SOURCES epollheap.cpp wrap.cpp)

add_executable(epollheap ${SOURCES})