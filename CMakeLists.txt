cmake_minimum_required(VERSION 3.22)

project(glicko LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(glicko main.cpp glicko.h)
