cmake_minimum_required(VERSION 2.8.3)
project(v_repExtLanelets)

find_package(Boost REQUIRED COMPONENTS system)

set(VREP_ROOT ~/V-REP_PRO_EDU_V3_4_0_Linux)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/modules/")

find_package(VREP REQUIRED)
find_package(geodesy REQUIRED)

SET(CMAKE_CXX_FLAGS "-std=c++11 -O2 -g -Wall ${CMAKE_CXX_FLAGS}")
