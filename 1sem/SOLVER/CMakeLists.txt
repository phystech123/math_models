cmake_minimum_required (VERSION 3.22)
     
project(SOLVER)
 
add_library(solver solver.hpp solver.cpp)
add_library(source equations.hpp equations.cpp)

add_executable(main main.cpp)
target_link_libraries(main PRIVATE solver)
target_link_libraries(main PRIVATE source)