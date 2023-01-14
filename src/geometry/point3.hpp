#ifndef RAYTRACINGINONEWEEKEND_GEOMETRY_POINT3_HPP
#define RAYTRACINGINONEWEEKEND_GEOMETRY_POINT3_HPP

#include "geometry/vec3.hpp"

struct Point3 {
    double x{}, y{}, z{};

    constexpr Point3& operator+=(const Vec3& v) noexcept {
        x += v.x;
        y += v.y;
        z += v.z;
        return *this;
    }

    constexpr Point3& operator-=(const Vec3& v) noexcept {
        x -= v.x;
        y -= v.y;
        z -= v.z;
        return *this;
    }
};

[[nodiscard]] constexpr Point3 operator+(Point3 p, const Vec3& v) noexcept {
    return p += v;
}

[[nodiscard]] constexpr Point3 operator-(Point3 p, const Vec3& v) noexcept {
    return p -= v;
}

[[nodiscard]] constexpr Vec3 operator-(const Point3& lhs, const Point3& rhs) noexcept {
    return { lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z };
}

#endif //RAYTRACINGINONEWEEKEND_GEOMETRY_POINT3_HPP
