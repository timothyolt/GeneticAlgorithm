cmake_minimum_required(VERSION 3.6)
project(geneticAlgoritm)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp sample.cpp sample.hpp)
add_executable(geneticAlgoritm ${SOURCE_FILES})