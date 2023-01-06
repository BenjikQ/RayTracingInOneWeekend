#ifndef RAYTRACINGINONEWEEKEND_IMAGE_HPP
#define RAYTRACINGINONEWEEKEND_IMAGE_HPP

#include <cstdint>
#include <string_view>
#include <vector>

#include "vec3.hpp"

class Image {
    static constexpr std::int32_t channels{ 3 };
    std::vector<std::uint8_t> pixels_;
    std::int32_t width_;
    std::int32_t height_;

public:
    Image(std::int32_t width, std::int32_t height);

    void set_pixel(std::int32_t row, std::int32_t col, const Color& rgb, int samples_per_pixel) noexcept;
    void save(std::string_view path) const;
};

#endif //RAYTRACINGINONEWEEKEND_IMAGE_HPP
