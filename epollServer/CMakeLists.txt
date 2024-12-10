cmake_minimum_required(VERSION 3.10)

project(epollServer)

set(SOURCES epollServer.cpp wrap.cpp)

add_executable(epollServer ${SOURCES})