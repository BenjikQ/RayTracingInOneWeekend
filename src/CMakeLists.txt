find_package(range-v3)
find_package(stb)
find_package(indicators)

add_executable(raytracer main.cpp)
target_link_libraries(raytracer PRIVATE range-v3::range-v3 stb::stb indicators::indicators)
target_compile_features(raytracer PRIVATE cxx_std_20)
