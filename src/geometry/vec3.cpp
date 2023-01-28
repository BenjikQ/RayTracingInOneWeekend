#include "vec3.hpp"

#include <utility>

#include "utils/random.hpp"

Vec3 refract(const Vec3& uv, const Vec3& normal, double coefficient) {
    const auto cos_theta = std::min(dot(-uv, normal), 1.0);
    const Vec3 r_out_perpendicular = coefficient * (uv + cos_theta * normal);
    const Vec3 r_out_parallel = -std::sqrt(std::fabs(1.0 - r_out_perpendicular.length_squared())) * normal;
    return r_out_perpendicular + r_out_parallel;
}

Vec3 Vec3::random(double min, double max) {
    return Vec3{ ::random(min, max), ::random(min, max), ::random(min, max) };
}

Vec3 random_in_unit_sphere() {
    while (true) {
        auto p = Vec3::random(-1,1);
        if (p.length_squared() >= 1) continue;
        return p;
    }
}
