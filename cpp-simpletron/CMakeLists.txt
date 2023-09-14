cmake_minimum_required(VERSION 3.21.4)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED true)

project(Simpletron VERSION 1.0)

file(GLOB SOURCES "src/*.cpp")
add_executable(Simpletron ${SOURCES})