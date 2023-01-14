#ifndef RAYTRACINGINONEWEEKEND_SHAPES_SHAPE_HPP
#define RAYTRACINGINONEWEEKEND_SHAPES_SHAPE_HPP

#include <optional>

class Material;
struct Hit;
struct Ray;

class Shape {
public:
    virtual ~Shape() = default;

    [[nodiscard]] virtual std::optional<Hit> hit(const Ray& ray, double t_min, double t_max) const = 0;
};

#endif //RAYTRACINGINONEWEEKEND_SHAPES_SHAPE_HPP
