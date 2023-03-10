#ifndef RAYTRACINGINONEWEEKEND_SPHERE_HPP
#define RAYTRACINGINONEWEEKEND_SPHERE_HPP

#include <optional>

#include "geometry/hit.hpp"
#include "geometry/point3.hpp"
#include "shapes/shape.hpp"

class Material;
struct Ray;

class Sphere : public Shape {
    Point3 center_{};
    double radius_{};
    const Material& material_;

public:
    Sphere(const Point3& center, double radius, const Material& material)
        : center_{ center }
        , radius_{ radius }
        , material_{ material }
    {}

    [[nodiscard]] std::optional<Hit> hit(const Ray& ray, double t_min, double t_max) const override;
};

#endif //RAYTRACINGINONEWEEKEND_SPHERE_HPP
