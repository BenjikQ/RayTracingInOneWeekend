find_package(range-v3)
find_package(stb)

add_executable(raytracer main.cpp)
target_link_libraries(raytracer PRIVATE range-v3::range-v3 stb::stb)
target_compile_features(raytracer PRIVATE cxx_std_20)
