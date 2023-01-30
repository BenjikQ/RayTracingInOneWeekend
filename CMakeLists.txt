cmake_minimum_required(VERSION 3.24)
project(RayTracingInOneWeekend
  VERSION 1.0.0
  LANGUAGES CXX)

include(CheckIPOSupported)

list(APPEND CMAKE_PREFIX_PATH ${CMAKE_CURRENT_BINARY_DIR})

set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(configured_files)
add_subdirectory(src)
