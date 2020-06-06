project(server)

cmake_minimum_required(VERSION 3.5)
SET(CMAKE_BUILD_TYPE DEBUG)
add_definitions(-std=c++11)

include_directories(include)
add_library(server 
src/EventLoop.cc
src/Channel.cc
src/Epoll.cc
src/Wakeuper.cc
src/Timestamp.cc
src/TimerQueue.cc
)

add_executable(test01 test/test01.cc)
target_link_libraries( test01 -lpthread server)

add_executable(test02 test/test02.cc)
target_link_libraries( test02 -lpthread server)

add_executable(test03 test/test03.cc)
target_link_libraries( test03 -lpthread server)

add_executable(test04 test/test04.cc)
target_link_libraries( test04 -lpthread server)

add_executable(test05 test/test05.cc)
target_link_libraries(test05 -lpthread server)

add_executable(test06 test/test06.cc)
target_link_libraries(test06 -lpthread server)

add_executable(test07 test/test07.cc)
target_link_libraries(test07 -lpthread server)