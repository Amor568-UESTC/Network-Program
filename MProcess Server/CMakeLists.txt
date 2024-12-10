cmake_minimum_required(VERSION 3.10)

project(mpServer)

set(SOURCES mpServer.cpp wrap.cpp)

add_executable(mpServer ${SOURCES})