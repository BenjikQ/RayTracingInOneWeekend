#ifndef RAYTRACINGINONEWEEKEND_CAMERA_HPP
#define RAYTRACINGINONEWEEKEND_CAMERA_HPP

#include "ray.hpp"
#include "vec3.hpp"

class Camera {
    static constexpr auto aspect_ratio = 16.0 / 9;
    static constexpr auto viewport_height = 2.0;
    static constexpr auto viewport_width = aspect_ratio * viewport_height;
    static constexpr auto focal_length = 1.0;

    Point3 origin_{};
    Vec3 horizontal_{ viewport_width, 0, 0 };
    Vec3 vertical_{ 0, viewport_height, 0 };
    Point3 lower_left_corner_{ origin_ - horizontal_ / 2 - vertical_ / 2 - Vec3{ 0, 0, focal_length } };

public:
    constexpr Camera() = default;

    [[nodiscard]] constexpr Ray ray(double u, double v) const noexcept {
        return { origin_, lower_left_corner_ + u * horizontal_ + v * vertical_ - origin_ };
    }
};

#endif //RAYTRACINGINONEWEEKEND_CAMERA_HPP
