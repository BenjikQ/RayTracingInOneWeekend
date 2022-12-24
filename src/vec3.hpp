#ifndef RAYTRACINGINONEWEEKEND_VEC3_HPP
#define RAYTRACINGINONEWEEKEND_VEC3_HPP

#include <cmath>

struct Vec3 {
    double x{}, y{}, z{};

    [[nodiscard]] constexpr Vec3 operator-() const noexcept {
        return Vec3{ -x, -y, -z };
    }

    constexpr Vec3& operator+=(const Vec3& other) noexcept {
        x += other.x;
        y += other.y;
        z += other.z;
        return *this;
    }

    constexpr Vec3& operator-=(const Vec3& other) noexcept {
        x -= other.x;
        y -= other.y;
        z -= other.z;
        return *this;
    }

    constexpr Vec3& operator*=(double t) noexcept {
        x *= t;
        y *= t;
        z *= t;
        return *this;
    }

    constexpr Vec3& operator/=(double t) noexcept {
        return *this *= 1 / t;
    }

    [[nodiscard]] constexpr double length_squared() const noexcept {
        return x * x + y * y + z * z;
    }

    [[nodiscard]] double length() const noexcept {
        return std::sqrt(length_squared());
    }
};

[[nodiscard]] constexpr Vec3 operator+(Vec3 lhs, const Vec3& rhs) noexcept {
    return lhs += rhs;
}

[[nodiscard]] constexpr Vec3 operator-(Vec3 lhs, const Vec3& rhs) noexcept {
    return lhs -= rhs;
}

[[nodiscard]] constexpr Vec3 operator*(Vec3 v, double t) noexcept {
    return v *= t;
}

[[nodiscard]] constexpr Vec3 operator*(double t, Vec3 v) noexcept {
    return v * t;
}

[[nodiscard]] constexpr Vec3 operator/(Vec3 v, double t) noexcept {
    return v /= t;
}

[[nodiscard]] inline Vec3 normalized(const Vec3& v) noexcept {
    return  v / v.length();
}

using Point3 = Vec3;
using Color = Vec3;

#endif //RAYTRACINGINONEWEEKEND_VEC3_HPP
