find_package(stb REQUIRED)
find_package(indicators REQUIRED)
find_package(pcg-cpp REQUIRED)

add_library(raytracer
  vec3.hpp vec3.cpp
  image.hpp image.cpp
  ray.cpp ray.hpp
  shape.cpp shape.hpp
  sphere.cpp sphere.hpp
  world.cpp world.hpp
  camera.cpp camera.hpp
  random.cpp random.hpp
  material.cpp material.hpp
  lambertian.cpp lambertian.hpp
  metal.cpp metal.hpp)
target_link_libraries(raytracer
  PRIVATE
    stb::stb
    pcg-cpp::pcg-cpp)
target_compile_features(raytracer PRIVATE cxx_std_20)

add_executable(raytracer-bin main.cpp)
target_link_libraries(raytracer-bin
  PRIVATE
    raytracer
    indicators::indicators)
target_compile_features(raytracer-bin PRIVATE cxx_std_20)
set_target_properties(raytracer-bin
  PROPERTIES
    OUTPUT_NAME raytracer)
