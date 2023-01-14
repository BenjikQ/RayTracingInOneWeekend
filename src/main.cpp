#include <indicators/cursor_control.hpp>

#include "core/camera.hpp"
#include "core/world.hpp"
#include "geometry/point3.hpp"
#include "geometry/ray.hpp"
#include "materials/lambertian.hpp"
#include "materials/material.hpp"
#include "materials/metal.hpp"
#include "shapes/sphere.hpp"
#include "utils/color.hpp"
#include "utils/image.hpp"
#include "utils/progress_bar.hpp"
#include "utils/random.hpp"

int main() {
    constexpr double aspect_ratio{ 16.0 / 9 };
    constexpr int image_width{ 400 };
    constexpr auto image_height = static_cast<int>(image_width / aspect_ratio);
    constexpr auto samples_per_pixel = 100;
    constexpr auto max_depth = 50;

    indicators::show_console_cursor(false);
    auto bar = create_progress_bar(image_height);

    Image image{ image_width, image_height };

    auto ground = create_material<Lambertian>(Color{ 0.8, 0.8, 0.0 });
    auto center = create_material<Lambertian>(Color{ 0.7, 0.3, 0.3 });
    auto left = create_material<Metal>(Color{ 0.8, 0.8, 0.8 }, 0.3);
    auto right = create_material<Metal>(Color{ 0.8, 0.6, 0.2 }, 1.0);

    World world{
        Sphere{ Point3{ 0, -100.5, 0 }, 100, *ground },
        Sphere{ Point3{ 0, 0, -1 },     0.5, *center },
        Sphere{ Point3{ -1, 0, -1 },    0.5, *left },
        Sphere{ Point3{ 1, 0, -1 },     0.5, *right }
    };

    Camera camera{};

    auto random_double = []() { return random(0.0, 1.0); };

    for (int row = image_height - 1; row >= 0; --row) {
        for (int col = 0; col < image_width; ++col) {
            Color pixel_color{};
            for (int sample = 0; sample < samples_per_pixel; ++sample) {
                const double u{ (static_cast<double>(col) + random_double()) / (image_width - 1) };
                const double v{ (static_cast<double>(row) + random_double()) / (image_height - 1) };
                const Ray ray{ camera.ray(u, v) };
                pixel_color += world.ray_color(ray, max_depth);
            }
            image.set_pixel(row, col, pixel_color, samples_per_pixel);

            if (col == 0) {
                bar.tick();
            }
        }
    }

    image.save("image.png");
    indicators::show_console_cursor(true);

    return 0;
}
