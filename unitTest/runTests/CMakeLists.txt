cmake_minimum_required(VERSION 3.5)
project(runTests CXX)

set(CMAKE_CXX_STANDARD 14)

include_directories("${gtest_SOURCE_DIR}/include" ${gtest_SOURCE_DIR})
set(BUILD_GMOCK OFF)
set(BUILD_GTEST ON)
set(BUILD_SHARED_LIBS ON)

set(EIGEN3_INCLUDE_DIR /usr/include/eigen3 )
include_directories ( ${EIGEN3_INCLUDE_DIR} )

add_executable(DissimRunTests Tests.cpp)
target_link_libraries(DissimRunTests gtest gtest_main)
target_link_libraries(DissimRunTests dissim)

