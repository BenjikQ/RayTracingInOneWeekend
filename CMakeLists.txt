cmake_minimum_required(VERSION 3.24)
project(RayTracingInOneWeekend
  VERSION 0.1.0
  LANGUAGES CXX)

set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(raytracer main.cpp)
target_compile_features(raytracer PRIVATE cxx_std_20)
