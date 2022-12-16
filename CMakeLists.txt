cmake_minimum_required(VERSION 3.2)

project(CPP_COURSE)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG}")

add_subdirectory(bank_project)

add_executable(Exercise_09 exercise_09.cpp)
add_executable(Exercise_10 exercise_10.cpp)
add_executable(Exercise_11 exercise_11.cpp)
add_executable(Exercise_12 exercise_12.cpp)
add_executable(Exercise_13 exercise_13.cpp)
add_executable(Exercise_14 exercise_14.cpp)
add_executable(Exercise_15 exercise_15.cpp)