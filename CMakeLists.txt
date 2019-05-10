cmake_minimum_required(VERSION 2.8.7)
project(algorithm CXX)

include_directories(
    /usr/include
    src/
)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wfatal-errors -std=c++11 -g")
file(GLOB_RECURSE SOURCES
    src/The_Triangle.cpp # Input filename to compile
)

add_executable(${CMAKE_PROJECT_NAME} "${SOURCES}")

SET_TARGET_PROPERTIES (
    ${CMAKE_PROJECT_NAME}
    PROPERTIES LINKER_LANGUAGE CXX
)

