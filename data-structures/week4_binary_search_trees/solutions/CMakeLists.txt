cmake_minimum_required(VERSION 3.17)
project(solutions)

set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "-pipe -O0 -lm")

add_executable(solution rope.cpp)