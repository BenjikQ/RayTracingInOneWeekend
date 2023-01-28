#ifndef RAYTRACINGINONEWEEKEND_GEOMETRY_VEC3_HPP
#define RAYTRACINGINONEWEEKEND_GEOMETRY_VEC3_HPP

#include <cmath>
#include <cstdlib>

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

    [[nodiscard]] bool near_zero() const noexcept {
        constexpr auto epsilon = 1e-8;
        return (std::abs(x) < epsilon) && (std::abs(y) < epsilon) && (std::abs(z) < epsilon);
    }

    [[nodiscard]] static Vec3 random(double min, double max);
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

[[nodiscard]] constexpr double dot(const Vec3& lhs, const Vec3& rhs) noexcept {
    return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z;
}

[[nodiscard]] constexpr Vec3 reflect(const Vec3& vec, const Vec3& normal) noexcept {
    return vec - 2 * dot(vec, normal) * normal;
}

[[nodiscard]] Vec3 refract(const Vec3& uv, const Vec3& normal, double coefficient);

[[nodiscard]] Vec3 random_in_unit_sphere();

#endif //RAYTRACINGINONEWEEKEND_GEOMETRY_VEC3_HPP
