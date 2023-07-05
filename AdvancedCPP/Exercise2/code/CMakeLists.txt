cmake_minimum_required(VERSION 3.9)
project(VectorExercise)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -Wall -pedantic -g")

#add_compile_options(-DVECTOR_DEBUG)
add_executable(${PROJECT_NAME} main.cpp)
