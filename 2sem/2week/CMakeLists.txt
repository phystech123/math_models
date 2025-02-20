cmake_minimum_required (VERSION 3.22)
     
project(project)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++23")

# add_library(lib ../../5week/common_fractions/fraction.h ../../5week/common_fractions/fraction.cpp)
add_executable(main main.cpp)
# target_link_libraries(main PRIVATE ../../lib_prog_2024/boost1_87_0)
# target_include_directories(main PRIVATE ../../../lib_prog_2024/boost1_87_0)