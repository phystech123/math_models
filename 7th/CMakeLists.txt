cmake_minimum_required (VERSION 3.22)
     
project(DIFF_SOLVER)
add_library(equation equation.hpp equation.cpp)
add_library(solver solving.hpp solving.cpp)
add_executable(main main.cpp)
target_link_libraries(main PRIVATE equation solver)