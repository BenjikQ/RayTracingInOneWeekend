#include <array>
#include <cstdint>
#include <string_view>

#include <range/v3/all.hpp>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb_image_write.h>

int main() {
    constexpr std::int32_t image_width{ 256 };
    constexpr std::int32_t image_height{ 256 };
    constexpr std::string_view image_path{ "image.png" };

    auto rows = ranges::view::iota(0, image_height);
    auto columns = ranges::view::iota(0, image_width);
    auto rng = ranges::view::cartesian_product(rows, columns);

    constexpr std::int32_t pixel_size_in_bytes{ 3 };
    std::array<std::uint8_t, image_height * image_width * pixel_size_in_bytes> pixels{};
    auto convert = [](double value) {
        return static_cast<std::uint8_t>(255.999 * value);
    };

    for (auto&& [row, col] : rng) {
        const auto r = convert(static_cast<double>(col) / (image_width - 1));
        const auto g = convert(static_cast<double>(image_height - row) / (image_height - 1));
        const auto b = convert(0.25);

        pixels[pixel_size_in_bytes * (image_width * row + col)] = r;
        pixels[pixel_size_in_bytes * (image_width * row + col) + 1] = g;
        pixels[pixel_size_in_bytes * (image_width * row + col) + 2] = b;
    }

    stbi_write_png(image_path.data(), image_width, image_height,
                   pixel_size_in_bytes, pixels.data(), pixel_size_in_bytes * image_width);

    return 0;
}
