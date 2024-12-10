cmake_minimum_required(VERSION 3.10)

project(pollServer)

set(SOURCES pollServer.cpp wrap.cpp)

add_executable(pollServer ${SOURCES})