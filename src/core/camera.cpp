#include "camera.hpp"

Ray Camera::ray(double s, double t) const noexcept {
    const Vec3 rd{ lens_radius_ * random_in_unit_disk() };
    const Vec3 offset{ u_ * rd.x + v_ * rd.y };
    return {
        origin_ + offset,
        lower_left_corner_ + s * horizontal_ + t * vertical_ - origin_ - offset
    };
}
