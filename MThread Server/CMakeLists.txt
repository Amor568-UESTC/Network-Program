cmake_minimum_required(VERSION 3.10)

project(mtServer)

set(SOURCES mtServer.cpp wrap.cpp)

add_executable(mtServer ${SOURCES})