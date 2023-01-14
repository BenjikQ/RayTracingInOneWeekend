#ifndef RAYTRACINGINONEWEEKEND_UTILS_IMAGE_HPP
#define RAYTRACINGINONEWEEKEND_UTILS_IMAGE_HPP

#include <string_view>
#include <vector>

struct Color;

class Image {
    static constexpr int channels{ 3 };
    std::vector<std::uint8_t> pixels_;
    int width_;
    int height_;

public:
    Image(int width, int height);

    void set_pixel(int row, int col, const Color& rgb, int samples_per_pixel) noexcept;
    void save(std::string_view path) const;
};

#endif //RAYTRACINGINONEWEEKEND_UTILS_IMAGE_HPP
