cmake_minimum_required(VERSION 3.10)

project(client)

set(SOURCES client.cpp wrap.cpp)

add_executable(client ${SOURCES})