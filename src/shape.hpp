#ifndef RAYTRACINGINONEWEEKEND_SHAPE_HPP
#define RAYTRACINGINONEWEEKEND_SHAPE_HPP

#include <optional>

#include "ray.hpp"
#include "vec3.hpp"

class Material;

class Shape {
public:
    struct Hit {
        Point3 point{};
        Vec3 normal{};
        const Material* material;
        double t{};
        bool front_face{};

        constexpr void set_face_normal(const Ray& ray, const Vec3& outward_normal) {
            front_face = dot(ray.direction, outward_normal) < 0.0;
            normal = front_face ? outward_normal : -outward_normal;
        }
    };

    virtual ~Shape() = default;

    [[nodiscard]] virtual std::optional<Hit> hit(const Ray& ray, double t_min, double t_max) const = 0;
};

#endif //RAYTRACINGINONEWEEKEND_SHAPE_HPP
