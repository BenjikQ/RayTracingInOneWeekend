#include "image.hpp"

#include <algorithm>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb_image_write.h>

Image::Image(std::int32_t width, std::int32_t height)
    : pixels_(width * height * pixel_size_in_bytes)
    , width_{ width }
    , height_{ height }
{}

[[nodiscard]] constexpr std::uint8_t convert(double v) {
    return static_cast<std::uint8_t>(256 * std::clamp(v, 0.0, 0.999));
}

void Image::set_pixel(std::int32_t row, std::int32_t col, const Color& rgb, int samples_per_pixel) noexcept {
    auto [r, g, b] = rgb;

    auto scale = 1.0 / samples_per_pixel;
    r *= scale;
    g *= scale;
    b *= scale;

    pixels_[pixel_size_in_bytes * (width_ * row + col)] = convert(r);
    pixels_[pixel_size_in_bytes * (width_ * row + col) + 1] = convert(g);
    pixels_[pixel_size_in_bytes * (width_ * row + col) + 2] = convert(b);
}

void Image::save(std::string_view path) const {
    stbi_write_png(path.data(), width_, height_,
                   pixel_size_in_bytes, pixels_.data(), pixel_size_in_bytes * width_);
}
