#ifndef RAYTRACINGINONEWEEKEND_RAY_HPP
#define RAYTRACINGINONEWEEKEND_RAY_HPP

#include "vec3.hpp"

struct Ray {
    Point3 origin{};
    Vec3 direction{};

    [[nodiscard]] constexpr Point3 at(double t) const noexcept {
        return origin + t * direction;
    }
};

#endif //RAYTRACINGINONEWEEKEND_RAY_HPP
