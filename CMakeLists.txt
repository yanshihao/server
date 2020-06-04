project(server)

cmake_minimum_required(VERSION 3.5)
SET(CMAKE_BUILD_TYPE DEBUG)
add_definitions(-std=c++11)

include_directories(include)
add_library(server 
src/EventLoop.cc
src/Channel.cc
src/Epoll.cc
)

add_executable(test01 test/test01.cc)
target_link_libraries( test01 -lpthread server)

add_executable(test02 test/test02.cc)
target_link_libraries( test02 -lpthread server)

add_executable(test03 test/test03.cc)
target_link_libraries( test03 -lpthread server)