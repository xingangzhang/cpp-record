cmake_minimum_required(VERSION 3.15)
project(cpp-record)

set(CMAKE_CXX_STANDARD 17)

add_executable(cpp-record main.cpp)

add_executable(server http/server.cpp)
target_link_libraries(server ws2_32)