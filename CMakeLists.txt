cmake_minimum_required(VERSION 3.1)

project(application VERSION 1.0 LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set (CMAKE_CXX_STANDARD 17)
set (CMAKE_CXX_STANDARD_REQUIRED ON)
set (CMAKE_CXX_EXTENSIONS OFF)

if (NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

add_library(linalg INTERFACE)
add_library(linalg::linalg ALIAS linalg)

target_compile_features(linalg INTERFACE cxx_std_17)
target_include_directories(linalg INTERFACE 
  $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include>
)

if (DEMO)
  add_subdirectory(demo)
endif()