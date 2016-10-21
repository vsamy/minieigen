# Version minimum
cmake_minimum_required(VERSION 2.8)
include(cmake/base.cmake)
include(cmake/eigen.cmake)
include(cmake/boost.cmake)

set(PROJECT_NAME minieigen)
set(PROJECT_DESCRIPTION "...")
set(PROJECT_URL "")

SET(CXX_DISABLE_WERROR True)

project(${PROJECT_NAME} CXX)
SETUP_PROJECT()

set(BOOST_REQUIRED 1.48)
set(BOOST_COMPONENTS python)
SEARCH_FOR_BOOST()
SEARCH_FOR_EIGEN()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -std=c++14 -pedantic")

add_subdirectory(src)

SETUP_PROJECT_FINALIZE()