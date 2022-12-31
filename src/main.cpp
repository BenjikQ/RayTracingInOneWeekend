#include <cstdint>
#include <limits>
#include <vector>

#include <indicators/cursor_control.hpp>
#include <indicators/progress_bar.hpp>

#include <range/v3/all.hpp>

#include "image.hpp"
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

[[nodiscard]] Color ray_color(const Ray& ray, const World& world) {
    static constexpr auto infinity = std::numeric_limits<double>::infinity();

    if (auto hit = world.hit(ray, 0.0, infinity)) {
        return 0.5 * (hit->normal + Color{ 1, 1, 1 });
    }

    const Vec3 unit_direction{ normalized(ray.direction) };
    auto t = 0.5 * (unit_direction.y + 1.0);
    return (1.0 - t) * Color{ 1.0, 1.0, 1.0 } + t * Color{ 0.5, 0.7, 1.0 }; // linear interpolation
}

int main() {
    constexpr double aspect_ratio{ 16.0 / 9 };
    constexpr std::int32_t image_width{ 400 };
    constexpr auto image_height = static_cast<std::int32_t>(image_width / aspect_ratio);

    constexpr double viewport_height{ 2.0 };
    constexpr double viewport_width{ aspect_ratio * viewport_height };
    constexpr double focal_length{ 1.0 };

    Image image{ image_width, image_height };

    indicators::show_console_cursor(false);
    auto bar = create_progress_bar(image_height);

    World world{
        Sphere{ Point3{ 0, 0, -1 }, 0.5 },
        Sphere{ Point3{ 0, -100.5, -1 }, 100.0 }
    };

    constexpr Point3 origin{};
    constexpr Vec3 horizontal{ viewport_width, 0, 0 };
    constexpr Vec3 vertical{ 0, viewport_height, 0 };
    constexpr Point3 lower_left_corner{
        origin - horizontal / 2 - vertical / 2 - Vec3{ 0, 0, focal_length }
    };

    auto rows = ranges::view::iota(0, image_height);
    auto columns = ranges::view::iota(0, image_width);
    auto rng = ranges::view::cartesian_product(rows, columns);

    for (auto&& [row, col] : rng) {
        const double u{ static_cast<double>(col) / (image_width - 1) };
        const double v{ static_cast<double>(image_height - row) / (image_height - 1) };
        const Ray ray{ origin, lower_left_corner + u * horizontal + v * vertical - origin };
        const Color pixel_color{ ray_color(ray, world) };

        image.set_pixel(row, col, pixel_color);

        if (col == 0) {
            bar.tick();
        }
    }

    image.save("image.png");

    indicators::show_console_cursor(true);

    return 0;
}
