#include "image.hpp"

#include <algorithm>
#include <cmath>
#include <cstdint>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb_image_write.h>

#include "utils/color.hpp"

Image::Image(int width, int height)
    : pixels_(width * height * channels)
    , width_{ width }
    , height_{ height }
{}

[[nodiscard]] constexpr std::uint8_t convert(double v) {
    return static_cast<std::uint8_t>(256 * std::clamp(v, 0.0, 0.999));
}

void Image::set_pixel(int row, int col, const Color& rgb, int samples_per_pixel) noexcept {
    auto [r, g, b] = rgb / samples_per_pixel;

    pixels_[channels * (width_ * row + col)] = convert(std::sqrt(r));
    pixels_[channels * (width_ * row + col) + 1] = convert(std::sqrt(g));
    pixels_[channels * (width_ * row + col) + 2] = convert(std::sqrt(b));
}

void Image::save(std::string_view path) const {
    stbi_flip_vertically_on_write(true);
    stbi_write_png(path.data(), width_, height_, channels, pixels_.data(), channels * width_);
}
