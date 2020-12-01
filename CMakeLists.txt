cmake_minimum_required(VERSION 3.17)
project(cpp-record)

set(CMAKE_CXX_STANDARD 20)

add_executable(cpp-record main.cpp)

add_executable(base-swap base/swap.cpp)

add_executable(server http/server.cpp)
target_link_libraries(server ws2_32)

# 生成动态链接库
add_library(test-lib-shared SHARED lib/test-lib.cpp)
add_executable(lib-test-shared lib/lib-test.cpp)
target_link_libraries(lib-test-shared test-lib-shared)

# 生成静态链接库
add_library(test-lib-static STATIC lib/test-lib.cpp)
add_executable(lib-test-static lib/lib-test.cpp)
target_link_libraries(lib-test-static test-lib-static)
