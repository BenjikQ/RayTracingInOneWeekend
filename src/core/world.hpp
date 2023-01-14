#ifndef RAYTRACINGINONEWEEKEND_CORE_WORLD_HPP
#define RAYTRACINGINONEWEEKEND_CORE_WORLD_HPP

#include <memory>
#include <optional>
#include <vector>

#include "geometry/hit.hpp"
#include "shapes/shape.hpp"
#include "utils/color.hpp"

class Ray;

class World : public Shape {
    using Shapes = std::vector<std::unique_ptr<Shape>>;

    Shapes shapes_{};

private:
    [[nodiscard]] std::optional<Hit> hit(const Ray& ray, double t_min, double t_max) const override;

public:
    World() = default;

    template<typename... Ts>
    explicit World(Ts&&... shapes) {
        shapes_.reserve(sizeof...(shapes));
        (shapes_.push_back(std::make_unique<Ts>(shapes)), ...);
    }

    [[nodiscard]] Color ray_color(const Ray& ray, int depth);
};

#endif //RAYTRACINGINONEWEEKEND_CORE_WORLD_HPP
