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

    Vec3 u_, v_, w_;
    double lens_radius_;
    Point3 origin_;
    Vec3 horizontal_;
    Vec3 vertical_;
    Point3 lower_left_corner_;

public:
    Camera(Point3 look_from, Point3 look_at, Vec3 up,
           double vertical_fov, double aspect_ratio, double aperture, double focus_distance) {
        const auto theta = degrees_to_radians(vertical_fov);
        const auto h = std::tan(theta / 2);
        const auto viewport_height = 2.0 * h;
        const auto viewport_width = aspect_ratio * viewport_height;

        w_ = normalized(look_from - look_at);
        u_ = normalized(cross(up, w_));
        v_ = cross(w_, u_);
        lens_radius_ = aperture / 2;

        origin_ = look_from;
        horizontal_ = focus_distance * viewport_width * u_;
        vertical_ = focus_distance * viewport_height * v_;
        lower_left_corner_ = origin_ - horizontal_ / 2 - vertical_ / 2 - focus_distance * w_;
    }

    [[nodiscard]] Ray ray(double s, double t) const noexcept;
};

#endif //RAYTRACINGINONEWEEKEND_CORE_CAMERA_HPP
