cmake_minimum_required(VERSION 3.22)

project(astar)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED true)

include_directories(include)

add_executable(astar Main.cpp)