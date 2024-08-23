cmake_minimum_required(VERSION 3.22)

project(glicko VERSION 0.3.2 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(glicko main.cpp glicko.h)
add_compile_definitions(GLICKO_VERSION="${CMAKE_PROJECT_VERSION}")
