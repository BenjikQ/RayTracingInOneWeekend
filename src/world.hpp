#ifndef RAYTRACINGINONEWEEKEND_WORLD_HPP
#define RAYTRACINGINONEWEEKEND_WORLD_HPP

#include <memory>
#include <optional>
#include <vector>

#include "shape.hpp"
#include "sphere.hpp"

class World : public Shape {
    using Shapes = std::vector<std::unique_ptr<Shape>>;

    Shapes shapes_{};

public:
    World() = default;

    template<typename... Ts>
    explicit World(Ts&&... shapes) {
        shapes_.reserve(sizeof...(shapes));
        (shapes_.push_back(std::make_unique<Ts>(shapes)), ...);
    }

    [[nodiscard]] std::optional<Hit> hit(const Ray& ray, double t_min, double t_max) const override;
};

#endif //RAYTRACINGINONEWEEKEND_WORLD_HPP
