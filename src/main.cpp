#include <memory>
#include <vector>

#include <indicators/cursor_control.hpp>

#include "core/camera.hpp"
#include "core/world.hpp"
#include "geometry/point3.hpp"
#include "geometry/ray.hpp"
#include "materials/dielectric.hpp"
#include "materials/lambertian.hpp"
#include "materials/material.hpp"
#include "materials/metal.hpp"
#include "shapes/sphere.hpp"
#include "utils/color.hpp"
#include "utils/image.hpp"
#include "utils/progress_bar.hpp"
#include "utils/random.hpp"

#if defined(_OPENMP)
#pragma omp declare reduction(color_add : Color : \
                              omp_out += omp_in) \
                    initializer(omp_priv = Color{})
#endif

[[nodiscard]] static auto random_double() noexcept {
    return random(0.0, 1.0);
}

[[nodiscard]] static const World& random_scene() {
    static auto ground = create_material<Lambertian>(Color{ 0.5, 0.5, 0.5 });
    static auto material1 = create_material<Dielectric>(1.5);
    static auto material2 = create_material<Lambertian>(Color{ 0.4, 0.2, 0.1 });
    static auto material3 = create_material<Metal>(Color{ 0.7, 0.6, 0.5 }, 0.0);

    static std::vector<std::unique_ptr<Material>> materials{};
    materials.reserve(128);

    static World world{
        Sphere{ Point3{ 0, -1000, 0 }, 1000, *ground },
        Sphere{ Point3{ 0, 1, 0 }, 1, *material1 },
        Sphere{ Point3{ -4, 1, 0 }, 1, *material2 },
        Sphere{ Point3{ 4, 1, 0 }, 1, *material3 },
    };

    for (int x = -11; x < 11; ++x) {
        for (int z = -11; z < 11; ++z) {
            const Point3 center{ x + 0.9 * random_double(), 0.2, z + 0.9 * random_double() };
            if ((center - Point3{ 4, 0.2, 0 }).length_squared() > 0.81) {
                auto choose_material = random_double();
                if (choose_material < 0.8) {
                    // diffuse
                    const auto albedo = Color::random(0.0, 1.0) * Color::random(0.0, 1.0);
                    materials.push_back(create_material<Lambertian>(albedo));
                } else if (choose_material < 0.95) {
                    // metal
                    const auto albedo = Color::random(0.5, 1);
                    const auto fuzz = random(0, 0.5);
                    materials.push_back(create_material<Metal>(albedo, fuzz));
                } else {
                    // glass
                    materials.push_back(create_material<Dielectric>(1.5));
                }
                world.add(Sphere{ center, 0.2, *materials.back() });
            }
        }
    }

    return world;
}

int main() {
    constexpr double aspect_ratio{ 3.0 / 2 };
    constexpr int image_width{ 1200 };
    constexpr auto image_height = static_cast<int>(image_width / aspect_ratio);
    constexpr auto samples_per_pixel = 500;
    constexpr auto max_depth = 50;

    indicators::show_console_cursor(false);
    auto bar = create_progress_bar(image_height);

    Image image{ image_width, image_height };

    const auto& world = random_scene();

    constexpr Point3 look_from{ 13, 2, 3 };
    constexpr Point3 look_at{ 0, 0, 0 };
    constexpr Vec3 up{ 0, 1, 0 };
    const double distance_to_focus{ 10.0 };
    constexpr double aperture{ 0.1 };
    Camera camera{ look_from, look_at, up, 20, aspect_ratio, aperture, distance_to_focus };

    for (int row = image_height - 1; row >= 0; --row) {
        for (int col = 0; col < image_width; ++col) {
            Color pixel_color{};
            int sample;

#if defined(_OPENMP)
#pragma omp parallel for private(sample) reduction(color_add : pixel_color)
#endif
            for (sample = 0; sample < samples_per_pixel; ++sample) {
                const double u{ (static_cast<double>(col) + random_double()) / (image_width - 1) };
                const double v{ (static_cast<double>(row) + random_double()) / (image_height - 1) };
                const Ray ray{ camera.ray(u, v) };
                pixel_color += world.ray_color(ray, max_depth);
            }
            image.set_pixel(row, col, pixel_color, samples_per_pixel);
        }
        bar.tick();
    }

    image.save("image.png");
    indicators::show_console_cursor(true);

    return 0;
}
