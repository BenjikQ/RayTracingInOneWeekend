#include "sphere.hpp"

#include <cmath>

#include "geometry/ray.hpp"
#include "materials/material.hpp"

std::optional<Hit> Sphere::hit(const Ray& ray, double t_min, double t_max) const {
    const Vec3 origin_to_center{ ray.origin - center_ };
    const auto a = ray.direction.length_squared();
    const auto half_b = dot(ray.direction, origin_to_center);
    const auto c = origin_to_center.length_squared() - radius_ * radius_;
    const auto discriminant = half_b * half_b - a * c;
    if (discriminant < 0.0) {
        return {};
    }

    auto in_range = [t_min, t_max](double t) {
        return t >= t_min && t <= t_max;
    };

    const auto sqrt_discriminant = std::sqrt(discriminant);
    auto root = (-half_b - sqrt_discriminant) / a;
    if (!in_range(root)) {
        root = (-half_b + sqrt_discriminant) / a;
        if (!in_range(root)) {
            return {};
        }
    }

    auto point = ray.at(root);
    auto outward_normal = (point - center_) / radius_;
    auto t = root;
    Hit hit{ point, outward_normal, &material_, t };
    hit.set_face_normal(ray, outward_normal);

    return hit;
}
