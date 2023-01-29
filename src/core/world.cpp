#include "world.hpp"

#include <limits>

#include "geometry/ray.hpp"
#include "geometry/vec3.hpp"
#include "materials/material.hpp"

std::optional<Hit> World::hit(const Ray& ray, double t_min, double t_max) const {
    Hit latest_hit{};
    bool hit_anything{ false };
    double closest_so_far{ t_max };

    for (const auto& shape : shapes_) {
        if (auto hit = shape->hit(ray, t_min, closest_so_far)) {
            hit_anything = true;
            closest_so_far = hit->t;
            latest_hit = *hit;
        }
    }

    return hit_anything ? std::optional(latest_hit) : std::nullopt;
}

Color World::ray_color(const Ray& ray, int depth) const {
    static constexpr auto infinity = std::numeric_limits<double>::infinity();

    if (depth <= 0) {
        return {};
    }

    if (auto hit = this->hit(ray, 0.001, infinity)) {
        Ray scattered;
        Color attenuation;
        if (hit->material->scatter(ray, *hit, attenuation, scattered)) {
            return attenuation * ray_color(scattered, depth - 1);
        }
        return Color{};
    }

    const Vec3 unit_direction{ normalized(ray.direction) };
    auto t = 0.5 * (unit_direction.y + 1.0);
    return (1.0 - t) * Color{ 1.0, 1.0, 1.0 } + t * Color{ 0.5, 0.7, 1.0 }; // linear interpolation
}
