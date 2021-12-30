cmake_minimum_required(VERSION 3.7.2)
project(SemestralkaServer)

set(CMAKE_CXX_STANDARD 17)

add_executable(SemestralkaServer main.cpp Sources/Application.cpp Headers/Application.h Sources/User.cpp Headers/User.h)

target_link_libraries(SemestralkaServer pthread)