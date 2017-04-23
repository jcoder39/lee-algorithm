cmake_minimum_required(VERSION 3.7)
project(lee)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES src/main.cpp include/Grid.hpp include/Cell.hpp include/Lee.hpp include/Settings.hpp include/Strategy.hpp)
add_executable(lee ${SOURCE_FILES})