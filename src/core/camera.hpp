#ifndef RAYTRACINGINONEWEEKEND_CORE_CAMERA_HPP
#define RAYTRACINGINONEWEEKEND_CORE_CAMERA_HPP

#include <cmath>
#include <numbers>

#include "geometry/point3.hpp"
#include "geometry/ray.hpp"
#include "geometry/vec3.hpp"

class Camera {
    [[nodiscard]] static constexpr auto degrees_to_radians(double degrees) {
        return degrees * (std::numbers::pi / 180);
    }

    Point3 origin_;
    Vec3 horizontal_;
    Vec3 vertical_;
    Point3 lower_left_corner_;

public:
    Camera(Point3 look_from, Point3 look_at, Vec3 up, double vertical_fov, double aspect_ratio) {
        const auto theta = degrees_to_radians(vertical_fov);
        const auto h = std::tan(theta / 2);
        const auto viewport_height = 2.0 * h;
        const auto viewport_width = aspect_ratio * viewport_height;

        const auto w = normalized(look_from - look_at);
        const auto u = normalized(cross(up, w));
        const auto v = cross(w, u);

        origin_ = look_from;
        horizontal_ = viewport_width * u;
        vertical_ = viewport_height * v;
        lower_left_corner_ = origin_ - horizontal_ / 2 - vertical_ / 2 - w;
    }

    [[nodiscard]] constexpr Ray ray(double s, double t) const noexcept {
        return { origin_, lower_left_corner_ + s * horizontal_ + t * vertical_ - origin_ };
    }
};

#endif //RAYTRACINGINONEWEEKEND_CORE_CAMERA_HPP
