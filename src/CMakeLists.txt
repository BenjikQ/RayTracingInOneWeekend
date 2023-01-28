find_package(stb REQUIRED)
find_package(indicators REQUIRED)

add_library(raytracer
  core/camera.cpp core/camera.hpp
  core/world.cpp core/world.hpp

  geometry/hit.cpp geometry/hit.hpp
  geometry/point3.cpp geometry/point3.hpp
  geometry/ray.cpp geometry/ray.hpp
  geometry/vec3.cpp geometry/vec3.hpp

  materials/dielectric.cpp materials/dielectric.hpp
  materials/lambertian.cpp materials/lambertian.hpp
  materials/material.cpp materials/material.hpp
  materials/metal.cpp materials/metal.hpp

  shapes/shape.cpp shapes/shape.hpp
  shapes/sphere.cpp shapes/sphere.hpp

  utils/color.cpp utils/color.hpp
  utils/image.cpp utils/image.hpp
  utils/random.cpp utils/random.hpp)
target_link_libraries(raytracer
  PRIVATE
    stb::stb)
target_compile_features(raytracer PRIVATE cxx_std_20)
target_include_directories(raytracer PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

check_ipo_supported(RESULT result OUTPUT output)
if(result)
  set_property(TARGET raytracer PROPERTY INTERPROCEDURAL_OPTIMIZATION TRUE)
else()
  message(WARNING "IPO is not supported: ${output}")
endif()

add_executable(raytracer-bin
  main.cpp

  utils/progress_bar.cpp utils/progress_bar.hpp)
target_link_libraries(raytracer-bin
  PRIVATE
    raytracer
    indicators::indicators)
target_compile_features(raytracer-bin PRIVATE cxx_std_20)
set_target_properties(raytracer-bin
  PROPERTIES
    OUTPUT_NAME raytracer)
