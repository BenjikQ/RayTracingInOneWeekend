#ifndef RAYTRACINGINONEWEEKEND_UTILS_COLOR_HPP
#define RAYTRACINGINONEWEEKEND_UTILS_COLOR_HPP

struct Color {
    double r{}, g{}, b{};

    constexpr Color& operator+=(const Color& other) noexcept {
        r += other.r;
        g += other.g;
        b += other.b;
        return *this;
    }

    constexpr Color& operator*=(double t) noexcept {
        r *= t;
        g *= t;
        b *= t;
        return *this;
    }

    constexpr Color& operator*=(const Color& other) noexcept {
        r *= other.r;
        g *= other.g;
        b *= other.b;
        return *this;
    }

    constexpr Color& operator/=(double t) noexcept {
        r /= t;
        g /= t;
        b /= t;
        return *this;
    }
};

[[nodiscard]] constexpr Color operator+(Color lhs, const Color& rhs) noexcept {
    return lhs += rhs;
}

[[nodiscard]] constexpr Color operator*(Color c, double t) noexcept {
    return c *= t;
}

[[nodiscard]] constexpr Color operator*(double t, Color c) noexcept {
    return c * t;
}

[[nodiscard]] constexpr Color operator*(Color lhs, const Color& rhs) noexcept {
    return lhs *= rhs;
}

[[nodiscard]] constexpr Color operator/(Color c, double t) noexcept {
    return c /= t;
}

#endif //RAYTRACINGINONEWEEKEND_UTILS_COLOR_HPP
