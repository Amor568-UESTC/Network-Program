cmake_minimum_required(VERSION 3.10)

project(IOServer)

set(SOURCES IOServer.cpp wrap.cpp)

add_executable(IOServer ${SOURCES})