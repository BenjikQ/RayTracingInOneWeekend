find_package(range-v3)
find_package(stb)
find_package(indicators)

add_library(raytracer
  vec3.hpp vec3.cpp
  image.hpp image.cpp)
target_link_libraries(raytracer
  PRIVATE
    stb::stb)
target_compile_features(raytracer PRIVATE cxx_std_20)

add_executable(raytracer-bin main.cpp)
target_link_libraries(raytracer-bin
  PRIVATE
    raytracer
    range-v3::range-v3
    indicators::indicators)
target_compile_features(raytracer-bin PRIVATE cxx_std_20)
set_target_properties(raytracer-bin
  PROPERTIES
    OUTPUT_NAME raytracer)
