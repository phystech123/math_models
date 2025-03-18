cmake_minimum_required (VERSION 3.22)
     
project(project)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++23")

add_executable(main main.cpp)