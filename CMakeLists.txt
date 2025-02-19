cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-psabi")

project(shell)

include(cmake/flags.cmake)
include(cmake/dependencies.cmake)

option(RUN_TESTS "Creates and runs unit tests for the project" OFF)

if(RUN_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()

add_subdirectory(examples)

include_directories(inc)
file(GLOB_RECURSE SOURCES "src/*.cpp")

add_library(${PROJECT_NAME} ${SOURCES})
IF(NOT Boost_FOUND)
    add_dependencies(${PROJECT_NAME} libboost)
ENDIF()
target_link_libraries(${PROJECT_NAME} boost_filesystem)
