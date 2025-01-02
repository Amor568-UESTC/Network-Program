cmake_minimum_required(VERSION 3.10)

project(domain_socket)

set(SOURCES domain_socket.cpp wrap.cpp)

add_executable(domain_socket ${SOURCES})