#include "world.hpp"

std::optional<Shape::Hit> World::hit(const Ray& ray, double t_min, double t_max) const {
    Shape::Hit latest_hit{};
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
