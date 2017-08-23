cmake_minimum_required(VERSION 2.8.3)
project(v_repExtLanelets)

SET(CMAKE_CXX_FLAGS "-std=c++11 -O2 -g -Wall ${CMAKE_CXX_FLAGS}")

find_package(Boost REQUIRED COMPONENTS system)

set(VREP_ROOT ~/V-REP_PRO_EDU_V3_4_0_Linux)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/modules/")

find_package(VREP REQUIRED)
find_package(geodesy REQUIRED)
find_package(Qt5Widgets)

qt5_wrap_cpp(MyProjectLib_hdr_moc ${CMAKE_SOURCE_DIR}/include/laneletsdialog.h)
qt5_wrap_ui (MyProjectLib_ui_moc ${PROJECT_SOURCE_DIR}/gui/laneletsdialog.ui)

include_directories(
  ${CMAKE_SOURCE_DIR}/include
  lib/liblanelet/installs/include
  ${VREP_INCLUDE}
)

set (SOURCES
  src/lanelet2obj.cpp
  src/laneletsdialog.cpp
  src/triangulate.cpp
  src/v_repExtLanelets.cpp
)

set (HEADERS
  include/laneletsdialog.h
  include/triangulate.h
  include/v_repExtLanelets.h
)

add_library(v_repExtLanelets SHARED 
  ${HEADERS}
  ${SOURCES}
  ${MyProjectLib_hdr_moc}
  ${MyProjectLib_ui_moc}
)
target_link_libraries(v_repExtLanelets 
  ${PROJECT_SOURCE_DIR}/lib/liblanelet/installs/lib/MRT/libLanelet.so
  Qt5::Widgets
)
