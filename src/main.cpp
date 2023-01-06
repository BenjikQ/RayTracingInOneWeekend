#include <cstdint>
#include <limits>
#include <vector>

#include <indicators/cursor_control.hpp>
#include <indicators/progress_bar.hpp>

#include "camera.hpp"
#include "image.hpp"
#include "random.hpp"
#include "ray.hpp"
#include "sphere.hpp"
#include "vec3.hpp"
#include "world.hpp"

[[nodiscard]] indicators::ProgressBar create_progress_bar(std::int32_t max_progress) noexcept {
    using namespace indicators;

    return ProgressBar{
        option::BarWidth{ 50 },
        option::Start{ "[" },
        option::Fill{ "=" },
        option::Lead{ ">" },
        option::Remainder{ " " },
        option::End{ "]" },
        option::ForegroundColor{ indicators::Color::green },
        option::ShowElapsedTime{ true },
        option::ShowPercentage{ true },
        option::MaxProgress{ max_progress },
        option::FontStyles{std::vector<FontStyle>{ FontStyle::bold } },
    };
}

[[nodiscard]] Color ray_color(const Ray& ray, const World& world, int depth) {
    static constexpr auto infinity = std::numeric_limits<double>::infinity();

    if (depth <= 0) {
        return {};
    }

    if (auto hit = world.hit(ray, 0.001, infinity)) {
        Point3 target{ hit->point + random_in_hemisphere(hit->normal) };
        return 0.5 * ray_color(Ray{ hit->point, target - hit->point }, world, depth - 1);
    }

    const Vec3 unit_direction{ normalized(ray.direction) };
    auto t = 0.5 * (unit_direction.y + 1.0);
    return (1.0 - t) * Color{ 1.0, 1.0, 1.0 } + t * Color{ 0.5, 0.7, 1.0 }; // linear interpolation
}

int main() {
    constexpr double aspect_ratio{ 16.0 / 9 };
    constexpr std::int32_t image_width{ 400 };
    constexpr auto image_height = static_cast<std::int32_t>(image_width / aspect_ratio);
    constexpr auto samples_per_pixel = 100;
    constexpr auto max_depth = 50;

    indicators::show_console_cursor(false);
    auto bar = create_progress_bar(image_height);

    Image image{ image_width, image_height };

    World world{
        Sphere{ Point3{ 0, 0, -1 }, 0.5 },
        Sphere{ Point3{ 0, -100.5, -1 }, 100.0 }
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
                pixel_color += ray_color(ray, world, max_depth);
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
